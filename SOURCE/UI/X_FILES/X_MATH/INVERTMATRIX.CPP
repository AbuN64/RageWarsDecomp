#include "include_asm.h"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/OBJRECAT3CV2.H"
#include "UI/X_FILES/X_MATH.H"
#include "TYPES.H"
#include <ultra64.h>
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/TRIPLE.H"

/* The values XMath_BuildYxzRotationMatrix loads by address:
 * 0x800CAC34 = 1.0 (float, k_xmathRotationMatrixHomogeneousUnit in this cartridge's tables)
 */

/* Build a rotation matrix from the three Euler angles in angles. */
void XMath_BuildYxzRotationMatrix(RotationMatrixWords *outputMatrix, CVector3 *angles) {
    f32 sinX;
    f32 cosX;
    f32 sinY;
    f32 cosY;
    f32 sinZ;
    f32 cosZ;
    f32 sinXSinZ;
    f32 sinXCosZ;
    f32 cosYCosZ;
    f32 sinZCosY;
    f32 cosXSinY;
    f32 cosXSinZ;
    f32 cosXCosZ;
    f32 sinYCosZ;
    f32 cosXCosY;
    float sinYSinXCosZ;
    f32 matrixXContribution;
    f32 matrixYContribution;
    f32 cosYSinXSinZ;
    float sinYSinXSinZ;
    f32 sinYSinZ;
    f32 unusedCosYSinZ;
    XMath_EvaluateSineCosine(angles->x, &sinX, &cosX);
    XMath_EvaluateSineCosine(angles->y, &sinY, &cosY);
    XMath_EvaluateSineCosine(angles->z, &sinZ, &cosZ);
    sinXSinZ = sinX * sinZ;
    sinXCosZ = sinX * cosZ;
    sinYSinXSinZ = sinY * sinXSinZ;
    cosYCosZ = cosY * cosZ;
    sinZCosY = sinZ * cosY;
    cosXSinY = cosX * sinY;
    sinYSinXCosZ = sinY * sinXCosZ;
    cosXSinZ = cosX * sinZ;
    cosXCosZ = cosX * cosZ;
    sinYCosZ = sinY * cosZ;
    cosXCosY = cosX * cosY;
    matrixXContribution = sinYSinXSinZ;
    matrixYContribution = sinYSinXCosZ;
    cosYSinXSinZ = cosY * sinXSinZ;
    sinYSinZ = sinY * sinZ;
    unusedCosYSinZ = cosY * sinZ;
    outputMatrix->m21 = -sinX;
    outputMatrix->m20 = cosXSinY;
    outputMatrix->m01 = cosXSinZ;
    outputMatrix->m11 = cosXCosZ;
    outputMatrix->m03 = outputMatrix->m13 = outputMatrix->m23 = outputMatrix->m30 = outputMatrix->m31 = outputMatrix->m32 = 0.0f;
    outputMatrix->m22 = cosXCosY;
    outputMatrix->m33 = k_xmathRotationMatrixHomogeneousUnit;
    outputMatrix->m00 = cosYCosZ + matrixXContribution;
    outputMatrix->m10 = matrixYContribution - sinZCosY;
    outputMatrix->m02 = cosYSinXSinZ - sinYCosZ;
    outputMatrix->m12 = sinYSinZ + sinXCosZ * cosY;
}


void XMath_ExtractYxzAngles(RotationMatrixWords *inputMatrix, CVector3 *outputAngles) {
    f32 clamped;
    f32 magnitude;
    f32 polynomial;
    f32 root;
    f32 delta;
    f32 test;
    f32 angle;
    f32 angle_temp;
    f32 out2;
    s32 negative;
    clamped = inputMatrix->m21;
    if (k_yxzExtractionClampAndZero < clamped) {
        clamped = k_yxzExtractionClampAndZero;
    }
    if (clamped < *(&k_yxzExtractionClampAndZero + 1)) {
        clamped = *(&k_yxzExtractionClampAndZero + 1);
    }
    magnitude = -clamped;
    if (k_yxzExtractionClampAndZero < magnitude) {
        magnitude = k_yxzExtractionClampAndZero;
    }
    if (magnitude < *(&k_yxzExtractionClampAndZero + 1)) {
        magnitude = *(&k_yxzExtractionClampAndZero + 1);
    }
    negative = 0;
    if (magnitude < 0.0f) {
        negative = 1;
        magnitude = -magnitude;
    }
    polynomial = (((((((((magnitude * k_yxzExtractionPolynomialCoefficientsOne) + *(&k_yxzExtractionPolynomialCoefficientsOne + 1)) * magnitude)
        - k_yxzExtractionPolynomialCoefficientsTwo) * magnitude) + *(&k_yxzExtractionPolynomialCoefficientsTwo + 1)) * magnitude)
        - k_yxzExtractionPolynomialCoefficientsThree) * magnitude) + *(&k_yxzExtractionPolynomialCoefficientsThree + 1);
    delta = k_yxzExtractionClampAndZero - magnitude;
    if (delta <= 0.0f) {
        root = 0.0f;
    } else {
        root = Gu_Sqrtf(delta);
    }
    angle_temp = k_yxzExtractionHalfPi - (root * polynomial);
    if (negative != 0) {
        angle_temp = -angle_temp;
    }
    angle = angle_temp;
    test = XMath_EvaluateSine(angle + k_yxzExtractionHalfPi);
    if ((*(&k_yxzExtractionHalfPi + 1) < test) || (test < *(&k_yxzExtractionHalfPi + 1))) {
        polynomial = XMath_EvaluateArcTangentTwo(inputMatrix->m20, inputMatrix->m22);
        out2 = XMath_EvaluateArcTangentTwo(inputMatrix->m01, inputMatrix->m11);
    } else {
        polynomial = 0.0f;
        out2 = XMath_EvaluateArcTangentTwo(inputMatrix->m02, inputMatrix->m00);
    }
    outputAngles->x = angle;
    outputAngles->y = polynomial;
    outputAngles->z = out2;
}
/* Computes an arcsine-style angle from a clamped matrix element by polynomial approximation, then derives the other two Euler angles with atan2-style calls and writes the triple. Adapted from XMath_ExtractYxzAngles, with the source element, the zero test, the branch operands, and the stored order changed. */


void XMath_ExtractZyxAngles(RotationMatrixWords *inputMatrix, CVector3 *outputAngles) {
    f32 clamped;
    f32 magnitude;
    f32 polynomial;
    f32 root;
    f32 delta;
    f32 test;
    f32 angle;
    f32 angle_temp;
    f32 out2;
    s32 negative;
    clamped = inputMatrix->m02;
    if (k_zyxExtractionClampAndZero < clamped) {
        clamped = k_zyxExtractionClampAndZero;
    }
    if (clamped < *(&k_zyxExtractionClampAndZero + 1)) {
        clamped = *(&k_zyxExtractionClampAndZero + 1);
    }
    magnitude = -clamped;
    if (k_zyxExtractionClampAndZero < magnitude) {
        magnitude = k_zyxExtractionClampAndZero;
    }
    if (magnitude < *(&k_zyxExtractionClampAndZero + 1)) {
        magnitude = *(&k_zyxExtractionClampAndZero + 1);
    }
    negative = 0;
    if (magnitude < 0.0f) {
        negative = 1;
        magnitude = -magnitude;
    }
    polynomial = (((((((((magnitude * k_zyxExtractionPolynomialCoefficientsOne) + *(&k_zyxExtractionPolynomialCoefficientsOne + 1)) * magnitude)
        - k_zyxExtractionPolynomialCoefficientsTwo) * magnitude) + *(&k_zyxExtractionPolynomialCoefficientsTwo + 1)) * magnitude)
        - k_zyxExtractionPolynomialCoefficientsThree) * magnitude) + *(&k_zyxExtractionPolynomialCoefficientsThree + 1);
    delta = k_zyxExtractionClampAndZero - magnitude;
    if (delta <= 0.0f) {
        root = 0.0f;
    } else {
        root = Gu_Sqrtf(delta);
    }
    angle_temp = k_zyxExtractionHalfPi - (root * polynomial);
    if (negative != 0) {
        angle_temp = -angle_temp;
    }
    angle = angle_temp;
    test = XMath_EvaluateSine(angle + k_zyxExtractionHalfPi);
    if ((0.0f < test) || (test < 0.0f)) {
        polynomial = XMath_EvaluateArcTangentTwo(inputMatrix->m12, inputMatrix->m22);
        out2 = XMath_EvaluateArcTangentTwo(inputMatrix->m01, inputMatrix->m00);
    } else {
        polynomial = XMath_EvaluateArcTangentTwo(-inputMatrix->m21, inputMatrix->m11);
        out2 = 0.0f;
    }
    outputAngles->x = polynomial;
    outputAngles->y = angle;
    outputAngles->z = out2;
}

void XMath_MultiplyMatrices(s32 matrix, s32 leftMatrix, s32 rightMatrix) {
    Matrix temporary;
    Matrix *out = (Matrix *)matrix;
    Matrix *a = (Matrix *)leftMatrix;
    Matrix *b = (Matrix *)rightMatrix;
    s32 row;

    if (out == a) {
        temporary = *a;
        if (a == b) {
            b = &temporary;
        }
        a = &temporary;
    } else if (out == b) {
        temporary = *b;
        b = &temporary;
    }

    {
        f32 *destination = out->m;
        f32 *left = a->m;
        f32 *right = b->m;
        row = 0;
        do {
            destination[0] = left[0] * right[0] +
                left[4] * right[1] +
                left[8] * right[2] +
                left[12] * right[3];
            destination[1] = left[1] * right[0] +
                left[5] * right[1] +
                left[9] * right[2] +
                left[13] * right[3];
            destination[2] = left[2] * right[0] +
                left[6] * right[1] +
                left[10] * right[2] +
                left[14] * right[3];
            destination[3] = left[3] * right[0] +
                left[7] * right[1] +
                left[11] * right[2] +
                left[15] * right[3];
            destination += 4;
            right += 4;
        } while (++row < 4);
    }
}

/* Re-orthonormalises the rotation rows of a matrix: normalises the first and second rows (a zero length is left to divide by zero), rebuilds the third row as their cross product and the second as the cross product of the third and first, and writes the three rows back. */






static inline f32 safe_sqrt_invert(f32 x) {
    if (x <= 0.0f) {
        return 0.0f;
    }
    return Gu_Sqrtf(x);
}

static inline void normalize_x(CVector3 *v) {
    f32 scale;

    scale = k_xmathFirstNormalizeUnit / safe_sqrt_invert(v->x * v->x + v->y * v->y + v->z * v->z);
    v->x *= scale;
    v->y *= scale;
    v->z *= scale;
}

static inline void normalize_y(CVector3 *v) {
    f32 scale;

    scale = k_xmathSecondNormalizeUnit / safe_sqrt_invert(v->x * v->x + v->y * v->y + v->z * v->z);
    v->x *= scale;
    v->y *= scale;
    v->z *= scale;
}

static inline CVector3 cross(CVector3 *a, CVector3 *b) {
    CVector3 r;

    r.x = a->y * b->z - a->z * b->y;
    r.y = a->z * b->x - a->x * b->z;
    r.z = a->x * b->y - a->y * b->x;
    return r;
}

void XMath_OrthogonalizeMatrixBasis(PlaneEquation *m) {
    CVector3 x;
    CVector3 y;
    CVector3 z;

    x.x = m[0].normal.x;
    x.y = m[0].normal.y;
    x.z = m[0].normal.z;
    y.x = m[1].normal.x;
    y.y = m[1].normal.y;
    y.z = m[1].normal.z;
    normalize_x(&x);
    normalize_y(&y);
    z = cross(&x, &y);
    y = cross(&z, &x);
    {
        CVector3 *p = &x;

        m[0].normal.x = p->x;
        m[0].normal.y = p->y;
        m[0].normal.z = p->z;
    }
    m[1].normal.x = y.x;
    m[1].normal.y = y.y;
    m[1].normal.z = y.z;
    m[2].normal.x = z.x;
    m[2].normal.y = z.y;
    m[2].normal.z = z.z;
}

s32 XMath_InvertAffineMatrix(f32 *out, f32 *input)
{
  struct CacheResourceBlockView copy[4];
  f32 *m;
  f32 determinant;
  f32 absoluteDeterminant;
  f32 reciprocal;
  f32 negativeReciprocal;
  f32 m5;
  f32 m10;
  f32 m6;
  f32 m9;
  f32 m4;
  f32 m8;
  f32 minor0;
  f32 affineOne;
  s32 result;
  m = input;
  if (input == out)
  {
    struct CacheResourceBlockView *dst = copy;
    struct CacheResourceBlockView *src = (struct CacheResourceBlockView *) out;
    struct CacheResourceBlockView *end = src + 4;
    do
    {
      *dst = *src;
      src++;
      dst++;
    }
    while (src != end);
    m = (f32 *) copy;
  }
  m5 = m[5];
  m10 = m[10];
  m6 = m[6];
  m9 = m[9];
  minor0 = (m5 * m10) - (m6 * m9);
  m4 = m[4];
  m8 = m[8];
  determinant = ((m[0] * minor0) - (m[1] * ((m4 * m10) - (m6 * m8)))) + (m[2] * ((m4 * m9) - (m5 * m8)));
  reciprocal = determinant;
  absoluteDeterminant = reciprocal;
  if (!(reciprocal >= 0.0f))
  {
    absoluteDeterminant = -determinant;
  }
  result = 1;
  if (!(absoluteDeterminant < k_xmathMatrixDeterminantTolerance))
  {
    affineOne = k_xmathAffineMatrixUnit;
    reciprocal = affineOne / determinant;
    out[0] = reciprocal * minor0;
    negativeReciprocal = -reciprocal;
    out[1] = negativeReciprocal * ((m[1] * m[10]) - (m[2] * m[9]));
    out[2] = reciprocal * ((m[1] * m[6]) - (m[2] * m[5]));
    out[3] = 0.0f;
    out[4] = negativeReciprocal * ((m[4] * m[10]) - (m[6] * m[8]));
    out[5] = reciprocal * ((m[0] * m[10]) - (m[2] * m[8]));
    out[6] = negativeReciprocal * ((m[0] * m[6]) - (m[2] * m[4]));
    out[7] = 0.0f;
    out[8] = reciprocal * ((m[4] * m[9]) - (m[5] * m[8]));
    out[9] = negativeReciprocal * ((m[0] * m[9]) - (m[1] * m[8]));
    out[10] = reciprocal * ((m[0] * m[5]) - (m[1] * m[4]));
    out[11] = 0.0f;
    out[12] = -(((m[12] * out[0]) + (m[13] * out[4])) + (m[14] * out[8]));
    out[13] = -(((m[12] * out[1]) + (m[13] * out[5])) + (m[14] * out[9]));
    out[14] = -(((m[12] * out[2]) + (m[13] * out[6])) + (m[14] * out[10]));
    result = 0;
    out[15] = affineOne;
  }
  return result;
}

/* Invert a 4x4 matrix with partial pivoting. Return one for a singular
 * matrix, leaving the destination untouched until elimination succeeds. */
s32 InvertMatrix(struct MatrixF *output, struct MatrixF *input)
{
    f32 augmented[4][8];
    s32 rowOrder[4];
    s32 i, j, elementIndex, pivotRow, otherRow;
    f32 value, entry, absoluteEntry;
    for (j = 0; j < 4; j++) {
        for (elementIndex = 0; elementIndex < 4; elementIndex++) {
            augmented[j][elementIndex] = input->m[j][elementIndex];
            augmented[j][elementIndex + 4] = 0.0f;
        }
        augmented[j][j + 4] = 1.0f;
        rowOrder[j] = j;
    }
    for (i = 0; i < 4; i++) {
        elementIndex = i;
        if (0.0f <= augmented[rowOrder[elementIndex]][elementIndex]) {
            value = augmented[rowOrder[elementIndex]][elementIndex];
        } else {
            value = -augmented[rowOrder[elementIndex]][elementIndex];
        }
        for (j = elementIndex + 1; j < 4; j++) {
            entry = augmented[rowOrder[j]][i];
            if (!(0.0f <= entry)) {
                absoluteEntry = -entry;
            } else {
                absoluteEntry = entry;
            }
            if (value < absoluteEntry) {
                elementIndex = j;
                if (!(0.0f <= entry)) {
                    value = -entry;
                } else {
                    value = entry;
                }
                absoluteEntry = value;
            }
        }
        pivotRow = rowOrder[elementIndex];
        rowOrder[elementIndex] = rowOrder[i];
        rowOrder[i] = pivotRow;
        value = augmented[pivotRow][i];
        if (value == 0.0f) return 1;
        augmented[pivotRow][i] = 1.0f;
        for (elementIndex = i + 1; elementIndex < 8; elementIndex++) augmented[pivotRow][elementIndex] /= value;
        for (j = i + 1; j < 4; j++) {
            otherRow = rowOrder[j];
            value = -augmented[otherRow][i];
            if (value != 0.0f) {
                augmented[otherRow][i] = 0.0f;
                for (elementIndex = i + 1; elementIndex < 8; elementIndex++) augmented[otherRow][elementIndex] += value * augmented[pivotRow][elementIndex];
            }
        }
    }
    for (i = 3; i > 0; i--) {
        pivotRow = rowOrder[i];
        for (j = i - 1; j >= 0; j--) {
            otherRow = rowOrder[j];
            value = augmented[otherRow][i];
            for (elementIndex = i; elementIndex < 8; elementIndex++) augmented[otherRow][elementIndex] -= value * augmented[pivotRow][elementIndex];
        }
    }
    for (j = 0; j < 4; j++) {
        otherRow = rowOrder[j];
        for (elementIndex = 0; elementIndex < 4; elementIndex++) output->m[j][elementIndex] = augmented[otherRow][elementIndex + 4];
    }
    return 0;
}
