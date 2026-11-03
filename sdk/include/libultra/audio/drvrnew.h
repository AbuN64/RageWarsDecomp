#ifndef LIBULTRA_AUDIO_DRVRNEW_H
#define LIBULTRA_AUDIO_DRVRNEW_H
struct ALEnvMixer;
void alEnvmixerNew(struct ALEnvMixer *envelopeMixer, ALHeap *heap);
struct ALFx;
void alFxNew(struct ALFx *r, ALSynConfig *c, ALHeap *hp);
struct ALResampler_s;
void alResampleNew(struct ALResampler_s *resampler, s32 heap);
#endif
