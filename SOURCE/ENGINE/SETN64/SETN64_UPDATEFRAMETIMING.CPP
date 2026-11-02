#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/SHARED_MENUREPLY.H"
#include "COMMON/UNSIGNED_QUOTIENT.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/TRIPLE.H"
#include "ENGINE/SETN64.H"
#include "RENDER/SETN64_UPDATEFADETRANSITION.H"


#if defined(VERSION_DE)
extern f32 g_systemTimeFrameRateDe;
#endif
static inline u32 averageFour(void) {
 s32 sum;
 s32 maximum;
 sum=g_lastFrameRetraceCount+g_previousFrameRetraceCount+g_secondPreviousFrameRetraceCount+g_thirdPreviousFrameRetraceCount;
 maximum=g_thirdPreviousFrameRetraceCount;
 if((u32)maximum<g_secondPreviousFrameRetraceCount)maximum=g_secondPreviousFrameRetraceCount;
 if((u32)maximum<g_previousFrameRetraceCount)maximum=g_previousFrameRetraceCount;
 if((u32)maximum<g_lastFrameRetraceCount)maximum=g_lastFrameRetraceCount;
 { s32 adjusted=maximum-2; return ((u32)sum-(u32)adjusted)/3; }
}
static inline s32 idlePause(TimingWorld *world) {
 if(Menu_CountLiveNodes(&g_matchEndingTeamWheelClose)==0 && Cinema_IsSequenceInWindow()!=0 && Cinema_GetSequenceRequest()==120) {
 if(g_gameSettings.counters.first==0) {
 if(world->menuNodeCount==0) { g_gameSettings.counters.first=1;Track_RequestCameraRefresh(); }
 goto checkFlag;
 }
 goto active;
 }
 checkFlag:
 if(g_gameSettings.counters.first!=0) {
 active:
 if(Cinema_GetPlaybackPauseState()!=0) return 1;
 }
 return 0;
}
/* Update the frame timestep, render the frame, and advance the session mode. */
void SetN64_UpdateFrameTiming(TimingWorld *world) {
    f32 scaledFrameTime;
    f32 unusedTimingFloat1;
    s32 unusedTimingWord2;
    s32 unusedTimingWord3;
    s32 unusedTimingWord4;
    s32 unusedTimingWord5;
    s32 unusedTimingWord6;
    s32 unusedTimingWord7;
    s32 unusedTimingWord8;
    s32 unusedTimingWord9;
    s32 idle;
    u32 unusedTimingWord10;
    u32 unusedTimingWord11;
    u32 unusedTimingWord12;
    u32 sessionMode;
    u32 unusedTimingWord13;
    u32 unusedTimingWord14;
    u32 unusedTimingWord15;
    u32 unusedTimingWord16;
    u32 unusedTimingWord17;
    u32 unusedTimingWord18;
    u64 nowTicks;
    u64 elapsedUnits;
    u64 unusedTimingTicks19;

    nowTicks = osGetTime();
    elapsedUnits = __udivdi3((nowTicks-g_previousFrameSystemTime)<<6,3000);
#if defined(VERSION_DE)
    scaledFrameTime = (f32)elapsedUnits * g_systemTimeFrameScale * g_systemTimeFrameRateDe;
#else
    scaledFrameTime = (f32)elapsedUnits * g_systemTimeFrameScale * g_systemTimeFrameRate;
#endif
    g_previousFrameSystemTime = nowTicks;
    if (Tsmos_IsFrontendActive() == 0) {
        if (SetN64_IsModeThirteen() == 0) {
            world->menuNodeCount = 0;
        } else {
            world->menuNodeCount = Menu_CountLiveNodes(&world->viewport.self.messageList.head);
        }
    }
    if (g_initialMatchStartPending != 0) {
        sessionMode = world->currentMode;
        if (sessionMode == 11) {
            world->menuNodeCount = 1;
            goto block_10;
        }
    } else {
block_10:
        sessionMode = world->currentMode;
    }
 switch(sessionMode) { case 1: case 3: case 4: {
 g_frameTimingTicks=averageFour()>1 ? averageFour():2;
 break; } default: {
 g_frameTimingTicks=averageFour()>1 ? averageFour():2;
 if(Cinema_IsSequenceInWindow()!=0) {
 if((u32)(world->currentMode-16)<2 && g_hudReferenceViewportHeight<223) {
 g_frameTimingTicks=averageFour()>1 ? averageFour():2;
 } else {
 g_frameTimingTicks=averageFour()>3 ? averageFour():4;
 }
 }
 }
 }
    g_frameElapsedTime = (f32) (g_frameTimingTicks * 15) / g_displayedFramebufferAndRefreshRate[1];
    if (Cinema_IsSequenceInWindow() != 0) {
        g_frameElapsedTime = scaledFrameTime;
    }
#if defined(VERSION_DE)
    if (Cinema_IsSequenceInWindow() != 0) {
        g_frameElapsedTime = g_frameElapsedTime * g_systemTimeFrameRate;
    }
#endif
    Cache_RunCompactionPasses(0);
    g_currentTaskFrame = g_gameSession.ring.current;
    SetN64_BuildAndSubmitSessionFrame(world);
    world->elapsedTime = world->elapsedTime + g_frameElapsedTime;
    SetN64_AdvanceGameClock(world);
    idle=idlePause(world);
    if ((idle != 0) && (world->currentMode != 16) && (world->pendingMode != 16)) {
        world->fadeMode = 2;
        world->pendingMode = 16;
    }
}
