#ifndef MENU_TRACK_TABLES_H
#define MENU_TRACK_TABLES_H
#include "Common/track_transform_keys.h"
typedef struct Shared_TrackClip {
    s32 stride, count;
    TrackTransformKey keys[1];
} Shared_TrackClip;
typedef struct Shared_TrackCues {
    s32 stride, count;
    PositionKey cues[1];
} Shared_TrackCues;
typedef struct Shared_TrackTable {
    s32 stride, count;
    TrackResourceEntry entries[1];
} Shared_TrackTable;
#endif
