#ifndef AI_PLAYER_PLAYER_UPDATEPLAYEREFFECTLIGHTS_H
#define AI_PLAYER_PLAYER_UPDATEPLAYEREFFECTLIGHTS_H
#include "Common/aiprofile.h"
struct SharedPlayer;
void Playerai_DrawAimHud(struct SharedPlayer *player, void *view);
extern void Player_UpdatePlayerEffectLights(struct Player *player, void *actor);

#endif
