#ifndef AUDIO_CHANNEL_INITIALIZEVOICEMIX_H
#define AUDIO_CHANNEL_INITIALIZEVOICEMIX_H
#include "Common/cartridgereadworker.h"
#include "Common/runtime_declarations.h"
#include "types.h"
struct Voice;
extern void Channel_InitializeVoiceMix(struct Voice *voice, struct SoundDescriptor *control, s32 voiceFlags);
struct CVector3_t;
struct GameplayCamera;
s16 Channel_ComputeListenerRelativePan(struct CVector3_t *position, struct GameplayCamera *listener);
struct ChannelPitchMotionView;
struct SoundDescriptor;
void Channel_InitializeVoicePitchMotion(struct ChannelPitchMotionView *view, struct SoundDescriptor *controller, s32 flags);
extern unsigned short Menu_GetFloatHighWord(f32);
extern s32 SoundInfo_GetY(struct SoundDescriptor *);
extern float g_voiceDefaultGain;
#endif
