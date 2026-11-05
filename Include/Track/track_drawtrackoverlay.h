#ifndef TRACK_TRACK_DRAWTRACKOVERLAY_H
#define TRACK_TRACK_DRAWTRACKOVERLAY_H
#include "types.h"
struct SharedTrackObject;
struct TrackRequestIds;
void Track_RequestTrackByIds(struct SharedTrackObject *owner, struct TrackRequestIds *obj);
typedef struct TrackRequestIds {
    char pad0[0x4];
    unsigned short trackId;
    char pad4[0xA - 0x4 - sizeof(unsigned short)];
    unsigned short variantId;
} TrackRequestIds;

#endif
