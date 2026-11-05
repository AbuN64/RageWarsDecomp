#ifndef WORLD_BARREL_SPAWNACTOREFFECT_DATA_H
#define WORLD_BARREL_SPAWNACTOREFFECT_DATA_H
#include "Engine/scene.h"
#include "Engine/graphics_math.h"
#include "Common/vector4f.h"
#include "Common/propgeometry.h"
#include "World/static_model_instance_views.h"

extern void Simpinst_UpdateScaleTransition(struct ObjB *staticObject);
extern void Simpinst_UpdateAnimationFrameDelta(struct ObjB *staticObject);
extern void Simpinst_ClearCachedResource(void *staticObject);
extern void Simpinst_BuildObjectTransform(void *staticObject);
extern s32 Simpinst_SelectModelVariant(struct ObjB *staticObject);
CQuatern Simpinst_BuildGroundRotation(void *actor);
#endif
