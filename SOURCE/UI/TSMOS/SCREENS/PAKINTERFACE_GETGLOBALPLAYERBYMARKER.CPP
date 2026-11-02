#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
s32 PAKInterface_GetGlobalPlayerByMarker(s32 anMarker, s32 anSlot) {
    s32 i;
    PAK_ASSERT(5770, anSlot >= 0 && anSlot < 4, s_pakAssertSlotRange);
    i = 0;
    while (i < 4) {
        if (g_pakGlobalPlayers[i].m_Slot == anSlot && g_pakGlobalPlayers[i].m_Marker == anMarker) {
            return i;
        }
        i++;
    }
    return -1;
}
#endif
