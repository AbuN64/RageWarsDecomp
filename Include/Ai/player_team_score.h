#ifndef AI_PLAYER_TEAM_SCORE_H
#define AI_PLAYER_TEAM_SCORE_H
struct TargetSelectionObj;
void Playerai_UpdateTeamScore(struct TargetSelectionObj *a, struct TargetSelectionObj *b, s32 mode);
extern void Playerai_InitializeActorModelEffect(void *effectPlayerState, void *sourceActor);
extern void Playerai_EnterMovingSequenceState(void *player, void *body);
#endif
