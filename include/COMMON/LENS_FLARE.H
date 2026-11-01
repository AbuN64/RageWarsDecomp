#ifndef COMMON_LENS_FLARE_H
#define COMMON_LENS_FLARE_H
#include "TYPES.H"

/* Seven flare elements: radius, opacity, and RGB components. */
typedef struct FlareRadii { f32 value[7]; } FlareRadii;
typedef struct FlareAlphas { s32 value[7]; } FlareAlphas;
typedef struct FlareColors { s32 value[21]; } FlareColors;
extern const FlareRadii k_lensFlareRadii;
extern const FlareAlphas k_lensFlareAlphas;
extern const FlareColors k_lensFlareColors;
#endif
