#ifndef GRAPHU64_GRAPHU64_PACKFIXEDMATRIX_H
#define GRAPHU64_GRAPHU64_PACKFIXEDMATRIX_H
#include "Engine/graphics_math.h"
#include "Common/vector4f.h"
struct FixedPointMatrix;
void GraphU64_PackFixedMatrix(f32 *src, struct FixedPointMatrix *dst);
struct CVector3_t;
CQuatern Graphu64_BuildDirectionQuaternion(struct CVector3_t *input);
void Graphu64_ConvertMatrixToFloat(f32 *dst, struct FixedPointMatrix *src);
void Graphu64_InvertAffineMatrix(f32 *out, f32 *m);
void Graphu64_MultiplyAffineMatrices(f32 *out, f32 *left, f32 *right);
#endif
