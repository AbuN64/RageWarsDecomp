#ifndef COMMON_SCENE_SWITCH_H
#define COMMON_SCENE_SWITCH_H
#include <PR/ultratypes.h>
typedef struct Bounds2D37 { f32 minX,minZ,maxX,maxZ; } Bounds2D37;
#include "types.h"
#include "Common/vector4f.h"
#include <platform_sdk.h>
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"
#include "Common/sharedplayer.h"
struct SceneStreamPair;
struct LevelActor;


struct SceneModelIdTable;
typedef struct SceneModelIdTable SceneModelIdTable;

struct Shared_World;

struct Entity;
typedef struct Entity Entity;


struct SceneSwitchDescriptor;
typedef struct SceneSwitchDescriptor SceneSwitchDescriptor;

struct SceneModelIdTable;
struct SceneModelIdTable {
    s32 unused;
    s32 count;
    u16 entries[1];
};


struct SceneSwitchDescriptor;
struct SceneSwitchDescriptor {
    s32 type;
    s32 flags;
    char pad8[4];
    s16 model;
    char padE[0x20 - 0xE];
    s32 kind;
};

struct SceneSwitchDescriptor;





struct Entity;



struct GlobalMode;


struct SceneModelIdTable;


struct GlobalMode;
typedef struct GlobalMode GlobalMode;


struct ObjectSceneChangeInstanceModel;
#include "Common/model_instance.h"


struct ObjectSceneChangeInstanceModel;
typedef struct ObjectSceneChangeInstanceModel ObjectSceneChangeInstanceModel;



struct ResourceBitGrid;
struct Pack;
extern void Visdata_DecodeRegionGrid(struct ResourceBitGrid *, s32, s32, struct Pack *, CVector3 *);

typedef struct SceneStreamPair { f32 first, second; } SceneStreamPair;
extern struct SceneStreamPair g_cameraVolumeMaxYzPair;
#endif
