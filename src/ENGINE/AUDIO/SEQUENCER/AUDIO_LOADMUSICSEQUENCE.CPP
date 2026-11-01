#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/OSTHREAD_S.H"
#include "COMMON/SOUNDVOICEPOOL.H"
#include "COMMON/STATERECAT34.H"
#include "ENGINE/AUDIO/SEQUENCER.H"
#include "TYPES.H"
#include "OS/AUDIO_STOPMUSIC.H"

#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ENTRYRECAT18V3.H"
#include "COMMON/S1.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <ultra64.h>
#include "RENDER/SETN64_GETPACKSECTION.H"
extern s32 Defs_FindSortedValue(s32, s32, s32);
#include "COMMON.H"
extern f32 g_musicSequenceFallbackDuration;

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

/** Clear offset 0x38 and initialize offset 0x40 from g_defaultMusicGain. */
void Audio_DisableMusicGainOverride(Track *track) {
    track->fadeResetValue = g_defaultMusicGain;
    track->gainOverride = 0;
}


void Audio_StopMusic(s32 a) {
    (((struct MusicStopState *) ((s8 *) a))->stopSentinel) = -1;
    alCSPStop((((struct MusicStopState *) ((s8 *) a))->sequencePlayer));
}
