#include "include_asm.h"

const float g_Wheel_GetDirectionSectorConstantWords[8] = {
    0.3926991f, 6.2831855f, 6.2831855f, 6.1831856f,
    0.1f, 0.15915494f, 8.0f, 7.0f,
};

#if defined(VERSION_US)
char s_WheelDirectionSectorConstantReSetRText[8] =
    "reSetR\000\000";
#endif

#if defined(VERSION_EU_X)
extern char g_weaponai_UpdateHeldFireEntry[];
void *k_WheelDirectionSectorConstantEncodedWordsBlock1[2] = {
    (void *)(g_weaponai_UpdateHeldFireEntry + 752), (void *)(g_weaponai_UpdateHeldFireEntry + 744),
};
#endif

#if defined(VERSION_DE)
unsigned int k_WheelDirectionSectorConstantEncodedWords[2] = {
    0x0C0AC91C, 0x02402821,
};
#endif
