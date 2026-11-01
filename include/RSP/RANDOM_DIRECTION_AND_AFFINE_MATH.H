#ifndef RSP_RANDOM_DIRECTION_AND_AFFINE_MATH_H
#define RSP_RANDOM_DIRECTION_AND_AFFINE_MATH_H
#include "COMMON/OBJRECAT4V7.H"
extern CVector3 *Graphu64_BlendRandomZDirection(CVector3 *out, CVector3 *in, f32 amount);
extern void Graphu64_InvertAffineMatrix(f32 *out, f32 *m);
extern f32 g_directionMatrixUnitConstants_de;
extern f32 g_turretAimSine;
extern f32 Gu_Sqrtf(f32 value);
extern s32 Graphu64_NextRandom(void);
extern f32 k_graphu64RandomDirectionLiteralFirst_de;
extern f32 k_graphu64RandomDirectionLiteralSecond_de;
#endif
