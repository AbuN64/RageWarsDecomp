#ifndef WORLD_BARREL_SPAWNACTOREFFECT_DATA_H
#define WORLD_BARREL_SPAWNACTOREFFECT_DATA_H
#include "COMMON/PROPGEOMETRY.H"
#include "WORLD/STATIC_MODEL_INSTANCE_VIEWS.H"

extern void Simpinst_UpdateScaleTransition(struct ObjB *staticObject);
extern void Simpinst_UpdateAnimationFrameDelta(struct ObjB *staticObject);
extern void Simpinst_ClearCachedResource(void *staticObject);
extern void Simpinst_BuildObjectTransform(void *staticObject);
extern s32 Simpinst_SelectModelVariant(ObjB *staticObject);
#endif
