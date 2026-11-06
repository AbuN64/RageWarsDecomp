#include "../../sdk/include/PERIPHERAL_PORT_BYTE_VIEWS.H"
#if ((defined(VERSION_EU)))
#include "types.h"
#endif

/* A float and its IEEE-754 bit pattern. */
typedef union FloatBits {
    float value;
    unsigned int bits;
    /* The two halves in memory order: on the big-endian target halves[0] is the high half. */
    unsigned short halves[2];
} FloatBits;

/* Returns the high half of the float's bit pattern: the sign, exponent and top mantissa bits. */
unsigned short Menu_GetFloatHighWord(float value) {
    return ((unsigned short *)&value)[0];
}

#if defined(VERSION_EU)

f32 Menu_ExpandFloatHighWord(u32 value) {
    u32 bits = value << 16;
    return *(f32 *)&bits;
}
/* Stale code words (j, move, jr ra, nop); no instruction reads it. */
unsigned int g_floatConvertStaleCode[4] = {
    0x080AA151, 0x02602821, 0x03E00008, 0x00000000,
};
#endif

#if !(defined(VERSION_EU))
float Menu_ExpandFloatHighWord(int floatHighBits) {
    int tmp = floatHighBits << 16;
    return *(float *)&tmp;
}
#endif
