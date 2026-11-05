#ifndef RSP_RANDOM_DIRECTION_AND_AFFINE_MATH_H
#define RSP_RANDOM_DIRECTION_AND_AFFINE_MATH_H
#include "Engine/graphics_math.h"
#include "Common/material_tree.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
extern CVector3 *Graphu64_BlendRandomZDirection(CVector3 *out, CVector3 *in, f32 amount);

extern f32 g_turretAimSine;
extern f32 Gu_Sqrtf(f32 value);
extern s32 Graphu64_NextRandom(void);
extern f32 k_matrixAndSlerpUnitConstantsTail;
extern f32 k_quaternionInterpolationThresholdConstantsTail;
#endif
