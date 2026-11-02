#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ENTRYRECAT18V3.H"
#include "COMMON/S1.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/STATERECAT34.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SOUNDVOICEPOOL.H"
#include "ENGINE/AUDIO/SEQUENCER.H"
#include "../../../../sdk/include/libgultra_inferred/cseq.H"
#include <ultra64.h>
#include "RENDER/SETN64_GETPACKSECTION.H"

/* ROM-grounded data: src/g_trackCommandFallbackDuration_TrackSequenceAndVolume.c */
const float g_trackCommandFallbackDuration[1] = {
    0.1f,
};

/* ROM-grounded data: src/g_trackNormalizedVolumeScale_TrackSequenceAndVolume.c */
const float g_trackNormalizedVolumeScale[1] = {
    32767.0f,
};

/* ROM-grounded data: src/g_trackContextVolumePercentScales_TrackSequenceAndVolume.c */
const float g_trackContextVolumePercentScales[2] = {
    0.01f, 0.01f,
};

extern f32 g_sequencerContextVolumeScale;
extern s32 Defs_FindSortedValue(s32, s32, s32);
#include "COMMON.H"
extern f32 g_sequencerFallbackDuration;

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

/* ROM-grounded data: rodata/unresolved/800C9120 */
const float g_trackContextVolumeScale[1] = {
    32767.0f,
};

/* ROM-grounded data: src/g_trackSequenceVolumeFactors_TrackSequenceAndVolume.c */
const float g_trackSequenceVolumeFactors[2] = {
    0.01f, 32767.0f,
};

