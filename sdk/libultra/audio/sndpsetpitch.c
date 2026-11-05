#include "../../include/libgultra.h"
#include "Common/runtime_declarations.h"
#include "Common/sound_player_parameter_events.h"
#include "Common/audio_voice_allocation.h"
#include "types.h"





void alSndpSetPitch(ALSndPlayer *soundPlayer, f32 pitchBits) {
    SoundPlayerWordParameterEvent p;
    s32 acc;

    acc = ((SoundPlayerEventStateView *)soundPlayer)->eventTime;
    p.f0 = 4;
    acc += ((SoundPlayerEventStateView *)soundPlayer)->frameSampleCount * 0x30;
    p.f8 = pitchBits;
    p.f4 = acc;
    alEvtqPostEvent(&((SoundPlayerEventStateView *)soundPlayer)->events, (s16 *)&p, 0);
}
