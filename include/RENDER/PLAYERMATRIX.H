#ifndef RENDER_PLAYERMATRIX_H
#define RENDER_PLAYERMATRIX_H
#include "COMMON/REC.H"
#include "WORLD/INTEGERSTATE170.H"

extern void Device_BuildPlayerMatrix(void *object, void *state);
extern void PlayerMatrix_ClearUnsupportedOpenFlag(void *actor, s32 *stateFlags);

extern void PlayerMatrix_EnableEventActor(void *event);
extern void PlayerMatrix_EnableCollisionFlags(void *object);
extern void PlayerMatrix_ClearUnsupportedCloseFlag(void *actor, s32 *stateFlags);
extern void PlayerMatrix_DisableEventActor(void *event);
extern void PlayerMatrix_MarkCloseRequested(char *object, unsigned int *flags);
extern void PlayerMatrix_MarkOpenAndResetTimer(struct LevelActor *actor, struct ActorMotionState *motionState);
extern int PlayerMatrix_ClearCollisionBit(void * player);
#endif
