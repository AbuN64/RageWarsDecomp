#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
void PAKInterface_InitUpdateInfo(s32 anUser) {
    s32 i;
    s32 nCount;
    s32 nStringId;
    PAKListItem *pItem;
    PAK_ASSERT(5841, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    nCount = 0;
    for (i = 0; i < 4; i++) {
        switch (nCount) {
        case 0:
            nStringId = 696;
            break;
        case 1:
            nStringId = 739;
            break;
        case 2:
            nStringId = 740;
            break;
        case 3:
            nStringId = 741;
            break;
        }
        if (g_pakGlobalPlayers[i].m_Quick == 0 && g_pakGlobalPlayers[i].m_User == anUser
            && g_pakUpdateInfo[i][PAK_UPDATE_ACTIVE] == 1 && g_pakUpdateInfo[i][PAK_UPDATE_PENDING] == 0) {
            pItem = PAKInterface_AddListItem(g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pWidget, nStringId);
            pItem->m_pPlayer = &g_pakGlobalPlayers[i];
            nCount++;
        }
    }
}
#endif
