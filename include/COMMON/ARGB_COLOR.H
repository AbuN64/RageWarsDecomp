#ifndef COMMON_ARGB_COLOR_H
#define COMMON_ARGB_COLOR_H
#include "TYPES.H"

/* Big-endian AARRGGBB argument representation used by the rectangle renderer.
 * US rev1 Combine_DrawClippedGradientQuad (80415D10) takes four words at incoming sp+10..1C.
 * Its byte loads/stores at 80415E1C, 80415E88, 80415EE8 and 80415F48 access
 * red +1, green +2, blue +3 and alpha +0. The emitted colour word rotates
 * AARRGGBB left eight bits to the RSP's RRGGBBAA. No padding or wider state.
 */
typedef struct ArgbColor {
    u8 a;
    u8 r;
    u8 g;
    u8 b;
} ArgbColor;

#endif
