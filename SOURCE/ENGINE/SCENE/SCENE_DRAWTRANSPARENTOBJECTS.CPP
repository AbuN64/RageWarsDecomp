#include "COMMON/OBJB.H"
#include "ENGINE/SCENE.H"
#include "COMMON/LONE/SCREEN_IMAGE_RESOURCES_ENABLED.H"
#include "include_asm.h"
#include "COMMON/SCENERECAT10C0.H"
#include "COMMON/SCENE_FRAME_AND_EFFECT_UPDATES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SETTINGSRECAT24.H"
#include "COMMON/MENUSELECTIONMESSAGE.H"
#include "TYPES.H"
#include "COMMON/WORLDRECAT1B6A4.H"
#include "TYPES.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/MENULISTSCREEN.H"
#include "ACHIEVE/ACHIEVE_OPENRESULTSFRONTEND.H"
#include "RENDER/EFFECT_POOL_OPERATIONS.H"
#include "SCENE/SCENE_UPDATEANDDRAWWORLD.H"
#include "ENGINE/SCENE_LOADLEVELRESOURCES.H"
#include "ENGINE/SCENE_GRID_AND_GEOMETRY_OPERATIONS.H"
#include "WEAPONS/PLAYER_UPDATEFRAGTAGSELECTION.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "VOICE/VOICE.H"

void Scene_UpdateAndDrawWorld(void *world) {
    Shared_World *state;
    Shared_Game *input;
    s32 old_flags;

    state = world;
    input = &g_gameSettings;
    old_flags = g_litGeometryResourceKeyFlags;
    g_litGeometryResourceKeyFlags = input->lightingGamma;
    if (input->flags & 0x4000) {
        g_litGeometryResourceKeyFlags |= 0x100;
    }
    if (input->flags & 0x8000) {
        g_litGeometryResourceKeyFlags |= 0x200;
    }
    if (old_flags != g_litGeometryResourceKeyFlags) {
        g_litGeometryResourceKeysChanged = 1;
        Cache_SetResourceActivityState(8);
    } else {
        g_litGeometryResourceKeysChanged = 0;
    }

    Scene_UpdateSelectionTransition(state);
    Scene_ClearSceneObjectCounts(state);
    state->counter120 = 0;
    state->counter124 = 0;
    Map_ResetFramePool(state->system128);
    Cache_MarkResourceInUse(0, state->resource);
    {
        void *manager;

        manager = &g_actorParticleScene;
        Fx_ResetRibbonVertexPool(manager);
        Playerai_RotatePlayerPoseBuffers(&g_playerViewRenderContext);
        Scene_UpdateActorVisibility(state);
        Scene_RequestVisibleGridSections(state);
        Scene_CollectVisibleEffects(state);

        if ((state->frozen == 0) && (g_frontendScreenStatus.status[7] == 0)) {
            Fx_UpdateEffectLists(manager);
            Scene_UpdateActorsAndRoundState(state);
            SetN64_UpdateEffectPool(&state->system11778);
            state->elapsed += g_frameElapsedTime * g_sceneElapsedTimeScaleDe;
            Scene_UpdateTriggerTimers(state);
        }
    }

    Particle_UpdateSystem(state->system1B08);
    if (state->frozen == 0) {
        Playerai_StopInactivePlayerSounds(&g_playerViewRenderContext);
    }

    Camera_DrawActiveViews(&g_frontendScreenStatus, state);
    if ((state->frozen == 0) && (g_frontendScreenStatus.status[7] == 0)) {
        Scene_UpdateStaticEventInstances(state);
    }
    Scene_UnlockActiveSectionResources(state);
    Scene_DrawTransitionColorOverlay(state);
}



extern void Gobjinst_UpdateActorController(void *base);
extern void Gobjinst_UpdateActorRootDisplacement(struct Actor36 *actor);
extern s32 SetN64_IsModeThirteen(void);
extern void Player_UpdateWorldPlayers(void *world);
extern s32 Playerai_BeginRoundEnd(void *forcePlayerList);



extern void *SoundVoicePool_GetGlobalState(void);









void Scene_UpdateActorsAndRoundState(void *world) {
    s32 count;
    s32 total;
    u32 skip_mask;
    s32 *objects;
    s32 *objectp;
    void *object;
    f32 saved_delta;
    u32 flags;
    s32 object_type;
    u32 remove_mask;
    u32 remove_value;

    count = 0;
    total = ((SceneActorUpdateLists *)world)->count;
    objects = &((SceneActorUpdateLists *)(world))->objects[0];
    if (total > 0) {
        object_type = 2;
        skip_mask = 0x40000000;
        remove_mask = 0x40002000;
        remove_value = 0x2000;
        objectp = objects;
        do {
            void *next_object;

            next_object = (void *)*objectp;
            if (*((SceneNearestActorView *)(next_object))->kind != object_type) {
                goto first_pass_done;
            }
            object = next_object;
            objectp++;
            flags = ((Shared_Actor *)object)->weaponFlags;
            saved_delta = g_frameElapsedTime;
            count++;
            if (!(flags & skip_mask)) {
                Gobjinst_UpdateActorController(object);
            }
            if ((((Shared_Actor *)object)->weaponFlags & remove_mask) == remove_value) {
                Gobjinst_UpdateActorRootDisplacement(object);
            }
            g_frameElapsedTime = saved_delta;
        } while (count < total);
    }

first_pass_done:
    if (SetN64_IsModeThirteen()) {
        Player_UpdateWorldPlayers(&g_playerViewRenderContext);
    }
    if (Playerai_BeginRoundEnd(&g_playerViewRenderContext)) {
        SoundElement_SetMusicPlaybackEnabled(52);
        {
        s32 sw_mode_value = ((GlobalMode *)&g_playerViewRenderContext)->mode;
        if ((unsigned int)sw_mode_value > 4) {
            goto sw_mode_default;
        }
        switch (sw_mode_value) {
        case 0: goto sw_mode_0;
        case 1: goto sw_mode_1;
        case 2: goto sw_mode_0;
        case 3: goto sw_mode_1;
        case 4: goto sw_mode_1;
        }
    }
    do {
        sw_mode_0:
        sw_mode_2:
            Frontend_InitMatchResultsMenu();
            break;
        sw_mode_1:
        sw_mode_3:
        sw_mode_4:
            Achieve_OpenResultsFrontend();
            break;

    sw_mode_default:;
    } while (0);
    }

    if (count < total) {
        objectp = (s32 *)((count * 4) + (s32)objects);
        do {
            object = (void *)*objectp;
            objectp++;
            saved_delta = g_frameElapsedTime;
            Gobjinst_UpdateActorController(object);
            count++;
            if (((Shared_Actor *)object)->weaponFlags & 0x2000) {
                Gobjinst_UpdateActorRootDisplacement(object);
            }
            g_frameElapsedTime = saved_delta;
        } while (count < total);
    }
    SoundVoicePool_RetireFinishedSounds(SoundVoicePool_GetGlobalState());
}

extern Gfx *g_displayListCursor;
extern char g_scene_SwapDistanceSortEntriesEntry[], g_scene_CompareDistanceDescendingEntry[];
typedef struct SortEntry { void *object; f32 distance; } SortEntry;
extern void Gsky_GetObjectPositionAt260(void *, void *);
extern void PpDecom_QuickSortRecords(void *, s32, s32, void *, void *);
extern void Statinst_DrawForGameMode(void *, void *);
struct ObjB; extern void Simple_DrawCachedModel(struct ObjB *obj);
extern void Gobjinst_DrawVisibleCachedActor(void *, void *);
/* Draws a world's scene objects back to front: emits the world's static display list if there is one, then
 * measures each object's squared distance to the camera (offset by a jittered vector from Gsky_GetObjectPositionAt260De),
 * sorts the list with PpDecom_QuickSortRecords and draws each object by its kind (0 actor, 1 prop, 3 effect). */
#include "COMMON/WORLD.H"
#include "COMMON/LEVEL_ACTOR.H"
#include <PR/gbi.h>
void Scene_DrawTransparentObjects(Shared_World *world, void *camera) {
    LevelActor *object;
    SortEntry entries[2048];
    CVector3 jitter;
    s32 count;
    s32 i;
    f32 ox;
    f32 oy;
    f32 oz;
    if ((void *)world->counter124 != 0) {
        gSPDisplayList(g_displayListCursor++, (void *)world->counter124);
    }
    count = world->drawableCount;
    if (count == 0) {
        return;
    }
    gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RNX, FRUSTRATIO_1);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RNY, FRUSTRATIO_1);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RPX, (u16)-FRUSTRATIO_1);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RPY, (u16)-FRUSTRATIO_1);
    Gsky_GetObjectPositionAt260(&jitter, camera);
    ox = jitter.x * -2.0f;
    Gsky_GetObjectPositionAt260(&jitter, camera);
    oy = jitter.y * -2.0f;
    Gsky_GetObjectPositionAt260(&jitter, camera);
    oz = jitter.z * -2.0f;
    for (i = 0; i < count; i++) {
        f32 x;
        f32 y;
        f32 z;
        object = world->drawables[i];
        switch (object->kind) {
        case 0:
            x = ((ObjA *)object)->bounds.min.x + ((ObjA *)object)->bounds.max.x + ox;
            y = ((ObjA *)object)->bounds.min.y + ((ObjA *)object)->bounds.max.y + oy;
            z = ((ObjA *)object)->bounds.min.z + ((ObjA *)object)->bounds.max.z + oz;
            break;
        case 1:
        case 3:
        default:
            x = object->position0.x + object->position0.x + ox;
            y = object->position0.y + object->position0.y + oy;
            z = object->position0.z + object->position0.z + oz;
            break;
        }
        entries[i].object = object;
        entries[i].distance = x * x + y * y + z * z;
    }
    PpDecom_QuickSortRecords(entries, count, 8, g_scene_CompareDistanceDescendingEntry, g_scene_SwapDistanceSortEntriesEntry);
    Geometry_BeginModelBatch();
    for (i = 0; i < count; i++) {
        object = entries[i].object;
        switch (object->kind) {
        case 0:
            Statinst_DrawForGameMode(object, camera);
            break;
        case 3:
            Simple_DrawCachedModel(object);
            break;
        case 1:
            Gobjinst_DrawVisibleCachedActor(object, camera);
            break;
        }
    }
    Geometry_FlushModelBatch();
}


#include "COMMON/APPROACHLOCATION.H"
#include "COMMON/WORLD.H"
#include <ultra64.h>
f32 Region_GetPolygonHeight(Node75 *node, f32 x, f32 z);
f32 Graphu64_GetTrianglePlaneHeight(Node75 *node, f32 x, f32 z);

/* The floor polygon under pos: a volume polygon (flag 0x40) that holds pos, else the one nearest in height. */
/* Finds the containing solid volume, or the nearest floor polygon, as a legacy 32-bit handle. */
s32 Scene_FindFloorPolygon(Shared_World *world, CVector3 *pos) {
    Node75 *polys;
    FloorPolygonTable *polygonTable;
    FloorGrid *grid;
    FloorCell *cell;
    FloorCell *cells;
    Node75 *poly;
    Node75 *best;
    f32 bestDist;
    f32 floor;
    f32 ceiling;
    f32 x;
    f32 z;
    f32 dist;
    s32 cellCount;
    s32 index;
    s32 i;
    u32 j;
    if (g_screenImageResourcesEnabled == 0) {
        return 0;
    }
    polygonTable = SetN64_GetPackSection(world->modelSections, 2);
    polys = polygonTable->polygons;
    index = 0;
    i = 0;
    bestDist = 0.0f;
    best = NULL;
    grid = SetN64_GetPackSection(world->modelSections, 3);
    cellCount = grid->cellCount;
    cells = grid->cells;
    if (cellCount > 0) {
        do {
            cell = &cells[i];
            x = pos->x;
            if (!(cell->bounds.minX <= x && x <= cell->bounds.maxX)) goto skip_cell;
            z = pos->z;
            if (!(cell->bounds.minZ <= z && z <= cell->bounds.maxZ)) goto skip_cell;
            j = 0;
            if (cell->count != 0) {
                /* Preserve the index-first address add emitted by the original compiler. */
                poly = polys - -index;
                do {
                    if (Region_IsPointInTriangleXZ(poly, pos->x, pos->z) != 0) {
                        floor = Region_GetPolygonHeight(poly, pos->x, pos->z);
                        if (poly->flags & 0x40) {
                            ceiling = Graphu64_GetTrianglePlaneHeight(poly, pos->x, pos->z);
                            if (floor <= pos->y && pos->y <= ceiling) {
                                return (s32)poly;
                            }
                        } else {
                            dist = pos->y - floor;
                            if (dist < 0.0f) {
                                dist = -dist;
                            }
                            if (best == NULL || dist < bestDist) {
                                best = poly;
                                bestDist = dist;
                            }
                        }
                    }
                    poly++;
                    index++;
                } while (cell->count > ++j);
            }
            goto advance_cell;
        skip_cell:
            index += cell->count;
        advance_cell:
            i++;
        } while (i < cellCount);
    }
    return (s32)best;
}
