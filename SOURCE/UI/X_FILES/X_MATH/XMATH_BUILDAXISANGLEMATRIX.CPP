#include "COMMON/VECTOR3.H"
#include "COMMON/MATRIXRECORD.H"
#include "UI/X_FILES/X_MATH.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "RESMGR/resmgr_string_memory.H"
extern void MatrixFromAngles(struct MatrixF *matrix, f32 *angles);


void XMath_SetMatrixElements(MatrixRecord *matrix, float element00, float element01, float element02,
                    float element03, float element10, float element11, float element12,
                    float element13, float element20, float element21, float element22,
                    float element23, float element30, float element31, float element32, float element33) {
    matrix->matrix.m[0] = element00;
    matrix->matrix.m[4] = element01;
    matrix->matrix.m[8] = element02;
    matrix->matrix.m[12] = element03;
    matrix->matrix.m[1] = element10;
    matrix->matrix.m[5] = element11;
    matrix->matrix.m[9] = element12;
    matrix->matrix.m[13] = element13;
    matrix->matrix.m[2] = element20;
    matrix->matrix.m[6] = element21;
    matrix->matrix.m[10] = element22;
    matrix->matrix.m[14] = element23;
    matrix->matrix.m[3] = element30;
    matrix->matrix.m[7] = element31;
    matrix->matrix.m[11] = element32;
    matrix->matrix.m[15] = element33;
}

void XMath_ClearMatrix(s32 destination) {
    XPlus_FillBytes(destination, 0, 64);
}

void XMath_SetIdentityMatrix(s32 matrixAddress)
{
  XPlus_FillBytes(matrixAddress, 0, 64);
  ((Matrix *)(matrixAddress))->m[15] = (((Matrix *)(matrixAddress))->m[10] = (((Matrix *)(matrixAddress))->m[5] = (((Matrix *)(matrixAddress))->m[0] = (f32) k_xmathIdentityMatrixUnit)));
}

void XMath_TransposeMatrix(f32 *matrix) {
    s32 i;
    s32 j;
    s32 offset1;
    s32 offset2;
    f32 temp;

    for (i = 0; i < 3; i++) {
        for (j = i + 1; j < 4; j++) {
            offset2 = j * 16 + i * 4;
            offset1 = i * 16 + j * 4;
            temp = *(f32 *)((u8 *)matrix + offset2);
            *(f32 *)((u8 *)matrix + offset2) =
                *(f32 *)((u8 *)matrix + offset1);
            *(f32 *)((u8 *)matrix + offset1) = temp;
        }
    }
}

/** Scatter three floats from scale into matrix's fields. */
void XMath_SetMatrixScaleDiagonal(Matrix *matrix, CVector3 *scale) {
    matrix->m[0] = scale->x;
    matrix->m[5] = scale->y;
    matrix->m[10] = scale->z;
}

void XMath_ScaleMatrixRows(void *matrix, void *scale) {
    char *m = (char *) matrix;
    char *v = (char *) scale;

    ((Matrix *)(m))->m[0] = ((Matrix *)(m))->m[0] * ((CVector3 *)(v))->x;
    ((Matrix *)(m))->m[4] = ((Matrix *)(m))->m[4] * ((CVector3 *)(v))->x;
    ((Matrix *)(m))->m[8] = ((Matrix *)(m))->m[8] * ((CVector3 *)(v))->x;
    ((Matrix *)(m))->m[1] = ((Matrix *)(m))->m[1] * ((CVector3 *)(v))->y;
    ((Matrix *)(m))->m[5] = ((Matrix *)(m))->m[5] * ((CVector3 *)(v))->y;
    ((Matrix *)(m))->m[9] = ((Matrix *)(m))->m[9] * ((CVector3 *)(v))->y;
    ((Matrix *)(m))->m[2] = ((Matrix *)(m))->m[2] * ((CVector3 *)(v))->z;
    ((Matrix *)(m))->m[6] = ((Matrix *)(m))->m[6] * ((CVector3 *)(v))->z;
    ((Matrix *)(m))->m[10] = ((Matrix *)(m))->m[10] * ((CVector3 *)(v))->z;
    ((Matrix *)(m))->m[12] = ((Matrix *)(m))->m[12] * ((CVector3 *)(v))->x;
    ((Matrix *)(m))->m[13] = ((Matrix *)(m))->m[13] * ((CVector3 *)(v))->y;
    ((Matrix *)(m))->m[14] = ((Matrix *)(m))->m[14] * ((CVector3 *)(v))->z;
}

/** Broadcast a float value into three fields of the object. */
void XMath_SetUniformMatrixScaleDiagonal(Matrix *matrix, float value) {
    matrix->m[0] = value;
    matrix->m[5] = value;
    matrix->m[10] = value;
}

void XMath_ScaleMatrixUniformly(void *matrix, f32 scale) {
    u8 *o = (u8 *)matrix;

    ((Matrix *)(o))->m[0] = ((Matrix *)(o))->m[0] * scale;
    ((Matrix *)(o))->m[4] = ((Matrix *)(o))->m[4] * scale;
    ((Matrix *)(o))->m[8] = ((Matrix *)(o))->m[8] * scale;
    ((Matrix *)(o))->m[1] = ((Matrix *)(o))->m[1] * scale;
    ((Matrix *)(o))->m[5] = ((Matrix *)(o))->m[5] * scale;
    ((Matrix *)(o))->m[9] = ((Matrix *)(o))->m[9] * scale;
    ((Matrix *)(o))->m[2] = ((Matrix *)(o))->m[2] * scale;
    ((Matrix *)(o))->m[6] = ((Matrix *)(o))->m[6] * scale;
    ((Matrix *)(o))->m[10] = ((Matrix *)(o))->m[10] * scale;
    ((Matrix *)(o))->m[12] = ((Matrix *)(o))->m[12] * scale;
    ((Matrix *)(o))->m[13] = ((Matrix *)(o))->m[13] * scale;
    ((Matrix *)(o))->m[14] = ((Matrix *)(o))->m[14] * scale;
}

void XMath_ResetMatrixRotation(Matrix3x4View *matrix) {
    s32 col;
    s32 row;

    col = 0;
    row = 0;
    do {
        row = 0;
        do {
            matrix->m[row][col] = 0;
            row += 1;
        } while (row < 3);
        col += 1;
    } while (col < 3);
    matrix->m[0][0] = k_xmathRotationResetUnit;
    matrix->m[1][1] = k_xmathRotationResetUnit;
    matrix->m[2][2] = k_xmathRotationResetUnit;
}

void XMath_PremultiplyEulerRotation(s32 matrix, f32 *angles) {
    f32 buf[16];
    MatrixFromAngles(buf, angles);
    XMath_MultiplyMatrices(matrix, buf, matrix);
}

void XMath_PremultiplyPitchRotation(s32 destinationMatrix, f32 angle) {
    Matrix matrix;
    f32 sineAngle;
    f32 cosineAngle;
    Matrix *p;

    if (angle != 0.0f) {
        XMath_EvaluateSineCosine(angle, &sineAngle, &cosineAngle);
        p = &matrix;
        XPlus_FillBytes(p, 0, 64);
        ((Matrix *)(p))->m[0] = k_xmathPitchRotationUnit;
        {
            f32 cosineValue = cosineAngle;
            f32 sineValue = sineAngle;
            ((Matrix *)(p))->m[5] = k_xmathPitchRotationUnit;
            ((Matrix *)(p))->m[10] = k_xmathPitchRotationUnit;
            ((Matrix *)(p))->m[15] = k_xmathPitchRotationUnit;
            matrix.m[5] = cosineValue;
            matrix.m[9] = -sineValue;
            matrix.m[6] = sineValue;
            matrix.m[10] = cosineValue;
        }
        XMath_MultiplyMatrices(destinationMatrix, (s32) p, destinationMatrix);
    }
}

void XMath_PremultiplyYawRotation(s32 matrixAddress, f32 radians) {
    Matrix matrix;
    f32 sinAngle;
    f32 cosAngle;
    Matrix *p;

    if (radians != 0.0f) {
        XMath_EvaluateSineCosine(radians, &sinAngle, &cosAngle);
        p = &matrix;
        XPlus_FillBytes(p, 0, 64);
        ((Matrix *)(p))->m[0] = k_xmathYawRotationUnit;
        {
            f32 cosineValue = cosAngle;
            f32 sineValue = sinAngle;
            f32 negativeSine;
            ((Matrix *)(p))->m[5] = k_xmathYawRotationUnit;
            ((Matrix *)(p))->m[10] = k_xmathYawRotationUnit;
            ((Matrix *)(p))->m[15] = k_xmathYawRotationUnit;
            negativeSine = -sineValue;
            matrix.m[8] = sineValue;
            matrix.m[0] = cosineValue;
            matrix.m[2] = negativeSine;
            matrix.m[10] = cosineValue;
        }
        XMath_MultiplyMatrices(matrixAddress, (s32) p, matrixAddress);
    }
}

void XMath_PremultiplyRollRotation(s32 matrixAddress, f32 radians) {
    Matrix matrix;
    f32 sinAngle;
    f32 cosAngle;
    Matrix *p;

    if (radians != 0.0f) {
        XMath_EvaluateSineCosine(radians, &sinAngle, &cosAngle);
        p = &matrix;
        XPlus_FillBytes(p, 0, 64);
        ((Matrix *)(p))->m[0] = k_xmathRollRotationUnit;
        {
            f32 cosineValue = cosAngle;
            f32 sineValue = sinAngle;
            f32 negativeSine;
            ((Matrix *)(p))->m[5] = k_xmathRollRotationUnit;
            ((Matrix *)(p))->m[10] = k_xmathRollRotationUnit;
            ((Matrix *)(p))->m[15] = k_xmathRollRotationUnit;
            negativeSine = -sineValue;
            matrix.m[0] = cosineValue;
            matrix.m[4] = negativeSine;
            matrix.m[1] = sineValue;
            matrix.m[5] = cosineValue;
        }
        XMath_MultiplyMatrices(matrixAddress, (s32) p, matrixAddress);
    }
}

/** Clear the three words at object offsets 0x30 through 0x38. */
void XMath_ClearMatrixTranslation(Matrix *matrix) {
    matrix->m[12] = 0;
    matrix->m[13] = 0;
    matrix->m[14] = 0;
}

/** Copy a three-float vector into object offsets 0x30 through 0x38. */
void XMath_SetMatrixTranslation(Matrix *matrix, float *translation) {
    matrix->m[12] = translation[0];
    matrix->m[13] = translation[1];
    matrix->m[14] = translation[2];
}

/** Copy the three floating components at offset 0x30. */
void XMath_GetMatrixTranslation(char *object, float *output) {
    output[0] = ((Matrix *)(object))->m[12];
    output[1] = ((Matrix *)(object))->m[13];
    output[2] = ((Matrix *)(object))->m[14];
}

void XMath_AddMatrixTranslation(Matrix *matrix, void *translation) {
    (matrix->m[12]) = (f32) ((matrix->m[12]) + (((struct CVector3_t *) ((s8 *) translation))->x));
    (matrix->m[13]) = (f32) ((matrix->m[13]) + (((struct CVector3_t *) ((s8 *) translation))->y));
    (matrix->m[14]) = (f32) ((matrix->m[14]) + (((struct CVector3_t *) ((s8 *) translation))->z));
}

/** Combine three column vectors into the first three matrix columns. */
void XMath_SetMatrixRows(float *matrix, float *rowX, float *rowY, float *rowZ) {
    matrix[0] = rowX[0];
    matrix[4] = rowX[1];
    matrix[8] = rowX[2];
    matrix[1] = rowY[0];
    matrix[5] = rowY[1];
    matrix[9] = rowY[2];
    matrix[2] = rowZ[0];
    matrix[6] = rowZ[1];
    matrix[10] = rowZ[2];
}

/** Split the first three matrix columns into three vectors. */
void XMath_GetMatrixRows(float *inputMatrix, float *rowX, float *rowY, float *rowZ) {
    rowX[0] = inputMatrix[0];
    rowX[1] = inputMatrix[4];
    rowX[2] = inputMatrix[8];
    rowY[0] = inputMatrix[1];
    rowY[1] = inputMatrix[5];
    rowY[2] = inputMatrix[9];
    rowZ[0] = inputMatrix[2];
    rowZ[1] = inputMatrix[6];
    rowZ[2] = inputMatrix[10];
}

/** Write three row vectors into the first three matrix rows. */
void XMath_SetMatrixColumns(float *matrix, float *columnX, float *columnY, float *columnZ) {
    matrix[0] = columnX[0];
    matrix[1] = columnX[1];
    matrix[2] = columnX[2];
    matrix[4] = columnY[0];
    matrix[5] = columnY[1];
    matrix[6] = columnY[2];
    matrix[8] = columnZ[0];
    matrix[9] = columnZ[1];
    matrix[10] = columnZ[2];
}

/** Split the first three matrix rows into three row vectors. */
void XMath_GetMatrixColumns(float *inputMatrix, float *columnX, float *columnY, float *columnZ) {
    columnX[0] = inputMatrix[0];
    columnX[1] = inputMatrix[1];
    columnX[2] = inputMatrix[2];
    columnY[0] = inputMatrix[4];
    columnY[1] = inputMatrix[5];
    columnY[2] = inputMatrix[6];
    columnZ[0] = inputMatrix[8];
    columnZ[1] = inputMatrix[9];
    columnZ[2] = inputMatrix[10];
}

/** Thin wrapper forwarding destinationMatrix twice (as first and third args) to XMath_MultiplyMatrices. */
void XMath_PremultiplyMatrix(int destinationMatrix, int leftMatrix) {
    XMath_MultiplyMatrices(destinationMatrix, leftMatrix, destinationMatrix);
}

void XMath_PostmultiplyMatrix(s32 destinationMatrix, s32 rightMatrix) {
    XMath_MultiplyMatrices(destinationMatrix, destinationMatrix, rightMatrix);
}

void XMath_TransformPointArray(void *matrix, void *outputPoints, void *inputPoints, s32 pointCount) {
    u8 *m = (u8 *) matrix;
    s32 i;
    f32 vx, vy, vz;

    i = 0;
    if (pointCount > 0) {
        do {
            u8 *v = (u8 *) inputPoints + i * sizeof(CVector3);
            u8 *out = (u8 *) outputPoints + i * sizeof(CVector3);

            vx = ((CVector3 *)(v))->x;
            vy = ((CVector3 *)(v))->y;
            vz = ((CVector3 *)(v))->z;
            ((CVector3 *)(out))->x = (((Matrix *)(m))->m[0] * vx) + (((Matrix *)(m))->m[4] * vy) + (((Matrix *)(m))->m[8] * vz) + ((Matrix *)(m))->m[12];
            ((CVector3 *)(out))->y = (((Matrix *)(m))->m[1] * vx) + (((Matrix *)(m))->m[5] * vy) + (((Matrix *)(m))->m[9] * vz) + ((Matrix *)(m))->m[13];
            ((CVector3 *)(out))->z = (((Matrix *)(m))->m[2] * vx) + (((Matrix *)(m))->m[6] * vy) + (((Matrix *)(m))->m[10] * vz) + ((Matrix *)(m))->m[14];
            i += 1;
        } while (i < pointCount);
    }
}

void XMath_BuildAxisAngleMatrix(struct MatrixF *matrixF, CVector3 *axis, f32 radians) {
    f32 sine;
    f32 cosine;
    f32 cosine_value;
    f32 one;
    f32 one_minus_cosine;
    f32 tx;
    f32 ty;
    f32 tz;
    f32 txx;
    f32 txy;
    f32 txz;
    f32 tyy;
    f32 tyz;
    f32 tzz;
    f32 sx;
    f32 sy;
    f32 sz;
    f32 zero;

    XMath_EvaluateSineCosine(radians, &sine, &cosine);
    cosine_value = cosine;
    one = k_xmathAxisAngleUnit;
    one_minus_cosine = one - cosine_value;
    tx = one_minus_cosine * axis->x;
    ty = one_minus_cosine * axis->y;
    tz = one_minus_cosine * axis->z;
    txx = tx * axis->x;
    txy = tx * axis->y;
    txz = tx * axis->z;
    tyy = ty * axis->y;
    tyz = ty * axis->z;
    tzz = tz * axis->z;
    sx = sine * axis->x;
    sy = sine * axis->y;
    sz = sine * axis->z;
    zero = 0.0f;
    matrixF->m[3][2] = zero;
    matrixF->m[3][1] = zero;
    matrixF->m[3][0] = zero;
    matrixF->m[2][3] = zero;
    matrixF->m[1][3] = zero;
    matrixF->m[0][3] = zero;
    matrixF->m[3][3] = one;
    matrixF->m[0][0] = txx + cosine_value;
    matrixF->m[0][1] = txy + sz;
    matrixF->m[0][2] = txz - sy;
    matrixF->m[1][0] = txy - sz;
    matrixF->m[1][1] = tyy + cosine_value;
    matrixF->m[1][2] = tyz + sx;
    matrixF->m[2][0] = txz + sy;
    matrixF->m[2][1] = tyz - sx;
    matrixF->m[2][2] = tzz + cosine_value;
}

void XMath_BuildScaleRotationTranslationMatrix(void *matrix, CVector3 *scale, void *angles, CVector3 *translation) {
    Matrix *m = matrix;

    MatrixFromAngles(matrix, angles);

    m->m[0] = m->m[0] * scale->x;
    m->m[1] = m->m[1] * scale->x;
    m->m[2] = m->m[2] * scale->x;
    m->m[4] = m->m[4] * scale->y;
    m->m[5] = m->m[5] * scale->y;
    m->m[6] = m->m[6] * scale->y;
    m->m[8] = m->m[8] * scale->z;
    m->m[9] = m->m[9] * scale->z;
    m->m[10] = m->m[10] * scale->z;
    m->m[12] = m->m[12] + translation->x;
    m->m[13] = m->m[13] + translation->y;
    m->m[14] = m->m[14] + translation->z;
}
