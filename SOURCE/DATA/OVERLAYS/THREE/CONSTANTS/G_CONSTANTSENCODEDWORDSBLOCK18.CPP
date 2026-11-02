#include "TYPES.H"


#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CD4C4_unclaimed_CE0F0_unclaimed_CE104_unclaimed_CE10C_unclaimed_CE124_unclaimed_CE130_unclaimed_CE144_unclaimed_CE148_unclaimed_CE1F8_unclaimed_CE210_unclaimed_CE21C */
unsigned int g_ConstantsEncodedWordsBlock9[2] = {
    0x801044F8, 0x0000521C,
};

#if defined(VERSION_US_REV1)
struct {
    f32 scale;
    s32 threshold;
    u32 flags;
} g_ConstantsEncodedWordsBlock18 __attribute__((aligned(4))) = {
    1.0f,
    0,
    0x0
};
typedef char g_ConstantsEncodedWordsBlock18SizeCheck[(sizeof(g_ConstantsEncodedWordsBlock18) == 12) ? 1 : -1];
#endif
#endif
