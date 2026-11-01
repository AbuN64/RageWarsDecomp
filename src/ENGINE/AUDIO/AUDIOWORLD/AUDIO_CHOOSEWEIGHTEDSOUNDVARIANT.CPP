#include "COMMON/AUDIO_CONTEXT.H"
#include "include_asm.h"
#include "COMMON/EXTERNS.H"
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/GAMEPLAY_ROUND_RULES.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "COMMON/SELF.H"
#include "ENGINE/AUDIO/AUDIOWORLD.H"
#include "COMMON/LISTNODE.H"
#include "COMMON/SOUNDVOICEPOOL.H"
#include "COMMON/STATERECAT34.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "AUDIO/VOICE.H"
#include "AUDIO/AUDIO_CHOOSEWEIGHTEDSOUNDVARIANT.H"
#include "ENGINE/AUDIO/RAXPLAYER.H"
#include "OS/AUDIO_STOPMUSIC.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "ENGINE/DEFS.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "COMMON/OS_TIMER_INTERRUPT_INTERNALS.H"

/* ROM-grounded data: src/k_AudioChooseweightedsoundvariantEncodedWordsUsRev1.c */
const double k_AudioChooseweightedsoundvariantEncodedWords[1] = {
    4294967296.0,
};

/* ROM-grounded data: src/k_AudioChooseweightedsoundvariantEncodedWordsBlock1UsRev1.c */
const float k_AudioChooseweightedsoundvariantEncodedWordsBlock1[2] = {
    1.0f, 4.0e+01f,
};

extern void Audio_StopVoicesByKey(void *record, s32 value);

extern void Audio_StopVoicesBySecondaryValue(void *, s32);

extern void Audio_StopVoicesByFlags(void *record, s32 value);

extern void AudioWorld_RecyclePendingSoundsByFlags(void *lists, s32 matchingFlags);

extern f32 g_audioContextGainScaleConstants[];

extern s32 SetN64_IsModeThirteen(void);

extern void *Gsky_FindNearestCamera(MenuMatchGlobals *menuMatchGlobals, CVector3 *zero);

extern void Audio_StopVoicesExceptKey(void *record, s32 value);

extern void AudioWorld_RecyclePendingSoundsExceptKey(void *channelOwner, s32 retainedKey);

extern void Audio_FadeOutMusic(int a);

extern void Audio_EnableMusicGainOverride(Track *a);

extern void Audio_DisableMusicGainOverride(Track *a);

/* Picks a weighted random entry from the range Defs_FindSortedGroupRange finds for an id in a scene's table: -1 when
 * the scene has no table or no range, the single entry when the range has one; otherwise each entry weighs
 * ten times its table value, a random draw selects one, and when avoidance is requested and it equals the
 * scene's last pick at 0x130 it steps to the next entry (or back from the last). Adapted from
 * Audio_ChooseSequenceVariant with the table weights and the stored last pick. */

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

/** Store the second argument at byte offset 0x2BA8 in the first argument. */
void Audio_SetDialogVolume(GameAudioContext *object, float value) {
    object->blue = value;
}

/** Return the indexed twelve-byte record from the table at offset 0x2B70. */
char *Audio_GetMetadataSectionThreeEntry(char *object, int index) {
    return ((GameAudioContext *)(object))->table2B70 + index * 12;
}

void *Audio_GetMetadataSectionFourEntry(GameAudioContext *audioContext, int entryIndex) {
    return (char *)audioContext->table2B74 + entryIndex * 12;
}

/** Return the indexed 12-byte entry under object offset 0x2B78. */
void *Audio_GetMetadataSectionFiveEntry(GameAudioContext *audioContext, int entryIndex) {
    return (char *)audioContext->table2B78 + entryIndex * 12;
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

/** Thin wrapper forwarding an offset argument to Audio_FadeOutMusic. */
void Audio_FadeOutContextMusic(int contextAddress) {
    Audio_FadeOutMusic((char *)&((GameAudioContext *)contextAddress)->panel);
}

/** Store the second argument at offset 0x2BAC. */
void Audio_SetVoiceMixValue(GameAudioContext *context, int mixValue) {
    context->voiceMixValue = mixValue;
}

int Audio_GetVoiceMixValue(GameAudioContext *context) {
    return context->voiceMixValue;
}

/** Store a value in the field at offset 0x2BB4. */
void Audio_SetPeriodicSoundEnabled(char *object, int value) {
    ((GameAudioContext *)(object))->spatialAudioEnabled = value;
}

/** Store a value in the field at offset 0x2B98. */
void Audio_SetListenerCamera(GameAudioContext *object, int value) {
    object->listenerCamera = value;
}

/** Read the object word at offset 0x2BB0. */
int Audio_GetSpatialPanMode(void *object) {
    return ((GameAudioContext *)(object))->spatialPanMode;
}

/** Store the supplied word at object offset 0x2BB0. */
void Audio_SetSpatialPanMode(GameAudioContext *audioContext, int panMode) {
    audioContext->spatialPanMode = panMode;
}

void *Audio_GetSoundPlayer(void *audioContext) {
    return &((GameAudioContext *)(audioContext))->list[0];
}

/** Store a word in the object field at offset 0x2BB8. */
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

/** Thin wrapper forwarding an offset argument to Audio_StopMusic. */
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

/** Thin wrapper forwarding an offset argument to Audio_EnableMusicGainOverride. */
void Audio_EnableContextMusicGainOverride(int contextAddress) {
    Audio_EnableMusicGainOverride((char *)&((GameAudioContext *)contextAddress)->panel);
}

/** Thin wrapper forwarding an offset argument to Audio_DisableMusicGainOverride. */
void Audio_DisableContextMusicGainOverride(int contextAddress) {
    Audio_DisableMusicGainOverride((char *)&((GameAudioContext *)contextAddress)->panel);
}

/** Thin wrapper forwarding an offset argument to Audio_ClearVoiceFlags. */
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

/** Thin wrapper forwarding an offset argument to Audio_StopDialogPlayer. */
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

/* Returns the index of the first of seventeen 0xCC-byte slots at offset 0x1DBC whose id at 0xC
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

/* Returns 1 when the object's owner at 0x102 is set, or when the id is below 256 and at least six of
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
