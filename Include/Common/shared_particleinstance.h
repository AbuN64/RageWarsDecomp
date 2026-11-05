#ifndef COMMON_SHARED_PARTICLEINSTANCE_H
#define COMMON_SHARED_PARTICLEINSTANCE_H
#include "types.h"
#include "Common/small_records.h"
#include "Common/sharedplayer.h"
#include "Common/vector4f.h"
#include "Common/ccollisioninfo2_t.h"
#include "Common/resident_event_handler.h"
#include "Common/characterselectionroot.h"
#include "Common/actor_definition.h"

struct ActorDefinitionHeader;
struct CharacterScreenCell;
struct FixedPointMatrix;
struct ParticleKindIdEntry;
struct EffectMotion {
    u16 gravityHi;
    u16 gravityLo;
    u16 speedHi;
    u16 speedLo;
    u16 bounceEnergy;
    u16 groundFriction;
    u16 airFriction;
    u16 waterFriction;
    u16 acceleration; /* 0x10: encoded, Menu_ExpandFloatHighWord_RuntimeDeclarations */
    u16 speedLimit; /* 0x12: encoded, Menu_ExpandFloatHighWord_RuntimeDeclarations */
};
struct Shared_ParticleColors {
    u8 initialPrim[3];
    u8 initialEnv[3];
    u8 prim[3];
    u8 env[3];
    s8 randomizeHue;
    s8 randomizeSaturation;
    s8 randomizeValue;
};
struct Shared_ParticleFade {
    s16 lifeBase;
    s16 lifeRange;
    s8 chance;
    s8 rangeMode;
    s8 countBase;
    s8 countRange;
    s8 listIndex;
    s8 fadeIn;
    s8 fadeOut;
    s8 animationParameter;
    s8 trailSegmentCount; /* 0x0C: interpolated emissions between previous/current positions */
    s8 emitSpread;
    s8 modeSelector;
};
struct Shared_ParticleSineWave {
    CharacterScreenCell ranges[6];
    s8 fadeInFrames; /* 0x18: m_nSineWaveFadeIn */
};
struct Shared_ParticleScaling {
    CharacterScreenCell ranges[6];
    f32 shadowScale;
    f32 nearScale;
    f32 farScale;
};
struct Shared_ParticleEvents {
    struct IntPair parameters[14];
    u16 particles[14];
    u16 effects[14];
    u16 sounds[14];
};
struct Shared_ParticleDesc {
    u32 flags;
    s16 textureId;
    s8 ribbonId;
    s8 lightId;
    s8 playback;
    u8 instanceBehavior;
    s8 wallBehavior; /* 0x0A: signed descriptor behavior, including matrix readers */
    u8 groundBehavior;
    s16 sound;
    s16 steeringAngleLimit; /* 0x0E: signed ballistic steering limit */
    s16 playerContactRadius;
    u8 playerMask;
    char pad13;
    s32 renderModel;
    struct Shared_ParticleEvents *events;
    struct CharacterScreenCell *offset;
    struct CharacterScreenCell *packedRangesB;
    struct Shared_ParticleScaling *scaling;
    struct CharacterScreenCell *direction;
    struct Shared_ParticleSineWave *sineWave;
    struct EffectMotion *motion;
    struct Shared_ParticleColors *colors;
    struct Shared_ParticleFade *fade;
};
struct EffectBlock {
    s32 reservedWord;
    s32 count;
    struct Shared_ParticleDesc entries[1];
};


struct Shared_ParticleInstance;
struct Shared_ParticleInstance {
    s8 kind; /* +0x0: Particle_InitializeObjectLinks sets particle actor kind 2 */
    char pad1[0x3];
    u16 type;
    CVector3 pos; /* 0x08: ABI aligns the vector after the type halfword */
    s32 region;
    struct ActorDefinitionHeader *definition; /* 0x18: base instance category */
    CVector3 velocity;
    CVector3 motionAngles; /* 0x28: GameObject_ResetActorMotion */
    void *attached; /* 0x34 */
    s32 instanceFlags;
    s32 motionIndex; /* 0x3C: reset to -1 */
    f32 floorHeight; /* 0x40 */
    CVector3 floorDirection; /* 0x44: reset to (0, floor direction Y, 0) */
};


struct ParticleKindIdEntry;
struct ParticleKindIdEntry {
    s16 kind;
    char pad[2];
    s16 id;
};







struct Shared_ParticleInstance;
typedef struct Shared_ParticleInstance Shared_ParticleInstance;


struct ParticleKindIdEntry;
typedef struct ParticleKindIdEntry ParticleKindIdEntry;

struct ParticleKindEntrySets;
struct ParticleKindEntrySets {
    char pad[0x20];
    struct ParticleKindIdEntry *first[3];
    struct ParticleKindIdEntry *second[3];
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
    struct FixedPointMatrix *drawMatrices; /* 0xB4: one per skeleton node (CGameObjectInstance_t m_pmtDrawMtxs) */
    struct FixedPointMatrix *bones;
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






extern int g_particlePrimaryContactRoom;














struct Shared_ParticleColors;

struct Shared_ParticleFade;

struct Shared_ParticleColors;
struct Shared_ParticleDesc;
struct Shared_ParticleFade;
/* The descriptor's sine wobble (CROMParticleSineWave_t): random X/Y amplitude, frequency and phase pairs, then the
 * frames the wobble fades in over. */

/* The descriptor scaling (CROMParticleScale_t): random X/Y/Z scale pairs, then m_ShadowScale, m_NearScale, m_FarScale. */

/* Two 24-byte directional-light records occupy particle +0xE0..+0x110. */
#include "Common/particle_lighting.h"
#include "Common/ccollisioninfo2_t.h"
/* Fourteen event slots: paired parameters followed by parallel ID arrays. */

struct EffectMotion;








struct Shared_Particle;
struct Shared_ParticleDesc;
struct CLoopingSoundData_t;
struct Shared_Particle {
    Shared_ParticleInstance inst;
    CVector3 attachmentPosition;
    s32 flags;
    FixedPointMatrix mtx[2];
    struct Shared_ParticleLighting lighting[2];
    s32 resource; /* 0x110 */
    s32 resourceSize; /* 0x114 */
    struct Shared_ParticleDesc *desc;
    s32 model;
    char pad120[4];
    void *ownerIdAddress; /* 0x124: emitter identity */
    struct Shared_Particle *source; /* 0x128: source actor */
    void *owner; /* kind 1: LevelActor; kind 2: Shared_Particle */
    s32 *ownerId; /* 0x130: shared effect reference counter */
    struct LevelActor *target;
    s32 handle;
    s32 reserved13C; /* 0x13C: cleared when allocating an effect */
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
    CCollisionInfo2_t render; /* 0x1B4: collision response */
    s8 space; /* reference frame the particle is placed in (-8..2): Particle_ParentTransform_SharedParticleinstance picks its parent transform, Particle_BuildMatrix_SharedParticleinstance its ground clamp */
    union {
        s8 collisionNode; /* 0x1D1: skeleton node of the target a riding particle (flags 0x10000) follows */
        s8 quiver; /* a stuck particle's (flags 0x20000) quiver strength 0..127, decaying 6 a frame */
    };
    u8 prim[3];
    u8 env[3];
    u8 opacity;
    u8 ribbonReferenceCount;
    struct CLoopingSoundData_t *sound; /* 0x1DC: attached spatial playback */
    f32 scale; /* 0x1E0: sampled motion and contact-parameter scale */
    struct IntrusiveList *list;
    struct Shared_Particle *previous;
    struct Shared_Particle *next;
    struct Shared_Particle *groupPrevious;
    struct Shared_Particle *groupNext;
};
struct EffectSystem {
    Shared_Particle particles[128];
    IntrusiveList free;
    IntrusiveList groups;
    IntrusiveList lists[3];
    s32 resource;
    struct Shared_Particle *last;
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










struct ParticleKindEntrySets;
typedef struct ParticleKindEntrySets ParticleKindEntrySets;










typedef struct SteeringSound {u32 header[2];s32 handle,id;} SteeringSound;
typedef struct SteeringOwner {u8 pad0[0x1D8];void *player;} SteeringOwner;
typedef struct SteeringTarget {u8 pad0[8];CVector3 anchor;u8 pad14[0x23C];CVector3 position;} SteeringTarget;
typedef struct SteeringSettings {u8 pad0[0x10];u16 acceleration,speed;} SteeringSettings;
typedef struct SteeringDescriptor {u8 pad0[0x30];SteeringSettings *motion;} SteeringDescriptor;
typedef struct SteeringParticle {u8 pad0[8];CVector3 position;u8 pad14[8];CVector3 velocity;u8 pad28[0x34];u32 flags;u8 pad60[0xB8];SteeringDescriptor *descriptor;u8 pad11C[0x10];SteeringOwner *owner;u8 pad130[4];SteeringTarget *target;u8 pad138[8];f32 time;u8 pad144[0x30];CVector3 direction;u8 pad180[0x39];s8 steeringFlagB9;s8 steeringFlagBA;u8 pad1BB[0x21];SteeringSound *sound;} SteeringParticle;
extern void *SoundVoicePool_PlaySpatialSound(void *,s32,CVector3 *,void *,s32);

void Particle_SteerToward(struct Shared_Particle *, CVector3 *);
#endif
