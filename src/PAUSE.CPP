#include "COMMON/RESERVED_SHARED_DECLARATIONS.H"
#include "FRONTEND/FRONTEND_OPENGAMEPLAYFRONTEND.H"
#include "COMMON/MENURECAT20V1.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "TYPES.H"
#include <ultra64.h>
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "SCENE/CACHE_FREEMEMORY.H"

/* FRONTEND_CREATEPAUSEMENU.CPP */
/* Calls InitFrontendMenus and then SmXlate_SwitchScreen with 1. */
#if defined(VERSION_EU)
extern void Tsmos_InitializeEuropeanFrontend(void);
#else
extern void InitFrontendMenus(void);
#endif
extern void SmXlate_SwitchScreen(int);

void Frontend_OpenGameplayFrontend(void) {

#if defined(VERSION_EU)
Tsmos_InitializeEuropeanFrontend
#else
InitFrontendMenus
#endif
();
    SmXlate_SwitchScreen(1);
}

/* Allocates menu state, selects the language-dependent title and enables the appropriate menu item. */
extern s32 *g_pauseMenuState;
extern struct Record *Cache_AllocateMemory(s32 size);
extern void Tsmos_ActivateControllerState(void); extern void Widget_SetWidgetFlag100(s32, s32);
extern s32 Frontend_GetScreenMode(void),ScenarioSetup_IsCupSelected(void);
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
enum { PAUSE_MENU_FLAGGED_WIDGET_ID = 62 };
#elif defined(VERSION_EU_X)
enum { PAUSE_MENU_FLAGGED_WIDGET_ID = 64 };
#endif
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
        Widget_SetWidgetFlag100((s32)Node_FindWidgetByResourceId(root, PAUSE_MENU_FLAGGED_WIDGET_ID), 1);
    }
    g_gameSession.clockPaused = 1;
    return 0;
}

/* FRONTEND_DESTROYPAUSEMENU.CPP */
/* Releases the object g_pauseMenuState holds through Cache_FreeMemory, clears g_pauseMenuState, calls
   Tsmos_SetModeOneFlag with 2 and Control_RestoreControllerSetup_FrontendDestroypausemenu, and returns zero. */

extern void Control_RestoreControllerSetup(void);

s32 Frontend_DestroyPauseMenu(void) {
    Cache_FreeMemory(g_pauseMenuState);
    g_pauseMenuState = 0;
    Tsmos_SetModeOneFlag(2);
    Control_RestoreControllerSetup();
    return 0;
}

/* FRONTEND_SETPAUSEMENUINPUTMODE.CPP */
/* Calls Tsmos_SetModeOneFlag with 2 and returns zero. */

s32 Frontend_SetPauseMenuInputMode(void) {
    Tsmos_SetModeOneFlag(2);
    return 0;
}

/* FRONTEND_RETURNPAUSEEVENTZERO.CPP */
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
