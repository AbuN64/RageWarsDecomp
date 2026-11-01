#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* Whether none of the user's four player data records holds a player. */
s32 PAKInterface_IsPlayerDataListEmpty(s32 anUser) {
    s32 i;
    s32 nEmpty;
    PAK_ASSERT(4466, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    nEmpty = 1;
    for (i = 0; i < 4 && nEmpty == 1; i++) {
        if (g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_MiddleRecords[i].m_User != -1) {
            nEmpty = 0;
        }
    }
    return nEmpty;
}
#endif
