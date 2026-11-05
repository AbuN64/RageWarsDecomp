#ifndef ENGINE_AUDIO_AUDIOMGR_H
#define ENGINE_AUDIO_AUDIOMGR_H
#include "Data/Overlays/Debug/constants_addresses.h"
#include "Defs/defs.h"
#include "Common/cartridgereadworker.h"

struct AudioFrameTask {
    void *owner;
    s16 id;
    char pad6[2];
    char payload[64];
    void *base;
    s32 offset;
};
typedef struct AudioFrameTask AudioFrameTask;


struct AudioFrameTask;
extern s32 * Audiomgr_InitializeDmaState(s32 * * dmaState);

extern s32 Audiomgr_RenderAudioFrame(struct AudioFrameTask *audioTask, u32 workerArgument);
extern u8 g_cartridgeReadWorker[];
#if defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
extern void Vhandler_InitializePagerEuroExtended(s32, s32);
#endif
extern void Cache_InitializeResourceCache(s32, s32);
extern u32 g_audioTaskCompletionMessages[10], g_audioWorkerEventMessages[10], g_audioDmaCompletionMessages[60];
extern u8 g_audioWorkerThread[], g_audioWorkerStack[10240];
extern u8 g_audioMicrocodeText[4096], g_audioMicrocodeData[2048];
extern char g_audioDmaInitializerEntry, g_audioWorkerEntry;
#endif
