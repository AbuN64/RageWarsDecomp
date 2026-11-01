#ifndef COMMON_SCENERECAT10C0_H
#define COMMON_SCENERECAT10C0_H
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include <ultra64.h>
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/SHAREDPLAYER.H"
struct LevelActor;
struct SceneActorUpdateLists;
typedef struct SceneActorUpdateLists SceneActorUpdateLists;


struct SceneModelIdTable;
typedef struct SceneModelIdTable SceneModelIdTable;

struct Shared_World;

struct Entity;
typedef struct Entity Entity;

struct SceneSceneDrawCachedOpaqueGeometry;
struct SceneSceneDrawCachedOpaqueGeometry {
    char pad0[0x88];
    void *model;
    char pad8C[0xF8 - 0x8C];
    s32 loaded;
    char padFC[0x120 - 0xFC];
    Gfx *lists[2];
};



struct ScenePackResourceView;
typedef struct ScenePackResourceView ScenePackResourceView;

struct SceneModelBankView;
typedef struct SceneModelBankView SceneModelBankView;

struct ObjectSceneDrawCachedOpaqueGeometry;

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
struct SceneSwitchObjectView;
struct SceneSwitchObjectView {
    char pad0[0x18];
    struct SceneSwitchDescriptor *descriptor;
    char pad1C[0x2E8 - 0x1C];
};

struct SceneSwitchObjectView;
typedef struct SceneSwitchObjectView SceneSwitchObjectView;

struct SceneSwitchObjectView;
struct SceneLevelSwitchCollectionView;



struct Entity;



struct GlobalMode;

struct ObjectSceneDrawCachedOpaqueGeometry;
typedef struct ObjectSceneDrawCachedOpaqueGeometry ObjectSceneDrawCachedOpaqueGeometry;

struct ScenePackResourceView;


struct SceneActorUpdateLists;
struct SceneActorUpdateLists {
    char pad0[0xC50];
    struct LevelActor *objects[128];
    s32 count;
    char padE54[0x10BC - 0xE54];
    s32 lateCount;
    struct LevelActor *late[64];
};

struct SceneModelBankView;
struct SceneModelIdTable;
struct SceneModelBankView {
    char pad0[0x24];
    s32 directoryBank;
    char pad28[0x2C];
    s32 modelDirectory;
    char pad58[0x3C];
    struct SceneModelIdTable *table;
};


struct SceneLevelSwitchCollectionView;
typedef struct SceneLevelSwitchCollectionView SceneLevelSwitchCollectionView;




struct GlobalMode;
typedef struct GlobalMode GlobalMode;


struct ObjectSceneChangeInstanceModel;
#include "COMMON/MODEL_INSTANCE.H"

struct SceneSceneDrawCachedOpaqueGeometry;
typedef struct SceneSceneDrawCachedOpaqueGeometry SceneSceneDrawCachedOpaqueGeometry;


struct ObjectSceneChangeInstanceModel;
typedef struct ObjectSceneChangeInstanceModel ObjectSceneChangeInstanceModel;


typedef struct Bounds2D37 { f32 minX,minZ,maxX,maxZ; } Bounds2D37;

typedef struct DraftStreamCell { f32 minX, minZ, maxX, maxZ; s32 occupied; } DraftStreamCell;
typedef struct DraftStreamData { s32 count; } DraftStreamData;
typedef struct DraftStreamHandle { DraftStreamData *data; } DraftStreamHandle;
typedef struct DraftStreamEntry {
    DraftStreamHandle *resource; DraftStreamCell *cell; s16 x, z;
} DraftStreamEntry;
typedef struct DraftStreamViewer {
    s32 pad0; struct DraftStreamViewer *next;
    char pad8[0x120]; CVector3 position;
    char pad134[0x234]; CVector3 minimum, maximum;
} DraftStreamViewer;
typedef struct DraftStreamPair { f32 first, second; } DraftStreamPair;
extern DraftStreamPair g_cameraVolumeMaxYzPair;
struct ResourceBitGrid;
extern void Visdata_DecodeRegionGrid(struct ResourceBitGrid *, s32, s32, DraftStreamData *, CVector3 *);
#endif
