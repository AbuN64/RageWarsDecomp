#ifndef WORLD_INTEGERSTATE170_H
#define WORLD_INTEGERSTATE170_H
#include "TYPES.H"



extern float k_motionOpenCompletionSpeed;




struct LevelActor;
struct ActorMotionState;


typedef struct ActorMotionEvent {
    u8 pad0[0x4];
    u16 key; /* 0x4 */
    u8 pad6[0x4];
    u16 id; /* 0xA */
} ActorMotionEvent;
#endif
