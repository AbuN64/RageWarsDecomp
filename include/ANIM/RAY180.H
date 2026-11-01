#ifndef ANIM_RAY180_H
#define ANIM_RAY180_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/OUTPUT.H"
#include "COMMON/FIELD_VEC_B0.H"
struct Ray180;
struct CCollisionInfo2_t;
struct Ray180 {
    char pad0[0x8];
    f32 spacing;
    f32 secondaryRadius;
    f32 length;
    char pad14[0x4];
    f32 radius;
    f32 height; /* 0x1C */
    char pad20[0x1C];
    u32 flags; /* 0x3C */
    struct CCollisionInfo2_t *surface; /* 0x40 */
    CVector3 start;
    CVector3 end;
    char pad5C[0x24];
    f32 scale;
    Box box;
    CQuatern rect;
    char padAC[0xD0];
    f32 nearest;
};

struct EntryC;
typedef struct EntryC EntryC;

struct ElementE8;
struct ElementE8 {
    char pad0[0x68];
    MatrixF transform; /* 0x68 */
    u8 padA8[0xC];
    void **resource; /* 0xB4 */
    Box box;
    char padD0[0x8];
    u16 flags;
    char padDA[0xE];
};

struct ElementE8;
typedef struct ElementE8 ElementE8;

struct Hit8;
struct Hit8 {
    ElementE8 *element;
    f32 t;
};

extern float g_frontPlaneIntersectionFallbackFraction;

struct RayEntryBlock;
typedef struct RayEntryBlock RayEntryBlock;

struct PlatformSavedCollisionQueryView;
typedef struct PlatformSavedCollisionQueryView PlatformSavedCollisionQueryView;

struct PlatformCollisionEntryOwner;
typedef struct PlatformCollisionEntryOwner PlatformCollisionEntryOwner;

struct PlatformCollisionEntryOwner;
struct PlatformCollisionEntryOwner {
    u8 pad0[0x18];
    u8 *entries;
};

struct ActorCPlatformCollisionTraceShape;
struct ActorCPlatformCollisionTraceShape {
    PlatformCollisionEntryOwner *owner;
    u8 pad04[8];
    f32 radius;
    u8 pad10[0x30];
    void *collisionShape;
    u8 pad44[0x18];
    f32 movementX;
    f32 movementY;
    f32 movementZ;
};

struct InputCPlatformCollisionLiftActorToSurface;
typedef struct InputCPlatformCollisionLiftActorToSurface InputCPlatformCollisionLiftActorToSurface;

struct ContextB0;
typedef struct ContextB0 ContextB0;

struct PlatformMovementView;
typedef struct PlatformMovementView PlatformMovementView;


struct Ray180;
typedef struct Ray180 Ray180;

struct SurfaceHit;
typedef struct SurfaceHit SurfaceHit;

struct EntryC;
struct EntryC {
    void **resource;
    CQuatern *rect;
    s32 reservedWord;
};

struct CollisionShapeDefinition;
struct CollisionShapeDefinition {
    s32 flags;
    u16 kind;
    f32 radius;
    f32 halfWidth;
    f32 height;
    f32 halfDepth;
    CVector3 center;
};

struct PlatformCollisionQuery;
struct PlatformCollisionQuery {
    s32 word0;
    s32 word4;
    s32 word8;
    s32 wordC;
    s32 word10;
    u8 pad14[0x40];
    PlatformCollisionEntryOwner *owner;
    s32 index;
    u8 pad5C[0x84];
};

struct ActorCPlatformCollisionTraceShape;
typedef struct ActorCPlatformCollisionTraceShape ActorCPlatformCollisionTraceShape;

struct Footprint;
typedef struct Footprint Footprint;

extern float g_frontPlaneIntersectionInitialFraction;

struct PlatformHeightView;
struct PlatformHeightView {
    unsigned char padding_0[28];
    f32 cylinderRadius;
};

struct ModelF0;
typedef struct ModelF0 ModelF0;

struct Footprint;
struct Footprint {
    char pad0[0x18];
    CVector3 corner[4];
    f32 pad48;
    f32 winding;
};


struct ActorB0;
struct ActorB0 {
    u8 pad0[0x1C];
    f32 height; /* 0x1C */
    u8 pad20[0x20];
    s32 *flags;
    u8 pad44[0x68];
    u8 *data;
};


struct PlatformRadiusMovementView;
struct PlatformRadiusMovementView {
    unsigned char padding_0[12];
    f32 radius;
    unsigned char padding_10[76];
    f32 movementX;
    f32 movementY;
    f32 movementZ;
};

struct PlatformCollisionQuery;
typedef struct PlatformCollisionQuery PlatformCollisionQuery;

struct IntPair;

struct PlatformMovementView;
struct PlatformMovementView {
    unsigned char padding_0[92];
    f32 movementX;
    f32 movementY;
    f32 movementZ;
};

struct RayCornerBounds;
struct RayCornerBounds {
    CVector3 corners[8];
};

struct CollisionKindValueRecord;
struct CollisionKindValueRecord {
    u8 pad0[4];
    u16 kind;
    u8 pad6[2];
    f32 value;
};

struct CollisionKindValueRecord;
typedef struct CollisionKindValueRecord CollisionKindValueRecord;

struct RayEntryBlock;
struct RayEntryBlock {
    u8 pad[0x14];
    CollisionKindValueRecord entry;
};

struct SurfaceHit;
struct SurfaceHit {
    s32 word0;
    s32 word4;
    s32 word8;
    s32 wordC;
    s32 word10;
    s32 valid; /* 0x14 */
    CVector3 point; /* 0x18 */
    u8 pad24[0x24];
    CVector3 normal; /* 0x48 */
    void *input;
    s32 index;
    u8 pad5C[0x80];
};

struct PlatformSavedCollisionQueryView;
struct PlatformSavedCollisionQueryView {
    u8 pad00[0x3C];
    s32 flags;
    u8 pad40[0x70];
    SurfaceHit saved_query;
};

struct PlatformActivityPhaseView;
typedef struct PlatformActivityPhaseView PlatformActivityPhaseView;

struct CollisionKindRecord;
struct CollisionKindRecord {
    u8 pad0[4];
    u16 kind;
};

struct QueryE0;
typedef struct QueryE0 QueryE0;

struct ActorB0;
typedef struct ActorB0 ActorB0;


struct ContextB0;
struct ContextB0 {
    void *ray; /* Ray shared by collision traversal callbacks. */
    CVector3 *start;
    CVector3 *end;
    MatrixF matrix;
    f32 reach;
    s32 segments;
    f32 step;
    ElementE8 *element;
    s32 kind;
    u32 flags; /* 0x60 */
    MatrixF transform; /* 0x64 */
    void *vertices; /* 0xA4 */
    s32 isKind9;
    char padAC[0x4];
};

struct PlatformRadiusMovementView;
typedef struct PlatformRadiusMovementView PlatformRadiusMovementView;


struct CollisionProbe;
struct PlatformCollisionEntryOwner;
struct CollisionProbe {
    u8 kind;
    u8 pad01[7];
    f32 x;
    f32 y;
    f32 z;
    u8 pad14[0xC];
    f32 floor;
    u8 pad24[0x10];
    struct PlatformCollisionEntryOwner *owner;
    s32 flags38;
    u8 pad3C[0xC4];
    s32 flags100;
};

struct CollisionKindRecord;
typedef struct CollisionKindRecord CollisionKindRecord;

extern float g_platformCollisionHeightClearance;

struct QueryE0;
struct QueryE0 {
    s32 word0;
    f32 word4;
    s32 word8;
    s32 wordC;
    s32 word10;
    s32 word14;
    CVector3 vectors[4];
    CVector3 result;
    void *input;
    s32 index;
    u8 pad5C[0x84];
};

struct ActorCPlatformCollisionPushActorFromBox;
struct ActorCPlatformCollisionPushActorFromBox {
    u8 pad00[0x3C];
    s32 flags;
    u8 pad40[0x1C];
    CVector3 movement; /* 0x5C */
    u8 pad68[0x48];
    SurfaceHit saved_query;
};

struct PlatformActivityPhaseView;
struct PlatformActivityPhaseView {
    char pad0[0x4];
    s32 top;
    char pad4[0x34 - 0x4 - sizeof(s32)];
    f32 bottom;
};

struct ActorCPlatformCollisionProcessRiderMotion;
struct ActorCPlatformCollisionProcessRiderMotion {
    PlatformCollisionEntryOwner *owner;
    u8 pad04[0x3C];
    s32 *flags;
    Triple previous;
    Triple position;
    Triple delta;
};

struct ActorCPlatformCollisionProcessRiderMotion;
typedef struct ActorCPlatformCollisionProcessRiderMotion ActorCPlatformCollisionProcessRiderMotion;

struct CollisionProbe;
typedef struct CollisionProbe CollisionProbe;

struct InputCPlatformCollisionLiftActorToSurface;
struct InputCPlatformCollisionLiftActorToSurface {
    u8 kind;
    u8 pad01[7];
    f32 x;
    f32 y;
    f32 z;
    u8 pad14[0xC];
    f32 floor;
    u8 pad24[0x10];
    void *owner;
    s32 flags38;
    u8 pad3C[0xC4];
    s32 flags100;
};

struct PlatformHeightView;
typedef struct PlatformHeightView PlatformHeightView;

struct ActorCPlatformCollisionPushActorFromBox;
typedef struct ActorCPlatformCollisionPushActorFromBox ActorCPlatformCollisionPushActorFromBox;


struct RayCornerBounds;
typedef struct RayCornerBounds RayCornerBounds;

struct CollisionShapeDefinition;
typedef struct CollisionShapeDefinition CollisionShapeDefinition;

struct ModelF0;
struct ModelF0 {
    s32 reservedWord;
    s32 count;
    ElementE8 elements[1];
};

struct Hit8;
typedef struct Hit8 Hit8;

typedef struct CollisionVertex {
    f32 x, y, z;
    char padC[0xC];
    u32 clipFlags; /* 0x18 */
    s16 *position; /* 0x1C */
} CollisionVertex;


extern void PolyCol_TraceMeshDisplayList(ContextB0 *context, void *resource);

extern void CPolyCollision_SwapSortedHits();
extern void CPolyCollision_CompareSortedHits();
extern void Graphu64_ComputeViewMatrix(MatrixF *, CVector3 *, CVector3 *, CVector3 *);
#endif
