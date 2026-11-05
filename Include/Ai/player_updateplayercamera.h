#ifndef AI_PLAYER_UPDATEPLAYERCAMERA_H
#define AI_PLAYER_UPDATEPLAYERCAMERA_H
#include "types.h"
#include "Common/small_records.h"

struct Desc;
struct Desc {
    char pad[0x108];
    s32 caps[4];
};

#include "types.h"
extern f32 Menu_MeasureLine(u8 *p, f32 sx, f32 sy);
#endif
