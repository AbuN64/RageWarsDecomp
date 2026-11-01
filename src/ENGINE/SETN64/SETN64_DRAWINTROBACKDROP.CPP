#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "ENGINE/SETN64.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <PR/gbi.h>
#include "COMMON/WORLD.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include <ultra64.h>
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/MENURECAT24.H"
#include "RENDER/TIMED_SESSION_TRANSITIONS.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"

void Control_DisableAllControllerPaks(void);

extern void SetN64_ResetSessionPlayerPools(void *session, s32 count, s32 force_active);



extern u8 g_matchRoundCounters;


extern u32 Defs_GetMemorySize(void);

/* Emits a set-color-image display list command for the current frame buffer, then draws image 0x388
 * scaled to fill the screen dimensions over the image's returned width and height, when both are nonzero. */





extern Gfx *g_displayListCursor;

#include "COMMON/DISPLAY.H"



/* Clears g_expansionMemoryIntroEnabled when SetN64_CheckTimedSessionTransition accepts its argument with 4.0 and two fours. */

/** Perform no work for callers at VRAM 0x80293DDC. */
void SetN64_OnMode5DrawComplete(s32 session) {
}

void SetN64_InitializeFrontendScreenState(GameSession *gameSession) {
    g_introSelectedItem = -1;
    g_introSelectionState = 0;
    Frontend_RequestScreenMode(0);
    g_frontendScreenInitialized = 1;
    g_pakRequestLatched = 1;
    g_pakStartButtonLatched = 1;
    g_pakScanActive = 0;
    gameSession->timer = g_introInitialFadeTimer;
    SmXlate_SwitchScreen(29);
}

void SetN64_ExitSessionAndDisablePaks(void *session) {
    if (g_pakRecheckRequested != 0) {
        SetN64_SetTransitionTarget(session, 1);
        Control_DisableAllControllerPaks();
    }
}

/** Thin wrapper around SetN64_DrawSessionWithRoundTimeout. */
void SetN64_DrawRoundTimeoutSession(GameSession *session) {
    SetN64_DrawSessionWithRoundTimeout(session);
}

void SetN64_ResetSceneForIntro(void *owner) {
    s8 *p1;
    s8 *p2;
    int memoryBytes;

    SoundElement_SetMusicPlaybackEnabled(0);
    memoryBytes = 1496;
    p1 = ((s8 *)(&g_matchRoundCounters)) - memoryBytes;
    ((struct IntegerStateB0 *) ((char *) (&g_matchRoundCounters)))->transitionActive = 0;
    ((struct IntegerStateB0 *) ((char *) (&g_matchRoundCounters)))->first = 0;
    p1[178] = 1;
    p1[29] = 0;
    p1[30] = 1;
    SetN64_ResetSessionPlayerPools(owner, 0, 0);
    Scene_LoadLevelResources(&g_world, 0, 0);
    p2 = ((s8 *)(&g_matchRoundCounters)) - (((char *)&((Shared_MenuData *)0)->game.counters - (char *)0) - ((char *)&((Shared_MenuData *)0)->object - (char *)0));
    Pools_ResetActorPools(p2, 1);
    ((IntroBackdropStateView *)(p2))->poolClearedWord = 0;
    Textload_SetTextureEffect(0);
}

void SetN64_AdvanceIntroForMemorySize(GameSession *session) {
    s32 eight;
    s32 call_result;
    u32 result;

    result = Defs_GetMemorySize();
    eight = 4;
    if ((result > 0x400000U) && (g_expansionMemoryIntroEnabled != 0)) {
        eight = 3;
    }
    if (session->transitionTime > g_introTransitionDelay) {
        g_introExitPending = 0;
    }
    if (g_introExitPending != 0) {
        call_result = SetN64_CheckTimedSessionTransition(session, 12.0f, eight, -1);
    } else {
        call_result = SetN64_CheckTimedSessionTransition(session, 12.0f, eight, eight);
    }
    if (call_result != 0) {
        g_introExitPending = 0;
    }
}

void SetN64_DrawIntroBackdrop(void) {
    s32 width;
    s32 height;
    Gfx *cmd;

    width = 0;
    height = 0;
    gDPSetColorImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, g_hudReferenceViewportWidth, (u32)g_currentRenderFrame->colorImage);
    OnScreen_GetImageDimensions(904, 0, &width, &height);
    if ((width != 0) && (height != 0)) {
        Onscrn_SetupSpriteMode(250);
        OnScreen_DrawSpriteResource(904, 0, 0, 0, (f32)g_hudReferenceViewportWidth / (f32)width, (f32)g_hudReferenceViewportHeight / (f32)height, 1);
    }
}

void SetN64_ClearSessionPlayerPools(void *owner) {
    SetN64_ResetSessionPlayerPools(owner, 0, 0);
}

void SetN64_AdvanceToModeFour(struct GameSession *value) {
    if (SetN64_CheckTimedSessionTransition(value, 4.0f, 4, 4) != 0) {
        g_expansionMemoryIntroEnabled = 0;
    }
}

/** Preserve the empty hook at VRAM 0x80294120. */
void SetN64_InitializeMode2(void) {
}

void SetN64_AdvanceToModeFive(struct GameSession *session)
{
  s32 five;
  five = 5;
  SetN64_CheckTimedSessionTransition(session, 14.0f, five, five);
}
