#ifndef COMMON_LEVEL_INPUT_H
#define COMMON_LEVEL_INPUT_H
#include "COMMON/SHAREDPLAYER.H"
typedef struct LevelPlacedActorRecord LevelPlacedActorRecord;
struct LevelPlacedActorRecord {
    s32 actorId;
    f32 vec4[3];
    f32 vec10[3];
    u16 actorKind;
    u16 actorVariant;
    u16 resource20;
    u16 resource22;
    s16 amount24;
    u8 spawnFlags;
    u8 ownerIndex;
};
#endif
