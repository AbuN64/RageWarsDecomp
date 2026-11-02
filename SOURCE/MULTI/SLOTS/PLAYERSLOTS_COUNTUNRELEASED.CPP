#include "MULTI/PLAYERSLOTS_COUNTUNRELEASED.H"
#include "TYPES.H"

#if VERSION_US
/* Counts the player slots that are neither empty nor released. */
s32 PlayerSlots_CountUnreleased(void) {
    s32 i;
    s32 count;

    count = 0;
    for (i = 0; i < 4; i++) {
        if (g_playerSlotTable->slots[i].state != PLAYER_SLOT_EMPTY && g_playerSlotTable->slots[i].state != PLAYER_SLOT_RELEASED) {
            count++;
        }
    }
    return count;
}
#endif
