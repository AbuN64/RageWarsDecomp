#include "COMMON/GAMEPLAY_CAMERA.H"
#include "ENGINE/EVENTS.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "COMMON/VIEWFLAGS.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
extern void Events_ApplyDamageEvent(void *, s32, s32, Triple, struct IntPair, s32, s32, s32);

/* Returns how strongly a blast at a position with a radius affects an actor: finds the shield covering the position (the held carrier shield g_currentActorInstance of the actor for an object target other than the two 0x402/0x404 types, otherwise Gobjinst_FindNearestBoneBounds's shield in g_damageBoneBoundsShield), reports it, scales by the shield factor unless friendly fire is off for team damage, and when falloff is asked returns zero for an invulnerable player's untouched full hit, zero beyond the radius plus the actor's width, or the scale times one minus the distance to the actor's body over that reach. */


















extern Carrier g_currentActorInstance;


extern s32 Gobjinst_FindNearestBoneBounds(ActorEventsComputeDamageScale *, CVector3, Shield *);

extern f32 Gobjinst_GetActorHeight(ActorEventsComputeDamageScale *);

extern f32 Gobjinst_GetActorRadius(ActorEventsComputeDamageScale *);

extern f32 Graphu64_GetPointDistance(CVector3 *, CVector3 *);

/* Spawns a hit effect when the target has a rider: turns the negated hit direction into the victim's frame through Player_TransformPointByViewOrOwnerMatrix, makes it relative to the victim rider's centre and converts it to a rotation, resolves the hit position on the attacker through InstHdr_CopyActorPositionAndModel, spawns effect 0xE9 there raised by k_playerEventClipHeightAndAngle (size 3 for kind 5, otherwise 1), and starts effect 3 on the victim's emitter. */












extern f32 k_playerEventClipScale;

extern char g_actorParticleEffectSystem;

extern void Player_TransformPointByViewOrOwnerMatrix(SharedPlayer *, CVector3 *);

extern struct CacheResourceBlockView Graphu64_BuildDirectionQuaternion(CVector3 *);

extern void InstHdr_CopyActorPositionAndModel(void *, Triple, void *, s32 *, s32, s32);

#include "particle/PARTICLE_SPAWNEFFECTGROUP.H"

extern void CScene_StartEventClips(void *, void *, s32, Triple, f32, f32);

/* Forwards a position and extent to Events_ApplyDamageEvent with zero flags and priority 0x80, but only when
   the first byte of the given object is 1. Adapted from the matched twin Events_ApplyRadialDamage with the object
   type test added and the leading flag changed to 0. */







extern void Events_UpdateNodeAtPosition(s32 actor, s32 positionXWord, s32 positionYWord, s32 positionZWord, s32 enableNodeFlag);

extern void *g_gameplayCameraList;

extern s32 Gsky_ContainsVisiblePoint(NodeEventsStartCameraFadeAtPoint *cameraAddress, Triple testPoint);


f32 Events_ComputeDamageScale(ActorEventsComputeDamageScale *self, Target *target, CVector3 position, f32 radius, s32 falloff, s32 flags, Shield **found) {
    PlayerDamageFlagsView *player;
    s32 shielded;
    s32 scaled;
    s32 special;
    Shield *shield;
    f32 scale;
    f32 bottom;
    f32 top;
    f32 reach;
    f32 distance;
    CVector3 body;

    special = 0;
    shielded = 1;
    player = 0;
    scale = *(&k_damageEuropeanFalloffScale + 1);
    scaled = 1;
    if (self->flags & 0x300000) {
        player = self->player;
    }
    if (g_gameSettings.local != 0 && (flags & 0x200)) {
        shielded = 0;
    }
    if (target->kind == 2) {
        if (target->type == 1028 || target->type == 1026) {
            special = 1;
        }
        if (target->kind == 2 && g_currentActorInstance.owner == self && g_currentActorInstance.slot != -1 && !special) {
            shield = &g_currentActorInstance.shield;
            falloff = 0;
            goto have;
        }
    }
    shield = Gobjinst_FindNearestBoneBounds(self, position, &g_damageBoneBoundsShield) ? &g_damageBoneBoundsShield : 0;
have:
    *found = shield;
    if (shielded && shield != 0) {
        scale *= shield->factor;
    }
    if (falloff != 0) {
        if (player != 0 && (player->flags & 2) && scale == k_damageSpecialScale && (flags & 0x200)) {
            scale = 0.0f;
        } else {
            body = self->position;
            bottom = self->position.y + self->height;
            top = bottom + Gobjinst_GetActorHeight(self);
            if (top < position.y) {
                body.y = top;
            } else if (position.y < bottom) {
                body.y = bottom;
            } else {
                body.y = position.y;
            }
            reach = radius + Gobjinst_GetActorRadius(self);
            distance = Graphu64_GetPointDistance(&position, &body);
            if (reach < distance) {
                return 0.0f;
            }
            if (scaled) {
                scale *= (1.0f) - distance / reach;
            }
        }
    }
    return scale;
}

void Events_SpawnRiderImpactEffect(SharedPlayer *target, ActorEventsSpawnRiderImpactEffect *actor, Triple position, CVector3 direction, s32 kind) {
    SharedPlayer *player;
    CVector3 v;
    Triple point;
    Triple zero;
    struct CacheResourceBlockView rotation;
    s32 unused;

    if (target->views5DC.view5DC_5.rider == 0) {
        return;
    }
    player = actor->player;
    v.x = -direction.x;
    v.y = direction.y;
    v.z = direction.z;
    Player_TransformPointByViewOrOwnerMatrix(player, &v);
    v.x -= player->views5DC.view5DC_5.rider->position.x;
    v.y -= player->views5DC.view5DC_5.rider->position.y;
    v.z -= player->views5DC.view5DC_5.rider->position.z;
    rotation = Graphu64_BuildDirectionQuaternion(&v);
    InstHdr_CopyActorPositionAndModel(actor, position, &point, &unused, 0, 1);
    point = position;
    ((CVector3 *)&point)->y += k_playerEventClipHeightAndAngle;
    zero.x = 0;
    zero.y = 0;
    zero.z = 0;
    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)actor, (struct EffectActor *)actor, 0, 0, 233, *(CVector3 *)&zero, *(CQuatern *)&rotation, *(CVector3 *)&point, 0, -1, kind == 5 ? 3 : 1);
    point.x = 0;
    point.y = 0;
    point.z = 0;
    CScene_StartEventClips(&g_world, &((ControllerProfile *)player->views5E8.view698_37.emitter)->effectPool, 3, point, *(&k_playerEventClipHeightAndAngle + 1), k_playerEventClipScale);
}

void Events_ApplyDirectDamage(unsigned char *source, s32 target, s32 kind, Triple position, struct IntPair params) {
    if (*source == 1) {
        Events_ApplyDamageEvent(source, target, kind, position, params, 0, 0, 128);
    }
}

void Events_ApplyRadialDamage(s32 source, s32 target, s32 kind, Triple position, struct IntPair params) {
    Events_ApplyDamageEvent((void *)source, target, kind, position, params, 1, 0, 128);
}

void Events_ApplyRadialDamageWithKnockback(s32 source, s32 target, s32 kind, Triple position, struct IntPair params) {
    Events_ApplyDamageEvent((void *)source, target, kind, position, params, 1, 1, 128);
}

void Events_PreserveEventArgument(int unused0, int unused1, int unused2, int eventArgument) {
    int *p = &eventArgument;
    *p = eventArgument;
}

void Events_RunFirstNodeOperation(s32 actor, s32 unusedTarget, s32 unusedKind, s32 positionXWord, s32 positionYWord, s32 positionZWord)
{
  s32 *positionXAddress;
  int enableNodeFlag;
  positionXAddress = &positionXWord;
  enableNodeFlag = 1;
  Events_UpdateNodeAtPosition(actor, *positionXAddress, positionYWord, positionZWord, enableNodeFlag);
}

void Events_RunSecondNodeOperation(s32 actor, s32 unusedTarget, s32 unusedKind, s32 positionXWord, s32 positionYWord, s32 positionZWord)
{
  s32 *positionXAddress;
  int enableNodeFlag;
  positionXAddress = &positionXWord;
  enableNodeFlag = 0;
  Events_UpdateNodeAtPosition(actor, *positionXAddress, positionYWord, positionZWord, enableNodeFlag);
}

void Events_StartCameraFadeAtPoint(s32 unused0, s32 unused1, s32 unused2, Triple testPoint, CEventValueFormat7a fadeParams) {
    NodeEventsStartCameraFadeAtPoint *node;

    node = g_gameplayCameraList;
    while (node != 0) {
        if (Gsky_ContainsVisiblePoint(node, testPoint) != 0) {
            Gsky_StartFade(node, fadeParams.a, fadeParams.b, fadeParams.c, fadeParams.m_u8_Value4,
                          fadeParams.m_u8_Value5, fadeParams.f, fadeParams.m_u8_Value7);
        }
        node = node->next;
    }
}

void Events_ConsumeEventArgument(int unused0, int unused1, int unused2, int eventArgument) {
    int *p = &eventArgument;
    *p = eventArgument;
}

/* Moves the target actor's linked player to the requested position, then raises the event on the actor. */
void Events_RequestActorPosition(s32 source, void *target, s32 kind, CVector3 position, struct IntPair positionParams) {
    s32 mode = positionParams.first;
    LevelActor *actor = (LevelActor *)target;
    ((Player *)actor->controller)->requestedPosition = position;
    Weapon_SpawnTargetPlayerFireEffect(actor, (s32) &actor->behaviorFlags, mode);
}
