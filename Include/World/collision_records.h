#ifndef WORLD_COLLISION_RECORDS_H
#define WORLD_COLLISION_RECORDS_H
#include "types.h"

struct Block70 {
    s32 w[28];
};

typedef struct Block70 Block70;

struct CollisionSegmentLimit {
    char pad[0x10];
    f32 value;
};

typedef struct CollisionSegmentLimit CollisionSegmentLimit;

#endif
