#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/PARTICLE_ATTACHMENT_AND_OWNER_VIEWS.H"
#include "TYPES.H"
#include "ENGINE/PARTICLE.H"
#include "ENGINE/CACHE/LIST.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "particle/PARTICLE_SPAWNEFFECTGROUP.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/PACKEDMESHMATERIAL.H"
#include "COMMON/S1.H"
#include "COMMON/SELF.H"
#include "RENDER/PARTICLE_SPAWNINTERPOLATEDTRAIL.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/SHARED_PARTICLEINSTANCE.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "particle/PARTICLE_SPAWNINTERPOLATEDTRAIL.H"

/* Particle_UpdateMatrix_ParticleSpawninterpolatedtrail.CPP */
extern s32 SoundVoicePool_StopNode(void *work, void *wantedNode);

extern s32 g_playerWeaponClassMode[];
extern s32 g_lightingBufferIndex;

void Particle_UpdateMatrix(Shared_Particle *particle) {
    CVector3 delta;
    GameplayCamera *camera;
    f32 amount;
    s32 *state;

    state = g_playerWeaponClassMode;
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

extern char g_actorParticleEffectSystem;

void Particle_SpawnInterpolatedTrail(TrailActor *actor) {
        CQuatern rotation;
        int hasTrailSegments;
        Triple delta;
        Triple step;
        unsigned int actor_2;
        Triple position;
        f32 divisor;
        s32 i;
        s8 count;
        void *system;
        count = actor->node->state->count;
        if (count > 0) {
                position = actor->position;
                rotation = Graphu64_BuildDirectionQuaternion((f32 *)&position);
                Graphu64_SubtractVectors(&delta, &actor->origin, &actor->end);
                system = &g_actorParticleEffectSystem;
                i = 1;
                hasTrailSegments = i <= count;
                if (hasTrailSegments) {
                        divisor = (f32) count + (&g_particleAveragePositionConstants)[1];
                        do {
    do { Graphu64_ScaleVector(&step, &delta, (f32) i / divisor); Graphu64_AddVec3(&step, &step, &actor->end); actor_2 = actor->model; Particle_SpawnEffectGroup((struct EffectSystem *)system, (struct EffectActor *)actor, (struct EffectActor *)actor->owner, (s32 *)actor->property, actor->type, actor_2, *(CVector3 *)&position, *(CQuatern *)&rotation, *(CVector3 *)&step, 0, -1, 0x20E001); i++; } while (0);
                        } while (count >= i);
                }
        }
}

extern void *SoundVoicePool_GetGlobalState(void);

void Particle_PlayAttachedSound(void *soundParticle, s32 soundId) {
    void *node;

    node = ((SoundParticle *)soundParticle)->sound;
    if (node != 0) {
        if (((CacheResourceNode *)node)->flags == soundId && ((CacheResourceNode *)node)->references != -1) {
            return;
        }
        Particle_StopSound(soundParticle);
    }
    ((SoundParticle *)soundParticle)->sound =
        SoundVoicePool_PlaySpatialSound(SoundVoicePool_GetGlobalState(), soundId, &((SoundParticle *)soundParticle)->particle.inst.pos, &((SoundParticle *)soundParticle)->particle.inst.pos, -1);
}

void Particle_StopSound(void *a) {
    if (((SoundParticle *)a)->sound != 0) {
        SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), ((SoundParticle *)a)->sound);
        ((SoundParticle *)a)->sound = 0;
    }
}

struct PoolNode84478;
typedef struct PoolBucket84478 {
    struct PoolNode84478 *head;
    struct PoolNode84478 *tail;
    s32 data[3];
} PoolBucket84478;
typedef struct PoolOwner84478 {
    char pad0[0xFC00];
    PoolBucket84478 free;
    char padFC14[0x14];
    PoolBucket84478 slots[256];
} PoolOwner84478;
typedef struct PoolNode84478 {
    char pad0[0x5C];
    s32 state;
    char pad60[0x184];
    PoolBucket84478 *owner;
    char pad1E8[8];
    s32 counter;
    s32 flags;
} PoolNode84478;
void Particle_Release(EffectSystem *, ParticleEffect *);

PoolNode84478 *Particle_AllocPoolNode(PoolOwner84478 *owner, s32 index) {
    PoolNode84478 *node;
    PoolBucket84478 *slot;
    s32 i;
    PoolNode84478 *tail;
    if (owner->free.head == 0) {
        for (i = 0; i <= (index & 0xFF); i++) {
            tail = (&owner->slots[i])->tail;
            if (tail != 0) {
                Particle_Release((EffectSystem *)owner, (ParticleEffect *)tail);
                break;
            }
        }
    }
    node = owner->free.head;
    if (node == 0) {
        return 0;
    }
    List_RemoveIntrusive(&owner->free, node);
    slot = &owner->slots[index & 0xFF];
    List_PrependIntrusive(slot, node);
    node->owner = slot;
    node->flags = 0;
    node->counter = 0;
    node->state = 0x100;
    return node;
}

/* 8028308C_3.CPP */
extern void Particle_FinishActorEffects(void *actor);
extern void Fx_DetachParticleSwooshes(void *effectWorld, void *detachedEntity);

void Particle_Release(EffectSystem *owner, ParticleEffect *releasedEffect) {
    s32 *releaseReferenceCount;
    s32 releasedLight;
    s32 flags;

    flags = releasedEffect->flags;
    if (flags & 0x100) {
        if (!(flags & 0x800)) {
            Particle_FinishActorEffects(releasedEffect);
            if (releasedEffect->releaseRequested != 0) {
                Particle_UpdateMatrix(releasedEffect);
                Fx_DetachParticleSwooshes(&g_actorParticleScene, releasedEffect);
            }
            releasedLight = releasedEffect->lightHandle;
            if (releasedLight != 0) {
                Gdynlight_ReleaseLight(&g_dynamicLightPool, releasedLight);
                releasedEffect->lightHandle = 0;
            }
            releaseReferenceCount = releasedEffect->refCount;
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
/* Passes the first non-null handle among entries 0 to count of the object's twenty-byte table at
   0xFC28 to Particle_Release_ParticleSpawninterpolatedtrail together with the object. */

void Particle_ReleaseFirstHandle(char *obj, unsigned char count) {
    int i;

    for (i = 0; i <= count; i++) {
        ParticleResourceHandleEntry *e = (ParticleResourceHandleEntry *)((obj + i * sizeof(ParticleResourceHandleEntry) + ((char *)&((struct EffectSystem *)0)->lists - (char *)0)));
        if (e->handle != 0) {
            Particle_Release(obj, e->handle);
            return;
        }
    }
}

/* 8028469C.CPP */
void *Particle_FindOwnerEntry(EffectSystem *effectSystem, s32 ownerId, EffectEntry *effectEntry) {
    void *record;

    record = effectEntry->params->listIndex[effectSystem->lists].head;
    if (effectEntry != 0) {
        if (record != 0) {
            do {
                if (((ParticleEffect *)record)->ownerId == ownerId) {
                    if (((ParticleEffect *)record)->entry == effectEntry) {
                        return record;
                    }
                }
                record = ((ParticleEffect *)record)->next;
            } while (record != 0);
        }
    } else if (record != 0) {
        do {
            if (((ParticleEffect *)record)->ownerId == ownerId) {
                return record;
            }
            record = ((ParticleEffect *)record)->next;
        } while (record != 0);
    }
    return 0;
}

extern void List_InsertBeforeIntrusive(void *, s32, s32);

void Particle_InsertEntryGroup(EffectSystem *effectSystem, ParticleEffect *particleEffect)
{
    void *current;
    s32 key;

    current = effectSystem->groups.head;
    if (current != 0) {
        key = (s32)particleEffect->entry;
loop:
        if (((ParticleEffect *)current)->entry != key) {
            current = ((ParticleEffect *)current)->groupNext;
            if (current != 0) {
                goto loop;
            }
        }
    }

    if (current != 0) {
        List_InsertBeforeIntrusive(&effectSystem->groups, current, particleEffect);
    } else if (particleEffect->entry->flags & 0x2000) {
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
float Particle_GetConditionalFirstValue(ParticleEffect *effect) {
    void *inner = effect->entry;
    if (((EffectEntry *)inner)->rangeModeFlag != 0) {
        return 0.0f;
    }
    return effect->sampledRangesB[0];
}

f32 Particle_GetConditionalSecondValue(ParticleEffect *effect) {
    f32 result;
    result = 0.0f;
    if ((effect->entry->rangeModeFlag) == 0) {
        result = (effect->sampledRangesB[1]);
    }
    return result;
}

s32 Particle_IsKind2Or86Or273Or294(ParticleEffect *effect) {
    u16 kind;
    s32 val;

    kind = effect->kind;
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

s32 Particle_IsKind5To7Or9Or17Or19Or26Or257Or272(ParticleEffect *effect) {
    u16 kind;
    s32 val;

    kind = effect->kind;
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

s32 Particle_IsKind8Or13Or18(ParticleEffect *effect) {
    u16 kind;
    s32 val;

    kind = effect->kind;
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

void Particle_UpdateForcesAndMotion(ParticleEffect *effect)
{
    CVector3 delta;
    CVector3 direction;
    f32 acceleration;
    f32 speed;
    f32 limit;
    f32 x, y, z;
    CVector3 *velocity;

    Playerai_ApplyPlayerForces(&g_playerViewRenderContext, effect);
    acceleration = Menu_ExpandFloatHighWord(effect->entry->motion->acceleration);
    if (acceleration != 0.0f) {
        direction = effect->direction;
        Graphu64_ScaleVector(&delta, &direction, acceleration);
        Graphu64_AddVec3(&effect->velocity, &effect->velocity, &delta);
        velocity = &effect->velocity;
        x = effect->velocity.x;
        y = effect->velocity.y;
        z = effect->velocity.z;
        speed = Gu_Sqrtf(x * x + y * y + z * z);
        limit = Menu_ExpandFloatHighWord(effect->entry->motion->speedLimit);
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

/* 8028469C_2.CPP */

extern f32 Graphu64_GetSquaredDistance(f32 *firstPosition, f32 *secondPosition);
extern void Particle_HandlePlayerContact(void *particle, void *player);

const float g_particleTrailSpacingAndOwnerHeightConstants[2] = {
    10.24f, 0.5f,
};
void Particle_CheckNearbyPlayerContacts(Shared_Particle *particle) {
    CVector3 point;
    void *node;
    void *point_ptr;
    int actor_id;
    s16 amount;
    int stop;
    f32 radius_sq;
    f32 height_scale;

    amount = particle->desc->playerContactRadius;
    radius_sq = (f32)amount;
    if (radius_sq <= 0.0f) {
        return;
    }
    radius_sq *= g_particleNearestEffectDistanceTuning;
    node = g_transientPlayerList.actorList;
    radius_sq *= radius_sq;
    if (node == 0) {
        return;
    }

    point_ptr = &point;
    actor_id = 1039;
    height_scale = (&g_particleNearestEffectDistanceTuning)[1];
    do {
        point = ((Shared_ActorView *)node)->position.vector;
        stop = 0;
        if (particle->inst.type != actor_id) {
            point.y += Gobjinst_GetActorHeight(node) * height_scale;
        }
        if (Graphu64_GetSquaredDistance(&particle->inst.pos.x, point_ptr) < radius_sq) {
            Particle_HandlePlayerContact(particle, node);
            if (particle->inst.type == actor_id) {
                stop = 1;
            }
        }
        if (stop != 0) {
            node = 0;
        } else {
            node = ((Shared_ActorView *)node)->next;
        }
    } while (node != 0);
}

typedef struct CollisionInfo CollisionInfo;

extern CollisionInfo g_defaultProbeMotionSettings;
extern ActorInstanceHeader *Gsky_FindScreenMessage(ParticleTrailEmitterView *messageId);
extern s32 Unicol_MoveActorWithCollision(ActorInstanceHeader *, CVector3, CollisionInfo *);

s32 Particle_HasClearMotionPath(ActorInstanceHeader *particle, ParticleTrailEmitterView *messageId) {
    ActorInstanceHeader saved;
    ActorInstanceHeader *instance;
    s32 collisions;

    instance = Gsky_FindScreenMessage(messageId);
    if (instance != 0 && messageId->mode == 0) {
        saved = *instance;
        instance->position = messageId->position128;
        collisions = Unicol_MoveActorWithCollision(instance, particle->position, &g_defaultProbeMotionSettings);
        *instance = saved;
    } else {
        saved = *particle;
        saved.position = messageId->position128;
        collisions = Unicol_MoveActorWithCollision(&saved, particle->position, &g_defaultProbeMotionSettings);
    }
    return collisions == 0;
}

/* Marks nearby objects other than type 87 as active. */

void Particle_MarkNearbyObjects(s32 unused, ObjParticleMarkNearbyObjects *center, ObjParticleMarkNearbyObjects **objects, s32 count) {
 f32 d[3]; s32 i; ObjParticleMarkNearbyObjects *o;
 for(i=0;i<count;i++) {
  o=objects[i];
  if(o->flags != 0x57) {
   Graphu64_SubtractVectors(d,o->pos,center->pos);
   if(d[0]*d[0]+d[1]*d[1]+d[2]*d[2]<=65536.0f) o->nearbyEffectFlags=1;
  }
 }
}

/* Checks object proximity through type-specific handlers and marks nearby objects active. */

static inline void nearby(s32 unused, ObjParticleMarkNearbyObjects *center, ObjParticleMarkNearbyObjects **objects, s32 count) {
 f32 d[3]; s32 i; ObjParticleMarkNearbyObjects *o;
 for(i=0;i<count;i++) {
  o=objects[i];
  if(o->flags != 0x57) {
   Graphu64_SubtractVectors(d,o->pos,center->pos);
   if(d[0]*d[0]+d[1]*d[1]+d[2]*d[2]<=65536.0f) o->nearbyEffectFlags=1;
  }
 }
}
extern void Particle_MarkCrowdedActor(int,ObjParticleMarkNearbyObjects *,ObjParticleMarkNearbyObjects **,int);
void Particle_UpdateNearbyObjectFlags(int context,ObjParticleMarkNearbyObjects **objects,int count) {
 int i; ObjParticleMarkNearbyObjects *obj;
 for(i=0;i<count;i++) {
  obj=objects[i];
  switch(obj->flags) {
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
    s8 *record;

    averagePositionOut->x = 0.0f;
    averagePositionOut->y = 0.0f;
    averagePositionOut->z = 0.0f;
    record = effectSystem->lists[1].head;
    count = 0;
    if (record != 0) {
        do {
            v = ((ParticleEffect *)record)->kind;
            if (((v == 1054) || (v == 1007)) &&
                (((ParticleEffect *)record)->owner == ownerId) &&
                (((ParticleEffect *)record)->flags & 0x100)) {
                averagePositionOut->x += ((ParticleEffect *)record)->pos.x;
                averagePositionOut->y += ((ParticleEffect *)record)->pos.y;
                count += 1;
                averagePositionOut->z += ((ParticleEffect *)record)->pos.z;
            }
            record = ((ParticleEffect *)record)->next;
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
    void *node;

    *distanceOut = g_particleMaximumSearchDistance;
    node = effectSystem->groups.head;
    if (node != 0) {
        do {
            if (((ParticleEffect *)node)->owner != actor && (((ParticleEffect *)node)->flags & 0x100)) {
                distanceSquared = Graphu64_GetSquaredDistance(&((ParticleEffect *)node)->pos.x, &actor->position0.x);
                if (distanceSquared < *distanceOut) {
                    *distanceOut = distanceSquared;
                }
            }
            node = ((ParticleEffect *)node)->groupNext;
        } while (node != 0);
    }
}


/* 800C9F80.CPP */

