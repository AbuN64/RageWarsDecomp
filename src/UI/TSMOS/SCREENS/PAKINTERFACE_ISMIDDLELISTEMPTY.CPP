#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* Whether none of the four middle-list slots holds a player. */
s32 PAKInterface_IsMiddleListEmpty(void) {
    s32 i;
    s32 empty;
    empty = 1;
    for (i = 0; i < 4 && empty == 1; i++) {
        if (g_pakInterfaceScreen->m_Slot[i].m_User != -1) {
            empty = 0;
        }
    }
    return empty;
}
#endif
