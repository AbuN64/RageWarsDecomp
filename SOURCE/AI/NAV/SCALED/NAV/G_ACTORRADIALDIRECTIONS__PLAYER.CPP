#include "COMMON/VECTOR3.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CDA3C_unclaimed_CE6E0 */
/* 16 zero bytes ahead of the direction table, read by no instruction (nothing addresses 0x800CDAE0..0x800CDAEF) */
unsigned int g_actorRadialDirectionsPad[4] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

/* eight unit directions in the xz plane, 45 degrees apart starting at +z; read by Wheel_MeasureWheelReach / Wheel_MeasureWheelClearance */
#endif
