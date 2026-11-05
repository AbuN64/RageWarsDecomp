#include "Common/alauxbus_s.h"
#include "Common/alparam_s.h"
#include "../../include/libgultra.h"
#include "Common/audio_callbacks.h"
#include "Audio/synth_player_and_voice_records.h"
#include "Common/runtime_declarations.h"
#include "Ui/Tsmos/Screens/pakinterfacescreen.h"
#include "../../include/VOICE_START_AND_PARAMETER_UPDATE_VIEWS.H"
#include "types.h"
#include "../../include/libultra/audio/synthesizer.h"

/* alSynStartVoiceParams, drafted from ultralib src/audio/synstartvoiceparam.c (2.0I branch, no
   fxmix clamp): posts a start-voice-alt update carrying pitch, volume, pan, fx mix, wave table and
   the ramp time in samples to the voice's channel filter. The fx mix is declared signed, since the
   cartridge keeps the reference's fxmix < 0 negation, which an unsigned type would fold away. */
















void alSynStartVoiceParams(ALSynth *synth, ALVoice *v, ALWaveTable *w, f32 pitch, s16 vol, ALPan pan, u8 fxmix, ALMicroTime t)
{
    ALSynth4C *s = (ALSynth4C *)synth;
    ALStartParamAlt *update;
    AudioVoiceChannelFilterView *f;

    if (v->pvoice) {
        update = (ALStartParamAlt *)__allocParam();
        if (update == 0) { return; };

        if ((s8)fxmix < 0) {
            fxmix = -(s8)fxmix;
        }

        update->delta = s->paramSamples + v->pvoice->offset;
        update->next = 0;
        update->type = AL_FILTER_START_VOICE_ALT; /* AL_FILTER_START_VOICE_ALT */
        update->unity = v->unityPitch;
        update->pan = pan;
        update->volume = vol;
        update->fxMix = fxmix;
        update->pitch = pitch;
        update->samples = _timeToSamples(s, t);
        update->wave = w;

        f = v->pvoice->channelKnob;
        (*f->setParam)(f, AL_FILTER_ADD_UPDATE, update); /* AL_FILTER_ADD_UPDATE */
    }
}
