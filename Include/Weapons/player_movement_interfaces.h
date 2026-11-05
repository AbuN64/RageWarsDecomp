#ifndef WEAPONS_PLAYER_MOVEMENT_INTERFACES_H
#define WEAPONS_PLAYER_MOVEMENT_INTERFACES_H
#include "Common/actor_header.h"
#include "Common/multiplayeroptions.h"
#include "Common/runtime_declarations.h"
#include "Player_updateplayercamera/player_updateplayercamera.h"

struct SharedPlayer;
/* Published implementations use these concrete actor and tuning records. */
void Player_EaseOwnerHeightEffect(struct EffectOwnerObject *object);

s32 Player_SetPlayerState(struct SharedPlayer *player, void *body, s32 state);
/* Turn-rate limits shared by player movement. */
extern const f32 g_playerClimbTurnMaximum;
extern const f32 g_playerClimbTurnMinimum;
#endif
