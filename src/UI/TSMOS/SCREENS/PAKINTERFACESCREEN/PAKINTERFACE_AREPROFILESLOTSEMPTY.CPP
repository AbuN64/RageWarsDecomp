#include "COMMON/ENTRYRECAT6C.H"
#include "FRONTEND/PAKMENU.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Returns 1 when all four of a player's 400-byte entries in the game g_pakProfileScreenState have state byte -1 at
   0x7D, stopping with 0 at the first in use. */





int PAKInterface_AreProfileSlotsEmpty(int player) {
    int result;
    int i;

    result = 1;
    for (i = 0; i < 4 && result == 1; i++) {
        if (g_pakProfileScreenState->players[player].records[i].player != -1) {
            result = 0;
        }
    }
    return result;
}
