#ifndef ENGINE_AUDIO_RAXPLAYER_H
#define ENGINE_AUDIO_RAXPLAYER_H
#include "Common/soundvoicepool.h"
#include "Audio/song_player_views.h"
#include "types.h"

struct DialogPlayerState {
    int resource;
    int request;
    int state;
    int group;
    int song;
    int speed;
    int volume;
    int soundId;
};


struct DialogGroupPlayer;
/* Sound-player calls shared by the audio units: stop a playing sound, and release one sample of it. */


extern void Audio_StopDialogPlayer(void *dialogPlayer);
extern s32 Audio_ChooseSequenceVariant(void **sequenceTable, s16 id, s16 avoid);
extern void Audio_LoadDialogMetadata(void *dialogPlayer, s32 songIndex);
extern void Audio_StopDialogPlayerUnlocked(void *dialogPlayer);
extern s32 Audio_StartDialogGroup(struct DialogGroupPlayer *player, s32 group, f32 scale, int pan);
struct DialogPlayerState;
void Audio_InitializeDialogPlayer(struct DialogPlayerState *record, s32 resource);
extern struct ResourceKeyView *g_dialogDefaultSample;
#endif
