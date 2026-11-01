#include "SYSTEM/ENGINE_DATA_SOURCE.H"
#include "include_asm.h"

/* g_SchedHandlerspcompletionEncodedWordsBlock1.CPP */
/* ROM-grounded data: rodata/writable/800D299C */
#ifdef VERSION_DE
EngineSchedulerState g_SchedHandlerspcompletionEncodedWordsBlock1 = {
    0.0f, 0.0f, 0.0f, 0.0f, 262144.0f, 1, 0, (void *)0x800E4C00,
    2048, 0, 0, 1, 1, 0, 0
};
#endif
#ifdef VERSION_EU
EngineSchedulerState g_SchedHandlerspcompletionEncodedWordsBlock1 = {
    0.0f, 0.0f, 0.0f, 0.0f, 262144.0f, 1, 0, (void *)0x800F4C00,
    2048, 0, 0, 1, 1, 0, 0
};
#endif
#ifdef VERSION_EU_X
EngineSchedulerState g_SchedHandlerspcompletionEncodedWordsBlock1 = {
    0.0f, 0.0f, 0.0f, 0.0f, 262144.0f, 1, 0, (void *)0x800EEC00,
    2048, 0, 0, 1, 1, 0, 0
};
#endif
#ifdef VERSION_US
EngineSchedulerState g_SchedHandlerspcompletionEncodedWordsBlock1 = {
    0.0f, 0.0f, 0.0f, 0.0f, 262144.0f, 1, 0, (void *)0x800E2C00,
    2048, 0, 0, 1, 1, 0, 0
};
#endif
#ifdef VERSION_US_REV1
EngineSchedulerState g_SchedHandlerspcompletionEncodedWordsBlock1 = {
    0.0f, 0.0f, 0.0f, 0.0f, 262144.0f, 1, 0, (void *)0x800E8C00,
    2048, 0, 0, 1, 1, 0, 0
};
#endif

#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
extern void SetN64_AdvanceIntroForMemorySize();
extern void SetN64_AdvanceToModeEight(struct GameSession *session);
extern void SetN64_AdvanceToModeFive(struct GameSession *session);
extern void SetN64_AdvanceToModeFour(struct GameSession *value);
extern void SetN64_ClearSessionPlayerPools();
extern void SetN64_DrawCenteredIntroText();
extern void SetN64_DrawFullscreenBackdrop();
extern void SetN64_DrawIntroBackdrop();
extern void SetN64_DrawMode10Session(void *session);
extern void SetN64_DrawMode11Session(void *session);
extern void SetN64_DrawMode12Session(void *session);
extern void SetN64_DrawMode15();
extern void SetN64_DrawMode16Credits();
extern void SetN64_DrawMode17Credits();
extern void SetN64_DrawMode18();
extern void SetN64_DrawMode19();
extern void SetN64_DrawMode4Backdrop();
extern void SetN64_DrawMode5Session();
extern void SetN64_DrawMode6();
extern void SetN64_DrawMode8Session(struct GameSession *session);
extern void SetN64_DrawMode9Session(void *session);
extern void SetN64_DrawRoundTimeoutSession(struct GameSession *session);
extern void SetN64_DrawSessionWithRoundTimeout(struct GameSession *session);
extern void SetN64_DrawTransitionMode();
extern void SetN64_EnterPendingSessionMode(void *gameSession);
extern void SetN64_ExitSessionAndDisablePaks();
extern void SetN64_HandleMode10Input();
extern void SetN64_HandleMode11Input();
extern void SetN64_HandleMode12Input();
extern void SetN64_HandleMode16CreditsInput();
extern void SetN64_HandleMode17CreditsInput();
extern void SetN64_HandleMode5Input();
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
extern void SetN64_ResetSceneForIntro();
extern void SetN64_ResumeSelectedSession();
extern void SetN64_SetMode7AudioState();
extern void SetN64_SetupLoadingBackdropDe();
extern void SetN64_StartRound();
extern void SetN64_UpdateActiveSession();
extern void SetN64_UpdateMode15();
extern void SetN64_UpdateMode18();
extern void SetN64_UpdateMode19();
extern void SetN64_UpdateMode6();
extern void SetN64_UpdateMode8();
EngineSessionHandlers D_src_55fe5453[21] = {
    { (EngineSessionCallback)((char *)SetN64_InitializeFrontendScreenState - 0x80000000), (EngineSessionCallback)((char *)SetN64_ExitSessionAndDisablePaks - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawRoundTimeoutSession - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResetSceneForIntro - 0x80000000), (EngineSessionCallback)((char *)SetN64_AdvanceIntroForMemorySize - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawIntroBackdrop - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeMode2 - 0x80000000), (EngineSessionCallback)((char *)SetN64_AdvanceToModeFive - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawCenteredIntroText - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ClearSessionPlayerPools - 0x80000000), (EngineSessionCallback)((char *)SetN64_AdvanceToModeFour - 0x80000000), (EngineSessionCallback)((char *)SetN64_SetupLoadingBackdropDe - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResetMode4Effects - 0x80000000), (EngineSessionCallback)((char *)SetN64_AdvanceToModeEight - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode4Backdrop - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResetMode5Items - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode5Input - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode5Session - 0x80000000) },
    { (EngineSessionCallback)((char *)SetN64_InitializeMode6 - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateMode6 - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode6 - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_SetMode7AudioState - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode7Transition - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawFullscreenBackdrop - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeMode8Scene - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateMode8 - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode8Session - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResetMode9Items - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode9Input - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode9Session - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResetMode10Items - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode10Input - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode10Session - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResetMode11Items - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode11Input - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode11Session - 0x80000000) },
    { (EngineSessionCallback)((char *)SetN64_ResetMode12Items - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode12Input - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode12Session - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_StartRound - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateActiveSession - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawSessionWithRoundTimeout - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResumeSelectedSession - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateActiveSession - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawSessionWithRoundTimeout - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeMode15 - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateMode15 - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode15 - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeMode16Credits - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode16CreditsInput - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode16Credits - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeMode17Credits - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode17CreditsInput - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode17Credits - 0x80000000) },
    { (EngineSessionCallback)((char *)SetN64_InitializeMode18 - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateMode18 - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode18 - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeMode19 - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateMode19 - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode19 - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeTransitionMode - 0x80000000), (EngineSessionCallback)((char *)SetN64_EnterPendingSessionMode - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawTransitionMode - 0x80000000) },
};
#endif
#if defined(VERSION_EU)
extern void SetN64_AdvanceIntroForMemorySize();
extern void SetN64_AdvanceToModeEight(struct GameSession *session);
extern void SetN64_AdvanceToModeFive(struct GameSession *session);
extern void SetN64_AdvanceToModeFour(struct GameSession *value);
extern void SetN64_ClearSessionPlayerPools();
extern void SetN64_DrawCenteredIntroText();
extern void SetN64_DrawFullscreenBackdrop();
extern void SetN64_DrawIntroBackdrop();
extern void SetN64_DrawMode10Session(void *session);
extern void SetN64_DrawMode11Session(void *session);
extern void SetN64_DrawMode12Session(void *session);
extern void SetN64_DrawMode15();
extern void SetN64_DrawMode16Credits();
extern void SetN64_DrawMode17Credits();
extern void SetN64_DrawMode18();
extern void SetN64_DrawMode19();
extern void SetN64_DrawMode4Backdrop();
extern void SetN64_DrawMode5Session();
extern void SetN64_DrawMode6();
extern void SetN64_DrawMode8Session(struct GameSession *session);
extern void SetN64_DrawMode9Session(void *session);
extern void SetN64_DrawRoundTimeoutSession(struct GameSession *session);
extern void SetN64_DrawSessionWithRoundTimeout(struct GameSession *session);
extern void SetN64_DrawTransitionMode();
extern void SetN64_EnterPendingSessionMode(void *gameSession);
extern void SetN64_ExitSessionAndDisablePaks();
extern void SetN64_HandleMode10Input();
extern void SetN64_HandleMode11Input();
extern void SetN64_HandleMode12Input();
extern void SetN64_HandleMode16CreditsInput();
extern void SetN64_HandleMode17CreditsInput();
extern void SetN64_HandleMode5Input();
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
extern void SetN64_ResetSceneForIntro();
extern void SetN64_ResumeSelectedSession();
extern void SetN64_SetMode7AudioState();
extern void SetN64_SetupLoadingBackdropEu();
extern void SetN64_StartRound();
extern void SetN64_UpdateActiveSession();
extern void SetN64_UpdateMode15();
extern void SetN64_UpdateMode18();
extern void SetN64_UpdateMode19();
extern void SetN64_UpdateMode6();
extern void SetN64_UpdateMode8();
EngineSessionHandlers D_src_55fe5453[21] = {
    { (EngineSessionCallback)((char *)SetN64_InitializeFrontendScreenState - 0x80000000), (EngineSessionCallback)((char *)SetN64_ExitSessionAndDisablePaks - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawRoundTimeoutSession - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResetSceneForIntro - 0x80000000), (EngineSessionCallback)((char *)SetN64_AdvanceIntroForMemorySize - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawIntroBackdrop - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeMode2 - 0x80000000), (EngineSessionCallback)((char *)SetN64_AdvanceToModeFive - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawCenteredIntroText - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ClearSessionPlayerPools - 0x80000000), (EngineSessionCallback)((char *)SetN64_AdvanceToModeFour - 0x80000000), (EngineSessionCallback)((char *)SetN64_SetupLoadingBackdropEu - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResetMode4Effects - 0x80000000), (EngineSessionCallback)((char *)SetN64_AdvanceToModeEight - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode4Backdrop - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResetMode5Items - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode5Input - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode5Session - 0x80000000) },
    { (EngineSessionCallback)((char *)SetN64_InitializeMode6 - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateMode6 - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode6 - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_SetMode7AudioState - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode7Transition - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawFullscreenBackdrop - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeMode8Scene - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateMode8 - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode8Session - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResetMode9Items - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode9Input - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode9Session - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResetMode10Items - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode10Input - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode10Session - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResetMode11Items - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode11Input - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode11Session - 0x80000000) },
    { (EngineSessionCallback)((char *)SetN64_ResetMode12Items - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode12Input - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode12Session - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_StartRound - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateActiveSession - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawSessionWithRoundTimeout - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResumeSelectedSession - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateActiveSession - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawSessionWithRoundTimeout - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeMode15 - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateMode15 - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode15 - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeMode16Credits - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode16CreditsInput - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode16Credits - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeMode17Credits - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode17CreditsInput - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode17Credits - 0x80000000) },
    { (EngineSessionCallback)((char *)SetN64_InitializeMode18 - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateMode18 - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode18 - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeMode19 - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateMode19 - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode19 - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeTransitionMode - 0x80000000), (EngineSessionCallback)((char *)SetN64_EnterPendingSessionMode - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawTransitionMode - 0x80000000) },
};
#endif
#if defined(VERSION_EU_X)
extern void SetN64_AdvanceIntroForMemorySize();
extern void SetN64_AdvanceToModeEight(struct GameSession *session);
extern void SetN64_AdvanceToModeFive(struct GameSession *session);
extern void SetN64_AdvanceToModeFour(struct GameSession *value);
extern void SetN64_ClearSessionPlayerPools();
extern void SetN64_DrawCenteredIntroText();
extern void SetN64_DrawFullscreenBackdrop();
extern void SetN64_DrawIntroBackdrop();
extern void SetN64_DrawMode10Session(void *session);
extern void SetN64_DrawMode11Session(void *session);
extern void SetN64_DrawMode12Session(void *session);
extern void SetN64_DrawMode15();
extern void SetN64_DrawMode16Credits();
extern void SetN64_DrawMode17Credits();
extern void SetN64_DrawMode18();
extern void SetN64_DrawMode19();
extern void SetN64_DrawMode4Backdrop();
extern void SetN64_DrawMode5Session();
extern void SetN64_DrawMode6();
extern void SetN64_DrawMode8Session(struct GameSession *session);
extern void SetN64_DrawMode9Session(void *session);
extern void SetN64_DrawRoundTimeoutSession(struct GameSession *session);
extern void SetN64_DrawSessionWithRoundTimeout(struct GameSession *session);
extern void SetN64_DrawTransitionMode();
extern void SetN64_EnterPendingSessionMode(void *gameSession);
extern void SetN64_ExitSessionAndDisablePaks();
extern void SetN64_HandleMode10Input();
extern void SetN64_HandleMode11Input();
extern void SetN64_HandleMode12Input();
extern void SetN64_HandleMode16CreditsInput();
extern void SetN64_HandleMode17CreditsInput();
extern void SetN64_HandleMode5Input();
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
extern void SetN64_ResetSceneForIntro();
extern void SetN64_ResumeSelectedSession();
extern void SetN64_SetMode7AudioState();
extern void SetN64_SetupLoadingBackdropEuX();
extern void SetN64_StartRound();
extern void SetN64_UpdateActiveSession();
extern void SetN64_UpdateMode15();
extern void SetN64_UpdateMode18();
extern void SetN64_UpdateMode19();
extern void SetN64_UpdateMode6();
extern void SetN64_UpdateMode8();
EngineSessionHandlers D_src_55fe5453[21] = {
    { (EngineSessionCallback)((char *)SetN64_InitializeFrontendScreenState - 0x80000000), (EngineSessionCallback)((char *)SetN64_ExitSessionAndDisablePaks - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawRoundTimeoutSession - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResetSceneForIntro - 0x80000000), (EngineSessionCallback)((char *)SetN64_AdvanceIntroForMemorySize - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawIntroBackdrop - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeMode2 - 0x80000000), (EngineSessionCallback)((char *)SetN64_AdvanceToModeFive - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawCenteredIntroText - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ClearSessionPlayerPools - 0x80000000), (EngineSessionCallback)((char *)SetN64_AdvanceToModeFour - 0x80000000), (EngineSessionCallback)((char *)SetN64_SetupLoadingBackdropEuX - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResetMode4Effects - 0x80000000), (EngineSessionCallback)((char *)SetN64_AdvanceToModeEight - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode4Backdrop - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResetMode5Items - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode5Input - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode5Session - 0x80000000) },
    { (EngineSessionCallback)((char *)SetN64_InitializeMode6 - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateMode6 - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode6 - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_SetMode7AudioState - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode7Transition - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawFullscreenBackdrop - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeMode8Scene - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateMode8 - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode8Session - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResetMode9Items - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode9Input - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode9Session - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResetMode10Items - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode10Input - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode10Session - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResetMode11Items - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode11Input - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode11Session - 0x80000000) },
    { (EngineSessionCallback)((char *)SetN64_ResetMode12Items - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode12Input - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode12Session - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_StartRound - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateActiveSession - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawSessionWithRoundTimeout - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_ResumeSelectedSession - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateActiveSession - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawSessionWithRoundTimeout - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeMode15 - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateMode15 - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode15 - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeMode16Credits - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode16CreditsInput - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode16Credits - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeMode17Credits - 0x80000000), (EngineSessionCallback)((char *)SetN64_HandleMode17CreditsInput - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode17Credits - 0x80000000) },
    { (EngineSessionCallback)((char *)SetN64_InitializeMode18 - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateMode18 - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode18 - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeMode19 - 0x80000000), (EngineSessionCallback)((char *)SetN64_UpdateMode19 - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawMode19 - 0x80000000) }, { (EngineSessionCallback)((char *)SetN64_InitializeTransitionMode - 0x80000000), (EngineSessionCallback)((char *)SetN64_EnterPendingSessionMode - 0x80000000), (EngineSessionCallback)((char *)SetN64_DrawTransitionMode - 0x80000000) },
};
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

EngineSessionHandlers g_SchedHandlerspcompletionEncodedWords[3] = {
    { (EngineSessionCallback)g_setN64_InitializeFrontendScreenStateEntry, (EngineSessionCallback)g_setN64_ExitSessionAndDisablePaksEntry, (EngineSessionCallback)g_setN64_DrawRoundTimeoutSessionEntry }, { (EngineSessionCallback)g_setN64_ResetSceneForIntroEntry, (EngineSessionCallback)g_setN64_AdvanceIntroForMemorySizeEntry, (EngineSessionCallback)g_setN64_DrawIntroBackdropEntry }, { (EngineSessionCallback)g_setN64_InitializeMode2Entry, (EngineSessionCallback)g_setN64_AdvanceToModeFiveEntry, (EngineSessionCallback)g_setN64_DrawCenteredIntroTextEntry },
};
#endif
