#if defined(VERSION_DE)

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


unsigned short k_GAudiopitchratiocurveEncodedHalfwords[12] = {
    0x800C, 0xBB20, 0x800C, 0xBB30, 0x8010, 0x8060, 0x403F, 0x0000, 0x3442, 0x0010, 0x8C42, 0x0000,
};
#endif

#if defined(VERSION_EU_X)

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


unsigned short k_GAudiopitchratiocurveEncodedHalfwords[12] = {
    0x800C, 0xD0D0, 0x800C, 0xD0E0, 0x8011, 0x2060, 0x403F, 0x0000, 0x3F8B, 0x4141, 0x3F8B, 0x1D14,
};
#endif

#if defined(VERSION_US)

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


unsigned short k_GAudiopitchratiocurveEncodedHalfwords[12] = {
    0x800C, 0xBA30, 0x800C, 0xBA40, 0x8010, 0x6060, 0x403F, 0x0000, 0x4252, 0x414C, 0x5F42, 0x4F52,
};
#endif
