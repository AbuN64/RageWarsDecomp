#ifndef ENGINE_AUDIO_AUDIOMGR_AUDIOMGR_WORKER_DMA_AND_FRAME_H
#define ENGINE_AUDIO_AUDIOMGR_AUDIOMGR_WORKER_DMA_AND_FRAME_H
#include "Engine/sched.h"
#include "Common/cartridgereadworker.h"
#include "Texture/cartridge_dma_and_audio_timing_views.h"
#include "Common/effectrender.h"
#include "Common/runtime_declarations.h"
#include "Common/controller_motor_state.h"
#include "Common/music_track_volume.h"
#include "Common/soundinfo.h"
#include "Common/sessionhandlerrow.h"
#include "Common/gumtxl2f.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "Common/lldivresult.h"
#include "types.h"
#include "types.h"
#include "System/sound_context_music_and_voice_control.h"
#include "System/sound_context_lock_and_activity.h"
#include "Engine/Audio/AUDIOMGR.h"
#include <platform_sdk.h>
#include "libgultra/alunlink.h"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Common/triple.h"
struct AudioFrameTask;
extern void Sound_RetireCompletedSampleWindows(struct AudioFrameTask *audioTask);
#endif
