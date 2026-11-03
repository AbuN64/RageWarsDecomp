#include "include_asm.h"
#include "COMMON/WORLD.H"
#include "COMMON/WORLDRECAT1B6A4.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/WORLDSORTENTRY.H"
#include "TYPES.H"
#include "SCHED/sched_runeventloopus.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "RENDER/SETN64_GETPACKSECTION.H"
#if defined(VERSION_US)
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "sched/sched_handleretrace.H"
#include "sched/sched_handlerspcompletion.H"
#include "sched/sched_handletaskcommands.H"
extern s32 g_schedulerFrameCountdown;

extern void Frontend_UpdateScreenMode(void);

extern void SoundElement_FadeOutMusic(void);
extern void *SoundVoicePool_GetGlobalState(void);
extern void SoundVoicePool_StopAll(void *);

#endif
#if defined(VERSION_US)
char s_SchedRuneventloopusBAdvanceCameText[12] =
    "bAdvanceCame";
#endif
