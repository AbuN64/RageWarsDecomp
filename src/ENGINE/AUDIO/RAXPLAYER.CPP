#include "include_asm.h"
#include "COMMON/EXTERNS.H"
#include "COMMON/LLDIVRESULT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/SOUNDVOICEPOOL.H"
#include "AUDIO/SONG_PLAYER_VIEWS.H"
#include "COMMON/AUDIO_LOADDECODEDSAMPLES.H"
#include "TYPES.H"
#include "ENGINE/AUDIO/RAXPLAYER.H"
#include "COMMON/SELF.H"
#include "ENGINE/AUDIO/RAXPLAYER.H"
#include "TEXTURE/SOUND_UPDATEAUDIOCONTEXT.H"
#include "AUDIO/AUDIO_CHOOSEWEIGHTEDSOUNDVARIANT.H"
#include "ENGINE/DEFS.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

/* Starts a random song from a group on a music player: picks one of the group's songs with equal weight, returning -1 when the group has none, records the group and song and takes the next request id, repeats the pick for the queued group, sets the volume to 0x40 and the speed from the given scale, then either stops the current song so it restarts (while starting or playing) or requests a start, and returns the request id. The picker and restart are inline helpers; the pick for the queued group is repeated with its result unused, as in the cartridge. */

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

/* Initialises a resource record with the resource, -1 at 4 and 0xC, zero at 8 and 0x14, 0x40 at 0x18, and at 0x1C the halfword alSndpAllocate returns for Audio_GetSoundPlayer's result on the stored resource and g_dialogDefaultSample_Raxplayer. Adapted from Device_RequestAndSetActiveState with the two calls replaced by field stores and a nested call pair whose first argument is read back from the record. */



s32 Audio_StartDialogGroup(DialogGroupPlayer *player, s32 group, f32 scale, int unused3) {
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

void Audio_InitializeDialogPlayer(struct DialogPlayerState *record, s32 resource) {
    extern char g_dialogDefaultSample[];
    record->resource = resource;
    record->request = -1;
    record->group = -1;
    record->state = 0;
    record->speed = 0;
    record->volume = 64;
    record->soundId = alSndpAllocate(Audio_GetSoundPlayer(record->resource), g_dialogDefaultSample);
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


/* ROM-grounded data: src/g_audio_LoadDialogMetadataConstantWords_Raxplayer.c */
const float g_audio_LoadDialogMetadataConstantWords[3] = {
    3.0e+01f, 0.0f, 0.01f,
};


#if defined(VERSION_DE)
float k_RaxplayerEncodedWords[3] = {
    0.01f, 32767.0f, 0.01f,
};
#endif
