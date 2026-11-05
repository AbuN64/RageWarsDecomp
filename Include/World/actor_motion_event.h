#ifndef WORLD_ACTOR_MOTION_EVENT_H
#define WORLD_ACTOR_MOTION_EVENT_H
#include "types.h"



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
