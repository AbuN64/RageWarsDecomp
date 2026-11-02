#include "TYPES.H"
#include "include_asm.h"

/* 8043D3BC.CPP */
#if defined(VERSION_US_REV1)
extern u32 g_encodedSelectedLevelIndex;

/* Returns the score threshold for the current level index, 1000 for level 0 or out of range. */
s32 Level_GetSelectedResourceId(void) {
    switch (g_encodedSelectedLevelIndex) {
    case 0:
    default:
        return 1000;
    case 1:
        return 2000;
    case 2:
        return 3000;
    case 3:
        return 4000;
    case 4:
        return 5000;
    case 5:
        return 6000;
    case 6:
        return 7401;
    case 7:
        return 7501;
    case 8:
        return 7601;
    case 9:
        return 7602;
    case 10:
        return 8000;
    }
}
#endif

/* 800DE2B4.CPP */
/* 800DE2B4.CPP */

/* SELECT_LEVEL_GETSELECTEDRESOURCEID_DATA.CPP */
