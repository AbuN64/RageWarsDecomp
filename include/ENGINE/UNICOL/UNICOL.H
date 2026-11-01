#ifndef ENGINE_UNICOL_UNICOL_H
#define ENGINE_UNICOL_UNICOL_H
#include "COMMON/GROUP.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
extern s32 CCollision_SweepUniformExtent(char *actorStorage, CVector3 startPosition, CVector3 endPosition, CCollisionInfo2_t *sweepSurfaceSettings, f32 sweepExtent);
extern s32 CCollision_SweepWithWorkBuffer(char *actorStorage, char *motionWork, CVector3 first, CVector3 second, s32 motionSurface);
#endif
