#include "thread_queue.h"
#include "include_asm.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "Common/manager.h"
#include "Common/aiprofile.h"
#include "Common/heap_arena.h"
#include "Texture/cache_recycleloadrequest.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Ui/X_files/x_plus.h"
#include "Engine/Cache/decmprsr.h"
#include "PR/os_message.h"
#include "Camera/ccinema_updatesequence.h"

/* DECMPRSR.CPP */

void Cache_StartResourceLoadWorker(ResourceLoadWorker *worker, s32 id) {
    osCreateMesgQueue(&worker->requests, worker->messages, 128);
    XPlus_FillMemory(worker->stack, id, 0x1000);
    osCreateThread(worker, id, &addrLow_Cache_RunResourceLoadWorker, worker,
        worker->stack + sizeof(worker->stack), g_resourceLoadIdlePriority);
    osStartThread(worker);
}

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
