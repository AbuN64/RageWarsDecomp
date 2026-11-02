#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
void PAKInterface_RemoveQuickPlayerFromGlobal(s32 anSlot) {
    PAK_ASSERT(5753, anSlot >= 0 && anSlot < 4, s_pakAssertSlotRange);
    if (g_pakInterfaceScreen->m_Slot[anSlot].m_State == 1) {
        CPersistentPlayerData_Initialize(&g_pakGlobalPlayers[anSlot]);
        g_pakInterfaceScreen->m_Slot[anSlot].m_State = 2;
        PAKInterface_RefreshMiddleList(-1);
    }
}
#endif
