#include "TYPES.H"


#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
struct {
    u32 reserved[2];
    f32 scale;
    s32 threshold;
    u32 flags;
} g_controllerState1TrailerWords __attribute__((aligned(4))) = {
    { 0x00000000, 0x00000000 },
    1.0f,
    5,
    0x00000000
};
#endif
#endif
