#ifndef AI_PLAYER_SCALED_UPDATETARGETPITCH_H
#define AI_PLAYER_SCALED_UPDATETARGETPITCH_H
struct AiController;
void Scaled_ClearAuxiliaryBehaviorState(struct AiController *controller);
void Scaled_ClearNodeQueue(struct AiController *controller);
struct CVector3_t *Scaled_GetControllerPosition(struct AiController *controller);
f32 Scaled_GetScaledAggression(struct AiController *controller);
int Scaled_IsBehaviorStateEight(struct AiController *object);
s32 Scaled_MatchesBehaviorStateFilter(struct AiController *controller);
#endif
