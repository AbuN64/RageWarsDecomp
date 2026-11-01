#ifndef COMMON_COLORENTRY_H
#define COMMON_COLORENTRY_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
extern float g_transitionAlphaUnsignedConversionBase;


struct StateSceneUpdateStaticEventInstances;
typedef struct StateSceneUpdateStaticEventInstances StateSceneUpdateStaticEventInstances;

struct StateSceneUpdateStaticEventInstances;
struct StateSceneUpdateStaticEventInstances {
    char pad[0xB4C];
    s32 values[64];
    s32 trackedInstanceCount;
    char padc50[0x1A6CC];
    f32 eventPhase;
};



struct ColorEntry;
struct ColorEntry {
    f32 value;
    u8 red;
    u8 green;
    u8 blue;
    u8 pad;
};





struct ObjectCSceneStartEventClips;
struct StridedTable;

struct ObjectCSceneStartEventClips;
typedef struct ObjectCSceneStartEventClips ObjectCSceneStartEventClips;

struct Container;
typedef struct Container Container;

struct SceneActorMatchRecord;
typedef struct SceneActorMatchRecord SceneActorMatchRecord;

struct SceneActorMatchDescriptor;
struct SceneActorMatchDescriptor {
    s32 kindId;
    char pad4[8];
    s16 teamId;
};
struct SceneActorMatchRecord;
struct SceneActorMatchDescriptor;
struct SceneActorMatchRecord {
    char pad0[0x18];
    struct SceneActorMatchDescriptor *kindDescriptor;
    char pad1C[0xC8];
    u16 modelId;
    char padE6[0x2E8 - 0xE6];
};

struct Container;
struct SceneActorMatchRecord;



struct OwnerSceneUnlockActiveSectionResources;
typedef struct OwnerSceneUnlockActiveSectionResources OwnerSceneUnlockActiveSectionResources;







struct ColorEntry;
typedef struct ColorEntry ColorEntry;




struct ScenePackSectionTableView;

struct SceneActiveResourceCountView;
typedef struct SceneActiveResourceCountView SceneActiveResourceCountView;

struct SceneActiveResourceCountView;






struct SceneNestedPackSectionTableView;


struct ScenePackSectionTableView;
typedef struct ScenePackSectionTableView ScenePackSectionTableView;



extern float g_nearestRouteFrameAbsentIndex;

struct OwnerSceneUnlockActiveSectionResources;



struct SceneNestedPackSectionTableView;
typedef struct SceneNestedPackSectionTableView SceneNestedPackSectionTableView;


/* Clip section 1 has a stride/count header and 0x38-byte pose records.
 * Position is used to select the nearest frame; the remaining pose data is
 * consumed by the animation routines reached through Scene_GetPlatformRoutePoint. */
typedef struct AnimationPoseFrame {
    CVector3 position;
    u8 poseData[0x38 - sizeof(CVector3)];
} AnimationPoseFrame;

#endif
