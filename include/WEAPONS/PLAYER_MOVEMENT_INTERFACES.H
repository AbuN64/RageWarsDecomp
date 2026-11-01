#ifndef WEAPONS_PLAYER_MOVEMENT_INTERFACES_H
#define WEAPONS_PLAYER_MOVEMENT_INTERFACES_H
#include "COMMON/ACTOR_HEADER.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"

/* Published implementations use these concrete actor and tuning records. */
void Player_EaseOwnerHeightEffect(struct EffectOwnerObject *object);
void Player_UpdateGroundThrustAndBoost(SharedPlayer *player,
                     PlayerBodyPositionYawView *body, SharedMovement *tuning);
s32 Player_SetPlayerState(SharedPlayer *player, void *body, s32 state);
/* Turn-rate limits shared by player movement. */
extern const f32 g_playerClimbTurnMaximum;
extern const f32 g_playerClimbTurnMinimum;
#endif
