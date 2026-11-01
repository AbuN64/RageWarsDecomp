#ifndef AI_PLAYER_DRAWTINTEDPLAYER_H
#define AI_PLAYER_DRAWTINTEDPLAYER_H
#include "COMMON/OBJRECV5.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/SHARED_GAMESLOT.H"

extern void Player_TransferRandomInventoryItems(Inventory *inventory, Receiver *receiver);
extern void Player_DrawTintedPlayer(LevelActor *actor, s32 animationContext, Draw *draw);
extern void Playerai_UpdateDamageTimers(void *actor);
#endif
