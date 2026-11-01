#ifndef COMMON_LEVEL_PLACEMENT_H
#define COMMON_LEVEL_PLACEMENT_H
#include "COMMON/SHAREDPLAYER.H"
typedef struct Shared_Placed Shared_Placed;
struct Shared_Placed {
    CVector3 pos; /* +0x0: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    f32 heading; /* +0xC: spawn heading */
    s16 kind; /* +0x10: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    s16 pad12; /* +0x12: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
};
#endif
