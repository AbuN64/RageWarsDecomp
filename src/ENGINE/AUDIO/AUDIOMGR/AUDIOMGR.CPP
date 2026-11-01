#include "../../../../sdk/include/thread_queue.h"
#include "include_asm.h"
#include "TEXTURE/CARTRIDGE_DMA_AND_AUDIO_TIMING_VIEWS.H"
#include "COMMON/CARTRIDGEREADWORKER.H"
#include "TYPES.H"
#include "TEXTURE/AUDIOMGR_INITHEAP.H"
#include "ENGINE/AUDIO/AUDIOMGR.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "UI/X_FILES/X_PLUS.H"
#include "../../../../sdk/include/libgultra/alunlink.h"

/* Clears and sizes the 0x8016E000 heap region against the detected RAM size, then initialises the
   five dependent subsystems over it. */

extern u8 g_runtimeHeapStart[];
extern u8 g_runtimeHeap[];
extern u8 g_resourceCacheWorker[];
extern u8 g_cartridgeReadWorker[];

extern s32 Defs_GetMemorySize(void);
extern void Heap_InitializeArena(void *, void *, s32);
extern void Cache_StartResourceLoadWorker(void *, s32);
extern void Cartridge_StartReadWorker(void *, s32);
#if defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
extern void Vhandler_InitializePagerEuroExtended(s32, s32);
#elif defined(VERSION_EU_X)
extern void Vhandler_InitializePagerEuroExtended(s32, s32);
#else
extern void Vhandler_InitializePagerEuroExtended(s32, s32);
#endif
extern void Cache_InitializeResourceCache(s32, s32);

void Audiomgr_InitHeap(void) {
    u8 *heapStart;
    s32 heapEnd;
    s32 size;

    heapEnd = 0x80400000;
    heapStart = g_runtimeHeapStart;
    if (Defs_GetMemorySize() != 0x400000) {
        heapEnd = Defs_GetMemorySize() | 0x80000000;
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

#include "COMMON/AUDIO_INITIALIZE.H"
#include "COMMON/ALAUXBUS_S.H"
extern u32 g_audioSamplesPerFrame, g_audioCommandBufferSamples;
extern struct CacheEntry *g_audioCacheCountdownHead;
extern ALHeap *g_audioHeap;
extern AudioCacheEntry g_audioDmaCacheEntries[60];
extern AudioWork *g_audioFrameTasks[3];
extern s16 *g_audioCommandBuffers[2];
extern u32 g_audioTaskCompletionMessages[10], g_audioWorkerEventMessages[10], g_audioDmaCompletionMessages[60];
extern u8 g_audioWorkerThread[], g_audioWorkerStack[10240];
extern u8 g_audioMicrocodeText[4096], g_audioMicrocodeData[2048];
extern u8 g_graphicsMicrocodeText[];
extern char g_audioDmaInitializerEntry, g_audioWorkerEntry;





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
