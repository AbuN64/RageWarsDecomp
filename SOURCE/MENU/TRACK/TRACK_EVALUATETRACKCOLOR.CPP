#include "include_asm.h"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/ENTRYRECAT8V4.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "TYPES.H"
#include "MENU/TRACK_EVALUATETRACKCOLOR.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

/* Evaluates the position keyframe track 1 of the current record's resource at time t: holds the
   first or last key's position outside the track, is zero when the track is empty, and otherwise
   blends the surrounding keys' positions linearly with the vector scale and add helpers. Vector
   counterpart of Track_EvaluateTrackOpacity. */

extern void Graphu64_ScaleVector(CVector3 *out, CVector3 *in, f32 scale);
extern void Graphu64_AddVec3(CVector3 *out, CVector3 *a, CVector3 *b);

CVector3 Track_EvaluateTrackColor(f32 t) {
    s32 *track;
    PositionKey *key;
    s32 count;
    f32 u;
    CVector3 result;
    CVector3 a;
    CVector3 b;

    track = SetN64_GetPackSection(g_cinemaSequenceState->resource, 1);
    count = track[1];
    key = (PositionKey *)(track + 2);
    if (count == 0) {
        result.x = 0.0f;
        result.y = 0.0f;
        result.z = 0.0f;
        return result;
    } else if (t <= key[0].time) {
        result.x = key[0].x;
        result.y = key[0].y;
        result.z = key[0].z;
        return result;
    } else if (key[count - 1].time <= t) {
        result.x = key[count - 1].x;
        result.y = key[count - 1].y;
        result.z = key[count - 1].z;
        return result;
    } else {
        while (key->time < t) {
            key++;
        }
        u = (t - key[-1].time) / (key->time - key[-1].time);
        a.x = key[-1].x;
        a.y = key[-1].y;
        a.z = key[-1].z;
        b.x = key->x;
        b.y = key->y;
        b.z = key->z;
        Graphu64_ScaleVector(&a, &a, (1.0f) - u);
        Graphu64_ScaleVector(&b, &b, u);
        Graphu64_AddVec3(&result, &a, &b);
    }
    return result;
}

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const float g_trackCameraInterpolationUnitConstantsDe[2] = {
    1.0f, 1.0f,
};
#endif
