#include "COMMON/ITEMRECAT20V1.H"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/NAME.H"
#include "FRONTEND/PAKINTERFACE_FINDREADYTRANSFERPLAYER.H"

/* Returns the first of the four players in g_pakProfileScreenState whose state at 0x58 is 14, provided every player
   is idle (0), finished (17) or in state 14; otherwise, or when none is in state 14, returns -1. */



int PAKInterface_FindReadyTransferPlayer(void) {
    int i;
    int state;

    for (i = 0; i < 4; i++) {
        state = g_pakProfileScreenState->players[i].state;
        if (state != 0 && state != 17 && state != 14) {
            return -1;
        }
    }
    for (i = 0; i < 4; i++) {
        if (g_pakProfileScreenState->players[i].state == 14) {
            return i;
        }
    }
    return -1;
}
