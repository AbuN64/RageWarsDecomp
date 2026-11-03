#include "thread_queue.h"
#include "include_asm.h"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/MANAGER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/ENTRYRECAT18V3.H"
#include "TEXTURE/CACHE_RECYCLELOADREQUEST.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "UI/X_FILES/X_PLUS.H"
#include "ENGINE/CACHE/DECMPRSR.H"

/* DECMPRSR.CPP */
void Cache_StartResourceLoadWorker(ResourceLoadWorker *worker, s32 id) {
    osCreateMesgQueue(&worker->requests, worker->messages, 128);
    XPlus_FillMemory(worker->stack, id, 0x1000);
    osCreateThread(worker, id, &g_Cache_RunResourceLoadWorkerPackedAddress24, worker,
                     worker->stack + sizeof(worker->stack), g_resourceLoadIdlePriority);
    osStartThread(worker);
}

extern s32 osJamMesg(OSMesgQueue *queue, void *message, s32 block);

s32 Cache_SubmitResourceLoadAndWait(ResourceLoadWorker *worker, ResourceLoadRequest *message) {
    OSMesgQueue completionQueue;
    s32 replyMessageStorage;
    void *completedRequest;
    s32 busyPriority;

    osCreateMesgQueue(&completionQueue, &replyMessageStorage, 1);
    busyPriority = g_resourceLoadBusyPriority;
    message->replyQueue = &completionQueue;
    g_resourceLoadPriorityBoost = 2;
    osSetThreadPri(worker, busyPriority);
    osJamMesg(&worker->requests, message, 1);
    osRecvMesg(&completionQueue, &completedRequest, 1);
    return 1;
}

s32 Cache_TrySubmitResourceLoad(ResourceLoadWorker *worker, ResourceRequest *request, void *replyQueue) {
    request->replyQueue = replyQueue;
    return ~osSendMesg(&worker->requests, request, 0) != 0;
}

s32 Cache_WaitForResourceLoads(ResourceLoadWorker *resourceLoadWorker) {
    if (resourceLoadWorker->requests.validCount != 0) {
        do {
            osSetThreadPri(resourceLoadWorker, g_resourceLoadBusyPriority);
        } while (resourceLoadWorker->requests.validCount != 0);
    }
    osSetThreadPri(resourceLoadWorker, g_resourceLoadIdlePriority);
}

#if defined(VERSION_US)
void Cache_RunResourceLoadWorkerUs(ResourceLoadWorker *worker)
{
    ResourceRequest *request;
    extern s32 g_gameFrameCounter;

    for (;;) {
        osRecvMesg(&worker->requests, (void **)&request, 1);
        worker->timestamp = g_gameFrameCounter;
        request->dispatch(request->argument, request);
        osSendMesg(request->replyQueue, request, 1);
    }
}
#endif

#if defined(VERSION_EU)
void Cache_RunResourceLoadWorkerEu(ResourceLoadWorker *worker)
{
    ResourceRequest *request;
    extern s32 g_gameFrameCounter;

    for (;;) {
        osRecvMesg(&worker->requests, (void **)&request, 1);
        worker->timestamp = g_gameFrameCounter;
        request->dispatch(request->argument, request);
        osSendMesg(request->replyQueue, request, 1);
    }
}
#endif

#if defined(VERSION_DE)
void Cache_RunResourceLoadWorkerDe(ResourceLoadWorker *worker)
{
    ResourceRequest *request;
    extern s32 g_gameFrameCounter;

    for (;;) {
        osRecvMesg(&worker->requests, (void **)&request, 1);
        worker->timestamp = g_gameFrameCounter;
        request->dispatch(request->argument, request);
        osSendMesg(request->replyQueue, request, 1);
    }
}
#endif

#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
void Cache_RunResourceLoadWorkerEuX(ResourceLoadWorker *worker)
{
    ResourceRequest *request;
    extern s32 g_gameFrameCounter;

    for (;;) {
        osRecvMesg(&worker->requests, (void **)&request, 1);
        worker->timestamp = g_gameFrameCounter;
        request->dispatch(request->argument, request);
        osSendMesg(request->replyQueue, request, 1);
    }
}
#endif
