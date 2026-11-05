#ifndef COMMON_WORLD_H
#define COMMON_WORLD_H
#include "types.h"
#include "Common/navigation_graph.h"
struct Shared_World;
struct WorldSectorExtent;
struct StridedTable;
struct BitReader;
typedef struct BitReader BitReader;





struct BitReader;
struct BitReader {
    u8 *data;
    s32 bitPos;
};

/* The 0x25C-byte region-grid state (Visdata_DecodeRegionGrid fills it): the bit reader on the stream, the grid's origin,
 * the last cell lookup, and one signed code (or stream offset) per cell of the 17x17 grid. */
struct ResourceBitGrid;
typedef struct ResourceBitGrid ResourceBitGrid;
struct ResourceBitGrid {
    BitReader reader;
    s32 originX;
    s32 originY;
    s32 cellState;
    s32 cellValue;
    s16 cells[17 * 17];
};

#include "Common/scene_switch.h"
#include "types.h"
#include "Common/level_track.h"
#include "Common/sharedplayer.h"
#include "Common/effect_slot_pool.h"
#include "Common/results.h"
#include "Gobjinst/gameobject_getactorheight.h"
#include "Menu/Items/Scene/scene_setlevelactorstatebit.h"
#include "Ovlgame/ovlgame_initializedynamiclightpool.h"
#include "Engine/map.h"
#include "Common/shared_particleinstance.h"
struct Shared_Pickup;
struct WorldTrigger;
struct WorldTrigger {
    u32 coordinates[3];
    u16 lifetime;
    u8 flags;
    u8 kind; /* 0: plain solid face; nonzero: trigger kind, Scene_UnpackVisibilityGeometry clears flags bit 0 */
    u8 state;
    u8 active;
    u8 mode;
    u8 visibilityGroup; /* bit index in the level's state bitmap (Shared_World.bitSections) */
};
typedef struct WorldTrigger WorldTrigger;
struct LevelActor;
typedef struct SceneResourceSixWordRecord {
    f32 originX; /* +0x0 */
    f32 originZ; /* +0x4 */
    f32 cellX; /* +0x8 */
    f32 cellZ; /* +0xC */
    s32 columnCount; /* +0x10 */
    s32 rowCount; /* +0x14 */
} SceneResourceSixWordRecord;
typedef char SceneResourceSixWordRecordSizeCheck[(sizeof(SceneResourceSixWordRecord) == 0x18) ? 1 : -1];

/* A world sector's x/z extent. */
typedef struct WorldSectorExtent {
    f32 minX;
    f32 minZ;
    f32 maxX;
    f32 maxZ;
    s32 occupied; /* +0x10: streamed cell exists; 20-byte source record */
} WorldSectorExtent;
typedef struct WorldSector {
    struct CacheResourceNode *resource;
    struct WorldSectorExtent *bounds;
    s16 gridX, gridZ; /* +0x8: streamed cell coordinates */
} WorldSector;
/* The seven words copied from a simple-model pack header by Scene_CopySimpleModelHeader. */
typedef struct SimpleModelHeader { u32 words[7]; } SimpleModelHeader;
/* One trigger timer slot: Scene_QueueTriggerTimer moves it from the world's free list to its
   active list with the trigger and its remaining lifetime. */
struct CActiveLink;
typedef struct CActiveLink CActiveLink;
struct CActiveLink {
    struct CActiveLink *prev;
    struct CActiveLink *next;
    struct WorldTrigger *object;
    f32 remaining;
};
typedef struct Shared_World {
    s32 mode;
    s32 previewLoaded; /* +0x4: set after Scene_LoadPreviewBufferA copies the resource */
    s32 sceneResourceResetState; /* +0x8: Scene_LoadSceneResources resets this word */
    s32 challengeFile; /* 0xC: file id of the per-level challenge table index */
    s32 challengeFileSize; /* 0x10 */
    void **resourceHandle; /* 0x14 */
    s32 resourceKey; /* 0x18 */
    s32 resourceBank; /* 0x1C */
    s32 textureBank;
    s32 indexedBank; /* 0x24 */
    s32 lookupBank; /* 0x28 */
    s32 resourceKindBank; /* +0x2C: Scene_StartWorldEffect */
    s32 sceneDirectoryKey; /* +0x30 */
    s32 trackLookup; /* 0x34 */
    s32 previewDirectoryKey; /* +0x38: Scene_LoadPreviewBufferA */
    union {
        s32 previewResourceKey; /* +0x3C: Scene_LoadPreviewBufferB */
        u8 selectionClearCursorAnchor; /* reverse selection reset cursor */
    };
    s32 visibilityResourceKey; /* +0x40 */
    s32 noteCount; /* 0x44: MENU/PAK 80409AC0, 80408870 */
    s32 previewResourceBank; /* +0x48: Scene_LoadPreviewBufferB */
    s32 *resourceDirectory; /* 0x4C */
    s32 textureDirectory;
    s32 *indexedDirectory; /* 0x54 */
    s32 *lookupDirectory; /* 0x58 */
    s32 *resourceKindDirectory; /* +0x5C: Scene_StartWorldEffect */
    s32 *sceneResources; /* +0x60 */
    void *sceneIndexData; /* +0x64: pinned resource output */
    void *gridBoundsAndSections; /* +0x68 */
    s32 *modelSections; /* 0x6C */
    s32 *objectSections; /* 0x70 */
    s32 *trackBundle; /* 0x74: g_trackResourceDirectory */
    s32 *actorDefinitions; /* 0x78: count followed by record offsets */
    s32 *routeCount; /* +0x7C: PatrolRouteSet */
    void *bitSections; /* 0x80 */
    void *secondaryLevels; /* 0x84 */
    s32 *cachedGeometryPack; /* +0x88: three-section resource/prop/display-list pack */
    s32 *visibilityTable; /* +0x8C */
    void *placedObjectTable; /* 0x90: keys and 20-byte placed track objects */
    struct SceneModelIdTable *modelIds; /* 0x94 */
    struct StridedTable *lookupTable; /* 0x98 */
    struct SceneModelIdTable *resourceKindTable; /* +0x9C */
    struct StridedTable *records; /* 0xA0 */
    struct StridedTable *stridedRecords; /* 0xA4 */
    struct StridedTable *eventClipGroups; /* +0xA8: section 15, sorted clip-group ids */
    struct StridedTable *eventClipDefinitions; /* +0xAC: section 14, clip descriptors */
    struct Table *triggerCounterIds; /* +0xB0: ids of the counter bytes in bitSections */
    s32 *slotPoolDefinition; /* +0xB4 */
    s32 levelIndexResourceHandle; /* +0xB8 */
    void **collisionResourceHandle; /* +0xBC */
    void **gridBoundsResourceHandle; /* +0xC0 */
    s32 sceneIndexResourceHandle; /* +0xC4 */
    void **levelInfoResourceHandle; /* +0xC8 */
    void **skyLayersResourceHandle; /* +0xCC */
    void **animatedInstancesResourceHandle; /* +0xD0 */
    void **actorLinksResourceHandle; /* +0xD4 */
    u8 unknownD8[0x10];
    s32 resource;
    void **levelPathsResourceHandle; /* +0xEC */
    void **navPointsResourceHandle; /* +0xF0 */
    void **navLinksResourceHandle; /* +0xF4 */
    struct CacheResourceNode *cachedGeometryHandle; /* +0xF8: owns cachedGeometryPack */
    void **navVisionResourceHandle; /* +0xFC */
    s32 visibilityResourceHandle; /* +0x100 */
    u8 unknown104[8];
    void *warpDestinationsResourceHandle; /* +0x10C */
    u8 unknown110[0x10];
    Gfx *cachedDisplayLists[2]; /* +0x120: opaque and flag-4 prop passes */
    struct MapBlockAllocatorView matrixPool; /* +0x128 */
    struct LevelActor *actors; /* 0x138 */
    s32 createdActorCount; /* 0x13C: constructed prefix */
    s32 actorCapacity; /* 0x140: allocated actor extent */
    struct LevelActor *interactive[512]; /* 0x144: InstHdr_CanActorReceiveInteraction accepts */
    s32 interactiveCount; /* 0x944 */
    struct LevelActor *movers[128]; /* 0x948: InstHdr_HasEnabledMotionHooks accepts */
    s32 moverCount; /* 0xB48 */
    void *queued[64]; /* 0xB4C: static props and event instances awaiting dispatch */
    s32 queuedCount; /* 0xC4C */
    struct LevelActor *registered[128]; /* 0xC50: every registered object */
    s32 registeredCount; /* 0xE50 */
    struct LevelActor *kind1[64]; /* 0xE54: definition kind 1 */
    s32 kind1Count; /* 0xF54 */
    s32 kind1Cursor; /* 0xF58: round-robin position in kind1, wraps at kind1Count */
    struct LevelActor *flagged[32]; /* 0xF5C: flags & 2 */
    s32 flaggedCount; /* 0xFDC */
    struct LevelActor *kind5[16]; /* 0xFE0: definition kind 5 */
    s32 kind5Count; /* 0x1020 */
    struct LevelActor *model64F[32]; /* 0x1024 */
    s32 model64FCount; /* 0x10A4 */
    struct LevelActor *model64D[4]; /* 0x10A8 */
    s32 model64DCount; /* 0x10B8 */
    s32 drawableCount; /* 0x10BC */
    void *drawables[64]; /* 0x10C0 */
    s32 recordCount; /* 0x11C0 */
    s32 alternateRecordCount; /* 0x11C4 */
    s32 * recordIndex; /* 0x11C8 */
    s32 * alternateRecordIndex; /* 0x11CC */
    struct WorldTrigger * recordArray; /* 0x11D0 */
    struct WorldTrigger * alternateRecordArray; /* 0x11D4 */
    IntrusiveList activeTriggerTimers; /* 0x11D8: Scene_QueueTriggerTimer, Scene_UpdateTriggerTimers */
    IntrusiveList freeTriggerTimers; /* 0x11EC */
    CActiveLink triggerTimers[48]; /* 0x1200: filed into freeTriggerTimers by Scene_UnpackVisibilityGeometry */
    s32 sectorEntryCount; /* 0x1500: Link_SumWorldSectionCounts */
    s32 sectorCount; /* 0x1504 */
    WorldSector sectors[128]; /* 0x1508 */
    struct EffectSystem particles; /* +0x1B08, extent 0xFC6C */
    u8 unknownAfterParticles[4];
    EffectSlotPool effectSlots;
    u8 reservedBytes9[4];
    struct CAnimPool sceneEffects; /* +0x15388, extent 0x5F28 */
    struct CROMLevel_t *levelInfo; /* 0x1B2B0 */
    s16 lightDirection[3]; /* +0x1B2B4: normalized by Scene_LoadSceneLight */
    u8 unknownAfterLightDirection[2];
    char levelName[64]; /* +0x1B2BC: Scene_CopyLevelName, limit 63 */
    f32 minimumCollisionY; /* +0x1B2FC */
    void *skyLayerEntries; /* +0x1B300 */
    s32 skyLayerCount; /* +0x1B304 */
    f32 elapsed;
    u8 unknownAfterElapsed[0x10];
    f32 eventPhase; /* +0x1B31C: static attachment-event phase */
    struct CGameDynamicLight_t dynamicLightPool; /* +0x1B320, two lists and eight lights: 0xE8 */
    s32 visibilityEnabled; /* 0x1B408 */
    s32 level; /* 0x1B40C */
    s32 selectionState; /* 0x1B410 */
    s32 frozen;
    f32 selectionTimer; /* 0x1B418 */
    s32 selectionFlags; /* 0x1B41C */
    Shared_Placed selectionSpawn; /* 0x1B420: selected track spawn */
    s32 selectionValues[4]; /* 0x1B434 */
    s32 previewState; /* 0x1B444 */
    s32 previewTimer; /* 0x1B448 */
    s32 previewStart; /* 0x1B44C */
    SimpleModelHeader simpleModelHeaders[5]; /* +0x1B450: five 28-byte pack headers */
    CNavData navigation; /* +0x1B4DC: complete 0x138-byte navigation graph */
    CVector3 offset;
    struct LevelActor *objects[16]; /* +0x1B620: collected kind-13 switches */
    s32 count;
    struct LevelActor *specialActors[16]; /* 0x1B664 */
    s32 specialActorCount; /* 0x1B6A4 */
    u8 unknownAfterSpecialActorCount[4];
    s32 sceneLoadResetState; /* +0x1B6AC */
    struct CacheResourceNode *visibilityData; /* +0x1B6B0: locked region stream */
    ResourceBitGrid visibilityGrid; /* +0x1B6B4, decoded region grid: 0x25C */
    SceneResourceSixWordRecord visibilityHeader; /* +0x1B910: copied grid configuration */
    s32 visibilityValid; /* +0x1B928: visible-sector producer and draw consumer */
    s32 hasVisibilityPayload; /* +0x1B92C */
} Shared_World;
extern struct Shared_World g_world;
/* The actor count (g_world_AchieveUpdateresultsscreen + 0x140) read as its own object: each access has its own lui. */
extern s32 g_navigationPlatformActorCount;
#endif
