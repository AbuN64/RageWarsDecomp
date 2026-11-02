#include "include_asm.h"

#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/EFFECTRENDER.H"

/* Minimal callback views established by Encoded_UpdateLevelSelectionAvailability_MenuHandleunlockedlevelselection..C85C: the owner at+12
   supplies the descriptor whose option flags are at+728. */
#include "MENU/LEVELSELECT_TYPES.H"


static inline s32 levelBit(s32 level) {
    s32 bit;

    switch (level) {
    default:
    case 0:
        bit = 0x10000;
        break;
    case 1:
        bit = 0x20000;
        break;
    case 2:
        bit = 0x40000;
        break;
    case 3:
        bit = 0x80000;
        break;
    case 4:
        bit = 0x100000;
        break;
    case 5:
        bit = 0x200000;
        break;
    case 6:
        bit = 0x800000;
        break;
    case 7:
        bit = 0x400000;
        break;
    case 8:
        bit = 0x1000000;
        break;
    case 9:
        bit = 0x2000000;
        break;
    case 10:
        bit = 0x4000000;
        break;
    }
    return bit;
}

/* Choose the first unlocked level, then enable the corresponding widget flags. */
static inline s32 firstUnlocked(void) {
    s32 level = 0;
    s32 i;
    for (i = 0; i < 11; i++) {
        if (g_gameSettings.unlockedLevels & levelBit(level)) {
            return level;
        }
        level++;
        if (level >= 11) {
            level = 0;
        } else if (level < 0) {
            level = 10;
        }
    }
    return -1;
}

void Encoded_UpdateLevelSelectionAvailability(LevelSelectOwner *owner) {
    s32 level = firstUnlocked();
    g_encodedSelectedLevelIndex = level;
    if (level != -1) {
        owner->descriptor->flags |= 0x01800000;
    } else {
        owner->descriptor->flags &= 0xFE7FFFFF;
    }
    if (g_gameSettings.local) {
        owner->descriptor->flags &= 0xFE7FFFFF;
    }
}
#if defined(VERSION_DE)
#include "MENU/HANDLE_UNLOCKED_LEVEL_SELECTION_BODY.H"
#endif
