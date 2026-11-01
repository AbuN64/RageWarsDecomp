#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* Puts the player anIndex of user anUser into the first empty middle-list slot; 0 when no slot is empty. */
s32 PAKInterface_AddPlayerToMiddle(s32 anUser, s32 anIndex) {
    s32 nSlot;
    s32 nAdded;
    PAK_ASSERT(4659, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    PAK_ASSERT(4660, anIndex >= 0 && anIndex < 4, s_pakAssertIndexRange);
    nAdded = 0;
    nSlot = PAKInterface_FindEmptyMiddleSlot();
    if (nSlot >= 0) {
        g_pakInterfaceScreen->m_Slot[nSlot].m_User = anUser;
        g_pakInterfaceScreen->m_Slot[nSlot].m_Record = anIndex;
        g_pakInterfaceScreen->m_Slot[nSlot].m_State = 1;
        nAdded = 1;
    } else {
        nAdded = 0;
        PAK_ASSERT(4676, 0, s_pakAssertNoEmptySlot);
    }
    return nAdded;
}
#endif
