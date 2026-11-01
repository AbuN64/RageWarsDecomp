#ifndef SCHED_OSSCREMOVECLIENT_H
#define SCHED_OSSCREMOVECLIENT_H
#include "COMMON/WORLDSORTENTRY.H"
extern OSSched g_systemScheduler;
extern OSMesgQueue g_gameSchedulerMessageQueue;
extern OSScClientWork g_gameSchedulerClient;
extern int Sched_GetInterruptQueueAddress(int scheduler);
extern void *Sched_GetTaskWithAvailableFramebuffer(struct OSScTask_s *scheduler);
extern void *Sched_GetCommandQueue(void *object);
extern s32 Sched_SelectRunnableTasks(OSSched *, struct OSScTask_s **, struct OSScTask_s **, s32);
extern void Sched_StartSelectedTasks(OSSched *, struct OSScTask_s *, struct OSScTask_s *);
extern s32 Sched_CompleteTaskAndSwapBuffer(void *,void *);
#endif
