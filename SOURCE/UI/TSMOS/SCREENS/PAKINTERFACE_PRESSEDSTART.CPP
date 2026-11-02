#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* Marks the user as having pressed start and moves the user's panel on to state 2. */
void PAKInterface_PressedStart(s32 anUser) {
    PAKUpdateInfo *pInfo;
    PAK_ASSERT(4296, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    pInfo = (PAKUpdateInfo *)g_pakUpdateInfo[anUser];
    pInfo->m_StartPressed = 1;
    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Panel = 2;
    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = 2;
}
#endif
