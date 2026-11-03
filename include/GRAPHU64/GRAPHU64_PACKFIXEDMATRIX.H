#ifndef GRAPHU64_GRAPHU64_PACKFIXEDMATRIX_H
#define GRAPHU64_GRAPHU64_PACKFIXEDMATRIX_H
struct PackedMatrixWords;
void GraphU64_PackFixedMatrix(f32 *src, struct PackedMatrixWords *dst);
struct CVector3_t;
struct CQuatern_t Graphu64_BuildDirectionQuaternion(struct CVector3_t *input);
void Graphu64_ConvertMatrixToFloat(f32 *dst, struct PackedMatrixWords *src);
void Graphu64_InvertAffineMatrix(f32 *out, f32 *m);
void Graphu64_MultiplyAffineMatrices(f32 *out, f32 *left, f32 *right);
#endif
