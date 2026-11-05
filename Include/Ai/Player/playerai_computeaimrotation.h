#ifndef AI_PLAYER_PLAYERAI_COMPUTEAIMROTATION_H
#define AI_PLAYER_PLAYERAI_COMPUTEAIMROTATION_H
#include "Common/vector4f.h"
struct TargetLockAttackerView;
struct TargetLockTargetView;
struct DraftAimPlayer;
struct CVector3_t;
CQuatern Playerai_ComputeAimRotation(struct DraftAimPlayer *player, struct DraftAimPlayer **target, struct CVector3_t *targetPosition);
#include "Common/multiplayeroptions.h"
extern s32 Playerai_CanLockTarget(struct TargetLockAttackerView *, struct TargetLockTargetView *);
#endif
