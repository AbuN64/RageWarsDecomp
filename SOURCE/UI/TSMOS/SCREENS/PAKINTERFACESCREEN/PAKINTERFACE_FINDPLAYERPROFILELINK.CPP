#include "COMMON/ENTRYRECAT6C.H"
#include "FRONTEND/PAKMENU.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Returns the index of the first of the four twelve-byte slots at offset 0x2DF8 of g_pakProfileScreenState whose
   id and value words match the arguments, or -1 when none does. */




int PAKInterface_FindPlayerProfileLink(int id, int value) {
    int result;
    int i;

    result = -1;
    for (i = 0; i < 4 && result == -1; i++) {
        if (g_pakProfileScreenState->links[i].player == id && g_pakProfileScreenState->links[i].entry == value) {
            result = i;
        }
    }
    return result;
}
