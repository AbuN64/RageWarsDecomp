#ifndef COMMON_OUTPUT_H
#define COMMON_OUTPUT_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
struct CCollisionResults;
typedef struct CCollisionResults CCollisionResults;

struct World;

struct Ray;
typedef struct Ray Ray;

struct PolygonCCollisionTestRayCylinder;
struct PolygonCCollisionTestRayCylinder {
    s32 type;
    s32 pad4;
    s32 kind;
    char padC[0x8];
    s32 flag;
    CVector3 point;
    char pad24[0x24];
    CVector3 normal;
    char pad54[0x78];
    f32 t;
    CVector3 hit;
};

struct Polygon;
typedef struct Polygon Polygon;

struct Ray;
struct Ray {
    char pad0[0x44];
    CVector3 start;
    CVector3 end;
    CVector3 dir;
    char pad68[0x114];
    f32 nearest;
};

extern float g_collisionSegmentPolygonSlackFactor;




struct Polygon;
struct Polygon {
    s32 type;
    f32 response; /* 0x04 */
    s32 kind;
    s32 category; /* 0x0C */
    u32 flags; /* 0x10 */
    s32 vertexCount; /* 0x14 */
    CVector3 vertices[4]; /* 0x18 */
    CVector3 normal; /* 0x48 */
    void *input; /* 0x54 */
    s32 index; /* 0x58 */
    char pad5C[0x70];
    f32 t; /* 0xCC */
    CVector3 hit;
};


struct ActorMotion;
struct MotionContactResult;


struct CollisionContactVectorView;
struct CollisionContactVectorView {
    char pad0[0x18C];
    Triple contactVector;
};


struct CollisionContactVectorView;
typedef struct CollisionContactVectorView CollisionContactVectorView;

struct PolygonCCollisionTestRayCylinder;
typedef struct PolygonCCollisionTestRayCylinder PolygonCCollisionTestRayCylinder;

struct RayCCollisionTestRayCylinder;
struct RayCCollisionTestRayCylinder {
    char pad0[0x44];
    CVector3 start;
    CVector3 end;
    CVector3 dir;
    char pad68[0x18];
    f32 slack;
    char pad84[0x2C];
    PolygonCCollisionTestRayCylinder nearest;
};


struct Polygon;
typedef struct Polygon PolygonCCollisionTestSegmentPolygon;

struct CapsuleSweep;
struct CCollisionInfo2_t;
struct CapsuleSweep {
    char pad0[0x08];
    f32 radius; /* 0x08 */
    f32 secondaryRadius; /* 0x0C */
    char pad10[0x0C];
    f32 height; /* 0x1C */
    char pad20[0x1C];
    u32 flags; /* 0x3C */
    struct CCollisionInfo2_t *surface; /* 0x40 */
    CVector3 start;
    CVector3 end;
    char pad5C[0x24];
    f32 slack;
    char pad84[0x2C];
    PolygonCCollisionTestSegmentPolygon nearest;
};

struct Instance;
struct Instance {
    u8 pad0[0x14];
    s32 value;
};
struct Input;
struct Instance;
struct Input {
    u8 pad0[0xB0];
    s32 type;
    u8 padB4[8];
    s32 contactAuxValue;
    s32 contactValue;
    u8 padC4[0x34];
    Triple vecF8;
    struct Instance *instance104;
    s32 blockValue;
    Block70 block10C;
    s32 reservedWord;
    Triple vec180;
    CVector3 contactNormal; /* 0x18C */
};

struct CapsuleSweep;
typedef struct CapsuleSweep CapsuleSweep;


struct World;

extern float g_collisionSlackThreshold;

extern float g_collisionContactSlackFactor;


struct Polygon;


struct CapsuleSweep;


struct Range;
struct Range {
    char pad[8];
    f32 low;
    s32 count;
    f32 high;
    f32 extra;
    f32 limit;
};






struct Instance;
struct CCollisionResults;
struct CCollisionResults {
    struct Instance *instance0;
    s32 instanceValue4;
    Triple vec8;
    s32 value;
    Block70 block18;
    struct Instance *instance88;
    s32 instanceValue8C;
    Triple vec90;
    u8 pad9C[0x28];
    s32 instanceValueC4;
    Triple vecC8;
    s32 contactAuxValue;
    u8 padD8[0xC];
    Triple vecE4;
    Triple vecF0;
    s32 typeFC;
    s32 contactValue;
};

struct RayCCollisionTestRayCylinder;
typedef struct RayCCollisionTestRayCylinder RayCCollisionTestRayCylinder;


struct CollisionPolygonNormalView;
typedef struct CollisionPolygonNormalView CollisionPolygonNormalView;

struct Reusable;
typedef struct Reusable Reusable;

struct CollisionPolygonNormalView;
struct CollisionPolygonNormalView {
    char pad0[0x48];
    Triple normal;
};

struct CollisionSegmentSurface;
typedef struct CollisionSegmentSurface CollisionSegmentSurface;


struct CollisionSegmentSurface;
struct CollisionSegmentSurface {
    char pad0[0x40];
    Field_f32_10 *limits;
    f32 x0;
    char pad48[4];
    f32 y0;
    f32 x1;
    f32 height;
    f32 y1;
    char pad5C[0x74 - 0x5C];
    char node[1];
};

struct Input;
typedef struct Input Input;

extern float g_collisionCylinderRangeMargin;



struct Reusable;


struct CapsuleSweep;

extern f32 g_collisionBounceOrientationDampingBase;
extern f32 g_collisionBounceRemainingFractionBase;
extern f32 g_collisionSlideOrientationDampingBase;
extern f32 g_collisionSlideRemainingFractionBase;
extern f32 g_collisionPreservedSlideFractionBase;
extern f32 g_collisionBlendedSlideDampingBase;
extern f32 g_collisionBlendedSlideFractionBase;
extern f32 g_collisionSurfaceGravityScale;
extern CVector3 Graphu64_ProjectVectorPreservingLength(CVector3 *,CVector3 *);
#endif
