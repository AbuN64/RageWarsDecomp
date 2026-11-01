#include "include_asm.h"
#include "COMMON/OBJRECAT26DD8.H"
#include "ENGINE/SETN64.H"
#include "TYPES.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/GROUP.H"

/* 802944E8_5.CPP */
/** Perform the no-op callback at VRAM 0x80294ABC. */
void SetN64_InitializeTransitionMode(void) {
}

#if defined(VERSION_US)
extern s32 g_frontendCurrentVideoModeIndex;
extern char g_videoModeDefaultLabel[], g_videoModeLabels[];
extern f32 g_Setn64Initializemode17creditsWords1;
extern void *g_Setn64ConfigurevideoandentermodeusPointerWords1[];
extern void osViSetYScale(f32);
extern void Cinema_EndSequence(void);
#define SCR_W(state, off) (*(s32 *)((char *)(state) + (off)))
/* Per-frame screen step: when the flag at 0x26DD0 is set it switches the video mode (label chosen by g_frontendCurrentVideoModeIndex, Y scale from a constant, mode 2); in state 2 of g_gameModeTransitionFrames with that flag clear it latches 0x26DBC into 0x26DB8, clears 0x26DB0, runs the reset calls and dispatches the 12-byte table row g_Setn64ConfigurevideoandentermodeusPointerWords1 for that value. */
void SetN64_ConfigureVideoAndEnterModeUs(char *state) {
    void (*handler)(char *);
    s32 mode;
    if (SCR_W(state, 0x26DD0) != 0) {
        char *label = g_videoModeDefaultLabel;
        if (g_frontendCurrentVideoModeIndex == 0) {
            label = g_videoModeLabels;
        }
        osViSetMode(label);
        osViSetYScale(g_Setn64Initializemode17creditsWords1);
        osViSetSpecialFeatures(2);
    }
    if (g_gameModeTransitionFrames == 2 && SCR_W(state, 0x26DD0) == 0) {
        mode = SCR_W(state, 0x26DBC);
        SCR_W(state, 0x26DB0) = 0;
        SCR_W(state, 0x26DB8) = mode;
        Cinema_EndSequence();
        SoundElement_StopAudioExceptKey(-1);
        Control_SetControllerMode(0);
        handler = (void (*)(char *))g_Setn64ConfigurevideoandentermodeusPointerWords1[SCR_W(state, 0x26DB8) * 3];
        if (handler != 0) {
            handler(state);
        }
    }
}
#endif

/* 802944E8_7.CPP */
#if !(defined(VERSION_US))
extern SessionInitializeHandler g_sessionInitializeHandlers[];

void SetN64_EnterPendingSessionMode(void *gameSession) {
    void (*callback)(void *gameSession);
    s32 index;

    if ((g_gameModeTransitionFrames == 2) &&
        (((struct GameSession *)gameSession)->transitionBlocked == 0)) {
        index = ((struct GameSession *)gameSession)->target;
        ((struct GameSession *)gameSession)->transitionTime = 0;
        ((struct GameSession *)gameSession)->mode = index;
        Cinema_EndSequence();
        SoundElement_StopAudioExceptKey(-1);
        Control_SetControllerMode(0);
        callback = g_sessionInitializeHandlers[((struct GameSession *)gameSession)->mode].callback;
        if (callback != 0) {
            callback(gameSession);
        }
    }
}
#endif

/* 802944E8_9.CPP */
void SetN64_DrawTransitionMode(void) {
}
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
void SetN64_InitializeMode18(void) {
}
#endif
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
void SetN64_UpdateMode18(void) {
}
#endif
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
void SetN64_DrawMode18(void) {
}
#endif
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
void SetN64_InitializeMode19(void) {
}
#endif
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
void SetN64_UpdateMode19(void) {
}
#endif
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
void SetN64_DrawMode19(void) {
}
#endif

#if defined(VERSION_US)
/** Perform no operation. */
void SetN64_EmptyVideoModeHookUs(void) {
}

/** Perform no operation. */
void SetN64_EmptyVideoModeHookSecondUs(void) {
}
#endif
