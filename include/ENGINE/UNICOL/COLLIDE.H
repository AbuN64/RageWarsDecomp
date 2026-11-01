#ifndef ENGINE_UNICOL_COLLIDE_H
#define ENGINE_UNICOL_COLLIDE_H
#include "COMMON/CCOLLISIONSETUP_T.H"
#include "COMMON/OUTPUT.H"
#include "COMMON/DESCRIPTORRECAT29.H"

extern void CCollision_UpdateMaterialFlags(struct ActorMotion *motion, struct MotionContactResult *contact);

extern void CCollision_UpdateSurfaceResponseFlags(struct ActorMotion *motion, struct MotionContactResult *contact);

extern void CCollision_ClearContactNormal(void *contactStorage);

extern s32 CCollision_HasMatchingNormal(struct Input *input, PolygonCCollisionTestSegmentPolygon *polygon);

extern void CCollision_CopyPolygonNormal(void *contactStorage, void *polygonStorage);

extern void InstCol_ProcessEntityContacts(void *self);

extern void CCollision_Initialize(void);
extern void CCollision_ResetResult(void);
extern void CCollision_ApplySetupTable(CCollisionSetup_t *setupTable);
#endif
