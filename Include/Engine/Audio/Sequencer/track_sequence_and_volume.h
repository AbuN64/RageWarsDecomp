#ifndef ENGINE_AUDIO_SEQUENCER_TRACK_SEQUENCE_AND_VOLUME_H
#define ENGINE_AUDIO_SEQUENCER_TRACK_SEQUENCE_AND_VOLUME_H
#include "types.h"
#include "Common/heap_arena.h"
#include "Common/heap_arena_entry.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/music_track_volume.h"
#include "Common/aiprofile.h"
#include "Common/runtime_declarations.h"
#include "Common/soundvoicepool.h"
#include "Engine/Audio/sequencer.h"
#include "../../../../sdk/include/libgultra_inferred/cseq.H"
#include <platform_sdk.h>
#include "Render/setn64_getpacksection.h"
#include "Engine/defs.h"
extern f32 g_sequencerContextVolumeScale;
extern f32 g_sequencerFallbackDuration;
#endif
