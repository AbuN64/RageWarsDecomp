#ifndef AI_PLAYER_PLAYER_RESETPLAYERFORROUND_H
#define AI_PLAYER_PLAYER_RESETPLAYERFORROUND_H
#include "types.h"

struct SharedPlayer;
void Player_InitActorHudState(struct SharedPlayer *actor);
struct RespawnPlayer;
void Player_ResetRespawnedPlayer(struct RespawnPlayer *player);
#endif
