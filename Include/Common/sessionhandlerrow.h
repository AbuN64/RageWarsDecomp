#ifndef COMMON_SESSIONHANDLERROW_H
#define COMMON_SESSIONHANDLERROW_H
#include "types.h"
#include <platform_sdk.h>
#include "Common/gameplay_camera.h"
#include "Common/resident_event_handler.h"
#include "Common/worldsortentry.h"
#include "Common/aiprofile.h"
#include "Common/display.h"
#include "Common/textlayermetrics.h"
#include "PFS/OVLGAME_INITIALIZERENDERDIRECTION.H"



struct FrameCallback;
typedef struct CMenu_t TimingQueue;
struct TimingWorld;
struct Panel;
struct SessionPlayerItemResetView;
typedef struct SessionPlayerItemResetView SessionPlayerItemResetView;






struct SessionPlayerItemResetView;


extern int g_bootstrapThreadPriority;





#include "Common/display.h"





extern int g_gameThreadPriority;

extern int g_sessionUpdateCount;




#include "Common/rendercounters.h"

extern char g_gameSchedulerMessages[];

extern Gfx *g_displayListCursor;
extern s32 g_schedulerThreadPriority;
extern u32 g_renderFrameBufferCount;
extern void *g_colorImageBuffers[];
extern void Sched_InitializeSchedulerThread(struct Panel *, s32, s32, s32, u8);
#include "SCHED/osscremoveclient.H"
struct COptions;
extern void Items_ResetGameOptions(struct COptions *options);

extern struct FrameCallback g_sessionDrawHandlers[];
extern s32 Cinema_GetSequenceRequest(void);
extern u32 Cinema_GetPlaybackPauseState(void);
extern s32 Menu_CountLiveNodes(struct CMenu_t **);
struct GameSession;
extern void SetN64_AdvanceGameClock(struct GameSession *);
extern void Track_RequestCameraRefresh(void);
extern u32 g_previousFrameRetraceCount;
extern u32 g_secondPreviousFrameRetraceCount;
extern u32 g_thirdPreviousFrameRetraceCount;
extern u32 g_lastFrameRetraceCount;
extern f32 g_displayedFramebufferAndRefreshRate[2];
extern struct MessageList g_matchEndingTeamWheelClose;

extern f32 rwFrameBuildSeconds;
extern f32 g_sessionFrameFadeMaximum;
extern void Cache_SelectResourceSlot(s32,s32);
extern void SetN64_CommitSessionInputs(void *);

extern int Control_IsSnapshotActive(void);

extern char g_buildVersionTextBuffer[];
extern char g_buildVersionFormat[];
extern const char g_buildTimestampText[];
extern char g_buildVersionSuffix[];

extern void SetN64_SelectSpawnAfterCredits(struct GameSession *scene, s32 spawnIndex);
extern u32 g_maximumDisplayListBytes;

#endif
