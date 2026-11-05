#ifndef INSTHDR_INSTHDR_GETACTORSHADOWRADIUS_H
#define INSTHDR_INSTHDR_GETACTORSHADOWRADIUS_H
#include "Common/shared_menureply.h"
#include "Engine/scene.h"
#include "Common/level_actor.h"
#include "Common/probe.h"
#include "Common/sharedplayer.h"
struct LevelActor;
extern f32 InstHdr_GetActorShadowRadius(Actor_u1 *actor);
extern f32 InstHdr_GetInactiveActorHeight(Actor_u1 *actor);
extern float InstHdr_GetTypeOneResourceValue50(void *object);
extern void InstHdr_ProjectPositionToActorGround(void *actor, void *, void *);
extern int InstHdr_GetTypeOneItemValue(void *actorStorage);
extern f32 InstHdr_GetActorTargetHeight(u8 *);
extern int InstHdr_GetActorMotionFlags(void *levelActor);
extern float InstHdr_ReturnUnusedActorFloat(void);
extern f32 InstHdr_GetActorTriangleTopOffset(void *);
extern f32 InstHdr_GetActorTriangleBottomOffset(void *);
extern s32 InstHdr_HasTypeOneFlagOne(void *actorStorage);
extern int InstHdr_ReturnUnusedActorStatus(void);
extern int InstHdr_ReturnUnusedActorStatusAlternate(void);
extern int InstHdr_ReturnUnusedActorQuery(void);
extern s32 InstHdr_CanActorCastShadow(void *);
extern s32 InstHdr_IsActorControllerActive(char *actor);
extern int InstHdr_IsDefinitionKindOne(struct LevelActor *actor);
extern int InstHdr_UsesDefaultDefinitionHandling(struct LevelActor *source);
int InstHdr_FindActorModelEntry(void *actorStorage);
struct MeasureObject;
f32 InstHdr_GetActorReach(struct MeasureObject *object);
void InstHdr_GetActorTargetOffset(u8 *player, void *vector);
int InstHdr_GetActorType(void *prop);
struct InstanceItemValueView;
void *InstHdr_GetEnabledItemValue(struct InstanceItemValueView *item);
struct ActorSurfaceKeyView;
f32 InstHdr_GetModelRecordValue20(struct ActorSurfaceKeyView *object);
struct Shared_CollisionActor;
float InstHdr_GetShadowGroundHeight(struct Shared_CollisionActor *object, s32 mode);

unsigned int InstHdr_UsesGroundRotation(char *object);
#endif
