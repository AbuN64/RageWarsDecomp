#ifndef INSTHDR_INSTHDR_GETACTORSHADOWRADIUS_H
#define INSTHDR_INSTHDR_GETACTORSHADOWRADIUS_H
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/PROBE.H"
extern const unsigned int k_InsthdrGetactorshadowradiusTrailingBytes[1];
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
extern int InstHdr_IsDefinitionKindOne(LevelActor *actor);
extern int InstHdr_UsesDefaultDefinitionHandling(LevelActor *source);
#endif
