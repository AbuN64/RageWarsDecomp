#ifndef AUDIO_CHANNEL_INITIALIZEVOICEMIX_H
#define AUDIO_CHANNEL_INITIALIZEVOICEMIX_H
#include "COMMON/CARTRIDGEREADWORKER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
extern void Channel_InitializeVoiceMix(Voice *voice, SoundDescriptor *control, s32 unused2);
struct CVector3_t;
struct GameplayCamera;
s16 Channel_ComputeListenerRelativePan(struct CVector3_t *position, struct GameplayCamera *listener);
struct ChannelPitchMotionView;
struct SoundDescriptor;
void Channel_InitializeVoicePitchMotion(struct ChannelPitchMotionView *view, struct SoundDescriptor *controller, s32 flags);
#endif
