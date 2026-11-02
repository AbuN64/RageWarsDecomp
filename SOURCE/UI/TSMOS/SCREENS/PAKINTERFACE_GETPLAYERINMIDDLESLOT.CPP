#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* The middle-list slot holding the player anIndex of user anUser, or -1. */
s32 PAKInterface_GetPlayerInMiddleSlot(s32 anUser, s32 anIndex) {
    s32 i;
    s32 found;
    PAK_ASSERT(4725, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    PAK_ASSERT(4726, anIndex >= 0 && anIndex < 4, s_pakAssertIndexRange);
    found = -1;
    for (i = 0; i < 4 && found == -1; i++) {
        if (g_pakInterfaceScreen->m_Slot[i].m_User == anUser && g_pakInterfaceScreen->m_Slot[i].m_Record == anIndex) {
            found = i;
        }
    }
    return found;
}
#endif
