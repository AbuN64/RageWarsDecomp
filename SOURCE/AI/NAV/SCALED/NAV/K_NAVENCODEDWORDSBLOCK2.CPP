#include "TYPES.H"

#if defined(VERSION_DE)
/* DE-only 60-byte rodata run after k_NavQuarterWords (0.25f); no instruction or pointer in the ROM addresses any word of it
   (lui/addiu/lwc1/lw scan of the whole image and a pointer-word scan found only 0x800C913C and 0x800C917C), so the types follow the values */
float g_teamWheelTuningFloats[3] = {
    0.09f, 0.05f, 0.5f,
};

/* stale word completing the 16-byte literal group (0x000C0000 here, 0x2E656F73 in the US image); read by nothing */
u32 g_teamWheelTuningPad = 0x000C0000;

/* eight (id, 0) halfword pairs */
u16 g_teamWheelSlotOrder[8][2] = {
    { 1, 0 }, { 5, 0 }, { 4, 0 }, { 12, 0 }, { 8, 0 }, { 10, 0 }, { 2, 0 }, { 3, 0 },
};

/* the last word is g_teamWheelScalePoolPrefix; g_teamWheelInitialSlotScale (0.25f) follows */
float g_teamWheelScaleLiterals[3] = {
    30.0f, 48.0f, 130.0f,
};
#endif
