#include "Data/rest_source_records.h"
#ifndef ENGINE_LIGHTING_H
#define ENGINE_LIGHTING_H
#include "Ai/ai_shared_symbols.h"
#include "Common/effectrender.h"
#include "Ai/player_symbols.h"
#include "Common/vector.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Actors/vertex_light_and_actor_views.h"
struct LightVolumeRecord;
struct Vertices38;
struct FixedPointMatrix;
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
typedef struct SceneLightVolume SceneLightVolume;
/* A world sector's light volumes: section 2 of its model pack. */
typedef struct LightVolumeList {
    s32 stride;
    s32 count;
    struct SceneLightVolume volumes[1];
} LightVolumeList;
extern s32 Lighting_EvaluateLightVolume(struct SceneLightVolume *lightVolume, CVector3 worldPoint, CVector3 surfaceNormal, f32 *lightTransform, CVector3 *lightContribution, f32 *contributionWeight);
extern void Lighting_AccumulateVertexLighting(struct SceneLightVolume * *lights, s32 lightCount, struct Vertices38 *mesh, struct FixedPointMatrix *matrices, CVector3 *output, s32 multiple);
extern void Lighting_AccumulateDirectionalLighting(struct Vertices38 *data, struct FixedPointMatrix *matrices, CVector3 *output, s32 skin);
#if defined(VERSION_DE)
extern unsigned int g_actionInitBreakableMotionRecordTable_de[339];
#endif
/* A light volume as the level resource stores it (76 bytes, fixed-point fields). */
typedef struct LightVolumeRecord {
    s32 translation[3];
    s32 rotation[3];
    s32 scale[3];
    s32 falloff;
    s32 value;
    u8 pad2C[3];
    u8 shape;
    u8 pad30[7];
    u8 flagB8;
    u8 pad38[3];
    u8 animatedLight;
    u32 direction[3];
    u8 pad48[3];
    u8 reservedWord;
} LightVolumeRecord;
extern void Lighting_DecodeBoxTransform(struct SceneLightVolume *self, struct LightVolumeRecord *src);
extern s32 Lighting_EvaluateLocalVolume(struct SceneLightVolume *lightVolume, CVector3 localPosition, CVector3 *vectorComponents, f32 *intensity);
extern char g_actionEnterDispatchTriggerPairs_eu[];
extern char g_actionEnterDispatchTriggerPairs_eu_x[];
extern char g_actionMotionDispatchTriggerPairs_eu[];
extern char g_actionMotionDispatchTriggerPairs_eu_x[];
extern char g_actionMotionDispatchTriggerPairs_us[];
extern char g_damageDispatchTriggerPairs_eu[];
extern char g_damageDispatchTriggerPairs_eu_x[];
extern char g_damageDispatchTriggerPairs_us[];
extern char g_movingMotionDispatchTriggerPairs_de[];
extern char g_movingMotionDispatchTriggerPairs_eu[];
extern char g_movingMotionDispatchTriggerPairs_us[];
/* One end-state word closing an actor dispatch table (US rev1, Data/Overlays/Actor/constants.cpp). */
typedef struct ActorEndFragment {
    s32 endState;
} ActorEndFragment;
extern ActorEndFragment g_secondaryCollisionContextAnimIdEndFragment;
extern ActorEndFragment g_deviceRespondToActivationEndFragment;
extern ActorEndFragment g_spawnAIDispatchSpawnChoiceEndFragment;
extern ActorEndFragment g_movingAIGetDeviceHealthEndFragment;
extern ActorEndFragment g_defaultCollisionInfoNullEndFragment;
extern char g_spawnActorDispatchTriggerPairs_de[];
extern char g_spawnActorDispatchTriggerPairs_eu[];
extern char g_triggeredMotionDispatchTriggerPairs_de[];
extern char g_triggeredMotionDispatchTriggerPairs_eu[];
extern char g_triggeredMotionDispatchTriggerPairs_us[];
extern char g_turretDispatchTriggerPairs_de[];
extern char g_turretDispatchTriggerPairs_eu[];
extern char g_turretDispatchTriggerPairs_eu_x[];
extern char g_turretDispatchTriggerPairs_us[];
extern char s_litVerticesAllocationTag[13];
extern s32 g_vertexLightingMode;
extern CVector3 g_vertexLightAccumulation[];
extern char g_primaryCollisionContext[];
#endif
