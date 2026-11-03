#include "UI/TSMOS/SCREENS/PAKINTERFACE_GETNPLAYERSJOINED.H"
#include "TYPES.H"

#if VERSION_US
/* Counts the player slots whose state is not empty. */
s32 PAKInterface_GetNPlayersJoined(void) {
    s32 i;
    s32 count;

    count = 0;
    for (i = 0; i < 4; i++) {
        if (g_playerSlotTable->slots[i].state != PLAYER_SLOT_EMPTY) {
            count++;
        }
    }
    return count;
}
#endif
