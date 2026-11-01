#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* Copies each slot's middle record into its global player, or marks the global player unowned. */
void PAKInterface_CopyMiddlePlayersToGlobal(void) {
    u8 *pSource;
    PAKGlobalPlayer *pGlobal;
    s32 i;
    s32 nSize;
    s32 nUser;
    s32 nRecord;
    for (i = 0; i < 4; i++) {
        nUser = g_pakInterfaceScreen->m_Slot[i].m_User;
        nRecord = g_pakInterfaceScreen->m_Slot[i].m_Record;
        pGlobal = &g_pakGlobalPlayers[i];
        if (nUser != -1) {
            pSource = (u8 *)&g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[nRecord];
            nSize = PAK_PLAYER_RECORD_SIZE;
            memcpy(pGlobal, pSource, nSize);
            pGlobal->m_Slot = nRecord;
        } else {
            pGlobal->m_User = -1;
        }
    }
}
#endif
