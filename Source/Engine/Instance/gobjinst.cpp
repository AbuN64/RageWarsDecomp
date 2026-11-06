#include "Common/output.h"
#include "Engine/events.h"
#include "Engine/Anim/compressed_motion.h"
#include "include_asm.h"
#include "Common/group.h"
#include "Common/sharedplayer.h"
#include "Common/level_actor.h"
#include "Common/access_s8_10f.h"
#include "Engine/Instance/gobjinst.h"
#include "Engine/Instance/insthdr.h"
#include "Common/shared_particleinstance.h"
#include "Common/aiprofile.h"
#include "types.h"
#include "Engine/gregion.h"
#include "Gobjinst/gameobject_movetoxzkeepheight.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Common/approachlocation.h"
#include "Common/runtime_declarations.h"
#include "Common/weapon_screen_message_operations.h"
#include "Camera/collision_sweep_views.h"
#include "Common/world.h"
#include "Common/Lone/particle_collision_probe_result.h"
#include "Common/vector4f.h"
#include "Common/particle_lighting.h"
#include "Scene/cache_allocateresourceat.h"
#include "Common/listheader.h"
#include "Scene/cache_requestresource.h"
#include "Render/setn64_getpacksection.h"
#include "Engine/lists.h"
#include "Actor/actor.h"
#include "Engine/defs.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Gobjinst/gameobject_loadmodel.h"
#include "Libsn/nav_isballisticarcobstructed_data.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Common/level_spawn.h"
#include "Common/game_player_and_menu_state.h"
#include "Gobjinst/gobjinst_data.h"
#include "Common/object_instance_transform_and_render_views.h"
#include "Common/resident_event_handler.h"
#include "Common/ppdecom_unpackresource.h"
#include "Common/material_tree.h"
#include <platform_sdk.h>
#include "Game/builddirectionmatrix.h"
#include "Engine/session.h"
#include "Link/link_dispatchmatchingtriggers.h"
#include "Insthdr/insthdr_getactorshadowradius.h"
#include "Common/ballisticparams.h"
#include "System/contact_effect.h"
#include "Common/actorresourceheader.h"
#include "Rsp/random_direction_and_affine_math.h"
#include "Common/gameplay_round_rules.h"
#include "Common/gameplay_transition.h"
#include "Common/animation_pool.h"
#include "Engine/Instance/gastate_advancerootmotion_data.h"
#include "Fx/normalize_vector.h"
#include "Ai/Enemies/turretai.h"
#include "Ai/Player/player_buildplayerviewtransform.h"
#include "Gobjinst/gobjinst_requestanimatedmodelvariant.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
#include "System/events_delivercontacteffect.h"
#include "Gastate/GAState.h"
#include "Common/gameplay_camera.h"
#include "Common/game_session.h"
#include "Common/unsigned_quotient.h"
#include "Common/shared_gameslot.h"
#include "Engine/ghot.h"
#include "Engine/visdata_decoderegiongrid.h"
#include "Fx/fx_drawboundedparticlequads.h"
#include "Gobjinst/gobjinst_buildactorpose.h"
#include "Graphu64/graphu64_buildlookatmatrix.h"
#include "Menu/Items/Scene/scene_registeractorinscenelists.h"
#include "Common/os_timer_interrupt_internals.h"
#include "Common/viewflags.h"
#include <PR/gbi.h>
#include "Common/sessionhandlerrow.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "System/textload_resettexturecache.h"
#include "Gobjinst/gastate_advancerootmotion_data.h"
#include "Render/material_color_and_fog_views.h"
#include "Common/model_render.h"
#include "Common/frag_tag_scores.h"
#include "Particle/particle_spawneffectgroup.h"
#include "Gobjinst/player_drawtintedplayer_data.h"
#include "Particle/ghot_dispatchattachmenteffects_data.h"
#include "Common/propgeometry.h"
#include "Particle/particle_releaseownerlistoneeffects.h"
#include "Common/triple.h"
#include "Engine/link.h"
#include "Engine/Instance/Gobjinst/gobjinst_drawteammaskedmodel.h"
#include "Common/math_helpers.h"
#include "Engine/gdynlight.h"
#include "Engine/Instance/gobjinst_getactoroffsetpositionandmodel.h"
#include "Engine/Instance/simpinst.h"
#include "Engine/Instance/Simpinst/simpinst_drawgroundshadow.h"
#include "Engine/Instance/gobjinst_initializeplacedactor.h"
#include "Engine/scene_drawtransitioncoloroverlay.h"
#include "Gobjinst/gobjinst_findnearestbonebounds.h"
#include "Gobjinst/gobjinst_buildactortransform.h"
#include "Gobjinst/gobjinst_buildtargetaimorientation.h"
#include "Gobjinst/gobjinst_packaffinematrixwords.h"
#include "Common/legacy_collision_actor.h"
#include "Cbarrel/barrel_spawnactoreffect.h"
#include "common.h"
#include "Common/localdecoderange.h"
#include "Common/mtx.h"
#include "Engine/Instance/Gobjinst/actor_animation_root_and_event_operations.h"
#include "Polytrak2/polytrak2_samplerotationtrack.h"
#include "Common/shared_worldfunc.h"
#include "Common/probe.h"
#include "Gobjinst/gameobject_getactorheight.h"
#include "Actors/lighting_buildlitmodel.h"
#include "Cache/cache.h"
#include "Common/obj.h"
#include "Ai/Player/player_getammocapacity.h"
#include "Engine/Instance/Gobjinst/gobjinst_buildtargetaimorientation.h"
#include "Common/format.h"
#include "data_overlay_layouts.h"
#include "Data/Overlays/Credits/linktables_addresses.h"
#include "Data/rest_source_records.h"
#include "Engine/Instance/Gobjinst/sndplayer.h"
#include "Ai/cbarrel.h"
#include "Engine/Cache/cache.h"

/* GAMEOBJECT_MOVETOXZKEEPHEIGHT.CPP */

static inline s32 currentEnabled(ActorHorizontalMovementView *actor) {
    if (actor->flags & 0x3000) return 1;
    if (actor->flags & 0x4000) return InstHdr_GetActorMotionState(actor);
    return 0;
}

void GameObject_ApplyMaterialCurrents(ActorHorizontalMovementView *actor, HorizontalMovementSurfaceView *material, CVector3 *movement, s32 applyDirectionalCurrent) {
    ActorHorizontalMovementView *rider;
    f32 speed;
    CVector3 v10,v20;
    f32 blendedYaw;
    f32 currentTargetYaw;
    f32 strength;
    f32 currentHeading;
    f32 unusedFloat;
    f32 unusedFloat1;
    f32 previousVerticalCurrent;
    f32 actorYaw;
    f32 unusedFloat2;
    f32 unusedFloat3;
    f32 currentBlend;
    f32 unusedFloat4;
    f32 currentYawStep;
    f32 wrappedTargetYaw;
    f32 targetAngle,oldAngle;
    s32 unusedValue;
    s32 unusedValue1;
    s32 riderMotionFlags;
    s32 actorCurrentEnabled;
    u16 flags;
    CVector3 *actorCurrent;

    if (actor->kind == 1) {
        rider=actor;
        actorCurrentEnabled=currentEnabled(actor);
        riderMotionFlags = rider->flags & 3;
    } else {
        actorCurrentEnabled = 0;
        riderMotionFlags = 0;
    }
    if ((riderMotionFlags != 0) || ((actorCurrentEnabled == 0) && !(material->flags & 0x8000))) {
        actor->current.x = 0.0f;
        actor->current.y = 0.0f;
        actor->current.z = 0.0f;
        return;
    }
    if ((material->flags & 0x100) && (applyDirectionalCurrent != 0)) {
        v10.x = (f32) material->x * 0.007874016f;
        v10.y = (f32) material->y * 0.007874016f;
        v10.z = (f32) material->z * 0.007874016f;
        strength = (f32) material->strength;
        speed=strength * 3.0f;
        currentYawStep = (strength + 1.0f) * 0.00872664712369442f;
        Graphu64_ScaleVector(&v10,&v10,speed);
        flags = material->flags;
        if (flags & 0x600) {
            if (flags & 0x400) {
                currentYawStep = -currentYawStep;
            }
            if (actor->kind == 1) {
                actor->yaw = (f32) (actor->yaw + currentYawStep);
            }
        }
        if ((material->flags & 0x2000) && (actor->kind == 1)) {
            rider=actor;
            v20=v10;
            v20.y = 0.0f;
            currentHeading = Graphu64_GetHorizontalAngle(&v20);
            actorYaw = actor->yaw;
            currentTargetYaw = currentHeading;
            blendedYaw = actorYaw;
            if (currentHeading != actorYaw) {
                Graphu64_WrapPeriodicValue(&blendedYaw);
                Graphu64_WrapPeriodicValue(&currentTargetYaw);
                if (blendedYaw > currentTargetYaw) {
                    wrappedTargetYaw=currentTargetYaw+6.2831855f;
                    if ((wrappedTargetYaw-blendedYaw)<(blendedYaw-currentTargetYaw)) currentTargetYaw=wrappedTargetYaw;
                } else {
                    wrappedTargetYaw=currentTargetYaw-6.2831855f;
                    if ((blendedYaw-wrappedTargetYaw)<(currentTargetYaw-blendedYaw)) currentTargetYaw=wrappedTargetYaw;
                }
                targetAngle=currentTargetYaw; oldAngle=blendedYaw;
                if (oldAngle < targetAngle) {
                    blendedYaw=oldAngle+((f32)material->strength*g_materialCurrentStrengthScales[1]*g_frameElapsedTime*0.017453294f);
                    if (targetAngle<blendedYaw) blendedYaw=targetAngle;
                } else {
                    blendedYaw=oldAngle-((f32)material->strength*g_materialCurrentStrengthScales[1]*g_frameElapsedTime*0.017453294f);
                    if (blendedYaw<targetAngle) blendedYaw=targetAngle;
                }
                Graphu64_WrapPeriodicValue(&blendedYaw);
            }
            rider->yaw = blendedYaw;
        }
    } else {
        v10.x = 0.0f;
        v10.y = 0.0f;
        v10.z = 0.0f;
    }
    currentBlend = (f32) material->strength * g_materialCurrentStrengthScales[0] * g_frameElapsedTime;
    currentBlend = ((currentBlend < 0.0f ? 0.0f : currentBlend) > 1.0f ? 1.0f : (currentBlend < 0.0f ? 0.0f : currentBlend));
    actorCurrent=&actor->current;
    Graphu64_InterpolateVector(actorCurrent, currentBlend, actorCurrent, &v10);
    movement->x = (f32) (movement->x + actor->current.x);
    movement->z = (f32) (movement->z + actor->current.z);
    if (material->flags & 0x100) {
        if (v10.y != 0.0f) {
            actor->vertical = 0.0f;
        } else {
            previousVerticalCurrent = actor->current.y;
            actor->current.y = (f32) (previousVerticalCurrent + ((v10.y - previousVerticalCurrent) * 0.2f));
        }
        actor->vertical = (f32) (actor->vertical + ((2.0f * (actor->current.y * 10.24f)) + 4.0f));
        return;
    }
    actor->current.y += (v10.y-actor->current.y)*0.2f;
}

/* Resets an object through Insthdr_ResetInstanceRenderIndices, then zeroes its position, motion angles,
   attachment and motion state and stores g_resetActorFloorDirectionY as its floor direction. */

void GameObject_ResetActorMotion(void *levelActor) {
    float k;

    Insthdr_ResetInstanceRenderIndices(levelActor);
    k = g_resetActorFloorDirectionY;
    ((LevelActor *)levelActor)->position1.x = 0;
    ((LevelActor *)levelActor)->position1.y = 0;
    ((LevelActor *)levelActor)->position1.z = 0;
    ((LevelActor *)levelActor)->motionAngles.x = 0;
    ((LevelActor *)levelActor)->motionAngles.y = 0;
    ((LevelActor *)levelActor)->motionAngles.z = 0;
    ((LevelActor *)levelActor)->attached = 0;
    ((LevelActor *)levelActor)->motionState = 0;
    ((LevelActor *)levelActor)->motionIndex = -1;
    ((LevelActor *)levelActor)->floorHeight = 0;
    ((LevelActor *)levelActor)->floorDirection.x = 0;
    ((LevelActor *)levelActor)->floorDirection.z = 0;
    ((LevelActor *)levelActor)->floorDirection.y = k;
}

void GameObject_MoveToXZKeepHeight(Shared_ParticleInstance *actor, f32 x, f32 z) {
    CVector3 saved;
    CVector3 position;
    s32 keep;
    f32 height;

    height = actor->pos.y - Region_GetPolygonHeight(actor->region, actor->pos.x, actor->pos.z);
    saved = actor->velocity;
    actor->velocity.x = actor->velocity.y = actor->velocity.z = 0.0f;
    position.x = x;
    position.y = actor->pos.y;
    position.z = z;
    keep = g_portalAlternateCollisionQuery.w[0];
    Unicol_MoveActorWithCollision(actor, position, g_portalAlternateCollisionQuery.w);
    g_portalAlternateCollisionQuery.w[0] = keep;
    actor->velocity = saved;
    actor->pos.y = Region_GetPolygonHeight(actor->region, actor->pos.x, actor->pos.z) + height;
}

/* GOBJINST.CPP */

/* Returns the collisions an object would meet moving to a position, without committing the move: picks the collision set for the object
 * (g_portalAlternateCollisionQuery for flagged players; otherwise by Insthdr_IsInactiveOrCollisionOption4 and then Insthdr_GetModelCollisionFlag8 or Insthdr_GetModelCollisionFlag1 among
 * g_portalDefaultCollisionQuery, g_portalNoModelFlagCollisionQuery, g_portalModeCollisionQuery and g_portalAlternateCollisionQuery), reports it through the optional out pointer, runs
 * the collision mover Collision_ProbeGround_de and restores the object's header. */

/* Spawns and initializes an actor with model, transforms, collision body, effects and default bounds. */

struct Shared_World;

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
            player = (char *)&g_gamePlayerAndMenuState.entries[i];
            if (player == obj) {
                return 0;
            }
            if ((char *)&((SharedPlayer *)player)->views1C.view2E8_27.weapon == obj) {
                return &g_actorDefinitionTable[0];
            }
        }
    }
    return g_actorTypeOperations[kind];
}


s32 Gobjinst_ProbeActorMovement(struct ActorInstanceHeader *actorState, CVector3 position, char **out) {

    struct ActorInstanceHeader saved;
    char *set;
    s32 grounded;
    s32 collisions;
    struct LevelActor *actor = (struct LevelActor *)actorState;

    if (actor->kind == 1 && (actor->flags & 0x300000) != 0) {
        set = (char *)&g_portalAlternateCollisionQuery;
    } else {
        grounded = Insthdr_GetModelCollisionFlag1(actorState);
        if (Insthdr_IsInactiveOrCollisionOption4(actorState) == 0) {
            set = (char *)&g_portalAlternateCollisionQuery;
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

s32 Gobjinst_HasClearPathToActor(struct ActorInstanceHeader *from, struct ActorInstanceHeader *to) {

    struct ActorInstanceHeader savedFrom;
    CVector3 desired;
    f32 scale;
    s32 collisions;

    savedFrom = *from;
    scale = g_actorVisibilityProbeHeightScale;
    ((struct LevelActor *)from)->position0.y += Gobjinst_GetActorHeight(from) * scale;
    desired = ((struct LevelActor *)to)->position0;
    desired.y += Gobjinst_GetActorHeight(to) * scale;
    collisions = Unicol_MoveActorWithCollision(from, desired, &g_particleCollisionProbeResult);
    *from = savedFrom;

    return collisions == 0;
}

s32 Gobjinst_HasClearInstancePath(struct ActorInstanceHeader *actorState, CVector3 position, UnicolMotionSettings *collisionSettings) {
    struct ActorInstanceHeader saved;
    UnicolMotionSettings collision_info;
    s32 collisions;

    saved = *actorState;
    collision_info = *collisionSettings;
    collision_info.ground_behavior = 0;
    collision_info.instance_behavior = 1;
    Unicol_MoveActorWithCollision(actorState, position, &collision_info);
    *actorState = saved;

    collisions = g_currentActorInstance.instance0 || g_currentActorInstance.contactFlags9C;
    return !collisions;
}

/** Thin wrapper around InstHdr_GetActorMotionIndex, discarding its result. */
void Gobjinst_ReadActorMotionIndex(void *record) {
    InstHdr_GetActorMotionIndex(record);
}

void Gobjinst_InitializeActor(char *obj, s32 model, s32 kind, s32 surfaceType, void *info, s32 effect, s32 owner, f32 heading,
    CVector3 pos, s32 flags, CVector3 extent, CVector3 offset, s32 trailingUnused) {
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
    ((LevelActor *)obj)->kind = 1;
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
    ((LevelActor *)obj)->ribbonReferenceCount = 0;
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
    entries = (s32 *)((struct StridedTable *)data)->data;
    total = ((struct StridedTable *)(data))->count;
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

/* GAMEOBJECT_LOADMODEL.CPP */

void Gobjinst_LoadModel(void *actorStorage, s32 *modelDirectory, s32 directoryBank, s32 extra) {
    s32 *animationMetadata;
    void **resource1;
    void **resource2;
    s32 *entry;
    void *modelBounds;
    void *node;
    s32 key;
    s32 found;

    ((LevelActor *)actorStorage)->resourceHandle = -1;
    ((LevelActor *)actorStorage)->resourceState = 0;
    ((LevelActor *)actorStorage)->resourceWindow = 0;
    ((LevelActor *)actorStorage)->flags &= 0xFFFBFFFF;
    key = SetN64_GetDirectoryEntry(modelDirectory, directoryBank, (u16)((LevelActor *)actorStorage)->modelIndex);
    resource1 = Cache_RequestResource(0, key, key, 24, 0, 0, 0, &g_gameObjectAnimIndexText, 1);
    if (resource1 != 0) {
        entry = *resource1;
        ((LevelActor *)actorStorage)->animationKey = SetN64_GetDirectoryEntry(entry, key, 1);
        found = Cache_RequestWordCountedResource(0, &animationMetadata, ((LevelActor *)actorStorage)->animationKey, &s_animModelsIndexText, 1);
        if (found != 0) {
            ((LevelActor *)actorStorage)->stateE7 = (u8)*animationMetadata;
            ((LevelActor *)actorStorage)->resourceAlignment = ((*animationMetadata * 4) + 15) & ~7;
            Cache_UnlockResource(0, (void *)found);
        }
        ((LevelActor *)actorStorage)->resource = SetN64_LocatePackSection((s32)entry, key, 0, &((LevelActor *)actorStorage)->resourceFlags);
        ((LevelActor *)actorStorage)->resourceKey = SetN64_GetDirectoryEntry(entry, key, 2);
        resource2 = Cache_RequestResource(0, ((LevelActor *)actorStorage)->resource,
            ((LevelActor *)actorStorage)->resource, ((LevelActor *)actorStorage)->resourceFlags,
            0, 0, 0, &g_gameObjectResetAnimInfoText, 1);
        if (resource2 != 0) {
            node = *resource2;
            modelBounds = SetN64_GetPackSection(node, 0);
            ((LevelActor *)actorStorage)->controllerUpdate(actorStorage, &((LevelActor *)actorStorage)->behaviorFlags);
            Graphu64_TransformBoundingBox(&((LevelActor *)actorStorage)->transform, (s32)modelBounds, &((LevelActor *)actorStorage)->bounds);
            Gastate_ResetAnimationReference(&((LevelActor *)actorStorage)->animationTime);
            Gastate_ResetAnimationReference((char *)&((LevelActor *)actorStorage)->animationReference);
            ((LevelActor *)actorStorage)->stateE6 = (u8)((ResourceManagerState *)SetN64_GetPackSection(node, 1))->count;
            ((LevelActor *)actorStorage)->flags |= 0x40000;
            if (extra > 0) {
                extra = Gobjinst_ChooseAnimationVariant(actorStorage, extra, -1);
            } else {
                extra = -extra;
            }
            if (extra == -1) {
                extra = 0;
            }
            ((LevelActor *)actorStorage)->nextAnimation = extra;
            ((LevelActor *)actorStorage)->animationPending = 0;
            if (((LevelActor *)actorStorage)->animation != extra) {
                ((LevelActor *)actorStorage)->animationChanged = 1;
            }
            ((LevelActor *)actorStorage)->animationState = -1;
            ((LevelActor *)actorStorage)->lean = extra;
            Cache_UnlockResource(0, resource2);
        }
        Cache_UnlockResource(0, resource1);
    }
}

/* Update or blend object rotation when the movement state permits it. */

struct CollisionInfo;

void Gobjinst_UpdateActorRootDisplacement(Actor36 *actor) {
    CVector3 before, after;
    u32 flags, mode;
    void **resource;
    void *box;
    flags = actor->flags;
    if (!(flags & 0x40000)) return;
    if (g_world.mode == 4 && !(flags & 0x2000)) return;
    mode = flags & 0x300000;
    before = actor->position;
    Gobjinst_AdvanceActorRootMotion(actor);
    after = actor->position;
    actor->position = before;
    if (mode == 0 && *actor->kind != 0) {
        Graphu64_SubtractVectors(&after, &after, &before);
        Graphu64_AddVec3(&after, &after, &actor->displacement);
        Gobjinst_MoveActorWithContactCallback((void *)actor, &after);
        if (*actor->kind == 1) {
            Scene_UpdateMovementTriggers(&g_world, actor, &before, &actor->position);
        }
    }
    Gobjinst_UpdateActorGroundRotation((void *)actor);
    resource = Cache_RequestResource(0, actor->size, actor->size, actor->alignment, 0, 0, 0, s_actorModelAllocationTag, 1);
    if (resource != 0) {
        box = SetN64_GetPackSection(*resource, 0);
        actor->update(actor, actor->state);
        Graphu64_TransformBoundingBox(actor->matrix, box, &actor->box);
        Cache_UnlockResource(0, (void *)resource);
    }
}

void Gobjinst_UpdateActorGroundRotation(ActorModelLoadState *actor) {
    CQuatern vec;
    f32 rotationBlend;
    f32 rotationBlendRate;
    s32 resetRotationFlag;
    s32 rotationState;
    s32 actorFlags;
    s32 flags;
    void *rotation;
    void *rotationDestination;
    actorFlags = actor->flags;
    flags = actorFlags & 0x300000;
    if (!(actorFlags & 1) && (rotationState = InstHdr_GetActorMotionState(actor), (actor->modelHeader != NULL)) && (vec = Insthdr_BuildActorGroundRotation(actor), resetRotationFlag = actor->modelHeader->spreadHighWord & 1, (InstHdr_UsesGroundRotation(actor) != 0))) {
        if (resetRotationFlag != 0) {
            vec.x = vec.y = vec.z = 0.0f;
            vec.w = g_actorGroundRotationUnitW;
        }
        if (flags) {
            if ((!(actor->flags & 0x1000) && (rotationDestination = actor->rotation, (rotationState != 0))) || (rotationDestination = actor->rotation, (resetRotationFlag != 0))) {
                Graphu64_ApproachQuaternion(rotationDestination, &vec);
            }
        } else {
            if ((rotationState != 0) && !(actor->flags & 0x1000)) {
                rotationBlend = g_frameElapsedTime; rotationBlendRate = *(&g_actorGroundRotationUnitW + 1);
            } else {
                rotationBlend = g_frameElapsedTime; rotationBlendRate = *(&g_actorGroundRotationUnitW + 2);
            }
            rotationBlend = rotationBlend * rotationBlendRate;
            rotation = actor->rotation;
            if (rotationBlend > *(f32 *)&g_actorRotationBlendAndResourceTuning) {
                rotationBlend = *(f32 *)&g_actorRotationBlendAndResourceTuning;
            }
            Graphu64_InterpolateQuaternionWithLinearFallback(rotation, rotationBlend, rotation, &vec);
        }
    }
}

void Gobjinst_MoveActorWithContactCallback(char *actor, CVector3 *destination) {
    struct CollisionInfo *collision;
    u16 *old_contact;
    s32 collided;
    f32 saved;
    void (*callback)(void *, void *, struct CollisionInfo *);

    if ((((ActorModelResourceView *)(actor))->flags & 0x10000) && ((ActorModelResourceView *)(actor))->collisionResource != 0) {
        collision = ((ActorCollisionResourceView *)(((ActorModelResourceView *)(actor))->collisionResource))->collisionInfo;
        if (collision == 0) {
            collision = &g_defaultActorCollisionInfo;
        }
        saved = ((ActorCollisionDataView *)(collision))->collisionParams.value;
        if ((u32)(((ActorModelResourceView *)(actor))->typeId - 11020) < 8) {
            ((ActorCollisionDataView *)(collision))->collisionParams.word = 0;
        }
        old_contact = ((ActorModelResourceView *)(actor))->model;
        collided = Unicol_MoveActorWithCollision(actor, *destination, collision);
        if (old_contact != ((ActorModelResourceView *)(actor))->model) {
            ((ActorModelResourceView *)(actor))->previousModel = old_contact;
        }
        ((ActorCollisionDataView *)(collision))->collisionParams.value = saved;
        if (old_contact != 0 && ((ActorModelResourceView *)(actor))->model != 0 &&
            *old_contact != *((ActorModelResourceView *)(actor))->model &&
            *((ActorModelResourceView *)(actor))->definition == 1) {
            Link_DispatchObjectLinks((s32)old_contact, 128, actor);
            Link_DispatchObjectLinks((s32)((ActorModelResourceView *)(actor))->model, 64, actor);
        }
        if (collided != 0 && !(((ActorModelResourceView *)(actor))->flags & 0x300000) &&
            *((ActorModelResourceView *)(actor))->definition == 1 && g_currentActorInstance.instance0 != 0 &&
            *(u8 *)g_currentActorInstance.instance0 == 1) {
            Link_DispatchActorLinks(g_currentActorInstance.instance0, 32, actor);
        }
        callback = ((struct ActorModelCallbackView *) ((char *) actor))->callback;
        if (callback != 0) {
            callback(actor, &((LevelActor *)actor)->behaviorFlags, collision);
        }
    } else {
        ((ActorModelResourceView *)(actor))->position0 = *destination;
    }
}

/* GASTATE_ADVANCEROOTMOTION_DATA.CPP */

/* Fires the effect events of an object's animation that fall within a frame window: only for the object's
 * own animation or an object flagged 0x4000000; each event whose frame lies in [from, to) is
 * placed from its local point through the object's matrix when it names no bone, otherwise through its
 * bone matrix (or at the object's position when it has none), and for models 0x44E, 0x451 and 0x453 an
 * effect flagged 4 fires only if its bone's hit box shares the object's mask; each fired event spawns its
 * effect through Events_DeliverContactEffect_ActorAnimationRootAndEventOperations and is counted in g_actorRootMotionSampleCount. */

/* Returns an actor's aiming orientation: a controlled actor turns a quarter turn about the vertical from its
 * weapon's orientation, or from the player's own orientation from Player_BuildPlayerOrientation when unarmed; an
 * actor of kind 4 composes a pitch from 0x294 with a yaw from its heading 0x6C and applies them to its body
 * orientation from Turret_BuildPlaneRot; any other actor turns its orientation by its heading. Quaternions
 * are composed through MultiplyQuaternions, keeping the latest sine in g_turretAimSine. */

/* Returns an actor's aim with auto-aim applied: with no assist cone the actor's aiming orientation from
 * Gobjinst_BuildActorAimQuaternion is returned unchanged; otherwise, of the live entities other than the actor (not flagged 1,
 * with a body), the one whose aim point (half its height above its top) lies most nearly along the
 * aim direction from the given point, within the cone (in degrees, halved), pulls the aim toward it by an
 * angle that fades with the fourth root of how far off-axis it is. The applied correction is also written
 * to the optional assist quaternion (identity when nothing is in range). */

/* Sways a model part: from the frame count g_gameFrameCounter, a per-part phase ((flags & 0x38) * 50, plus 40
 * unless flag 4 is set) and the part's time divided by 113, it reads a 120-step sine table at g_actorMatrixWobbleSamples to
 * build a rotation axis and angle for the part's sway mode (2: about a wobbling z/y axis, 0x82: doubled
 * about a wobbling x/y axis, 0x40: doubled about a fully wobbling axis, 1: 0.7 of the swing about y) and
 * applies that rotation to the part's matrix about its own origin; other modes leave it unchanged. */


void Gobjinst_AdvanceActorRootMotion(void *actor) {
    CVector3 first;
    CVector3 second;
    CVector3 saved;
    CVector3 moved;
    MatrixF matrix;
    s32 active;
    f32 first_value;
    f32 second_value;
    void **resource;
    void *track0;
    void *track1;
    f32 value;

    if (g_world.mode == 4) {
        if ((s8)((Actor36 *)actor)->currentTrack.active == 0)
        ((Actor36 *)actor)->currentTrack.blending = 1;
        if ((s8)((Actor36 *)actor)->previousTrack.active == 0)
        ((Actor36 *)actor)->previousTrack.blending = 1;
        if ((s8)((Actor36 *)actor)->currentTrack.active == 0 && !(((Actor36 *)actor)->flags & 0x400))
        return;
        if (!(((Actor36 *)actor)->flags & 0x2000))
        return;
    }

    resource = Cache_RequestResource(0, ((Actor36 *)actor)->animationKey, ((Actor36 *)actor)->animationKey,
        ((((Actor36 *)actor)->animationCount * 4) + 15) & ~7, 4, 0, 0,
        &g_actorRotationBlendAndResourceTuning + 4, 0);
    if (resource == 0)
    return;

    track0 = &((Actor36 *)(actor))->currentTrack;
    track1 = &((Actor36 *)(actor))->previousTrack;
    Gastate_SwitchRequestedAnimation(track0, (s32)*resource, ((Actor36 *)actor)->animationKey, 1, &active, track1);
    if (Gastate_IsAnimationResourceRetained(track0) != 0) {
        void *entry;
        Gastate_AdvanceRootMotion(track0, &first, &first_value, actor);
        value = first_value;
        saved = first;
        if (active != 0 && ((Anim *)track1)->current != -1) {
            u16 count;
            entry = Gastate_GetAnimationPoseSection(track0);
            if (((AnimationBlendEntry *)entry)->frames != 0) {
                ((Actor36 *)actor)->flags |= 0x400;
                count = ((AnimationBlendEntry *)entry)->frames;
                ((Actor36 *)actor)->blendTime = 0.0f;
                ((Actor36 *)actor)->blendFrames = count;
                ((Actor36 *)actor)->blendStart = ((AnimationBlendEntry *)entry)->start;
                ((Actor36 *)actor)->blendEnd = ((AnimationBlendEntry *)entry)->end;
            } else {
                ((Actor36 *)actor)->flags &= ~0x400;
            }
        }
        if (((Actor36 *)actor)->flags & 0x400) {
            Gastate_SwitchRequestedAnimation(track1, (s32)*resource, ((Actor36 *)actor)->animationKey, 0, 0, 0);
            if (Gastate_IsAnimationResourceRetained(track1) != 0) {
                f32 time;
                f32 end;
                time = ((Actor36 *)actor)->blendTime + g_frameElapsedTime;
                end = (f32)((Actor36 *)actor)->blendFrames;
                ((Actor36 *)actor)->blendTime = time;
                if (end < time) {
                    ((Actor36 *)actor)->flags &= ~0x400;
                } else {
                    f32 endTangent = (f32)((Actor36 *)actor)->blendEnd;
                    f32 startTangent = (f32)((Actor36 *)actor)->blendStart;
                    f32 progress = time / (end + g_frameElapsedTime);
                    ((Actor36 *)actor)->blend = (((endTangent + g_actorRootMotionBlendCoefficients + startTangent) * progress * progress * progress) +
                        ((((&g_actorRootMotionBlendCoefficients)[1] - endTangent) - (2.0f * startTangent)) * progress * progress) + (startTangent * progress));
                    Gastate_AdvanceRootMotion(&((Actor36 *)(actor))->previousTrack, &second, &second_value, actor);
                    Graphu64_InterpolateVector(&saved, ((Actor36 *)actor)->blend, &second, &first);
                    value = Graphu64_InterpolateWrappedValue(((Actor36 *)actor)->blend, second_value, first_value);
                }
                Gastate_ReleaseAnimationResource(track1);
            } else {
                ((Actor36 *)actor)->flags &= ~0x400;
            }
        }
        Gastate_ReleaseAnimationResource(track0);
        if (((Actor36 *)actor)->flags & 0x20000) {
            ((Actor36 *)actor)->heading -= value;
            Graphu64_WrapPeriodicValue(&((Actor36 *)(actor))->heading);
            saved.z = saved.y;
            saved.y = 0.0f;
            BuildYawMatrix(&matrix, ((Actor36 *)actor)->heading);
            Graphu64_TransformPoint(&matrix, &saved, &moved);
            ((Actor36 *)actor)->position.x += moved.x * ((Actor36 *)actor)->scaleX;
            ((Actor36 *)actor)->position.z += moved.z * ((Actor36 *)actor)->scaleZ;
        } else if (!(((Actor36 *)actor)->flags & 0x300000) && ((Actor36 *)actor)->ownerId == 311) {
            ((Actor36 *)actor)->heading -= value;
            Graphu64_WrapPeriodicValue(&((Actor36 *)(actor))->heading);
        }
    }
    Cache_UnlockResource(0, resource);
}

void Gobjinst_DispatchAnimationIntervalEvents(char *obj, void *anim, f32 from, f32 to) {
    CVector3 pos;
    CVector3 local;
    f32 matrix[16];
    CROMEventEntry *events;
    s32 count;
    s32 i;
    s32 checkMask;
    s32 fire;
    s32 *resource;
    struct ActorAnimationEventTable *table;

    if (!(((struct RootMotionActorView *) obj)->flags & 0x4000000) && anim != &((LevelActor *)obj)->animationTime) {
        return;
    }
    switch (((struct RootMotionActorView *) obj)->type) {
    case 1102:
    case 1105:
    case 1107:
        checkMask = 1;
        break;
    default:
        checkMask = 0;
        break;
    }
    table = 0;
    events = Gastate_GetAnimationEventEntries(anim);
    count = Gastate_GetAnimationEventCount(anim);
    resource = 0;
    for (i = 0; i < count; i++) {
        if (from <= (f32)events[i].frame && (f32)events[i].frame < to) {
            fire = 1;
            if (events[i].bone == -1) {
                local.x = events[i].local.x;
                local.y = events[i].local.z;
                local.z = events[i].local.y;
                Graphu64_TransformPoint(&((LevelActor *)obj)->transform, &local, &pos);
            } else {
                if (checkMask && (g_effectCallbackFlags[events[i].effect].flags & 4)) {
                    if (resource == 0) {
                        resource = Gobjinst_RequestAnimatedModelVariant(obj, ((struct RootMotionActorView *) obj)->team);
                        if (resource == 0) {
                            goto masked;
                        }
                        table = SetN64_GetPackSection(*resource, 5);
                    }
                    fire = ((ModelBoneRecord *)&table->records[events[i].bone * table->entrySize])->eventMask & ((struct RootMotionActorView *) obj)->boneMask;
                }
                masked:
                if (fire == 0) {
                    continue;
                }
                if (((struct RootMotionActorView *) obj)->previousPoseMatrices != 0) {
                    Graphu64_ConvertMatrixToFloat(matrix, ((struct RootMotionActorView *) obj)->previousPoseMatrices + (events[i].bone << 6));
                    Graphu64_TransformPoint(matrix, &events[i].local, &pos);
                } else {
                    pos = ((struct RootMotionActorView *) obj)->position0;
                }
            }
            if (fire != 0) {
                Events_DeliverContactEffect(obj, obj, events[i].effect, -1, *(CVector3 *)&(pos), *(ContactEffectStyle *)&(events[i].params));
                g_actorRootMotionSampleCount++;
            }
        }
    }
    if (resource != 0) {
        Cache_UnlockResource(0, resource);
    }
}

CQuatern Gobjinst_BuildActorAimQuaternion(char *actor) {
    CQuatern result;
    CQuatern pitch;
    CQuatern yaw;
    CQuatern both;
    CQuatern base;
    CQuatern own;
    char *player;
    char *weapon;
    f32 angle;
    f32 sine;

    if (((LevelActor *)actor)->flags & 0x300000) {
        player = ((LevelActor *)actor)->controller;
        weapon = ((Player *)player)->camera;
        if (weapon != 0) {
            angle = 1.5707964f;
            g_turretAimSine = Gu_Sinf(angle);
            yaw.x = 0.0f;
            yaw.y = g_turretAimSine;
            yaw.z = 0.0f;
            yaw.w = Math_Cosf(angle);
            MultiplyQuaternions(&result, &yaw, &((PlayerCameraTargetView *)weapon)->orientation);
        } else {
            angle = 1.5707964f;
            Player_BuildPlayerOrientation(player, &own);
            g_turretAimSine = Gu_Sinf(angle);
            yaw.x = 0.0f;
            yaw.y = g_turretAimSine;
            yaw.z = 0.0f;
            yaw.w = Math_Cosf(angle);
            MultiplyQuaternions(&result, &yaw, &own);
        }
    } else if (((LevelActor *)actor)->definition->kind == 4) {
        sine = Gu_Sinf(((LevelActor *)actor)->pitch * 0.5f);
        pitch.x = sine;
        pitch.y = 0.0f;
        pitch.z = 0.0f;
        angle = ((LevelActor *)actor)->pitch * 0.5f;
        g_turretAimSine = sine;
        pitch.w = Math_Cosf(angle);
        sine = Gu_Sinf((((LevelActor *)actor)->yaw + 3.1415927f) * 0.5f);
        yaw.x = 0.0f;
        yaw.y = sine;
        yaw.z = 0.0f;
        angle = (((LevelActor *)actor)->yaw + 3.1415927f) * 0.5f;
        g_turretAimSine = sine;
        yaw.w = Math_Cosf(angle);
        MultiplyQuaternions(&both, &pitch, &yaw);
        Turret_BuildPlaneRot(&base, actor, &((LevelActor *)actor)->behaviorFlags);
        MultiplyQuaternions(&result, &both, &base);
    } else {
        sine = Gu_Sinf((((LevelActor *)actor)->yaw + 3.1415927f) * 0.5f);
        yaw.x = 0.0f;
        yaw.y = sine;
        yaw.z = 0.0f;
        angle = (((LevelActor *)actor)->yaw + 3.1415927f) * 0.5f;
        g_turretAimSine = sine;
        yaw.w = Math_Cosf(angle);
        MultiplyQuaternions(&result, &yaw, &((LevelActor *)actor)->rotation);
    }
    return result;
}

CQuatern Gobjinst_BuildAssistedAimQuaternion(char *actor, CVector3 point, CQuatern *assist, f32 cone) {
    CVector3 dir;
    CVector3 local;
    CVector3 aim;
    CVector3 axis;
    CVector3 best;
    CVector3 center;
    CQuatern base;
    CQuatern turn;
    CQuatern result;
    f32 matrix[16];
    char *entity;
    char *target;
    s32 count;
    s32 i;
    f32 bestDot;
    f32 dot;
    f32 angle;

    local.x = 0.0f;
    local.y = 0.0f;
    local.z = 1.0f;
    base = Gobjinst_BuildActorAimQuaternion(actor);
    if (cone == 0.0f) {
        if (assist != 0) {
            assist->x = assist->y = assist->z = 0.0f;
            assist->w = 1.0f;
        }
        return base;
    }
    MatrixFromQuaternion(&base, matrix);
    Graphu64_TransformPoint(matrix, &local, &aim);
    i = 0;
    target = 0;
    bestDot = Math_Cosf(cone * 0.008726647f);
    count = g_world.registeredCount;
    for (; i < count; i++) {
        entity = g_playerAimCandidateActors[i];
        if (entity == actor || (((LevelActor *)(entity))->flags & 1) || ((LevelActor *)(entity))->active == 0) {
            continue;
        }
        center = ((LevelActor *)(entity))->position0;
        center.y += ((LevelActor *)(entity))->eyeHeight;
        center.y += Gobjinst_GetActorHeight(entity) * 0.5f;
        Graphu64_SubtractVectors(&dir, &center, &point);
        Graphu64_NormalizeVec3(&dir);
        dot = aim.x * dir.x + aim.y * dir.y + aim.z * dir.z;
        if (bestDot < dot) {
            bestDot = dot;
            best = dir;
            target = entity;
        }
    }
    if (target != 0) {
        Graphu64_CrossVectors(&axis, &aim, &best);
        Graphu64_NormalizeVec3(&axis);
        angle = Graphu64_ArcCos(bestDot);
        angle *= Gu_Sqrtf(Gu_Sqrtf(1.0f - angle / (cone * 0.008726647f)));
        angle *= 0.5f;
        g_turretAimSine = Gu_Sinf(angle);
        turn.x = axis.x * g_turretAimSine;
        turn.y = axis.y * g_turretAimSine;
        turn.z = axis.z * g_turretAimSine;
        turn.w = Math_Cosf(angle);
        MultiplyQuaternions(&result, &base, &turn);
        if (assist != 0) {
            *assist = turn;
        }
        return result;
    }
    if (assist != 0) {
        assist->x = assist->y = assist->z = 0.0f;
        assist->w = 1.0f;
    }
    return base;
}

void Gobjinst_ApplyImpactBoneTwist(char *actor, ActorBoneTwistState *twistState, char *boneMatrix, CVector3 impactPosition,
    CVector3 impactDirection, s32 hitBoneIndex) {
    CVector3 twistAxis;
    CVector3 boneOrigin;
    CVector3 perpendicularDirection;
    s32 *modelResource;
    ActorAnimationEventTable *boneTable;
    s32 ancestorBoneIndex;
    s32 chainSlot;
    ModelBoneRecord *boneEntry;

    if (twistState->state != 60) {
        if (twistState->count < 23) {
            modelResource = Gobjinst_RequestAnimatedModelVariant(actor, actor[1]);
            if (modelResource != 0) {
                boneTable = SetN64_GetPackSection((void *)*modelResource, 5);
                boneEntry = (ModelBoneRecord *)&boneTable->records[hitBoneIndex * boneTable->entrySize];
                ancestorBoneIndex = hitBoneIndex;
                if ((boneEntry->flags & 3) == 3) {
                    Cache_UnlockResource(0, modelResource);
                    return;
                }
                chainSlot = 0;
                do {
                    twistState->ancestorBones[chainSlot] = ancestorBoneIndex;
                    ancestorBoneIndex = boneEntry->parent;
                    chainSlot++;
                    if (ancestorBoneIndex != -1) {
                        boneEntry = (ModelBoneRecord *)&boneTable->records[ancestorBoneIndex * boneTable->entrySize];
                    }
                } while (chainSlot < 4);
                Cache_UnlockResource(0, modelResource);
                twistState->count = 25;
                boneOrigin.x = ((Matrix *)boneMatrix)->m[12];
                boneOrigin.y = ((Matrix *)boneMatrix)->m[13];
                boneOrigin.z = ((Matrix *)boneMatrix)->m[14];
                Graphu64_SubtractVectors(&impactPosition, &impactPosition, &boneOrigin);
                Graphu64_CrossVectors(&twistAxis, &impactPosition, &impactDirection);
                Graphu64_NormalizeVec3(&twistAxis);
                Graphu64_NormalizeVec3(&impactPosition);
                Graphu64_NormalizeVec3(&impactDirection);
                Graphu64_CrossVectors(&perpendicularDirection, &twistAxis, &impactPosition);
                Graphu64_ScaleVector(&twistAxis, &twistAxis,
                    (perpendicularDirection.x * impactDirection.x) + (perpendicularDirection.y * impactDirection.y) +
                    (perpendicularDirection.z * impactDirection.z));
                Graphu64_NormalizeVec3(&twistAxis);
                ((BoneTwistAxis *)(twistState))->value = twistAxis;
            }
        }
    }
}

void Gobjinst_ApplyTimedMatrixWobble(s32 time, s32 flags, f32 *matrix) {
    f32 rotation[16];
    f32 inverse[16];
    CVector3 origin;
    CVector3 axis;
    u32 t;
    f32 angle;
    f32 flip;
    s32 mode;

    t = g_gameFrameCounter;
    t += (flags & 0x38) * 50;
    t += (u32)(time & 0xFFFF) / 113;
    if (!(flags & 4)) {
        t += 40;
    }
    axis.x = 0.0f;
    axis.z = 0.0f;
    axis.y = 1.0f;
    mode = flags & 0xC3;
    if (mode == 2) {
        axis.z = 1.0f;
        axis.x = 0.0f;
        angle = g_actorMatrixWobbleSamples.value[t % 120] - 0.5f;
        axis.y = g_actorMatrixWobbleSamples.value[(t + 12) % 120];
    } else if (mode == 130) {
        axis.x = 1.0f;
        axis.z = 0.0f;
        angle = g_actorMatrixWobbleSamples.value[t % 120] - 0.5f;
        axis.y = g_actorMatrixWobbleSamples.value[(t + 12) % 120];
        angle *= 2.0f;
    } else if (mode == 64) {
        angle = g_actorMatrixWobbleSamples.value[(t + 30) % 120] - 0.5f;
        axis.x = g_actorMatrixWobbleSamples.value[(t + 12) % 120];
        axis.y = g_actorMatrixWobbleSamples.value[(t + 42) % 120];
        axis.z = g_actorMatrixWobbleSamples.value[(t + 110) % 120];
        angle *= 2.0f;
    } else if (mode == 1) {
        angle = g_actorMatrixWobbleSamples.value[(t + 70) % 120] - 0.5f;
        angle *= 0.7f;
    } else {
        return;
    }
    Graphu64_NormalizeVec3(&axis);
    origin.x = matrix[12];
    origin.y = matrix[13];
    origin.z = matrix[14];
    CopyMatrix(inverse, matrix);
    flip = -1.0f;
    Graphu64_ScaleVector(&origin, &origin, flip);
    TranslateMatrix(inverse, origin.x, origin.y, origin.z);
    Graphu64_BuildAxisAngleMatrix(rotation, angle, axis.x, axis.y, axis.z);
    Graphu64_MultiplyAffineMatrices(matrix, inverse, rotation);
    Graphu64_ScaleVector(&origin, &origin, flip);
    TranslateMatrix(matrix, origin.x, origin.y, origin.z);
}

/* GOBJINST_BUILDACTORPOSE.CPP */

/* Builds and packs the animated part matrices of an actor, then updates the
 * frame timing totals. */

/* Pose records whose fields are all in use, in the shared pose header layout. */
typedef struct Shared_PoseJointRef Shared_PoseJointRef;
struct Shared_PoseJointRef {
    s16 pos;
    s16 rot;
};

typedef struct Shared_PoseDefaultFrame Shared_PoseDefaultFrame;
struct Shared_PoseDefaultFrame {
    CVector3 pos;
    s16 rot[4];
};

typedef struct Shared_PoseTrack Shared_PoseTrack;
struct Shared_PoseTrack {
    Shared_PoseJointRef *joints;
    Shared_PoseDefaultFrame *frames;
    void *posTable;
    void *rotTable;
    s32 rotFrame0;
    s32 rotFrame1;
    s32 posFrame0;
    s32 posFrame1;
    f32 blend;
};

typedef struct Shared_PoseFlags Shared_PoseFlags;
struct Shared_PoseFlags {
    s32 frame;
    s32 blend;
    s32 mode;
};
typedef struct Shared_FrameProfile Shared_FrameProfile;
struct Shared_FrameProfile {
    u64 start;
    u32 unknown08[2];
    s32 frame;
    s32 prevCount;
    s32 count;
    u32 reservedWord;
    f32 prev;
    f32 cur;
    f32 avg;
};

typedef f32 PoseMatrix[4][4];
typedef void (*PoseCallback)(PoseMatrix, Shared_PoseContext *);


static inline CVector3 randVec(void) {
    CVector3 v;

    v.x = Graphu64_NextRandom() % 100;
    v.y = Graphu64_NextRandom() % 100;
    v.z = Graphu64_NextRandom() % 100;
    return v;
}

static inline void twistPart(Shared_PosePart *part, PoseMatrix cur, s32 n, s32 i) {
    CVector3 turn;
    CVector3 axis;
    PoseMatrix rotm;
    PoseMatrix inv;
    f32 angle;

    if (i != 0) {
        turn.x = cur[3][0];
        turn.y = cur[3][1];
        turn.z = cur[3][2];
        axis = part->twistAxis;
        angle = g_boneTwistImpulseCurve[25 - part->twistStep] * 0.5f;
        angle *= 0.3f;
        angle *= (n == 5 ? -2.0f : (f32)n);
        CopyMatrix(inv, cur);
        Graphu64_ScaleVector(&turn, &turn, -1.0f);
        TranslateMatrix(inv, turn.x, turn.y, turn.z);
        Graphu64_BuildAxisAngleMatrix(rotm, angle, axis.x, axis.y, axis.z);
        Graphu64_MultiplyAffineMatrices(cur, inv, rotm);
        Graphu64_ScaleVector(&turn, &turn, -1.0f);
        TranslateMatrix(cur, turn.x, turn.y, turn.z);
        if (part->twistJoints[0] == i) {
            part->twistStep--;
        }
    }
}

static inline void trackPos(Shared_PoseTrack *t, s32 i, CVector3 *out) {
    if (t->joints[i].pos == -1) {
        *out = t->frames[i].pos;
    } else {
        f32 *data = SetN64_GetPackSection(t->posTable, t->joints[i].pos);
        f32 *a = &data[t->posFrame0];
        f32 *b = &data[t->posFrame1];

        out->x = a[0] + t->blend * (b[0] - a[0]);
        out->y = a[1] + t->blend * (b[1] - a[1]);
        out->z = a[2] + t->blend * (b[2] - a[2]);
    }
}

static inline void trackRot(Shared_PoseTrack *t, s32 i, CQuatern *out, s32 slerp) {
    Shared_PoseDefaultFrame *frame;
    f32 z;
    if (slerp) {
        if (t->joints[i].rot == -1) {
            frame = t->frames;
            frame += i;
            out->x = frame->rot[0] * (1.0f / 32767.0f);
            out->y = frame->rot[1] * (1.0f / 32767.0f);
            z = frame->rot[2] * (1.0f / 32767.0f);
            goto default_frame;
        } else {
            f32 *data = SetN64_GetPackSection(t->rotTable, t->joints[i].rot);

            Graphu64_InterpolateQuaternionArc(out, t->blend, (CQuatern *)&data[t->rotFrame0], (CQuatern *)&data[t->rotFrame1]);
        }
    } else if (t->joints[i].rot == -1) {
        frame = t->frames;
        frame += i;

        out->x = frame->rot[0] * (1.0f / 32767.0f);
        out->y = frame->rot[1] * (1.0f / 32767.0f);
        z = frame->rot[2] * (1.0f / 32767.0f);
        default_frame:
        out->z = z;
        out->w = frame->rot[3] * (1.0f / 32767.0f);
    } else {
        f32 *data = SetN64_GetPackSection(t->rotTable, t->joints[i].rot);
        f32 *a = &data[t->rotFrame0];
        f32 *b = &data[t->rotFrame1];

        out->x = a[0] + t->blend * (b[0] - a[0]);
        out->y = a[1] + t->blend * (b[1] - a[1]);
        out->z = a[2] + t->blend * (b[2] - a[2]);
        out->w = a[3] + t->blend * (b[3] - a[3]);
    }
}

static inline void quatToMtx(PoseMatrix m, CQuatern *q, CVector3 *t) {
    f32 xx = q->x * q->x;
    f32 yy = q->y * q->y;
    f32 zz = q->z * q->z;
    f32 ww = q->w * q->w;
    f32 xy = 2.0f * q->x * q->y;
    f32 wz = 2.0f * q->w * q->z;
    f32 xz = 2.0f * q->x * q->z;
    f32 wy = 2.0f * q->w * q->y;
    f32 yz = 2.0f * q->y * q->z;
    f32 wx = 2.0f * q->w * q->x;

    m[0][0] = ww + xx - yy - zz;
    m[0][1] = xy + wz;
    m[0][2] = xz - wy;
    m[0][3] = 0.0f;
    m[1][0] = xy - wz;
    m[1][1] = ww - xx + yy - zz;
    m[1][2] = yz + wx;
    m[1][3] = 0.0f;
    m[2][0] = xz + wy;
    m[2][1] = yz - wx;
    m[2][2] = ww - xx - yy + zz;
    m[2][3] = 0.0f;
    m[3][0] = t->x;
    m[3][1] = t->y;
    m[3][2] = t->z;
    m[3][3] = 1.0f;
}

static inline void packMtx(u32 *out, PoseMatrix m) {
    u32 *hi = out;
    u32 *lo = out + 8;
    u32 e1;
    u32 e2;

    e1 = (u32)m[0][0];
    e2 = (u32)m[0][1];
    *hi++ = (e1 & 0xFFFF0000) | (e2 >> 16);
    *lo++ = (e1 << 16) | (e2 & 0xFFFF);
    e1 = (u32)m[0][2];
    e2 = 0;
    *hi++ = (e1 & 0xFFFF0000) | (e2 >> 16);
    *lo++ = (e1 << 16) | (e2 & 0xFFFF);
    e1 = (u32)m[1][0];
    e2 = (u32)m[1][1];
    *hi++ = (e1 & 0xFFFF0000) | (e2 >> 16);
    *lo++ = (e1 << 16) | (e2 & 0xFFFF);
    e1 = (u32)m[1][2];
    e2 = 0;
    *hi++ = (e1 & 0xFFFF0000) | (e2 >> 16);
    *lo++ = (e1 << 16) | (e2 & 0xFFFF);
    e1 = (u32)m[2][0];
    e2 = (u32)m[2][1];
    *hi++ = (e1 & 0xFFFF0000) | (e2 >> 16);
    *lo++ = (e1 << 16) | (e2 & 0xFFFF);
    e1 = (u32)m[2][2];
    e2 = 0;
    *hi++ = (e1 & 0xFFFF0000) | (e2 >> 16);
    *lo++ = (e1 << 16) | (e2 & 0xFFFF);
    e1 = (u32)m[3][0];
    e2 = (u32)m[3][1];
    *hi++ = (e1 & 0xFFFF0000) | (e2 >> 16);
    *lo++ = (e1 << 16) | (e2 & 0xFFFF);
    e1 = (u32)m[3][2];
    e2 = 65536;
    *hi++ = (e1 & 0xFFFF0000) | (e2 >> 16);
    *lo++ = (e1 << 16) | (e2 & 0xFFFF);

}

s32 Gobjinst_BuildActorPose(Shared_PoseActor *actor, void *modelPack, s32 model) {
    PoseMatrix mtx[129];
    CVector3 pos;
    Shared_PoseContext ctx;
    Shared_PoseTrack tracks[2];
    Shared_PoseFlags f;
    PoseMatrix m;
    CVector3 trans;
    CVector3 posA;
    CVector3 posB;
    CQuatern rot;
    CQuatern rotA;
    CQuatern rotB;
    CVector3 scale;
    Shared_PoseWorld *world;
    s32 *mem;
    Shared_AnimState *animA;
    Shared_AnimState *animB;
    s32 id0;
    s32 id1;
    s32 id2;
    s32 id3;
    s32 id4;
    s32 count;
    s32 kind;
    PoseMatrix *parent;
    u32 *out;
    s32 scaled;
    s32 ret;
    s32 skip;
    s32 isRoot;
    s32 isKind9;
    s32 i;
    PoseMatrix *cur;
    s32 flags;
    u32 dt;

    world = 0;
    ctx.parts = SetN64_GetPackSection(modelPack, 5);
    count = ctx.parts->count;
    actor->handle = Map_ReserveEntries(&g_actorMatrixPool, count);
    if (actor->handle == 0) {
        return 0;
    }
    ret = 0;
    isRoot = actor->flags & 1;
    isKind9 = actor->model->kind == 9;
    mem = Cache_RequestResource(0, actor->animationResourceId, actor->animationResourceId, ((actor->animationResourceUnits * 4) + 15) & ~7, 4, 0, 0, &g_actorRotationBlendAndResourceTuning + 4, 0);
    skip = ret;
    if (mem != 0) {
        animA = &actor->animA;
        animB = &actor->animB;
        Gastate_SwitchRequestedAnimation(animA, *mem, actor->animationResourceId, 0, 0, 0);
        if (Gastate_IsAnimationResourceRetained(animA)) {
            if (actor->flags & 0x400) {
                Gastate_SwitchRequestedAnimation(animB, *mem, actor->animationResourceId, 0, 0, 0);
                f.blend = Gastate_IsAnimationResourceRetained(animB);
            } else {
                f.blend = 0;
            }
            ctx.actor = actor;
            ctx.handle = actor->handle;
            ctx.mtx = &mtx[1];
            ctx.model = model;
            ctx.modelPack = modelPack;
            ctx.animA = animA;
            ctx.animB = animB;
            f.frame = (!isRoot || isKind9) && !skip;
            Gastate_PrepareAnimationFrames(&actor->animA, &tracks[0], f.frame);
            Gastate_PrepareAnimationFrames(&actor->animB, &tracks[1]);
            kind = actor->model->kind;
            scaled = 0;
            scale.x = 1.0f;
            scale.y = 1.0f;
            scale.z = 1.0f;
            flags = actor->flags;
            if (flags & 0x300000) {
                if (flags & 0x100000) {
                    world = actor->world;
                    if (world->scale != 1.0f) {
                        scaled = 1;
                        if (world->scale > 1.0f) {
                            scale.x = world->scale;
                            scale.y = world->scale * 1.5f;
                        } else {
                            scale.x = world->scale;
                            scale.y = world->scale;
                            scale.z = world->scale;
                        }
                    }
                    f.frame = 1;
                } else {
                    f.frame = 0;
                }
                if (Cinema_IsSequenceInWindow()) {
                    f.frame = 0;
                }
            }
            if (!Cinema_IsSequenceInWindow() && ((animA->activeFlag == 0 && animB->activeFlag == 0) || kind == 1)) {
                f.mode = 0;
            } else {
                f.mode = 1;
            }
            if (!(actor->flags & 0x200000) && (kind == 1 || kind == 11)) {
                if (g_gameSettings.flags & 0x100) {
                    id0 = 195;
                    id1 = 199;
                    id2 = 194;
                    id3 = 198;
                } else {
                    id0 = -1;
                    id1 = -1;
                    id2 = -1;
                    id3 = -1;
                }
                id4 = -1;
                if (g_gameSettings.flags & 0x20) {
                    id4 = 1;
                }
                if (g_gameSettings.flags & 0x80) {
                    scaled = 1;
                    Graphu64_ScaleVector(&scale, &scale, 0.5f);
                }
            } else {
                id0 = -1;
                id1 = -1;
                id2 = -1;
                id3 = -1;
                id4 = -1;
            }
            mtx[0][0][0] = actor->mtx.right.x * 65536.0f;
            mtx[0][1][0] = actor->mtx.up.x * 65536.0f;
            mtx[0][2][0] = actor->mtx.forward.x * 65536.0f;
            mtx[0][3][0] = actor->mtx.m30 * 65536.0f;
            mtx[0][0][1] = actor->mtx.right.y * 65536.0f;
            mtx[0][1][1] = actor->mtx.up.y * 65536.0f;
            mtx[0][2][1] = actor->mtx.forward.y * 65536.0f;
            mtx[0][3][1] = actor->mtx.m31 * 65536.0f;
            mtx[0][0][2] = actor->mtx.right.z * 65536.0f;
            mtx[0][1][2] = actor->mtx.up.z * 65536.0f;
            mtx[0][2][2] = actor->mtx.forward.z * 65536.0f;
            mtx[0][3][2] = actor->mtx.m32 * 65536.0f;
            mtx[0][0][3] = mtx[0][1][3] = mtx[0][2][3] = 0.0f;
            mtx[0][3][3] = 65536.0f;
            out = (u32 *)actor->handle;
            i = 0;
            g_actorPoseTiming.start = osGetCount();
            cur = &mtx[1];
            for (; i < count; cur++, out += 16, i++) {
                Shared_PosePartEntry *entry;
                s32 partFlags;

                ctx.index = i;
                entry = (Shared_PosePartEntry *)&ctx.parts->data[i * ctx.parts->stride];
                ctx.part = entry;
                parent = &mtx[entry->u.b.parent + 1];
                partFlags = entry->u.b.flags;
                trackPos(&tracks[0], i, &posA);
                trackRot(&tracks[0], i, &rotA, f.mode);
                if (f.blend) {
                    trackPos(&tracks[1], i, &posB);
                    trackRot(&tracks[1], i, &rotB, f.mode);
                    {
                        f32 blendWeight = actor->blendFactor;

                        trans.x = posB.x + blendWeight * (posA.x - posB.x);
                        trans.y = posB.y + blendWeight * (posA.y - posB.y);
                        trans.z = posB.z + blendWeight * (posA.z - posB.z);
                    }
                    Graphu64_InterpolateQuaternionArc(&rot, actor->blendFactor, &rotB, &rotA);
                } else {
                    trans = posA;
                    rot = rotA;
                }
                if (f.frame) {
                    f.frame = 0;
                    trans.x = trans.y = 0.0f;
                }
                quatToMtx(m, &rot, &trans);
                if (actor->callback != 0) {
                    ((PoseCallback)actor->callback)(m, &ctx);
                }
                Graphu64_MultiplyAffineMatrices(*cur, m, *parent);
                if (actor->part.twistStep) {
                    s32 twistWeight = 0;
                    if (actor->part.twistJoints[0] == i) {
                        twistWeight = 4;
                    }
                    if (actor->part.twistJoints[1] == i) {
                        twistWeight = 3;
                    }
                    if (actor->part.twistJoints[2] == i) {
                        twistWeight = 2;
                    }
                    if (actor->part.twistJoints[3] == i) {
                        twistWeight = 1;
                    }
                    if (twistWeight != 0 && actor->callback != 0) {
                        twistPart(&actor->part, *cur, twistWeight, i);
                    }
                } else if (i != 0 && world != 0 && world->impactTwistPending != 0 && ctx.part != 0 &&
                    ctx.part->u.f.kind == 1 && ctx.part->u.f.sway == 0) {
                    if ((actor->flags & 0x1000000) && actor->boneMatrixData != 0) {
                        PoseMatrix bone;
                        CVector3 r = randVec();

                        Graphu64_ConvertMatrixToFloat(bone, actor->boneMatrixData + i * 64);
                        Gobjinst_ApplyImpactBoneTwist(actor, &actor->part, bone, actor->pos, r, i);
                    }
                    world->impactTwistPending = 0;
                }
                if (actor->flags & 0x800000) {
                    Gobjinst_ApplyTimedMatrixWobble(actor, partFlags, *cur);
                }
                if (partFlags == id0) {
                    id0 = -1;
                    ScaleMatrixLocal(*cur, 2.0f, 2.0f, 2.0f);
                } else if (partFlags == id1) {
                    id1 = -1;
                    ScaleMatrixLocal(*cur, 2.0f, 2.0f, 2.0f);
                } else if (partFlags == id2) {
                    id2 = -1;
                    ScaleMatrixLocal(*cur, 2.0f, 2.0f, 2.0f);
                } else if (partFlags == id3) {
                    id3 = -1;
                    ScaleMatrixLocal(*cur, 2.0f, 2.0f, 2.0f);
                } else if (partFlags == id4) {
                    id4 = -1;
                    ScaleMatrixLocal(*cur, 3.0f, 3.0f, 3.0f);
                }
                if (scaled) {
                    CopyMatrix(m, *cur);
                    ScaleMatrixLocal(m, scale.x, scale.y, scale.z);
                    packMtx(out, m);
                } else {
                    packMtx(out, *cur);
                }
            }
            dt = osGetCount() - g_actorPoseTiming.start;
            if (g_gameFrameCounter != g_actorPoseTiming.frame) {
                f32 last = g_actorPoseTiming.cur;
                s32 previousCount = g_actorPoseTiming.count;

                g_actorPoseTiming.frame = g_gameFrameCounter;
                g_actorPoseTiming.cur = 0.0f;
                g_actorPoseTiming.count = 0;
                g_actorPoseTiming.prev = last;
                g_actorPoseTiming.prevCount = previousCount;
                g_actorPoseTiming.avg = g_actorPoseTiming.avg * 0.97f + last * 0.03f;
            }
            g_actorPoseTiming.cur += (f32)(((u64)dt * 64) / 3000);
            g_actorPoseTiming.count++;
            if (f.blend) {
                Gastate_ReleaseAnimationResource(animB);
            }
            Gastate_ReleaseAnimationResource(animA);
            switch (kind) {
            case 4:
                actor->verticalOffset = actor->model->verticalOffset;
                break;
            case 1:
            case 11: {
                    f32 h = Gobjinst_GetActorHeight(actor);

                    actor->verticalOffset = mtx[1][3][1] * (1.0f / 65536.0f) - actor->pos.y - h * 0.5f;
                    if (actor->verticalOffset < 0.0f) {
                        actor->verticalOffset = 0.0f;
                    }
                    if ((actor->flags & 0x20000000) && actor->surface != 0 && (actor->surface->flags & 0x40)) {
                        f32 ground = Graphu64_GetTrianglePlaneHeight(actor->surface, actor->pos.x, actor->pos.z);
                        f32 heightAboveGround = actor->pos.y + actor->verticalOffset + h;

                        heightAboveGround -= ground;

                        if (heightAboveGround > 0.0f) {
                            mtx[1][3][1] -= heightAboveGround * 65536.0f;
                            actor->verticalOffset -= heightAboveGround;
                        }
                    }
                    break;
                }
            default:
                actor->verticalOffset = 0.0f;
                break;
            }
            if (actor->attachmentEffectsFlag != 0) {
                s32 bit = 1 << actor->partBitIndex;

                if (actor->part.effectPartMask & bit) {
                    Shared_PosePartTable *table = SetN64_GetPackSection(modelPack, 3);
                    s32 attachmentCount = table->count;

                    if (attachmentCount != 0) {
                        u8 *data = table->data;

                        Ghot_DispatchAttachmentEffects(data, attachmentCount, &mtx[1], actor, SetN64_GetPackSection(modelPack, 5));
                    }
                }
            }
            if (actor->effectReferenceCount) {
                Fx_AddActorRibbonSamples(&g_gameSession.hud.actors, actor, &mtx[1]);
            }
            if (!(actor->flags & 8)) {
                pos = actor->pos;
                pos.y += actor->verticalOffset;
                pos.y += Gobjinst_GetActorHeight(actor) * 0.5f;
                Scene_SampleWorldLighting(&g_world, &pos, actor->sampledLighting[g_lightingBufferIndex]);
            }
            ret = 1;
            actor->flags |= 0x200;
        }
        Cache_UnlockResource(0, mem);
    }
    if (!ret) {
        actor->handle = 0;
    }
    return ret;
}

typedef struct SceneModelRef {
    u8 pad0[0x1C];
    u32 viewMask;
} SceneModelRef;
typedef struct SceneObject SceneObject;
typedef struct DrawContext {
    s32 visible;
    s32 hasSecond;
    struct GameplayCamera *camera;
    void *first;
    void *second;
    f32 *offset;
    s32 pad;
} DrawContext;
struct SceneObject {
    u8 pad0;
    s8 firstKey;
    s8 secondKey;
    u8 pad3[0x11];
    SceneModelRef *model;
    u8 pad18[0x5C];
    f32 transform[16];
    u8 padB4[0xC];
    Gfx *cached;
    s32 resource;
    u8 padC8[8];
    s32 resourceFlags;
    u8 padD4[0x14];
    Box bounds;
    u32 flags;
    u8 pad104[0x6C];
    s32 behaviorFlags;
    u8 pad174[0x108];
    void (*draw)(SceneObject *, void *, DrawContext *);
    u8 pad280[0xC];
    void (*update)(SceneObject *, void *);
};

/* Draws one scene object: loads its model, culls its bounding box against the camera's clip box and plane test,
 * then records the object's draw callback into a display list cached on the object (a branch placeholder is
 * patched at the end) or replays the cached list. */
void Gobjinst_DrawVisibleCachedActor(SceneObject *object, struct GameplayCamera *camera) {
    void **mem;
    void *model;
    void *first;
    void *second;
    s32 visible;
    s32 second_needed;
    f32 offset[3];
    s32 spare[6];
    DrawContext context;

    if (!(object->flags & 0x40000) || object->draw == 0) {
        return;
    }
    if (!(object->flags & 0x2000)) {
        object->flags &= ~0x200;
        return;
    }
    mem = Cache_RequestResource(0, object->resource, object->resource, object->resourceFlags, 0, 0, 0, s_actorModelVariantResourceTag, 1);
    if (mem == 0) {
        return;
    }
    model = SetN64_GetPackSection(*mem, 0);
    if (g_gameSession.clockPaused != 0) {
        object->update(object, &object->behaviorFlags);
        Graphu64_TransformBoundingBox(object->transform, (s32)model, &object->bounds);
    }
    visible = 1;
    if (!(object->flags & 0x200000)) {
        second_needed = visible = 0;
        if (object->model == 0 || (camera->floorSurface & object->model->viewMask)) {
            if (camera->clipBounds[1].x > object->bounds.min.x && camera->clipBounds[0].x < object->bounds.max.x &&
                camera->clipBounds[1].z > object->bounds.min.z && camera->clipBounds[0].z < object->bounds.max.z &&
                camera->clipBounds[1].y > object->bounds.min.y && camera->clipBounds[0].y < object->bounds.max.y &&
                Visdata_TestBoxAgainstFrustum((char *)&((GameplayCamera *)camera)->clipPlanes, &object->bounds) != 0) {
                visible = 1;
                if (object->model != 0) {
                    goto sync;
                }
            }
        }
    } else {
        sync:
        second_needed = visible;
    }
    if (visible == 0 && second_needed == 0) {
        Cache_UnlockResource(0, mem);
        return;
    }
    Geometry_InvalidateMaterialKeys();
    TextLoad_ResetTextureCache();
    if (object->cached != 0) {
        gSPDisplayList(g_displayListCursor++, (unsigned int)object->cached);
        Cache_UnlockResource(0, mem);
        return;
    }
    first = Gobjinst_RequestAnimatedModelVariant(object, object->firstKey);
    if (first == 0) {
        Cache_UnlockResource(0, mem);
        return;
    }
    if ((object->flags & 0x200) == 0 && Gobjinst_BuildActorPose(object, *(void **)first, (s32)model) == 0) {
        Cache_UnlockResource(0, first);
        Cache_UnlockResource(0, mem);
        return;
    }
    offset[0] = offset[1] = offset[2] = 0.0f;
    if (second_needed != 0) {
        second = Gobjinst_RequestAnimatedModelVariant(object, object->secondKey);
        second_needed = second != 0;
    } else {
        second = 0;
    }
    context.hasSecond = second_needed;
    context.visible = visible;
    context.camera = camera;
    context.first = first;
    context.second = second;
    context.offset = offset;
    context.pad = 0;
    object->cached = g_displayListCursor;
    gSPBranchList(g_displayListCursor++, 0);
    object->draw(object, &object->behaviorFlags, &context);
    gSPEndDisplayList(g_displayListCursor++);
    gSPBranchList(object->cached++, (unsigned int)g_displayListCursor);
    gSPDisplayList(g_displayListCursor++, (unsigned int)object->cached);
    Cache_UnlockResource(0, first);
    if (second != 0) {
        Cache_UnlockResource(0, second);
    }
    Cache_UnlockResource(0, mem);
}

/* Keep this source unit's macros local to its body. */

/* PLAYER_DRAWTINTEDPLAYER_DATA.CPP */

/* Refreshes the actor's animation from the lookup through GameObject_DrawActorShadow and Geometry_DrawModelResource and, when the lookup's third node carries flag 0x8000, spawns a 0x94 effect at the actor scaled by its size, then clears g_menuModelFillEnabled. */

extern char g_actorParticleEffectSystem[];

extern void GameObject_DrawActorShadow(char *obj, s32 shadowContext, char *info);

extern s32 Geometry_GetViewEffect(void);

struct EffectSystem; extern int Particle_GetLastSpawnedEffect(struct EffectSystem *effectSystem);



static inline void Gobjinst_SpawnViewEffectForModel(LevelActor *actor, Lookup *lookup) {
    CVector3 position;
    SpawnedEffectMotionView *effect;
    f32 scale;
    s32 *node;

    if (Geometry_GetViewEffect() != 0) {
        node = SetN64_GetPackSection(*lookup->value, 2);
        if ((*node != 0) &&
            (*((s32 *)SetN64_GetPackSection(SetN64_GetPackSection(node, 0), 0)) & 0x8000)) {
            position = actor->position0;
            position.y += Gobjinst_GetActorHeight(actor) * g_actorModelViewEffectConstants[1];
            Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], actor, actor, 0, 0, 148,
                          actor->position1, actor->rotation, position, 0, -1, 0);
            effect = Particle_GetLastSpawnedEffect(&g_actorParticleEffectSystem[0]);
            if (effect != 0) {
                scale = g_actorPartsViewEffectTuning;
                effect->radius = Gobjinst_GetActorRadius(actor) * scale;
                effect->height = Gobjinst_GetActorHeight(actor) * scale;
            }
        }
    }
}

static inline void spawn(LevelActor *actor) {
    CVector3 position;

    position = actor->position0;
    position.y += Gobjinst_GetActorHeight(actor) * *(&g_actorPartsViewEffectTuning + 1);
    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], actor, actor, 0, 0, 148,
                  actor->position1, actor->rotation, position, 0, -1, 0);
}

void Gobjinst_DrawActorModelWithViewEffects(LevelActor *actor, void *context, Lookup *lookup) {
    s32 one;

    if (lookup->drawShadow != 0) {
        GameObject_DrawActorShadow(actor, context, lookup);
    }
    if (lookup->drawModel != 0) {
        one = 1;
        Geometry_DrawModelResource(lookup->value, actor->animationMatrices, one,
                      &actor->lighting[g_lightingBufferIndex],
                      0, actor->renderPass);
        Gobjinst_SpawnViewEffectForModel(actor, lookup);
    }
    g_menuModelFillEnabled = 0;
}

void Gobjinst_DrawActorPartsWithViewEffects(LevelActor *actor, PlayerControllerView *player, s32 animationContext, Draw *params) {
    SpawnedEffectMotionView *effect;
    f32 scale;
    s32 *node;

    if (params->updateAnimation != 0) {
        GameObject_DrawActorShadow(actor, animationContext, params);
    }
    if (params->drawModel != 0) {
        Geometry_DrawActorModelParts(params->model, player, actor->animationMatrices, 1, &actor->lighting[g_lightingBufferIndex], 0, actor->renderPass);
        if (Geometry_GetViewEffect() != 0) {
            node = SetN64_GetPackSection(*params->model, 2);
            if ((*node != 0) &&
                (*((s32 *)SetN64_GetPackSection(SetN64_GetPackSection(node, 0), 0)) & 0x8000)) {
                spawn(actor);
                effect = Particle_GetLastSpawnedEffect(&g_actorParticleEffectSystem[0]);
                if (effect != 0) {
                    scale = g_actorBlendedViewEffectTuning;
                    effect->radius = Gobjinst_GetActorRadius(actor) * scale;
                    effect->height = Gobjinst_GetActorHeight(actor) * scale;
                }
            }
        }
    }
    g_menuModelFillEnabled = 0;
}

/* Optionally runs GameObject_DrawActorShadow, then starts the actor's current block through Geometry_DrawBlendParts and, when the resulting animation node is flagged, spawns an effect at the actor raised by its height and scales it to the actor's size, always clearing g_menuModelFillEnabled at the end. */

static inline void spawn_blend_effect(TintedPlayerRenderActor *actor) {
    CVector3 position;

    position = actor->position0;
    position.y += Gobjinst_GetActorHeight(actor) * *(&g_actorBlendedViewEffectTuning + 1);
    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], actor, actor, 0, 0, 148,
                  actor->position1, actor->rotation, position, 0, -1, 0);
}

void Gobjinst_DrawBlendPartsWithViewEffects(TintedPlayerRenderActor *actor, s32 drawView, s32 animationContext, Lookup *params) {
    SpawnedEffectMotionView *effect;
    f32 scale;
    s32 *node;

    if (params->drawShadow != 0) {
        GameObject_DrawActorShadow(actor, animationContext, params);
    }
    if (params->drawModel != 0) {
        Geometry_DrawBlendParts(params->value, drawView, actor->poseMatrices, 1, &actor->blocks[g_lightingBufferIndex], 0, actor->renderVariant);
        if (Geometry_GetViewEffect() != 0) {
            node = SetN64_GetPackSection(*params->value, 2);
            if ((*node != 0) &&
                (*((s32 *)SetN64_GetPackSection(SetN64_GetPackSection(node, 0), 0)) & 0x8000)) {
                spawn_blend_effect(actor);
                effect = Particle_GetLastSpawnedEffect(&g_actorParticleEffectSystem[0]);
                if (effect != 0) {
                    scale = g_actorBlendedViewEffectScale;
                    effect->radius = Gobjinst_GetActorRadius(actor) * scale;
                    effect->height = Gobjinst_GetActorHeight(actor) * scale;
                }
            }
        }
    }
    g_menuModelFillEnabled = 0;
}

/* GOBJINST_DRAWTEAMMASKEDMODEL.CPP */
struct CacheResourceNode;


static inline void spawn_gobjinst_drawteammaskedmodel(LevelActor *actor) {
    CVector3 position;

    position = actor->position0;
    position.y += Gobjinst_GetActorHeight(actor) * g_actorModelViewEffectHeightScale;
    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], actor, actor, 0, 0, 148,
                  actor->position1, actor->rotation, position, 0, -1, 0);
}

void Gobjinst_DrawTeamMaskedModel(LevelActor *actor, s32 unusedShadowContext, Lookup *params) {
    SpawnedEffectMotionView *effect;
    f32 scale;
    s32 *node;
    s32 resource;
    LitModelResourceHeader *header;
    char *data;

    actor->mask = 1 << actor->team;
    if (params->drawShadow != 0) {
        GameObject_DrawActorShadow(actor, unusedShadowContext, params);
    }
    if (params->drawModel == 0) {
        return;
    }
    resource = Cache_RequestPairedResource(0, actor->flags2E4 | g_litGeometryResourceKeyFlags, params->value, 0, 0,
        actor, &g_GameObject_BuildLitActorResourceAddress, &s_actorLitModelResourceTag, 1);
    if (resource == 0) {
        return;
    }
    Cache_MarkResourceInUse(0, resource);
    header = *(LitModelResourceHeader **)resource;
    if (header->layout == 1) {
        char *object = LitModel_Object(header);

        Link_AnimateVertexColors(object, LitModel_VertexColors(header));
        data = object;
    } else {
        data = (char *)&header->vertexColorOffset;
    }
    Geometry_DrawModelResource(params->value, actor->animationMatrices, 1, 0, data, actor->renderPass);
    if (Geometry_GetViewEffect() != 0) {
        node = SetN64_GetPackSection(*params->value, 2);
        if ((*node != 0) &&
            (*((s32 *)SetN64_GetPackSection(SetN64_GetPackSection(node, 0), 0)) & 0x8000)) {
            spawn_gobjinst_drawteammaskedmodel(actor);
            effect = Particle_GetLastSpawnedEffect(&g_actorParticleEffectSystem[0]);
            if (effect != 0) {
                scale = g_actorModelViewEffectScale;
                effect->radius = Gobjinst_GetActorRadius(actor) * scale;
                effect->height = Gobjinst_GetActorHeight(actor) * scale;
            }
        }
    }
    Cache_UnlockResource(0, resource);
}

/* GOBJINST.CPP */

/* Draws an object's cast shadow: objects without shadow flag 0x10000000 get the blob shadow of
 * GameObject_DrawBlobShadow; otherwise, once per frame the shadow model from Map_ReserveEntries is built for an object above
 * the ground: the light of the current view (direction from its signed bytes, strength from its colour)
 * is sampled at the object through Gdynlight_AccumulateLightDirections, the shadow alpha is 128 plus 56 per unit of light (faded
 * by g_menuModelFillColor[3] during a fade), the light direction is kept at least 0.15 from horizontal, and the shadow
 * is projected along it onto a plane just below the object (0.9 of its height up to 512), grown by 0.003
 * per unit of height, turned by the object's orientation and placed on the ground; the shadow is then
 * submitted through Gobjinst_DrawModelWithProjection. */

void GameObject_DrawActorShadow(char *obj, s32 shadowContext, char *info) {
    CVector3 dir;
    f32 projection[16];
    f32 turn[16];
    f32 strength;
    f32 ground;
    f32 height;
    f32 plane;
    f32 scale;
    f32 diff;
    char *light;
    s32 alpha;
    if (((struct LevelActor *)(obj))->model == 0 || InstHdr_CanActorCastShadow(obj) == 0 || (((struct LevelActor *)(obj))->flags & 0x200000)) {
        return;
    }
    if (((struct LevelActor *)(obj))->flags & 0x10000000) {
        if (((struct LevelActor *)(obj))->shadow == 0) {
            ground = InstHdr_GetActorGroundHeight((struct Shared_CollisionActor *)obj, 0);
            if (((struct LevelActor *)(obj))->position0.y < ground) {
                return;
            }
            diff = ((struct LevelActor *)(obj))->position0.y - ground;
            height = (512.0f < diff) ? 512.0f : diff;
            if ((((struct LevelActor *)(obj))->shadow = Map_ReserveEntries(&g_actorMatrixPool, 1)) == 0) {
                return;
            }
            light = (char *)&((LevelActor *)obj)->lighting[g_lightingBufferIndex];
            dir.x = ((struct Shared_ParticleLighting *)(light))->direction[0] * 0.007874016f;
            dir.y = ((struct Shared_ParticleLighting *)(light))->direction[1] * 0.007874016f;
            dir.z = ((struct Shared_ParticleLighting *)(light))->direction[2] * 0.007874016f;
            strength = Gu_Sqrtf((f32)((struct Shared_ParticleLighting *)(light))->diffuse[0] * (f32)((struct Shared_ParticleLighting *)(light))->diffuse[0] +
                                         (f32)((struct Shared_ParticleLighting *)(light))->diffuse[1] * (f32)((struct Shared_ParticleLighting *)(light))->diffuse[1] +
                                         (f32)((struct Shared_ParticleLighting *)(light))->diffuse[1] * (f32)((struct Shared_ParticleLighting *)(light))->diffuse[1]) *
                       -0.00090497744f;
            Gdynlight_AccumulateLightDirections(&g_dynamicLightPool, ((LevelActor *)obj)->position0, &dir, &strength);
            if (strength < -1.0f) {
                strength = -1.0f;
            }
            alpha = strength * 56.0f + 128.0f;
            if (g_menuModelFillEnabled == 1) {
                alpha = alpha * g_menuModelFillColor[3] * 0.003921569f;
            }
            ((struct LevelActor *)(obj))->shadowAlpha = alpha;
            dir.y = 1.0f;
            Graphu64_NormalizeVec3(&dir);
            if (RW_ABS(dir.y) < 0.15f) {
                if (dir.y >= 0.0f) {
                    dir.y = 0.15f;
                } else {
                    dir.y = -0.15f;
                }
                Graphu64_NormalizeVec3(&dir);
            }
            plane = ground + height * 0.9f;
            Graphu64_BuildPlaneProjectionMatrix(projection, &dir, plane);
            TranslateMatrix(projection, -((struct LevelActor *)(obj))->position0.x, -plane, -((struct LevelActor *)(obj))->position0.z);
            scale = height * 0.003f + 1.0f;
            Graphu64_ScaleMatrixWorld(projection, scale, scale, scale);
            MatrixFromQuaternion((f32 *)(&((LevelActor *)obj)->rotation), turn);
            Graphu64_MultiplyAffineMatrices(((struct LevelActor *)(obj))->shadow, projection, turn);
            TranslateMatrix(((struct LevelActor *)(obj))->shadow, ((struct LevelActor *)(obj))->position0.x, ground, ((struct LevelActor *)(obj))->position0.z);
            if (((struct LevelActor *)(obj))->shadow == 0) {
                return;
            }
        }
        Gobjinst_DrawModelWithProjection(obj, info, ((struct LevelActor *)(obj))->shadow, ((struct LevelActor *)(obj))->shadowAlpha);
    } else {
        GameObject_DrawBlobShadow((struct LevelActor *)obj, ((struct ActorRenderSettings *)(info))->shadowOffset, 0);
    }
}


void GameObject_DrawBlobShadow(struct LevelActor *actor, CVector3 *offset, s32 raised) {
    f32 matrix[16];
    CVector3 position;
    f32 scale;
    f32 groundHeight;
    f32 height;
    f32 opacity;
    f32 shrink;
    f32 limitedRadius;
    f32 radius;
    f32 lift;
    FixedPointMatrix *packed;
    u8 targetAlpha;

    packed = Map_ReserveEntries(&g_actorMatrixPool, 1);
    if (packed != 0) {
        groundHeight = InstHdr_GetShadowGroundHeight(actor, 0);
        height = (actor->position0.y + actor->eyeHeight) - groundHeight;
        radius = InstHdr_GetActorShadowRadius((Actor_u1 *)actor);
        shrink = height * 0.1f;
        limitedRadius = radius - shrink;
        if (!(limitedRadius <= radius)) {
            limitedRadius = radius;
        }
        if (limitedRadius < 0.0f) {
            radius = 0.0f;
            limitedRadius = radius;
        } else {
            limitedRadius = radius - shrink;
            if (!(limitedRadius <= radius)) {
                limitedRadius = radius;
            }
        }
        radius = limitedRadius;
        if (raised != 0) {
            radius *= 0.5f;
            lift = 15.36f;
        } else {
            radius *= 0.7f;
            lift = 0.0f;
        }
        scale = radius;
        position.x = actor->position0.x + offset->x;
        position.z = actor->position0.z + offset->z;
        position.y = groundHeight + lift + offset->y;
        Graphu64_LimitVectorLength((f32 *)&position, 20000.0f);
        MatrixFromQuaternion(&actor->rotation, matrix);
        ScaleMatrixLocal(matrix, scale, 1.0f, scale);
        TranslateMatrix((s8 *) matrix, position.x, position.y, position.z);
        Graphu64_ConvertMatrixToFixed(matrix, (FixedPointMatrix *) packed);
        opacity = 200.0f - (height * 1.2207031f);
        targetAlpha = 0xFF;
        if (!(255.0f < opacity)) {
            targetAlpha = 0;
            if (!(opacity < 0.0f)) {
                targetAlpha = 0xFF;
                if (!(255.0f < opacity)) {
                    targetAlpha = (u8)opacity;
                }
            }
        }
        actor->shadowAlpha = (u8)(actor->shadowAlpha +
            ((s32)targetAlpha - actor->shadowAlpha) * 0.5f);
        Geometry_DrawIntensityMask(packed, raised == 0, actor->shadowAlpha);
    }
}

/* GOBJINST_FINDNEARESTBONEBOUNDS.CPP */

/* Finds the hit box of an object nearest a point: with the object's bone matrices (its primary set, else the
 * alternate set) and its hit-box resource from Gobjinst_RequestAnimatedModelVariant, each box whose mask matches the object's collision mask has the average
 * of its eight corners carried through its bone matrix, and the box whose center lies nearest the point is
 * copied out, taking weight 1 for a controlled actor unless the global option g_gameSettings.local is set. The
 * resource is released afterwards; returns whether a box was found. */

s32 Gobjinst_FindNearestBoneBounds(char *obj, CVector3 point, Box70 *out) {
    CVector3 center;
    CVector3 diff;
    f32 matrix[16];
    s32 *resource;
    s32 count;
    struct ActorAnimationEventTable *table;
    Box70 *box;
    Box70 *best;
    char *bones;
    s32 i;
    s32 j;
    f32 dist;
    f32 bestDist;

    bones = ((struct BoneBoundsActorView *) obj)->poseMatrices;
    if (bones == 0) {
        bones = ((struct BoneBoundsActorView *) obj)->previousPoseMatrices;
        if (bones == 0) {
            return 0;
        }
    }
    resource = Gobjinst_RequestAnimatedModelVariant(obj, ((struct BoneBoundsActorView *) obj)->team);
    if (resource == 0) {
        return 0;
    }
    table = SetN64_GetPackSection(*resource, 5);
    count = table->entryCount;
    bestDist = 3.4028235e38f;
    best = 0;
    for (i = 0; i < count; i++) {
        box = (Box70 *)&table->records[i * table->entrySize];
        if (box->mask & ((struct BoneBoundsActorView *) obj)->boneMask) {
            center = box->corners[0];
            for (j = 1; j < 8; j++) {
                Graphu64_AddVec3(&center, &center, &box->corners[j]);
            }
            Graphu64_ScaleVector(&center, &center, 0.125f);
            Graphu64_ConvertMatrixToFloat(matrix, &((Matrix *)bones)[i]);
            Graphu64_TransformPoint(matrix, &center, &diff);
            Graphu64_SubtractVectors(&diff, &diff, &point);
            dist = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
            if (dist < bestDist) {
                best = box;
                bestDist = dist;
            }
        }
    }
    if (best != 0) {
        *out = *best;
        if ((((struct BoneBoundsActorView *) obj)->flags & 0x300000) && g_gameSettings.local == 0) {
            ((struct Shield *) ((char *) out))->factor = 1.0f;
        }
    }
    Cache_UnlockResource(0, resource);
    return best != 0;
}

void Gobjinst_DispatchActorTypeUpdate(char *actor)
{
    s32 type;
    s32 i;
    s32 count;
    s32 limit;
    char *object;
    TypeEntry *entry;

    type = ((struct LevelActor *)(actor))->definition->kind;
    if ((u32)type < 15) {
        goto valid_type;
    }
    zero_entry:
    entry = 0;
    goto selected;
    special_entry:
    entry = (TypeEntry *)g_actorDefinitionTable;
    goto selected;
    valid_type:
    if (type == 11) {
        count = g_playerCount;
        i = 0;
        if (count > 0) {
            limit = count;
            object = (char *)g_gamePlayerAndMenuState.entries;
            do {
                if (object == actor) {
                    goto zero_entry;
                }
                if ((char *)&((SharedPlayer *)object)->views1C.view2E8_27.weapon == actor) {
                    goto special_entry;
                }
                i++;
                object += sizeof(SharedPlayer);
            } while (i < limit);
        }
    }
    entry = g_actorTypeOperations[type];

    selected:
    if (entry != 0 && entry->callback != 0) {
        entry->callback(actor, &((LevelActor *)actor)->behaviorFlags);
    }
    if ((((struct LevelActor *)(actor))->flags & 0x08000000) != 0) {
        (((struct LevelActor *)(actor))->updateCount)++;
    }
}

void Gobjinst_InitializePlacedActor(void *actorStorage, LevelPlacedActorRecord *placement, s32 mode, s32 index) {
    void *resource0;
    s32 resource1;
    s32 lookup;
    s32 amountRaw;
    f32 fzero;
    f32 amount;
    CVector3 zero;

    resource0 = Scene_GetActorDefinition(&g_world, placement->resource22);
    if (placement->resource20 == 0xFFFF) {
        resource1 = 0;
    } else {
        resource1 = Scene_GetModelSectionTwoRecord(&g_world, placement->resource20);
    }
    amountRaw = placement->amount24;
    fzero = 0.0f;
    amount = amountRaw * g_actorOffsetTransformConstants[1];
    zero.x = zero.y = zero.z = fzero;
    lookup = Rumble_TestActorStateBit(&g_world, actorStorage);
    Gobjinst_InitializeActor(actorStorage, placement->actorKind, placement->actorVariant, placement->actorId,
        resource0, placement->ownerIndex == 0xFF ? -1 : placement->ownerIndex,
        resource1, amount, *(CVector3 *)placement->vec4, placement->spawnFlags,
        *(CVector3 *)placement->vec10, zero, lookup);
}

void Gobjinst_UpdateModelBounds(void *actorStorage, int model) {
    Actor36 *actor = actorStorage;
    ActorBoneBoundsCallback fn = actor->update;
    fn(actorStorage, actor->state);
    Graphu64_TransformBoundingBox(actor->matrix, model, &actor->box);
}

/* GOBJINST_BUILDACTORTRANSFORM.CPP */

void Gobjinst_BuildActorTransform(void *levelActor) {
    CQuatern trig;
    CQuatern product;
    CQuatern copy;
    CQuatern *copy_ptr;
    CQuatern *product_ptr;
    char *transform;
    f32 scale;
    f32 sine;
    f32 angle;

    copy = ((struct LevelActor *)(levelActor))->rotation;
    copy_ptr = &copy;
    if (Cinema_IsSequenceInWindow() != 0) {
        copy = Gobjinst_BuildActorDirectionTilt(levelActor);
    }

    angle = ((struct LevelActor *)(levelActor))->yaw;
    scale = (0.5f);
    sine = Gu_Sinf(angle * scale);
    trig.x = 0.0f;
    trig.y = sine;
    trig.z = 0.0f;
    angle = ((struct LevelActor *)(levelActor))->yaw * scale;
    g_turretAimSine = sine;
    trig.w = Math_Cosf(angle);

    product_ptr = &product;
    MultiplyQuaternions(product_ptr, &trig, copy_ptr);
    transform = &((struct LevelActor *)(levelActor))->transform[0];
    MatrixFromQuaternion(product_ptr, transform);
    ScaleMatrixLocal(transform, ((struct LevelActor *)(levelActor))->scale.x,
        ((struct LevelActor *)(levelActor))->scale.y,
        ((struct LevelActor *)(levelActor))->scale.z);
    Graphu64_LimitVectorLength(&((struct LevelActor *)(levelActor))->position0.x, 20000.0f);
    TranslateMatrix(transform, ((struct LevelActor *)(levelActor))->position0.x,
        ((struct LevelActor *)(levelActor))->position0.y,
        ((struct LevelActor *)(levelActor))->position0.z);
    SwapMatrixUpForward(transform);
}

void Gobjinst_NoOperation(void) {
}

void Gobjinst_QueueAnimation(void *actorStorage, unsigned int animationIndex)
{
    ((struct LevelActor *)(actorStorage))->nextAnimation = animationIndex;
    ((struct LevelActor *)(actorStorage))->animationPending = 0;
    if ((((struct LevelActor *)(actorStorage))->animation) != animationIndex)
    {
        ((struct LevelActor *)(actorStorage))->animationChanged = 1;
    }
}

void Gobjinst_RestartAnimation(void *actorAnimationState) {
    (((struct ActorAnimationResetState *) ((s8 *) actorAnimationState))->animationChanged) = 1;
    (((struct ActorAnimationResetState *) ((s8 *) actorAnimationState))->animationTime) = 0;
    (((struct ActorAnimationResetState *) ((s8 *) actorAnimationState))->animationPending) = 0;
    (((struct ActorAnimationResetState *) ((s8 *) actorAnimationState))->flags) = (s32) ((((struct ActorAnimationResetState *) ((s8 *) actorAnimationState))->flags) & ~0x400);
}

s32 Gobjinst_RequestAnimationKind(void *a, s32 c, s32 flag) {
    s32 selectedAnimation = Gobjinst_ChooseAnimationVariant(a, c, -1);

    if (selectedAnimation != -1) {
        return Gobjinst_RequestAnimationIndex(a, selectedAnimation, flag);
    }
    return 0;
}

s32 Gobjinst_RequestAnimationIndex(void *levelActor, s32 animationIndex, s32 allowDuringBlend) {
    if (animationIndex < 0 || (allowDuringBlend == 0 && (((struct LevelActor *)(levelActor))->flags & 0x400))) {
        return 0;
    }
    Gobjinst_QueueAnimation(levelActor, (u32) animationIndex);
    return 1;
}

s32 Gobjinst_ChooseAvailableAnimationKind(void *actor, s16 *callback, s32 excludedAnimation) {
    WeightedTable eligibleKinds;
    u16 animationKind;

    Lists_ClearWeightedTable(&eligibleKinds);
    animationKind = *(u16 *) callback;
    if (*callback != -1) {
        do {
            if (Gobjinst_ChooseAnimationVariant(actor, (s32) (s16) animationKind, excludedAnimation) != -1) {
                Lists_AppendWeightedEntry(&eligibleKinds, callback[0], callback[1]);
            }
            callback += 2;
            animationKind = *(u16 *) callback;
        } while (*callback != -1);
    }
    return Lists_ChooseWeightedTableEntry(&eligibleKinds);
}

s32 Gobjinst_BuildAnimatedPose(void *actorStorage, s32 resourceRequestMode)
{
    void *resource;
    s32 *entry;
    s32 value;
    s32 result;
    result = 0;
    if ((((struct LevelActor *)(actorStorage))->flags) & 0x40000)
    {
        if (resource)
        {
            resource = Cache_RequestResource(0, ((struct LevelActor *)(actorStorage))->resource, ((struct LevelActor *)(actorStorage))->resource, ((struct LevelActor *)(actorStorage))->resourceFlags, 0, 0, 0, (&g_actorAnimatedModelResourceTuning) + 4, resourceRequestMode);
        }
        else
        {
            resource = Cache_RequestResource(0, ((struct LevelActor *)(actorStorage))->resource, ((struct LevelActor *)(actorStorage))->resource, ((struct LevelActor *)(actorStorage))->resourceFlags, 0, 0, 0, (&g_actorAnimatedModelResourceTuning) + 4, resourceRequestMode);
        }
        if (resource == 0)
        {
            return result;
        }
        entry = Gobjinst_RequestAnimatedModelVariant(actorStorage, ((struct LevelActor *)(actorStorage))->team);
        if (entry != 0)
        {
            value = *entry;
            result = Gobjinst_BuildActorPose(actorStorage, value, SetN64_GetPackSection(*((void **) resource), 0));
            Cache_UnlockResource(0, (s32) entry);
        }
        Cache_UnlockResource(0, (s32) resource);
    }
    return result;
}

void Gobjinst_RotatePoseMatrixBuffers(void *actorRenderState) {
    s32 previousPoseMatrices;
    previousPoseMatrices = (((struct ActorPoseBufferState *) ((s8 *) actorRenderState))->poseMatrices);
    (((struct ActorPoseBufferState *) ((s8 *) actorRenderState))->poseMatrices) = 0;
    (((struct ActorPoseBufferState *) ((s8 *) actorRenderState))->clearedWordFirst) = 0;
    (((struct ActorPoseBufferState *) ((s8 *) actorRenderState))->clearedWordSecond) = 0;
    (((struct ActorPoseBufferState *) ((s8 *) actorRenderState))->flags) = (s32) ((((struct ActorPoseBufferState *) ((s8 *) actorRenderState))->flags) & ~0x200);
    (((struct ActorPoseBufferState *) ((s8 *) actorRenderState))->previousPoseMatrices) = previousPoseMatrices;
}

extern s32 g_lightingBufferIndex;
extern void GameObject_DrawActorShadow(char *obj, s32 shadowContext, char *info);


void Gobjinst_DrawMaskedModel(void *actor, void *unusedShadowContext, void *renderSettings) {
    s8 index;

    index = ((struct LevelActor *)(actor))->team;
    if (index != -1) {
        ((struct LevelActor *)(actor))->mask = 1 << index;
        if (((struct ActorRenderSettings *)(renderSettings))->drawShadow != 0) {
            GameObject_DrawActorShadow(actor, unusedShadowContext, renderSettings);
        }
        if (*(s32 *)renderSettings != 0) {
            Geometry_DrawModelResource(((struct ActorRenderSettings *)(renderSettings))->view,
                ((struct LevelActor *)(actor))->animationMatrices, 1,
                &((LevelActor *)actor)->lighting[g_lightingBufferIndex],
                0, ((struct LevelActor *)(actor))->renderPass);
            Gobjinst_SpawnAnimatedModelViewEffect(actor, renderSettings);
        }
    }
}

void Gobjinst_DrawMaskedModelWithLighting(void *actor, void *unusedShadowContext, void *renderSettings, Block24 *lighting) {
    s8 index;

    ((ActorLightingBlockView *)actor)->blocks[g_lightingBufferIndex] = *lighting;
    index = ((struct LevelActor *)(actor))->team;
    if (index != -1) {
        ((struct LevelActor *)(actor))->mask = 1 << index;
        if (((struct ActorRenderSettings *)(renderSettings))->drawShadow != 0) {
            GameObject_DrawActorShadow(actor, unusedShadowContext, renderSettings);
        }
        if (*(s32 *)renderSettings != 0) {
            Geometry_DrawModelResource(((struct ActorRenderSettings *)(renderSettings))->view,
                ((struct LevelActor *)(actor))->animationMatrices, 1,
                &((LevelActor *)actor)->lighting[g_lightingBufferIndex],
                0, ((struct LevelActor *)(actor))->renderPass);
            Gobjinst_SpawnAnimatedModelViewEffect(actor, renderSettings);
        }
    }
}

/* GOBJINST_GETACTOROFFSETPOSITIONANDMODEL.CPP */

/* Draws an actor's attached model: when the actor has one, allocates a matrix from the pool g_actorMatrixPool,
 * fills it with the given transform multiplied by the camera matrix (Graphu64_MultiplyMatrices, Graphu64_ClampMatrixToFixedRange,
 * GraphU64_PackFixedMatrix), loads it into the display list, draws the model through Geometry_DrawResourceModel with the
 * actor's per-frame state for the current frame, then reloads the camera's per-frame matrix. */

/* Moves an actor toward a point given relative to it: the offset is turned by the actor's facing and added to its position (or, for a mirrored actor with a parent, negated in x and z and transformed by the parent's matrix), then passed to InstHdr_CopyActorPositionAndModel with both final flags set. */

void Gobjinst_DrawModelWithProjection(void *actor, Camera *camera, f32 *transform, u8 layer) {
    struct LevelActor *object = actor;
    f32 mf[16];
    s32 mtx;
    s32 matrices;
    Gfx *restore;
    Gfx *load;
    s32 offset;

    if (object->animationMatrices != 0) {
        mtx = Map_ReserveEntries(&g_actorMatrixPool, 1);
        if (mtx != 0) {
            matrices = camera->matrices;
            Graphu64_MultiplyMatrices(mf, transform, (f32 *)(matrices + 480));
            Graphu64_ClampMatrixToFixedRange(mf);
            GraphU64_PackFixedMatrix(mf, mtx);
            gSPMatrix(g_displayListCursor++, mtx, G_MTX_LOAD | G_MTX_PROJECTION);
            Geometry_DrawResourceModel(layer, camera->style, object->animationMatrices, 1,
                &object->lighting[g_lightingBufferIndex], 0, object->renderPass);
            restore = g_displayListCursor++;
            offset = (g_lightingBufferIndex << 6) + 896;
            gSPMatrix(restore, matrices + offset, G_MTX_LOAD | G_MTX_PROJECTION);
        }
    }
}

void Gobjinst_GetActorOffsetPositionAndModel(char *actor, CVector3 offset, void *positionOut, s32 *modelOut)
{
    CVector3 turned;
    CVector3 target;

    if (((ActorAnimationResourceView *)(actor))->flags & 0x300000) {
        char *parent;

        offset.x = -offset.x;
        offset.z = -offset.z;
        parent = ((Player *)((ActorAnimationResourceView *)actor)->owner)->camera;
        if (parent != 0) {
            Graphu64_TransformPoint((char *)&((GameplayCamera *)parent)->viewOrient, &offset, &target);
        } else {
            Gobjinst_TransformVectorByActorAim(&turned, actor, offset);
            Graphu64_AddVec3(&target, &((ActorAnimationResourceView *)(actor))->position, &turned);
        }
    } else {
        Gobjinst_TransformVectorByActorAim(&turned, actor, offset);
        Graphu64_AddVec3(&target, &((ActorAnimationResourceView *)(actor))->position, &turned);
    }
    InstHdr_CopyActorPositionAndModel(actor, target, positionOut, modelOut, 1, 1);
}

CVector3 *Gobjinst_TransformVectorByActorAim(CVector3 *outVector, void *actor, CVector3 localVector) {
    CQuatern aimOrientation;
    s32 aimMatrix[16];
    CVector3 transformedVector;

    aimOrientation = Gobjinst_BuildActorAimQuaternion(actor);
    MatrixFromQuaternion(&aimOrientation, aimMatrix);
    Graphu64_TransformPoint(aimMatrix, &localVector, &transformedVector);
    *outVector = transformedVector;
    return outVector;
}

s32 Gobjinst_TestActorTriangleVerticalClearance(Shared_CollisionActor *actor) {
    CVector3 direction;
    Node75 *node;
    f32 upper;
    f32 upperNext;
    f32 lower;
    f32 lowerNext;
    f32 sine;
    f32 cosine;

    node = (void *)actor->collision;
    if (node != 0) {
        upper = node->cur->y;
        if (node->prev->y <= upper) {
        } else {
            upper = node->prev->y;
        }
        upperNext = node->next->y;
        if (upper <= upperNext) {
        } else {
            upperNext = upper;
        }
        lower = node->cur->y;
        if (lower <= node->prev->y) {
        } else {
            lower = node->prev->y;
        }
        lowerNext = node->next->y;
        if (lowerNext <= lower) {
        } else {
            lowerNext = lower;
        }
        if (upperNext < actor->y) {
            return 0;
        }
        if (actor->y < lowerNext) {
            return 0;
        }
        sine = Gu_Sinf(actor->angle);
        cosine = Math_Cosf(actor->angle);
        Region_GetNodeEdgeCross(&direction, node);
        if (direction.x * -sine + direction.z * -cosine < 0.0f) {
            return 1;
        }
    }
    return 0;
}

/** Return the global float at g_actorDefaultOffsetValue. */

float Gobjinst_GetActorOffsetDefault(void) {
    return g_actorDefaultOffsetValue;
}

/** Updates the actor controller of a barrel-style actor, passing the actor and its behaviour flags. */
void Gobjinst_UpdateActorController(LevelActor *base) {
    Barrel_UpdateActorController(base, &base->behaviorFlags);
}

/** Set or clear the attachment effect flag (bit two of the effect flags). */
void Gobjinst_SetAttachmentEffectBitTwo(void *object, int enabled) {
    ActorEffectFlagsView *object_record = object;
    unsigned int *flags = &object_record->effectFlags;
    if (enabled) {
        *flags |= 2;
    } else {
        *flags &= ~2U;
    }
}

s32 Gobjinst_GetModelRenderMode(void *typedActor) {
    void **modelResource;
    char *modelMetadata;
    s32 result;

    result = -1;
    modelResource = Gobjinst_RequestAnimatedModelVariant(typedActor, ((LevelActor *)typedActor)->team);
    if (modelResource != 0) {
        modelMetadata = SetN64_GetPackSection((int *)*modelResource, 5);
        result = ((struct ActorFrameMetadata *)modelMetadata)->renderMode;
        Cache_UnlockResource(0, modelResource);
    }
    return result;
}

/* GOBJINST_REQUESTANIMATEDMODELVARIANT.CPP */

f32 Gobjinst_GetRootMeanSquareScale(void *target) {
    float scaleX = ((LevelActor *)target)->scale.x;
    float scaleY = ((LevelActor *)target)->scale.y;
    float scaleZ = ((LevelActor *)target)->scale.z;
    return Gu_Sqrtf(((scaleX * scaleX) + (scaleY * scaleY) + (scaleZ * scaleZ)) * (0.3333333432674408f));
}

f32 Gobjinst_GetModelParticleScale(void *actor) {
    f32 result;
    void **modelResource;

    result = g_defaultModelParticleScale;
    if (((LevelActor *)actor)->flags & 0x40000) {
        modelResource = Cache_RequestResource(0, ((LevelActor *)actor)->resource, ((LevelActor *)actor)->resource, ((LevelActor *)actor)->resourceFlags, 4, 0, 0, &g_unitScaleMultiplierAnimObjectInfoRev1Text, 1);
        if (modelResource != 0) {
            result = RW_BITS_TO_FLOAT((s32) ((ActorResourceHeader *)SetN64_GetPackSection(*modelResource, 0))->particleScale);
            Cache_UnlockResource(0, modelResource);
        }
    }
    return result;
}

void **Gobjinst_RequestAnimatedModelVariant(MenuPanelRoot *actor, s32 variantIndex) {
    void **resource;

    if (variantIndex < 0) {
        return 0;
    }
    if (variantIndex != actor->selected) {
        resource = Cache_RequestResource(0, actor->resource,
            actor->resource, actor->resourceSize,
            0, 0, 0, &s_animModelIndexText, 1);
        if (resource != 0) {
            actor->selectedResource = SetN64_LocatePackSection((s32)*resource,
                actor->resource,
                variantIndex % *(s32 *)*resource,
                &actor->window);
            actor->selected = variantIndex;
            Cache_UnlockResource(0, resource);
        }
    }
    if (actor->selectedResource != 0) {
        return Cache_RequestResource(0, actor->selectedResource,
            actor->selectedResource, actor->window,
            0, 0, &g_Geometry_ExpandExtendedModelAddress, &s_animatedModelText, 0);
    }
    return 0;
}

#if defined(VERSION_EU_X)
void Gobjinst_EuropeExtendedNoOperation(void) {
}
#endif

#if defined(VERSION_EU_X)
void Gobjinst_EuropeExtendedAlternateNoOperation(void) {
}
#endif

#if defined(VERSION_EU)
void Gobjinst_EuropeNoOperation(void) {
}
#endif

#if defined(VERSION_EU)
void Gobjinst_EuropeAlternateNoOperation(void) {
}
#endif

/* ACTOR_ANIMATION_ROOT_AND_EVENT_OPERATIONS.CPP */

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
void Gobjinst_NoOperationAnimationHookUs(void) {
}
#if defined(VERSION_DE) || defined(VERSION_US_REV1)
void Gobjinst_NoOperationAnimationHook(void) {
}
#endif
#endif

#if defined(VERSION_US)
/** Perform no operation. */
void Gobjinst_NoOperationAnimationHookAlternateUs(void) {
}
#endif

/* Spawns the standing effects of an animation for an object: every event whose effect id is 6 or 7 is placed by transforming its local point through the object's matrix and spawned through Events_DeliverContactEffect_ActorAnimationRootAndEventOperations with its parameters. */

void *Gobjinst_GetAnimationRootOffset(Triple *outOffset, void *actor, CGameAnimateState_t *anim) {
    char *o1 = (char *) actor;
    char mtx[64];
    f32 spVec[3];
    f32 inVec[3];
    f32 outVec[3];

    Polytrak2_SampleVectorTrack(anim, 0, anim->time, spVec);
    inVec[0] = spVec[0];
    inVec[1] = spVec[2];
    inVec[2] = spVec[1];
    BuildYawMatrix(mtx, ((LevelActor *)o1)->yaw);
    Graphu64_TransformPoint(mtx, inVec, outVec);
    outVec[0] *= ((LevelActor *)o1)->scale.x;
    outVec[1] *= ((LevelActor *)o1)->scale.y;
    outVec[2] *= ((LevelActor *)o1)->scale.z;
    *outOffset = *(Triple *) outVec;
    return outOffset;
}

void Gobjinst_SpawnStandingAnimationEffects(char *obj, void *anim)
{
    CROMEventEntry *e;
    s32 count;
    s32 i;
    CVector3 pos;

    e = Gastate_GetAnimationEventEntries(anim);
    count = Gastate_GetAnimationEventCount(anim);
    for (i = 0; i < count; i++) {
        switch (e[i].effect) {
        case 6:
        case 7:
            Graphu64_TransformPoint(&((LevelActor *)obj)->transform, &e[i].local, &pos);
            Events_DeliverContactEffect(obj, obj, e[i].effect, -1, *(CVector3 *)&(pos), *(ContactEffectStyle *)&(e[i].params));
        }
    }
}

s32 Gobjinst_GetAnimationSectionDelta(LevelActor *actor, s32 deltaIndex) {
    void *modelResource;
    Table *deltaTable;
    s32 sectionDelta;

    if (actor->flags & 0x40000) {
        modelResource = Cache_RequestResource(0, actor->resource, actor->resource, actor->resourceFlags, 4, 0, 0, &s_actorAnimationResourceTag, 1);
        if (modelResource != 0) {
            deltaTable = SetN64_GetPackSection(*(void **) modelResource, 1);
            sectionDelta = deltaTable->deltas[deltaIndex];
            Cache_UnlockResource(0, (s32) modelResource);
            return sectionDelta;
        }
    }
    return -1;
}

int Gobjinst_ReturnUnusedAnimationStatus(void) {
    return 0;
}

void Gobjinst_ApplyHorizontalAnimationRootOffset(LevelActor *actor, CGameAnimateState_t *animation) {
    Scratch scratch;
    f32 zero;

    zero = 0.0f;
    Polytrak2_SampleVectorTrack(animation, 0, zero, scratch.first);
    Polytrak2_SampleVectorTrack(animation, 0, animation->time, scratch.second);
    scratch.in[0] = scratch.second[0] - scratch.first[0];
    scratch.in[1] = zero;
    scratch.in[2] = scratch.second[1] - scratch.first[1];
    BuildYawMatrix(scratch.matrix, actor->yaw);
    Graphu64_TransformPoint(scratch.matrix, scratch.in, scratch.out);
    scratch.position.x = actor->position0.x +
        (scratch.out[0] * actor->scale.x);
    scratch.position.y = actor->position0.y;
    scratch.position.z = actor->position0.z +
        (scratch.out[2] * actor->scale.z);
    InstHdr_CopyActorPositionAndModel(actor, scratch.position, &actor->position0,
        &actor->model, 0, 0);
}

/* GOBJINST_PACKAFFINEMATRIXWORDS.CPP */

extern char g_actorParticleEffectSystem[];




struct EffectSystem; extern int Particle_GetLastSpawnedEffect(struct EffectSystem *effectSystem);






extern void *g_actorTypeOperations[];


/* Applies a blast from a source to a body when an owner is given: the strength comes from the falloff table
 * g_boneTwistImpulseCurve indexed by the source's remaining charges, times 0.5 and 0.3 and the kind (-2 for kind 5);
 * the body's reversed velocity is placed in its offset transform, an impulse at the source position is
 * built by Graphu64_BuildAxisAngleMatrix and applied through Graphu64_MultiplyAffineMatrices, the velocity is restored onto the body, and
 * the source spends a charge when its owner matches. */




















void Gobjinst_SpawnAnimatedModelViewEffect(LevelActor *actor, ResourceLookupPointerView *lookup) {
    CVector3 position;
    SpawnedEffectMotionView *effect;
    f32 scale;
    s32 *node;

    if (Geometry_GetViewEffect() != 0) {
        node = SetN64_GetPackSection(*lookup->value, 2);
        if ((*node != 0) &&
            (*((s32 *)SetN64_GetPackSection(SetN64_GetPackSection(node, 0), 0)) & 0x8000)) {
            position = actor->position0;
            position.y += Gobjinst_GetActorHeight(actor) * 0.5f;
            Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], actor, actor, 0, 0, 148,
                          actor->position1, actor->rotation, position, 0, -1, 0);
            effect = Particle_GetLastSpawnedEffect(&g_actorParticleEffectSystem[0]);
            if (effect != 0) {
                scale = 0.1f;
                effect->radius = Gobjinst_GetActorRadius(actor) * scale;
                effect->height = Gobjinst_GetActorHeight(actor) * scale;
            }
        }
    }
}

void Gobjinst_DispatchAttachmentEffects(void *actor, void *modelPack, s32 attachmentMaskIndex, s32 boneMatrices)
{
    ActorMatrixPackFlagsView *object = actor;
    AttachmentEventTableView *attachmentTable;
    s32 attachmentCount;
    s32 mask = 1 << attachmentMaskIndex;
    char *attachmentEntries;
    if ((object->matrixPackFlags) & mask)
    {
        attachmentTable = SetN64_GetPackSection(modelPack, 3);
        attachmentCount = attachmentTable->entryCount;
        if (attachmentCount != 0)
        {
            attachmentEntries = &attachmentTable->entries;
            Ghot_DispatchAttachmentEffects(attachmentEntries, attachmentCount, boneMatrices, actor, SetN64_GetPackSection(modelPack, 5));
        }
    }
}

void *Gobjinst_GetActorTypeEntry(char *actorStorage)
{
    s32 type;
    s32 i;
    s32 count;
    s32 limit;
    char *object;
    ObjectList *list;

    LevelActor *actor = (void *)actorStorage;

    type = actor->definition->kind;
    if ((unsigned int)type >= 15) {
        return 0;
    }
    if (type == 11) {
        list = (ObjectList *)&g_playerViewRenderContext;
        count = list->count;
        i = 0;
        if (count > 0) {
            limit = count;
            object = list->objects;
            do {
                if (object == actorStorage) {
                    return 0;
                }
                if ((char *)&((SharedPlayer *)object)->views1C.view2E8_27.weapon == actorStorage) {
                    return g_actorDefinitionTable;
                }
                i++;
                object += sizeof(SharedPlayer);
            } while (i < limit);
        }
    }
    return g_actorTypeOperations[type];
}

void Gobjinst_ApplyBoneTwistImpulse(s32 operationContext, BoneTwistSourceView *source, BodyGobjinstApplyBoneTwistImpulse *body, s32 owner, s32 kind) {
    CVector3 velocity;
    CVector3 position;
    f32 impulse[16];
    f32 transform[16];
    f32 strength;
    f32 reverse;
    f32 multiplier;

    if (owner == 0) {
        return;
    }
    velocity.x = body->velocity.x;
    velocity.y = body->velocity.y;
    velocity.z = body->velocity.z;
    position = source->position;
    strength = g_boneTwistImpulseCurve[25 - source->charges] * 0.5f;
    strength *= 0.3f;
    if (kind == 5) {
        strength *= -2.0f;
    } else {
        strength *= kind;
    }
    CopyMatrix(transform, body);
    reverse = -1.0f;
    Graphu64_ScaleVector(&velocity, &velocity, reverse);
    TranslateMatrix(transform, velocity.x, velocity.y, velocity.z);
    Graphu64_BuildAxisAngleMatrix(impulse, strength, position.x, position.y, position.z);
    Graphu64_MultiplyAffineMatrices(body, transform, impulse);
    Graphu64_ScaleVector(&velocity, &velocity, reverse);
    TranslateMatrix(body, velocity.x, velocity.y, velocity.z);
    if (source->owner == owner) {
        source->charges--;
    }
}

/** Lerp a 3-component vector: out = a + t * (b - a). */
void Gobjinst_InterpolatePoseTranslation(void *outVector, f32 t, void *a, void *b) {
    CVector3 *out = outVector;
    CVector3 *start = a;
    CVector3 *end = b;
    out->x = start->x + (t * (end->x - start->x));
    out->y = start->y + (t * (end->y - start->y));
    out->z = start->z + (t * (end->z - start->z));
}

/** Lerp a 4-component vector: out = a + t * (b - a). */
void Gobjinst_InterpolatePoseRotation(void *cQuatern, f32 t, void *a, void *b) {
    CQuatern *out = cQuatern;
    CQuatern *left = a;
    CQuatern *right = b;

    out->x = left->x + (t * (right->x - left->x));
    out->y = left->y + (t * (right->y - left->y));
    out->z = left->z + (t * (right->z - left->z));
    out->w = left->w + (t * (right->w - left->w));
}

void Gobjinst_SampleBoneTranslation(void *poseTrack, s32 boneIndex, void *outTranslation) {
    AnimInfo *o = poseTrack;
    CVector3 *out = outTranslation;
    BoneRotationIndexPair *indices = (void *)o->boneIndexPairs;
    s16 idx;
    CROMInitialOrientation_t *recs;
    f32 *base;
    f32 *a;
    f32 scale;

    idx = indices[boneIndex].translation;
    if (idx == -1) {
        recs = (void *)o->initialOrientations;
        *out = recs[boneIndex].position;
        return;
    }
    base = SetN64_GetPackSection(o->translationFrames, (s32) idx);
    a = base + o->translationFirst;
    base = base + o->translationNext;

    scale = o->frameBlend;

    out->x = a[0] + scale * (base[0] - a[0]);
    out->y = a[1] + scale * (base[1] - a[1]);
    out->z = a[2] + scale * (base[2] - a[2]);
}

void Gobjinst_SampleBoneRotation(void *poseTrack, s32 boneIndex, CQuatern *outRotation) {
    char *o = (char *)poseTrack;
    s16 idx;
    char *rec;
    void *base;
    char *a;

    idx = ((struct BoneRotationIndexPair *) (((AnimInfo *) o)->boneIndexPairs + (boneIndex * 4)))->rotationIndex;
    if (idx == -1) {
        f32 scale;
        rec = ((AnimInfo *)(o))->initialOrientations + boneIndex * sizeof(CROMInitialOrientation_t);
        scale = (3.0518509447574615e-05f);
        outRotation->x = (f32)(((CROMInitialOrientation_t *)(rec))->m_RotX) * scale;
        outRotation->y = (f32)(((CROMInitialOrientation_t *)(rec))->m_RotY) * scale;
        outRotation->z = (f32)(((CROMInitialOrientation_t *)(rec))->m_RotZ) * scale;
        outRotation->w = (f32)(((CROMInitialOrientation_t *)(rec))->m_RotW) * scale;
        return;
    }
    base = SetN64_GetPackSection(((AnimInfo *)(o))->rotationFrames, (s32)idx);
    a = (char *)base + (((AnimInfo *)(o))->rotationFirst) * 4;
    base = (char *)base + (((AnimInfo *)(o))->rotationNext) * 4;
    {
        f32 scale;
        scale = ((AnimInfo *)(o))->frameBlend;
        outRotation->x = ((CQuatern *)(a))->x + scale * (((CQuatern *)(base))->x - ((CQuatern *)(a))->x);
        outRotation->y = ((CQuatern *)(a))->y + scale * (((CQuatern *)(base))->y - ((CQuatern *)(a))->y);
        outRotation->z = ((CQuatern *)(a))->z + scale * (((CQuatern *)(base))->z - ((CQuatern *)(a))->z);
        outRotation->w = ((CQuatern *)(a))->w + scale * (((CQuatern *)(base))->w - ((CQuatern *)(a))->w);
    }
}

void Gobjinst_SampleInterpolatedBoneRotation(BoneRotationTrackView *animation, s32 boneIndex, CQuatern *rotationOut) {
    BoneRotationTrackView *o = animation;
    BoneRotationIndexPair *indices;
    s16 idx;
    CROMInitialOrientation_t *rec;
    void *base;
    f32 scale;

    indices = (void *)o->boneIndexPairs;
    idx = indices[boneIndex].rotationIndex;
    if (idx == -1) {
        rec = (void *)(o->initialOrientations + boneIndex * sizeof(CROMInitialOrientation_t));
        scale = g_maskedModelViewEffectScale;
        rotationOut->x = (f32)rec->m_RotX * scale;
        rotationOut->y = (f32)rec->m_RotY * scale;
        rotationOut->z = (f32)rec->m_RotZ * scale;
        rotationOut->w = (f32)rec->m_RotW * scale;
        return;
    }
    base = SetN64_GetPackSection(o->rotationFrames, (s32)idx);
    Graphu64_InterpolateQuaternionArc(rotationOut, o->frameBlend,
        (char *)base + o->rotationFirst * 4,
        (char *)base + o->rotationNext * 4);
}

/* Converts a float to a signed word; values at or above the threshold are shifted down by it and flagged with the top bit,
 * which stores them as unsigned integers beyond the signed range. */
static inline s32 Gobjinst_FloatToUnsignedFlaggedWord(f32 value, f32 threshold) {
    s32 word;

    if (!(threshold <= value)) {
        return (s32)value;
    }
    word = (s32)(value - threshold);
    word |= 0x80000000;
    return word;
}

/* Packs one row of the affine part: the first two values share a high/low halfword pair, the third fills the next pair alone. */
#define GOBJINST_PACK_AFFINE_ROW(row, endFlag)                                                                                 \
    first = Gobjinst_FloatToUnsignedFlaggedWord(src[(row) * 4 + 0], g_affinePackUnsignedThresholdPairs[(row) * 3 / 2][((row) * 3) & 1]);       \
    second = Gobjinst_FloatToUnsignedFlaggedWord(src[(row) * 4 + 1], g_affinePackUnsignedThresholdPairs[((row) * 3 + 1) / 2][((row) * 3 + 1) & 1]); \
    *upper++ = (first & 0xFFFF0000) | ((u32)second >> 16);                                                            \
    *lower++ = (first << 16) | (second & 0xFFFF);                                                                      \
    first = Gobjinst_FloatToUnsignedFlaggedWord(src[(row) * 4 + 2], g_affinePackUnsignedThresholdPairs[((row) * 3 + 2) / 2][((row) * 3 + 2) & 1]); \
    *upper++ = (first & 0xFFFF0000) | (endFlag);                                                                               \
    *lower++ = first << 16;

/* Converts the twelve used entries of a 4x4 float matrix (the fourth column is skipped) to unsigned integers, splitting
 * each pair into the high and low halfword arrays of a packed matrix and setting the final high word's low bit. */
void Gobjinst_PackAffineMatrixWords(f32 *src, FixedPointMatrix *dst) {
    u32 *upper = dst->upper;
    u32 *lower = dst->lower;
    s32 a;
    s32 b;
    { f32 value = (src[0]);
    if (!((g_affinePackUnsignedThresholdPairs[0][0]) <= value)) { (a) = (s32)value;
    } else { (a) = (s32)(value - (g_affinePackUnsignedThresholdPairs[0][0]));
    (a) |= 0x80000000;
    } };
    { f32 value = (src[1]);
    if (!((*(&g_affinePackUnsignedThresholdPairs[0][0] + 1)) <= value)) { (b) = (s32)value;
    } else { (b) = (s32)(value - (*(&g_affinePackUnsignedThresholdPairs[0][0] + 1)));
    (b) |= 0x80000000;
    } };
    *upper = (a & 0xFFFF0000) | ((u32)b >> 16);
    *lower = (a << 16) | (b & 0xFFFF);
    upper++;
    lower++;
    { f32 value = (src[2]);
    if (!((g_affinePackUnsignedThresholdPairs[1][0]) <= value)) { (a) = (s32)value;
    } else { (a) = (s32)(value - (g_affinePackUnsignedThresholdPairs[1][0]));
    (a) |= 0x80000000;
    } };
    *upper = a & 0xFFFF0000;
    *lower = a << 16;
    upper++;
    lower++;
    { f32 value = (src[4]);
    if (!((*(&g_affinePackUnsignedThresholdPairs[1][0] + 1)) <= value)) { (a) = (s32)value;
    } else { (a) = (s32)(value - (*(&g_affinePackUnsignedThresholdPairs[1][0] + 1)));
    (a) |= 0x80000000;
    } };
    { f32 value = (src[5]);
    if (!((g_affinePackUnsignedThresholdPairs[2][0]) <= value)) { (b) = (s32)value;
    } else { (b) = (s32)(value - (g_affinePackUnsignedThresholdPairs[2][0]));
    (b) |= 0x80000000;
    } };
    *upper = (a & 0xFFFF0000) | ((u32)b >> 16);
    *lower = (a << 16) | (b & 0xFFFF);
    upper++;
    lower++;
    { f32 value = (src[6]);
    if (!((*(&g_affinePackUnsignedThresholdPairs[2][0] + 1)) <= value)) { (a) = (s32)value;
    } else { (a) = (s32)(value - (*(&g_affinePackUnsignedThresholdPairs[2][0] + 1)));
    (a) |= 0x80000000;
    } };
    *upper = a & 0xFFFF0000;
    *lower = a << 16;
    upper++;
    lower++;
    { f32 value = (src[8]);
    if (!((g_affinePackUnsignedThresholdPairs[3][0]) <= value)) { (a) = (s32)value;
    } else { (a) = (s32)(value - (g_affinePackUnsignedThresholdPairs[3][0]));
    (a) |= 0x80000000;
    } };
    { f32 value = (src[9]);
    if (!((*(&g_affinePackUnsignedThresholdPairs[3][0] + 1)) <= value)) { (b) = (s32)value;
    } else { (b) = (s32)(value - (*(&g_affinePackUnsignedThresholdPairs[3][0] + 1)));
    (b) |= 0x80000000;
    } };
    *upper = (a & 0xFFFF0000) | ((u32)b >> 16);
    *lower = (a << 16) | (b & 0xFFFF);
    upper++;
    lower++;
    { f32 value = (src[10]);
    if (!((g_affinePackUnsignedThresholdPairs[4][0]) <= value)) { (a) = (s32)value;
    } else { (a) = (s32)(value - (g_affinePackUnsignedThresholdPairs[4][0]));
    (a) |= 0x80000000;
    } };
    *upper = a & 0xFFFF0000;
    *lower = a << 16;
    upper++;
    lower++;
    { f32 value = (src[12]);
    if (!((*(&g_affinePackUnsignedThresholdPairs[4][0] + 1)) <= value)) { (a) = (s32)value;
    } else { (a) = (s32)(value - (*(&g_affinePackUnsignedThresholdPairs[4][0] + 1)));
    (a) |= 0x80000000;
    } };
    { f32 value = (src[13]);
    if (!((g_affinePackUnsignedThresholdPairs[5][0]) <= value)) { (b) = (s32)value;
    } else { (b) = (s32)(value - (g_affinePackUnsignedThresholdPairs[5][0]));
    (b) |= 0x80000000;
    } };
    *upper = (a & 0xFFFF0000) | ((u32)b >> 16);
    *lower = (a << 16) | (b & 0xFFFF);
    upper++;
    lower++;
    { f32 value = (src[14]);
    if (!((*(&g_affinePackUnsignedThresholdPairs[5][0] + 1)) <= value)) { (a) = (s32)value;
    } else { (a) = (s32)(value - (*(&g_affinePackUnsignedThresholdPairs[5][0] + 1)));
    (a) |= 0x80000000;
    } };
    *upper = (a & 0xFFFF0000) | 1;
    *lower = a << 16;
}

/* GAMEOBJECT_GETACTORHEIGHT.CPP */

/* Builds a 4x4 transform from a rotation quaternion (x, y, z, w) and a translation, with a zero fourth column and the corner set to the constant at g_actorAffineMatrixHomogeneousUnit. */

void GameObject_BuildQuaternionTranslationMatrix(f32 *m, f32 *q, f32 *t)
{
    f32 x = q[0];
    f32 xx = x * x;
    f32 y = q[1];
    f32 yy = y * y;
    f32 z = q[2];
    f32 zz = z * z;
    f32 w = q[3];
    f32 ww = w * w;
    f32 x2 = x + x;
    f32 xy = x2 * y;
    f32 w2 = w + w;
    f32 wz = w2 * z;
    f32 xz = x2 * z;
    f32 wy = w2 * y;
    f32 wx = w2 * x;
    f32 yz = (y + y) * z;

    m[0] = ww + xx - yy - zz;
    m[1] = xy + wz;
    m[2] = xz - wy;
    m[4] = xy - wz;
    m[5] = ww - xx + yy - zz;
    m[6] = yz + wx;
    m[8] = xz + wy;
    m[9] = yz - wx;
    m[10] = ww - xx - yy + zz;
    m[12] = t[0];
    m[13] = t[1];
    m[14] = t[2];
    m[3] = 0.0f;
    m[7] = 0.0f;
    m[11] = 0.0f;
    m[15] = g_actorAffineMatrixHomogeneousUnit;
}

void GameObject_BuildLitActorResource(void *levelActor, int **resourcePair) {
    struct LevelActor *object = levelActor;
    int *deref1;
    int deref2;
    int ret;

    deref1 = *resourcePair;
    deref2 = *deref1;
    ret = Lighting_BuildLitModel(deref2, 0, &object->bounds, object->animationMatrices, 1, levelActor);
    Cache_ReplaceResourcePairFirst(0, resourcePair, ret);
}

typedef struct InteractionDescriptor { s32 kind; char pad4[0x10]; s32 flags; } InteractionDescriptor;
typedef struct InteractionLink { char pad0[0x1C]; s32 flags; char pad20[0x83C]; s32 linked; } InteractionLink;
typedef struct InteractionActor {
    u8 kind; char pad1[0x17]; InteractionDescriptor *descriptor;
    char pad1C[0xE4]; s32 flags; char pad104[0x9C]; InteractionLink *attached;
    char pad1A4[0x34]; InteractionLink *player;
} InteractionActor;
s32 InstHdr_CanActorReceiveInteraction(InteractionActor *actor) {
    s32 flags;
    InteractionLink *link;
    s32 bit;
    switch (actor->descriptor->kind) {
    case 11:
        if (actor->kind == 1 && (actor->flags & 0x300000) != 0) {
            link = actor->player;
            if (g_gameSettings.local != 0 && link->linked != 0) return 0;
        }
    case 8: return 1;
    case 0: return actor->descriptor->flags & 2;
    case 2:
        if (actor->kind != 1) return 0;
        return actor->flags & 0x10000;
    case 1:
        if (actor->kind != 1 || (actor->flags & 0x2000) == 0) return 0;
        link = actor->attached;
        if (link == 0) return 0;
        bit = link->flags & 0x10000;
        return !bit;
    case 4: case 5: case 7: case 10:
        if (actor->kind != 1) return 0;
        flags = actor->flags;
        if (!(flags & 0x2000)) return 0;
        return flags & 0x10000;
    case 12: return actor->descriptor->flags & 1;
    }
    return 0;
}

f32 Gobjinst_GetActorHeight(Actor_u1 *actor) {
    Resource_u1 *resource;

    if (actor->kind == 1 && actor->active <= 0) {
        return InstHdr_GetInactiveActorHeight(actor);
    }
    switch (actor->resource->kind) {
    case 11:
        if (actor->kind == 1 && (actor->flags & 0x300000)) {
            return actor->state->heightDelta;
        }
        return actor->resource->valueF4;
    case 1:
    case 4:
        return actor->resource->value30;
    case 8:
        resource = actor->resource;
        if (resource->flags14 & 1) {
            return 122.88f;
        }
        return resource->value1C;
    case 7:
        return actor->resource->value20;
    case 6:
        return 102.399994f;
    case 0:
    case 5:
    case 10:
    case 12:
    case 13:
    case 14:
        return actor->resource->value1C;
    }
    return 0.0f;
}

f32 Gobjinst_GetActorRadius(Actor_u1 *actor)
{
    Resource_u1 *resource;
    f32 a;
    f32 b;
    switch (actor->resource->kind) {
    case 11:
        if (actor->kind == 1 && (actor->flags & 0x300000) && actor->state->active) {
            return g_activePlayerActorRadius;
        }
        return actor->resource->valueEC;
    case 0: case 5: case 8: case 10: case 12: case 13: case 14:
        return actor->resource->radius;
    case 1: case 4:
        return actor->resource->value28;
    case 2:
        resource = actor->resource;
        if (((CollisionShapeResource *)resource)->mode == 2) {
            a = ((CollisionShapeResource *)resource)->width;
            b = ((CollisionShapeResource *)resource)->height;
            if (!(b <= a)) a = b;
            b = ((CollisionShapeResource *)resource)->depth;
            if (!(a <= b)) b = a;
            return b * g_collisionShapeRadiusScale;
        }
        return ((CollisionShapeResource *)resource)->height;
    case 7:
        return actor->resource->value1C;
    default:
        return 0.0f;
    }
}

#if defined(VERSION_DE)

#endif

/* GOBJINST_BUILDTARGETAIMORIENTATION.CPP */

/* Returns the rotation that turns an actor's aim toward a target point: a player's forward axis is its
 * aiming orientation from Gobjinst_BuildActorAimQuaternion applied to +z, anyone else looks along +z; the target is the
 * player's lock-on or else whatever Playerai_FindNearestPlayer finds at the point, and with no target the
 * identity is returned. Otherwise the forward axis turns about its cross product with the direction from
 * the point up to three quarters of the target's height, by half the angle between them, composed with the
 * player's aiming orientation; the sine is kept in g_turretAimSine. */

CQuatern Gobjinst_BuildTargetAimOrientation(char *actor, CVector3 point) {
    CVector3 origin;
    CVector3 dir;
    CVector3 forward;
    CVector3 local;
    CVector3 axis;
    CQuatern turn;
    CQuatern aim;
    CQuatern result;
    f32 matrix[16];
    char *target;
    char *found;
    f32 angle;
    f32 scale;

    target = 0;
    if (actor != 0 && ((LevelActor *)actor)->kind == 1) {
        target = ((LevelActor *)(actor))->lockOn;
        aim = Gobjinst_BuildActorAimQuaternion(actor);
        MatrixFromQuaternion(&aim, matrix);
        local.x = 0.0f;
        local.y = 0.0f;
        local.z = 1.0f;
        Graphu64_TransformPoint(matrix, &local, &forward);
    } else {
        forward.x = 0.0f;
        forward.y = 0.0f;
        forward.z = 1.0f;
    }
    if (target == 0) {
        found = Playerai_FindNearestPlayer(&g_playerViewRenderContext, point);
        if (found != 0) {
            target = found;
        }
        if (target == 0) {
            result.x = result.y = result.z = 0.0f;
            result.w = 1.0f;
            return result;
        }
    }
    origin = ((LevelActor *)target)->position0;
    origin.y += ((LevelActor *)target)->eyeHeight;
    origin.y += Gobjinst_GetActorHeight(target) * 0.75f;
    Graphu64_SubtractVectors(&dir, &origin, &point);
    Graphu64_NormalizeVec3(&dir);
    Graphu64_CrossVectors(&axis, &forward, &dir);
    Graphu64_NormalizeVec3(&axis);
    angle = Graphu64_ArcCos(forward.x * dir.x + forward.y * dir.y + forward.z * dir.z) * 0.5f;
    scale = Gu_Sinf(angle);
    turn.x = axis.x * scale;
    turn.y = axis.y * scale;
    turn.z = axis.z * scale;
    g_turretAimSine = scale;
    turn.w = Math_Cosf(angle);
    if (actor != 0 && ((LevelActor *)actor)->kind == 1) {
        MultiplyQuaternions(&result, &aim, &turn);
    } else {
        result = turn;
    }
    return result;
}

CQuatern Gobjinst_BuildActorDirectionTilt(ActorDirectionTiltInput *input) {
    CVector3 source;
    CVector3 up;
    CVector3 axis;
    CQuatern result;
    f32 angle;
    f32 scale;
    int state;

    state = input->state;
    if (state == 0) {
        goto default_source;
    }
    if (state < 0) {
        goto default_source;
    }
    if (state < 4) {
        goto input_source;
    }
    default_source:
    source.x = 0.0f;
    source.y = g_actorBoneAimSourceY;
    source.z = 0.0f;
    goto source_ready;
    input_source:
    source = input->direction;
    source_ready:

    up.x = 0.0f;
    up.y = g_actorBoneAimUpY;
    up.z = 0.0f;
    Graphu64_CrossVectors(&axis, &up, &source);
    Graphu64_NormalizeVec3(&axis);

    angle = Graphu64_ArcCos((up.x * source.x) +
        (up.y * source.y) +
        (up.z * source.z));
    angle *= g_actorBoneAimAngleScale;
    scale = Gu_Sinf(angle);
    result.x = axis.x * scale;
    result.y = axis.y * scale;
    result.z = axis.z * scale;
    g_turretAimSine = scale;
    result.w = Math_Cosf(angle);

    return result;
}

/* GAMEOBJECT_RESETACTORMOTION_DATA.CPP */

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)



#endif

/* ANIMATION_TYPE_OBJECT_INFO_TEXT.CPP */

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)

#endif

/* GOBJINST_DATA.CPP */

extern const char g_lookupAIAnimTypeAnimObjectInfoText[56];

extern const char g_gameObjectAnimIndexText[18];

/* G_ANIMMODELSINDEXTEXT.CPP */

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)
extern const char s_animModelsIndexText[18];
#endif

/* GAMEOBJECT_LOADMODEL_DATA.CPP */

#if !(defined(VERSION_US_REV1))
extern const char g_gameObjectResetAnimInfoText[45];
#endif

#if defined(VERSION_US_REV1)

#endif

/* ANIMATION_ADVANCE_OBJECT_INFO_TEXT.CPP */

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)

#endif

/* G_ANIMATIONSINDEXTEXT.CPP */

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)



#endif

/* RANDVEC.CPP */













/* GOBJINST_DRAWTEAMMASKEDMODEL_DATA.CPP */



/* GOBJINST_GETMODELPARTICLESCALE_DATA.CPP */

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)
extern const char g_unitScaleMultiplierAnimObjectInfoRev1Text[62];
#endif

/* S_ANIMMODELINDEXTEXT.CPP */

#if !(defined(VERSION_US_REV1))
extern const char s_animModelIndexText[17];
#endif

#if defined(VERSION_US_REV1)

#endif

/* S_ANIMATEDMODELTEXT.CPP */

#if !(defined(VERSION_US_REV1))
extern const char s_animatedModelText[15];
#endif

#if defined(VERSION_US_REV1)

#endif

/* ACTOR_TRANSFORM_EPSILON_CONSTANT.CPP */



/* GOBJINST_GETACTOROFFSETPOSITIONANDMODEL_DATA.CPP */



/* GOBJINST_REQUESTANIMATEDMODELVARIANT_DATA.CPP */



/* GOBJINST_SPAWNANIMATEDMODELVIEWEFFECT_DATA.CPP */



/* GOBJINST_SAMPLEINTERPOLATEDBONEROTATION_DATA.CPP */



/* GOBJINST_PACKAFFINEMATRIXWORDS_DATA.CPP */





#if defined(VERSION_EU_X)
extern char k_GobjinstPackaffinematrixwordsEncodedBytes[12];
#endif

/* GOBJINST_BUILDACTORDIRECTIONTILT_DATA.CPP */



/* GAMEOBJECT_MOVETOXZKEEPHEIGHT_DATA.CPP */

#if defined(VERSION_DE) || defined(VERSION_US_REV1)
const float g_gameObjectMoveToXzKeepHeightConstants[2] = {
    0.3f, 3.0f,
};
#endif

#if defined(VERSION_EU)
struct {
    s32 g_collisionMovementCount;
    s32 g_collisionPeakMovementCount;
    s32 g_collisionSweepCount;
    s32 g_collisionPeakSweepCount;
    s32 g_cinemaLastUpdatedFrame;
    u8 retainedDinosoidsText[12];
} g_gameObjectMoveToXzKeepHeightRetainedWords __attribute__((aligned(4))) = {
    0,
    0,
    0,
    0,
    -1,
    { 0x2f, 0x20, 0x44, 0x49, 0x4e, 0x4f, 0x53, 0x4f, 0x49, 0x44, 0x53, 0x0 }
};
typedef char g_gameObjectMoveToXzKeepHeightRetainedWordsSizeCheck[(sizeof(g_gameObjectMoveToXzKeepHeightRetainedWords) == 32) ? 1 : -1];

const float g_gameObjectMoveToXzKeepHeightConstants[2] = {
    0.3f, 3.0f,
};
#endif

#if defined(VERSION_EU_X)
extern struct {
    s32 g_collisionMovementCount;
    s32 g_collisionPeakMovementCount;
    s32 g_collisionSweepCount;
    s32 g_collisionPeakSweepCount;
    s32 g_cinemaLastUpdatedFrame;
    u8 retainedFloatWords[12];
} g_gameObjectMoveToXzKeepHeightRetainedWords __attribute__((aligned(4)));
typedef char g_gameObjectMoveToXzKeepHeightRetainedWordsSizeCheck[(sizeof(g_gameObjectMoveToXzKeepHeightRetainedWords) == 32) ? 1 : -1];

const float g_gameObjectMoveToXzKeepHeightConstants[2] = {
    0.3f, 3.0f,
};
#endif

#if defined(VERSION_US)
extern struct {
    s32 g_collisionMovementCount;
    s32 g_collisionPeakMovementCount;
    s32 g_collisionSweepCount;
    s32 g_collisionPeakSweepCount;
    s32 g_cinemaLastUpdatedFrame;
    u8 retainedParticleTagText[12];
} g_gameObjectMoveToXzKeepHeightRetainedWords __attribute__((aligned(4)));
typedef char g_gameObjectMoveToXzKeepHeightRetainedWordsSizeCheck[(sizeof(g_gameObjectMoveToXzKeepHeightRetainedWords) == 32) ? 1 : -1];

const float g_gameObjectMoveToXzKeepHeightConstants[2] = {
    0.3f, 3.0f,
};
#endif

/* K_BREAKABLEMOTIONRECORDPOINTERS_DE.CPP */

#if defined(VERSION_DE)
unsigned int k_breakableMotionRecordPointers_de[17] = {
    (unsigned int)&g_actionInitBreakableMotionRecordTable_de[311],
    (unsigned int)&g_actionInitBreakableMotionRecordTable_de[202], 0x00000000, 0x00000000,
    (unsigned int)&g_actionInitBreakableMotionRecordTable_de[315],
    (unsigned int)&g_actionInitBreakableMotionRecordTable_de[206], (unsigned int)&g_turretDispatchTriggerPairs_de[96], 0x00000000,
    (unsigned int)&g_actionInitBreakableMotionRecordTable_de[91],
    (unsigned int)&g_actionInitBreakableMotionRecordTable_de[139], 0x00000000,
    (unsigned int)&g_actionInitBreakableMotionRecordTable_de[239],
    (unsigned int)&g_actionInitBreakableMotionRecordTable_de[32], 0x00000000, 0x00000000, 0x00000000,
    0x00000000,
};
#endif

/* ACTOR_POSE_TUNING_CONSTANT_TAIL.CPP */

#if defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)

#endif

/* S_ROBERTSOTEXT.CPP */
#if defined(VERSION_EU)

struct {
    char text0[8];
    unsigned int words1[15];
} s_robertsoText = {
    "ROBERTSO",
    {
        0x00000000, 0x00000000, 0x800C9370, 0x800C91BC, 0x800C8E40, 0x00000000, 0x800C8FF0, 0x800C90B0,
        0x00000000, 0x800C9240, 0x800C8F04, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    },
};
#endif



/* GAMEOBJECT_BUILDTARGETAIMORIENTATION.CPP */

#if defined(VERSION_EU_X)

#endif

/* SNDPLAYER.CPP */
#if defined(VERSION_EU_X)
SndplayerEncodedWordsLayout k_Sndplayer = {
    { 1.5483116f, 1.5473337f, 0.0f, 0.0f },
    { &g_triggeredMotionDispatchTable[224], &g_spawnActorDispatchTable[128], &g_turretDispatchTriggerPairs_eu_x[92], 0, &g_actionEnterDispatchTriggerPairs_eu_x[16], &g_damageDispatchTriggerPairs_eu_x[72], 0, &g_movingMotionDispatchTable[96], &g_actionMotionDispatchTriggerPairs_eu_x[12], 0, 0, 0, 0 }
};
#endif

/* Retained data for this translation unit. */

const float g_actorRootMotionCubicCoefficients[2] = {
    -2.0f, 3.0f,
};
#if defined(VERSION_DE)
const float k_GameobjectGetactorheightEncodedWords[2] = {
    122.88f, 1.42f,
};
#endif
#if !(defined(VERSION_US_REV1))
const float g_actorMotionResetUnitConstants[2] = {
    1.0f, 0.8f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_GameObject_ResetActorMotionConstants[1] = {
    1.0f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_Gobjinst_HasClearPathToActorConstants[1] = {
    0.8f,
};
#endif
#if !(defined(VERSION_US_REV1))
const char s_getAnimTypeAnimObjectInfoText[51] =
    "CGameObjectInstance__GetAnimType: anim object info\000";
#endif
#if defined(VERSION_US_REV1)
const char s_animationTypeObjectInfoUsRev1[51] =
    "CGameObjectInstance__GetAnimType: anim object info";
#endif
#if !(defined(VERSION_US_REV1))
const char g_animModelsIndexText[18] =
    "anim models index\000";
#endif
#if defined(VERSION_US_REV1)
const char s_animationResetObjectInfoUsRev1[45] =
    "CGameObjectInstance__Reset: anim object info";
#endif
#if !(defined(VERSION_US_REV1))
const char s_advanceAnimObjectInfoText[47] =
    "CGameObjectInstance__Advance: anim object info\000";
#endif
#if defined(VERSION_US_REV1)
const char s_animationAdvanceObjectInfoUsRev1[47] =
    "CGameObjectInstance__Advance: anim object info";
#endif
#if !(defined(VERSION_US_REV1))
const char k_GAnimationsindextextEncodedBytes[33] =
    "\077\200\000\000>\000\000\000=\031\231\232\077\200\000\000animations index\000";
#endif
#if defined(VERSION_US_REV1)
const float k_GAnimationsindextext[4] = {
    1.0f, 0.125f, 0.0375f, 1.0f,
};
#endif
#if defined(VERSION_US_REV1)
const char g_animationsIndexText[17] =
    "animations index";
#endif

const char s_calculateMatrixStackAnimInfoText[60] = "CGameObjectInstance__CalculateMatrixStack: anim object info";

const char s_drawAnimObjectInfoText[44] = "CGameObjectInstance__Draw: anim object info";

const float g_Gobjinst_DrawActorModelWithViewEffectsConstants[2] = {
    0.5f, 0.1f,
};

const float g_Gobjinst_DrawActorPartsWithViewEffectsConstants[2] = {
    0.5f, 0.1f,
};

const float g_Gobjinst_DrawBlendPartsWithViewEffectsConstants[2] = {
    0.5f, 0.1f,
};

const char s_maskedModelLitVerticesTagUsRev1[13] = "lit vertices\000";

const float g_Gobjinst_DrawTeamMaskedModelConstants[2] = {
    0.5f, 0.1f,
};
#if !(defined(VERSION_US_REV1))
const char g_unitScaleMultiplierAnimObjectInfoText[62] =
    "CGameObjectInstance__GetUnitScaleMultiplier: anim object info\000";
#endif
#if defined(VERSION_US_REV1)
const char s_animatedModelIndexTagUsRev1[17] =
    "anim model index";
#endif
#if defined(VERSION_US_REV1)
const char s_animatedModelResourceTagUsRev1[15] =
    "animated model";
#endif

const float g_Gobjinst_InitializePlacedActorConstants[1] = {
    9.587673e-05f,
};

const float g_Gobjinst_UpdateActorControllerConstants[1] = {
    1.0f,
};

const float g_Gobjinst_GetModelParticleScaleConstants[1] = {
    1.0f,
};

const float g_Gobjinst_SampleInterpolatedBoneRotationConstants[1] = {
    3.051851e-05f,
};

const float g_affinePackUnsignedConversionThresholds[12] = {
    2.1474836e+09f, 2.1474836e+09f, 2.1474836e+09f, 2.1474836e+09f, 2.1474836e+09f, 2.1474836e+09f,
    2.1474836e+09f, 2.1474836e+09f, 2.1474836e+09f, 2.1474836e+09f, 2.1474836e+09f, 2.1474836e+09f,
};

const float g_GameObject_BuildQuaternionTranslationMatrixConstants[1] = {
    1.0f,
};

const float g_Gobjinst_BuildActorDirectionTiltConstants[3] = {
    1.0f, 1.0f, 0.5f,
};
#if defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
const float g_Gobjinst_GetActorRadiusConstantTail[2] = {
    122.88f, 1.42f,
};
#endif
#if defined(VERSION_EU_X)
const float k_GameobjectBuildtargetaimorientation[2] = {
    122.88f, 1.42f,
};
#endif

const char g_lookupAIAnimTypeAnimObjectInfoText[56] = "CGameObjectInstance__LookupAIAnimType: anim object info";

const char g_gameObjectAnimIndexText[18] = "anim object index";
#if defined(VERSION_US_REV1)
const char s_animModelsIndexText[18] = "anim models index";
#endif
#if !(defined(VERSION_US_REV1))
const char g_gameObjectResetAnimInfoText[45] =
    "CGameObjectInstance__Reset: anim object info\000";
#endif
#if defined(VERSION_US_REV1)
const char g_unitScaleMultiplierAnimObjectInfoRev1Text[62] = "CGameObjectInstance__GetUnitScaleMultiplier: anim object info";
#endif
#if !(defined(VERSION_US_REV1))
const char s_animModelIndexText[17] =
    "anim model index\000";
#endif
#if !(defined(VERSION_US_REV1))
const char s_animatedModelText[15] =
    "animated model\000";
#endif
