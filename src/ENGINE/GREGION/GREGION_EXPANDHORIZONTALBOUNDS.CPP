#include "include_asm.h"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/MODEL_TREE_REGION_OPERATIONS.H"
#include "TYPES.H"

/** Expand the four-float X/Z bounds in bounds over pointCount packed vectors. */
void Gregion_ExpandHorizontalBounds(f32 *bounds, s32 pointCount, CVector3 *points)
{
    f32 value;
    f32 bound;
    s32 i;
    i = 0;
    if (pointCount > 0) {
        do {
            value = points[i].x;
            bound = bounds[0];
            if (!(value <= bound)) {
                value = bound;
            }
            bounds[0] = value;
            value = points[i].z;
            bound = bounds[1];
            if (!(value <= bound)) {
                value = bound;
            }
            bounds[1] = value;
            value = points[i].x;
            bound = bounds[2];
            if (!(bound <= value)) {
                value = bound;
            }
            bounds[2] = value;
            value = points[i].z;
            bound = bounds[3];
            if (!(bound <= value)) {
                value = bound;
            }
            bounds[3] = value;
            i += 1;
        } while (i < pointCount);
    }
}
/** Empty adjacent entry point included in Gregion_ExpandHorizontalBounds's Splat span. */
void Gregion_NoOperation(void)
{
}

#if defined(VERSION_US)
/* Alignment fill to the next 16-byte object boundary. */
unsigned char g_GregionExpandhorizontalboundsTrailingBytesAlignmentPad[4] = { 0x00, 0x06, 0x00, 0x00 };
#endif

