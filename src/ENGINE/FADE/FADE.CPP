#include "COMMON/SOUNDVOICEPOOL.H"
#include <ultra64.h>
#include "COMMON/VERSION_CALLS.H"

/* Advances streamed music through fade, retry, loading and playback states while updating volume. */
#include "TYPES.H"
#include "COMMON/EXTERNS.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "libgultra_inferred/cseq.H"
extern s32 Defs_FindSortedValue(s32,s32,s32);
extern f32 Menu_ExpandFloatHighWord(s32);
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
