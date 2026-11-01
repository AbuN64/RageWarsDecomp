#ifndef COMMON_SHARED_SCRATCH_H
#define COMMON_SHARED_SCRATCH_H
#include "COMMON/SHAREDPLAYER.H"

typedef struct Shared_Scratch Shared_Scratch;
struct Shared_Scratch {
    union {
        struct {
            s32 damage[5]; /* +0x0: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
        } view0_0;
        struct {
            CVector3 to; /* +0x0: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
        } view0_1;
    } views0;
};

#endif
