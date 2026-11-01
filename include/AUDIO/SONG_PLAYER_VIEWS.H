#ifndef AUDIO_SONG_PLAYER_VIEWS_H
#define AUDIO_SONG_PLAYER_VIEWS_H
#include "TYPES.H"
struct SongHeader {
    u32 tempo;
    u16 volume;
};
struct DialogGroupPlayer {
    struct BankAudioStartDialogGroup *bank;
    s32 request;
    s32 state;
    s32 group;
    s32 song;
    s32 speed;
    s32 volume;
    char pad1C[2];
    s16 id;
};
struct DialogPlaybackPlayer {
    struct Bank *bank;
    char pad4[4];
    u32 state;
    s32 loop;
    s32 song;
    s32 speed;
    char pad18[3];
    u8 priority;
    char pad1C[2];
    s16 id;
    f32 tempoScale;
    f32 volume;
};
#endif
