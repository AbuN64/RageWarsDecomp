#ifndef ENGINE_INSTANCE_STATINST_STATINST_DRAWGEOMETRYVARIANT_H
#define ENGINE_INSTANCE_STATINST_STATINST_DRAWGEOMETRYVARIANT_H
#include "Common/objb.h"
#include "Common/model_render.h"
#include "Common/shared_gameslot.h"
#include "Render/material_color_and_fog_views.h"
#include "Common/manager.h"
#include "Common/aiprofile.h"
#include "Common/level_actor.h"
#include "Common/level_spawn.h"
#include "Common/propgeometry.h"
#include "types.h"
#include "Actors/lighting_buildlitmodel.h"
#include "Render/setn64_getpacksection.h"
#include "Engine/link.h"
#include "Geometry/geometry_drawblendparts.h"
#include "Statinst/statinst_acquiregeometry.h"
#include "Common/runtime_declarations.h"
#include "Scene/cache_allocateresourceat.h"
extern s32 g_gameFrameCounter;
extern void Cache_TouchResourceByKey(s32 cache, s32 resourceKey);
extern s32 *Geometry_CollectMaterialResources(void **modelResource, s32 variation, s32 *resourcesOut);
extern void Cache_MarkResourceInUse(s32, struct CacheResourceNode *);
extern void Geometry_QueueModelInstance(void **, void *, s32, void *, void *, s32);
#endif
