#include "COMMON/ALPARAM_S.H"
#include "include_asm.h"
#include "../../include/libgultra.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "../../include/VOICE_START_AND_PARAMETER_UPDATE_VIEWS.H"
#include "TYPES.H"
#include "../../include/libultra/audio/synthesizer.h"












void alSynSetVol(ALSynth *synth, ALVoice *voice, s16 targetVolume, ALMicroTime rampTime) {
    s32 updateSampleTime;
    void *controlUpdate;
    void *voiceFilter;
    SharedRecV10 fn;

    if ((((AudioVoicePhysicalLinkView *)(voice))->pvoice.v0) != 0) {
        controlUpdate = __allocParam();
        if (controlUpdate != 0) {
            updateSampleTime = (((struct AudioSynthParamSamplesView *)(synth))->paramSamples) + (((struct AudioPhysicalVoiceOffsetView *) ((AudioVoicePhysicalLinkView *) voice)->pvoice.v1)->offset);
            ((AudioVolumeControlUpdate *)(controlUpdate))->type = AL_FILTER_SET_VOLUME;
            ((AudioVolumeControlUpdate *)(controlUpdate))->volume = (s32) targetVolume;
            ((AudioVolumeControlUpdate *)(controlUpdate))->delta = updateSampleTime;
            ((AudioVolumeControlUpdate *)(controlUpdate))->samples = _timeToSamples(synth, rampTime);
            ((AudioVolumeControlUpdate *)(controlUpdate))->next = 0;
            voiceFilter = ((struct Draw *) ((AudioVoicePhysicalLinkView *) voice)->pvoice.v1)->model;
            fn = ((CallbackStateC_4 *)(voiceFilter))->callback;
            fn(voiceFilter, AL_FILTER_ADD_UPDATE, controlUpdate);
        }
    }
}

