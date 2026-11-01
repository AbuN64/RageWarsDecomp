#include "include_asm.h"
#include "COMMON/LONE/PARTICLE_PITCH_MATRIX_SCRATCH.H"
#include "COMMON/GAMEPLAY_ROUND_RULES.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/SHARED_PARTICLEINSTANCE.H"
#include "TYPES.H"
#include "GAME/BUILDDIRECTIONMATRIX.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "ENGINE/PARTICLE.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/AIPROFILE.H"
#include "ENGINE/GREGION.H"

extern void BuildDirectionMatrix(void *matrix, CVector3 *direction);
extern f32 Region_GetPolygonHeight(Node75 *node, f32 x, f32 z);
extern void MatrixFromQuaternion(f32 *q, f32 *m);
extern void Graphu64_MultiplyAffineMatrices(f32 *out, f32 *left, f32 *right);








/* Returns the matrix a particle's alignment places it in, or null for world space. Matrices built here go to the
 * scratch matrix g_particleYawMatrixScratch; g_particlePitchMatrixScratch is the lying-flat basis (a quarter turn about X), tilted to the floor's
 * slope for a floor particle on the floor and to the cached slope for a ceiling one. */
f32 *Particle_ParentTransform(Shared_Particle *particle, GameplayCamera *camera) {
    f32 tilt[16];
    CQuatern up;
    f32 *matrix;
    f32 value;

    switch (particle->space) {
    case PARTICLE_ALIGN_TRAVEL:
        matrix = g_particleYawMatrixScratch;
        BuildDirectionMatrix(matrix, &particle->direction);
        return matrix;
    case PARTICLE_ALIGN_BILLBOARD_UPRIGHT:
        if (camera == 0) {
            return 0;
        }
        return camera->faceScreenUpright;
    case PARTICLE_ALIGN_BILLBOARD:
    case PARTICLE_ALIGN_BILLBOARD_ALT:
        if (camera == 0) {
            return 0;
        }
        return camera->faceScreen;
    case PARTICLE_ALIGN_FLOOR:
        value = Region_GetPolygonHeight(0, particle->inst.pos.x, particle->inst.pos.z);
        if (particle->inst.pos.y - value <= 0.01f) {
            Region_GetPolygonUpQuat(&up, 0);
            MatrixFromQuaternion(&up, tilt);
            matrix = g_particleYawMatrixScratch;
            Graphu64_MultiplyAffineMatrices(matrix, g_particlePitchMatrixScratch, tilt);
            return matrix;
        }
        /* off the floor it lies flat */
    case PARTICLE_ALIGN_FLAT:
        return g_particlePitchMatrixScratch;
    case PARTICLE_ALIGN_CEILING:
        Region_GetCachedUpQuat(&up, 0);
        MatrixFromQuaternion(&up, tilt);
        matrix = g_particleYawMatrixScratch;
        Graphu64_MultiplyAffineMatrices(matrix, g_particlePitchMatrixScratch, tilt);
        return matrix;
    case PARTICLE_ALIGN_EDGE_0:
    case PARTICLE_ALIGN_EDGE_1:
    case PARTICLE_ALIGN_EDGE_2:
        value = Region_GetTriangleEdgeAngle(0, particle->space);
        BuildYawMatrix(g_particleYawMatrixScratch, value);
        return g_particleYawMatrixScratch;
    }
    return 0;
}

/* Refreshes a particle that rides something and returns its position and direction through optional pointers: a
 * particle riding a target (flag 0x10000) of one of the bone-mounted types takes its position and direction from
 * the target's draw matrix for its collision node (or just the target's position when the target has no draw
 * matrices) and clears its region; a particle carried by its owner (flag 0x400000) places its local position through
 * the owner's orientation, or for a player owner (flags 0x300000) through its camera's view orientation, or the
 * player view transform when the player has no camera. */
extern void Graphu64_ConvertMatrixToFloat(f32 *dst, PackedMatrixWords *src);
extern void Graphu64_TransformDirection(void *matrix, CVector3 *in, CVector3 *out);
extern void Player_BuildPlayerViewTransform(Player *player, f32 out[4][4]);
void Particle_Attach(Shared_Particle *particle, CVector3 *outPosition, CVector3 *outDirection) {
    f32 matrix[16];
    CVector3 position;
    CVector3 direction;
    f32 viewTransform[4][4];
    Shared_ParticleTarget *target;
    Shared_ParticleOwner *owner;
    f32 *transform;
    PackedMatrixWords *drawMatrices;

    position = particle->inst.pos;
    direction = particle->inst.velocity;
    if (particle->flags & 0x10000) {
        target = particle->target;
        switch (particle->inst.type) {
            case 2:
            case 11:
            case 15:
            case 45:
            case 79:
            case 86:
            case 294:
            case 298:
            case 306:
            case 1054:
                drawMatrices = target->drawMatrices;
                if (drawMatrices != 0) {
                    Graphu64_ConvertMatrixToFloat(matrix, &drawMatrices[particle->collisionNode]);
                    Graphu64_TransformPoint(matrix, &particle->attachmentPosition, &position);
                    Graphu64_TransformDirection(matrix, &particle->inst.velocity, &direction);
                    particle->inst.pos = position;
                    particle->direction = direction;
                } else {
                    position = target->position;
                    particle->inst.pos = position;
                }
                break;
        }
        particle->inst.region = 0;
    }
    if (particle->flags & 0x400000) {
        owner = particle->owner;
        if (owner->flags & 0x300000) {
            if (owner->player->camera != 0) {
                transform = owner->player->camera->viewOrient;
            } else {
                Player_BuildPlayerViewTransform(owner->player, viewTransform);
                transform = viewTransform[0];
            }
        } else {
            transform = owner->orient;
        }
        Graphu64_TransformPoint(transform, &particle->attachmentPosition, &position);
        particle->inst.pos = position;
    }
    if (outPosition != 0) {
        *outPosition = position;
    }
    if (outDirection != 0) {
        *outDirection = direction;
    }
}

#include "COMMON/MTX.H"
#include "TYPES.H"
#include "COMMON/APPROACHLOCATION.H"
#include "COMMON/SHARED_PARTICLEINSTANCE.H"
#include "COMMON/WORLD.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/MATH_HELPERS.H"
#include "ENGINE/SCENE_SAMPLEWORLDLIGHTING.H"

void Graphu64_CrossVectors(CVector3 *out, CVector3 *a, CVector3 *b);
void Graphu64_MatrixFromEulerXYZ(f32 *m, f32 x, f32 y, f32 z);
void Graphu64_IdentityMatrix(void *matrix);
void BuildRollMatrix(void *matrix, f32 angle);
void TranslateMatrix(void *matrix, f32 x, f32 y, f32 z);
f32 Graphu64_GetTrianglePlaneHeight(void *node, f32 x, f32 z);
s32 Graphu64_LimitVectorLength(f32 *vector, f32 limit);
void ScaleMatrixLocal(void *matrix, f32 sx, f32 sy, f32 sz);
void SwapMatrixUpForward(void *matrix);
void CopyMatrix(f32 *dst, f32 *src);
void Graphu64_BuildTranslationMatrix(void *matrix, f32 x, f32 y, f32 z);
void YawMatrix(void *matrix, f32 angle);
void PitchMatrix(void *matrix, f32 angle);
void Graphu64_ClampMatrixToFixedRange(f32 *matrix);
void Graphu64_ConvertMatrixToFixed(f32 *src, PackedMatrixWords *dst);



/* Gap kept between a particle and the floor or ceiling it is clamped to, and how far a travel-aligned one is drawn
 * ahead of its position. */
#define PARTICLE_SURFACE_GAP 5.12f
/* A settling particle closer to the floor than this lands on it. */
#define PARTICLE_LANDING_HEIGHT 1.024f
/* Particles are drawn this many times deeper than their size. */
#define PARTICLE_DEPTH_STRETCH 10.24f
/* Model units per particle size unit. */
#define PARTICLE_MODEL_SCALE (35.0f / 1024.0f)
/* Particles further than this from the origin are pulled back to it before drawing. */
#define PARTICLE_MAX_DISTANCE 20000.0f
/* A stuck particle quivers about a point this far behind it, by up to 5 degrees at full strength. */
#define PARTICLE_QUIVER_PIVOT 66.56f
#define PARTICLE_QUIVER_STRENGTH_MAX 127.0f
#define PARTICLE_QUIVER_SWING (RW_PI_F6 * 5 / 180)

/* Builds a particle's display matrix: its size scaled for camera depth and field of view, the drawn-only part of its
 * sine wobble, its orientation (model particles) or roll and tilt (sprites), its placement for its alignment, and the
 * quiver of a stuck particle, then packs the result into the fixed-point matrix the display list loads. */
void Particle_BuildMatrix(Shared_Particle *particle, PackedMatrixWords *out, GameplayCamera *camera, f32 depth) {
    f32 orientation[16], basis[16], local[16], world[16], quivering[16];
    CVector3 position;
    CVector3 up;
    CVector3 attachedDirection;
    CVector3 axisX;
    CVector3 axisY;
    CVector3 axisZ;
    CVector3 across;
    CVector3 side;
    CVector3 travel;
    CVector3 offset;
    struct Shared_ParticleDesc *desc;
    f32 *parent;
    f32 *final;
    f32 scale;
    f32 lift;
    f32 frame;
    f32 wobbleFade;
    f32 floorHeight;
    f32 resting;
    f32 unit;
    f32 strength;
    f32 strengthSq;
    f32 swing;
    f32 yawWave;
    f32 tiltX;
    f32 tiltY;
    s32 fadeInFrames;
    s32 quiver;
    s32 model;
    u16 type;

    desc = particle->desc;
    if (camera != 0) {
        scale = particleCameraScale(particle, depth, camera);
    } else {
        scale = 1.0f;
    }
    /* A standing sprite pivots about its base: it is lifted by its height before it turns. */
    if (desc->flags & PARTICLE_EFFECT_STANDING) {
        lift = particle->size.y * particle->size.z * scale;
    } else {
        lift = 0.0f;
    }
    Particle_Attach(particle, &position, &attachedDirection);
    /* Negative sine amplitudes only offset where the particle is drawn (the particle update moves it for positive ones),
     * fading in over the descriptor's first frames: X across the travel direction, Y up from it. */
    if (!(particle->flags & (PARTICLE_FLAG_RIDING | PARTICLE_FLAG_STUCK))) {
        frame = particle->time;
        if (frame > 0.0f) {
            fadeInFrames = desc->sineWave->fadeInFrames;
            wobbleFade = 1.0f;
            if (fadeInFrames != 0) {
                f32 fadeInLength = (f32)fadeInFrames;
                if (frame < fadeInLength) {
                    wobbleFade = frame / fadeInLength;
                }
            }
            travel = particle->direction;
            if (particle->sineAmplitudeX < 0.0f) {
                up.x = 0;
                up.z = 0;
                up.y = 1.0f;
                Graphu64_CrossVectors(&side, &up, &travel);
                Graphu64_ScaleVector(&offset, &side, Gu_Sinf(particle->sineAngleX) * -particle->sineAmplitudeX * wobbleFade);
                Graphu64_AddVec3(&position, &position, &offset);
            }
            if (particle->sineAmplitudeY < 0.0f) {
                up.x = 0;
                up.z = 0;
                up.y = 1.0f;
                Graphu64_CrossVectors(&across, &up, &travel);
                Graphu64_CrossVectors(&side, &across, &travel);
                Graphu64_ScaleVector(&offset, &side, Gu_Sinf(particle->sineAngleY) * -particle->sineAmplitudeY * wobbleFade);
                Graphu64_AddVec3(&position, &position, &offset);
            }
        }
    }
    if (particle->desc->renderModel != 0) {
        if (particle->space == PARTICLE_ALIGN_WORLD) {
            /* A free model points its Z axis along the direction it was attached with (else its travel), its X axis
             * level, and turns by its rotation on top, a quarter turn pitched up. */
            Graphu64_MatrixFromEulerXYZ(orientation, particle->rot.x + RW_PI_F6 / 2, particle->rot.y, particle->rot.z);
            if ((attachedDirection.x == 0.0f) && (attachedDirection.y == 0.0f) && (attachedDirection.z == 0.0f)) {
                axisZ = particle->direction;
            } else {
                axisZ = attachedDirection;
            }
            Graphu64_NormalizeVec3(&axisZ.x);
            up.x = 0;
            up.z = 0;
            up.y = 1.0f;
            Graphu64_CrossVectors(&axisX, &up, &axisZ);
            Graphu64_CrossVectors(&axisY, &axisX, &axisZ);
            Graphu64_IdentityMatrix(basis);
            Graphu64_NormalizeVec3(&axisX.x);
            Graphu64_NormalizeVec3(&axisY.x);
            Graphu64_NormalizeVec3(&axisZ.x);
            basis[0] = axisX.x;
            basis[1] = axisX.y;
            basis[2] = axisX.z;
            basis[4] = axisY.x;
            basis[5] = axisY.y;
            basis[6] = axisY.z;
            basis[8] = axisZ.x;
            basis[9] = axisZ.y;
            basis[10] = axisZ.z;
            Graphu64_MultiplyAffineMatrices(local, orientation, basis);
        } else {
            Graphu64_MatrixFromEulerXYZ(local, particle->rot.x, particle->rot.y + RW_PI_F6, particle->rot.z);
        }
        Scene_SampleWorldLighting(&g_world, &particle->inst.pos, &particle->lighting[g_lightingBufferIndex]);
    } else if ((particle->rot.x == 0.0f) && (particle->rot.y == 0.0f)) {
        BuildRollMatrix(local, particle->rot.z);
    } else {
        /* A sprite rolls by rot.z and slides by -rot.x, -rot.y in its own plane (the ROM reads the model again here,
         * though only sprites get this far). */
        BuildRollMatrix(local, particle->rot.z);
        model = particle->desc->renderModel;
        tiltX = 0.0f;
        if (model == 0) {
            tiltX = particle->rot.x;
        }
        tiltX = -tiltX;
        tiltY = 0.0f;
        if (model == 0) {
            tiltY = particle->rot.y;
        }
        TranslateMatrixLocal(local, tiltX, -tiltY, 0.0f);
    }
    if (lift != 0.0f) {
        TranslateMatrixLocal(local, 0.0f, lift, 0.0f);
        TranslateMatrix(local, 0.0f, -lift, 0.0f);
    }
    particle->flags &= ~PARTICLE_FLAG_ON_GROUND;
    switch (particle->space) {
    case PARTICLE_ALIGN_TRAVEL:
        position.x += particle->direction.x * PARTICLE_SURFACE_GAP;
        position.y += particle->direction.y * PARTICLE_SURFACE_GAP;
        position.z += particle->direction.z * PARTICLE_SURFACE_GAP;
        break;
    case PARTICLE_ALIGN_FLAT:
        if (desc->wallBehavior != 0) {
            position.y = RW_MAX_GT(position.y, Region_GetPolygonHeight(0, position.x, position.z) + PARTICLE_SURFACE_GAP);
        }
        break;
    case PARTICLE_ALIGN_FLOOR:
        floorHeight = Region_GetPolygonHeight(0, position.x, position.z);
        if (desc->flags & PARTICLE_EFFECT_SETTLES) {
            if (position.y < floorHeight + PARTICLE_LANDING_HEIGHT) {
                position.y = floorHeight;
                particle->flags |= PARTICLE_FLAG_ON_GROUND;
            }
        } else {
            resting = floorHeight + PARTICLE_SURFACE_GAP;
            position.y = (position.y <= resting) ? resting : position.y;
        }
        break;
    case PARTICLE_ALIGN_CEILING:
        if (desc->wallBehavior != 0) {
            position.y = RW_MIN_LT(position.y, Graphu64_GetTrianglePlaneHeight(0, position.x, position.z) - PARTICLE_SURFACE_GAP);
        }
        break;
    case PARTICLE_ALIGN_BILLBOARD_UPRIGHT:
    case PARTICLE_ALIGN_BILLBOARD:
    case PARTICLE_ALIGN_BILLBOARD_ALT:
        position.y += lift;
        break;
    case PARTICLE_ALIGN_WORLD:
    case PARTICLE_ALIGN_EDGE_0:
    case PARTICLE_ALIGN_EDGE_1:
    case PARTICLE_ALIGN_EDGE_2:
        break;
    }
    Graphu64_LimitVectorLength(&position.x, PARTICLE_MAX_DISTANCE);
    if ((desc->flags & PARTICLE_EFFECT_OPACITY_SIZE) && (desc->playback == 1)) {
        scale = scale * ((f32)particle->opacity / 255.0f);
    }
    if (particle->desc->renderModel != 0) {
        type = particle->inst.type;
        unit = scale * particle->size.z * PARTICLE_MODEL_SCALE;
        /* These models are built inside out (0x40B is tested twice in the ROM). */
        if ((type == 1035) || (type == 1039) || (type == 1054) || (type == 1035) || (type == 1078)) {
            ScaleMatrixLocal(local, -1.0f, -1.0f, -1.0f);
        }
        ScaleMatrixLocal(local, particle->size.x * unit, particle->size.y * unit, unit * PARTICLE_DEPTH_STRETCH);
        SwapMatrixUpForward(local);
    } else {
        unit = scale * particle->size.z;
        ScaleMatrixLocal(local, particle->size.x * unit, particle->size.y * unit, unit * PARTICLE_DEPTH_STRETCH);
    }
    parent = Particle_ParentTransform(particle, camera);
    if (parent != 0) {
        Graphu64_MultiplyAffineMatrices(world, local, parent);
    } else {
        CopyMatrix(world, local);
    }
    TranslateMatrix(world, position.x, position.y, position.z);
    /* A stuck particle quivers about a pivot behind it: a swing about Y three times and about X seven times over the
     * decay of its strength, both shrinking with its square. */
    if ((particle->flags & PARTICLE_FLAG_STUCK) && (quiver = particle->quiver) != 0) {
        strength = (f32)quiver * (1.0f / PARTICLE_QUIVER_STRENGTH_MAX);
        strengthSq = strength * strength;
        swing = strengthSq * PARTICLE_QUIVER_SWING;
        Graphu64_BuildTranslationMatrix(quivering, 0.0f, 0.0f, -PARTICLE_QUIVER_PIVOT);
        yawWave = Gu_Sinf(strengthSq * (6 * RW_PI_F6)) * 0.25f;
        YawMatrix(quivering, swing * yawWave);
        PitchMatrix(quivering, swing * Gu_Sinf(strengthSq * (14 * RW_PI_F6)));
        TranslateMatrix(quivering, 0.0f, 0.0f, PARTICLE_QUIVER_PIVOT);
        Graphu64_MultiplyAffineMatrices(orientation, quivering, world);
        Graphu64_ClampMatrixToFixedRange(orientation);
        final = orientation;
    } else {
        Graphu64_ClampMatrixToFixedRange(world);
        final = world;
    }
    Graphu64_ConvertMatrixToFixed(final, out);
}
