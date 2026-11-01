#ifndef RENDER_TIMED_SESSION_TRANSITIONS_H
#define RENDER_TIMED_SESSION_TRANSITIONS_H
#include "COMMON/INTEGERSTATEB0.H"
struct GameSession;
extern void SetN64_DrawRoundTimeoutSession(struct GameSession *session);
extern void SetN64_AdvanceToModeFour(struct GameSession *value);
extern void SetN64_InitializeMode2(void);
extern void SetN64_OnMode5DrawComplete(s32 session);
extern void SetN64_AdvanceToModeFive(struct GameSession *session);
extern void SetN64_DrawIntroBackdrop(void);
extern s32 SetN64_CheckTimedSessionTransition(struct TimedSessionTransitionView *session, f32 duration, s32 eight, s32 inputTargetMode);
extern void Scene_ResetTransitionViewport(void);
extern void SetN64_DrawSessionWithAttractTimeout(void *session);
#endif
