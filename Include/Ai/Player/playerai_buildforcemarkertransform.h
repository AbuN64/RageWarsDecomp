#ifndef AI_PLAYER_PLAYERAI_BUILDFORCEMARKERTRANSFORM_H
#define AI_PLAYER_PLAYERAI_BUILDFORCEMARKERTRANSFORM_H
void Playerai_ClearDamageTimers(s32 player);
struct PlayerEffectTimerSet;
void Playerai_StartDamageTimer(struct PlayerEffectTimerSet *obj, float target, float rate, int kind, int tag);
#endif
