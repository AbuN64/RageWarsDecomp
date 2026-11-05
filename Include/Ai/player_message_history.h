#ifndef AI_PLAYER_MESSAGE_HISTORY_H
#define AI_PLAYER_MESSAGE_HISTORY_H
void Playerai_PostMessageHistoryEntry(void *player, u8 *message, f32 size);
extern void Player_DrainReserveAndDamage(void *actor, f32 amount, void *damageSource);
#endif
