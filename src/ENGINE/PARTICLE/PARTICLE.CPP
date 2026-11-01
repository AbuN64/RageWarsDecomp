#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/SHARED_PARTICLEINSTANCE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/MATH_HELPERS.H"
#include <ultra64.h>
#include "TYPES.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "ENGINE/PARTICLE.H"
#include "SYSTEM/CONTACT_EFFECT.H"

/* Updates a particle for one frame: halves the frame step for particles owned by a slowed object, measures its bounding
 * box, kills it or bounces it off its target when its type's rule says so (the German cartridge has a gentler rule
 * table), advances its spin and size (growing towards a capped target size, or dying when a size goes negative), lets
 * nearby players react to it, and when it moves or falls probes the ground through Collision_ProbeGround_de, orients itself to the
 * surface it hit and runs the collision responses its descriptor allows. g_frameElapsedTime (the frame step) is restored on
 * every exit after the early time check. */
extern f32 g_frameElapsedTime;

extern ParticleAttachmentState *g_collisionCurrentActor;

extern ParticleAttachmentState g_currentActorInstance;

extern char g_actorParticleEffectSystem;

extern SharedPlayer *g_transientPlayerList;

s32 Unicol_MoveActorWithCollision(Shared_Particle *particle, CVector3 pos, s32 *flags);

f32 Gobjinst_GetActorHeight(SharedPlayer *player);

void Graphu64_SubtractVectors(struct CVector3_t *difference, struct CVector3_t *leftVector, struct CVector3_t *rightVector);


f32 Graphu64_GetSquaredDistance(CVector3 *a, CVector3 *b);

s32 Graphu64_NextRandom(void);

void Particle_UpdateTypedMotion(Shared_Particle *particle);

void Particle_DispatchOwnerContactLinks(Shared_Particle *particle);

void Particle_HandleInitialMaterialContact(Shared_Particle *particle);

void Particle_HandleTypedContact(Shared_Particle *particle);

void Particle_HandleSelectedSurfaceContact(Shared_Particle *particle);

void Particle_HandleMaterialContact(Shared_Particle *particle);

void Particle_HitTarget(void *particle);

void Particle_ApplyImpactResponse(Shared_Particle *particle);

void Particle_HandlePlayerContact(Shared_Particle *particle, SharedPlayer *player);

void Particle_DispatchSpatialContactEvents(Shared_Particle *particle);

void Particle_DispatchParticleContactEvents(Shared_Particle *particle);

void Particle_SpawnInterpolatedTrail(Shared_Particle *particle);

/* Squared distance from the particle to a player's position, raised by half the player's height unless the particle
 * is type 0x40F. */
static inline f32 Particle_GetPlayerTargetDistanceSquared(Shared_Particle *particle, SharedPlayer *player) {
    CVector3 pos;
    pos = player->views0.view8_3.pos;
    if (particle->inst.type != 1039) {
        pos.y += Gobjinst_GetActorHeight(player) * 0.5f;
    }
    return Graphu64_GetSquaredDistance(&particle->inst.pos, &pos);
}

extern CVector3 g_particlePrimaryContactPosition;

extern CVector3 g_particleZeroVector;

extern s32 Region_GetModelBlendByte59(s32);

extern void Events_DeliverContactEffect(void *, void *, u16, s32, CVector3, struct IntPair);
extern struct CacheResourceBlockView Graphu64_BuildDirectionQuaternion(CVector3 *);

#include "particle/PARTICLE_SPAWNEFFECTGROUP.H"
#include "ENGINE/PARTICLE.H"

extern s32 SoundElement_PlaySoundAtPosition(s16, CVector3, s32, s32);

extern void Graphu64_ScaleVector(CVector3 *, CVector3 *, f32);
extern void Particle_Release(void *, void *);
/* Picks an animation slot from a global mode, then plays the slot's effect, spawns its object at the owner or a fixed position, plays its sound, and flags the owner. Adapted from Particle_HandleMaterialContact, with the slot chosen by a switch on g_particleContactMode (the extra case below 7 that shares the default body is needed for the decision tree; its value is not recoverable), the constant triple, one argument, the dropped Graphu64_ScaleVector call, and the final test changed. */





extern CVector3 g_particleTertiaryContactPosition;

extern CVector3 g_particleSecondaryContactPosition;

extern s32 Region_TestPolygonSlopeFlag(s32);

extern s32 Region_GetModelBlendByte58(s32);

/* Per-frame step of one live particle: sizes its culling box, resolves target hit and death, grows and spins it,
 * applies influence to nearby players, then runs the move and collision passes. */
void Particle_Update(Shared_Particle *particle) {
    Box bounds;
    Shared_ParticleOwner *owner;
    Shared_ParticleTarget *target;
    SharedPlayer *player;
    f32 savedStep;
    f32 extent;
    f32 boxSpan; /* the larger scaled size, then the box height */
    f32 halfExtent; /* the box half-size, then the shake decay */
    f32 advance;
    f32 speed;
    f32 growStep;
    f32 goalSize;
    f32 influenceRange;
    s32 die;
    s32 bounce;
    s32 done;
    s8 newShake;
    owner = particle->owner;
    savedStep = g_frameElapsedTime;
    if (particle->time < 0.0f) {
        return;
    }
    if (owner != NULL && owner->kind == 1 && (owner->flags & 0x300000) && owner->player != NULL &&
        (owner->player->reactionFlags & 0x2000)) {
        g_frameElapsedTime = savedStep * 0.25f;
    }
    extent = particle->size.z;
    boxSpan = particle->size.y * extent;
    if (!(particle->size.x * extent <= boxSpan)) {
        boxSpan = particle->size.x * extent;
    }
    if (!(boxSpan <= extent)) {
        extent = boxSpan;
    }
    boxSpan = extent * 1.4142135f;
    halfExtent = boxSpan * 0.5f;
    bounds.min.x = particle->inst.pos.x - halfExtent;
    bounds.max.x = particle->inst.pos.x + halfExtent;
    bounds.min.y = particle->inst.pos.y - halfExtent;
    bounds.max.y = particle->inst.pos.y + boxSpan;
    bounds.min.z = particle->inst.pos.z - halfExtent;
    bounds.max.z = particle->inst.pos.z + halfExtent;
    if (particle->flags & 0x20000) {
        particle->time = 0.0f;
        particle->life = particle->lifetime * 32.0f;
        halfExtent = particle->quiver - g_frameElapsedTime * 6.0f;
        newShake = (halfExtent < 0.0f) ? 0 : (s32)halfExtent;
        particle->quiver = newShake;
    }
    if (particle->flags & 0x10000) {
        target = particle->target;
        switch (particle->inst.type) {
            default:
                particle->time = 0.0f;
                particle->life = particle->lifetime * 32.0f;
            case 45:
            case 79:
                die = 0;
                break;
            case 11:
            case 1054:
                die = 0;
                break;
        }
        bounce = die;
        switch (particle->inst.type) {
            case 298:
            case 306:
                die = 0;
#if defined(VERSION_DE)
                bounce = 1;
#elif defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
                if (target->health == 0) {
                    bounce = 1;
                }
#endif
                break;
            case 2:
#if defined(VERSION_DE)
            case 273:
            case 1013:
                bounce = 1;
            case 1054:
                die = 0;
                break;
#elif defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
#endif
            case 15:
            case 86:
#if defined(VERSION_DE)
#elif defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
            case 273:
#endif
            case 294:
#if defined(VERSION_DE)
                die = 1;
#elif defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
            case 1013:
                if (particle->flags & 0x4000000) {
                    die = 1;
                } else if (!(target->flags & 0x100)) {
                    die = 1;
                } else if (target->flags & 0x300000) {
                    die = (f32)target->health <= 0.0f;
                } else {
                    die = target->stateFlags & 0x20;
                }
#endif
                bounce = 0;
                break;
            case 11:
                die = 0;
                if (target->typeCode != 33 || !(target->flags & 0x100)) {
                    bounce = 1;
                }
                break;
            case 4:
                die = 0;
                if (target->typeCode != 32 || !(target->flags & 0x100)) {
                    bounce = 1;
                }
                break;
            case 45:
            case 79:
                bounce = !(target->flags & 0x100);
#if defined(VERSION_DE)
#elif defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
                break;
            case 1054:
                die = 0;
#endif
                break;
            default:
                bounce = die = 0;
                particle->flags &= ~0x10000;
                break;
        }
        if (die || bounce) {
            particle->time = 0.0f;
            particle->space = PARTICLE_ALIGN_WORLD;
            particle->flags = (particle->flags & ~0x30000) | 0x40000;
            particle->rot.z = (f32)(Graphu64_NextRandom() % 360) * 0.017453294f;
            particle->inst.velocity.y = 0.0f;
            if (particle->flags & 0x4000000) {
                particle->inst.velocity.x = -particle->direction.x;
                particle->inst.velocity.z = -particle->direction.z;
            } else {
                particle->inst.velocity.x = 0.0f;
                particle->inst.velocity.z = 0.0f;
            }
            particle->inst.region = 0;
            particle->collisionFlags &= ~0x4000;
            if (bounce) {
                particle->life = 1;
            }
        }
    }
    if (particle->flags & 0x40000) {
        if (Unicol_MoveActorWithCollision(particle, particle->inst.pos, &particle->collisionFlags) && g_currentActorInstance.spaceHit != 0) {
            particle->space = PARTICLE_ALIGN_FLOOR;
        }
        if (particle->inst.instanceFlags & 0x1000) {
            particle->flags |= 4;
        } else {
            particle->flags &= ~4;
        }
    }
    particle->prevPos = particle->inst.pos;
    /* frames advanced this step at the particle frame rate, scaled by the game speed (15 = normal) */
    advance = g_frameElapsedTime * particle->lifetime;
    speed = g_particleSimulationTimeScale * 0.06666667f;
    particle->frame += advance * speed;
    if (particle->desc->flags & 0x1000) {
        growStep = g_frameElapsedTime * 10.24f;
        particle->size.x += growStep * particle->growth.x;
        particle->size.y += growStep * particle->growth.y;
        particle->size.z += g_frameElapsedTime * particle->growth.z;
        particle->size.x = (particle->size.x > 4096.0f) ? 4096.0f : particle->size.x;
        particle->size.y = (particle->size.y > 4096.0f) ? 4096.0f : particle->size.y;
        particle->size.z = (particle->size.z > 400.0f) ? 400.0f : particle->size.z;
    } else {
        goalSize = RW_MIN(particle->size.x * particle->growth.x, 4096.0f);
        particle->size.x += (goalSize - particle->size.x) * g_frameElapsedTime;
        goalSize = RW_MIN(particle->size.y * particle->growth.y, 4096.0f);
        particle->size.y += (goalSize - particle->size.y) * g_frameElapsedTime;
        goalSize = RW_MIN(particle->size.z * particle->growth.z, 400.0f);
        particle->size.z += (goalSize - particle->size.z) * g_frameElapsedTime;
        if (particle->size.x < 0.0f || particle->size.y < 0.0f || particle->size.z < 0.0f) {
            Particle_DispatchParticleContactEvents(particle);
            Particle_Release(&g_actorParticleEffectSystem, particle);
            ((void (*)(Shared_Particle *))Particle_StopSound)(particle);
            g_frameElapsedTime = savedStep;
            return;
        }
    }
    particle->rot.x += particle->rotSpeed.x * g_frameElapsedTime;
    particle->rot.y += particle->rotSpeed.y * g_frameElapsedTime;
    particle->rot.z += particle->rotSpeed.z * g_frameElapsedTime;
    g_collisionCurrentActor->direction = particle->inst.velocity;
    Particle_DispatchSpatialContactEvents(particle);
    influenceRange = particle->desc->playerContactRadius;
    if (!(influenceRange <= 0.0f)) {
        influenceRange *= 10.24f;
        influenceRange *= influenceRange;
        for (player = g_transientPlayerList; player != NULL;) {
            done = 0;
            if (Particle_GetPlayerTargetDistanceSquared(particle, player) < influenceRange) {
                Particle_HandlePlayerContact(particle, player);
                if (particle->inst.type == 1039) {
                    done = 1;
                }
            }
            if (done) {
                player = NULL;
            } else {
                player = player->views16E0.view16E0_1.next;
            }
        }
    }
    Particle_UpdateTypedMotion(particle);
    if ((particle->restGate == 0.0f || (particle->inst.pos.y == 0.0f && particle->restGate < 0.0f)) &&
        particle->inst.velocity.x * particle->inst.velocity.x + particle->inst.velocity.y * particle->inst.velocity.y +
                particle->inst.velocity.z * particle->inst.velocity.z <
            0.001f) {
        g_frameElapsedTime = savedStep;
        return;
    }
    if (!(particle->flags & 0x72000)) {
        die = Unicol_MoveActorWithCollision(particle, particle->inst.pos, &particle->collisionFlags);
        if (particle->inst.instanceFlags & 0x1000) {
            particle->flags |= 4;
        } else {
            particle->flags &= ~4;
        }
        if (particle->inst.type == 104 && g_currentActorInstance.current != NULL) {
            particle->target = g_currentActorInstance.current;
        }
        if (die) {
            if (g_currentActorInstance.current != NULL) {
                Graphu64_SubtractVectors(&particle->direction, &particle->inst.pos, &g_currentActorInstance.origin);
            } else if (g_currentActorInstance.pointHit != 0) {
                Graphu64_SubtractVectors(&particle->direction, &particle->inst.pos, &g_currentActorInstance.pointHitPosition);
            } else if (g_currentActorInstance.materialHit != 0) {
                Graphu64_SubtractVectors(&particle->direction, &particle->inst.pos, &g_currentActorInstance.materialHitPosition);
            } else if (g_currentActorInstance.spaceHit != 0) {
                Graphu64_SubtractVectors(&particle->direction, &particle->inst.pos, &g_currentActorInstance.spaceHitPosition);
                if (particle->space == PARTICLE_ALIGN_WORLD) {
                    particle->space = PARTICLE_ALIGN_FLOOR;
                }
            } else if (g_currentActorInstance.typedHit != 0) {
                Graphu64_SubtractVectors(&particle->direction, &particle->inst.pos, &g_currentActorInstance.typedHitPosition);
            }
            Graphu64_NormalizeVec3(&particle->direction);
        }
        Particle_DispatchOwnerContactLinks(particle);
        if (g_currentActorInstance.typedHit != 0) {
            Particle_HandleTypedContact(particle);
        }
        if (particle->flags & 0x100) {
            if (g_currentActorInstance.materialHit != 0) {
                if (!(particle->desc->flags & 0x10000000)) {
                    Particle_HandleInitialMaterialContact(particle);
                }
                if (particle->desc->flags & 0x800) {
                    particle->mode1 = 1;
                }
            }
            if (particle->flags & 0x100) {
                if (g_currentActorInstance.current != NULL) {
                    if ((particle->collisionFlags & 0x4000) && g_currentActorInstance.current->kind == 0) {
                        Particle_ApplyImpactResponse(particle);
                    } else {
                        Particle_HitTarget(particle);
                    }
                    if (particle->desc->flags & 0x800) {
                        particle->mode1 = 1;
                    }
                }
                if ((particle->flags & 0x100) && g_currentActorInstance.surfaceHitKind != 0 && !(particle->desc->flags & 0x20000000)) {
                    if (g_currentActorInstance.surfaceHitKind == 1) {
                        Particle_HandleSelectedSurfaceContact(particle);
                    } else {
                        Particle_HandleMaterialContact(particle);
                    }
                }
            }
        }
    }
    if ((particle->flags & 0x8100) == 0x100) {
        Particle_SpawnInterpolatedTrail(particle);
    }
    g_frameElapsedTime = savedStep;
}

void Particle_HandleInitialMaterialContact(Shared_Particle *particle) {
    struct IntPair pair;
    struct CacheResourceBlockView rotation;
    CVector3 position;
    s32 surfaceIndex;
    struct Shared_ParticleEvents *events;
    s32 surfaceKind;
    s32 effectId;
    s32 kind;
    s32 sound;
    struct Shared_ParticleDesc *desc;
    struct IntPair *eventParameters;

    if ((particle->flags & 0x400) != 0) {
        if ((particle->desc->flags & 0x800) != 0) {
            goto skip_effects;
        }
    }
    {
        surfaceKind = Region_GetModelBlendByte59(0);
        if (surfaceKind == 10) {
            surfaceKind = 0;
        }
        desc = particle->desc;
        surfaceIndex = surfaceKind;
        events = desc->events;
        kind = events->particles[surfaceIndex];
        effectId = events->effects[surfaceIndex];
        eventParameters = &events->parameters[surfaceKind];
        pair = *eventParameters;
        sound = desc->events->sounds[surfaceIndex];
        if (effectId != 0xFFFF) {
            Events_DeliverContactEffect(particle, particle, effectId, -1, g_particlePrimaryContactPosition, pair);
        }
        if (kind != 0xFFFF) {
            if ((particle->desc->flags & 0x10) != 0) {
                position = g_particleZeroVector;
            } else {
                position = particle->inst.velocity;
            }
            rotation = Graphu64_BuildDirectionQuaternion(&position);
            Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)particle,
                          (struct EffectActor *)particle->owner,
                          (s32 *)particle->ownerId,
                          (s32)particle->target, kind,
                          position, *(CQuatern *)&rotation, g_particlePrimaryContactPosition, 0,
                          g_particlePrimaryContactRoom,
                          (particle->flags & 0x200006) | 1);
        }
        if (sound != 0xFFFF) {
            SoundElement_PlaySoundAtPosition((s16)sound, g_particlePrimaryContactPosition, 0, -1);
        }
    }
skip_effects:
    Graphu64_ScaleVector(&particle->rotSpeed, &particle->rotSpeed,
                  particle->rotationScale);
    particle->flags |= 0x400;
    if (particle->mode1 == 1) {
        Particle_Release(&g_actorParticleEffectSystem, particle);
        Particle_StopSound(particle);
    }
}

void Particle_HandleTypedContact(Shared_Particle *particle) {
    struct IntPair pair;
    struct CacheResourceBlockView rotation;
    CVector3 position;
    s32 surfaceIndex;
    struct Shared_ParticleEvents *events;
    s32 surfaceKind;
    s32 effectId;
    s32 kind;
    s32 sound;
    struct Shared_ParticleDesc *desc;
    struct IntPair *eventParameters;

    switch (g_particleContactMode) {
    case 1:
    default:
        surfaceKind = 1;
        break;
    case 7:
        surfaceKind = 7;
        break;
    case 8:
        surfaceKind = 8;
        break;
    }
    desc = particle->desc;
    surfaceIndex = surfaceKind;
    events = desc->events;
    kind = events->particles[surfaceIndex];
    effectId = events->effects[surfaceIndex];
    eventParameters = &events->parameters[surfaceKind];
    pair = *eventParameters;
    sound = desc->events->sounds[surfaceIndex];
    if (effectId != 0xFFFF) {
        Events_DeliverContactEffect(particle, particle, effectId, -1, g_particleTertiaryContactPosition, pair);
    }
    if (kind != 0xFFFF) {
        if ((particle->desc->flags & 0x10) != 0) {
            position = g_particleZeroVector;
        } else {
            position = particle->inst.velocity;
        }
        rotation = Graphu64_BuildDirectionQuaternion(&position);
        Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)particle,
                      (struct EffectActor *)particle->owner,
                      (s32 *)particle->ownerId,
                      (s32)particle->target, kind,
                      position, *(CQuatern *)&rotation, g_particleTertiaryContactPosition, 0,
                      -5,
                      (particle->flags & 0x200006) | 1);
    }
    if (sound != 0xFFFF) {
        SoundElement_PlaySoundAtPosition((s16)sound, g_particleTertiaryContactPosition, 0, -1);
    }
    particle->flags |= 0x200;
    if ((particle->desc->flags & 0x20000) != 0) {
        Particle_Release(&g_actorParticleEffectSystem, particle);
        Particle_StopSound(particle);
    }
}

void Particle_HandleSelectedSurfaceContact(Shared_Particle *particle) {
    struct IntPair pair;
    struct CacheResourceBlockView rotation;
    CVector3 position;
    s32 surfaceIndex;
    struct Shared_ParticleEvents *events;
    s32 surfaceKind;
    s32 effectId;
    s32 kind;
    s32 sound;
    struct Shared_ParticleDesc *desc;
    struct IntPair *eventParameters;

    if (Region_TestPolygonSlopeFlag(0) != 0) {
        surfaceKind = Region_GetModelBlendByte59(0);
    } else {
        surfaceKind = Region_GetModelBlendByte58(0);
    }
    if (surfaceKind == 10) {
        surfaceKind = 0;
    }
    desc = particle->desc;
    surfaceIndex = surfaceKind;
    events = desc->events;
    kind = events->particles[surfaceIndex];
    effectId = events->effects[surfaceIndex];
    eventParameters = &events->parameters[surfaceKind];
    pair = *eventParameters;
    sound = desc->events->sounds[surfaceIndex];
    if (effectId != 0xFFFF) {
        Events_DeliverContactEffect(particle, particle, effectId, -1, g_particleSecondaryContactPosition, pair);
    }
    if (kind != 0xFFFF) {
        if ((particle->desc->flags & 0x10) != 0) {
            position = g_particleZeroVector;
        } else {
            position = particle->inst.velocity;
        }
        rotation = Graphu64_BuildDirectionQuaternion(&position);
        Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)particle,
                      (struct EffectActor *)particle->owner,
                      (s32 *)particle->ownerId,
                      (s32)particle->target, kind,
                      position, *(CQuatern *)&rotation, g_particleSecondaryContactPosition, 0,
                      -3,
                      (particle->flags & 0x200006) | 1);
    }
    if (sound != 0xFFFF) {
        SoundElement_PlaySoundAtPosition((s16)sound, g_particleSecondaryContactPosition, 0, -1);
    }
    Graphu64_ScaleVector(&particle->rotSpeed, &particle->rotSpeed,
                  particle->rotationScale);
    particle->flags |= 0x200;
    if (particle->mode2 == 1) {
        Particle_Release(&g_actorParticleEffectSystem, particle);
        Particle_StopSound(particle);
    }
}

void Particle_HandleMaterialContact(Shared_Particle *particle) {
    struct IntPair pair;
    struct CacheResourceBlockView rotation;
    CVector3 position;
    s32 surfaceIndex;
    struct Shared_ParticleEvents *events;
    s32 surfaceKind;
    s32 effectId;
    s32 kind;
    s32 sound;
    struct Shared_ParticleDesc *desc;
    struct IntPair *eventParameters;

    surfaceKind = Region_GetModelBlendByte59(0);
    if (surfaceKind == 10) {
        surfaceKind = 0;
    }
    desc = particle->desc;
    surfaceIndex = surfaceKind;
    events = desc->events;
    kind = events->particles[surfaceIndex];
    effectId = events->effects[surfaceIndex];
    eventParameters = &events->parameters[surfaceKind];
    pair = *eventParameters;
    sound = desc->events->sounds[surfaceIndex];
    if (effectId != 0xFFFF) {
        Events_DeliverContactEffect(particle, particle, effectId, -1, g_particleSecondaryContactPosition, pair);
    }
    if (kind != 0xFFFF) {
        if ((particle->desc->flags & 0x10) != 0) {
            position = g_particleZeroVector;
        } else {
            position = particle->inst.velocity;
        }
        rotation = Graphu64_BuildDirectionQuaternion(&position);
        Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)particle,
                      (struct EffectActor *)particle->owner,
                      (s32 *)particle->ownerId,
                      (s32)particle->target, kind,
                      position, *(CQuatern *)&rotation, g_particleSecondaryContactPosition, 0,
                      -2,
                      (particle->flags & 0x200006) | 1);
    }
    if (sound != 0xFFFF) {
        SoundElement_PlaySoundAtPosition((s16)sound, g_particleSecondaryContactPosition, 0, -1);
    }
    Graphu64_ScaleVector(&particle->rotSpeed, &particle->rotSpeed,
                  particle->rotationScale);
    particle->flags |= 0x200;
    if (particle->mode2 == 1) {
        Particle_Release(&g_actorParticleEffectSystem, particle);
        Particle_StopSound(particle);
    }
}

typedef struct ImpactContext { CVector3 position; char padC[0xE8 - 0xC]; CVector3 normal; } ImpactContext;
extern ImpactContext g_particleContactState;
extern char g_actorParticleScene, g_dynamicLightPool;
extern s32 Barrel_GetImpactSlot(void *);
extern void Particle_UpdateMatrix(void *);
extern void Fx_DetachParticleSwooshes(void *, void *);
extern void Particle_SpawnChildEffect(void *, s32, s32, s32);
extern LiveParticle *g_particleLinkedAttachmentEffect;

int InstHdr_UsesDefaultDefinitionHandling(struct LevelActor *source);
void Graphu64_ConvertMatrixToFloat(f32 *, void *);
void Gobjinst_ApplyImpactBoneTwist(void *, void *, void *, CVector3, CVector3, s32);
void Graphu64_InvertAffineMatrix(f32 *, f32 *);
void Graphu64_TransformDirection(f32 *, CVector3 *, CVector3 *);
s32 InstHdr_ReturnUnusedActorStatus(void *);
void PitchMatrixLocal(f32 *, f32);
static __inline__ void attachParticle(Shared_Particle *particle, f32 *transform, s32 action) {
    f32 localTransform[16];
    f32 inverse[16];
    CVector3 direction;
    Shared_ParticleTarget *attached;
    ParticleAttachmentState *scene;
    attached=g_currentActorInstance.current;
    if (transform) Graphu64_InvertAffineMatrix(inverse, transform);
    else {
        Graphu64_ConvertMatrixToFloat(localTransform, &attached->drawMatrices[g_currentActorInstance.frame]);
        Graphu64_InvertAffineMatrix(inverse, localTransform);
    }
    scene=&g_currentActorInstance;
    Graphu64_TransformPoint(inverse, &scene->origin, &particle->attachmentPosition);
    direction=scene->direction;
    Graphu64_NormalizeVec3(&direction);
    Graphu64_TransformDirection(inverse, &direction, &particle->inst.velocity);
    particle->flags|=0x10000;
    particle->target=attached;
    particle->collisionNode=g_currentActorInstance.frame;
    if (particle->inst.type==86 && action==2) particle->flags|=0x4000000;
}
#if defined(VERSION_DE)
/* This cartridge routes type 0x129 through its surface-contact event. */
static inline void Particle_DispatchSurfaceContact(LiveParticle *actor) {
    struct Shared_ParticleDesc *desc;
    s32 event;
    u32 model, effect, sound;
    struct IntPair params;
    desc = actor->particle.desc;
    event = Particle_HasSurfaceFlag(actor) ? 12 : 10;
    model = desc->events->particles[event];
    effect = desc->events->effects[event];
    params = desc->events->parameters[event];
    sound = desc->events->sounds[event];
    if (effect != 0xffff) Events_DeliverContactEffect(actor, actor, effect, -1, actor->particle.inst.pos, params);
    if (model != 0xffff) Particle_SpawnChildEffect(actor, model, actor->particle.space, 1);
    if (sound != 0xffff) SoundElement_PlaySoundAtPosition((s16)sound, actor->particle.inst.pos, 0, -1);
}
#endif
void Particle_HitTarget(void *particle) {
    LiveParticle *actor = particle;
    ParticleActionPair primary, secondary;
    f32 boneMatrix[16];
    s32 handle, mode, enabled, hasMatrix, action, special;
    s32 model, effect, sound, extraEffect; u16 type;
    Shared_ParticleTarget *source, *owner, *hit;
    void *other;
    struct Shared_ParticleEvents *actions;
    struct Shared_ParticleEvents *extraActions;
    struct Shared_ParticleDesc *definition;
    s32 draw;
    owner=0;
    source=g_currentActorInstance.current;
    enabled=1;
    special=0;
    hasMatrix=0;
    definition=actor->particle.desc;
    if (InstHdr_UsesDefaultDefinitionHandling(source)) mode=actor->particle.mode1;
    else mode=actor->particle.mode0;
    if (!actor->particle.inst.region) actor->particle.inst.region=0;
    if (g_currentActorInstance.frame!=-1) {
        action=Barrel_GetImpactSlot(source);
        if (action!=9) {
            action=g_currentActorInstance.mode;
            if (actor->particle.inst.type==13) action=4;
            owner=g_currentActorInstance.current;
            if (owner->flags&0x3000000) {
                Graphu64_ConvertMatrixToFloat(boneMatrix, &owner->bones[g_currentActorInstance.frame]);
                hasMatrix=1;
                if (owner->flags&0x1000000) {
                    Gobjinst_ApplyImpactBoneTwist(owner, &owner->stateFlags, boneMatrix, g_currentActorInstance.origin, g_currentActorInstance.direction, g_currentActorInstance.frame);
                }
                if (owner->flags&0x2000000) {
                    type=actor->particle.inst.type;
                    if (type==298 || type==306) {
                        if (*owner->category==11) {
                            special=owner->extraUses<1;
                            if (special) owner->extraUses++;
                        }
                    }
                    if (actor->particle.inst.type==86 || actor->particle.inst.type==2 || actor->particle.inst.type==294 || actor->particle.inst.type==15 ||
                        special || (actor->particle.inst.type==11 && (g_particleAttachmentModeFlags&3)==1)) {
                        attachParticle(&actor->particle, boneMatrix, action);
                        if (actor->particle.drawWhenHidden) {
                            Particle_UpdateMatrix(actor);
                            Fx_DetachParticleSwooshes(&g_actorParticleScene, actor);
                        }
                        handle=actor->particle.handle;
                        if (handle) { Gdynlight_ReleaseLight(&g_dynamicLightPool, handle); actor->particle.handle=0; }
                    }
                }
            }
        }
    } else action=Barrel_GetImpactSlot(source);
    if (action==5) { action=4; actor->particle.flags|=2; }
    if (Particle_HasSurfaceFlag(actor) && action<6 && action>=4) action=6;
    actions=definition->events;
    model=actions->particles[action]; effect=actions->effects[action];
    primary.words=actions->parameters[action];
    sound=definition->events->sounds[action];
    if (source->kind==1) {
        owner=source;
        if (owner->callback) owner->callback(owner, &owner->stateFlags, actor);
        if (InstHdr_ReturnUnusedActorStatus(owner)) enabled=0;
        if (owner->stateFlags&2) enabled=0;
    }
    if (effect!=0xffff) {
        if (g_effectCallbackFlags[effect].flags&4) {
            if (actor->particle.inst.type==86) primary.control.lower=primary.control.lower*actor->scale;
        }
        other=source;
        if (g_effectCallbackFlags[effect].flags&2) other=actor;
        Events_DeliverContactEffect(other, actor, effect, -1, g_particleContactState.position, primary.words);
    }
    if (action!=4) {
        draw=1;
        if (g_gameSettings.local) {
            draw=*source->category!=11;
            if (mode==actor->particle.mode1) draw=0;
        }
        if (draw) {
            extraActions=definition->events;
            extraEffect=extraActions->effects[4];
            if (extraEffect!=0xffff) {
                secondary.words=extraActions->parameters[4];
                if (g_effectCallbackFlags[extraEffect].flags&4) {
                    other=source;
                    if (g_effectCallbackFlags[extraEffect].flags&2) other=actor;
                    Events_DeliverContactEffect(other, actor, extraEffect, -1, g_particleContactState.position, secondary.words);
                }
            }
        }
    }
    if (model!=0xffff) Particle_SpawnChildEffect(actor, model, -8, enabled);
    if (sound!=0xffff) {
#if defined(VERSION_DE)
        if (actor->particle.inst.type!=297)
#endif
            SoundElement_PlaySoundAtPosition((s16)sound, g_particleContactState.position, 0, (s32)actor);
#if defined(VERSION_DE)
        else Particle_DispatchSurfaceContact(actor);
#endif
    }
    if (!(actor->particle.flags&0x30000)) {
        if (actor->particle.inst.type==1007 && g_particleLinkedAttachmentEffect && owner->bones && g_particleLinkedAttachmentEffect->particle.inst.type==1054 && action!=9) {
            g_particleLinkedAttachmentEffect->particle.rot=g_collisionCurrentActor->point;
            if (!hasMatrix) Graphu64_ConvertMatrixToFloat(boneMatrix, &owner->bones[g_currentActorInstance.frame]);
            PitchMatrixLocal(boneMatrix, 3.141593f);
            if (g_collisionCurrentActor->current->kind==1) {
                if (*g_collisionCurrentActor->current->category==2) Graphu64_ConvertMatrixToFloat(boneMatrix, &owner->bones[g_currentActorInstance.frame]);
                hit=g_collisionCurrentActor->current;
                if (hit->kind==1 && (hit->flags&0x300000 || *hit->category==2)) {
                    attachParticle(&g_particleLinkedAttachmentEffect->particle, boneMatrix, action);
                }
            }
        }
        if (mode==1 || (effect!=0xffff && g_effectCallbackFlags[effect].flags&1)) {
            Particle_Release(&g_actorParticleEffectSystem, actor);
            Particle_StopSound(actor);
        }
    }
}

extern u32 g_particleOwnerEffectFlags;
extern void Fx_SpawnImpactMark(void *, CVector3, CVector3, s32, s32);
extern void Player_SetPlayerResetPosition(void *, CVector3 *);
extern void Graphu64_AddVec3(CVector3 *, CVector3 *, CVector3 *);

/* Reacts to a particle striking the current attachment target. The target picks the impact slot (slot 5 becomes slot 4
 * and sets flag 2). Under the controlled-impact mode (g_motionVisibilitySettings) descriptor slot 12 or 10 fires its event, particle
 * and sound at the particle. Otherwise slots 0, 2 and 3 leave a mark when the descriptor has flag 0x800000; a particle
 * whose response byte is 8 is handed to a kind 1 owner (flag 0x20000) or expires; types 0x56, 0x126, 0xCD and 0xF move
 * to the impact point and release their swooshes and light; then the particle is pushed off the surface along the hit
 * normal and the slot's event, particle and sound fire at the impact point (event table flag 2 makes the particle, not
 * the target, the event source). The particle is removed when its response byte is 1 and flags 0x30000 are clear. */
void Particle_ApplyImpactResponse(Shared_Particle *particle) {
    struct Shared_ParticleDesc *desc, *controlledDesc;
    Shared_ParticleTarget *target;
    void *eventSource;
    s32 hit;
    s32 event;
    u32 particleType, eventType, soundType;
    u32 model, sound, effect;
    struct IntPair params;
    CVector3 normal;
    struct IntPair controlledParams;
    Shared_ParticleOwner *owner;

    target = g_currentActorInstance.current;
    desc = particle->desc;
    hit = Barrel_GetImpactSlot(target);
    if (hit == 5) {
        hit = 4;
        particle->flags |= 2;
    }
    if (g_gameSettings.local && Particle_HasSurfaceFlag(particle)) {
        controlledDesc = particle->desc;
        event = Particle_HasSurfaceFlag(particle) ? 12 : 10;
        particleType = controlledDesc->events->particles[event];
        eventType = controlledDesc->events->effects[event];
        controlledParams = controlledDesc->events->parameters[event];
        soundType = controlledDesc->events->sounds[event];
        if (eventType != 0xFFFF) {
            Events_DeliverContactEffect(particle, particle, eventType, -1, particle->inst.pos, controlledParams);
        }
        if (particleType != 0xFFFF) {
            Particle_SpawnChildEffect(particle, particleType, particle->space, 1);
        }
        if (soundType != 0xFFFF) {
            SoundElement_PlaySoundAtPosition(soundType, particle->inst.pos, 0, -1);
        }
    } else {
        switch (hit) {
        case 0:
        case 2:
        case 3:
            if (desc->flags & 0x800000) {
                Fx_SpawnImpactMark(&g_actorParticleScene, g_particleContactState.position, g_particleContactState.normal, hit, 0);
            }
            break;
        }
        if (particle->mode1 == 8 || particle->mode2 == 8) {
            if ((g_particleOwnerEffectFlags & 0x1000000) && (owner = particle->owner) && owner->kind == 1 && (owner->flags & 0x300000)) {
                particle->flags |= 0x20000;
                particle->inst.pos = g_particleContactState.position;
                particle->inst.velocity = g_particleZeroVector;
                Player_SetPlayerResetPosition(particle->owner->player, &particle->inst.pos);
            } else {
                particle->life = 1;
            }
        }
        if (particle->inst.type == 86 || particle->inst.type == 294 || particle->inst.type == 205 ||
            particle->inst.type == 15) {
            particle->flags |= 0x20000;
            particle->inst.pos = g_particleContactState.position;
            particle->inst.velocity = g_particleZeroVector;
            if (particle->drawWhenHidden) {
                Particle_UpdateMatrix(particle);
                Fx_DetachParticleSwooshes(&g_actorParticleScene, particle);
            }
            if (particle->handle) {
                Gdynlight_ReleaseLight(&g_dynamicLightPool, particle->handle);
                particle->handle = 0;
            }
        }
        normal = g_particleContactState.normal;
        Graphu64_NormalizeVec3(&normal.x);
        Graphu64_ScaleVector(&normal, &normal, 1.024f);
        Graphu64_AddVec3(&particle->inst.pos, &particle->inst.pos, &normal);
        model = desc->events->particles[hit];
        effect = desc->events->effects[hit];
        params = desc->events->parameters[hit];
        sound = desc->events->sounds[hit];
        if (effect != 0xFFFF) {
            eventSource = target;
            if (g_effectCallbackFlags[effect].flags & 2) {
                eventSource = particle;
            }
            Events_DeliverContactEffect(eventSource, particle, effect, -1, g_particleContactState.position, params);
        }
        if (model != 0xFFFF) {
            Particle_SpawnChildEffect(particle, model, -8, 1);
        }
        if (sound != 0xFFFF) {
            SoundElement_PlaySoundAtPosition(sound, g_particleContactState.position, 0, (s32)particle);
        }
        if (particle->flags & 0x30000) {
            return;
        }
        if (particle->mode1 != 1) {
            return;
        }
    }
    Particle_Release(&g_actorParticleEffectSystem, particle);
    Particle_StopSound(particle);
}
