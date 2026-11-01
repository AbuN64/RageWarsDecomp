#ifndef LIBULTRA_AUDIO_SYNTHESIZER_H
#define LIBULTRA_AUDIO_SYNTHESIZER_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ALAUXBUS_S.H"

struct ALEnvMixer4C {
    char pad[0x4C];
};
struct PVoice_s {
    ListLink node;
    struct Opaque_ALVoice_s *vvoice;
    ALFilter_s14 *channelKnob;
    ALLoadFilter decoder;
    ALResampler resampler;
    ALEnvMixer4C envmixer;
    s32 offset;
};

extern void*__allocParam(void);
extern void __freeParam(void*parameterStorage);
extern void _freePVoice(s32 synthesizer, s32 listLink);
extern s32 _timeToSamples(SynthOutputRateView*synth, s32 microseconds);
#endif
