#include "COMMON/ALPARAM_S.H"
#include "../../include/libgultra.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDRECV4.H"
#include "TYPES.H"
#include "../../include/libultra/audio/synthesizer.h"












void alSynFreeVoice(ALSynth *synth, ALVoice *voice) {
    void *controlUpdate;
    void *voiceFilter;
    SharedRecV8 fn;
    s32 updateSampleTime;

    if ((((AudioVoicePhysicalLinkView *)(voice))->pvoice.v0) != 0) {
        if ((((struct AudioPhysicalVoiceOffsetView *) ((AudioVoicePhysicalLinkView *) voice)->pvoice.v1)->offset) != 0) {
            controlUpdate = __allocParam();
            if (controlUpdate != 0) {
                updateSampleTime = (((struct AudioSynthParamSamplesView *)(synth))->paramSamples) + (((struct AudioPhysicalVoiceOffsetView *) ((AudioVoicePhysicalLinkView *) voice)->pvoice.v1)->offset);
                ((AudioFreeVoiceUpdateView *)(controlUpdate))->type = AL_FILTER_FREE_VOICE;
                ((AudioFreeVoiceUpdateView *)(controlUpdate))->delta = updateSampleTime;
                ((AudioFreeVoiceUpdateView *)(controlUpdate))->pvoice = ((AudioVoicePhysicalLinkView *)(voice))->pvoice.v0;
                voiceFilter = ((struct Draw *) ((AudioVoicePhysicalLinkView *) voice)->pvoice.v1)->model;
                fn = ((CallbackStateC_4 *)(voiceFilter))->callback;
                fn(voiceFilter, AL_FILTER_ADD_UPDATE, controlUpdate);
                ((AudioVoicePhysicalLinkView *)(voice))->pvoice.v0 = 0;
            }
        } else {
            _freePVoice((s32) synth, ((AudioVoicePhysicalLinkView *)(voice))->pvoice.v0);
            ((AudioVoicePhysicalLinkView *)(voice))->pvoice.v0 = 0;
        }
    }
}
