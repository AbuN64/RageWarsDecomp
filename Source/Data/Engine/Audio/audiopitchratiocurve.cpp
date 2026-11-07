#if defined(VERSION_US_REV1)

#include "Common/externs.h"


#include "Common/lldivresult.h"


#include "Common/aiprofile.h"


#include "Common/soundvoicepool.h"


#include "Audio/song_player_views.h"


#include "Common/audio_loaddecodedsamples.h"


#include "types.h"


#include "Common/runtime_declarations.h"


#include "Audio/audio_nextdecodedsampleblock.h"


#include "Texture/sound_updateaudiocontext.h"


#include "Audio/audio_chooseweightedsoundvariant.h"


#include "Render/setn64_getpacksection.h"


#include "AUDIO/AUDIO.H"


#include "Audio/audio_initbitreverseorder.h"


#include "Engine/Audio/audio.h"


#include "include_asm.h"


#include "Engine/Audio/RAXPlayer.h"


#include "Common/self.h"


#include "Engine/defs.h"


#include "Common/format.h"


#include "Common/resident_event_handler.h"


#include "data_overlay_layouts.h"


DialogDefaultSample g_dialogDefaultSample = {
    (struct ResourceKeyView *)(&g_lastResumedPoolSoundHandle + 1), (void *)(&g_lastResumedPoolSoundHandle + 5), (void *)g_dialogDecodeStreamRecord,
    0x40, 0x3F, 0x00, 0x00,
    { 0x3F, 0x8B, 0xD1, 0xC1, 0x3F, 0x8B, 0xAD, 0xA9 },
};
#endif
