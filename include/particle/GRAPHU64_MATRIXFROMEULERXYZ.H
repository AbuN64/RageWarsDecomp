#ifndef PARTICLE_GRAPHU64_MATRIXFROMEULERXYZ_H
#define PARTICLE_GRAPHU64_MATRIXFROMEULERXYZ_H
#include "COMMON/GRAPHICS_MATRIX_AND_VECTOR_MATH.H"
extern void Graphu64_RunCountdown(void);
extern void Graphu64_NoOperation(void);
extern void Graphu64_TransformPoint(void *matrix, void *inputPoint, void *transformedPoint);
void Graphu64_BuildAxisAngleMatrix(f32 (*mfThis)[4], f32 Theta, f32 X, f32 Y, f32 Z);
void Graphu64_BuildTranslationMatrix(void *matrix, f32 translationX, f32 translationY, f32 translationZ);
void Graphu64_ClampMatrixToFixedRange(f32 *matrixComponents);
f32 Graphu64_GetVerticalAngle(f32 *delta);
void Graphu64_IdentityMatrix(void *matrixStorage);
s32 Graphu64_LimitVectorLength(f32 *vectorComponents, f32 maximumLength);
void Graphu64_MatrixFromEulerXYZ(f32 *m, f32 x, f32 y, f32 z);
struct CVector3_t;
void Graphu64_ProjectPoint(void *matrix, void *inputPoint, struct CVector3_t *localDirection);
void Graphu64_TransformDirection(void *matrix, void *inputDirection, void *transformedDirection);
void Graphu64_TransformDirectionTranspose(void *matrix, void *inputDirection, void *outputDirection);
void Graphu64_TransformPoints(f32 *m, f32 *in, f32 *out, u32 count);
#endif
