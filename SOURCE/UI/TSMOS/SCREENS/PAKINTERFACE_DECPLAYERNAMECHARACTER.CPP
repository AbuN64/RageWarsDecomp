#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
void PAKInterface_DecPlayerNameCharacter(s32 anUser) {
    u8 c;
    void *pUserObject;
    g_pakInterfaceScreen->m_UserBusy[anUser] = 0;
    pUserObject = PAKInterface_GetUserObject(g_pakInterfaceScreen->m_pUserList, anUser);
    PAK_ASSERT(5944, pUserObject != 0, s_pakAssertUserObject);
    if (g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Name[g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_NameCursor].ch == 0) {
        g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Name[g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_NameCursor].ch = 65;
    }
    c = g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Name[g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_NameCursor].ch;
    c--;
    if (c < 32) {
        c = 90;
    }
    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Name[g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_NameCursor].ch = c;
}
#endif
