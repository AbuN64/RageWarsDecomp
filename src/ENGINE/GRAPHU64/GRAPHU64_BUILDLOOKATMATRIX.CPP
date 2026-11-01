#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/PACKED.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "ENGINE/GRAPHU64.H"
#include "COMMON/OBJB.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include <ultra64.h>
extern u32 g_secondaryRandomSeed;
extern f32 g_boundedIntegrationAndEaseConstants[2];







/* Builds a look-at view matrix (ultralib guLookAtF) from an eye, a target and an up vector,
   substituting a fallback x component when the up vector is parallel to the view direction.
   Adapted from ultralib gu/lookat.c with single-precision const extern constants, the degenerate check and the 1.0 held in a temporary. */




/* Returns the normalised cross product of a path node's two edge vectors, cached in g_cachedSurfaceNormal for the last node seen, with a default up vector for a null node. Adapted from Region_GetCachedCeilingNormal, which it inlines to compute the raw cross product, with the result normalised through Graphu64_NormalizeVector_de and cached by a second last-node word; the inlined copy records its last node before copying its result. */






extern void Graphu64_CrossVectors(CVector3 *, CVector3 *, CVector3 *);


static inline CVector3 *cross_edges(CVector3 *out, Node75 *node) {
    CVector3 a;
    CVector3 b;
    char *p;
    char *q;

    if (node == 0) {
        g_cachedCeilingCrossProduct.x = 0;
        g_cachedCeilingCrossProduct.z = 0;
        g_cachedCeilingCrossProduct.y = g_defaultCeilingNormalY;
    } else if ((int)node != g_cachedCeilingCrossProductNode) {
        p = node->cur;
        q = node->prev;
        a.x = ((CollisionBuildVertex *)p)->x - ((CollisionBuildVertex *)q)->x;
        p = node->cur;
        q = node->prev;
        a.y = ((CollisionBuildVertex *)p)->ceiling - ((CollisionBuildVertex *)q)->ceiling;
        p = node->cur;
        q = node->prev;
        a.z = ((CollisionBuildVertex *)p)->z - ((CollisionBuildVertex *)q)->z;
        p = node->next;
        q = node->cur;
        b.x = ((CollisionBuildVertex *)p)->x - ((CollisionBuildVertex *)q)->x;
        p = node->next;
        q = node->cur;
        b.y = ((CollisionBuildVertex *)p)->ceiling - ((CollisionBuildVertex *)q)->ceiling;
        p = node->next;
        q = node->cur;
        b.z = ((CollisionBuildVertex *)p)->z - ((CollisionBuildVertex *)q)->z;
        Graphu64_CrossVectors(&g_cachedCeilingCrossProduct, &b, &a);
    }
    g_cachedCeilingCrossProductNode = (int)node;
    *out = g_cachedCeilingCrossProduct;
    return out;
}

/** Perform the no-op callback at VRAM 0x8027451C. */
void Graphu64_ReturnWithoutWork(void) {
}

/** Store a fill pattern into two paired global words. */
void Graphu64_ResetRandomSeeds(void) {
    g_primaryRandomSeed = 0xE3F635E3;
    g_secondaryRandomSeed = 0xE3F635E3;
}

s32 Graphu64_NextRandom(void) {
    u32 seed;

    seed = (g_primaryRandomSeed * 0xA84A5B53) + 0x58348C2D;
    g_primaryRandomSeed = seed;
    return ((seed << 16) | (seed >> 16)) & 0x7FFFFFFF;
}

s32 Graphu64_NextRandomValue(void) {
    u32 seed;

    seed = (g_secondaryRandomSeed * 0xA84A5B53) + 0x58348C2D;
    g_secondaryRandomSeed = seed;
    return ((seed << 16) | (seed >> 16)) & 0x7FFFFFFF;
}

/** LCG PRNG step scaled into [0, range * g_randomFloatRangeScale) as a float. */
f32 Graphu64_RandomFloat(f32 range) {
    f64 value;
    s32 randomBits;
    u32 seed;

    seed = (g_primaryRandomSeed * 0xA84A5B53) + 0x58348C2D;
    randomBits = (s32)((seed >> 16) & 0x7FFF);
    value = (f64)randomBits;
    g_primaryRandomSeed = seed;
    if (randomBits < 0) {
        value = value + g_randomUnsignedFloatCorrection;
    }
    return (f32)value * range * g_randomFloatRangeScale;
}

f32 Graphu64_ArcCos(f32 cosineValue) {
    f32 tableCoordinate;
    f32 interpolatedAngle;
    f32 lowerSample;
    s32 sampleIndex;
    s32 negativeInput;

    negativeInput = 1;
    if (cosineValue < 0.0f) {
        tableCoordinate = cosineValue * g_arcCosNegativeInputScale;
    } else {
        tableCoordinate = cosineValue * g_arcCosPositiveInputScale;
        negativeInput = 0;
    }
    sampleIndex = (s32) tableCoordinate;
    if ((f32) sampleIndex < g_arcCosInterpolationLimit) {
        lowerSample = g_arcCosLowerSamples[sampleIndex];
        interpolatedAngle = lowerSample + ((tableCoordinate - (f32) sampleIndex) * (g_arcCosUpperSamples[sampleIndex] - lowerSample));
        if (negativeInput != 0) {
            return g_arcCosNegativeAngleBase - interpolatedAngle;
        }
        return interpolatedAngle;
    }
    if (negativeInput != 0) {
        tableCoordinate = g_arcCosEndpoint;
        return g_arcCosNegativeEndpointBase - tableCoordinate;
    }
    return g_arcCosEndpoint;
}

f32 Graphu64_IntegrateBoundedValue(f32 value, f32 velocity, f32 limit) {
    if (velocity < 0.0f) {
        if (value <= -limit) {
            return value;
        }
    }
    if (0.0f < velocity) {
        if (limit <= value) {
            return value;
        }
    }
    if ((value < 0.0f && 0.0f < velocity) ||
        (0.0f < value && velocity < 0.0f)) {
        velocity *= g_boundedIntegrationAndEaseConstants[0];
    }
    value += velocity * g_frameElapsedTime;
    if (velocity < 0.0f) {
        if (value < -limit) {
            value = -limit;
        }
    } else if (limit < value) {
        value = limit;
    }
    return value;
}

f32 Graphu64_DecayToZero(f32 value, f32 rate) {
    f32 zero;

    zero = 0.0f;
    if (zero < value) {
        value -= rate * g_frameElapsedTime;
        if (value < zero) {
            value = zero;
        }
    } else if (value < zero) {
        value += rate * g_frameElapsedTime;
        if (zero < value) {
            value = zero;
        }
    }
    return value;
}

f32 Graphu64_ApproachValue(f32 current, f32 target, f32 rate) {
    f32 value;
    value = current;
    if (value < target) {
        value += rate * g_frameElapsedTime;
        if (target < value) {
            value = target;
        }
    }
    else if (target < value) {
        value -= rate * g_frameElapsedTime;
        if (value < target) {
            value = target;
        }
    }
    return value;
}

void Graphu64_EaseValueToward(f32 *value, f32 target, f32 rate) {
    f32 current;
    f32 next;

    current = *value;
    next = (target - current) * rate * g_frameElapsedTime;
    if (rate == g_boundedIntegrationAndEaseConstants[1]) {
        *value = target;
    } else if (current < target) {
        *value += next;
        if (target < *value) {
            *value = target;
        }
    } else if (target < current) {
        *value += next;
        if (*value < target) {
            *value = target;
        }
    }
}

s32 Graphu64_IntegrateBoundedInteger(s32 value, s32 velocity, s32 limit)
{
  f32 velocityFloat;
  s32 nextValue;
  s32 directionalLimit;
  s32 exceedsLimit;
  directionalLimit = limit;
  velocityFloat = (f32) velocity;
  nextValue = value + ((s32) (velocityFloat * g_frameElapsedTime));
  if (velocityFloat < 0.0f)
  {
    directionalLimit = -directionalLimit;
    exceedsLimit = nextValue < directionalLimit;
  }
  else
  {
    exceedsLimit = directionalLimit < nextValue;
  }
  if (exceedsLimit != 0)
  {
    directionalLimit = directionalLimit;
    nextValue = directionalLimit;
  }
  if (directionalLimit)
  {
    return nextValue;
  }
  else
  {
    return nextValue;
  }
}

f32 Graphu64_NegateWrappedValue(f32 value)
{
  unsigned char lowerBoundIndex;
  f32 val;
  val = value;
  lowerBoundIndex = 0;
  if (val < g_wrappedValueLowerConstants[lowerBoundIndex])
  {
    do
    {
      val += g_wrappedValueLowerConstants[1];
    }
    while (val < g_wrappedValueLowerConstants[lowerBoundIndex]);
  }
  if (g_wrappedValueUpperConstants[lowerBoundIndex] < val)
  {
    do
    {
      val -= g_wrappedValueUpperConstants[1];
    }
    while (g_wrappedValueUpperConstants[lowerBoundIndex] < val);
  }
  return -val;
}

f32 Graphu64_GetNegatedWrappedDifference(f32 angleA, f32 angleB) {
    f32 difference;
    f32 wrappedB;

    wrappedB = angleB;
    if (wrappedB < g_wrappedAngleLowerConstants) {
        do {
            wrappedB += *(&g_wrappedAngleLowerConstants + 1);
        } while (wrappedB < g_wrappedAngleLowerConstants);
    }
    if (g_wrappedAngleUpperConstants < wrappedB) {
        do {
            wrappedB -= *(&g_wrappedAngleUpperConstants + 1);
        } while (g_wrappedAngleUpperConstants < wrappedB);
    }
    difference = angleA - wrappedB;
    if (difference < g_wrappedDifferenceLowerConstants) {
        do {
            difference += *(&g_wrappedDifferenceLowerConstants + 1);
        } while (difference < g_wrappedDifferenceLowerConstants);
    }
    if (g_wrappedDifferenceUpperConstants < difference) {
        do {
            difference -= *(&g_wrappedDifferenceUpperConstants + 1);
        } while (g_wrappedDifferenceUpperConstants < difference);
    }
    return -difference;
}

f32 Graphu64_RandomBetween(f32 shakeMin, f32 shakeMax) {
    f32 blend;
    u32 seed;
    s32 randomValue;

    seed = (g_primaryRandomSeed * 0xA84A5B53) + 0x58348C2D;
    randomValue = ((seed << 16) | (seed >> 16)) & 0x7FFFFFFF;
    randomValue = randomValue % 10000;
    blend = (f32)randomValue * g_randomBlendScale;
    g_primaryRandomSeed = seed;
    return (blend * shakeMin) + ((g_randomBlendUnitScale - blend) * shakeMax);
}

s32 Graphu64_UpdateCountdown(f32 *countdown)
{
  f32 *expiredCountdown;
  float zeroCountdown;
  f32 *countdownPointer;
  f32 remaining;
  remaining = (*countdown) - g_frameElapsedTime;
  *countdown = remaining;
  countdownPointer = countdown;
  expiredCountdown = countdownPointer;
  zeroCountdown = 0.0f;
  if ((remaining <= 0.0f) == 0)
  {
    if (g_frameElapsedTime)
    {
      remaining = 0;
      return remaining;
    }
    else
    {
      remaining = 0;
      return remaining;
    }
  }
  *expiredCountdown = zeroCountdown;
  return 1;
}

/** Copy two 3-vectors, then derive an edge vector, its z-component twice, and a negated x. */
void Graphu64_InitializeEdge(void *geometryEdge, void *startPoint, void *endPoint) {
    GeometryEdge *dst = geometryEdge;
    CVector3 *a = startPoint;
    CVector3 *b = endPoint;
    f32 zdiff;

    dst->start = *a;
    dst->end = *b;
    dst->direction.x = b->x - a->x;
    dst->direction.y = b->y - a->y;
    zdiff = b->z - a->z;
    dst->normal.y = 0.0f;
    dst->normal.z = -dst->direction.x;
    dst->direction.z = zdiff;
    dst->normal.x = zdiff;
}

void Graphu64_NormalizeEdgeHorizontal(void *geometryEdge)
{
    GeometryEdgeDirectionView *o = geometryEdge;
    f32 magSq;
    f32 mag;
    f32 zOut;

    magSq = (o->directionX * o->directionX) +
            (o->directionZ * o->directionZ);
    zOut = 0.0f;
    if (magSq != 0.0f) {
        mag = Gu_Sqrtf(magSq);
        magSq = *(f32 *)&g_horizontalEdgeNormalizeScale / mag;
        o->unitDirectionX = o->directionX * magSq;
        o->unitDirectionY = o->directionY * magSq;
        zOut = o->directionZ * magSq;
    } else {
        o->unitDirectionX = 0.0f;
        o->unitDirectionY = 0.0f;
    }
    o->unitDirectionZ = zOut;
}

void Graphu64_NormalizeEdgeDirection(void *geometryEdge)
{
    GeometryEdgeDirectionView *o = geometryEdge;
    f32 magSq;
    f32 mag;
    f32 zOut;

    magSq = (o->directionX * o->directionX) +
            (o->directionY * o->directionY) +
            (o->directionZ * o->directionZ);
    zOut = 0.0f;
    if (magSq != 0.0f) {
        mag = Gu_Sqrtf(magSq);
        magSq = g_edgeDirectionNormalizeScale / mag;
        o->unitDirectionX = o->directionX * magSq;
        o->unitDirectionY = o->directionY * magSq;
        zOut = o->directionZ * magSq;
    } else {
        o->unitDirectionX = 0.0f;
        o->unitDirectionY = 0.0f;
    }
    o->unitDirectionZ = zOut;
}

s32 Graphu64_GetHorizontalIntersectionParameter(f32 *edgePlane, f32 *intersectingEdge, f32 *parameterOutput) {
    CVector3 delta;
    f32 directionDotNormal;
    s32 result;

    delta.x = intersectingEdge[0] - edgePlane[0];
    delta.z = intersectingEdge[2] - edgePlane[2];
    directionDotNormal = (intersectingEdge[6] * edgePlane[12]) + (intersectingEdge[8] * edgePlane[14]);
    result = 0;
    if (directionDotNormal != 0.0f) {
        result = 1;
        *parameterOutput = ((delta.x * edgePlane[12]) + (delta.z * edgePlane[14])) / -directionDotNormal;
    }
    return result;
}

/** Half-plane test: is pointPosition on the positive side of geometryEdge's normal (at +0x30)? */
s32 Graphu64_IsPointOnPositiveEdgeSide(void *geometryEdge, void *pointPosition) {
    GeometryEdge *edge = geometryEdge;
    CVector3 *point = pointPosition;
    CVector3 normal;
    CVector3 delta;
    s32 result;

    normal = edge->normal;
    delta.x = point->x - edge->start.x;
    delta.z = point->z - edge->start.z;
    result = 0;
    if (!(((normal.x * delta.x) + (normal.z * delta.z)) <= 0.0f)) {
        result = 1;
    }
    return result;
}

void Graphu64_BuildLookAtMatrix(float mf[4][4], float xEye, float yEye, float zEye,
                   float xAt, float yAt, float zAt,
                   float xUp, float yUp, float zUp)
{
    float one, len, xLook, yLook, zLook, xRight, yRight, zRight;

    guMtxIdentF(mf);

    xLook = xAt - xEye;
    yLook = yAt - yEye;
    zLook = zAt - zEye;

    len = g_lookAtNormalizeAndFallbackConstants / Gu_Sqrtf(xLook * xLook + yLook * yLook + zLook * zLook);
    xLook *= len;
    yLook *= len;
    zLook *= len;

    xRight = yUp * zLook - zUp * yLook;
    yRight = zUp * xLook - xUp * zLook;
    zRight = xUp * yLook - yUp * xLook;
    if (xRight == 0.0f && yRight == 0.0f && zRight == 0.0f) {
        xRight = (&g_lookAtNormalizeAndFallbackConstants)[1];
    }
    one = g_lookAtHomogeneousScale;
    len = one / Gu_Sqrtf(xRight * xRight + yRight * yRight + zRight * zRight);
    xRight *= len;
    yRight *= len;
    zRight *= len;

    xUp = yLook * zRight - zLook * yRight;
    yUp = zLook * xRight - xLook * zRight;
    zUp = xLook * yRight - yLook * xRight;
    len = one / Gu_Sqrtf(xUp * xUp + yUp * yUp + zUp * zUp);
    xUp *= len;
    yUp *= len;
    zUp *= len;

    mf[0][0] = xRight;
    mf[1][0] = yRight;
    mf[2][0] = zRight;
    mf[3][0] = -(xEye * xRight + yEye * yRight + zEye * zRight);

    mf[0][1] = xUp;
    mf[1][1] = yUp;
    mf[2][1] = zUp;
    mf[3][1] = -(xEye * xUp + yEye * yUp + zEye * zUp);

    mf[0][2] = xLook;
    mf[1][2] = yLook;
    mf[2][2] = zLook;
    mf[3][2] = -(xEye * xLook + yEye * yLook + zEye * zLook);

    mf[0][3] = 0;
    mf[1][3] = 0;
    mf[2][3] = 0;
    mf[3][3] = one;
}

CVector3 *Graphu64_GetCachedSurfaceNormal(CVector3 *out, Node75 *node) {
    if (node == 0) {
        ((CVector3 *)&g_cachedSurfaceNormal)->x = 0;
        ((CVector3 *)&g_cachedSurfaceNormal)->z = 0;
        ((CVector3 *)&g_cachedSurfaceNormal)->y = g_cachedSurfaceDefaultNormalY;
    } else if ((int)node != g_cachedSurfaceNormalNode) {
        cross_edges((CVector3 *)&g_cachedSurfaceNormal, node);
        Graphu64_NormalizeVec3((CVector3 *)&g_cachedSurfaceNormal);
    }
    *out = *(CVector3 *)&g_cachedSurfaceNormal;
    g_cachedSurfaceNormalNode = (int)node;
    return out;
}

f32 Graphu64_GetTrianglePlaneHeight(Node75 *node, f32 x, f32 z) {
    CVector3 normal;
    CVector3 point;
    CVector3 a;
    CVector3 b;
    char *p;
    char *q;

    if (node == 0) {
        return 0.0f;
    }
    if ((int)node != g_cachedCeilingCrossProductNode) {
        p = node->cur;
        q = node->prev;
        a.x = ((CollisionBuildVertex *)p)->x - ((CollisionBuildVertex *)q)->x;
        p = node->cur;
        q = node->prev;
        a.y = ((CollisionBuildVertex *)p)->ceiling - ((CollisionBuildVertex *)q)->ceiling;
        p = node->cur;
        q = node->prev;
        a.z = ((CollisionBuildVertex *)p)->z - ((CollisionBuildVertex *)q)->z;
        p = node->next;
        q = node->cur;
        b.x = ((CollisionBuildVertex *)p)->x - ((CollisionBuildVertex *)q)->x;
        p = node->next;
        q = node->cur;
        b.y = ((CollisionBuildVertex *)p)->ceiling - ((CollisionBuildVertex *)q)->ceiling;
        p = node->next;
        q = node->cur;
        b.z = ((CollisionBuildVertex *)p)->z - ((CollisionBuildVertex *)q)->z;
        Graphu64_CrossVectors(&g_cachedCeilingCrossProduct, &b, &a);
    }
    normal = g_cachedCeilingCrossProduct;
    g_cachedCeilingCrossProductNode = (int)node;
    if (normal.y == 0.0f) {
        return (((CollisionBuildVertex *)node->prev)->ceiling +
                ((CollisionBuildVertex *)node->cur)->ceiling +
                ((CollisionBuildVertex *)node->next)->ceiling) * g_cachedSurfaceCeilingAverageScale;
    }
    p = node->prev;
    point.x = ((CollisionBuildVertex *)p)->x;
    p = node->prev;
    point.y = ((CollisionBuildVertex *)p)->ceiling;
    p = node->prev;
    point.z = ((CollisionBuildVertex *)p)->z;
    return (((point.z - z) * normal.z) +
            ((point.x - x) * normal.x) + (point.y * normal.y)) /
           normal.y;
}
