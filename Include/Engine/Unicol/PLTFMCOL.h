#ifndef ENGINE_UNICOL_PLTFMCOL_H
#define ENGINE_UNICOL_PLTFMCOL_H
#include "Engine/Unicol/Instcol/instcol.h"
#include "Engine/Unicol/Polycol/polycol_tracemeshtriangle.h"
#include "Ai/nav_symbols.h"
#include "Gobjinst/gameobject_getactorheight.h"
#include "Common/runtime_declarations.h"
#include "Anim/collision_ray.h"

struct Shape {
    s32 flags;
    s8 enabled;
};
typedef struct Shape Shape;


struct ActorCPlatformCollisionPushActorFromBox;
struct CollisionProbe;
struct InputCPlatformCollisionLiftActorToSurface;
struct PlatformSavedCollisionQueryView;
struct RayCornerBounds;
struct SurfaceHit;
extern void CPlatformCollision_MarkBlocked(void *first, void *second);

extern void CPlatformCollision_ApplyMovement(void *platformMotion, void *levelActor);

extern void CPlatformCollision_BuildWorldBounds(char *obj, CVector3 *corners, char *floor, s32 attachment);
extern void CPlatformCollision_PushActorFromBox(struct ActorCPlatformCollisionPushActorFromBox *actor, struct PlatformCollisionEntryOwner *owner, struct RayCornerBounds *bounds, struct SurfaceHit *query, struct CollisionProbe *input);
extern void CPlatformCollision_PushActorFromCylinder(struct ActorCPlatformCollisionPushActorFromBox *actor, struct PlatformCollisionEntryOwner *owner, struct RayCornerBounds *bounds, struct SurfaceHit *query, struct CollisionProbe *input);


extern void CPlatformCollision_LiftActorToSurface(struct PlatformSavedCollisionQueryView *actor, void *owner, struct InputCPlatformCollisionLiftActorToSurface *input, struct SurfaceHit *query);
struct ActorCPlatformCollisionProcessRiderMotion;
struct SourceBarrelUpdateActorController;
void CPlatformCollision_ProcessRiderMotion(struct ActorCPlatformCollisionProcessRiderMotion *actor, struct SourceBarrelUpdateActorController *input);
struct ActorCPlatformCollisionTraceShape;
struct PlatformCollisionEntryOwner;
void CPlatformCollision_TraceShape(struct ActorCPlatformCollisionTraceShape *actor, struct PlatformCollisionEntryOwner *owner);
extern f32 InstHdr_GetActorBaseOffset(void *);
extern s32 Unicol_SweepActorMotion(void *, CVector3, CVector3, struct CCollisionInfo2_t *, f32, f32, f32, f32);
extern void MatrixFromQuaternion(f32 *q, f32 *m);
#endif
