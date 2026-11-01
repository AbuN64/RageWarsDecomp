#ifndef ENGINE_SCHED_H
#define ENGINE_SCHED_H
#include "TYPES.H"
extern f32 g_schedulerAccumulatedGraphicsRspDuration;

struct SchedulerCommandQueueView {
    char pad0[0x78];
    char commandQueue;
};
#endif
