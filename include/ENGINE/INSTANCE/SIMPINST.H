#ifndef ENGINE_INSTANCE_SIMPINST_H
#define ENGINE_INSTANCE_SIMPINST_H
#include "COMMON/PROPGEOMETRY.H"
#include "WORLD/STATIC_MODEL_INSTANCE_VIEWS.H"

extern f32 InstHdr_GetActorShadowRadius(Actor_u1 *);

extern void Simpinst_RefreshModelResourceUsage(struct StaticObject *staticObject);
#endif
