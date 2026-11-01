#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* The first middle-list slot with no player, or -1. */
s32 PAKInterface_FindEmptyMiddleSlot(void) {
    s32 i;
    s32 slot;
    slot = -1;
    for (i = 0; i < 4 && slot == -1; i++) {
        if (g_pakInterfaceScreen->m_Slot[i].m_User == -1) {
            slot = i;
        }
    }
    return slot;
}
#endif
