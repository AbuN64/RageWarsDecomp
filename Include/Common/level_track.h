#ifndef COMMON_LEVEL_TRACK_H
#define COMMON_LEVEL_TRACK_H
#include "Common/level_placement.h"
struct Shared_Placed;
s32 Scene_FindPlacedObjectsByKey(void *world, s32 kind, s32 key, struct Shared_Placed *out, s32 max);
#endif
