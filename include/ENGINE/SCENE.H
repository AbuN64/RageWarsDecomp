#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H
/* Clip-ratio words the scene code loads with gMoveWd(G_MW_CLIP) in the F3DEX2 display lists. */
#define FRUSTRATIO_1 1
#define FRUSTRATIO_2 2
#include "COMMON/OBJB.H"
#include "COMMON/SCENERECAT10C0.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/COLORENTRY.H"
#include "SCENE/SCENEPRIMARYACTORS.H"

/* One cell of the floor grid: the polygons of the cell lie in its x/z bounds. */
typedef struct FloorCell {
    Bounds2D37 bounds;
    u32 count;
} FloorCell;

typedef struct SceneResourceStateView SceneResourceStateView;

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
    u8 matrixPool; /* +0x128: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad129[0xF];
    void * levelActors; /* +0x138: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 levelActorCursor; /* +0x13C: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 levelActorCount; /* +0x140: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad144[0xF58 - 0x144];
    s32 kind1Cursor;
    char padF5C[0x1B08 - 0xF5C];
    u8 batchSlotPool; /* +0x1B08: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad1B09[0xFC6F];
    u8 effectPool; /* +0x11778: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad11779[0x3C0F];
    u8 sceneEffectPool; /* +0x15388: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad15389[0x5F27];
    void * sceneSettings; /* +0x1B2B0: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad1B2B4[0x8];
    u8 levelNameBuffer; /* +0x1B2BC: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad1B2BD[0x3F];
    f32 minimumCollisionY; /* +0x1B2FC: src/Scene_LoadLevelResources_SceneResourceState.c */
    void * skyLayerEntries; /* +0x1B300: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 skyLayerCount; /* +0x1B304: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad1B308[0x18];
    u8 dynamicLightPool; /* +0x1B320: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad1B321[0xE7];
    s32 specialSceneEnabled; /* +0x1B408: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 levelSelection; /* +0x1B40C: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad1B410[0xC];
    s32 gameplayStarted; /* +0x1B41C: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad1B420[0x14];
    s32 spawnPlacementKey; /* +0x1B434: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad1B438[0xA4];
    void * navPointSet; /* +0x1B4DC: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 navPointCount; /* +0x1B4E0: src/Scene_LoadLevelResources_SceneResourceState.c */
    void * navLinkSet; /* +0x1B4E4: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 navLinkCount; /* +0x1B4E8: src/Scene_LoadLevelResources_SceneResourceState.c */
    void * navVisionSet; /* +0x1B4EC: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 navVisionCount; /* +0x1B4F0: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad1B4F4[0xC];
    IntrusiveList navigationSearchNodes; /* +0x1B500: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad1B514[0x100];
    f32 spawnOffsetX;
    f32 spawnOffsetY;
    f32 spawnOffsetZ;
    char pad1B620[0x84];
    s32 selectedActorCount; /* +0x1B6A4: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad1B6A8[0x4];
    s32 sceneLoadResetState; /* +0x1B6AC: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad1B6B0[0x260];
    s32 visibilityHeaderWord0; /* +0x1B910: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 visibilityHeaderWord1; /* +0x1B914: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 visibilityHeaderWord2; /* +0x1B918: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 visibilityHeaderWord3; /* +0x1B91C: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 visibilityHeaderWord4; /* +0x1B920: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 visibilityHeaderWord5; /* +0x1B924: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad1B928[0x4];
    s32 hasVisibilityPayload; /* +0x1B92C: src/Scene_LoadLevelResources_SceneResourceState.c */
};

struct ObjectCSceneStartEventClips {
    char pad[0xA8];
    struct StridedTable *clipGroupKeys;
    struct StridedTable *clipDefinitions;
};

struct Container {
    char pad0[0x138];
    struct SceneActorMatchRecord *actors;
    s32 actorCursor;
    s32 actorCount;
};

struct ScenePackSectionTableView {
    char pad0[0x78];
    void * sectionTable;
};

struct SceneActiveResourceCountView {
    char pad0[0x10BC];
    int activeResourceCount;
};

struct SceneNestedPackSectionTableView {
    char pad0[0x7C];
    void * nestedSectionTable;
};

struct OwnerSceneUnlockActiveSectionResources {
    char pad0[0x944];
    s32 reservedWord944;
    char pad948[0xC4C - 0x948];
    s32 reservedWordC4C;
    char padC50[0x10BC - 0xC50];
    s32 activeResourceCount;
    char pad10C0[0x1500 - 0x10C0];
    s32 prevCount;
    s32 count;
    Triple entries[1];
};

typedef struct AnimationPoseFrameSet {
    s32 stride;
    s32 count;
    AnimationPoseFrame frames[1];
} AnimationPoseFrameSet;

struct Field_void_80 {
    char pad[0x80];
    void * value;
};

typedef struct Shared_SceneActorKind Shared_SceneActorKind;

struct Shared_SceneActorKind {
    u16 kind; /* +0x0: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char Shared_SceneActorKind_size_check[(sizeof(Shared_SceneActorKind) == 0x2) ? 1 : -1];

typedef struct Shared_SceneActorPrefix Shared_SceneActorPrefix;

struct Shared_SceneActorPrefix {
    u8 pad0[24]; /* +0x0: src/Scene_LoadLevelResources_SceneResourceState.c */
    void * definition; /* +0x18: src/Scene_LoadLevelResources_SceneResourceState.c */
    u8 pad1C[200]; /* +0x1C: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char Shared_SceneActorPrefix_size_check[(sizeof(Shared_SceneActorPrefix) == 0xE4) ? 1 : -1];

typedef struct Shared_SceneActorResources Shared_SceneActorResources;

struct Shared_SceneActorResources {
    u8 base; /* +0x0: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char Shared_SceneActorResources_size_check[(sizeof(Shared_SceneActorResources) == 0x1) ? 1 : -1];

typedef struct Shared_SceneActorStride Shared_SceneActorStride;

struct Shared_SceneActorStride {
    u8 bytes[744]; /* +0x0: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char Shared_SceneActorStride_size_check[(sizeof(Shared_SceneActorStride) == 0x2E8) ? 1 : -1];

/* Step through the scene actor storage using its verified element size. */
#define NEXT_SCENE_ACTOR(ptr) ((void *)(((struct Shared_SceneActorStride *)(ptr)) + 1))

typedef struct Shared_SceneActorTables Shared_SceneActorTables;

struct Shared_SceneActorTables {
    void * kind64e[10]; /* +0x0: src/Scene_LoadLevelResources_SceneResourceState.c */
    Shared_ScenePrimaryActors primary; /* +0x28: src/Scene_LoadLevelResources_SceneResourceState.c */
    void * kindBd6; /* +0x3C: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char Shared_SceneActorTables_size_check[(sizeof(Shared_SceneActorTables) == 0x40) ? 1 : -1];

typedef struct Shared_SceneFontResources Shared_SceneFontResources;

struct Shared_SceneFontResources {
    u8 bytes[712]; /* +0x0: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char Shared_SceneFontResources_size_check[(sizeof(Shared_SceneFontResources) == 0x2C8) ? 1 : -1];

typedef struct Shared_SceneGlobal Shared_SceneGlobal;

struct Shared_SceneGlobal {
    u8 pad0[72]; /* +0x0: src/Scene_LoadLevelResources_SceneResourceState.c */
    u8 address48; /* +0x48: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char Shared_SceneGlobal_size_check[(sizeof(Shared_SceneGlobal) == 0x49) ? 1 : -1];

typedef struct Shared_SceneResources Shared_SceneResources;

struct Shared_SceneResources {
    Shared_SceneFontResources font; /* +0x0: src/Scene_LoadLevelResources_SceneResourceState.c */
    Shared_SceneActorResources actors; /* +0x2C8: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char Shared_SceneResources_size_check[(sizeof(Shared_SceneResources) == 0x2C9) ? 1 : -1];

typedef struct SceneResourceFlagsView SceneResourceFlagsView;

struct SceneResourceFlagsView {
    char pad0[0x10];
    u8 flags; /* +0x10: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char SceneResourceFlagsSizeCheck[(sizeof(SceneResourceFlagsView) == 0x11) ? 1 : -1];

typedef struct SceneResourceSixWordRecord SceneResourceSixWordRecord;

struct SceneResourceSixWordRecord {
    s32 visibilityHeaderWord0; /* +0x0: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 visibilityHeaderWord1; /* +0x4: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 visibilityHeaderWord2; /* +0x8: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 visibilityHeaderWord3; /* +0xC: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 visibilityHeaderWord4; /* +0x10: src/Scene_LoadLevelResources_SceneResourceState.c */
    s32 visibilityHeaderWord5; /* +0x14: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char SceneResourceSixWordRecordSizeCheck[(sizeof(SceneResourceSixWordRecord) == 0x18) ? 1 : -1];

typedef struct ScenePlayerNavigationLinkView ScenePlayerNavigationLinkView;

struct ScenePlayerNavigationLinkView {
    char pad0[0x8];
    u8 address8; /* +0x8: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad9[0x144B];
    void * navigationRecord; /* +0x1454: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad1458[0x288];
    void * nextPlayer; /* +0x16E0: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char ScenePlayerNavigationLinkSizeCheck[(sizeof(ScenePlayerNavigationLinkView) == 0x16E4) ? 1 : -1];

typedef struct SceneLoadedResourceView SceneLoadedResourceView;

struct SceneLoadedResourceView {
    char pad0[0x1B664];
    void * loadedResource; /* +0x1B664: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char SceneLoadedResourceViewSizeCheck[(sizeof(SceneLoadedResourceView) == 0x1B668) ? 1 : -1];

typedef struct SceneSelectedActorSlotView SceneSelectedActorSlotView;

struct SceneSelectedActorSlotView {
    char pad0[0x1B664];
    s32 selectedActor; /* +0x1B664: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char SceneSelectedActorSlotSizeCheck[(sizeof(SceneSelectedActorSlotView) == 0x1B668) ? 1 : -1];

typedef struct SceneActorDefinitionKindView SceneActorDefinitionKindView;

struct SceneActorDefinitionKindView {
    s32 kind; /* +0x0: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad4[0x24];
    s16 flags; /* +0x28: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad2A[0x2];
};

typedef char SceneActorDefinitionKindSizeCheck[(sizeof(SceneActorDefinitionKindView) == 0x2C) ? 1 : -1];

typedef struct ScenePackedResourceTableView ScenePackedResourceTableView;

struct ScenePackedResourceTableView {
    char pad0[0x4];
    s32 count; /* +0x4: src/Scene_LoadLevelResources_SceneResourceState.c */
    u8 address8; /* +0x8: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad9[0x3];
};

typedef char ScenePackedResourceTableSizeCheck[(sizeof(ScenePackedResourceTableView) == 0xC) ? 1 : -1];

typedef struct LevelResourceLoadFlags LevelResourceLoadFlags;

struct LevelResourceLoadFlags {
    char pad0[0x78];
    u8 loadFlagFirst; /* +0x78: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad79[0x18];
    u8 loadFlagSecond; /* +0x91: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char LevelResourceLoadFlagsSizeCheck[(sizeof(LevelResourceLoadFlags) == 0x92) ? 1 : -1];

typedef struct SceneStatusBarModeView SceneStatusBarModeView;

struct SceneStatusBarModeView {
    char pad0[0x84];
    u8 address84; /* +0x84: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad85[0xF];
    u8 statusBarMode; /* +0x94: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char SceneStatusBarModeSizeCheck[(sizeof(SceneStatusBarModeView) == 0x95) ? 1 : -1];

typedef struct SceneSpecialActorModeView SceneSpecialActorModeView;

struct SceneSpecialActorModeView {
    char pad0[0x98];
    s32 statusBarsEnabled; /* +0x98: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char SceneSpecialActorModeSizeCheck[(sizeof(SceneSpecialActorModeView) == 0x9C) ? 1 : -1];

typedef struct SceneActorKindView SceneActorKindView;

struct SceneActorKindView {
    Shared_SceneActorPrefix prefix; /* +0x0: src/Scene_LoadLevelResources_SceneResourceState.c */
    Shared_SceneActorKind kind; /* +0xE4: src/Scene_LoadLevelResources_SceneResourceState.c */
    char padE6[0x2];
};

typedef char SceneActorKindViewSizeCheck[(sizeof(SceneActorKindView) == 0xE8) ? 1 : -1];

typedef struct SceneLoadWordPairView SceneLoadWordPairView;

struct SceneLoadWordPairView {
    char pad0[0x4];
    s32 reservedWord; /* +0x4: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char SceneLoadWordPairView_size_check[(sizeof(SceneLoadWordPairView) == 0x8) ? 1 : -1];

typedef struct Shared_SceneLoadLevelResources Shared_SceneLoadLevelResources;

struct Shared_SceneLoadLevelResources {
    char pad0[0x4];
    s32 reservedWord; /* +0x4: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char Shared_SceneLoadLevelResources_size_check[(sizeof(Shared_SceneLoadLevelResources) == 0x8) ? 1 : -1];

typedef struct SceneResourceSectionPointerView SceneResourceSectionPointerView;

struct SceneResourceSectionPointerView {
    char pad0[0x18];
    s32 * sectionWords; /* +0x18: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char SceneResourceSectionPointerSizeCheck[(sizeof(SceneResourceSectionPointerView) == 0x1C) ? 1 : -1];

typedef struct ScenePlayerResourceView ScenePlayerResourceView;

struct ScenePlayerResourceView {
    char pad0[0x5D8];
    struct ScenePlayerProfileView * profile; /* +0x5D8: src/Scene_LoadLevelResources_SceneResourceState.c */
    char pad5DC[0xE78];
    s32 controllerState; /* +0x1454: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char ScenePlayerResourceViewSizeCheck[(sizeof(ScenePlayerResourceView) == 0x1458) ? 1 : -1];

typedef struct SceneResourceSectionHeader SceneResourceSectionHeader;

struct SceneResourceSectionHeader {
    char pad0[0x4];
    s32 reservedWord; /* +0x4: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char SceneResourceSectionHeaderSizeCheck[(sizeof(SceneResourceSectionHeader) == 0x8) ? 1 : -1];

typedef struct ScenePlayerProfileView ScenePlayerProfileView;

struct ScenePlayerProfileView {
    char pad0[0x80];
    s8 characterKind; /* +0x80: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char ScenePlayerProfileViewSizeCheck[(sizeof(ScenePlayerProfileView) == 0x81) ? 1 : -1];

typedef struct ScenePackedResourceCountView ScenePackedResourceCountView;

struct ScenePackedResourceCountView {
    char pad0[0x4];
    s32 count; /* +0x4: src/Scene_LoadLevelResources_SceneResourceState.c */
};

typedef char ScenePackedResourceCountSizeCheck[(sizeof(ScenePackedResourceCountView) == 0x8) ? 1 : -1];

struct NearbySpecialActorView {
    u8 kind;
    char pad1[0x17];
    s32 *definition;
    char pad2[0xE4 - 0x1C];
    u16 modelId;
};

extern void Scene_CopySimpleModelHeader(void *,void *,s32);
#endif
