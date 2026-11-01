#ifndef COMMON_SHARED_PARTICLEINSTANCE_H
#define COMMON_SHARED_PARTICLEINSTANCE_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
struct ActorParticleMarkCrowdedActor;
typedef struct ActorParticleMarkCrowdedActor ActorParticleMarkCrowdedActor;

struct Shared_ParticleInstance;
struct Shared_ParticleInstance {
    char pad0[0x4];
    u16 type;
    char pad6[0x2];
    CVector3 pos;
    s32 region;
    char pad18[0x4];
    CVector3 velocity;
    char pad28[0x10];
    s32 instanceFlags;
    char pad3C[0x14];
};


struct ActorParticleDispatchOwnerContactLinks;
typedef struct ActorParticleDispatchOwnerContactLinks ActorParticleDispatchOwnerContactLinks;

struct ActorParticleDispatchOwnerContactLinks;
struct MemoryUsageStats;
struct ActorParticleDispatchOwnerContactLinks {
    char pad0[4];
    u16 type;
    char pad6[0x12];
    struct MemoryUsageStats *descriptor;
    char pad1C[0x110];
    ActorEmitterSource *owner;
};



struct ParticleKindIdEntry;
struct ParticleKindIdEntry {
    s16 kind;
    char pad[2];
    s16 id;
};







struct Shared_ParticleInstance;
typedef struct Shared_ParticleInstance Shared_ParticleInstance;

struct Shared_ParticleOwner;
typedef struct Shared_ParticleOwner Shared_ParticleOwner;

struct ParticleKindIdEntry;
typedef struct ParticleKindIdEntry ParticleKindIdEntry;

struct ParticleKindEntrySets;
struct ParticleKindEntrySets {
    char pad[0x20];
    ParticleKindIdEntry *first[3];
    ParticleKindIdEntry *second[3];
};



extern int g_particleContactMode;



struct Shared_ParticleInstance;

struct Shared_ParticleInstance;


struct Shared_Particle;

struct Shared_ParticleTarget;
struct Shared_ParticleTarget {
    u8 kind;
    char reserved1[0x7];
    CVector3 position; /* 0x08 */
    char reserved14[0x4];
    s32 *category;
    char reserved1C[0x98];
    PackedMatrixWords *drawMatrices; /* 0xB4: one per skeleton node (CGameObjectInstance_t m_pmtDrawMtxs) */
    PackedMatrixWords *bones;
    char padBC[0x44];
    s32 flags;
    char pad104[0x6C];
    s32 stateFlags;
    s32 health;
    char pad178[0x2C];
    s8 typeCode;
    char reserved1A5[0xE3];
    void (*callback)(struct Shared_ParticleTarget *, s32 *, void *);
    char reserved28C[0x1158];
    s32 extraUses;
};


extern float g_particleOwnerImpactDuration;




struct Shared_Particle;
typedef struct Shared_Particle Shared_Particle;




struct Ground;
struct Ground {
    s32 found;
    char pad4[8];
    f32 height;
    char pad10[0xE0];
    CVector3 normal;
};

extern int g_particlePrimaryContactRoom;












struct Shared_ParticleOwner;
struct Shared_ParticleOwner {
    u8 kind;
    char pad1[0x73];
    f32 orient[16]; /* 0x74: the owner's orientation (CGameObjectInstance_t m_mfOrient) */
    char padB4[0x4C];
    s32 flags; /* 0x100: 0x300000 = a player */
    char pad104[0xD4];
    struct Player *player; /* 0x1D8: a player owner's player record */
};

struct Shared_ParticleColors;
struct Shared_ParticleColors {
    char pad0[0x6];
    u8 prim[3];
    u8 env[3];
};
struct Shared_ParticleFade;
struct Shared_ParticleFade {
    char pad0[0x5];
    s8 rangeMode;
    char pad6[0x3];
    s8 fadeIn;
    s8 fadeOut;
    char padB[0x3];
    s8 modeSelector;
};
struct Shared_ParticleColors;
struct Shared_ParticleDesc;
struct Shared_ParticleFade;
/* The descriptor's sine wobble (CROMParticleSineWave_t): random X/Y amplitude, frequency and phase pairs, then the
 * frames the wobble fades in over. */
struct Shared_ParticleSineWave {
    char reserved[0x18];
    s8 fadeInFrames; /* 0x18: m_nSineWaveFadeIn */
};
/* The descriptor scaling (CROMParticleScale_t): random X/Y/Z scale pairs, then m_ShadowScale, m_NearScale, m_FarScale. */
struct Shared_ParticleScaling {
    u8 reserved0[0x18];
    f32 shadowScale;
    f32 nearScale;
    f32 farScale;
};
/* Two 24-byte directional-light records occupy particle +0xE0..+0x110. */
#include "COMMON/PARTICLE_LIGHTING.H"
/* Fourteen event slots: paired parameters followed by parallel ID arrays. */
struct Shared_ParticleEvents {
    struct IntPair parameters[14];
    u16 particles[14];
    u16 effects[14];
    u16 sounds[14];
};
struct Shared_ParticleDesc {
    s32 flags;
    char pad4[0x4];
    s8 playback; /* 0x08: CROMParticleEffect_t m_Playback */
    char pad9;
    s8 wallBehavior; /* 0x0A: m_WallBehavior; the floor and ceiling alignments clamp to their surface when set */
    char padB[5];
    s16 playerContactRadius;
    char pad12[2];
    s32 renderModel;
    struct Shared_ParticleEvents *events;
    char pad1C[8];
    struct Shared_ParticleScaling *scaling;
    char pad28[4];
    struct Shared_ParticleSineWave *sineWave;
    char pad30[0x4];
    struct Shared_ParticleColors *colors;
    struct Shared_ParticleFade *fade;
};
struct Shared_Particle;
struct Shared_ParticleDesc;
struct Shared_ParticleOwner;
struct Shared_ParticleTarget;
struct Shared_Particle {
    Shared_ParticleInstance inst;
    CVector3 attachmentPosition;
    s32 flags;
    PackedMatrixWords mtx[2];
    struct Shared_ParticleLighting lighting[2];
    s32 resource; /* 0x110 */
    s32 resourceSize; /* 0x114 */
    struct Shared_ParticleDesc *desc;
    s32 model;
    char pad120[0xC];
    struct Shared_ParticleOwner *owner;
    s32 ownerId;
    struct Shared_ParticleTarget *target;
    s32 handle;
    char pad13C[4];
    f32 time;
    f32 frame;
    f32 lifetime;
    s16 life;
    s8 spriteFrame;
    s8 fixedSpriteFrame;
    CVector3 size;
    CVector3 growth;
    CVector3 prevPos;
    CVector3 direction; /* unit travel direction: aligns direction-frame particles, offsets space -8, axis of the wobble */
    CVector3 rot;
    CVector3 rotSpeed;
    f32 alpha;
    /* Sine wobble across (X) and up (Y) the travel direction (CParticle_t m_X/YSine*); amplitude > 0 moves it, < 0 only draws it offset. */
    f32 sineAngleX;
    f32 sineAngleY;
    f32 sineAngleSpeedX;
    f32 sineAngleSpeedY;
    f32 sineAmplitudeX;
    f32 sineAmplitudeY;
    s32 collisionFlags;
    s8 mode0;
    s8 mode1;
    s8 mode2;
    char pad1BB;
    f32 restGate;
    char pad1C0[4];
    f32 rotationScale;
    char pad1C8[8];
    s8 space; /* reference frame the particle is placed in (-8..2): Particle_ParentTransform_SharedParticleinstance picks its parent transform, Particle_BuildMatrix_SharedParticleinstance its ground clamp */
    union {
        s8 collisionNode; /* 0x1D1: skeleton node of the target a riding particle (flags 0x10000) follows */
        s8 quiver; /* a stuck particle's (flags 0x20000) quiver strength 0..127, decaying 6 a frame */
    };
    u8 prim[3];
    u8 env[3];
    u8 opacity;
    u8 drawWhenHidden;
    u8 reserved1DA[2];
};
/* Shared_Particle flags (CParticle_t m_dwFlags). */
#define PARTICLE_FLAG_RIDING 0x10000 /* follows a skeleton node of its target */
#define PARTICLE_FLAG_STUCK 0x20000 /* stuck in a surface; quivers */
#define PARTICLE_FLAG_MATRIX_BUILT 0x100000 /* its display matrix is built for this frame */
#define PARTICLE_FLAG_CARRIED 0x400000 /* placed through its owner's orientation */
#define PARTICLE_FLAG_ON_GROUND 0x800000 /* a settling particle lies on the floor */
/* Shared_ParticleDesc flags (CROMParticleEffect_t m_dwFlags). */
#define PARTICLE_EFFECT_STANDING 0x8 /* a sprite turns about its base, not its centre */
#define PARTICLE_EFFECT_SETTLES 0x400 /* a floor-aligned particle lands on the floor */
#define PARTICLE_EFFECT_OPACITY_SIZE 0x80000 /* with playback 1 its size follows its opacity */
/* Shared_Particle space: the frame a particle is drawn in (CParticle_t m_Alignment); Particle_ParentTransform
 * returns the matrix for each, Particle_BuildMatrix keeps the surface ones off their surface. */
enum ParticleAlignment {
    PARTICLE_ALIGN_TRAVEL = -8, /* along its travel direction */
    PARTICLE_ALIGN_WORLD = -7, /* world axes; a model turns to its direction */
    PARTICLE_ALIGN_BILLBOARD_UPRIGHT = -6, /* faces the camera, Y kept up */
    PARTICLE_ALIGN_FLAT = -5, /* lies flat, above the floor */
    PARTICLE_ALIGN_BILLBOARD = -4, /* faces the screen */
    PARTICLE_ALIGN_FLOOR = -3, /* lies on the floor, tilted to it */
    PARTICLE_ALIGN_CEILING = -2, /* tilted to the cached surface, below the ceiling */
    PARTICLE_ALIGN_BILLBOARD_ALT = -1, /* as PARTICLE_ALIGN_BILLBOARD */
    PARTICLE_ALIGN_EDGE_0 = 0, /* turned to edge 0..2 of a floor triangle */
    PARTICLE_ALIGN_EDGE_1 = 1,
    PARTICLE_ALIGN_EDGE_2 = 2
};








struct Shared_ParticleTarget;
typedef struct Shared_ParticleTarget Shared_ParticleTarget;


struct ParticleKindEntrySets;
typedef struct ParticleKindEntrySets ParticleKindEntrySets;





struct Ground;
typedef struct Ground Ground;

struct ActorParticleMarkCrowdedActor;
struct ActorParticleMarkCrowdedActor {
    char pad0[4];
    u16 type;
    char pad6[2];
    CVector3 position;
    char pad14[0x118];
    SharedPlayer *owner;
    char pad130[0x1C];
    s16 crowded;
};


typedef struct SteeringSound {u32 header[2];s32 handle,id;} SteeringSound;
typedef struct SteeringTarget {u8 pad0[0x248];CVector3 position;} SteeringTarget;
typedef struct SteeringSettings {u8 pad0[0x10];u16 acceleration,speed;} SteeringSettings;
typedef struct SteeringDescriptor {u8 pad0[0x30];SteeringSettings *motion;} SteeringDescriptor;
typedef struct SteeringParticle {u8 pad0[8];CVector3 position;u8 pad14[8];CVector3 velocity;u8 pad28[0x34];u32 flags;u8 pad60[0xB8];SteeringDescriptor *descriptor;u8 pad11C[0x18];SteeringTarget *target;u8 pad138[8];f32 time;u8 pad144[0x30];CVector3 direction;u8 pad180[0x5C];SteeringSound *sound;} SteeringParticle;
extern void *SoundVoicePool_PlaySpatialSound(void *,s32,CVector3 *,void *,s32);

typedef struct CVector3_t AccelSteeringVec;
typedef struct { char pad[16]; u16 accel, limit; } AccelSteeringParams;
typedef struct { char pad[48]; AccelSteeringParams *params; } AccelSteeringLink;
typedef struct { char pad[8]; AccelSteeringVec point; } AccelSteeringTarget;
typedef struct {
    char pad0[8];
    AccelSteeringVec position;
    char pad14[8];
    AccelSteeringVec velocity;
    char gap[0x118 - 40];
    AccelSteeringLink *link;
    char gap2[0x134 - 0x11c];
    AccelSteeringTarget *target;
    char gap3[0x140 - 0x138];
    f32 distance;
    char gap4[0x174 - 0x144];
    AccelSteeringVec direction;
} AccelSteeringObj;
void Particle_SteerToward(AccelSteeringObj *, AccelSteeringVec *);
#endif
