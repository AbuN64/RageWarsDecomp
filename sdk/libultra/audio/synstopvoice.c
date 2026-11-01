#include "COMMON/ALPARAM_S.H"
#include "../../include/libgultra.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ALAUXBUS_S.H"
#include "TYPES.H"
#include "../../include/libultra/audio/synthesizer.h"











void alSynStopVoice(ALSynth *s, ALVoice *voice)
{
    struct AudioSynthParamSamplesView *synth = (struct AudioSynthParamSamplesView *)s;
  int updateSampleTime;
  void *controlUpdate;
  void *voiceFilter;
  SharedRecV12 fn;
  if ((((AudioVoicePhysicalLinkView *)(voice))->pvoice.v0) != 0)
  {
    controlUpdate = __allocParam();
    if (controlUpdate != 0)
    {
      updateSampleTime = (synth->paramSamples) + (((struct AudioPhysicalVoiceOffsetView *) ((AudioVoicePhysicalLinkView *) voice)->pvoice.v1)->offset);
      ((AudioStopVoiceUpdate *)(controlUpdate))->type = AL_FILTER_STOP_VOICE;
      ((AudioStopVoiceUpdate *)(controlUpdate))->next = 0;
      ((AudioStopVoiceUpdate *)(controlUpdate))->delta = updateSampleTime;
      voiceFilter = ((struct Draw *) ((AudioVoicePhysicalLinkView *) voice)->pvoice.v1)->model;
      fn = ((CallbackStateC_4 *)(voiceFilter))->callback;
      fn(voiceFilter, AL_FILTER_ADD_UPDATE, controlUpdate);
    }
  }
}
