#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H
#include "types.h"
struct Shared_World;
extern void *Scene_GetBlLevelData(struct Shared_World *world, s32 record);
#include "types.h"
struct Shared_World;
extern void *Scene_FindActorDefinition(struct Shared_World *world, s32 selection, s32 modelKind);
#include "types.h"
struct Shared_World;
struct LevelActor;
extern void Scene_RegisterActorInSceneLists(struct Shared_World *world, struct LevelActor *object);
#include "types.h"
struct Shared_World;
struct LevelActor;

#include "Common/small_records.h"
#include "Common/Lone/resource_request_queue.h"
#include "Common/triple.h"
#include "Frontend/frontend_address_symbols.h"
#include "Data/Character_preview/character_preview.h"
#include "Common/level_actor.h"
#include "Common/runtime_declarations.h"
struct ResultsHeadingCharacter;
#include "Common/scene_switch.h"
struct Shared_World;
struct LevelActor;
struct SceneLightVolume;
/* Clip-ratio words the scene code loads with gMoveWd(G_MW_CLIP) in the F3DEX2 display lists. */
#define FRUSTRATIO_1 1
#define FRUSTRATIO_2 2
#include "Common/objb.h"
#include "Common/world.h"
#include "Common/scene_switch.h"
#include "Engine/map.h"
#include "types.h"
#include "Common/hud_effects.h"
#include "Common/sharedplayer.h"
#include "Common/colorentry.h"
#include "Scene/sceneprimaryactors.h"

struct StridedTable {
    s32 stride;
    s32 count;
    char data[1];
};
typedef struct StridedTable StridedTable;


/* One cell of the floor grid: the polygons of the cell lie in its x/z bounds. */
typedef struct FloorCell {
    Bounds2D37 bounds;
    u32 count;
} FloorCell;


typedef struct AnimationPoseFrameSet {
    s32 stride;
    s32 count;
    AnimationPoseFrame frames[1];
} AnimationPoseFrameSet;


typedef struct Shared_SceneActorTables Shared_SceneActorTables;

struct Shared_SceneActorTables {
    void * kind64e[10];
    Shared_ScenePrimaryActors primary;
    void * kindBd6;
};

typedef char Shared_SceneActorTables_size_check[(sizeof(Shared_SceneActorTables) == 0x40) ? 1 : -1];















































extern void Scene_CopySimpleModelHeader(void *,void *,s32);
extern int Scene_GetModelIdAtIndex(struct Shared_World *world, int modelIndex);
extern void CScene_StartEventClips(struct Shared_World *scene,s32 resource,s32 group,Triple pos,f32 firstValue,f32 secondValue);
extern void *Scene_GetStridedWorldRecord(struct Shared_World *object, int index);
extern void Scene_ActivateTriggersOfKind(struct Shared_World *world, s32 triggerKind);
extern void Scene_ReleaseCachedLevelData(struct Shared_World *world);
extern void Scene_ShowResultsGoal(void);
#if defined(VERSION_US_REV1)
extern const unsigned char s_matricesText[9];
#endif
extern const char s_collisionText[10];
extern const char s_linksText[6];
extern const char s_levelPathsText[12];
extern const unsigned char s_levelInfoText[11];
extern const char g_levelNavigationResourceNames[32];
extern const unsigned char s_levelNavVisionText[17];
#if defined(VERSION_US_REV1)
extern const unsigned char s_animatedInstancesText[19];
#else
extern const char s_animatedInstancesText[19];
#endif
extern void Scene_FindLightVolumes(struct Shared_World *world, CVector3 *point, struct SceneLightVolume **volumes, s32 *total);
struct SceneResourceStateView {
    s32 loadStage; /* +0x0: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad4[0x18];
    s32 levelDirectoryKey; /* +0x1C: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad20[0x10];
    s32 sceneDirectoryKey; /* +0x30: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad34[0x8];
    u8 selectionClearCursorAnchor; /* +0x3C: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad3D[0x3];
    s32 visibilityResourceKey; /* +0x40: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad44[0x8];
    s32 * levelDirectory; /* +0x4C: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad50[0x10];
    s32 * sceneResources; /* +0x60: src/Scene_LoadLevelResources_SceneResourceState.c */
    u8 sceneIndexDataSlot; /* +0x64: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad65[0x3];
    void * gridBoundsAndSections; /* +0x68: src/Scene_LoadLevelResources_SceneResourceState.c */
    void * collisionData; /* +0x6C: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad70[0x1C];
    s32 * visibilityTable; /* +0x8C: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad90[0x24];
    s32 * slotPoolDefinition; /* +0xB4: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 levelIndexResourceHandle; /* +0xB8: src/Scene_LoadLevelResources_SceneResourceState.c */
    void ** collisionResourceHandle; /* +0xBC: src/Scene_LoadLevelResources_SceneResourceState.c */
    void ** gridBoundsResourceHandle; /* +0xC0: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 sceneIndexResourceHandle; /* +0xC4: src/Scene_LoadLevelResources_SceneResourceState.c */
    void ** levelInfoResourceHandle; /* +0xC8: src/Scene_LoadLevelResources_SceneResourceState.c */
    void ** skyLayersResourceHandle; /* +0xCC: src/Scene_LoadLevelResources_SceneResourceState.c */
    void ** animatedInstancesResourceHandle; /* +0xD0: src/Scene_LoadLevelResources_SceneResourceState.c */
    void ** actorLinksResourceHandle; /* +0xD4: src/Scene_LoadLevelResources_SceneResourceState.c */
    char padD8[0x10];
    s32 * matrixPoolResourceHandle; /* +0xE8: src/Scene_LoadLevelResources_SceneResourceState.c */
    void ** levelPathsResourceHandle; /* +0xEC: src/Scene_LoadLevelResources_SceneResourceState.c */
    void ** navPointsResourceHandle; /* +0xF0: src/Scene_LoadLevelResources_SceneResourceState.c */
    void ** navLinksResourceHandle; /* +0xF4: src/Scene_LoadLevelResources_SceneResourceState.c */
    char padF8[0x4];
    void ** navVisionResourceHandle; /* +0xFC: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 visibilityResourceHandle; /* +0x100: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad104[0x24];
    struct MapBlockAllocatorView matrixPool; /* +0x128, size 0x10 */
    void * levelActors; /* +0x138: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 levelActorCursor; /* +0x13C: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 levelActorCount; /* +0x140: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad144[0xF58 - 0x144];
    s32 kind1Cursor;
    char padF5C[0x1B08 - 0xF5C];
    u8 batchSlotPool; /* +0x1B08: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad1B09[0xFC6F];
    u8 effectPool; /* +0x11778: src/Scene_LoadLevelResources_SceneResourceState.c */
    char padAfterEffectPool[0x3C0F];
    u8 sceneEffectPool; /* +0x15388: src/Scene_LoadLevelResources_SceneResourceState.c */
    char padAfterSceneEffectPool[0x5F27];
    void * sceneSettings; /* +0x1B2B0: src/Scene_LoadLevelResources_SceneResourceState.c */
    char padAfterSceneSettings[0x8];
    u8 levelNameBuffer; /* +0x1B2BC: src/Scene_LoadLevelResources_SceneResourceState.c */
    char padAfterLevelNameBuffer[0x3F];
    f32 minimumCollisionY; /* +0x1B2FC: src/Scene_LoadLevelResources_SceneResourceState.c */
    void * skyLayerEntries; /* +0x1B300: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 skyLayerCount; /* +0x1B304: src/Scene_LoadLevelResources_SceneResourceState.c */
    char padAfterSkyLayerCount[0x18];
    u8 dynamicLightPool; /* +0x1B320: src/Scene_LoadLevelResources_SceneResourceState.c */
    char padAfterDynamicLightPool[0xE7];
    s32 specialSceneEnabled; /* +0x1B408: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 levelSelection; /* +0x1B40C: src/Scene_LoadLevelResources_SceneResourceState.c */
    char padAfterLevelSelection[0xC];
    s32 gameplayStarted; /* +0x1B41C: src/Scene_LoadLevelResources_SceneResourceState.c */
    char padAfterGameplayStarted[0x14];
    s32 spawnPlacementKey; /* +0x1B434: src/Scene_LoadLevelResources_SceneResourceState.c */
    char padAfterSpawnPlacementKey[0xA4];
    void * navPointSet; /* +0x1B4DC: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 navPointCount; /* +0x1B4E0: src/Scene_LoadLevelResources_SceneResourceState.c */
    void * navLinkSet; /* +0x1B4E4: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 navLinkCount; /* +0x1B4E8: src/Scene_LoadLevelResources_SceneResourceState.c */
    void * navVisionSet; /* +0x1B4EC: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 navVisionCount; /* +0x1B4F0: src/Scene_LoadLevelResources_SceneResourceState.c */
    char padAfterNavVisionCount[0xC];
    IntrusiveList navigationSearchNodes; /* +0x1B500: src/Scene_LoadLevelResources_SceneResourceState.c */
    char padAfterNavigationSearchNodes[0x100];
    f32 spawnOffsetX;
    f32 spawnOffsetY;
    f32 spawnOffsetZ;
    char padAfterSpawnOffsetZ[0x84];
    s32 selectedActorCount; /* +0x1B6A4: src/Scene_LoadLevelResources_SceneResourceState.c */
    char padAfterSelectedActorCount[0x4];
    s32 sceneLoadResetState; /* +0x1B6AC: src/Scene_LoadLevelResources_SceneResourceState.c */
    char padAfterSceneLoadResetState[0x260];
    s32 visibilityHeaderWord0; /* +0x1B910: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 visibilityHeaderWord1; /* +0x1B914: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 visibilityHeaderWord2; /* +0x1B918: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 visibilityHeaderWord3; /* +0x1B91C: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 visibilityHeaderWord4; /* +0x1B920: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 visibilityHeaderWord5; /* +0x1B924: src/Scene_LoadLevelResources_SceneResourceState.c */
    char padAfterVisibilityHeaderWord5[0x4];
    s32 hasVisibilityPayload; /* +0x1B92C: src/Scene_LoadLevelResources_SceneResourceState.c */
};
typedef struct SceneResourceStateView SceneResourceStateView;
extern void Scene_LoadLevelResources(struct SceneResourceStateView *table, s32 target, s32 allowTransition);
#if defined(VERSION_DE)
extern const char s_graphicsetText[12];
#else
extern const char s_graphicsetText[11];
#endif
extern char *g_resultsPlayerOrLivesSingularFormat;
extern char *g_resultsLivesPluralFormat;
extern char *g_resultsGoalLabelFormat;
extern char *g_resultsGoalSingularFormat;
extern char *g_resultsGoalsPluralFormat;
extern char *g_resultsGoalValueFormat;
extern char *g_resultsSingleLapsPluralFormat;
extern char *g_resultsSingleLapSingularFormat;
extern char *g_resultsLapSingularFormat;
extern char *g_resultsLapsControllerModeFormat;
extern char *g_resultsLapsPluralFormat;
extern char *g_resultsMinuteSingularFormat;
extern char *g_resultsMinuteSecondsSingularFormat;
extern char *g_resultsMinutesSecondsPluralFormat;
extern char *g_resultsMinutesPluralFormat;
extern char *g_resultsRoundsControllerModeFormat;
extern char *g_resultsRoundsPluralFormat;
extern char *g_resultsTimeLimitFormat;
#if defined(VERSION_DE)
extern void *g_resultsModeMessage[];
#else
extern char *g_resultsModeMessage;
extern char addrLow_SetN64_AdvanceIntroForMemorySize_us_rev1[];
extern char addrLow_SetN64_AdvanceIntroTextToOpeningCinema_us_rev1[];
extern char addrLow_SetN64_DrawCenteredIntroText_us_rev1[];
extern char addrLow_SetN64_DrawIntroBackdrop_us_rev1[];
extern char addrLow_SetN64_DrawRoundTimeoutSession_us_rev1[];
extern char addrLow_SetN64_ExitSessionAndDisablePaks_us_rev1[];
extern char addrLow_SetN64_InitializeFrontendScreenState_us_rev1[];
extern char addrLow_SetN64_InitializeIntroText_us_rev1[];
extern char addrLow_SetN64_ResetSceneForIntro_us_rev1[];
#endif
extern s32 g_textureVariationBypassEnabled;
extern unsigned char g_navigationLinksResourceName[];
extern unsigned char g_sceneAnimatedInstancesLoaderEntry[];
extern unsigned char g_sceneCollisionLoaderEntry[];
extern unsigned char g_sceneIndexResourceTag[];
extern unsigned char g_sceneLevelPathsLoaderEntry[];
extern unsigned char g_sceneLinksLoaderEntry[];
extern unsigned char g_spatialSoundPoolNodes[];
extern unsigned char g_visibilityHeaderResourceTag[];
extern struct LevelActor *g_fragTagObjectiveActor;
extern struct LevelActor *g_sceneFlagReturnPickupActor;
extern struct LevelActor *g_sceneTrackedActors[4];
extern struct ResultsHeadingCharacter g_resultCharacterHeadings[];
extern const char g_levelNameText[];
extern char g_resultsNameFormat_de[];
extern char g_scene_CompareDistanceDescendingEntry[];
extern char g_scene_SwapDistanceSortEntriesEntry[];
extern s32 g_scene_UnpackImagesWithHighBoostEntry;
extern s32 g_scene_UnpackImagesWithLowBoostEntry;
extern struct Shared_SceneResources g_tutorialStatusBars;
extern struct LevelActor *g_sceneSpecialActorTables[];
extern const char g_levelNameText[];
extern char g_resultsNameFormat_de[];
extern unsigned char g_cResource_UnpackRequestEntry[];
extern s32 g_scene_UnpackImagesWithHighBoostEntry;
extern s32 g_scene_UnpackImagesWithLowBoostEntry;
struct SceneActorCategoryListsView; struct ObjectSceneRegisterActorInSceneLists;
struct WorldTrigger;
extern s32 Scene_QueueTriggerTimer(struct Shared_World *world, struct WorldTrigger *trigger);
#endif
