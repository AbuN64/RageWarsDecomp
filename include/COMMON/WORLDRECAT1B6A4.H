#ifndef COMMON_WORLDRECAT1B6A4_H
#define COMMON_WORLDRECAT1B6A4_H
struct LevelBitRecord;
#ifndef WORLD_SCENE_LIST_AND_LOOKUP_DECLARATIONS_H
#define WORLD_SCENE_LIST_AND_LOOKUP_DECLARATIONS_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"




extern void Scene_ClearActorLinksById(void *scene, s32 linkId);




struct ObjectSceneRegisterActorInSceneLists;
typedef struct ObjectSceneRegisterActorInSceneLists ObjectSceneRegisterActorInSceneLists;

struct SceneActorLinkGroupView;
struct SceneActorLinkGroupView {
    char pad[0xC50];
    ActorLinkedControllerView *actors[128];
    int count;
};

struct SceneActorLinkGroupView;
typedef struct SceneActorLinkGroupView SceneActorLinkGroupView;

extern ActorLinkedControllerView *Scene_ResolveActorLinkGroup(SceneActorLinkGroupView *obj, int id);


struct ScenePlayerObjectListView;
struct ScenePlayerObjectListView {
    char pad0[0x1B664];
    Player *objects[16];
    s32 count;
};

struct SceneTriggerCounterOwnerView;
typedef struct SceneTriggerCounterOwnerView SceneTriggerCounterOwnerView;

extern s32 Scene_TestLevelRecordStateBit(void *world, struct LevelBitRecord *levelBitRecord);


struct World;

struct SceneCounterPairView;
typedef struct SceneCounterPairView SceneCounterPairView;




extern int g_vertexLightingMode;






struct SceneTypeFourteenActorListView;
typedef struct SceneTypeFourteenActorListView SceneTypeFourteenActorListView;

struct SceneNearestActorView;
typedef struct SceneNearestActorView SceneNearestActorView;

struct SceneNearestActorView;
struct SceneNearestActorView {
    u8 pad0[0x8];
    f32 x;
    f32 y;
    f32 z;
    u8 pad14[0x4];
    s32 *kind;
    u8 pad1C[0xC8];
    u16 team;
    u8 padE6[0x8E];
    s32 active;
    u8 pad178[0x2C];
    s8 state; /* 0x1A4 */
    u8 pad1A5[0x2E8 - 0x1A5];
};

struct WorldSceneFindNearestMatchingActor;
typedef struct WorldSceneFindNearestMatchingActor WorldSceneFindNearestMatchingActor;

struct SceneNearestActorView;
struct WorldSceneFindNearestMatchingActor;
struct WorldSceneFindNearestMatchingActor {
    u8 pad0[0x138];
    struct SceneNearestActorView *objects;
    u8 pad13C[0x4];
    s32 count;
};

extern SceneNearestActorView *Scene_FindNearestMatchingActor(WorldSceneFindNearestMatchingActor *world, SceneNearestActorView *self, s32 team, s32 kind, s32 activeOnly);

struct SceneDefinitionActorView;
struct SceneDefinitionActorView {
    char pad[0x18];
    MenuActorInputView *def;
};

struct SceneDefinitionActorView;
typedef struct SceneDefinitionActorView SceneDefinitionActorView;

struct SceneTypeFourteenActorListView;
struct SceneTypeFourteenActorListView {
    char pad[0x1B664];
    SceneDefinitionActorView *list[16];
    s32 count;
};

extern SceneDefinitionActorView *Scene_FindTypeFourteenActorByDefinitionId(SceneTypeFourteenActorListView *world, s32 id);

struct SceneCounterPairView;
struct SceneCounterPairView {
    unsigned char padding_0[32];
    s32 packBankOffset;
    unsigned char padding_24[44];
    s32 packDirectory;
};




struct ScenePositionEntry;
struct ScenePositionEntry {
    char pad[8];
    f32 x;
    f32 y;
    f32 z;
};

struct ScenePositionEntry;
struct SceneListedEntryOwnerView;
struct SceneListedEntryOwnerView {
    char pad[0x1024];
    struct ScenePositionEntry *entries[32];
    s32 count;
};

struct ScenePositionEntry;
struct SceneListedEntryOwnerView;
extern struct ScenePositionEntry *Scene_FindNearestListedEntry(struct SceneListedEntryOwnerView *owner, struct ScenePositionEntry *pos);




struct World;

extern SceneDefinitionActorView *Scene_FindSwitchByDefinitionId(World *world, s32 id);



struct ObjectSceneRegisterActorInSceneLists;
struct MemoryUsageStats;
struct ObjectSceneRegisterActorInSceneLists {
    char pad0[0x18];
    struct MemoryUsageStats *descriptor;
    char pad1C[0xE4 - 0x1C];
    u16 model;
    char padE6[0x100 - 0xE6];
    s32 flags;
    char pad104[0x23E - 0x104];
    signed char slot;
};



struct SceneActorCategoryListsView;
struct SceneActorCategoryListsView {
    char pad0[0x144];
    ObjectSceneRegisterActorInSceneLists *listA[512];
    s32 countA;
    ObjectSceneRegisterActorInSceneLists *listB[128];
    s32 countB;
    char padB4C[0xC50 - 0xB4C];
    ObjectSceneRegisterActorInSceneLists *all[128];
    s32 countAll;
    ObjectSceneRegisterActorInSceneLists *type1[64];
    s32 countType1;
    s32 padF58;
    ObjectSceneRegisterActorInSceneLists *flagged[32];
    s32 countFlagged;
    ObjectSceneRegisterActorInSceneLists *type5[16];
    s32 countType5;
    ObjectSceneRegisterActorInSceneLists *model64F[32];
    s32 count64F;
    ObjectSceneRegisterActorInSceneLists *model64D[4];
    s32 count64D;
};




struct SceneTriggerCounterOwnerView;
struct SceneTriggerCounterOwnerView {
    u8 pad0[0x80];
    void *resource;
    u8 pad84[0x2C];
    Table *list;
};

extern s32 Scene_GetTriggerCounterById(SceneTriggerCounterOwnerView *counterOwner, s32 counterId);


struct SceneActorCategoryListsView;
typedef struct SceneActorCategoryListsView SceneActorCategoryListsView;





struct ScenePlayerObjectListView;
typedef struct ScenePlayerObjectListView ScenePlayerObjectListView;

extern Player *Scene_FindNearestObjectToFirstPlayer(ScenePlayerObjectListView *world);












/* Shared object layout established by level-bits consumers. */
struct LevelBitRecord {
    u8 padding000[0x19E];
    u16 bitIndex; /* 0x19E */
};

#endif
#endif
