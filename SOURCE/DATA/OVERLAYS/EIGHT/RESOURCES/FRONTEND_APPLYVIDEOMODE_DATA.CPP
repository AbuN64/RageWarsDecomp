#include "TYPES.H"


#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
struct {
    s32 renderConfig[15];
} g_VideoConfigurationsWords1 __attribute__((aligned(4))) = {
    { 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 }
};
#endif
/* Video mode id per TV region (rows) and viewport flags (columns). */
unsigned int VideoModeIds[3][8] = {
    { 0x00, 0x01, 0x02, 0x03, 0x08, 0x09, 0x0A, 0x0B },
    { 0x0E, 0x0F, 0x10, 0x11, 0x16, 0x17, 0x18, 0x19 },
    { 0x1C, 0x1D, 0x1E, 0x1F, 0x24, 0x25, 0x26, 0x27 },
};
#endif
