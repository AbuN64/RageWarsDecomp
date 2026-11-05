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












void alSynFreeVoice(ALSynth *synth, ALVoice *voice) {
    void *controlUpdate;
    void *voiceFilter;
    ALSetParam fn;
    s32 updateSampleTime;

    if ((((ALVoice *)(voice))->pvoice) != 0) {
        if ((((struct PVoice_s *) ((ALVoice *) voice)->pvoice)->offset) != 0) {
            controlUpdate = __allocParam();
            if (controlUpdate != 0) {
                updateSampleTime = (((struct ALSynth4C *)(synth))->paramSamples) + (((struct PVoice_s *) ((ALVoice *) voice)->pvoice)->offset);
                ((AudioFreeVoiceUpdateView *)(controlUpdate))->type = AL_FILTER_FREE_VOICE;
                ((AudioFreeVoiceUpdateView *)(controlUpdate))->delta = updateSampleTime;
                ((AudioFreeVoiceUpdateView *)(controlUpdate))->pvoice = ((ALVoice *)(voice))->pvoice;
                voiceFilter = ((ALVoice *) voice)->pvoice->channelKnob;
                fn = ((ALFilter_s14 *)(voiceFilter))->setParam;
                fn(voiceFilter, AL_FILTER_ADD_UPDATE, controlUpdate);
                ((ALVoice *)(voice))->pvoice = 0;
            }
        } else {
            _freePVoice((s32) synth, ((ALVoice *)(voice))->pvoice);
            ((ALVoice *)(voice))->pvoice = 0;
        }
    }
}
