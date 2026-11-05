#ifndef SOUND_SOUND_H
#define SOUND_SOUND_H
struct AudioInitializeTiming;
struct GameAudioContext;
struct CVector3_t;
s32 Sound_PlayInstrumentAtPosition(struct GameAudioContext *self, s32 index, struct CVector3_t position, s32 voiceParameter);
s32 Sound_UpdateSoundSlot(struct GameAudioContext *context, s32 id, s32 updateFlags, struct CVector3_t *position);
extern char g_cartridgeReadWorker;
extern float g_soundContextVolumePercentScale, g_soundContextInitialPlaybackScale;
extern void Audiomgr_InitializeAudioWorker(ALSynConfig *, s32, struct AudioInitializeTiming *);
extern s32 g_audioWorkerThreadPriority;
extern s32 g_audioFxConfigParams;
#endif
