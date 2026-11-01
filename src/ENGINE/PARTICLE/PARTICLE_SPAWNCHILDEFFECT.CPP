#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/LONE/COLLISION_CURRENT_ACTOR.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/LISTHEADER.H"
#include "TYPES.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "ENGINE/PARTICLE.H"

typedef struct Owner Owner;

extern void *Particle_GetEffectResource(void *particle);
extern s32 Playerai_IsPlayerInactive(void *player);
extern void Player_GiveAmmoWithMessage(void *player, s32 type, s32 amount);











void Particle_FinishActorEffects(void *actorStorage) {
    char *actor = actorStorage;
    char *state;
    char *owner;
    char *resource;

    if (((ParticleOwnerActorView *)(actor))->kindId != 1044) {
        if (((ParticleOwnerActorView *)(actor))->kindId == 1069) {
            state = Particle_GetEffectResource(actor);
            if (((ParticleAmmoRewardView *)(state))->ammoAmount != 0 && Playerai_IsPlayerInactive(state) == 0) {
                Player_GiveAmmoWithMessage(state, ((ParticleAmmoRewardView *)(state))->ammoType,
                               ((ParticleAmmoRewardView *)(state))->ammoAmount);
            }
            goto reset_state;
        }
    } else {
reset_state:
        state = Particle_GetEffectResource(actor);
        ((ParticleAmmoRewardView *)(state))->ammoAmount = 0;
        if (Playerai_IsPlayerInactive(state) == 0) {
            ((ParticleAmmoRewardView *)(state))->resetFlag = 1;
        }
    }

    if (((ParticleOwnerActorView *)(actor))->stateByte0 == 8 ||
        ((ParticleOwnerActorView *)(actor))->stateByte1 == 8 ||
        ((ParticleOwnerActorView *)(actor))->stateByte2 == 8) {
        resource = ((ParticleOwnerActorView *)(actor))->owner;
        if (resource != 0 && *(u8 *)resource == 1 &&
            (((Shared_Actor *)(resource))->weaponFlags & 0x300000) != 0) {
            Player_SetPlayerState(((Shared_Actor *)(resource))->entity, resource, 2);
        }
    }

    Particle_StopSound(actor);
    owner = ((ParticleOwnerActorView *)(actor))->def;
    if (((struct ParticleFinishSoundView *) ((Owner *) owner)->track)->firstSoundId != 0xFFFF) {
        SoundElement_StopAudioBySecondaryValue((s32)actor);
    }
    if (((struct ParticleFinishSoundView *) ((Owner *) owner)->track)->secondSoundId != 0xFFFF) {
        SoundElement_StopAudioBySecondaryValue((s32)actor);
    }
}

/* Spawns an effect for an actor through Particle_SpawnEffectGroup: the rotation comes from the fixed direction g_particleZeroVector or the actor's own facing, and the spawn point is the actor's position, or when the actor carries a horizontal offset the negated offset turned by the actor's angle, carried through its parent transform when it has one, and added to the position; the flags passed are the given flags with the actor's bits 0x200006. Adapted from Particle_HandleInitialMaterialContact with the offset reads as static inline getters and a stack state briefly made current in g_collisionCurrentActor. */









extern char g_actorParticleEffectSystem;
extern char g_currentActorInstance;
extern CQuatern Graphu64_BuildDirectionQuaternion(CVector3 *);
extern void BuildRollMatrix(f32 *matrix, s32 angle);
extern void Graphu64_AddVec3(CVector3 *out, CVector3 *a, CVector3 *b);
#include "particle/PARTICLE_SPAWNEFFECTGROUP.H"

static inline f32 offset_x(ParticleChildEffectActorView *actor) {
    if (actor->def->flags != 0) {
        return 0.0f;
    }
    return actor->offsetX;
}

static inline f32 offset_y(ParticleChildEffectActorView *actor) {
    if (actor->def->flags != 0) {
        return 0.0f;
    }
    return actor->offsetY;
}

void Particle_SpawnChildEffect(ParticleChildEffectActorView *actor, s32 model, s32 spawnMode, s32 flags) {
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

    if (actor->def->kind & 0x10) {
        direction = g_particleZeroVector;
    } else {
        direction = actor->facing;
    }
    rotation = Graphu64_BuildDirectionQuaternion(&direction);
    if (offset_x(actor) == 0.0f && offset_y(actor) == 0.0f) {
        point = actor->position;
    } else {
        offset.x = -offset_x(actor);
        offset.y = -offset_y(actor);
        offset.z = 0.0f;
        BuildRollMatrix(matrix, actor->angle);
        Graphu64_TransformPoint(matrix, &offset, &turned);
        parent = Particle_ParentTransform((struct Shared_Particle *)actor, 0);
        if (parent != 0) {
            Graphu64_TransformPoint(parent, &turned, &carried);
        } else {
            carried = turned;
        }
        Graphu64_AddVec3(&moved, &carried, &actor->position);
        g_collisionCurrentActor = scratch;
        point = moved;
        g_collisionCurrentActor = &g_currentActorInstance;
    }
    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)actor, (struct EffectActor *)actor->owner, (s32 *)actor->effectEntries, actor->effectEntryCount, model,
                  direction, rotation, point, 0, spawnMode, flags | (actor->flags & 0x200006));
}
