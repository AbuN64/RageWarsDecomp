#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* Puts the player anIndex of user anUser into the middle-list slot anSlot. */
void PAKInterface_AddPlayerToSpecificMiddleSlot(s32 anUser, s32 anIndex, s32 anSlot) {
    PAK_ASSERT(4685, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    PAK_ASSERT(4686, anIndex >= 0 && anIndex < 4, s_pakAssertIndexRange);
    PAK_ASSERT(4687, anSlot >= 0 && anSlot < 4, s_pakAssertSlotRange);
    g_pakInterfaceScreen->m_Slot[anSlot].m_User = anUser;
    g_pakInterfaceScreen->m_Slot[anSlot].m_Record = anIndex;
    g_pakInterfaceScreen->m_Slot[anSlot].m_State = 1;
}
#endif
