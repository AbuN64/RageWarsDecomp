#include "include_asm.h"

#include "MULTI/PLAYERSLOTS_FINDSTAGEDWHENIDLE.H"
#include "TYPES.H"

#if VERSION_US
/* Returns -1 when any slot is live; otherwise the index of the first staged slot, or -1 when none is. */
s32 PlayerSlots_FindStagedWhenIdle(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_playerSlotTable->slots[i].state != PLAYER_SLOT_EMPTY && g_playerSlotTable->slots[i].state != PLAYER_SLOT_RELEASED && g_playerSlotTable->slots[i].state != PLAYER_SLOT_STAGED) {
            return -1;
        }
    }
    i = 0;
    while (i < 4) {
        if (g_playerSlotTable->slots[i].state == PLAYER_SLOT_STAGED) {
            return i;
        }
        i++;
    }
    return -1;
}
#endif
