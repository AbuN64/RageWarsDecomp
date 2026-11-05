#ifndef ENGINE_SCHED_H
#define ENGINE_SCHED_H
#include "Common/sessionhandlerrow.h"
#include "types.h"
#include <PR/sched.h>
extern f32 g_schedulerAccumulatedGraphicsRspDuration;

extern void Sched_SendSchedulerTask(s32 schedulerAddress, s32 taskMessage);
extern s32 g_schedulerPendingFramebuffer;
#endif
