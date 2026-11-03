#include "SYSTEM/ENGINE_DATA_SOURCE.H"
#include "include_asm.h"
#include "SETN64/SETN64_DRAWMODE4BACKDROP.H"
#ifdef VERSION_DE
#if defined(VERSION_US)

/* g_SchedHandlerspcompletionEncodedWordsBlock1.CPP */
/* ROM-grounded data: rodata/writable/800D299C */
EngineSchedulerState g_SchedHandlerspcompletionEncodedWordsBlock1 = {
    0.0f, 0.0f, 0.0f, 0.0f, 262144.0f, 1, 0, (void *)0x800E4C00,
    2048, 0, 0, 1, 1, 0, 0
};
#endif
#endif
#ifdef VERSION_EU
#if defined(VERSION_US)
EngineSchedulerState g_SchedHandlerspcompletionEncodedWordsBlock1 = {
    0.0f, 0.0f, 0.0f, 0.0f, 262144.0f, 1, 0, (void *)0x800F4C00,
    2048, 0, 0, 1, 1, 0, 0
};
#endif
#endif
#ifdef VERSION_EU_X
#if defined(VERSION_US)
EngineSchedulerState g_SchedHandlerspcompletionEncodedWordsBlock1 = {
    0.0f, 0.0f, 0.0f, 0.0f, 262144.0f, 1, 0, (void *)0x800EEC00,
    2048, 0, 0, 1, 1, 0, 0
};
#endif
#endif
#ifdef VERSION_US
#if defined(VERSION_US)
EngineSchedulerState g_SchedHandlerspcompletionEncodedWordsBlock1 = {
    0.0f, 0.0f, 0.0f, 0.0f, 262144.0f, 1, 0, (void *)0x800E2C00,
    2048, 0, 0, 1, 1, 0, 0
};
#endif
#endif
#ifdef VERSION_US_REV1
#if defined(VERSION_US)
EngineSchedulerState g_SchedHandlerspcompletionEncodedWordsBlock1 = {
    0.0f, 0.0f, 0.0f, 0.0f, 262144.0f, 1, 0, (void *)0x800E8C00,
    2048, 0, 0, 1, 1, 0, 0
};
#endif
#endif
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)

struct GameSession; extern void SetN64_AdvanceIntroForMemorySize(struct GameSession *session);
extern void SetN64_AdvanceToModeEight(struct GameSession *session);
extern void SetN64_AdvanceToModeFive(struct GameSession *session);
extern void SetN64_AdvanceToModeFour(struct GameSession *value);
extern void SetN64_ClearSessionPlayerPools(void *owner);
extern void SetN64_DrawCenteredIntroText(void *state);
extern void SetN64_DrawFullscreenBackdrop(void *unused);
extern void SetN64_DrawIntroBackdrop();
extern void SetN64_DrawMode10Session(void *session);
extern void SetN64_DrawMode11Session(void *session);
extern void SetN64_DrawMode12Session(void *session);
extern void SetN64_DrawMode15();
extern void SetN64_DrawMode16Credits(s32 session);
extern void SetN64_DrawMode17Credits(s32 session);
extern void SetN64_DrawMode18();
extern void SetN64_DrawMode19();
extern void SetN64_DrawMode4Backdrop();
extern void SetN64_DrawMode5Session(s32 session);
extern void SetN64_DrawMode6();
extern void SetN64_DrawMode8Session(struct GameSession *session);
extern void SetN64_DrawMode9Session(void *session);
extern void SetN64_DrawRoundTimeoutSession(struct GameSession *session);
extern void SetN64_DrawSessionWithRoundTimeout(struct GameSession *session);
extern void SetN64_DrawTransitionMode();
extern void SetN64_EnterPendingSessionMode(void *gameSession);
extern void SetN64_ExitSessionAndDisablePaks(void *session);
extern void SetN64_HandleMode10Input(s32 session);
extern void SetN64_HandleMode11Input(s32 session);
extern void SetN64_HandleMode12Input(s32 session);
extern void SetN64_HandleMode16CreditsInput(s32 session);
extern void SetN64_HandleMode17CreditsInput(s32 session);
extern void SetN64_HandleMode5Input(s32 session);
extern void SetN64_HandleMode7Transition(struct GameSession *session);
extern void SetN64_HandleMode9Input();
extern void SetN64_InitializeFrontendScreenState(struct GameSession *gameSession);
extern void SetN64_InitializeMode15();
extern void SetN64_InitializeMode16Credits(s32 sessionAddress);
extern void SetN64_InitializeMode17Credits(s32 sessionAddress);
extern void SetN64_InitializeMode18();
extern void SetN64_InitializeMode19();
extern void SetN64_InitializeMode2();
extern void SetN64_InitializeMode6();
extern void SetN64_InitializeMode8Scene();
extern void SetN64_InitializeTransitionMode();
extern void SetN64_ResetMode10Items(s32 sessionAddress);
extern void SetN64_ResetMode11Items(s32 sessionAddress);
extern void SetN64_ResetMode12Items(int sessionAddress);
extern void SetN64_ResetMode4Effects();
extern void SetN64_ResetMode5Items(s32 sessionAddress);
extern void SetN64_ResetMode9Items(s32 sessionAddress);
extern void SetN64_ResetSceneForIntro(void *owner);
struct GameSession; extern void SetN64_ResumeSelectedSession(struct GameSession *unused);
extern void SetN64_SetMode7AudioState();
struct TimedSessionTransitionView; extern void SetN64_SetupLoadingBackdropDe(struct TimedSessionTransitionView *state);
struct GameSession; extern void SetN64_StartRound(struct GameSession *session);
extern void SetN64_UpdateActiveSession();
extern void SetN64_UpdateMode15();
extern void SetN64_UpdateMode18();
extern void SetN64_UpdateMode19();
extern void SetN64_UpdateMode6();
extern void SetN64_UpdateMode8();
#endif
#if defined(VERSION_EU)
struct GameSession; extern void SetN64_AdvanceIntroForMemorySize(struct GameSession *session);
extern void SetN64_AdvanceToModeEight(struct GameSession *session);
extern void SetN64_AdvanceToModeFive(struct GameSession *session);
extern void SetN64_AdvanceToModeFour(struct GameSession *value);
extern void SetN64_ClearSessionPlayerPools(void *owner);
extern void SetN64_DrawCenteredIntroText(void *state);
extern void SetN64_DrawFullscreenBackdrop(void *unused);
extern void SetN64_DrawIntroBackdrop();
extern void SetN64_DrawMode10Session(void *session);
extern void SetN64_DrawMode11Session(void *session);
extern void SetN64_DrawMode12Session(void *session);
extern void SetN64_DrawMode15();
extern void SetN64_DrawMode16Credits(s32 session);
extern void SetN64_DrawMode17Credits(s32 session);
extern void SetN64_DrawMode18();
extern void SetN64_DrawMode19();
extern void SetN64_DrawMode4Backdrop();
extern void SetN64_DrawMode5Session(s32 session);
extern void SetN64_DrawMode6();
extern void SetN64_DrawMode8Session(struct GameSession *session);
extern void SetN64_DrawMode9Session(void *session);
extern void SetN64_DrawRoundTimeoutSession(struct GameSession *session);
extern void SetN64_DrawSessionWithRoundTimeout(struct GameSession *session);
extern void SetN64_DrawTransitionMode();
extern void SetN64_EnterPendingSessionMode(void *gameSession);
extern void SetN64_ExitSessionAndDisablePaks(void *session);
extern void SetN64_HandleMode10Input(s32 session);
extern void SetN64_HandleMode11Input(s32 session);
extern void SetN64_HandleMode12Input(s32 session);
extern void SetN64_HandleMode16CreditsInput(s32 session);
extern void SetN64_HandleMode17CreditsInput(s32 session);
extern void SetN64_HandleMode5Input(s32 session);
extern void SetN64_HandleMode7Transition(struct GameSession *session);
extern void SetN64_HandleMode9Input();
extern void SetN64_InitializeFrontendScreenState(struct GameSession *gameSession);
extern void SetN64_InitializeMode15();
extern void SetN64_InitializeMode16Credits(s32 sessionAddress);
extern void SetN64_InitializeMode17Credits(s32 sessionAddress);
extern void SetN64_InitializeMode18();
extern void SetN64_InitializeMode19();
extern void SetN64_InitializeMode2();
extern void SetN64_InitializeMode6();
extern void SetN64_InitializeMode8Scene();
extern void SetN64_InitializeTransitionMode();
extern void SetN64_ResetMode10Items(s32 sessionAddress);
extern void SetN64_ResetMode11Items(s32 sessionAddress);
extern void SetN64_ResetMode12Items(int sessionAddress);
extern void SetN64_ResetMode4Effects();
extern void SetN64_ResetMode5Items(s32 sessionAddress);
extern void SetN64_ResetMode9Items(s32 sessionAddress);
extern void SetN64_ResetSceneForIntro(void *owner);
struct GameSession; extern void SetN64_ResumeSelectedSession(struct GameSession *unused);
extern void SetN64_SetMode7AudioState();
struct TimedSessionTransitionView; extern void SetN64_SetupLoadingBackdropEu(struct TimedSessionTransitionView *state);
struct GameSession; extern void SetN64_StartRound(struct GameSession *session);
extern void SetN64_UpdateActiveSession();
extern void SetN64_UpdateMode15();
extern void SetN64_UpdateMode18();
extern void SetN64_UpdateMode19();
extern void SetN64_UpdateMode6();
extern void SetN64_UpdateMode8();
#endif
#if defined(VERSION_EU_X)
struct GameSession; extern void SetN64_AdvanceIntroForMemorySize(struct GameSession *session);
extern void SetN64_AdvanceToModeEight(struct GameSession *session);
extern void SetN64_AdvanceToModeFive(struct GameSession *session);
extern void SetN64_AdvanceToModeFour(struct GameSession *value);
extern void SetN64_ClearSessionPlayerPools(void *owner);
extern void SetN64_DrawCenteredIntroText(void *state);
extern void SetN64_DrawFullscreenBackdrop(void *unused);
extern void SetN64_DrawIntroBackdrop();
extern void SetN64_DrawMode10Session(void *session);
extern void SetN64_DrawMode11Session(void *session);
extern void SetN64_DrawMode12Session(void *session);
extern void SetN64_DrawMode15();
extern void SetN64_DrawMode16Credits(s32 session);
extern void SetN64_DrawMode17Credits(s32 session);
extern void SetN64_DrawMode18();
extern void SetN64_DrawMode19();
extern void SetN64_DrawMode4Backdrop();
extern void SetN64_DrawMode5Session(s32 session);
extern void SetN64_DrawMode6();
extern void SetN64_DrawMode8Session(struct GameSession *session);
extern void SetN64_DrawMode9Session(void *session);
extern void SetN64_DrawRoundTimeoutSession(struct GameSession *session);
extern void SetN64_DrawSessionWithRoundTimeout(struct GameSession *session);
extern void SetN64_DrawTransitionMode();
extern void SetN64_EnterPendingSessionMode(void *gameSession);
extern void SetN64_ExitSessionAndDisablePaks(void *session);
extern void SetN64_HandleMode10Input(s32 session);
extern void SetN64_HandleMode11Input(s32 session);
extern void SetN64_HandleMode12Input(s32 session);
extern void SetN64_HandleMode16CreditsInput(s32 session);
extern void SetN64_HandleMode17CreditsInput(s32 session);
extern void SetN64_HandleMode5Input(s32 session);
extern void SetN64_HandleMode7Transition(struct GameSession *session);
extern void SetN64_HandleMode9Input();
extern void SetN64_InitializeFrontendScreenState(struct GameSession *gameSession);
extern void SetN64_InitializeMode15();
extern void SetN64_InitializeMode16Credits(s32 sessionAddress);
extern void SetN64_InitializeMode17Credits(s32 sessionAddress);
extern void SetN64_InitializeMode18();
extern void SetN64_InitializeMode19();
extern void SetN64_InitializeMode2();
extern void SetN64_InitializeMode6();
extern void SetN64_InitializeMode8Scene();
extern void SetN64_InitializeTransitionMode();
extern void SetN64_ResetMode10Items(s32 sessionAddress);
extern void SetN64_ResetMode11Items(s32 sessionAddress);
extern void SetN64_ResetMode12Items(int sessionAddress);
extern void SetN64_ResetMode4Effects();
extern void SetN64_ResetMode5Items(s32 sessionAddress);
extern void SetN64_ResetMode9Items(s32 sessionAddress);
extern void SetN64_ResetSceneForIntro(void *owner);
struct GameSession; extern void SetN64_ResumeSelectedSession(struct GameSession *unused);
extern void SetN64_SetMode7AudioState();
struct TimedSessionTransitionView; extern void SetN64_SetupLoadingBackdropEuX(struct TimedSessionTransitionView *state);
struct GameSession; extern void SetN64_StartRound(struct GameSession *session);
extern void SetN64_UpdateActiveSession();
extern void SetN64_UpdateMode15();
extern void SetN64_UpdateMode18();
extern void SetN64_UpdateMode19();
extern void SetN64_UpdateMode6();
extern void SetN64_UpdateMode8();
#endif
#endif
#if defined(VERSION_US_REV1)

/* ROM-grounded exact candidate, normalized from prior lane proof. */
extern char g_setN64_InitializeFrontendScreenStateEntry[];
extern char g_setN64_ExitSessionAndDisablePaksEntry[];
extern char g_setN64_DrawRoundTimeoutSessionEntry[];
extern char g_setN64_ResetSceneForIntroEntry[];
extern char g_setN64_AdvanceIntroForMemorySizeEntry[];
extern char g_setN64_DrawIntroBackdropEntry[];
extern char g_setN64_InitializeMode2Entry[];
extern char g_setN64_AdvanceToModeFiveEntry[];
extern char g_setN64_DrawCenteredIntroTextEntry[];
#endif
