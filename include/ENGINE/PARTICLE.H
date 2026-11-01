#ifndef ENGINE_PARTICLE_H
#define ENGINE_PARTICLE_H
#include "COMMON/SHARED_PARTICLEINSTANCE.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "TYPES.H"
#include "COMMON/ASSERT.H"
#include "COMMON/MATH_HELPERS.H"
#include "COMMON/PARTICLE_ATTACHMENT_AND_OWNER_VIEWS.H"

/* Attachment view of the existing collision state: ROM pointer at0,
 * draw-frame selector at0x14; the scene vector begins at0x08. */
typedef struct ParticleAttachmentState {
    Shared_ParticleTarget *current;
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

/* The common particle remains 0x1DC bytes; sound and list state follow it. */
typedef struct LiveParticle {
    Shared_Particle particle;
    CacheResourceNode *sound;
    f32 scale;
} LiveParticle;

/* Effect arguments use the same two-word ABI with signed halfword controls. */
typedef union ParticleActionPair {
    struct IntPair words;
    struct { s16 upper, lower; s32 last; } control;
} ParticleActionPair;

/* Sound-capable particles append their playback node to the common particle. */
typedef struct SoundParticle {
    Shared_Particle particle;
    CacheResourceNode *sound; /* 0x1DC */
} SoundParticle;

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
static inline f32 particleCameraScale(Shared_Particle *particle, f32 distFromCamera, GameplayCamera *camera) {
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

struct PackedMatrixWords;

struct Shared_Particle;

extern f32 *Particle_ParentTransform(struct Shared_Particle *particle, struct GameplayCamera *camera);

extern void Particle_Attach(struct Shared_Particle *particle, struct CVector3_t *outPosition,
                            struct CVector3_t *outDirection);

extern void Particle_BuildMatrix(struct Shared_Particle *particle, struct PackedMatrixWords *out,
                                 struct GameplayCamera *camera, f32 depth);

extern void Particle_RecycleReleasedEffects(void *recycleSystem);

extern void Particle_FlagKind86ModeTwo(void *owner, s32 mode);

extern void Particle_CaptureSharedTrailState(void *owner);

extern s32 Particle_GetRenderLayer(void *particle);

extern s32 Particle_MapEventTenToZero(s32 event);

extern void Particle_InitializeObjectLinks(void *owner);

extern float Particle_CameraScale(struct Shared_Particle *particle, float depth, struct GameplayCamera *camera);

extern void Particle_DrawModel(struct Shared_Particle *particle, GameplayCamera *view);
extern void Particle_DrawGroundShadow(struct Shared_Particle *actor, GameplayCamera *view);
extern u8 g_particleAttachmentModeFlags;
#endif
