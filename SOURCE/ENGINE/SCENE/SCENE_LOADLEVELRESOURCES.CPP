#include "COMMON/NAVIGATION_GRAPH.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "../../../sdk/include/LIBC.H"
#include "COMMON/SCENERECAT10C0.H"
#include "COMMON/LONE/g_currentStagePreset.H"
#include "SCENE/SCENE_UPDATEANDDRAWWORLD.H"
#include "TYPES.H"
#include "COMMON/CACHE_RELEASERESOURCE.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/TRIGGER_AND_FLOAT_VALUE_OPERATIONS.H"
#include "COMMON/WORLD.H"
#include "ENGINE/SCENE.H"
#include "SCENE/SCENEPRIMARYACTORS.H"
#include "COMMON/OUTPUT.H"
#include "COMMON/NAVIGATION_NODE_AND_ROUTE_VIEWS.H"
#include "COMMON/INTEGERSTATE2C.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/S1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "AI/NAV/PORTAL_LINKNAVIGATIONOBJECTS.H"
#include "AI/NAV/PORTAL_INITSEARCHNODE.H"
#include "OVLGAME/SCENE_DISPATCHANDRECYCLEQUEUEDTRIGGERS.H"
#include "ENGINE/UNICOL/COLLIDE.H"
#include "OVLGAME/OVLGAME_INITIALIZEDYNAMICLIGHTPOOL.H"
#include "COMMON/LOCALDECODERANGE.H"
#include "include_asm.h"
#include "SCENE/SIMPLE_INSTANCE_RECORD.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "COMMON/OBJB.H"
#include "COMMON/PROPGEOMETRY.H"
#include "COMMON/LIGHT_VOLUME_AND_TRIGGER_VIEWS.H"
#include "COMMON/PARTICLE_LIGHTING.H"
#include "COMMON/PPDECOM_UNPACKRESOURCE.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/OBJRECAT5F14.H"

/* 80286050_2.CPP */
/* Collects up to sixteen switch objects (descriptor type 0xD) of a world into its switch list, first syncing each one's flag 4 with the switch table g_currentStagePreset when its kind is 0xD34 to 0xD37: model 0xD2B follows table byte 1, models 0xD2C to 0xD2E follow their own table byte, and any other model clears the flag; the flag is set when the byte is zero. */

void Scene_CollectLevelSwitches(SceneLevelSwitchCollectionView *world) {
    SceneSwitchObjectView *object;
    SceneSwitchDescriptor *descriptor;
    s32 found;
    s32 i;

    found = 0;
    object = world->objects;
    world->switchCount = 0;
    for (i = 15; i >= 0; i--) {
        world->switches[i] = 0;
    }
    for (i = 0; i < world->count; object++, i++) {
        descriptor = object->descriptor;
        if (descriptor->type == 13) {
            if (g_currentStagePreset != 0 && (unsigned)(descriptor->kind - 3380) < 4) {
                switch (descriptor->model) {
                case 3371:
                    if (g_currentStagePreset[1] == 0) {
                        descriptor->flags |= 4;
                    } else {
                        descriptor->flags &= ~4;
                    }
                    break;
                case 3372:
                case 3373:
                case 3374:
                    if (g_currentStagePreset[object->descriptor->model - 3370] == 0) {
                        object->descriptor->flags |= 4;
                        break;
                    }
                default:
                    object->descriptor->flags &= ~4;
                    break;
                }
            }
            world->switches[found] = object;
            found++;
        }
        if (found >= 16) {
            break;
        }
    }
    world->switchCount = found;
}

/* SCENE.CPP */
/* Unknown data types are explicit unresolved contracts, never guessed s32. */

extern void Nav_ResetPlayerState();
struct CNavData_t; extern void Portal_AssignPlatformEndpoints(struct CNavData_t *graph);
struct NavigationSearchGraphView; extern s32 Portal_FindNearestPointIndex(struct NavigationSearchGraphView *pointSet, void *point);
extern void * Playerai_GetPlayerByIndex();
extern void Camera_UpdateViewportLayoutAndBounds();
extern void Gobjinst_UpdateActorRootDisplacement(struct Actor36 *actor);
extern void Gobjinst_DispatchActorTypeUpdate(char *actor);
extern void Gobjinst_UpdateActorController(void *);
extern void **Cache_AllocateResource(s32, s32, s32, char *);
extern void Cache_DrainAndCompactResources(s32);
extern s32 Cache_RequestWordCountedResourcePinned(s32, void *, s32, void *);
extern void **Cache_RequestPackSection(s32 cacheAddress, void *handle, s32 sectionSelector, s32 resourceKey, void *world, void *resourceTag, void *loadTag);
extern s32 Cache_WaitForResourceLoads(struct ResourceLoadWorker *resourceLoadWorker);
extern void SoundVoicePool_Initialize(void *, void *, s32);
extern void Scene_ShowResultsGoal(void);
extern int Scene_GetModelIdAtIndex(void *world, int modelIndex);
extern void Scene_CopyLevelName(struct Shared_World *world, s32 type, void *levelName, s32 maximumBytes);
extern void Scene_ClearSceneObjectCounts(void *object);
extern void Scene_UnlockActiveSectionResources(struct OwnerSceneUnlockActiveSectionResources *owner);
extern void Scene_ResetTransitionViewport(void);
struct Shared_World; extern void Scene_ReleaseCachedLevelData(struct Shared_World *world);
extern int SetN64_GetDirectoryEntry();
extern s32 XPlus_NextRandomInteger();
extern void OnScreen_StartFirstStatusBar();
extern void OnScreen_StartSecondStatusBar();
extern void Menu_TriggerTrackEvent(int event);
extern void Player_RefreshActivePlayerSceneState();
extern void Pools_InitGroupPools();
extern void Ovlgame_InitializeSceneEffectPool();
extern void Batch_InitEntryBatch();
extern void Batch_InitSlotPool();
extern void Scene_LoadSceneLight();
extern void Scene_FreeSceneResources();
extern void Scene_UpdatePendingObjects();
extern void Scene_DispatchSelectedEntityKinds();
extern void Effect_InitEffectPool();
extern void Hud_InitializeWorldActorPools();
extern void Hud_StartPanelMovers(void *panel);

extern unsigned char g_cResource_UnpackRequestEntry[];
extern unsigned char g_sceneLinksLoaderEntry[];
extern unsigned char g_sceneCollisionLoaderEntry[];
extern unsigned char g_sceneAnimatedInstancesLoaderEntry[];
extern unsigned char g_sceneLevelPathsLoaderEntry[];
extern unsigned char g_resourceCacheWorker[];
extern unsigned char g_spatialSoundPoolNodes[];

extern struct Shared_SceneResources g_tutorialStatusBars;
extern unsigned char g_matchRoundCounters[];

extern const unsigned char s_matricesText[];                          /* unable to generate initializer: unknown type; const */

                          /* unable to generate initializer: unknown type; const */
extern const char s_collisionText[];                          /* unable to generate initializer: unknown type; const */
extern unsigned char g_gridBoundsAndSectionsIndexText[];                          /* unable to generate initializer: unknown type; const */
extern unsigned char g_sceneIndexResourceTag[];                          /* unable to generate initializer: unknown type; const */
extern unsigned char s_visibilityText[];                          /* unable to generate initializer: unknown type; const */
extern unsigned char g_visibilityHeaderResourceTag[];                          /* unable to generate initializer: unknown type; const */
extern const char s_linksText[];                          /* unable to generate initializer: unknown type; const */
extern const char s_levelPathsText[];                          /* unable to generate initializer: unknown type; const */
extern const unsigned char s_levelInfoText[];                          /* unable to generate initializer: unknown type; const */
extern const char g_levelNavigationResourceNames[];                          /* unable to generate initializer: unknown type; const */
extern unsigned char g_navigationLinksResourceName[];                          /* unable to generate initializer: unknown type; const */
extern const unsigned char s_levelNavVisionText[];                          /* unable to generate initializer: unknown type; const */
extern unsigned char s_skyLayersText[];                          /* unable to generate initializer: unknown type; const */
extern unsigned char s_animatedInstancesText[];                          /* unable to generate initializer: unknown type; const */
extern s32 g_gameLoopFrameCount;                          /* const */

       /* const */
extern struct Shared_SceneActorTables g_sceneSpecialActorTables; /* const */

/* const */

/* Initializes scene resources, actors, and game mode state. */
void Scene_LoadLevelResources(void *table, s32 target, s32 allowTransition) {
    s32 *unusedPointer3;
    struct CacheResourceBlockView *resourceResult;
    s32 actorCount;
    s32 unusedInteger4;
    s32 previousStageId;
    s32 resource_count;
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
    s32 kind_actor;
    s32 kind_654;
    s32 kind_653;
    s32 kind_655;
    s32 second_type3;
    s32 second_type10;
    s32 second_kind_bd6;
    s32 second_kind_64e;
    s32 header_copy0;
    s32 header_copy1;
    s32 header_copy2;
    s32 header_copy3;
    s32 header_copy4;
    s32 header_copy5;
    Record *record;
    s32 loop_buffer;
    s32 actorByteOffset;
    s32 actorIndex;
    s32 k;
    s32 initializationIndex;
    s32 unusedInteger6;
    s32 finalActorByteOffset;
    s32 transitionAllowed;
    s32 levelSelection;
    s32 kind_656;
    s32 hasSelectedActorCapacity;
    s32 primarySlotByteOffset;
    s32 secondarySlotByteOffset;
    s32 hasSecondaryActorCapacity;
    s32 actorIterationIndex;
    s32 actor_kind_bd7;
    s32 first_actor_kind;
    s32 actor_type3;
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
    void *playerHudProfile;
    void *unusedPointer8;
    void *unusedPointer9;
    void *group;
    struct ResourceKeyView *navigationPoints;
    struct ResourceKeyView *navigationLinks;
    struct ResourceKeyView *navigationVision;
    struct Shared_SceneActorKind *primaryActorKind;
    void *levelActor;
    struct ScenePlayerResourceView *scene_actor_ptr;
    void *playerProfile;
    struct SceneResourceSixWordRecord *visibilityHeader;
    void *skyLayerTable;
    struct SceneActorDefinitionKindView *primaryActorDefinition;
    struct SceneActorDefinitionKindView *secondaryActorDefinition;
    void *unusedPointer1;
    void *selectedActorSlot;
    struct Shared_SceneActorKind *secondaryActorKind;
    void *secondaryActor;
    void *unusedPointer2;
    struct ScenePlayerResourceView *playerActor;
    void *resetCursor;

    levelSelection = target;
    (((struct SceneResourceStateView *)(table))->minimumCollisionY) = k_initialMinimumCollisionY;
    transitionAllowed = allowTransition;
    if ((((struct SceneResourceStateView *)(table))->levelSelection) != -1) {
        Scene_DispatchAndRecycleQueuedTriggers(table);
    }
    (((struct SceneResourceStateView *)(table))->sceneLoadResetState) = 0;
    if ((Cinema_IsSequenceActive() == 0) && (transitionAllowed != 0) && ((((struct SceneResourceStateView *)(table))->gameplayStarted) != 0) && (g_gameSettings.counters.transitionActive == 0)) {
        Scene_ResetTransitionViewport();
        previousStageId = (((struct SceneResourceStateView *)(table))->spawnPlacementKey);
        if ((u32) (previousStageId - 3010) < 351U) {
            Menu_TriggerTrackEvent(((previousStageId - 3010) / 10) + 601);
        }
        Scene_ShowResultsGoal();
    }
    Scene_UnlockActiveSectionResources(table);
    (((struct SceneResourceStateView *)(table))->loadStage) = 0;
    Cache_WaitForResourceLoads(&g_resourceCacheWorker);
    Scene_ReleaseCachedLevelData(table);
    Cache_DrainAndCompactResources(0);
    if ((((struct SceneResourceStateView *)(table))->levelSelection) != -1) {
        Scene_FreeSceneResources(table);
    }
    Cache_DrainAndCompactResources(0);
    g_gameLoopFrameCount = 0;
    Cache_SetResourceActivityState(8);
    Scene_ClearSceneObjectCounts(table);
    Batch_InitSlotPool(&((struct SceneResourceStateView *)table)->batchSlotPool, *(((struct SceneResourceStateView *)(table))->slotPoolDefinition));
    initializationIndex = 0;
    Effect_InitEffectPool(&((struct SceneResourceStateView *)table)->effectPool);
    Ovlgame_InitializeSceneEffectPool(&((struct SceneResourceStateView *)table)->sceneEffectPool);
    Hud_InitializeWorldActorPools(&g_tutorialStatusBars.actors);
    CCollision_Initialize();
    Ovlgame_InitializeDynamicLightPool(&((struct SceneResourceStateView *)table)->dynamicLightPool);
    SoundVoicePool_Initialize(&g_soundVoicePoolGlobalState, &g_spatialSoundPoolNodes, 15);
    Hud_StartPanelMovers(&g_tutorialStatusBars);
    do {
        playerActor = Playerai_GetPlayerByIndex(&g_playerViewRenderContext, initializationIndex);
        if (playerActor != 0) {
            playerProfile = playerActor->profile;
            if ((((struct LevelResourceLoadFlags *)playerProfile)->loadFlagFirst == 1) && (((struct LevelResourceLoadFlags *)playerProfile)->loadFlagSecond == 1)) {
                Nav_ResetPlayerState(playerActor->controllerState);
            }
            if ((((struct SceneSpecialActorModeView *)(&g_matchRoundCounters))->statusBarsEnabled) != 0) {
                playerHudProfile = playerActor->profile;
                statusBarKind = (((struct SceneStatusBarModeView *)(playerHudProfile))->statusBarMode);
                if (statusBarKind != 0) {
                    if (statusBarKind == 1) {
                        OnScreen_StartFirstStatusBar(&g_tutorialStatusBars, playerActor, &((struct SceneStatusBarModeView *)playerHudProfile)->address84);
                    } else if (statusBarKind == 2) {
                        OnScreen_StartSecondStatusBar(&g_tutorialStatusBars, playerActor, &((struct SceneStatusBarModeView *)playerHudProfile)->address84);
                    }
                    if (playerActor->profile->characterKind == 11) {
                        OnScreen_StartFirstStatusBar(&g_tutorialStatusBars, playerActor, g_firstStatusBarTarget);
                    }
                }
            }
        }
        initializationIndex += 1;
    } while (initializationIndex < 8);
    levelCount = *(((struct SceneResourceStateView *)(table))->levelDirectory);
    if (levelCount < levelSelection) {
        levelSelection = levelCount - 1;
        transitionAllowed = 0;
    }
    (((struct SceneResourceStateView *)(table))->levelSelection) = levelSelection;
    if (transitionAllowed == 0) {
        (((struct SceneResourceStateView *)(table))->gameplayStarted) = 0;
    }
    Scene_CopyLevelName(table, levelSelection, &((struct SceneResourceStateView *)table)->levelNameBuffer, 63);
    stageIdForFlags = (((struct SceneResourceStateView *)(table))->spawnPlacementKey);
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
    (((struct SceneResourceStateView *)(table))->specialSceneEnabled) = 1;
    goto scene_flag_done;
scene_flag_off:
    (((struct SceneResourceStateView *)(table))->specialSceneEnabled) = 0;
scene_flag_done:
    stageIdForPoolSize = (((struct SceneResourceStateView *)(table))->spawnPlacementKey);
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
    (((struct SceneResourceStateView *)(table))->matrixPoolResourceHandle) = (void *)resourceResult;
    Batch_InitEntryBatch(&((struct SceneResourceStateView *)table)->matrixPool, resourceResult->first, count);
    resourceKey = SetN64_GetDirectoryEntry((((struct SceneResourceStateView *)(table))->levelDirectory), (((struct SceneResourceStateView *)(table))->levelDirectoryKey), levelSelection);
    (((struct SceneResourceStateView *)(table))->levelIndexResourceHandle) = Cache_RequestWordCountedResourcePinned(0, &((struct SceneResourceStateView *)table)->sceneResources, resourceKey, g_levelIndexText);
    collisionHandle = Cache_RequestPackSection(0, (((struct SceneResourceStateView *)(table))->sceneResources), 1, resourceKey, table, &g_sceneCollisionLoaderEntry, &s_collisionText);
    (((struct SceneResourceStateView *)(table))->collisionResourceHandle) = collisionHandle;
    (((struct SceneResourceStateView *)(table))->collisionData) = (void *) *collisionHandle;
    gridBoundsHandle = Cache_RequestPackSection(0, (((struct SceneResourceStateView *)(table))->sceneResources), 4, resourceKey, table, &g_cResource_UnpackRequestEntry, &g_gridBoundsAndSectionsIndexText);
    (((struct SceneResourceStateView *)(table))->gridBoundsResourceHandle) = gridBoundsHandle;
    (((struct SceneResourceStateView *)(table))->gridBoundsAndSections) = (void *) *gridBoundsHandle;
    sceneDirectoryEntry = SetN64_GetDirectoryEntry((((struct SceneResourceStateView *)(table))->sceneResources), resourceKey, 5);
    (((struct SceneResourceStateView *)(table))->sceneDirectoryKey) = sceneDirectoryEntry;
    (((struct SceneResourceStateView *)(table))->sceneIndexResourceHandle) = Cache_RequestWordCountedResourcePinned(0, &((struct SceneResourceStateView *)table)->sceneIndexDataSlot, sceneDirectoryEntry, &g_sceneIndexResourceTag);
    if (*(((struct SceneResourceStateView *)(table))->sceneResources) >= 13) {
        visibilityResourceKey = SetN64_GetDirectoryEntry((((struct SceneResourceStateView *)(table))->sceneResources), resourceKey, 12);
        (((struct SceneResourceStateView *)(table))->visibilityResourceKey) = visibilityResourceKey;
        (((struct SceneResourceStateView *)(table))->visibilityResourceHandle) = Cache_RequestWordCountedResourcePinned(0, &((struct SceneResourceStateView *)table)->visibilityTable, visibilityResourceKey, &s_visibilityText);
        sceneResourceHandle = Cache_RequestPackSection(0, (((struct SceneResourceStateView *)(table))->visibilityTable), 0, (((struct SceneResourceStateView *)(table))->visibilityResourceKey), table, 0, &g_visibilityHeaderResourceTag);
        visibilityHeader = *sceneResourceHandle;
        *(struct SceneResourceSixWordRecord *)&((struct SceneResourceStateView *)table)->visibilityHeaderWord0 = *visibilityHeader;
        Cache_ReleaseResource(0, sceneResourceHandle);
        if ((((struct SceneResourceStateView *)(table))->visibilityHeaderWord4) != 0 || (((struct SceneResourceStateView *)(table))->visibilityHeaderWord5) != 0) {
            (((struct SceneResourceStateView *)(table))->hasVisibilityPayload) = 1;
        } else {
            (((struct SceneResourceStateView *)(table))->hasVisibilityPayload) = 0;
        }
    } else {
        (((struct SceneResourceStateView *)(table))->hasVisibilityPayload) = 0;
    }
    (((struct SceneResourceStateView *)(table))->actorLinksResourceHandle) = Cache_RequestPackSection(0, (((struct SceneResourceStateView *)(table))->sceneResources), 7, resourceKey, table, &g_sceneLinksLoaderEntry, &s_linksText);
    (((struct SceneResourceStateView *)(table))->levelPathsResourceHandle) = Cache_RequestPackSection(0, (((struct SceneResourceStateView *)(table))->sceneResources), 2, resourceKey, table, &g_sceneLevelPathsLoaderEntry, &s_levelPathsText);
    levelInfoHandle = Cache_RequestPackSection(0, (((struct SceneResourceStateView *)(table))->sceneResources), 0, resourceKey, table, 0, &s_levelInfoText);
    (((struct SceneResourceStateView *)(table))->levelInfoResourceHandle) = levelInfoHandle;
    (((struct SceneResourceStateView *)(table))->sceneSettings) = (void *) *levelInfoHandle;
    Scene_LoadSceneLight(table);
    resource_count = *(((struct SceneResourceStateView *)(table))->sceneResources);
    g_geometryFogEffectEnabled = ((u8) (((struct SceneResourceFlagsView *)(((struct SceneResourceStateView *)(table))->sceneSettings))->flags) >> 2) & 1;
    if (resource_count >= 9) {
        navigationPointsHandle = Cache_RequestPackSection(0, (((struct SceneResourceStateView *)(table))->sceneResources), 9, resourceKey, table, &g_cResource_UnpackRequestEntry, &g_levelNavigationResourceNames);
        (((struct SceneResourceStateView *)(table))->navPointsResourceHandle) = navigationPointsHandle;
        navigationPoints = *navigationPointsHandle;
        (((struct SceneResourceStateView *)(table))->navPointSet) = navigationPoints;
        (((struct SceneResourceStateView *)(table))->navPointCount) = (s32) navigationPoints->key;
        navigationLinksHandle = Cache_RequestPackSection(0, (((struct SceneResourceStateView *)(table))->sceneResources), 10, resourceKey, table, &g_cResource_UnpackRequestEntry, &g_navigationLinksResourceName);
        (((struct SceneResourceStateView *)(table))->navLinksResourceHandle) = navigationLinksHandle;
        navigationLinks = *navigationLinksHandle;
        (((struct SceneResourceStateView *)(table))->navLinkSet) = navigationLinks;
        (((struct SceneResourceStateView *)(table))->navLinkCount) = (s32) navigationLinks->key;
        List_InitializeIntrusive(&((struct SceneResourceStateView *)table)->navigationSearchNodes, 12, 16);
        navigationPointCount = (((struct SceneResourceStateView *)(table))->navPointCount);
        if (navigationPointCount > 0) {
            record = Cache_AllocateMemory(navigationPointCount * 80);

            initializationIndex = 0;
            if ((((struct SceneResourceStateView *)(table))->navPointCount) > 0) {
                do {
                    Portal_InitSearchNode(record, initializationIndex);
                    List_AppendIntrusive(&((struct SceneResourceStateView *)table)->navigationSearchNodes, record);
                    record = (void *)((char *)record + sizeof(NavigationSearchNode));
                } while ((((struct SceneResourceStateView *)table)->navPointCount) > ++initializationIndex);
            }
        }
    }
    if (*(((struct SceneResourceStateView *)(table))->sceneResources) >= 12) {
        navigationVisionHandle = Cache_RequestPackSection(0, (((struct SceneResourceStateView *)(table))->sceneResources), 11, resourceKey, table, &g_cResource_UnpackRequestEntry, &s_levelNavVisionText);
        (((struct SceneResourceStateView *)(table))->navVisionResourceHandle) = navigationVisionHandle;
        navigationVision = *navigationVisionHandle;
        (((struct SceneResourceStateView *)(table))->navVisionSet) = navigationVision;
        (((struct SceneResourceStateView *)(table))->navVisionCount) = (s32) navigationVision->key;
    }
    skyLayersHandle = Cache_RequestPackSection(0, (((struct SceneResourceStateView *)(table))->sceneResources), 6, resourceKey, table, &g_cResource_UnpackRequestEntry, &s_skyLayersText);
    (((struct SceneResourceStateView *)(table))->skyLayersResourceHandle) = skyLayersHandle;
    skyLayerTable = *skyLayersHandle;
    (((struct SceneResourceStateView *)(table))->skyLayerEntries) = (void *) (&((struct ScenePackedResourceTableView *)skyLayerTable)->address8);
    (((struct SceneResourceStateView *)(table))->skyLayerCount) = (s32) (((struct ScenePackedResourceTableView *)(skyLayerTable))->count);
    (((struct SceneResourceStateView *)(table))->loadStage) = 1;
    (((struct SceneResourceStateView *)(table))->levelActors) = 0;
    (((struct SceneResourceStateView *)(table))->levelActorCount) = 0;
    (((struct SceneResourceStateView *)(table))->animatedInstancesResourceHandle) = Cache_RequestPackSection(0, (((struct SceneResourceStateView *)(table))->sceneResources), 3, resourceKey, table, &g_sceneAnimatedInstancesLoaderEntry, &s_animatedInstancesText);
    Scene_CollectLevelSwitches(table);

    i = 0;
    actorIterationIndex = 15;

    actorScanCursor = (s32)(((struct SceneResourceStateView *)(table))->levelActors);
    resetCursor = &((struct SceneResourceStateView *)table)->selectionClearCursorAnchor;
    (((struct SceneResourceStateView *)(table))->selectedActorCount) = 0;
    do {
        (((struct SceneSelectedActorSlotView *)(resetCursor))->selectedActor) = 0;
        actorIterationIndex -= 1;
        resetCursor -= 4;
    } while (actorIterationIndex >= 0);

    actorIterationIndex = 0;

    if ((((struct SceneResourceStateView *)(table))->levelActorCount) > 0) {
        first_actor_kind = 14;
        selectedActorSlot = (void *)(i * sizeof(void *) + (u32)table);
loop_81:
        if (*(((struct ActorKindDefinitionPointerView *)((void *)actorScanCursor))->definition) == first_actor_kind) {
            (((struct SceneLoadedResourceView *)(selectedActorSlot))->loadedResource) = (void *)actorScanCursor;
            selectedActorSlot += 4;
            i += 1;
            hasSelectedActorCapacity = i < 16;
        } else {
            hasSelectedActorCapacity = i < 16;
        }
        if (hasSelectedActorCapacity != 0) {
            actorScanCursor = (s32)NEXT_SCENE_ACTOR((void *)actorScanCursor);
            actorIterationIndex += 1;
            if (actorIterationIndex < (((struct SceneResourceStateView *)(table))->levelActorCount)) {
                goto loop_81;
            }
        }
    }

    actorIndex = 3;
    scene_actor_ptr = (((struct SceneResourceStateView *)(table))->levelActors);
    actor_type3 = 3;
    actor_kind_bd7 = 3031;
    primarySlotByteOffset = 3 * sizeof(void *);

    (((struct SceneResourceStateView *)(table))->selectedActorCount) = i;
    g_sceneSpecialActorTables.primary.kindBd7 = 0;
    do {
        *(void **)((char *)g_sceneSpecialActorTables.primary.actors + primarySlotByteOffset) = 0;
        actorIndex -= 1;
        primarySlotByteOffset -= sizeof(void *);
    } while (actorIndex >= 0);
    actorIndex = 0;
    if ((((struct SceneResourceStateView *)(table))->levelActorCount) > 0) {
        kind_actor = 10;
        kind_654 = 1620;
        kind_653 = 1619;
        kind_655 = 1621;
        kind_656 = 1622;
        primaryActorKind = &((struct SceneActorKindView *)scene_actor_ptr)->kind;
loop_89:
        primaryActorDefinition = ((struct Shared_SceneActorPrefix *)primaryActorKind)[-1].definition;
        primaryDefinitionType = primaryActorDefinition->kind;
        if (primaryDefinitionType == actor_type3) {
            if (Scene_GetModelIdAtIndex(&g_world, primaryActorDefinition->flags) != actor_kind_bd7) {
                goto block_108;
            }
            g_sceneSpecialActorTables.primary.kindBd7 = scene_actor_ptr;
            goto block_109;
        } else {
            if (primaryDefinitionType == kind_actor) {
                kind = primaryActorKind->kind;
                if (kind == kind_654) {
                    goto actor_kind_654;
                }
                if (kind < 1621) {
                    if (kind == kind_653) {
                        goto actor_kind_653;
                    }
                        goto block_108;
                }
                if (kind == kind_655) {
                    goto actor_kind_655;
                }
                if (kind == kind_656) {
                        goto actor_kind_656;
                }
                goto block_108;
actor_kind_653:
                g_sceneSpecialActorTables.primary.actors[0] = scene_actor_ptr;
                goto block_108;
actor_kind_654:
                g_sceneSpecialActorTables.primary.actors[1] = scene_actor_ptr;
                goto block_108;
actor_kind_655:
                g_sceneSpecialActorTables.primary.actors[2] = scene_actor_ptr;
                goto block_108;
actor_kind_656:
                g_sceneSpecialActorTables.primary.actors[3] = scene_actor_ptr;
            }
block_108:
            primaryActorKind = NEXT_SCENE_ACTOR(primaryActorKind);
            scene_actor_ptr = NEXT_SCENE_ACTOR(scene_actor_ptr);
            actorIndex += 1;
            if (actorIndex >= (((struct SceneResourceStateView *)(table))->levelActorCount)) {
                goto block_109;
            }
            goto loop_89;
        }
    } else {
block_109:
        j = 0;
    }

    actorScanCursor = 9;
    secondaryActor = (((struct SceneResourceStateView *)(table))->levelActors);
    secondarySlotByteOffset = 9 * sizeof(void *);

    g_sceneSpecialActorTables.kindBd6 = 0;
    do {
        *(void **)((char *)g_sceneSpecialActorTables.kind64e + secondarySlotByteOffset) = 0;
        actorScanCursor -= 1;
        secondarySlotByteOffset -= sizeof(void *);
    } while (actorScanCursor >= 0);
    actorScanCursor = 0;
    if ((((struct SceneResourceStateView *)(table))->levelActorCount) > 0) {
        second_type3 = 3;
        second_kind_bd6 = 3030;
        second_type10 = 10;
        second_kind_64e = 1614;
        secondaryActorKind = &((struct SceneActorKindView *)secondaryActor)->kind;
loop_114:
        secondaryActorDefinition = ((struct Shared_SceneActorPrefix *)secondaryActorKind)[-1].definition;
        secondaryDefinitionType = secondaryActorDefinition->kind;
        if (secondaryDefinitionType == second_type3) {
            if (secondaryActorDefinition->flags == second_kind_bd6) {
                g_sceneSpecialActorTables.kindBd6 = secondaryActor;
            }
        } else if (secondaryDefinitionType == second_type10) {
            if (secondaryActorKind->kind == second_kind_64e) {
                g_sceneSpecialActorTables.kind64e[j] = secondaryActor;
                j += 1;
            }
        }
        hasSecondaryActorCapacity = j < 10;
        if (hasSecondaryActorCapacity != 0) {
            secondaryActorKind = NEXT_SCENE_ACTOR(secondaryActorKind);
            secondaryActor = NEXT_SCENE_ACTOR(secondaryActor);
            actorScanCursor += 1;
            if (actorScanCursor >= (((struct SceneResourceStateView *)(table))->levelActorCount)) {
                goto block_122;
            }
            goto loop_114;
        }
    } else {
block_122:
        g_gameSettings.counters.m_nFragTagSkin = XPlus_NextRandomInteger(actorScanCursor) % 3;
    }
    (((struct SceneResourceStateView *)(table))->loadStage) = 2;
    Scene_UpdatePendingObjects(table);
    actorCount = (((struct SceneResourceStateView *)(table))->levelActorCount);
    actorIndex = (((struct SceneResourceStateView *)(table))->levelActorCursor);
    (((struct SceneResourceStateView *)(table))->loadStage) = 3;
    if (actorIndex < actorCount) {
        actorByteOffset = actorIndex * sizeof(struct Shared_SceneActorStride);
        do {
            actorIndex += 1;
            Gobjinst_DispatchActorTypeUpdate((((struct SceneResourceStateView *)(table))->levelActors) + actorByteOffset);
            actorByteOffset += sizeof(struct Shared_SceneActorStride);
        } while (actorIndex < actorCount);
    }
    playerActor = g_transientPlayerList.actorList;
    if (playerActor != 0) {

        levelActor = playerActor;
        do {
            Gobjinst_DispatchActorTypeUpdate(levelActor);
            Gobjinst_DispatchActorTypeUpdate(NEXT_SCENE_ACTOR(levelActor));
            (((struct ResourceKeyView *)(((struct ScenePlayerNavigationLinkView *)(playerActor))->navigationRecord))->key) = Portal_FindNearestPointIndex(&((struct SceneResourceStateView *)table)->navPointSet, &((struct ScenePlayerNavigationLinkView *)playerActor)->address8);
            playerActor = (((struct ScenePlayerNavigationLinkView *)(playerActor))->nextPlayer);
            if (playerActor == 0) {
                break;
            }
            levelActor = playerActor;
        } while (1);
    }
    Scene_DispatchSelectedEntityKinds(table);
    actorCount = (((struct SceneResourceStateView *)(table))->levelActorCount);
    k = (((struct SceneResourceStateView *)(table))->levelActorCursor);
    if (k < actorCount) {
        finalActorByteOffset = k * sizeof(struct Shared_SceneActorStride);
        do {
            k += 1;

            levelActor = (((struct SceneResourceStateView *)(table))->levelActors) + finalActorByteOffset;
            Gobjinst_UpdateActorController(levelActor);
            Gobjinst_UpdateActorRootDisplacement(levelActor);
            finalActorByteOffset += sizeof(struct Shared_SceneActorStride);
        } while (k < actorCount);
    }

    count = (char *)&((struct SceneResourceStateView *)table)->navPointSet - (char *)table;
    levelActor = (char *)table + count;
    Portal_LinkNavigationObjects(levelActor);
    Portal_AssignPlatformEndpoints(levelActor);
    (((struct SceneResourceStateView *)(table))->loadStage) = 4;
    Player_RefreshActivePlayerSceneState(&g_playerViewRenderContext);
    group = &g_playerViewRenderContext.object;
    Pools_InitGroupPools(group);
    Camera_UpdateViewportLayoutAndBounds(group);
}

/* Native resident constant storage; absolute access symbols retain their addresses. */

/* SCENE_2.CPP */
/* Spawns an entity through Link_DispatchTrigger when its bit is set in the current level's placement mask and it either names no flag or its flag in the global flag table g_levelFlagTable is clear. */

extern s32 SetN64_GetPackSectionSize(void *table, s32 index);

void Scene_DispatchEnabledEntityTrigger(WorldSceneDispatchEnabledEntityTrigger *world, Entity *entity) {
    s32 index;
    s32 level;
    void *mask;
    unsigned char *bits;
    void *flags;
    s32 flag;
    s32 bit;

    index = entity->index;
    level = world->level;
    mask = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(world->levels, 0), level), 2);
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

/* A light volume as the level resource stores it. */
typedef struct LightVolumeRecord {
    u8 data[76];
} LightVolumeRecord;

extern s32 SetN64_GetPackSize(s32 *bitSet);
extern void *Cache_AllocResourceBlock(s32 pool, void *handle, s32 size);
extern void Cache_ReplaceResourceBlock(s32 pool, void *handle, void *block);

extern void Statinst_InitializePlacedProp(ObjA *prop, PackedPlacedPropDefinition *record, s32 owner, char *segments, f32 spacing);
extern void Statinst_InitPlacedProp(ObjA *prop, PlacedPropRecord *record, s32 owner, char *segments);
struct CROMSimpleInstance; extern void Simple_InitSimpleInstance(ObjB *inst, struct CROMSimpleInstance *rec, s32 owner, char *segments);
extern void Lighting_DecodeBoxTransform(u8 *self, u8 *src);

#define ALIGN8(size) (((size) + 7) & ~7)

/* Whether the instance's bit is set in the current level's instance mask (section 1 of the level's bit sections).
 * The same body as Scene_TestLevelRecordStateBit; the ROM inlines it here. */
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
    char *dst;
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
            ((RecordSet *)dst)->size = sizeof(ObjA);
            ((RecordSet *)dst)->count = efficientCount + staticCount;
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

extern void Playerai_UpdatePlayerRenderResources(void *pool, void *world);
extern s32 InstHdr_CanActorReceiveInteraction(void *actor);
extern s32 InstHdr_HasEnabledMotionHooks(void *actor);
extern void Gobjinst_RotatePoseMatrixBuffers(void *actor);
extern f32 Gsky_GetDistanceTo(void *camera, CVector3 *position);
extern s32 Visdata_TestBoxAgainstFrustum(void *planes, void *bounds);
struct CAnimPool; extern void Animpool_UpdateSceneEffects(struct CAnimPool *scene, s32 world);

typedef struct SceneVisibilitySettings {
    u32 mask;
    u8 reserved04[0x11];
    u8 local;
} SceneVisibilitySettings;

/* Whether the actor's bounding box overlaps the box. */
#define ACTOR_OVERLAPS(actor, box) ((box)->x > (actor)->bounds.min.x && \
    ((Box *)((u8 *)(box) - 12))->min.x < (actor)->bounds.max.x && \
    (box)->z > (actor)->bounds.min.z && \
    ((Box *)((u8 *)(box) - 12))->min.z < (actor)->bounds.max.z && \
    (box)->y > (actor)->bounds.min.y && \
    ((Box *)((u8 *)(box) - 12))->min.y < (actor)->bounds.max.y)

/* Per-frame visibility scan over the world's actors. Rebuilds the lists of registered, interactive, mover, flagged and
 * per-model actors from the actors that are visible this frame (inside the clip box and the camera frustum, or within
 * range for kind 14), copies each actor's visible bit into bit 15 of its flags, then culls the scene's effects. */

void Scene_UpdateActorVisibility(Shared_World *world) {
    SceneVisibilitySettings *settings;
    LevelActor *actors;
    LevelActor *actor;
    GameplayCamera *camera;
    ActorDefinitionHeader *definition;
    CVector3 *clipBox;
    CVector3 *rangeBox;
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
    Playerai_UpdatePlayerRenderResources((u8 *)settings - ((char *)&((Shared_MenuData *)0)->game.sceneMask - (char *)0), world);
    camera = 0;
    if (settings->local == 0) {
        camera = *(GameplayCamera **)((u8 *)settings - (((char *)&((Shared_MenuData *)0)->game.sceneMask - (char *)0) - ((char *)&((Shared_MenuData *)0)->object - (char *)0) - ((char *)&((MenuMatchGlobals *)0)->cameras - (char *)0)));
    }
    cull = 0;
    if (Cinema_IsSequenceInWindow() == 0) {
        cull = world->visibilityEnabled == 0;
    }
    i = world->actorCapacity;
    end = world->actorCount;
    actors = (LevelActor *)world->actors;
    for (; i < end; i++) {
        clipBox = &g_cameraClipBounds.max;
        rangeBox = &g_cameraVolumeBounds.max;
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
            actor->flags |= 0x80000000;
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
                /* byte 0x23E of the word actionReady holds the slot */
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
    Animpool_UpdateSceneEffects((struct CAnimPool *)world->effectPool, world);
    world->kind1Cursor++;
    if (world->kind1Cursor >= world->kind1Count) {
        world->kind1Cursor = 0;
    }
}
#undef ACTOR_OVERLAPS

/* 800CA2FC.CPP */
/* ROM-grounded data: src/g_scene_UpdateActorVisibilityConstantWords_SceneLoadlevelresources.c */
const float g_scene_UpdateActorVisibilityConstantWords[1] = {
    3e+03f,
};
