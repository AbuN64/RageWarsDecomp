#ifndef ENGINE_GRAPHICS_MATH_H
#define ENGINE_GRAPHICS_MATH_H
#include "types.h"
struct FixedPointMatrix;
extern void Graphu64_ConvertMatrixToFixed(f32 *src, struct FixedPointMatrix *dst);
#include "types.h"
struct FixedPointMatrix;

extern int g_primaryRandomSeed;
#include "Collide/ccollision_testsegmentdisk.h"
#include "Common/vector.h"
#include "types.h"
#include "Common/material_tree.h"
#include "Common/graphics_matrix_and_vector_math.h"

struct MatrixF {
    f32 m[4][4];
};
typedef struct MatrixF MatrixF;


struct Matrix;
extern f32 g_arcCosEndpoint;

extern const float g_fullMatrixFixedConversionPairs[16][2];
extern const float g_affineMatrixFixedConversionPairs[12][2];
/* The converters read each scale/offset pair as its own symbol, as the ROM addresses them (link-only aliases). */
extern float g_fullFixedMatrixElement0ConversionConstants;
extern float g_fullFixedMatrixElement1ConversionConstants;
extern float g_fullFixedMatrixElement2ConversionConstants;
extern float g_fullFixedMatrixElement3ConversionConstants;
extern float g_fullFixedMatrixElement4ConversionConstants;
extern float g_fullFixedMatrixElement5ConversionConstants;
extern float g_fullFixedMatrixElement6ConversionConstants;
extern float g_fullFixedMatrixElement7ConversionConstants;
extern float g_fullFixedMatrixElement8ConversionConstants;
extern float g_fullFixedMatrixElement9ConversionConstants;
extern float g_fullFixedMatrixElement10ConversionConstants;
extern float g_fullFixedMatrixElement11ConversionConstants;
extern float g_fullFixedMatrixElement12ConversionConstants;
extern float g_fullFixedMatrixElement13ConversionConstants;
extern float g_fullFixedMatrixElement14ConversionConstants;
extern float g_fullFixedMatrixElement15ConversionConstants;
extern float g_affineFixedMatrixElement0ConversionConstants;
extern float g_affineFixedMatrixElement1ConversionConstants;
extern float g_affineFixedMatrixElement2ConversionConstants;
extern float g_affineFixedMatrixElement4ConversionConstants;
extern float g_affineFixedMatrixElement5ConversionConstants;
extern float g_affineFixedMatrixElement6ConversionConstants;
extern float g_affineFixedMatrixElement8ConversionConstants;
extern float g_affineFixedMatrixElement9ConversionConstants;
extern float g_affineFixedMatrixElement10ConversionConstants;
extern float g_affineFixedMatrixElement12ConversionConstants;
extern float g_affineFixedMatrixElement13ConversionConstants;
extern float g_affineFixedMatrixElement14ConversionConstants;

extern CVector3 *Graphu64_ProjectOntoCrossNormal(CVector3 *out, CVector3 *value, CVector3 *a, CVector3 *b);
extern void Graphu64_InterpolateQuaternionArc(CQuatern *out, f32 amount, CQuatern *a, CQuatern *b);
extern f32 Graphu64_GetPointDistance(f32 *a, f32 *b);
extern void Graphu64_ScaleMatrixWorld(struct Matrix *matrix, f32 sx, f32 sy, f32 sz);
extern void MatrixFromQuaternion(f32 *q, f32 *m);

extern void RollMatrixLocal(struct CMatrix4 *matrix, f32 rollAngle);
extern void BuildRollMatrix(struct CMatrix4 *matrix, f32 rollAngle);
extern f32 Graphu64_GetSquaredDistance(f32 *a, f32 *b);
extern void SwapMatrixUpForward(struct CMatrix4 *object);
extern f32 g_boundedIntegrationAndEaseConstants[2];
extern f32 g_planeProjectionNormalScale;
extern f32 g_wrappedApproachStep;
extern u32 g_secondaryRandomSeed;
extern CVector3 g_directionMatrixUnitConstants_de[2];
struct FixedPointMatrix; extern void Graphu64_UnpackFixedMatrix(f32 *dst, struct FixedPointMatrix *src);
#endif
