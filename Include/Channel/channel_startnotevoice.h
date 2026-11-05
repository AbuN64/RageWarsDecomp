#ifndef CHANNEL_CHANNEL_STARTNOTEVOICE_H
#define CHANNEL_CHANNEL_STARTNOTEVOICE_H
#include "Engine/Audio/audioworld.h"
struct SoundPlayer;
struct SoundDescriptor;
struct SoundVoice *Channel_StartNoteVoice(struct SoundPlayer *player, struct SoundDescriptor *note, s32 variant, s32 userData);
struct ViewChannelUpdateVoicePlayback;
void Channel_UpdateVoicePlayback(struct ViewChannelUpdateVoicePlayback *view);
extern s32 g_noteVoicePrimaryKeyTable[];
extern s32 g_noteVoiceSecondaryKeyTable[];
#endif
