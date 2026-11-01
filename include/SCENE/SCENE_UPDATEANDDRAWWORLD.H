#ifndef SCENE_SCENE_UPDATEANDDRAWWORLD_H
#define SCENE_SCENE_UPDATEANDDRAWWORLD_H
#include "COMMON/INTEGERSTATEB0.H"
#include "ENGINE/SCENE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SCENERECAT10C0.H"
struct CacheResourceBlockView;
typedef struct FloorGrid {
    s32 stride;
    s32 cellCount;
    FloorCell cells[0];
} FloorGrid;
/* Counted polygon records in model resource section 2. */
typedef struct FloorPolygonTable {
    s32 stride;
    s32 count;
    Node75 polygons[1];
} FloorPolygonTable;
/* A placed prop instance (0xE8 bytes), stored inline in a scene cell resource's section 0. */
struct ObjectSceneDrawCachedOpaqueGeometry {
    char pad0[0x20];
    DraftStreamHandle *resource;
    char pad24[4];
    PackedMatrixWords transform;
    char pad68[0xD8 - 0x68];
    u16 flags;
    char padDA[0xE8 - 0xDA];
};
struct SceneLevelSwitchCollectionView {
    char pad0[0x138];
    struct SceneSwitchObjectView *objects;
    s32 pad13C;
    s32 count;
    char pad144[0x1B620 - 0x144];
    SceneSwitchObjectView *switches[16];
    s32 switchCount;
};
struct Entity {
    char pad0[0xF];
    unsigned char flag;
    char pad10[3];
    unsigned char index;
};
struct GlobalMode {
    char pad[0x1295];
    u8 mode;
};
struct ScenePackResourceView {
    unsigned char padding_0[112];
    void *pack;
};
typedef struct DraftStreamTable {
    s32 stride, count;
    union { f32 coordinates[1]; DraftStreamCell cells[1]; struct ObjectSceneDrawCachedOpaqueGeometry objects[1]; u8 bytes[1]; } data;
} DraftStreamTable;
typedef struct DraftStreamWorld {
    char pad0[0x30]; s32 key;
    char pad34[0xC]; s32 resourceKey;
    char pad44[0x20]; void *table, *grid;
    char pad6C[0x1C]; s32 *cache; void *specialTable;
    char pad90[0x68]; struct CacheResourceBlockView *cacheHandle;
    char padFC[0x1404]; s32 entryCount, activeCount;
    DraftStreamEntry entries[128];
    char pad1B08[0x1B2FC - 0x1B08]; f32 maximumHeight;
    char pad1B300[0x1B6B0 - 0x1B300]; DraftStreamHandle *special;
    char specialState[604];
    f32 originX, originZ, cellX, cellZ;
    char pad1B920[8]; s32 specialPresent, specialEnabled;
} DraftStreamWorld;
extern void Scene_UpdateAndDrawWorld(void *sceneState);
#endif
