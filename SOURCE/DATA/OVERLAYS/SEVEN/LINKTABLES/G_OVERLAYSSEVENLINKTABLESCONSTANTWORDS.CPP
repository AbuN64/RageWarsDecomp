#include "TYPES.H"


#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
struct {
    u8 alignmentFill[12];
} g_overlaysSevenLinktablesConstantWords __attribute__((aligned(4))) = {
    { 0x80, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x0C, 0x00, 0x12 }
};
#endif
#endif
