#ifndef COMMON_GRAPHICS_MATRIX_AND_VECTOR_MATH_H
#define COMMON_GRAPHICS_MATRIX_AND_VECTOR_MATH_H
#include "types.h"
struct CMatrix4;
extern void YawMatrix(struct CMatrix4 *matrix, f32 yawAngle);
#include "types.h"
struct CMatrix4;
extern void PitchMatrix(struct CMatrix4 *matrixStorage, f32 pitchAngle);
#include "types.h"
struct CMatrix4;
extern void BuildYawMatrix(struct CMatrix4 *matrixStorage, f32 yawAngle);
#include "types.h"
struct Matrix;
extern void Graphu64_BuildScaleMatrix(struct Matrix *matrix, f32 scaleX, f32 scaleY, f32 scaleZ);
#include "types.h"
struct CMatrix4;

#include "types.h"
struct CMatrix4;

#include "types.h"
struct CMatrix4;

#include "types.h"
struct Matrix;

#include "types.h"
#include "Common/sharedplayer.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"

struct Matrix;

extern float g_inverseAffineHomogeneousScale;















extern f32 Graphu64_GetAngleDistance(f32 target, f32 current);

extern void Graphu64_MultiplyVectorComponents(CVector3 *result, CVector3 *left, CVector3 *right);

extern float g_vectorVerticalAngleLowerConstants;

extern float g_eulerMatrixHomogeneousScale;

extern float g_vectorVerticalAngleUpperConstants;


extern void *Graphu64_ReflectVector(CVector3 *result, CVector3 *remaining, CVector3 *normal, f32 restitution);

extern void *Graphu64_ProjectVectorOntoPlane(CVector3 *result, CVector3 *remaining, CVector3 *normal);





extern void Graphu64_InterpolateAtHeight(CVector3 *out, CVector3 *a, CVector3 *b, f32 y);





#endif
