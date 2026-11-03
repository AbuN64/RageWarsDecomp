#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "include_asm.h"
#include "COMMON/NUMBERPADSCREEN.H"
#include "TYPES.H"
#include "COMMON/GLOBALS.H"
#include "COMMON/WORLD.H"
#include "COMMON/MENU_INITIALIZEOPTIONSSCENE.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "MENU/ITEMS/SCENE/SCENE_UPDATEPENDINGOBJECTS.H"

/* 804221A0_8.CPP */

/* 804221A0_2.CPP */
/* Sets up the match display: calls Menu_ConfigureOptionsCamera, starts the objects at g_frontendScreenStatus and 0x48 bytes
   before it through Pools_ResetActorPools and Player_InitializePlayerPool, loads the resource Track_RequestTrackByKey names for
   0x27D into g_world_AchieveUpdateresultsscreen through Scene_SetSelection_MenuInitializeoptionsscene, and calls Cache_SetResourceActivityState with one when Cache_GetResourceActivityState
   reports nothing. */



void Menu_ConfigureOptionsCamera(void);

/* OPTIONSCENE.CPP */
/* Tears down the match display: calls Cinema_ReleaseSequenceContext_FrontendHandletaboptionsshortcut, stops the objects at g_frontendScreenStatus and 0x48 bytes
   before it through Pools_ResetActorPools and Player_InitializePlayerPool, releases resource 0x24 of g_world_AchieveUpdateresultsscreen through
   Scene_LoadLevelResources, calls Cache_SetResourceActivityState with one when Cache_GetResourceActivityState reports nothing, then calls
   Cinema_ClearResponse_Optionscene, Cinema_SetLoopMode with zero and Cinema_ResetViewport. */

void Menu_ReleaseOptionsScene(void) {
    char *object;

    Cinema_ReleaseSequenceContext();
    object = &g_frontendScreenStatus;
    Pools_ResetActorPools(object, 0);
    Player_InitializePlayerPool(object - ((char *)&((Shared_MenuData *)0)->object - (char *)0), 0, 0);
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

/* MENU_INITIALIZEOPTIONSSCENE.CPP */
void Menu_InitializeOptionsScene(void) {
    char *object;

    Menu_ConfigureOptionsCamera();
    object = &g_frontendScreenStatus;
    Pools_ResetActorPools(object, 1);
    Player_InitializePlayerPool(object - ((char *)&((Shared_MenuData *)0)->object - (char *)0), 1, 0);
    Scene_SetSelection(&g_world, ~Track_RequestTrackByKey(637), 0);
    if (Cache_GetResourceActivityState() == 0) {
        Cache_SetResourceActivityState(1);
    }
}

/* Calls Cinema_SetLoopMode with 1, Cinema_SetResponse_Setn64Drawmode4backdrop with the pooled constant k_optionsCameraResponse and
   Cinema_SetViewport with 0x43, 0x4F, 0x12 and 0x80. */

void Menu_ConfigureOptionsCamera(void) {
    Cinema_SetLoopMode(1);
    Cinema_SetResponse((45.0f));
    Cinema_SetViewport(67, 79, 18, 128);
}

/* K_MENUENCODEDWORDSBLOCK6.CPP */
#if defined(VERSION_EU)
unsigned int k_MenuEncodedWordsBlock6[1] = {
    0x0800002A,
};
#endif

/* K_MENUENCODEDWORDSBLOCK5.CPP */
#if defined(VERSION_EU_X)
unsigned int k_MenuEncodedWordsBlock5[1] = {
    0x0044333C,
};
#endif

/* K_MENUENCODEDWORDSBLOCK4.CPP */
#if defined(VERSION_DE)
unsigned int k_MenuEncodedWordsBlock4[1] = {
    0x00422E30,
};
#endif

/* K_MENUENCODEDWORDS.CPP */
#if defined(VERSION_US)
char k_MenuEncodedWordsBlock3[4] =
    "2equ";
#endif

/* G_MENUENCODEDWORDSBLOCK2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800E164C */
unsigned int g_MenuEncodedWordsBlock2[1] = {
    0x00442454,
};
#endif

/* OPTIONSCENE.CPP */
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const float k_OptionsceneEncodedWords[1] = {
    1.333333f,
};
#endif

/* K_MENUENCODEDWORDSBLOCK1.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800E1644 */
const float k_MenuEncodedWordsBlock1[1] = {
    1.333333f,
};
#endif
