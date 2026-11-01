#ifndef COMMON_STATERECAT34_H
#define COMMON_STATERECAT34_H
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
struct MusicFadeState;

extern void SoundElement_StopAudioByKey(s32 matchingKey);


struct MusicTrackVolumeView;
struct MusicTrackVolumeView {
    struct GameAudioContext *context;
    char pad4[0x10];
    s32 sequencePlayer;
    char pad18[4];
    s32 flags; /* 0x1C */
    s32 volume; /* 0x20 */
    s32 baseVolume;
    char pad24[0x2C - 0x24 - sizeof(s32)];
    f32 appliedVolume;
    char pad30[4];
    f32 fadeStep; /* 0x34 */
    s32 gainOverrideActive;
    char pad38[0x3C - 0x38 - sizeof(s32)];
    f32 currentGain;
    f32 targetGain; /* 0x40 */
};

extern void SoundElement_StopSoundsByIdentifier(s32 soundId);

struct MusicStopState;

extern void SoundElement_UpdateContext(void);


extern float g_defaultMusicGain;

extern float g_musicFadeGainStep;


struct MusicFadeState;
typedef struct MusicFadeState MusicFadeState;

extern float g_sequencerInitialVolumeScale;

struct Track;

struct MusicStopState;
typedef struct MusicStopState MusicStopState;






extern void SoundElement_InitializeContext(void);







struct MusicTrackVolumeView;
typedef struct MusicTrackVolumeView MusicTrackVolumeView;

extern float g_sequencerVolumePercentScale;

extern float g_sequencerVolumeScale;
extern float g_sequencerOverrideVolumePercentScale;


extern int SoundElement_PlayFlatInstrument(int index);



extern void SoundElement_StopDialog(void);

extern void SoundElement_StopAudioByMask(s32 matchingFlags);

extern s32 alLoadParam(void *, s32, struct ALWaveTable_s *);
extern s32 alEnvmixerParam(void *, s32, void *);

struct GameAudioContext;
extern s32 Sound_PlaySoundAtPosition(struct GameAudioContext *, s32, CVector3, s32, s32);
#endif
