#ifndef COMMON_KEYRECAT1C_H
#define COMMON_KEYRECAT1C_H
#include "TYPES.H"

struct TrackTransformKey;
typedef struct TrackTransformKey TrackTransformKey;

struct TrackTransformKey;
struct TrackTransformKey {
    char pad0[0x1C];
    f32 time;
    char pad20[4];
};

struct PositionKey;
typedef struct PositionKey PositionKey;

struct PositionKey;
struct PositionKey {
    f32 x;
    f32 y;
    f32 z;
    f32 pad;
    f32 time;
};

struct TrackResourceEntry;
typedef struct TrackResourceEntry TrackResourceEntry;

struct TrackResourceEntry;
struct TrackResourceEntry {
    s32 id0;
    s32 id4;
    s32 id8;
    s32 flags;
    char pad10[0x28];
    f32 scaleA0; /* record + 0x38, context + 0xA0 */
    f32 aspectRatio; /* record + 0x3C, context + 0xA4 */
    u32 settings[2]; /* context + 0xA8, + 0xAC */
    u32 unknown48;
};
#endif
