#include "include_asm.h"
#include "../../include/libgultra.h"
#include "Common/runtime_declarations.h"
#include "Common/sound_player_parameter_events.h"
#include "Common/audio_voice_allocation.h"
#include "Common/contreadformat.h"
#include "types.h"

void alSndpSetSound(ALSndPlayer *soundPlayer, s16 soundId) {
    soundPlayer->target = (s32) soundId;
}


void alSndpSetVol(ALSndPlayer *soundPlayer, s16 eventVolume) {
    union ALSndpEventhandleEvent p;
    s32 acc;

    acc = (s32)soundPlayer->sndState;
    p.vol.type = 3;
    acc += soundPlayer->target * 0x30;
    p.vol.vol = eventVolume;
    p.vol.state = (struct ALSoundStatehandleEvent *)acc;
    alEvtqPostEvent(&soundPlayer->evtq, (s16 *)&p, 0);
}

