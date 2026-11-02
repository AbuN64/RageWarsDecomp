#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* Copies one slot's middle record into its global player and records which slot and user it came from, or marks the global player unowned. */
void PAKInterface_CopySpecificMiddlePlayerToGlobal(s32 anSlot) {
    PAKGlobalPlayer *pSource;
    PAKGlobalPlayer *pGlobal;
    s32 nSize;
    s32 nUser;
    s32 nRecord;
    nUser = g_pakInterfaceScreen->m_Slot[anSlot].m_User;
    nRecord = g_pakInterfaceScreen->m_Slot[anSlot].m_Record;
    pGlobal = &g_pakGlobalPlayers[anSlot];
    if (nUser != -1) {
        pSource = &g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[nRecord];
        nSize = PAK_PLAYER_RECORD_SIZE;
        memcpy(pGlobal, pSource, nSize);
        pGlobal->m_Slot = nRecord;
        pGlobal->m_User = nUser;
    } else {
        pGlobal->m_User = -1;
    }
}
#endif
