#ifndef AI_PLAYER_SCALED_UPDATETARGETPITCH_H
#define AI_PLAYER_SCALED_UPDATETARGETPITCH_H
#include "Ai/nav_symbols.h"
struct AiBehaviourTable;
struct AiController;
struct Brain;
struct SharedPlayer;
struct AiController;
void Scaled_ClearAuxiliaryBehaviorState(struct AiController *controller);
void Scaled_ClearNodeQueue(struct AiController *controller);
struct CVector3_t *Scaled_GetControllerPosition(struct AiController *controller);
f32 Scaled_GetScaledAggression(struct AiController *controller);
int Scaled_IsSeekingPickup(struct AiController *object);
s32 Scaled_MatchesBehaviorStateFilter(struct AiController *controller);
#include "Common/brain.h"
#include "Common/ai_behaviour_types.h"
#include "Common/sharedplayer.h"
struct Player;
extern f32 Scaled_GetScaledAttackRange(struct AiController *controller);
extern s32 Scaled_HasLineOfSight(struct Player **fromRef, struct Player *target);
extern void Scaled_UpdateTargetPitch(struct Brain *);
extern f32 Scaled_GetDifficultyEngagementAdjustment(struct AiController *controller);
extern f32 Scaled_UpdateDifficultyAimJitter(void *aiController);


extern void Scaled_SetPitchFromAngle(struct AiController *controller, float amount);
extern void Scaled_SetBehaviorTable(struct AiController *object, struct AiBehaviourTable *value);
extern void Scaled_HandlePlayerTimeout(struct SharedPlayer **brain);

#endif
