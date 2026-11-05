#include "Common/ballisticparams.h"
#include "Common/shared_optionsscreen.h"
#include "include_asm.h"
#include "Common/numberpadscreen.h"
#include "types.h"
#include "Common/globals.h"
#include "Common/world.h"
#include "Common/menu_initializeoptionsscene.h"
#include "Common/menu_match_globals.h"
#include "Menu/Items/Scene/scene_updatependingobjects.h"

/* Sets up the match display: calls Menu_ConfigureOptionsCamera, starts the options-screen objects and the player pool
   through Pools_ResetActorPools and Player_InitializePlayerPool, loads the resource Track_RequestTrackByKey names for
   0x27D into g_world_AchieveUpdateresultsscreen through Scene_SetSelection_MenuInitializeoptionsscene, and calls Cache_SetResourceActivityState with one when Cache_GetResourceActivityState
   reports nothing. */

/* Tears down the match display: calls Cinema_ReleaseSequenceContext_FrontendHandletaboptionsshortcut, stops the options-screen objects and the player pool
   through Pools_ResetActorPools and Player_InitializePlayerPool, releases resource 0x24 of g_world_AchieveUpdateresultsscreen through
   Scene_LoadLevelResources, calls Cache_SetResourceActivityState with one when Cache_GetResourceActivityState reports nothing, then calls
   Cinema_ClearResponse_Optionscene, Cinema_SetLoopMode with zero and Cinema_ResetViewport. */
void Menu_ReleaseOptionsScene(void) {
    Cinema_ReleaseSequenceContext();
    Pools_ResetActorPools(&g_playerViewRenderContext.object, 0);
    Player_InitializePlayerPool(&g_playerViewRenderContext, 0, 0);
    Scene_LoadLevelResources(&g_world, 36, 0);
    if (Cache_GetResourceActivityState() == 0) {
        Cache_SetResourceActivityState(1);
    }
    Cinema_ClearResponse();
    Cinema_SetLoopMode(0);
    Cinema_ResetViewport();
}

void Menu_SetOptionsSceneSelection(int key) {
 GlobalsMenuSetOptionsSceneSelection *g = &g_gameplayCameraList;
 GameplayCamera *o = g->camera;
 float width = 45.0f;
 float height = g_cameraAspectRatios[1];
 StateMenuSetOptionsSceneSelection *state = g_cinemaSequenceState;
 int selection;
 o->fovY = width; o->aspect = height;
 o->viewWidth = state->a; o->viewHeight = state->b; o->viewLeft = state->c; o->viewTop = state->d;
 selection = Track_RequestTrackByKey(key);
 if (!Cache_GetResourceActivityState()) Cache_SetResourceActivityState(1);
 Scene_SetSelection(&g_world, ~selection, 0);
 g->width = width; width = height; g->height = width;
}

void Menu_InitializeOptionsScene(void) {
    Menu_ConfigureOptionsCamera();
    Pools_ResetActorPools(&g_playerViewRenderContext.object, 1);
    Player_InitializePlayerPool(&g_playerViewRenderContext, 1, 0);
    Scene_SetSelection(&g_world, ~Track_RequestTrackByKey(637), 0);
    if (Cache_GetResourceActivityState() == 0) {
        Cache_SetResourceActivityState(1);
    }
}

/* Calls Cinema_SetLoopMode with 1, Cinema_SetResponse_Setn64Drawsplashimage with the pooled constant k_optionsCameraResponse and
   Cinema_SetViewport with 0x43, 0x4F, 0x12 and 0x80. */
void Menu_ConfigureOptionsCamera(void) {
    Cinema_SetLoopMode(1);
    Cinema_SetResponse((45.0f));
    Cinema_SetViewport(67, 79, 18, 128);
}

#if defined(VERSION_EU)
unsigned int k_menuOptionSceneAspectRatio[1] = {
    0x0800002A,
};
#endif

#if defined(VERSION_EU_X)
unsigned int k_menuOptionSceneAspectRatio[1] = {
    0x0044333C,
};
#endif

#if defined(VERSION_DE)
unsigned int k_menuOptionSceneAspectRatio[1] = {
    0x00422E30,
};
#endif

#if defined(VERSION_US)
char k_menuOptionSceneAspectRatio[4] =
    "2equ";
#endif

#if defined(VERSION_US_REV1)
unsigned int g_optionSceneRetainedWord[1] = {
    0x00442454,
};
#endif

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const float k_OptionsceneEncodedWords[1] = {
    1.333333f,
};
#endif

#if defined(VERSION_US_REV1)
const float k_menuOptionSceneAspectRatio[1] = {
    1.333333f,
};
#endif
