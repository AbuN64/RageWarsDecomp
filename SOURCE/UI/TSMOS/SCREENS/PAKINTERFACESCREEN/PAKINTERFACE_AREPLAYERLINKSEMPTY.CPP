#include "COMMON/ENTRYRECAT6C.H"
#include "FRONTEND/PAKMENU.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Returns 1 when all four twelve-byte slots at offset 0x2DF0 of the object g_pakProfileScreenState hold -1 in
   their id word, stopping at the first that does not. */




int PAKInterface_ArePlayerLinksEmpty(void) {
    int result;
    int i;

    result = 1;
    for (i = 0; i < 4 && result == 1; i++) {
        if (g_pakProfileScreenState->links[i].player != -1) {
            result = 0;
        }
    }
    return result;
}
