#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/PARTICLE_ATTACHMENT_AND_OWNER_VIEWS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "ENGINE/PARTICLE.H"
#include "COMMON/SHARED_PARTICLEINSTANCE.H"
#include <ultra64.h>
#include "TYPES.H"
#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/MATH_HELPERS.H"
extern void Particle_UpdateMatrix(void *);

extern void Particle_FinishActorEffects(void *actor);

extern void Fx_DetachParticleSwooshes(void *effectWorld, void *detachedEntity);







extern char g_actorParticleEffectSystem;

extern void Particle_Release(void *a, void *b);

extern CVector3 g_particleZeroVector;

extern Params g_particlePrimaryContactPosition;


/* Apply resource indices and dispatch the optional object effect. */


 /* extern */
s32 Gdynlight_AllocateWorldLight(void *, s8);

 /* extern */
void Particle_PlayAttachedSound(void *, s32);

 /* extern */
void Fx_AttachActorRibbon(void *, void *, s8);

/* Adds acceleration along a direction and clamps the resulting speed to its configured limit. */

f32 Gu_Sqrtf(f32);

void Graphu64_ScaleVector(CVector3 *,CVector3 *,f32);

 void Graphu64_AddVec3(CVector3 *,CVector3 *,CVector3 *);

/* Transform the measured attachment position and direction into the target frame. */
extern ParticleAttachmentState g_currentActorInstance;

extern void Graphu64_ConvertMatrixToFloat(f32 *out, void *in);




extern void Graphu64_TransformDirection(void *matrix, void *input, void *output);

extern void Events_DeliverContactEffect(void *, void *, s32, s32, CVector3, struct IntPair);

extern void Particle_SpawnChildEffect(void *, s32, s8, s32);

/** Return the word at offset 0xFC68. */
int Particle_GetLastSpawnedEffect(struct EffectSystem *effectSystem) {
    return (s32)effectSystem->last;
}

void Particle_ReleaseOwnerListOneEffects(struct EffectSystem *effectSystem, s32 ownerAddress) {
    s32 *referenceCount;
    s32 light;
    s32 flags;
    u16 kind;
    ParticleEffect *next;
    ParticleEffect *effect;

    effect = effectSystem->lists[1].head;
    if (effect != 0) {
        do {
            kind = effect->kind;
            next = effect->next;
            if ((kind == 1054) || (kind == 1007)) {
                flags = effect->flags;
                if ((flags & 0x100) && (effect->owner == (void *)ownerAddress) && !(flags & 0x800)) {
                    Particle_FinishActorEffects(effect);
                    if (effect->releaseRequested != 0) {
                        Particle_UpdateMatrix(effect);
                        Fx_DetachParticleSwooshes(&g_actorParticleScene, effect);
                    }
                    light = effect->lightHandle;
                    if (light != 0) {
                        Gdynlight_ReleaseLight(&g_dynamicLightPool, light);
                        effect->lightHandle = 0;
                    }
                    referenceCount = effect->refCount;
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
    ParticleEffect *record;
    s32 count;
    u16 v;

    record = effectSystem->lists[1].head;
    count = 0;
    if (record != 0) {
        do {
            v = record->kind;
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
    ParticleEffect *next;
    ParticleEffect *effect;

    effect = effectSystem->lists[2].head;
    if (effect != 0) {
        do {
            kind = effect->kind;
            next = effect->next;
            if (((kind == 1044) || (kind == 1069)) &&
                (effect->owner == (void *)ownerAddress)) {
                flags = effect->flags;
                if (flags & 0x100) {
                  if (!(flags & 0x800)) {
                    Particle_FinishActorEffects(effect);
                    if (effect->releaseRequested != 0) {
                        Particle_UpdateMatrix(effect);
                        Fx_DetachParticleSwooshes(&g_actorParticleScene, effect);
                    }
                    light = effect->lightHandle;
                    if (light != 0) {
                        Gdynlight_ReleaseLight(&g_dynamicLightPool, light);
                        effect->lightHandle = 0;
                    }
                    referenceCount = effect->refCount;
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
    ObjParticleInitializeAttachmentsAndSound *actor = particle;
    return (int)actor->effectResource;
}

s32 Particle_GetRenderLayer(void *particle) {
    ObjParticleInitializeAttachmentsAndSound *object = particle;
    s32 result;

    result = 0;
    if ((*object->effectFlags) & 0x02000000) {
        if (object->flags & 2) {
            result = 2;
        } else if (g_gameSettings.bloodMode == 2) {
            result = 1;
        }
    }
    return result;
}

void Particle_InitializeObjectLinks(void *particle) {
    (((struct ParticleObjectLinkView *) ((s8 *) particle))->actorDefinition) = &g_particleActorDefinition;
    (((struct ParticleObjectLinkView *) ((s8 *) particle))->kind) = 2;
    (((struct ParticleObjectLinkView *) ((s8 *) particle))->flags) = 0;
    (((struct ParticleObjectLinkView *) ((s8 *) particle))->reservedWord1DC) = 0;
    (((struct ParticleObjectLinkView *) ((s8 *) particle))->reservedWord1E4) = 0;
}

void Particle_ReleaseObjectAndSound(void *object) {
    Particle_Release(&g_actorParticleEffectSystem, object);
    Particle_StopSound(object);
}

#include "particle/PARTICLE_SPAWNEFFECTGROUP.H"
extern CQuatern Graphu64_BuildDirectionQuaternion(CVector3 *);
extern Triple g_particleSecondaryContactPosition;
extern s32 SoundElement_PlaySoundAtPosition(s16, CVector3, s32, s32);
void Particle_SpawnAtSharedContactPoint(ObjParticleInitializeAttachmentsAndSound *source, s32 kind) {
    CQuatern q;
    CVector3 pos;

    if ((*source->effectFlags & 0x10) != 0) {
        pos = g_particleZeroVector;
    } else {
        pos = source->rotation;
    }
    q = Graphu64_BuildDirectionQuaternion(&pos);
    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)source,
                  (struct EffectActor *)source->effectResource,
                  (s32 *)source->effectIndex,
                  source->effectCount, kind,
                  pos, q, *(CVector3 *)&g_particlePrimaryContactPosition.v, 0, g_particlePrimaryContactPosition.w,
                  (source->flags & 0x200006) | 1);
}

void Particle_SpawnWithModeMinusThree(ObjParticleInitializeAttachmentsAndSound *source, s32 kind) {
    CQuatern rotation;
    CVector3 position;

    if ((*source->effectFlags & 0x10) != 0) {
        position = g_particleZeroVector;
    } else {
        position = source->rotation;
    }
    rotation = Graphu64_BuildDirectionQuaternion(&position);
    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)source,
                  (struct EffectActor *)source->effectResource,
                  (s32 *)source->effectIndex,
                  source->effectCount, kind,
                  position, rotation, *(CVector3 *)&g_particleSecondaryContactPosition, 0, -3,
                  (source->flags & 0x200006) | 1);
}

void Particle_SpawnWithModeMinusTwo(ObjParticleInitializeAttachmentsAndSound *source, s32 kind) {
    CQuatern rotation;
    CVector3 position;

    if ((*source->effectFlags & 0x10) != 0) {
        position = g_particleZeroVector;
    } else {
        position = source->rotation;
    }
    rotation = Graphu64_BuildDirectionQuaternion(&position);
    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)source,
                  (struct EffectActor *)source->effectResource,
                  (s32 *)source->effectIndex,
                  source->effectCount, kind,
                  position, rotation, *(CVector3 *)&g_particleSecondaryContactPosition, 0, -2,
                  (source->flags & 0x200006) | 1);
}

void Particle_SpawnWithModeMinusFive(ObjParticleInitializeAttachmentsAndSound *source, s32 kind) {
    CQuatern rotation;
    CVector3 position;

    if (*source->effectFlags & 0x10) {
        position = g_particleZeroVector;
    } else {
        position = source->rotation;
    }
    rotation = Graphu64_BuildDirectionQuaternion(&position);
    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)source,
                  (struct EffectActor *)source->effectResource,
                  (s32 *)source->effectIndex,
                  source->effectCount, kind,
                  position, rotation, *(CVector3 *)&g_particleTertiaryContactPosition, 0, -5,
                  (source->flags & 0x200006) | 1);
}

void Particle_InitializeAttachmentsAndSound(ObjParticleInitializeAttachmentsAndSound *actor, ParamsParticleInitializeAttachmentsAndSound *parameters) {
    s32 soundId;
    s8 lightType;
    s8 resourceId;
    u16 unusedValue;
    Particle_Attach((Shared_Particle *)actor, 0, 0);
    resourceId = parameters->resourceId;
    if (resourceId != -1) {
        Fx_AttachActorRibbon(&g_actorParticleScene, actor, resourceId);
    }
    lightType = parameters->attachmentIndex;
    actor->soundHandle = lightType == -1 ? 0 : Gdynlight_AllocateWorldLight(&g_dynamicLightPool, lightType);
    if (!(actor->flags & 0x200000) && (soundId = parameters->soundId, (soundId != 0))) {
        switch(actor->modelId) {
        case 34: case 95: case 96:
            Particle_PlayAttachedSound(actor,soundId); break;
        default:
            SoundElement_PlaySoundAtPosition(soundId, *(CVector3 *)&actor->positionX, 0, -1); break;
        }
    }
}

void Particle_ReleaseAttachments(void *particle) {
    s32 attachmentLightHandle;

    if (((ObjParticleInitializeAttachmentsAndSound *)particle)->active1D9 != 0) {
        Particle_UpdateMatrix(particle);
        Fx_DetachParticleSwooshes(&g_actorParticleScene, particle);
    }
    attachmentLightHandle = ((ObjParticleInitializeAttachmentsAndSound *)particle)->soundHandle;
    if (attachmentLightHandle != 0) {
        Gdynlight_ReleaseLight(&g_dynamicLightPool, attachmentLightHandle);
        ((ObjParticleInitializeAttachmentsAndSound *)particle)->soundHandle = 0;
    }
}

void Particle_ApplyDirectionalAcceleration(DirectionalAccelerationParticle *particle) {
 CVector3 delta, direction;
 CVector3 *velocity, *dir;
 int condition;
 f32 accel, length, limit;
 accel=RW_BITS_TO_FLOAT(particle->link->params->accel);
 if(accel != 0.0f) {
 dir=&direction;
 direction=particle->direction;
 Graphu64_ScaleVector(&delta,dir,accel);
 velocity=&particle->velocity;
 Graphu64_AddVec3(velocity,velocity,&delta);
 length=Gu_Sqrtf(particle->velocity.x*particle->velocity.x+particle->velocity.y*particle->velocity.y+particle->velocity.z*particle->velocity.z);
 limit=RW_BITS_TO_FLOAT(particle->link->params->limit);
 if(accel>0.0f) { if(!(limit<length)) goto done; } else { if(!(length<limit)) goto done; } Graphu64_ScaleVector(velocity,dir,limit); done:;
 }
}

void Particle_FlagKind86ModeTwo(void *particle, s32 mode) {
    if (((((struct ParticleKindFlagsView *) ((s8 *) particle))->modelId) == 86) && (mode == 2)) {
        (((struct ParticleKindFlagsView *) ((s8 *) particle))->flags) = (s32) ((((struct ParticleKindFlagsView *) ((s8 *) particle))->flags) | 0x04000000);
    }
}

void Particle_CaptureSharedTrailState(void *particle) {
    ((ObjParticleInitializeAttachmentsAndSound *)particle)->flags |= 0x20000;
    ((TrailActor *)particle)->origin = g_particleContactState.first;
    ((TrailActor *)particle)->position = g_particleContactState.second;
}

void Particle_AttachToCurrentTarget(void *particle, f32 *attachmentMatrix, s32 attachmentMode) {
    f32 source[16];
    f32 matrix[16];
    CVector3 direction;
    void *actor;
    s32 mode;
    Shared_ParticleTarget *current;
    f32 *matrix_ptr;
    SceneState *scene;
    CVector3 *direction_ptr;

    actor = particle;
    mode = attachmentMode;
    current = g_currentActorInstance.current;
    if (attachmentMatrix != 0) {
        Graphu64_InvertAffineMatrix(matrix, attachmentMatrix);
    } else {
        Graphu64_ConvertMatrixToFloat(source,
            &current->drawMatrices[g_currentActorInstance.frame]);
        Graphu64_InvertAffineMatrix(matrix, source);
    }
    matrix_ptr = matrix;
    scene = &g_particleContactState;
    Graphu64_TransformPoint(matrix_ptr, scene, &((Shared_Particle *)actor)->attachmentPosition);
    direction_ptr = &direction;
    direction = scene->direction;
    Graphu64_NormalizeVec3((f32 *)direction_ptr);
    Graphu64_TransformDirection(matrix_ptr, direction_ptr, &((Shared_Particle *)actor)->inst.velocity);
    ((Shared_Particle *)actor)->target = current;
    ((Shared_Particle *)actor)->flags |= 0x10000;
    ((Shared_Particle *)actor)->collisionNode = scene->actor_byte;
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

void Particle_DispatchActorContactEvents(void *actor) {
    struct IntPair pair;
    s32 surfaceIndexBytes;
    struct Shared_ParticleEvents *events;
    s32 surfaceEventIndex;
    s32 effectId;
    s32 model;
    s32 soundId;
    struct Shared_ParticleDesc *particleDescription;
    void *eventParameterAddress;
    void *eventHalfwordAddress;

    particleDescription = ((Shared_Particle *)actor)->desc;
    if (Particle_HasSurfaceFlag(actor) != 0) {
        surfaceEventIndex = 12;
    } else {
        surfaceEventIndex = 10;
    }
    surfaceIndexBytes = surfaceEventIndex * 2;
    events = particleDescription->events;
    eventHalfwordAddress = (char *)events + surfaceIndexBytes;
    model = events->particles[surfaceEventIndex];
    effectId = events->effects[surfaceEventIndex];
    eventParameterAddress = (char *)events + (surfaceEventIndex * 8);
    pair = events->parameters[surfaceEventIndex];
    soundId = particleDescription->events->sounds[surfaceEventIndex];
    if (effectId != 0xFFFF) {
        Events_DeliverContactEffect(actor, actor, effectId, -1,
                     ((Shared_Particle *)actor)->inst.pos, pair);
    }
    if (model != 0xFFFF) {
        Particle_SpawnChildEffect(actor, model, ((Shared_Particle *)actor)->space, 1);
    }
    if (soundId != 0xFFFF) {
        SoundElement_PlaySoundAtPosition((s16)soundId,
                      ((Shared_Particle *)actor)->inst.pos, 0, -1);
    }
}

void Particle_DispatchSpatialContactEvents(void *particle) {
    struct IntPair pair;
    s32 surfaceIndexBytes;
    struct Shared_ParticleEvents *events;
    s32 surfaceEventIndex;
    s32 effectId;
    s32 childParticleType;
    s32 soundId;
    struct Shared_ParticleDesc *particleDescription;
    void *eventParameterAddress;
    void *eventHalfwordAddress;

    particleDescription = ((Shared_Particle *)particle)->desc;
    if (Particle_HasSurfaceFlag(particle) != 0) {
        surfaceEventIndex = 13;
    } else {
        surfaceEventIndex = 11;
    }
    surfaceIndexBytes = surfaceEventIndex * 2;
    events = particleDescription->events;
    eventHalfwordAddress = (char *)events + surfaceIndexBytes;
    childParticleType = events->particles[surfaceEventIndex];
    effectId = events->effects[surfaceEventIndex];
    eventParameterAddress = (char *)events + (surfaceEventIndex * 8);
    pair = events->parameters[surfaceEventIndex];
    soundId = particleDescription->events->sounds[surfaceEventIndex];
    if (effectId != 0xFFFF) {
        Events_DeliverContactEffect(particle, particle, effectId, -1,
                     ((Shared_Particle *)particle)->inst.pos, pair);
    }
    if (childParticleType != 0xFFFF) {
        Particle_SpawnChildEffect(particle, childParticleType, ((Shared_Particle *)particle)->space, 1);
    }
    if (soundId != 0xFFFF) {
        SoundElement_PlaySoundAtPosition((s16)soundId,
                      ((Shared_Particle *)particle)->inst.pos,
                      (s32)&((Shared_Particle *)particle)->inst.pos, (s32)particle);
    }
}

void Particle_DispatchParticleContactEvents(void *particle) {
    struct IntPair pair;
    s32 surfaceIndexBytes;
    struct Shared_ParticleEvents *events;
    s32 surfaceEventIndex;
    s32 effectId;
    s32 childParticleType;
    s32 soundId;
    struct Shared_ParticleDesc *particleDescription;
    void *eventParameterAddress;
    void *eventHalfwordAddress;

    particleDescription = ((Shared_Particle *)particle)->desc;
    if (Particle_HasSurfaceFlag(particle) != 0) {
        surfaceEventIndex = 12;
    } else {
        surfaceEventIndex = 10;
    }
    surfaceIndexBytes = surfaceEventIndex * 2;
    events = particleDescription->events;
    eventHalfwordAddress = (char *)events + surfaceIndexBytes;
    childParticleType = events->particles[surfaceEventIndex];
    effectId = events->effects[surfaceEventIndex];
    eventParameterAddress = (char *)events + (surfaceEventIndex * 8);
    pair = events->parameters[surfaceEventIndex];
    soundId = particleDescription->events->sounds[surfaceEventIndex];
    if (effectId != 0xFFFF) {
        Events_DeliverContactEffect(particle, particle, effectId, -1,
                     ((Shared_Particle *)particle)->inst.pos, pair);
    }
    if (childParticleType != 0xFFFF) {
        Particle_SpawnChildEffect(particle, childParticleType, ((Shared_Particle *)particle)->space, 1);
    }
    if (soundId != 0xFFFF) {
        SoundElement_PlaySoundAtPosition((s16)soundId,
                      ((Shared_Particle *)particle)->inst.pos, 0, -1);
    }
}

int Particle_HasSurfaceFlag(void *particle) {
    char pad[0x10];
    return ((u32)((Shared_Particle *)particle)->flags >> 2) & 1;
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
