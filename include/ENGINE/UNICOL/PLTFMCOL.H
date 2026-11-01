#ifndef ENGINE_UNICOL_PLTFMCOL_H
#define ENGINE_UNICOL_PLTFMCOL_H
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "ANIM/RAY180.H"

extern void CPlatformCollision_MarkBlocked(void *first, void *second);

extern void CPlatformCollision_ApplyMovement(void *platformMotion, void *levelActor);

extern void CPlatformCollision_BuildWorldBounds(char *obj, CVector3 *corners, char *floor, s32 attachment);
extern void CPlatformCollision_PushActorFromBox(ActorCPlatformCollisionPushActorFromBox *actor, PlatformCollisionEntryOwner *owner, RayCornerBounds *bounds, SurfaceHit *query, CollisionProbe *input);
extern void CPlatformCollision_PushActorFromCylinder(ActorCPlatformCollisionPushActorFromBox *actor, PlatformCollisionEntryOwner *owner, RayCornerBounds *bounds, SurfaceHit *query, CollisionProbe *input);
extern void CPlatformCollision_TraceShape(ActorCPlatformCollisionTraceShape *actor, PlatformCollisionEntryOwner *owner);
extern void CPlatformCollision_ProcessRiderMotion(ActorCPlatformCollisionProcessRiderMotion *actor, SourceBarrelUpdateActorController *input);
extern void CPlatformCollision_LiftActorToSurface(PlatformSavedCollisionQueryView *actor, void *owner, InputCPlatformCollisionLiftActorToSurface *input, SurfaceHit *query);
#endif
