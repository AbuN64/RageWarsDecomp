#ifndef COMMON_EFFECTCONTRIBUTION_H
#define COMMON_EFFECTCONTRIBUTION_H
#include "TYPES.H"
/* Reset and accumulate the scale, weight and displacement of an effect. */
typedef struct EffectContribution {
    s32 id;
    s32 state;
    u8 reserved8[4];
    s32 stateC;
    s32 state10;
    f32 scale;
    u8 reserved18[0xC];
    f32 weight;
    u8 reserved28[0xC];
    f32 x, y, z;
} EffectContribution;

#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"


struct Node438C;
typedef struct Node438C Node438C;

struct Node438C;
struct AnimationFrameDefinition;
typedef struct AnimationFrameDefinition AnimationFrameDefinition;
typedef struct AnimationFrameState AnimationFrameState;

struct AnimationFrameState;

struct Node438C {
    u8 pad0[4];
    struct Node438C *next;
    u8 pad8[8];
    CVector3 position;
    f32 a;
    f32 b;
    f32 c;
    f32 matrices[2][16]; /* 0x28: double-buffered transforms */
};

struct Node438C;

struct TexturedRibbonOwnerView;

struct StateSmpUpdateRibbonLifetime;
typedef struct StateSmpUpdateRibbonLifetime StateSmpUpdateRibbonLifetime;


struct RibbonFrameBufferView;

struct Shade;
typedef struct Shade Shade;

struct EffectBoneNode;
struct ParticleSwooshAttachment;
struct ParticleSwooshAttachment {
    u8 pad0[4];
    struct ParticleSwooshAttachment *next;
    struct EffectBoneNode *node;
    u8 padC[0x10];
    void *object;
    u8 pad20[4];
    f32 value;
    u8 pad28[0x14];
    u32 flags;
};
struct SwooshAttachmentOwnerView;
struct ParticleSwooshAttachment;

struct ParticleActorListView;
typedef struct ParticleActorListView ParticleActorListView;

struct RibbonFrameBufferView;
typedef struct RibbonFrameBufferView RibbonFrameBufferView;

struct ParticleRibbonLifetimeView;

struct ParticleQuadPoolScene;
typedef struct ParticleQuadPoolScene ParticleQuadPoolScene;

struct Transform;
struct Transform {
    union {
        PackedMatrixWords matrix;
        struct {
            char pad0[0x18];
            s16 position[3];
        };
    };
};

extern void Fx_RibbonNoop(void);

extern void Fx_ResetEffectContribution(EffectContribution *contribution, s32 effectId);


struct Entity1DC;
struct Entity1DC {
    char pad[0x118];
    LinkedWorldFlagsView *renderDefinition;
    char p11c[31];
    u8 effectReferenceCount;
    char p13c[157];
    u8 ribbonReferenceCount;
};

struct Entity1DC;
typedef struct Entity1DC Entity1DC;

struct Particle;
typedef struct Particle Particle;

struct DefC;
typedef struct DefC DefC;

struct ChildB4;
typedef struct ChildB4 ChildB4;

struct DefC;
struct DefC {
    int reservedDefinitionWord;
    f32 minimumLifetime;
    f32 segmentLifetime;
};

struct ChildB4;
struct ChildB4 {
    int previousAddress;
    struct ChildB4 *next;
    f32 remainingLifetime;
    int pc;
    f32 pos[3];
    f32 rot[3];
    Matrix mat[2];
    f32 fraction; /* 0xA8 */
    f32 length; /* 0xAC */
    Entity1DC *attachedEntity;
};

struct Node44;
struct Node44 {
    int previousAddress;
    struct Node44 *next;
    DefC *definition;
    char pc[16];
    Entity1DC *attachedEntity;
    int p20;
    f32 lifetime;
    char p28[20];
    int flags;
    ChildB4 *segments;
};

struct Node44;
typedef struct Node44 Node44;

struct Root752C;

extern float g_ribbonDistancePhaseScale;


struct RibbonActor;
typedef struct RibbonActor RibbonActor;

struct FloatStateB0;

struct Root752C;
typedef struct Root752C Root752C;


struct TexturedRibbonOwnerView;
typedef struct TexturedRibbonOwnerView TexturedRibbonOwnerView;

struct ParticleRibbonNodeView;

extern float g_particleRibbonActorScale;

struct Morph;
typedef struct Morph Morph;


struct Shade;
struct Shade {
    u8 a;
    u8 b;
    u8 g;
    u8 r;
};

struct Blend;
struct Blend {
    Shade from;
    Shade to;
    u16 first;
    u16 second;
};


struct TexturedRibbonSegmentView;



struct CROMSwoosh_t;
struct CROMSwoosh_t {
    char pad0[4];
    f32 span;
    f32 total;
    char padC[0x12 - 0xC];
    u8 closed;
    char pad13[0x16 - 0x13];
    u8 prim[3];
    u8 env[3];
    u8 kind;
    u8 textureScale;
    char pad1E[0x21 - 0x1E];
    u8 scaleS, scaleT, count;
    struct Blend blends[1];
};
struct RibbonActor;
struct CROMSwoosh_t;

struct Transform;
typedef struct Transform Transform;

struct Particle;
struct Particle {
    char pad0[4];
    struct Particle *next;
    Transform transform;
    u8 padTransform[0x48 - 8 - sizeof(Transform)];
    s32 owner; /* 0x48: actor whose projected effect this is */
};

struct Blend;
typedef struct Blend Blend;


struct FloatStateB0;
typedef struct FloatStateB0 FloatStateB0;

struct VertexArena;
typedef struct VertexArena VertexArena;






struct Nodes;
struct Nodes {
    s32 reservedWord;
    struct Nodes *next;
    f32 value;
};



struct Particle;

struct Particle;
struct ParticleQuadPoolScene;
struct ParticleQuadPoolScene {
    char pad0[0x94E0];
    IntrusiveList lists[10];
    char pad95A8[0x95A8 - 0x94E0 - 10 * 0x14];
    IntrusiveList free;
};


struct ParticleRibbonNodeView;
typedef struct ParticleRibbonNodeView ParticleRibbonNodeView;

struct ParticleRibbonLifetimeView;
typedef struct ParticleRibbonLifetimeView ParticleRibbonLifetimeView;




struct SwooshAttachmentOwnerView;
typedef struct SwooshAttachmentOwnerView SwooshAttachmentOwnerView;

struct TexturedRibbonStateView;

struct Nodes;
struct StateSmpUpdateRibbonLifetime;
struct StateSmpUpdateRibbonLifetime {
    u8 pad0[0x1C];
    void *object;
    u8 pad20[4];
    f32 timer;
    u8 pad28[4];
    f32 count_up;
    f32 total;
    u8 pad34[8];
    u32 flags;
    struct Nodes *nodes;
    u8 pad44[4];
    s32 active;
    f32 amount;
    s32 retries;
};


struct TexturedRibbonSegmentView;
typedef struct TexturedRibbonSegmentView TexturedRibbonSegmentView;

struct Blend;
struct Key;
struct Morph;

extern float g_particleQuadMatrixAxisScale;

extern float g_particleRibbonSpecialActorScale;

extern float g_particleQuadMatrixScale;


struct TexturedRibbonResourceView;

extern void Fx_DetachEffectOwner(SwooshAttachmentOwnerView *owner, int object);


struct TexturedRibbonStateView;
typedef struct TexturedRibbonStateView TexturedRibbonStateView;





/* Shared four-vertex particle quad initialized by Match_InitParticleQuad. */
extern Vtx g_particleQuadVertices[4];


struct Nodes;
typedef struct Nodes Nodes;


extern float g_effectUpQuaternionConstants;

/* The ribbon vertex arena Fx_AllocateRibbonVertices allocates from; only passed through here. */
struct VertexArena;

struct ParticleActorListView;

struct TexturedRibbonResourceView;
typedef struct TexturedRibbonResourceView TexturedRibbonResourceView;

extern CQuatern *Fx_BuildUpAxisQuaternion(CQuatern *out, u32 bx, u32 by, u32 bz);


extern f32 g_detachedRibbonActorScale;
extern f32 g_detachedRibbonSpecialActorScale;
extern f32 g_detachedRibbonEntityScale;
extern f32 g_detachedRibbonSpecialEntityScale;
#endif
