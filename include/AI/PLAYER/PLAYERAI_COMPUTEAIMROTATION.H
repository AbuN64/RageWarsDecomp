#ifndef AI_PLAYER_PLAYERAI_COMPUTEAIMROTATION_H
#define AI_PLAYER_PLAYERAI_COMPUTEAIMROTATION_H
struct DraftAimPlayer;
struct CVector3_t;
struct CQuatern_t Playerai_ComputeAimRotation(struct DraftAimPlayer *player, struct DraftAimPlayer **target, struct CVector3_t *targetPosition);
#endif
