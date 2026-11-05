#include "../../include/libgultra.h"
#include "Common/runtime_declarations.h"
#include "Ui/Tsmos/Screens/pakinterfacescreen.h"
#include "Common/sound_player_parameter_events.h"
#include "Common/contreadformat.h"
#include "types.h"





void alSndpPlay(ALSndPlayer *soundPlayer) {
    s32 base = (s32)soundPlayer->sndState;

    if (((ALSoundState *) (base + (soundPlayer->target * 0x30)))->state == 0) {
        ALSndpEvent p;
        p.common.type = 0;
        p.common.state = (void *)(base + soundPlayer->target * 0x30);
        alEvtqPostEvent(&soundPlayer->evtq, (s16 *)&p, 0);
    }
}





void alSndpSetFXMix(ALSndPlayer *soundPlayer, u8 effectMix) {
    SoundPlayerByteParameterEvent p;
    s32 acc;

    acc = (s32)soundPlayer->sndState;
    p.f0 = 8;
    acc += soundPlayer->target * 0x30;
    p.f8 = effectMix;
    p.f4 = acc;
    alEvtqPostEvent(&soundPlayer->evtq, (s16 *)&p, 0);
}
