#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VIEWFLAGS.H"
#include "CAMERA/FADE_AND_COLOR_BLEND_VIEWS.H"

/** Copy the three-word vector at source offset 0x260. */
void *Gsky_GetObjectPositionAt260(void *destination, void *source) {
    CameraObjectPositionView *source_record = source;

    Triple *out = destination;
    *out =
        source_record->position;
    return destination;
}
