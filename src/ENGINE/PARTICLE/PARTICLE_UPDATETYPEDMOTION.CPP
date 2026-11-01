#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/SHARED_PARTICLEINSTANCE.H"
#include "COMMON/TRIPLE.H"
#include "particle/PARTICLE_UPDATETYPEDMOTION.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "COMMON/APPROACHLOCATION.H"

/* 8027A0F4.CPP */
extern s32 *SoundVoicePool_GetGlobalState(void);
extern s32 SoundVoicePool_StopNode(void *,void *);
static inline void makeImpulse(CVector3 *input,f32 scale,CVector3 *out){Graphu64_ScaleVector(out,input,scale);}
static inline void addImpulse(CVector3 *v,CVector3 *impulse){Graphu64_AddVec3(v,v,impulse);}
void Particle_SteerSoundTrackingParticle(void *particle) {
    SteeringParticle *steeringParticle=particle;
    CVector3 targetPosition;
    CVector3 offsetToTarget;
    CVector3 basisPoint;
    CQuatern currentDirectionQuaternion;
    CQuatern wantedDirectionQuaternion;
    CQuatern steeredDirectionQuaternion;
    Matrix steeringMatrix;
    CVector3 impulseVector;
    CVector3 accelerationDirection;
    CVector3 *acceleratedVelocity;
    CVector3 *direction;
    CVector3 *unusedPointer;
    f32 initialVelocityZ;
    f32 acceleratedVelocityZ;
    f32 acceleratedSpeed;
    f32 initialVelocityY;
    f32 initialSpeed;
    f32 scale;
    f32 acceleratedVelocityY;
    f32 speedLimit;
    f32 initialVelocityX;
    f32 attractionDistanceOffset;
    f32 acceleratedVelocityX;
    f32 amount;

    s32 unusedValue;s32 id;
    CVector3 *unusedPointer1;
    SteeringTarget *target;
    CVector3 *steeredDirection;
    SteeringSound *sound;

    if (steeringParticle->flags & 0x10000) {
        if (steeringParticle->sound != 0) {
            SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), steeringParticle->sound);
            steeringParticle->sound = 0;
        }
    } else {
        id=1840;sound = steeringParticle->sound;
        if (sound != 0) {
            if ((sound->id != id) || (sound->handle == -1)) {
                Particle_StopSound(steeringParticle);
                goto block_7;
            }
        } else {
block_7:
            steeringParticle->sound = SoundVoicePool_PlaySpatialSound(SoundVoicePool_GetGlobalState(), 1840, &steeringParticle->position, &steeringParticle->position, -1);
        }
        target = steeringParticle->target;
        if ((target != 0) && (steeringParticle->time > g_particleAttractionDelay)) {
            direction = &steeringParticle->direction;
            currentDirectionQuaternion = Graphu64_BuildDirectionQuaternion(direction);
            initialVelocityX = steeringParticle->velocity.x;
            initialVelocityY = steeringParticle->velocity.y;
            initialVelocityZ = steeringParticle->velocity.z;
            initialSpeed = Gu_Sqrtf((initialVelocityX * initialVelocityX) + (initialVelocityY * initialVelocityY) + (initialVelocityZ * initialVelocityZ));

            targetPosition = target->position;
            Graphu64_SubtractVectors(&offsetToTarget, &targetPosition, &steeringParticle->position);
            amount = Gu_Sqrtf((offsetToTarget.x * offsetToTarget.x) + (offsetToTarget.y * offsetToTarget.y) + (offsetToTarget.z * offsetToTarget.z));
            if (amount < g_particleAttractionMinimumDistance) {
                steeredDirectionQuaternion = Graphu64_BuildDirectionQuaternion(&offsetToTarget);
                MatrixFromQuaternion(&steeredDirectionQuaternion.x, steeringMatrix.m);
                basisPoint.x = 0;
                basisPoint.y = 0;
                basisPoint.z = g_particleAttractionBasisZ;
                Graphu64_TransformPoint(&steeringMatrix, &basisPoint, direction);
                Graphu64_ScaleVector(&steeringParticle->velocity, direction, initialSpeed);
                return;
            }
            if (g_particleAttractionFarDistance < amount) {
                targetPosition.y += g_particleAttractionMinimumDistance;
                Graphu64_SubtractVectors(&offsetToTarget, &targetPosition, &steeringParticle->position);
                amount = Gu_Sqrtf((offsetToTarget.x * offsetToTarget.x) + (offsetToTarget.y * offsetToTarget.y) + (offsetToTarget.z * offsetToTarget.z));
            }
            Graphu64_NormalizeVec3(&offsetToTarget.x);
            wantedDirectionQuaternion = Graphu64_BuildDirectionQuaternion(&offsetToTarget);
            if (amount < g_particleAttractionNearDistance) {
                attractionDistanceOffset = amount - g_particleAttractionDistanceOffset;
                if (attractionDistanceOffset < 0.0f) {
                    amount = 0.0f;
                } else {
                    amount = attractionDistanceOffset * g_particleAttractionDistanceScale;
                }
                amount = g_particleAttractionFalloffBase - (amount * g_particleAttractionFalloffScale);
            } else {
                amount = g_particleAttractionMaximumStrength;
            }
            Graphu64_NormalizeQuaternion(&wantedDirectionQuaternion.x);
            Graphu64_NormalizeQuaternion(&currentDirectionQuaternion.x);
            Graphu64_InterpolateQuaternionWithLinearFallback(&steeredDirectionQuaternion, amount, &currentDirectionQuaternion, &wantedDirectionQuaternion);
            MatrixFromQuaternion(&steeredDirectionQuaternion.x, steeringMatrix.m);
            steeredDirection = &steeringParticle->direction;
            basisPoint.x = 0;
            basisPoint.y = 0;
            basisPoint.z = g_particleAttractionDirectionZ;
            Graphu64_TransformPoint(&steeringMatrix, &basisPoint, steeredDirection);
            Graphu64_ScaleVector(&steeringParticle->velocity, steeredDirection, initialSpeed);
            goto block_21;
        }
block_21:
        scale = Menu_ExpandFloatHighWord((s32) steeringParticle->descriptor->motion->acceleration);
        if (scale != 0.0f) {
            accelerationDirection = steeringParticle->direction;
            makeImpulse(&accelerationDirection,scale,&impulseVector);
            addImpulse(&steeringParticle->velocity,&impulseVector);
            acceleratedVelocity=&steeringParticle->velocity;
            acceleratedVelocityX = steeringParticle->velocity.x;
            acceleratedVelocityY = steeringParticle->velocity.y;
            acceleratedVelocityZ = steeringParticle->velocity.z;
            acceleratedSpeed = Gu_Sqrtf((acceleratedVelocityX * acceleratedVelocityX) + (acceleratedVelocityY * acceleratedVelocityY) + (acceleratedVelocityZ * acceleratedVelocityZ));
            speedLimit = Menu_ExpandFloatHighWord((s32) steeringParticle->descriptor->motion->speed);
            if (scale > 0.0f) {if (!(speedLimit < acceleratedSpeed)) goto after_clamp;} else {if (!(acceleratedSpeed < speedLimit)) goto after_clamp;}
            Graphu64_ScaleVector(acceleratedVelocity, &accelerationDirection, speedLimit);
            after_clamp:;
        }
        Particle_UpdateSineMotion(steeringParticle, 1.0f);
    }
}

#ifndef FIELD
#define FIELD(type, base, off) (*(type *)((char *)(base) + (off)))
#endif
extern char g_actorParticleEffectSystem[];
extern void Player_TransformPointByViewOrOwnerMatrix(void *, CVector3 *);
extern void Particle_DispatchActorContactEvents(void *);
extern void Particle_Release(void *, void *);
/* Steers a homing particle (sound 0x8AC) at its target, or straight ahead when it has none: keeps its loop
 * sound alive, drops the target after g_homingParticleSteeringStartTime seconds, ends the particle when it gets close enough,
 * otherwise turns the direction toward the target by a blend rate chosen from the turn angle and age,
 * resets the velocity along the new direction and applies the descriptor's acceleration (clamped to its
 * top speed). */
void Particle_SteerHoming(void *particle) {
    SteeringParticle *homingParticle = particle;
    CVector3 v18;
    CVector3 v28;
    CVector3 v38;
    CQuatern v48;
    CVector3 v58;
    CVector3 v68;
    CQuatern q78;
    CQuatern q88;
    CQuatern q98;
    Matrix mA8;
    CVector3 vE8;
    CVector3 vF8;
    CVector3 *direction;
    void *owner;
    f32 speed;
    f32 distance;
    f32 angle;
    f32 rate;
    f32 accel;
    f32 limit;
    f32 speed2;
    s32 id;
    CVector3 *velocity;
    SteeringSound *sound;
    q78 = Graphu64_BuildDirectionQuaternion(&homingParticle->direction);
    speed = Gu_Sqrtf(homingParticle->velocity.x * homingParticle->velocity.x + homingParticle->velocity.y * homingParticle->velocity.y +
                             homingParticle->velocity.z * homingParticle->velocity.z);
    owner = FIELD(void *, FIELD(void *, homingParticle, 300), 472);
    id = 2220;
    sound = homingParticle->sound;
    if (sound != 0) {
        if ((sound->id != id) || (sound->handle == -1)) {
            Particle_StopSound(homingParticle);
            goto create_sound;
        }
    } else {
create_sound:
        homingParticle->sound = SoundVoicePool_PlaySpatialSound(SoundVoicePool_GetGlobalState(), 2220, &homingParticle->position, &homingParticle->position, -1);
    }
    if (FIELD(void *, homingParticle, 308) != 0) {
        if (homingParticle->time >= g_homingParticleSteeringStartTime) {
            FIELD(void *, homingParticle, 308) = 0;
        }
    }
    if (FIELD(void *, homingParticle, 308) == 0) {
        v58.x = 0;
        v58.y = 0;
        v58.z = g_homingParticleForwardZ;
        Player_TransformPointByViewOrOwnerMatrix(owner, &v58);
        Graphu64_SubtractVectors(&v68, &v58, &homingParticle->position);
        distance = Gu_Sqrtf(v68.x * v68.x + v68.y * v68.y + v68.z * v68.z);
        if (distance < g_homingParticleNearTargetDistance && homingParticle->time > g_homingParticleNearTargetDelay) {
            Particle_DispatchActorContactEvents(homingParticle);
            Particle_Release(g_actorParticleEffectSystem, homingParticle);
            Particle_StopSound(homingParticle);
            return;
        }
    } else {
        v18 = FIELD(CVector3, FIELD(void *, homingParticle, 308), 8);
        v18.y += Gobjinst_GetActorHeight(FIELD(void *, homingParticle, 308)) * g_homingParticleTargetHeightScale;
        Graphu64_SubtractVectors(&v68, &v18, &homingParticle->position);
    }
    v28 = v68;
    Graphu64_NormalizeVec3(&v28);
    q88 = Graphu64_BuildDirectionQuaternion(&v28);
    Graphu64_NormalizeQuaternion(&q88);
    Graphu64_NormalizeQuaternion(&q78);
    Graphu64_NormalizeVec3(&v28);
    v38 = homingParticle->direction;
    Graphu64_NormalizeVec3(&v38);
    angle = Graphu64_ArcCos(v28.x * v38.x + v28.y * v38.y + v28.z * v38.z);
    rate = 0.0f;
    if (!(homingParticle->time < g_homingParticleTrackingDelay)) {
        rate = g_homingParticleAcquiredTurnRate;
        if ((angle < g_homingParticleSteeringAngleThreshold && g_homingParticleAcquisitionDelay < homingParticle->time) || FIELD(void *, homingParticle, 308) != 0) {
            rate = g_homingParticleDefaultTurnRate;
        }
    }
    Graphu64_InterpolateQuaternionWithLinearFallback(&q98, rate, &q78, &q88);
    MatrixFromQuaternion(&q98, mA8.m);
    direction = &homingParticle->direction;
    v48.x = 0;
    v48.y = 0;
    v48.z = g_homingParticleSteeringBasisZ;
    Graphu64_TransformPoint(&mA8, &v48, direction);
    velocity = &homingParticle->velocity;
    Graphu64_ScaleVector(velocity, direction, speed);
    if (homingParticle->time >= g_homingParticleMotionStartTime) {
        FIELD(s8, homingParticle, 441) = 0;
        FIELD(s8, homingParticle, 442) = 0;
    }
    accel = Menu_ExpandFloatHighWord((s32)homingParticle->descriptor->motion->acceleration);
    if (accel != 0.0f) {
        vF8 = homingParticle->direction;
        makeImpulse(&vF8, accel, &vE8);
        addImpulse(velocity, &vE8);
        speed2 = Gu_Sqrtf(homingParticle->velocity.x * homingParticle->velocity.x + homingParticle->velocity.y * homingParticle->velocity.y +
                                  homingParticle->velocity.z * homingParticle->velocity.z);
        limit = Menu_ExpandFloatHighWord((s32)homingParticle->descriptor->motion->speed);
        if (accel > 0.0f) {
            if (!(limit < speed2)) goto after_clamp;
        } else {
            if (!(speed2 < limit)) goto after_clamp;
        }
        Graphu64_ScaleVector(velocity, &vF8, limit);
    after_clamp:;
    }
    Particle_UpdateSineMotion(homingParticle, 1.0f);
}

/* Steers a homing particle toward goal: snaps onto it within 51.2 units, otherwise turns its heading
   toward it (harder as it closes in), keeps its speed along the new heading and applies its acceleration
   up to the speed limit before moving it. */
void Particle_SteerToward(AccelSteeringObj *particle, AccelSteeringVec *goal) {
    AccelSteeringVec offset;
    AccelSteeringVec forward;
    CQuatern current;
    CQuatern wanted;
    CQuatern turned;
    f32 rotation[16];
    AccelSteeringVec impulse;
    AccelSteeringVec heading;
    f32 distance;
    f32 speed;
    f32 blend;
    f32 acceleration;
    f32 newSpeed;
    f32 limit;
    AccelSteeringVec *vel;

    Graphu64_SubtractVectors(&offset, goal, &particle->position);
    distance = Gu_Sqrtf((offset.x * offset.x) + (offset.y * offset.y) + (offset.z * offset.z));
    if (distance <= 51.199997f) {
        particle->position = *goal;
        return;
    }
    Graphu64_NormalizeVec3(&offset.x);
    wanted = Graphu64_BuildDirectionQuaternion(&offset.x);
    current = Graphu64_BuildDirectionQuaternion(&particle->direction.x);
    speed = Gu_Sqrtf((particle->velocity.x * particle->velocity.x) + (particle->velocity.y * particle->velocity.y) + (particle->velocity.z * particle->velocity.z));
    if (distance < 1024.0f) {
        blend = distance - 204.79999f;
        if (blend < 0.0f) {
            blend = 0.0f;
        } else {
            blend = blend * 0.0012207031f;
        }
        blend = 0.9f - (blend * 0.85999995f);
    } else {
        blend = 0.04f;
    }
    Graphu64_InterpolateQuaternionWithLinearFallback(&turned, blend, &current, &wanted);
    MatrixFromQuaternion(&turned.x, rotation);
    forward.x = 0.0f;
    forward.y = 0.0f;
    forward.z = 1.0f;
    Graphu64_TransformPoint(rotation, &forward, &particle->direction);
    Graphu64_ScaleVector(&particle->velocity, &particle->direction, speed);
    acceleration = Menu_ExpandFloatHighWord(particle->link->params->accel);
    vel = &particle->velocity;
    if (acceleration != 0.0f) {
        heading = particle->direction;
        makeImpulse(&heading, acceleration, &impulse);
        addImpulse(vel, &impulse);
        newSpeed = Gu_Sqrtf((particle->velocity.x * particle->velocity.x) + (particle->velocity.y * particle->velocity.y) + (particle->velocity.z * particle->velocity.z));
        limit = Menu_ExpandFloatHighWord(particle->link->params->limit);
        if (acceleration > 0.0f) {
            if (!(limit < newSpeed)) goto skip;
        } else if (!(newSpeed < limit)) goto skip;
        Graphu64_ScaleVector(vel, &heading, limit);
    skip:;
    }
    Particle_UpdateSineMotion(particle, 1.0f);
}

/* 8027A0F4_2.CPP */
/* Reports an actor to the active collision state g_currentActorInstance when that state is of kind 1: an actor whose owner is a kind 1 object flagged 0x300000 is reported with bit 8, 4 or 0x10 for each of three type groups its type belongs to, and otherwise an actor whose descriptor is of kind 1 or 4 is reported with bit 0x80, 0x40 or 0x100 for the same groups, each through Link_DispatchActorLinks. */

extern ActorEmitterSource *g_currentActorInstance;

extern void Link_DispatchActorLinks(ActorEmitterSource *state, s32 bits, ActorParticleDispatchOwnerContactLinks *actor);

static inline s32 is_group_a(ActorParticleDispatchOwnerContactLinks *actor) {
    switch (actor->type) {
        case 2:
        case 86:
        case 273:
        case 294:
            return 1;
    }
    return 0;
}

static inline s32 is_group_b(ActorParticleDispatchOwnerContactLinks *actor) {
    switch (actor->type) {
        case 5:
        case 6:
        case 7:
        case 9:
        case 17:
        case 19:
        case 26:
        case 257:
        case 272:
            return 1;
    }
    return 0;
}

static inline s32 is_group_c(ActorParticleDispatchOwnerContactLinks *actor) {
    switch (actor->type) {
        case 8:
        case 13:
        case 18:
            return 1;
    }
    return 0;
}

void Particle_UpdateTargetedAcceleration(AccelSteeringObj *particle) {
    AccelSteeringVec delta, direction;
    AccelSteeringVec *velocity;
    f32 accel, length, limit;

    if (particle->target != 0 && particle->distance > 1.0f) {
        Particle_SteerToward(particle, &particle->target->point);
        return;
    }
    accel = Menu_ExpandFloatHighWord(particle->link->params->accel);
    if (accel != 0.0f) {
        do {
            direction = particle->direction;
            Graphu64_ScaleVector(&delta, &direction, accel);
            velocity = &particle->velocity;
            Graphu64_AddVec3(velocity, velocity, &delta);
        } while (0);
        length = Gu_Sqrtf(particle->velocity.x * particle->velocity.x + particle->velocity.y * particle->velocity.y + particle->velocity.z * particle->velocity.z);
        limit = Menu_ExpandFloatHighWord(particle->link->params->limit);
        if (accel > 0.0f) {
            if (!(limit < length)) goto done;
        } else {
            if (!(length < limit)) goto done;
        }
        Graphu64_ScaleVector(velocity, &direction, limit);
done:;
    }
    Particle_UpdateSineMotion(particle, 1.0f);
}

void Particle_UpdateTypedMotion(Shared_Particle *particle)
{
  CVector3 offsetToTarget;
  CVector3 targetPosition;
  CVector3 currentDirection;
  CVector3 directionToTarget;
  CVector3 basisPoint;
  CQuatern currentDirectionQuaternion;
  CQuatern wantedDirectionQuaternion;
  CQuatern steeredDirectionQuaternion;
  Matrix steeringMatrix;
  CVector3 motionVectorStorage;

  CVector3 directionCopy;
  CVector3 *nearby_position;
  CVector3 *steeringDirection;
  f32 unusedFloat;
  f32 acceleratedVelocityY;
  CVector3 *transformedDirection;
  f32 acceleratedSpeedLimit;
  f32 attractionTargetHeight;
  f32 targetMotionSpeed;
  f32 specialVelocityY;
  f32 specialSpeedLimit;
  f32 targetBaseOffset;
  f32 steeringVelocityY;
  f32 steeringAngle;
  f32 ballisticMotionSpeed;
  f32 specialVelocityZ;
  f32 steeringVelocityZ;
  f32 acceleratedVelocityZ;
  f32 specialVelocityX;
  f32 unusedFloat1;
  f32 steeringVelocityX;
  f32 steeringAngleLimit;
  f32 acceleratedVelocityX;
  f32 neighborInfluence;
  f32 nearby_height;
  f32 nearby_scale;
  f32 nearby_random_max;
  f32 tracking_min;
  f32 tracking_max;
  f32 specialSpeed;
  f32 steeringSpeed;
  f32 acceleratedSpeed;
  f32 steeringBlend;
  s32 particleType;
  void *particleDescriptor;
  ParticleAttractionTargetView *attractionTarget;
  void *motionVector;
  ParticleAttractionTargetView *targetValue;
  void *unusedPointer2;
  void *velocity;
  void *nearbyActorCursor;
  ParticleNearbyActorView *nearbyActor;
  particleType = particle->inst.type;
  if (particleType == 295)
  {
    goto block_26;
  }
  if (particleType < 296)
  {
    if (particleType == 46)
    {
      goto block_46;
    }
    if (particleType < 47)
    {
      if (particleType == 11)
      {
        goto block_24;
      }
      if (particleType == 14)
      {
        goto block_26;
      }
      goto block_common;
    }
    if (particleType >= 97)
    {
      goto block_common;
    }
    if (particleType >= 95)
    {
      goto block_26;
    }
    goto block_common;
  }
  if (particleType == 1044)
  {
    goto block_540;
  }
  if (particleType < 1045)
  {
    if (particleType == 297)
    {
      goto block_24;
    }
    if (particleType == 1004)
    {
      goto block_26;
    }
    goto block_common;
  }
  if (particleType == 1069)
  {
    goto block_540;
  }
  if (particleType == 1204)
  {
    goto block_26;
  }
  goto block_common;
  block_46:
  nearbyActorCursor = g_transientPlayerList.actorList;

  if (nearbyActorCursor != ((void *) 0))
  {
    nearby_position = &targetPosition;
    velocity = (void *) (&particle->inst.velocity.x);
    do {
      nearby_scale = g_particleNeighborScale;
      nearby_random_max = g_particleNeighborRandomMaximum;
    } while (0);
    nearbyActor = nearbyActorCursor;
    do
    {
      nearby_height = nearbyActor->baseHeightOffset;
      targetPosition = nearbyActor->pos;
      targetPosition.y += nearby_height;
      targetPosition.y += Gobjinst_GetActorHeight(nearbyActorCursor) * nearby_scale;
      Graphu64_SubtractVectors(&offsetToTarget, nearby_position, &particle->inst.pos);
      neighborInfluence = Gu_Sqrtf(((offsetToTarget.x * offsetToTarget.x) + (offsetToTarget.y * offsetToTarget.y)) + (offsetToTarget.z * offsetToTarget.z));
      if (neighborInfluence < g_particleNeighborInfluenceThreshold)
      {
        neighborInfluence = g_particleNeighborInfluenceBase - (neighborInfluence * g_particleNeighborInfluenceScale);
        offsetToTarget.x *= neighborInfluence * Graphu64_RandomBetween(nearby_scale, nearby_random_max);
        offsetToTarget.y *= neighborInfluence * Graphu64_RandomBetween(nearby_scale, nearby_random_max);
        offsetToTarget.z *= neighborInfluence * Graphu64_RandomBetween(nearby_scale, nearby_random_max);
        Graphu64_SubtractVectors(velocity, velocity, &offsetToTarget);
      }
      nearbyActorCursor = nearbyActor->next;
      nearbyActor = nearbyActorCursor;
    }
    while (nearbyActorCursor != ((void *) 0));
  }
  attractionTarget = particle->target;
  attractionTargetHeight = InstHdr_GetActorBaseOffset(attractionTarget);
  targetPosition = attractionTarget->pos;
  targetPosition.y += attractionTargetHeight;
  Graphu64_SubtractVectors(&offsetToTarget, &targetPosition, &particle->inst.pos);
  tracking_min = g_particleTrackingMinimum;
  tracking_max = g_particleTrackingMaximum;
  offsetToTarget.x *= Graphu64_RandomBetween(tracking_min, tracking_max);
  offsetToTarget.y *= Graphu64_RandomBetween(tracking_min, tracking_max);
  offsetToTarget.z *= Graphu64_RandomBetween(tracking_min, tracking_max);
  motionVector = (void *) (&particle->inst.velocity.x);
  Graphu64_AddVec3(motionVector, motionVector, &offsetToTarget);
#if defined(VERSION_EU)
  Graphu64_ClampMotionLength(motionVector, Menu_ExpandFloatHighWord((s32) ((BallisticParamsHolder *)particle->desc)->parameters->speedLimitHi));
#else
  Graphu64_ClampMotionLength(motionVector, Menu_ExpandFloatHighWord((s32) ((BallisticParamsHolder *)particle->desc)->parameters->speedLimitHi));
#endif
  return;
  block_24:
  Particle_SteerSoundTrackingParticle(particle);

  return;
  block_540:
  Particle_SteerHoming(particle);

  return;
  block_26:
  Playerai_ApplyPlayerForces(&g_playerViewRenderContext, particle);

#if defined(VERSION_EU)
  targetMotionSpeed = Menu_ExpandFloatHighWord((s32) ((BallisticParamsHolder *)particle->desc)->parameters->motionSpeedHi);
#else
  targetMotionSpeed = Menu_ExpandFloatHighWord((s32) ((BallisticParamsHolder *)particle->desc)->parameters->motionSpeedHi);
#endif
  if (targetMotionSpeed != 0.0f)
  {
    motionVector = &motionVectorStorage;
    directionCopy = particle->direction;
    Graphu64_ScaleVector(motionVector, &directionCopy, targetMotionSpeed);
    motionVector = (void *) (&particle->inst.velocity.x);
    Graphu64_AddVec3(motionVector, motionVector, &motionVectorStorage);
    specialVelocityX = particle->inst.velocity.x;
    specialVelocityY = particle->inst.velocity.y;
    specialVelocityZ = particle->inst.velocity.z;
    specialSpeed = Gu_Sqrtf(((specialVelocityX * specialVelocityX) + (specialVelocityY * specialVelocityY)) + (specialVelocityZ * specialVelocityZ));
#if defined(VERSION_EU)
    specialSpeedLimit = Menu_ExpandFloatHighWord((s32) ((BallisticParamsHolder *)particle->desc)->parameters->speedLimitHi);
#else
    specialSpeedLimit = Menu_ExpandFloatHighWord((s32) ((BallisticParamsHolder *)particle->desc)->parameters->speedLimitHi);
#endif
    if (targetMotionSpeed > 0.0f)
    {
      if (!(specialSpeedLimit < specialSpeed))
      {
        goto after_special_clamp;
      }
    }
    else
      if (!(specialSpeed < specialSpeedLimit))
    {
      goto after_special_clamp;
    }
    Graphu64_ScaleVector(motionVector, &directionCopy, specialSpeedLimit);
    after_special_clamp:
    ;

    ;
  }
  Particle_UpdateSineMotion(particle, 1.0f);
  return;
  block_common:
  targetValue = particle->target;

  particleDescriptor = particle->desc;
  if (((targetValue != ((void *) 0)) && (particle->desc->flags & 0x40000)) && (((BallisticParamsHolder *)particle->desc)->steeringAngleLimit != 0))
  {
    targetBaseOffset = InstHdr_GetActorBaseOffset(targetValue);
    targetPosition = targetValue->pos;
    targetPosition.y += targetBaseOffset;
    targetPosition.y += Gobjinst_GetActorHeight(targetValue) * g_particleTrackingTargetHeightScale;
    Graphu64_SubtractVectors(&directionToTarget, &targetPosition, &particle->inst.pos);
    Graphu64_NormalizeVec3(&directionToTarget);
    wantedDirectionQuaternion = Graphu64_BuildDirectionQuaternion(&directionToTarget);
    steeringDirection = &particle->direction;
    currentDirectionQuaternion = Graphu64_BuildDirectionQuaternion(steeringDirection);
    currentDirection = particle->direction;
    Graphu64_NormalizeVec3(&currentDirection);
    steeringVelocityX = particle->inst.velocity.x;
    steeringVelocityY = particle->inst.velocity.y;
    steeringVelocityZ = particle->inst.velocity.z;
    steeringSpeed = Gu_Sqrtf(((steeringVelocityX * steeringVelocityX) + (steeringVelocityY * steeringVelocityY)) + (steeringVelocityZ * steeringVelocityZ));
    steeringAngle = Graphu64_ArcCos(((currentDirection.x * directionToTarget.x) + (currentDirection.y * directionToTarget.y)) + (currentDirection.z * directionToTarget.z));
    steeringAngleLimit = ((f32) ((BallisticParamsHolder *)particle->desc)->steeringAngleLimit) * g_particleBallisticParameterScale;
    steeringBlend = g_particleBallisticDefaultValue;
    if (steeringAngleLimit < steeringAngle)
    {
      steeringBlend = steeringAngleLimit / steeringAngle;
    }
    Graphu64_InterpolateQuaternionWithLinearFallback(&steeredDirectionQuaternion, steeringBlend, &currentDirectionQuaternion, &wantedDirectionQuaternion);
    MatrixFromQuaternion(&steeredDirectionQuaternion, &steeringMatrix);
    basisPoint.x = 0;
    basisPoint.y = 0;
    basisPoint.z = g_particleBallisticBasisZ;
    transformedDirection = steeringDirection;
    Graphu64_TransformPoint(&steeringMatrix, &basisPoint, transformedDirection);
    Graphu64_ScaleVector(&particle->inst.velocity.x, transformedDirection, steeringSpeed);
  }
  if (!(particle->flags & 0x70000))
  {
#if defined(VERSION_EU)
    ballisticMotionSpeed = Menu_ExpandFloatHighWord((s32) ((BallisticParamsHolder *)particle->desc)->parameters->motionSpeedHi);
#else
    ballisticMotionSpeed = Menu_ExpandFloatHighWord((s32) ((BallisticParamsHolder *)particle->desc)->parameters->motionSpeedHi);
#endif
    if (ballisticMotionSpeed != 0.0f)
    {
      motionVector = &motionVectorStorage;
    directionCopy = particle->direction;
      Graphu64_ScaleVector(motionVector, &directionCopy, ballisticMotionSpeed);
      motionVector = (void *) (&particle->inst.velocity.x);
      Graphu64_AddVec3(motionVector, motionVector, &motionVectorStorage);
      acceleratedVelocityX = particle->inst.velocity.x;
      acceleratedVelocityY = particle->inst.velocity.y;
      acceleratedVelocityZ = particle->inst.velocity.z;
      acceleratedSpeed = Gu_Sqrtf(((acceleratedVelocityX * acceleratedVelocityX) + (acceleratedVelocityY * acceleratedVelocityY)) + (acceleratedVelocityZ * acceleratedVelocityZ));
#if defined(VERSION_EU)
      acceleratedSpeedLimit = Menu_ExpandFloatHighWord((s32) ((BallisticParamsHolder *)particle->desc)->parameters->speedLimitHi);
#else
      acceleratedSpeedLimit = Menu_ExpandFloatHighWord((s32) ((BallisticParamsHolder *)particle->desc)->parameters->speedLimitHi);
#endif
      if (ballisticMotionSpeed > 0.0f)
      {
        if (!(acceleratedSpeedLimit < acceleratedSpeed))
        {
          goto after_normal_clamp;
        }
      }
      else
        if (!(acceleratedSpeed < acceleratedSpeedLimit))
      {
        goto after_normal_clamp;
      }
      Graphu64_ScaleVector(motionVector, &directionCopy, acceleratedSpeedLimit);
      after_normal_clamp:
      ;

      ;
    }
  }
  if (!(particle->flags & 0x30000))
  {
    Particle_UpdateSineMotion(particle, 1.0f);
  }
}

void Particle_DispatchOwnerContactLinks(ActorParticleDispatchOwnerContactLinks *actor) {
    ActorEmitterSource *owner;

    if (g_currentActorInstance == 0 || g_currentActorInstance->actorKind != 1) {
        return;
    }
    owner = actor->owner;
    if (owner != 0 && owner->actorKind == 1 && (owner->flags & 0x300000)) {
        if (is_group_a(actor)) {
            Link_DispatchActorLinks(g_currentActorInstance, 8, actor);
        }
        if (is_group_b(actor)) {
            Link_DispatchActorLinks(g_currentActorInstance, 4, actor);
        }
        if (is_group_c(actor)) {
            Link_DispatchActorLinks(g_currentActorInstance, 16, actor);
        }
    } else if (actor->descriptor->value == 1 || actor->descriptor->value == 4) {
        if (is_group_a(actor)) {
            Link_DispatchActorLinks(g_currentActorInstance, 128, actor);
        }
        if (is_group_b(actor)) {
            Link_DispatchActorLinks(g_currentActorInstance, 64, actor);
        }
        if (is_group_c(actor)) {
            Link_DispatchActorLinks(g_currentActorInstance, 0x100, actor);
        }
    }
}
