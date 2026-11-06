#ifndef ENGINE_INSTANCE_STATINST_STATINST_H
#define ENGINE_INSTANCE_STATINST_STATINST_H
#include "Common/objb.h"
#include "Menu/scene_resource_preview_and_collision_views.h"
#include "Common/model_render.h"
#include "Render/material_color_and_fog_views.h"
#include "Common/propgeometry.h"
#include "World/static_model_instance_views.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/gameplay_camera.h"
#include "types.h"
#include "Scene/cache_requestresource.h"
#include "Scene/cache_allocateresourceat.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Engine/link.h"
#include "Engine/session.h"
#include "Statinst/statinst_acquiregeometry.h"
#include "Common/approachlocation.h"
#include "System/events_delivercontacteffect.h"
extern s32 g_gameFrameCounter;
extern f32 g_staticObjectFadeThresholdAndAlpha[];
extern void Geometry_QueueModelInstance(void **, void *, s32, void *, void *, s32);
/* The resource tag string every static placed object reads; each version names the same text differently. */
#if defined(VERSION_EU)
extern char s_staticInstanceResourceTag[];
#elif defined(VERSION_EU_X)
extern char s_staticModelResourceTag[];
#elif defined(VERSION_US)
extern char s_staticGeometryResourceTag[];
#elif defined(VERSION_US_REV1)
extern char s_staticPropResourceTag[];
#endif
struct GeometryVariantByteView {
    unsigned char padding_0[18];
    signed char propModelIndex;
};
struct OwnerStaticInstanceDrawGeometryVariant {
    char pad0[0x20];
    s32 resourceDescriptor;
    char pad24[4];
    char transform[168];
    s32 flagsD0;
    char padD4[6];
    u8 colorFrame;
};
struct ActorResourceStatusView {
    char pad0[0x18];
    char * geometryVariant;
    char pad18[0xD8 - 0x18 - sizeof(char*)];
    unsigned short statusFlags;
};
/* Shared object layout established by resource-binding consumers. */
struct ResourceBinding {
    u8 padding000[1];
    s8 variant; /* 0x01 */
    u8 padding002[0x1E];
    s32 *resource; /* 0x20: loaded resource descriptor */
    u8 padding024[4];
    u8 transform[140]; /* 0x28 */
    void *loadedResource; /* 0xB4 */
    u8 runtimeState[24]; /* 0xB8 */
    s32 registrationFlags; /* 0xD0 */
    u8 padding0D4[4];
    u16 status; /* 0xD8 */
    u8 colorFrame; /* 0xDA */
};
/* Actor resource fade selects the near/far value using its frame threshold. */
struct ResourceFadeDefinition {
    u8 reserved0[0xE];
    s8 nearValue; /* 0xE */
    s8 farValue; /* 0xF */
    u8 reserved10[0x14];
    u32 threshold; /* 0x24 */
};
struct LevelActor;
extern int Statinst_SelectDistanceVariant(void *object);
extern void Statinst_RefreshResourceUsage(void *resourceBinding);
extern s8 Statinst_SelectGameModeVariant(struct LevelActor *actor);
extern void Statinst_DrawForGameMode(void *owner, void *camera);
#endif
