#ifndef COMMON_GRAPHICS_MATRIX_AND_VECTOR_MATH_H
#define COMMON_GRAPHICS_MATRIX_AND_VECTOR_MATH_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
extern void Graphu64_BuildTranslationMatrix(void *matrix, f32 x, f32 y, f32 z);
extern void Graphu64_BuildScaleMatrix(void *matrix, f32 x, f32 y, f32 z);
extern float g_inverseAffineHomogeneousScale;










extern f32 Graphu64_GetVerticalAngle(f32 *delta);




extern f32 Graphu64_GetAngleDistance(f32 target, f32 current);

extern void Graphu64_MultiplyVectorComponents(CVector3 *result, CVector3 *left, CVector3 *right);

extern float g_vectorVerticalAngleLowerConstants;

extern float g_eulerMatrixHomogeneousScale;

extern float g_vectorVerticalAngleUpperConstants;


extern void *Graphu64_ReflectVector(CVector3 *result, CVector3 *remaining, CVector3 *normal, f32 restitution);

extern void *Graphu64_ProjectVectorOntoPlane(CVector3 *result, CVector3 *remaining, CVector3 *normal);





extern void Graphu64_InterpolateAtHeight(CVector3 *out, CVector3 *a, CVector3 *b, f32 y);





#endif
