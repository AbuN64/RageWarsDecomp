#ifndef SEQUENCER_AUDIO_LOADMUSICSEQUENCE_H
#define SEQUENCER_AUDIO_LOADMUSICSEQUENCE_H
struct MusicFadeState;
void Audio_FadeOutMusic(struct MusicFadeState *musicState);
extern f32 g_musicSequenceFallbackDuration;
#endif
