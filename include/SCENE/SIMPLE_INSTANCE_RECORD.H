#ifndef SCENE_SIMPLE_INSTANCE_RECORD_H
#define SCENE_SIMPLE_INSTANCE_RECORD_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
typedef struct CROMSimpleInstance {
    s32 visBits;
    CVector3 position;
    f32 maxRadius;
    u16 type;
    u16 region;
    u16 flags;
    u16 id;
    u16 variation;
    s8 rotY;
    u8 pad;
} CROMSimpleInstance;
#endif
