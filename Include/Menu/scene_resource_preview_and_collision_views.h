#ifndef MENU_SCENE_RESOURCE_PREVIEW_AND_COLLISION_VIEWS_H
#define MENU_SCENE_RESOURCE_PREVIEW_AND_COLLISION_VIEWS_H
#include "types.h"
#include "Common/gameplay_camera.h"
#include "Common/level_actor.h"
#include "Common/objb.h"
#include "Common/packed.h"
#include "Common/sharedplayer.h"
/* The resource header is followed by count input records or runtime actors. */
typedef struct LevelBlock {
    s32 size;
    s32 count;
    LevelActor objects[1];
} LevelBlock;
struct Node_Items_FindPlacedObjectsByKey {
    s32 index;
    s32 link[2];
};

typedef struct CollisionBuildHeader {
    s32 count;
    s32 offsets[5];
} CollisionBuildHeader;
typedef struct CollisionBuildList {
    s32 kind;
    s32 count;
    CollisionBuildFace items[0];
} CollisionBuildList;
typedef union CollisionBuildMeshHandle {
    struct CacheResourceNode canonical;
    struct { void *data; s32 size,refs,flags; } payload;
} CollisionBuildMeshHandle;
typedef struct CollisionBuildVertexList { s32 kind,count; CollisionBuildVertex items[0]; } CollisionBuildVertexList;
typedef struct CollisionBuildTriangleList { s32 kind,count; CollisionBuildTriangle items[0]; } CollisionBuildTriangleList;

#endif
