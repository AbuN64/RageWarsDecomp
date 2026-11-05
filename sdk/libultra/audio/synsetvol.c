#include "Common/small_records.h"
#include "Common/alauxbus_s.h"
#include "Common/alparam_s.h"
#include "include_asm.h"
#include "../../include/libgultra.h"
#include "Common/runtime_declarations.h"
#include "Pools/pools.h"
#include "Ui/Tsmos/Screens/pakinterfacescreen.h"
#include "../../include/VOICE_START_AND_PARAMETER_UPDATE_VIEWS.H"
#include "types.h"
#include "../../include/libultra/audio/synthesizer.h"












void alSynSetVol(ALSynth *synth, ALVoice *voice, s16 targetVolume, ALMicroTime rampTime) {
    s32 updateSampleTime;
    void *controlUpdate;
    void *voiceFilter;
    ALSetParam fn;

    if ((((ALVoice *)(voice))->pvoice) != 0) {
        controlUpdate = __allocParam();
        if (controlUpdate != 0) {
            updateSampleTime = (((struct ALSynth4C *)(synth))->paramSamples) + (((struct PVoice_s *) ((ALVoice *) voice)->pvoice)->offset);
            ((AudioVolumeControlUpdate *)(controlUpdate))->type = AL_FILTER_SET_VOLUME;
            ((AudioVolumeControlUpdate *)(controlUpdate))->volume = (s32) targetVolume;
            ((AudioVolumeControlUpdate *)(controlUpdate))->delta = updateSampleTime;
            ((AudioVolumeControlUpdate *)(controlUpdate))->samples = _timeToSamples(synth, rampTime);
            ((AudioVolumeControlUpdate *)(controlUpdate))->next = 0;
            voiceFilter = ((ALVoice *) voice)->pvoice->channelKnob;
            fn = ((ALFilter_s14 *)(voiceFilter))->setParam;
            fn(voiceFilter, AL_FILTER_ADD_UPDATE, controlUpdate);
        }
    }
}

