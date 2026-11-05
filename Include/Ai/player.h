#ifndef AI_PLAYER_H
#define AI_PLAYER_H
#include "types.h"
#include "Common/vector.h"

struct Context;

extern void Player_SetPlayerResetPosition(void *actorObject, CVector3 *newResetPosition);
extern void Playerai_ResetPlayerControllers(struct Context *);
#endif

extern void Playerai_UpdateRoundEndWait(struct Player *player);
