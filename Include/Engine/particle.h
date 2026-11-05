#ifndef ENGINE_PARTICLE_H
#define ENGINE_PARTICLE_H
#include "types.h"
struct Shared_Particle;
extern void Particle_MarkCrowdedActor(s32 particleContext, struct Shared_Particle *actor, struct Shared_Particle **others, s32 count);
#include "types.h"
struct ParticleOwnerActorView;
struct Shared_Particle;
extern void Particle_FinishActorEffects(struct Shared_Particle *actor);
#include "types.h"
struct EffectSystem;
extern void Particle_RetireOwnedActors(struct EffectSystem *world, void *owner);
#include "types.h"
struct EffectSystem;
extern void Particle_ReleaseOwnerEmitters(struct EffectSystem *world, s32 owner);
#include "types.h"
struct EffectSystem;
struct GameplayCamera;
extern void Particle_DrawRenderList(struct EffectSystem *world, struct GameplayCamera *view);
#include "types.h"
struct Shared_ParticleInstance;
extern s32 Particle_HasKindTwoEntry(struct Shared_ParticleInstance *obj);
#include "types.h"
struct Shared_ParticleInstance;
extern s32 Particle_HasKindZeroEntry(struct Shared_ParticleInstance *obj);
#include "types.h"
struct Shared_ParticleInstance;
extern s32 Particle_HasKindOneEntry(struct Shared_ParticleInstance *obj);
#include "types.h"
struct EffectSystem;

#include "types.h"
struct EffectSystem;

#include "types.h"
struct EffectSystem;
struct GameplayCamera;

#include "types.h"
struct Shared_ParticleInstance;

#include "types.h"
struct Shared_ParticleInstance;

#include "types.h"
struct Shared_ParticleInstance;

extern unsigned char g_unreadByte;
#include "Ai/ai_shared_symbols.h"
#include "Common/ballisticparams.h"
#include "Common/effectrender.h"
#include "Common/globals.h"
#include "Menu/Items/Batch/batch_symbols.h"

struct EmitterModel;
struct MinigunTextLayout;
struct ParticleContactState;
struct EffectSystem;
struct LevelActor;
struct ParticleKindEntrySets;
/* Bits of a particle's flag word. */
#define PARTICLE_FLAG_CARRIED_BY_OWNER 0x400000
#define PARTICLE_FLAG_TEXTURED 0x800000
#define PARTICLE_FLAG_MOVES_AGAINST_DIRECTION 0x4000000
/* Bit of a particle descriptor's flag word. */
#define PARTICLE_DESC_FLAG_LEAVES_IMPACT_MARK 0x800000
#include "Common/runtime_declarations.h"
#include "Common/sharedplayer.h"
#include "Common/vector.h"
#include "Common/shared_particleinstance.h"
#include "Common/gameplay_camera.h"
#include "types.h"
#include "Common/assert.h"
#include "Common/math_helpers.h"
#include "Common/particle_attachment_and_owner_views.h"

/* Attachment view of the existing collision state: ROM pointer at0,
 * draw-frame selector at0x14; the scene vector begins at0x08. */
typedef struct ParticleAttachmentState {
    struct LevelActor *current;
    s32 reserved4;
    CVector3 origin;
    union { s32 frame; u8 frameBytes[4]; };
    char reserved18[0x66];
    u8 mode;
    char reserved7F[0x88 - 0x7F];
    s32 pointHit;
    char reserved8C[0x4];
    CVector3 pointHitPosition;
    s32 materialHit;
    CVector3 materialHitPosition;
    char reservedAC[0x4];
    s32 surfaceHitKind;
    s32 spaceHit;
    CVector3 spaceHitPosition;
    s32 typedHit;
    CVector3 typedHitPosition;
    char reservedD4[0x4];
    CVector3 direction;
    char reservedE4[0xC];
    CVector3 point;
} ParticleAttachmentState;

/* Effect arguments use the same two-word ABI with signed halfword controls. */
typedef union ParticleActionPair {
    struct IntPair words;
    struct { s16 upper, lower; s32 last; } control;
} ParticleActionPair;

/* Distance (in units) where the particle size ramp starts and ends. */
#define PARTICLE_DEPTH_RAMP_START 16.0f

#define PARTICLE_DEPTH_RAMP_END 2048.0f

#define PARTICLE_DEPTH_RAMP_LENGTH (PARTICLE_DEPTH_RAMP_END - PARTICLE_DEPTH_RAMP_START)

/* Size scale of a particle seen through a camera: a descriptor with flag 4 scales with the distance, ramping from the
 * descriptor's near scale to its far scale, in thousandths of the distance, between
 * PARTICLE_DEPTH_RAMP_START and PARTICLE_DEPTH_RAMP_END (others use 1); the result is corrected for the camera's
 * vertical field of view against the 47.5 degree default. Particle_CameraScale is its out-of-line copy and
 * Particle_BuildMatrix inlines it, as the release build did.
 *
 * What pins the text: the original's debug build. Its read-only data survives in the eu and eu-x ROMs (eu rom
 * 0x14EF58, eu-x 0x143F58): this function's assert strings "DistFromCamera >= 0.0f", "pEffect" and "pCamera", in that
 * order, then its float pool, one word per float literal the -O0 code loads: 16 16 2032 1 | 16 16 2032 1 |
 * 16 2032 16 2032 | 0.001 | 1 | 47.5 4 47.5. This text compiled at -O0 gives exactly those bytes, strings included:
 * the three asserts on entry, the clamp (MAX before the division, MIN with 1 outside, each macro evaluating its
 * operand twice), a second statement that evaluates (distance - 16) / 2032 twice, the 0.001 factor, the else 1, and
 * the field-of-view tail with its division by 4. The release units are built with -ffast-math (config.toml): only
 * that flag turns these divisions into the ROM's reciprocal multiplies (1/2032, 0.25, 1/47.5) and its
 * scale * (1/47.5) * (...) order.
 * The second farness line has no reader: farness is not read after the lerp, and the release build deletes it after
 * register allocation; its compare keeping the distance live until then is why the distance sits in $f5. Nothing in
 * either build read it: the release keeps no trace of its value, its debug build adds no string or literal after it
 * (so no assert or trace used it), its 2032 appears nowhere else in any ROM (no shared macro), and writing it into
 * the distance instead (where the entry assert would cover it) makes gcc copy the argument where Particle_BuildMatrix
 * inlines this function, which the ROM does not do. */
static inline f32 particleCameraScale(struct Shared_Particle *particle, f32 distFromCamera, struct GameplayCamera *camera) {
    struct Shared_ParticleDesc *desc;
    f32 scale;
    f32 farness;
    f32 fov;
    ASSERT(distFromCamera >= 0.0f);
    desc = particle->desc;
    ASSERT(desc);
    ASSERT(camera);
    if (desc->flags & 4) {
        scale = distFromCamera;
        farness = RW_MIN_LT(1.0f, RW_MAX_GT(0.0f, scale - PARTICLE_DEPTH_RAMP_START) / PARTICLE_DEPTH_RAMP_LENGTH);
        scale *= desc->scaling->nearScale + (desc->scaling->farScale - desc->scaling->nearScale) * farness;
        farness = RW_MAX_GT(0.0f, (distFromCamera - PARTICLE_DEPTH_RAMP_START) / PARTICLE_DEPTH_RAMP_LENGTH);
        scale *= 0.001f;
    } else {
        scale = 1.0f;
    }
    fov = camera->fovY;
    return scale * ((fov + (47.5f - fov) / 4.0f) / 47.5f);
}

struct CVector3_t;

struct GameplayCamera;

struct FixedPointMatrix;

struct Shared_Particle;

extern f32 *Particle_ParentTransform(struct Shared_Particle *particle, struct GameplayCamera *camera);

extern void Particle_Attach(struct Shared_Particle *particle, struct CVector3_t *outPosition,
                            struct CVector3_t *outDirection);

extern void Particle_BuildMatrix(struct Shared_Particle *particle, struct FixedPointMatrix *out,
                                 struct GameplayCamera *camera, f32 depth);

extern void Particle_RecycleReleasedEffects(struct EffectSystem *recycleSystem);

extern void Particle_FlagKind86ModeTwo(void *particle, s32 mode);

extern void Particle_CaptureSharedTrailState(void *owner);

extern s32 Particle_GetRenderLayer(void *particle);

extern s32 Particle_MapEventTenToZero(s32 event);

extern void Particle_InitializeObjectLinks(void *particle);

extern float Particle_CameraScale(struct Shared_Particle *particle, float depth, struct GameplayCamera *camera);

extern void Particle_DrawModel(struct Shared_Particle *particle, struct GameplayCamera *view);
extern void Particle_DrawGroundShadow(struct Shared_Particle *actor, struct GameplayCamera *view);
extern u8 g_particleAttachmentModeFlags;
struct Shared_Particle;
void Particle_Update(struct Shared_Particle *particle);
extern int Particle_GetEffectResource(void *particle);
#if defined(VERSION_US_REV1)
extern struct MinigunTextLayout g_minigunText;
#endif
extern void Particle_Release(struct EffectSystem *owner, struct Shared_Particle *releasedEffect);
extern void Particle_PlayAttachedSound(void *soundParticle, s32 soundId);

extern void Particle_HandlePlayerContact(struct Shared_Particle *particle, struct Player *player);
extern void Particle_DrawSprite(struct Shared_Particle *particle, struct GameplayCamera *view);
extern void Particle_DispatchActorContactEvents(struct Shared_Particle *actor);
extern f32 g_frameElapsedTime;
extern f32 g_particleInitialVelocityScale;
extern float g_particleRibbonHeightScale;
extern u32 g_particleOwnerEffectFlags;
extern CVector3 g_particleTertiaryContactPosition;
extern CVector3 g_particleZeroVector;
extern struct ParticleKindEntrySets *g_weaponInfoByType[];
extern char g_actorParticleScene;
extern const f32 g_particleLightColorFadeScale;
extern const f32 g_particleLightMovementDistanceSquared;
extern s32 g_lightingBufferIndex;
extern CVector3 g_particlePrimaryContactPosition;
extern CVector3 g_particleSecondaryContactPosition;
extern s32 g_lightingBufferIndex;
struct ActorDamageHookView;

struct ParticleKindListView;
struct ParticleKindListView;
struct ParticleKindListView;
struct ActorParticleMarkCrowdedActor;
struct ParticleDrawWorld; struct GameplayCamera;
extern void Particle_UpdateTypedMotion(struct Shared_Particle *particle);
void Particle_DispatchOwnerContactLinks(struct Shared_Particle *actor);
extern void Particle_DispatchSpatialContactEvents(struct Shared_Particle *particle);
extern void Particle_DispatchParticleContactEvents(struct Shared_Particle *particle);
void Particle_SpawnInterpolatedTrail(struct Shared_Particle *actor);

/* ParticleEmitter actor (type 1054) and the effect world that lists the emitters, with the per-surface action table of the emitter model. */
typedef struct EmitterActionTable {
    struct IntPair params[14]; u16 animation[14], effect[14], sound[14];
} EmitterActionTable;
typedef struct EmitterModel { u8 pad[0x18]; EmitterActionTable *actions; } EmitterModel;
typedef struct ParticleEmitter {
    u8 pad[4]; u16 type; u8 pad6[2]; CVector3 position;
    u8 pad14[0x48]; u32 flags; u8 pad60[0xB8]; struct EmitterModel *model;
    u8 pad11C[0x10]; s32 owner; s32 *refs; u8 pad134[4]; s32 effect;
    u8 pad13C[0x94]; s8 animation; u8 pad1D1[8]; u8 linked;
    u8 pad1DA[0xA]; void *list; u8 pad1E8[4]; struct ParticleEmitter *next;
} ParticleEmitter;
typedef struct EmitterWorld { u8 pad[0xFC00]; u8 freeList[20], activeList[20], padFC28[0x14]; ParticleEmitter *actors; } EmitterWorld;

/* The shared scratch record of the last particle contact: where the contact happened, a second point (the far end of a trail) and the surface normal. */
typedef struct ParticleContactState {
    CVector3 position;
    char pad0C[0xD0 - 0xC];
    CVector3 secondPosition;
    char padDC[0xE8 - 0xDC];
    CVector3 normal;
} ParticleContactState;
extern struct ParticleContactState g_particleContactState;

#endif
