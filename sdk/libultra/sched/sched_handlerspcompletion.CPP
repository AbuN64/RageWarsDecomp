#include "include_asm.h"
#include "types.h"
#include <platform_sdk.h>
#include "Common/runtime_declarations.h"
#include "Common/os_timer_interrupt_internals.h"
#include "Common/unsigned_quotient.h"
#include "Common/worldsortentry.h"
#include "Common/sessionhandlerrow.h"
#include "Common/triple.h"
#include "Scene/cache_sendcompletionmessage.h"
#include "../../include/SCHED/osscremoveclient.H"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

#include "Common/game_session.h"
void Sched_HandleRspCompletion(void *object) {
 OSSched *scheduler=object;
 OSScTask *nextRsp,*nextRdp;
 OSScTask *task;
 Frame *frame;
 u64 elapsed;
 f32 duration1,duration2,duration3,duration4;
 s32 flags,taskState;
 task=scheduler->curRSPTask;
 scheduler->curRSPTask=0;
 taskState=task->state;
 nextRsp=0;nextRdp=0;
 if((taskState&0x10)&&osSpTaskYielded(&task->list)) {
  task->state|=0x20;
  if((task->flags&7)==3) {
   task->next=scheduler->gfxListHead;
   scheduler->gfxListHead=task;
   if(!scheduler->gfxListTail) scheduler->gfxListTail=task;
  }
  if(task->flags&0x20) {
   elapsed=((osGetTime()-g_schedulerGraphicsTaskStartTime)<<6)/3;
   duration1=(f32)elapsed;
   g_schedulerAccumulatedGraphicsRspDuration+=duration1*g_schedulerRspDurationScales[0];
  }
 } else {
  task->state&=~2;
  if(task->list.t.type==1) {
   g_schedulerRetraceCount=0;
   if(task->flags&0x20) {
    elapsed=((osGetTime()-g_schedulerGraphicsTaskStartTime)<<6)/3;
    duration2=(f32)elapsed;
    g_schedulerAccumulatedGraphicsRspDuration=g_schedulerAccumulatedGraphicsRspDuration+duration2*g_schedulerRspDurationScales[1];
    g_schedulerAudioDuration=g_schedulerAccumulatedGraphicsRspDuration;
    elapsed=((osGetTime()-g_schedulerAudioTaskStartTime)<<6)/3;
    duration3=(f32)elapsed;
    g_schedulerTaskDuration=duration3*g_schedulerRspDurationScales[2];
    frame=g_gameSession.ring.frames;
    if(task->framebuffer!=frame[0].colorImage) {
     if(task->framebuffer==frame[1].colorImage) frame+=1;
     else if(task->framebuffer==frame[2].colorImage) frame+=2;
    }
    Cache_SendCompletionMessage(0,frame->commands==g_displayListBuffers[1]);
    if(osSendMesg(task->msgQ,task->msg,1)==-1) *((char *)NULL)=0;
   }
  } else {
   elapsed=((osGetTime()-g_schedulerAudioTaskStartTime)<<6)/3;
   duration4=(f32)elapsed;
   g_schedulerTaskDuration=duration4*g_schedulerRspDurationScales[3];
   if(osSendMesg(task->msgQ,task->msg,1)==-1) *((char *)NULL)=0;
  }
  Sched_CompleteTaskAndSwapBuffer(scheduler,task);
 }
 flags=((scheduler->curRSPTask==0)<<1)|(scheduler->curRDPTask==0);
 if(Sched_SelectRunnableTasks(scheduler,&nextRsp,&nextRdp,flags)!=flags) Sched_StartSelectedTasks(scheduler,nextRsp,nextRdp);
}

/* Mechanically ported from github/legacy:src/Sched_HandleRdpCompletion_SchedHandlerspcompletion.c by address. */
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/worldsortentry.h"
#include "Common/frame_direction.h"
#include "Common/sessionhandlerrow.h"
#include "Common/triple.h"
#include "Sched/sched_handlerspcompletion.h"


extern u32 g_schedulerRetracesSinceSwap;

extern s32 g_schedulerPendingFramebuffer;

extern s32 g_schedulerSwapPending;

extern s32 g_schedulerQueuedFrameCount;

extern u32 g_schedulerFrameQueueWriteIndex;

void Sched_HandleRdpCompletion(OSSched *sc)
{
    s32 value1 = 0;
    s32 value2 = 0;
    OSScTask *task = sc->curRDPTask;
    void *framebuffer;
    Frame *schedule;
    Frame *schedules;
    s32 flags;
    task->state &= ~1;
    if (task->list.t.type == 1) {
        if ((task->flags & 0x20) != 0) {
            g_schedulerElapsedFrameDuration = (f32)(((osGetTime() - g_schedulerRdpTaskStartTime) << 6) / 3) * g_schedulerElapsedDurationScale;
        }
        sc->curRDPTask = 0;
        if ((task->flags & 0x20) != 0) {
            schedules = g_gameSession.ring.frames;
            framebuffer = task->framebuffer;
            if (framebuffer == schedules[0].colorImage) {
                schedule = &schedules[0];
            } else if (framebuffer == schedules[1].colorImage) {
                schedule = &schedules[1];
            } else if (framebuffer == schedules[2].colorImage) {
                schedule = &schedules[2];
            } else {
                schedule = &schedules[0];
            }
            g_thirdPreviousFrameRetraceCount = g_secondPreviousFrameRetraceCount;
            g_secondPreviousFrameRetraceCount = g_previousFrameRetraceCount;
            g_previousFrameRetraceCount = g_lastFrameRetraceCount;
            g_lastFrameRetraceCount = g_schedulerRetracesSinceSwap + 1;
            if (g_lastFrameRetraceCount >= schedule->ticks && g_schedulerQueuedFrameCount == 0 && g_schedulerSwapPending == 0) {
                g_schedulerPendingFramebuffer = (s32)schedule->colorImage;
                osViSwapBuffer((s32)schedule->colorImage);
                g_schedulerSwapPending++;
            } else {
                g_schedulerQueuedFrameCount++;
                g_schedulerFramebufferSchedule[g_schedulerFrameQueueWriteIndex] = schedule;
                g_schedulerFrameQueueWriteIndex++;
                if (g_schedulerFrameQueueWriteIndex >= g_renderFrameBufferCount) {
                    g_schedulerFrameQueueWriteIndex = 0;
                }
            }
            SetN64_OnFrameComplete(schedule);
        }
    }
    Sched_CompleteTaskAndSwapBuffer(sc, task);
    flags = (sc->curRSPTask == 0) * 2 | (sc->curRDPTask == 0);
    if (Sched_SelectRunnableTasks(sc, &value1, &value2, flags) != flags) {
        Sched_StartSelectedTasks(sc, value1, value2);
    }
}
