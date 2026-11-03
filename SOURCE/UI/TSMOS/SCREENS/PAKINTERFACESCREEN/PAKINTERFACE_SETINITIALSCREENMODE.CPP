#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#if VERSION_US
extern char s_pakInterfaceScreenSourceFile[];
extern char s_pakInterfaceInitialModeRange[];
extern s32 g_pakInterfaceScreenMode;
/* Select the initial screen mode after checking the original enum range. */
void PAKInterface_SetInitialScreenMode(s32 mode) {
    if (!(mode >= 0 && mode < 8)) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 3542, s_pakInterfaceInitialModeRange)) *(char *)0 = 0;
    }
    g_pakInterfaceScreenMode = mode;
}
#endif
