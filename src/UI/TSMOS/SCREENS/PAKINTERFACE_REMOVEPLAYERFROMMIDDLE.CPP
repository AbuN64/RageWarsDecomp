#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* Empties the middle-list slot holding the player anIndex of user anUser; 0 when it holds none. */
s32 PAKInterface_RemovePlayerFromMiddle(s32 anUser, s32 anIndex) {
    s32 i;
    s32 nRemoved;
    PAK_ASSERT(4700, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    PAK_ASSERT(4701, anIndex >= 0 && anIndex < 4, s_pakAssertIndexRange);
    nRemoved = 0;
    for (i = 0; i < 4 && !nRemoved; i++) {
        if (g_pakInterfaceScreen->m_Slot[i].m_User == anUser && g_pakInterfaceScreen->m_Slot[i].m_Record == anIndex) {
            g_pakInterfaceScreen->m_Slot[i].m_User = -1;
            g_pakInterfaceScreen->m_Slot[i].m_State = 2;
            nRemoved = 1;
        }
    }
    return nRemoved;
}
#endif
