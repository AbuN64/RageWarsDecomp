#include "Common/small_records.h"
#include "Common/alauxbus_s.h"
#include "Common/alparam_s.h"
#include "../../include/libgultra.h"
#include "Common/runtime_declarations.h"
#include "Pools/pools.h"
#include "Ui/Tsmos/Screens/pakinterfacescreen.h"
#include "Common/audio_voice_allocation.h"
#include "types.h"
#include "../../include/libultra/audio/synthesizer.h"












void alSynSetFXMix(ALSynth *synth, ALVoice *voice, u8 effectMix) {
    s32 updateSampleTime;
    s32 mixMagnitude;
    void *controlUpdate;
    void *voiceFilter;
    ALSetParam fn;

    if ((((ALVoice *)(voice))->pvoice) != 0) {
        controlUpdate = __allocParam();
        if (controlUpdate != 0) {
            updateSampleTime = (((struct ALSynth4C *)(synth))->paramSamples) + (((struct PVoice_s *) ((ALVoice *) voice)->pvoice)->offset);
            ((AudioIntegerControlUpdate *)(controlUpdate))->type = AL_FILTER_SET_FXAMT;
            ((AudioIntegerControlUpdate *)(controlUpdate))->delta = updateSampleTime;
            if ((s8)effectMix < 0) {
                mixMagnitude = -(s8)effectMix;
            } else {
                mixMagnitude = (u8) effectMix;
            }
            ((AudioIntegerControlUpdate *)(controlUpdate))->value = mixMagnitude;
            ((AudioIntegerControlUpdate *)(controlUpdate))->next = 0;
            voiceFilter = ((ALVoice *) voice)->pvoice->channelKnob;
            fn = ((ALFilter_s14 *)(voiceFilter))->setParam;
            fn(voiceFilter, AL_FILTER_ADD_UPDATE, controlUpdate);
        }
    }
}












void alSynSetPan(ALSynth *synth, ALVoice *voice, ALPan pan) {
    s32 updateSampleTime;
    void *controlUpdate;
    void *voiceFilter;
    ALSetParam fn;

    if ((((ALVoice *)(voice))->pvoice) != 0) {
        controlUpdate = __allocParam();
        if (controlUpdate != 0) {
            updateSampleTime = (((struct ALSynth4C *)(synth))->paramSamples) + (((struct PVoice_s *) ((ALVoice *) voice)->pvoice)->offset);
            ((AudioIntegerControlUpdate *)(controlUpdate))->type = AL_FILTER_SET_PAN;
            ((AudioIntegerControlUpdate *)(controlUpdate))->value = pan;
            ((AudioIntegerControlUpdate *)(controlUpdate))->next = 0;
            ((AudioIntegerControlUpdate *)(controlUpdate))->delta = updateSampleTime;
            voiceFilter = ((ALVoice *) voice)->pvoice->channelKnob;
            fn = ((ALFilter_s14 *)(voiceFilter))->setParam;
            fn(voiceFilter, AL_FILTER_ADD_UPDATE, controlUpdate);
        }
    }
}












void alSynSetPitch(ALSynth *synth, ALVoice *voice, f32 pitchRatio) {
    s32 updateSampleTime;
    void *controlUpdate;
    void *voiceFilter;
    ALSetParam fn;

    if ((((ALVoice *)(voice))->pvoice) != 0) {
        controlUpdate = __allocParam();
        if (controlUpdate != 0) {
            updateSampleTime = (((struct ALSynth4C *)(synth))->paramSamples) + (((struct PVoice_s *) ((ALVoice *) voice)->pvoice)->offset);
            ((AudioPitchControlUpdate *)(controlUpdate))->type = AL_FILTER_SET_PITCH;
            ((AudioPitchControlUpdate *)(controlUpdate))->pitch = pitchRatio;
            ((AudioPitchControlUpdate *)(controlUpdate))->next = 0;
            ((AudioPitchControlUpdate *)(controlUpdate))->delta = updateSampleTime;
            voiceFilter = ((ALVoice *) voice)->pvoice->channelKnob;
            fn = ((ALFilter_s14 *)(voiceFilter))->setParam;
            fn(voiceFilter, AL_FILTER_ADD_UPDATE, controlUpdate);
        }
    }
}
