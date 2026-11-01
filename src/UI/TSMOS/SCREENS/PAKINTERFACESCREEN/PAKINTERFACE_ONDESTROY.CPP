#include "TYPES.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "COMMON/SHARED_MENUREPLY.H"
#if VERSION_US
/* Releases the screen object through Cache_FreeMemory, clears g_pakInterfaceScreen, re-activates the controller state and
   calls Tsmos_SetModeOneFlag with 1. */
s32 PAKInterface_OnDestroy(s32 a, s32 b, s32 c, s32 d) {
    Cache_FreeMemory(g_pakInterfaceScreen);
    g_pakInterfaceScreen = 0;
    Tsmos_ActivateControllerState();
    Tsmos_SetModeOneFlag(1);
    return 0;
}
#endif
