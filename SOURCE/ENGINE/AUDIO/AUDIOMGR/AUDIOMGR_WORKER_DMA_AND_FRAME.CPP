#include "COMMON/CARTRIDGEREADWORKER.H"
#include "TEXTURE/CARTRIDGE_DMA_AND_AUDIO_TIMING_VIEWS.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/CONTROLLER_MOTOR_STATE.H"
#include "COMMON/STATERECAT34.H"
#include "COMMON/SOUNDINFO.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/GUMTXL2F.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/LLDIVRESULT.H"
#include "TYPES.H"
#include "TYPES.H"
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
#include "SYSTEM/SOUND_CONTEXT_LOCK_AND_ACTIVITY.H"
#include "ENGINE/AUDIO/AUDIOMGR.H"
#include <ultra64.h>
#include "libgultra/alunlink.h"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>


extern u32 g_audioWorkerElapsedTicks;









extern void Sound_RetireCompletedSampleWindows(Work56EC8 *audioTask);




extern void Sched_SendSchedulerTask(void *scheduler, void *task);



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

s32 Audiomgr_RenderAudioFrame(Work56EC8 *audioTask, u32 unused)
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
