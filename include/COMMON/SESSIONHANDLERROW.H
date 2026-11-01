#ifndef COMMON_SESSIONHANDLERROW_H
#define COMMON_SESSIONHANDLERROW_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include <ultra64.h>
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/WORLDSORTENTRY.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/DISPLAY.H"
#include "COMMON/TEXTLAYERMETRICS.H"
#include "PFS/OVLGAME_INITIALIZERENDERDIRECTION.H"



struct SessionPlayerItemResetView;
typedef struct SessionPlayerItemResetView SessionPlayerItemResetView;






struct SessionPlayerItemResetView;


extern int g_bootstrapThreadPriority;


extern int g_videoFrameSchedulingMode;



#include "COMMON/DISPLAY.H"





extern int g_gameThreadPriority;

extern int g_sessionUpdateCount;




#include "COMMON/RENDERCOUNTERS.H"

extern char g_gameSchedulerMessages[];

extern Gfx *g_displayListCursor;
extern s32 g_schedulerThreadPriority;
extern u32 g_renderFrameBufferCount;
extern void *g_colorImageBuffers[];
extern void Sched_InitializeSchedulerThread(Panel *, s32, s32, s32, u8);
#include "SCHED/osscremoveclient.H"
extern void Items_ResetGameOptions(struct COptions *options);

typedef Node_Pak_CountLiveNodes TimingQueue;
typedef struct TimingWorld {
 char pad0[0x255C8];
 RaceViewportState viewport;
 char pad267C8[0x5E8]; f32 elapsedTime;
 s32 previousMode; u32 currentMode,pendingMode;
 u8 fadeFast; u8 fadeMode;
 char pad26DC2[2]; f32 fade;
 char pad26DC8[0xC]; s32 menuNodeCount;
} TimingWorld;
/* Drawing callback followed by the remaining two state-dispatch slots. */
typedef struct FrameCallback {
 void (*draw)(TimingWorld *);
 void (*auxiliary0)(TimingWorld *);
 void (*auxiliary1)(TimingWorld *);
} FrameCallback;
extern FrameCallback g_sessionDrawHandlers[];
extern s32 Cinema_GetSequenceRequest(void);
extern u32 Cinema_GetPlaybackPauseState(void);
extern s32 Menu_CountLiveNodes(Node_Pak_CountLiveNodes **);
struct GameSession;
extern void SetN64_AdvanceGameClock(struct GameSession *);
extern void Track_RequestCameraRefresh(void);
extern u32 g_previousFrameRetraceCount;
extern u32 g_secondPreviousFrameRetraceCount;
extern u32 g_thirdPreviousFrameRetraceCount;
extern u32 g_lastFrameRetraceCount;
extern f32 g_displayedFramebufferAndRefreshRate[2];
extern TimingQueue *g_matchEndingTeamWheelClose;

extern u32 g_maximumDisplayListBytes;
extern f32 rwFrameBuildSeconds;
extern f32 g_sessionFrameFadeMaximum;
extern void Cache_SelectResourceSlot(s32,s32);
extern void SetN64_CommitSessionInputs(void *);

extern int Control_IsSnapshotActive(void);

extern char g_buildVersionTextBuffer[];
extern char g_buildVersionFormat[];
extern const char g_buildDateTimeTextRev1[];
extern char g_buildVersionSuffix[];

extern void SetN64_SelectSpawnAfterCredits(void *session, s32 selectionValues);

#endif
