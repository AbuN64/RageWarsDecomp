#include "Common/small_records.h"
#include "Common/alparam_s.h"
#include "../../include/libgultra.h"
#include "Common/runtime_declarations.h"
#include "Pools/pools.h"
#include "Ui/Tsmos/Screens/pakinterfacescreen.h"
#include "Common/alauxbus_s.h"
#include "types.h"
#include "../../include/libultra/audio/synthesizer.h"











void alSynStopVoice(ALSynth *s, ALVoice *voice)
{
    struct ALSynth4C *synth = (struct ALSynth4C *)s;
  int updateSampleTime;
  void *controlUpdate;
  void *voiceFilter;
  ALSetParam fn;
  if ((((ALVoice *)(voice))->pvoice) != 0)
  {
    controlUpdate = __allocParam();
    if (controlUpdate != 0)
    {
      updateSampleTime = (synth->paramSamples) + (((struct PVoice_s *) ((ALVoice *) voice)->pvoice)->offset);
      ((AudioStopVoiceUpdate *)(controlUpdate))->type = AL_FILTER_STOP_VOICE;
      ((AudioStopVoiceUpdate *)(controlUpdate))->next = 0;
      ((AudioStopVoiceUpdate *)(controlUpdate))->delta = updateSampleTime;
      voiceFilter = ((ALVoice *) voice)->pvoice->channelKnob;
      fn = ((ALFilter_s14 *)(voiceFilter))->setParam;
      fn(voiceFilter, AL_FILTER_ADD_UPDATE, controlUpdate);
    }
  }
}
