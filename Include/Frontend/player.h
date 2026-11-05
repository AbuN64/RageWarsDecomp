#ifndef FRONTEND_PLAYER_H
#define FRONTEND_PLAYER_H
#include "types.h"
extern f32 g_fourPlayerBadgeDepth;
extern u16 g_fourPlayerResultsWidgetIds[];
extern f32 g_fourPlayerBadgeBaseY;
void Nav_ResetPlayerState(s32 *state);
struct AiController;
void Nav_UpdateTargetSteering(struct AiController *controller);
extern s32 Player_CreateFourPlayerResults(void *window);
extern s32 Player_DrawFourPlayerResults(void *window, void *item, s32 event);
extern s32 Player_StartFourPlayerResults(void);
extern s32 Player_UpdateFourPlayerResults(void);
#endif
