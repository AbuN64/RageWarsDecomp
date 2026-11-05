#ifndef SCENE_SCENE_UPDATEANDDRAWWORLD_H
#define SCENE_SCENE_UPDATEANDDRAWWORLD_H
#include "Engine/gregion.h"
#include "Common/frontend_clock_state.h"
#include "Engine/scene.h"
#include "Common/world.h"
#include "Common/scene_switch.h"
struct CacheResourceNode;
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
/* Separate pack sections retain their actual element types; no payload overlay. */
typedef struct GridAxisSection {
    s32 stride, count;
    f32 coordinates[0];
} GridAxisSection;
typedef struct WorldSectorExtentTable {
    s32 stride, count;
    WorldSectorExtent cells[0];
} WorldSectorExtentTable;
typedef struct ScenePropSection {
    s32 stride, count;
    ObjA props[0];
} ScenePropSection;
extern void Scene_UpdateAndDrawWorld(void *sceneState);
#endif
