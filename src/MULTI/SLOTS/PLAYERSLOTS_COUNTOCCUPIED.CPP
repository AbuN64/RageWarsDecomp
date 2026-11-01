#include "MULTI/PLAYERSLOTS_COUNTOCCUPIED.H"
#include "TYPES.H"

#if VERSION_US
/* Counts the player slots whose state is not empty. */
s32 PlayerSlots_CountOccupied(void) {
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
