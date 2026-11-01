#ifndef COMMON_WORLD_H
#define COMMON_WORLD_H
#include "COMMON/SCENERECAT10C0.H"
#include "TYPES.H"
#include "COMMON/LEVEL_TRACK.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RESULTS.H"
struct Shared_Pickup;
struct Record14;
struct LevelActor;
/* A world sector's model: its first word is the pack table SetN64_GetPackSection reads
   (section 2 holds the sector's light volumes). */
typedef struct WorldSectorModel {
    void *pack;
} WorldSectorModel;
/* A world sector's x/z extent. */
typedef struct WorldSectorExtent {
    f32 minX;
    f32 minZ;
    f32 maxX;
    f32 maxZ;
} WorldSectorExtent;
typedef struct WorldSector {
    WorldSectorModel *resource;
    WorldSectorExtent *bounds;
    u16 ids[2];
} WorldSector;
typedef struct Shared_World {
    s32 mode;
    u8 reservedBytes[8];
    s32 challengeFile; /* 0xC: file id of the per-level challenge table index */
    s32 challengeFileSize; /* 0x10 */
    void **resourceHandle; /* 0x14 */
    s32 resourceKey; /* 0x18 */
    s32 resourceBank; /* 0x1C */
    s32 textureBank;
    s32 indexedBank; /* 0x24 */
    s32 lookupBank; /* 0x28 */
    s32 resourceKindBank; /* +0x2C: Scene_StartWorldEffect */
    u8 reservedBytes1[4];
    s32 trackLookup; /* 0x34 */
    u8 reservedBytes2[0xC];
    s32 noteCount; /* 0x44: MENU/PAK 80409AC0, 80408870 */
    u8 unknown48[4];
    s32 *resourceDirectory; /* 0x4C */
    s32 textureDirectory;
    s32 *indexedDirectory; /* 0x54 */
    s32 *lookupDirectory; /* 0x58 */
    s32 *resourceKindDirectory; /* +0x5C: Scene_StartWorldEffect */
    u8 reservedBytes3[0xC];
    s32 *modelSections; /* 0x6C */
    s32 *objectSections; /* 0x70 */
    s32 *trackBundle; /* 0x74: g_trackResourceDirectory */
    s32 *actorDefinitions; /* 0x78: count followed by record offsets */
    s32 *routeCount; /* +0x7C: PatrolRouteSet */
    void *bitSections; /* 0x80 */
    void *secondaryLevels; /* 0x84 */
    u8 reservedBytes4[8];
    void *placedObjectTable; /* 0x90: keys and 20-byte placed track objects */
    struct SceneModelIdTable *modelIds; /* 0x94 */
    StridedTable *lookupTable; /* 0x98 */
    struct SceneModelIdTable *resourceKindTable; /* +0x9C */
    StridedTable *records; /* 0xA0 */
    StridedTable *stridedRecords; /* 0xA4 */
    u8 reservedBytes5[4];
    StridedTable *actorRecords; /* 0xAC */
    u8 reservedBytes6[0x38];
    s32 resource;
    u8 reservedBytes7[0x34];
    s32 counter120;
    s32 counter124;
    u8 system128[16];
    struct LevelActor *actors; /* 0x138 */
    s32 actorCapacity; /* 0x13C */
    s32 actorCount; /* 0x140 */
    struct LevelActor *interactive[512]; /* 0x144: InstHdr_CanActorReceiveInteraction accepts */
    s32 interactiveCount; /* 0x944 */
    struct LevelActor *movers[128]; /* 0x948: InstHdr_HasEnabledMotionHooks accepts */
    s32 moverCount; /* 0xB48 */
    struct LevelActor *queued[64]; /* 0xB4C */
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
    struct Record14 * recordArray; /* 0x11D0 */
    struct Record14 * alternateRecordArray; /* 0x11D4 */
    u8 reservedBytes8[0x328];
    s32 sectorEntryCount; /* 0x1500: Link_SumWorldSectionCounts */
    s32 sectorCount; /* 0x1504 */
    WorldSector sectors[128]; /* 0x1508 */
    u8 system1B08[0x11778 - 0x1B08];
    EffectSlotPool system11778;
    u8 reservedBytes9[4];
    u8 effectPool[0x1B2B0 - 0x15388]; /* 0x15388: CAnimPool */
    struct CROMLevel_t *levelInfo; /* 0x1B2B0 */
    u8 reservedBytes10[0x1B308 - 0x1B2B4];
    f32 elapsed;
    u8 reservedBytes11[0xFC];
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
    u8 reservedBytes12[0x1C4];
    CVector3 offset;
    struct Shared_Pickup *objects[16];
    s32 count;
    struct LevelActor *specialActors[16]; /* 0x1B664 */
    s32 specialActorCount; /* 0x1B6A4 */
} Shared_World;
extern Shared_World g_world;
/* The actor count (g_world_AchieveUpdateresultsscreen + 0x140) read as its own object: each access has its own lui. */
extern s32 g_navigationPlatformActorCount;
#endif
