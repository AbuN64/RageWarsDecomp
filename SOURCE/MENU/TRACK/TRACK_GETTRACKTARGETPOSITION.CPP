#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/ENTRYRECAT8V4.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "TYPES.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

/* Samples the current record's clip sequence at time t: walks clip list 0 accumulating each
   clip's end time (the time of its last 0x24-byte key) until the clip spanning t is found or the
   ends are passed, then evaluates that clip's keys through Track_EvaluateCameraSpline at the time into the
   clip, frozen at the clip start when the clip's second flag word is set; the track-1 counterpart of Track_GetTrackEyePosition, matched the same way. */








extern CVector3 Track_EvaluateCameraSpline(SplineNode *keys, s32 count, f32 t);

CVector3 Track_GetTrackTargetPosition(f32 t) {
    s32 i;
    s32 idx;
    s32 count;
    TrackTransformKey *keys;
    s32 *clip;
    f32 start;
    f32 end;

    start = 0.0f;
    count = 0;
    keys = 0;
    idx = 0;
    i = 0;
    end = start;
    while (i < *((s32 *)SetN64_GetPackSection(g_cinemaSequenceState->resource, 0))) {
        idx = i;
        clip = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(g_cinemaSequenceState->resource, 0), idx), 1);
        count = clip[1];
        keys = (TrackTransformKey *)(clip + 2);
        start = end;
        end = start + keys[count - 1].time;
        if (idx == 0 && t <= start) {
            break;
        }
        if (idx == *((s32 *)SetN64_GetPackSection(g_cinemaSequenceState->resource, 0)) - 1 && end < t) {
            break;
        }
        i = idx + 1;
        if (start <= t && t <= end) {
            break;
        }
    }
    if (((s32 *)SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(g_cinemaSequenceState->resource, 0), idx), 2))[1] != 0) {
        t = start;
    }
    return Track_EvaluateCameraSpline((SplineNode *)keys, count, t - start);
}
