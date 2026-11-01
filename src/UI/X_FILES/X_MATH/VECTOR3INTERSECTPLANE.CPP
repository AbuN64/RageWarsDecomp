#include "COMMON/OBJRECAT3CV2.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "MATH/DOUBLEBITS.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/TRIPLE.H"
#include "MATH/math_double.H"
#include "UI/X_FILES/X_MATH.H"

/* Normalizes an offset angle, using double remainder for large magnitudes and repeated single-precision adjustments otherwise. */







inline static f32 wrap(f32 angle)
{
  f32 angleReductionValue;
  f32 value;
  f32 *angleWrapConstants;
  f32 originalAngle;
  value = angle;
  originalAngle = value;
  if (1)
  {
    if (((long long) (k_xmathVectorAngleUpperThreshold < originalAngle)) || (originalAngle < k_xmathVectorAngleLowerThreshold))
    {
      value = (f32) FloatModulo((f64) value, k_xmathVectorAnglePeriodDouble);
    }
    else
    {
      if (k_xmathVectorAngleWrapConstants[0] < value)
      {
        angleReductionValue = k_xmathVectorAngleWrapConstants[0];
        do
        {
          value -= angleReductionValue;
          if (1)
          {
          }
        }
        while (angleReductionValue < value);
      }
      if (value < 0.0f)
      {
        do
        {
          angleWrapConstants = k_xmathVectorAngleWrapConstants;
          value += angleWrapConstants[1];
        }
        while (value < (angleReductionValue = 0.0f));
      }
    }
  }
  return value;
}


static inline f32 centered(f32 x)
{
  f32 centerOffset;
  float shiftedAngle;
  f32 wrappedAngle;
  centerOffset = k_xmathVectorAngleCenterOffset;
  wrappedAngle = x + centerOffset;
  {
    shiftedAngle = wrappedAngle;
  }
  wrappedAngle = wrap(shiftedAngle);
  return wrappedAngle - k_xmathVectorAngleCenterResultOffset;
}



static inline f32 safe_sqrt(f32 x) {
    if (x <= 0.0f) {
        return 0.0f;
    }
    return Gu_Sqrtf(x);
}

f32 XMath_SubtractAnglesCentered(f32 a, f32 b) { return centered(a - b); }

/** Clear a three-component floating-point vector. */
void Vector3Zero(float *vector) {
    vector[0] = vector[1] = vector[2] = 0.0f;
}

void Vector3Set(void *destination, float xValue, float yValue, float zValue) {
    CVector3 *vector = destination;
    vector->x = xValue;
    vector->y = yValue;
    vector->z = zValue;
}

/** Split a three-float vector into three destinations. */
void Vector3Unpack(float *source, float *xOut, float *yOut, float *zOut) {
    *xOut = source[0];
    *yOut = source[1];
    *zOut = source[2];
}

void Vector3Copy(Triple *destination, Triple *source) {
    *destination = *source;
}

void Vector3Add(void *destination, void *leftVector, void *rightVector) {
    (((struct CVector3_t *) ((s8 *) destination))->x) = (f32) ((((struct CVector3_t *) ((s8 *) leftVector))->x) + (((struct CVector3_t *) ((s8 *) rightVector))->x));
    (((struct CVector3_t *) ((s8 *) destination))->y) = (f32) ((((struct CVector3_t *) ((s8 *) leftVector))->y) + (((struct CVector3_t *) ((s8 *) rightVector))->y));
    (((struct CVector3_t *) ((s8 *) destination))->z) = (f32) ((((struct CVector3_t *) ((s8 *) leftVector))->z) + (((struct CVector3_t *) ((s8 *) rightVector))->z));
}

void Vector3Subtract(void *destination, void *leftVector, void *rightVector) {
    (((struct CVector3_t *) ((s8 *) destination))->x) = (f32) ((((struct CVector3_t *) ((s8 *) leftVector))->x) - (((struct CVector3_t *) ((s8 *) rightVector))->x));
    (((struct CVector3_t *) ((s8 *) destination))->y) = (f32) ((((struct CVector3_t *) ((s8 *) leftVector))->y) - (((struct CVector3_t *) ((s8 *) rightVector))->y));
    (((struct CVector3_t *) ((s8 *) destination))->z) = (f32) ((((struct CVector3_t *) ((s8 *) leftVector))->z) - (((struct CVector3_t *) ((s8 *) rightVector))->z));
}

/** Scale a 3-vector (source) by a scalar (scaleFactor), store into destination. */
void Vector3Scale(void *destination, void *source, f32 scaleFactor) {
    CVector3 *sourceVector = source;
    CVector3 *destinationVector = destination;
    destinationVector->x = sourceVector->x * scaleFactor;
    destinationVector->y = sourceVector->y * scaleFactor;
    destinationVector->z = sourceVector->z * scaleFactor;
}

void Vector3Negate(void *destination, void *source) {
    (((struct CVector3_t *) ((s8 *) destination))->x) = (f32) -(((struct CVector3_t *) ((s8 *) source))->x);
    (((struct CVector3_t *) ((s8 *) destination))->y) = (f32) -(((struct CVector3_t *) ((s8 *) source))->y);
    (((struct CVector3_t *) ((s8 *) destination))->z) = (f32) -(((struct CVector3_t *) ((s8 *) source))->z);
}

void Vector3Distance(f32 *a, f32 *b) {
    f32 dx = a[0] - b[0];
    f32 dy = a[1] - b[1];
    f32 dz = a[2] - b[2];
    f32 sum;

    sum = ((dx * dx) + (dy * dy)) + (dz * dz);
    if (!(((dx * dx) + (dy * dy)) + (dz * dz) <= 0.0f)) {
        sum = dz;
        Gu_Sqrtf(((dx * dx) + (dy * dy)) + (sum * sum));
    }
}

f32 Vector3Dot(f32 *a, f32 *b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

/** Cross product of two vectors, written through a local temp to allow aliasing with out. */
void Vector3Cross(CVector3 *out, CVector3 *a, CVector3 *b) {
    CVector3 tmp;

    tmp.x = (a->y * b->z) - (a->z * b->y);
    tmp.y = (a->z * b->x) - (a->x * b->z);
    tmp.z = (a->x * b->y) - (a->y * b->x);
    *out = tmp;
}

void XMath_EvaluateVectorLength(CVector3 *vector)
{
  f32 sum;
  sum = ((vector->x * vector->x) + (vector->y * vector->y)) + (vector->z * vector->z);
  if (!((((vector->x * vector->x) + (vector->y * vector->y)) + (vector->z * vector->z)) <= 0.0f))
  {
    sum = vector->z;
    Gu_Sqrtf(((vector->x * vector->x) + (vector->y * vector->y)) + (sum * sum));
  }
}

void Vector3Normalize(f32 *vector) {
    f32 mag;
    f32 scale;

    mag = safe_sqrt((vector[0] * vector[0]) + (vector[1] * vector[1]) + (vector[2] * vector[2]));
    scale = k_xmathVectorNormalizeUnit / mag;
    vector[0] = vector[0] * scale;
    vector[1] = vector[1] * scale;
    vector[2] = vector[2] * scale;
}

void Vector3RotatePitch(CVector3 *destination, CVector3 *source, f32 angle) {
    CVector3 tmp;
    f32 sinOut;
    f32 cosOut;

    XMath_EvaluateSineCosine(angle, &sinOut, &cosOut);
    tmp.x = source->x;
    tmp.y = (cosOut * source->y) - (sinOut * source->z);
    tmp.z = (cosOut * source->z) + (sinOut * source->y);
    *destination = tmp;
}

void Vector3RotateYaw(CVector3 *destination, CVector3 *source, f32 angle) {
    CVector3 tmp;
    f32 sineAngle;
    f32 cosineAngle;

    XMath_EvaluateSineCosine(angle, &sineAngle, &cosineAngle);
    tmp.x = (cosineAngle * source->x) + (sineAngle * source->z);
    tmp.y = source->y;
    tmp.z = (cosineAngle * source->z) - (sineAngle * source->x);
    *destination = tmp;
}

void Vector3RotateRoll(CVector3 *destination, CVector3 *source, f32 angle) {
    CVector3 tmp;
    f32 sineAngle;
    f32 cosineAngle;

    XMath_EvaluateSineCosine(angle, &sineAngle, &cosineAngle);
    tmp.x = (cosineAngle * source->x) - (sineAngle * source->y);
    tmp.y = (cosineAngle * source->y) + (sineAngle * source->x);
    tmp.z = source->z;
    *destination = tmp;
}

void Vector3Angles(f32 *vector, f32 *pitchOut, f32 *yawOut) {
    f32 magnitude_squared;
    f32 magnitude;
    f32 x;
    f32 z;

    x = vector[0];
    z = vector[2];
    x *= x;
    z *= z;
    x += z;
    magnitude_squared = x;
    if (magnitude_squared <= 0.0f) {
        magnitude = 0.0f;
    } else {
        magnitude = Gu_Sqrtf(magnitude_squared);
    }
    *yawOut = XMath_EvaluateArcTangentTwo(vector[0], vector[2]);
    *pitchOut = -XMath_EvaluateArcTangentTwo(vector[1], magnitude);
}

void Vector3AnglesInverse(f32 *vector, f32 *pitchOut, f32 *yawOut) {
    f32 magnitude_squared;
    f32 magnitude;
    f32 x;
    f32 z;

    x = vector[0];
    z = vector[2];
    x *= x;
    z *= z;
    x += z;
    magnitude_squared = x;
    if (magnitude_squared <= 0.0f) {
        magnitude = 0.0f;
    } else {
        magnitude = Gu_Sqrtf(magnitude_squared);
    }
    *yawOut = XMath_EvaluateArcTangentTwo(vector[0], vector[2]);
    *pitchOut = XMath_EvaluateArcTangentTwo(vector[1], magnitude);
    *yawOut = -*yawOut;
}

/* Projects n vectors onto the screen plane: each one with depth above 0.01 becomes (ox + sx * x / z, oy + sy * y / z, z), and any other becomes zero. */



void Vector3ProjectArray(CVector3 *out, CVector3 *in, s32 n, f32 ox, f32 sx, f32 oy, f32 sy) {
    s32 i;

    for (i = 0; i < n; i++) {
        if (in[i].z > 0.01f) {
            out[i].x = ox + sx * (in[i].x / in[i].z);
            out[i].y = oy + sy * (in[i].y / in[i].z);
            out[i].z = in[i].z;
        } else {
            out[i].x = 0.0f;
            out[i].y = 0.0f;
            out[i].z = 0.0f;
        }
    }
}

void Vector3IntersectPlane(CVector3 *intersectionOut, CVector3 *lineStart, CVector3 *lineEnd, f32 normalX, f32 normalY, f32 normalZ, f32 planeOffset) {
    CVector3 delta;
    f32 numerator;
    f32 denominator;
    f32 fraction;

    delta.x = lineEnd->x - lineStart->x;
    delta.y = lineEnd->y - lineStart->y;
    delta.z = lineEnd->z - lineStart->z;
    numerator = -((normalX * lineStart->x) + (normalY * lineStart->y) + (normalZ * lineStart->z) + planeOffset);
    denominator = (normalX * delta.x) + (normalY * delta.y) + (normalZ * delta.z);
    if (!(denominator < k_xmathPlaneDenominatorUpperTolerance) || (fraction = k_xmathPlaneParallelFraction, !(k_xmathPlaneDenominatorLowerTolerance < denominator))) {
        fraction = numerator / denominator;
    }
    intersectionOut->x = lineStart->x + (fraction * delta.x);
    intersectionOut->y = lineStart->y + (fraction * delta.y);
    intersectionOut->z = lineStart->z + (fraction * delta.z);
}

void XMath_CopyMatrix(void *destination, void *source) {
    char *dst = (char *)destination;
    char *src = (char *)source;
    char *end = src + sizeof(Matrix);
    do {
        *(struct CacheResourceBlockView *)dst = *(struct CacheResourceBlockView *)src;
        src += sizeof(CQuatern);
        dst += sizeof(CQuatern);
    } while (src != end);
}
