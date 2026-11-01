#ifndef COMMON_OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS_H
#define COMMON_OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS_H
#include "TYPES.H"
#include "COMMON/LEVEL_INPUT.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/OBJRECAT4V7.H"
#include "COMMON/LOCALDECODERANGE.H"

extern float g_actorBlendedViewEffectTuning;

struct BoneBoundsActorView;
typedef struct BoneBoundsActorView BoneBoundsActorView;

struct ActorModelLoadState;
typedef struct ActorModelLoadState ActorModelLoadState;



extern float g_actorPartsViewEffectTuning;



struct ActorAnimationResetState;
struct ActorAnimationResetState {
    unsigned char padding_0[256];
    s32 flags;
    s32 animationTime;
    unsigned char padding_108[6];
    s8 animationPending;
    s8 animationChanged;
};

extern int g_actorRootMotionSampleCount;

struct SineTable;
struct SineTable {
    f32 count;
    f32 value[120];
};



extern float g_actorRootMotionBlendCoefficients;


struct Box70;
struct Box70 {
    CVector3 corners[8];
    char pad60[0xC];
    s32 mask;
};

struct ActorModelResourceView;
struct ActorModelResourceView {
    char pad0[0x8];
    CVector3 position0;
    char pad8[0x14 - 0x8 - sizeof(CVector3)];
    u16 * model;
    char pad14[0x18 - 0x14 - sizeof(u16*)];
    s32 * definition;
    char pad18[0x100 - 0x18 - sizeof(s32*)];
    s32 flags;
    char pad100[0x1A0 - 0x100 - sizeof(s32)];
    void * collisionResource;
    char pad1A0[0x1F4 - 0x1A0 - sizeof(void*)];
    u16 * previousModel;
    char pad1F4[0x238 - 0x1F4 - sizeof(u16*)];
    u16 typeId;
};

struct ActorPoseBufferState;
struct ActorPoseBufferState {
    unsigned char padding_0[180];
    s32 poseMatrices;
    s32 previousPoseMatrices;
    s32 clearedWordFirst;
    s32 clearedWordSecond;
    unsigned char padding_C4[60];
    s32 flags;
};

struct ActorModelLoadState;
struct ActorModelLoadState {
    char pad[0x14];
    PackedMaterialHalfwordView *modelHeader;
    char pad18[0x5C - 0x18];
    f32 rotation[4]; /* 0x5C */
    char pad6C[0x100 - 0x6C];
    u32 flags;
};

struct Lookup;
struct Lookup {
    s32 drawModel;
    s32 drawShadow;
    u32 pad8;
    void **value;
};



struct BoneBoundsActorView;
struct BoneBoundsActorView {
    unsigned char padding_0[1];
    s8 team;
    unsigned char padding_2[178];
    char *poseMatrices;
    char *previousPoseMatrices;
    unsigned char padding_BC[68];
    s32 flags;
    unsigned char padding_104[120];
    s32 boneMask;
};

struct LevelPlacedActorRecord;



struct Lookup;
typedef struct Lookup Lookup;


struct Box70;
typedef struct Box70 Box70;

struct BlendPartBlockView;
struct BlendPartBlockView {
    u32 words[6];
};

struct ActorPoseBufferState;
typedef struct ActorPoseBufferState ActorPoseBufferState;

struct TypeEntry;
typedef struct TypeEntry TypeEntry;




struct ActorAnimationResetState;
typedef struct ActorAnimationResetState ActorAnimationResetState;




struct SineTable;
typedef struct SineTable SineTable;

extern float g_actorBlendedViewEffectScale;


struct TypeEntry;
struct TypeEntry {
    void *data;
    void (*callback)(void *, void *);
};

struct LevelPlacedActorRecord;



struct ActorLightingBlockView;
typedef struct ActorLightingBlockView ActorLightingBlockView;

struct BlendPartBlockView;
typedef struct BlendPartBlockView BlendPartBlockView;



struct ActorModelCallbackView;
struct CollisionInfo;
struct ActorModelCallbackView {
    unsigned char padding_0[644];
    void (*callback)(void *, void *, struct CollisionInfo *);
};



struct ActorLightingBlockView;
struct ActorLightingBlockView {
    char pad[0x140];
    Block24 blocks[2];
};

struct ActorCollisionDataView;
typedef struct ActorCollisionDataView ActorCollisionDataView;

extern float g_actorGroundRotationUnitW;

struct RootMotionActorView;
typedef struct RootMotionActorView RootMotionActorView;

struct ActorCollisionResourceView;
typedef struct ActorCollisionResourceView ActorCollisionResourceView;




struct RootMotionActorView;
struct RootMotionActorView {
    unsigned char padding_0[1];
    s8 team;
    unsigned char padding_2[6];
    CVector3 position0;
    unsigned char padding_14[164];
    char *previousPoseMatrices;
    unsigned char padding_BC[40];
    u16 type;
    unsigned char padding_E6[26];
    s32 flags;
    unsigned char padding_104[120];
    s32 boneMask;
};

struct ActorModelCallbackView;
typedef struct ActorModelCallbackView ActorModelCallbackView;


struct CollisionInfo;
struct ActorCollisionResourceView;
struct ActorCollisionResourceView {
    char pad0[0xC];
    struct CollisionInfo * collisionInfo;
};


struct ActorModelResourceView;
typedef struct ActorModelResourceView ActorModelResourceView;

struct ActorCollisionDataView;
struct ActorCollisionDataView {
    char pad0[0x8];
    FloatOrWord collisionParams;
};



struct TintedPlayerRenderActor;
struct TintedPlayerRenderActor {
    char pad0[3];
    s8 renderVariant;
    u32 pad4;
    CVector3 position0;
    u32 pad14[2];
    CVector3 position1;
    u32 pad28[13];
    CQuatern rotation;
    char pad6C[0xB4 - 0x6C];
    s32 poseMatrices;
    char padB8[0x140 - 0xB8];
    BlendPartBlockView blocks[4];
};

struct TintedPlayerRenderActor;
typedef struct TintedPlayerRenderActor TintedPlayerRenderActor;

typedef void (*ActorBoneBoundsCallback)(void *, void *);
extern void Graphu64_TransformBoundingBox(f32 m[4][4], struct ModelBoundingBox *box, struct ModelBoundingBox *out);

extern void Gobjinst_AdvanceActorRootMotion(void *);
extern void Scene_UpdateMovementTriggers(struct Shared_World *, struct LevelActor *, CVector3 *, CVector3 *);
extern u8 s_actorModelAllocationTag[];
typedef struct Actor36 {
    u8 pad0[8];
    CVector3 position;
    u8 pad14[4];
    s32 *kind;
    u8 pad1C[0x34];
    f32 scaleX;
    u8 pad54[4];
    f32 scaleZ;
    u8 pad5C[0x10];
    f32 heading;
    u8 pad70[4];
    f32 matrix[4][4];
    u8 padB4[0x10];
    s32 size;
    s32 animationKey;
    u8 padCC[4];
    s32 alignment;
    u8 padD4[0x10];
    u16 ownerId;
    s8 animationCount;
    u8 padE7;
    ModelBoundingBox box;
    u32 flags;
    struct Anim currentTrack;
    struct Anim previousTrack;
    s16 blendFrames;
    u8 pad12E[2];
    f32 blend;
    f32 blendTime;
    u8 blendStart;
    u8 blendEnd;
    u8 pad13A[0x36];
    u8 state[84];
    CVector3 displacement;
    u8 pad1D0[0xBC];
    void (*update)(void *, void *);
} Actor36;


/* Options passed with an actor render submission. */
typedef struct ActorRenderSettings {
    s32 drawModel;
    s32 drawShadow;
    s32 reserved8;
    s32 view;
    s32 reserved10;
    CVector3 *shadowOffset; /* 0x14: offset of the blob shadow from the actor */
} ActorRenderSettings;
#endif
