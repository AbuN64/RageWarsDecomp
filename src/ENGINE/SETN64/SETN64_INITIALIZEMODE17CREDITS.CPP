#include "RENDER/TIMED_SESSION_TRANSITIONS.H"
#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/OBJRECAT26DD8.H"
#include "COMMON/SHARED_WORLDFUNC.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/PAKQUEUESTATE.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/WORLD.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "TYPES.H"
#include "ENGINE/SETN64.H"
extern s32 g_hudReferenceViewportWidth;








extern int Playerai_GetFirstPlayer(void *world);


extern void SetN64_HandleSessionTransitionInput(s32 session, s32 cancelTarget, s32 target);


s32 SetN64_DrawCreditsLines(s32);

s32 CCredits_UpdateScroll(s32);


void SetN64_SelectSpawnAfterCredits(void *scene, s32 spawnIndex) {
    GameSession *object = scene;
    Shared_Placed spawn;
    s32 selectionValues;

    selectionValues = spawnIndex;
    if (Scene_FindPlacedObjectsByKey(&g_world, -1, selectionValues, &spawn, 1) == 0) {
        selectionValues = 0;
    }
    object->phase = 2;
    object->selector = selectionValues;
    object->target = 14;
}

/* Initializes the game state for a new game phase with sessionAddress as the phase identifier. */
void SetN64_InitializeMode16Credits(s32 sessionAddress) {
    g_creditsReturnToFrontend = 0;
    g_creditsCurrentLine = 0;
    g_creditsScrollPosition = (f32)(&g_hudReferenceViewportWidth)[1];
    g_creditsSkipRequested = 0;
    Playerai_GetFirstPlayer(&g_playerViewRenderContext);
    g_creditsSelectSpawnOnExit = 0;
    Scene_ResetTransitionViewport();
    SetN64_ResetPlayerItems(sessionAddress, 130);
}

void SetN64_HandleMode16CreditsInput(s32 session) {
    s32 *p;

    if (g_creditsReturnToFrontend != 0) {
        SetN64_HandleSessionTransitionInput(session, 1, 1);
        return;
    }
    p = (s32 *)&g_combinedControllerProfile.pressedButtons;
    if ((*p & 0x1000) && (g_creditsSkipRequested == 0)) {
        g_creditsSkipRequested = 1;
        *p = 0;
        g_creditsLineTimer = g_creditsInitialLineTimer;
    }
}

void SetN64_DrawMode16Credits(s32 session) {
    SetN64_DrawSessionWithAttractTimeout((void *)session);
    SetN64_DrawCreditsLines(session);
    CCredits_UpdateScroll(session);
}

/* Initializes the game state for a new game phase with sessionAddress and updates the game state flag. */
void SetN64_InitializeMode17Credits(s32 sessionAddress) {
    Shared_Game *game = &g_playerViewRenderContext.game;

    game->local = 0;
    g_creditsReturnToFrontend = 0;
    g_creditsCurrentLine = 0;
    g_creditsScrollPosition = (f32)(&g_hudReferenceViewportWidth)[1];
    g_creditsSkipRequested = 0;
    Playerai_GetFirstPlayer(&g_playerViewRenderContext);
    g_creditsSelectSpawnOnExit = 0;
    Scene_ResetTransitionViewport();
    SetN64_ResetPlayerItems(sessionAddress, 130);
    g_creditsReturnToFrontend = 1;
    g_creditsSelectSpawnOnExit = 0;
}

void SetN64_HandleMode17CreditsInput(s32 session) {
    if (g_creditsReturnToFrontend != 0) {
        SetN64_HandleSessionTransitionInput(session, 1, 1);
        return;
    }
    if ((g_creditsControllerButtons & 0x1000) && (g_creditsSkipRequested == 0)) {
        g_creditsSkipRequested = 1;
        g_creditsControllerButtons = 0;
        g_creditsLineTimer = (15.0f);
    }
}

void SetN64_DrawMode17Credits(s32 session) {
    SetN64_DrawSessionWithAttractTimeout((void *)session);
    SetN64_DrawCreditsLines(session);
    CCredits_UpdateScroll(session);
}

#if defined(VERSION_US)
const float g_Setn64Initializemode17creditsWords1 = 1.0f;
#endif

