#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* Copies a user's quick-play record from the middle list into a free global slot and reports whether it was added. */
s32 PAKInterface_AddQuickPlayerToGlobal(s32 anUser) {
    s32 nRecord;
    s32 nGlobal;
    s32 nRet;
    PAKGlobalPlayer *pSource;
    PAKGlobalPlayer *pGlobal;
    PAK_ASSERT(5720, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    nRet = 0;
    nRecord = g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_QuickRecord;
    if (g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_RecordState[nRecord] == 1) {
        nGlobal = PAKInterface_FindEmptyGlobalSlot();
        if (nGlobal >= 0) {
            PAKInterface_InitGlobalSlot(0, nGlobal);
            pSource = &g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_MiddleRecords[nRecord];
            pGlobal = &g_pakGlobalPlayers[nGlobal];
            memcpy(pGlobal, pSource, PAK_PLAYER_RECORD_SIZE);
            pGlobal->m_User = anUser;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Mode = 0;
            PAKInterface_RefreshMiddleList(-1);
            nRet = 1;
        }
    }
    return nRet;
}
#endif
