#include "COMMON/RESERVED_SHARED_DECLARATIONS.H"
#include "TYPES.H"
#include "SCENE/CACHE_FREEMEMORY.H"

/* Releases the object g_pauseTimedMenu holds through Cache_FreeMemory, clears g_pauseTimedMenu, calls Tsmos_SetModeOneFlag with 2
   and returns zero. */
extern struct MenuRules *g_pauseTimedMenu;


s32 Timed_DestroyPauseConfirmation(void) {
    Cache_FreeMemory(g_pauseTimedMenu);
    g_pauseTimedMenu = 0;
    Tsmos_SetModeOneFlag(2);
    return 0;
}
