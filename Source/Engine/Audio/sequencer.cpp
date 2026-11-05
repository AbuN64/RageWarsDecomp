#include "Common/soundvoicepool.h"
#include <platform_sdk.h>
#include "Common/version_calls.h"
#include "types.h"
#include "Common/externs.h"
#include "Render/setn64_getpacksection.h"
#include "libgultra_inferred/cseq.H"
#include "Engine/defs.h"
#include "Fade/fade.h"
#include "common.h"
#include "Common/aiprofile.h"
#include "Common/resident_event_handler.h"
#include "Engine/Audio/sequencer.h"
#include "Common/music_track_volume.h"
#include "Common/compressed_sequence_and_event_views.h"
#include "Common/triple.h"
#include "Audio/audio_updatemusicfade.h"
#include "include_asm.h"
#include "Common/osthread_s.h"
#include "Os/audio_stopmusic.h"
#include "Common/heap_arena.h"
#include "Common/heap_arena_entry.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Sequencer/audio_loadmusicsequence.h"
#include "Engine/Audio/Sequencer/track_sequence_and_volume.h"
#include "Common/format.h"
#include "data_overlay_layouts.h"

/* FADE.CPP */

/* Advances streamed music through fade, retry, loading and playback states while updating volume. */

static inline f32 fade_rate(Track *track,f32 time,f32 rate) {track->fadeDuration=time;return (f32)track->fadeStartVolume/(time*rate);}
void Audio_UpdateMusicPlayback(Track *queue) {
    f32 sequenceFadeDuration;
    f32 initialVolume;
    f32 targetVolume;
    f32 fadeDuration;
    s32 unusedValue;
    s32 requestedSequence;
    s32 sectionIndex;
    s32 startupFrames;
    s32 sortedValueResult;
    s32 playbackState;
    s32 i;
    s32 nextPlaybackState;
    ALCMidiHdr *sequenceData;
    AudioPlaybackContextView *sequenceContext;
    struct Resource *sequenceInfo;
    AudioPlaybackContextView *volumeContext;
    ALCMidiHdr *selectedSequence;
    playbackState = queue->playbackState;
    switch (playbackState) { /* irregular */
    case 32:
        if (queue->playbackFlags & 4) {
            queue->playbackFlags = 0;
            g_musicRequestedTrack = -1;
            if (queue->requestedSequence >= 0) {
                queue->playbackState = 64;
                return;
            }
            queue->playbackState = 16;
            return;
        }
        return;
    case 256:
        if (queue->playbackFlags & 8) {
            queue->playbackState = 128;
            queue->playbackFlags = 0;
            return;
        }
        startupFrames = g_musicStartupFrameCount + 1;
        g_musicStartupFrameCount = startupFrames;
        if (startupFrames >= 10) {
            g_musicRequestedTrack = -1;
            queue->playbackState = 64;
            return;
        }
        break;
    case 64:
        requestedSequence = queue->requestedSequence;
        nextPlaybackState = 16;
        if (requestedSequence != -1) {
            sequenceContext = queue->context;
            sortedValueResult = Defs_FindSortedValue(sequenceContext->resourceIndexTable, sequenceContext->resourceIndexCount, requestedSequence);
            sectionIndex = sortedValueResult;
            if (sectionIndex != -1) {
                sectionIndex *= 2;
                sequenceData = SetN64_GetPackSection(queue->context->songs, sectionIndex | 1);
                sequenceInfo = SetN64_GetPackSection(queue->context->songs, sectionIndex);
                queue->baseVolume = (s32) sequenceInfo->baseVolume;
                sequenceFadeDuration = Menu_ExpandFloatHighWord(sequenceInfo->durationHighWord);
                queue->fadeDuration = sequenceFadeDuration;
                if (sequenceFadeDuration <= 0.0f) {
                    queue->fadeDuration = g_musicDefaultFadeAndVolumeScale;
                }
                selectedSequence = sequenceData;
            } else {
                selectedSequence = NULL;
            }
            queue->midiHeader = selectedSequence;
            if (selectedSequence == NULL) {
                queue->playbackState = 256;
                g_musicStartupFrameCount = 0;
                queue->playbackFlags = 0;
                return;
            }
            queue->playbackState = 128;
            queue->sequenceLoaded = 1;
        case 128:
            i = 0;
            alCSeqNew(queue->sequence, queue->midiHeader);
            alCSPSetSeq(queue->sequencePlayer, queue->sequence);
            alCSPSetBank(queue->sequencePlayer, queue->sequenceTable->second);
            do {
                alCSPSetChlFXMix(queue->sequencePlayer, i & 0xFF, 0);
                i += 1;
            } while (i < 20);
            initialVolume = (f32) queue->baseVolume * (queue->context->volumePercent * *(&g_musicDefaultFadeAndVolumeScale+1));
            alCSPSetVol(queue->sequencePlayer, (s16) (s32) (initialVolume * g_musicVolumeAndFadeScale));
            queue->currentVolume = initialVolume;
            alCSPPlay(queue->sequencePlayer);
            queue->playbackFlags = 0;
            queue->playbackState = 16;
            g_musicRequestedTrack = queue->requestedSequence;
            return;
        }
        goto block_44;
    case 16:
    default:
        if ((g_musicRequestedTrack > 0) && (alCSPGetState((void *)queue->sequencePlayer) == 0)) {
            g_musicRequestedTrack = 0;
            queue->requestedSequence = 0;
        } else {
            if (queue->gainOverride != 0) {
                targetVolume = (f32) queue->baseVolume;
                targetVolume *= queue->context->volumePercent * *(&g_musicVolumeAndFadeScale+1);
                targetVolume *= queue->overrideGain;
                goto block_37;
            }
            volumeContext = queue->context;
            targetVolume = (f32) queue->baseVolume * (volumeContext->volumePercent * g_musicPlaybackVolumeScale);
            if (volumeContext->musicAttenuated != 0) {
                targetVolume *= g_musicDuckedVolumeScale;
            }
            if (targetVolume != queue->currentVolume) {
block_37:
                alCSPSetVol(queue->sequencePlayer, (s16) (s32) (targetVolume * g_musicTargetVolumeToMidiScale));
                queue->currentVolume = targetVolume;
            }
        }
        if (queue->requestedSequence != g_musicRequestedTrack) {
            if (g_musicRequestedTrack > 0) {
                fadeDuration = queue->fadeDuration;
                queue->playbackFlags = 2;
                queue->playbackState = 32;
                queue->fadeStartVolume = (s32) (queue->currentVolume * g_musicCurrentVolumeToMidiScale);
                if (!(fadeDuration >= g_musicFadeDurationLimits)) {
                    fadeDuration = g_musicFadeDurationLimits;
                }
                queue->fadeStep = fade_rate(queue,fadeDuration,*(&g_musicFadeDurationLimits+1));
                return;
            }
            nextPlaybackState = 64;
            queue->playbackFlags = 0;
block_44:
            queue->playbackState = nextPlaybackState;
        }
        break;
    }
}

/* AUDIO_UPDATEMUSICFADE.CPP */

void Audio_InitializeMusicPlayer(struct AudioStateD844 *state, struct AudioRootD844 *root) {
    struct AudioParamsD844 params;
    void *player;
    state->root = root;
    state->mode = 16;
    state->index = -1;
    state->flags = 0;
    params.count38 = 20;
    params.count1C = 192;
    params.kind = 20;
    params.context = &state->root->heap;
    params.value10 = 0;
    params.value14 = 0;
    params.value18 = 0;
    player = alHeapDBAlloc(0, 0, &state->root->heap, 1, 124);
    state->player = player;
    alCSPNew(player, &params);
    state->allocation = alHeapDBAlloc(0, 0, &state->root->heap, 1, 248);
    state->timer = 50;
    state->counter = 0;
    state->first = k_musicPlayerInitialUnitValue_de;
    state->second = k_musicPlayerInitialMiddleValue_de;
    state->third = k_musicPlayerInitialUnitValue_de;
    state->fourth = k_musicPlayerInitialUnitValue_de;
}

void Audio_UpdateMusicFade(void *queue) {
    MusicTrackVolumeView *o = queue;
    f32 currentGain;
    f32 targetGain;
    f32 nextGain;
    s32 nextVolume;

    if (o->flags & 2) {
        alCSPSetVol(o->sequencePlayer, (s16)o->volume);
        nextVolume = (s32) ((f32) o->volume - o->fadeStep);
        o->volume = nextVolume;
        if (nextVolume <= 0) {
            o->volume = 0;
            alCSPStop(o->sequencePlayer);
            o->flags |= 4;
        }
    } else if (o->gainOverrideActive != 0) {
        currentGain = o->currentGain;
        targetGain = o->targetGain;
        if (targetGain < currentGain) {
            nextGain = currentGain - g_musicFadeGainStep;
            if (targetGain <= nextGain) {
                goto store;
            }
            goto clamp;
        }
        if (currentGain < targetGain) {
            nextGain = currentGain + (0.01666666753590107f);
            if (nextGain <= targetGain) {
                goto store;
            }
            clamp:
            nextGain = targetGain;
            store:
            o->currentGain = nextGain;
        }
    }
}



/* AUDIO_LOADMUSICSEQUENCE.CPP */



s32 Audio_LoadMusicSequence(Track *state, s32 index) {
    s32 selection;

    ALCMidiHdr *result;
    ALCMidiHdr *selected;
    Resource *command;
    f32 duration;
    selection = Defs_FindSortedValue(state->context->resourceIndexTable, state->context->resourceIndexCount, index);
    if (selection != -1) {
        selection *= 2;
        selected = SetN64_GetPackSection(state->context->songs, selection | 1);
        command = SetN64_GetPackSection(state->context->songs, selection);
        state->baseVolume = command->baseVolume;
#if defined(VERSION_EU)
        duration = Menu_ExpandFloatHighWord(command->durationHighWord);
#else
        duration = Menu_ExpandFloatHighWord(command->durationHighWord);
#endif
        state->fadeDuration = duration;
        if (duration <= 0.0f) state->fadeDuration = g_musicSequenceFallbackDuration;
        result = selected;
    } else {
        result = NULL;
    }
    state->midiHeader = result;
    return result != NULL;
}

/* Sets the sound fade state and derives its step from the clamped duration. */

void Audio_FadeOutMusic(MusicFadeState *musicState) {
    f32 fadeDuration;

    fadeDuration = musicState->fadeDuration;
    musicState->fadeMode = 2;
    musicState->playbackState = 32;
    musicState->currentMidiVolume = (s32) (musicState->volume * 32767.0f);
    if (!(fadeDuration >= 0.1f)) {
        fadeDuration = 0.1f;
    }
    musicState->fadeDuration = fadeDuration;
    musicState->requestedSequence = 0;
    musicState->fadeStep = (f32) ((f32) musicState->currentMidiVolume / (fadeDuration * 60.0f));
}

void Audio_EnableMusicGainOverride(Track *track) {
    track->gainOverride = 1;
    track->fadeResetValue = 0;
}

/** Clears the track's gain override and restores its fade reset value to g_defaultMusicGain. */
void Audio_DisableMusicGainOverride(Track *track) {
    track->fadeResetValue = g_defaultMusicGain;
    track->gainOverride = 0;
}

void Audio_StopMusic(s32 a) {
    (((struct MusicStopState *) ((s8 *) a))->stopSentinel) = -1;
    alCSPStop((((struct MusicStopState *) ((s8 *) a))->sequencePlayer));
}

/* TRACK_SEQUENCE_AND_VOLUME.CPP */








void *Sequencer_SelectTrackSequence(Track *state, s32 index) {
    s32 selection;

    void *result;
    Resource *command;
    f32 duration;
    selection = Defs_FindSortedValue(state->context->resourceIndexTable, state->context->resourceIndexCount, index);
    if (selection != -1) {
        selection *= 2;
        result = SetN64_GetPackSection(state->context->songs, selection | 1);
        command = SetN64_GetPackSection(state->context->songs, selection);
        state->baseVolume = command->baseVolume;
#if defined(VERSION_EU)
        duration = Menu_ExpandFloatHighWord(command->durationHighWord);
#else
        duration = Menu_ExpandFloatHighWord(command->durationHighWord);
#endif
        state->fadeDuration = duration;
        if (duration <= 0.0f) state->fadeDuration = g_sequencerFallbackDuration;
        return result;
    }
    return NULL;
}

void Sequencer_SetTrackVolume(void *trackState, f32 volume) {
    Track *track = trackState;
    f32 f20 = volume;
    f32 f0 = f20 * g_sequencerVolumeScale;
    alCSPSetVol(track->sequencePlayer, (s16)(s32) f0);
    track->currentVolume = f20;
}

void Sequencer_UpdateTrackVolume(void *trackState) {
    MusicTrackVolumeView *o = trackState;
    f32 effectiveVolume;
    GameAudioContext *context;

    if (o->gainOverrideActive != 0) {
        f32 prod = o->context->green;
        prod = prod * g_sequencerOverrideVolumePercentScale;
        effectiveVolume = (f32) (o->baseVolume);
        effectiveVolume = effectiveVolume * prod;
        effectiveVolume = effectiveVolume * o->currentGain;
        goto do_update;
    }
    context = o->context;
    effectiveVolume = (f32) (o->baseVolume) * (context->green * g_sequencerVolumePercentScale);
    if (context->dialogEnabled != 0) {
        effectiveVolume = effectiveVolume * (0.699999988079071f);
    }
    if (effectiveVolume != o->appliedVolume) {
        do_update:
        alCSPSetVol(o->sequencePlayer, (s16) (s32) (effectiveVolume * g_sequencerContextVolumeScale));
        o->appliedVolume = effectiveVolume;
    }
}

void Sequencer_AttachTrackSequence(Track *track) {
    s32 i;
    f32 scaled;

    i = 0;
    alCSeqNew(track->sequence, track->midiHeader);
    alCSPSetSeq(track->sequencePlayer, track->sequence);
    alCSPSetBank(track->sequencePlayer,
        track->sequenceTable->second);
    do {
        alCSPSetChlFXMix(track->sequencePlayer, i & 0xFF, 0);
        i++;
    } while (i < 20);

    scaled = (f32)track->baseVolume *
        (track->context->volumePercent * (&g_sequencerContextVolumeScale)[1]);
    alCSPSetVol(track->sequencePlayer, (s16)(s32)(scaled * g_sequencerInitialVolumeScale));
    track->currentVolume = scaled;
}





/* SEQUENCER.CPP */







/* AUDIO_DISABLEMUSICGAINOVERRIDE_DATA.CPP */



/* G_AUDIOPITCHRATIOCURVE.CPP */

#if defined(VERSION_DE)
struct {
    s32 g_musicRequestedTrack;
    s32 g_musicStartupFrameCount;
    u8 retainedInstructionWords[8];
} g_sequencerDrDonLabel __attribute__((aligned(4))) = {
    0,
    0,
    { 0x3c, 0x3, 0xa4, 0x60, 0x34, 0x63, 0x0, 0x10 }
};
typedef char g_sequencerDrDonLabelSizeCheck[(sizeof(g_sequencerDrDonLabel) == 16) ? 1 : -1];
#endif

#if defined(VERSION_EU)
char g_sequencerDrDonLabel[16] __attribute__((aligned(4))) = "\000\000\000\000\000\000\000\000DR. DON ";
#endif

#if defined(VERSION_EU_X)
struct {
    s32 g_musicRequestedTrack;
    s32 g_musicStartupFrameCount;
    u8 retainedPitchRatioWords[8];
} g_sequencerDrDonLabel __attribute__((aligned(4))) = {
    0,
    0,
    { 0x3f, 0x8a, 0xb0, 0x6c, 0x3f, 0x8a, 0x8c, 0x29 }
};
typedef char g_sequencerDrDonLabelSizeCheck[(sizeof(g_sequencerDrDonLabel) == 16) ? 1 : -1];
#endif

#if defined(VERSION_US)
struct {
    s32 g_musicRequestedTrack;
    s32 g_musicStartupFrameCount;
    u8 retainedEosTagWords[8];
} g_sequencerDrDonLabel __attribute__((aligned(4))) = {
    0,
    0,
    { 0x65, 0x71, 0x75, 0x4, 0x2e, 0x65, 0x6f, 0x73 }
};
typedef char g_sequencerDrDonLabelSizeCheck[(sizeof(g_sequencerDrDonLabel) == 16) ? 1 : -1];
#endif

#if defined(VERSION_US_REV1)
struct {
    s32 g_musicRequestedTrack;
    s32 g_musicStartupFrameCount;
    u8 retainedPitchRatioWords[8];
} g_sequencerDrDonLabel __attribute__((aligned(4))) = {
    0,
    0,
    { 0x3f, 0x8b, 0x41, 0x41, 0x3f, 0x8b, 0x1d, 0x14 }
};
typedef char g_sequencerDrDonLabelSizeCheck[(sizeof(g_sequencerDrDonLabel) == 16) ? 1 : -1];
#endif

/* Retained data for this translation unit. */

const float g_audio_LoadMusicSequenceConstant[1] = {
    0.1f,
};

const float g_trackCommandFallbackDuration[1] = {
    0.1f,
};

const float g_trackNormalizedVolumeScale[1] = {
    32767.0f,
};

const float g_trackContextVolumePercentScales[2] = {
    0.01f, 0.01f,
};

const float g_trackContextVolumeScale[1] = {
    32767.0f,
};

const float g_trackSequenceVolumeFactors[2] = {
    0.01f, 32767.0f,
};

const float g_audio_UpdateMusicPlaybackConstant[10] = {
    0.1f, 0.01f, 32767.0f, 0.01f, 0.01f, 0.7f,
    32767.0f, 32767.0f, 0.1f, 6.0e+01f,
};

const float g_audio_InitializeMusicPlayerConstant[2] = {
    1.0f, 125.0f,
};

const float g_audio_UpdateMusicFadeConstant[1] = {
    0.016666668f,
};

const float g_audio_DisableMusicGainOverrideConstant[1] = {
    1.0f,
};
