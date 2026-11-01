#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
void PAKInterface_UpdatePAK(s32 anUser) {
    s32 i;
    s32 nSlot;
    s32 nSize;
    PAK_ASSERT(5817, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    nSize = 400;
    for (i = 0; i < 4; i++) {
        if (g_pakGlobalPlayers[i].m_Quick == 0 && g_pakGlobalPlayers[i].m_User == anUser
            && g_pakUpdateInfo[i][PAK_UPDATE_ACTIVE] == 1 && g_pakUpdateInfo[i][PAK_UPDATE_PENDING] == 0) {
            nSlot = g_pakGlobalPlayers[i].m_Slot;
            memcpy(&g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_MiddleRecords[nSlot], &g_pakGlobalPlayers[i], nSize);
        }
    }
}
#endif
