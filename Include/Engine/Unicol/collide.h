#ifndef ENGINE_UNICOL_COLLIDE_H
#define ENGINE_UNICOL_COLLIDE_H
#include "Engine/Instance/gobjinst.h"
#include "Common/ccollisionsetup_t.h"
#include "Common/output.h"
#include "Common/sky_layers.h"

struct CCollisionSetup_t;
extern void CCollision_UpdateMaterialFlags(struct ActorMotion *motion, struct MotionContactResult *contact);

extern void CCollision_UpdateSurfaceResponseFlags(struct ActorMotion *motion, struct MotionContactResult *contact);

extern void CCollision_ClearContactNormal(void *contactStorage);

extern s32 CCollision_HasMatchingNormal(struct Input *input, PolygonCCollisionTestSegmentPolygon *polygon);

extern void CCollision_CopyPolygonNormal(void *contactStorage, void *polygonStorage);

struct HitSelf; extern void InstCol_ProcessEntityContacts(struct HitSelf *self);

extern void CCollision_Initialize(void);
extern void CCollision_ResetResult(void);
extern void CCollision_ApplySetupTable(struct CCollisionSetup_t *setupTable);
extern struct CCollisionSetup_t g_collisionSetupTableResource[];
#endif
