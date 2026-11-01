#ifndef UI_X_FILES_X_MATH_H
#define UI_X_FILES_X_MATH_H
#include "TYPES.H"
#include "COMMON/OBJRECAT3CV2.H"
#include "COMMON/MATRIXRECORD.H"
struct RotationMatrixWords {
    f32 m00;
    f32 m01;
    f32 m02;
    f32 m03;
    f32 m10;
    f32 m11;
    f32 m12;
    f32 m13;
    f32 m20;
    f32 m21;
    f32 m22;
    f32 m23;
    f32 m30;
    f32 m31;
    f32 m32;
    f32 m33;
};
struct RotationMatrixElementsView {
    f32 f00;
    f32 f04;
    f32 f08;
    f32 pad0C;
    f32 pad10;
    f32 f14;
    f32 pad18;
    f32 pad1C;
    f32 f20;
    f32 f24;
    f32 f28;
};

extern void XMath_BuildYxzRotationMatrix(RotationMatrixWords *matrixOut, CVector3 *angles);
extern void XMath_OrthogonalizeMatrixBasis(PlaneEquation *m);
extern void XMath_ExtractYxzAngles(RotationMatrixElementsView *matrix, CVector3 *anglesOut);
extern void XMath_ExtractZyxAngles(RotationMatrixElementsView *matrix, CVector3 *anglesOut);
extern s32 XMath_InvertAffineMatrix(f32 *out, f32 *input);

extern void Vector3AnglesInverse(f32 *vector, f32 *pitchOut, f32 *yawOut);
extern void Vector3ProjectArray(CVector3 *out, CVector3 *in, s32 n, f32 ox, f32 sx, f32 oy, f32 sy);
extern void Vector3IntersectPlane(CVector3 *intersectionOut, CVector3 *lineStart, CVector3 *lineEnd, f32 normalX, f32 normalY, f32 normalZ, f32 planeOffset);
extern void Vector3Angles(f32 *vector, f32 *pitchOut, f32 *yawOut);
extern f32 Vector3Dot(f32 *a, f32 *b);
extern void Vector3Distance(f32 *a, f32 *b);
extern void Vector3Cross(CVector3 *out, CVector3 *a, CVector3 *b);
extern void XMath_EvaluateVectorLength(CVector3 *vector);
extern void Vector3Add(void *destination, void *leftVector, void *rightVector);
extern void Vector3Zero(float *vector);
extern void Vector3Normalize(f32 *vector);
extern void Vector3Copy(Triple *destination, Triple *source);
extern void Vector3Subtract(void *destination, void *leftVector, void *rightVector);
extern void XMath_CopyMatrix(void *destination, void *source);
extern f32 XMath_SubtractAnglesCentered(f32 a, f32 b);
extern void Vector3Set(void *destination, float xValue, float yValue, float zValue);
extern void Vector3Negate(void *destination, void *source);
extern void Vector3Scale(void *destination, void *source, f32 scaleFactor);
extern void Vector3Unpack(float *source, float *xOut, float *yOut, float *zOut);

extern s32 XMath_ClipPolygonToPlane(CVector3 *out, s32 *outCount, CVector3 *in, s32 n, f32 a, f32 b, f32 c, f32 d);

extern f64 XMath_EvaluateHyperbolicTangent(f64 x);
extern void XMath_ConvertYzxToZyxAngles(CVector3 *angles);
extern void XMath_ConvertZyxToYxzAngles(f32 *angles);
extern void XMath_ConvertYxzToZyxAngles(f32 *angles);
extern void XMath_ConvertZyxToYzxAngles(CVector3 *angles);

extern f32 XMath_WrapAnglePositive(f32 angle);

/* Matrix constructor record: four header words precede the 4x4 matrix. */
typedef struct MatrixRecord {
    u32 header[4];
    Matrix matrix;
} MatrixRecord;
struct Matrix3x4View {
    f32 m[3][4];
};

extern void XMath_GetMatrixTranslation(char *object, float *output);
extern void XMath_ResetMatrixRotation(Matrix3x4View *matrix);
extern void XMath_SetMatrixScaleDiagonal(Matrix *matrix, CVector3 *scale);
extern void XMath_AddMatrixTranslation(Matrix *matrix, void *translation);
extern void XMath_ClearMatrixTranslation(Matrix *matrix);
extern void XMath_SetUniformMatrixScaleDiagonal(Matrix *matrix, float value);
extern void XMath_TransformPointArray(void *matrix, void *destination, void *source, s32 pointCount);
extern void XMath_ScaleMatrixRows(void *matrix, void *scale);
extern void XMath_GetMatrixColumns(float *matrix, float *columnX, float *columnY, float *columnZ);
extern void XMath_PremultiplyMatrix(int destinationMatrix, int leftMatrix);
extern void XMath_PostmultiplyMatrix(s32 destinationMatrix, s32 rightMatrix);
extern void XMath_PremultiplyEulerRotation(s32 matrix, f32 *angles);
extern void XMath_SetMatrixTranslation(Matrix *matrix, float *translation);
extern void XMath_SetMatrixRows(float *matrix, float *rowX, float *rowY, float *rowZ);
extern void XMath_SetMatrixColumns(float *matrix, float *columnX, float *columnY, float *columnZ);
extern void XMath_ScaleMatrixUniformly(void *matrix, f32 scale);
extern void XMath_SetMatrixElements(MatrixRecord *matrix, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);
extern void XMath_GetMatrixRows(float *matrix, float *rowX, float *rowY, float *rowZ);
extern void XMath_TransposeMatrix(f32 *matrix);
#endif
