#include "Engine/Instance/gobjinst.h"
#include "Cache/cache_allocateresourceat.h"
#include "Weapons/player_movement_interfaces.h"
#include "Common/vector4f.h"
#include "Gobjinst/gobjinst_buildtargetaimorientation.h"
#include "Common/Lone/collision_current_actor.h"
#include "Common/sharedplayer.h"
#include "Common/level_actor.h"
#include "Common/listheader.h"
#include "types.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Engine/particle.h"
#include "Ai/player_ammo_gift.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
#include "Particle/ghot_dispatchattachmenteffects_data.h"
#include "Particle/particle_spawnchildeffect.h"
#include "Render/playerai_toggleforcemarker.h"
#include "Engine/graphics_math.h"
#include "Common/approachlocation.h"
#include "Engine/events.h"
#include "Particle/particle_spawneffectgroup.h"
#include "Common/triple.h"
#include "Common/shared_particleinstance.h"
#include "Common/weapon_screen_message_operations.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Common/soundvoicepool.h"
#include "include_asm.h"
#include "common.h"
#include "Common/resident_event_handler.h"
#include "Common/ballisticparams.h"
#include "Particle/particle_updatetypedmotion.h"
#include "Fx/normalize_vector.h"
#include "Audio/voice.h"
#include "Link/link_dispatchmatchingtriggers.h"
#include "Engine/Audio/voice.h"
#include "Common/game_session.h"
#include "Common/shared_gameslot.h"
#include "Common/math_helpers.h"
#include <platform_sdk.h>
#include "System/contact_effect.h"
#include "Fx/fx_drawcoloredribbon.h"
#include "Fx/fx_spawnimpactmark.h"
#include "Game/builddirectionmatrix.h"
#include "Render/particle_spawninterpolatedtrail.h"
#include "Engine/gregion.h"
#include "System/events_delivercontacteffect.h"
#include "Common/animationtriggerdefinition.h"
#include "Engine/Unicol/polycol.h"
#include "Ai/player.h"
#include "Camera/collision_sweep_views.h"
#include "Engine/Instance/gobjinst.h"
#include "Common/self.h"
#include "Common/rendersortrecord.h"
#include "Insthdr/insthdr_getactorshadowradius.h"
#include "Common/Lone/particle_pitch_matrix_scratch.h"
#include "Common/gameplay_round_rules.h"
#include "Common/gameplay_transition.h"
#include "Common/runtime_declarations.h"
#include "Common/gameplay_camera.h"
#include "Common/aiprofile.h"
#include "Ai/Player/player_buildplayerviewtransform.h"
#include "Graphu64/graphu64_buildlookatmatrix.h"
#include "Menu/Items/Scene/scene_registeractorinscenelists.h"
#include "Common/mtx.h"
#include "Common/world.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Engine/scene_sampleworldlighting.h"
#include "Render/player_controller_reset_views.h"
#include "Common/libsn_and_resident_callbacks.h"
#include "Rsp/random_direction_and_affine_math.h"
#include <PR/abi.h>
#include <PR/gbi.h>
#include "Scene/cache_requestresource.h"
#include "Engine/session.h"
#include "Common/cache_releaseresource.h"
#include "Engine/geometry.h"
#include "Scene/cache_allocateresourceat.h"
#include "Engine/map.h"
#include "Common/sessionhandlerrow.h"
#include "Anim/animation_frame.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Common/display.h"
#include "Gsky/gsky_findscreenmessage.h"
#include "Textload/textload_readtextureanimationinfo.h"
#include "Textload/textload_requesttexturevariationsync.h"
#include "Texture/textload_loadtextureframe.h"
#include "Texture/textload_loadtextureframetiles.h"
#include "Common/globals.h"
#include "Engine/Cache/list.h"
#include "Common/objb.h"
#include "Common/effectrender.h"
#include "Common/heap_arena_entry.h"
#include "Engine/defs.h"
#include "Render/setn64_getpacksection.h"
#include "Engine/gdynlight.h"
#include "Gobjinst/gameobject_movetoxzkeepheight.h"
#include "Render/weapon_initializechargeandstartupcues_data.h"
#include "Textload/textload_locatetextureresource.h"
#include "engine.h"
#if defined(VERSION_EU)
#include "common.h"
#endif
#if defined(VERSION_EU)
#include "Engine/Instance/gobjinst.h"
#endif
#include "Render/soundelement_playflatsound.h"
#include "Ui/X_files/x_plus.h"
#include "Ai/Player/playerai_buildforcemarkertransform.h"
#include "Particle/particle_haskindzeroentry.h"
#include "Common/particle_attachment_and_owner_views.h"
#include "Particle/particle_releaseownerlistoneeffects.h"
#include "Common/packedmeshmaterial.h"
#include "Particle/particle_spawninterpolatedtrail.h"
#include "Data/rest_source_records.h"
#include "libultra/ACTOR_STATE_TABLE_END_DATA.H"
#include "Engine/lighting.h"
#include "Ai/cbarrel.h"
#include "Ai/Devices/Movingai/movingai.h"
#include "Common/frustum.h"

/* PARTICLE_SPAWNCHILDEFFECT.CPP */


void Particle_FinishActorEffects(Shared_Particle *actor) {
    Player *state;
    struct Shared_ParticleDesc *owner;

    char *resource;

    if (((Shared_Particle *)(actor))->inst.type != 1044) {
        if (((Shared_Particle *)(actor))->inst.type == 1069) {
            state = Particle_GetEffectResource(actor);
            if (((Player *)(state))->ammoRewardAmount != 0 && Playerai_IsPlayerInactive(state) == 0) {
                Player_GiveAmmoWithMessage(state, ((Player *)(state))->ammoRewardType,
                               ((Player *)(state))->ammoRewardAmount);
            }
            goto reset_state;
        }
    } else {
reset_state:
        state = Particle_GetEffectResource(actor);
        ((Player *)(state))->ammoRewardAmount = 0;
        if (Playerai_IsPlayerInactive(state) == 0) {
            ((Player *)(state))->effectResetFlag = 1;
        }
    }

    if (((Shared_Particle *)(actor))->render.WallBehavior == 8 ||
        ((Shared_Particle *)(actor))->render.GroundBehavior == 8 ||
        ((Shared_Particle *)(actor))->render.InstanceBehavior == 8) {
        resource = ((Shared_Particle *)(actor))->owner;
        if (resource != 0 && *(u8 *)resource == 1 &&
            (((Shared_Actor *)(resource))->weaponFlags & 0x300000) != 0) {
            Player_SetPlayerState(((Shared_Actor *)(resource))->entity, resource, 2);
        }
    }

    Particle_StopSound(actor);
    owner = actor->desc;
    if (((struct Shared_ParticleDesc *)owner)->events->sounds[11] != 0xFFFF) {
        SoundElement_StopAudioBySecondaryValue((s32)actor);
    }
    if (((struct Shared_ParticleDesc *)owner)->events->sounds[13] != 0xFFFF) {
        SoundElement_StopAudioBySecondaryValue((s32)actor);
    }
}


static inline f32 offset_x(Shared_Particle *actor) {
    if (actor->desc->renderModel != 0) {
        return 0.0f;
    }
    return actor->rot.x;
}

static inline f32 offset_y(Shared_Particle *actor) {
    if (actor->desc->renderModel != 0) {
        return 0.0f;
    }
    return actor->rot.y;
}

void Particle_SpawnChildEffect(Shared_Particle *actor, s32 model, s32 spawnMode, s32 flags) {
    CQuatern rotation;
    CVector3 direction;
    CVector3 offset;
    CVector3 turned;
    CVector3 carried;
    CVector3 point;
    CVector3 moved;
    f32 matrix[16];
    char scratch[264];
    void *parent;

    if (actor->desc->flags & 0x10) {
        direction = g_particleZeroVector;
    } else {
        direction = actor->inst.velocity;
    }
    rotation = Graphu64_BuildDirectionQuaternion(&direction);
    if (offset_x(actor) == 0.0f && offset_y(actor) == 0.0f) {
        point = actor->inst.pos;
    } else {
        offset.x = -offset_x(actor);
        offset.y = -offset_y(actor);
        offset.z = 0.0f;
        BuildRollMatrix(matrix, *(f32 *)&actor->rot.z);
        Graphu64_TransformPoint(matrix, &offset, &turned);
        parent = Particle_ParentTransform((struct Shared_Particle *)actor, 0);
        if (parent != 0) {
            Graphu64_TransformPoint(parent, &turned, &carried);
        } else {
            carried = turned;
        }
        Graphu64_AddVec3(&moved, &carried, &actor->inst.pos);
        g_collisionCurrentActor = scratch;
        point = moved;
        g_collisionCurrentActor = &g_currentActorInstance;
    }
    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], actor, actor->owner, (s32 *)actor->ownerId, (s32)actor->target, model,
                  direction, rotation, point, 0, spawnMode, flags | (actor->flags & 0x200006));
}

/* PARTICLE_UPDATESINEMOTION.CPP */

/* Advance the two measured oscillator phases and apply their velocity deltas. */
void Particle_UpdateSineMotion(Shared_Particle *particle, f32 amplitudeScale) {
    CVector3 referenceAxis;
    CVector3 perpendicularAxis;
    Triple travelDirection;
    CVector3 previousSineOffset;
    CVector3 nextSineOffset;
    CVector3 sideAxis;
    f32 fadeInDuration;
    f32 nextSineAngleX;
    f32 nextSineAngleY;
    f32 particleAge;
    f32 motionAmplitude;
    s8 fadeInFrames;

    fadeInFrames = (particle)->desc->sineWave->fadeInFrames;
    motionAmplitude = g_particleSineMotionAmplitude;
    if (fadeInFrames != 0) {
        particleAge = (particle)->time;
        fadeInDuration = (f32) fadeInFrames;
        if (particleAge < fadeInDuration) {
            motionAmplitude = particleAge / fadeInDuration;
        }
    }
    motionAmplitude *= amplitudeScale;
    travelDirection = *(Triple *)&(particle)->direction;
    if ((particle)->sineAmplitudeX > 0.0f) {
        CVector3 *velocity;

        referenceAxis.x = 0.0f;
        referenceAxis.z = 0.0f;
        referenceAxis.y = g_particleSineMotionOffsetY;
        Graphu64_CrossVectors(&perpendicularAxis, &referenceAxis, (CVector3 *)&travelDirection);
        Graphu64_ScaleVector(&previousSineOffset, &perpendicularAxis, Gu_Sinf((particle)->sineAngleX) * (particle)->sineAmplitudeX * motionAmplitude);
        nextSineAngleX = (particle)->sineAngleX + ((particle)->sineAngleSpeedX * motionAmplitude * g_frameElapsedTime);
        (particle)->sineAngleX = nextSineAngleX;
        Graphu64_ScaleVector(&nextSineOffset, &perpendicularAxis, Gu_Sinf(nextSineAngleX) * (particle)->sineAmplitudeX * motionAmplitude);
        velocity = &(particle)->inst.velocity;
        Graphu64_SubtractVectors(velocity, velocity, &previousSineOffset);
        Graphu64_AddVec3((CVector3 *) velocity, (CVector3 *) velocity, (CVector3 *) &nextSineOffset);
    } else {
        (particle)->sineAngleX = (f32) ((particle)->sineAngleX + ((particle)->sineAngleSpeedX * motionAmplitude * g_frameElapsedTime));
    }
    if ((particle)->sineAmplitudeY > 0.0f) {
        referenceAxis.x = 0.0f;
        referenceAxis.z = 0.0f;
        referenceAxis.y = g_particleSineMotionTargetY;
        Graphu64_CrossVectors(&sideAxis, &referenceAxis, (CVector3 *)&travelDirection);
        Graphu64_CrossVectors(&perpendicularAxis, &sideAxis, (CVector3 *)&travelDirection);
        Graphu64_ScaleVector(&previousSineOffset, &perpendicularAxis, Gu_Sinf((particle)->sineAngleY) * (particle)->sineAmplitudeY * motionAmplitude);
        nextSineAngleY = (particle)->sineAngleY + ((particle)->sineAngleSpeedY * motionAmplitude * g_frameElapsedTime);
        (particle)->sineAngleY = nextSineAngleY;
        Graphu64_ScaleVector(&nextSineOffset, &perpendicularAxis, Gu_Sinf(nextSineAngleY) * (particle)->sineAmplitudeY * motionAmplitude);
        Graphu64_SubtractVectors(&(particle)->inst.velocity, &(particle)->inst.velocity, &previousSineOffset);
        Graphu64_AddVec3(&(particle)->inst.velocity, &(particle)->inst.velocity, &nextSineOffset);
        return;
    }
    (particle)->sineAngleY = (f32) ((particle)->sineAngleY + ((particle)->sineAngleSpeedY * motionAmplitude * g_frameElapsedTime));
}

/* PARTICLE_UPDATETYPEDMOTION.CPP */

static inline void makeImpulse(CVector3 *input,f32 scale,CVector3 *out){Graphu64_ScaleVector(out,input,scale);}
static inline void addImpulse(CVector3 *v,CVector3 *impulse){Graphu64_AddVec3(v,v,impulse);}
void Particle_SteerSoundTrackingParticle(void *particle) {
    Shared_Particle *steeringParticle=particle;
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
    LevelActor *target;
    CVector3 *steeredDirection;
    CLoopingSoundData *sound;

    if (steeringParticle->flags & 0x10000) {
        if (steeringParticle->sound != 0) {
            SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), steeringParticle->sound);
            steeringParticle->sound = 0;
        }
    } else {
        id=1840;sound = steeringParticle->sound;
        if (sound != 0) {
            if ((sound->state != id) || (sound->value == -1)) {
                Particle_StopSound(steeringParticle);
                goto block_7;
            }
        } else {
block_7:
            steeringParticle->sound = SoundVoicePool_PlaySpatialSound(SoundVoicePool_GetGlobalState(), 1840, &steeringParticle->inst.pos, &steeringParticle->inst.pos, -1);
        }
        target = steeringParticle->target;
        if ((target != 0) && (steeringParticle->time > g_particleAttractionDelay)) {
            direction = &steeringParticle->direction;
            currentDirectionQuaternion = Graphu64_BuildDirectionQuaternion(direction);
            initialVelocityX = steeringParticle->inst.velocity.x;
            initialVelocityY = steeringParticle->inst.velocity.y;
            initialVelocityZ = steeringParticle->inst.velocity.z;
            initialSpeed = Gu_Sqrtf((initialVelocityX * initialVelocityX) + (initialVelocityY * initialVelocityY) + (initialVelocityZ * initialVelocityZ));

            targetPosition = target->attachmentPosition;
            Graphu64_SubtractVectors(&offsetToTarget, &targetPosition, &steeringParticle->inst.pos);
            amount = Gu_Sqrtf((offsetToTarget.x * offsetToTarget.x) + (offsetToTarget.y * offsetToTarget.y) + (offsetToTarget.z * offsetToTarget.z));
            if (amount < g_particleAttractionMinimumDistance) {
                steeredDirectionQuaternion = Graphu64_BuildDirectionQuaternion(&offsetToTarget);
                MatrixFromQuaternion(&steeredDirectionQuaternion.x, steeringMatrix.m);
                basisPoint.x = 0;
                basisPoint.y = 0;
                basisPoint.z = g_particleAttractionBasisZ;
                Graphu64_TransformPoint(&steeringMatrix, &basisPoint, direction);
                Graphu64_ScaleVector(&steeringParticle->inst.velocity, direction, initialSpeed);
                return;
            }
            if (g_particleAttractionFarDistance < amount) {
                targetPosition.y += g_particleAttractionMinimumDistance;
                Graphu64_SubtractVectors(&offsetToTarget, &targetPosition, &steeringParticle->inst.pos);
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
            Graphu64_ScaleVector(&steeringParticle->inst.velocity, steeredDirection, initialSpeed);
            goto block_21;
        }
block_21:
        scale = Menu_ExpandFloatHighWord((s32) steeringParticle->desc->motion->acceleration);
        if (scale != 0.0f) {
            accelerationDirection = steeringParticle->direction;
            makeImpulse(&accelerationDirection,scale,&impulseVector);
            addImpulse(&steeringParticle->inst.velocity,&impulseVector);
            acceleratedVelocity=&steeringParticle->inst.velocity;
            acceleratedVelocityX = steeringParticle->inst.velocity.x;
            acceleratedVelocityY = steeringParticle->inst.velocity.y;
            acceleratedVelocityZ = steeringParticle->inst.velocity.z;
            acceleratedSpeed = Gu_Sqrtf((acceleratedVelocityX * acceleratedVelocityX) + (acceleratedVelocityY * acceleratedVelocityY) + (acceleratedVelocityZ * acceleratedVelocityZ));
            speedLimit = Menu_ExpandFloatHighWord((s32) steeringParticle->desc->motion->speedLimit);
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


struct EffectSystem; struct Shared_Particle; extern void Particle_Release(struct EffectSystem *owner, struct Shared_Particle *releasedEffect);
/* Steers a homing particle (sound 0x8AC) at its target, or straight ahead when it has none: keeps its loop
 * sound alive, drops the target after g_homingParticleSteeringStartTime seconds, ends the particle when it gets close enough,
 * otherwise turns the direction toward the target by a blend rate chosen from the turn angle and age,
 * resets the velocity along the new direction and applies the descriptor's acceleration (clamped to its
 * top speed). */
void Particle_SteerHoming(Shared_Particle *particle) {
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
    f32 blendRate;
    f32 acceleration;
    f32 limit;
    f32 newSpeed;
    s32 loopSoundId;
    CVector3 *velocity;
    CLoopingSoundData *sound;
    q78 = Graphu64_BuildDirectionQuaternion(&particle->direction);
    speed = Gu_Sqrtf(particle->inst.velocity.x * particle->inst.velocity.x + particle->inst.velocity.y * particle->inst.velocity.y +
                             particle->inst.velocity.z * particle->inst.velocity.z);
    owner = FIELD(void *, FIELD(void *, particle, 300), 472);
    loopSoundId = 2220;
    sound = particle->sound;
    if (sound != 0) {
        if ((sound->state != loopSoundId) || (sound->value == -1)) {
            Particle_StopSound(particle);
            goto create_sound;
        }
    } else {
create_sound:
        particle->sound = SoundVoicePool_PlaySpatialSound(SoundVoicePool_GetGlobalState(), 2220, &particle->inst.pos, &particle->inst.pos, -1);
    }
    if (particle->target != 0) {
        if (particle->time >= g_homingParticleSteeringStartTime) {
            particle->target = 0;
        }
    }
    if (FIELD(void *, particle, 308) == 0) {
        v58.x = 0;
        v58.y = 0;
        v58.z = g_homingParticleForwardZ;
        Player_TransformPointByViewOrOwnerMatrix(owner, &v58);
        Graphu64_SubtractVectors(&v68, &v58, &particle->inst.pos);
        distance = Gu_Sqrtf(v68.x * v68.x + v68.y * v68.y + v68.z * v68.z);
        if (distance < g_homingParticleNearTargetDistance && particle->time > g_homingParticleNearTargetDelay) {
            Particle_DispatchActorContactEvents(particle);
            Particle_Release(g_actorParticleEffectSystem, particle);
            Particle_StopSound(particle);
            return;
        }
    } else {
        v18 = FIELD(CVector3, FIELD(void *, particle, 308), 8);
        v18.y += Gobjinst_GetActorHeight(FIELD(void *, particle, 308)) * g_homingParticleTargetHeightScale;
        Graphu64_SubtractVectors(&v68, &v18, &particle->inst.pos);
    }
    v28 = v68;
    Graphu64_NormalizeVec3(&v28);
    q88 = Graphu64_BuildDirectionQuaternion(&v28);
    Graphu64_NormalizeQuaternion(&q88);
    Graphu64_NormalizeQuaternion(&q78);
    Graphu64_NormalizeVec3(&v28);
    v38 = particle->direction;
    Graphu64_NormalizeVec3(&v38);
    angle = Graphu64_ArcCos(v28.x * v38.x + v28.y * v38.y + v28.z * v38.z);
    blendRate = 0.0f;
    if (!(particle->time < g_homingParticleTrackingDelay)) {
        blendRate = g_homingParticleAcquiredTurnRate;
        if ((angle < g_homingParticleSteeringAngleThreshold && g_homingParticleAcquisitionDelay < particle->time) || particle->target != 0) {
            blendRate = g_homingParticleDefaultTurnRate;
        }
    }
    Graphu64_InterpolateQuaternionWithLinearFallback(&q98, blendRate, &q78, &q88);
    MatrixFromQuaternion(&q98, mA8.m);
    direction = &particle->direction;
    v48.x = 0;
    v48.y = 0;
    v48.z = g_homingParticleSteeringBasisZ;
    Graphu64_TransformPoint(&mA8, &v48, direction);
    velocity = &particle->inst.velocity;
    Graphu64_ScaleVector(velocity, direction, speed);
    if (particle->time >= g_homingParticleMotionStartTime) {
        particle->render.WallBehavior = 0;
        particle->render.GroundBehavior = 0;
    }
    acceleration = Menu_ExpandFloatHighWord((s32)particle->desc->motion->acceleration);
    if (acceleration != 0.0f) {
        vF8 = particle->direction;
        makeImpulse(&vF8, acceleration, &vE8);
        addImpulse(velocity, &vE8);
        newSpeed = Gu_Sqrtf(particle->inst.velocity.x * particle->inst.velocity.x + particle->inst.velocity.y * particle->inst.velocity.y +
                                  particle->inst.velocity.z * particle->inst.velocity.z);
        limit = Menu_ExpandFloatHighWord((s32)particle->desc->motion->speedLimit);
        if (acceleration > 0.0f) {
            if (!(limit < newSpeed)) goto after_clamp;
        } else {
            if (!(newSpeed < limit)) goto after_clamp;
        }
        Graphu64_ScaleVector(velocity, &vF8, limit);
    after_clamp:;
    }
    Particle_UpdateSineMotion(particle, 1.0f);
}

/* Steers a homing particle toward goal: snaps onto it within 51.2 units, otherwise turns its heading
   toward it (harder as it closes in), keeps its speed along the new heading and applies its acceleration
   up to the speed limit before moving it. */
void Particle_SteerToward(Shared_Particle *particle, CVector3 *goal) {
    CVector3 offset;
    CVector3 forward;
    CQuatern current;
    CQuatern wanted;
    CQuatern turned;
    f32 rotation[16];
    CVector3 impulse;
    CVector3 heading;
    f32 distance;
    f32 speed;
    f32 blend;
    f32 acceleration;
    f32 newSpeed;
    f32 limit;
    CVector3 *vel;

    Graphu64_SubtractVectors(&offset, goal, &particle->inst.pos);
    distance = Gu_Sqrtf((offset.x * offset.x) + (offset.y * offset.y) + (offset.z * offset.z));
    if (distance <= 51.199997f) {
        particle->inst.pos = *goal;
        return;
    }
    Graphu64_NormalizeVec3(&offset.x);
    wanted = Graphu64_BuildDirectionQuaternion(&offset.x);
    current = Graphu64_BuildDirectionQuaternion(&particle->direction.x);
    speed = Gu_Sqrtf((particle->inst.velocity.x * particle->inst.velocity.x) + (particle->inst.velocity.y * particle->inst.velocity.y) + (particle->inst.velocity.z * particle->inst.velocity.z));
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
    Graphu64_ScaleVector(&particle->inst.velocity, &particle->direction, speed);
    acceleration = Menu_ExpandFloatHighWord(particle->desc->motion->acceleration);
    vel = &particle->inst.velocity;
    if (acceleration != 0.0f) {
        heading = particle->direction;
        makeImpulse(&heading, acceleration, &impulse);
        addImpulse(vel, &impulse);
        newSpeed = Gu_Sqrtf((particle->inst.velocity.x * particle->inst.velocity.x) + (particle->inst.velocity.y * particle->inst.velocity.y) + (particle->inst.velocity.z * particle->inst.velocity.z));
        limit = Menu_ExpandFloatHighWord(particle->desc->motion->speedLimit);
        if (acceleration > 0.0f) {
            if (!(limit < newSpeed)) goto skip;
        } else if (!(newSpeed < limit)) goto skip;
        Graphu64_ScaleVector(vel, &heading, limit);
    skip:;
    }
    Particle_UpdateSineMotion(particle, 1.0f);
}

/* Reports an actor to the active collision state g_currentActorInstance when that state is of kind 1: an actor whose owner is a kind 1 object flagged 0x300000 is reported with bit 8, 4 or 0x10 for each of three type groups its type belongs to, and otherwise an actor whose descriptor is of kind 1 or 4 is reported with bit 0x80, 0x40 or 0x100 for the same groups, each through Link_DispatchActorLinks. */




static inline s32 is_group_a(Shared_Particle *actor) {
    switch (actor->inst.type) {
        case 2:
        case 86:
        case 273:
        case 294:
            return 1;
    }
    return 0;
}

static inline s32 is_group_b(Shared_Particle *actor) {
    switch (actor->inst.type) {
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

static inline s32 is_group_c(Shared_Particle *actor) {
    switch (actor->inst.type) {
        case 8:
        case 13:
        case 18:
            return 1;
    }
    return 0;
}

void Particle_UpdateTargetedAcceleration(Shared_Particle *particle) {
    CVector3 delta, direction;
    CVector3 *velocity;
    f32 accel, length, limit;

    if (particle->target != 0 && particle->time > 1.0f) {
        Particle_SteerToward(particle, &particle->target->position0);
        return;
    }
    accel = Menu_ExpandFloatHighWord(particle->desc->motion->acceleration);
    if (accel != 0.0f) {
        do {
            direction = particle->direction;
            Graphu64_ScaleVector(&delta, &direction, accel);
            velocity = &particle->inst.velocity;
            Graphu64_AddVec3(velocity, velocity, &delta);
        } while (0);
        length = Gu_Sqrtf(particle->inst.velocity.x * particle->inst.velocity.x + particle->inst.velocity.y * particle->inst.velocity.y + particle->inst.velocity.z * particle->inst.velocity.z);
        limit = Menu_ExpandFloatHighWord(particle->desc->motion->speedLimit);
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
  CVector3 *nearbyPosition;
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
  f32 nearbyHeight;
  f32 nearbyScale;
  f32 nearbyRandomMax;
  f32 trackingMin;
  f32 trackingMax;
  f32 specialSpeed;
  f32 steeringSpeed;
  f32 acceleratedSpeed;
  f32 steeringBlend;
  s32 particleType;
  void *particleDescriptor;
  LevelActor *attractionTarget;
  void *motionVector;
  LevelActor *targetValue;
  void *unusedPointer2;
  void *velocity;
  void *nearbyActorCursor;
  Player *nearbyActor;
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
    nearbyPosition = &targetPosition;
    velocity = (void *) (&particle->inst.velocity.x);
    do {
      nearbyScale = g_particleNeighborScale;
      nearbyRandomMax = g_particleNeighborRandomMaximum;
    } while (0);
    nearbyActor = nearbyActorCursor;
    do
    {
      nearbyHeight = nearbyActor->actorParts[0].eyeHeight;
      targetPosition = nearbyActor->pos;
      targetPosition.y += nearbyHeight;
      targetPosition.y += Gobjinst_GetActorHeight(nearbyActorCursor) * nearbyScale;
      Graphu64_SubtractVectors(&offsetToTarget, nearbyPosition, &particle->inst.pos);
      neighborInfluence = Gu_Sqrtf(((offsetToTarget.x * offsetToTarget.x) + (offsetToTarget.y * offsetToTarget.y)) + (offsetToTarget.z * offsetToTarget.z));
      if (neighborInfluence < g_particleNeighborInfluenceThreshold)
      {
        neighborInfluence = g_particleNeighborInfluenceBase - (neighborInfluence * g_particleNeighborInfluenceScale);
        offsetToTarget.x *= neighborInfluence * Graphu64_RandomBetween(nearbyScale, nearbyRandomMax);
        offsetToTarget.y *= neighborInfluence * Graphu64_RandomBetween(nearbyScale, nearbyRandomMax);
        offsetToTarget.z *= neighborInfluence * Graphu64_RandomBetween(nearbyScale, nearbyRandomMax);
        Graphu64_SubtractVectors(velocity, velocity, &offsetToTarget);
      }
      nearbyActorCursor = nearbyActor->next;
      nearbyActor = nearbyActorCursor;
    }
    while (nearbyActorCursor != ((void *) 0));
  }
  attractionTarget = particle->target;
  attractionTargetHeight = InstHdr_GetActorBaseOffset(attractionTarget);
  targetPosition = attractionTarget->position0;
  targetPosition.y += attractionTargetHeight;
  Graphu64_SubtractVectors(&offsetToTarget, &targetPosition, &particle->inst.pos);
  trackingMin = g_particleTrackingMinimum;
  trackingMax = g_particleTrackingMaximum;
  offsetToTarget.x *= Graphu64_RandomBetween(trackingMin, trackingMax);
  offsetToTarget.y *= Graphu64_RandomBetween(trackingMin, trackingMax);
  offsetToTarget.z *= Graphu64_RandomBetween(trackingMin, trackingMax);
  motionVector = (void *) (&particle->inst.velocity.x);
  Graphu64_AddVec3(motionVector, motionVector, &offsetToTarget);
#if defined(VERSION_EU)
  Graphu64_ClampMotionLength(motionVector, Menu_ExpandFloatHighWord((s32) particle->desc->motion->speedLimit));
#else
  Graphu64_ClampMotionLength(motionVector, Menu_ExpandFloatHighWord((s32) particle->desc->motion->speedLimit));
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
  targetMotionSpeed = Menu_ExpandFloatHighWord((s32) particle->desc->motion->acceleration);
#else
  targetMotionSpeed = Menu_ExpandFloatHighWord((s32) particle->desc->motion->acceleration);
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
    specialSpeedLimit = Menu_ExpandFloatHighWord((s32) particle->desc->motion->speedLimit);
#else
    specialSpeedLimit = Menu_ExpandFloatHighWord((s32) particle->desc->motion->speedLimit);
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
  if (((targetValue != ((void *) 0)) && (particle->desc->flags & 0x40000)) && (particle->desc->steeringAngleLimit != 0))
  {
    targetBaseOffset = InstHdr_GetActorBaseOffset(targetValue);
    targetPosition = targetValue->position0;
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
    steeringAngleLimit = ((f32) particle->desc->steeringAngleLimit) * g_particleBallisticParameterScale;
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
    ballisticMotionSpeed = Menu_ExpandFloatHighWord((s32) particle->desc->motion->acceleration);
#else
    ballisticMotionSpeed = Menu_ExpandFloatHighWord((s32) particle->desc->motion->acceleration);
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
      acceleratedSpeedLimit = Menu_ExpandFloatHighWord((s32) particle->desc->motion->speedLimit);
#else
      acceleratedSpeedLimit = Menu_ExpandFloatHighWord((s32) particle->desc->motion->speedLimit);
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

void Particle_DispatchOwnerContactLinks(Shared_Particle *actor) {
    LevelActor *owner;

    if (g_currentActorInstance.instance0 == 0 || ((LevelActor *)g_currentActorInstance.instance0)->kind != 1) {
        return;
    }
    owner = (LevelActor *)actor->owner;
    if (owner != 0 && owner->kind == 1 && (owner->flags & 0x300000)) {
        if (is_group_a(actor)) {
            Link_DispatchActorLinks(g_currentActorInstance.instance0, 8, actor);
        }
        if (is_group_b(actor)) {
            Link_DispatchActorLinks(g_currentActorInstance.instance0, 4, actor);
        }
        if (is_group_c(actor)) {
            Link_DispatchActorLinks(g_currentActorInstance.instance0, 16, actor);
        }
    } else if (actor->inst.definition->kind == 1 || actor->inst.definition->kind == 4) {
        if (is_group_a(actor)) {
            Link_DispatchActorLinks(g_currentActorInstance.instance0, 128, actor);
        }
        if (is_group_b(actor)) {
            Link_DispatchActorLinks(g_currentActorInstance.instance0, 64, actor);
        }
        if (is_group_c(actor)) {
            Link_DispatchActorLinks(g_currentActorInstance.instance0, 0x100, actor);
        }
    }
}

/* Keep this source unit's macros local to its body. */
#undef FIELD

/* PARTICLE.CPP */

/* Updates a particle for one frame: halves the frame step for particles owned by a slowed object, measures its bounding
 * box, kills it or bounces it off its target when its type's rule says so (the German cartridge has a gentler rule
 * table), advances its spin and size (growing towards a capped target size, or dying when a size goes negative), lets
 * nearby players react to it, and when it moves or falls probes the ground through Collision_ProbeGround_de, orients itself to the
 * surface it hit and runs the collision responses its descriptor allows. g_frameElapsedTime (the frame step) is restored on
 * every exit after the early time check. */





void Particle_DispatchOwnerContactLinks(Shared_Particle *actor);

void Particle_HandleInitialMaterialContact(Shared_Particle *particle);

void Particle_HandleTypedContact(Shared_Particle *particle);

void Particle_HandleSelectedSurfaceContact(Shared_Particle *particle);

void Particle_HandleMaterialContact(Shared_Particle *particle);

void Particle_HitTarget(void *particle);

void Particle_ApplyImpactResponse(Shared_Particle *particle);




void Particle_SpawnInterpolatedTrail(Shared_Particle *actor);

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


/* Picks an animation slot from a global mode, then plays the slot's effect, spawns its object at the owner or a fixed position, plays its sound, and flags the owner. */


struct EffectSystem; struct Shared_Particle; extern void Particle_Release(struct EffectSystem *owner, struct Shared_Particle *releasedEffect);
/* Picks an animation slot from a global mode, then plays the slot's effect, spawns its object at the owner or a fixed position, plays its sound, and flags the owner. Adapted from Particle_HandleMaterialContact, with the slot chosen by a switch on g_particleContactMode (the extra case below 7 that shares the default body is needed for the decision tree; its value is not recoverable), the constant triple, one argument, the dropped Graphu64_ScaleVector call, and the final test changed. */





extern CVector3 g_particleTertiaryContactPosition;

extern CVector3 g_particleSecondaryContactPosition;

struct Triangle; extern s32 Region_TestPolygonSlopeFlag(struct Triangle *polygon);



/* Per-frame step of one live particle: sizes its culling box, resolves target hit and death, grows and spins it,
 * applies influence to nearby players, then runs the move and collision passes. */
void Particle_Update(Shared_Particle *particle) {
    Box bounds;
    LevelActor *owner;
    LevelActor *target;
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
    owner = (LevelActor *)particle->owner;
    savedStep = g_frameElapsedTime;
    if (particle->time < 0.0f) {
        return;
    }
    if (owner != NULL && owner->kind == 1 && (owner->flags & 0x300000) && ((Player *)owner->controller) != NULL &&
        (((Player *)owner->controller)->reactionFlags & 0x2000)) {
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
                if (target->active == 0) {
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
                if (particle->flags & PARTICLE_FLAG_MOVES_AGAINST_DIRECTION) {
                    die = 1;
                } else if (!(target->flags & 0x100)) {
                    die = 1;
                } else if (target->flags & 0x300000) {
                    die = (f32)target->active <= 0.0f;
                } else {
                    die = target->behaviorFlags & 0x20;
                }
#endif
                bounce = 0;
                break;
            case 11:
                die = 0;
                if (target->animationMarker != 33 || !(target->flags & 0x100)) {
                    bounce = 1;
                }
                break;
            case 4:
                die = 0;
                if (target->animationMarker != 32 || !(target->flags & 0x100)) {
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
            if (particle->flags & PARTICLE_FLAG_MOVES_AGAINST_DIRECTION) {
                particle->inst.velocity.x = -particle->direction.x;
                particle->inst.velocity.z = -particle->direction.z;
            } else {
                particle->inst.velocity.x = 0.0f;
                particle->inst.velocity.z = 0.0f;
            }
            particle->inst.region = 0;
            particle->render.dwFlags &= ~0x4000;
            if (bounce) {
                particle->life = 1;
            }
        }
    }
    if (particle->flags & 0x40000) {
        if (Unicol_MoveActorWithCollision(particle, particle->inst.pos, &particle->render.dwFlags) && (*(s32 *)g_currentActorInstance.padB4) != 0) {
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
            Particle_Release(&g_actorParticleEffectSystem[0], particle);
            ((void (*)(Shared_Particle *))Particle_StopSound)(particle);
            g_frameElapsedTime = savedStep;
            return;
        }
    }
    particle->rot.x += particle->rotSpeed.x * g_frameElapsedTime;
    particle->rot.y += particle->rotSpeed.y * g_frameElapsedTime;
    particle->rot.z += particle->rotSpeed.z * g_frameElapsedTime;
    (*(CVector3 *)&g_collisionCurrentActor->particleVelocity) = particle->inst.velocity;
    Particle_DispatchSpatialContactEvents(particle);
    influenceRange = particle->desc->playerContactRadius;
    if (!(influenceRange <= 0.0f)) {
        influenceRange *= 10.24f;
        influenceRange *= influenceRange;
        for (player = g_transientPlayerList.actorList; player != NULL;) {
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
    if ((particle->render.GravityAcceleration == 0.0f || (particle->inst.pos.y == 0.0f && particle->render.GravityAcceleration < 0.0f)) &&
        particle->inst.velocity.x * particle->inst.velocity.x + particle->inst.velocity.y * particle->inst.velocity.y +
                particle->inst.velocity.z * particle->inst.velocity.z <
            0.001f) {
        g_frameElapsedTime = savedStep;
        return;
    }
    if (!(particle->flags & 0x72000)) {
        die = Unicol_MoveActorWithCollision(particle, particle->inst.pos, &particle->render.dwFlags);
        if (particle->inst.instanceFlags & 0x1000) {
            particle->flags |= 4;
        } else {
            particle->flags &= ~4;
        }
        if (particle->inst.type == 104 && g_currentActorInstance.instance0 != NULL) {
            particle->target = g_currentActorInstance.instance0;
        }
        if (die) {
            if (g_currentActorInstance.instance0 != NULL) {
                Graphu64_SubtractVectors(&particle->direction, &particle->inst.pos, &(*(CVector3 *)&g_currentActorInstance.vec8));
            } else if (g_currentActorInstance.instance88 != 0) {
                Graphu64_SubtractVectors(&particle->direction, &particle->inst.pos, &(*(CVector3 *)&g_currentActorInstance.vec90));
            } else if (g_currentActorInstance.contactFlags9C != 0) {
                Graphu64_SubtractVectors(&particle->direction, &particle->inst.pos, &(*(CVector3 *)g_currentActorInstance.padA0));
            } else if ((*(s32 *)g_currentActorInstance.padB4) != 0) {
                Graphu64_SubtractVectors(&particle->direction, &particle->inst.pos, &(*(CVector3 *)(g_currentActorInstance.padB4 + 4)));
                if (particle->space == PARTICLE_ALIGN_WORLD) {
                    particle->space = PARTICLE_ALIGN_FLOOR;
                }
            } else if (g_currentActorInstance.instanceValueC4 != 0) {
                Graphu64_SubtractVectors(&particle->direction, &particle->inst.pos, &(*(CVector3 *)&g_currentActorInstance.vecC8));
            }
            Graphu64_NormalizeVec3(&particle->direction);
        }
        Particle_DispatchOwnerContactLinks(particle);
        if (g_currentActorInstance.instanceValueC4 != 0) {
            Particle_HandleTypedContact(particle);
        }
        if (particle->flags & 0x100) {
            if (g_currentActorInstance.contactFlags9C != 0) {
                if (!(particle->desc->flags & 0x10000000)) {
                    Particle_HandleInitialMaterialContact(particle);
                }
                if (particle->desc->flags & 0x800) {
                    particle->render.WallBehavior = 1;
                }
            }
            if (particle->flags & 0x100) {
                if (g_currentActorInstance.instance0 != NULL) {
                    if ((particle->render.dwFlags & 0x4000) && ((LevelActor *)g_currentActorInstance.instance0)->kind == 0) {
                        Particle_ApplyImpactResponse(particle);
                    } else {
                        Particle_HitTarget(particle);
                    }
                    if (particle->desc->flags & 0x800) {
                        particle->render.WallBehavior = 1;
                    }
                }
                if ((particle->flags & 0x100) && g_currentActorInstance.contactFlagsB0 != 0 && !(particle->desc->flags & 0x20000000)) {
                    if (g_currentActorInstance.contactFlagsB0 == 1) {
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
    CQuatern rotation;
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
            Events_DeliverContactEffect(particle, particle, effectId, -1, *(CVector3 *)&(g_particlePrimaryContactPosition), *(ContactEffectStyle *)&(pair));
        }
        if (kind != 0xFFFF) {
            if ((particle->desc->flags & 0x10) != 0) {
                position = g_particleZeroVector;
            } else {
                position = particle->inst.velocity;
            }
            rotation = Graphu64_BuildDirectionQuaternion(&position);
            Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], particle,
                          particle->owner,
                          (s32 *)particle->ownerId,
                          (s32)particle->target, kind,
                          position, rotation, g_particlePrimaryContactPosition, 0,
                          g_particlePrimaryContactRoom,
                          (particle->flags & 0x200006) | 1);
        }
        if (sound != 0xFFFF) {
            SoundElement_PlaySoundAtPosition((s16)sound, g_particlePrimaryContactPosition, 0, -1);
        }
    }
skip_effects:
    Graphu64_ScaleVector(&particle->rotSpeed, &particle->rotSpeed,
                  particle->render.GroundFriction);
    particle->flags |= 0x400;
    if (particle->render.WallBehavior == 1) {
        Particle_Release(&g_actorParticleEffectSystem[0], particle);
        Particle_StopSound(particle);
    }
}

void Particle_HandleTypedContact(Shared_Particle *particle) {
    struct IntPair pair;
    CQuatern rotation;
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
        Events_DeliverContactEffect(particle, particle, effectId, -1, *(CVector3 *)&(g_particleTertiaryContactPosition), *(ContactEffectStyle *)&(pair));
    }
    if (kind != 0xFFFF) {
        if ((particle->desc->flags & 0x10) != 0) {
            position = g_particleZeroVector;
        } else {
            position = particle->inst.velocity;
        }
        rotation = Graphu64_BuildDirectionQuaternion(&position);
        Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], particle,
                      particle->owner,
                      (s32 *)particle->ownerId,
                      (s32)particle->target, kind,
                      position, rotation, g_particleTertiaryContactPosition, 0,
                      -5,
                      (particle->flags & 0x200006) | 1);
    }
    if (sound != 0xFFFF) {
        SoundElement_PlaySoundAtPosition((s16)sound, g_particleTertiaryContactPosition, 0, -1);
    }
    particle->flags |= 0x200;
    if ((particle->desc->flags & 0x20000) != 0) {
        Particle_Release(&g_actorParticleEffectSystem[0], particle);
        Particle_StopSound(particle);
    }
}

void Particle_HandleSelectedSurfaceContact(Shared_Particle *particle) {
    struct IntPair pair;
    CQuatern rotation;
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
        Events_DeliverContactEffect(particle, particle, effectId, -1, *(CVector3 *)&(g_particleSecondaryContactPosition), *(ContactEffectStyle *)&(pair));
    }
    if (kind != 0xFFFF) {
        if ((particle->desc->flags & 0x10) != 0) {
            position = g_particleZeroVector;
        } else {
            position = particle->inst.velocity;
        }
        rotation = Graphu64_BuildDirectionQuaternion(&position);
        Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], particle,
                      particle->owner,
                      (s32 *)particle->ownerId,
                      (s32)particle->target, kind,
                      position, rotation, g_particleSecondaryContactPosition, 0,
                      -3,
                      (particle->flags & 0x200006) | 1);
    }
    if (sound != 0xFFFF) {
        SoundElement_PlaySoundAtPosition((s16)sound, g_particleSecondaryContactPosition, 0, -1);
    }
    Graphu64_ScaleVector(&particle->rotSpeed, &particle->rotSpeed,
                  particle->render.GroundFriction);
    particle->flags |= 0x200;
    if (particle->render.GroundBehavior == 1) {
        Particle_Release(&g_actorParticleEffectSystem[0], particle);
        Particle_StopSound(particle);
    }
}

void Particle_HandleMaterialContact(Shared_Particle *particle) {
    struct IntPair pair;
    CQuatern rotation;
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
        Events_DeliverContactEffect(particle, particle, effectId, -1, *(CVector3 *)&(g_particleSecondaryContactPosition), *(ContactEffectStyle *)&(pair));
    }
    if (kind != 0xFFFF) {
        if ((particle->desc->flags & 0x10) != 0) {
            position = g_particleZeroVector;
        } else {
            position = particle->inst.velocity;
        }
        rotation = Graphu64_BuildDirectionQuaternion(&position);
        Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], particle,
                      particle->owner,
                      (s32 *)particle->ownerId,
                      (s32)particle->target, kind,
                      position, rotation, g_particleSecondaryContactPosition, 0,
                      -2,
                      (particle->flags & 0x200006) | 1);
    }
    if (sound != 0xFFFF) {
        SoundElement_PlaySoundAtPosition((s16)sound, g_particleSecondaryContactPosition, 0, -1);
    }
    Graphu64_ScaleVector(&particle->rotSpeed, &particle->rotSpeed,
                  particle->render.GroundFriction);
    particle->flags |= 0x200;
    if (particle->render.GroundBehavior == 1) {
        Particle_Release(&g_actorParticleEffectSystem[0], particle);
        Particle_StopSound(particle);
    }
}

struct CGameDynamicLight_t;
extern struct CGameDynamicLight_t g_dynamicLightPool;
extern s32 Barrel_GetImpactSlot(void *);



extern Shared_Particle *g_particleLinkedAttachmentEffect;

int InstHdr_UsesDefaultDefinitionHandling(struct LevelActor *source);

struct CVector3_t; void Gobjinst_ApplyImpactBoneTwist(char *actor, char *twistState, char *boneMatrix, struct CVector3_t impactPosition, struct CVector3_t impactDirection, s32 hitBoneIndex);


static __inline__ void attachParticle(Shared_Particle *particle, f32 *transform, s32 action) {
    f32 localTransform[16];
    f32 inverse[16];
    CVector3 direction;
    LevelActor *attached;
    ParticleAttachmentState *scene;
    attached=g_currentActorInstance.instance0;
    if (transform) Graphu64_InvertAffineMatrix(inverse, transform);
    else {
        Graphu64_ConvertMatrixToFloat(localTransform, &((FixedPointMatrix *)attached->animationMatrices)[g_currentActorInstance.value]);
        Graphu64_InvertAffineMatrix(inverse, localTransform);
    }
    scene=&g_currentActorInstance;
    Graphu64_TransformPoint(inverse, &scene->origin, &particle->attachmentPosition);
    direction=scene->direction;
    Graphu64_NormalizeVec3(&direction);
    Graphu64_TransformDirection(inverse, &direction, &particle->inst.velocity);
    particle->flags|=0x10000;
    particle->target=attached;
    particle->collisionNode=g_currentActorInstance.value;
    if (particle->inst.type==86 && action==2) particle->flags |= PARTICLE_FLAG_MOVES_AGAINST_DIRECTION;
}
#if defined(VERSION_DE)
/* This cartridge routes type 0x129 through its surface-contact event. */
static inline void Particle_DispatchSurfaceContact(Shared_Particle *actor) {
    struct Shared_ParticleDesc *desc;
    s32 event;
    u32 model, effect, sound;
    struct IntPair params;
    desc = actor->desc;
    event = Particle_HasSurfaceFlag(actor) ? 12 : 10;
    model = desc->events->particles[event];
    effect = desc->events->effects[event];
    params = desc->events->parameters[event];
    sound = desc->events->sounds[event];
    if (effect != 0xffff) Events_DeliverContactEffect(actor, actor, effect, -1, *(CVector3 *)&(actor->inst.pos), *(ContactEffectStyle *)&(params));
    if (model != 0xffff) Particle_SpawnChildEffect(actor, model, actor->space, 1);
    if (sound != 0xffff) SoundElement_PlaySoundAtPosition((s16)sound, actor->inst.pos, 0, -1);
}
#endif
void Particle_HitTarget(void *particle) {
    Shared_Particle *actor = particle;
    ParticleActionPair primary, secondary;
    f32 boneMatrix[16];
    s32 handle, mode, enabled, hasMatrix, action, special;
    s32 model, effect, sound, extraEffect; u16 type;
    LevelActor *source, *owner, *hit;
    void *other;
    struct Shared_ParticleEvents *actions;
    struct Shared_ParticleEvents *extraActions;
    struct Shared_ParticleDesc *definition;
    s32 draw;
    owner=0;
    source=g_currentActorInstance.instance0;
    enabled=1;
    special=0;
    hasMatrix=0;
    definition=actor->desc;
    if (InstHdr_UsesDefaultDefinitionHandling(source)) mode=actor->render.WallBehavior;
    else mode=actor->render.InstanceBehavior;
    if (!actor->inst.region) actor->inst.region=0;
    if (g_currentActorInstance.value!=-1) {
        action=Barrel_GetImpactSlot(source);
        if (action!=9) {
            action=((u8 *)&g_currentActorInstance.block18)[0x66];
            if (actor->inst.type==13) action=4;
            owner=g_currentActorInstance.instance0;
            if (owner->flags&0x3000000) {
                Graphu64_ConvertMatrixToFloat(boneMatrix, &((FixedPointMatrix *)owner->alternateAnimationMatrices)[g_currentActorInstance.value]);
                hasMatrix=1;
                if (owner->flags&0x1000000) {
                    Gobjinst_ApplyImpactBoneTwist((char *)owner, (char *)&owner->behaviorFlags, (char *)boneMatrix, (*(CVector3 *)&g_currentActorInstance.vec8), (*(CVector3 *)&g_currentActorInstance.particleVelocity), g_currentActorInstance.value);
                }
                if (owner->flags&0x2000000) {
                    type=actor->inst.type;
                    if (type==298 || type==306) {
                        if (owner->definition->kind==11) {
                            special=((Player *)owner)->attachedSpecialEffectCount<1;
                            if (special) ((Player *)owner)->attachedSpecialEffectCount++;
                        }
                    }
                    if (actor->inst.type==86 || actor->inst.type==2 || actor->inst.type==294 || actor->inst.type==15 ||
                        special || (actor->inst.type==11 && (g_particleAttachmentModeFlags&3)==1)) {
                        attachParticle(actor, boneMatrix, action);
                        if (actor->ribbonReferenceCount) {
                            Particle_UpdateMatrix(actor);
                            Fx_DetachParticleSwooshes(&g_gameSession.hud.actors, actor);
                        }
                        handle=actor->handle;
                        if (handle) { Gdynlight_ReleaseLight(&g_dynamicLightPool, handle); actor->handle=0; }
                    }
                }
            }
        }
    } else action=Barrel_GetImpactSlot(source);
    if (action==5) { action=4; actor->flags|=2; }
    if (Particle_HasSurfaceFlag(actor) && action<6 && action>=4) action=6;
    actions=definition->events;
    model=actions->particles[action]; effect=actions->effects[action];
    primary.words=actions->parameters[action];
    sound=definition->events->sounds[action];
    if (source->kind==1) {
        owner=source;
        if (owner->projectileContactCallback) owner->projectileContactCallback(owner, &owner->behaviorFlags, actor);
        if (InstHdr_ReturnUnusedActorStatus(owner)) enabled=0;
        if (owner->behaviorFlags&2) enabled=0;
    }
    if (effect!=0xffff) {
        if (g_effectCallbackFlags[effect].flags&4) {
            if (actor->inst.type==86) primary.control.lower=primary.control.lower*actor->scale;
        }
        other=source;
        if (g_effectCallbackFlags[effect].flags&2) other=actor;
        Events_DeliverContactEffect(other, actor, effect, -1, *(CVector3 *)&((*(CVector3 *)&g_currentActorInstance.vec8)), *(ContactEffectStyle *)&(primary.words));
    }
    if (action!=4) {
        draw=1;
        if (g_gameSettings.local) {
            draw=source->definition->kind!=11;
            if (mode==actor->render.WallBehavior) draw=0;
        }
        if (draw) {
            extraActions=definition->events;
            extraEffect=extraActions->effects[4];
            if (extraEffect!=0xffff) {
                secondary.words=extraActions->parameters[4];
                if (g_effectCallbackFlags[extraEffect].flags&4) {
                    other=source;
                    if (g_effectCallbackFlags[extraEffect].flags&2) other=actor;
                    Events_DeliverContactEffect(other, actor, extraEffect, -1, *(CVector3 *)&((*(CVector3 *)&g_currentActorInstance.vec8)), *(ContactEffectStyle *)&(secondary.words));
                }
            }
        }
    }
    if (model!=0xffff) Particle_SpawnChildEffect(actor, model, -8, enabled);
    if (sound!=0xffff) {
#if defined(VERSION_DE)
        if (actor->inst.type!=297)
#endif
            SoundElement_PlaySoundAtPosition((s16)sound, (*(CVector3 *)&g_currentActorInstance.vec8), 0, (s32)actor);
#if defined(VERSION_DE)
        else Particle_DispatchSurfaceContact(actor);
#endif
    }
    if (!(actor->flags&0x30000)) {
        if (actor->inst.type==1007 && g_particleLinkedAttachmentEffect && ((FixedPointMatrix *)owner->alternateAnimationMatrices) && g_particleLinkedAttachmentEffect->inst.type==1054 && action!=9) {
            g_particleLinkedAttachmentEffect->rot=(*(CVector3 *)&(*(CVector3 *)&g_collisionCurrentActor->vecF0));
            if (!hasMatrix) Graphu64_ConvertMatrixToFloat(boneMatrix, &((FixedPointMatrix *)owner->alternateAnimationMatrices)[g_currentActorInstance.value]);
            PitchMatrixLocal(boneMatrix, 3.141593f);
            if (((LevelActor *)g_collisionCurrentActor->instance0)->kind==1) {
                if (((LevelActor *)g_collisionCurrentActor->instance0)->definition->kind==2) Graphu64_ConvertMatrixToFloat(boneMatrix, &((FixedPointMatrix *)owner->alternateAnimationMatrices)[g_currentActorInstance.value]);
                hit=g_collisionCurrentActor->instance0;
                if (hit->kind==1 && (hit->flags&0x300000 || hit->definition->kind==2)) {
                    attachParticle(g_particleLinkedAttachmentEffect, boneMatrix, action);
                }
            }
        }
        if (mode==1 || (effect!=0xffff && g_effectCallbackFlags[effect].flags&1)) {
            Particle_Release(&g_actorParticleEffectSystem[0], actor);
            Particle_StopSound(actor);
        }
    }
}

/* Reacts to a particle striking the current attachment target. The target picks the impact slot (slot 5 becomes slot 4
 * and sets flag 2). Under the controlled-impact mode (g_gameSettings.local) descriptor slot 12 or 10 fires its event, particle
 * and sound at the particle. Otherwise slots 0, 2 and 3 leave a mark when the descriptor has flag 0x800000; a particle
 * whose response byte is 8 is handed to a kind 1 owner (flag 0x20000) or expires; types 0x56, 0x126, 0xCD and 0xF move
 * to the impact point and release their swooshes and light; then the particle is pushed off the surface along the hit
 * normal and the slot's event, particle and sound fire at the impact point (event table flag 2 makes the particle, not
 * the target, the event source). The particle is removed when its response byte is 1 and flags 0x30000 are clear. */
void Particle_ApplyImpactResponse(Shared_Particle *particle) {
    struct Shared_ParticleDesc *desc, *controlledDesc;
    LevelActor *target;
    void *eventSource;
    s32 hit;
    s32 event;
    u32 particleType, eventType, soundType;
    u32 model, sound, effect;
    struct IntPair params;
    CVector3 normal;
    struct IntPair controlledParams;
    LevelActor *owner;

    target = g_currentActorInstance.instance0;
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
            Events_DeliverContactEffect(particle, particle, eventType, -1, *(CVector3 *)&(particle->inst.pos), *(ContactEffectStyle *)&(controlledParams));
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
                Fx_SpawnImpactMark(&g_gameSession.hud.actors, (*(CVector3 *)&g_currentActorInstance.vec8), (*(CVector3 *)&(*(CVector3 *)&g_currentActorInstance.vecF0)), hit, 0);
            }
            break;
        }
        if (particle->render.WallBehavior == 8 || particle->render.GroundBehavior == 8) {
            if ((g_particleOwnerEffectFlags & 0x1000000) && (owner = (LevelActor *)particle->owner) && owner->kind == 1 && (owner->flags & 0x300000)) {
                particle->flags |= 0x20000;
                particle->inst.pos = (*(CVector3 *)&g_currentActorInstance.vec8);
                particle->inst.velocity = g_particleZeroVector;
                Player_SetPlayerResetPosition(((Player *)((LevelActor *)particle->owner)->controller), &particle->inst.pos);
            } else {
                particle->life = 1;
            }
        }
        if (particle->inst.type == 86 || particle->inst.type == 294 || particle->inst.type == 205 ||
            particle->inst.type == 15) {
            particle->flags |= 0x20000;
            particle->inst.pos = (*(CVector3 *)&g_currentActorInstance.vec8);
            particle->inst.velocity = g_particleZeroVector;
            if (particle->ribbonReferenceCount) {
                Particle_UpdateMatrix(particle);
                Fx_DetachParticleSwooshes(&g_gameSession.hud.actors, particle);
            }
            if (particle->handle) {
                Gdynlight_ReleaseLight(&g_dynamicLightPool, particle->handle);
                particle->handle = 0;
            }
        }
        normal = (*(CVector3 *)&(*(CVector3 *)&g_currentActorInstance.vecF0));
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
            Events_DeliverContactEffect(eventSource, particle, effect, -1, *(CVector3 *)&((*(CVector3 *)&g_currentActorInstance.vec8)), *(ContactEffectStyle *)&(params));
        }
        if (model != 0xFFFF) {
            Particle_SpawnChildEffect(particle, model, -8, 1);
        }
        if (sound != 0xFFFF) {
            SoundElement_PlaySoundAtPosition(sound, (*(CVector3 *)&g_currentActorInstance.vec8), 0, (s32)particle);
        }
        if (particle->flags & 0x30000) {
            return;
        }
        if (particle->render.WallBehavior != 1) {
            return;
        }
    }
    Particle_Release(&g_actorParticleEffectSystem[0], particle);
    Particle_StopSound(particle);
}

/* PARTICLE_BUILDMATRIX.CPP */

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

void Particle_Attach(Shared_Particle *particle, CVector3 *outPosition, CVector3 *outDirection) {
    f32 matrix[16];
    CVector3 position;
    CVector3 direction;
    f32 viewTransform[4][4];
    LevelActor *target;
    LevelActor *owner;
    f32 *transform;
    FixedPointMatrix *drawMatrices;

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
                drawMatrices = ((FixedPointMatrix *)target->animationMatrices);
                if (drawMatrices != 0) {
                    Graphu64_ConvertMatrixToFloat(matrix, &drawMatrices[particle->collisionNode]);
                    Graphu64_TransformPoint(matrix, &particle->attachmentPosition, &position);
                    Graphu64_TransformDirection(matrix, &particle->inst.velocity, &direction);
                    particle->inst.pos = position;
                    particle->direction = direction;
                } else {
                    position = target->position0;
                    particle->inst.pos = position;
                }
                break;
        }
        particle->inst.region = 0;
    }
    if (particle->flags & 0x400000) {
        owner = (LevelActor *)particle->owner;
        if (owner->flags & 0x300000) {
            if (((Player *)owner->controller)->camera != 0) {
                transform = ((Player *)owner->controller)->camera->viewOrient;
            } else {
                Player_BuildPlayerViewTransform(((Player *)owner->controller), viewTransform);
                transform = viewTransform[0];
            }
        } else {
            transform = owner->transform;
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
void Particle_BuildMatrix(Shared_Particle *particle, FixedPointMatrix *out, GameplayCamera *camera, f32 depth) {
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
        /* A sprite rolls by rot.z and slides by -rot.x, -rot.y in its own plane (the original reads the model again here,
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
        /* These models are built inside out (0x40B is tested twice in the original). */
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

/* Keep this source unit's macros local to its body. */
#undef PARTICLE_DEPTH_STRETCH
#undef PARTICLE_LANDING_HEIGHT
#undef PARTICLE_MAX_DISTANCE
#undef PARTICLE_MODEL_SCALE
#undef PARTICLE_QUIVER_PIVOT
#undef PARTICLE_QUIVER_STRENGTH_MAX
#undef PARTICLE_QUIVER_SWING
#undef PARTICLE_SURFACE_GAP

/* PARTICLE_DRAWGROUNDSHADOW.CPP */

/* Draws an actor's ground shadow: probes the ground under the actor through Collision_ProbeGround_de into g_currentActorInstance, and when ground is found tilts the shadow model from g_actorMatrixPool to the ground normal, scales it by the actor's size shrinking with height above the ground, fades it with height (and with lost health for actors flagged 1), places it on the ground and draws it through Geometry_DrawIntensityMask between render-mode commands. */




extern Gfx *g_displayListCursor;









extern void MatrixFromQuaternion(f32 *q, f32 *m);









extern s32 g_playerWeaponClassMode;


extern char s_particleModelResourceTag;

extern const char g_simpPartModelsIndexText[];

extern const char s_simpPartModelText[];

extern char g_simpleModelResourceCallbackAddress;







extern void **Cache_RequestWordCountedResource(s32,void **,s32,void *,s32);



extern void Geometry_QueueModelInstance(void **, void *, s32, void *, void *, s32);




void Particle_DrawGroundShadow(Shared_Particle *actor, GameplayCamera *view) {
    f32 matrix[16];
    CVector3 point;
    CQuatern rotation;
    CQuatern tilt;
    CQuatern roll;
    Shared_ParticleInstance probe;
    void *model;
    ParticleAttachmentState *ground;
    f32 angle;
    f32 height;
    f32 alpha;
    f32 size;
    f32 health;
    f32 floor;
    f32 shrink;

    model = Map_ReserveEntries(&g_actorMatrixPool, 1);
    if (model == 0) {
        return;
    }
    probe = actor->inst;
    probe.velocity.x = 0.0f;
    probe.velocity.y = 0.0f;
    probe.velocity.z = 0.0f;
    probe.pos.y += 10.24f;
    point.x = probe.pos.x;
    point.y = probe.pos.y - 102400.0f;
    point.z = probe.pos.z;
    Unicol_MoveActorWithCollision(&probe, point, &g_defaultProbeMotionSettings);
    ground = &g_currentActorInstance;
    if (ground->current == 0) {
        return;
    }
    angle = 0.78539824f;
    tilt = Graphu64_BuildDirectionQuaternion(&ground->point);
    roll.x = g_turretAimSine = Gu_Sinf(angle);
    roll.y = 0.0f;
    roll.z = 0.0f;
    roll.w = Math_Cosf(angle);
    MultiplyQuaternions(&rotation, &roll, &tilt);
    floor = ground->origin.y;
    height = actor->inst.pos.y - floor;
    alpha = ((RW_MIN(200.0f - height * 0.30517578f, 255.0f)) < (0.0f) ? (0.0f) : (RW_MIN(200.0f - height * 0.30517578f, 255.0f)));
    size = actor->size.z * 7.68f;
    if (actor->desc->renderModel != 0) {
        size *= 8.0f;
    }
    size *= actor->desc->scaling->shadowScale;
    shrink = height * 0.1f;
    size = RW_MIN_F32(size - shrink, size) < 0.0f ? 0.0f : RW_MIN_F32(size - shrink, size);
    if (actor->desc->flags & 1) {
        health = actor->life;
        if (0.0f < health) {
            alpha *= (health - actor->time) / health;
        }
    }
    point.x = actor->inst.pos.x;
    point.z = actor->inst.pos.z;
    point.y = floor;
    Graphu64_LimitVectorLength(&point, 20000.0f);
    MatrixFromQuaternion(&rotation, matrix);
    ScaleMatrixLocal(matrix, size, 1.0f, size);
    TranslateMatrix(matrix, point.x, point.y, point.z);
    Graphu64_ConvertMatrixToFixed(matrix, model);
    {
        Gfx *cmd = g_displayListCursor++;
        gDPPipeSync(cmd);
        cmd = g_displayListCursor++;
        gDPSetCycleType(cmd, G_CYC_2CYCLE);
    }
    Geometry_DrawIntensityMask(model, 1, (u8)(u32)alpha);
    {
        Gfx *cmd = g_displayListCursor++;
        gDPPipeSync(cmd);
        cmd = g_displayListCursor++;
        gDPSetCycleType(cmd, G_CYC_1CYCLE);
    }
}

void Particle_DrawModel(Shared_Particle *particle, GameplayCamera *view) {
    CVector3 delta;
    void *modelTable;
    FixedPointMatrix *matrix;
    void **resource;
    s32 key;
    s32 found;
    s32 index;
    f32 amount;

    index = 0;
    if (g_playerWeaponClassMode == 1) {
        matrix = &particle->mtx[g_lightingBufferIndex];
    } else {
        matrix = Map_ReserveEntries(&g_actorMatrixPool, 1);
        if (matrix == 0) {
            return;
        }
        Graphu64_TransformPoint(view->worldToView, &particle->inst.pos, &delta);
        amount = delta.z;
        if (amount < 0.0f) {
            amount = -amount;
        }
        Particle_BuildMatrix(particle, matrix, view, amount);
    }

    if (particle->resource == 0) {
        resource = Cache_RequestResource(0, particle->desc->renderModel,
                                particle->desc->renderModel, 24,
                                0, 0, 0, &s_particleModelResourceTag, 1);
        if (resource != 0) {
            key = SetN64_GetDirectoryEntry(*resource,
                                particle->desc->renderModel, 1);
            Cache_ReleaseResource(0, resource);
            found = Cache_RequestWordCountedResource(0, &modelTable, key, &g_simpPartModelsIndexText, 1);
            if (found != 0) {
                particle->resource = SetN64_LocatePackSection(
                    (s32)modelTable, key, index % *(s32 *)modelTable,
                    &particle->resourceSize);
                Cache_ReleaseResource(0, (void *)found);
            }
        }
        if (particle->resource == 0) {
            return;
        }
    }

    resource = Cache_RequestResource(0, particle->resource,
                            particle->resource, particle->resourceSize,
                            0, 0, &g_simpleModelResourceCallbackAddress, &s_simpPartModelText, 1);
    if (resource != 0) {
        Geometry_QueueModelInstance(resource, matrix, 0,
                      &particle->lighting[g_lightingBufferIndex], 0, -1);
        Cache_UnlockResource(0, resource);
    }
}

/* PARTICLE_DRAWSPRITE.CPP */

struct Shared_AnimInfo;

/* Draws one particle for a view: fades particles hidden behind geometry in or out, blends its colours towards the
 * descriptor's targets (greyscale for views that ask for it), picks the animation frame, builds its matrix (once per
 * frame for a shared camera, per view otherwise), selects the texture and render mode, works out its alpha from life,
 * fade-in, fade-out and distance from the view, and emits the colour and draw commands. */



static inline s32 Particle_IsSpriteOccluded(Shared_Particle *particle, GameplayCamera *view) {
    Shared_ParticleInstance *inst;
    s32 hit;

    inst = Gsky_FindScreenMessage(view);
    if (inst != 0 && view->bobSuppressed == 0) {
        Shared_ParticleInstance saved;
        saved = *inst;
        inst->pos = view->position;
        hit = Unicol_MoveActorWithCollision(inst, particle->inst.pos, &g_defaultProbeMotionSettings);
        *inst = saved;
    } else {
        Shared_ParticleInstance probe;
        probe = particle->inst;
        probe.pos = view->position;
        hit = Unicol_MoveActorWithCollision(&probe, particle->inst.pos, &g_defaultProbeMotionSettings);
    }
    return hit;
}

static inline s32 Particle_GetSpriteViewMode(Shared_Particle *particle) {
    s32 mode = 0;

    if (particle->desc->flags & 0x2000000) {
        if (particle->flags & 2) {
            mode = 2;
        } else if (g_particleSpriteViewMode == 2) {
            mode = 1;
        }
    }
    return mode;
}

static inline s32 Particle_GetNonnegativeScaledSpriteSize(f32 value, f32 div) {
    return (value < 0.0f) ? 0 : (s32)((s32)value / div);
}

#define PARTICLE_MIN(a, b) ((a) > (b) ? (b) : (a))
#define PARTICLE_MAX(a, b) ((a) < (b) ? (b) : (a))

/* Linearly blends one colour channel from a start value to an end value and clamps the result to 0..255.
   A macro, as in the ROM's unit: the clamp evaluates the blend once per comparison and once per result. */
#define PARTICLE_BLEND_COLOR_CHANNEL(from, to, ratio) \
    ((u32)PARTICLE_MAX(PARTICLE_MIN(((to) - (from)) * (ratio) + (from), 255.0f), 0.0f))

void Particle_DrawSprite(Shared_Particle *particle, GameplayCamera *view) {
    struct Shared_AnimInfo info;
    u8 env[3];
    u8 prim[3];
    CVector3 viewPos;
    void *model;
    struct Shared_ParticleDesc *desc;
    void *mtx;
    f32 fade;
    f32 ratio;
    f32 dist;
    s32 hit;
    s32 alpha;
    s8 duration;
    s32 mode;
    s32 frame;
    s32 time;
    s32 textured;
    s32 shiftS;
    s32 shiftT;
    s32 sum;
    s16 gray;
    u8 *envTo;
    u8 *primTo;
    u8 *envFrom;
    u8 *primFrom;

    if (g_primaryDisplayListCapacity - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
        return;
    }
    if (particle->time < 0.0f) {
        return;
    }
    model = Textload_RequestTextureVariation(&particle->model, -1);
    if (model == 0) {
        return;
    }
    desc = particle->desc;
    if ((desc->flags & 0x80000) && desc->playback == 1) {
        if (particle->inst.type != 96) {
            particle->time = 0.0f;
        }
        hit = Particle_IsSpriteOccluded(particle, view);
        if (!hit) {
            fade = particle->opacity + g_frameElapsedTime * 128.0f;
            alpha = (fade > 255.0f) ? 255 : (s32)fade;
        } else {
            fade = particle->opacity - g_frameElapsedTime * 128.0f;
            alpha = (fade < 0.0f) ? 0 : (s32)fade;
        }
        particle->opacity = alpha;
        if (alpha == 0.0f) {
            Cache_UnlockResource(0, model);
            return;
        }
    }

    particle->flags |= 8 << view->index;
    particle->alpha = 255.0f;
    ratio = particle->time / particle->life > 1.0f ? 1.0f : particle->time / particle->life;
    primFrom = particle->prim;
    envFrom = particle->env;
    primTo = desc->colors->prim;
    envTo = desc->colors->env;
    env[0] = PARTICLE_BLEND_COLOR_CHANNEL(envFrom[0], envTo[0], ratio);
    env[1] = PARTICLE_BLEND_COLOR_CHANNEL(envFrom[1], envTo[1], ratio);
    env[2] = PARTICLE_BLEND_COLOR_CHANNEL(envFrom[2], envTo[2], ratio);
    prim[0] = PARTICLE_BLEND_COLOR_CHANNEL(primFrom[0], primTo[0], ratio);
    prim[1] = PARTICLE_BLEND_COLOR_CHANNEL(primFrom[1], primTo[1], ratio);
    prim[2] = PARTICLE_BLEND_COLOR_CHANNEL(primFrom[2], primTo[2], ratio);

    if (view->monochrome != 0) {
        gray = env[0] + env[1] + env[2];
        gray /= 12;
        env[0] = gray * 2;
        env[1] = 0;
        env[2] = 0;
        gray = prim[0] + prim[1] + prim[2];
        gray /= 12;
        prim[0] = gray * 2;
        prim[1] = gray * 3;
        prim[2] = 0;
    }

    mode = Particle_GetSpriteViewMode(particle);
    Textload_ReadTextureAnimationInfo(model, &info);
    frame = particle->frame;
    time = particle->time;
    switch (desc->playback) {
        case 0:
            if (frame >= info.count - 1) {
                time = particle->life;
                frame = info.count - 1;
                particle->time = time;
            }
            break;
        case 1:
            if (frame >= info.count) {
                frame = info.count - 1;
            }
            break;
        case 2:
            frame %= info.count;
            break;
        case 3:
            if (info.count * 2 - 2 > 0) {
                frame %= info.count * 2 - 2;
            } else {
                frame = 0;
            }
            if (frame >= info.count) {
                frame = (info.count * 2 - 2) - frame;
            }
            break;
        case 4:
            frame = Graphu64_NextRandom() % info.count;
            break;
        case 5:
            if (particle->fixedSpriteFrame == -1) {
                particle->fixedSpriteFrame = Graphu64_NextRandom() % info.count;
            }
            frame = particle->fixedSpriteFrame;
            break;
    }

    if (!(particle->flags & 0x100000)) {
        if (g_playerWeaponClassMode == 1) {
            GameplayCamera *camera = g_gameplayCameraList.camera;
            CVector3 local;
            f32 depth;
            Graphu64_TransformPoint(camera->worldToView, &particle->inst.pos, &local);
            depth = local.z;
            if (depth < 0.0f) {
                depth = -depth;
            }
            Particle_BuildMatrix(particle, &particle->mtx[g_lightingBufferIndex], camera, depth);
        } else {
            Particle_BuildMatrix(particle, &particle->mtx[g_lightingBufferIndex], 0, 0.0f);
        }
        particle->spriteFrame = frame;
        particle->flags |= 0x100000;
    }
    Graphu64_TransformPoint(view->worldToView, &particle->inst.pos, &viewPos);
    dist = viewPos.z;
    if (dist < 0.0f) {
        dist = -dist;
    }
    if (g_playerWeaponClassMode == 1) {
        gSPMatrix(g_displayListCursor++, &particle->mtx[g_lightingBufferIndex], G_MTX_LOAD);
    } else {
        mtx = Map_ReserveEntries(&g_actorMatrixPool, 1);
        if (mtx == 0) {
            Cache_UnlockResource(0, model);
            return;
        }
        Particle_BuildMatrix(particle, mtx, view, dist);
        gSPMatrix(g_displayListCursor++, (u32)mtx, G_MTX_LOAD);
    }

    textured = particle->flags & PARTICLE_FLAG_TEXTURED;
    shiftS = 1 << (((desc->flags & 0x100) ? 7 : 6) + info.frame->shiftS);
    shiftT = 1 << (((desc->flags & 0x200) ? 7 : 6) + info.frame->shiftT);
#if defined(VERSION_US_REV1)
    Textload_LoadTextureFrameTiles(&particle->model, model, frame, 0, shiftS, shiftT, 1, 1, 0);
#else
    Textload_LoadTextureFrame(&particle->model, model, frame, 0, shiftS, shiftT, 1, 1, 0);
#endif
    switch (info.frame->kind) {
        case 0:
        case 1:
            Geometry_SetCombineMode(24);
            break;
        case 3:
            Geometry_SetCombineMode(29);
            break;
    }
    if (textured) {
        Geometry_SetModePreset(15);
        {
            gSPTextureL(g_displayListCursor++, shiftS, shiftT, 0, 0xFF, 0, G_ON);
        }
    } else if ((desc->flags & 0x400) && desc->fade->modeSelector != 4) {
        Geometry_SetModePreset(15);
    } else if (desc->flags & 0x4000) {
        Geometry_SetModePreset(!(g_gameSettings.flags & 0x200) ? 13 : 17);
    } else {
        Geometry_SetModePreset((g_gameSettings.flags & 0x200) ? 18 : 19);
    }

    alpha = 0xFF;
    if ((desc->flags & 1) && particle->life > 0) {
        alpha = (particle->life - time) * 255.0f / particle->life;
    }
    duration = desc->fade->fadeIn;
    if (duration != -1 && time < duration) {
        alpha = alpha * (time + 1.0f) / (duration + 1.0f);
    }
    duration = desc->fade->fadeOut;
    if (duration != -1) {
        f32 left = particle->life - time;
        if ((left < 0.0f ? 0.0f : left) < duration) {
            alpha = Particle_GetNonnegativeScaledSpriteSize(alpha * (particle->life - time), duration + 1.0f);
        }
    }
    if (view->farPlane < -0.0001f || view->farPlane > 0.0001f) {
        f32 range = view->farPlane;
        f32 half;
        f32 delta;
        switch (desc->fade->rangeMode) {
            case 2:
                alpha = alpha * (((range - dist) * 10.0f / range) > 1.0f ? 1.0f : ((range - dist) * 10.0f / range));
                break;
            case 0:
                alpha = alpha * (((range - dist) * 5.0f / range) > 1.0f ? 1.0f : ((range - dist) * 5.0f / range));
                break;
            case 1:
                half = range * 0.5f;
                delta = half - dist;
                alpha = alpha * (delta < 0.0f ? half + delta : half - delta) / half;
                break;
        }
    }

    if (info.frame->kind == 3) {
        switch (mode) {
            case 0:
            default:
                gDPSetEnvColor(g_displayListCursor++, env[0], env[1], env[2], 255);
                break;
            case 2:
                gDPSetEnvColor(g_displayListCursor++, env[0], env[0], env[2], 255);
                break;
            case 1:
                gDPSetEnvColor(g_displayListCursor++, env[1], env[0], env[2], 255);
                break;
        }
    }
    alpha = (alpha > 255 ? 255 : alpha) < 0 ? 0 : (alpha > 255 ? 255 : alpha);
    gSPVertex(g_displayListCursor++, &g_particleSpriteVertices, 4, 0);
    if (textured) {
        gSPTextureL(g_displayListCursor++, shiftS, shiftT, 0, 0xFF, 0, G_ON);
        }
    particle->alpha = (alpha * particle->opacity) >> 8;
    switch (mode) {
        case 0:
        default:
            gDPSetPrimColor(g_displayListCursor++, 0, 0, prim[0], prim[1], prim[2], (u32)particle->alpha);
            break;
        case 2:
            gDPSetPrimColor(g_displayListCursor++, 0, 0, prim[0], prim[0], prim[2], (u32)particle->alpha);
            break;
        case 1:
            gDPSetPrimColor(g_displayListCursor++, 0, 0, prim[1], prim[0], prim[2], (u32)particle->alpha);
            break;
    }
    gSP2Triangles(g_displayListCursor++, 0, 1, 2, 0, 2, 3, 0, 0);
    Cache_UnlockResource(0, model);
}

/* Keep this source unit's macros local to its body. */

/* PARTICLE_RECYCLERELEASEDEFFECTS.CPP */

void Particle_RecycleReleasedEffects(EffectSystem *recycleSystem) {
    s32 *referenceCount;
    s32 lightHandle;
    s32 flags;
    s32 i;
    s32 clear_mask;
    s32 remove_offset;
    s32 active_mask;
    s32 flagged_offset;
    s32 head_offset;
    Shared_Particle *effect;
    Shared_Particle *next;
    u8 *head_cursor;

    i = 0;
    clear_mask = 0xFDFFFEFF;
    remove_offset = 64512;
    active_mask = 0x01000000;
    flagged_offset = 0xFC14;
    do {
        __builtin_memcpy(&next, &(recycleSystem)->lists[i].head, sizeof(next));
        if (next != 0) {
            do {
                effect = next;
                next = next->next;
                flags = effect->flags;
                if (flags & 0x100) {
                  if (!(flags & 0x800)) {
                    Particle_FinishActorEffects(effect);
                    if (effect->ribbonReferenceCount != 0) {
                        Particle_UpdateMatrix(effect);
                        Fx_DetachParticleSwooshes(&g_gameSession.hud.actors, effect);
                    }
                    lightHandle = effect->handle;
                    if (lightHandle != 0) {
                        Gdynlight_ReleaseLight(&g_dynamicLightPool, lightHandle);
                        effect->handle = 0;
                    }
                    referenceCount = effect->ownerId;
                    if (referenceCount != 0) {
                        *referenceCount -= 1;
                    }
                    effect->flags = effect->flags & clear_mask;
                    List_RemoveIntrusive(effect->list, effect);
                    effect->list = 0;
                    List_PrependIntrusive((char *)recycleSystem + remove_offset, effect);
                    if (effect->flags & active_mask) {
                        List_RemoveIntrusive((char *)recycleSystem + flagged_offset, effect);
                    }
                  }
                }
            } while (next != 0);
        }
        i += 1;
    } while (i < 3);
}

/* GHOT_DISPATCHATTACHMENTEFFECTS_DATA.CPP */

/* Spawns the effects that template block 2 of the system lists for a kind: for each template in the kind's range it filters by player mask, existing owner effects, anchor distance, mode, team flags and a percent chance, builds a spawn matrix (source matrix, mirror, translation or rotation), then for a random count allocates effects, fills their timing, spread, colour, render and direction fields from the template's packed floats, links them into their group, aims shots at the held target for kinds 0x2D and 0x4F, and plays their sound. Returns the number spawned. */



extern CVector3 g_particleZeroVector;

extern s32 g_playerWeaponClassMode;


extern f32 g_particleInitialVelocityScale;







extern void Particle_Release(EffectSystem *, Shared_Particle *);





#if defined(VERSION_EU)
#else
#endif

static inline s32 effect_spawn_random_count(s32 range) {
    return range != 0 ? Graphu64_NextRandom() % (range + 1) : 0;
}

static inline Shared_Particle *effect_spawn_find_owned(IntrusiveList *list, void *ownerId, Shared_ParticleDesc *entry) {
    Shared_Particle *effect;

    effect = list->head;
    if (entry != 0) {
        for (; effect != 0; effect = effect->next) {
            if (effect->ownerIdAddress == ownerId && effect->desc == entry) {
                return effect;
            }
        }
    } else {
        for (; effect != 0; effect = effect->next) {
            if (effect->ownerIdAddress == ownerId) {
                return effect;
            }
        }
    }
    return 0;
}

static inline Shared_Particle *effect_spawn_allocate(EffectSystem *sys, u8 index) {
    Shared_Particle *effect;
    IntrusiveList *list;
    s32 i;

    if (sys->free.head == 0) {
        for (i = 0; i <= index; i++) {
            if ((&sys->lists[i])->tail != 0) {
                Particle_Release(sys, (&sys->lists[i])->tail);
                break;
            }
        }
    }
    effect = sys->free.head;
    if (effect == 0) {
        return 0;
    }
    List_RemoveIntrusive(&sys->free, effect);
    list = &sys->lists[index];
    List_PrependIntrusive(list, effect);
    effect->list = list;
    effect->groupNext = 0;
    effect->groupPrevious = 0;
    effect->flags = 0x100;
    return effect;
}

static inline void effect_spawn_aim(Shared_Particle *effect, EffectTarget *aimTarget, CVector3 *vel, s32 sourceType) {
    MatrixF targetMtx;
    MatrixF targetInv;
    CVector3 up;
    LevelActor *targetActor;
    s32 targetTeam;

    if (aimTarget->matrixIndex != -1) {
        effect->space = -4;
        targetActor = (LevelActor *)g_currentActorInstance.instance0;
        targetTeam = aimTarget->victimTeam;
        Graphu64_ConvertMatrixToFloat(&targetMtx, &((FixedPointMatrix *)targetActor->animationMatrices)[g_currentActorInstance.value]);
        Graphu64_InvertAffineMatrix(targetInv.m[0], targetMtx.m[0]);
        Graphu64_TransformPoint(&targetInv, &aimTarget->pos, &effect->attachmentPosition);
        up = g_particleZeroVector;
        Graphu64_NormalizeVec3(&up.x);
        Graphu64_TransformDirection(&targetInv, &up, vel);
        effect->target = (LevelActor *)targetActor;
        effect->flags |= 0x10000;
        effect->collisionNode = g_currentActorInstance.value;
        if (effect->inst.type == 86 && targetTeam == sourceType) {
            effect->flags |= 0x4000000;
        }
    }
}

s32 Particle_SpawnEffectGroup(EffectSystem *sys, void *source, void *owner, s32 *refCount, s32 followTarget, s32 kind,
                  CVector3 inheritedVelocity, CQuatern rotation, CVector3 pos, CVector3 *aim, s32 requestedMode, s32 spawnFlags) {
    MatrixF mtx;
    CVector3 dir;
    CVector3 dirOut;
    CVector3 offset;
    CVector3 offsetOut;
    CVector3 delta;
    CQuatern quat;
    EffectTarget target;
    CVector3 aimDelta;
    s32 first;
    s32 last;
    u8 h, sv, v;
    u8 r, g, b;
    u8 r0, g0, b0;
    u8 r1, g1, b1;
    s32 count;
    s32 j;
    s32 n;
    s32 mode;
    s32 i;
    Player *anchor;
    void *ownerId;
    s32 extra;
    s32 life;
    s32 layer;
    s32 ok;
    s32 hue;
    u8 sat;
    u8 val;
    s32 spread;
    u32 *bits;
    u8 mask;
    s32 resource;
    EffectBlock *block;
    s32 numEntries;
    Shared_ParticleDesc *entries;
    Shared_ParticleDesc *entry;
    Shared_Particle *effect;
    CCollisionInfo2_t *render;
    CVector3 *vel;
    EffectTarget *aimTarget;
    GameplayCamera *camera;
    f32 distSq;
    f32 scale;
    f32 depth;
    s32 sourceType;
    s32 sound;

    if (g_transientPlayerList.frozen != 0) {
        return 0;
    }
    count = 0;
    resource = sys->resource;
    g_collisionCurrentActor = &target;
    sys->last = 0;
    block = SetN64_GetPackSection(resource, 1);
    numEntries = block->count;
    if (Defs_FindSortedGroupRange(block->entries, numEntries, kind, &first, &last) != 0) {
        entries = ((EffectBlock *)SetN64_GetPackSection(resource, 2))->entries;
        anchor = 0;
        if (g_transientPlayerList.actorList != 0) {
            anchor = g_transientPlayerList.actorList;
        }
        ownerId = 0;
        if (owner != 0) {
            switch (*(u8 *)owner) {
                case 1:
                case 2:
                    ownerId = owner;
                    break;
                case 0:
                    ownerId = (void *)((ObjA *)owner)->flagsD0;
                    owner = 0;
                    break;
            }
        }
        mask = 1;
        if (g_frontendScreenStatus.settings.local != 0) {
            mask = 2;
        }
        for (i = first; i <= last; i++) {
            entry = &entries[i];
            ok = (entry->playerMask & mask) != 0;
            if ((entry->flags & 0x80) && ownerId != 0) {
                if (effect_spawn_find_owned(&sys->lists[entry->fade->listIndex], ownerId, entry) != 0) {
                    ok = 0;
                }
            }
            if (anchor != 0) {
                Graphu64_SubtractVectors(&delta, &pos, &anchor->pos);
            } else {
                delta.x = delta.y = delta.z = 0.0f;
            }
            distSq = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
            if (entry->flags & 0x400000) {
                if (262144.0f <= distSq) {
                    ok = 0;
                }
            } else if (entry->flags & 0x200000) {
                if (distSq <= 262144.0f) {
                    ok = 0;
                }
            }
            switch (entry->fade->modeSelector) {
                case 6:
                    mode = -7;
                    break;
                case 5:
                    mode = -6;
                    break;
                case 0:
                    mode = -4;
                    break;
                case 1:
                    mode = -5;
                    break;
                default:
                    switch (requestedMode) {
                        case -5:
                        case -3:
                        case -2:
                            mode = requestedMode;
                            break;
                        default:
                            mode = -3;
                            break;
                    }
                    break;
                case 3:
                    if (0.0f <= (f32) requestedMode) {
                        mode = requestedMode;
                    } else {
                        ok = 0;
                        mode = 0;
                    }
                    break;
                case 4:
                    if (*(u8 *)source == 2 && ((Shared_Particle *)source)->space == -8) {
                        requestedMode = -8;
                        g_particleSharedInitialDirection = ((Shared_Particle *)source)->direction;
                    }
                    mode = requestedMode;
                    break;
            }
            if (entry->flags & 0x2000000) {
                if (g_gameSettings.bloodMode == 0 || !(spawnFlags & 1)) {
                    ok = 0;
                }
            }
            if (entry->flags & 0x4000000) {
                if (g_gameSettings.bloodMode != 0) {
                    ok = 0;
                }
            }
            if (entry->fade->chance != 100) {
                if (Graphu64_NextRandom() % 1000 + 1 > entry->fade->chance * 10) {
                    ok = 0;
                }
            }
            if (!ok) {
                continue;
            }
            extra = 0;
            if (entry->flags & 0x8000) {
                switch (*(u8 *)source) {
                    case 2:
                        if (!(((Shared_Particle *)source)->flags & 0x100000)) {
                            if (g_playerWeaponClassMode == 1) {
                                camera = g_gameplayCameraList.camera;
                                Graphu64_TransformPoint(camera->worldToView, &((Shared_Particle *)source)->inst.pos, &aimDelta);
                                depth = aimDelta.z;
                                if (depth < 0.0f) {
                                    depth = -depth;
                                }
                                Particle_BuildMatrix((Shared_Particle *)source, &((Shared_Particle *)source)->mtx[g_lightingBufferIndex], camera, depth);
                            } else {
                                Particle_BuildMatrix((Shared_Particle *)source, &((Shared_Particle *)source)->mtx[g_lightingBufferIndex], 0, 0.0f);
                            }
                            ((Shared_Particle *)source)->flags |= 0x100000;
                        }
                        Graphu64_ConvertMatrixToFloat(&mtx, &((Shared_Particle *)source)->mtx[g_lightingBufferIndex]);
                        scale = 0.09765625f;
                        if (((Shared_Particle *)source)->desc->renderModel != 0) {
                            scale = 2.857143f;
                        }
                        ScaleMatrixLocal(&mtx, scale, scale, scale);
                        if (((Shared_Particle *)source)->desc->flags & 8) {
                            TranslateMatrix(&mtx, 0.0f, -((Shared_Particle *)source)->size.y * ((Shared_Particle *)source)->size.z, 0.0f);
                        }
                        break;
                    case 1:
                        extra = 0x400000;
                        Graphu64_BuildScaleMatrix(&mtx, -1.0f, 1.0f, -1.0f);
                        break;
                    default:
                        Graphu64_BuildTranslationMatrix(&mtx, ((ObjA *)source)->position.x, ((ObjA *)source)->position.y, ((ObjA *)source)->position.z);
                        break;
                }
            } else if (entry->flags & 0x1000000) {
                Graphu64_IdentityMatrix(&mtx);
            } else {
                if (entry->flags & 0x40000) {
                    quat = Gobjinst_BuildTargetAimOrientation(owner, pos);
                } else {
                    quat = rotation;
                }
                MatrixFromQuaternion(&quat.x, &mtx.m[0][0]);
            }
            n = entry->fade->countBase + effect_spawn_random_count(entry->fade->countRange);
            for (j = 0; j < n; j++) {
                life = entry->fade->lifeBase + effect_spawn_random_count(entry->fade->lifeRange);
                if (life == 0) {
                    continue;
                }
                effect = effect_spawn_allocate(sys, entry->fade->listIndex);
                if (effect == 0) {
                    break;
                }
                count++;
                Textload_LocateTextureResource(&effect->model, entry->textureId);
                GameObject_ResetActorMotion(effect);
                effect->resource = 0;
                effect->resourceSize = 0;
                effect->inst.type = kind;
                effect->desc = entry;
                effect->space = mode;
                if (*(u8 *)source == 2) {
                    effect->source = (Shared_Particle *)source;
                } else {
                    effect->source = 0;
                }
                effect->ownerIdAddress = ownerId;
                effect->owner = owner;
                effect->ownerId = refCount;
                if (refCount != 0) {
                    (*refCount)++;
                }
                effect->target = (LevelActor *)followTarget;
                effect->reserved13C = 0;
                effect->flags = (effect->flags & ~0xE600) | (spawnFlags | extra);
                bits = &effect->model;
                layer = 0;
                if (effect->desc->flags & 0x2000000) {
                    if (effect->flags & 2) {
                        layer = 2;
                    } else if (g_gameSettings.bloodMode == 2) {
                        layer = 1;
                    }
                }
                *bits |= layer << 30;
                effect->ribbonReferenceCount = 0;
                spread = entry->fade->emitSpread;
                if (spread < 0) {
                    effect->time = spread;
                } else {
                    effect->time = -(f32) effect_spawn_random_count(spread);
                }
                effect->sineAngleX = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->sineWave->ranges[2])) * g_particleAngularVelocityScale;
                effect->sineAngleSpeedX = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->sineWave->ranges[1])) * 0.41887906f;
                effect->sineAmplitudeX = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->sineWave->ranges[0]));
                effect->sineAngleY = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->sineWave->ranges[5])) * g_particleAngularVelocityScale;
                effect->sineAngleSpeedY = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->sineWave->ranges[4])) * 0.41887906f;
                effect->sineAmplitudeY = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->sineWave->ranges[3]));
                if (entry->flags & 2) {
                    effect->frame = effect_spawn_random_count(life);
                } else {
                    effect->frame = 0.0f;
                }
                effect->lifetime = entry->fade->animationParameter;
                effect->life = life;
                effect->spriteFrame = 0;
                effect->fixedSpriteFrame = -1;
                if (aim == 0) {
                    dir.x = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->direction[0]));
                    dir.y = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->direction[1]));
                    dir.z = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->direction[2]));
                    Graphu64_NormalizeVec3(&dir.x);
                    if (dir.x != 0.0f || dir.y != 0.0f || dir.z != 0.0f) {
                        Graphu64_TransformPoint(&mtx, &dir, &dirOut);
                    } else {
                        dirOut = dir;
                    }
                    if (mode == -8) {
                        effect->direction = g_particleSharedInitialDirection;
                        Graphu64_NormalizeVec3(&effect->direction.x);
                    } else {
                        effect->direction = dirOut;
                    }
                }
                effect->size.x = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->scaling->ranges[0]));
                effect->size.y = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->scaling->ranges[2]));
                effect->size.z = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->scaling->ranges[4]));
                effect->growth.x = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->scaling->ranges[1]));
                effect->growth.y = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->scaling->ranges[3]));
                effect->growth.z = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->scaling->ranges[5]));
                if (entry->renderModel != 0) {
                    effect->rot.x = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->packedRangesB[0]));
                    effect->rot.y = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->packedRangesB[2]));
                    effect->rot.z = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->packedRangesB[4]));
                    effect->rotSpeed.x = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->packedRangesB[1]));
                    effect->rotSpeed.y = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->packedRangesB[3]));
                    effect->rotSpeed.z = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->packedRangesB[5]));
                } else {
                    effect->rot.x = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->packedRangesB[0]));
                    effect->rot.y = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->packedRangesB[2]));
                    effect->rot.z = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->packedRangesB[4]));
                    effect->rotSpeed.x = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->packedRangesB[1]));
                    effect->rotSpeed.y = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->packedRangesB[3]));
                    effect->rotSpeed.z = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->packedRangesB[5]));
                }
                if ((entry->flags & 0x80000) && entry->playback == 1) {
                    effect->opacity = 0;
                    effect->alpha = 0.0f;
                } else {
                    effect->opacity = 0xFF;
                    effect->alpha = 255.0f;
                }
                effect->inst.region = 0;
                effect->inst.pos = pos;
                offset.x = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->offset[0]));
                offset.y = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->offset[1]));
                offset.z = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->offset[2]));
                if (offset.x != 0.0f || offset.y != 0.0f || offset.z != 0.0f) {
                    Graphu64_TransformPoint(&mtx, &offset, &offsetOut);
                    if (!(entry->flags & 0x8000)) {
                        Graphu64_AddVec3(&offsetOut, &pos, &offsetOut);
                    }
                    effect->inst.pos = offsetOut;
                }
                if (aim != 0) {
                    Graphu64_SubtractVectors(&aimDelta, aim, &effect->inst.pos);
                    Graphu64_NormalizeVec3(&aimDelta.x);
                    BuildDirectionMatrix(&mtx, &aimDelta);
                    if (mode == -8) {
                        effect->direction = g_particleSharedInitialDirection;
                        Graphu64_NormalizeVec3(&effect->direction.x);
                    } else {
                        dir.x = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->direction[0]));
                        dir.y = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->direction[1]));
                        dir.z = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(entry->direction[2]));
                        Graphu64_NormalizeVec3(&dir.x);
                        if (dir.x != 0.0f || dir.y != 0.0f || dir.z != 0.0f) {
                            Graphu64_TransformPoint(&mtx, &dir, &dirOut);
                        } else {
                            dirOut = dir;
                        }
                        effect->direction = dirOut;
                    }
                }
                effect->prevPos = effect->inst.pos;
                effect->attachmentPosition = effect->inst.pos;
                Graphu64_ScaleVector(&effect->inst.velocity, &dirOut, Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(*(CharacterScreenCell *)&entry->motion->speedHi)));
                if (entry->flags & 0x20) {
                    Graphu64_AddVec3(&effect->inst.velocity, &effect->inst.velocity, &inheritedVelocity);
                }
                hue = 0;
                if (entry->colors->randomizeHue != 0) {
                    hue = Graphu64_NextRandom() % (entry->colors->randomizeHue * 2) - (u8) entry->colors->randomizeHue;
                }
                sat = entry->colors->randomizeSaturation != 0 ? Graphu64_NextRandom() % entry->colors->randomizeSaturation : 0;
                val = entry->colors->randomizeValue != 0 ? Graphu64_NextRandom() % entry->colors->randomizeValue : 0;
                r = entry->colors->initialPrim[0];
                g = entry->colors->initialPrim[1];
                b = entry->colors->initialPrim[2];
                Gregion_ShiftColorHue(hue, r, g, b, &h, &sv, &v);
                Gregion_DesaturateColor(sat, h, sv, v, &r, &g, &b);
                Gregion_DarkenColor(val, r, g, b, &r0, &g0, &b0);
                r = entry->colors->initialEnv[0];
                g = entry->colors->initialEnv[1];
                b = entry->colors->initialEnv[2];
                Gregion_ShiftColorHue(hue, r, g, b, &h, &sv, &v);
                Gregion_DesaturateColor(sat, h, sv, v, &r, &g, &b);
                Gregion_DarkenColor(val, r, g, b, &r1, &g1, &b1);
                effect->prim[0] = r0;
                effect->prim[1] = g0;
                effect->prim[2] = b0;
                effect->env[0] = r1;
                effect->env[1] = g1;
                effect->env[2] = b1;
                render = &effect->render;
                *render = g_effectRenderDefaults;
                render->WallBehavior = entry->wallBehavior;
                render->InstanceBehavior = entry->instanceBehavior;
                render->GroundBehavior = entry->groundBehavior;
                render->GravityAcceleration = Rumble_SamplePackedFloatRange(*(PackedFloatRange *)&(*(CharacterScreenCell *)&entry->motion->gravityHi));
#if defined(VERSION_EU)
                render->BounceReturnEnergy = Menu_ExpandFloatHighWord(entry->motion->bounceEnergy);
                render->GroundFriction = Menu_ExpandFloatHighWord(entry->motion->groundFriction);
                render->AirFriction = Menu_ExpandFloatHighWord(entry->motion->airFriction);
                render->WaterFriction = Menu_ExpandFloatHighWord(entry->motion->waterFriction);
#else
                render->BounceReturnEnergy = Menu_ExpandFloatHighWord(entry->motion->bounceEnergy);
                render->GroundFriction = Menu_ExpandFloatHighWord(entry->motion->groundFriction);
                render->AirFriction = Menu_ExpandFloatHighWord(entry->motion->airFriction);
                render->WaterFriction = Menu_ExpandFloatHighWord(entry->motion->waterFriction);
#endif
                if (render->WallBehavior == 8 || render->GroundBehavior == 8 || render->InstanceBehavior == 8) {
                    if (effect->owner != 0 && ((LevelActor *)effect->owner)->kind == 1 && (((LevelActor *)effect->owner)->flags & 0x300000)) {
                        Playerai_StartTransitionState(((Player *)((LevelActor *)effect->owner)->controller), effect);
                    }
                }
                if (kind == 257 || kind == 296) {
                    render->dwFlags |= 4;
                }
                if (entry->flags & 0x100000) {
                    render->dwFlags |= 0x40000;
                }
                if (entry->flags & 0x800) {
                    render->dwFlags |= 0x2000;
                }
                if (entry->flags & 0x40000000) {
                    render->dwFlags |= 0x4000;
                }
                if (entry->fade->rangeMode != 3) {
                    Shared_Particle *other;

                    for (other = sys->groups.head; other != 0; other = other->groupNext) {
                        if (other->desc == effect->desc) {
                            break;
                        }
                    }
                    if (other != 0) {
                        List_InsertBeforeIntrusive(&sys->groups, other, effect);
                    } else if (effect->desc->flags & 0x2000) {
                        List_PrependIntrusive(&sys->groups, effect);
                    } else {
                        List_AppendIntrusive(&sys->groups, effect);
                    }
                    effect->flags |= 0x1000000;
                }
                if ((g_effectCallbackFlags[entry->events->effects[4]].flags & 1) || kind == 104) {
                    render->dwFlags |= 0x20000;
                }
                vel = &effect->inst.velocity;
                Graphu64_ScaleVector(vel, vel, g_particleInitialVelocityScale);
                if ((kind == 45 || kind == 79) && (sourceType = *(u8 *)source) == 2) {
                    aimTarget = &g_currentActorInstance;
                    if (aimTarget->actor != 0) {
                        effect_spawn_aim(effect, aimTarget, vel, sourceType);
                    }
                }
                effect->scale = g_particleInitialMotionValue;
                Particle_Attach((Shared_Particle *)effect, 0, 0);
                if (entry->ribbonId != -1) {
                    Fx_AttachActorRibbon(&g_gameSession.hud.actors, effect, entry->ribbonId);
                }
                if (entry->lightId != -1) {
                    effect->handle = Gdynlight_AllocateWorldLight(&g_dynamicLightPool, entry->lightId);
                } else {
                    effect->handle = 0;
                }
                if (!(effect->flags & 0x200000) && (sound = entry->sound) != 0) {
                    switch (effect->inst.type) {
                        case 34:
                        case 95:
                        case 96:
                            Particle_PlayAttachedSound(effect, sound);
                            break;
                        default:
                            SoundElement_PlaySoundAtPosition(sound, effect->inst.pos, 0, -1);
                            break;
                    }
                }
                sys->last = effect;
            }
        }
    }
    g_collisionCurrentActor = &g_currentActorInstance;
    return count;
}

/* PARTICLE_UPDATESYSTEM.CPP */
struct CGameDynamicLight_t;
extern struct CGameDynamicLight_t g_dynamicLightPool;

/* Marks an actor as crowded when something is near it: a world object that is active within 256 units, a player other than the actor's owner with positive health within 256 units, or another actor of type 12 or 34 from the given list within 512 units (all compared as squared distances). */

void Particle_MarkCrowdedActor(s32 particleContext, Shared_Particle *actor, Shared_Particle **others, s32 count) {
    CVector3 delta;
    Shared_World *world;
    SharedPlayer *player;
    s32 i;
    s32 objectCount;

    world = &g_world;
    objectCount = world->kind1Count;
    for (i = 0; i < objectCount; i++) {
        if (world->kind1[i]->active > 0) {
            Graphu64_SubtractVectors(&delta, &world->kind1[i]->position0, &actor->inst.pos);
            if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z <= 65536.0f) {
                actor->life = 1;
                return;
            }
        }
    }
    for (player = g_transientPlayerList.actorList; player != 0; player = player->views16E0.view16E0_1.next) {
        if ((void *)actor->owner != (void *)player && player->views5E4.view5E4_2.health > 0) {
            Graphu64_SubtractVectors(&delta, &player->views0.view8_4.position, &actor->inst.pos);
            if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z <= 65536.0f) {
                actor->life = 1;
                return;
            }
        }
    }
    for (i = 0; i < count; i++) {
        if (others[i] != actor && (others[i]->inst.type == 12 || others[i]->inst.type == 34)) {
            Graphu64_SubtractVectors(&delta, &others[i]->inst.pos, &actor->inst.pos);
            if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z <= 262144.0f) {
                actor->life = 1;
                return;
            }
        }
    }
}

extern const f32 g_particleLightColorFadeScale,g_particleLightMovementDistanceSquared;


/* Frees a particle: runs its end hook (and its swoosh teardown when it has swooshes), hands its dynamic light back to
 * g_dynamicLightPool, drops one owner count, unlinks it from its active list onto the free list and, when flagged, from the
 * draw list. */
static __inline__ void Particle_Free(EffectSystem *world, Shared_Particle *p) {
    Particle_FinishActorEffects(p);
    if (p->ribbonReferenceCount) {
        Particle_UpdateMatrix(p);
        Fx_DetachParticleSwooshes(&g_gameSession.hud.actors, p);
    }
    if (((struct CDLight_t *)p->handle)) {
        Gdynlight_ReleaseLight(&g_dynamicLightPool, (s32)((struct CDLight_t *)p->handle));
        p->handle = 0;
    }
    if (p->ownerId) {
        --*p->ownerId;
    }
    p->flags &= 0xFDFFFEFF;
    List_RemoveIntrusive(p->list, p);
    p->list = 0;
    List_PrependIntrusive(&world->free, p);
    if (p->flags & 0x01000000) {
        List_RemoveIntrusive(&world->groups, p);
    }
}
/* Steps the particle system once: marks every particle on the three active lists, then (outside a pause) advances the
 * ones in the play box (or of type 0x41E), fires the impact events of the expired ones and frees them, and lets each
 * collected type 34 particle react to the others and each type 87 particle expire the non-87 ones within range. */
void Particle_UpdateSystem(EffectSystem *world) {
    Shared_Particle *colliders[128];
    Shared_Particle *stepped[128];
    struct IntPair value;
    CVector3 delta;
    Shared_Particle *p;
    Shared_Particle *node;
    Shared_Particle *focus;
    Shared_Particle **begin;
    Shared_ParticleDesc *effect;
    struct CDLight_t *light;
    s32 count;
    s32 idx;
    s32 pairCount;
    s32 i;
    s32 j;
    s32 event;
    u32 particleType;
    u32 eventType;
    u32 soundType;
    f32 savedStep;
    count = 0;
    savedStep = g_frameElapsedTime;
    for (idx = 0; idx < 3; idx++) {
        for (node = (Shared_Particle *)(world->lists + idx)->head; node != 0; node = node->next) {
            node->flags = (node->flags & 0xFFEFFFFF) | 0x02000000;
            stepped[count++] = node;
        }
    }
    if (g_frontendScreenStatus.status[7] != 0 || g_world.frozen != 0) {
        return;
    }
    g_frameElapsedTime = savedStep;
    g_frameElapsedTime = savedStep * g_particleSimulationTimeScale;
    pairCount = 0;
    for (idx = 0; idx < count; idx++) {
        p = stepped[idx];
        if ((p->flags & 0x02000100) != 0x02000100) {
            continue;
        }
        p->flags &= 0xFFEFFF87;
        if (((struct CDLight_t *)p->handle)) {
            ((struct CDLight_t *)p->handle)->m_bEnabled = 0;
        }
        if (p->time < (f32)p->life && p->life != 1 && !(p->flags & 0x1000)) {
            if ((g_cameraVolumeBounds.max.x > p->inst.pos.x && g_cameraVolumeBounds.max.y > p->inst.pos.y && g_cameraVolumeBounds.max.z > p->inst.pos.z &&
                 g_cameraVolumeBounds.min.x <= p->inst.pos.x && g_cameraVolumeBounds.min.y <= p->inst.pos.y && g_cameraVolumeBounds.min.z <= p->inst.pos.z) ||
                p->inst.type == 1054) {
                Particle_Update(p);
                light = ((struct CDLight_t *)p->handle);
                if (light) {
                    light->m_bEnabled = 1;
                    light->x = p->inst.pos.x;
                    light->y = p->inst.pos.y;
                    light->z = p->inst.pos.z;
                    light->m_ColorFade = p->alpha * g_particleLightColorFadeScale;
                }
                p->time += g_frameElapsedTime;
            } else {
                if (!(p->flags & 0x100)) {
                    continue;
                }
                if (!(p->flags & 0x800)) {
                    Particle_Free(world, p);
                }
            }
        } else {
            effect = p->desc;
            event = Particle_HasSurfaceFlag(p) ? 12 : 10;
            particleType = ((struct Shared_ParticleEvents *)effect->events)->particles[event];
            eventType = ((struct Shared_ParticleEvents *)effect->events)->effects[event];
            value = ((struct Shared_ParticleEvents *)effect->events)->parameters[event];
            soundType = ((struct Shared_ParticleEvents *)effect->events)->sounds[event];
            if (eventType != 0xFFFF) {
                Events_DeliverContactEffect(p, p, eventType, -1, *(CVector3 *)&(p->inst.pos), *(ContactEffectStyle *)&(value));
            }
            if (particleType != 0xFFFF) {
                Particle_SpawnChildEffect(p, particleType, p->space, 1);
            }
            if (soundType != 0xFFFF) {
                SoundElement_PlaySoundAtPosition(soundType, p->inst.pos, 0, -1);
            }
            if (!(p->flags & 0x100)) {
                continue;
            }
            if (!(p->flags & 0x800)) {
                Particle_Free(world, p);
            }
        }
        if (p->flags & 0x100) {
            switch (p->inst.type) {
            case 12:
            case 34:
            case 87:
                colliders[pairCount++] = p;
                break;
            }
        }
    }
    if (pairCount != 0) {
        begin = colliders;
        for (i = 0; i < pairCount; i++) {
            focus = begin[i];
            switch (focus->inst.type) {
            case 34:
                Particle_MarkCrowdedActor((s32)world, focus, begin, pairCount);
                break;
            case 87:
                for (j = 0; j < pairCount; j++) {
                    p = begin[j];
                    if (p->inst.type != 87) {
                        Graphu64_SubtractVectors(&delta, &p->inst.pos, &focus->inst.pos);
                        if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z <= g_particleLightMovementDistanceSquared) {
                            p->life = 1;
                        }
                    }
                }
                break;
            case 12:
                break;
            }
        }
    }
    g_frameElapsedTime = savedStep;
}

extern Gfx *g_displayListCursor;
extern GlobalsMenuSetOptionsSceneSelection g_gameplayCameraList;
extern s32 g_playerWeaponClassMode, g_lightingBufferIndex;
extern float g_particleRibbonHeightScale;
extern void Geometry_SetColorDither(s32 ditherMode);

extern void Particle_DrawSprite(Shared_Particle *particle, GameplayCamera *view);
extern void Fx_AddParticleRibbonSamples(RibbonWorld *effectWorld, Shared_Particle *particle, FixedPointMatrix *matrix);
void Particle_DrawRenderList(EffectSystem *world, GameplayCamera *view) {
    Box box;
    CVector3 transformed;
    Shared_Particle *node;
    s32 visible, built;
    f32 zScale, xyScale, xScale, maximum, height, radius;
    f32 minX, maxX, minY, maxY, minZ, maxZ;
    f32 depth;
    GameplayCamera *camera;
    u32 skipAttached;
    if (world->groups.head != 0) {
        gDPPipeSync(g_displayListCursor++);
        gDPSetAlphaDither(g_displayListCursor++, G_AD_NOISE);
        Geometry_SetColorDither(128);
        gDPSetCycleType(g_displayListCursor++, G_CYC_1CYCLE);
        gSPGeometryMode(g_displayListCursor++, 0x60400, 0);
        for (node = (Shared_Particle *)world->groups.head; node != 0; node = node->groupNext) {
            visible = 0;
            built = node->flags & 0x100000;
            if (node->inst.region == 0) {
                if (!(node->flags & 0x400000) && node->desc->renderModel == 0) {
                    zScale = node->size.z;
                    xyScale = node->size.y * zScale;
                    xScale = node->size.x * zScale;
                    if (!(xScale <= xyScale)) xyScale = xScale;
                    maximum = zScale;
                    if (!(xyScale <= maximum)) maximum = xyScale;
                    height = maximum * g_particleRibbonHeightScale;
                    radius = height * g_particleOwnerImpactRadiusAndStrength[0];
                    minX = node->inst.pos.x - radius;
                    box.min.x = minX;
                    maxX = node->inst.pos.x + radius;
                    box.max.x = maxX;
                    minY = node->inst.pos.y - radius;
                    box.min.y = minY;
                    maxY = node->inst.pos.y + height;
                    box.max.y = maxY;
                    minZ = node->inst.pos.z - radius;
                    box.min.z = minZ;
                    maxZ = node->inst.pos.z + radius;
                    box.max.z = maxZ;
                    if (minX < view->clipBounds[1].x && view->clipBounds[0].x < maxX &&
                        minZ < view->clipBounds[1].z && view->clipBounds[0].z < maxZ &&
                        minY < view->clipBounds[1].y && view->clipBounds[0].y < maxY &&
                        Visdata_TestBoxAgainstFrustum(view->clipPlanes, &box)) {
                        visible = 1;
                    }
                } else visible = 1;
            }
            do {
                if (visible) {
                    if (!built) {
                        if (g_playerWeaponClassMode == 1) {
                            camera = g_gameplayCameraList.camera;
                            Graphu64_TransformPoint(camera->worldToView, &node->inst.pos, &transformed);
                            depth = transformed.z;
                            if (depth < 0.0f) depth = -depth;
                            Particle_BuildMatrix((Shared_Particle *)node, &node->mtx[g_lightingBufferIndex], camera, depth);
                        } else {
                            Particle_BuildMatrix((Shared_Particle *)node, &node->mtx[g_lightingBufferIndex], 0, 0.0f);
                        }
                        node->flags |= 0x100000;
                    }
                    if (node->desc->renderModel != 0) Particle_DrawModel((Shared_Particle *)node, view);
                    else Particle_DrawSprite((Shared_Particle *)node, view);
                    if (node->desc->flags & 0x100000) {
                        Particle_DrawGroundShadow((Shared_Particle *)node, view);
                    }
                    if (!node->ribbonReferenceCount || built) break;
                    skipAttached = node->desc->flags & 0x10000;
                } else {
                    if (!node->ribbonReferenceCount || built) break;
                    if (g_playerWeaponClassMode == 1) {
                        camera = g_gameplayCameraList.camera;
                        Graphu64_TransformPoint(camera->worldToView, &node->inst.pos, &transformed);
                        depth = transformed.z;
                        if (depth < 0.0f) depth = -depth;
                        Particle_BuildMatrix((Shared_Particle *)node, &node->mtx[g_lightingBufferIndex], camera, depth);
                    } else {
                        Particle_BuildMatrix((Shared_Particle *)node, &node->mtx[g_lightingBufferIndex], 0, 0.0f);
                    }
                    node->flags |= 0x100000;
                    skipAttached = node->desc->flags & 0x10000;
                }
                if (!skipAttached) {
                    Fx_AddParticleRibbonSamples(&g_gameSession.hud.actors, (Shared_Particle *)node, &node->mtx[g_lightingBufferIndex]);
                }
            } while (0);
        }
        gDPPipeSync(g_displayListCursor++);
        gDPSetCycleType(g_displayListCursor++, G_CYC_2CYCLE);
        Geometry_SetColorDither(0);
        gDPSetAlphaDither(g_displayListCursor++, G_AD_NOTPATTERN);
    }
}

void Particle_ReleaseOwnerEmitters(EffectSystem *world, s32 owner)
{
  Shared_Particle *actor;
  Shared_Particle *next;
  struct Shared_ParticleEvents *actions;
  Shared_ParticleDesc *model;
  struct IntPair params;
  s32 animation;
  s32 effect;
  s32 sound;
  s32 count = 0;
  s32 index;
  actor = (Shared_Particle *)world->lists[1].head;
  while (actor)
  {
    next = actor->next;
    if (((actor->inst.type == 1054) && (actor->flags & 0x100)) && ((s32)actor->owner == owner))
    {
      model = actor->desc;
      actor->flags &= ~0x100;
      index = (Particle_HasSurfaceFlag(actor)) ? (12) : (10);
      actions = (struct Shared_ParticleEvents *)model->events;
      animation = actions->particles[index];
      effect = actions->effects[index];
      params = actions->parameters[index];
      sound = ((struct Shared_ParticleEvents *)model->events)->sounds[index];
      if (effect != 0xFFFF)
      {
        Events_DeliverContactEffect(actor, actor, effect, -1, *(CVector3 *)&(actor->inst.pos), *(ContactEffectStyle *)&(params));
      }
      if (animation != 0xFFFF)
      {
        Particle_SpawnChildEffect(actor, animation, actor->space, 1);
      }
      if (sound != 0xFFFF)
      {
        SoundElement_PlaySoundAtPosition((s16) sound, actor->inst.pos, 0, -1);
      }
      actor->flags |= 0x100;
      if (actor->flags & 0x100)
      {
      if (!(actor->flags & 0x800))
      {
        Particle_FinishActorEffects(actor);
        if (actor->ribbonReferenceCount)
        {
          Particle_UpdateMatrix(actor);
          Fx_DetachParticleSwooshes(&g_gameSession.hud.actors, actor);
        }
        if (actor->handle)
        {
          Gdynlight_ReleaseLight(&g_dynamicLightPool, actor->handle);
          actor->handle = 0;
        }
        if (actor->ownerId)
        {
          --(*actor->ownerId);
        }
        actor->flags &= 0xFDFFFEFF;
        List_RemoveIntrusive(actor->list, actor);
        actor->list = 0;
        List_PrependIntrusive(&world->free, actor);
        if (actor->flags & 0x1000000)
        {
          List_RemoveIntrusive(&world->groups, actor);
        }
      }
      }
      count++;
    }
    actor = next;
  }

  if (count)
  {
    SoundElement_PlayFlatSound(2330);
    SoundElement_PlayFlatSound(2330);
  }
}






void Particle_RetireOwnedActors(EffectSystem *world, void *owner) {
    Shared_Particle *actor, *next;
    Shared_ParticleDesc *definition;
    s32 index;
    s32 animation, effect, sound;
    struct IntPair pair;
    actor = (Shared_Particle *)world->lists[1].head;
    while (actor != 0) {
        next = actor->next;
        if ((actor->inst.type == 1054 || actor->inst.type == 1007) &&
            (actor->flags & 0x100) && (void *)actor->target == owner) {
            definition = actor->desc;
            index = Particle_HasSurfaceFlag(actor) ? 12 : 10;
            animation = ((struct Shared_ParticleEvents *)definition->events)->particles[index];
            effect = ((struct Shared_ParticleEvents *)definition->events)->effects[index];
            pair = ((struct Shared_ParticleEvents *)definition->events)->parameters[index];
            sound = ((struct Shared_ParticleEvents *)definition->events)->sounds[index];
            if (effect != 0xFFFF)
                Events_DeliverContactEffect(actor, actor, effect, -1, *(CVector3 *)&(actor->inst.pos), *(ContactEffectStyle *)&(pair));
            if (animation != 0xFFFF)
                Particle_SpawnChildEffect(actor, animation, actor->space, 1);
            if (sound != 0xFFFF)
                SoundElement_PlaySoundAtPosition((s16)sound, actor->inst.pos, 0, -1);
            if (actor->flags & 0x100) {
                if (!(actor->flags & 0x800)) {
                    Particle_FinishActorEffects(actor);
                    if (actor->ribbonReferenceCount) {
                        Particle_UpdateMatrix(actor);
                        Fx_DetachParticleSwooshes(&g_gameSession.hud.actors, actor);
                    }
                    if (actor->handle) {
                        Gdynlight_ReleaseLight(&g_dynamicLightPool, actor->handle);
                        actor->handle = 0;
                    }
                    if (actor->ownerId) --*actor->ownerId;
                    actor->flags &= 0xFDFFFEFF;
                    List_RemoveIntrusive(actor->list, actor);
                    actor->list = 0;
                    List_PrependIntrusive(&world->free, actor);
                    if (actor->flags & 0x1000000)
                        List_RemoveIntrusive(&world->groups, actor);
                }
            }
        }
        actor = next;
    }
}

/* PARTICLE_HASKINDZEROENTRY.CPP */

/* Returns whether any of the 22 records in g_weaponInfoByType holds, in either of its two three-entry lists, an entry of kind 1 whose id matches the given object's id. */







extern ParticleKindEntrySets *g_weaponInfoByType[];

s32 Particle_HasKindOneEntry(Shared_ParticleInstance *obj) {
    s32 i;
    s32 j;
    ParticleKindIdEntry *entry;

    for (i = 0; i < 22; i++) {
        for (j = 0; j < 3; j++) {
            entry = g_weaponInfoByType[i]->first[j];
            if (entry != 0 && entry->id == obj->type && entry->kind == 1) {
                return 1;
            }
            entry = g_weaponInfoByType[i]->second[j];
            if (entry != 0 && entry->id == obj->type && entry->kind == 1) {
                return 1;
            }
        }
    }
    return 0;
}

/* Accepts special id 0x427 or an id found in either record list with entry kind zero. */








s32 Particle_HasKindZeroEntry(Shared_ParticleInstance *obj) {
    s32 i;
    s32 j;
    ParticleKindIdEntry *entry;

    if (obj->type == 1063) return 1;
    for (i = 0; i < 22; i++) {
        for (j = 0; j < 3; j++) {
            entry = g_weaponInfoByType[i]->first[j];
            if (entry != 0 && entry->id == obj->type && entry->kind == 0) {
                return 1;
            }
            entry = g_weaponInfoByType[i]->second[j];
            if (entry != 0 && entry->id == obj->type && entry->kind == 0) {
                return 1;
            }
        }
    }
    return 0;
}

/* Returns whether any of the 22 records in g_weaponInfoByType holds, in either of its two three-entry lists, an entry of kind 2 whose id matches the given object's id. */

s32 Particle_HasKindTwoEntry(Shared_ParticleInstance *obj) {
    s32 i;
    s32 j;
    ParticleKindIdEntry *entry;

    for (i = 0; i < 22; i++) {
        for (j = 0; j < 3; j++) {
            entry = g_weaponInfoByType[i]->first[j];
            if (entry != 0 && entry->id == obj->type && entry->kind == 2) {
                return 1;
            }
            entry = g_weaponInfoByType[i]->second[j];
            if (entry != 0 && entry->id == obj->type && entry->kind == 2) {
                return 1;
            }
        }
    }
    return 0;
}


extern char g_actorParticleEffectSystem[];



extern s32 SoundElement_PlaySoundAtPosition(s16, CVector3, s32, s32);




struct EffectSystem; struct Shared_Particle; extern void Particle_Release(struct EffectSystem *owner, struct Shared_Particle *releasedEffect);















void Particle_HandlePlayerContact(Shared_Particle *particle, Player *player) {
    Triple scratch;
    struct IntPair pair;
    struct Shared_ParticleEvents *events;
    s32 contactEventIndex;
    s32 contactEffectId;
    s32 model;
    s32 contactSoundId;
    struct Shared_ParticleDesc *particleDescription;

    XPlus_FillMemory(&scratch, 0, 12);
    if (((Shared_Particle *)particle)->inst.type == 1039) {
        SoundElement_PlaySoundAtPosition(3290, ((Player *)player)->pos,
                      (s32)&((Player *)player)->pos, -1);
        Playerai_StartDamageTimer(player, 30.0f, 3.0f,
                     (particle)->owner, 0);
        CScene_StartEventClips(&g_world, &((ControllerProfile *)((Player *)player)->weaponAnimation)->effectPool, 20, *(Triple *)&scratch, g_particleOwnerImpactRadiusAndStrength[1], g_particleOwnerImpactDuration);;
        ((Player *)player)->glow = (&g_particleOwnerImpactDuration)[1];
    }

    particleDescription = (particle)->desc;
    if (Particle_HasSurfaceFlag(particle) != 0) {
        contactEventIndex = 12;
    } else {
        contactEventIndex = 10;
    }
    events = particleDescription->events;
    model = events->particles[contactEventIndex];
    contactEffectId = events->effects[contactEventIndex];
    pair = events->parameters[contactEventIndex];
    contactSoundId = particleDescription->events->sounds[contactEventIndex];
    if (contactEffectId != 0xFFFF) {
        Events_DeliverContactEffect(particle, particle, contactEffectId, -1, *(CVector3 *)&((particle)->inst.pos), *(ContactEffectStyle *)&(pair));
    }
    if (model != 0xFFFF) {
        Particle_SpawnChildEffect(particle, model, (particle)->space, 1);
    }
    if (contactSoundId != 0xFFFF) {
        SoundElement_PlaySoundAtPosition((s16)contactSoundId, (particle)->inst.pos, 0, -1);
    }
    Particle_Release(&g_actorParticleEffectSystem[0], particle);
    Particle_StopSound(particle);
}

void Particle_EncodeRenderLayer(Shared_Particle *actor, s32 *renderFlags) {
    s32 result;

    result = 0;
    if (((actor)->desc->flags) & 0x02000000) {
        if ((actor)->flags & 2) {
            result = 2;
        } else if (g_gameSettings.bloodMode == 2) {
            result = 1;
        }
    }
    *renderFlags |= result << 30;
}

/* PARTICLE_RELEASEOWNERLISTONEEFFECTS.CPP */












extern char g_actorParticleEffectSystem[];

struct EffectSystem; struct Shared_Particle; extern void Particle_Release(struct EffectSystem *owner, struct Shared_Particle *releasedEffect);

extern CVector3 g_particleZeroVector;




/* Apply resource indices and dispatch the optional object effect. */


/* Adds acceleration along a direction and clamps the resulting speed to its configured limit. */


 void Graphu64_AddVec3(CVector3 *,CVector3 *,CVector3 *);

/* Transform the measured attachment position and direction into the target frame. */
/* Exported symbol for the collision owner's origin subobject (+8). */


/** Return the word. */
int Particle_GetLastSpawnedEffect(struct EffectSystem *effectSystem) {
    return (s32)effectSystem->last;
}

void Particle_ReleaseOwnerListOneEffects(struct EffectSystem *effectSystem, s32 ownerAddress) {
    s32 *referenceCount;
    s32 light;
    s32 flags;
    u16 kind;
    Shared_Particle *next;
    Shared_Particle *effect;

    effect = effectSystem->lists[1].head;
    if (effect != 0) {
        do {
            kind = effect->inst.type;
            next = effect->next;
            if ((kind == 1054) || (kind == 1007)) {
                flags = effect->flags;
                if ((flags & 0x100) && (effect->owner == (void *)ownerAddress) && !(flags & 0x800)) {
                    Particle_FinishActorEffects(effect);
                    if (effect->ribbonReferenceCount != 0) {
                        Particle_UpdateMatrix(effect);
                        Fx_DetachParticleSwooshes(&g_gameSession.hud.actors, effect);
                    }
                    light = effect->handle;
                    if (light != 0) {
                        Gdynlight_ReleaseLight(&g_dynamicLightPool, light);
                        effect->handle = 0;
                    }
                    referenceCount = effect->ownerId;
                    if (referenceCount != 0) {
                        *referenceCount -= 1;
                    }
                    effect->flags = effect->flags & 0xFDFFFEFF;
                    List_RemoveIntrusive(effect->list, effect);
                    effect->list = 0;
                    List_PrependIntrusive(&effectSystem->free, effect);
                    if (effect->flags & 0x01000000) {
                        List_RemoveIntrusive(&effectSystem->groups, effect);
                    }
                }
            }
            effect = next;
        } while (effect != 0);
    }
}

s32 Particle_CountOwnerListOneEffects(struct EffectSystem *effectSystem, s32 ownerAddress) {
    Shared_Particle *record;
    s32 count;
    u16 v;

    record = effectSystem->lists[1].head;
    count = 0;
    if (record != 0) {
        do {
            v = record->inst.type;
            if (((v == 1007) || (v == 1054)) && (record->owner == (void *)ownerAddress)) {
                count += 1;
            }
            record = record->next;
        } while (record != 0);
    }
    return count;
}

void Particle_ReleaseOwnerListTwoEffects(struct EffectSystem *effectSystem, s32 ownerAddress) {
    s32 *referenceCount;
    s32 light;
    s32 flags;
    u16 kind;
    Shared_Particle *next;
    Shared_Particle *effect;

    effect = effectSystem->lists[2].head;
    if (effect != 0) {
        do {
            kind = effect->inst.type;
            next = effect->next;
            if (((kind == 1044) || (kind == 1069)) &&
                (effect->owner == (void *)ownerAddress)) {
                flags = effect->flags;
                if (flags & 0x100) {
                  if (!(flags & 0x800)) {
                    Particle_FinishActorEffects(effect);
                    if (effect->ribbonReferenceCount != 0) {
                        Particle_UpdateMatrix(effect);
                        Fx_DetachParticleSwooshes(&g_gameSession.hud.actors, effect);
                    }
                    light = effect->handle;
                    if (light != 0) {
                        Gdynlight_ReleaseLight(&g_dynamicLightPool, light);
                        effect->handle = 0;
                    }
                    referenceCount = effect->ownerId;
                    if (referenceCount != 0) {
                        *referenceCount -= 1;
                    }
                    effect->flags =
                        effect->flags & 0xFDFFFEFF;
                    List_RemoveIntrusive(effect->list, effect);
                    effect->list = 0;
                    List_PrependIntrusive(&effectSystem->free, effect);
                    if (effect->flags & 0x01000000) {
                        List_RemoveIntrusive(&effectSystem->groups, effect);
                    }
                  }
                }
            }
            effect = next;
        } while (effect != 0);
    }
}

int Particle_GetEffectResource(void *particle) {
    Shared_Particle *actor = particle;
    return (int)actor->owner;
}

s32 Particle_GetRenderLayer(void *particle) {
    Shared_Particle *object = particle;
    s32 result;

    result = 0;
    if ((object->desc->flags) & 0x02000000) {
        if (object->flags & 2) {
            result = 2;
        } else if (g_gameSettings.bloodMode == 2) {
            result = 1;
        }
    }
    return result;
}

void Particle_InitializeObjectLinks(void *particleStorage) {
    Shared_Particle *particle = particleStorage;
    particle->inst.definition = (ActorDefinitionHeader *)&g_particleActorDefinition;
    particle->inst.kind = 2;
    particle->flags = 0;
    particle->sound = 0;
    particle->list = 0;
}

void Particle_ReleaseObjectAndSound(void *object) {
    Particle_Release(&g_actorParticleEffectSystem[0], object);
    Particle_StopSound(object);
}



extern s32 SoundElement_PlaySoundAtPosition(s16, CVector3, s32, s32);
void Particle_SpawnAtSharedContactPoint(Shared_Particle *source, s32 kind) {
    CQuatern q;
    CVector3 pos;

    if ((source->desc->flags & 0x10) != 0) {
        pos = g_particleZeroVector;
    } else {
        pos = source->inst.velocity;
    }
    q = Graphu64_BuildDirectionQuaternion(&pos);
    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], source,
                  source->owner,
                  (s32 *)source->ownerId,
                  (s32)source->target, kind,
                  pos, q, *(CVector3 *)&g_particlePrimaryContactPosition, 0, *(s32 *)(&g_particlePrimaryContactPosition + 1),
                  (source->flags & 0x200006) | 1);
}

void Particle_SpawnWithModeMinusThree(Shared_Particle *source, s32 kind) {
    CQuatern rotation;
    CVector3 position;

    if ((source->desc->flags & 0x10) != 0) {
        position = g_particleZeroVector;
    } else {
        position = source->inst.velocity;
    }
    rotation = Graphu64_BuildDirectionQuaternion(&position);
    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], source,
                  source->owner,
                  (s32 *)source->ownerId,
                  (s32)source->target, kind,
                  position, rotation, *(CVector3 *)&g_particleSecondaryContactPosition, 0, -3,
                  (source->flags & 0x200006) | 1);
}

void Particle_SpawnWithModeMinusTwo(Shared_Particle *source, s32 kind) {
    CQuatern rotation;
    CVector3 position;

    if ((source->desc->flags & 0x10) != 0) {
        position = g_particleZeroVector;
    } else {
        position = source->inst.velocity;
    }
    rotation = Graphu64_BuildDirectionQuaternion(&position);
    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], source,
                  source->owner,
                  (s32 *)source->ownerId,
                  (s32)source->target, kind,
                  position, rotation, *(CVector3 *)&g_particleSecondaryContactPosition, 0, -2,
                  (source->flags & 0x200006) | 1);
}

void Particle_SpawnWithModeMinusFive(Shared_Particle *source, s32 kind) {
    CQuatern rotation;
    CVector3 position;

    if (source->desc->flags & 0x10) {
        position = g_particleZeroVector;
    } else {
        position = source->inst.velocity;
    }
    rotation = Graphu64_BuildDirectionQuaternion(&position);
    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], source,
                  source->owner,
                  (s32 *)source->ownerId,
                  (s32)source->target, kind,
                  position, rotation, *(CVector3 *)&g_particleTertiaryContactPosition, 0, -5,
                  (source->flags & 0x200006) | 1);
}

void Particle_InitializeAttachmentsAndSound(Shared_Particle *actor, Shared_ParticleDesc *parameters) {
    s32 soundId;
    s8 lightType;
    s8 resourceId;
    u16 unusedValue;
    Particle_Attach((Shared_Particle *)actor, 0, 0);
    resourceId = parameters->ribbonId;
    if (resourceId != -1) {
        Fx_AttachActorRibbon(&g_gameSession.hud.actors, actor, resourceId);
    }
    lightType = parameters->lightId;
    actor->handle = lightType == -1 ? 0 : Gdynlight_AllocateWorldLight(&g_dynamicLightPool, lightType);
    if (!(actor->flags & 0x200000) && (soundId = parameters->sound, (soundId != 0))) {
        switch(actor->inst.type) {
        case 34: case 95: case 96:
            Particle_PlayAttachedSound(actor,soundId); break;
        default:
            SoundElement_PlaySoundAtPosition(soundId, actor->inst.pos, 0, -1); break;
        }
    }
}

void Particle_ReleaseAttachments(Shared_Particle *particle) {
    s32 attachmentLightHandle;

    if (particle->ribbonReferenceCount != 0) {
        Particle_UpdateMatrix(particle);
        Fx_DetachParticleSwooshes(&g_gameSession.hud.actors, particle);
    }
    attachmentLightHandle = particle->handle;
    if (attachmentLightHandle != 0) {
        Gdynlight_ReleaseLight(&g_dynamicLightPool, attachmentLightHandle);
        particle->handle = 0;
    }
}

void Particle_ApplyDirectionalAcceleration(Shared_Particle *particle) {
 CVector3 delta, direction;
 CVector3 *velocity, *dir;
 int condition;
 f32 accel, length, limit;
 accel=RW_BITS_TO_FLOAT(particle->desc->motion->acceleration);
 if(accel != 0.0f) {
 dir=&direction;
 direction=particle->direction;
 Graphu64_ScaleVector(&delta,dir,accel);
 velocity=&particle->inst.velocity;
 Graphu64_AddVec3(velocity,velocity,&delta);
 length=Gu_Sqrtf(particle->inst.velocity.x*particle->inst.velocity.x+particle->inst.velocity.y*particle->inst.velocity.y+particle->inst.velocity.z*particle->inst.velocity.z);
 limit=RW_BITS_TO_FLOAT(particle->desc->motion->speedLimit);
 if(accel>0.0f) { if(!(limit<length)) goto done; } else { if(!(length<limit)) goto done; } Graphu64_ScaleVector(velocity,dir,limit); done:;
 }
}

void Particle_FlagKind86ModeTwo(void *particle, s32 mode) {
    Shared_Particle *effect = particle;
    if (effect->inst.type == 86 && mode == 2) {
        effect->flags |= 0x04000000;
    }
}

void Particle_CaptureSharedTrailState(void *particle) {
    ((Shared_Particle *)particle)->flags |= 0x20000;
    ((Shared_Particle *)particle)->inst.pos = (*(CVector3 *)&g_currentActorInstance.vec8);
    ((Shared_Particle *)particle)->inst.velocity = (*(CVector3 *)&g_currentActorInstance.particleVelocity);
}

void Particle_AttachToCurrentTarget(void *particle, f32 *attachmentMatrix, s32 attachmentMode) {
    f32 source[16];
    f32 matrix[16];
    CVector3 direction;
    Shared_Particle *actor;
    s32 mode;
    LevelActor *current;
    f32 *matrix_ptr;
    CVector3 *scene;
    CVector3 *direction_ptr;

    actor = particle;
    mode = attachmentMode;
    current = g_currentActorInstance.instance0;
    if (attachmentMatrix != 0) {
        Graphu64_InvertAffineMatrix(matrix, attachmentMatrix);
    } else {
        Graphu64_ConvertMatrixToFloat(source,
            &((FixedPointMatrix *)current->animationMatrices)[g_currentActorInstance.value]);
        Graphu64_InvertAffineMatrix(matrix, source);
    }
    matrix_ptr = matrix;
    scene = &g_particleContactState;
    Graphu64_TransformPoint(matrix_ptr, scene, &((Shared_Particle *)actor)->attachmentPosition);
    direction_ptr = &direction;
    direction = ((ParticleAttachmentState *)((char *)scene - ((char *)&((ParticleAttachmentState *)0)->origin - (char *)0)))->direction;
    Graphu64_NormalizeVec3((f32 *)direction_ptr);
    Graphu64_TransformDirection(matrix_ptr, direction_ptr, &((Shared_Particle *)actor)->inst.velocity);
    ((Shared_Particle *)actor)->target = current;
    ((Shared_Particle *)actor)->flags |= 0x10000;
    ((Shared_Particle *)actor)->collisionNode = ((ParticleAttachmentState *)((char *)scene - ((char *)&((ParticleAttachmentState *)0)->origin - (char *)0)))->frameBytes[3];
    if (((Shared_Particle *)actor)->inst.type == 86 && mode == 2) {
        ((Shared_Particle *)actor)->flags |= 0x04000000;
    }
}

/** Return eventId, but treat the sentinel value 0xA as 0. */
s32 Particle_MapEventTenToZero(s32 eventId) {
    if (eventId == 10) {
        return 0;
    }
    return eventId;
}

void Particle_DispatchActorContactEvents(Shared_Particle *actor) {
    struct IntPair pair;
    struct Shared_ParticleEvents *events;
    s32 surfaceEventIndex;
    s32 effectId;
    s32 model;
    s32 soundId;
    struct Shared_ParticleDesc *particleDescription;

    particleDescription = (actor)->desc;
    if (Particle_HasSurfaceFlag(actor) != 0) {
        surfaceEventIndex = 12;
    } else {
        surfaceEventIndex = 10;
    }
    events = particleDescription->events;
    model = events->particles[surfaceEventIndex];
    effectId = events->effects[surfaceEventIndex];
    pair = events->parameters[surfaceEventIndex];
    soundId = particleDescription->events->sounds[surfaceEventIndex];
    if (effectId != 0xFFFF) {
        Events_DeliverContactEffect(actor, actor, effectId, -1, *(CVector3 *)&((actor)->inst.pos), *(ContactEffectStyle *)&(pair));
    }
    if (model != 0xFFFF) {
        Particle_SpawnChildEffect(actor, model, (actor)->space, 1);
    }
    if (soundId != 0xFFFF) {
        SoundElement_PlaySoundAtPosition((s16)soundId,
                      (actor)->inst.pos, 0, -1);
    }
}

void Particle_DispatchSpatialContactEvents(Shared_Particle *particle) {
    struct IntPair pair;
    struct Shared_ParticleEvents *events;
    s32 surfaceEventIndex;
    s32 effectId;
    s32 childParticleType;
    s32 soundId;
    struct Shared_ParticleDesc *particleDescription;

    particleDescription = (particle)->desc;
    if (Particle_HasSurfaceFlag(particle) != 0) {
        surfaceEventIndex = 13;
    } else {
        surfaceEventIndex = 11;
    }
    events = particleDescription->events;
    childParticleType = events->particles[surfaceEventIndex];
    effectId = events->effects[surfaceEventIndex];
    pair = events->parameters[surfaceEventIndex];
    soundId = particleDescription->events->sounds[surfaceEventIndex];
    if (effectId != 0xFFFF) {
        Events_DeliverContactEffect(particle, particle, effectId, -1, *(CVector3 *)&((particle)->inst.pos), *(ContactEffectStyle *)&(pair));
    }
    if (childParticleType != 0xFFFF) {
        Particle_SpawnChildEffect(particle, childParticleType, (particle)->space, 1);
    }
    if (soundId != 0xFFFF) {
        SoundElement_PlaySoundAtPosition((s16)soundId,
                      (particle)->inst.pos,
                      (s32)&(particle)->inst.pos, (s32)particle);
    }
}

void Particle_DispatchParticleContactEvents(Shared_Particle *particle) {
    struct IntPair pair;
    struct Shared_ParticleEvents *events;
    s32 surfaceEventIndex;
    s32 effectId;
    s32 childParticleType;
    s32 soundId;
    struct Shared_ParticleDesc *particleDescription;

    particleDescription = (particle)->desc;
    if (Particle_HasSurfaceFlag(particle) != 0) {
        surfaceEventIndex = 12;
    } else {
        surfaceEventIndex = 10;
    }
    events = particleDescription->events;
    childParticleType = events->particles[surfaceEventIndex];
    effectId = events->effects[surfaceEventIndex];
    pair = events->parameters[surfaceEventIndex];
    soundId = particleDescription->events->sounds[surfaceEventIndex];
    if (effectId != 0xFFFF) {
        Events_DeliverContactEffect(particle, particle, effectId, -1, *(CVector3 *)&((particle)->inst.pos), *(ContactEffectStyle *)&(pair));
    }
    if (childParticleType != 0xFFFF) {
        Particle_SpawnChildEffect(particle, childParticleType, (particle)->space, 1);
    }
    if (soundId != 0xFFFF) {
        SoundElement_PlaySoundAtPosition((s16)soundId,
                      (particle)->inst.pos, 0, -1);
    }
}

int Particle_HasSurfaceFlag(Shared_Particle *particle) {
    char pad[0x10];
    return ((u32)(particle)->flags >> 2) & 1;
}

int Particle_ReturnZero(void) {
    char pad[0x10];
    return 0;
}

/* Size scale for a particle seen through a camera: the out-of-line copy of the inline particleCameraScale
 * (particle/CAMERA_SCALE.H), which Particle_BuildMatrix inlines. */
f32 Particle_CameraScale(Shared_Particle *particle, f32 distFromCamera, GameplayCamera *camera) {
    return particleCameraScale(particle, distFromCamera, camera);
}

/* PARTICLE_SPAWNINTERPOLATEDTRAIL.CPP */


void Particle_UpdateMatrix(Shared_Particle *particle) {
    CVector3 delta;
    GameplayCamera *camera;
    f32 amount;
    s32 *state;

    state = &g_playerWeaponClassMode;
    if (state[0] == 1) {
        camera = (GameplayCamera *)state[-4];
        Graphu64_TransformPoint(camera->worldToView, &particle->inst.pos, &delta);
        amount = delta.z;
        if (amount < 0.0f) {
            amount = -amount;
        }
        Particle_BuildMatrix(particle, &particle->mtx[g_lightingBufferIndex], camera, amount);
    } else {
        Particle_BuildMatrix(particle, &particle->mtx[g_lightingBufferIndex], 0, 0.0f);
    }
    particle->flags |= 0x100000;
}

/* Spawns a sequence of effects along an object's motion segment. */

extern char g_actorParticleEffectSystem[];

void Particle_SpawnInterpolatedTrail(Shared_Particle *actor) {
        CQuatern rotation;
        int hasTrailSegments;
        CVector3 delta;
        CVector3 step;
        unsigned int actor_2;
        CVector3 position;
        f32 divisor;
        s32 i;
        s8 count;
        void *system;
        count = actor->desc->fade->trailSegmentCount;
        if (count > 0) {
                position = actor->inst.velocity;
                rotation = Graphu64_BuildDirectionQuaternion((f32 *)&position);
                Graphu64_SubtractVectors(&delta, &actor->inst.pos, &actor->prevPos);
                system = &g_actorParticleEffectSystem[0];
                i = 1;
                hasTrailSegments = i <= count;
                if (hasTrailSegments) {
                        divisor = (f32) count + (&g_particleAveragePositionConstants)[1];
                        do {
    do { Graphu64_ScaleVector(&step, &delta, (f32) i / divisor); Graphu64_AddVec3(&step, &step, &actor->prevPos); actor_2 = actor->inst.type; Particle_SpawnEffectGroup((struct EffectSystem *)system, actor, actor->owner, (s32 *)actor->ownerId, (s32)actor->target, actor_2, *(CVector3 *)&position, *(CQuatern *)&rotation, *(CVector3 *)&step, 0, -1, 0x20E001); i++; } while (0);
                        } while (count >= i);
                }
        }
}

void Particle_PlayAttachedSound(void *soundParticle, s32 soundId) {
    struct CacheResourceNode *node;

    node = ((Shared_Particle *)soundParticle)->sound;
    if (node != 0) {
        if (((CLoopingSoundData *)node)->state == soundId && ((CLoopingSoundData *)node)->value != -1) {
            return;
        }
        Particle_StopSound(soundParticle);
    }
    ((Shared_Particle *)soundParticle)->sound =
        SoundVoicePool_PlaySpatialSound(SoundVoicePool_GetGlobalState(), soundId, &((Shared_Particle *)soundParticle)->inst.pos, &((Shared_Particle *)soundParticle)->inst.pos, -1);
}

void Particle_StopSound(void *a) {
    if (((Shared_Particle *)a)->sound != 0) {
        SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), ((Shared_Particle *)a)->sound);
        ((Shared_Particle *)a)->sound = 0;
    }
}

void Particle_Release(EffectSystem *, Shared_Particle *);

Shared_Particle *Particle_AllocPoolNode(EffectSystem *owner, s32 index) {
    Shared_Particle *node;
    IntrusiveList *slot;
    s32 i;
    Shared_Particle *tail;
    if (owner->free.head == 0) {
        for (i = 0; i <= (index & 0xFF); i++) {
            tail = (Shared_Particle *)(&owner->lists[i])->tail;
            if (tail != 0) {
                Particle_Release((EffectSystem *)owner, (Shared_Particle *)tail);
                break;
            }
        }
    }
    node = (Shared_Particle *)owner->free.head;
    if (node == 0) {
        return 0;
    }
    List_RemoveIntrusive(&owner->free, node);
    slot = &owner->lists[index & 0xFF];
    List_PrependIntrusive(slot, node);
    node->list = slot;
    node->groupNext = 0;
    node->groupPrevious = 0;
    node->flags = 0x100;
    return node;
}

/* 8028308C_3.CPP */



void Particle_Release(EffectSystem *owner, Shared_Particle *releasedEffect) {
    s32 *releaseReferenceCount;
    s32 releasedLight;
    s32 flags;

    flags = releasedEffect->flags;
    if (flags & 0x100) {
        if (!(flags & 0x800)) {
            Particle_FinishActorEffects(releasedEffect);
            if (releasedEffect->ribbonReferenceCount != 0) {
                Particle_UpdateMatrix(releasedEffect);
                Fx_DetachParticleSwooshes(&g_gameSession.hud.actors, releasedEffect);
            }
            releasedLight = releasedEffect->handle;
            if (releasedLight != 0) {
                Gdynlight_ReleaseLight(&g_dynamicLightPool, releasedLight);
                releasedEffect->handle = 0;
            }
            releaseReferenceCount = releasedEffect->ownerId;
            if (releaseReferenceCount != 0) {
                *releaseReferenceCount -= 1;
            }
            releasedEffect->flags =
                releasedEffect->flags & 0xFDFFFEFF;
            List_RemoveIntrusive(releasedEffect->list, releasedEffect);
            releasedEffect->list = 0;
            List_PrependIntrusive(&owner->free, releasedEffect);
            if (releasedEffect->flags & 0x01000000) {
                List_RemoveIntrusive(&owner->groups, releasedEffect);
            }
        }
    }
}

/* 8028308C_4.CPP */
/* Releases the tail of the first nonempty owner list among indices zero through count. */

void Particle_ReleaseFirstHandle(char *obj, unsigned char count) {
    int i;

    for (i = 0; i <= count; i++) {
        IntrusiveList *list = (IntrusiveList *)((obj + i * sizeof(IntrusiveList) + ((char *)&((struct EffectSystem *)0)->lists - (char *)0)));
        if (list->tail != 0) {
            Particle_Release(obj, list->tail);
            return;
        }
    }
}

/* 8028469C.CPP */
void *Particle_FindOwnerEntry(EffectSystem *effectSystem, s32 ownerId, Shared_ParticleDesc *effectEntry) {
    void *record;

    record = effectEntry->fade->listIndex[effectSystem->lists].head;
    if (effectEntry != 0) {
        if (record != 0) {
            do {
                if (((Shared_Particle *)record)->ownerIdAddress == ownerId) {
                    if (((Shared_Particle *)record)->desc == effectEntry) {
                        return record;
                    }
                }
                record = ((Shared_Particle *)record)->next;
            } while (record != 0);
        }
    } else if (record != 0) {
        do {
            if (((Shared_Particle *)record)->ownerIdAddress == ownerId) {
                return record;
            }
            record = ((Shared_Particle *)record)->next;
        } while (record != 0);
    }
    return 0;
}



void Particle_InsertEntryGroup(EffectSystem *effectSystem, Shared_Particle *particleEffect)
{
    Shared_Particle *current;
    s32 key;

    current = effectSystem->groups.head;
    if (current != 0) {
        key = (s32)particleEffect->desc;
loop:
        if (((Shared_Particle *)current)->desc != key) {
            current = ((Shared_Particle *)current)->groupNext;
            if (current != 0) {
                goto loop;
            }
        }
    }

    if (current != 0) {
        List_InsertBeforeIntrusive(&effectSystem->groups, current, particleEffect);
    } else if (particleEffect->desc->flags & 0x2000) {
        List_PrependIntrusive(&effectSystem->groups, particleEffect);
    } else {
        List_AppendIntrusive(&effectSystem->groups, particleEffect);
    }

    particleEffect->flags |= 0x01000000;
}

s32 Particle_RandomInclusiveCount(s32 maximumCount) {
    if (maximumCount != 0) {
        return Graphu64_NextRandom() % (maximumCount + 1);
    }
    return 0;
}

void Particle_AdvanceRandomWhenNonzero(f32 advanceCondition) {
    if (advanceCondition != 0.0f) {
        ((s32 (*)())Graphu64_RandomFloat)();
    }
}

/** Return offset 0x180 only when the nested state word is zero. */
float Particle_GetConditionalFirstValue(Shared_Particle *effect) {
    void *inner = effect->desc;
    if (((Shared_ParticleDesc *)inner)->renderModel != 0) {
        return 0.0f;
    }
    return effect->rot.x;
}

f32 Particle_GetConditionalSecondValue(Shared_Particle *effect) {
    f32 result;
    result = 0.0f;
    if ((effect->desc->renderModel) == 0) {
        result = (effect->rot.y);
    }
    return result;
}

s32 Particle_IsKind2Or86Or273Or294(Shared_Particle *effect) {
    u16 kind;
    s32 val;

    kind = effect->inst.type;
    val = kind;
    if (val == 86) {
        goto ret1;
    }
    if (val >= 87) {
        goto ge_e;
    }
    if (val == 2) {
        goto ret1;
    }
    goto ret0;
ge_e:
    if (val == 273) {
        goto ret1;
    }
    if (val != 294) {
        goto ret0;
    }
ret1:
    return 1;
ret0:
    return 0;
}

s32 Particle_IsKind5To7Or9Or17Or19Or26Or257Or272(Shared_Particle *effect) {
    u16 kind;
    s32 val;

    kind = effect->inst.type;
    val = kind;
    if (val == 17) {
        goto ret1;
    }
    if (val >= 18) {
        goto ge_12;
    }
    if (val < 5) {
        goto ret0;
    }
    if (val < 8) {
        goto ret1;
    }
    if (val == 9) {
        goto ret1;
    }
    goto ret0;
ge_12:
    if (val == 26) {
        goto ret1;
    }
    if (val >= 27) {
        goto ge_1b;
    }
    if (val == 19) {
        goto ret1;
    }
    goto ret0;
ge_1b:
    if (val == 257) {
        goto ret1;
    }
    if (val != 272) {
        goto ret0;
    }
ret1:
    return 1;
ret0:
    return 0;
}

s32 Particle_IsKind8Or13Or18(Shared_Particle *effect) {
    u16 kind;
    s32 val;

    kind = effect->inst.type;
    val = kind;
    if (val == 13) {
        goto ret1;
    }
    if (val >= 14) {
        goto ge_e;
    }
    if (val == 8) {
        goto ret1;
    }
    goto ret0;
ge_e:
    if (val != 18) {
        goto ret0;
    }
ret1:
    return 1;
ret0:
    return 0;
}

void Particle_UpdateForcesAndMotion(Shared_Particle *effect)
{
    CVector3 delta;
    CVector3 direction;
    f32 acceleration;
    f32 speed;
    f32 limit;
    f32 x, y, z;
    CVector3 *velocity;

    Playerai_ApplyPlayerForces(&g_playerViewRenderContext, effect);
    acceleration = Menu_ExpandFloatHighWord(effect->desc->motion->acceleration);
    if (acceleration != 0.0f) {
        direction = effect->direction;
        Graphu64_ScaleVector(&delta, &direction, acceleration);
        Graphu64_AddVec3(&effect->inst.velocity, &effect->inst.velocity, &delta);
        velocity = &effect->inst.velocity;
        x = effect->inst.velocity.x;
        y = effect->inst.velocity.y;
        z = effect->inst.velocity.z;
        speed = Gu_Sqrtf(x * x + y * y + z * z);
        limit = Menu_ExpandFloatHighWord(effect->desc->motion->speedLimit);
        if (acceleration > 0.0f) {
            if (!(limit < speed)) goto finished;
        } else {
            if (!(speed < limit)) goto finished;
        }
        Graphu64_ScaleVector(velocity, &direction, limit);
finished:
        ;
    }
    Particle_UpdateSineMotion(effect, 1.0f);
}


void Particle_CheckNearbyPlayerContacts(Shared_Particle *particle) {
    CVector3 point;
    Player *node;
    void *pointPtr;
    int actorId;
    s16 amount;
    int stop;
    f32 radiusSq;
    f32 heightScale;

    amount = particle->desc->playerContactRadius;
    radiusSq = (f32)amount;
    if (radiusSq <= 0.0f) {
        return;
    }
    radiusSq *= g_particleNearestEffectDistanceTuning;
    node = g_transientPlayerList.actorList;
    radiusSq *= radiusSq;
    if (node == 0) {
        return;
    }

    pointPtr = &point;
    actorId = 1039;
    heightScale = (&g_particleNearestEffectDistanceTuning)[1];
    do {
        point = ((Player *)node)->pos;
        stop = 0;
        if (particle->inst.type != actorId) {
            point.y += Gobjinst_GetActorHeight(node) * heightScale;
        }
        if (Graphu64_GetSquaredDistance(&particle->inst.pos.x, pointPtr) < radiusSq) {
            Particle_HandlePlayerContact(particle, node);
            if (particle->inst.type == actorId) {
                stop = 1;
            }
        }
        if (stop != 0) {
            node = 0;
        } else {
            node = ((Player *)node)->next;
        }
    } while (node != 0);
}

struct CollisionInfo;





s32 Particle_HasClearMotionPath(struct ActorInstanceHeader *particle, GameplayCamera *messageId) {
    struct ActorInstanceHeader saved;
    struct ActorInstanceHeader *instance;
    s32 collisions;

    instance = Gsky_FindScreenMessage((s32)messageId);
    if (instance != 0 && messageId->bobSuppressed == 0) {
        saved = *instance;
        instance->position = messageId->position;
        collisions = Unicol_MoveActorWithCollision(instance, particle->position, &g_defaultProbeMotionSettings);
        *instance = saved;
    } else {
        saved = *particle;
        saved.position = messageId->position;
        collisions = Unicol_MoveActorWithCollision(&saved, particle->position, &g_defaultProbeMotionSettings);
    }
    return collisions == 0;
}

/* Marks nearby objects other than type 87 as active. */

void Particle_MarkNearbyObjects(s32 particleContext, Shared_Particle *center, Shared_Particle **objects, s32 count) {
 f32 d[3]; s32 i; Shared_Particle *o;
 for(i=0;i<count;i++) {
  o=objects[i];
  if(o->inst.type != 0x57) {
   Graphu64_SubtractVectors(d,&o->inst.pos.x,&center->inst.pos.x);
   if(d[0]*d[0]+d[1]*d[1]+d[2]*d[2]<=65536.0f) o->life=1;
  }
 }
}

/* Checks object proximity through type-specific handlers and marks nearby objects active. */

static inline void nearby(s32 particleContext, Shared_Particle *center, Shared_Particle **objects, s32 count) {
 f32 d[3]; s32 i; Shared_Particle *o;
 for(i=0;i<count;i++) {
  o=objects[i];
  if(o->inst.type != 0x57) {
   Graphu64_SubtractVectors(d,&o->inst.pos.x,&center->inst.pos.x);
   if(d[0]*d[0]+d[1]*d[1]+d[2]*d[2]<=65536.0f) o->life=1;
  }
 }
}

void Particle_UpdateNearbyObjectFlags(int context,Shared_Particle **objects,int count) {
 int i; Shared_Particle *obj;
 for(i=0;i<count;i++) {
  obj=objects[i];
  switch(obj->inst.type) {
   case 12: break;
   case 34: Particle_MarkCrowdedActor(context,obj,objects,count); break;
   case 87: nearby(context,obj,objects,count); break;
  }
 }
}

void Particle_AverageOwnerEffectPositions(EffectSystem *effectSystem, s32 ownerId, CVector3 *averagePositionOut) {
    f32 effectCountFloat;
    s32 count;
    u16 v;
    Shared_Particle *record;

    averagePositionOut->x = 0.0f;
    averagePositionOut->y = 0.0f;
    averagePositionOut->z = 0.0f;
    record = effectSystem->lists[1].head;
    count = 0;
    if (record != 0) {
        do {
            v = ((Shared_Particle *)record)->inst.type;
            if (((v == 1054) || (v == 1007)) &&
                (((Shared_Particle *)record)->owner == ownerId) &&
                (((Shared_Particle *)record)->flags & 0x100)) {
                averagePositionOut->x += ((Shared_Particle *)record)->inst.pos.x;
                averagePositionOut->y += ((Shared_Particle *)record)->inst.pos.y;
                count += 1;
                averagePositionOut->z += ((Shared_Particle *)record)->inst.pos.z;
            }
            record = ((Shared_Particle *)record)->next;
        } while (record != 0);
    }
    if (count != 0) {
        effectCountFloat = (f32)count;
        averagePositionOut->x = (f32)(averagePositionOut->x / effectCountFloat);
        averagePositionOut->y = (f32)(averagePositionOut->y / effectCountFloat);
        averagePositionOut->z = (f32)(averagePositionOut->z / effectCountFloat);
    }
}

void Particle_FindNearestForeignEffectDistance(EffectSystem *effectSystem, LevelActor *actor, f32 *distanceOut) {
    f32 distanceSquared;
    Shared_Particle *node;

    *distanceOut = g_particleMaximumSearchDistance;
    node = effectSystem->groups.head;
    if (node != 0) {
        do {
            if (((Shared_Particle *)node)->owner != actor && (((Shared_Particle *)node)->flags & 0x100)) {
                distanceSquared = Graphu64_GetSquaredDistance(&((Shared_Particle *)node)->inst.pos.x, &actor->position0.x);
                if (distanceSquared < *distanceOut) {
                    *distanceOut = distanceSquared;
                }
            }
            node = ((Shared_Particle *)node)->groupNext;
        } while (node != 0);
    }
}

/* PARTICLE_UPDATESINEMOTION_DATA.CPP */



/* PARTICLE_CONTACT_AND_LIGHT_CONSTANTS.CPP */



/* PARTICLE_DRAWMODEL_DATA.CPP */

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)

#endif

/* PARTICLE_DRAWGROUNDSHADOW_DATA.CPP */

#if !(defined(VERSION_US_REV1))
extern const char g_simpPartModelsIndexText[23];
#endif

#if defined(VERSION_US_REV1)

#endif

/* S_SIMPPARTMODELTEXT.CPP */

extern const char s_simpPartModelText[16];

/* PARTICLE_FULL_TURN_CONSTANT.CPP */



/* PARTICLE_OWNER_IMPACT_CONSTANTS.CPP */



/* PARTICLE_EVENT_UNIT_CONSTANT.CPP */



/* PARTICLE_FINDNEARESTFOREIGNEFFECTDISTANCE_DATA.CPP */



#if defined(VERSION_EU_X)
extern float g_foreignEffectDistanceScales[3];
#endif

/* ENEMY_UNIT_FLOAT_WORD.CPP */



/* SCENE_LOADLEVELRESOURCES_DATA.CPP */
#if defined(VERSION_US_REV1)
extern float g_levelParticleScale[3];
#endif

/* G_MINIGUNTEXT.CPP */

#if defined(VERSION_US_REV1)

/* bytes live in the preceding array */

MinigunTextLayout g_minigunText = {
    { 0, 0 },
    { (void *)&g_minigunText, (void *)&g_minigunText, (void *)((char *)&g_actorStateEnd_us_rev1 + 40), (void *)((char *)&g_spawnAIDispatchSpawnChoiceEndFragment + 40), (void *)((char *)&g_actorStateTableEndWords + 40), (void *)&g_minigunText, (void *)((char *)&g_secondaryCollisionContextAnimIdEndFragment + 40), (void *)((char *)&g_deviceRespondToActivationEndFragment + 40), (void *)&g_minigunText, (void *)((char *)&g_movingAIGetDeviceHealthEndFragment + 40), (void *)((char *)&g_defaultCollisionInfoNullEndFragment + 40), (void *)&g_minigunText, (void *)&g_minigunText, (void *)&g_minigunText, (void *)&g_minigunText },
    "E\000\000\000MINIGUN\000",
    1.0f
};
#endif

/* Retained data for this translation unit. */

const float g_particleTrailSpacingAndOwnerHeightConstants[2] = {
    10.24f, 0.5f,
};

const float g_particleUpdateSineMotionConstants[26] = {
    1.0f, 1.0f, 1.0f, 7.0f, 102.399994f, 1.0f,
    153.59999f, 1024.0f, 204.79999f, 0.0012207031f, 0.85999995f, 1.0f,
    0.04f, 1.0f, 3.0e+01f, -40.96f, 51.199997f, 5.0f,
    0.5f, 1.0e+01f, 9.0e+01f, 0.1f, 5.0f, 0.3f,
    1.0f, 3.0e+01f,
};

const float g_particleContactAndLightConstants[11] = {
    0.5f, 2.0f, 512.0f, 0.001953125f, 1.0f, 0.3f,
    0.7f, 0.5f, 0.017453294f, 1.0f, 1.0f,
};
#if !(defined(VERSION_US_REV1))
const char s_simpleParticleObjectIndexText[23] =
    "simp part object index\000";
#endif
#if defined(VERSION_US_REV1)
const char s_particleSimplePartObjectIndexUsRev1[23] =
    "simp part object index";
#endif
#if defined(VERSION_US_REV1)
const char s_particleSimplePartModelsIndexUsRev1[23] =
    "simp part models index";
#endif

const float g_particleFullTurnConstant[1] = {
    6.2831855f,
};

const float g_particleOwnerImpactConstants[3] = {
    10.24f, 1.0f, 45.0f,
};

const float g_particleEventUnitConstant[1] = {
    1.0f,
};

const float g_findNearestForeignEffectDistanceConstants[1] = {
    1e+07f,
};

const float k_enemyUnitFloat[1] = {
    1.0f,
};
#if defined(VERSION_EU_X)
float g_foreignEffectDistanceScales[3] = {
    1.0f, 0.01f, 0.29257143f,
};
#endif
#if defined(VERSION_US_REV1)
float g_levelParticleScale[3] = {
    1.0f, 3.125f, 0.0f,
};
#endif
#if !(defined(VERSION_US_REV1))
const char g_simpPartModelsIndexText[23] =
    "simp part models index\000";
#endif

const char s_simpPartModelText[16] = "simp part model";
