#ifndef MENU_TRACK_TYPES_H
#define MENU_TRACK_TYPES_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"

typedef struct SharedTrackObjectPrefix {
    u32 reservedElements[2];
    CVector3 position;
    u8 reservedBytes[0x3C];
} SharedTrackObjectPrefix;

typedef struct SharedTrackObject {
    SharedTrackObjectPrefix prefix;
    u8 reservedBytes1[0x1C];
    f32 yaw;
} SharedTrackObject;

typedef struct SharedTrackCamera {
    u8 reservedBytes2[0x28];
    f32 distance;
    f32 pitch;
    u8 reservedBytes3[8];
    CVector3 position;
} SharedTrackCamera;


#endif
