#include "COMMON/INTEGERSTATE244.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/OBJRECV5.H"
#include "COMMON/PLAYER_ACTION_AND_POSE_VIEWS.H"
#include "COMMON/RESOURCELOADSTATE.H"
#include "TYPES.H"
#include "FX/CONTPAD_INITCONTROLLERINPUT.H"
extern f32 g_playerMotionResetAndProbeScales;

extern char g_controllerProfiles[];




extern s32 g_playerWeaponClassMode;

typedef struct CollisionInfo CollisionInfo;

extern CollisionInfo g_defaultProbeMotionSettings;

extern f32 Gobjinst_GetActorHeight(ActorInstanceHeader *);

extern s32 Unicol_MoveActorWithCollision(ActorInstanceHeader *, CVector3, CollisionInfo *);

extern f32 Graphu64_GetPointDistance(f32 *a, f32 *b);

void Playerai_ApplyLinkedProjectileStatus(void *unused1, s32 unused2, s32 projectileEvent) {
    Playerai_ApplyProjectileStatus((((struct ActorLinkedControllerView *) ((s8 *) unused1))->link), unused1, unused2, projectileEvent);
}

void Playerai_ResetControllerMotion(void *player) {
    Player *object = player;
    void *attributes;
    void *state = object->tuning;
    f32 zero;

    if (object->computer != 0) {
        attributes = g_botControllerProfile;
    } else {
        s32 index = object->slot;
        attributes = (void *)(index << 4);
        attributes = (char *)attributes + index;
        attributes = (void *)((s32)attributes << 3);
        attributes = (char *)attributes + index;
        attributes = (void *)((s32)attributes << 2);
        attributes = g_controllerProfiles + (s32)attributes;
    }
    ContPad_InitControllerInput(state, attributes);

    object->stick = 0;
    object->state6C4 = 0;
    object->landing = 0;
    object->state6CC = 0;
    object->active = 1;
    object->state6D4 = 0;
    object->state6D8 = 0;
    object->state6DC = 0;
    object->state6E4 = 0;
    object->state758 = 0;
    object->state75C = 0;
    object->locked = 0;
    object->lockState = 0;
    object->state708 = 0;
    object->state70C = 0;
    object->state710 = 0;
    object->state714 = 0;
    object->pitchOffset = 0;
    object->kickYaw = 0;
    object->lean = 0;
    object->sway[0] = 0;
    object->sway[1] = 0;
    object->sway[2] = 0;
    object->sideOffset = 0;
    object->baseHeight = Playerai_GetObjectOwnerHeight(object);
    object->forwardOffset = 0;
    zero = object->forwardOffset;
    (&object->velocity)->x = (&object->velocity)->y = (&object->velocity)->z = zero;
    object->velocityScale = g_playerMotionResetAndProbeScales;
    object->cameraOffset = zero;
    object->cameraScale = g_playerMotionResetAndProbeScales;
    object->previousPosition = object->pos;
    object->previousTarget = object->pos;
}

s32 Playerai_HasWeaponClassType(Player *player, s32 weaponId, s32 classType) {
    s16 **entry;
    s16 **scan;
    WeaponInfo *resource;
    s16 *item;
    s32 i;

    resource = g_weaponInfoByType[weaponId];
    if (player->computer != 0) {
        entry = resource->computerClasses;
        goto scan_setup;
    }
    if (g_playerWeaponClassMode != 1) {
        entry = resource->computerClasses;
        goto scan_setup;
    }
    entry = &resource->weaponClass;

scan_setup:
    i = 0;
    scan = entry;
loop:
    item = *scan;
    if (item == 0) {
        goto null_item;
    }
    if (item[2] != classType) {
        goto mismatch;
    }
    return 1;
null_item:
    return 0;
mismatch:
    i += 1;
    if (i < 3) {
        scan += 1;
        goto loop;
    }
    return 0;
}

s32 Playerai_ProbeCollisionAdjustedPosition(ActorInstanceHeader *actor, CVector3 *position) {
    ActorInstanceHeader saved;
    s32 moved;

    saved = *actor;
    ((struct BarrelAnchorActorView *)actor)->pos.y += Gobjinst_GetActorHeight(actor) * (&g_playerMotionResetAndProbeScales)[1];
    ((struct BarrelAnchorActorView *)actor)->pos.y += ((struct BarrelAnchorActorView *)actor)->height;
    Unicol_MoveActorWithCollision(actor, *position, &g_defaultProbeMotionSettings);

    moved = (position->x != ((struct BarrelAnchorActorView *)actor)->pos.x) ||
            (position->y != ((struct BarrelAnchorActorView *)actor)->pos.y) ||
            (position->z != ((struct BarrelAnchorActorView *)actor)->pos.z);
    *position = ((struct BarrelAnchorActorView *)actor)->pos;
    *actor = saved;

    return moved;
}

f32 Playerai_SumActivePlayerDistances(void *roundContext, f32 *position) {
    f32 result;
    Round *round = roundContext;
    Shared_ActorView *actorView;

    actorView = round->players;
    result = 0.0f;
    if (actorView != 0) {
        do {
            if (actorView->message != 0) {
                result += Graphu64_GetPointDistance(position, &actorView->position.vector.x);
            }
            actorView = (Shared_ActorView *)actorView->next;
        } while (actorView != 0);
    }
    return result;
}

/* Returns whether a record in state 3 carries type 0x5E2A or 0x5E5A, or a type in the range 0x7DF to 0x7E3. */

s32 Playerai_IsStateThreeUpperAnimationGroup(struct SharedPlayer *player) {
    s32 type;

    if (player->views5E8.view650_15.actionState == 3) {
        type = player->views5E8.view86C_125.animationId;
        if (type == 24106 || type == 24154) {
            return 1;
        }
    }
    return player->views5E8.view650_15.actionState == 3 && player->views5E8.view86C_125.animationId >= 2015 && player->views5E8.view86C_125.animationId < 2020;
}

/* Returns whether a record in state 3 carries type 0x5E29 or 0x5E59, or a type in the range 0x7DA to 0x7DE. Adapted from Playerai_IsStateThreeUpperAnimationGroup with the type constants changed. */

s32 Playerai_IsStateThreeLowerAnimationGroup(struct SharedPlayer *player) {
    s32 type;

    if (player->views5E8.view650_15.actionState == 3) {
        type = player->views5E8.view86C_125.animationId;
        if (type == 24105 || type == 24153) {
            return 1;
        }
    }
    return player->views5E8.view650_15.actionState == 3 && player->views5E8.view86C_125.animationId >= 2010 && player->views5E8.view86C_125.animationId < 2015;
}

int Playerai_IsStateFifteen(struct SharedPlayer *player) {
    return player->views5E8.view650_15.actionState == 15;
}
