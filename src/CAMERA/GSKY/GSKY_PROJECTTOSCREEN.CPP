#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/VIEWFLAGS.H"
#include "TYPES.H"

extern void Graphu64_ProjectPoint(void *, void *, CVector3 *);




void Gsky_ProjectToScreen(s32 view, s32 point, f32 *screenX, f32 *screenY) {
    CVector3 value;
    f32 half;

    Graphu64_ProjectPoint(view + 480, point, &value);
    half = (f32)(g_hudReferenceViewportWidth / 2);
    *screenX = value.x * half + half;
    *screenY = value.y * (f32)(-g_hudReferenceViewportHeight / 2) +
            (f32)(g_hudReferenceViewportHeight / 2);
}
