#include "include_asm.h"

#include "MULTI/PLAYERSLOTS_COUNTLIVE.H"
#include "TYPES.H"

#if VERSION_US
/* Counts the player slots whose state is neither empty, staged nor released. */
s32 PlayerSlots_CountLive(void) {
    s32 i;
    s32 count;

    count = 0;
    for (i = 0; i < 4; i++) {
        if (g_playerSlotTable->slots[i].state != PLAYER_SLOT_EMPTY && g_playerSlotTable->slots[i].state != PLAYER_SLOT_STAGED && g_playerSlotTable->slots[i].state != PLAYER_SLOT_RELEASED) {
            count++;
        }
    }
    return count;
}
#endif
