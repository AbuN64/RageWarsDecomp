#ifndef ENGINE_SESSION_H
#define ENGINE_SESSION_H
#include "types.h"
struct EffectSlotPool;
struct Shared_World;
extern void SetN64_CollectVisibleEffectNodes(struct EffectSlotPool *effectPool, struct Shared_World *results);
extern int g_gameModeTransitionFrames;
extern float g_creditsScrollPosition;
#include "Common/timing_world.h"
#include "Frontend/frontend_address_symbols.h"
#include "Common/Lone/screen_image_resources_enabled.h"
#include "Engine/Instance/insthdr.h"
#include "Common/gameplay_camera.h"
#include "Common/menu_model_preview.h"
#include "Ovlgame/render_buffer_resources.h"
#include "Common/sessionhandlerrow.h"
#include "types.h"
#include "Common/rendersettings.h"
#include <PR/ucode.h>

struct EngineSessionHandlers;
struct SessionInitializeHandler;
struct TimingWorld;
struct UnitVp;
struct EffectSlotPool;
/* Byte size of the RSP boot microcode, from its linker boundary symbols. */
#define RSP_BOOT_TEXT_SIZE ((u32)rspbootTextEnd - (u32)rspbootTextStart)
#include "Common/display.h"
#include "Common/round_session.h"
#include "Common/vector4f.h"
#include "Common/frontend_clock_state.h"
#include "Common/frame_direction.h"
#include "Common/results.h"
#include "Common/vector.h"

/* GameSession mode: the screen the session mode table runs; values index that table. */
enum SessionMode {
    SESSION_MODE_FRONTEND_START = 0,
    SESSION_MODE_INTRO = 1,
    SESSION_MODE_INTRO_TEXT = 2,
    SESSION_MODE_LOADING_BACKDROP = 3,
    SESSION_MODE_SPLASH_IMAGE = 4,
    SESSION_MODE_OPENING_CINEMA = 5,
    SESSION_MODE_UNUSED_AFTER_OPENING_CINEMA = 6,
    SESSION_MODE_TITLE_SCREEN = 7,
    SESSION_MODE_MAIN_MENU = 8,
    SESSION_MODE_ATTRACT_CINEMA = 9,
    SESSION_MODE_SKIPPABLE_PRE_ROUND_CINEMA = 10,
    SESSION_MODE_PRE_ROUND_CINEMA = 11,
    SESSION_MODE_LEVEL_INTRO_CINEMA = 12,
    SESSION_MODE_ROUND = 13,
    SESSION_MODE_RESUME_ROUND = 14,
    SESSION_MODE_UNUSED_AFTER_RESUME = 15,
    SESSION_MODE_CREDITS_ROLL = 16,
    SESSION_MODE_SKIPPABLE_CREDITS_ROLL = 17,
    SESSION_MODE_UNUSED_AFTER_CREDITS = 18,
    SESSION_MODE_UNUSED_BEFORE_TRANSITION = 19,
    SESSION_MODE_TRANSITION = 20,
};
struct IntrusiveList;

struct Draw {
    s32 drawModel;
    s32 updateAnimation;
    s32 allocationMode; /* 0x08: resource allocation request */
    void **model;
    char reserved10[0x10];
    IntrusiveList recycled; /* 0x20 */
};
typedef struct Draw Draw;


struct RecordOutputFieldsView {
    char pad0[0x8];
    float thirdScalar;
    char pad8[0xC - 0x8 - sizeof(float)];
    float fourthScalar;
    char padC[0x10 - 0xC - sizeof(float)];
    float secondScalar;
    char pad10[0x20 - 0x10 - sizeof(float)];
    int outputWord;
};

typedef struct TimedSessionTransitionView {
    char pad0[0x26DB0];
    f32 transitionTimer;
    char padAfterTransitionTimer[0x26DBC - 0x26DB4];
    s32 transitionTarget;
    char padAfterTransitionTarget[1];
    s8 transitionPhase;
} TimedSessionTransitionView;

/* One state-dispatch row in g_sessionUpdateHandlers, stride 0xC. */
typedef struct SessionHandlerRow {
    void (*update)(void *);
    char reserved4[8];
} SessionHandlerRow;

struct SessionPlayerItemResetView {
    char pad0[0x25580];
    char playerPool;
    char padAfterPlayerPool[0x255C8 - 0x25580 - sizeof(char)];
    char actorPools;
};

typedef struct RenderState {
    union { Frame views[4]; Display display; } ring; char pad500[0x2688C]; RenderSettings settings; char padAfterSettings[4]; s32 handle;
    char padAfterHandle[0x10]; s32 enabled, reservedTransitionState, transitionBlocked, clockPaused;
} RenderState;

extern void SetN64_AdvanceDisplayFrame(struct Display *);

extern void SetN64_BuildAndSubmitSessionFrame(struct TimingWorld *);

extern void SetN64_UpdateUnusedModeBeforeTransition(void);

extern void SetN64_DrawUnusedModeAfterCredits(void);

extern void SetN64_InitializeUnusedModeAfterCredits(void);

extern void SetN64_DrawUnusedModeBeforeTransition(void);

extern void SetN64_DrawTransitionMode(void);

extern void SetN64_UpdateUnusedModeAfterCredits(void);

extern void SetN64_InitializeUnusedModeBeforeTransition(void);

extern void SetN64_EmptyVideoModeHookUs(void);

extern void SetN64_EmptyVideoModeHookSecondUs(void);

struct IntegerStateB0 {
    unsigned char padding_0[136];
    s32 first;
    unsigned char padding_8C[32];
    s32 transitionActive;
};

struct IntroBackdropStateView {
    char pad0[0x160];
    s32 poolClearedWord;
};

extern void SetN64_UpdateActiveSession(void);

extern void SetN64_InitializeUnusedModeAfterResume(void);

extern void SetN64_UpdateUnusedModeAfterResume(void);

extern void SetN64_DrawUnusedModeAfterResume(void);

extern void SetN64_DrawUnusedModeAfterOpeningCinema(void);

extern void SetN64_AdvanceSplashImageToMainMenu(struct GameSession *session);

extern void SetN64_StartPreRoundCinema(s32 sessionAddress);

extern void SetN64_StartAttractCinema(s32 sessionAddress);

extern void SetN64_UpdateUnusedModeAfterOpeningCinema(void);

extern void SetN64_DrawMainMenu(struct GameSession *session);

extern void SetN64_DrawAttractCinema(void *session);

extern void SetN64_HandleTitleScreenInput(struct GameSession *session);

extern void SetN64_UpdateMainMenu(void);

extern void SetN64_ResetSplashImageEffects(void);

extern void SetN64_StartOpeningCinema(s32 sessionAddress);

extern void SetN64_StartTitleMusic(void);

extern void SetN64_InitializeUnusedModeAfterOpeningCinema(void);

extern void SetN64_DrawSplashImage(void);

extern void SetN64_DrawTextLines(void *state, s32 drawBackdrop, char **lines, s32 screenX, s32 screenY, s32 lineStep, f32 scaleX, f32 scaleY);

extern void SetN64_EmptySessionHookDeA(void);

extern void SetN64_EmptySessionHookRev1A(void);

extern void SetN64_EmptySessionHookRev1C(void);

extern void SetN64_EmptySessionHookRev1B(void);

extern void SetN64_EnterPendingSessionMode(void *gameSession);

extern void SetN64_InitializeCreditsRoll(s32 sessionAddress);

extern void SetN64_InitializeSkippableCreditsRoll(s32 sessionAddress);

extern void SetN64_InitializeTransitionMode(void);

extern void SetN64_GetRecordOutputs(struct RecordOutputFieldsView *source, int *word, float *third, float *fourth, float *second);

extern void SetN64_EmptyFrameDirectionHookUs(void);

extern void SetN64_EmptyFrameDirectionHookEu(void);

extern void SetN64_EmptyFrameDirectionHookSecondEu(void);

extern void SetN64_EmptyFrameDirectionHookSecondUs(void);

extern void SetN64_EmptySessionHookSecondEuX(void);

struct RoundSessionItemStateView {
    char pad0[0x26DB8];
    s32 reservedWord;
    char padAfterReservedWord[0x1C];
    s32 selectionKeyBase;
};

extern void SetN64_StartSkippablePreRoundCinema(s32 sessionAddress);

extern void SetN64_DrawPreRoundCinema(void *session);

extern void SetN64_DrawSkippablePreRoundCinema(void *session);

extern void SetN64_DrawLevelIntroCinema(void *session);

extern void SetN64_StartLevelIntroCinema(int sessionAddress);

#define LOAD_SETUP SetN64_SetupLoadingBackdrop
/* The loading-screen setup routine and the view-matrix array it fills sit at different addresses in each cartridge. */
#if defined(VERSION_DE)
#define VIEW_MATRICES g_loadingViewMatricesDe
#else
#define VIEW_MATRICES g_loadingViewMatrices
#endif

extern u8 VIEW_MATRICES[];




extern void Cache_RunCompactionPasses(s32);

extern void *SetN64_GetPackSection(void *table, s32 index);
extern char g_schedulerStateBuffer;

extern s32 SetN64_GetPackSectionOffsetAndSize(s32 directoryAddress, s32 sectionIndex, s32 *sectionSizeOut);

extern void SetN64_GetPackBaseAndSize(int *directory, int * *packBaseOut, int *packSizeOut);

extern int SetN64_GetRecordBlockSize(int *recordHeader);

extern void SetN64_GetChunkStorage(struct ActorAnimationEventTable *chunk, void **storageOut, s32 *sizeOut);

extern void *SetN64_GetChunkPayload(int *, int *);

extern void SetN64_TransposeRecords(void *sourceBlock, void *destinationBlock, s32 copyBack);

extern void SetN64_UpdateEffectPool(struct EffectSlotPool *world);

extern void SetN64_InitializeEffectSlot(struct EffectSlot *effectSlot);

void SetN64_UpdateEffectMotionAndBounds(struct EffectSlot *effect);

extern void SetN64_DrawVisibleEffects(char *effectPool, char *view);

extern void *SetN64_AllocateActorFromPool(struct EffectSlotPool *);

extern void SetN64_BeginFrameDisplayList(void *world);
struct GameSession;
extern void SetN64_RunGameLoop(struct GameSession *session);
int SetN64_GetDirectoryEntry(int *directory, int bankOffset, int level);
s32 SetN64_GetPackSectionSize(s32 *table, s32 index);
s32 SetN64_GetSizedPackSection(s32 packAddress, s32 sectionIndex, s32 *sectionSizeOut);
s32 SetN64_LocatePackSection(void *directory, s32 bankOffset, s32 sectionIndex, s32 *sectionSizeOut);
struct EffectSlot;
void SetN64_RecycleGlobalEffectNode(struct EffectSlot *node);
struct Display;
struct Frame;
void SetN64_SubmitFrameTasks(struct Display *display, struct Frame *frame);
extern s32 SetN64_GetPackSize(s32 *bitSet);
extern void SetN64_ClearSessionPlayerPools(void *owner);
extern void SetN64_DrawCenteredIntroText(void *state);
extern void SetN64_DrawFullscreenBackdrop(void *session);
extern void SetN64_DrawCreditsRoll(s32 session);
extern void SetN64_DrawSkippableCreditsRoll(s32 session);
extern void SetN64_DrawOpeningCinema(s32 session);
extern void SetN64_ExitSessionAndDisablePaks(void *session);
extern void SetN64_HandleSkippablePreRoundCinemaInput(s32 session);
extern void SetN64_HandlePreRoundCinemaInput(s32 session);
extern void SetN64_HandleLevelIntroCinemaInput(s32 session);
extern void SetN64_HandleCreditsRollInput(s32 session);
extern void SetN64_HandleSkippableCreditsRollInput(s32 session);
extern void SetN64_HandleOpeningCinemaInput(s32 session);
extern void SetN64_HandleAttractCinemaInput(s32 session);
extern void SetN64_InitializeMainMenuScene(void *owner);
extern void SetN64_ResetSceneForIntro(void *owner);
extern void SetN64_BeginModeTransition(struct GameSession *session, s32 targetMode);
extern void SetN64_UpdateGameMode(struct GameSession *session);
extern void SetN64_ClearDepthRect(void *session, s32 ulx, s32 lrx, s32 uly, s32 lry, s32 interlaced);
#if defined(VERSION_US)
extern struct EngineSessionHandlers g_screenModeHandlers[21];
#endif
extern void SetN64_ResetSessionPlayerPools(struct GameSession *owner, s32 count, s32 forceActive);
extern void SetN64_DrawSessionFade(struct GameSession *session);
extern char g_SetN64_AdvanceIntroForMemorySizePackedAddress[];
extern char addrLow_SetN64_AdvanceSplashImageToMainMenu_us[];
extern char addrLow_SetN64_AdvanceIntroTextToOpeningCinema_us[];
extern char addrLow_SetN64_AdvanceLoadingToSplashImage_us[];
extern char g_SetN64_ClearSessionPlayerPoolsPackedAddress[];
extern char g_SetN64_ConfigureVideoAndEnterModeUsPackedAddress[];
extern char g_SetN64_DrawCenteredIntroTextPackedAddress[];
extern char g_SetN64_DrawIntroBackdropPackedAddress[];
extern char addrLow_SetN64_DrawSkippablePreRoundCinema_us[];
extern char addrLow_SetN64_DrawPreRoundCinema_us[];
extern char addrLow_SetN64_DrawLevelIntroCinema_us[];
extern char addrLow_SetN64_DrawUnusedModeAfterResume_us[];
extern char addrLow_SetN64_DrawCreditsRoll_us[];
extern char addrLow_SetN64_DrawSkippableCreditsRoll_us[];
extern char addrLow_SetN64_DrawOpeningCinema_us[];
extern char addrLow_SetN64_DrawUnusedModeAfterOpeningCinema_us[];
extern char addrLow_SetN64_DrawMainMenu_us[];
extern char g_SetN64_DrawRoundTimeoutSessionPackedAddress[];
extern char g_SetN64_DrawSessionWithRoundTimeoutPackedAddress[];
extern char g_SetN64_DrawTransitionModePackedAddress[];
extern char g_SetN64_EmptyVideoModeHookUsPackedAddress[];
extern char g_SetN64_ExitSessionAndDisablePaksPackedAddress[];
extern char addrLow_SetN64_HandleSkippablePreRoundCinemaInput_us[];
extern char addrLow_SetN64_HandlePreRoundCinemaInput_us[];
extern char addrLow_SetN64_HandleLevelIntroCinemaInput_us[];
extern char addrLow_SetN64_HandleCreditsRollInput_us[];
extern char addrLow_SetN64_HandleSkippableCreditsRollInput_us[];
extern char addrLow_SetN64_HandleOpeningCinemaInput_us[];
extern char addrLow_SetN64_HandleTitleScreenInput_us[];
extern char addrLow_SetN64_HandleAttractCinemaInput_us[];
extern char g_SetN64_InitializeFrontendScreenStatePackedAddress[];
extern char addrLow_SetN64_InitializeUnusedModeAfterResume_us[];
extern char addrLow_SetN64_InitializeCreditsRoll_us[];
extern char addrLow_SetN64_InitializeSkippableCreditsRoll_us[];
extern char addrLow_SetN64_InitializeIntroText_us[];
extern char addrLow_SetN64_InitializeUnusedModeAfterOpeningCinema_us[];
extern char addrLow_SetN64_InitializeMainMenuScene_us[];
extern char g_SetN64_InitializeTransitionModePackedAddress[];
extern char addrLow_SetN64_StartSkippablePreRoundCinema_us[];
extern char addrLow_SetN64_StartPreRoundCinema_us[];
extern char addrLow_SetN64_StartLevelIntroCinema_us[];
extern char addrLow_SetN64_ResetSplashImageEffects_us[];
extern char addrLow_SetN64_StartOpeningCinema_us[];
extern char addrLow_SetN64_StartAttractCinema_us[];
extern char g_SetN64_ResetSceneForIntroPackedAddress[];
extern char g_SetN64_ResumeSelectedSessionPackedAddress[];
extern char addrLow_SetN64_StartTitleMusic_us[];
extern char g_SetN64_UpdateActiveSessionPackedAddress[];
extern char addrLow_SetN64_UpdateUnusedModeAfterResume_us[];
extern char addrLow_SetN64_UpdateUnusedModeAfterOpeningCinema_us[];
extern char addrLow_SetN64_UpdateMainMenu_us[];
extern char g_Visdata_EmptyInitializeHookUsPackedAddress[];
extern char g_Visdata_EmptyReleaseHookUsPackedAddress[];
extern char addrLow_SetN64_AdvanceIntroForMemorySize[];
extern char addrLow_SetN64_AdvanceToMode8[];
extern char addrLow_SetN64_AdvanceToMode5[];
extern char addrLow_SetN64_AdvanceToMode4[];
extern char addrLow_SetN64_ClearSessionPlayerPools[];
extern char addrLow_SetN64_ConfigureVideoAndEnterModeUs[];
extern char addrLow_SetN64_DrawCenteredIntroText[];
extern char addrLow_SetN64_DrawIntroBackdrop[];
extern char addrLow_SetN64_DrawMode10Session[];
extern char addrLow_SetN64_DrawMode11Session[];
extern char addrLow_SetN64_DrawMode12Session[];
extern char addrLow_SetN64_DrawMode15[];
extern char addrLow_SetN64_DrawMode16Credits[];
extern char addrLow_SetN64_DrawMode17Credits[];
extern char addrLow_SetN64_DrawMode5Session[];
extern char addrLow_SetN64_DrawMode6[];
extern char addrLow_SetN64_DrawMode8Session[];
extern char addrLow_SetN64_DrawRoundTimeoutSession[];
extern char addrLow_SetN64_DrawSessionWithRoundTimeout[];
extern char addrLow_SetN64_DrawTransitionMode[];
extern char addrLow_SetN64_EmptyVideoModeHookUs[];
extern char addrLow_SetN64_ExitSessionAndDisablePaks[];
extern char addrLow_SetN64_HandleMode10Input[];
extern char addrLow_SetN64_HandleMode11Input[];
extern char addrLow_SetN64_HandleMode12Input[];
extern char addrLow_SetN64_HandleMode16CreditsInput[];
extern char addrLow_SetN64_HandleMode17CreditsInput[];
extern char addrLow_SetN64_HandleMode5Input[];
extern char addrLow_SetN64_HandleMode7Transition[];
extern char addrLow_SetN64_HandleMode9Input[];
extern char addrLow_SetN64_InitializeFrontendScreenState[];
extern char addrLow_SetN64_InitializeMode15[];
extern char addrLow_SetN64_InitializeMode16Credits[];
extern char addrLow_SetN64_InitializeMode17Credits[];
extern char addrLow_SetN64_InitializeMode2[];
extern char addrLow_SetN64_InitializeMode6[];
extern char addrLow_SetN64_InitializeMode8Scene[];
extern char addrLow_SetN64_InitializeTransitionMode[];
extern char addrLow_SetN64_ResetMode10Items[];
extern char addrLow_SetN64_ResetMode11Items[];
extern char addrLow_SetN64_ResetMode12Items[];
extern char addrLow_SetN64_ResetMode4Effects[];
extern char addrLow_SetN64_ResetMode5Items[];
extern char addrLow_SetN64_ResetMode9Items[];
extern char addrLow_SetN64_ResetSceneForIntro[];
extern char addrLow_SetN64_ResumeSelectedSession[];
extern char addrLow_SetN64_SetMode7AudioState[];
extern char addrLow_SetN64_UpdateActiveSession[];
extern char addrLow_SetN64_UpdateMode15[];
extern char addrLow_SetN64_UpdateMode6[];
extern char addrLow_SetN64_UpdateMode8[];
extern char addrLow_Visdata_EmptyInitializeHookUs[];
extern char addrLow_Visdata_EmptyReleaseHookUs[];
extern char g_debugLinkNotificationQueue[];
extern char addrLow_SetN64_AdvanceLoadingToSplashImage_us_rev1[];
extern char addrLow_SetN64_HandleTitleScreenInput_us_rev1[];
extern char addrLow_SetN64_StartLevelIntroCinema_us_rev1[];
extern f32 g_snapshotModeTransitionTimer;
extern f32 g_systemTimeFrameRateDe;
extern s16 *g_gameSchedulerMessage;
extern s32 *g_backdropTextLinesByLanguage[];
extern s32 g_backdropTextLinesDe;
extern s32 g_backdropTextLinesUs;
extern s32 g_frontendCurrentVideoModeIndex;
extern s32 g_schedulerFrameQueueReadIndex;
extern s32 g_schedulerFrameQueueWriteIndex;
extern s32 g_schedulerQueuedFrameCount;
extern s32 g_schedulerRetracesSinceSwap;
extern s32 g_schedulerSwapPending;
extern struct SessionInitializeHandler g_sessionInitializeHandlers[];
extern struct UnitVp g_fullScreenViewports[];
extern char g_videoModeDefaultLabel[];
extern f32 g_backdropModelFillValue;
extern f32 g_backdropTextScalePair;
extern f32 g_backdropYawRate;
extern f32 g_roundTimeoutBegin;
extern f32 g_roundTimeoutFinish;
extern struct MenuModelScreen g_fallbackScreenMessageEmitter[];
extern struct RenderBufferResources g_renderResourceRecord;
extern void System_CreateVideoManagerEu(s32 managerPriority);
struct GameSession; extern void SetN64_AdvanceIntroForMemorySize(struct GameSession *session);
struct GameSession; extern void SetN64_ResumeSelectedSession(struct GameSession *session);
struct TimedSessionTransitionView; extern void SetN64_SetupLoadingBackdrop(struct TimedSessionTransitionView *state);
struct GameSession; extern void SetN64_StartRound(struct GameSession *session);
struct GameSession; extern void SetN64_HandleSessionTransitionInput(struct GameSession *session, s32 cancelTarget, s32 target);

struct EffectSlot;
void SetN64_RecycleEffectNode(void *container, struct EffectSlot *node);
extern void SetN64_DrawCreditsLines(void);
extern void CCredits_UpdateScroll(void *);
extern void SetN64_StartBootstrapThread(void);
extern void SetN64_StartGameThreadAndIdle(s32 *gameSession, s32 threadArgument);
#endif

extern char addrLow_SetN64_DrawFullscreenBackdrop[];

extern char addrLow_SetN64_EmptyVideoModeHookSecondUs[];

extern char addrLow_SetN64_SetupLoadingBackdropUs[];

extern char addrLow_Visdata_EmptyInitializeHookSecondUs[];

extern char addrLow_Visdata_EmptyReleaseHookSecondUs[];
