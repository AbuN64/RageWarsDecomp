#ifndef ENGINE_UNICOL_INSTCOL_H
#define ENGINE_UNICOL_INSTCOL_H
#include "COMMON/RENDERSORTRECORD.H"
#include "COMMON/BOX_CONTACT.H"

extern int CRenderSortRecord_CompareDepth(RenderSortRecord *left, RenderSortRecord *right);

extern void CCollision_ExpandBoxCoordinates(float *s, float *d);

extern void CRenderSortRecord_Swap(RenderSortRecord *left, RenderSortRecord *right);

extern s32 CInstanceCollision_TestBoxFaces(BoxContactRay *ray, void *unused, BoxContactActor *actor, CVector3 *origin, CVector3 *vertices, BoxContactTransform *transform, s32 index);

extern void CInstanceCollision_TraceActorBounds(BoxContactRay *ray, BoxContactActor *actor, CVector3 *origin, Box *bounds);

void Player_AddImpulse(void *, f32);
#endif
