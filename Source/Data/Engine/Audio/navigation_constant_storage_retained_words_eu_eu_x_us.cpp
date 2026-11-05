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


struct {
    u8 retainedHeadTagWords[12];
} g_navigationConstantStorageRetainedWordsEuEuXUs __attribute__((aligned(4))) = {
    { 0x69, 0x73, 0x74, 0x48, 0x65, 0x61, 0x64, 0x54, 0x00, 0x00, 0xE8, 0x02 }
};
#endif
