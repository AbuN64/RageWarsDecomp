#ifndef ENGINE_UNICOL_INSTCOL_H
#define ENGINE_UNICOL_INSTCOL_H
#include "Common/rendersortrecord.h"
#include "Common/box_contact.h"

struct Query {
    f32 radius;
    f32 bottom;
    f32 top;
    f32 top1;
    f32 bottom1;
    f32 top2;
    f32 bottom2;
    f32 minX;
    f32 minZ;
    f32 maxX;
    f32 maxZ;
    s32 flag;
};


struct BoxContactActor;
struct BoxContactRay;
struct BoxContactTransform;
struct RenderSortRecord;
struct Box;
extern int CRenderSortRecord_CompareDepth(struct RenderSortRecord *left, struct RenderSortRecord *right);

extern void CCollision_ExpandBoxCoordinates(float *s, float *d);

extern void CRenderSortRecord_Swap(struct RenderSortRecord *left, struct RenderSortRecord *right);

extern s32 CInstanceCollision_TestBoxFaces(struct BoxContactRay *ray, void *bounds, struct BoxContactActor *actor, CVector3 *origin, CVector3 *vertices, struct BoxContactTransform *transform, s32 index);

extern void CInstanceCollision_TraceActorBounds(struct BoxContactRay *ray, struct BoxContactActor *actor, CVector3 *origin, struct Box *bounds);

void Player_AddImpulse(void *, f32);
#endif
