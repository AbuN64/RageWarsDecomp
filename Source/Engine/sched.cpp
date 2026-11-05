#include "thread_queue.h"
#include "include_asm.h"
#include "Common/worldsortentry.h"
#include "Common/vector4f.h"
#include "Common/runtime_declarations.h"
#include <platform_sdk.h>
#include "Common/osviscale.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "Common/lldivresult.h"
#include "types.h"
#include "Common/boot_tv_type.h"
#include "SCHED/osscremoveclient.H"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Engine/sched.h"
#include "Common/results.h"
#include "Common/world.h"
#include "Common/world_scene.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "SCHED/sched_runeventloopus.H"
#include "Render/setn64_getpacksection.h"
#if defined(VERSION_US)
#include "Common/boot_memory_and_thread_boundaries.h"
#endif
#if defined(VERSION_US)
#include "Sched/sched_handleretrace.h"
#endif
#if defined(VERSION_US)
#include "Sched/sched_handlerspcompletion.h"
#endif
#if defined(VERSION_US)
#include "Sched/sched_handletaskcommands.h"
#endif
#if defined(VERSION_US)
#include "Common/runtime_declarations.h"
#endif
#if defined(VERSION_US)
#include "Frontend/screen.h"
#endif
#if defined(VERSION_US)
#include "Engine/Audio/T2soundelement/sound_context_control.h"
#endif
#if defined(VERSION_US)
#include "Engine/Audio/voice.h"
#endif
#if defined(VERSION_US)
#include "Voice/voice.h"
#endif

/* SCHED_SELECTRUNNABLETASKS.CPP */
/* Initialises a panel: marks it active, clears its counters, lays out its two eight-slot rows, binds text 0x29B to 0x29D and 0x29A with the given style byte to the first row, and builds its element list from the PanelElementTemplate template. */

s32 Sched_SelectRunnableTasks(OSSched *scheduler, OSScTask **rspTaskOut, OSScTask **rdpTaskOut, s32 processorMask) {
    OSScTask *gfxListHead;
    OSScTask *audioListHead;
    OSScTask *next;
    OSScTask *runnableGraphicsTask;
    s32 initialProcessorMask;
    s32 graphicsTaskFlags;
    s32 state;
    s32 availableProcessors;

    availableProcessors = processorMask;
    gfxListHead = scheduler->gfxListHead;
    audioListHead = scheduler->audioListHead;
    initialProcessorMask = availableProcessors;
    if ((scheduler->doAudio != 0) && (availableProcessors & 2)) {
        if ((gfxListHead == 0) || !(gfxListHead->flags & 0x10)) {
            *rspTaskOut = audioListHead;
            scheduler->doAudio = 0;
            next = scheduler->audioListHead->next;
            availableProcessors &= ~2;
            scheduler->audioListHead = next;
            if (next == 0) {
                scheduler->audioListTail = 0;
            }
        } else {
            *rspTaskOut = gfxListHead;
            availableProcessors &= ~2;
        }
    } else {
        if (gfxListHead == 0) {
            runnableGraphicsTask = 0;
        } else if ((s32)gfxListHead->framebuffer == g_displayedFramebufferAndRefreshRate) {
            runnableGraphicsTask = 0;
        } else if (gfxListHead->framebuffer == osViGetCurrentFramebuffer()) {
            runnableGraphicsTask = 0;
        } else if ((s32)gfxListHead->framebuffer == g_schedulerPendingFramebuffer) {
            runnableGraphicsTask = 0;
        } else {
            runnableGraphicsTask = gfxListHead;
        }
        if (runnableGraphicsTask != 0) {
            graphicsTaskFlags = gfxListHead->flags & 7;
            switch (graphicsTaskFlags) {
            case 1:
            case 4:
            case 5:
                break;
            case 3:
                if (gfxListHead->state & 0x20) {
                    if (availableProcessors & 2) {
                        *rspTaskOut = gfxListHead;
                        availableProcessors &= ~2;
                        if (gfxListHead->state & 1) {
                            *rdpTaskOut = gfxListHead;
                            availableProcessors &= ~1;
                        }
                        scheduler->gfxListHead = scheduler->gfxListHead->next;
                        if (scheduler->gfxListHead == 0) {
                            scheduler->gfxListTail = 0;
                        }
                    }
                } else if (availableProcessors == 3) {
                    *rdpTaskOut = gfxListHead;
                    *rspTaskOut = gfxListHead;
                    scheduler->gfxListHead = scheduler->gfxListHead->next;
                    availableProcessors = 0;
                    if (scheduler->gfxListHead == 0) {
                        scheduler->gfxListTail = 0;
                    }
                }
                break;
            case 2:
            case 6:
            case 7:
                state = gfxListHead->state;
                if (state & 2) {
                    if (availableProcessors & 2) {
                        *rspTaskOut = gfxListHead;
                        availableProcessors &= ~2;
                    }
                } else if ((state & 1) && (availableProcessors & 1)) {
                    *rdpTaskOut = gfxListHead;
                    scheduler->gfxListHead = scheduler->gfxListHead->next;
                    availableProcessors &= ~1;
                    if (scheduler->gfxListHead == 0) {
                        scheduler->gfxListTail = 0;
                    }
                }
                break;
            }
        }
    }
    if (availableProcessors != initialProcessorMask) {
        availableProcessors = Sched_SelectRunnableTasks(scheduler, rspTaskOut, rdpTaskOut, availableProcessors);
    }
    return availableProcessors;
}

void Sched_InitializeSchedulerThread(Panel *panel, s32 threadStack, s32 priority, s32 unusedVideoMode, unsigned char style) {
    panel->active = 1;
    panel->curRSPTask = 0;
    panel->curRDPTask = 0;
    panel->clientList = 0;
    panel->frameCount = 0;
    panel->audioListHead = 0;
    panel->gfxListHead = 0;
    panel->audioListTail = 0;
    panel->gfxListTail = 0;
    panel->doAudio = 0;
    panel->mode = 4;
    osCreateMesgQueue(panel->row0, panel->row0Slots, 8);
    osCreateMesgQueue(panel->row1, panel->row1Slots, 8);
    osSetEventMesg(4, panel->row0, 667);
    osSetEventMesg(9, panel->row0, 668);
    osSetEventMesg(14, panel->row0, 669);
    osViSetEvent(panel->row0, 666, style);
    osCreateThread(panel->elements, 7, &g_schedulerThreadEntryAddress, panel, threadStack, priority);
    osStartThread(panel->elements);
}

/* SCHED_GETCOMMANDQUEUE.CPP */
/** Return the scheduler command queue. */
void *Sched_GetCommandQueue(void *storage) {
    OSSched *object = storage;
    return &object->cmdQ;
}

/* SCHED.CPP */
/* Switches a view to a new current and next scene: stamps the time of a pending next scene, starts the current scene (resetting its timer for mode 2, and stamping its start and, unless flagged 0x10, its first-start time for flag 0x20), clears its flags 0x30, runs its start and update hooks and records it, then when the next scene differs starts its music at its time and records it. */
void Sched_StartSelectedTasks(OSSched *view, OSScTask *current, OSScTask *next) {
    s64 now;

    if (next != 0 && (next->flags & 0x20) && !(next->state & 0x10)) {
        g_schedulerRdpTaskStartTime = osGetTime();
    }
    if (current != 0) {
        if (current->list.t.type == 2) {
            osWritebackDCacheAll();
            g_schedulerAudioTaskStartTime = osGetTime();
        } else if (current->flags & 0x20) {
            now = osGetTime();
            g_schedulerGraphicsTaskStartTime = now;
            if (!(current->state & 0x10)) {
                g_schedulerGraphicsInitialStartTime = now;
                g_schedulerAccumulatedGraphicsRspDuration = 0;
            }
        }
        current->state &= ~0x30;
        osSpTaskLoad((s32 *)&current->list.t.type);
        osSpTaskStartGo((s32 *)&current->list.t.type);
        view->curRSPTask = current;
        if (current == next) {
            view->curRDPTask = next;
        }
    }
    if (next != 0 && next != current) {
        osDpSetNextBuffer((s32)next->list.t.output_buff, *next->list.t.output_buff_size);
        g_schedulerRdpBufferSetFlag = 1;
        g_schedulerRdpBufferSetState = 0;
        view->curRDPTask = next;
    }
}

/* SCHED_SENDSCHEDULERTASK.CPP */

void Sched_SendSchedulerTask(s32 schedulerAddress, s32 taskMessage) {
  OSSched *scheduler = (OSSched *) schedulerAddress;
    osSendMesg(&scheduler->cmdQ, taskMessage, 1);
    osSendMesg(&scheduler->interruptQ, 6, 1);
}

/* sched_runeventloopus.CPP */
#if defined(VERSION_US)



void Sched_RunEventLoopUs(OSSched *sc) {
    void *msg;
    OSScClientWork *client;
    for (;;) {
        osRecvMesg(&sc->interruptQ, &msg, 1);
        switch ((s32)msg) {
        case 0x29A:
            if (g_schedulerShutdownPending && --g_schedulerFrameCountdown <= 0) {
                osViBlack(1);
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

/* S_SCHEDACCLAIMNETTEXT.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU)

unsigned int s_SchedACCLAIMNETText[3] = {
    0x3162FFFF, 0x00031C00, 0x00621825,
};
#endif
#if defined(VERSION_EU_X)
#if defined(VERSION_EU)
char s_SchedACCLAIMNETText[12] =
    ".ACCLAIM.NET";
#endif
#endif
#endif
