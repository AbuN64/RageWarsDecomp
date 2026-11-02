#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* The first of the user's four player data records holding no player, or -1. */
s32 PAKInterface_FindEmptyPlayerDataSlot(s32 anUser) {
    s32 i;
    s32 nSlot;
    PAK_ASSERT(4486, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    nSlot = -1;
    for (i = 0; i < 4 && nSlot == -1; i++) {
        if (g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_MiddleRecords[i].m_User == -1) {
            nSlot = i;
        }
    }
    return nSlot;
}
#endif
