#include "include_asm.h"

/* 802ABDBC_10.CPP */

/* Pickup_NoOp_de.CPP */
#if defined(VERSION_DE)
void Pickup_NoOp_de(void) {}
#endif

#if defined(VERSION_DE)
#include "TYPES.H"

s32 Pickup_ClassifyMenuCode(s32 menuCode) {
    if ((menuCode == 1999) || (menuCode == 2999) || (menuCode == 3999) ||
        (menuCode == 4999) || (menuCode == 5999) || (menuCode == 6999) ||
        (menuCode == 99)) {
        return 0;
    }
    if ((u32)(menuCode - 1000) < 1000) {
        return 1;
    }
    if ((u32)(menuCode - 2000) < 1000) {
        return 2;
    }
    if ((u32)(menuCode - 3000) < 1000) {
        return 3;
    }
    if ((u32)(menuCode - 4000) < 1000) {
        return 4;
    }
    if ((u32)(menuCode - 5000) < 1000) {
        return 5;
    }
    if ((u32)(menuCode - 6000) < 1000) {
        return 6;
    }
    return -1;
}
#endif
