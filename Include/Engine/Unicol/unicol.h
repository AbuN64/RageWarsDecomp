#ifndef ENGINE_UNICOL_UNICOL_H
#define ENGINE_UNICOL_UNICOL_H
#include "Ai/nav_symbols.h"
#include "Common/group.h"
#include "Common/runtime_declarations.h"
#include "Common/vector.h"
#include "Common/legacy_collision_actor.h"
#include "Common/ccollisioninfo2_t.h"
struct CCollisionInfo2_t;
extern s32 CCollision_SweepUniformExtent(char *actorStorage, CVector3 startPosition, CVector3 endPosition, struct CCollisionInfo2_t *sweepSurfaceSettings, f32 sweepExtent);
extern s32 CCollision_SweepWithWorkBuffer(char *actorStorage, char *motionWork, CVector3 first, CVector3 second, s32 motionSurface);
extern s32 g_collisionNoDetachSettingsAlternate;
extern float k_collisionUpNormalY_de;
extern void CCollision_SetUniformSweepExtent(void *actorMotion, f32 extent);
extern s32 CCollision_ApplyMotionResponse(void *actorStorage);
extern s32 CCollision_SweepPoint(char *actorStorage, CVector3 startPosition, CVector3 desired, s32 motionSettings);
#endif
