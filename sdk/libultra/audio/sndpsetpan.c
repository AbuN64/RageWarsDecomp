#include "../../include/libgultra.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/PARAMSRECAT8V3.H"
#include "COMMON/SHAREDRECV4.H"
#include "TYPES.H"





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
