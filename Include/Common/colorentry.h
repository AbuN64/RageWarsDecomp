#ifndef COMMON_COLORENTRY_H
#define COMMON_COLORENTRY_H
#include "types.h"
#include "Common/world.h"
#include "Common/sharedplayer.h"
extern float g_transitionAlphaUnsignedConversionBase;


struct ColorEntry;
struct ColorEntry {
    f32 value;
    u8 red;
    u8 green;
    u8 blue;
    u8 pad;
};


struct StridedTable;


struct ColorEntry;
typedef struct ColorEntry ColorEntry;

















extern float g_nearestRouteFrameAbsentIndex;






/* Clip section 1 has a stride/count header and 0x38-byte pose records.
 * Position is used to select the nearest frame; the remaining pose data is
 * consumed by the animation routines reached through Scene_GetPlatformRoutePoint. */
typedef struct AnimationPoseFrame {
    CVector3 position;
    u8 poseData[0x38 - sizeof(CVector3)];
} AnimationPoseFrame;

#endif
