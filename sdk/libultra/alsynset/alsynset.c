#include "COMMON/ALPARAM_S.H"
#include "../../include/libgultra.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDRECV4.H"
#include "TYPES.H"
#include "../../include/libultra/audio/synthesizer.h"












void alSynSetFXMix(ALSynth *synth, ALVoice *voice, u8 effectMix) {
    s32 updateSampleTime;
    s32 mixMagnitude;
    void *controlUpdate;
    void *voiceFilter;
    SharedRecV4 fn;

    if ((((AudioVoicePhysicalLinkView *)(voice))->pvoice.v0) != 0) {
        controlUpdate = __allocParam();
        if (controlUpdate != 0) {
            updateSampleTime = (((struct AudioSynthParamSamplesView *)(synth))->paramSamples) + (((struct AudioPhysicalVoiceOffsetView *) ((AudioVoicePhysicalLinkView *) voice)->pvoice.v1)->offset);
            ((AudioIntegerControlUpdate *)(controlUpdate))->type = AL_FILTER_SET_FXAMT;
            ((AudioIntegerControlUpdate *)(controlUpdate))->delta = updateSampleTime;
            if ((s8)effectMix < 0) {
                mixMagnitude = -(s8)effectMix;
            } else {
                mixMagnitude = (u8) effectMix;
            }
            ((AudioIntegerControlUpdate *)(controlUpdate))->value = mixMagnitude;
            ((AudioIntegerControlUpdate *)(controlUpdate))->next = 0;
            voiceFilter = ((struct Draw *) ((AudioVoicePhysicalLinkView *) voice)->pvoice.v1)->model;
            fn = ((CallbackStateC_4 *)(voiceFilter))->callback;
            fn(voiceFilter, AL_FILTER_ADD_UPDATE, controlUpdate);
        }
    }
}












void alSynSetPan(ALSynth *synth, ALVoice *voice, ALPan pan) {
    s32 updateSampleTime;
    void *controlUpdate;
    void *voiceFilter;
    SharedRecV5 fn;

    if ((((AudioVoicePhysicalLinkView *)(voice))->pvoice.v0) != 0) {
        controlUpdate = __allocParam();
        if (controlUpdate != 0) {
            updateSampleTime = (((struct AudioSynthParamSamplesView *)(synth))->paramSamples) + (((struct AudioPhysicalVoiceOffsetView *) ((AudioVoicePhysicalLinkView *) voice)->pvoice.v1)->offset);
            ((AudioIntegerControlUpdate *)(controlUpdate))->type = AL_FILTER_SET_PAN;
            ((AudioIntegerControlUpdate *)(controlUpdate))->value = pan;
            ((AudioIntegerControlUpdate *)(controlUpdate))->next = 0;
            ((AudioIntegerControlUpdate *)(controlUpdate))->delta = updateSampleTime;
            voiceFilter = ((struct Draw *) ((AudioVoicePhysicalLinkView *) voice)->pvoice.v1)->model;
            fn = ((CallbackStateC_4 *)(voiceFilter))->callback;
            fn(voiceFilter, AL_FILTER_ADD_UPDATE, controlUpdate);
        }
    }
}












void alSynSetPitch(ALSynth *synth, ALVoice *voice, f32 pitchRatio) {
    s32 updateSampleTime;
    void *controlUpdate;
    void *voiceFilter;
    SharedRecV7 fn;

    if ((((AudioVoicePhysicalLinkView *)(voice))->pvoice.v0) != 0) {
        controlUpdate = __allocParam();
        if (controlUpdate != 0) {
            updateSampleTime = (((struct AudioSynthParamSamplesView *)(synth))->paramSamples) + (((struct AudioPhysicalVoiceOffsetView *) ((AudioVoicePhysicalLinkView *) voice)->pvoice.v1)->offset);
            ((AudioPitchControlUpdate *)(controlUpdate))->type = AL_FILTER_SET_PITCH;
            ((AudioPitchControlUpdate *)(controlUpdate))->pitch = pitchRatio;
            ((AudioPitchControlUpdate *)(controlUpdate))->next = 0;
            ((AudioPitchControlUpdate *)(controlUpdate))->delta = updateSampleTime;
            voiceFilter = ((struct Draw *) ((AudioVoicePhysicalLinkView *) voice)->pvoice.v1)->model;
            fn = ((CallbackStateC_4 *)(voiceFilter))->callback;
            fn(voiceFilter, AL_FILTER_ADD_UPDATE, controlUpdate);
        }
    }
}
