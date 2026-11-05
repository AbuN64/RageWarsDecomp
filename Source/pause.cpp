#include "Common/reserved_shared_declarations.h"
#include "Common/shared_menureply.h"
#include "Frontend/widget_findwidgetatpoint.h"
#include "Frontend/frontend_opengameplayfrontend.h"
#include "Common/pak_enter_player_options.h"
#include "Common/game_session.h"
#include "Common/shared_gameslot.h"
#include "types.h"
#include <platform_sdk.h>
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Scene/cache_freememory.h"
#include "Ui/Tsmos/TSMOS.h"
#include "Common/selectionscreenstate.h"
#include "Common/snapshot_actor.h"
#include "Common/menu_options_and_results.h"
#include "pause_symbols.h"
#include "Frontend/frontend.h"

/* Calls InitFrontendMenus and then SmXlate_SwitchScreen with 1. */
void Frontend_OpenGameplayFrontend(void) {

#if defined(VERSION_EU)
Tsmos_InitializeEuropeanFrontend
#else
InitFrontendMenus
#endif
();
    SmXlate_SwitchScreen(1);
}

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
enum { PAUSE_MENU_FLAGGED_WIDGET_ID = 62 };
#elif defined(VERSION_EU_X)
enum { PAUSE_MENU_FLAGGED_WIDGET_ID = 64 };
#endif

/* Allocates menu state, selects the language-dependent title and enables the appropriate menu item. */
s32 Frontend_CreatePauseMenu(MenuWidget *root) {
    s32 *pauseMenuState;
    pauseMenuState = Cache_AllocateMemory(20);
    g_pauseMenuState = pauseMenuState;
    *pauseMenuState = 0;
    SoundElement_StopAudioExceptKey(-1);
    Control_SaveControllerSetup();
    if (Frontend_GetScreenMode() == 1) {
        root->x = 98;
        root->y = 69;
    } else if (Frontend_GetScreenMode() == 2) {
        root->x = 105;
    }
    Tsmos_ActivateControllerState();
    if ((g_gameSettings.controllerMode != 0) || (ScenarioSetup_IsCupSelected() == 0)) {
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(root, PAUSE_MENU_FLAGGED_WIDGET_ID), 1);
    }
    g_gameSession.clockPaused = 1;
    return 0;
}

/* Releases the object g_pauseMenuState holds through Cache_FreeMemory, clears g_pauseMenuState, calls
   Tsmos_SetMenuModelFlag with 2 and Control_RestoreControllerSetup_FrontendDestroypausemenu, and returns zero. */
s32 Frontend_DestroyPauseMenu(void) {
    Cache_FreeMemory(g_pauseMenuState);
    g_pauseMenuState = 0;
    Tsmos_SetMenuModelFlag(2);
    Control_RestoreControllerSetup();
    return 0;
}

/* Calls Tsmos_SetMenuModelFlag with 2 and returns zero. */
s32 Frontend_SetPauseMenuInputMode(void) {
    Tsmos_SetMenuModelFlag(2);
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Frontend_ReturnPauseEventZero(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Frontend_ReturnPauseEventZeroAlt(void) {
    return 0;
}
