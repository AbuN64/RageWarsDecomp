#ifndef ENGINE_AUDIO_RAXPLAYER_H
#define ENGINE_AUDIO_RAXPLAYER_H
#include "COMMON/SOUNDVOICEPOOL.H"
#include "AUDIO/SONG_PLAYER_VIEWS.H"
#include "TYPES.H"

/* Sound-player calls shared by the audio units: stop a playing sound, and release one sample of it. */


extern void Audio_StopDialogPlayer(void *dialogPlayer);
extern s32 Audio_ChooseSequenceVariant(void **sequenceTable, s16 id, s16 avoid);
extern void Audio_LoadDialogMetadata(void *dialogPlayer, s32 songIndex);
extern void Audio_StopDialogPlayerUnlocked(void *dialogPlayer);
extern s32 Audio_StartDialogGroup(DialogGroupPlayer *player, s32 group, f32 scale, int unused3);
#endif
