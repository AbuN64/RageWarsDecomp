#include "include_asm.h"
#include "COMMON/WORLD.H"
#include "COMMON/WORLDRECAT1B6A4.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/WORLDSORTENTRY.H"
#include "TYPES.H"
#include "../../include/SCHED/sched_runeventloopus.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "RENDER/SETN64_GETPACKSECTION.H"
#if defined(VERSION_US)
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
extern s32 g_schedulerFrameCountdown;
extern void Sched_HandleRetrace(OSSched *);
extern void Frontend_UpdateScreenMode(void);
extern void Sched_HandleRdpCompletion(OSSched *);
extern void SoundElement_FadeOutMusic(void);
extern void *SoundVoicePool_GetGlobalState(void);
extern void SoundVoicePool_StopAll(void *);
extern void Sched_HandleTaskCommands(OSSched *);

void Sched_RunEventLoopUs(OSSched *sc) {
    void *msg;
    OSScClientWork *client;
    for (;;) {
        osRecvMesg(&sc->interruptQ, &msg, 1);
        switch ((s32)msg) {
        case 0x29A:
            if (g_schedulerShutdownPending && --g_schedulerFrameCountdown <= 0) {
                osViBlack(1);
                for (;;) {}
            }
            Sched_HandleRetrace(sc);
            Frontend_UpdateScreenMode();
            break;
        case 0x29B: Sched_HandleRspCompletion(sc); break;
        case 0x29C: Sched_HandleRdpCompletion(sc); break;
        case 0x29D:
            SoundElement_FadeOutMusic();
            SoundElement_StopAudioExceptKey(-1);
            SoundVoicePool_StopAll(SoundVoicePool_GetGlobalState());
            client = sc->clientList;
            g_schedulerShutdownPending = 1;
            g_schedulerFrameCountdown = 20;
            while (client) {
                osSendMesg(client->queue, &sc->retraceMsg, 0);
                client = client->next;
            }
            break;
        case 6: Sched_HandleTaskCommands(sc); break;
        }
    }
}
#endif
#if defined(VERSION_US)
char s_SchedRuneventloopusBAdvanceCameText[12] =
    "bAdvanceCame";
#endif
