#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "RENDER/SETN64_GETPACKSECTION.H"






/* The copied prefix is exactly 0x50 bytes. */
#include "MENU/TRACK_TYPES.H"





/* The two adjacent track constants are consumed at base and base+4. */



#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ENTRYRECAT8V4.H"
#include "MENU/TRACK_EVALUATETRACKOPACITY.H"
#include "COMMON/TRIPLE.H"

extern f32 g_trackSplineRangeScale;


f32 Track_EvaluateTrackOpacity(f32 t) {
    s32 *track;
    TrackOpacityKey *key;
    s32 count;
    f32 u;
    f32 v;

    track = SetN64_GetPackSection(g_cinemaSequenceState->resource, 1);
    count = track[1];
    key = (TrackOpacityKey *)(track + 2);
    if (count == 0) {
        v = 0.0f;
    } else if (t <= key[0].time) {
        v = key[0].value;
    } else if (key[count - 1].time <= t) {
        v = key[count - 1].value;
    } else {
        while (key->time < t) {
            key++;
        }
        u = (t - key[-1].time) / (key->time - key[-1].time);
        v = key[-1].value * ((*(&g_trackLinearInterpolationConstants + 1)) - u) + key->value * u;
    }
    v *= 2.0f * g_trackSplineRangeScale + g_trackSplineOutputBounds[0];
    v -= g_trackSplineRangeScale;
    if (g_trackSplineOutputBounds[0] < v) {
        v = g_trackSplineOutputBounds[0];
    }
    if (v < 0.0f) {
        v = 0.0f;
    }
    return v;
}
