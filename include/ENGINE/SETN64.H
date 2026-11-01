#ifndef ENGINE_SETN64_H
#define ENGINE_SETN64_H
#include "COMMON/SESSIONHANDLERROW.H"
#include "TYPES.H"
#include "COMMON/RENDERSETTINGS.H"
#include "COMMON/DISPLAY.H"
#include "COMMON/OBJRECAT26DD8.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/OBJRECAT20V1.H"
#include "COMMON/RESULTS.H"

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
    char pad26DB4[0x26DBC - 0x26DB4];
    s32 transitionTarget;
    char pad26DC0[1];
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
    char pad25580[0x255C8 - 0x25580 - sizeof(char)];
    char actorPools;
};

typedef struct RenderState {
    union { Frame views[4]; Display display; } ring; char pad500[0x2688C]; RenderSettings settings; char pad26DB0[4]; s32 handle;
    char pad26DB8[0x10]; s32 enabled, reservedTransitionState, transitionBlocked, clockPaused;
} RenderState;

extern void SetN64_AdvanceDisplayFrame(Display *);

extern void SetN64_BuildAndSubmitSessionFrame(TimingWorld *);

extern void SetN64_UpdateMode19(void);

extern void SetN64_DrawMode18(void);

extern void SetN64_InitializeMode18(void);

extern void SetN64_DrawMode19(void);

extern void SetN64_DrawTransitionMode(void);

extern void SetN64_UpdateMode18(void);

extern void SetN64_InitializeMode19(void);

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

extern void SetN64_DrawMode15Revision1(void);

extern void SetN64_UpdateMode15Revision1(void);

extern void SetN64_InitializeMode15Revision1(void);

extern void SetN64_InitializeMode15(void);

extern void SetN64_UpdateMode15(void);

extern void SetN64_DrawMode15(void);

extern void SetN64_DrawMode6(void);

extern void SetN64_AdvanceToModeEight(struct GameSession *session);

extern void SetN64_ResetMode11Items(s32 sessionAddress);

extern void SetN64_ResetMode9Items(s32 sessionAddress);

extern void SetN64_UpdateMode6(void);

extern void SetN64_DrawMode8Session(struct GameSession *session);

extern void SetN64_DrawMode9Session(void *session);

extern void SetN64_HandleMode7Transition(struct GameSession *session);

extern void SetN64_UpdateMode8(void);

extern void SetN64_ResetMode4Effects(void);

extern void SetN64_ResetMode5Items(s32 sessionAddress);

extern void SetN64_SetMode7AudioState(void);

extern void SetN64_InitializeMode6(void);

extern void SetN64_DrawMode4Backdrop(void);

extern void SetN64_DrawTextLines(void *state, s32 drawBackdrop, char **lines, s32 screenX, s32 screenY, s32 lineStep, f32 scaleX, f32 scaleY);

extern void SetN64_EmptySessionHookDeA(void);

extern void SetN64_EmptySessionHookRev1A(void);

extern void SetN64_EmptySessionHookRev1C(void);

extern void SetN64_EmptySessionHookRev1B(void);

extern void SetN64_EnterPendingSessionMode(void *gameSession);

extern void SetN64_InitializeMode16Credits(s32 sessionAddress);

extern void SetN64_InitializeMode17Credits(s32 sessionAddress);

extern void SetN64_InitializeTransitionMode(void);

extern void SetN64_GetRecordOutputs(void *source, int *word, float *third, float *fourth, float *second);

extern void SetN64_EmptyFrameDirectionHookUs(void);

extern void SetN64_EmptyFrameDirectionHookEu(void);

extern void SetN64_EmptyFrameDirectionHookSecondEu(void);

extern void SetN64_EmptyFrameDirectionHookSecondUs(void);

extern void SetN64_EmptySessionHookSecondEuX(void);

struct RoundSessionItemStateView {
    char pad0[0x26DB8];
    s32 reservedWord;
    char pad26DB8[0x1C];
    s32 selectionKeyBase;
};

extern void SetN64_ResetMode10Items(s32 sessionAddress);

extern void SetN64_DrawMode11Session(void *session);

extern void SetN64_DrawMode10Session(void *session);

extern void SetN64_DrawMode12Session(void *session);

extern void SetN64_ResetMode12Items(int sessionAddress);

/* The loading-screen setup routine and the view-matrix array it fills sit at different addresses in each cartridge. */
#if defined(VERSION_DE)
#define LOAD_SETUP SetN64_SetupLoadingBackdropDe
#define VIEW_MATRICES g_loadingViewMatricesDe
#else
#define LOAD_SETUP SetN64_SetupLoadingBackdropRev1
#define VIEW_MATRICES g_loadingViewMatricesUsRev1
#endif

extern u8 VIEW_MATRICES[];

struct ActorPoolFreeListView {
    char pad0[0x3C00];
    void * freeHead;
    char pad3C00[0x3C04 - 0x3C00 - sizeof(void*)];
    void * next;
    char pad3C04[0x3C08 - 0x3C04 - sizeof(void*)];
    void * activeTail;
};

struct VisibleEffectNodeLinks {
    char pad0[0x1C8];
    s32 clearedWord;
    char pad1C8[0x1D0 - 0x1C8 - sizeof(s32)];
    s32 flags;
    char pad1D0[0x1D8 - 0x1D0 - sizeof(s32)];
    void * previous;
    char pad1D8[0x1DC - 0x1D8 - sizeof(void*)];
    void * next;
};

struct VisibleEffectPoolView {
    char pad0[0x3C04];
    struct NodeSetN64CollectVisibleEffectNodes *head;
};

extern void Cache_RunCompactionPasses(s32);

extern void *SetN64_GetPackSection(void *table, s32 index);

extern s32 SetN64_GetPackSectionOffsetAndSize(s32 directoryAddress, s32 sectionIndex, s32 *sectionSizeOut);

extern void SetN64_GetPackBaseAndSize(int *directory, int * *packBaseOut, int *packSizeOut);

extern int SetN64_GetRecordBlockSize(int *recordHeader);

extern void SetN64_GetChunkStorage(void *, void * *, s32 *);

extern void *SetN64_GetChunkPayload(int *, int *);

extern void SetN64_TransposeRecords(void *sourceBlock, void *destinationBlock, s32 copyBack);

extern void SetN64_UpdateEffectPool(EffectSlotPool *world);

extern void SetN64_InitializeEffectSlot(struct EffectSlot *effectSlot);

extern void SetN64_UpdateEffectMotionAndBounds(SceneEffect *effect);

extern void SetN64_DrawVisibleEffects(char *effectPool, char *view);

extern void *SetN64_AllocateActorFromPool(ActorPoolFreeListView *);

extern void SetN64_BeginFrameDisplayList(void *world);
struct GameSession;
extern void SetN64_RunGameLoop(struct GameSession *session);
#endif
