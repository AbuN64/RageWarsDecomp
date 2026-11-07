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


DialogDefaultSample g_dialogDefaultSample = {
    (struct ResourceKeyView *)0x800CBB20, (void *)0x800CBB30, (void *)0x80108060, 0x40, 0x3F, 0x00, 0x00,
    { 0x34, 0x42, 0x00, 0x10, 0x8C, 0x42, 0x00, 0x00 },
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


DialogDefaultSample g_dialogDefaultSample = {
    (struct ResourceKeyView *)0x800CD0D0, (void *)0x800CD0E0, (void *)0x80112060, 0x40, 0x3F, 0x00, 0x00,
    { 0x3F, 0x8B, 0x41, 0x41, 0x3F, 0x8B, 0x1D, 0x14 },
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


DialogDefaultSample g_dialogDefaultSample = {
    (struct ResourceKeyView *)0x800CBA30, (void *)0x800CBA40, (void *)0x80106060, 0x40, 0x3F, 0x00, 0x00,
    { 0x42, 0x52, 0x41, 0x4C, 0x5F, 0x42, 0x4F, 0x52 },
};
#endif
