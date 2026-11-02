#include "COMMON/ENTRYRECAT6C.H"
#include "FRONTEND/PAKMENU.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Releases the first of the four twelve-byte slots at 0x2DF8 of g_pakProfileScreenState whose id and value match
   the arguments, marking its id -1 and its state 2, and returns whether one was found. */




int PAKInterface_RemovePlayerProfileLink(int id, int value) {
    int found;
    int i;

    found = 0;
    for (i = 0; i < 4 && found == 0; i++) {
        if (g_pakProfileScreenState->links[i].player == id && g_pakProfileScreenState->links[i].entry == value) {
            found = 1;
            g_pakProfileScreenState->links[i].player = -1;
            g_pakProfileScreenState->links[i].state = 2;
        }
    }
    return found;
}
