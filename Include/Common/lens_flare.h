#ifndef COMMON_LENS_FLARE_H
#define COMMON_LENS_FLARE_H
#include "types.h"

/* Seven flare elements: radius, opacity, and RGB components. */
typedef struct FlareRadii { f32 value[7]; } FlareRadii;
typedef struct FlareAlphas { s32 value[7]; } FlareAlphas;
typedef struct FlareColors { s32 value[21]; } FlareColors;
extern f32 k_lensFlareRadii[6];
extern s32 k_lensFlareAlphas[7];
extern s32 k_lensFlareColors[21];
#endif
