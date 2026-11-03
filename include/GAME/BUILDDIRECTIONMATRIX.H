#ifndef GAME_BUILDDIRECTIONMATRIX_H
#define GAME_BUILDDIRECTIONMATRIX_H
#include "COMMON/MTX.H"
extern void TranslateMatrixLocal(void *matrix, f32 x, f32 y, f32 z);
extern void BuildYawMatrix(void *matrix, f32 angle);
extern void Graphu64_ApproachQuaternion(CQuatern *rotation, CQuatern *target);
extern f32 Graphu64_GetWrappedDifference(f32 firstValue, f32 secondValue);
extern void Graphu64_CopySwappedMatrixBasis(f32 *dst, f32 *src);
extern void Graphu64_TransposeMatrixBasis(f32 *destination, f32 *source);
extern void Graphu64_CopyScaledMatrix(float * destination, float * source, float sx, float sy, float sz);
extern void Graphu64_InterpolateQuaternionComponents(void *cQuatern, f32 t, void *a, void *b);
extern void Graphu64_SwapMatrixCoordinates(struct CMatrix4 *object);
extern void Graphu64_CopySwappedMatrixCoordinates(f32 *dst, f32 *src);
struct CMatrix4;
struct CVector3_t;
void BuildDirectionMatrix(struct CMatrix4 *m, struct CVector3_t *direction);
void BuildPitchMatrix(void *rest, f32 pitchAngle);
void CopyMatrix(float *destinationMatrix, float *sourceMatrix);
void Graphu64_BuildPlaneProjectionMatrix(void *projection, void *projectionDirection, f32 plane);
void Graphu64_GetMatrixScale(void *matrix, f32 *scaleOutput);
void Graphu64_GetMatrixTranslation(char *object, float *output);
void MultiplyQuaternions(void *productQuaternion, void *leftQuaternion, void *rightQuaternion);
void PitchMatrixLocal(void *matrixStorage, f32 pitchAngle);
void RollMatrix(void *matrixStorage, f32 rollAngle);
void ScaleMatrixLocal(void *matrix, f32 sx, f32 sy, f32 sz);
void TranslateMatrix(char *object, float x, float y, float z);
#endif
