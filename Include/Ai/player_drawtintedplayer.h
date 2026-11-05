#ifndef AI_PLAYER_DRAWTINTEDPLAYER_H
#define AI_PLAYER_DRAWTINTEDPLAYER_H
#include "Common/frag_tag_scores.h"
#include "Common/level_actor.h"
#include "Common/shared_gameslot.h"

struct Draw;
struct Inventory;
struct LevelActor;
struct Receiver;
extern void Player_TransferRandomInventoryItems(struct Inventory *inventory, struct Receiver *receiver);
extern void Player_DrawTintedPlayer(struct LevelActor *actor, s32 animationContext, struct Draw *draw);
extern void Playerai_UpdateDamageTimers(void *actor);
#endif
