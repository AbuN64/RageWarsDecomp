#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* Starts leaving the screen: disables input and picks the target the frontend mode returns to when the caller passes -2. */
void PAKInterface_ExitScreen(s32 anTarget) {
    TSMOS_InputDisable();
    g_pakInterfaceScreen->m_ExitPhase = 5;
    g_pakInterfaceScreen->m_ExitStep = 4;
    g_pakInterfaceScreen->m_ExitTarget = anTarget;
    if (anTarget == -2) {
        switch (g_engineApp.m_FrontendMode) {
        case 0:
            g_pakInterfaceScreen->m_ExitTarget = 7;
            break;
        case 1:
            g_pakInterfaceScreen->m_ExitTarget = 7;
            break;
        case 2:
            g_pakInterfaceScreen->m_ExitTarget = 9;
            break;
        case 3:
            g_pakInterfaceScreen->m_ExitTarget = 7;
            break;
        case 4:
            g_pakInterfaceScreen->m_ExitTarget = 10;
            break;
        default:
            PAK_ASSERT(5705, 0, s_pakAssertExitMode);
            break;
        }
    }
}
#endif
