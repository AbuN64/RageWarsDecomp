#include "include_asm.h"
#include "COMMON/LONE/RESOURCE_REQUEST_QUEUE.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/PAKQUEUESTATE.H"
#include "COMMON/WORLDSORTENTRY.H"
#include "TYPES.H"
#include "../../include/SCHED/osscremoveclient.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

#if defined(VERSION_EU)
#include "COMMON/OSVISCALE.H"
extern s32 g_schedulerFrameCountdown, g_frontendCurrentVideoModeIndex;
extern OSViMode g_schedulerAlternateVideoMode, g_videoModeLabels;
extern void Sched_HandleRetrace(OSSched *);
extern void Frontend_UpdateScreenMode(void);
extern void Sched_HandleRdpCompletion(OSSched *);
extern void SoundElement_FadeOutMusic(void);
extern void *SoundVoicePool_GetGlobalState(void);
extern void SoundVoicePool_StopAll(void *);
extern void Sched_HandleTaskCommands(OSSched *);

void Sched_RunEventLoopEu(OSSched *sc) {
    void *msg;
    OSScClientWork *client;
    OSViMode *mode;
    for (;;) {
        osRecvMesg(&sc->interruptQ, &msg, 1);
        switch ((s32)msg) {
        case 0x29A:
            if (g_schedulerShutdownPending && --g_schedulerFrameCountdown <= 0) {
                osViSetYScale(g_schedulerVideoYScale);
                mode = &g_schedulerAlternateVideoMode;
                if (g_frontendCurrentVideoModeIndex == 0) mode = &g_videoModeLabels;
                osViSetMode(mode);
                osViBlack(1);
                osViSetSpecialFeatures(2);
                for (;;) {}
            }
            Sched_HandleRetrace(sc);
            Frontend_UpdateScreenMode();
            break;
        case 0x29B: Sched_HandleRspCompletion(sc); break;
        case 0x29C: Sched_HandleRdpCompletion(sc); break;
        case 0x29D:
            SoundElement_FadeOutMusic();
            SoundElement_StopAudioExceptKey(-1);
            SoundVoicePool_StopAll(SoundVoicePool_GetGlobalState());
            client = sc->clientList;
            g_schedulerShutdownPending = 1;
            g_schedulerFrameCountdown = 20;
            while (client) {
                osSendMesg(client->queue, &sc->retraceMsg, 0);
                client = client->next;
            }
            break;
        case 6: Sched_HandleTaskCommands(sc); break;
        }
    }
}
#endif










extern s32 g_resourceLoadPriorityBoost, g_resourceLoadIdlePriority, g_renderFrameBufferCount;
extern s32 g_schedulerFrameQueueReadIndex, g_schedulerRetracesSinceSwap, g_schedulerPendingFramebuffer, g_displayedFramebufferAndRefreshRate, g_schedulerSwapPending, g_schedulerQueuedFrameCount;
#include "COMMON/DISPLAY.H"




/** Handle one scheduler retrace, recover a lost yielded-task completion, and notify clients. */
void Sched_HandleRetrace(OSSched *sc) {
    OSScTask *event = 0;
    s32 value1 = 0;
    s32 value2 = 0;
    s32 flags;
    OSScTask *pending;
    OSScClientWork *work;
    Frame *schedule;

    if (g_resourceLoadPriorityBoost != 0) {
        g_resourceLoadPriorityBoost--;
        if (g_resourceLoadPriorityBoost == 0) osSetThreadPri(&g_resourceCacheWorker, g_resourceLoadIdlePriority);
    }
    sc->frameCount++;
    while (osRecvMesg(&sc->cmdQ, &event, 0) != -1) __scAppendList(sc, event);
    g_schedulerRetracesSinceSwap++;
    if (g_schedulerSwapPending != 0) {
        g_schedulerRetracesSinceSwap = 0;
        g_schedulerSwapPending = 0;
        g_displayedFramebufferAndRefreshRate = g_schedulerPendingFramebuffer;
        g_schedulerPendingFramebuffer = 0;
    }
    if (g_schedulerQueuedFrameCount != 0) {
        schedule = g_schedulerFramebufferSchedule[g_schedulerFrameQueueReadIndex];
        if ((u32)(g_schedulerRetracesSinceSwap + 1) >= schedule->ticks) {
            g_schedulerPendingFramebuffer = (s32)schedule->colorImage;
            osViSwapBuffer((s32)schedule->colorImage);
            g_schedulerQueuedFrameCount--;
            g_schedulerSwapPending++;
            g_schedulerFrameQueueReadIndex++;
            if ((u32)g_schedulerFrameQueueReadIndex >= (u32)g_renderFrameBufferCount) g_schedulerFrameQueueReadIndex = 0;
        }
    }
    if (sc->curRSPTask == 0 && sc->curRDPTask == 0) {
        pending = sc->gfxListHead;
        if (pending != 0 && pending->list.t.type == 1 && pending->state == 0x32) {
            pending->state = 2;
            sc->curRSPTask = sc->gfxListHead;
            sc->gfxListHead = sc->gfxListHead->next;
            if (sc->gfxListHead == 0) sc->gfxListTail = 0;
            Sched_HandleRspCompletion(sc);
        }
    }
    g_schedulerRetraceCount++;
    if (g_schedulerRetraceCount == 0x4B0) *(char *)0 = 0;
    if (sc->doAudio != 0 && sc->curRSPTask != 0) __scYield(sc);
    else {
        flags = (sc->curRSPTask == 0) * 2 | (sc->curRDPTask == 0);
        if (((s32 (*)(void *, s32 *, s32 *, s32))Sched_SelectRunnableTasks)(sc, &value1, &value2, flags) != flags) ((void (*)(void *, s32, s32))Sched_StartSelectedTasks)(sc, value1, value2);
    }
    work = sc->clientList;
    while (work != 0) {
        if (work->queue->validCount < 2) osSendMesg(work->queue, sc, 0);
        work = work->next;
    }
    Control_PollControllerPaks();
}
