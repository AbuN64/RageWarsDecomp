#include "PR/R4300.h"
#include "thread_queue.h"
#include "include_asm.h"
#include "Texture/cartridge_dma_and_audio_timing_views.h"
#include "Common/cartridgereadworker.h"
#include "types.h"
#include "Texture/audiomgr_initheap.h"
#include "Engine/Audio/AUDIOMGR.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Ui/X_files/x_plus.h"
#include "libgultra/alunlink.h"
#include "Data/Gfxdata/audio_decodeframe_data.h"
#include "Engine/Cache/decmprsr.h"
#include "Engine/Cache/heap.h"
#include "Engine/Cache/loader.h"
#include "Common/audio_initialize.h"
#include "Common/alauxbus_s.h"
#include "Common/effectrender.h"
#include "Common/Lone/resource_request_queue.h"
#include "Common/Lone/runtime_heap.h"
#include "Common/runtime_declarations.h"
#include "Common/controller_motor_state.h"
#include "Common/music_track_volume.h"
#include "Common/soundinfo.h"
#include "Common/sessionhandlerrow.h"
#include "Common/gumtxl2f.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "Common/lldivresult.h"
#include "System/sound_context_music_and_voice_control.h"
#include "System/sound_context_lock_and_activity.h"
#include "Common/triple.h"
#include "Engine/Audio/Audiomgr/audiomgr_worker_dma_and_frame.h"

/* AUDIOMGR.CPP */

/* Clears and sizes the runtime heap region against the detected RAM size, then initialises the
   five dependent subsystems over it. */

void Audiomgr_InitHeap(void) {
    u8 *heapStart;
    s32 heapEnd;
    s32 size;

    heapEnd = K0BASE + 0x400000;
    heapStart = g_runtimeHeapStart;
    if (Defs_GetMemorySize() != 0x400000) {
        heapEnd = Defs_GetMemorySize() | K0BASE;
    }

    size = heapEnd - (s32)heapStart;
    XPlus_FillMemory(heapStart, 0, size);
    Heap_InitializeArena(g_runtimeHeap, heapStart, size);
    Cache_StartResourceLoadWorker(g_resourceCacheWorker, 3);
    Cartridge_StartReadWorker(g_cartridgeReadWorker, 4);

#if defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    Vhandler_InitializePagerEuroExtended
#elif defined(VERSION_EU_X)
    Vhandler_InitializePagerEuroExtended
#else
    Vhandler_InitializePagerEuroExtended
#endif
    (0, 0);
    Cache_InitializeResourceCache(0, 5);
}


/* Reset the DMA cache, allocate sample/task buffers, then start the audio worker. */
void Audiomgr_InitializeAudioWorker(ALSynConfig *config, s32 priority, AudioInitializeTiming *timing) {
    u32 i;
    f32 samplesPerFrame;
    g_audioDmaState.initialized = 0;
    config->dmaproc = (void *)&g_audioDmaInitializerEntry;
    config->outputRate = osAiSetFrequency(timing->frequency);
    samplesPerFrame = (f32)timing->frameTime * config->outputRate * (1.0f / 60.0f);
    g_audioSamplesPerFrame = (s32)samplesPerFrame;
    if ((f32)g_audioSamplesPerFrame < samplesPerFrame) g_audioSamplesPerFrame++;
    if (g_audioSamplesPerFrame & 15) g_audioSamplesPerFrame = (g_audioSamplesPerFrame & ~15U) + 16;
    alInit(&g_audioSynthGlobals, config);
    g_audioDmaCacheEntries[0].prev = 0;
    g_audioDmaCacheEntries[0].next = 0;
    for (i = 0; i < 59; i++) {
        alLink(&g_audioDmaCacheEntries[i+1], &g_audioDmaCacheEntries[i]);
        g_audioDmaCacheEntries[i].buffer = alHeapDBAlloc(0, 0, config->heap, 1, 768);
    }
    g_audioDmaCacheEntries[i].buffer = alHeapDBAlloc(0, 0, config->heap, 1, 768);
    for (i = 0; i < 2; i++) g_audioCommandBuffers[i] = alHeapDBAlloc(0, 0, config->heap, 1, timing->samples * 8);
    g_audioCommandBufferSamples = timing->samples;
    for (i = 0; i < 3; i++) {
        g_audioFrameTasks[i] = alHeapDBAlloc(0, 0, config->heap, 1, sizeof(AudioWork));
        g_audioFrameTasks[i]->samples = alHeapDBAlloc(0, 0, config->heap, 1, g_audioSamplesPerFrame * 4);
        g_audioFrameTasks[i]->queue = &g_audioTaskCompletionQueue;
        g_audioFrameTasks[i]->message = g_audioFrameTasks[i];
        g_audioFrameTasks[i]->task.type = 2;
        g_audioFrameTasks[i]->task.boot = rspbootTextStart; g_audioFrameTasks[i]->task.bootSize = (u32)g_graphicsMicrocodeText - (u32)rspbootTextStart;
        g_audioFrameTasks[i]->task.flags = 0;
        g_audioFrameTasks[i]->task.code = g_audioMicrocodeText; g_audioFrameTasks[i]->task.codeSize = sizeof(g_audioMicrocodeText);
        g_audioFrameTasks[i]->task.codeData = g_audioMicrocodeData; g_audioFrameTasks[i]->task.codeDataSize = sizeof(g_audioMicrocodeData);
        g_audioFrameTasks[i]->task.yield = 0; g_audioFrameTasks[i]->task.yieldSize = 0;
        g_audioFrameTasks[i]->task.stack = 0; g_audioFrameTasks[i]->task.stackSize = 0;
        g_audioFrameTasks[i]->task.output = 0; g_audioFrameTasks[i]->task.outputSize = 0;
    }
    osCreateMesgQueue(&g_audioTaskCompletionQueue, g_audioTaskCompletionMessages, 10);
    osCreateMesgQueue(&g_audioWorkerEventQueue, g_audioWorkerEventMessages, 10);
    osCreateMesgQueue(&g_audioDmaCompletionQueue, g_audioDmaCompletionMessages, 60);
    osSetEventMesg(6, &g_audioWorkerEventQueue, 7);
    g_audioCacheCountdownHead = 0;
    g_audioHeap = config->heap;
    XPlus_FillMemory(g_audioWorkerStack, 8, sizeof(g_audioWorkerStack));
    osCreateThread(g_audioWorkerThread, 8, (void (*)(void))&g_audioWorkerEntry, 0, g_audioWorkerStack + sizeof(g_audioWorkerStack), priority);
    osStartThread(g_audioWorkerThread);
    osSendMesg(&g_audioWorkerEventQueue, (OSMesg)7, 0);
}

/* AUDIOMGR_WORKER_DMA_AND_FRAME.CPP */

void Audiomgr_RunAudioWorker(void) {
    u32 stop, argument, frame;
    u64 previous;
    OSScClientWork client;
    union { void *message; u32 words[2]; } event;
    CacheCountdownEntry *entry;
    void *entryObject;
    stop = 0;
    argument = stop;
    frame = stop;
    previous = 0;
    osScAddClient(&g_systemScheduler, &client, &g_audioWorkerEventQueue);
    do {
        g_audioWorkerElapsedTicks = ((osGetTime() - previous) << 6) / 3000ULL;
        osRecvMesg(&g_audioWorkerEventQueue, &event.message, 1);
        previous = osGetTime();
        switch (event.words[0]) {
        case 1:
            frame++;
            if (frame < 21) break;
            frame = 0;
        case 7:
            g_audioWorkerEventCount++;
            while (!(osAiGetStatus() & 0x80000000)) {
                Audiomgr_RenderAudioFrame(g_audioFrameTasks[g_audioTaskFrameIndex % 3], argument);
            }
            entryObject = g_audioCacheCountdownHead;
            for (entry = entryObject; entry; entry = entry->next) {
                if (entry->state) entry->state--;
            }
            break;
        case 4:
            break;
        }
    } while (stop == 0);
    alClose(&g_audioSynthGlobals);
}

s32 *Audiomgr_InitializeDmaState(s32 **dmaStateOutput) {
    if (g_audioDmaState.initialized == 0) {
        g_audioDmaState.firstFree = (struct Window *)&g_audioDmaCacheEntries;
        g_audioDmaState.firstUsed = 0;
        g_audioDmaState.initialized = 1U;
    }
    *dmaStateOutput = (s32 *)&g_audioDmaState;
    return &g_sound_GetSampleDmaWindowAddressEntry;
}

s32 Audiomgr_RenderAudioFrame(AudioFrameTask *audioTask, u32 workerArgument)
{
    s32 completed;
    s32 event;
    s32 value;
    void *item;
    Sound_RetireCompletedSampleWindows(audioTask);
    value = osVirtualToPhysical(audioTask->owner);
    audioTask->id = (u16)g_audioSamplesPerFrame;
    SoundElement_AcquireContextLock();
    item = alAudioFrame(g_audioCommandBuffers[g_audioCommandBufferIndex], &completed, value, audioTask->id);
    SoundElement_ReleaseContextLock();
    if (completed != 0)
    {
        audioTask->base = g_audioCommandBuffers[g_audioCommandBufferIndex];
        audioTask->offset = ((((s32) item) - ((s32) g_audioCommandBuffers[g_audioCommandBufferIndex])) >> 3) << 3;
        osWritebackDCacheAll();
        Sched_SendSchedulerTask(&g_systemScheduler, audioTask->payload);
        g_audioCommandBufferIndex ^= 1;
        SoundElement_UpdateContext();
        osRecvMesg(&g_audioTaskCompletionQueue, &event, 1);
        osAiSetNextBuffer(audioTask->owner, audioTask->id << 2);
        return 1;
    }
    if (completed || audioTask->id)
    {
        return 0;
    }
    else
    {
        return 0;
    }
}

/* AUDIOMGR_INIT.CPP */

#if defined(VERSION_US)
char s_AudiomgrInitIMsgTText[8] =
    "iMsgT\000\000@";
#endif

#if defined(VERSION_EU_X)
float k_AudiomgrInitConstants[2] = {
    1.0f, 1.0f,
};
#endif

#if defined(VERSION_DE)
float k_AudiomgrInit[2] = {
    0.5f, 127.0f,
};
#endif

#if defined(VERSION_US_REV1)
float g_AudiomgrInit[2] = {
    1.0f, 1.0f,
};
#endif
