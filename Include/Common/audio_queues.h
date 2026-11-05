#ifndef COMMON_AUDIO_QUEUES_H
#define COMMON_AUDIO_QUEUES_H
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
/* The initializer creates these as queues of 10, 10 and 60 messages. */
extern OSMesgQueue g_audioTaskCompletionQueue, g_audioWorkerEventQueue, g_audioDmaCompletionQueue;
#endif
