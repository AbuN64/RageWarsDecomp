#ifndef RENDER_TIMED_SESSION_TRANSITIONS_H
#define RENDER_TIMED_SESSION_TRANSITIONS_H
#include "Common/frontend_clock_state.h"
struct GameSession;
extern void SetN64_DrawRoundTimeoutSession(struct GameSession *session);
extern void SetN64_AdvanceLoadingToSplashImage(struct GameSession *value);
extern void SetN64_InitializeIntroText(void);
extern void SetN64_OnOpeningCinemaDrawn(s32 session);
extern void SetN64_AdvanceIntroTextToOpeningCinema(struct GameSession *session);
extern void SetN64_DrawIntroBackdrop(void);
extern s32 SetN64_CheckTimedSessionTransition(struct TimedSessionTransitionView *session, f32 duration, s32 eight, s32 inputTargetMode);
extern void Scene_ResetTransitionViewport(void);
extern void SetN64_DrawSessionWithAttractTimeout(void *session);
#endif
