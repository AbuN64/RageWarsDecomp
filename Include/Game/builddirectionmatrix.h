#ifndef GAME_BUILDDIRECTIONMATRIX_H
#define GAME_BUILDDIRECTIONMATRIX_H
#include "Common/graphics_matrix_and_vector_math.h"
#include "Engine/graphics_math.h"
#include "Common/mtx.h"
struct Matrix;
extern void TranslateMatrixLocal(struct Matrix *matrix, f32 tiltX, f32 lift, f32 translationZ);

extern void Graphu64_ApproachQuaternion(CQuatern *rotation, CQuatern *target);
extern f32 Graphu64_GetWrappedDifference(f32 firstValue, f32 secondValue);
extern void Graphu64_CopySwappedMatrixBasis(f32 *dst, f32 *src);
extern void Graphu64_TransposeMatrixBasis(f32 *destination, f32 *source);
extern void Graphu64_CopyScaledMatrix(float * destination, float * source, float sx, float sy, float sz);
extern void Graphu64_InterpolateQuaternionComponents(CQuatern *cQuatern, f32 t, void *savedComponent, void *b);
extern void Graphu64_SwapMatrixCoordinates(struct CMatrix4 *object);
extern void Graphu64_CopySwappedMatrixCoordinates(f32 *dst, f32 *src);
struct CMatrix4;
struct CVector3_t;
void BuildDirectionMatrix(struct CMatrix4 *m, struct CVector3_t *direction);
void BuildPitchMatrix(struct CMatrix4 *rest, f32 pitchAngle);
void CopyMatrix(float *destinationMatrix, float *sourceMatrix);
void Graphu64_BuildPlaneProjectionMatrix(void *projection, CVector3 *projectionDirection, f32 plane);
void Graphu64_GetMatrixScale(struct Matrix *matrix, f32 *scaleOutput);
void Graphu64_GetMatrixTranslation(char *object, float *output);
void MultiplyQuaternions(void *productQuaternion, void *leftQuaternion, void *rightQuaternion);
void PitchMatrixLocal(struct CMatrix4 *matrixStorage, f32 pitchAngle);
void RollMatrix(struct CMatrix4 *matrixStorage, f32 rollAngle);
void ScaleMatrixLocal(struct Matrix *matrix, f32 sx, f32 sy, f32 sz);
void TranslateMatrix(char *object, float x, float y, float z);
extern void MatrixFromQuaternion(f32 *q, f32 *m);


#endif
