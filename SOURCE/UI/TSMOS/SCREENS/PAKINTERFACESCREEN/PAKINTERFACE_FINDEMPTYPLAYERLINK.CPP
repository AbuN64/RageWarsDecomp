#include "COMMON/ENTRYRECAT6C.H"
#include "FRONTEND/PAKMENU.H"
#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Returns the index of the first of the four 12-byte slots at offset 0x2DF8 of the table g_pakProfileScreenState
   points to whose first word is -1, meaning free, or -1 when none is. */





s32 PAKInterface_FindEmptyPlayerLink(void) {
    s32 found = -1;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (found != -1) {
            break;
        }
        if (g_pakProfileScreenState->links[i].player == -1) {
            found = i;
        }
    }
    return found;
}
