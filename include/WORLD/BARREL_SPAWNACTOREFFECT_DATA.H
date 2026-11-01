#ifndef WORLD_BARREL_SPAWNACTOREFFECT_DATA_H
#define WORLD_BARREL_SPAWNACTOREFFECT_DATA_H
#include "COMMON/PROPGEOMETRY.H"
#include "WORLD/STATIC_MODEL_INSTANCE_VIEWS.H"

extern void Simpinst_UpdateScaleTransition(struct StaticObject *staticObject);
extern void Simpinst_UpdateAnimationFrameDelta(struct StaticObject *staticObject);
extern void Simpinst_ClearCachedResource(void *staticObject);
extern void Simpinst_BuildObjectTransform(void *staticObject);
extern s32 Simpinst_SelectModelVariant(StaticObject *staticObject);
#endif
