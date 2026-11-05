#include "../../include/libgultra.h"
#include "Common/runtime_declarations.h"
#include "Common/sound_player_parameter_events.h"
#include "Common/audio_voice_allocation.h"
#include "types.h"





void alSndpSetPan(ALSndPlayer *soundPlayer, ALPan pan) {
    SoundPlayerByteParameterEvent p;
    s32 acc;

    acc = ((SoundPlayerEventStateView *)soundPlayer)->eventTime;
    p.f0 = 2;
    p.f8 = pan;
    acc += ((SoundPlayerEventStateView *)soundPlayer)->frameSampleCount * 0x30;
    p.f4 = acc;
    alEvtqPostEvent(&((SoundPlayerEventStateView *)soundPlayer)->events, (s16 *)&p, 0);
}
