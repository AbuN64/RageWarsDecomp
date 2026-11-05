#include "Common/sound_player_parameter_events.h"
#include "include_asm.h"
#include "../../include/libgultra.h"
#include "Common/vector4f.h"
#include "Common/runtime_declarations.h"
#include "Common/audio_voice_allocation.h"
#include "types.h"





void alSndpStop(ALSndPlayer *soundPlayer) {
    s32 soundStateBase;
    ALSndpEvent stopEvent;

    soundStateBase = ((SoundPlayerEventStateView *)soundPlayer)->eventTime;
    stopEvent.common.type = 1;
    stopEvent.common.state = (void *)(soundStateBase + (((SoundPlayerEventStateView *)soundPlayer)->frameSampleCount * 0x30));
    alEvtqPostEvent(&((SoundPlayerEventStateView *)soundPlayer)->events, &stopEvent, 0);
}

