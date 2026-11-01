#include "TYPES.H"


#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800D9370_unclaimed_D9F7C */
#if defined(VERSION_US_REV1)
struct {
    u8 alignmentFill[4];
} g_audioReadpackedsamplesDataZeroWords __attribute__((aligned(4))) = {
    { 0x00, 0x00, 0x00, 0x00 }
};
#endif

#if defined(VERSION_US_REV1)
u16 g_audioReadpackedsamplesDataConstantWords[17] = {
    0, 1, 3, 7, 15, 31, 63, 127,
    255, 511, 1023, 2047, 4095, 8191, 16383, 32767,
    65535
};
#endif
#endif
