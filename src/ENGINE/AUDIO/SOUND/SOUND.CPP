#include "../../../../sdk/include/LIBC.H"
#include "include_asm.h"
#include "COMMON/CARTRIDGEREADWORKER.H"
#include "TEXTURE/CARTRIDGE_DMA_AND_AUDIO_TIMING_VIEWS.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "TYPES.H"
#include "../../../../sdk/include/libgultra/alunlink.h"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "ENGINE/AUDIO/AUDIOWORLD.H"
#include "ENGINE/DEFS.H"
#include "COMMON/AUDIO_CONTEXT.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/PPDECOM_UNPACKRESOURCE.H"
#include "COMMON/ALAUXBUS_S.H"
#include "COMMON/AUDIO_INITIALIZE.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/LISTNODE.H"
#include "COMMON/OS_TIMER_INTERRUPT_INTERNALS.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "COMMON/SELF.H"

/* 80256220_14.CPP */
/* Returns the physical address of a cached copy of a data block: finds the cache entry keyed by the
 * block's address and refreshes the copy (and flushes it from the data cache) when the size changed;
 * otherwise reuses a free entry or allocates and links a new 0x90-byte one, copies the block into it and
 * marks it in use. */



extern void osWritebackDCache(void *, s32);



/* Returns the physical address of a ROM offset through the 0x300-byte ROM window cache: a cached window
 * covering the offset and length is stamped with the current frame; otherwise a free window node is
 * linked in address order (or at the head), aligned to an even start, stamped, counted, filled from ROM
 * through Cartridge_SubmitReadChunks and its buffer address returned with the odd byte added back. */

extern char g_cartridgeReadWorker;

extern void Cartridge_SubmitReadChunks(void *, u32, s32, s32, void *, s32, s32);

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
    CacheEntry *unused;

    unused = 0;
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
            unused = entry;
        }
    }
    if (unused == 0) {
        unused = (CacheEntry *)alHeapDBAlloc(0, 0, g_audioHeap, 1, 144);
        unused->next = g_audioCacheCountdownHead;
        g_audioCacheCountdownHead = unused;
        g_audioCacheEntryAllocCount++;
    }
    unused->key = block;
    unused->state = 3;
    unused->size = size;
    Libc_CopyBytes(unused->data, block, size);
    return osVirtualToPhysical(unused->data);
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

extern u8 *g_audioContextHeapBuffer;
extern int g_audioContextHeapBytes;
extern float g_soundContextVolumePercentScale, g_soundContextInitialPlaybackScale;
typedef struct AudioBankHeader {
    s32 reserved0;
    s32 table;
    s32 reserved8;
    ALBankFile *bankFile;
} AudioBankHeader;
extern void Mutex_InitializeQueueLock(MenuRules *lock);
extern void Audiomgr_InitializeAudioWorker(ALSynConfig *, s32, AudioInitializeTiming *);

extern void Audio_InitializeMusicPlayer(void *, void *);
extern void AudioWorld_InitializePendingSoundPool(void *, void *);
extern void Audio_InitializeVoicePool(void *, void *);
extern void Audio_InitializeDialogPlayer(void *, void *);
extern s32 g_audioWorkerThreadPriority;
extern s32 g_audioFxConfigParams;
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
    ctx->tableCount2B7C = rest[1];
    ctx->table2B70 = rest + 2;
    ctx->tableCount2B80 = refs[1];
    ctx->table2B74 = refs + 2;
    ctx->tableCount2B84 = sounds[1];
    ctx->table2B78 = sounds + 2;
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
/* The voice mix block at +0x10 of each Voice (Channel_InitializeVoiceMix views it the same way). */
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
s32 Sound_UpdateSoundSlot(GameAudioContext *context, s32 id, s32 unused, CVector3 *position) {
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

/* 80256220_15.CPP */
/* Stops every voice playing a sound id while holding the manager's recursive lock at 0x110: tells
 * AudioWorld_RecyclePendingSoundsByIdentifier about the id, then for each of the 17 voice records whose sound matches it counts the voice
 * and either resets the spare record 16 or clears the voice's pending flag and stops its channel through
 * Audio_StopVoiceSlot when it has a handle; returns the number of voices found (0 for id -1). Lock handling
 * adapted from Audio_StopAudioBySecondaryValue; the voice records are addressed by offset from the manager.
 */

extern void Audio_StopVoiceSlot(void *, s16);

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

extern void *Gsky_FindNearestCamera(MenuMatchGlobals *, CVector3 *);
extern s32 Audio_HasVoiceWithKey(void *, s32);
extern f32 Audio_ComputeDistanceAttenuation(CVector3 *, void *);
extern s32 Audio_FindVoiceByKeyPair(void *, s32, s32);
extern s32 AudioWorld_QueuePrioritizedSound(void *, Item57BD4 *, CVector3 *, s32, s32);

extern void *Channel_StartNoteVoice(void *, Item57BD4 *, s32, s32);
extern void Audio_SetVoicePositionTracking(void *, CVector3 *, s32);

extern void Audio_InitializeVoiceParameters(void *, Item57BD4 *, s32);

s32 Sound_StartSoundRecord(void *context, Item57BD4 *soundRecord, CVector3 *position, s32 playbackValue,
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
    Sound_UpdateSoundSlot(context, ((Draw *)(node))->model, 0, position);
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
            Sound_StartSoundRecord(context, (Item57BD4 *)((u8 *)(group + 1) + i * group->stride), &position, index,
                                     playId, 0, spatialMode);
        }
        context->selectedOwner = -1;
        return playId;
    }
    return -1;
}

/* Starts a sound-bank entry: looks up the entry's record in the bank table at 0x2B4C, resets the current
 * selection (0x2B88/0x2B8C/0x2B90), takes the recursive lock at 0x110 to hand out a new play id (counter
 * at 0x10C), then starts every voice record of the entry through Sound_StartSoundRecord at the given position;
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
        Sound_StartSoundRecord(self, (Item57BD4 *)((u8 *)(group + 1) + i * group->stride), &position, index, playId, 0, voiceParameter);
    }
    return playId;
}
