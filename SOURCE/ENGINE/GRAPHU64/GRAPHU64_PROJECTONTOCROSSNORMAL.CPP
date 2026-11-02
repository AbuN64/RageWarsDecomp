#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/GRAPHICS_MATRIX_AND_VECTOR_MATH.H"
#include "ENGINE/GRAPHU64.H"

static inline void normalizeProjectionNormal(CVector3 *normal) {
    f32 length;
    f32 inverse;
    length = Gu_Sqrtf(normal->x * normal->x + normal->y * normal->y + normal->z * normal->z);
    if (length != 0.0f) {
        inverse = g_vectorVerticalAngleLowerConstants / length;
        normal->x *= inverse;
        normal->y *= inverse;
        normal->z *= inverse;
    }
}

static inline void projectionCross(CVector3 *normal, CVector3 *a, CVector3 *b) {
    normal->x = a->y * b->z - a->z * b->y;
    normal->y = a->z * b->x - a->x * b->z;
    normal->z = a->x * b->y - a->y * b->x;
}

static inline void projectionScale(CVector3 *out, CVector3 *normal, f32 projection) {
    out->x = normal->x * projection;
    out->y = normal->y * projection;
    out->z = normal->z * projection;
}

CVector3 *Graphu64_ProjectOntoCrossNormal(CVector3 *out, CVector3 *value, CVector3 *a, CVector3 *b) {
    CVector3 normal;
    CVector3 projected;
    f32 length;
    f32 projection;
    projectionCross(&normal, a, b);
    normalizeProjectionNormal(&normal);
    projection = value->x * normal.x + value->y * normal.y + value->z * normal.z;
    projectionScale(&projected, &normal, projection);
    *out = projected;
    return out;
}
