#ifndef AI_DEVICES_PLAYERMATRIX_PLAYERMATRIX_H
#define AI_DEVICES_PLAYERMATRIX_PLAYERMATRIX_H
extern void PlayerMatrix_UpdateOpeningDelay(void *object, void *state);
extern void PlayerMatrix_RequestOpen(struct Shared_Actor *actor, int *motionFlags);
extern void PlayerMatrix_RequestClose(struct Shared_Actor *actor, int *motionFlags);
extern void PlayerMatrix_ActivateMotion(struct Shared_Actor *actor);
extern void PlayerMatrix_DeactivateMotion(struct Shared_Actor *actor);
#endif
