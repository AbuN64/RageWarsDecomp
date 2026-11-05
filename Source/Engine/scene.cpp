#include "Common/packed_callback_symbols.h"
#include "Common/packed_callback.h"
#include "Cache/cache_allocateresourceat.h"
#include "Common/game_session.h"
#include "Common/objb.h"
#include "Engine/scene.h"
#include "Common/Lone/screen_image_resources_enabled.h"
#include "include_asm.h"
#include "Common/scene_switch.h"
#include "Common/scene_frame_and_effect_updates.h"
#include "Common/match_settings.h"
#include "Common/menuselectionmessage.h"
#include "types.h"
#include "Common/world_scene.h"
#include "Common/resident_event_handler.h"
#include "Common/frontend_clock_state.h"
#include "Common/menulistscreen.h"
#include "Achieve/achieve_openresultsfrontend.h"
#include "Render/effect_pool_operations.h"
#include "Scene/scene_updateanddrawworld.h"
#include "Engine/scene_loadlevelresources.h"
#include "Engine/scene_grid_and_geometry_operations.h"
#include "Weapons/player_updatefragtagselection.h"
#include "Render/setn64_getpacksection.h"
#include "Voice/voice.h"
#include "Ai/Player/player_getammocapacity.h"
#include "Engine/gregion.h"
#include "Engine/Instance/gobjinst_getactoroffsetpositionandmodel.h"
#include "Gobjinst/gobjinst_buildactorpose.h"
#include "Graphu64/graphu64_buildlookatmatrix.h"
#include "Gsky/gsky_copyobjectposition.h"
#include "Menu/Items/Scene/scene_buildcachedgeometry.h"
#include "Menu/Items/Scene/scene_drawtransparentobjects.h"
#include "Ppdecom/ppdecom_quicksortrecords.h"
#include "Engine/Instance/gobjinst.h"
#include "Render/setn64_updatefadetransition.h"
#include "Ai/Player/player_buildplayerviewtransform.h"
#include "Engine/Audio/voice.h"
#include "Common/sessionhandlerrow.h"
#include "Common/world.h"
#include "Common/level_actor.h"
#include <PR/gbi.h>
#include "Common/approachlocation.h"
#include <platform_sdk.h>
#include "Engine/Instance/simpinst.h"
#include "Common/rendercounters.h"
#include "Common/navigation_graph.h"
#include "Common/viewflags.h"
#include "Common/menu_match_globals.h"
#include "LIBC.H"
#include "Common/Lone/g_currentstagepreset.h"
#include "Common/cache_releaseresource.h"
#include "Common/shared_gameslot.h"
#include "Common/runtime_declarations.h"
#include "Common/trigger_and_float_value_operations.h"
#include "Scene/sceneprimaryactors.h"
#include "Common/output.h"
#include "Common/navigation_node_and_route_views.h"
#include "Common/integerstate2c.h"
#include "Common/aiprofile.h"
#include "Common/triple.h"
#include "Common/heap_arena_entry.h"
#include "Common/sharedplayer.h"
#include "Common/selectionscreenstate.h"
#include "Ai/Nav/portal_linknavigationobjects.h"
#include "Ai/Nav/portal_initsearchnode.h"
#include "Ovlgame/scene_dispatchandrecyclequeuedtriggers.h"
#include "Engine/Unicol/collide.h"
#include "Ovlgame/ovlgame_initializedynamiclightpool.h"
#include "Common/localdecoderange.h"
#include "Scene/simple_instance_record.h"
#include "Common/propgeometry.h"
#include "Common/particle_lighting.h"
#include "Common/ppdecom_unpackresource.h"
#include "Common/gameplay_camera.h"
#include "Common/shared_optionsscreen.h"
#include "Common/animation_pool.h"
#include "Ai/Player/playerai_findtransientplayer.h"
#include "Audio/voice.h"
#include "Batch/batch.h"
#include "Camera/camera.h"
#include "Engine/Cache/cache.h"
#include "Engine/Cache/list.h"
#include "Engine/session.h"
#include "Engine/visdata_decoderegiongrid.h"
#include "Frontend/player.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#include "Gobjinst/gameobject_getactorheight.h"
#include "Menu/Items/Scene/grid_index_and_visibility_text.h"
#include "Menu/Items/Scene/scene_loadlevelresources.h"
#include "Menu/Items/Scene/scene_relocateparticleeffectdata.h"
#include "Menu/Items/Scene/scene_updatependingobjects.h"
#include "Menu/Items/Scene/s_skylayerstext.h"
#include "Menu/Items/Scene/s_visibilitytext.h"
#include "Ovlgame/effect.h"
#include "Ovlgame/hud.h"
#include "Ovlgame/ovlgame_initializeplayerpool.h"
#include "Pools/pools.h"
#include "Scene/scene_unpackvisibilitygeometry.h"
#include "Source/ovlgame.h"
#include "Engine/cache.h"
#include "Engine/Cache/decmprsr.h"
#include "Ui/X_files/x_plus.h"
#include "Onscrn/onscreen_drawscaledmaskedtilegrid.h"
#include "Menu/track_angles.h"
#include "Engine/Instance/statinst.h"
#include "Engine/lighting.h"
#include "Engine/Instance/insthdr.h"
#include "Camera/gsky.h"
#include "Engine/scene_findtrackedactors.h"
#include "Render/timed_session_transitions.h"
#include "Engine/geometry.h"
#include "Ai/Nav/portal.h"
#include "Engine/animpool.h"
#include "Common/resourcelockstate.h"
#include "Common/globals.h"
#include "Scene/cache_requestresource.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Scene/cache_allocateresourceat.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Common/actor_definition.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
#include "Gsky/gsky_findscreenmessage.h"
#include "Statinst/statinst_acquiregeometry.h"
#include "Common/level_goal.h"
#include "Common/ballisticparams.h"
#include "Fx/normalize_vector.h"
#include "Weapons/actor_requestactorstate.h"
#include "Common/playerprofiles.h"
#include "Engine/Cinema/cinema.h"
#include "Actionai/action_updatebreakableproximity.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Gsky/sky_postscaledscreenmessage.h"
#include "Engine/link.h"
#include "Ui/X_files/x_stdio.h"
#include "ai.h"
#include "Common/player_join_requests.h"
#include "Common/object_instance_transform_and_render_views.h"
#include "Common/colorentry.h"
#include "Engine/particle.h"
#include "Common/menu_text.h"
#include "Common/results_text.h"
#include "Common/vector4f.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Gobjinst/gameobject_loadmodel.h"
#include "Common/worldsortentry.h"
#include "Common/track_spline.h"
#include "Engine/defs.h"
#include "Menu/Items/Scene/scene_setlevelactorstatebit.h"
#include "Common/packed.h"
#include "Link/link_dispatchmatchingtriggers.h"
#include "Menu/Items/Scene/scene_findactortriggerrange.h"
#include "Common/weapon_screen_message_operations.h"
#include "Engine/scene_sampleworldlighting.h"
#include "Common/gameplay_reactions.h"
#include "Cbarrel/barrel_spawnflaggedeffects.h"
#include "Menu/Items/Scene/scene_registeractorinscenelists.h"
#include "Ai/cbarrel.h"
#include "Common/multiplayeroptions.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Common/animationtriggerdefinition.h"
#include "Engine/scene_drawtransitioncoloroverlay.h"
#include "Setn64/setn64_drawcolorrectangle.h"
#include "Engine/rumble.h"
#include "Common/unresolved_word_access_set.h"
#include "Common/unresolved_word_accesses.h"
#include "Common/manager.h"
#include "Scene/scene_findtrackedactors.h"
#include "SCHED/sched_runeventloopus.H"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Data/rest_source_records.h"
#include "Data/Ovl1_d/nav_initvisiblepursuit.h"
#include "Data/Ovl1_d/addrlow_nav_updatevisiblepursuit.h"
#if defined(VERSION_US)
#include "Common/boot_memory_and_thread_boundaries.h"
#endif
#if defined(VERSION_US)
#include "Sched/sched_handleretrace.h"
#endif
#if defined(VERSION_US)
#include "Sched/sched_handlerspcompletion.h"
#endif
#if defined(VERSION_US)
#include "Sched/sched_handletaskcommands.h"
#endif
#if defined(VERSION_US)
#include "Common/runtime_declarations.h"
#endif
#if defined(VERSION_US)
#include "Frontend/screen.h"
#endif
#if defined(VERSION_US)
#include "Engine/Audio/T2soundelement/sound_context_control.h"
#endif
#if defined(VERSION_US)
#include "Engine/Audio/voice.h"
#endif
#if defined(VERSION_US)
#include "Voice/voice.h"
#endif
#include <PR/R4300.h>
#include "System/engine_data_source.h"
#include "Setn64/setn64_setuploadingbackdrop.h"
#if defined(VERSION_US)
#include "Engine/session.h"
#endif
#if defined(VERSION_US)
#include "Engine/visdata.h"
#include "Ai/Player/player_model_and_held_weapon_rendering.h"
#include "Ai/Playerai/playerai_playerai.h"
#include "Engine/Instance/Statinst/statinst.h"
#endif

/* SCENE_DRAWTRANSPARENTOBJECTS.CPP */

void Scene_UpdateAndDrawWorld(void *world) {
    Shared_World *state;
    Shared_Game *input;
    s32 oldFlags;

    state = world;
    input = &g_gameSettings;
    oldFlags = g_litGeometryResourceKeyFlags;
    g_litGeometryResourceKeyFlags = input->lightingGamma;
    if (input->flags & 0x4000) {
        g_litGeometryResourceKeyFlags |= 0x100;
    }
    if (input->flags & 0x8000) {
        g_litGeometryResourceKeyFlags |= 0x200;
    }
    if (oldFlags != g_litGeometryResourceKeyFlags) {
        g_litGeometryResourceKeysChanged = 1;
        Cache_SetResourceActivityState(8);
    } else {
        g_litGeometryResourceKeysChanged = 0;
    }

    Scene_UpdateSelectionTransition(state);
    Scene_ClearSceneObjectCounts(state);
    state->cachedDisplayLists[0] = 0;
    state->cachedDisplayLists[1] = 0;
    Map_ResetFramePool(&state->matrixPool);
    Cache_MarkResourceInUse(0, state->resource);
    {
        void *manager;

        manager = &g_gameSession.hud.actors;
        Fx_ResetRibbonVertexPool(manager);
        Playerai_RotatePlayerPoseBuffers(&g_playerViewRenderContext);
        Scene_UpdateActorVisibility(state);
        Scene_RequestVisibleGridSections(state);
        Scene_CollectVisibleEffects(state);

        if ((state->frozen == 0) && (g_frontendScreenStatus.status[7] == 0)) {
            Fx_UpdateEffectLists(manager);
            Scene_UpdateActorsAndRoundState(state);
            SetN64_UpdateEffectPool(&state->effectSlots);
            state->elapsed += g_frameElapsedTime * g_sceneElapsedTimeScaleDe;
            Scene_UpdateTriggerTimers(state);
        }
    }

    Particle_UpdateSystem(&state->particles);
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




extern void Gobjinst_UpdateActorRootDisplacement(struct Actor36 *actor);
extern s32 SetN64_IsModeThirteen(void);















void Scene_UpdateActorsAndRoundState(Shared_World *world) {
    s32 count;
    s32 total;
    u32 skipMask;
    LevelActor **objects;
    LevelActor **objectp;
    LevelActor *object;
    f32 savedDelta;
    u32 flags;
    s32 objectType;
    u32 removeMask;
    u32 removeValue;

    count = 0;
    total = world->registeredCount;
    objects = &world->registered[0];
    if (total > 0) {
        objectType = 2;
        skipMask = 0x40000000;
        removeMask = 0x40002000;
        removeValue = 0x2000;
        objectp = objects;
        do {
            LevelActor *nextObject;

            nextObject = *objectp;
            if (nextObject->definition->kind != objectType) {
                goto first_pass_done;
            }
            object = nextObject;
            objectp++;
            flags = (object)->flags;
            savedDelta = g_frameElapsedTime;
            count++;
            if (!(flags & skipMask)) {
                Gobjinst_UpdateActorController(object);
            }
            if (((object)->flags & removeMask) == removeValue) {
                Gobjinst_UpdateActorRootDisplacement(object);
            }
            g_frameElapsedTime = savedDelta;
        } while (count < total);
    }

first_pass_done:
    if (SetN64_IsModeThirteen()) {
        Player_UpdateWorldPlayers(&g_playerViewRenderContext);
    }
    if (Playerai_BeginRoundEnd(&g_playerViewRenderContext)) {
        SoundElement_SetMusicPlaybackEnabled(52);
        {
        s32 swModeValue = ((GlobalMode *)&g_playerViewRenderContext)->mode;
        if ((unsigned int)swModeValue > 4) {
            goto sw_mode_default;
        }
        switch (swModeValue) {
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
            object = *objectp;
            objectp++;
            savedDelta = g_frameElapsedTime;
            Gobjinst_UpdateActorController(object);
            count++;
            if ((object)->flags & 0x2000) {
                Gobjinst_UpdateActorRootDisplacement(object);
            }
            g_frameElapsedTime = savedDelta;
        } while (count < total);
    }
    SoundVoicePool_RetireFinishedSounds(SoundVoicePool_GetGlobalState());
}

typedef struct SortEntry { void *object; f32 distance; } SortEntry;


/* Draws a world's scene objects back to front: emits the world's static display list if there is one, then
 * measures each object's squared distance to the camera (offset by a jittered vector from Gsky_CopyObjectPositionDe),
 * sorts the list with PpDecom_QuickSortRecords and draws each object by its kind (0 actor, 1 prop, 3 effect). */
void Scene_DrawTransparentObjects(Shared_World *world, void *camera) {
    LevelActor *object;
    SortEntry entries[2048];
    CVector3 jitter;
    s32 count;
    s32 i;
    f32 ox;
    f32 oy;
    f32 oz;
    if ((void *)world->cachedDisplayLists[1] != 0) {
        gSPDisplayList(g_displayListCursor++, (void *)world->cachedDisplayLists[1]);
    }
    count = world->drawableCount;
    if (count == 0) {
        return;
    }
    gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RNX, FRUSTRATIO_1);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RNY, FRUSTRATIO_1);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RPX, (u16)-FRUSTRATIO_1);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RPY, (u16)-FRUSTRATIO_1);
    Gsky_CopyObjectPosition(&jitter, camera);
    ox = jitter.x * -2.0f;
    Gsky_CopyObjectPosition(&jitter, camera);
    oy = jitter.y * -2.0f;
    Gsky_CopyObjectPosition(&jitter, camera);
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
            Statinst_DrawForGameMode(object);
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
                /* The index is added to the base address before the offset. */
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

/* SCENE_LOADLEVELRESOURCES.CPP */

/* Collects up to sixteen switch objects (descriptor type 0xD) of a world into its switch list, first syncing each one's flag 4 with the switch table g_currentStagePreset when its kind is 0xD34 to 0xD37: model 0xD2B follows table byte 1, models 0xD2C to 0xD2E follow their own table byte, and any other model clears the flag; the flag is set when the byte is zero. */

void Scene_CollectLevelSwitches(Shared_World *world) {
    LevelActor *object;
    SceneSwitchDescriptor *descriptor;
    s32 found;
    s32 i;

    found = 0;
    object = world->actors;
    world->count = 0;
    for (i = 15; i >= 0; i--) {
        world->objects[i] = 0;
    }
    for (i = 0; i < world->actorCapacity; object++, i++) {
        descriptor = (SceneSwitchDescriptor *)object->definition;
        if (descriptor->type == 13) {
            if (g_currentStagePreset != 0 && (unsigned)(descriptor->kind - 3380) < 4) {
                switch (descriptor->model) {
                case 3371:
                    if (((u8 *)g_currentStagePreset)[1] == 0) {
                        descriptor->flags |= 4;
                    } else {
                        descriptor->flags &= ~4;
                    }
                    break;
                case 3372:
                case 3373:
                case 3374:
                    if (((u8 *)g_currentStagePreset)[((SceneSwitchDescriptor *)object->definition)->model - 3370] == 0) {
                        ((SceneSwitchDescriptor *)object->definition)->flags |= 4;
                        break;
                    }
                default:
                    ((SceneSwitchDescriptor *)object->definition)->flags &= ~4;
                    break;
                }
            }
            world->objects[found] = object;
            found++;
        }
        if (found >= 16) {
            break;
        }
    }
    world->count = found;
}

/* Unknown data types are explicit unresolved contracts, never guessed s32. */


struct CNavData_t; extern void Portal_AssignPlatformEndpoints(struct CNavData_t *graph);
struct CNavData_t; extern s32 Portal_FindNearestPointIndex(struct CNavData_t *pointSet, void *point);
extern void * Playerai_GetPlayerByIndex();


extern void **Cache_AllocateResource(s32, s32, s32, char *);
extern void Cache_DrainAndCompactResources(s32);


extern s32 Cache_WaitForResourceLoads(struct ResourceLoadWorker *resourceLoadWorker);

extern void Scene_ShowResultsGoal(void);

extern void Scene_CopyLevelName(struct Shared_World *world, s32 type, void *levelName, s32 maximumBytes);

extern void Scene_UnlockActiveSectionResources(struct Shared_World *owner);
extern void Scene_ResetTransitionViewport(void);
struct Shared_World; extern void Scene_ReleaseCachedLevelData(struct Shared_World *world);

extern s32 XPlus_NextRandomInteger();
extern void OnScreen_StartFirstStatusBar();

extern void Menu_TriggerTrackEvent(int event);













extern unsigned char g_cResource_UnpackRequestEntry[];
extern unsigned char g_sceneLinksLoaderEntry[];
extern unsigned char g_sceneCollisionLoaderEntry[];
extern unsigned char g_sceneAnimatedInstancesLoaderEntry[];
extern unsigned char g_sceneLevelPathsLoaderEntry[];

extern unsigned char g_spatialSoundPoolNodes[];



extern const unsigned char s_matricesText[];                          /* unable to generate initializer: unknown type; const */

                          /* unable to generate initializer: unknown type; const */
/* unable to generate initializer: unknown type; const */
                          /* unable to generate initializer: unknown type; const */
/* unable to generate initializer: unknown type; const */
                          /* unable to generate initializer: unknown type; const */
/* unable to generate initializer: unknown type; const */
/* unable to generate initializer: unknown type; const */
/* unable to generate initializer: unknown type; const */
/* unable to generate initializer: unknown type; const */
/* unable to generate initializer: unknown type; const */
/* unable to generate initializer: unknown type; const */
/* unable to generate initializer: unknown type; const */
                          /* unable to generate initializer: unknown type; const */
/* unable to generate initializer: unknown type; const */
/* const */

       /* const */
/* const */

/* const */

/* Initializes scene resources, actors, and game mode state. */
void Scene_LoadLevelResources(SceneResourceStateView *table, s32 target, s32 allowTransition) {
    struct SceneResourceStateView *state = table;
    s32 *unusedPointer3;
    struct CacheResourceNode *resourceResult;
    s32 actorCount;
    s32 unusedInteger4;
    s32 previousStageId;
    s32 resourceCount;
    s32 navigationPointCount;
    s32 primaryDefinitionType;
    s32 secondaryDefinitionType;
    s32 resourceKey;
    s32 sceneDirectoryEntry;
    s32 visibilityResourceKey;
    s32 levelCount;
    s32 stageIdForFlags;
    s32 stageIdForPoolSize;
    s32 unusedInteger5;
    s32 actorScanCursor;
    s32 i;
    s32 j;
    s32 count;
    s32 kindActor;
    s32 kind654;
    s32 kind653;
    s32 kind655;
    s32 secondType3;
    s32 secondType10;
    s32 secondKindBd6;
    s32 secondKind64e;
    s32 headerCopy0;
    s32 headerCopy1;
    s32 headerCopy2;
    s32 headerCopy3;
    s32 headerCopy4;
    s32 headerCopy5;
    NavigationSearchNode *record;
    s32 loopBuffer;
    s32 actorByteOffset;
    s32 actorIndex;
    s32 k;
    s32 initializationIndex;
    s32 unusedInteger6;
    s32 finalActorByteOffset;
    s32 transitionAllowed;
    s32 levelSelection;
    s32 kind656;
    s32 hasSelectedActorCapacity;
    s32 primarySlotByteOffset;
    s32 secondarySlotByteOffset;
    s32 hasSecondaryActorCapacity;
    s32 actorIterationIndex;
    s32 actorKindBd7;
    s32 firstActorKind;
    s32 actorType3;
    s32 unusedInteger7;
    s32 kind;
    u8 statusBarKind;
    void **sceneResourceHandle;
    void **levelInfoHandle;
    void **navigationPointsHandle;
    void **navigationLinksHandle;
    void **navigationVisionHandle;
    void **skyLayersHandle;
    void **collisionHandle;
    void **gridBoundsHandle;
    AiProfile *playerHudProfile;
    void *unusedPointer8;
    void *unusedPointer9;
    void *group;
    NavigationBuffer *navigationPoints;
    NavigationBuffer *navigationLinks;
    NavigationBuffer *navigationVision;
    LevelActor *primaryActor;
    void *levelActor;
    LevelActor *scene_actor_ptr;
    void *playerProfile;
    struct SceneResourceSixWordRecord *visibilityHeader;
    void *skyLayerTable;
    struct ModelBlend *primaryActorDefinition;
    struct ModelBlend *secondaryActorDefinition;
    void *unusedPointer1;
    void *selectedActorSlot;
    u16 *secondaryActorKind;
    LevelActor *secondaryActor;
    void *unusedPointer2;
    struct Player *playerActor;
    void *resetCursor;

    levelSelection = target;
    (((struct Shared_World *)(table))->minimumCollisionY) = k_initialMinimumCollisionY;
    transitionAllowed = allowTransition;
    if ((((struct Shared_World *)(table))->level) != -1) {
        Scene_DispatchAndRecycleQueuedTriggers(table);
    }
    (((struct Shared_World *)(table))->sceneLoadResetState) = 0;
    if ((Cinema_IsSequenceActive() == 0) && (transitionAllowed != 0) && ((((struct Shared_World *)(table))->selectionFlags) != 0) && (g_gameSettings.counters.transitionActive == 0)) {
        Scene_ResetTransitionViewport();
        previousStageId = (((struct Shared_World *)(table))->selectionValues[0]);
        if ((u32) (previousStageId - 3010) < 351U) {
            Menu_TriggerTrackEvent(((previousStageId - 3010) / 10) + 601);
        }
        Scene_ShowResultsGoal();
    }
    Scene_UnlockActiveSectionResources(table);
    (((struct Shared_World *)(table))->mode) = 0;
    Cache_WaitForResourceLoads(&g_resourceCacheWorker);
    Scene_ReleaseCachedLevelData(table);
    Cache_DrainAndCompactResources(0);
    if ((((struct Shared_World *)(table))->level) != -1) {
        Scene_FreeSceneResources(table);
    }
    Cache_DrainAndCompactResources(0);
    g_gameLoopFrameCount = 0;
    Cache_SetResourceActivityState(8);
    Scene_ClearSceneObjectCounts(table);
    Batch_InitSlotPool(&((struct Shared_World *)table)->particles, *(((struct Shared_World *)(table))->slotPoolDefinition));
    initializationIndex = 0;
    Effect_InitEffectPool(&((struct Shared_World *)table)->effectSlots);
    Ovlgame_InitializeSceneEffectPool(&((struct Shared_World *)table)->sceneEffects);
    Hud_InitializeWorldActorPools(&g_gameSession.hud.actors);
    CCollision_Initialize();
    Ovlgame_InitializeDynamicLightPool(&((struct Shared_World *)table)->dynamicLightPool);
    SoundVoicePool_Initialize(&g_soundVoicePoolGlobalState, &g_spatialSoundPoolNodes, 15);
    Hud_StartPanelMovers(&g_gameSession.hud);
    do {
        playerActor = Playerai_GetPlayerByIndex(&g_playerViewRenderContext, initializationIndex);
        if (playerActor != 0) {
            playerProfile = playerActor->profile;
            if ((((AiProfile *)playerProfile)->loadFlagFirst == 1) && (((AiProfile *)playerProfile)->sessionApplied == 1)) {
                Nav_ResetPlayerState((s32 *)playerActor->controller);
            }
            if ((((CGameStatus *)(&g_matchRoundCounters))->enabled) != 0) {
                playerHudProfile = playerActor->profile;
                statusBarKind = (((AiProfile *)(playerHudProfile))->enabled);
                if (statusBarKind != 0) {
                    if (statusBarKind == 1) {
                        OnScreen_StartFirstStatusBar(&g_gameSession.hud, playerActor, &((AiProfile *)playerHudProfile)->name);
                    } else if (statusBarKind == 2) {
                        OnScreen_StartSecondStatusBar(&g_gameSession.hud, playerActor, &((AiProfile *)playerHudProfile)->name);
                    }
                    if (playerActor->profile->character == 11) {
                        OnScreen_StartFirstStatusBar(&g_gameSession.hud, playerActor, g_firstStatusBarTarget);
                    }
                }
            }
        }
        initializationIndex += 1;
    } while (initializationIndex < 8);
    levelCount = *(((struct Shared_World *)(table))->resourceDirectory);
    if (levelCount < levelSelection) {
        levelSelection = levelCount - 1;
        transitionAllowed = 0;
    }
    (((struct Shared_World *)(table))->level) = levelSelection;
    if (transitionAllowed == 0) {
        (((struct Shared_World *)(table))->selectionFlags) = 0;
    }
    Scene_CopyLevelName(table, levelSelection, &((struct Shared_World *)table)->levelName, 63);
    stageIdForFlags = (((struct Shared_World *)(table))->selectionValues[0]);
    if (stageIdForFlags < 7402) {
        if (stageIdForFlags < 7400) {
            if (stageIdForFlags != 0x1BBC) {
                if (stageIdForFlags < 7101) {
                    if (stageIdForFlags == 0x123A) {
                        goto scene_flag_on;
                    }
                    goto scene_flag_off;
                } else if (stageIdForFlags != 0x1C20) {
                    if (stageIdForFlags == 0x1C84) {
                        goto scene_flag_on;
                    }
                    goto scene_flag_off;
                }
            }
        }
    } else {
        if (stageIdForFlags < 7500) {
            goto scene_flag_off;
        }
        if (stageIdForFlags >= 7502) {
            if (stageIdForFlags >= 7603) {
                goto scene_flag_off;
            }
            if (stageIdForFlags < 7601) {
                goto scene_flag_off;
            }
        }
    }
scene_flag_on:
    (((struct Shared_World *)(table))->visibilityEnabled) = 1;
    goto scene_flag_done;
scene_flag_off:
    (((struct Shared_World *)(table))->visibilityEnabled) = 0;
scene_flag_done:
    stageIdForPoolSize = (((struct Shared_World *)(table))->selectionValues[0]);
    if (stageIdForPoolSize < 7402) {
        if (stageIdForPoolSize < 7400) {
            if (stageIdForPoolSize != 7100) {
                if (stageIdForPoolSize < 7101) {
                    count = 800;
                    if (stageIdForPoolSize == 4666) {
                        goto scene_size_c80;
                    }
                    goto scene_size_done;
                }
                if (stageIdForPoolSize == 7200) {
                    goto scene_size_c80;
                }
                count = 800;
                if (stageIdForPoolSize == 7300) {
                    goto scene_size_c80;
                }
                goto scene_size_done;
            }
        }
        goto scene_size_c80;
    }
    if (stageIdForPoolSize == 7601) {
        goto scene_size_4b0;
    }
    if (stageIdForPoolSize < 7602) {
        if (stageIdForPoolSize < 7502) {
            count = 800;
            if (stageIdForPoolSize < 7500) {
                goto scene_size_done;
            }
            goto scene_size_c80;
        }
        goto scene_size_320;
    }
    count = 800;
    if (stageIdForPoolSize == 7602) {
        goto scene_size_c80;
    }
    goto scene_size_done;
scene_size_c80:
    count = 3200;
    goto scene_size_done;
scene_size_4b0:
    count = 1200;
    goto scene_size_done;
scene_size_320:
    count = 800;
scene_size_done:
    if (g_frontendScreenStatus.settings.local != 0) {
        count += 512;
    }
    Cache_DrainAndCompactResources(0);
    resourceResult = Cache_AllocateResource(0, count << 6, 3, &s_matricesText);
    (((struct Shared_World *)(table))->resource) = (s32)resourceResult;
    Batch_InitEntryBatch(&((struct Shared_World *)table)->matrixPool, resourceResult->data, count);
    resourceKey = SetN64_GetDirectoryEntry((((struct Shared_World *)(table))->resourceDirectory), (((struct Shared_World *)(table))->resourceBank), levelSelection);
    (((struct Shared_World *)(table))->levelIndexResourceHandle) = Cache_RequestWordCountedResourcePinned(0, &((struct Shared_World *)table)->sceneResources, resourceKey, g_levelIndexText);
    collisionHandle = Cache_RequestPackSection(0, (((struct Shared_World *)(table))->sceneResources), 1, resourceKey, table, &g_sceneCollisionLoaderEntry, &s_collisionText);
    (((struct Shared_World *)(table))->collisionResourceHandle) = collisionHandle;
    (((struct Shared_World *)(table))->modelSections) = (void *) *collisionHandle;
    gridBoundsHandle = Cache_RequestPackSection(0, (((struct Shared_World *)(table))->sceneResources), 4, resourceKey, table, &g_cResource_UnpackRequestEntry, &g_gridBoundsAndSectionsIndexText);
    (((struct Shared_World *)(table))->gridBoundsResourceHandle) = gridBoundsHandle;
    (((struct Shared_World *)(table))->gridBoundsAndSections) = (void *) *gridBoundsHandle;
    sceneDirectoryEntry = SetN64_GetDirectoryEntry((((struct Shared_World *)(table))->sceneResources), resourceKey, 5);
    (((struct Shared_World *)(table))->sceneDirectoryKey) = sceneDirectoryEntry;
    (((struct Shared_World *)(table))->sceneIndexResourceHandle) = Cache_RequestWordCountedResourcePinned(0, &((struct Shared_World *)table)->sceneIndexData, sceneDirectoryEntry, &g_sceneIndexResourceTag);
    if (*(((struct Shared_World *)(table))->sceneResources) >= 13) {
        visibilityResourceKey = SetN64_GetDirectoryEntry((((struct Shared_World *)(table))->sceneResources), resourceKey, 12);
        (((struct Shared_World *)(table))->visibilityResourceKey) = visibilityResourceKey;
        (((struct Shared_World *)(table))->visibilityResourceHandle) = Cache_RequestWordCountedResourcePinned(0, &((struct Shared_World *)table)->visibilityTable, visibilityResourceKey, &s_visibilityText);
        sceneResourceHandle = Cache_RequestPackSection(0, (((struct Shared_World *)(table))->visibilityTable), 0, (((struct Shared_World *)(table))->visibilityResourceKey), table, 0, &g_visibilityHeaderResourceTag);
        visibilityHeader = *sceneResourceHandle;
        ((struct Shared_World *)table)->visibilityHeader = *visibilityHeader;
        Cache_ReleaseResource(0, sceneResourceHandle);
        if ((((struct Shared_World *)(table))->visibilityHeader.columnCount) != 0 || (((struct Shared_World *)(table))->visibilityHeader.rowCount) != 0) {
            (((struct Shared_World *)(table))->hasVisibilityPayload) = 1;
        } else {
            (((struct Shared_World *)(table))->hasVisibilityPayload) = 0;
        }
    } else {
        (((struct Shared_World *)(table))->hasVisibilityPayload) = 0;
    }
    (((struct Shared_World *)(table))->actorLinksResourceHandle) = Cache_RequestPackSection(0, (((struct Shared_World *)(table))->sceneResources), 7, resourceKey, table, &g_sceneLinksLoaderEntry, &s_linksText);
    (((struct Shared_World *)(table))->levelPathsResourceHandle) = Cache_RequestPackSection(0, (((struct Shared_World *)(table))->sceneResources), 2, resourceKey, table, &g_sceneLevelPathsLoaderEntry, &s_levelPathsText);
    levelInfoHandle = Cache_RequestPackSection(0, (((struct Shared_World *)(table))->sceneResources), 0, resourceKey, table, 0, &s_levelInfoText);
    (((struct Shared_World *)(table))->levelInfoResourceHandle) = levelInfoHandle;
    (((struct Shared_World *)(table))->levelInfo) = (void *) *levelInfoHandle;
    Scene_LoadSceneLight(table);
    resourceCount = *(((struct Shared_World *)(table))->sceneResources);
    g_geometryFogEffectEnabled = ((u8)((struct Shared_World *)table)->levelInfo->lightingFlags >> 2) & 1;
    if (resourceCount >= 9) {
        navigationPointsHandle = Cache_RequestPackSection(0, (((struct Shared_World *)(table))->sceneResources), 9, resourceKey, table, &g_cResource_UnpackRequestEntry, &g_levelNavigationResourceNames);
        (((struct Shared_World *)(table))->navPointsResourceHandle) = navigationPointsHandle;
        navigationPoints = *navigationPointsHandle;
        (((struct Shared_World *)(table))->navigation.points) = (NavigationBuffer *)navigationPoints;
        (((struct Shared_World *)(table))->navigation.m_nNavNodes) = (s32) navigationPoints->count;
        navigationLinksHandle = Cache_RequestPackSection(0, (((struct Shared_World *)(table))->sceneResources), 10, resourceKey, table, &g_cResource_UnpackRequestEntry, &g_navigationLinksResourceName);
        (((struct Shared_World *)(table))->navLinksResourceHandle) = navigationLinksHandle;
        navigationLinks = *navigationLinksHandle;
        (((struct Shared_World *)(table))->navigation.m_pusNavLinks) = (NavigationBuffer *)navigationLinks;
        (((struct Shared_World *)(table))->navigation.m_nNavLinks) = (s32) navigationLinks->count;
        List_InitializeIntrusive(&((struct Shared_World *)table)->navigation.searchNodes, 12, 16);
        navigationPointCount = (((struct Shared_World *)(table))->navigation.m_nNavNodes);
        if (navigationPointCount > 0) {
            record = Cache_AllocateMemory(navigationPointCount * 80);

            initializationIndex = 0;
            if ((((struct Shared_World *)(table))->navigation.m_nNavNodes) > 0) {
                do {
                    Portal_InitSearchNode(record, initializationIndex);
                    List_AppendIntrusive(&((struct Shared_World *)table)->navigation.searchNodes, record);
                    record = (void *)((char *)record + sizeof(NavigationSearchNode));
                } while ((((struct Shared_World *)table)->navigation.m_nNavNodes) > ++initializationIndex);
            }
        }
    }
    if (*(((struct Shared_World *)(table))->sceneResources) >= 12) {
        navigationVisionHandle = Cache_RequestPackSection(0, (((struct Shared_World *)(table))->sceneResources), 11, resourceKey, table, &g_cResource_UnpackRequestEntry, &s_levelNavVisionText);
        (((struct Shared_World *)(table))->navVisionResourceHandle) = navigationVisionHandle;
        navigationVision = *navigationVisionHandle;
        (((struct Shared_World *)(table))->navigation.links) = (NavigationBuffer *)navigationVision;
        (((struct Shared_World *)(table))->navigation.visionCount) = (s32) navigationVision->count;
    }
    skyLayersHandle = Cache_RequestPackSection(0, (((struct Shared_World *)(table))->sceneResources), 6, resourceKey, table, &g_cResource_UnpackRequestEntry, &s_skyLayersText);
    (((struct Shared_World *)(table))->skyLayersResourceHandle) = skyLayersHandle;
    skyLayerTable = *skyLayersHandle;
    (((struct Shared_World *)(table))->skyLayerEntries) = (void *) (((struct StridedTable *)skyLayerTable)->data);
    (((struct Shared_World *)(table))->skyLayerCount) = (s32) (((struct StridedTable *)(skyLayerTable))->count);
    (((struct Shared_World *)(table))->mode) = 1;
    (((struct Shared_World *)(table))->actors) = 0;
    (((struct Shared_World *)(table))->actorCapacity) = 0;
    (((struct Shared_World *)(table))->animatedInstancesResourceHandle) = Cache_RequestPackSection(0, (((struct Shared_World *)(table))->sceneResources), 3, resourceKey, table, &g_sceneAnimatedInstancesLoaderEntry, &s_animatedInstancesText);
    Scene_CollectLevelSwitches(table);

    i = 0;
    actorIterationIndex = 15;

    actorScanCursor = (s32)(((struct Shared_World *)(table))->actors);
    resetCursor = &((struct Shared_World *)table)->selectionClearCursorAnchor;
    (((struct Shared_World *)(table))->specialActorCount) = 0;
    do {
        (((struct Shared_World *)(resetCursor))->specialActors[0]) = 0;
        actorIterationIndex -= 1;
        resetCursor -= 4;
    } while (actorIterationIndex >= 0);

    actorIterationIndex = 0;

    if ((((struct Shared_World *)(table))->actorCapacity) > 0) {
        firstActorKind = 14;
        selectedActorSlot = (void *)(i * sizeof(void *) + (u32)table);
loop_81:
        if (((LevelActor *)((void *)actorScanCursor))->definition->kind == firstActorKind) {
            (((struct Shared_World *)(selectedActorSlot))->specialActors[0]) = (struct LevelActor *)actorScanCursor;
            selectedActorSlot += 4;
            i += 1;
            hasSelectedActorCapacity = i < 16;
        } else {
            hasSelectedActorCapacity = i < 16;
        }
        if (hasSelectedActorCapacity != 0) {
            actorScanCursor = (s32)((void *)((u8 *)actorScanCursor + sizeof(LevelActor)));
            actorIterationIndex += 1;
            if (actorIterationIndex < (((struct Shared_World *)(table))->actorCapacity)) {
                goto loop_81;
            }
        }
    }

    actorIndex = 3;
    scene_actor_ptr = (((struct Shared_World *)(table))->actors);
    actorType3 = 3;
    actorKindBd7 = 3031;
    primarySlotByteOffset = 3 * sizeof(void *);

    (((struct Shared_World *)(table))->specialActorCount) = i;
    g_fragTagObjectiveActor = 0;
    do {
        *(LevelActor **)((u8 *)g_sceneTrackedActors + primarySlotByteOffset) = 0;
        actorIndex -= 1;
        primarySlotByteOffset -= sizeof(void *);
    } while (actorIndex >= 0);
    actorIndex = 0;
    if ((((struct Shared_World *)(table))->actorCapacity) > 0) {
        kindActor = 10;
        kind654 = 1620;
        kind653 = 1619;
        kind655 = 1621;
        kind656 = 1622;
        primaryActor = scene_actor_ptr;
loop_89:
        primaryActorDefinition = (ModelBlend *) primaryActor->definition;
        primaryDefinitionType = primaryActorDefinition->kind;
        if (primaryDefinitionType == actorType3) {
            if (Scene_GetModelIdAtIndex(&g_world, primaryActorDefinition->modelIndex) != actorKindBd7) {
                goto block_108;
            }
            g_fragTagObjectiveActor = primaryActor;
            goto block_109;
        } else {
            if (primaryDefinitionType == kindActor) {
                kind = primaryActor->type;
                if (kind == kind654) {
                    goto actor_kind_654;
                }
                if (kind < 1621) {
                    if (kind == kind653) {
                        goto actor_kind_653;
                    }
                        goto block_108;
                }
                if (kind == kind655) {
                    goto actor_kind_655;
                }
                if (kind == kind656) {
                        goto actor_kind_656;
                }
                goto block_108;
actor_kind_653:
                g_sceneTrackedActors[0] = primaryActor;
                goto block_108;
actor_kind_654:
                g_sceneTrackedActors[1] = primaryActor;
                goto block_108;
actor_kind_655:
                g_sceneTrackedActors[2] = primaryActor;
                goto block_108;
actor_kind_656:
                g_sceneTrackedActors[3] = primaryActor;
            }
block_108:
            primaryActor++;
            scene_actor_ptr += 1;
            actorIndex += 1;
            if (actorIndex >= (((struct Shared_World *)(table))->actorCapacity)) {
                goto block_109;
            }
            goto loop_89;
        }
    } else {
block_109:
        j = 0;
    }

    actorScanCursor = 9;
    secondaryActor = (((struct Shared_World *)(table))->actors);
    secondarySlotByteOffset = 9 * sizeof(void *);

    g_sceneFlagReturnPickupActor = 0;
    do {
        *(LevelActor **)((u8 *)g_sceneSpecialActorTables + secondarySlotByteOffset) = 0;
        actorScanCursor -= 1;
        secondarySlotByteOffset -= sizeof(void *);
    } while (actorScanCursor >= 0);
    actorScanCursor = 0;
    if ((((struct Shared_World *)(table))->actorCapacity) > 0) {
        secondType3 = 3;
        secondKindBd6 = 3030;
        secondType10 = 10;
        secondKind64e = 1614;
        secondaryActorKind = &secondaryActor->type;
loop_114:
        secondaryActorDefinition = (ModelBlend *) ((LevelActor *)((u8 *)secondaryActorKind - (u32)&((LevelActor *)0)->type))->definition;
        secondaryDefinitionType = secondaryActorDefinition->kind;
        if (secondaryDefinitionType == secondType3) {
            if (secondaryActorDefinition->modelIndex == secondKindBd6) {
                g_sceneFlagReturnPickupActor = secondaryActor;
            }
        } else if (secondaryDefinitionType == secondType10) {
            if (*secondaryActorKind == secondKind64e) {
                g_sceneSpecialActorTables[j] = secondaryActor;
                j += 1;
            }
        }
        hasSecondaryActorCapacity = j < 10;
        if (hasSecondaryActorCapacity != 0) {
            secondaryActorKind = (u16 *)((u8 *)secondaryActorKind + sizeof(LevelActor));
            secondaryActor += 1;
            actorScanCursor += 1;
            if (actorScanCursor >= (((struct Shared_World *)(table))->actorCapacity)) {
                goto block_122;
            }
            goto loop_114;
        }
    } else {
block_122:
        g_gameSettings.counters.m_nFragTagSkin = XPlus_NextRandomInteger() % 3;
    }
    (((struct Shared_World *)(table))->mode) = 2;
    Scene_UpdatePendingObjects(table);
    actorCount = (((struct Shared_World *)(table))->actorCapacity);
    actorIndex = (((struct Shared_World *)(table))->createdActorCount);
    (((struct Shared_World *)(table))->mode) = 3;
    if (actorIndex < actorCount) {
        actorByteOffset = actorIndex * sizeof(LevelActor);
        do {
            actorIndex += 1;
            Gobjinst_DispatchActorTypeUpdate(((char *)((struct Shared_World *)(table))->actors) + actorByteOffset);
            actorByteOffset += sizeof(LevelActor);
        } while (actorIndex < actorCount);
    }
    playerActor = g_transientPlayerList.actorList;
    if (playerActor != 0) {

        levelActor = playerActor;
        do {
            Gobjinst_DispatchActorTypeUpdate(levelActor);
            Gobjinst_DispatchActorTypeUpdate(((void *)((u8 *)levelActor + sizeof(LevelActor))));
            (((struct ResourceKeyView *)(((struct Player *)(playerActor))->controller))->key) = Portal_FindNearestPointIndex((struct CNavData_t *)&((struct Shared_World *)table)->navigation, &((struct Player *)playerActor)->pos);
            playerActor = (((struct Player *)(playerActor))->next);
            if (playerActor == 0) {
                break;
            }
            levelActor = playerActor;
        } while (1);
    }
    Scene_DispatchSelectedEntityKinds(table);
    actorCount = (((struct Shared_World *)(table))->actorCapacity);
    k = (((struct Shared_World *)(table))->createdActorCount);
    if (k < actorCount) {
        finalActorByteOffset = k * sizeof(LevelActor);
        do {
            k += 1;

            levelActor = ((char *)((struct Shared_World *)(table))->actors) + finalActorByteOffset;
            Gobjinst_UpdateActorController(levelActor);
            Gobjinst_UpdateActorRootDisplacement(levelActor);
            finalActorByteOffset += sizeof(LevelActor);
        } while (k < actorCount);
    }

    count = (char *)&((struct Shared_World *)table)->navigation.points - (char *)table;
    levelActor = (char *)table + count;
    Portal_LinkNavigationObjects(levelActor);
    Portal_AssignPlatformEndpoints(levelActor);
    (((struct Shared_World *)(table))->mode) = 4;
    Player_RefreshActivePlayerSceneState(&g_playerViewRenderContext);
    group = &g_playerViewRenderContext.object;
    Pools_InitGroupPools(group);
    Camera_UpdateViewportLayoutAndBounds(group);
}

/* Native resident constant storage; absolute access symbols retain their addresses. */

/* Spawns an entity through Link_DispatchTrigger when its bit is set in the current level's placement mask and it either names no flag or its flag in the global flag table g_levelFlagTable is clear. */



void Scene_DispatchEnabledEntityTrigger(Shared_World *world, Entity *entity) {
    s32 index;
    s32 level;
    void *mask;
    unsigned char *bits;
    void *flags;
    s32 flag;
    s32 bit;

    index = entity->index;
    level = world->level;
    mask = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(world->bitSections, 0), level), 2);
    SetN64_GetPackSection(mask, 0);
    SetN64_GetPackSectionSize(mask, 1);
    bits = SetN64_GetPackSection(mask, 1);
    bit = 1 << (index & 7);
    if (bits[index / 8] & bit) {
        if (entity->flag != 0) {
            flag = entity->flag;
            flags = SetN64_GetPackSection(g_world.bitSections, 1);
            SetN64_GetPackSection(flags, 0);
            if (((unsigned char *)SetN64_GetPackSection(flags, 1))[flag] != 0) {
                return;
            }
        }
        Link_DispatchTrigger(entity);
    }
}

/* A resource's block set: the count of blocks and the byte offset of each from the set's start. */

/* A run of equal-sized records: record size, count, then the records. */
typedef struct RecordSet {
    s32 size;
    s32 count;
} RecordSet;

/* A simple (animated, unlit-by-grid) instance as the level resource stores it. */

/* A simple instance in the game: the header's position, its flags and id, and the lighting baked from the level's
 * light volumes. */



#define ALIGN8(size) (((size) + 7) & ~7)

/* Whether the instance's bit is set in the current level's instance mask (section 1 of the level's bit sections).
 * The same body as Scene_TestLevelRecordStateBit; it is inlined here. */
static inline s32 Engine_TestInstanceBit(Shared_World *world, ObjB *instance) {
    s32 index;
    void *sections;
    s32 level;
    void *mask;
    u8 *bits;
    s32 bit;

    index = instance->placementId;
    sections = world->bitSections;
    level = world->level;
    mask = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(sections, 0), level), 1);
    SetN64_GetPackSection(mask, 0);
    SetN64_GetPackSectionSize(mask, 1);
    bits = SetN64_GetPackSection(mask, 1);
    bit = 1 << (index & 7);
    return (bits[index / 8] & bit) != 0;
}

/* Builds a level's placed instances into one pool block of five sections: props (efficient then static records),
 * simple instances (flagged when the level's instance mask has their bit), light volumes, and a copy of the bit set.
 * Each simple instance then takes its lighting from the volumes at half its actor height. */
void Scene_BuildPlacedInstances(Shared_World *world, void ***handle) {
    SceneLightVolume *volumeList[128];
    CVector3 position;
    Pack *bitSet;
    RecordSet *efficientSet;
    RecordSet *simpleSet;
    RecordSet *volumeSet;
    char *base;
    s32 staticCount;
    s32 simpleCount;
    s32 volumeCount;
    s32 staticSize;
    s32 simpleSize;
    s32 volumeSize;
    s32 bitSize;
    PlacedPropRecord *statics;
    ObjB *simples;
    char *segments;
    void **block;
    Pack *source;
    RecordSet *staticSet;
    s32 efficientCount;
    Pack *blocks;
    RecordSet *dst;
    s32 offset;
    s32 n;
    s32 i;
    s32 j;
    s32 k;
    ObjA *props;
    PackedPlacedPropDefinition *efficient;
    CROMSimpleInstance *simpleRecords;
    LightVolumeRecord *volumeRecords;
    SceneLightVolume *volumes;
    void *objects;

    if (Ppdecom_UnpackResource(handle, 1) != 0) {
        source = **handle;
        efficientSet = SetN64_GetPackSection(source, 0);
        efficientCount = efficientSet->count;
        staticSet = SetN64_GetPackSection(source, 1);
        staticCount = staticSet->count;
        staticSize = ALIGN8((efficientCount + staticCount) * sizeof(ObjA) + sizeof(RecordSet));
        simpleSet = SetN64_GetPackSection(source, 2);
        simpleCount = simpleSet->count;
        simpleSize = ALIGN8(simpleCount * sizeof(ObjB) + sizeof(RecordSet));
        volumeSet = SetN64_GetPackSection(source, 3);
        volumeCount = volumeSet->count;
        volumeSize = ALIGN8(volumeCount * sizeof(SceneLightVolume) + sizeof(RecordSet));
        bitSet = SetN64_GetPackSection(source, 4);
        bitSize = ALIGN8(bitSet->count * sizeof(s32) + sizeof(RecordSet));
        block = Cache_AllocResourceBlock(0, handle, staticSize + 24 + simpleSize + volumeSize + bitSize);
        if (block != 0) {
            n = 0;
            offset = 24;
            blocks = *block;
            dst = (char *)blocks + offset;
            blocks->count = n++;
            blocks->offsets[blocks->count] = offset;
            SetN64_TransposeRecords(efficientSet, dst, 1);
            SetN64_TransposeRecords(staticSet, dst, 1);
            (dst)->size = sizeof(ObjA);
            (dst)->count = efficientCount + staticCount;
            efficient = (PackedPlacedPropDefinition *)(efficientSet + 1);
            objects = SetN64_GetPackSection(world->modelSections, 2);
            statics = (PlacedPropRecord *)(staticSet + 1);
            props = (ObjA *)(dst + 8);
            base = (char *)blocks;
            segments = (char *)objects + 8;
            for (i = 0; i < efficientCount; i++) {
                Statinst_InitializePlacedProp(&props[i], &efficient[i],
                                 SetN64_GetDirectoryEntry(world->indexedDirectory, world->indexedBank, efficient[i].id),
                                 segments, world->levelInfo->m_GridDistance);
            }
            for (j = 0; j < staticCount; j++) {
                Statinst_InitPlacedProp(&props[j + efficientCount], &statics[j],
                                 SetN64_GetDirectoryEntry(world->indexedDirectory, world->indexedBank, statics[j].id),
                                 segments);
            }

            offset += staticSize;
            blocks->count = n++;
            blocks->offsets[blocks->count] = offset;
            SetN64_TransposeRecords(simpleSet, base + offset, 1);
            ((RecordSet *)(base + offset))->size = sizeof(ObjB);
            ((RecordSet *)(base + offset))->count = simpleCount;
            simpleRecords = (CROMSimpleInstance *)(simpleSet + 1);
            simples = (ObjB *)(base + offset + 8);
            for (k = 0; k < simpleCount; k++) {
                Simple_InitSimpleInstance(&simples[k], &simpleRecords[k],
                                 SetN64_GetDirectoryEntry(world->indexedDirectory, world->indexedBank, simpleRecords[k].type),
                                 segments);
                if (Engine_TestInstanceBit(world, &simples[k])) {
                    simples[k].flags |= 1;
                }
            }

            offset += simpleSize;
            blocks->count = n++;
            blocks->offsets[blocks->count] = offset;
            SetN64_TransposeRecords(volumeSet, base + offset, 1);
            ((RecordSet *)(base + offset))->size = sizeof(SceneLightVolume);
            ((RecordSet *)(base + offset))->count = volumeCount;
            volumeRecords = (LightVolumeRecord *)(volumeSet + 1);
            volumes = (SceneLightVolume *)(base + offset + 8);
            for (i = 0; i < volumeCount; i++) {
                Lighting_DecodeBoxTransform(&volumes[i], &volumeRecords[i]);
            }

            offset += volumeSize;
            blocks->count = n++;
            blocks->offsets[blocks->count] = offset;
            Libc_CopyBytes(base + offset, bitSet, SetN64_GetPackSize(bitSet));

            blocks->count = n++;
            offset += bitSize;
            blocks->offsets[blocks->count] = offset;

            for (i = 0; i < volumeCount; i++) {
                volumeList[i] = &volumes[i];
            }
            for (k = 0; k < simpleCount; k++) {
                position.x = simples[k].position.x;
                position.y = simples[k].position.y + Gobjinst_GetActorHeight(&simples[k]) * 0.5f;
                position.z = simples[k].position.z;
                Scene_SampleVolumeLighting(volumeList, volumeCount, &position, &simples[k].lights);
            }
        }
        Cache_ReplaceResourceBlock(0, handle, block);
    }
}


typedef struct SceneVisibilitySettings {
    u32 mask;
    u8 reserved04[0x11];
    u8 local;
} SceneVisibilitySettings;

/* Whether the actor's bounding box overlaps the box. */
/* True when the actor's bounds intersect the box on all three axes. */
#define ACTOR_OVERLAPS(actor, box) ((box)->max.x > (actor)->bounds.min.x && \
    (box)->min.x < (actor)->bounds.max.x && \
    (box)->max.z > (actor)->bounds.min.z && \
    (box)->min.z < (actor)->bounds.max.z && \
    (box)->max.y > (actor)->bounds.min.y && \
    (box)->min.y < (actor)->bounds.max.y)

/* Per-frame visibility scan over the world's actors. Rebuilds the lists of registered, interactive, mover, flagged and
 * per-model actors from the actors that are visible this frame (inside the clip box and the camera frustum, or within
 * range for kind 14), copies each actor's visible bit into bit 15 of its flags, then culls the scene's effects. */

void Scene_UpdateActorVisibility(Shared_World *world) {
    SceneVisibilitySettings *settings;
    LevelActor *actors;
    LevelActor *actor;
    GameplayCamera *camera;
    ActorDefinitionHeader *definition;
    Box *clipBox;
    Box *rangeBox;
    s32 end;
    u32 mask;
    s32 i;
    s32 visible;
    s32 cull;

    settings = (SceneVisibilitySettings *)&g_playerViewRenderContext.game.sceneMask;
    mask = settings->mask;
    world->registeredCount = 0;
    world->kind1Count = 0;
    world->flaggedCount = 0;
    Playerai_UpdatePlayerRenderResources((struct CPlayerPool_t *)&g_playerViewRenderContext, world);
    camera = 0;
    if (settings->local == 0) {
        camera = ((MenuMatchGlobals *)&g_playerViewRenderContext.object)->cameras;
    }
    cull = 0;
    if (Cinema_IsSequenceInWindow() == 0) {
        cull = world->visibilityEnabled == 0;
    }
    i = world->createdActorCount;
    end = world->actorCapacity;
    actors = (LevelActor *)world->actors;
    for (; i < end; i++) {
        clipBox = &g_cameraClipBounds;
        rangeBox = &g_cameraVolumeBounds;
        actor = &actors[i];
        if (!(actor->flags & 0x100)) {
            continue;
        }
        definition = actor->definition;
        visible = 0;
        if (definition->gate & mask) {
            if (cull && !(actor->flags & 2) && actor->animationChanged == 0 &&
                !(actor->flags & 0x400) && definition->kind != 3) {
                if (definition->kind == 14) {
                    goto distance_visible;
                }
                if (!InstHdr_CanActorReceiveInteraction(actor)) {
                    if (ACTOR_OVERLAPS(actor, clipBox)) {
                        if (camera != 0) {
                            visible = Visdata_TestBoxAgainstFrustum(camera->clipPlanes, &actor->bounds);
                        } else {
                            visible = 1;
                        }
                    }
                    goto visibility_ready;
                }
            }
            if (definition->kind == 14) {
            distance_visible:
                if (Gsky_GetDistanceTo(camera, &actor->position0) < g_sceneActorVisibilityDistance) {
                    visible = 1;
                }
            } else {
                visible = ACTOR_OVERLAPS(actor, rangeBox);
            }
        }
    visibility_ready:
        if (Cinema_IsSequenceInWindow() && g_playerSequenceWindowEnabled) {
            if (!(definition->gate & 0x200)) {
                visible = 0;
            }
        } else if (!(definition->gate & 0x100) && definition->kind != 11 && definition->kind != 14) {
            visible = 0;
        }
        if (actor->flags < 0) {
            actor->flags |= 0x8000;
        } else {
            actor->flags &= ~0x8000;
        }
        if (visible) {
            actor->flags |= ACTOR_FLAG_VISIBLE;
            if (definition->kind == 14) {
                continue;
            }
            Gobjinst_RotatePoseMatrixBuffers(actor);
            if (InstHdr_CanActorReceiveInteraction(actor) && world->interactiveCount != 512) {
                world->interactive[world->interactiveCount++] = actor;
            }
            if (InstHdr_HasEnabledMotionHooks(actor) && world->moverCount != 128) {
                world->movers[world->moverCount++] = actor;
            }
            if (world->registeredCount < 128) {
                world->registered[world->registeredCount++] = actor;
            }
            if (world->kind1Count < 64 && actor->definition->kind == 1) {
                world->kind1[world->kind1Count] = actor;
                /* bits 8..15 of actionReady (its third byte) hold the kind-1 slot index */
                ((u8 *)&actor->actionReady)[2] = world->kind1Count++;
            }
            if (world->flaggedCount < 32 && (actor->flags & 2)) {
                world->flagged[world->flaggedCount++] = actor;
            }
            if (world->kind5Count < 16 && actor->definition->kind == 5) {
                world->kind5[world->kind5Count++] = actor;
            }
            if (world->model64FCount < 32 && actor->type == 1615) {
                world->model64F[world->model64FCount++] = actor;
            }
            if (actor->type == 1613 && world->model64DCount < 4) {
                world->model64D[world->model64DCount++] = actor;
            }
        } else {
            actor->flags &= 0x7FFFFFFF;
            actor->flags &= ~0x200;
        }
    }
    Animpool_UpdateSceneEffects(&world->sceneEffects, world);
    world->kind1Cursor++;
    if (world->kind1Cursor >= world->kind1Count) {
        world->kind1Cursor = 0;
    }
}

const char s_gridSectionText[] = "grid section";
#undef ACTOR_OVERLAPS



/* Keep this source unit's macros local to its body. */
#undef ACTOR_OVERLAPS
#undef ALIGN8

/* SCENE_BUILDCACHEDGEOMETRY.CPP */

/* Tag of the cell grid packs (the first .rodata of this unit; the items overlay reads it too). */
extern const char s_gridSectionText[];



extern void Cache_LockResource(void *, CacheResourceNode *);

void Scene_RequestVisibleGridSections(Shared_World *world)
{
    s32 xCount, firstX, count;
    WorldSectorExtent *cells;
    GameplayCamera *viewers, *viewer;
    GridAxisSection *axis;
    WorldSectorExtentTable *cellTable;
    f32 *xLow, *xHigh, *zLow, *zHigh;
    WorldSectorExtent *cell;
    CacheResourceNode *resource;
    WorldSector *entry;
    Pack *resourceData;
    s32 zCount, lastX, firstZ, lastZ;
    s32 x, z, row, loaded, size, visible, slot;

    viewers = g_gameplayCameraList.camera;
    if (viewers) {
        firstX = count = 0;
        axis = SetN64_GetPackSection(world->gridBoundsAndSections, 0);
        firstZ=0;
        xLow = axis->coordinates;
        xCount = axis->count;
        axis = SetN64_GetPackSection(world->gridBoundsAndSections, 1);
        xHigh = axis->coordinates;
        lastX = xCount - 1;
        axis = SetN64_GetPackSection(world->gridBoundsAndSections, 2);
        zLow = axis->coordinates;
        zCount = axis->count;
        axis = SetN64_GetPackSection(world->gridBoundsAndSections, 3);
        zHigh = axis->coordinates;
        cellTable = SetN64_GetPackSection(world->gridBoundsAndSections, 4);
        lastZ = zCount - 1;
        cells = cellTable->cells;
        while (firstX < xCount && xHigh[firstX] < g_cameraVolumeBounds.min.x) firstX++;
        while (lastX >= 0 && g_cameraVolumeBounds.max.x < xLow[lastX]) lastX--;
        while (firstZ < zCount && zHigh[firstZ] < g_cameraVolumeBounds.min.z) firstZ++;
        while (lastZ >= 0 && g_cameraVolumeBounds.max.z < zLow[lastZ]) lastZ--;
        entry = world->sectors;
        { s32 focusX,focusZ;
        if (world->hasVisibilityPayload == 1) {
            focusX = (s32)((viewers->position.x - world->visibilityHeader.originX) / world->visibilityHeader.cellX);
            focusZ = (s32)((viewers->position.z - world->visibilityHeader.originZ) / world->visibilityHeader.cellZ);
        } else focusZ = focusX = -1;
        if (focusX < 0 || focusX >= xCount || focusZ < 0 || focusZ >= zCount) world->visibilityValid = 0;
        else {
            world->visibilityValid = 1;
            world->visibilityData = Cache_RequestPackSection(0, world->visibilityTable, focusX + focusZ * xCount + 1,
                world->visibilityResourceKey, world, g_cResource_UnpackRequestEntry, "Vis Info");
            Cache_LockResource(0, world->visibilityData);
            Visdata_DecodeRegionGrid(&world->visibilityGrid, focusX, focusZ, (void *)world->visibilityData->data, &viewers->position);
        }
        }
        z = firstZ;
        if(z<=lastZ) {
        row = z * xCount;
        do {
            for (x = firstX, slot=x+row; x <= lastX; x++,slot=x+row) {
                        cell = &cells[slot];
                if (cell->occupied) continue;
                visible = 0;
                for (viewer = viewers; viewer; viewer = viewer->next) {
                    if (viewer->volumeBounds[0].x < cell->maxX && cell->minX < viewer->volumeBounds[1].x &&
                        cell->maxZ > viewer->volumeBounds[0].z && cell->minZ < viewer->volumeBounds[1].z) {
                        visible = 1;
                        break;
                    }
                }
                if (visible) {
                    loaded = SetN64_LocatePackSection(world->sceneIndexData, world->sceneDirectoryKey, slot, &size);
                    resource = Cache_RequestResource(0, loaded, loaded, size, 8, world,
                                              g_scene_BuildPlacedInstancesEntry, s_gridSectionText, 0);
                    if (resource) {
                        resourceData = (void *)resource->data;
                        if (resourceData->count) {
                            entry->resource = resource;
                            entry->bounds = cell;
                            entry->gridX = x;
                            entry->gridZ = z;
                            entry++;
                            count++;
                            if (count == 128) goto finished;
                        } else Cache_UnlockResource(0,(void *)resource);
                    }
                }
            }
            row+=xCount; z++;
        } while(z<=lastZ);
        }
finished:
        world->sectorEntryCount = count;
        world->sectorCount = count;
    }
}

/* One geometry vertex of a prop's collision mesh (stride from its section header). */
typedef struct ScenePoint { s16 x, y, z; } ScenePoint;
extern Gfx *g_displayListCursor;
extern void **Cache_AllocateResource(s32, s32, s32, char *);
extern int Statinst_GetPropModelIndex(char *object);

extern s32 *Statinst_CollectPropResources(void *prop, s32 model, s32 geometryVariant, s32 *nextResource);




void Scene_BuildCachedGeometry(Shared_World *world) {
    f32 matrix[16];
    CVector3 position;
    CVector3 transformed;
    CacheResourceNode *resources[3000];
    ObjA *props[512];
    s32 resourceSize;
    s32 xCount;
    s32 z;
    s32 lastX;
    s32 lastZ;
    WorldSectorExtent *cells;
    WorldSectorExtent *cell;
    s32 propCount;
    ObjA **nextProp;
    Gfx *firstGfx;
    s32 row;
    CacheResourceNode **nextResource;
    CacheResourceNode *resource;
    struct CacheResourceNode *handle;
    CacheResourceNode *geometry;
    ScenePropSection *table;
    GridAxisSection *axis;
    WorldSectorExtentTable *cellTable;
    Pack *resourceData;
    StridedTable *points;
    ObjA *prop;
    ObjA *objects;
    ScenePoint *point;
    s32 zCount;
    s32 x;
    s32 slot;
    s32 key;
    s32 p;
    s32 i;
    s32 count;
    s32 model;
    s32 resourceBytes;
    s32 propBytes;
    s32 gfxBytes;
    s32 offset;
    s32 *cache;
    f32 height;
    f32 maximum;
    s32 firstX;
    s32 size;

    nextResource = resources;
    nextProp = props;
    firstX = 0;
    firstGfx = g_displayListCursor;
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_2CYCLE);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RNX, FRUSTRATIO_2);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RNY, FRUSTRATIO_2);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RPX, (u16)-FRUSTRATIO_2);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RPY, (u16)-FRUSTRATIO_2);
    z = 0;
    Geometry_BeginModelBatch();
    axis = SetN64_GetPackSection(world->gridBoundsAndSections, 0);
    xCount = axis->count;
    axis = SetN64_GetPackSection(world->gridBoundsAndSections, 2);
    zCount = axis->count;
    cellTable = SetN64_GetPackSection(world->gridBoundsAndSections, 4);
    cells = cellTable->cells;
    lastZ = zCount - 1;
    lastX = xCount - 1;
    if (z <= lastZ) {
        row = z * xCount;
        do {
            for (x = firstX; x <= lastX; x++) {
                slot = x + row;
                cell = &cells[slot];
                if (cell->occupied == 0) {
                    key = SetN64_LocatePackSection(world->sceneIndexData, world->sceneDirectoryKey, slot, &resourceSize);
                    resource = Cache_RequestResource(0, key, key, resourceSize, 4, (s32)world, g_scene_BuildPlacedInstancesEntry, s_gridSectionText, 1);
                    if (resource != 0) {
                        resourceData = (void *)resource->data;
                        if (resourceData->count != 0) {
                            Cache_LockResource(0, resource);
                            *nextResource++ = resource;
                            table = SetN64_GetPackSection(resourceData, 0);
                            propCount = table->count;
                            objects = table->props;
                            for (p = 0; p < propCount; p++) {
                                prop = &objects[p];
                                if (!(prop->flagsD8 & 0x40)) {
                                    prop->block = (void *)resource;
                                    if ((prop->flagsD8 & 4) || Statinst_GetPropModelIndex(prop) < 0) {
                                        *nextProp++ = prop;
                                    } else {
                                        model = Statinst_GetPropModelIndex(prop);
                                        nextResource = Statinst_CollectPropResources(prop, model, Statinst_GetPropGeometryIndex(prop), nextResource);
                                        Statinst_DrawModel(prop);
                                    }
                                    geometry = Statinst_AcquireGeometry(prop, Statinst_GetPropGeometryIndex(prop));
                                    if (geometry != 0) {
                                        points = SetN64_GetPackSection(geometry->data, 0);
                                        count = points->count;
                                        Graphu64_ConvertMatrixToFloat(matrix, &prop->transform);
                                        for (i = 0; i < count; i++) {
                                            point = (ScenePoint *)(points->data + i * points->stride);
                                            position.x = (f32)point->x;
                                            position.y = (f32)point->y;
                                            position.z = (f32)point->z;
                                            Graphu64_TransformPoint(matrix, &position, &transformed);
                                            height = transformed.y;
                                            maximum = world->minimumCollisionY;
                                            if (!(height <= maximum)) height = maximum;
                                            world->minimumCollisionY = height;
                                        }
                                        Cache_UnlockResource(0, geometry);
                                    }
                                }
                            }
                        }
                        Cache_UnlockResource(0, resource);
                    }
                }
            }
            row += xCount;
            z++;
        } while (z <= lastZ);
    }
    *nextResource++ = 0;
    *nextProp++ = 0;
    Geometry_FlushModelBatch();
    /* Cache blob: header {3 sections, offsets}, then the resource list, the prop list and the display list, each 8-aligned. */
    resourceBytes = (u8 *)nextResource - (u8 *)resources;
    offset = ((resourceBytes + 7) & ~7) + 24;
    propBytes = (u8 *)nextProp - (u8 *)props;
    size = propBytes + 7;
    size &= ~7;
    count = offset;
    offset += size;
    gSPEndDisplayList(g_displayListCursor++);
    gfxBytes = (u8 *)g_displayListCursor - (u8 *)firstGfx;
    handle = Cache_AllocateResource(0, offset + ((gfxBytes + 7) & ~7), 3, "Multi player data");
    world->cachedGeometryHandle = handle;
    cache = handle->data;
    world->cachedGeometryPack = cache;
    cache[0] = 3;
    world->cachedGeometryPack[1] = 24;
    world->cachedGeometryPack[2] = count;
    world->cachedGeometryPack[3] = offset;
    Libc_CopyBytes(SetN64_GetPackSection(world->cachedGeometryPack, 0), resources, resourceBytes);
    Libc_CopyBytes(SetN64_GetPackSection(world->cachedGeometryPack, 1), props, propBytes);
    Libc_CopyBytes(SetN64_GetPackSection(world->cachedGeometryPack, 2), firstGfx, gfxBytes);
    g_displayListCursor = firstGfx;
}

/* Draws a scene through cached display lists: loads the scene if needed (returning if that fails), calls the model's base list, and on first use records two lists in the frame's command stream, one for objects without flag 4 and one for objects with it, each drawn through Statinst_DrawModel inside a Geometry_BeginModelBatch pass and preceded by a branch past its end; finally calls the first cached list. */

void Scene_DrawCachedOpaqueGeometry(Shared_World *scene, void *camera) {
    ObjA **objects;
    ObjA *object;
    Gfx *branch;
    s32 pass;

    if (scene->cachedGeometryHandle == 0) {
        Cache_DrainAndCompactResources(0);
        Scene_BuildCachedGeometry(scene);
        if (scene->cachedGeometryHandle == 0) {
            return;
        }
    }
    gSPDisplayList(g_displayListCursor++, (unsigned int)SetN64_GetPackSection(scene->cachedGeometryPack, 2));
    if (scene->cachedDisplayLists[0] == 0) {
        for (pass = 0; pass < 2; pass++) {
            scene->cachedDisplayLists[pass] = g_displayListCursor;
            gSPBranchList(g_displayListCursor++, 0);
            Geometry_BeginModelBatch();
            objects = SetN64_GetPackSection(scene->cachedGeometryPack, 1);
            while (*objects != 0) {
                object = *objects++;
                switch (pass) {
                case 0:
                    if (!(object->flagsD8 & 4)) {
                        Statinst_DrawModel(object);
                    }
                    break;
                case 1:
                    if (object->flagsD8 & 4) {
                        Statinst_DrawModel(object);
                    }
                    break;
                }
            }
            Geometry_FlushModelBatch();
            gSPEndDisplayList(g_displayListCursor++);
            gSPBranchList(scene->cachedDisplayLists[pass]++, (unsigned int)g_displayListCursor);
        }
    }
    gSPDisplayList(g_displayListCursor++, (unsigned int)scene->cachedDisplayLists[0]);
}


/* One sector of the world: its model resource, its x/z extent and its cell in the streaming grid. */
/* The world and its streaming sectors use their owning definitions. */




typedef struct SceneStaticSection {
    s32 kind;
    s32 count;
    ObjB statics[1];
} SceneStaticSection;



static __inline__ s32 SceneFindShip(SceneModelIdTable *table) {
    s32 i;
    s32 count = table->count;
    u16 *p = table->entries;
    for (i = 0; i < count; i++) {
        if (p[i] == 51) {
            return i;
        }
    }
    return -1;
}
void Scene_DrawVisibleInstances(Shared_World *world, GameplayCamera *camera) {
    Shared_World *scene;
    ObjA *props;
    ObjA *prop;
    s32 model;
    s32 sectorIndex;
    s32 sectorCount;
    u32 mask;
    s32 viewMask;
    s32 shipModel;
    s32 showShip;
    SharedCameraOwnerView *player;
    WorldSector *sector;
    WorldSector *sectors;
    ObjB *statics;
    ScenePropSection *propSection;
    SceneStaticSection *staticSection;
    s32 propCount;
    s32 staticCount;
    s32 queued;
    s32 i;

    mask = g_gameSettings.sceneMask;
    viewMask = camera->floorSurface;
    world->drawableCount = 0;
#if defined(VERSION_US_REV1)
    if (g_textureVariationBypassEnabled == 0 && g_gameSettings.local != 0) {
#else
    if (g_gameSettings.local != 0) {
#endif
        Scene_DrawCachedOpaqueGeometry(world, camera);
        return;
    }
    player = Gsky_FindScreenMessage(camera);
    shipModel = SceneFindShip(world->modelIds);
    showShip = 0;
    if (player != NULL && shipModel != -1) {
        showShip = g_gameSettings.local == 0;
    }
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_2CYCLE);
    scene = world;
    Geometry_BeginModelBatch();
    scene->drawableCount = 0;
    if (player != NULL && (player->movementFlags & 0x100)) {
        gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RNX, FRUSTRATIO_1);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RNY, FRUSTRATIO_1);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RPX, (u16)-FRUSTRATIO_1);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RPY, (u16)-FRUSTRATIO_1);
    } else {
        gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RNX, FRUSTRATIO_2);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RNY, FRUSTRATIO_2);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RPX, (u16)-FRUSTRATIO_2);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RPY, (u16)-FRUSTRATIO_2);
    }
    sectorCount = scene->sectorCount;
    sectors = scene->sectors;
    for (sectorIndex = 0; sectorIndex < sectorCount; sectorIndex++) {
        sector = &sectors[sectorIndex];
        if (!(sector->bounds->maxX > camera->clipBounds[0].x && sector->bounds->minX < camera->clipBounds[1].x &&
              sector->bounds->maxZ > camera->clipBounds[0].z && sector->bounds->minZ < camera->clipBounds[1].z)) {
            continue;
        }
        Cache_MarkResourceInUse(0, sector->resource);
        model = sector->resource->data;
        propSection = SetN64_GetPackSection(model, 0);
        propCount = propSection->count;
        props = propSection->props;
        for (i = 0; i < propCount; i++) {
            prop = props;
            prop += i;
            queued = 0;
            if (!(prop->descriptor->gate & mask)) {
                continue;
            }
            prop->block = sector->resource;
            if (g_gameLoopFrameCount == 0) {
                Statinst_RegisterGeometryResources(prop);
            }
            if ((prop->flagsD8 & 8) && (prop->descriptor->flags & 4)) {
                queued = 1;
                if (prop->id == shipModel) {
                    if (showShip && scene->queuedCount != 64) {
                        scene->queued[scene->queuedCount++] = prop;
                    }
                } else if (scene->queuedCount != 64) {
                    scene->queued[scene->queuedCount++] = prop;
                }
            }
            if (scene->visibilityValid != 0 &&
                Visdata_TestVisibilityGridBit(&scene->visibilityGrid, sector->gridX, sector->gridZ, i) == 0) {
                continue;
            }
            if (camera->clipBounds[1].x > prop->bounds.min.x && camera->clipBounds[0].x < prop->bounds.max.x &&
                camera->clipBounds[1].z > prop->bounds.min.z && camera->clipBounds[0].z < prop->bounds.max.z &&
                camera->clipBounds[1].y > prop->bounds.min.y && camera->clipBounds[0].y < prop->bounds.max.y &&
                Visdata_TestBoxAgainstFrustum(camera->clipPlanes, &prop->bounds)) {
                if ((prop->flagsD8 & 8) && !queued && (prop->id != shipModel || showShip)) {
                    if (scene->queuedCount != 64) {
                        scene->queued[scene->queuedCount++] = prop;
                    }
                }
                if (Statinst_UpdateDistanceFade(prop, camera)) {
                    if (prop->flagsD8 & 4) {
                        if (scene->drawableCount != 64) {
                            scene->drawables[scene->drawableCount++] = prop;
                        }
                    } else {
                        Statinst_DrawDistanceFadedModel(prop);
                    }
                }
                prop->flagsD8 &= ~0x200;
            } else {
                prop->flagsD8 |= 0x200;
            }
        }
        staticSection = SetN64_GetPackSection(model, 1);
        staticCount = staticSection->count;
        statics = staticSection->statics;
        for (i = 0; i < staticCount; i++) {
            statics[i].block = sector->resource;
            if (g_gameLoopFrameCount == 0) {
                Simpinst_RegisterModelVariantResources(&statics[i], camera);
            }
            if ((statics[i].definition->gate & mask) && !(statics[i].flags & 1) && (viewMask & statics[i].scene) &&
                camera->clipBounds[1].x > statics[i].bounds.min.x && camera->clipBounds[0].x < statics[i].bounds.max.x &&
                camera->clipBounds[1].z > statics[i].bounds.min.z && camera->clipBounds[0].z < statics[i].bounds.max.z &&
                camera->clipBounds[1].y > statics[i].bounds.min.y && camera->clipBounds[0].y < statics[i].bounds.max.y &&
                (statics[i].flags & 2) && Visdata_TestBoxAgainstFrustum(camera->clipPlanes, &statics[i].bounds)) {
                if (statics[i].flags & 0x20) {
                    if (scene->drawableCount != 64) {
                        scene->drawables[scene->drawableCount++] = &statics[i];
                    }
                } else {
                    Simple_DrawCachedModel(&statics[i]);
                }
            }
        }
    }
    Geometry_FlushModelBatch();
    if (scene->visibilityValid != 0) {
        Cache_UnlockResource(NULL, scene->visibilityData);
        Cache_ReleaseResource(NULL, scene->visibilityData);
    }
}

/* SCENE_SAMPLEVOLUMELIGHTING.CPP */

/* Collects up to 10 light volumes holding a point from the world sector whose x/z extent holds it, returning their
 * count through total (0 outside every sector). */
void Scene_FindLightVolumes(Shared_World *world, CVector3 *point, SceneLightVolume **volumes, s32 *total) {
    WorldSector *sector;
    s32 i, found, sectorCount, volumeCount;
    f32 x, z;
    LightVolumeList *list;
    SceneLightVolume *volume, *base;
    sector = 0;
    i = 0;
    found = 0;
    x = point->x; z = point->z;
    sectorCount = world->sectorCount;
    for (; i < sectorCount; i++) {
        WorldSectorExtent *extent = world->sectors[i].bounds;
        if (extent->maxX < x || x < extent->minX ||
            extent->maxZ < z || z < extent->minZ) continue;
        sector = &world->sectors[i];
        break;
    }
    if (sector == 0) {
        *total = 0;
    } else {
        list = SetN64_GetPackSection(sector->resource->data, 2);
        volumeCount = list->count;
        base = list->volumes;
        for (i = 0; i < volumeCount; i++) {
            Box *bounds;
            volume = &base[i];
            bounds = &volume->bounds;
            if (bounds->max.x > point->x && bounds->max.y > point->y && bounds->max.z > point->z &&
                bounds->min.x <= point->x && bounds->min.y <= point->y && bounds->min.z <= point->z) {
                volumes[found++] = volume;
                if (found == 10) break;
            }
        }
        *total = found;
    }
}


static inline f32 sampleDot(CVector3 *a, f32 *b, s32 index) { f32 *d=b+index+128; return a->x*d[0] + a->y*d[1] + a->z*d[2]; }
void Scene_SampleVolumeLighting(SceneLightVolume **volumes, s32 count, CVector3 *position, Shared_ParticleLighting *lighting) {
    Shared_Game *settings;
    /* The first 128 floats are weights; the remaining 384 hold XYZ directions. */
    f32 samples[512];
    f32 *weights;
    f32 *directions;
    f32 *sampleDirection;
    CVector3 transformed;
    CVector3 combinedDirection;
    CVector3 color;
    CVector3 ambient;
    CVector3 backLight;
    CVector3 diffuse;
    CVector3 contribution;
    CVector3 localDirection;
    CVector3 translatedDirection;
    CVector3 animationColor;
    CVector3 animatedContribution;
    SceneLightVolume *animatedVolume;
    f32 zero;
    f32 one;
    f32 scale;
    f32 brightness;
    f32 level;
    f32 pulse;
    f32 amount;
    f32 backScale;
    f32 ambientRed;
    f32 ambientGreenLevel;
    f32 ambientBlueLevel;
    f32 diffuseRedLevel;
    f32 diffuseGreenLevel;
    f32 ambientGreen;
    f32 ambientBlue;
    f32 diffuseRed;
    f32 diffuseGreen;
    f32 diffuseBlue;
    s32 sampleIndex;
    SceneLightVolume *volume;

    settings = &g_gameSettings;
    brightness = (f32)(u32)settings->lightingGamma * 0.003921568859368563f;
    animatedVolume = NULL;
    if (settings->flags & 0x4000) {
        lighting->ambientCopy[0] = 0;
        lighting->ambient[0] = 0;
        lighting->ambientCopy[1] = 0;
        lighting->ambient[1] = 0;
        lighting->ambientCopy[2] = 0;
        lighting->ambient[2] = 0;
        lighting->diffuseCopy[0] = 0;
        lighting->diffuse[0] = 0;
        lighting->diffuseCopy[1] = 0;
        lighting->diffuse[1] = 0;
        lighting->diffuseCopy[2] = 0;
        lighting->diffuse[2] = 0;
        lighting->direction[0] = 0x7F;
        lighting->direction[1] = 0;
        lighting->direction[2] = 0;
        return;
    }
    sampleIndex = 0;
    combinedDirection.x = combinedDirection.y = combinedDirection.z = 0.0f;
    ambient.x = ambient.y = ambient.z = 0.0f;
    backLight.x = backLight.y = backLight.z = 0.0f;
    diffuse.x = diffuse.y = diffuse.z = 0.0f;
    if (sampleIndex < count) {

        weights = samples;
        directions = samples + 128;
        do {
            sampleDirection = directions + sampleIndex * 3;
            volume = volumes[sampleIndex];
            Graphu64_TransformPoint(volume->inverse, position, &transformed);
            if (Lighting_EvaluateLocalVolume(volume, transformed, &localDirection, &weights[sampleIndex]) != 0) {
                Graphu64_AddVec3(&translatedDirection, &localDirection, &transformed);
                Graphu64_ProjectPoint(volume->transform, &translatedDirection, &localDirection);
                Graphu64_SubtractVectors(sampleDirection, position, &localDirection);
                Graphu64_NormalizeVec3(sampleDirection);
                color = volume->direction;
                if (volume->animatedLight != 0) {
                    level = Link_GetLightAnimationOffset(volume);
                    animationColor.x = level;
                    animationColor.y = level;
                    animationColor.z = level;
                    Graphu64_ScaleVector(&contribution, &animationColor, weights[sampleIndex] * volume->value);
                    animatedVolume = volume;
                    if (volume->flagB8 != 0) {
                        Graphu64_ScaleVector(&contribution, &contribution, -1.0f);
                    }
                    Graphu64_AddVec3(&ambient, &ambient, &contribution);
                }
                amount = volume->value * 0.5f;
                scale = 1.0f - amount;
                Graphu64_ScaleVector(&contribution, &color, weights[sampleIndex] * amount);
                if (volume->flagB8 != 0) {
                    Graphu64_ScaleVector(&contribution, &contribution, -1.0f);
                }
                Graphu64_AddVec3(&ambient, &ambient, &contribution);
                weights[sampleIndex] *= scale;
                amount = color.x; if (amount < 0.0f) amount = -amount;
                if (color.y < 0.0f) amount = amount - color.y; else amount = amount + color.y;
                if (color.z < 0.0f) scale = amount - color.z; else scale = amount + color.z;
                Graphu64_ScaleVector(&contribution, sampleDirection, weights[sampleIndex]);
                Graphu64_ScaleVector(&contribution, &contribution, scale);
                Graphu64_AddVec3(&combinedDirection, &combinedDirection, &contribution);
                if (volume->flagB8 != 0) {
                    weights[sampleIndex] = -weights[sampleIndex];
                }
            } else {
                sampleDirection[0] = 0.0f;
                sampleDirection[1] = 0.0f;
                sampleDirection[2] = 0.0f;
                weights[sampleIndex] = 0.0f;
            }

            sampleIndex += 1;

        } while (sampleIndex < count);
    }
    Graphu64_NormalizeVec3(&combinedDirection);
    sampleIndex = 0;
    if (sampleIndex < count) {
        one = 1.0f;
        zero = 0.0f;
        do {
            volume = volumes[sampleIndex];
            scale = sampleDot(&combinedDirection, samples, sampleIndex * 3);
            backScale = one - scale; if (scale < zero) backScale = one;
            backScale *= 0.5f;
            color = volume->direction;
            scale = one - backScale;
            if (volume == animatedVolume) {
                pulse = Link_GetLightAnimationOffset(volume);
                animationColor.x = pulse;
                animationColor.y = pulse;
                animationColor.z = pulse;
                Graphu64_ScaleVector(&animatedContribution, &animationColor, scale * samples[sampleIndex]);
                Graphu64_AddVec3(&diffuse, &diffuse, &animatedContribution);
                Graphu64_ScaleVector(&animatedContribution, &animationColor, backScale * samples[sampleIndex]);
                Graphu64_AddVec3(&backLight, &backLight, &animatedContribution);
            }
            Graphu64_ScaleVector(&contribution, &color, scale * samples[sampleIndex]);
            Graphu64_AddVec3(&diffuse, &diffuse, &contribution);

            Graphu64_ScaleVector(&contribution, &color, backScale * samples[sampleIndex]);
            Graphu64_AddVec3(&backLight, &backLight, &contribution);
            sampleIndex++;
        } while (sampleIndex < count);
    }
    Graphu64_ScaleVector(&backLight, &backLight, 0.5f);
    Graphu64_AddVec3(&ambient, &ambient, &backLight);
    if (ambient.x < 0.0f) {
        diffuse.x += ambient.x;
    }
    if (ambient.y < 0.0f) {
        diffuse.y += ambient.y;
    }
    if (ambient.z < 0.0f) {
        diffuse.z += ambient.z;
    }
    ambientRed = ambient.x;
    if (!(ambientRed <= 255.0f)) ambientRed = 255.0f;
    if (!(5.0f <= ambientRed)) ambientRed = 5.0f;
    ambient.x = ambientRed * (1.0f - brightness) + brightness * 255.0f;
    ambientGreen = ambient.y;
    if (!(ambientGreen <= 255.0f)) ambientGreen = 255.0f;
    ambientGreenLevel = ambientGreen;
    if (!(5.0f <= ambientGreenLevel)) ambientGreenLevel = 5.0f;
    ambient.y = ambientGreenLevel * (1.0f - brightness) + brightness * 255.0f;
    ambientBlue = ambient.z;
    if (!(ambientBlue <= 255.0f)) ambientBlue = 255.0f;
    ambientBlueLevel = ambientBlue;
    if (!(5.0f <= ambientBlueLevel)) ambientBlueLevel = 5.0f;
    ambient.z = ambientBlueLevel * (1.0f - brightness) + brightness * 255.0f;
    diffuseRed = diffuse.x;
    if (!(diffuseRed <= 255.0f)) diffuseRed = 255.0f;
    diffuseRedLevel = diffuseRed;
    if (!(5.0f <= diffuseRedLevel)) diffuseRedLevel = 5.0f;
    diffuse.x = diffuseRedLevel * (1.0f - brightness) + brightness * 255.0f;
    diffuseGreen = diffuse.y;
    if (!(diffuseGreen <= 255.0f)) diffuseGreen = 255.0f;
    diffuseGreenLevel = diffuseGreen;
    if (!(5.0f <= diffuseGreenLevel)) diffuseGreenLevel = 5.0f;
    diffuse.y = diffuseGreenLevel * (1.0f - brightness) + brightness * 255.0f;
    diffuseBlue = diffuse.z;
    if (!(diffuseBlue <= 255.0f)) diffuseBlue = 255.0f;
    if (!(5.0f <= diffuseBlue)) diffuseBlue = 5.0f;
    diffuse.z = diffuseBlue * (1.0f - brightness) + brightness * 255.0f;
    lighting->ambient[0] = lighting->ambientCopy[0] = (u32)ambient.x;
    lighting->ambient[1] = lighting->ambientCopy[1] = (u32)ambient.y;
    lighting->ambient[2] = lighting->ambientCopy[2] = (u32)ambient.z;
    lighting->diffuse[0] = lighting->diffuseCopy[0] = (u32)diffuse.x;
    lighting->diffuse[1] = lighting->diffuseCopy[1] = (u32)diffuse.y;
    lighting->diffuse[2] = lighting->diffuseCopy[2] = (u32)diffuse.z;
    lighting->direction[0] = (s32)(combinedDirection.x * 127.0f);
    lighting->direction[1] = (s32)(combinedDirection.y * 127.0f);
    lighting->direction[2] = (s32)(combinedDirection.z * 127.0f);
}


typedef struct SceneTriggerDefinition {
    ActorDefinitionHeader header;
    char pad18[8];
    f32 enterRadius;
    f32 exitRadius;
    f32 touchRadius;
} SceneTriggerDefinition;
/* Fires the movement triggers an actor crosses between two positions. Only kinds 0xB and 1 trip triggers. Kind 6
 * triggers are rings (enter when moving inside enterRadius from outside it, exit when moving outside exitRadius
 * from inside it); kinds 10 and 7 fire their enter event inside their radius while the two actors overlap in height,
 * and a kind 10 trigger first asks Action_ShowTriggerMessage_SceneSamplevolumelighting. Distances are measured in the xz plane. */
void Scene_UpdateMovementTriggers(Shared_World *world, LevelActor *actor, CVector3 *before, CVector3 *after) {
    s32 isKindB;
    s32 isKind1;
    f32 bottom;
    f32 top;
    f32 triggerBottom;
    f32 triggerTop;
    f32 beforeDistance;
    f32 afterDistance;
    f32 enterRadius;
    f32 exitRadius;
    f32 radius;
    s32 kind;
    s32 flags;
    s32 enterOnB;
    s32 enterOn1;
    s32 exitOnB;
    s32 exitOn1;
    s32 entering;
    s32 exiting;
    s32 hit;
    s32 enterMode;
    s32 exitMode;
    s32 ring;
    s32 checkHeight;
    s32 i;
    SceneTriggerDefinition *definition;
    LevelActor *trigger;

    if (before->x == after->x && before->y == after->y && before->z == after->z) {
        return;
    }
    kind = actor->definition->kind;
    isKindB = kind == 11;
    isKind1 = kind == 1;
    bottom = actor->position0.y + InstHdr_GetActorBaseOffset(actor);
    top = bottom + Gobjinst_GetActorHeight(actor);
    for (i = 0; i < world->flaggedCount; i++) {
        trigger = world->flagged[i];
        if (trigger == actor) {
            continue;
        }
        ring = 0;
        checkHeight = 0;
        triggerBottom = trigger->position0.y + InstHdr_GetActorBaseOffset(trigger);
        triggerTop = triggerBottom + Gobjinst_GetActorHeight(trigger);
        definition = (SceneTriggerDefinition *)trigger->definition;
        switch (definition->header.kind) {
        case 6:
            enterMode = 0;
            ring = 1;
            exitMode = 1;
            flags = definition->header.flags;
            enterRadius = definition->enterRadius;
            exitRadius = definition->exitRadius;
            enterOnB = flags & 4;
            enterOn1 = flags & 8;
            exitOnB = flags & 0x10;
            exitOn1 = flags & 0x20;
            break;
        case 10:
            enterMode = 1;
            exitMode = 0;
            exitOnB = 0;
            exitOn1 = 0;
            checkHeight = 1;
            flags = definition->header.flags;
            enterRadius = definition->exitRadius;
            exitRadius = 0.0f;
            enterOnB = flags & 4;
            enterOn1 = flags & 8;
            break;
        case 7:
            enterMode = 1;
            exitMode = 0;
            exitOnB = 0;
            exitOn1 = 0;
            checkHeight = 1;
            flags = definition->header.flags;
            enterRadius = definition->touchRadius;
            exitRadius = 0.0f;
            enterOnB = flags & 8;
            enterOn1 = flags & 0x10;
            break;
        default:
            enterMode = 0;
            enterRadius = 0.0f;
            enterOnB = 0;
            enterOn1 = 0;
            exitMode = 0;
            exitOnB = 0;
            exitOn1 = 0;
            exitRadius = 0.0f;
            break;
        }
        if (checkHeight && (top < triggerBottom || triggerTop < bottom)) {
            entering = 0;
            exiting = 0;
        } else {
            entering = 0;
            if ((isKindB && enterOnB) || (isKind1 && enterOn1)) {
                entering = 1;
            }
            exiting = 0;
            if ((isKindB && exitOnB) || (isKind1 && exitOn1)) {
                exiting = 1;
            }
        }
        if (entering || exiting) {
            beforeDistance = (before->x - trigger->position0.x) * (before->x - trigger->position0.x) +
                             (before->z - trigger->position0.z) * (before->z - trigger->position0.z);
            afterDistance = (after->x - trigger->position0.x) * (after->x - trigger->position0.x) +
                            (after->z - trigger->position0.z) * (after->z - trigger->position0.z);
            if (entering) {
                if (ring) {
                    radius = enterRadius * enterRadius;
                    hit = 0;
                    if (radius < beforeDistance && afterDistance <= radius) {
                        hit = 1;
                    }
                } else {
                    hit = 1;
                    if (!(afterDistance <= enterRadius * enterRadius)) {
                        hit = 0;
                    }
                }
                if (hit) {
                    if (trigger->definition->kind == 10 && enterMode == 1) {
                        hit = Action_ShowTriggerMessage(trigger, &trigger->behaviorFlags, actor);
                    }
                    if (hit) {
                        Actor_RequestActorState(trigger, &trigger->behaviorFlags, enterMode);
                    }
                }
            }
            if (exiting) {
                if (ring) {
                    radius = exitRadius * exitRadius;
                    hit = 0;
                    if (beforeDistance <= radius && radius < afterDistance) {
                        hit = 1;
                    }
                } else {
                    hit = 1;
                    if (!(exitRadius * exitRadius < afterDistance)) {
                        hit = 0;
                    }
                }
                if (hit) {
                    Actor_RequestActorState(trigger, &trigger->behaviorFlags, exitMode);
                }
            }
        }
    }
}




static inline s32 transitionId(Shared_World *scene) {
    if (scene->selectionFlags != 0) return scene->selectionSpawn.kind;
    return scene->selectionValues[1];
}
void Scene_UpdateSelectionTransition(Shared_World *scene)
{
    ColorEntry *entry = &((ColorEntry *)&g_emacText)[scene->selectionState];
    s32 id;
    MenuSettings *settings;
    switch (scene->frozen) {
    case 0:
        break;
    case 1:
        if (scene->selectionTimer == entry->value) {
            if (scene->selectionValues[1] == 999) { Track_RequestCameraRefresh(); Track_RequestTrackByKey(400); }
            if (scene->selectionState == 0) scene->frozen = 0;
            else scene->frozen = 2;
            if (scene->selectionValues[1] < 0) { scene->selectionValues[1] = ~scene->selectionValues[1]; scene->selectionFlags = 0; }
            else scene->selectionFlags = Scene_FindPlacedObjectsByKey(scene, -1, scene->selectionValues[1], &scene->selectionSpawn, 1);
            scene->selectionValues[0] = scene->selectionValues[1];
            id = transitionId(scene);
            Scene_LoadLevelResources(scene, id, scene->selectionFlags);
            settings = &g_frontendScreenStatus.settings;
            if (scene->previewStart != settings->optionFlags && SetN64_IsModeThirteen()) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
                Gsky_PostScaledScreenMessage(&g_frontendScreenStatus, &g_frontendScreenStatus.fallbackCamera, g_optionFlagsChangedMessageText[settings->language], 4.0f);
#else
                Gsky_PostScaledScreenMessage(&g_frontendScreenStatus, &g_frontendScreenStatus.fallbackCamera, g_optionFlagsChangedMessageText, 4.0f);
#endif
                scene->previewStart = settings->optionFlags;
            }
        } else {
            scene->selectionTimer += g_frameElapsedTime;
            if (entry->value < scene->selectionTimer) scene->selectionTimer = entry->value;
        }
        break;
    case 2:
        if (scene->selectionTimer == 0.0f) scene->frozen = 0;
        else {
            scene->selectionTimer -= g_frameElapsedTime;
            if (scene->selectionTimer < 0.0f) scene->selectionTimer = 0.0f;
        }
        break;
    }
}

typedef struct ResultsText {
    char *text;
    s32 length;
} ResultsText;
typedef struct ResultsCourse {
    u8 reservedBytes[0x21];
    u8 laps;
    u8 targetCount;
    u8 rounds;
    u8 timeLimit;     /* seconds */
    u8 reservedBytes1[3];
    u8 lives;
} ResultsCourse;
typedef struct LevelChallenge {
    u8 reservedBytes2[4];
    u8 character;     /* the opponent's character key */
    u8 reservedWord;
    u16 weapons[8];   /* starting weapon item ids (read by the achieve loadout) */
} LevelChallenge;


static inline void copyLevelName(Shared_World *world, s32 level, char *out, s32 limit) {
    void *handle;
    s32 entry;
    void *bank;
    ResultsText *name;
    s32 length;

    entry = SetN64_GetDirectoryEntry(world->resourceDirectory, world->resourceBank, level);
    bank = Cache_RequestWordCountedResourcePinned(0, &handle, entry, g_levelIndexText);
    name = Cache_RequestPackSection(0, handle, 8, entry, world, 0, g_levelNameText);
    length = name->length;
    if (limit < length) {
        length = limit;
    }
    Libc_CopyBytes(out, name->text, length);
    Cache_ReleaseResource(0, name);
    if (world->level != level) {
        Cache_ReleaseResource(0, bank);
    }
}
static inline LevelChallenge *findLevelChallenge(Shared_World *world, s32 level) {
    s32 size;
    void **index;
    s32 file;
    s32 mode;
    s32 direct;

    if (world->resourceHandle == 0 || world->resourceKey != level) {
        Scene_ReleaseCachedLevelData(world);
        if (world->challengeFile != 0) {
            mode = 16;
            direct = 1;
            index = Cache_RequestResource(0, world->challengeFile, world->challengeFile, world->challengeFileSize, mode,
                                     0, 0, g_sceneResourceRequestSpareDe, direct);
            if (index != 0) {
                file = SetN64_LocatePackSection((s32)*index, world->challengeFile, level, &size);
                Cache_ReleaseResource(0, index);
                if ((world->resourceHandle =
                         Cache_RequestResource(0, file, file, size, mode, 0, g_cResource_UnpackRequestEntry, g_sceneUnpackRequestSpare, direct)) == 0) {
                    goto missing;
                }
                world->resourceKey = level;
            }
        }
    }
    if (world->resourceHandle != 0) {
        return *world->resourceHandle;
    }
missing:
    return 0;
}

/* Print the level name, then the goal line and the mode's detail line of the results screen. */
void Scene_ShowResultsGoal(void) {
    char name[40];
    char goal[40];
    LevelGoal *levelGoal;
    u8 mode;
    u8 minutes;
    s32 seconds;
    s32 players;
    LevelChallenge *challenge;
    ResultsHeadingCharacter *character;

    Cinema_ClearMessageCount();
    copyLevelName(&g_world, g_selectedLevelId, name, 63);
    Cinema_AddMessage(name);
    if (currentGame()->controllerMode == 0) {
        return;
    }
    levelGoal = &g_currentResultMode; /* kind (0 rounds, 1 laps, 2 single laps, 3 targets), then the target goal */
    switch (levelGoal->kind) {
    case 0:
        if (currentGame()->controllerMode == 2) {
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsRoundsControllerModeFormat, g_resultsRoundsControllerModeFormatLocalized), g_currentStagePreset->other);
        } else if (g_currentStagePreset->other < 2) {
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsRoundSingularFormat, g_resultsRoundSingularFormatLocalized), g_currentStagePreset->other);
        } else {
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsRoundsPluralFormat, g_resultsRoundsPluralFormatLocalized), g_currentStagePreset->other);
        }
        break;
    case 1:
        if (currentGame()->controllerMode == 2) {
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsLapsControllerModeFormat, g_resultsLapsControllerModeFormatLocalized), g_currentStagePreset->score);
        } else if (g_currentStagePreset->score < 2) {
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsLapSingularFormat, g_resultsLapSingularFormatLocalized), g_currentStagePreset->score);
        } else {
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsLapsPluralFormat, g_resultsLapsPluralFormatLocalized), g_currentStagePreset->score);
        }
        break;
    case 2:
        if (g_currentStagePreset->score < 2) {
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsSingleLapSingularFormat, g_resultsSingleLapSingularFormatLocalized), g_currentStagePreset->score);
        } else {
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsSingleLapsPluralFormat, g_resultsSingleLapsPluralFormatLocalized), g_currentStagePreset->score);
        }
        break;
    case 3:
        switch (levelGoal->goal) {
        case 4:
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsGoalLabelFormat, g_resultsGoalLabelFormatLocalized), RESULTS_TEXT(*(int *)&g_characterNames[0x30], g_bastilleNameLocalized));
            break;
        case 9:
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsGoalValueFormat, g_resultsGoalValueFormatLocalized), RESULTS_TEXT(&g_characterNames[0x34], g_syraNameLocalized),
                             RESULTS_TEXT(g_characterNames, g_characterNamesLocalized));
            break;
        case 22:
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsGoalLabelFormat, g_resultsGoalLabelFormatLocalized), RESULTS_TEXT(*(int *)&g_characterNames[0x38], g_symbiontNameLocalized));
            break;
        case 35:
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsGoalLabelFormat, g_resultsGoalLabelFormatLocalized), RESULTS_TEXT((int *)&g_characterNames[0x3C], g_talSetRaptorMantidMitesNamesLocalized));
            break;
        default:
            if (g_currentStagePreset->limit < 2) {
                XStdio_FormatBuffer(goal, RW_LOCALIZED_TEXT(g_resultsGoalSingularFormat, g_resultsGoalSingularFormatLocalized, g_resultsGoalSingularFormatLocalized, g_languageIndex),
                                 g_currentStagePreset->limit);
            } else {
                XStdio_FormatBuffer(goal, RW_LOCALIZED_TEXT(g_resultsGoalsPluralFormat, g_resultsGoalsPluralFormatLocalized, g_resultsGoalsPluralFormatLocalized, g_languageIndex),
                                 g_currentStagePreset->limit);
            }
            break;
        }
        break;
    }
    mode = currentGame()->controllerMode;
    switch (mode) {
    case 1:
        Cinema_AddMessage(goal);
        players = (Player_GetLevelProgress(g_localPlayerProfiles, g_localPlayerProfiles[0].slot) >> 1) + 1;
        if (players < 2) {
            XStdio_FormatBuffer(name, RESULTS_TEXT(g_resultsPlayerOrLivesSingularFormat, g_resultsPlayerOrLivesSingularFormatLocalized), players);
        } else {
            XStdio_FormatBuffer(name, RESULTS_TEXT(g_resultsLivesPluralFormat, g_resultsLivesPluralFormatLocalized), players);
        }
        Cinema_AddMessage(name);
        break;
    case 3:
        Cinema_AddMessage(goal);
        if (g_currentStagePreset->time <= 60) {
            XStdio_FormatBuffer(name, RESULTS_TEXT(g_resultsTimeLimitFormat, g_resultsTimeLimitFormatLocalized), g_currentStagePreset->time);
        } else {
            minutes = g_currentStagePreset->time / 60;
            if (minutes < 2) {
                seconds = g_currentStagePreset->time % 60;
                if (seconds == 0) {
                    XStdio_FormatBuffer(name, RESULTS_TEXT(g_resultsMinuteSingularFormat, g_resultsMinuteSingularFormatLocalized), minutes);
                } else {
                    XStdio_FormatBuffer(name, RESULTS_TEXT(g_resultsMinuteSecondsSingularFormat, g_resultsMinuteSecondsSingularFormatLocalized), minutes, seconds);
                }
            } else {
                seconds = g_currentStagePreset->time % 60;
                if (seconds == 0) {
                    XStdio_FormatBuffer(name, RESULTS_TEXT(g_resultsMinutesPluralFormat, g_resultsMinutesPluralFormatLocalized), minutes);
                } else {
                    XStdio_FormatBuffer(name, RESULTS_TEXT(g_resultsMinutesSecondsPluralFormat, g_resultsMinutesSecondsPluralFormatLocalized), minutes, seconds);
                }
            }
        }
        Cinema_AddMessage(name);
        break;
    case 4:
        challenge = findLevelChallenge(&g_world, g_selectedLevelId);
        character = &RESULTS_CHARACTERS[Key_FindKeyIndex(challenge->character)];
        XStdio_FormatBuffer(name, RESULTS_NAME_FORMAT, character->name[RESULTS_LANGUAGE].text);
        Cinema_AddMessage(name);
        Cinema_AddMessage(goal);
        if (g_currentStagePreset->laps < 2) {
            XStdio_FormatBuffer(name, RESULTS_TEXT(g_resultsPlayerOrLivesSingularFormat, g_resultsPlayerOrLivesSingularFormatLocalized), g_currentStagePreset->laps);
        } else {
            XStdio_FormatBuffer(name, RESULTS_TEXT(g_resultsLivesPluralFormat, g_resultsLivesPluralFormatLocalized), g_currentStagePreset->laps);
        }
        Cinema_AddMessage(name);
        break;
    case 2:
        Cinema_AddMessage(goal);
        switch (g_currentResultMode.kind) {
        case 0:
            break;
        case 1:
            Cinema_AddMessage(RESULTS_TEXT(g_resultsModeMessage, g_slotAchievementTextPointers_EveryManForThemselves));
            break;
        case 2:
            Cinema_AddMessage(RESULTS_TEXT(g_resultsModeMessage, g_slotAchievementTextPointers_EveryManForThemselves));
            break;
        }
        break;
    }
}

/* SCENE_DRAWOPAQUEACTORS.CPP */

char *Scene_GetLinkedResourceSection(Shared_World *world, s32 resourceId) {
    return SetN64_GetPackSection(world->objectSections, resourceId);
}

/** Return an indexed record from the table. */
void *Scene_GetStridedWorldRecord(struct Shared_World *object, int index) {
    StridedTable *table = (StridedTable *)object->records;

    return &table->data[index * table->stride];
}





/* Draws a scene's object list inside a Geometry_BeginModelBatch and Geometry_FlushModelBatch pass: writes four G_MOVEWORD commands setting the words at 4, 0xC, 0x14 and 0x1C to 5, 5, 0xFFFB and 0xFFFB, then draws each object through Gobjinst_DrawVisibleCachedActor unless its flag 4 is set, in which case it is deferred to the scene's 64-entry late list. */






extern Gfx *g_displayListCursor;




void Scene_DrawOpaqueActors(Shared_World *scene, void *camera) {
    LevelActor *object;
    s32 count;
    s32 i;
    s32 late;
    LevelActor **objects;

    Geometry_BeginModelBatch();
    count = scene->registeredCount;
    gMoveWd(g_displayListCursor++, G_MW_CLIP, 4, 5);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, 12, 5);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, 20, 0xFFFB);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, 28, 0xFFFB);
    objects = scene->registered;
    for (i = 0; i < count; i++) {
        object = objects[i];
        if (object->flags & 4) {
            late = scene->drawableCount;
            if (late != 64) {
                scene->drawables[late] = object;
                scene->drawableCount = late + 1;
            }
        } else {
            Gobjinst_DrawVisibleCachedActor(object, camera);
        }
    }
    Geometry_FlushModelBatch();
}


struct EffectSystem; struct GameplayCamera;


void Scene_DrawWorldParticles(s32 world, s32 view) {
    Gfx *cmd;

    cmd = g_displayListCursor++;
    gMoveWd(cmd, G_MW_CLIP, 4, 1);
    cmd = g_displayListCursor++;
    gMoveWd(cmd, G_MW_CLIP, 12, 1);
    cmd = g_displayListCursor++;
    gMoveWd(cmd, G_MW_CLIP, 20, 0xFFFF);
    cmd = g_displayListCursor++;
    gMoveWd(cmd, G_MW_CLIP, 28, 0xFFFF);
    Geometry_BeginModelBatch();
    Particle_DrawRenderList(world + 6920, view);
    Geometry_FlushModelBatch();
}

s32 Scene_FindModelIdIndex(struct Shared_World *world, s32 modelId)
{
  s32 count;
  s32 i;
  u16 *ptr;
  SceneModelIdTable *base;
  s32 masked;
  base = world->modelIds;
  count = (base)->count;
  ptr = &(base)->entries[0];
  i = 0;
  if (count <= 0)
  {
    goto fail;
  }
  masked = modelId & 0xFFFF;
  loop_2:
  if ((*ptr) == masked)
  {
 do { return i; } while (0);
  }

  i += 1;
  ptr += 1;
  if (i < count)
  {
    goto loop_2;
  }
  fail:
  return -1;

}

int Scene_GetModelIdAtIndex(Shared_World *world, int modelIndex) {
    return (world)->modelIds->entries[modelIndex];
}

/* Changes an object's model when the requested model id is present in the resource bank, then rebuilds its model data. */
static inline s32 find(SceneModelIdTable *table,u16 id) {
 s32 index=0,count; u16 *entry;entry=table->entries;count=table->count;
 if(count>0) { do {if(*entry==id) return index; index++;entry++;} while(index<count); }
 return -1;
}
void Scene_ChangeInstanceModel(Shared_World *modelBank,ObjectSceneChangeInstanceModel *draw,s32 modelId,s32 extra) {
 s32 index=0;
 if(draw->id!=modelId) {
 index=find(modelBank->modelIds,modelId);
 if(index!=-1){draw->index=index;draw->id=modelId;Gobjinst_LoadModel(draw,modelBank->indexedDirectory,modelBank->indexedBank,extra);}
 }
}


void *Scene_GetModelRecordByIndexPointer(Shared_World *world, u16 *modelIndex) {
    s32 base;
    s32 idx;

    if (modelIndex == 0) {
        return 0;
    }
    base = ((char *)SetN64_GetPackSection(world->modelSections, 0)) + 8;
    idx = *modelIndex;
    return (void *)(base + idx * 100);
}


u32 Scene_GetModelSectionTwoIndex(Shared_World *world, s32 modelId) {
    s32 offset;
    s32 result;

    if (modelId == 0) {
        return -1;
    }
    offset = ((char *)SetN64_GetPackSection(world->modelSections, 2)) + 8;
    result = modelId - offset;
    return (u32)result >> 5;
}







s32 Scene_GetModelSectionTwoRecord(Shared_World *world, s32 modelId) {
    s32 raw;
    s32 base;

    raw = SetN64_GetPackSection((world)->modelSections, 2);
    base = raw + 8;
    if (modelId < 0 || modelId >= ((StridedTable *)raw)->count) {
        return 0;
    }
    return base + (modelId << 5);
}






void Scene_SetSecondaryLevelBit(struct Shared_World *world, s32 index, s32 bitIndex, s32 enabled) {
    void *table;
    u8 *stateBytes;
    u8 *stateBytesForClear;
    s32 mask;
    s32 idx;
    s32 clearBitIndex;

    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(world->secondaryLevels, 0), index), 0);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    stateBytes = SetN64_GetPackSection(table, 1);
    stateBytesForClear = stateBytes;
    mask = 1 << (bitIndex & 7);
    if (enabled != 0) {
        idx = bitIndex;
        if (bitIndex < 0) {
            idx = bitIndex + 7;
        }
        stateBytes[idx >> 3] |= mask;
        return;
    }
    clearBitIndex = bitIndex;
    if (clearBitIndex < 0) {
        clearBitIndex += 7;
    }
    stateBytesForClear[clearBitIndex >> 3] &= ~mask;
}

void Scene_EmptyHandlerAfterSetSecondaryLevelBit(void) {
}





void Scene_SetCurrentSecondaryLevelBit(struct Shared_World *world, s32 bitIndex, s32 enabled) {
    void *secondaryLevels;
    s32 levelIndex;
    void *table;
    u8 *stateBytes;
    u8 *stateBytesForClear;
    s32 mask;
    s32 idx;
    s32 clearBitIndex;

    secondaryLevels = world->secondaryLevels;
    levelIndex = world->level;
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(secondaryLevels, 0), levelIndex), 0);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    stateBytes = SetN64_GetPackSection(table, 1);
    stateBytesForClear = stateBytes;
    mask = 1 << (bitIndex & 7);
    if (enabled != 0) {
        idx = bitIndex;
        if (bitIndex < 0) {
            idx = bitIndex + 7;
        }
        stateBytes[idx >> 3] |= mask;
        return;
    }
    clearBitIndex = bitIndex;
    if (clearBitIndex < 0) {
        clearBitIndex += 7;
    }
    stateBytesForClear[clearBitIndex >> 3] &= ~mask;
}





s32 Scene_TestCurrentSecondaryLevelBit(struct Shared_World *world, s32 bitIndex) {
    void *secondaryLevels;
    s32 levelIndex;
    void *table;
    u8 *stateBits;
    s32 mask;
    s32 i;

    secondaryLevels = world->secondaryLevels;
    levelIndex = world->level;
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(secondaryLevels, 0), levelIndex), 0);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    stateBits = SetN64_GetPackSection(table, 1);
    mask = 1 << (bitIndex & 7);
    i = bitIndex;
    if (i < 0) {
        i += 7;
    }
    return (stateBits[i >> 3] & mask) != 0;
}

/* SCENE_SETLEVELACTORSTATEBIT.CPP */

void Scene_SetLevelActorStateBit(void *world, s32 index, s32 actorIndex, s32 enabled) {
  Shared_World *sceneWorld = (Shared_World *) world;
    LevelActor *entry;
    struct Def *cond;
    void *levelResources;
    void *table;
    u8 *stateBytes;
    u8 *stateBytesForClear;
    s32 mask;
    s32 idx;
    s32 clearBitIndex;

    if (sceneWorld->mode == 2) {
        return;
    }
    if (((Shared_World *)world)->level == index) {
        entry = (char *)&((Shared_World *)world)->actors[(s32)actorIndex];
        cond = (struct Def *)((LevelActor *)entry)->definition;
        if ((u32) (cond->type - 9) < 2) {
            if (cond->flags & 0x200) {
                return;
            }
        }
    }
    levelResources = sceneWorld->bitSections;
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(levelResources, 0), (s32) index), 0);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    stateBytes = SetN64_GetPackSection(table, 1);
    stateBytesForClear = stateBytes;
    mask = 1 << (actorIndex & 7);
    if (enabled != 0) {
        idx = actorIndex;
        if ((s32) actorIndex < 0) {
            idx = actorIndex + 7;
        }
        stateBytes[idx >> 3] |= mask;
        return;
    }
    clearBitIndex = actorIndex;
    if (clearBitIndex < 0) {
        clearBitIndex += 7;
    }
    stateBytesForClear[clearBitIndex >> 3] &= ~mask;
}

void Scene_SetRecordBitForLevel(Shared_World *worldState, s32 index, s32 recordBitIndex, s32 enabled) {
    void *table;
    u8 *stateBytes;
    u8 *stateBytesForClear;
    s32 mask;
    s32 idx;
    s32 clearBitIndex;

    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(worldState->bitSections, 0), index), 1);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    stateBytes = SetN64_GetPackSection(table, 1);
    stateBytesForClear = stateBytes;
    mask = 1 << (recordBitIndex & 7);
    if (enabled != 0) {
        idx = recordBitIndex;
        if (recordBitIndex < 0) {
            idx = recordBitIndex + 7;
        }
        stateBytes[idx >> 3] |= mask;
        return;
    }
    clearBitIndex = recordBitIndex;
    if (clearBitIndex < 0) {
        clearBitIndex += 7;
    }
    stateBytesForClear[clearBitIndex >> 3] &= ~mask;
}

void Scene_SetLevelRecordStateBit(void *world, struct ObjB *levelBitRecord, s32 recordIndex) {
    s32 bitIndex;
    void *levelResources;
    s32 levelIndex;
    void *table;
    u8 *stateBytes;
    u8 *stateBytesForClear;
    s32 mask;
    s32 idx;
    s32 clearBitIndex;

    bitIndex = levelBitRecord->placementId;
    levelResources = ((Shared_World *)(world))->bitSections;
    levelIndex = ((Shared_World *)(world))->level;
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(levelResources, 0), levelIndex), 1);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    stateBytes = SetN64_GetPackSection(table, 1);
    stateBytesForClear = stateBytes;
    mask = 1 << (bitIndex & 7);
    if (recordIndex != 0) {
        idx = bitIndex;
        if (bitIndex < 0) {
            idx = bitIndex + 7;
        }
        stateBytes[idx >> 3] |= mask;
        return;
    }
    clearBitIndex = bitIndex;
    if (clearBitIndex < 0) {
        clearBitIndex += 7;
    }
    stateBytesForClear[clearBitIndex >> 3] &= ~mask;
}

s32 Scene_TestLevelRecordStateBit(void *world, struct ObjB *levelBitRecord) {
    s32 bitIndex;
    void *levelResources;
    s32 levelIndex;
    void *table;
    u8 *recordBits;
    s32 mask;

    bitIndex = levelBitRecord->placementId;
    levelResources = ((Shared_World *)(world))->bitSections;
    levelIndex = ((Shared_World *)(world))->level;
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(levelResources, 0), levelIndex), 1);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    recordBits = SetN64_GetPackSection(table, 1);
    mask = 1 << (bitIndex & 7);
    if (bitIndex < 0) {
        bitIndex += 7;
    }
    return (recordBits[bitIndex >> 3] & mask) != 0;
}

void Scene_SetTriggerBitForLevel(Shared_World *worldState, s32 index, s32 triggerBitIndex, s32 enabled) {
    void *table;
    u8 *stateBytes;
    u8 *stateBytesForClear;
    s32 mask;
    s32 idx;
    s32 clearBitIndex;

    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(worldState->bitSections, 0), index), 2);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    stateBytes = SetN64_GetPackSection(table, 1);
    stateBytesForClear = stateBytes;
    mask = 1 << (triggerBitIndex & 7);
    if (enabled != 0) {
        idx = triggerBitIndex;
        if (triggerBitIndex < 0) {
            idx = triggerBitIndex + 7;
        }
        stateBytes[idx >> 3] |= mask;
        return;
    }
    clearBitIndex = triggerBitIndex;
    if (clearBitIndex < 0) {
        clearBitIndex += 7;
    }
    stateBytesForClear[clearBitIndex >> 3] &= ~mask;
}

void Scene_SetTriggerStateBit(void *world, void *trigger, s32 triggerIndex) {
    s32 bitIndex;
    void *levelResources;
    s32 levelIndex;
    void *table;
    u8 *stateBytes;
    u8 *stateBytesForClear;
    s32 mask;
    s32 idx;
    s32 clearBitIndex;

    bitIndex = ((struct TriggerStateBitDescriptor *)trigger)->bitIndex;
    levelResources = ((Shared_World *)(world))->bitSections;
    levelIndex = ((Shared_World *)(world))->level;
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(levelResources, 0), levelIndex), 2);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    stateBytes = SetN64_GetPackSection(table, 1);
    stateBytesForClear = stateBytes;
    mask = 1 << (bitIndex & 7);
    if (triggerIndex != 0) {
        idx = bitIndex;
        if (bitIndex < 0) {
            idx = bitIndex + 7;
        }
        stateBytes[idx >> 3] |= mask;
        return;
    }
    clearBitIndex = bitIndex;
    if (clearBitIndex < 0) {
        clearBitIndex += 7;
    }
    stateBytesForClear[clearBitIndex >> 3] &= ~mask;
}

s32 Scene_TestTriggerStateBit(Shared_World *world, WorldTrigger *trigger) {
    s32 bitIndex;
    void *levelResources;
    s32 levelIndex;
    void *table;
    u8 *stateBits;
    s32 mask;

    bitIndex = (trigger)->visibilityGroup;
    levelResources = world->bitSections;
    levelIndex = world->level;
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(levelResources, 0), levelIndex), 2);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    stateBits = SetN64_GetPackSection(table, 1);
    mask = 1 << (bitIndex & 7);
    if (bitIndex < 0) {
        bitIndex += 7;
    }
    return (stateBits[bitIndex >> 3] & mask) != 0;
}

/* Finds an identifier in the object's list and returns its mapped byte from the resource record, or -1 when absent. */
s32 Scene_GetTriggerCounterById(Shared_World *counterOwner, s32 counterId) {
    s32 i;
    void *record;
    Table *list = counterOwner->triggerCounterIds;
    s32 count = list->count;
    s32 *ids = list->deltas;

    for (i = 0; i < count; i++) {
        if (ids[i] == counterId) {
            record = SetN64_GetPackSection(counterOwner->bitSections, 1);
            SetN64_GetPackSection(record, 0);
            return ((u8 *)SetN64_GetPackSection(record, 1))[i];
        }
    }
    return -1;
}

void Scene_DecrementTriggerCounter(struct Shared_World *world, s32 triggerIndex) {
    u8 *counter;
    void *counterSections;
    counterSections = SetN64_GetPackSection((((struct Shared_World *) ((s8 *) world))->bitSections), 1);
    SetN64_GetPackSection(counterSections, 0);
    counter = SetN64_GetPackSection(counterSections, 1) + triggerIndex;
    *counter -= 1;
}

s32 Scene_TestTriggerCounterZero(struct Shared_World *world, s32 triggerIndex) {
    void *packSectionResult;
    u8 *result;

    packSectionResult = SetN64_GetPackSection((((struct Shared_World *) ((s8 *) world))->bitSections), 1);
    SetN64_GetPackSection(packSectionResult, 0);
    result = (u8 *)((char *)SetN64_GetPackSection(packSectionResult, 1)) + triggerIndex;
    return *result == 0;
}

void *Scene_RequestBinaryResourceByKey(Shared_World *world, s32 resourceId, s32 mode, s32 direct) {
    StridedTable *table;
    s32 idx;
    s32 resourceSize;
    s32 result;

    table = world->lookupTable;
    idx = Defs_FindSortedValue(table->data, table->count, resourceId);
    if (idx == -1) {
        return 0;
    }
    result = SetN64_LocatePackSection(world->lookupDirectory, world->lookupBank, idx, &resourceSize);
    return Cache_RequestResource(0, result, result, resourceSize, mode, 0, &g_cResource_UnpackRequestEntry, &s_binaryBlockText, direct);
}

/* Starts a sound effect from the world's sound table: looks the id up (0 or unknown returns 0),
 * picks the effect's behaviour table (ids 5 and 7 have their own, everything else the default), sets
 * the loop/priority bits 0x4 or 0x18 from the id's range, and queues it through Cache_RequestResource. */
s32 Scene_StartWorldEffect(Shared_World *world, s32 id, s32 flags, s32 extra) {
    s32 index;
    s32 *behaviour;
    s32 handle;
    s32 out;

    if (id == 0) {
        return 0;
    }
    index = Defs_FindSortedValue(world->resourceKindTable->entries, world->resourceKindTable->count, id);
    if (index == -1) {
        return 0;
    }
    switch (id) {
    case 5:
        behaviour = &g_scene_UnpackImagesWithLowBoostEntry;
        break;
    case 7:
        behaviour = &g_scene_UnpackImagesWithHighBoostEntry;
        break;
    default:
        behaviour = &g_cResource_UnpackRequestEntry;
        break;
    }
    switch (id) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 100:
    case 101:
    case 102:
    case 103:
    case 104:
        flags |= 0x18;
        break;
    default:
        flags |= 4;
        break;
    }
    handle = SetN64_LocatePackSection(world->resourceKindDirectory, world->resourceKindBank, index, &out);
    return Cache_RequestResource(0, handle, handle, out, flags, world, behaviour, &s_graphicsetText, extra);
}

/* SCENE_FINDACTORTRIGGERRANGE.CPP */

void Scene_SpawnUnrotatedEffect(s32 worldAddress, s32 ownerId, Triple position, s32 modelId, f32 lifetime) {
    Triple zero;

    zero.x = 0;
    zero.y = 0;
    zero.z = 0;
    SetN64_SpawnModelEffect(&((Shared_World *)worldAddress)->effectSlots, 0, modelId, *(CVector3 *)&zero, *(CVector3 *)&position, ownerId, lifetime);
}

void *Scene_ResolveFloorPolygon(Triangle *triangle, CVector3 *position) {
    f32 lower;
    f32 upper;
    f32 value;

    if (triangle != 0 &&
        Region_IsPointInTriangleXZ(triangle, position->x,
                          position->z) != 0) {
        if (!((triangle)->flags & 0x40)) {
            return triangle;
        }
        lower = Region_GetPolygonHeight(triangle,
            position->x, position->z);
        upper = Graphu64_GetTrianglePlaneHeight(triangle,
            position->x, position->z);
        value = position->y;
        if (lower <= value && value <= upper) {
            return triangle;
        }
    }
    return Scene_FindFloorPolygon(&g_world, position);
}

/* Searches the counted pointer list of a world record for the first entry whose definition id equals the given id, returning it or null. */

LevelActor *Scene_FindSwitchByDefinitionId(Shared_World *world, s32 id) {
    s32 i;
    LevelActor *found = 0;

    for (i = 0; i < world->count; i++) {
        if (world->objects[i]->definition->character == id) {
            found = world->objects[i];
            break;
        }
    }
    return found;
}

void Scene_LocateTextureResource(void *world, s32 sectionIndex, s32 *resourceAddressOutput, s32 *sectionSizeOut) {
    *resourceAddressOutput = SetN64_LocatePackSection((((struct Shared_World *) ((s8 *) world))->textureDirectory), (((struct Shared_World *) ((s8 *) world))->textureBank), sectionIndex, sectionSizeOut);
}

s32 Scene_GetIndexedModelResource(Shared_World *world, s32 type) {
    s32 *directory = world->indexedDirectory;

    if (type < *directory) {
        return SetN64_GetDirectoryEntry(directory, world->indexedBank, type);
    }
    return 0;
}

s32 Scene_FindAlternateTriggerRange(Shared_World *world, u16 *triggerIds, s32 *firstIndex, s32 *lastIndex) {
    s32 groupFirst;
    s32 groupLast;
    s32 matchCount;
    s32 alternateRecordIndex;
    s32 alternateRecordCount;

    matchCount = Defs_FindSortedGroupRange(alternateRecordIndex, alternateRecordCount, *triggerIds,
        (alternateRecordIndex = (s32)(world)->alternateRecordIndex,
         alternateRecordCount = (world)->alternateRecordCount, &groupFirst), &groupLast);
    if (matchCount != 0) {
        *firstIndex = (s32)(world)->alternateRecordArray + (groupFirst * 20);
        matchCount = (groupLast - groupFirst) + 1;
        *lastIndex = matchCount;
    } else {
        *firstIndex = 0;
        *lastIndex = 0;
    }
    return matchCount;
}

void Scene_FindActorTriggerRange(Shared_World *world, LevelActor *levelActor, s32 *firstIndex, s32 *lastIndex) {
    s32 groupFirst;
    s32 last;
    s32 index;
    u32 first;
    s32 lastOffset;
    s32 sortedGroupRangeResult;
    s32 recordIndex;
    s32 recordCount;

    if (!((levelActor)->flags & 0x80000)) {
        first = (u32)(world)->actors;
        index = -1;
        if ((u32)levelActor >= first) {
            lastOffset = ((Shared_World *)world)->actorCapacity * 744;
            lastOffset -= 744;
            if (first + lastOffset >= (u32)levelActor) {
                index = ((u32)levelActor - first) / 744;
            }
        }
    } else {
        index = -1;
    }
    if (index == -1) {
        *lastIndex = 0;
        return;
    }
    sortedGroupRangeResult = Defs_FindSortedGroupRange(recordIndex, recordCount, index,
        (recordIndex = (s32)(world)->recordIndex,
         recordCount = (world)->recordCount, &groupFirst), &last);
    if (sortedGroupRangeResult != 0) {
        *firstIndex = (s32)(world)->recordArray + (groupFirst * 20);
        *lastIndex = (last - groupFirst) + 1;
    } else {
        *firstIndex = 0;
        *lastIndex = 0;
    }
}

void Scene_ActivateTriggersOfKind(Shared_World *world, s32 triggerKind) {
    s32 primaryRemaining;
    s32 alternateRemaining;
    WorldTrigger *trigger;
    WorldTrigger *alternateTrigger;

    primaryRemaining = world->recordCount;
    trigger = world->recordArray;
    primaryRemaining -= 1;
    if (primaryRemaining != -1) {
        do {
            if (trigger->kind == triggerKind) {
                Link_ActivateTrigger(trigger);
            }
            primaryRemaining -= 1;
            trigger = trigger + 1;
        } while (primaryRemaining != -1);
    }
    alternateTrigger = world->alternateRecordArray;
    alternateRemaining = world->alternateRecordCount;
    alternateRemaining -= 1;
    if (alternateRemaining != -1) {
        do {
            if (alternateTrigger->kind == triggerKind) {
                Link_ActivateTrigger(alternateTrigger);
            }
            alternateRemaining -= 1;
            alternateTrigger = alternateTrigger + 1;
        } while (alternateRemaining != -1);
    }
}

s32 Scene_TestTriggerKindFlags(Shared_World *object, s32 type) {
    s32 index;
    WorldTrigger *record;
    u8 *flags;

    index = (object)->recordCount;
    record = (object)->recordArray;
    index--;
    if (index != -1) {
        flags = &record->flags;
        do {
            if (flags[1] == type &&
                (*flags & 0x40) == 0) {
                return 0;
            }
            index--;
            flags += sizeof(WorldTrigger);
        } while (index != -1);
    }

    index = (object)->alternateRecordCount;
    record = (object)->alternateRecordArray;
    index--;
    if (index != -1) {
        do {
            if (record->kind == type &&
                (record->flags & 0x40) == 0) {
                return 0;
            }
            index--;
            record++;
        } while (index != -1);
    }

    return 1;
}

/* SCENE_REGISTERACTORINSCENELISTS.CPP */

void Scene_DispatchSecondaryTriggersOfKind(Shared_World *world, s32 triggerKind) {
    WorldTrigger *trigger;
    WorldTrigger *edgeTrigger;
    s32 remainingFaces;
    s32 remainingEdges;

    remainingFaces = (world)->recordCount;
    trigger = (world)->recordArray;
    remainingFaces -= 1;
    if (remainingFaces != -1) {
        do {
            if (trigger->kind == triggerKind) {
                Link_DispatchTriggerExit(trigger);
            }
            remainingFaces -= 1;
            trigger += 1;
        } while (remainingFaces != -1);
    }

    remainingEdges = (world)->alternateRecordCount;
    edgeTrigger = (world)->alternateRecordArray;
    remainingEdges -= 1;
    if (remainingEdges != -1) {
        do {
            if (edgeTrigger->kind == triggerKind) {
                Link_DispatchTriggerExit(edgeTrigger);
            }
            remainingEdges -= 1;
            edgeTrigger += 1;
        } while (remainingEdges != -1);
    }
}

s32 Scene_QueueTriggerTimer(Shared_World *world, WorldTrigger *trigger) {
    CActiveLink *rec;
    f32 val;
    s32 flag;

    rec = world->freeTriggerTimers.head;
    if (rec != 0) {
        List_RemoveIntrusive(&world->freeTriggerTimers, rec);
        List_PrependIntrusive(&world->activeTriggerTimers, rec);
        (rec)->object = trigger;
    } else {
        rec = world->activeTriggerTimers.tail;
        Link_DispatchTrigger((rec)->object);
        (rec)->object = trigger;
    }
    val = recordValue((s32) trigger->lifetime);
    (rec)->remaining = val;
    flag = trigger->flags & 2;
    if (flag != 0) {
        (rec)->remaining = val * g_triggerTimerFrameScale;
    }
    return flag;
}

void Scene_UpdateTriggerTimers(Shared_World *world) {
    CActiveLink *node;
    void *next;
    WorldTrigger *object;
    s32 remove;
    s32 expired;
    f32 zero;
    f32 value;

    node = (world)->activeTriggerTimers.head;
    remove = 0;
    if (node != 0) {
        zero = 0.0f;
        do {
            object = (node)->object;
            next = (node)->next;
            expired = remove;
            if ((object)->flags & 2) {
                value = (node)->remaining - g_frameElapsedTime;
                (node)->remaining = value;
                if (value <= zero) {
                    expired = 1;
                    remove = 1;
                }
            }
            if (expired != 0) {
                Link_DispatchTrigger(object);
            }
            if (remove != 0) {
                List_RemoveIntrusive(&(world)->activeTriggerTimers, node);
                List_PrependIntrusive(&(world)->freeTriggerTimers, node);
            }
            node = next;
            remove = 0;
        } while (node != 0);
    }
}

/* Lights a point: blends the light volumes around it when the world's sectors hold any and lighting is on (g_vertexLightingMode), else copies the default lights g_playerModelLighting. */

static inline s32 worldHasLightVolumes(Shared_World *world) {
    s32 i;
    for (i = 0; i < world->sectorCount; i++) {
        if (((LightVolumeList *)SetN64_GetPackSection((void *)world->sectors[i].resource->data, 2))->count != 0) {
            return 1;
        }
    }
    return 0;
}
void Scene_SampleWorldLighting(Shared_World *world, CVector3 *position, Shared_ParticleLighting *out) {
    SceneLightVolume *volumes[10];
    s32 count;
    if (!worldHasLightVolumes(world) || g_vertexLightingMode == 0) {
        *out = *(Shared_ParticleLighting *)&g_playerModelLighting[0];
    } else {
        Scene_FindLightVolumes(world, position, volumes, &count);
        Scene_SampleVolumeLighting(volumes, count, position, out);
    }
}

/* Searches the counted pointer list of a world record for the first entry whose definition id equals the given id, returning it or null. */

LevelActor *Scene_FindTypeFourteenActorByDefinitionId(Shared_World *world, s32 id) {
    s32 i;
    LevelActor *found = 0;

    for (i = 0; i < world->specialActorCount; i++) {
        if (world->specialActors[i]->definition->character == id) {
            found = world->specialActors[i];
            break;
        }
    }
    return found;
}

/* Returns the object in the world's object list nearest to the current player actor, comparing whole-unit distances and starting from a bound of 9999999. */








#ifdef VERSION_EU
#endif

Player *Scene_FindNearestObjectToFirstPlayer(Shared_World *world) {
    CVector3 delta;
    Player *player;
    Player *object;
    Player *nearest;
    s32 best;
    s32 distance;
    s32 i;

#ifdef VERSION_EU
    player = Playerai_GetFirstPlayer(&g_playerViewRenderContext);
#else
    player = Playerai_GetFirstPlayer(&g_playerViewRenderContext);
#endif
    best = 9999999;
    nearest = 0;
    for (i = 0; i < world->specialActorCount; i++) {
        object = (Player *)world->specialActors[i];
        Graphu64_SubtractVectors(&delta, &object->pos, &player->pos);
        distance = Gu_Sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
        if (distance <= best) {
            nearest = object;
            best = distance;
        }
    }
    return nearest;
}

/* Registers an object with a world after preparing it with Gobjinst_RotatePoseMatrixBuffers: adds it to the lists of objects accepted by InstHdr_CanActorReceiveInteraction and InstHdr_HasEnabledMotionHooks, to the list of all objects, to the type 1 list (storing its slot in the object), to the list of objects flagged 2, to the type 5 list, and to the lists of model 0x64F and model 0x64D objects, each while that list has room. */







extern void Gobjinst_RotatePoseMatrixBuffers(void *actorRenderState);

extern s32 InstHdr_HasEnabledMotionHooks(void *actor);

void Scene_RegisterActorInSceneLists(Shared_World *world, LevelActor *object) {
    Gobjinst_RotatePoseMatrixBuffers(object);
    if (InstHdr_CanActorReceiveInteraction(object) != 0) {
        s32 n = world->interactiveCount;
        if (n != 512) {
            world->interactive[n] = (LevelActor *)object;
            world->interactiveCount = n + 1;
        }
    }
    if (InstHdr_HasEnabledMotionHooks(object) != 0) {
        s32 n = world->moverCount;
        if (n != 128) {
            world->movers[n] = (LevelActor *)object;
            world->moverCount = n + 1;
        }
    }
    {
        s32 n = world->registeredCount;
        if (n < 128) {
            world->registered[n] = (LevelActor *)object;
            world->registeredCount = n + 1;
        }
    }
    {
        s32 n = world->kind1Count;
        if (n < 64 && object->definition->kind == 1) {
            world->kind1[n] = (LevelActor *)object;
            ((s8 *)object)[(u32)&((LevelActor *)0)->actionReady + 2] = world->kind1Count++;
        }
    }
    {
        s32 n = world->flaggedCount;
        if (n < 32 && (object->flags & 2)) {
            world->flagged[n] = (LevelActor *)object;
            world->flaggedCount = n + 1;
        }
    }
    {
        s32 n = world->kind5Count;
        if (n < 16 && object->definition->kind == 5) {
            world->kind5[n] = (LevelActor *)object;
            world->kind5Count = n + 1;
        }
    }
    {
        s32 n = world->model64FCount;
        if (n < 32 && object->type == 1615) {
            world->model64F[n] = (LevelActor *)object;
            world->model64FCount = n + 1;
        }
    }
    if (object->type == 1613) {
        s32 n = world->model64DCount;
        if (n < 4) {
            world->model64D[n] = (LevelActor *)object;
            world->model64DCount = n + 1;
        }
    }
}

/* Returns the nearest other object matching the optional team, kind and active filters, by squared distance. */
LevelActor *Scene_FindNearestMatchingActor(Shared_World *world, LevelActor *self, s32 team, s32 kind, s32 activeOnly) {
    s32 i;
    LevelActor *obj;
    LevelActor *best;
    f32 min;
    f32 dx, dy, dz, distSq;

    s32 count;

    i = 0;
    min = 3.4028235e38f;
    count = world->actorCapacity;
    best = 0;
    for (; i < count; i++) {
        obj = &world->actors[i];
        if (obj == self) {
            continue;
        }
        if (team != -1 && obj->type != team) {
            continue;
        }
        if (kind != -1 && obj->definition->kind != kind) {
            continue;
        }
        if (activeOnly && obj->active == 0) {
            continue;
        }
        dx = self->position0.x - obj->position0.x;
        dy = self->position0.y - obj->position0.y;
        dz = self->position0.z - obj->position0.z;
        distSq = dx * dx + dy * dy + dz * dz;
        if (distSq < min) {
            min = distSq;
            best = obj;
        }
    }
    return best;
}

/* Returns the entry in an object's pointer list, counted by its list size, whose position lies nearest a given position, or null when none lies closer than g_transitionAlphaScaleTable. */

LevelActor *Scene_FindNearestListedEntry(Shared_World *owner, LevelActor *pos) {
    s32 i;
    LevelActor *best;
    f32 min;
    LevelActor **entries;
    f32 dx, dy, dz, distSq;
    LevelActor *e;
    s32 n;
    LevelActor **p;

    i = 0;
    best = 0;
    min = (3.4028234663852886e+38f);
    n = owner->model64FCount;
    entries = owner->model64F;
    if (i < n) {
        p = entries;
        do {
            e = *p;
            dx = pos->position0.x - e->position0.x;
            dx = dx * dx;
            dy = pos->position0.y - e->position0.y;
            dy = dy * dy;
            dz = pos->position0.z - e->position0.z;
            dz = dz * dz;
            distSq = (dx + dy) + dz;
            if (distSq < min) {
                min = distSq;
                best = e;
            }
            i++;
            p++;
        } while (i < n);
    }
    return best;
}

/* Finds the first of the object's listed actors (its actor count and pointer array) linked to an id, clears that actor's link and relinks every other actor with that id to it; returns the
   actor, or 0. */




LevelActor *Scene_ResolveActorLinkGroup(Shared_World *obj, int id) {
    int i;
    LevelActor *found;
    int count;
    LevelActor **list;

    i = 0;
    found = 0;
    count = obj->registeredCount;
    list = (LevelActor **)obj->registered;
    for (; i < count; i++) {
        if ((s32) list[i]->controller == id) {
            found = list[i];
            found->controller = 0;
            break;
        }
    }
    for (i = 0; i < count; i++) {
        if ((s32) list[i]->controller == id) {
            list[i]->controller = found;
        }
    }
    return found;
}

void Scene_ClearActorLinksById(Shared_World *scene, s32 linkId) {
    s32 count;
    s32 i;
    LevelActor **arr;
    void *entry;

    i = 0;
    count = scene->registeredCount;
    arr = &scene->registered[0];
    if (count > 0) {
        do {
            entry = *arr;
            if ((s32) ((LevelActor *)((entry)))->controller == linkId) {
                ((LevelActor *)((entry)))->controller = 0;
            }
            i += 1;
            arr += 1;
        } while (i < count);
    }
}

void Scene_ApplyDamageToTypeOneActors(Shared_World *world, s32 damage, s32 flags) {
    CDamageInfo event;
    LevelActor **actors;
    s32 count;
    s32 i;

    Barrel_FillDamagePacket(&event, 0, damage, 102.399994f, flags, 0);
    count = world->kind1Count;
    actors = world->kind1;
    for (i = 0; i < count; i++) {
        Barrel_RunDamageHook(actors[i], &actors[i]->behaviorFlags, &event);
    }
}

/* SCENE_DRAWTRANSITIONCOLOROVERLAY.CPP */

/* Draws each selected entry in the object range with shared position and scale. */

void Scene_SetTypeThreeActorStateBits(Shared_World *world) {
    s32 i, count, three, offset, field;
    Shared_World *object;
    LevelActor *entry;

    object = world;
    count = object->actorCapacity;
    i = 0;
    if (count > 0) {
        three = 3;
        offset = 0;
        do {
            object = world;
            entry = (void *)((char *)object->actors + offset);
            field = ((struct Def *)entry->definition)->type;
            if (field != three) {
                i += 1;
            } else {
                Rumble_SetActorStateBit(world, entry, 1);
                i += 1;
            }
            offset += 744;
        } while (i < count);
    }
}

void Scene_ClearTypeThreeActorStateBits(Shared_World *world) {
    s32 i, count, three, offset, field;
    Shared_World *object;
    LevelActor *entry;

    object = world;
    count = object->actorCapacity;
    i = 0;
    if (count > 0) {
        three = 3;
        offset = 0;
        do {
            object = world;
            entry = (void *)((char *)object->actors + offset);
            field = ((struct Def *)entry->definition)->type;
            if (field != three) {
                i += 1;
            } else {
                Rumble_SetActorStateBit(world, entry, 0);
                i += 1;
            }
            offset += 744;
        } while (i < count);
    }
}

/** Return an indexed record from the world's strided table. */
void *Scene_GetEffectCurveRecord(Shared_World *world, s32 index) {
    StridedTable *table = world->stridedRecords;

    return &table->data[index * table->stride];
}

void CScene_StartEventClips(Shared_World *scene,s32 resource,s32 group,Triple pos,f32 firstValue,f32 secondValue) {
 s32 groupFirstIndex,groupLastIndex; void *data; s32 count; StridedTable *clipRecords; s32 i; StridedTable *clipGroups;
 clipGroups=scene->eventClipGroups;
 data=clipGroups->data;count=clipGroups->count;
 if(Defs_FindSortedGroupRange(data,count,group,&groupFirstIndex,&groupLastIndex)) {
  for(i=groupFirstIndex;i<=groupLastIndex;i++) {
   clipRecords=scene->eventClipDefinitions;
   Rumble_AllocatePoolNode(resource,(char *)clipRecords+(i*clipRecords->stride+8),*(CVector3 *)&pos,firstValue,secondValue,0);
  }
 }
}

void *Scene_GetActorDefinition(void *world, s32 index) {
    void *result;

    if (index == -1) {
        goto ret_null;
    }
    result = SetN64_GetPackSection(((struct Shared_World *) ((s8 *) world))->actorDefinitions, index);
    goto end;
ret_null:
    result = 0;
end:
    return result;
}

void *Scene_FindActorDefinition(Shared_World *world, s32 selection, s32 modelKind) {
    s32 *descriptor;
    s32 count;
    s32 i;
    ActorDefinitionHeader *entry;

    descriptor = world->actorDefinitions;
    count = *descriptor;
    for (i = 0; i < count; i++) {
        entry = SetN64_GetPackSection(world->actorDefinitions, i);
        if (selection != -1 && entry->kind != selection) {
            continue;
        }
        if (modelKind == -1) {
            return entry;
        }
        if (entry->character != modelKind) {
            continue;
        }
        return entry;
    }
    return 0;
}

/* Collects matching actors from the remaining allocation range; -1 skips a filter. */
s32 Scene_CollectMatchingLevelActors(Shared_World *container, s32 key0, s32 key1, s32 key2, LevelActor **out, s32 max) {
    s32 i = container->createdActorCount;
    s32 end = container->actorCapacity;
    LevelActor *base = container->actors;
    s32 count = 0;
    LevelActor *rec;

    for (; i < end; i++) {
        rec = &base[i];
        if (count >= max) {
            return count;
        }
        if ((key0 == -1 || rec->type == key0) && (key1 == -1 || rec->definition->kind == key1)
            && (key2 == -1 || rec->definition->character == key2)) {
            *out++ = rec;
            count++;
        }
    }
    return count;
}

void Scene_DrawTransitionColorOverlay(Shared_World *world) {
    s8 color[4];
    s32 state;
    ColorEntry *entry;
    f32 alpha;
    s32 converted;

    state = world->frozen;
    if (state == 0) {
        return;
    }
    if (state < 0) {
        return;
    }
    if (state >= 3) {
        return;
    }
    {
        entry = &((ColorEntry *)&g_emacText)[world->selectionState];
        if (entry->value != 0.0f) {
            color[0] = entry->red;
            color[1] = entry->green;
            color[2] = entry->blue;
            alpha = (world->selectionTimer * g_transitionAlphaScaleTable[1]) /
                    entry->value;
            if (!(g_transitionAlphaUnsignedConversionBase <= alpha)) {
                converted = (s32)alpha;
            } else {
                converted = (s32)(alpha - g_transitionAlphaUnsignedConversionBase);
                converted |= SIGN_BIT_32;
            }
            color[3] = converted;
            SetN64_DrawColorRectangle(&g_gameSession, color, 0, 0, g_hudReferenceViewportWidth,
                          g_hudReferenceViewportHeight);
        }
    }
}

char *Scene_GetPlatformRoute(void *world, s32 index) {
    return SetN64_GetPackSection(SetN64_GetPackSection((((struct Shared_World *) ((s8 *) world))->routeCount), index), 0);
}

/* SCENE_FINDTRACKEDACTORS.CPP */

/* SCENE_14.CPP */









extern void Scene_ReleaseCachedLevelData(Shared_World *world);







struct EffectSlotPool; struct Shared_World;

/* Advances the fractional animation clock and updates every active object with the resulting tick flag. */

/* Releases the resource of each of the owner's listed entries through Cache_UnlockResource, then clears its three entry counters, and moves the entry count to 0x1500 and zeroes it. */

void *Scene_GetPlatformRoutePoint(Shared_World *world, s32 routeIndex, s32 pointIndex) {
    void *route;
    ResidentDataChunk *pointTable;
    s32 pointStride;

    route = SetN64_GetPackSection(world->routeCount, routeIndex);
    pointTable = SetN64_GetPackSection(route, 1);
    pointStride = pointTable->width;
    return pointTable->data + (pointIndex * pointStride);
}

s32 Scene_FindNearestRouteFrame(Shared_World *worldPointer, s32 routeIndex, void *queryPosition) {
    CVector3 position;
    AnimationPoseFrameSet *list;
    AnimationPoseFrame *item;
    f32 distSq;
    f32 bestDist;
    f32 bestIndex;
    s32 count;
    s32 index;

    bestIndex = g_nearestRouteFrameAbsentIndex;
    bestDist = 0.0f;
    index = 0;
    list = SetN64_GetPackSection(SetN64_GetPackSection(worldPointer->routeCount, routeIndex), 1);
    count = list->count;
    item = list->frames;
    if (count > 0) {
        do {
            Graphu64_SubtractVectors(&position, queryPosition, item);
            distSq = (position.x * position.x) +
                     (position.y * position.y) +
                     (position.z * position.z);
            if ((bestIndex < 0.0f) || (distSq < bestDist)) {
                bestIndex = (f32)index;
                bestDist = distSq;
            }
            index += 1;
            item++;
        } while (index < count);
    }
    return (s32)bestIndex;
}

void Scene_CopyLevelName(Shared_World *world, s32 type, void *levelName, s32 maximumBytes) {
    s32 specialTable;
    s32 resourceKey;
    s32 levelIndexHandle;
    CachedResource *node;
    s32 count;

    resourceKey = SetN64_GetDirectoryEntry(world->resourceDirectory, world->resourceBank, type);
    levelIndexHandle = Cache_RequestWordCountedResourcePinned(0, &specialTable, resourceKey, g_levelIndexText);
    node = Cache_RequestPackSection(0, specialTable, 8, resourceKey, (s32)world, 0, &g_sceneLevelNameRequestTagDe + 4);
    count = node->dataSize;
    if (maximumBytes < count) {
        count = maximumBytes;
    }
    Libc_CopyBytes(levelName, node->data, count);
    Cache_ReleaseResource(0, (s32)node);
    if (world->level != type) {
        Cache_ReleaseResource(0, levelIndexHandle);
    }
}

void *Scene_GetBlLevelData(Shared_World *world, s32 record) {
    s32 sectionSize;
    void **resource;
    s32 key;
    s32 size;
    s32 one;

    if (world->resourceHandle == 0 || world->resourceKey != record) {
        Scene_ReleaseCachedLevelData(world);
        if (world->challengeFile != 0) {
            size = 16;
            one = 1;
            resource = Cache_RequestResource(0, world->challengeFile,
                                     world->challengeFile,
                                     world->challengeFileSize, size, 0, 0,
                                     g_sceneResourceRequestSpareDe, one);
            if (resource != 0) {
                key = SetN64_LocatePackSection((s32)*resource, world->challengeFile,
                                    record, &sectionSize);
                Cache_ReleaseResource(0, resource);
                if ((world->resourceHandle =
                     Cache_RequestResource(0, key, key, sectionSize, size, 0,
                                   &g_cResource_UnpackRequestEntry, g_sceneUnpackRequestSpare, one)) != 0) {
                    world->resourceKey = record;
                } else {
                    return 0;
                }
            }
        }
    }
    if (world->resourceHandle != 0) {
        return *world->resourceHandle;
    }
    return 0;
}

void Scene_ReleaseCachedGeometry(Shared_World *world) {
    s32 *list;
    s32 val;

    if (world->cachedGeometryHandle != 0) {
        list = (s32 *) SetN64_GetPackSection(world->cachedGeometryPack, 0);
        if (*list != 0) {
            do {
                val = *list;
                list += 1;
                Cache_UnlockResource(0, val);
            } while (*list != 0);
        }
        Cache_ReleaseResource(0, world->cachedGeometryHandle);
        world->cachedGeometryHandle = 0;
        world->cachedGeometryPack = 0;
    }
}

void Scene_CollectVisibleEffects(s32 results) {
    Shared_World *world = (Shared_World *)results;
    SetN64_CollectVisibleEffectNodes(&world->effectSlots, world);
}

/** Clear the object field. */
void Scene_ClearTransparentInstanceCount(void *object) {
    Shared_World *record = object;
    record->drawableCount = 0;
}

/** Clear the scene counters and linked state fields. */
void Scene_ClearSceneObjectCounts(Shared_World *object) {
    (object)->interactiveCount = 0;
    (object)->moverCount = 0;
    (object)->queuedCount = 0;
    (object)->registeredCount = 0;
    (object)->kind1Count = 0;
    (object)->flaggedCount = 0;
    (object)->kind5Count = 0;
    (object)->model64FCount = 0;
    (object)->model64DCount = 0;
    (object)->drawableCount = 0;
    (object)->sectorCount = 0;
}

void Scene_UpdateStaticEventInstances(Shared_World *scene)
{
  f32 nextEventPhase;
  s32 object;
  int firstIndex;
  s32 instanceIndex;
  s32 dispatchAll;

  nextEventPhase = scene->eventPhase + 1.0f;
  scene->eventPhase = nextEventPhase;
  dispatchAll = 1;
  if (!(nextEventPhase > 0.0f))
  {
    dispatchAll = 0;
  }
  if (dispatchAll != 0)
  {
    scene->eventPhase = (f32) (nextEventPhase - ((f32) (((s32) nextEventPhase) + 1)));
  }
  instanceIndex = (firstIndex = 0);
  if (scene->queuedCount > firstIndex)
  {
    do
    {
      object = (s32) scene->queued[instanceIndex];
      Statinst_DispatchAttachmentEvents(object, dispatchAll);
      instanceIndex += 1;
    }
    while (instanceIndex < scene->queuedCount);
  }
}

s32 Scene_GetLevelActorIndex(void *container, void *actorStorage) {
    Shared_World *scene = container;
    LevelActor *actor = actorStorage;
    LevelActor *base;

    if (actor->flags & 0x80000) {
        return -1;
    }
    base = scene->actors;
    if (actorStorage >= base &&
        (char *)actorStorage <= (char *)base + ((u32)scene->actorCapacity * sizeof(LevelActor) - sizeof(LevelActor))) {
        return ((u32)actorStorage - (u32)base) / 744;
    }
    return -1;
}

void Scene_FindSelectedTriggerRange(Shared_World *world, s32 useAlternateRecords, s32 group, s32 *recordsOutput, s32 *countOutput) {
    s32 firstRecordIndex;
    s32 lastRecordIndex;
    s32 recordIndex;
    s32 recordCount;
    s32 offset;

    if (useAlternateRecords != 0) {
        recordIndex = (s32)(world)->alternateRecordIndex;
        recordCount = (world)->alternateRecordCount;
    } else {
        recordIndex = (s32)(world)->recordIndex;
        recordCount = (world)->recordCount;
    }
    if (Defs_FindSortedGroupRange(recordIndex, recordCount, group, &firstRecordIndex, &lastRecordIndex) != 0) {
        offset = firstRecordIndex * 20;
        if (useAlternateRecords != 0) {
            *recordsOutput = (s32)(world)->alternateRecordArray + offset;
        } else {
            *recordsOutput = (s32)(world)->recordArray + offset;
        }
        *countOutput = (lastRecordIndex - firstRecordIndex) + 1;
    } else {
        *recordsOutput = 0;
        *countOutput = 0;
    }
}

void Scene_UnlockActiveSectionResources(Shared_World *owner) {
    s32 i;
    s32 n;
    s32 count;
    WorldSector *entries;

    n = owner->sectorCount;
    entries = owner->sectors;
    for (i = 0; i < n; i++) {
        Cache_UnlockResource(0, (s32)entries[i].resource);
    }
    count = owner->sectorCount;
    owner->interactiveCount = 0;
    owner->queuedCount = 0;
    owner->drawableCount = 0;
    owner->sectorCount = 0;
    owner->sectorEntryCount = count;
}

void Scene_ResetTransitionViewport(void) {
    s32 viewportWidth;
    s32 viewportHeight;

    Cinema_SetLoopMode(0);
    Cinema_SetResponse(g_sceneTransitionCinemaResponseDe);
    viewportWidth = 480;
    if (g_frontendCurrentVideoModeIndex == 0) {
        viewportWidth = 380;
        viewportHeight = 220;
    } else {
        viewportHeight = 360;
    }
    Cinema_SetViewport(viewportWidth, viewportHeight, 0, 0);
}

void Scene_CacheBlLevelData(Shared_World *world, s32 sectionIndex) {
    s32 sectionSize;
    void **resource;
    s32 key;
    s32 size;
    s32 one;

    if (world->resourceHandle == 0 || world->resourceKey != sectionIndex) {
        Scene_ReleaseCachedLevelData(world);
        if (world->challengeFile != 0) {
            size = 16;
            one = 1;
            resource = Cache_RequestResource(0, world->challengeFile,
                                     world->challengeFile,
                                     world->challengeFileSize, size, 0, 0,
                                     g_sceneResourceRequestSpareDe, one);
            if (resource != 0) {
                key = SetN64_LocatePackSection((s32)*resource, world->challengeFile,
                                    sectionIndex, &sectionSize);
                Cache_ReleaseResource(0, resource);
                if ((world->resourceHandle =
                     Cache_RequestResource(0, key, key, sectionSize, size, 0,
                                   &g_cResource_UnpackRequestEntry, g_sceneUnpackRequestSpare, one)) != 0) {
                    world->resourceKey = sectionIndex;
                }
            }
        }
    }
}
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
#if defined(VERSION_US)

float g_trackedActorScaleTriple[3] = {
    1.0f, 1.0f, 1.0f,
};
#endif
#endif

void Scene_ReleaseCachedLevelData(Shared_World *world) {
    void *handle;

    handle = world->resourceHandle;
    if (handle != 0) {
        Cache_ReleaseResource(0, handle);
        world->resourceHandle = 0;
        world->resourceKey = -1;
    }
}

void Scene_AccessLevelStateSection(struct Shared_World *world, s32 usePrimaryLevels, s32 index, s32 levelIndex) {
    void *base;
    void *table;

    if (usePrimaryLevels != 0) {
        base = world->bitSections;
    } else {
        base = world->secondaryLevels;
    }
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(base, 0), levelIndex), index);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    SetN64_GetPackSection(table, 1);
}

void Scene_SetSelectedLevelStateBit(struct Shared_World *world, s32 usePrimaryLevels, s32 index, s32 levelIndex, s32 bitIndex, s32 enabled) {
    void *base;
    void *table;
    u8 *stateBytes;
    u8 *stateBytesForClear;
    s32 mask;
    s32 idx;
    s32 clearBitIndex;

    if (usePrimaryLevels != 0) {
        base = world->bitSections;
    } else {
        base = world->secondaryLevels;
    }
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(base, 0), levelIndex), index);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    stateBytes = SetN64_GetPackSection(table, 1);
    stateBytesForClear = stateBytes;
    mask = 1 << (bitIndex & 7);
    if (enabled != 0) {
        idx = bitIndex;
        if (bitIndex < 0) {
            idx = bitIndex + 7;
        }
        stateBytes[idx >> 3] |= mask;
        return;
    }
    clearBitIndex = bitIndex;
    if (clearBitIndex < 0) {
        clearBitIndex += 7;
    }
    stateBytesForClear[clearBitIndex >> 3] &= ~mask;
}

s32 Scene_TestSelectedLevelStateBit(struct Shared_World *world, s32 usePrimaryLevels, s32 index, s32 levelIndex, s32 bitIndex) {
    void *base;
    void *table;
    u8 *stateBits;
    s32 mask;
    s32 i;

    if (usePrimaryLevels != 0) {
        base = world->bitSections;
    } else {
        base = world->secondaryLevels;
    }
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(base, 0), levelIndex), index);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32)table, 1);
    stateBits = SetN64_GetPackSection(table, 1);
    mask = 1 << (bitIndex & 7);
    i = bitIndex;
    if (i < 0) {
        i += 7;
    }
    return (stateBits[i >> 3] & mask) != 0;
}

s32 Scene_TestSecondaryLevelBit(Shared_World *worldStorage, s32 index, s32 bitIndex) {
    void *table;
    u8 *stateBits;
    s32 mask;
    s32 i;

    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(worldStorage->secondaryLevels, 0), index), 0);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32)table, 1);
    stateBits = SetN64_GetPackSection(table, 1);
    mask = 1 << (bitIndex & 7);
    i = bitIndex;
    if (i < 0) {
        i += 7;
    }
    return (stateBits[i >> 3] & mask) != 0;
}

s32 Scene_TestActorBitForLevel(Shared_World *world, s32 index, s32 actorIndex) {
    void *table;
    u8 *stateBits;
    s32 mask;
    s32 i;

    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(world->bitSections, 0), index), 0);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32)table, 1);
    stateBits = SetN64_GetPackSection(table, 1);
    mask = 1 << (actorIndex & 7);
    i = actorIndex;
    if (i < 0) {
        i += 7;
    }
    return (stateBits[i >> 3] & mask) != 0;
}

s32 Scene_TestRecordBitForLevel(Shared_World *world, s32 index, s32 recordIndex) {
    void *table;
    u8 *stateBits;
    s32 mask;
    s32 i;

    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(world->bitSections, 0), index), 1);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32)table, 1);
    stateBits = SetN64_GetPackSection(table, 1);
    mask = 1 << (recordIndex & 7);
    i = recordIndex;
    if (i < 0) {
        i += 7;
    }
    return (stateBits[i >> 3] & mask) != 0;
}

s32 Scene_TestTriggerBitForLevel(Shared_World *world, s32 index, s32 triggerIndex) {
    void *table;
    u8 *stateBits;
    s32 mask;
    s32 i;

    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(world->bitSections, 0), index), 2);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32)table, 1);
    stateBits = SetN64_GetPackSection(table, 1);
    mask = 1 << (triggerIndex & 7);
    i = triggerIndex;
    if (i < 0) {
        i += 7;
    }
    return (stateBits[i >> 3] & mask) != 0;
}

s32 Scene_GetTriggerCounterAddress(Shared_World *world, s32 triggerIndex) {
    void *packSectionResult;
    packSectionResult = SetN64_GetPackSection(world->bitSections, 1);
    SetN64_GetPackSection(packSectionResult, 0);
    return SetN64_GetPackSection(packSectionResult, 1) + triggerIndex;
}

void Scene_SwapDistanceSortEntries(WorldSortEntry *left, WorldSortEntry *right) {
    WorldSortEntry tmp;

    tmp = *left;
    *left = *right;
    *right = tmp;
}

s32 Scene_CompareDistanceAscending(WorldSortEntry *left, WorldSortEntry *right) {
    s32 result;
    result = 1;
    if ((left->distance) < (right->distance)) {
        result = -1;
    }
    return result;
}

s32 Scene_CompareDistanceDescending(WorldSortEntry *left, WorldSortEntry *right)
{
  f32 leftDistance;
  s32 sortOrder;
  leftDistance = left->distance;
  sortOrder = 1;
  if ((right->distance) < leftDistance)
  {
    sortOrder = -1;
  }
  return sortOrder;
}

void Scene_CollectTypeFourteenActors(Shared_World *world) {
    s32 found;
    s32 clearIndex;
    LevelActor *record;
    struct Shared_Pickup **clearPtr;
    struct Shared_Pickup **out;
    s32 wantedType;

    found = 0;
    clearIndex = 15;
    record = world->actors;
    world->specialActorCount = 0;
    do {
        world->specialActors[clearIndex] = 0;
        clearIndex--;
    } while (clearIndex >= 0);

    if (world->actorCapacity > 0) {
        clearIndex = 0;
        wantedType = 14;
        do {
            if (((struct Def *)record->definition)->type == wantedType) {
                world->specialActors[found] = record;
                found++;
            }
            if (found >= 16) {
                break;
            }
            clearIndex++;
            if (clearIndex >= world->actorCapacity) {
                break;
            }
            record++;
        } while (1);
    }
    world->specialActorCount = found;
}

void Scene_FindTrackedActors(Shared_World *world) {
    LevelActor *actor = world->actors;
    s32 i;
    g_fragTagObjectiveActor = 0;
    for (i = 0; i < 4; i++) {
        g_sceneTrackedActors[i] = 0;
    }
    for (i = 0; i < world->actorCapacity; actor++, i++) {
        struct Def *def = (struct Def *)actor->definition;
        if (def->type == 3) {
            if (Scene_GetModelIdAtIndex(&g_world, def->id) == 3031) {
                g_fragTagObjectiveActor = actor;
                return;
            }
        } else if (def->type == 10) {
            switch (actor->type) {
            case 1619:
                g_sceneTrackedActors[0] = actor;
                break;
            case 1620:
                g_sceneTrackedActors[1] = actor;
                break;
            case 1621:
                g_sceneTrackedActors[2] = actor;
                break;
            case 1622:
                g_sceneTrackedActors[3] = actor;
                break;
            }
        }
    }
}

/* SCENE_UNPACKIMAGESWITHHIGHBOOST.CPP */

/* Collects platform actors, records the special actor and selects one of three random states. */

void Scene_CollectSecondarySpecialActors(LevelActorArrayView *scene) {
    s32 count = 0;
    s32 i;
    LevelActor *actor = scene->actors;

    g_sceneFlagReturnPickupActor = 0;
    for (i = 9; i >= 0; i--) {
        g_sceneSpecialActorTables[i] = 0;
    }
    if (scene->count > 0) {
        i = 0;
        do {
            if (((struct Def *)actor->definition)->type == 3) {
                if (((struct Def *)actor->definition)->id == 3030) {
                    g_sceneFlagReturnPickupActor = actor;
                }
            } else if (((struct Def *)actor->definition)->type == 10) {
                if (actor->type == 1614) {
                    g_sceneSpecialActorTables[count++] = actor;
                }
            }
            if (count >= 10) {
                return;
            }
            actor++;
        } while (++i < scene->count);
    }
    g_gameSettings.counters.m_nFragTagSkin = XPlus_NextRandomInteger() % 3;
}

/* Remaps every 4-bit pixel of every image in each of the 256 entries of a table through the given
   nibble table. */

void Scene_RemapFourBitImagePixels(void *cacheContext, void *table, u8 *remap) {
    s32 i;
    void *data;
    u8 tag;
    ImageSet *set;
    struct IntPair *image;
    s32 rows;
    s32 columns;
    u32 count;
    u8 *pixel;
    s32 hi;
    s32 lo;
    s32 end;
    s32 width;
    s32 height;

    i = 0;
    end = -1;
    for (; i < 256; i++) {
        end = -1;
        OnScreen_GetImageEntry(table, i, &data, &tag);
        rows = data == 0;
        if (rows) {
            continue;
        }
        set = data;
        rows = set->rows;
        rows--;
        image = (struct IntPair *)(set + 1);
        while (1) {
            if (rows == end) {
                break;
            }
            columns = set->columns;
            columns--;
            for (; columns != end; columns--) {
                width = image->first;
                height = image->second;
                count = (u32)(width * height) >> 1;
                pixel = (u8 *)(image + 1);
                while (count--) {
                    hi = *pixel >> 4;
                    lo = *pixel & 0xF;
                    hi = remap[hi];
                    lo = remap[lo];
                    *pixel = (hi << 4) | lo;
                    pixel++;
                }
                image = (struct IntPair *)((u8 *)image + ((u32)(width * height) >> 1));
                image++;
            }
            rows--;
        }
    }
}

/* Remaps every 4-bit pixel of every image in each of the 256 entries of a resource through the nibble table g_imageLowBoostNibbleRemap, once the resource has been loaded by Ppdecom_UnpackResource_SceneUnpackimageswithhighboost. */

void Scene_UnpackImagesWithLowBoost(void *cacheContext, void **resource) {
    s32 i;
    void *data;
    u8 tag;
    void *table;
    u8 *remap;
    ImageSet *set;
    struct IntPair *image;
    s32 rows;
    s32 columns;
    u32 count;
    u8 *pixel;
    s32 hi;
    s32 lo;
    s32 end;
    s32 width;
    s32 height;

    end = Ppdecom_UnpackResource(resource, 0) == 0;
    if (end) {
        return;
    }
    table = *resource;
    remap = g_imageLowBoostNibbleRemap;
    do {
        for (i = 0; i < 256; i++) {
            end = -1;
            OnScreen_GetImageEntry(table, i, &data, &tag);
            if (data == 0) {
                continue;
            }
            set = data;
            rows = set->rows;
            rows--;
            image = (struct IntPair *)(set + 1);
            while (1) {
                if (rows == end) {
                    break;
                }
                columns = set->columns;
                columns--;
                for (; columns != end; columns--) {
                    width = image->first;
                    height = image->second;
                    count = (u32)(width * height) >> 1;
                    pixel = (u8 *)(image + 1);
                    while (count--) {
                        hi = *pixel >> 4;
                        lo = *pixel & 0xF;
                        hi = remap[hi];
                        lo = remap[lo];
                        *pixel = (hi << 4) | lo;
                        pixel++;
                    }
                    image = (struct IntPair *)((u8 *)image + ((u32)(width * height) >> 1));
                    image++;
                }
                rows--;
            }
        }
    } while (0);
}

/* Remaps every 4-bit pixel of every image in each of the 256 entries of a resource through the nibble table g_imageHighBoostNibbleRemap, once the resource has been loaded by Ppdecom_UnpackResource_SceneUnpackimageswithhighboost. */

void Scene_UnpackImagesWithHighBoost(void *cacheContext, void **resource) {
    s32 i;
    void *data;
    u8 tag;
    void *table;
    u8 *remap;
    ImageSet *set;
    struct IntPair *image;
    s32 rows;
    s32 columns;
    u32 count;
    u8 *pixel;
    s32 hi;
    s32 lo;
    s32 end;
    s32 width;
    s32 height;

    end = Ppdecom_UnpackResource(resource, 0) == 0;
    if (end) {
        return;
    }
    table = *resource;
    remap = g_imageHighBoostNibbleRemap;
    do {
        for (i = 0; i < 256; i++) {
            end = -1;
            OnScreen_GetImageEntry(table, i, &data, &tag);
            if (data == 0) {
                continue;
            }
            set = data;
            rows = set->rows;
            rows--;
            image = (struct IntPair *)(set + 1);
            while (1) {
                if (rows == end) {
                    break;
                }
                columns = set->columns;
                columns--;
                for (; columns != end; columns--) {
                    width = image->first;
                    height = image->second;
                    count = (u32)(width * height) >> 1;
                    pixel = (u8 *)(image + 1);
                    while (count--) {
                        hi = *pixel >> 4;
                        lo = *pixel & 0xF;
                        hi = remap[hi];
                        lo = remap[lo];
                        *pixel = (hi << 4) | lo;
                        pixel++;
                    }
                    image = (struct IntPair *)((u8 *)image + ((u32)(width * height) >> 1));
                    image++;
                }
                rows--;
            }
        }
    } while (0);
}



s32 Scene_TestSectorSectionTwoEntries(Shared_World *world)
{
  Shared_World *elem;
  s32 i;
  void *field;
  char *unusedPointer1;
  struct IntPair *ret;
  s32 count;
  count = world->sectorCount;
  if (count <= 0)
  {
    return 0;
  }
  i = 0;
  elem = world;
  do
  {
    field = world->sectors[i].resource;
    ret = SetN64_GetPackSection(*((s32 *) field), 2);
    if (((ret)->second) != 0)
    {
      if (world || i)
      {
        return 1;
      }
      else
      {
        return 1;
      }
    }
    count = world->sectorCount;
    i += 1;

  }
  while (i < count);
  return 0;
}

/** Return an indexed record from the table. */
void *Scene_GetStridedActorRecord(struct Shared_World *object, int index) {
    char *base = (char *)object->eventClipDefinitions;
    int stride = *(int *)base;
    return base + (index * stride + 8);
}

s32 Scene_TestNearbyActiveActor(LevelActor *actor, CVector3 *rightVector) {
    CVector3 vector;
    f32 magnitude;
    u16 type;

    Graphu64_SubtractVectors(&vector, &actor->position0, rightVector);
    magnitude = (vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z);
    if (actor->definition->kind != 1) {
        return 0;
    }
    type = actor->type;
    if (type == 1102 || type == 1107 || type == 1105 || type == 1104 ||
        type == 1108 || type == 1109 || type == 1110) {
        return 0;
    }
    if (actor->active == 0) {
        return 0;
    }
    if (actor->animationMarker == 61) {
        return 0;
    }
    return magnitude <= g_sceneImageVectorTolerance;
}

/* Reports whether rightVector is within range of actor, using its type and state to pick the check. */

s32 Scene_ClassifyNearbySpecialActor(LevelActor *player, CVector3 *rightVector) {
    CVector3 delta;
    u16 type;

    if (player->kind == 1 && player->definition->kind == 7) {
        Graphu64_SubtractVectors(&delta, &player->position0, rightVector);
        delta.y = 0;
        if (262144.0f < delta.x * delta.x + delta.z * delta.z) {
            return 0;
        }
        return 0xFF;
    }
    if (player->definition->kind != 1) {
        return 0;
    }
    type = player->type;
    if (type == 1102 || type == 1107 || type == 1105 || type == 1104 ||
        type == 1108 || type == 1109 || type == 1110) {
        return 0xFF;
    }
    return 0;
}

#if defined(VERSION_DE)
extern float g_imageUnpackEpsilonTriple[3];
#endif

/* SCENE_UPDATEANDDRAWWORLD_DATA.CPP */



/* G_LIGHTDIRECTIONLENGTH.CPP */



/* S_MATRICESTEXT.CPP */

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)
extern const unsigned char s_matricesText[9];
#endif

/* G_LEVELINDEXTEXT.CPP */

extern const char g_levelIndexText[12];

/* S_COLLISIONTEXT.CPP */

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_US)
const char g_collisionText[10] =
    "collision\000";
#endif
#if defined(VERSION_EU_X)
const char g_collisionText[12] =
    "collision\000\000\000";
#endif
#endif

#if defined(VERSION_US_REV1)
extern const char s_collisionText[10];
#endif

/* GRID_INDEX_AND_VISIBILITY_TEXT.CPP */

extern const char g_gridBoundsAndSectionsIndexText[32];

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)

#endif

/* TEMP_VIS_TEXT.CPP */

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)

#endif

/* S_LINKSTEXT.CPP */

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE) || defined(VERSION_EU_X) || defined(VERSION_US)
const char g_sceneLinksText[6] = "links\000";
#endif
#if defined(VERSION_EU)
const char g_sceneLinksText[8] =
    "links\000\000\000";
#endif
#endif

#if defined(VERSION_US_REV1)
extern const char s_linksText[6];
#endif

/* S_LEVELPATHSTEXT.CPP */
extern const char s_levelPathsText[12];

/* SCENE_LOADLEVELRESOURCES_DATA.CPP */

#if defined(VERSION_DE)

#endif

/* G_LEVELNAVIGATIONRESOURCENAMES.CPP */
extern const char g_levelNavigationResourceNames[32];

/* LEVEL_NAV_VISION_TEXT.CPP */

#if defined(VERSION_DE)

#endif

/* S_SKYLAYERSTEXT.CPP */

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE) || defined(VERSION_EU)
const char g_skyLayersText[12] =
    "sky layers\000\000";
#endif
#if defined(VERSION_EU_X) || defined(VERSION_US)
const char g_skyLayersText[11] =
    "sky layers\000";
#endif
#endif

#if defined(VERSION_US_REV1)
extern const unsigned char s_skyLayersText[11];
#endif

/* S_ANIMATEDINSTANCESTEXT.CPP */

#if !(defined(VERSION_US_REV1))
extern const char s_animatedInstancesText[19];
#endif

#if defined(VERSION_US_REV1)
extern const unsigned char s_animatedInstancesText[19];
#endif

/* SCENE_LEVEL_RESOURCE_CONSTANT_DATA.CPP */


#if defined(VERSION_DE)
const f32 g_loadLevelResourcesConstants = 3.40282347e+38f;
#endif
#if defined(VERSION_EU)
const f32 g_loadLevelResourcesConstants = 3.40282347e+38f;
#endif
#if defined(VERSION_EU_X)
const f32 g_loadLevelResourcesConstants = 3.40282347e+38f;
#endif
#if defined(VERSION_US)
const f32 g_loadLevelResourcesConstants = 3.40282347e+38f;
#endif
#if defined(VERSION_US_REV1)
const f32 g_loadLevelResourcesConstants = 3.40282347e+38f;
#endif

/* S_BINARYBLOCKTEXT.CPP */

#if !(defined(VERSION_US_REV1))
extern const char s_binaryBlockText[13];
#endif

#if defined(VERSION_US_REV1)

#endif

/* S_GRAPHICSETTEXT.CPP */

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
extern const char s_graphicsetText[12];
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
extern const char s_graphicsetText[11];
#endif
#endif

#if defined(VERSION_US_REV1)

#endif

/* SCENE.CPP */

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
extern const char g_levelNameText[11];
#endif
#if defined(VERSION_US)
extern const char g_levelNameText[12];
#endif

/* SCENE_SHOWRESULTSGOAL_DATA.CPP */



/* SCENE_GETBLLEVELDATA_DATA.CPP */



/* K_SCENEENCODEDBYTES.CPP */

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)

#endif

/* SCENE_QUEUETRIGGERTIMER_DATA.CPP */



/* SCENE_DRAW_TRANSITION_COLOR_OVERLAY_CONSTANT_WORDS_DATA.CPP */



/* OVLSCENE.CPP */



/* K_NIBBLEBOOSTTABLES.CPP */

#if defined(VERSION_DE)
struct {
    u8 previousRecordTail[8];
    u8 lowNibbleBoost[16];
    u8 highNibbleBoost[16];
} k_nibbleBoostTables __attribute__((aligned(4))) = {
    { 0xb, 0xc, 0xe, 0xf, 0xf, 0xf, 0xf, 0xf },
    { 0x0, 0x3, 0x4, 0x5, 0x6, 0x8, 0x9, 0xa, 0xb, 0xc, 0xe, 0xf, 0xf, 0xf, 0xf, 0xf },
    { 0x0, 0x5, 0x7, 0x8, 0xa, 0xb, 0xd, 0xe, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf }
};
typedef char k_nibbleBoostTablesSizeCheck[(sizeof(k_nibbleBoostTables) == 40) ? 1 : -1];
#endif

/* G_EMACTEXT.CPP */

s32 g_emacTextEnabled[1] = {
    1,
};

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
RestemacTextLayout324 g_emacText = {
    { 0, 0 },
    { 1.5f, 0.0f, 15.0f },
    { 65280, 20 }
};
#endif
#if defined(VERSION_EU)
extern unsigned short g_emacText[14];
#endif
#if defined(VERSION_EU_X)
RestemacTextLayout325 g_emacText = {
    { 0, 0 },
    { 1.5f, 0.0f, 15.0f },
    { 65280, 0 }
};
#endif
#if defined(VERSION_US)
RestemacTextLayout326 g_emacText = {
    { 0, 0 },
    { 1.5f, 0.0f, 15.0f },
    65280,
    "HRIN"
};
#endif
#endif

#if defined(VERSION_US_REV1)
SceneEmacRev1 g_emacText = {
    0x00000000,
    {
        0x00, 0x00, 0x00, 0x00,
    },
    0x3FC00000,
    {
        0x00, 0x00, 0x00, 0x00,
    },
    0x41700000,
    {
        0x00, 0x00, 0xFF, 0x00,
    },
    0x454D4143,
};
#endif

/* WEAPON_SWITCH_STATE_TABLE_US.CPP */
#if defined(VERSION_EU)

#endif
#if defined(VERSION_EU_X)

#endif

/* SCENE_LOADLEVELRESOURCES_DATA_RUMBLE.CPP */
#if defined(VERSION_US)

#endif
#if defined(VERSION_EU)

#endif

/* SCENE_SAMPLEVOLUMELIGHTING_DATA.CPP */

#if defined(VERSION_EU) || defined(VERSION_EU_X)

#endif

/* PLAYER_CONTROLLER_STATE_RECORDS.CPP */
#if defined(VERSION_EU)
extern unsigned char g_playerControllerStateByteLookupEu[40];
#endif

/* SCENE_LOADLEVELRESOURCES_DATA_CONSTANTS.CPP */
#if defined(VERSION_EU_X)

#endif

/* S_SCHEDACCLAIMNETTEXT.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU)
#if defined(VERSION_EU_X)

extern unsigned int s_SchedACCLAIMNETText[3];
#endif
#endif
#if defined(VERSION_EU_X)
extern char s_SchedACCLAIMNETText[12];
#endif
#endif

/* S_EMACTEXT.CPP */

#if defined(VERSION_EU_X)
struct {
    u8 previousRecordTail[8];
    u8 lowNibbleBoost[16];
    u8 highNibbleBoost[16];
} s_emacText __attribute__((aligned(1))) = {
    { 0x45, 0x4c, 0x0, 0x0, 0x45, 0x4d, 0x41, 0x43 },
    { 0x0, 0x3, 0x4, 0x5, 0x6, 0x8, 0x9, 0xa, 0xb, 0xc, 0xe, 0xf, 0xf, 0xf, 0xf, 0xf },
    { 0x0, 0x5, 0x7, 0x8, 0xa, 0xb, 0xd, 0xe, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf }
};
typedef char s_emacTextSizeCheck[(sizeof(s_emacText) == 40) ? 1 : -1];
#endif

/* CARTRIDGE_INDEX.CPP */
#if defined(VERSION_US)

#endif

/* sched_runeventloopus.CPP */
#if defined(VERSION_US)



#endif
#if defined(VERSION_US)
extern char s_SchedRuneventloopusBAdvanceCameText[12];
#endif

/* S_IATORTEXT.CPP */

#if defined(VERSION_US)
struct {
    u8 previousRecordTail[8];
    u8 lowNibbleBoost[16];
    u8 highNibbleBoost[16];
} s_iatorText __attribute__((aligned(1))) = {
    { 0x49, 0x41, 0x54, 0x4f, 0x52, 0x5f, 0x43, 0x48 },
    { 0x0, 0x3, 0x4, 0x5, 0x6, 0x8, 0x9, 0xa, 0xb, 0xc, 0xe, 0xf, 0xf, 0xf, 0xf, 0xf },
    { 0x0, 0x5, 0x7, 0x8, 0xa, 0xb, 0xd, 0xe, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf }
};
typedef char s_iatorTextSizeCheck[(sizeof(s_iatorText) == 40) ? 1 : -1];
#endif

/* SCHED_HANDLERETRACE_DATA.CPP */
#if defined(VERSION_US)

s32 g_schedHandleretraceWords[6] = {
    0, 0, 0, 20, 0, 0,
};
#endif
#if defined(VERSION_US)

extern char g_schedHandleretraceTailBytesUs[19];
#endif

/* PARTICLE_DRAWRENDERLIST_DATA.CPP */
#if defined(VERSION_US)


unsigned char g_particleRenderFramePrefixByte[1] = {
    0x00,
};
#endif
#if defined(VERSION_US)

s32 g_particleRenderFrameState[3] = {
    0, 0, 0,
};
#endif

/* SETN64_CONFIGUREVIDEOANDENTERMODEUS_DATA.CPP */

#if defined(VERSION_US)

EngineSessionHandlers g_screenModeHandlers[21] = {
    { (EngineSessionCallback)addrLow_SetN64_InitializeFrontendScreenState, (EngineSessionCallback)addrLow_SetN64_ExitSessionAndDisablePaks, (EngineSessionCallback)addrLow_SetN64_DrawRoundTimeoutSession }, { (EngineSessionCallback)addrLow_SetN64_ResetSceneForIntro, (EngineSessionCallback)addrLow_SetN64_AdvanceIntroForMemorySize, (EngineSessionCallback)addrLow_SetN64_DrawIntroBackdrop }, { (EngineSessionCallback)addrLow_SetN64_InitializeMode2, (EngineSessionCallback)addrLow_SetN64_AdvanceToMode5, (EngineSessionCallback)addrLow_SetN64_DrawCenteredIntroText }, { (EngineSessionCallback)addrLow_SetN64_ClearSessionPlayerPools, (EngineSessionCallback)addrLow_SetN64_AdvanceToMode4, (EngineSessionCallback)PACKED_CALLBACK_LOW(SetN64_SetupLoadingBackdropUs) }, { (EngineSessionCallback)addrLow_SetN64_ResetMode4Effects, (EngineSessionCallback)addrLow_SetN64_AdvanceToMode8, (EngineSessionCallback)addrLow_SetN64_AdvanceLoadingToSplashImage_us_rev1 }, { (EngineSessionCallback)addrLow_SetN64_ResetMode5Items, (EngineSessionCallback)addrLow_SetN64_HandleMode5Input, (EngineSessionCallback)addrLow_SetN64_DrawMode5Session },
    { (EngineSessionCallback)addrLow_SetN64_InitializeMode6, (EngineSessionCallback)addrLow_SetN64_UpdateMode6, (EngineSessionCallback)addrLow_SetN64_DrawMode6 }, { (EngineSessionCallback)addrLow_SetN64_SetMode7AudioState, (EngineSessionCallback)addrLow_SetN64_HandleMode7Transition, (EngineSessionCallback)PACKED_CALLBACK_LOW(SetN64_DrawFullscreenBackdrop) }, { (EngineSessionCallback)addrLow_SetN64_InitializeMode8Scene, (EngineSessionCallback)addrLow_SetN64_UpdateMode8, (EngineSessionCallback)addrLow_SetN64_DrawMode8Session }, { (EngineSessionCallback)addrLow_SetN64_ResetMode9Items, (EngineSessionCallback)addrLow_SetN64_HandleMode9Input, (EngineSessionCallback)addrLow_SetN64_HandleTitleScreenInput_us_rev1 }, { (EngineSessionCallback)addrLow_SetN64_ResetMode10Items, (EngineSessionCallback)addrLow_SetN64_HandleMode10Input, (EngineSessionCallback)addrLow_SetN64_DrawMode10Session }, { (EngineSessionCallback)addrLow_SetN64_ResetMode11Items, (EngineSessionCallback)addrLow_SetN64_HandleMode11Input, (EngineSessionCallback)addrLow_SetN64_DrawMode11Session },
    { (EngineSessionCallback)addrLow_SetN64_ResetMode12Items, (EngineSessionCallback)addrLow_SetN64_HandleMode12Input, (EngineSessionCallback)addrLow_SetN64_DrawMode12Session }, { (EngineSessionCallback)addrLow_SetN64_StartLevelIntroCinema_us_rev1, (EngineSessionCallback)addrLow_SetN64_UpdateActiveSession, (EngineSessionCallback)addrLow_SetN64_DrawSessionWithRoundTimeout }, { (EngineSessionCallback)addrLow_SetN64_ResumeSelectedSession, (EngineSessionCallback)addrLow_SetN64_UpdateActiveSession, (EngineSessionCallback)addrLow_SetN64_DrawSessionWithRoundTimeout }, { (EngineSessionCallback)addrLow_SetN64_InitializeMode15, (EngineSessionCallback)addrLow_SetN64_UpdateMode15, (EngineSessionCallback)addrLow_SetN64_DrawMode15 }, { (EngineSessionCallback)addrLow_SetN64_InitializeMode16Credits, (EngineSessionCallback)addrLow_SetN64_HandleMode16CreditsInput, (EngineSessionCallback)addrLow_SetN64_DrawMode16Credits }, { (EngineSessionCallback)addrLow_SetN64_InitializeMode17Credits, (EngineSessionCallback)addrLow_SetN64_HandleMode17CreditsInput, (EngineSessionCallback)addrLow_SetN64_DrawMode17Credits },
    { (EngineSessionCallback)addrLow_SetN64_EmptyVideoModeHookUs, (EngineSessionCallback)PACKED_CALLBACK_LOW(SetN64_EmptyVideoModeHookSecondUs), (EngineSessionCallback)addrLow_Visdata_EmptyInitializeHookUs }, { (EngineSessionCallback)PACKED_CALLBACK_LOW(Visdata_EmptyInitializeHookSecondUs), (EngineSessionCallback)addrLow_Visdata_EmptyReleaseHookUs, (EngineSessionCallback)PACKED_CALLBACK_LOW(Visdata_EmptyReleaseHookSecondUs) }, { (EngineSessionCallback)addrLow_SetN64_InitializeTransitionMode, (EngineSessionCallback)addrLow_SetN64_ConfigureVideoAndEnterModeUs, (EngineSessionCallback)addrLow_SetN64_DrawTransitionMode },
};
#endif

/* SETN64_BUILDANDSUBMITSESSIONFRAME_DATA.CPP */
#ifdef VERSION_DE
#if defined(VERSION_US)

EngineRenderState g_sessionFrameRenderState = {
    0, "\000\000\000\000\003\340\000\010", 0, 1, "\000\000\000\012\000\000\000\013"
};
#endif
#endif
#ifdef VERSION_EU
#if defined(VERSION_US)
EngineRenderState g_sessionFrameRenderState = {
    0, "\000\000\000\000\000\000\000\010", 0, 1, "\000\000\000\000\000\000\000\010"
};
#endif
#endif
#ifdef VERSION_EU_X
#if defined(VERSION_US)
EngineRenderState g_sessionFrameRenderState = {
    0, "were bes", 0, 1, "Munch.\000\000"
};
#endif
#endif
#ifdef VERSION_US
#if defined(VERSION_US)
EngineRenderState g_sessionFrameRenderState = {
    0, "INFLATOR", 0, 1, "\004\000\000\000f\000\000\000"
};
#endif
#endif
#ifdef VERSION_US_REV1
#if defined(VERSION_US)
EnginePreviewRenderState g_sessionFrameRenderState = {
    0, "eft.\000\000\000\000", 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, "ep?\000Oops"
};
#endif
#endif

/* S_SMACKFORMAT.CPP */
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_US)
SmackFormatTableLayoutD g_smackFormatTable = {
    { 0, 10, 10, 11, 12, 13, 14, 15, 16, 17, 18, 22, -1 },
    "INFLATOR_REC"
};
#endif
#endif

/* S_VISIBILITYTEXT.CPP */

#if defined(VERSION_US_REV1)
extern const unsigned char s_visibilityText[11];
#endif

/* S_LEVELINFOTEXT.CPP */

#if defined(VERSION_US_REV1)
extern const unsigned char s_levelInfoText[11];
#endif

/* S_LEVELNAVVISIONTEXT.CPP */

#if defined(VERSION_US_REV1)
extern const unsigned char s_levelNavVisionText[17];
#endif

/* PLAYERAI_INITIALIZEPLAYERHEALTH_DATA.CPP */
#if defined(VERSION_US_REV1)
extern float g_playerAiHealthLimits[3];
#endif

/* S_IFLETEXT.CPP */

#if defined(VERSION_US_REV1)
extern unsigned char s_ifleText[40];
#endif

/* Retained data for this translation unit. */

const float g_updateActorVisibilityConstants[1] = {
    3e+03f,
};

const float g_testNearbyActiveActorConstants[1] = {
    6.5536e+06f,
};

const float g_updateAndDrawWorldConstants[1] = {
    0.087266475f,
};

const float g_lightDirectionLength = 127.0f;
#if !(defined(VERSION_US_REV1))
const char g_matricesText[9] =
    "Matrices\000";
#endif
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const char g_visibilityText[11] =
    "Visibility\000";
#endif
#if !(defined(VERSION_US_REV1))
const char s_tempVisText[9] =
    "temp vis\000";
#endif
#if defined(VERSION_US_REV1)
const char g_temporaryVisibilityText[9] =
    "temp vis";
#endif
#if defined(VERSION_DE)
const char g_sceneLevelInfoText[12] =
    "level info\000\000";
#endif
#if defined(VERSION_DE)
const char g_overlayLevelNavVisionText[20] =
    "level nav vision\000\000\000\000";
#endif
#if defined(VERSION_US_REV1)
const char g_sBinaryblocktextBytes[13] =
    "binary block";
#endif
#if defined(VERSION_US_REV1)
const char g_sGraphicsettextBytes[11] =
    "graphicset";
#endif

const char g_sceneShowresultsgoalBytes[43] = "CScene__GetBLLevelData: bllevel data index\000";

const char g_sceneGetblleveldataBytes[37] = "CScene__GetBLLevelData: bllevel data\000";
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
const char g_sceneBytes[3] = "%s\000";
#endif

const float g_queueTriggerTimerConstants[1] = {
    15.0f,
};

const float g_drawTransitionColorOverlayConstants[2] = {
    255.0f, 2.1474836e+09f,
};

const float k_ovlsceneFloatConstants[1] = {
    75.0f,
};
#if defined(VERSION_EU)
const char g_overlayLevelInfoText[12] =
    "level info\000\000";
#endif
#if defined(VERSION_EU_X)
const char g_overlayLevelNavVisionLabelText[20] =
    "level nav vision\000\000\000\000";
#endif
#if defined(VERSION_US)
const char s_SceneLoadlevelresourcesLevelInfoText[12] =
    "level info\000\000";
#endif
#if defined(VERSION_EU)
const char s_SceneLoadlevelresourcesLevelNavVisionText[20] =
    "level nav vision\000\000\000\000";
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char g_showResultsGoalConstants[3] = "%s\000";
#endif
#if defined(VERSION_EU_X)
const char g_levelInfoText[12] =
    "level info\000\000";
#endif
#if defined(VERSION_US)
const char g_levelNavVisionText[20] =
    "level nav vision\000\000\000\000";
#endif
#if defined(VERSION_DE)
float g_imageUnpackEpsilonTriple[3] = {
    1.0e-06f, 1.0e-06f, 1.0e-06f,
};
#endif
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_EU)
unsigned short g_emacText[14] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x3FC0, 0x0000, 0x0000, 0x0000, 0x4170, 0x0000, 0x0000, 0xFF00,
    0x8011, 0x00B0,
};
#endif
#endif
#if defined(VERSION_EU)
unsigned char g_playerControllerStateByteLookupEu[40] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x05, 0x06, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0E, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x05, 0x07, 0x08, 0x0A, 0x0B, 0x0D, 0x0E, 0x0F, 0x0F,
    0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
};
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU)
#if defined(VERSION_EU_X)
unsigned int s_SchedACCLAIMNETText[3] = {
    0x3162FFFF, 0x00031C00, 0x00621825,
};
#endif
#endif
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
char s_SchedACCLAIMNETText[12] =
    ".ACCLAIM.NET";
#endif
#endif
#if defined(VERSION_US)
char s_SchedRuneventloopusBAdvanceCameText[12] =
    "bAdvanceCame";
#endif
#if defined(VERSION_US)
char g_schedHandleretraceTailBytesUs[19] =
    "EMACIATO\000\000\000\000\000\000\000\001\000\000\000";
#endif
#if defined(VERSION_US_REV1)
float g_playerAiHealthLimits[3] = {
    3.0e+02f, 255.0f, 3.0e+02f,
};
#endif
#if defined(VERSION_US_REV1)
unsigned char s_ifleText[40] = {
    0x49, 0x46, 0x4C, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x05, 0x06, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0E, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x05, 0x07, 0x08, 0x0A, 0x0B, 0x0D, 0x0E, 0x0F, 0x0F,
    0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
};
#endif

#if defined(VERSION_US_REV1)
const unsigned char s_matricesText[9] =
    "Matrices";
#endif

const char g_levelIndexText[12] = "level index";
#if defined(VERSION_US_REV1)
const char s_collisionText[10] = "collision";
#endif

const char g_gridBoundsAndSectionsIndexText[32] = "grid bounds\000grid sections index";
#if defined(VERSION_US_REV1)
const char s_linksText[6] = "links";
#endif

const char s_levelPathsText[12] = "level paths";

const char g_levelNavigationResourceNames[32] = "level nav nodes\000level nav links";
#if defined(VERSION_US_REV1)
const unsigned char s_skyLayersText[11] =
    "sky layers";
#endif
#if !(defined(VERSION_US_REV1))
const char s_animatedInstancesText[19] =
    "animated instances\000";
#endif
#if defined(VERSION_US_REV1)
const unsigned char s_animatedInstancesText[19] =
    "animated instances";
#endif
#if !(defined(VERSION_US_REV1))
const char s_binaryBlockText[13] =
    "binary block\000";
#endif
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
const char s_graphicsetText[12] =
    "graphicset\000\000";
#endif
#endif
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const char s_graphicsetText[11] =
    "graphicset\000";
#endif
#endif
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
const char g_levelNameText[11] = "level name\000";
#endif
#if defined(VERSION_US)
const char g_levelNameText[12] = "level name\000\000";
#endif
#if defined(VERSION_US_REV1)
const unsigned char s_visibilityText[11] =
    "Visibility";
#endif
#if defined(VERSION_US_REV1)
const unsigned char s_levelInfoText[11] =
    "level info";
#endif
#if defined(VERSION_US_REV1)
const unsigned char s_levelNavVisionText[17] =
    "level nav vision";
#endif
