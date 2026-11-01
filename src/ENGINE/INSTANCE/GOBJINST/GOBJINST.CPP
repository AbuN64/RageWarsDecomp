#include "COMMON/WORLD.H"
#include "COMMON/LONE/PARTICLE_COLLISION_PROBE_RESULT.H"
#include "COMMON/GROUP.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/PARTICLE_LIGHTING.H"
#include "COMMON/ACCESS_S8_10F.H"
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include "COMMON/LISTHEADER.H"
#include "CAMERA/COLLISION_SWEEP_VIEWS.H"
#include "TYPES.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "ENGINE/LISTS.H"

/* Returns the collisions an object would meet moving to a position, without committing the move: picks the collision set for the object
 * (g_portalAlternateCollisionQuery for flagged players; otherwise by Insthdr_IsInactiveOrCollisionOption4 and then Insthdr_GetModelCollisionFlag8 or Insthdr_GetModelCollisionFlag1 among
 * g_portalDefaultCollisionQuery, g_portalNoModelFlagCollisionQuery, g_portalModeCollisionQuery and g_portalAlternateCollisionQuery), reports it through the optional out pointer, runs
 * the collision mover Collision_ProbeGround_de and restores the object's 0x50-byte header. Adapted from
 * Gobjinst_HasClearPathToActor. */





extern char g_portalDefaultCollisionQuery;

extern char g_portalModeCollisionQuery;

extern char g_portalNoModelFlagCollisionQuery;

extern char g_portalAlternateCollisionQuery;

extern s32 Insthdr_GetModelCollisionFlag1(ActorInstanceHeader *);

extern s32 Insthdr_IsInactiveOrCollisionOption4(ActorInstanceHeader *);

extern s32 Insthdr_GetModelCollisionFlag8(ActorInstanceHeader *);


extern f32 Gobjinst_GetActorHeight(ActorInstanceHeader *);

extern CollisionState g_currentActorInstance;

extern int InstHdr_GetActorMotionIndex(void *record);

/* Spawns and initializes an actor with model, transforms, collision body, effects and default bounds. */










extern char *g_gamePlayerAndMenuState;

extern void *g_actorTypeOperations[];

extern char g_actorDefinitionTable;

extern void g_Gobjinst_DrawTeamMaskedModelAddress();

struct Shared_World;
extern s32 Scene_FindModelIdIndex(struct Shared_World *, s32);

extern void GameObject_ResetActorMotion(char *);

extern CQuatern Insthdr_BuildActorGroundRotation(char *);

extern void Gastate_ResetAnimationReference(char *);

extern void Gobjinst_QueueAnimation(char *, s32);

extern void Graphu64_IdentityMatrix(char *);

extern void Actor_InitSpawnedActor(char *, char *, void *);

extern void Playerai_InitializeRouteCursor(char *, s32, char *);

extern void Gobjinst_LoadModel(char *, s32, s32, s32);


static inline void *body_setup(char *obj) {
    u32 kind;
    s32 i;
    char *player;

    kind = ((LevelActor *)obj)->definition->kind;
    if (kind >= 15) {
        return 0;
    }
    if (kind == 11) {
        for (i = 0; i < g_playerCount; i++) {
            player = g_gamePlayerAndMenuState + i * sizeof(SharedPlayer);
            if (player == obj) {
                return 0;
            }
            if ((char *)&((SharedPlayer *)player)->views1C.view2E8_27.weapon == obj) {
                return &g_actorDefinitionTable;
            }
        }
    }
    return g_actorTypeOperations[kind];
}

extern s32 g_lookupAIAnimTypeAnimObjectInfoText[];



extern s32 Defs_FindSortedValue(void *, s32, s32);

extern void Lists_ClearWeightedTable(WeightedTable *);


s32 Gobjinst_ProbeActorMovement(ActorInstanceHeader *actorState, CVector3 position, char **out) {

    ActorInstanceHeader saved;
    char *set;
    s32 grounded;
    s32 collisions;
    struct BarrelAnchorActorView *actor = (struct BarrelAnchorActorView *)actorState;

    if (actor->type == 1 && (actor->flags100 & 0x300000) != 0) {
        set = &g_portalAlternateCollisionQuery;
    } else {
        grounded = Insthdr_GetModelCollisionFlag1(actorState);
        if (Insthdr_IsInactiveOrCollisionOption4(actorState) == 0) {
            set = &g_portalAlternateCollisionQuery;
            if (grounded != 0) {
                set = &g_portalModeCollisionQuery;
            }
        } else if (Insthdr_GetModelCollisionFlag8(actorState) == 0) {
            set = &g_portalNoModelFlagCollisionQuery;
        } else {
            set = &g_portalDefaultCollisionQuery;
        }
    }
    if (out != 0) {
        *out = set;
    }
    saved = *actorState;
    collisions = Unicol_MoveActorWithCollision(actorState, position, set);
    *actorState = saved;
    return collisions;
}

s32 Gobjinst_HasClearPathToActor(ActorInstanceHeader *from, ActorInstanceHeader *to) {

    ActorInstanceHeader savedFrom;
    CVector3 desired;
    f32 scale;
    s32 collisions;

    savedFrom = *from;
    scale = g_actorVisibilityProbeHeightScale;
    ((struct BarrelAnchorActorView *)from)->pos.y += Gobjinst_GetActorHeight(from) * scale;
    desired = ((struct BarrelAnchorActorView *)to)->pos;
    desired.y += Gobjinst_GetActorHeight(to) * scale;
    collisions = Unicol_MoveActorWithCollision(from, desired, &g_particleCollisionProbeResult);
    *from = savedFrom;

    return collisions == 0;
}

s32 Gobjinst_HasClearInstancePath(ActorInstanceHeader *actorState, CVector3 position, UnicolMotionSettings *collisionSettings) {
    ActorInstanceHeader saved;
    UnicolMotionSettings collision_info;
    s32 collisions;

    saved = *actorState;
    collision_info = *collisionSettings;
    collision_info.ground_behavior = 0;
    collision_info.instance_behavior = 1;
    Unicol_MoveActorWithCollision(actorState, position, &collision_info);
    *actorState = saved;

    collisions = g_currentActorInstance.active0 || g_currentActorInstance.active9c;
    return !collisions;
}

/** Thin wrapper around InstHdr_GetActorMotionIndex, discarding its result. */
void Gobjinst_ReadActorMotionIndex(void *record) {
    InstHdr_GetActorMotionIndex(record);
}

void Gobjinst_InitializeActor(char *obj, s32 model, s32 kind, s32 unused, void *info, s32 effect, s32 owner, f32 heading,
                   CVector3 pos, s32 flags, CVector3 extent, CVector3 offset) {
    s32 lean;
    s32 delay;
    Shared_World *world;

    ((LevelActor *)obj)->flags &= ~0x40000;
    if (model == -1) {
        model = Scene_FindModelIdIndex(&g_world, kind);
        if (model == -1) {
            return;
        }
    }
    GameObject_ResetActorMotion(obj);
    *(u8 *)obj = 1;
    ((LevelActor *)obj)->modelIndex = model;
    ((LevelActor *)obj)->definition = info;
    ((LevelActor *)obj)->model = owner;
    ((LevelActor *)obj)->yaw = heading;
    ((LevelActor *)obj)->position0 = pos;
    ((LevelActor *)obj)->flags = flags;
    ((LevelActor *)obj)->scale = extent;
    ((LevelActor *)obj)->position1 = offset;
    ((LevelActor *)obj)->type = kind;
    ((LevelActor *)obj)->rotation = Insthdr_BuildActorGroundRotation(obj);
    ((LevelActor *)obj)->eyeHeight = 0;
    ((LevelActor *)obj)->stateE6 = 0;
    ((LevelActor *)obj)->stateE7 = 0;
    ((LevelActor *)obj)->state139 = 0;
    ((LevelActor *)obj)->state138 = 0;
    ((LevelActor *)obj)->renderFlags = 0x17800074;
    Gastate_ResetAnimationReference(&((LevelActor *)obj)->animationTime);
    Gastate_ResetAnimationReference((char *)&((LevelActor *)obj)->animationReference);
    Gobjinst_QueueAnimation(obj, 0);
    ((LevelActor *)obj)->flags = (((LevelActor *)obj)->flags & ~0x400) | 0x2100;
    Graphu64_IdentityMatrix(&((LevelActor *)obj)->transform);
    ((LevelActor *)obj)->animationMatrices = 0;
    ((LevelActor *)obj)->alternateAnimationMatrices = 0;
    ((LevelActor *)obj)->shadow = 0;
    ((LevelActor *)obj)->state13B = 0;
    ((LevelActor *)obj)->flags |= 0x10000;
    ((LevelActor *)obj)->flags |= 0x20000;
    if (((LevelActor *)obj)->definition->kind == 0 || (((LevelActor *)obj)->flags & 1)) {
        ((LevelActor *)obj)->flags &= ~0x20000;
    }
    lean = 0;
    delay = 0;

Actor_InitSpawnedActor
(obj, &((LevelActor *)obj)->behaviorFlags, body_setup(obj));
    if (((LevelActor *)obj)->collisionEnabled != 0) {
        lean = -((LevelActor *)obj)->lean;
    }
    ((LevelActor *)obj)->controller = 0;
    if (effect != -1) {
        Playerai_InitializeRouteCursor(&((LevelActor *)obj)->routeCursor, effect, &((LevelActor *)obj)->position0);
    }
    world = &g_world;
    Gobjinst_LoadModel(obj, (s32)world->indexedDirectory, world->indexedBank, lean);
    if (delay != 0) {
        ((LevelActor *)obj)->animationTime = delay;
        ((LevelActor *)obj)->flags &= ~0x400;
    }
    ((LevelActor *)obj)->flags2E4 = Statinst_AdvanceResourceKey() << 10;
    if (((LevelActor *)obj)->flags & 8) {
        ((LevelActor *)obj)->update = g_Gobjinst_DrawTeamMaskedModelAddress;
        ((LevelActor *)obj)->lighting[0] = g_defaultParticleLighting;
        ((LevelActor *)obj)->lighting[1] = g_defaultParticleLighting;
    }
}

s32 Gobjinst_ChooseAnimationVariant(LevelActor *owner, s32 animationKind, s32 excludedEntry) {
    WeightedTable table;
    void **resource;
    s32 *entries;
    void *data;
    s32 count;
    s32 total;
    s32 original;

    if (!(owner->flags & 0x40000)) {
        goto fail;
    }
    resource = Cache_RequestResource(0, ((struct Access_s32_C4 *)(owner))->field,
                             ((struct Access_s32_C4 *)(owner))->field, ((struct Access_s32_D0 *)(owner))->field,
                             0, 0, 0, g_lookupAIAnimTypeAnimObjectInfoText, 1);
    if (resource == 0) {
        goto fail;
    }
    data = SetN64_GetPackSection(*resource, 1);
    entries = &((struct MenuTextOwnerView *)(data))->flags;
    total = ((struct ResourceKeyView *)(data))->key;
    count = Defs_FindSortedValue(entries, ((struct Access_s8_E6 *)(owner))->field, animationKind);
    if (count != -1) {
        original = count;
        while (count > 0) {
            if (entries[count - 1] != animationKind) {
                break;
            }
            count--;
        }

        Lists_ClearWeightedTable(&table);
        if (excludedEntry == -1) {
            while (count < total && entries[count] == animationKind) {
                Lists_AppendWeightedEntry(&table, count++, 10);
            }
        } else {
            while (count < total && entries[count] == animationKind) {
                if (excludedEntry != count) {
                    Lists_AppendWeightedEntry(&table, count, 10);
                }
                count++;
            }
        }
        if (table.count == 0) {
            Lists_AppendWeightedEntry(&table, original, 10);
        }
        count = Lists_ChooseWeightedTableEntry(&table);
    }
    Cache_UnlockResource(0, resource);
    return count;

fail:
    return -1;
}
