#ifndef COMMON_INTEGERSTATEB0_H
#define COMMON_INTEGERSTATEB0_H
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"

struct IntegerStateB0;


extern int g_frontendScreenInitialized;

struct GameSession;
#include "COMMON/GAME_SESSION.H"

extern void SetN64_DrawSessionWithRoundTimeout(struct GameSession *session);


struct IntegerStateB0;
typedef struct IntegerStateB0 IntegerStateB0;










extern float g_gameClockTicksPerSecond;
extern float g_gameClockUnitIncrement;

struct IntroBackdropStateView;
typedef struct IntroBackdropStateView IntroBackdropStateView;

extern float g_attractTimeoutBegin;

extern float g_introInitialFadeTimer;

struct GameSession;


struct IntroBackdropStateView;

extern int g_modeFourFrameCounter;








extern float g_attractTimeoutFinish;

extern float g_gameClockSecondsPerMinute;






extern void Frontend_RequestScreenMode(s32 value);
extern void Textload_SetTextureEffect(unsigned int value);
extern s32 g_introExitPending;


extern s32 g_geometryFogEffectEnabled;

extern s32 Control_IsSnapshotActive(void);
extern void OnScreen_DrawStatusBars(void *playerHud);
#endif
