#include "../../sdk/include/PERIPHERAL_PORT_BYTE_VIEWS.H"
#if ((defined(VERSION_EU)))
#include "types.h"
#endif

/* A float and its IEEE-754 bit pattern. */
typedef union FloatBits {
    float value;
    unsigned int bits;
} FloatBits;

/* Returns the high half of the float's bit pattern: the sign, exponent and top mantissa bits. */
unsigned short Menu_GetFloatHighWord(float value) {
    FloatBits converted;
    converted.value = value;
    return converted.bits >> 16;
}

#if defined(VERSION_EU)

f32 Menu_ExpandFloatHighWord(u32 value) {
    FloatBits expanded;
    expanded.bits = value << 16;
    return expanded.value;
}
/* Stale code words (j, move, jr ra, nop); no instruction reads it. */
unsigned int g_floatConvertStaleCode[4] = {
    0x080AA151, 0x02602821, 0x03E00008, 0x00000000,
};
#endif

#if !(defined(VERSION_EU))
float Menu_ExpandFloatHighWord(int floatHighBits) {
    FloatBits expanded;
    expanded.bits = floatHighBits << 16;
    return expanded.value;
}
#endif
