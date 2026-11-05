#ifndef WEAPONS_WEAPON_MODE_ORIGIN_H
#define WEAPONS_WEAPON_MODE_ORIGIN_H
#include "Common/measured_storage.h"
/* Measured 4-byte access at 0x1D8; storage view, complete object unknown. */

/* Measured 1-byte access at 0x34; storage view, complete object unknown. */
struct WeaponModeByteView { unsigned char padding[52]; s8 value; };
/* Measured 4-byte access at 0x128; storage view, complete object unknown. */
struct WeaponOriginScalarView { unsigned char padding[296]; f32 value; };
/* Measured 4-byte access at 0x698; storage view, complete object unknown. */

/* Measured 4-byte access at 0x168; storage view, complete object unknown. */

#endif
