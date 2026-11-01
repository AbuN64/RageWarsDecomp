#include "include_asm.h"
#include "../../include/libgultra.h"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDRECV4.H"
#include "TYPES.H"





void alSndpStop(ALSndPlayer *soundPlayer) {
    s32 soundStateBase;
    Buf16 stopEvent;

    soundStateBase = ((SoundPlayerEventStateView *)soundPlayer)->eventTime;
    stopEvent.count = 1;
    stopEvent.value = soundStateBase + (((SoundPlayerEventStateView *)soundPlayer)->frameSampleCount * 0x30);
    alEvtqPostEvent(&((SoundPlayerEventStateView *)soundPlayer)->events, &stopEvent, 0);
}

