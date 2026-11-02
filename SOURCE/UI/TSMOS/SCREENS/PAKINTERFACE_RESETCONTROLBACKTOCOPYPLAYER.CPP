#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
void PAKInterface_ResetControlBackToCopyPlayer(s32 anUser) {
    s32 nCopyUser;
    nCopyUser = g_pakInterfaceScreen->m_Slot[0].m_User;
    PAKInterface_SetControlOwner(g_pakInterfaceScreen->m_pUserList, nCopyUser, 0);
    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = 17;
    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_NameTarget = 0;
    g_pakInterfaceScreen->m_PAKInterfacePlayer[nCopyUser].m_Panel = 2;
    g_pakInterfaceScreen->m_PAKInterfacePlayer[nCopyUser].m_State = 2;
    g_pakInterfaceScreen->m_PAKInterfacePlayer[nCopyUser].m_Step = 13;
    g_pakInterfaceScreen->m_PAKInterfacePlayer[nCopyUser].m_Mode = 3;
    PAKInterface_InitPlayerMode(nCopyUser);
    PAKInterface_RefreshMiddleNamesForCopy(-1);
}
#endif
