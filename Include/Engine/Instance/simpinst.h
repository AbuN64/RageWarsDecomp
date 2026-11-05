#ifndef ENGINE_INSTANCE_SIMPINST_H
#define ENGINE_INSTANCE_SIMPINST_H
#include "Common/propgeometry.h"
#include "World/static_model_instance_views.h"

extern f32 InstHdr_GetActorShadowRadius(Actor_u1 *);

extern void Simpinst_RefreshModelResourceUsage(struct ObjB *staticObject);
struct ObjB;
void Simpinst_RegisterModelVariantResources(struct ObjB *object, s32 camera);
extern void Simpinst_UpdateModelAndScale(void *staticObject);
struct ObjB; extern void Simple_DrawCachedModel(struct ObjB *obj);
struct CROMSimpleInstance; extern void Simple_InitSimpleInstance(struct ObjB *inst, struct CROMSimpleInstance *rec, s32 owner, char *segments);
#endif
