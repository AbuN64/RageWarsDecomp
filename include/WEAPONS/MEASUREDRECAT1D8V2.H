#ifndef WEAPONS_MEASUREDRECAT1D8V2_H
#define WEAPONS_MEASUREDRECAT1D8V2_H
#include "COMMON/MEASURED_STORAGE.H"
#include "WEAPONS/MEASUREDRECAT1D8V3.H"
/* Measured 4-byte access at 0x1D8; storage view, complete object unknown. */

/* Measured 4-byte access at 0x124; storage view, complete object unknown. */
struct WeaponChargeAccumulatorView { unsigned char padding[292]; f32 value; };
/* Measured 4-byte access at 0x128; storage view, complete object unknown. */
/* Measured 4-byte access at 0x698; storage view, complete object unknown. */

/* Measured 4-byte access at 0x168; storage view, complete object unknown. */

/* Measured 1-byte access at 0xCB; storage view, complete object unknown. */
struct WeaponFireLatchView { unsigned char padding[203]; s8 value; };
/* Measured 4-byte access at 0x13C; storage view, complete object unknown. */

#endif
