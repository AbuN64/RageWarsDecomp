#include "include_asm.h"

#include "MULTI/PLAYERSLOTS_ASSERTSLOTINDEX.H"
#include "TYPES.H"

#if VERSION_US
extern char s_playerSlotsSourceFile[];
extern char s_playerSlotsAssertSlotIndex[];
extern s32 AssertFailed(char *file, s32 line, char *expr);

/* Reports a slot number outside 0..3 through the assert hook, then writes through a null pointer. */
void PlayerSlots_AssertSlotIndex(s32 anSlot) {
    if (anSlot >= 0 && anSlot < 4) {
        return;
    }
    if (AssertFailed(s_playerSlotsSourceFile, 5579, s_playerSlotsAssertSlotIndex)) {
        *(char *)0 = 0;
    }
}
#endif
