#ifndef COMMON_PACKED_H
#define COMMON_PACKED_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
struct Packed;
struct Packed {
    unsigned short kind;
    unsigned short flags;
    unsigned short first[3];
    unsigned short second[3];
    int mask;
};

struct Packed;
typedef struct Packed Packed;
/* Cached path-node plane normals (Graphu64_CrossVectors edge cross products). */
extern CVector3 g_regionCachedEdgeCross;
extern CVector3 g_regionCachedUnitNormal;

struct CGameRegion_t;
struct CGameRegion_t {
    short kind;
    short flags;
    void *first[3];
    void *second[3];
    int mask;
};

struct CGameRegion_t;
typedef struct CGameRegion_t CGameRegion;
/* Cached path-node plane normal (Graphu64_CrossVectors edge cross product). */
extern CVector3 g_cachedCeilingCrossProduct;

extern void Region_DecodePackedRegion(CGameRegion *dst, Packed *src, char *base, int unused, char *extra);

extern float g_wrappedAngleUpperConstants;

extern void Graphu64_ResetRandomSeeds(void);

extern float g_regionWallSlopeThreshold;

extern void Graphu64_ReturnWithoutWork(void);




extern void Region_ScaleWordsToFloats(void *wordStorage);

extern float g_wrappedAngleLowerConstants;

extern s32 Graphu64_NextRandomValue(void);

extern float g_cachedSurfaceDefaultNormalY;

struct GeometryEdgeDirectionView;
struct GeometryEdgeDirectionView {
    char pad0[0x18];
    f32 directionX;
    char pad18[0x1C - 0x18 - sizeof(f32)];
    f32 directionY;
    char pad1C[0x20 - 0x1C - sizeof(f32)];
    f32 directionZ;
    char pad20[0x24 - 0x20 - sizeof(f32)];
    f32 unitDirectionX;
    char pad24[0x28 - 0x24 - sizeof(f32)];
    f32 unitDirectionY;
    char pad28[0x2C - 0x28 - sizeof(f32)];
    f32 unitDirectionZ;
};

extern float g_randomFloatRangeScale;

extern float g_regionWordToFloatScaleDe;

extern void Graphu64_BuildLookAtMatrix(float mf[4][4], float xEye, float yEye, float zEye, float xAt, float yAt, float zAt, float xUp, float yUp, float zUp);

extern float g_defaultCeilingNormalY;

extern f32 Graphu64_GetNegatedWrappedDifference(f32 angleA, f32 angleB);

struct Triangle;
struct Triangle {
    char pad0[2];
    u16 flags;
    CVector3 *vertices[3];
};

extern s32 Graphu64_IsPointOnPositiveEdgeSide(void *geometryEdge, void *point);


struct Triangle;
typedef struct Triangle Triangle;

extern void Graphu64_NormalizeEdgeDirection(void *geometryEdge);


struct GeometryEdgeDirectionView;
typedef struct GeometryEdgeDirectionView GeometryEdgeDirectionView;

extern void Graphu64_NormalizeEdgeHorizontal(void *geometryEdge);

extern float g_cachedSurfaceCeilingAverageScale;

extern float g_randomBlendScale;


extern double g_randomUnsignedFloatCorrection;

extern void Graphu64_InitializeEdge(void *geometryEdge, void *startPoint, void *endPoint);

extern s32 Graphu64_IntegrateBoundedInteger(s32 value, s32 step, s32 limit);

extern float g_randomBlendUnitScale;

extern float g_wrappedDifferenceUpperConstants;

extern float g_regionUpQuaternionHalfAngleScale;

extern f32 Graphu64_NegateWrappedValue(f32 value);

extern float g_wrappedDifferenceLowerConstants;

extern s32 Graphu64_GetHorizontalIntersectionParameter(f32 *point, f32 *edgeStart, f32 *edgeEnd);

/* Edge endpoints and the direction/normal derived by the edge helpers. */
typedef struct GeometryEdge {
    CVector3 start;
    CVector3 end;
    CVector3 direction;
    CVector3 unitDirection;
    CVector3 normal;
} GeometryEdge;
#endif
