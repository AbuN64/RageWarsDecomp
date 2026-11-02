#include "include_asm.h"
#include "RENDER/RANGENODE.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "ENGINE/EVENTS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/OBJRECAT5F14.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "ENGINE/AUDIO/T2SOUNDELEMENT.H"

/* Spawns an effect of the given kind for an object through Animpool_SpawnAnimationObject at the object's position with its velocity (none when the object is inactive) and a uniform scale; kind 0x40C instead starts at the camera with no velocity and, once spawned, follows the camera's target through Particle_GetEffectResource, and kinds 0x474 to 0x477 attach to the host's partner effect for active flagged hosts, otherwise the effect is started through Animpool_ReleaseSceneEffect. */

extern CameraEventsSpawnAttachedEffect *g_collisionCurrentActor;

extern s32 Particle_GetEffectResource(void *host);

extern s32 Animpool_ReleaseSceneEffect(void *effect);

/* Forwards a position read from an object to SetN64_SpawnModelEffect on the global g_modelEffectPool with a zero offset and a zero trailing weight, returning its result. Adapted from Scene_SpawnUnrotatedEffect with the base argument, the source vector, the trailing arguments passed as a by-value struct and the return value changed. */









extern s32 SetN64_SpawnModelEffect(s32, s32, s32, Triple, Triple, s32, f32);

void Events_SpawnAttachedEffect(EffectSpawnSourceView *source, Shared_ParticleOwner *host, s32 unused, Spawn spawn) {
    Vec3f scale;
    Vec3f velocity;
    EffectEventsSpawnAttachedEffect *effect;
    void *storage;
    EffectEventsSpawnAttachedEffect *partner;

#if defined(VERSION_DE)
    if (spawn.kind == 801) {
        return;
    }
#endif
    if (source->active == 0) {
        velocity.x = 0;
        velocity.y = 0;
        velocity.z = 0;
    } else {
        velocity = source->velocity;
    }
    spawn.position = source->position;
    scale.x = spawn.size;
    scale.y = spawn.size;
    scale.z = spawn.size;
    if (spawn.kind == 1036) {
        spawn.position = g_collisionCurrentActor->position;
        velocity.x = 0;
        velocity.y = 0;
        velocity.z = 0;
    }
    storage = Animpool_SpawnAnimationObject(&g_sceneEffectPool, spawn.kind, source->id, spawn.position, 0.0f, velocity, scale, 0);
    effect = storage;
    if (effect == 0) {
        return;
    }
    if (spawn.kind == 1036) {
        effect->target = Particle_GetEffectResource(host);
        effect->offset.x = g_collisionCurrentActor->offset.x;
        effect->offset.y = g_collisionCurrentActor->offset.y;
        effect->offset.z = g_collisionCurrentActor->offset.z;
    } else if ((unsigned)(spawn.kind - 1140) < 4) {
        if (host->kind == 1 && (host->flags & 0x300000)) {
            partner = host->player;
            if (partner != 0) {
                partner->child = effect;
                effect->scale = partner->scale;
            }
        } else {
            Animpool_ReleaseSceneEffect(effect);
        }
    }
}

s32 Events_SpawnPositionedEffect(s32 unused0, BarrelTrackActorView *targetActor, s32 unused2, Triple unused3, Extra effectParams) {
    CVector3 scale;
    Triple zero;

    zero.x = 0;
    zero.y = 0;
    zero.z = 0;
    scale.x = effectParams.scale;
    scale.y = effectParams.scale;
    scale.z = effectParams.scale;
    return SetN64_SpawnModelEffect((s32)&g_modelEffectPool, 0, effectParams.id, zero, targetActor->vec, 0, 0.0f);
}

typedef struct SoundDefinition { s32 kind; } SoundDefinition;
typedef struct SoundActor {
    char pad0[0x18];
    SoundDefinition *definition;
} SoundActor;
typedef struct SoundSource {
    u8 kind;
    char pad1[0xCF];
    s32 owner;
} SoundSource;
extern f32 k_positionedSoundDefaultGain;
extern f32 k_positionedSoundAlternateGain;
extern s32 InstHdr_GetActorMotionIndex(void *);

void Events_PlayTeamEffect(SoundActor *actor, SoundSource *source, s32 unused,
                     CVector3 position, EventCounterParameters params) {
    f32 gain = k_positionedSoundDefaultGain;
    s32 owner = -1;
    u8 kind;
    if (g_frontendScreenStatus.status[7] == 0 && InstHdr_GetActorMotionIndex(actor) == params.team) {
        kind = source->kind;
        switch (kind) {
        case 0:
            owner = source->owner;
            break;
        case 1:
            if (actor->definition->kind == kind) {
                if (g_frontendScreenStatus.settings.flags & 0x40) {
                    gain = k_positionedSoundAlternateGain;
                }
                if (g_frontendScreenStatus.settings.flags & 0x20) {
                    gain = k_nearbyPlayerBlastConstants[0];
                }
            }
            break;
        }
        SoundElement_PlayPositionedSoundWithScale(params.value, position, 0, owner, gain);
    }
}
