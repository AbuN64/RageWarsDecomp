#ifndef COMMON_LIGHT_VOLUME_AND_TRIGGER_VIEWS_H
#define COMMON_LIGHT_VOLUME_AND_TRIGGER_VIEWS_H
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"

struct WorldSectionResourceView;
typedef struct WorldSectionResourceView WorldSectionResourceView;

struct WorldSectionCountView;

struct WorldSectionCountView;
typedef struct WorldSectionCountView WorldSectionCountView;

struct SceneLightVolume;
struct SceneLightVolume {
    f32 falloff;
    f32 value;
    CVector3 direction; /* 0x08 */
    CVector3 axis; /* 0x14 */
    f32 inverse[16]; /* 0x20: world to volume, Graphu64_InvertAffineMatrix(inverse, transform) */
    f32 transform[16]; /* 0x60: volume to world */
    Box bounds; /* 0xA0: Region_ComputePointBounds_LightVolumeAndTriggerViews over the 8 corners */
    u8 flagB8;
    u8 flagB9;
    u8 animatedLight; /* 0xBA: Link_GetLightAnimationOffset */
    u8 shape; /* 0xBB */
    u8 animationSeed; /* 0xBC */
    u8 reservedWord; /* 0xBD: Lighting_DecodeBoxTransform */
};
/* A world sector's light volumes: section 2 of its model pack. */
typedef struct LightVolumeList {
    s32 stride;
    s32 count;
    struct SceneLightVolume volumes[1];
} LightVolumeList;

struct VertexColorMeshView;

struct TriggerSoundIdView;


struct WorldSectionResourceView;


struct TriggerTargetTransformView;
typedef struct TriggerTargetTransformView TriggerTargetTransformView;

struct Record14;
typedef struct Record14 Record14;

struct Record14;
struct Record14 {
    u32 coordinates[3];
    u16 lifetime;
    u8 flags;
    u8 kind;
    u8 state;
    u8 active;
    u8 mode;
    u8 reserved13;
};

struct TriggerActorTransformView;

struct TriggerActivationView;
typedef struct TriggerActivationView TriggerActivationView;

struct TriggerActorTransformView;
typedef struct TriggerActorTransformView TriggerActorTransformView;

struct TriggerSoundIdView;
typedef struct TriggerSoundIdView TriggerSoundIdView;


struct TriggerTargetTransformView;

struct TriggerActivationView;

struct Trigger;

struct VertexColorMeshView;
typedef struct VertexColorMeshView VertexColorMeshView;


struct LevelActor;




struct SceneLightVolume;
typedef struct SceneLightVolume SceneLightVolume;


struct SceneVisibilityGeometryView;
extern s32 Scene_QueueTriggerTimer(struct SceneVisibilityGeometryView *world, Record14 *trigger);
#endif
