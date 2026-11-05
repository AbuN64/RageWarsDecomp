#include <platform_sdk.h>
#include "Common/texture.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "Common/runtime_declarations.h"
#include "Common/soundinfo.h"
#include "Common/worldsortentry.h"
#include "Common/osviscale.h"
#include "Common/frontend_video_mode.h"
#include "types.h"
#include "../../include/libgultra.h"
#include "Common/boot_tv_type.h"
#include "Frontend/screen_video_mode.h"
#include "System/sound_context_music_and_voice_control.h"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Sched/sched_handleretrace.h"
#include "Sched/sched_handlerspcompletion.h"
#include "Sched/sched_handletaskcommands.h"

#if !(defined(VERSION_EU) || defined(VERSION_US))






extern void *SoundVoicePool_GetGlobalState(void);
extern void SoundVoicePool_StopAll(void *soundVoicePool);











void Sched_RunEventLoop(void *schedulerStorage) {
    OSSched *scheduler = schedulerStorage;
    s32 event;
    OSScClientWork *node;
    void *resource;

loop_1:
loop_2:
    osRecvMesg(&scheduler->interruptQ, &event, 1);
    if (event == 0x29B) {
        goto event_29b;
    }
    if (event < 0x29C) {
        if (event == 6) {
            goto event_6;
        }
        if (event == 0x29A) {
            goto event_29a;
        }
        goto loop_2;
    }
    if (event == 0x29C) {
        goto event_29c;
    }
    if (event == 0x29D) {
        goto event_29d;
    }
    goto loop_2;

event_29a:
    if (g_schedulerShutdownPending != 0) {
        g_schedulerFrameCountdown--;
        if (g_schedulerFrameCountdown <= 0) {
            osViSetYScale(g_schedulerVideoYScale);
            resource = &g_schedulerAlternateVideoMode;
            if (g_frontendCurrentVideoModeIndex == 0) {
                resource = &g_videoModeLabels;
            }
            osViSetMode(resource);
            osViBlack(1);
            osViSetSpecialFeatures(2);
            for (;;) {
            }
        }
    }
    Sched_HandleRetrace(scheduler);
    Frontend_UpdateScreenMode();
    goto loop_1;

event_29b:
    Sched_HandleRspCompletion(scheduler);
    goto loop_1;

event_29c:
    Sched_HandleRdpCompletion(scheduler);
    goto loop_1;

event_29d:
    SoundElement_FadeOutMusic();
    SoundElement_StopAudioExceptKey(-1);
    SoundVoicePool_StopAll(SoundVoicePool_GetGlobalState());
    node = scheduler->clientList;
    g_schedulerShutdownPending = 1;
    g_schedulerFrameCountdown = 0x14;
    if (node != 0) {
        do {
            osSendMesg(node->queue, &scheduler->retraceMsg, 0);
            node = node->next;
        } while (node != 0);
    }
    goto loop_1;

event_6:
    Sched_HandleTaskCommands(scheduler);
    goto loop_1;
}
#endif
