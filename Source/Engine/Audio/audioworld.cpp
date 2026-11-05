#include "Engine/session.h"
#include "LIBC.H"
#include "include_asm.h"
#include "Common/cartridgereadworker.h"
#include "Texture/cartridge_dma_and_audio_timing_views.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "types.h"
#include "libgultra/alunlink.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Render/setn64_getpacksection.h"
#include "Engine/Audio/audioworld.h"
#include "Engine/defs.h"
#include "Common/audio_context.h"
#include "Common/gameplay_camera.h"
#include "Common/ppdecom_unpackresource.h"
#include "Common/alauxbus_s.h"
#include "Common/audio_initialize.h"
#include "Common/shared_gameslot.h"
#include "Common/runtime_declarations.h"
#include "Common/audio_voice_slots.h"
#include "Common/sharedplayer.h"
#include "Common/listnode.h"
#include "Common/os_timer_interrupt_internals.h"
#include "Common/menu_match_globals.h"
#include "Common/self.h"
#include "Audio/audio_updatemusicfade.h"
#include "Audio/voice.h"
#include "Channel/channel_startnotevoice.h"
#include "Engine/Audio/RAXPlayer.h"
#include "Engine/Cache/loader.h"
#include "Engine/Cache/mutex.h"
#include "Gsky/sky_postscaledscreenmessage.h"
#include "Sound/sound.h"
#include "Common/effectrender.h"
#include "PR/os_cache.h"
#include "Common/gameplay_round_rules.h"
#include "Common/vector4f.h"
#include "Common/music_track_volume.h"
#include "Common/externs.h"
#include "Texture/sound_updateaudiocontext.h"
#include "AUDIO/AUDIO.H"
#include "Fade/fade.h"
#include "Render/setn64_updatefadetransition.h"
#include "Common/soundvoicepool.h"
#include "Audio/audio_chooseweightedsoundvariant.h"
#include "Os/audio_stopmusic.h"
#include "Sequencer/audio_loadmusicsequence.h"
#include "Audio/list_and_channel_views.h"
#include "Voice/voice.h"
#include "Common/soundinfo.h"
#include "Common/format.h"
#include "Common/resident_event_handler.h"
#include "data_overlay_layouts.h"
#include "System/engine_data_source.h"

/* SOUND.CPP */

/* Returns the physical address of a cached copy of a data block: finds the cache entry keyed by the
 * block's address and refreshes the copy (and flushes it from the data cache) when the size changed;
 * otherwise reuses a free entry or allocates and links a new one, copies the block into it and
 * marks it in use. */

/* Returns the physical address of a ROM offset through the ROM window cache: a cached window
 * covering the offset and length is stamped with the current frame; otherwise a free window node is
 * linked in address order (or at the head), aligned to an even start, stamped, counted, filled from ROM
 * through Cartridge_SubmitReadChunks and its buffer address returned with the odd byte added back. */

void Sound_RetireCompletedSampleWindows(void) {
    u32 i;
    s32 value;
    Window *node;
    Window *next;

    value = 0;
    for (i = 0; i < g_audioDmaPendingReadCount; i++) {
        osRecvMesg(&g_audioDmaCompletionQueue, &value, 1);
    }

    node = g_audioDmaUsedWindowHead[0];
    if (node != 0) {
        do {
            next = node->next;
            if (node->frame + 1 < g_audioTaskFrameIndex) {
                if (g_audioDmaUsedWindowHead[0] == node) {
                    g_audioDmaUsedWindowHead[0] = next;
                }
                alUnlink((ListLink *)node);
                if (g_audioDmaUsedWindowHead[1] != 0) {
                    alLink(node, (void **)g_audioDmaUsedWindowHead[1]);
                } else {
                    g_audioDmaUsedWindowHead[1] = node;
                    node->next = 0;
                    node->prev = 0;
                }
            }
            node = next;
        } while (node != 0);
    }

    g_audioDmaPendingReadCount = 0;
    g_audioTaskFrameIndex++;
}

u32 Sound_GetCachedAudioBlockAddress(void *block, s32 size) {
    CacheEntry *entry;
    CacheEntry *reusableEntry;

    reusableEntry = 0;
    for (entry = g_audioCacheCountdownHead; entry != 0; entry = entry->next) {
        if (entry->key == block) {
            entry->state = 3;
            if (entry->size != size) {
                entry->size = size;
                Libc_CopyBytes(entry->data, block, size);
                osWritebackDCache(entry->data, size);
            }
            return osVirtualToPhysical(entry->data);
        }
        if (entry->state == 0) {
            reusableEntry = entry;
        }
    }
    if (reusableEntry == 0) {
        reusableEntry = (CacheEntry *)alHeapDBAlloc(0, 0, g_audioHeap, 1, 144);
        reusableEntry->next = g_audioCacheCountdownHead;
        g_audioCacheCountdownHead = reusableEntry;
        g_audioCacheEntryAllocCount++;
    }
    reusableEntry->key = block;
    reusableEntry->state = 3;
    reusableEntry->size = size;
    Libc_CopyBytes(reusableEntry->data, block, size);
    return osVirtualToPhysical(reusableEntry->data);
}

u32 Sound_GetSampleDmaWindowAddress(s32 offset, s32 length) {
    Window *window;
    Window *after;
    Window **pool;
    u32 address;
    s32 end;
    s32 top;
    s32 odd;
    s32 word;

    after = 0;
    address = offset + g_audioSampleRomBase;
    end = address + length;
    for (window = g_audioDmaState.firstUsed; window != 0; window = window->next) {
        top = window->base + 0x300;
        word = window->base;
        if (address < word) {
            break;
        }
        after = window;
        if (top >= end) {
            window->frame = g_audioTaskFrameIndex;
            return osVirtualToPhysical(window->buffer + address - window->base);
        }
    }
    pool = &g_audioDmaState.firstFree;
    window = *pool;
    *pool = window->next;
    alUnlink((ListLink *)window);
    if (after != 0) {
        alLink(window, after);
    } else if (pool[-1] != 0) {
        after = pool[-1];
        pool[-1] = window;
        window->next = after;
        window->prev = 0;
        after->prev = window;
    } else {
        pool[-1] = window;
        window->next = 0;
        window->prev = 0;
    }
    odd = address & 1;
    address -= odd;
    window->base = address;
    window->frame = g_audioTaskFrameIndex;
    word = window->buffer;
    g_audioDmaPendingReadCount++;
    Cartridge_SubmitReadChunks(&g_cartridgeReadWorker, address, 768, word, &g_audioDmaCompletionQueue, 0, 1);
    return osVirtualToPhysical(word) + odd;
}

typedef struct AudioBankHeader {
    s32 reserved0;
    s32 table;
    s32 reserved8;
    ALBankFile *bankFile;
} AudioBankHeader;

void *Vhandler_AllocateVirtualRegion(s32 byteCount, s32 arg1_unused, s32 allocationMode);
static inline void LockEnter(MenuRules *lock) {
    u32 mask = __osDisableInt();
    if (++lock->locked != 1) {
        __osRestoreInt(mask);
        osRecvMesg(lock, 0, 1);
    } else {
        __osRestoreInt(mask);
    }
}
static inline void LockLeave(MenuRules *lock) {
    u32 mask = __osDisableInt();
    if (--lock->locked != 0) {
        __osRestoreInt(mask);
        osSendMesg(lock, 0, 1);
    } else {
        __osRestoreInt(mask);
    }
}

/* Initialises the audio context: creates and takes its lock, sets up the frame heap and the synthesizer,
 * loads the sound bank and sorts the first instrument sounds by address, creates the sound player, clears the
 * voice handles and seeds the mix volumes from the saved settings bytes, then releases the lock. */
void Sound_InitializeContext(GameAudioContext *ctx) {
    ALSynConfig config;
    AudioInitializeTiming timing;
    AudioBankHeader *loaded;
    ALInstrument *instrument;
    ALSound *swap;
    s32 size;
    s32 j, i;
    s32 n;

    Mutex_InitializeQueueLock(&ctx->lock);
    LockEnter(&ctx->lock);
    ctx->soundState = 0;
    alHeapInit(ctx->frames, g_audioContextHeapBuffer, g_audioContextHeapBytes);
    config.maxVVoices = 37;
    config.maxPVoices = 37;
    config.maxUpdates = 256;
    config.fxType = 6;
    config.params = &g_audioFxConfigParams;
    timing.frequency = 22050;
    timing.frameTime = 1;
    config.dmaproc = 0;
    config.heap = ctx->frames;
    timing.samples = 2048;
    Audiomgr_InitializeAudioWorker(&config, g_audioWorkerThreadPriority, &timing);
    g_audioSampleRomBase = Defs_ReadResourceWord(8);
    size = Defs_ReadResourceWord(4) - Defs_ReadResourceWord(0);
    loaded = Vhandler_AllocateVirtualRegion(size, 0, Defs_ReadResourceWord(0));
    ctx->soundTable = loaded->table;
    ctx->resource = loaded->bankFile;
    ctx->font = ctx->resource->bankArray[0];
    Sound_LoadSoundAndSequenceTables(ctx);
    Audio_InitializeMusicPlayer(ctx->panel, ctx);
    instrument = ctx->font->instArray[0];
    for (i = 0; i < instrument->soundCount; i++) {
        for (j = i + 1; j < instrument->soundCount; j++) {
            if ((u32)instrument->soundArray[j] < (u32)instrument->soundArray[i]) {
                swap = instrument->soundArray[i];
                instrument->soundArray[i] = instrument->soundArray[j];
                instrument->soundArray[j] = swap;
            }
        }
    }
    ctx->maximumSoundCount = 17;
    ctx->eventCount = 192;
    ctx->soundHeap = ctx->frames;
    alSndpNew(ctx->list, &ctx->maximumSoundCount);
    {
        s16 noHandle = -1;

        for (n = 15; n >= 0; n--) {
            ctx->handles[n] = noHandle;
        }
    }
    ctx->selectedHandle = -1;
    ctx->selectedSound = -1;
    ctx->soundCounter = 0;
    ctx->frame = 0;
    ctx->selectedEntry = 0;
    ctx->randomPan = 64;
    ctx->listenerCamera = 0;
    ctx->dialogEnabled = 0;
    ctx->effectMixOffset = 0;
    AudioWorld_InitializePendingSoundPool(ctx->view, ctx);
    Audio_InitializeVoicePool(ctx->menu, ctx);
    ctx->red = g_gameSettings.volume[1] * g_soundContextVolumePercentScale;
    ctx->green = g_gameSettings.volume[0] * g_soundContextVolumePercentScale;
    ctx->blue = g_gameSettings.volume[2] * g_soundContextVolumePercentScale;
    ctx->voiceMixValue = 0;
    ctx->spatialPanMode = g_gameSettings.stereo;
    ctx->spatialAudioEnabled = 1;
    ctx->alpha = g_soundContextInitialPlaybackScale;
    Audio_InitializeDialogPlayer(ctx->dialog, ctx);
    g_audioContextInitialized = 1;
    LockLeave(&ctx->lock);
}

void Sound_LoadSoundAndSequenceTables(GameAudioContext *ctx) {
    s32 total;
    s32 *index;
    s32 *rest;
    s32 *tables;
    s32 *names;
    s32 *refs;
    s32 *sounds;
    s32 *seq;
    s32 *group;
    void *section;

    total = Defs_ReadResourceWord(20) - Defs_ReadResourceWord(16);
    ctx->soundData = Vhandler_AllocateVirtualRegion(total, 0, Defs_ReadResourceWord(16));
    section = SetN64_GetPackSection(ctx->soundData, 0);
    SetN64_GetPackSection(ctx->soundData, 1);
    tables = SetN64_GetPackSection(section, 0);
    names = SetN64_GetPackSection(section, 1);
    index = SetN64_GetPackSection(section, 2);
    ctx->instrumentIndex = index;
    ctx->instrumentCount = *index;
    ctx->instrumentData = tables + 2;
    ctx->envelopeData = names + 2;
    rest = SetN64_GetPackSection(section, 3);
    refs = SetN64_GetPackSection(section, 4);
    sounds = SetN64_GetPackSection(section, 5);
    ctx->metadataSectionThreeCount = rest[1];
    ctx->metadataSectionThree = (AudioMetadataRecord *)(rest + 2);
    ctx->metadataSectionFourCount = refs[1];
    ctx->metadataSectionFour = (AudioMetadataRecord *)(refs + 2);
    ctx->metadataSectionFiveCount = sounds[1];
    ctx->metadataSectionFive = (AudioMetadataRecord *)(sounds + 2);
    group = SetN64_GetPackSection(ctx->soundData, 1);
    seq = SetN64_GetPackSection(group, 0);
    ctx->sequenceData = seq + 2;
    ctx->sequenceCount = seq[1];
    ctx->sequenceIndex = SetN64_GetPackSection(group, 1);
}

/* Refreshes the voice playing sound id: an unknown id returns -1, slot 16 is handed to the spatial voice
 * update with the passed-through position, a finished voice is flagged and the selection cleared; otherwise
 * pitch, volume, pan and gain are pushed to the player. The not-found path has a dead conditional store:
 * flow deletes it but its label stays until jump2, so the -1 return value is hoisted above the test. */
/* The voice mix block at of each Voice (Channel_InitializeVoiceMix views it the same way). */
typedef struct VoiceMix {
    s32 frame, reserved4;
    s32 left, right;
    s16 volume;
    u8 reserved12[2];
    f32 pitch;
    u8 reserved18;
    u8 pan;
    u8 reserved1A[2];
    f32 attenuation;
} VoiceMix;

static inline s32 findVoiceById(GameAudioContext *context, s32 id) {
    s32 i;
    Voice *voice = context->voices;
    for (i = 0; i < 17; i++, voice++) {
        if (voice->secondaryKey == id) {
            return i;
        }
    }
    return -1;
}
s32 Sound_UpdateSoundSlot(GameAudioContext *context, s32 id, s32 updateFlags, CVector3 *position) {
    s16 index;
    VoiceMix *mix;
    ALSndPlayer *player;
    f32 gain;
    if (id == -1) {
        return -1;
    }
    index = findVoiceById(context, id);
    if (index == -1) {
        if (id != 0) {
            mix = 0;
        }
        return -1;
    }
    if (index == 16) {
        AudioWorld_StartSpatialVoice((AudioSpatialVoiceManagerView *)context->view, index, id, position);
        return -1;
    }
    mix = (VoiceMix *)context->voices[index].reserved10;
    player = context->list;
    if (mix->left == 0 && !(context->voices[index].flags & 4)) {
        context->voices[index].flags |= 8;
        context->selectedHandle = -1;
        return 0;
    }
    if (!Audio_GetVoiceSoundState((AudioVoiceSoundSlotView *)context->menu, index)) {
        alSndpSetPitch(player, mix->pitch);
        alSndpSetFXMix(player, (mix->volume + context->effectMixOffset < 128) ? (u8)mix->volume + (u8)context->effectMixOffset : 127);
        alSndpSetPan(player, mix->pan);
        if (context->voices[index].flags & 0x200) {
            gain = context->blue;
        } else {
            gain = context->red;
            if (context->voices[index].musicGainScalingEnabled && context->dialogEnabled) {
                gain *= 0.5f;
            }
        }
        alSndpSetVol(player, (s16)(s32)((f32)mix->left * gain * mix->attenuation));
        if (!context->voices[index].pending) {
            Audio_PlayVoiceSound((AudioVoiceSoundSlotView *)context->menu, index);
        }
    }
    context->selectedHandle = -1;
    return 0;
}

/* Stops every voice playing a sound id while holding the manager's recursive lock: tells
 * AudioWorld_RecyclePendingSoundsByIdentifier about the id, then for each of the 17 voice records whose sound matches it counts the voice
 * and either resets the spare record 16 or clears the voice's pending flag and stops its channel through
 * Audio_StopVoiceSlot when it has a handle; returns the number of voices found (0 for id -1). Lock handling
 * adapted from Audio_StopAudioBySecondaryValue; the voice records are addressed by offset from the manager.
 */

s32 Sound_StopSoundsByIdentifier(void *context, s32 id) {
    void *contextLock;
    void *channelSet;
    s32 lockClaimCount;
    u32 mask;
    u32 releaseInterruptMask;
    s32 found;
    s32 i;
    Voice *voice;

    found = 0;
    if (id == -1) {
        return found;
    }
    contextLock = &((GameAudioContext *)(context))->lock;
    mask = __osDisableInt();
    lockClaimCount = ((MenuRules *)(contextLock))->locked + 1;
    ((MenuRules *)(contextLock))->locked = lockClaimCount;
    if (lockClaimCount != 1) {
        __osRestoreInt(mask);
        osRecvMesg(contextLock, 0, 1);
        channelSet = &((GameAudioContext *)(context))->view[0];
    } else {
        __osRestoreInt(mask);
        channelSet = &((GameAudioContext *)(context))->view[0];
    }
    AudioWorld_RecyclePendingSoundsByIdentifier(channelSet, id);
    for (i = 0; i < 17; i++) {
        if (((GameAudioContext *)context)->voices[i].sound == id) {
            found++;
            voice = &((GameAudioContext *)context)->voices[i];
            if (i == 16) {
                voice->sound = -1;
                voice->priority = 0;
                voice->channel = -1;
                voice->secondaryKey = -1;
                voice->primaryKey = -1;
            } else {
                if (voice->pending > 0) {
                    voice->pending = 0;
                    voice->flags &= ~0x10;
                }
                if ((&((AudioVoiceContextView *)context)->slots)[0].ids[i] != -1) {
                    Audio_StopVoiceSlot(&((GameAudioContext *)(context))->menu[0], i);
                }
            }
        }
    }
    contextLock = &((GameAudioContext *)(context))->lock;
    releaseInterruptMask = __osDisableInt();
    lockClaimCount = ((MenuRules *)(contextLock))->locked - 1;
    ((MenuRules *)(contextLock))->locked = lockClaimCount;
    if (lockClaimCount != 0) {
        __osRestoreInt(releaseInterruptMask);
        osSendMesg(contextLock, 0, 1);
    } else {
        __osRestoreInt(releaseInterruptMask);
    }
    return found;
}

s32 Sound_StartSoundRecord(void *context, SoundVoiceGroupRecord *soundRecord, CVector3 *position, s32 playbackValue,
    s32 voiceUserData, s32 extra, s32 trackedPosition) {
    void *node;

    ((GameAudioContext *)(context))->listenerCamera = Gsky_FindNearestCamera(&g_frontendScreenStatus, position);
    if (soundRecord->flags & 1) {
        if (Audio_HasVoiceWithKey(&((GameAudioContext *)(context))->menu[0], ((GameAudioContext *)(context))->selectedSound) != 0) {
            return -1;
        }
        if (Audio_ComputeDistanceAttenuation(position, &((GameAudioContext *)context)->listenerCamera->position) == 0.0f) {
            return -1;
        }
    }
    if ((soundRecord->flags & 0x1000) && ((GameAudioContext *)(context))->selectedOwner != -1) {
        if (Audio_FindVoiceByKeyPair(&((GameAudioContext *)(context))->menu[0], ((GameAudioContext *)(context))->selectedSound,
            ((GameAudioContext *)(context))->selectedOwner) != -1) {
            return -1;
        }
    }
    if (soundRecord->priority != 0) {
        return AudioWorld_QueuePrioritizedSound(&((GameAudioContext *)(context))->view[0], soundRecord, position, playbackValue, extra);
    }
    if (soundRecord->flags & 0x40) {
        Audio_ReleaseMatchingExclusiveVoice(&((GameAudioContext *)(context))->menu[0], ((GameAudioContext *)(context))->selectedSound, soundRecord->exclusiveKey);
    }
    node = Channel_StartNoteVoice(&((GameAudioContext *)(context))->menu[0], soundRecord, playbackValue, voiceUserData);
    if (node == 0) {
        return -1;
    }
    Audio_SetVoicePositionTracking(node, position, trackedPosition);
    Audio_SetVoiceTrackId(node, ((GameAudioContext *)(context))->selectedSound);
    Audio_InitializeVoiceParameters(node, soundRecord, extra);

    {
        char *queue = &((GameAudioContext *)(context))->lock;
        u32 token = __osDisableInt();
        s32 count = ((MenuRules *)(queue))->locked + 1;
        ((MenuRules *)(queue))->locked = count;
        if (count != 1) {
            __osRestoreInt(token);
            osRecvMesg(queue, 0, 1);
        } else {
            __osRestoreInt(token);
        }
    }
    Sound_UpdateSoundSlot(context, ((struct Draw *)(node))->model, 0, position);
    {
        char *queue = &((GameAudioContext *)(context))->lock;
        u32 token = __osDisableInt();
        s32 count = ((MenuRules *)(queue))->locked - 1;
        ((MenuRules *)(queue))->locked = count;
        if (count != 0) {
            __osRestoreInt(token);
            osSendMesg(queue, 0, 1);
        } else {
            __osRestoreInt(token);
        }
    }
    return 0;
}

static inline void soundAcquireLock(MenuRules *lock) {
    u32 mask = __osDisableInt();
    s32 held = lock->locked + 1;
    lock->locked = held;
    if (held != 1) {
        __osRestoreInt(mask);
        osRecvMesg((OSMesgQueue *)lock, 0, 1);
    } else {
        __osRestoreInt(mask);
    }
}

static inline void soundReleaseLock(MenuRules *lock) {
    u32 mask = __osDisableInt();
    s32 held = lock->locked - 1;
    lock->locked = held;
    if (held != 0) {
        __osRestoreInt(mask);
        osSendMesg((OSMesgQueue *)lock, 0, 1);
    } else {
        __osRestoreInt(mask);
    }
}

typedef struct SoundVoiceGroup {
    s32 stride;
    u32 count;
} SoundVoiceGroup;

/* Voice records follow the group header back to back, `stride` bytes apart. */
static inline SoundVoiceGroupRecord *voiceGroupRecord(SoundVoiceGroup *group, u32 index) {
    return (SoundVoiceGroupRecord *)((u8 *)(group + 1) + index * group->stride);
}

/* The definition range is inclusive; weights are signed 32-bit entries. */
static inline s32 selectSoundVariant(GameAudioContext *context, s32 sound, s16 avoidPrevious) {
    s32 first;
    s32 last;
    s32 total;
    s32 index;
    s32 i;
    s32 threshold;
    total = 0;
    if (context->instrumentCount != 0) {
        if (!Defs_FindSortedGroupRange((u32 *)context->instrumentData, context->instrumentCount, (s16)sound, &first, &last)) {
            return -1;
        }
        index = first;
        if (index != last) {
            for (i = first; i <= last; i++) {
                total += context->envelopeData[i] * 10;
            }
            threshold = Graphu64_NextRandom() % total;
            total = 0;
            for (index = first; index < last; index++) {
                total += context->envelopeData[index] * 10;
                if (total >= threshold) {
                    break;
                }
            }
            if (avoidPrevious && index == context->lastInstrument) {
                if (index == last) {
                    index--;
                } else {
                    index++;
                }
            }
        }
        return index;
    }
    return -1;
}
static inline s32 soundVoiceLimitReached(GameAudioContext *context, s32 sound) {
    s32 count;
    s32 i;
    if (context->selectedHandle != -1) {
        return 1;
    }
    count = 0;
    if (sound < 256) {
        for (i = 0; i < 17; i++) {
            if (context->voices[i].soundId == sound) {
                count++;
            }
        }
        if (count >= 6) {
            return 1;
        }
    }
    return 0;
}

/* Plays sound-bank entry `sound` at `position`: refuses while a handle is selected or when six voices
 * already play the same sound effect, picks a weighted random variant of the entry (sound effects below
 * 0x100 avoid repeating the previous variant and get a random pan), records the entry, sound and owner as
 * the current selection, hands out a play id under the recursive lock and starts every voice record of the
 * variant; returns the play id, or -1 when nothing was started. */
s32 Sound_PlaySoundAtPosition(GameAudioContext *context, s32 sound, CVector3 position, s32 spatialMode, s32 owner) {
    SoundVoiceGroup *group;
    u32 count;
    u32 i;
    s32 index;
    s32 playId;

    if (soundVoiceLimitReached(context, sound)) {
        return -1;
    }
    if (sound < 256) {
        index = selectSoundVariant(context, sound, context->lastInstrument);
        context->randomPan = (s32)Graphu64_RandomFloat(127.0f);
    } else {
        index = selectSoundVariant(context, sound, 0);
    }
    if (index != -1) {
        context->selectedEntry = SetN64_GetPackSection(SetN64_GetPackSection(context->instrumentIndex, (s16)index), 0);
        context->selectedSound = sound;
        context->selectedOwner = owner;
        group = SetN64_GetPackSection(SetN64_GetPackSection(context->instrumentIndex, (s16)index), 1);
        count = group->count;
        if (count != 0) {
            soundAcquireLock(&context->lock);
            playId = ++context->playIdCounter;
            soundReleaseLock(&context->lock);
            if (sound < 256) {
                context->lastInstrument = index;
            }
        } else {
            playId = -1;
        }
        for (i = 0; i < count; i++) {
            Sound_StartSoundRecord(context, voiceGroupRecord(group, i), &position, index,
                playId, 0, spatialMode);
        }
        context->selectedOwner = -1;
        return playId;
    }
    return -1;
}

/* Starts a sound-bank entry: looks up the entry's record in the bank table, resets the current
 * selection (0x2B88/0x2B8C/0x2B90), takes the recursive lock to hand out a new play id (counter
 *), then starts every voice record of the entry through Sound_StartSoundRecord at the given position;
 * returns the play id, or -1 for an out-of-range index or an empty entry. */
s32 Sound_PlayInstrumentAtPosition(GameAudioContext *self, s32 index, CVector3 position, s32 voiceParameter) {
    SoundVoiceGroup *group;
    u32 count;
    u32 i;
    s32 playId;
    if (index >= self->instrumentCount) {
        return -1;
    }
    self->selectedEntry = SetN64_GetPackSection(SetN64_GetPackSection(self->instrumentIndex, (s16)index), 0);
    self->selectedSound = 256;
    self->selectedOwner = -1;
    group = SetN64_GetPackSection(SetN64_GetPackSection(self->instrumentIndex, (s16)index), 1);
    count = group->count;
    if (count != 0) {
        soundAcquireLock(&self->lock);
        playId = ++self->playIdCounter;
        soundReleaseLock(&self->lock);
    } else {
        playId = -1;
    }
    for (i = 0; i < count; i++) {
        Sound_StartSoundRecord(self, voiceGroupRecord(group, i), &position, index, playId, 0, voiceParameter);
    }
    return playId;
}

/* SOUND_UPDATEAUDIOCONTEXT.CPP */



/* Per-frame update of the audio context: refreshes the gain colours and pan mode from the volume settings, updates the
 * voice pool under the context lock, dispatches pending sounds, advances dialog and music, and plays the spatial-audio
 * test sound every fourth frame. Returns the new frame count. */
s32 Sound_UpdateAudioContext(void *context) {
    GameAudioContext *audio = context;
    u8 *bytes = &g_gameSettings.volume[1];
    u32 mask;
    s32 count;

    f32 gainScale = g_audioContextGainScaleConstants[0];

    audio->red = (f32)bytes[0] * gainScale;
    audio->green = (f32)bytes[-1] * gainScale;
    audio->blue = (f32)bytes[1] * gainScale;
    audio->spatialPanMode = bytes[-2];

    mask = __osDisableInt();
    count = audio->lock.locked + 1;
    audio->lock.locked = count;
    if (count != 1) {
        __osRestoreInt(mask);
        osRecvMesg((OSMesgQueue *)&audio->lock, 0, 1);
    } else {
        __osRestoreInt(mask);
    }

    Audio_UpdateVoicePool(&audio->menu[0]);

    mask = __osDisableInt();
    count = audio->lock.locked - 1;
    audio->lock.locked = count;
    if (count != 0) {
        __osRestoreInt(mask);
        osSendMesg((OSMesgQueue *)&audio->lock, 0, 1);
    } else {
        __osRestoreInt(mask);
    }

    AudioWorld_DispatchPendingSounds((char *)&audio->view);
    Audio_UpdateDialogPlayer((char *)&audio->dialog);
    Audio_UpdateMusicFade((char *)&audio->panel);
    Audio_UpdateMusicPlayback((char *)&audio->panel);

    if (g_audioContextInitialized != 0 &&
        audio->spatialAudioEnabled != 0 &&
        SetN64_IsModeThirteen() != 0 &&
        audio->track > 0) {
        CVector3 zero;
        void *result;
        CVector3 *vec;

        zero.z = 0.0f;
        zero.y = 0.0f;
        zero.x = 0.0f;
        result = Gsky_FindNearestCamera(&g_frontendScreenStatus, &zero);
        vec = &((struct PlayerCameraTargetView *)(result))->position;
        if ((audio->frame & 3) == 0) {
            Sound_PlaySoundAtPosition(audio, audio->track, *vec, 0, -1);
        }
    }
    return ++audio->frame;
}

s32 Sound_HasActiveOrPendingSound(struct GameAudioContext *context, s32 queryValue) {
    {
        MenuRules *contextLock;
        s32 lockClaimCount;
        u32 mask;

        contextLock = &context->lock;
        mask = __osDisableInt();
        lockClaimCount = contextLock->locked + 1;
        contextLock->locked = lockClaimCount;
        if (lockClaimCount != 1) {
            __osRestoreInt(mask);
            osRecvMesg(contextLock, 0, 1);
        } else {
            __osRestoreInt(mask);
        }
    }
    if (Audio_HasVoiceOrReservedSlotWithKey(&context->menu[0], queryValue) != 0) {
        MenuRules *contextLock;
        s32 lockClaimCount;
        u32 releaseInterruptMask;

        contextLock = &context->lock;
        releaseInterruptMask = __osDisableInt();
        lockClaimCount = contextLock->locked - 1;
        contextLock->locked = lockClaimCount;
        if (lockClaimCount != 0) {
            __osRestoreInt(releaseInterruptMask);
            osSendMesg(contextLock, 0, 1);
        } else {
            __osRestoreInt(releaseInterruptMask);
        }
        return 1;
    }
    if (AudioWorld_HasPendingSoundWithKey(&context->view[0], queryValue) != 0) {
        MenuRules *contextLock;
        s32 lockClaimCount;
        u32 releaseInterruptMask;

        contextLock = &context->lock;
        releaseInterruptMask = __osDisableInt();
        lockClaimCount = contextLock->locked - 1;
        contextLock->locked = lockClaimCount;
        if (lockClaimCount != 0) {
            __osRestoreInt(releaseInterruptMask);
            osSendMesg(contextLock, 0, 1);
        } else {
            __osRestoreInt(releaseInterruptMask);
        }
        return 1;
    }
    {
        MenuRules *contextLock;
        s32 lockClaimCount;
        u32 releaseInterruptMask;

        contextLock = &context->lock;
        releaseInterruptMask = __osDisableInt();
        lockClaimCount = contextLock->locked - 1;
        contextLock->locked = lockClaimCount;
        if (lockClaimCount != 0) {
            __osRestoreInt(releaseInterruptMask);
            osSendMesg(contextLock, 0, 1);
        } else {
            __osRestoreInt(releaseInterruptMask);
        }
    }
    return 0;
}

void Sound_AcquireContextLock(s32 *engine) {
    MenuRules *menuRules;
    s32 claimCount;
    u32 mask;

    menuRules = &((struct GameAudioContext *)(engine))->lock;
    mask = __osDisableInt();
    claimCount = menuRules->locked + 1;
    menuRules->locked = claimCount;
    if (claimCount != 1) {
        __osRestoreInt(mask);
        osRecvMesg(menuRules, 0, 1);
        return;
    }
    __osRestoreInt(mask);
}

void Sound_ReleaseContextLock(s32 *engine) {
    MenuRules *menuRules;
    s32 remainingClaims;
    u32 mask;

    menuRules = &((struct GameAudioContext *)(engine))->lock;
    mask = __osDisableInt();
    remainingClaims = menuRules->locked - 1;
    menuRules->locked = remainingClaims;
    if (remainingClaims != 0) {
        __osRestoreInt(mask);
        osSendMesg(menuRules, 0, 1);
        return;
    }
    __osRestoreInt(mask);
}

/* AUDIO_CHOOSEWEIGHTEDSOUNDVARIANT.CPP */





/* Picks a weighted random entry from the range Defs_FindSortedGroupRange finds for an id in a scene's table: -1 when
 * the scene has no table or no range, the single entry when the range has one; otherwise each entry weighs
 * ten times its table value, a random draw selects one, and when avoidance is requested and it equals the
 * scene's last pick it steps to the next entry (or back from the last). */

void Audio_StopAudioByKey(GameAudioContext *context, s32 matchValue) {
    {
        s32 *contextLock;
        s32 lockClaimCount;
        u32 mask;

        contextLock = &context->lock;
        mask = __osDisableInt();
        lockClaimCount = ((MenuRules *)(contextLock))->locked + 1;
        ((MenuRules *)(contextLock))->locked = lockClaimCount;
        if (lockClaimCount != 1) {
            __osRestoreInt(mask);
            osRecvMesg(contextLock, 0, 1);
        } else {
            __osRestoreInt(mask);
        }
    }
    Audio_StopVoicesByKey(&context->menu[0], matchValue);
    AudioWorld_RecyclePendingSoundsByKey(&context->view[0], matchValue);
    {
        s32 *contextLock;
        s32 lockClaimCount;
        u32 releaseInterruptMask;

        contextLock = &context->lock;
        releaseInterruptMask = __osDisableInt();
        lockClaimCount = ((MenuRules *)(contextLock))->locked - 1;
        ((MenuRules *)(contextLock))->locked = lockClaimCount;
        if (lockClaimCount != 0) {
            __osRestoreInt(releaseInterruptMask);
            osSendMesg(contextLock, 0, 1);
        } else {
            __osRestoreInt(releaseInterruptMask);
        }
    }
}

void Audio_StopAudioBySecondaryValue(GameAudioContext *context, s32 matchValue) {
    void *contextLock;
    void *record;
    s32 lockClaimCount;
    u32 mask;
    u32 releaseInterruptMask;

    contextLock = &context->lock;
    mask = __osDisableInt();
    lockClaimCount = ((MenuRules *)(contextLock))->locked + 1;
    ((MenuRules *)(contextLock))->locked = lockClaimCount;
    if (lockClaimCount != 1) {
        __osRestoreInt(mask);
        osRecvMesg(contextLock, 0, 1);
        record = &context->menu[0];
    } else {
        __osRestoreInt(mask);
        record = &context->menu[0];
    }
    Audio_StopVoicesBySecondaryValue(record, matchValue);
    AudioWorld_RecyclePendingSoundsByTrack(&context->view[0], matchValue);
    contextLock = &context->lock;
    releaseInterruptMask = __osDisableInt();
    lockClaimCount = ((MenuRules *)(contextLock))->locked - 1;
    ((MenuRules *)(contextLock))->locked = lockClaimCount;
    if (lockClaimCount != 0) {
        __osRestoreInt(releaseInterruptMask);
        osSendMesg(contextLock, 0, 1);
        return;
    }
    __osRestoreInt(releaseInterruptMask);
}

void Audio_StopAudioByMask(GameAudioContext *context, s32 matchMask) {
    void *contextLock;
    void *record;
    s32 lockClaimCount;
    u32 mask;
    u32 releaseInterruptMask;

    contextLock = &context->lock;
    mask = __osDisableInt();
    lockClaimCount = ((MenuRules *)(contextLock))->locked + 1;
    ((MenuRules *)(contextLock))->locked = lockClaimCount;
    if (lockClaimCount != 1) {
        __osRestoreInt(mask);
        osRecvMesg(contextLock, 0, 1);
        record = &context->menu[0];
    } else {
        __osRestoreInt(mask);
        record = &context->menu[0];
    }
    Audio_StopVoicesByFlags(record, matchMask);
    AudioWorld_RecyclePendingSoundsByFlags(&context->view[0], matchMask);
    contextLock = &context->lock;
    releaseInterruptMask = __osDisableInt();
    lockClaimCount = ((MenuRules *)(contextLock))->locked - 1;
    ((MenuRules *)(contextLock))->locked = lockClaimCount;
    if (lockClaimCount != 0) {
        __osRestoreInt(releaseInterruptMask);
        osSendMesg(contextLock, 0, 1);
        return;
    }
    __osRestoreInt(releaseInterruptMask);
}

s32 Audio_PlayPositionedSoundWithScale(GameAudioContext *context, s32 track, CVector3 position, s32 spatialMode, s32 owner, f32 volumeScale) {
    s32 handle;

    context->alpha = volumeScale;
    handle = Sound_PlaySoundAtPosition(context, track, position, spatialMode, owner);
    context->alpha = g_audioContextGainScaleConstants[1];
    return handle;
}

void Audio_PlayPeriodicTrackSound(GameAudioContext *context) {
    CVector3 zero;
    void *result;
    CVector3 *vec;

    if (g_audioContextInitialized != 0 &&
        context->spatialAudioEnabled != 0 &&
        SetN64_IsModeThirteen() != 0 &&
        context->track > 0) {
        {
            register f32 value = 0.0f;

            zero.z = value;
            zero.y = value;
            zero.x = value;
        }
        result = Gsky_FindNearestCamera(&g_frontendScreenStatus, &zero);
        vec = &((struct PlayerCameraTargetView *)(result))->position;
        if ((context->frame & 3) == 0) {
            Sound_PlaySoundAtPosition(context, context->track, *vec, 0, -1);
        }
    }
}

void Audio_SetVolumeSettingOne(GameAudioContext *audioContext, float volume) {
    audioContext->red = volume;
}

void Audio_SetVolumeSettingZero(GameAudioContext *audioContext, int volume) {
    double d = (double)volume;
    if (volume < 0) {
        d = d + g_audioContextUnsignedValueCorrection;
    }
    audioContext->green = (float)d;
}

/** Set the dialog volume of the audio context. */
void Audio_SetDialogVolume(GameAudioContext *audioContext, float value) {
    audioContext->blue = value;
}

/** Return the indexed 12-byte record of metadata section three. */
char *Audio_GetMetadataSectionThreeEntry(GameAudioContext *audioContext, int index) {
    return (char *)&audioContext->metadataSectionThree[index];
}

/** Return the indexed 12-byte record of metadata section four. */
void *Audio_GetMetadataSectionFourEntry(GameAudioContext *audioContext, int entryIndex) {
    return &audioContext->metadataSectionFour[entryIndex];
}

/** Return the indexed 12-byte record of metadata section five. */
void *Audio_GetMetadataSectionFiveEntry(GameAudioContext *audioContext, int entryIndex) {
    return &audioContext->metadataSectionFive[entryIndex];
}

void Audio_StopAudioExceptKey(void *context, s32 matchValue) {
    {
        s32 *contextLock;
        s32 lockClaimCount;
        u32 mask;

        contextLock = &((GameAudioContext *)(context))->lock;
        mask = __osDisableInt();
        lockClaimCount = ((MenuRules *)(contextLock))->locked + 1;
        ((MenuRules *)(contextLock))->locked = lockClaimCount;
        if (lockClaimCount != 1) {
            __osRestoreInt(mask);
            osRecvMesg(contextLock, 0, 1);
        } else {
            __osRestoreInt(mask);
        }
    }
    Audio_StopVoicesExceptKey(&((GameAudioContext *)(context))->menu[0], matchValue);
    AudioWorld_RecyclePendingSoundsExceptKey(&((GameAudioContext *)(context))->view[0], matchValue);
    {
        s32 *contextLock;
        s32 lockClaimCount;
        u32 releaseInterruptMask;

        contextLock = &((GameAudioContext *)(context))->lock;
        ((GameAudioContext *)(context))->effectMixOffset = 0;
        releaseInterruptMask = __osDisableInt();
        lockClaimCount = ((MenuRules *)(contextLock))->locked - 1;
        ((MenuRules *)(contextLock))->locked = lockClaimCount;
        if (lockClaimCount != 0) {
            __osRestoreInt(releaseInterruptMask);
            osSendMesg(contextLock, 0, 1);
        } else {
            __osRestoreInt(releaseInterruptMask);
        }
    }
    Audio_StopDialogPlayer((char *)&((GameAudioContext *)context)->dialog);
}

/** Calls Audio_FadeOutMusic on the panel of the audio context at the given address. */
void Audio_FadeOutContextMusic(int contextAddress) {
    Audio_FadeOutMusic((char *)&((GameAudioContext *)contextAddress)->panel);
}

/** Set the voice mix value of the audio context. */
void Audio_SetVoiceMixValue(GameAudioContext *context, int mixValue) {
    context->voiceMixValue = mixValue;
}

int Audio_GetVoiceMixValue(GameAudioContext *context) {
    return context->voiceMixValue;
}

/** Enable or disable spatial audio for the context. */
void Audio_SetPeriodicSoundEnabled(GameAudioContext *audioContext, int value) {
    audioContext->spatialAudioEnabled = value;
}

/** Set the camera that spatial audio listens from. */
void Audio_SetListenerCamera(GameAudioContext *object, int value) {
    object->listenerCamera = value;
}

/** Return the spatial pan mode of the context. */
int Audio_GetSpatialPanMode(GameAudioContext *audioContext) {
    return audioContext->spatialPanMode;
}

/** Set the spatial pan mode of the context. */
void Audio_SetSpatialPanMode(GameAudioContext *audioContext, int panMode) {
    audioContext->spatialPanMode = panMode;
}

void *Audio_GetSoundPlayer(void *audioContext) {
    return &((GameAudioContext *)(audioContext))->list[0];
}

/** Enable or disable music gain scaling for dialog. */
void Audio_SetMusicGainScalingEnabled(GameAudioContext *object, int value) {
    object->dialogEnabled = value;
}

s32 Audio_CountSoundVoices(char *obj, s32 owner)
{
    s32 count;
    s32 i;

    count = 0;
    {
        s32 *contextLock;
        s32 lockDepth;
        u32 savedInterruptMask;

        contextLock = &((GameAudioContext *)(obj))->lock;
        savedInterruptMask = __osDisableInt();
        lockDepth = ((MenuRules *)(contextLock))->locked + 1;
        ((MenuRules *)(contextLock))->locked = lockDepth;
        if (lockDepth != 1) {
            __osRestoreInt(savedInterruptMask);
            osRecvMesg(contextLock, 0, 1);
        } else {
            __osRestoreInt(savedInterruptMask);
        }
    }
    for (i = 0; i < 17; i++) {
        if (((GameAudioContext *)obj)->voices[i].sound == owner) {
            count++;
        }
    }
    {
        s32 *contextLock;
        s32 lockDepth;
        u32 savedInterruptMask;

        contextLock = &((GameAudioContext *)(obj))->lock;
        savedInterruptMask = __osDisableInt();
        lockDepth = ((MenuRules *)(contextLock))->locked - 1;
        ((MenuRules *)(contextLock))->locked = lockDepth;
        if (lockDepth != 0) {
            __osRestoreInt(savedInterruptMask);
            osSendMesg(contextLock, 0, 1);
        } else {
            __osRestoreInt(savedInterruptMask);
        }
    }
    return count;
}

/** Calls Audio_StopMusic on the panel of the audio context at the given address. */
void Audio_StopContextMusic(int contextAddress) {
    Audio_StopMusic((char *)&((GameAudioContext *)contextAddress)->panel);
}

/* Clamps a level to between zero and g_audioLevelMaximum, scales it by g_audioLevelIntegerScale and stores it as an integer
   at 0x2B9C of the object. */

void Audio_SetClampedAudioLevel(AudioLevelSettingView *obj, float value) {
    float v;
    float max = g_audioLevelMaximum;
    if (value > max || !(value < 0.0f)) {
        v = value;
        if (v > max) {
            v = max;
        }
    } else {
        v = 0.0f;
    }
    obj->level = v * g_audioLevelIntegerScale;
}

/** Calls Audio_EnableMusicGainOverride on the panel of the audio context at the given address. */
void Audio_EnableContextMusicGainOverride(int contextAddress) {
    Audio_EnableMusicGainOverride((char *)&((GameAudioContext *)contextAddress)->panel);
}

/** Calls Audio_DisableMusicGainOverride on the panel of the audio context at the given address. */
void Audio_DisableContextMusicGainOverride(int contextAddress) {
    Audio_DisableMusicGainOverride((char *)&((GameAudioContext *)contextAddress)->panel);
}

/** Calls Audio_ClearVoiceFlags on the panel of the audio context at the given address. */
void Audio_ClearContextVoiceFlags(int contextAddress) {
    Audio_ClearVoiceFlags((char *)&((GameAudioContext *)contextAddress)->menu);
}

int Audio_PlayDialogGroup(GameAudioContext *audioContext, int group) {
    float scale = (1.0f);
    float blue = audioContext->blue;
    if (!(scale < blue)) {
        scale = blue;
    }
    return Audio_StartDialogGroup(&audioContext->dialog[0], group, scale, 64);
}

/** Calls Audio_StopDialogPlayer on the panel of the audio context at the given address. */
void Audio_StopContextDialog(int contextAddress) {
    Audio_StopDialogPlayer((char *)&((GameAudioContext *)contextAddress)->dialog);
}

/** Sort the table's word entries into ascending unsigned order. */
void Audio_SortTableEntries(SortTable *table) {
    int i;
    int j;
    u32 right;
    u32 left;

    for (i = 0; i < table->count; i++) {
        for (j = i + 1; j < table->count; j++) {
            right = table->entries[j];
            left = table->entries[i];
            if (right < left) {
                table->entries[i] = right;
                table->entries[j] = left;
            }
        }
    }
}

/* Returns the index of the first of seventeen slots whose id
   equals the given id, or -1 when the id is -1 or absent. */

int Audio_FindVoiceSlotById(char *context, int id) {
    Voice *slot;
    int i;
    slot = ((GameAudioContext *)context)->voices;
    if (id == -1) {
        return -1;
    }
    for (i = 0; i < 17; i++, slot++) {
        if (slot->secondaryKey == id) {
            return i;
        }
    }
    return -1;
}

s32 Audio_ChooseWeightedSoundVariant(AudioWeightedVariantView *scene, s16 id, s16 avoid) {
    s32 first;
    s32 last;
    s32 total;
    s32 entry;
    s32 draw;
    s32 i;

    total = 0;
    if (scene->count != 0) {
        if (Defs_FindSortedGroupRange(scene->ids, scene->count, id, &first, &last) == 0) {
            return -1;
        }
        entry = first;
        if (entry != last) {
            for (i = first; i <= last; i++) {
                total += scene->weights[i] * 10;
            }
            draw = Graphu64_NextRandom() % total;
            total = 0;
            for (entry = first; entry < last; entry++) {
                total += scene->weights[entry] * 10;
                if (total >= draw) {
                    break;
                }
            }
            if (avoid != 0 && entry == scene->lastPick) {
                if (entry == last) {
                    entry--;
                } else {
                    entry++;
                }
            }
        }
        return entry;
    }
    return -1;
}

void Audio_ResolveInstrumentSectionZero(void *audioContext, s16 index) {
    SetN64_GetPackSection(SetN64_GetPackSection((((struct AudioInstrumentPackView *) ((s8 *) audioContext))->instrumentPack), (s32) index), 0);
}

void Audio_ResolveInstrumentSectionOne(void *audioContext, s16 index) {
    SetN64_GetPackSection(SetN64_GetPackSection((((struct AudioInstrumentPackView *) ((s8 *) audioContext))->instrumentPack), (s32) index), 1);
}

/* Returns 1 when the object's owner is set, or when the id is below 256 and at least six of
   its seventeen 0xCC-byte slots at 0x1E64 already carry that id; otherwise 0. */

int Audio_IsSoundInstanceLimitReached(AudioInstanceLimitOwner *obj, int id) {
    int count;
    int i;

    if (obj->owner != -1) {
        return 1;
    }
    if (id < 256) {
        count = 0;
        for (i = 0; i < 17; i++) {
            if (obj->slots[i].id == id) {
                count++;
            }
        }
        if (count >= 6) {
            return 1;
        }
    }
    return 0;
}

/* AUDIOWORLD.CPP */

/* Starts a sound instance from a description: when the scene's free node list is not empty it takes the
 * first node under the audio lock (Sound_AcquireContextLock/Sound_ReleaseContextLock), unlinks it, gives it the next handle, the
 * volume, sample, priority, pan and pitch fields decoded from the description, full gain, the scene frame
 * and the position, prepares its channel through Audio_SetVoiceTrackId and Audio_InitializeVoiceParameters and inserts it into the
 * active list ahead of the first lower-priority node; returns the handle or -1 when no node is free. */

/* Services the pending glyph requests of a text cache: each request still counting down its delay is ticked and, when it reaches zero, stamped with the current frame and the next sequence number; a request older than sixteen frames is moved to the done list, otherwise it reserves a cell for its glyph and a texture for its bitmap, stopping when none is free, copies itself into the cell, uploads the cell through Sound_UpdateSoundSlot and moves to the done list. The slot address is written as the doubled slot plus the table address because the cartridge adds the scaled index first; array indexing puts the table first (1 word). */

static inline void append(ListHead *head, EntryAudioWorldDispatchPendingSounds *entry) {
    entry->prev = head->prev;
    entry->next = (EntryAudioWorldDispatchPendingSounds *)head;
    head->prev->next = entry;
    head->prev = entry;
}

s32 AudioWorld_QueuePrioritizedSound(AudioPriorityQueueManagerView *manager, void *desc, Vec3Words *position, s32 volume, s32 extra) {
    AudioQueuedSoundNode *node;
    AudioQueuedSoundNode *first;
    AudioQueuedSoundNode *at;
    s32 *scene;
    s32 priority;

    if (manager->free.next != (AudioQueuedSoundNode *)&manager->free) {
        Sound_AcquireContextLock(manager->scene);
        first = manager->free.next;
        first->prev->next = first->next;
        first->next->prev = first->prev;
        scene = manager->scene;
        node = first;
        node->handle = ((GameAudioContext *)scene)->soundCounter;
        ((GameAudioContext *)scene)->soundCounter = node->handle + 1;
        node->volume = volume;
        node->voice = -1;
        node->volume16 = volume;
        node->group = SoundInfo_GetGroup(desc);
        node->priority = SoundInfo_GetPriority(desc);
        node->sample = SoundInfo_GetSample(desc);
        node->pan = SoundInfo_GetPan(desc);
        node->flags = SoundInfo_GetFlags(desc);
        node->pitch = SoundInfo_GetPitch(desc);
        node->gainB = 32000;
        node->gainA = 32000;
        node->time = 0;
        node->frame = ((GameAudioContext *)manager->scene)->frame;
        node->position = *position;
        node->playbackResetWord = 0;
        node->mixResetWord = 0;
        Audio_SetVoiceTrackId(node->channel, ((struct GameAudioContext *)manager->scene)->selectedSound);
        node->mix = ((GameAudioContext *)manager->scene)->voiceMixValue;
        Audio_InitializeVoiceParameters(node->channel, desc, extra);
        at = manager->active.next;
        priority = node->priority;
        while (at != (AudioQueuedSoundNode *)&manager->active) {
            if (at->priority < priority) {
                break;
            }
            at = at->next;
        }
        node->prev = at->prev;
        node->next = at;
        at->prev->next = node;
        at->prev = node;
        Sound_ReleaseContextLock(manager->scene);
        return node->handle;
    }
    return -1;
}

void AudioWorld_DispatchPendingSounds(Cache *cache) {
    s16 *slots;
    char *textures;
    Glyphs *glyphs;
    EntryAudioWorldDispatchPendingSounds *entry;
    EntryAudioWorldDispatchPendingSounds *next;
    s32 slot;
    s16 *cursor;
    s32 free;
    AudioSoundCell *cell;

    Sound_AcquireContextLock(cache->context);
    slots = cache->context->slots;
    textures = cache->context->textures;
    glyphs = cache->context->font->glyphs;
    for (entry = cache->pending.next; entry != (EntryAudioWorldDispatchPendingSounds *)&cache->pending; entry = next) {
        next = entry->next;
        if (entry->delay != 0) {
            if (--entry->delay == 0) {
                entry->frame = cache->context->frame;
                entry->sequence = cache->context->sequence++;
                entry->reservedWordA8 = 0;
            }
            continue;
        }
        if (cache->context->frame - entry->frame >= 16) {
            entry->prev->next = next;
            entry->next->prev = entry->prev;
            append(&cache->done, entry);
            continue;
        }
        slot = Channel_SelectVoiceSlot((struct RecordD90 *)cache->context->cells, entry->style, entry->font, entry->glyph, 0);
        if (slot == -1 || slot == 16) {
            break;
        }
        cursor = (s16 *)((slot << 1) + (u32)slots);
        free = *cursor;
        if (free != -1) {
            break;
        }
        *cursor = alSndpAllocate(textures, glyphs->bitmaps[entry->font]);
        if (*cursor == free) {
            break;
        }
        cell = (AudioSoundCell *)(cache->context->cells + 4 + slot * sizeof(AudioSoundCell));
        Libc_CopyBytes(cell, entry->body, 204);
        cell->sequence = entry->sequence;
        cell->texture = *cursor;
        cell->frame = cache->context->frame;
        cell->index = slot;
        Sound_UpdateSoundSlot(cache->context, cell->sequence, 0, cell->data);
        entry->sequence = free;
        entry->glyph = free;
        entry->prev->next = entry->next;
        entry->next->prev = entry->prev;
        append(&cache->done, entry);
    }
    Sound_ReleaseContextLock(cache->context);
}

void AudioWorld_InitializeVoiceListSentinel(void *sentinel, s32 owner) {
    (((struct AudioVoiceListLinks *) ((s8 *) sentinel))->next) = sentinel;
    (((struct AudioVoiceListLinks *) ((s8 *) sentinel))->prev) = sentinel;
    Audio_InitializeVoiceRecord(sentinel + 8, owner, -1);
}

void *AudioWorld_UnlinkChannelNode(LinkPair *channelNode) {
    channelNode->first[1] = (void *) channelNode->second;
    channelNode->second[0] = (void *) channelNode->first;
    return channelNode;
}

static inline void AudioWorld_InitializeListLink(ListLink *link) {
    link->prev = link;
    link->next = link;
}

static inline void AudioWorld_InsertLinkAfter(ListLink *at, ListLink *link) {
    link->next = at->next;
    link->prev = at;
    at->next->prev = link;
    at->next = link;
}

static inline void AudioWorld_InitializePoolVoice(AudioChannelVoiceNode *voice, s32 owner) {
    AudioWorld_InitializeListLink(&voice->link);
    Audio_InitializeVoiceRecord(&voice->header, owner, -1);
}

/* Starts a copy of a sound table entry when that entry is idle: takes the first node of the scene's free
 * list, copies the entry into it, sets its owner value and position, clears its timer and
 * inserts it into the active list ahead of the first node with lower priority; the scene's
 * current selection fields are then reset. */

/* Initialises a channel set: records the owner, sets up its free and active lists with headers, and appends 32 initialised voices to the active list. */
void AudioWorld_InitializePendingSoundPool(ChannelSet *set, s32 owner) {
    s32 i;

    set->owner = owner;
    AudioWorld_InitializeListLink(&set->free);
    Audio_InitializeVoiceRecord(&set->freeHeader, owner, -1);
    AudioWorld_InitializeListLink(&set->active);
    Audio_InitializeVoiceRecord(&set->activeHeader, owner, -1);
    for (i = 0; i < 32; i++) {
        AudioWorld_InitializePoolVoice(&set->voices[i], owner);
        AudioWorld_InsertLinkAfter(set->active.prev, &set->voices[i].link);
    }
}

void AudioWorld_StartSpatialVoice(AudioSpatialVoiceManagerView *manager, s32 index, s32 owner, CVector3 *position) {
    AudioDispatchBusySlot *entry;
    AudioPrioritizedSoundNode *node;
    AudioPrioritizedSoundNode *at;
    AudioPrioritizedSoundNode *first;
    s32 priority;

    entry = &manager->scene->entries[index];
    if (entry->busy != 0) {
        return;
    }
    first = manager->free.next;
    if (first != (AudioPrioritizedSoundNode *)&manager->free) {
        first->prev->next = first->next;
        first->next->prev = first->prev;
        node = first;
        Libc_CopyBytes(node->soundDescriptorStart, entry, 204);
        node->owner = owner;
        node->position.x = position->x;
        node->position.y = position->y;
        node->position.z = position->z;
        node->timer = 0;
        at = manager->active.next;
        priority = node->priority;
        while (at != (AudioPrioritizedSoundNode *)&manager->active) {
            if (at->priority < priority) {
                break;
            }
            at = at->next;
        }
        node->prev = at->prev;
        node->next = at;
        at->prev->next = node;
        at->prev = node;
    }
    manager->scene->activeSelection = 0;
    manager->scene->pendingSelection = -1;
    manager->scene->previousSelection = -1;
    manager->scene->selection = -1;
}

void AudioWorld_RecyclePendingSoundsByIdentifier(ChannelSet *channelSet, s32 soundId) {
    NodeAudioWorldRecyclePendingSoundsByIdentifier *node;
    NodeAudioWorldRecyclePendingSoundsByIdentifier *next;
    NodeAudioWorldRecyclePendingSoundsByIdentifier *end;
    NodeAudioWorldRecyclePendingSoundsByIdentifier *initial_end;
    NodeAudioWorldRecyclePendingSoundsByIdentifier *tail_end;

    node = (NodeAudioWorldRecyclePendingSoundsByIdentifier *)channelSet->free.prev;
    tail_end = (NodeAudioWorldRecyclePendingSoundsByIdentifier *)&channelSet->active;
    initial_end = (NodeAudioWorldRecyclePendingSoundsByIdentifier *)&channelSet->free;
    if (node != initial_end) {
        end = initial_end;
        do {
            next = node->next;
            if (node->value == soundId) {
                node->prev->next = next;
                node->next->prev = node->prev;
                node->prev = (NodeAudioWorldRecyclePendingSoundsByIdentifier *)channelSet->active.next;
                node->next = tail_end;
                ((NodeAudioWorldRecyclePendingSoundsByIdentifier *)channelSet->active.next)->next = node;
                channelSet->active.next = (ListLink *)node;
            }
            node = next;
        } while (node != end);
    }
}

/* Moves nodes whose key differs from retainedKey (or every node when retainedKey is -1) from the active list to the tail of the retained list. */

void AudioWorld_RecyclePendingSoundsExceptKey(AudioPendingSoundListOwner *channelOwner, s32 retainedKey) {
    NodeAudioWorldRecyclePendingSoundsExceptKey *node;
    NodeAudioWorldRecyclePendingSoundsExceptKey *next;
    node = channelOwner->activeNext;
    while (node != (NodeAudioWorldRecyclePendingSoundsExceptKey *) &channelOwner->activePrev) {
        next = node->next;
        if (retainedKey == -1 || node->key != retainedKey) {
            node->prev->next = next;
            node->next->prev = node->prev;
            do { NodeAudioWorldRecyclePendingSoundsExceptKey *tail_ = (channelOwner)->otherPrev; (node)->next = (NodeAudioWorldRecyclePendingSoundsExceptKey *) &(channelOwner)->otherPrev; (node)->prev = tail_; (channelOwner)->otherPrev->next = (node); (channelOwner)->otherPrev = (node); } while (0);
        }
        node = next;
    }
}

/* Move nodes with the requested key from the active list to the other list. */
void AudioWorld_RecyclePendingSoundsByKey(void *channelOwner, s32 matchingKey)
{
    AudioPendingSoundListOwner *owner = channelOwner;
    NodeAudioWorldRecyclePendingSoundsExceptKey *node = owner->activeNext;
    NodeAudioWorldRecyclePendingSoundsExceptKey *head = (NodeAudioWorldRecyclePendingSoundsExceptKey *)&owner->activePrev;
    NodeAudioWorldRecyclePendingSoundsExceptKey *other = (NodeAudioWorldRecyclePendingSoundsExceptKey *)&owner->otherPrev;

    if (node != head) {
        NodeAudioWorldRecyclePendingSoundsExceptKey *sentinel = head;
        do {
            NodeAudioWorldRecyclePendingSoundsExceptKey *next = node->next;
            if (node->key == matchingKey) {
                NodeAudioWorldRecyclePendingSoundsExceptKey *tail;
                node->prev->next = next;
                node->next->prev = node->prev;
                tail = owner->otherPrev;
                node->next = other;
                node->prev = tail;
                owner->otherPrev->next = node;
                owner->otherPrev = node;
            }
            node = next;
        } while (node != sentinel);
    }
}

void AudioWorld_RecyclePendingSoundsByTrack(AudioPendingSoundListOwner *listNode, s32 matchingValue) {
    ListNode *node;
    ListNode *next;
    ListNode *sentinel;
    ListNode *loop_sentinel;
    ListNode *append_sentinel;
    ListNode *tail;

    node = (ListNode *)listNode->activeNext;
    sentinel = (ListNode *)&listNode->activePrev;
    append_sentinel = (ListNode *)&listNode->otherPrev;
    if (node != sentinel) {
        loop_sentinel = sentinel;
        do {
            next = node->next;
            if (node->valueBC == matchingValue) {
                node->prev->next = next;
                node->next->prev = node->prev;
                tail = (ListNode *)listNode->otherPrev;
                node->next = append_sentinel;
                node->prev = tail;
                ((ListNode *)listNode->otherPrev)->next = node;
                listNode->otherPrev = (NodeAudioWorldRecyclePendingSoundsExceptKey *)node;
            }
            node = next;
        } while (node != loop_sentinel);
    }
}

void AudioWorld_RecyclePendingSoundsByFlags(Lists *lists, s32 matchingFlags) {
    AudioPendingFlagsNode *channelCursor;
    AudioPendingFlagsNode *next;
    AudioPendingFlagsNode *sourceSentinel;
    AudioPendingFlagsNode *iterationSentinel;
    AudioPendingFlagsNode *destinationSentinel;

    channelCursor = lists->first.next;
    sourceSentinel = &lists->first;
    if (channelCursor != sourceSentinel) {
        destinationSentinel = &lists->second;
        iterationSentinel = sourceSentinel;
        do {
            next = channelCursor->next;
            if ((channelCursor->flags & matchingFlags) != 0) {
                AudioPendingFlagsNode *prev;

                channelCursor->prev->next = next;
                channelCursor->next->prev = channelCursor->prev;
                prev = lists->second.prev;
                channelCursor->next = destinationSentinel;
                channelCursor->prev = prev;
                lists->second.prev->next = channelCursor;
                lists->second.prev = channelCursor;
            }
            channelCursor = next;
        } while (channelCursor != iterationSentinel);
    }
}

int AudioWorld_HasPendingSoundWithKey(void *channelOwner, int wantedKey) {
    struct AudioPendingSoundListOwner *owner = channelOwner;
    struct NodeAudioWorldRecyclePendingSoundsExceptKey *node = owner->activeNext;
    void *sentinel = &owner->activePrev;
    if (node != sentinel) {
        do {
            int value = node->key;
            node = node->next;
            if (value == wantedKey) {
                return 1;
            }
        } while (node != sentinel);
    }
    return 0;
}

/* K_AUDIOWORLDFLOATCONSTANTWORDS.CPP */



/* AUDIO.CPP */





/* STATINST_DRAWGEOMETRYVARIANT_DATA.CPP */

#if defined(VERSION_DE)
struct {
    s32 g_staticObjectResourceSerial;
    u8 retainedResourceSerialInstructions[12];
    s32 g_resourceCacheNodeCapacity;
    u8 retainedCacheCapacityWords[12];
    s32 g_resourceHashBucketCount;
    u32 g_resourceHashSlotCount;
    s32 g_resourceHashInitialized;
    u8 zeroHashTail[4];
    u32 g_audioTaskFrameIndex;
    u32 g_audioDmaPendingReadCount;
    s32 g_audioCommandBufferIndex;
    u32 g_audioWorkerEventCount;
    u32 g_audioWorkerElapsedTicks;
    s32 g_audioCacheEntryAllocCount;
    u8 retainedResourceStateWords[8];
    s32 g_audioContextInitialized;
} g_statinstDrawGeometryVariant __attribute__((aligned(4))) = {
    3670016,
    { 0x3c, 0x1, 0x80, 0xd, 0x0, 0x22, 0x8, 0x21, 0xac, 0x30, 0x43, 0x70 },
    1024,
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x43, 0x10, 0x25 },
    0,
    0x0,
    0,
    { 0x0, 0x0, 0x0, 0x0 },
    0x0,
    0x0,
    0,
    0x0,
    0x0,
    0,
    { 0x0, 0x0, 0x12, 0xc0, 0x0, 0x0, 0x0, 0xa0 },
    0
};
typedef char g_statinstDrawGeometryVariantWordsSizeCheck[(sizeof(g_statinstDrawGeometryVariant) == 84) ? 1 : -1];
#endif

/* G_OVERLAYSSEVENSCALEFACTORWORDS_US.CPP */
#if defined(VERSION_DE)

struct {
    s32 sectionCount;
    s32 delayLength;
    s32 sections[48];
} g_overlayssevenscalefactorwordsUs __attribute__((aligned(4))) = {
    6,
    4800,
    { 160, 944, 9830, -9830, 2815, 0, 0, 16383, 416, 768, 13107, -13107, 0, 0, 0, 0, 784, 912, 19660, -19660, 0, 0, 0, 0, 1664, 2864, 13107, -13107, 2719, 0, 0, 16383, 1984, 2496, 14107, -14107, 0, 0, 0, 0, 64, 4592, 19384, 0, 20479, 0, 0, 21759 }
};
typedef char g_overlayssevenscalefactorwordsUsSizeCheck[(sizeof(g_overlayssevenscalefactorwordsUs) == 200) ? 1 : -1];
#endif
#if defined(VERSION_EU)
struct {
    s32 sectionCount;
    s32 delayLength;
    s32 sections[48];
} g_overlayssevenscalefactorwordsUs __attribute__((aligned(4))) = {
    6,
    4800,
    { 160, 944, 9830, -9830, 2815, 0, 0, 16383, 416, 768, 13107, -13107, 0, 0, 0, 0, 784, 912, 19660, -19660, 0, 0, 0, 0, 1664, 2864, 13107, -13107, 2719, 0, 0, 16383, 1984, 2496, 14107, -14107, 0, 0, 0, 0, 64, 4592, 19384, 0, 20479, 0, 0, 21759 }
};
typedef char g_overlayssevenscalefactorwordsUsSizeCheck[(sizeof(g_overlayssevenscalefactorwordsUs) == 200) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
struct {
    s32 sectionCount;
    s32 delayLength;
    s32 sections[48];
} g_overlayssevenscalefactorwordsUs __attribute__((aligned(4))) = {
    6,
    4800,
    { 160, 944, 9830, -9830, 2815, 0, 0, 16383, 416, 768, 13107, -13107, 0, 0, 0, 0, 784, 912, 19660, -19660, 0, 0, 0, 0, 1664, 2864, 13107, -13107, 2719, 0, 0, 16383, 1984, 2496, 14107, -14107, 0, 0, 0, 0, 64, 4592, 19384, 0, 20479, 0, 0, 21759 }
};
typedef char g_overlayssevenscalefactorwordsUsSizeCheck[(sizeof(g_overlayssevenscalefactorwordsUs) == 200) ? 1 : -1];
#endif
#if defined(VERSION_US)
struct {
    s32 sectionCount;
    s32 delayLength;
    s32 sections[48];
} g_overlayssevenscalefactorwordsUs __attribute__((aligned(4))) = {
    6,
    4800,
    { 160, 944, 9830, -9830, 2815, 0, 0, 16383, 416, 768, 13107, -13107, 0, 0, 0, 0, 784, 912, 19660, -19660, 0, 0, 0, 0, 1664, 2864, 13107, -13107, 2719, 0, 0, 16383, 1984, 2496, 14107, -14107, 0, 0, 0, 0, 64, 4592, 19384, 0, 20479, 0, 0, 21759 }
};
typedef char g_overlayssevenscalefactorwordsUsSizeCheck[(sizeof(g_overlayssevenscalefactorwordsUs) == 200) ? 1 : -1];
#endif
#if defined(VERSION_US_REV1)
struct {
    s32 sectionCount;
    s32 delayLength;
    s32 sections[48];
} g_overlayssevenscalefactorwordsUs __attribute__((aligned(4))) = {
    6,
    4800,
    { 160, 944, 9830, -9830, 2815, 0, 0, 16383, 416, 768, 13107, -13107, 0, 0, 0, 0, 784, 912, 19660, -19660, 0, 0, 0, 0, 1664, 2864, 13107, -13107, 2719, 0, 0, 16383, 1984, 2496, 14107, -14107, 0, 0, 0, 0, 64, 4592, 19384, 0, 20479, 0, 0, 21759 }
};
typedef char g_overlayssevenscalefactorwordsUsSizeCheck[(sizeof(g_overlayssevenscalefactorwordsUs) == 200) ? 1 : -1];
#endif

/* STATINST_ADVANCERESOURCEKEY_DATA_RESOURCES.CPP */

#if defined(VERSION_EU)
struct {
    s32 g_staticObjectResourceSerial;
    u8 retainedRyanTracyText[12];
    s32 g_resourceCacheNodeCapacity;
    u8 retainedOmlanskyText[12];
    s32 g_resourceHashBucketCount;
    u32 g_resourceHashSlotCount;
    s32 g_resourceHashInitialized;
    u8 zeroHashTail[4];
    u32 g_audioTaskFrameIndex;
    u32 g_audioDmaPendingReadCount;
    s32 g_audioCommandBufferIndex;
    u32 g_audioWorkerEventCount;
    u32 g_audioWorkerElapsedTicks;
    s32 g_audioCacheEntryAllocCount;
    u8 retainedSpaceText[8];
    s32 g_audioContextInitialized;
} g_staticObjectResourceStateWords_eu __attribute__((aligned(4))) = {
    3670016,
    { 0x52, 0x59, 0x41, 0x4e, 0x20, 0x54, 0x52, 0x41, 0x43, 0x59, 0x0, 0x0 },
    1024,
    { 0x20, 0x4f, 0x4d, 0x4c, 0x41, 0x4e, 0x53, 0x4b, 0x59, 0x0, 0x0, 0x0 },
    0,
    0x0,
    0,
    { 0x0, 0x0, 0x0, 0x0 },
    0x0,
    0x0,
    0,
    0x0,
    0x0,
    0,
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 },
    0
};
typedef char g_staticObjectResourceStateWords_euSizeCheck[(sizeof(g_staticObjectResourceStateWords_eu) == 84) ? 1 : -1];
#endif

/* STATINST_DRAWGEOMETRYVARIANT_DATA.CPP */


#if defined(VERSION_EU_X)
struct {
    s32 g_staticObjectResourceSerial;
    u8 retainedResourceSerialFloatWords[12];
    s32 g_resourceCacheNodeCapacity;
    u8 retainedCacheCapacityFloatWords[12];
    s32 g_resourceHashBucketCount;
    u32 g_resourceHashSlotCount;
    s32 g_resourceHashInitialized;
    u8 retainedHashSizeFloatWord[4];
    u32 g_audioTaskFrameIndex;
    u32 g_audioDmaPendingReadCount;
    s32 g_audioCommandBufferIndex;
    u32 g_audioWorkerEventCount;
    u32 g_audioWorkerElapsedTicks;
    s32 g_audioCacheEntryAllocCount;
    u8 retainedResourceStateFloatWords[8];
    s32 g_audioContextInitialized;
} g_statinstDrawGeometryVariantTable_eu_x __attribute__((aligned(4))) = {
    3670016,
    { 0x3f, 0xb1, 0x26, 0x5e, 0x3f, 0xb1, 0x5, 0xc4, 0x3f, 0xb0, 0xe5, 0x28 },
    1024,
    { 0x3f, 0xb0, 0xa3, 0xed, 0x3f, 0xb0, 0x83, 0x4c, 0x3f, 0xb0, 0x62, 0xaa },
    0,
    0x0,
    0,
    { 0x3f, 0xaf, 0xe0, 0x12 },
    0x0,
    0x0,
    0,
    0x0,
    0x0,
    0,
    { 0x3f, 0xae, 0xfb, 0x47, 0x3f, 0xae, 0xda, 0x91 },
    0
};
typedef char g_statinstDrawGeometryVariantTable_eu_xSizeCheck[
    (sizeof(g_statinstDrawGeometryVariantTable_eu_x) == 84) ? 1 : -1];
#endif

/* STATINST_ADVANCERESOURCEKEY_DATA.CPP */


#if defined(VERSION_US)
struct {
    s32 g_staticObjectResourceSerial;
    u8 retainedSfxTagWords[12];
    s32 g_resourceCacheNodeCapacity;
    u8 retainedChamberTagText[12];
    s32 g_resourceHashBucketCount;
    u32 g_resourceHashSlotCount;
    s32 g_resourceHashInitialized;
    u8 retainedHashWords[4];
    u32 g_audioTaskFrameIndex;
    u32 g_audioDmaPendingReadCount;
    s32 g_audioCommandBufferIndex;
    u32 g_audioWorkerEventCount;
    u32 g_audioWorkerElapsedTicks;
    s32 g_audioCacheEntryAllocCount;
    u8 retainedHissTagText[8];
    s32 g_audioContextInitialized;
} g_statinstAdvanceResourceKeyDataWords __attribute__((aligned(4))) = {
    3670016,
    { 0xa, 0x0, 0x4, 0x0, 0x0, 0x0, 0x1b, 0x53, 0x46, 0x58, 0x5f, 0x53 },
    1024,
    { 0x55, 0x4e, 0x5f, 0x43, 0x48, 0x41, 0x4d, 0x42, 0x45, 0x52, 0x5f, 0x48 },
    0,
    0x0,
    0,
    { 0x0, 0x10, 0x0, 0xb },
    0x0,
    0x0,
    0,
    0x0,
    0x0,
    0,
    { 0x52, 0x5f, 0x48, 0x49, 0x53, 0x53, 0x54, 0x0 },
    0
};
typedef char g_statinstAdvanceResourceKeyDataWordsSizeCheck[
    (sizeof(g_statinstAdvanceResourceKeyDataWords) == 84) ? 1 : -1];
#endif

/* STATINST_ADVANCERESOURCEKEY_DATA.CPP */

#if defined(VERSION_US_REV1)
struct {
    s32 g_staticObjectResourceSerial;
    u8 retainedResourceSerialFloatWords[12];
    s32 g_resourceCacheNodeCapacity;
    u8 retainedCacheCapacityFloatWords[12];
    s32 g_resourceHashBucketCount;
    u32 g_resourceHashSlotCount;
    s32 g_resourceHashInitialized;
    u8 retainedHashSizeFloatWord[4];
    u32 g_audioTaskFrameIndex;
    u32 g_audioDmaPendingReadCount;
    s32 g_audioCommandBufferIndex;
    u32 g_audioWorkerEventCount;
    u32 g_audioWorkerElapsedTicks;
    s32 g_audioCacheEntryAllocCount;
    u8 retainedResourceStateFloatWords[8];
    s32 g_audioContextInitialized;
} g_statinstAdvanceResourceKeyWritable __attribute__((aligned(4))) = {
    3670016,
    { 0x3f, 0xb1, 0xa8, 0xb6, 0x3f, 0xb1, 0x88, 0x23, 0x3f, 0xb1, 0x67, 0x8d },
    1024,
    { 0x3f, 0xb1, 0x26, 0x5e, 0x3f, 0xb1, 0x5, 0xc4, 0x3f, 0xb0, 0xe5, 0x28 },
    0,
    0x0,
    0,
    { 0x3f, 0xb0, 0x62, 0xaa },
    0x0,
    0x0,
    0,
    0x0,
    0x0,
    0,
    { 0x3f, 0xaf, 0x7e, 0xe, 0x3f, 0xaf, 0x5d, 0x5f },
    0
};
typedef char g_statinstAdvanceResourceKeyWritableWordsSizeCheck[(sizeof(g_statinstAdvanceResourceKeyWritable) == 84) ? 1 : -1];
#endif

/* LOOKUPPANVALUE.CPP */
#if defined(VERSION_US_REV1)

/* Bytes the original holds up to the next 16-byte object boundary; no instruction reads them. */
unsigned int g_lookupPanValueStaleFloat[1] = {
    0x3FA8AFC2,
};
#endif

/* Retained data for this translation unit. */

const double k_AudioChooseweightedsoundvariant[1] = {
    4294967296.0,
};

const float k_AudioChooseweightedsoundvariantConstants[2] = {
    1.0f, 4.0e+01f,
};

const float k_audioWorldFloatConstant[2] = {
    0.003921569f, 1.0f,
};

const float g_sound_UpdateAudioContextConstant[1] = {
    0.003921569f,
};

const float g_audio_PlayPositionedSoundWithScaleConstant[1] = {
    1.0f,
};
