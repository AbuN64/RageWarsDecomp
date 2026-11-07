#include "Common/externs.h"
#include "Common/lldivresult.h"
#include "Common/aiprofile.h"
#include "Common/soundvoicepool.h"
#include "Audio/song_player_views.h"
#include "Common/audio_loaddecodedsamples.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Audio/audio_nextdecodedsampleblock.h"
#include "Texture/sound_updateaudiocontext.h"
#include "Audio/audio_chooseweightedsoundvariant.h"
#include "Render/setn64_getpacksection.h"
#include "AUDIO/AUDIO.H"
#include "Audio/audio_initbitreverseorder.h"
#include "Engine/Audio/audio.h"
#include "include_asm.h"
#include "Engine/Audio/RAXPlayer.h"
#include "Common/self.h"
#include "Engine/defs.h"
#include "Common/format.h"
#include "Common/resident_event_handler.h"
#include "data_overlay_layouts.h"

/* AUDIO.CPP */

/* Runs a music player's state machine on its channel: a start request loads the song's header and sequence from the song bank, records its tempo scale and volume, sets the sequence, clears the player queue, starts the sequence through Audio_InitDecodeStream, then sets the channel's sample rate from the sequence rate over 22050, its tempo, priority, channel volume, master volume and plays it; a playing song that has ended is stopped and returns to idle or to the start state when it loops, and a stop request stops the sequencer. The state is unsigned with an empty case 0, and the rate and tempo factors are literals so the resident rodata keeps its order. */

void Audio_UpdateDialogPlayer(DialogPlaybackPlayer *player) {

    s32 rate;
    char *channel;
    s32 index;
    SongHeader *header;
    void *sequence;

    Sound_AcquireContextLock(player->bank);
    channel = Audio_GetSoundPlayer(player->bank);
    switch (player->state) {
    case 0:
        break;
    case 3:
        Audio_GetDecodeFramesRemaining();
        break;
    case 2:
        alSndpSetSound(channel, player->id);
        if (alSndpGetState(channel) == 0) {
            Audio_ClearDecodeFramesRemaining();
            if (player->loop >= 0) {
                player->state = 1;
            } else {
                player->state = 0;
            }
        }
        break;
    case 1:
        ((s32 *)&g_dialogDecodeStreamRecord->head)[0] = 0;
        ((u8 *)&g_dialogDecodeStreamRecord->head)[4] = 2;
        ((s32 *)&g_dialogDecodeStreamRecord->head)[2] = 0;
        index = player->song * 2;
        header = SetN64_GetPackSection(player->bank->songs, index);
        player->tempoScale = header->tempo * 0.01f;
        player->volume = header->volume;
        sequence = SetN64_GetPackSection(player->bank->songs, index | 1);
        ((void **)&g_dialogDecodeStreamRecord->head)[-1] = sequence;
        g_dialogDefaultSample.key->key = Audio_InitDecodeStream(sequence, 22050, &rate);
        player->state = 3;
        alSndpSetSound(channel, player->id);
        alSndpSetPitch(channel, rate * 4.5351473e-05f);
        alSndpSetVol(channel, (s16)(player->speed * player->tempoScale));
        alSndpSetPan(channel, player->priority);
        alSndpSetPriority(channel, player->id, 0x7F);
        alSndpSetFXMix(channel, (u8)(u32)player->volume);
        alSndpPlay(channel);
        player->loop = -1;
        break;
    }
    Sound_ReleaseContextLock(player->bank);
}

/* RAXPLAYER.CPP */

/* Starts a random song from a group on a music player: picks one of the group's songs with equal weight, returning -1 when the group has none, records the group and song and takes the next request id, repeats the pick for the queued group, sets the volume to 0x40 and the speed from the given scale, then either stops the current song so it restarts (while starting or playing) or requests a start, and returns the request id. The picker and restart are inline helpers; the pick for the queued group is repeated with its result discarded, as in the cartridge. */

static inline s32 pick(BankAudioStartDialogGroup *bank, s32 group) {
    s32 first;
    s32 last;
    s32 i;
    s32 total;
    s32 roll;

    total = 0;
    if (Defs_FindSortedGroupRange(bank->table, bank->count, group, &first, &last) == 0) {
        return -1;
    }
    if (first != last) {
        for (i = first; i <= last; i++) {
            total += 100;
        }
        roll = Graphu64_NextRandom() % total;
        total = 0;
        for (i = first; i < last; i++) {
            total += 100;
            if (roll <= total) {
                return i;
            }
        }
        return i;
    }
    return first;
}

static inline void restart(DialogGroupPlayer *player) {

    char *channel;

    if (player->state != 2 && player->state != 0) {
        player->state = 2;
        channel = Audio_GetSoundPlayer(player->bank);
        alSndpSetSound(channel, player->id);
        alSndpStop(channel);
    }
}

/* Starts a dialog group on the player: picks its song, scales the playback speed, then restarts the
 * player when it is playing or queued, or begins it. Returns the new request number, or -1 when the group has no song. */
s32 Audio_StartDialogGroup(DialogGroupPlayer *player, s32 group, f32 scale, int pan) {
    s32 song;
    s32 request;

    song = pick(player->bank, (s16)group);
    if (song == -1) {
        return -1;
    }
    Audio_GetSoundPlayer(player->bank);
    Sound_AcquireContextLock(player->bank);
    player->group = group;
    player->song = song;
    request = ++player->request;
    pick(player->bank, (s16)player->group);
    player->speed = scale * *(&g_dialogPlaybackTimingConstants + 1);
    player->volume = 64;
    if (player->state == 3 || player->state == 1) {
        restart(player);
    } else {
        player->state = 1;
    }
    Sound_ReleaseContextLock(player->bank);
    return request;
}

/* Initialises a dialog player for a resource: no request or group, idle, full volume, with a sound allocated
 * from the resource's sound player using the default dialog sample. */
void Audio_InitializeDialogPlayer(struct DialogPlayerState *record, s32 resource) {
    record->resource = resource;
    record->request = -1;
    record->group = -1;
    record->state = 0;
    record->speed = 0;
    record->volume = 64;
    record->soundId = alSndpAllocate(Audio_GetSoundPlayer(record->resource), (ALSound *)&g_dialogDefaultSample);
}

void Audio_StopDialogPlayer(void *dialogPlayer) {

    DialogGroupPlayer *player = dialogPlayer;
    void *soundPlayer;
    s32 state;

    Sound_AcquireContextLock((s32 *)player->bank);
    state = player->state;
    if (state != 2 && state != 0) {
        player->state = 2;
        soundPlayer = Audio_GetSoundPlayer(player->bank);
        alSndpSetSound(soundPlayer, player->id);
        alSndpStop(soundPlayer);
    }
    Sound_ReleaseContextLock((s32 *)player->bank);
}

s32 Audio_ChooseSequenceVariant(void **dialogPlayer, s16 id, s16 avoid) {
    s32 first;
    s32 last;
    s32 total;
    s32 entry;
    s32 draw;
    AudioPlaybackContextView *table;
    s32 result;

    total = 0;
    table = *dialogPlayer;
    if (Defs_FindSortedGroupRange(table->resourceIndexTable, table->resourceIndexCount, id, &first, &last) == 0) {
        return -1;
    }
    result = first;
    if (result != last) {
        for (entry = first; entry <= last; entry++) {
            total += 100;
        }
        draw = Graphu64_NextRandom() % total;
        total = 0;
        for (entry = first; entry < last; entry++) {
            total += 100;
            if (total >= draw) {
                break;
            }
        }
        if (avoid != 0 && entry == avoid) {
            if (entry == last) {
                entry--;
            } else {
                entry++;
            }
        }
        result = entry;
    }
    return result;
}

void Audio_LoadDialogMetadata(void *dialogPlayer, s32 songIndex) {
    DialogPlaybackPlayer *player = dialogPlayer;
    f64 tempoValue;
    s32 tempo;
    SongHeader *song;

    song = SetN64_GetPackSection(player->bank->songs, songIndex * 2);
    tempo = song->tempo;
    tempoValue = (f64) tempo;
    if (tempo < 0) {
        tempoValue += g_dialogUnsignedTimeCorrection;
    }
    player->tempoScale = (f32) tempoValue * g_dialogTempoScale;
    player->volume = (f32) song->volume;
    SetN64_GetPackSection(player->bank->songs, (songIndex * 2) | 1);
}

void Audio_StopDialogPlayerUnlocked(void *dialogPlayer) {

    DialogGroupPlayer *player = dialogPlayer;
    void *soundPlayer;
    s32 state;

    state = player->state;
    if (state != 2 && state != 0) {
        player->state = 2;
        soundPlayer = Audio_GetSoundPlayer(player->bank);
        alSndpSetSound(soundPlayer, player->id);
        alSndpStop(soundPlayer);
    }
}

/* 2^32, added when a negative song tempo converts to double, then the tempo scale. */
const double g_dialogUnsignedTimeCorrection = 4294967296.0;
const float g_dialogTempoScale = 0.01f;

#if defined(VERSION_DE)
extern float k_Raxplayer[3];
#endif

/* AUDIO_UPDATEDIALOGPLAYER.CPP */

const float g_audio_StartDialogGroupConstant[1] = {
    32767.0f,
};

/* G_AUDIOPITCHRATIOCURVE.CPP */

#if defined(VERSION_EU)
DialogDefaultSample g_dialogDefaultSample = {
    (struct ResourceKeyView *)0x800CC700, (void *)0x800CC710, (void *)0x80118060, 0x40, 0x3F, 0x00, 0x00,
    { 0x20, 0x54, 0x55, 0x20, 0x4D, 0x45, 0x20, 0x4D },
};
#endif

/* CONTROL_RESTOREACTORSNAPSHOT.CPP */
#if defined(VERSION_EU_X)

extern char g_ControlRestoreactorsnapshotEncodedBytes[12];
#endif

/* NAVIGATION_CONSTANT_STORAGE_RETAINED_WORDS_EU_EU_X_US.CPP */

#if defined(VERSION_US)
extern struct {
    u8 retainedHeadTagWords[12];
} g_navigationConstantStorageRetainedWordsEuEuXUs __attribute__((aligned(4)));
#endif

/* S_BINARIESTEXT.CPP */

#if defined(VERSION_US_REV1)
extern char s_binariesText[12];
#endif
