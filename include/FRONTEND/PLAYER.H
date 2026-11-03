#ifndef FRONTEND_PLAYER_H
#define FRONTEND_PLAYER_H
#include "TYPES.H"
extern f32 g_fourPlayerBadgeDepth;
extern u16 g_fourPlayerResultsWidgetIds[];
extern f32 g_fourPlayerBadgeBaseY;
void Nav_ResetPlayerState(s32 *state);
struct AiController;
void Nav_UpdateTargetSteering(struct AiController *controller);
#endif
