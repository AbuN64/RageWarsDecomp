#include "include_asm.h"

/* 800E2284.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800E2284 */
const float k_LevelGetselectedresourceidgermanEncodedWords[1] = {
    15.0f,
};
#endif

/* 8043D1DC_2.CPP */
#if !(defined(VERSION_US_REV1))
/* Maps the state number g_encodedSelectedLevelIndex (0 to 10) to a fixed value through a jump table; anything else gives 1000. */
extern u32 g_encodedSelectedLevelIndex;
s32 Level_GetSelectedResourceIdGerman(void) {
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
