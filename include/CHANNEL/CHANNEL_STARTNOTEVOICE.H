#ifndef CHANNEL_CHANNEL_STARTNOTEVOICE_H
#define CHANNEL_CHANNEL_STARTNOTEVOICE_H
struct SoundPlayer;
struct SoundDescriptor;
struct SoundVoice *Channel_StartNoteVoice(struct SoundPlayer *player, struct SoundDescriptor *note, s32 variant, s32 userData);
struct ViewChannelUpdateVoicePlayback;
void Channel_UpdateVoicePlayback(struct ViewChannelUpdateVoicePlayback *view);
#endif
