#include "../../include/libgultra.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/PARAMSRECAT8V3.H"
#include "COMMON/SHAREDRECV4.H"
#include "TYPES.H"





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
