#include "COMMON/AUDIO_CONTEXT.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/GAMEPLAY_ROUND_RULES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/CARTRIDGEREADWORKER.H"
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/STATERECAT34.H"
#include "TYPES.H"
#include "COMMON/EXTERNS.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "TEXTURE/SOUND_UPDATEAUDIOCONTEXT.H"

extern f32 g_audioContextGainScaleConstants;

#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "AUDIO/VOICE.H"
#include "AUDIO/AUDIO_UPDATEMUSICFADE.H"

#include "COMMON/OS_TIMER_INTERRUPT_INTERNALS.H"

extern void AudioWorld_DispatchPendingSounds(void *cache);
extern void Audio_UpdateDialogPlayer(void *player);

extern void Audio_UpdateMusicPlayback(void *queue);
extern s32 SetN64_IsModeThirteen(void);
extern void *Gsky_FindNearestCamera(MenuMatchGlobals *menuMatchGlobals, CVector3 *zero);










s32 Sound_UpdateAudioContext(void *context) {
    char *object = context;
    u8 *bytes = &g_gameSettings.volume[1];
    char *queue;
    u32 mask;
    s32 count;

    ((struct GameAudioContext *)(object))->red = (f32)bytes[0] * g_audioContextGainScaleConstants;
    ((struct GameAudioContext *)(object))->green = (f32)bytes[-1] * g_audioContextGainScaleConstants;
    ((struct GameAudioContext *)(object))->blue = (f32)bytes[1] * g_audioContextGainScaleConstants;
    queue = (char *)&((GameAudioContext *)object)->lock;
    ((struct GameAudioContext *)(object))->spatialPanMode = bytes[-2];
    mask = __osDisableInt();
    count = ((MenuRules *)(queue))->locked + 1;
    ((MenuRules *)(queue))->locked = count;
    if (count != 1) {
        __osRestoreInt(mask);
        osRecvMesg(queue, 0, 1);
    } else {
        __osRestoreInt(mask);
    }

    Audio_UpdateVoicePool(&((struct GameAudioContext *)(object))->menu[0]);
    {
        char *queue2 = (char *)&((GameAudioContext *)object)->lock;
        u32 mask2 = __osDisableInt();
        s32 count2 = ((MenuRules *)(queue2))->locked - 1;

        ((MenuRules *)(queue2))->locked = count2;
        if (count2 != 0) {
            __osRestoreInt(mask2);
            osSendMesg(queue2, 0, 1);
        } else {
            __osRestoreInt(mask2);
        }
    }

    AudioWorld_DispatchPendingSounds((char *)&((GameAudioContext *)object)->view);
    Audio_UpdateDialogPlayer((char *)&((GameAudioContext *)object)->dialog);
    queue = (char *)&((GameAudioContext *)object)->panel;
    Audio_UpdateMusicFade(queue);
    Audio_UpdateMusicPlayback(queue);

    if (g_audioContextInitialized != 0 &&
        ((struct GameAudioContext *)(object))->spatialAudioEnabled != 0 &&
        SetN64_IsModeThirteen() != 0 &&
        ((struct GameAudioContext *)(object))->track > 0) {
        CVector3 zero;
        void *result;
        CVector3 *vec;

        zero.z = 0.0f;
        zero.y = 0.0f;
        zero.x = 0.0f;
        result = Gsky_FindNearestCamera(&g_frontendScreenStatus, &zero);
        vec = &((struct PlayerCameraTargetView *)(result))->position;
        if ((((struct GameAudioContext *)(object))->frame & 3) == 0) {
            Sound_PlaySoundAtPosition(object, ((struct GameAudioContext *)(object))->track, *vec, 0, -1);
        }
    }
    return ++((struct GameAudioContext *)(object))->frame;
}

extern s32 Audio_HasVoiceOrReservedSlotWithKey(void *record, s32 value);
extern s32 AudioWorld_HasPendingSoundWithKey(void *channelOwner, s32 wantedKey);






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
