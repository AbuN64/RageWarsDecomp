#ifndef COMMON_POOLED_FLOATS_H
#define COMMON_POOLED_FLOATS_H
#include "TYPES.H"
/* Float constants pooled by the linker: the first word is read by some functions and the second by others. */
extern f32 g_portalNodeWaitAndHeightOffset;
extern f32 g_matrixClampAndProjectionConstants;
extern f32 g_translationAndScaleMatrixUnitConstants;
extern f32 g_pitchAndRollMatrixUnitConstants[2];
extern f32 g_wrappedDifferenceAndApproachConstants[2];
extern f32 g_identityAndFixedMatrixConstants;
extern const f32 g_translationAndSwappedBasisUnitConstants[2];
extern const f32 g_swappedCoordinatesAndWrapConstants[2];
#endif
