#ifndef AI_DEVICES_MOVINGAI_MOVINGAI_H
#define AI_DEVICES_MOVINGAI_MOVINGAI_H
#include "types.h"
#include "Common/small_records.h"

struct GameModeEnableView;
struct GameModeEnableView {
    char pad0[0x1D];
    u8 local;
};
typedef struct GameModeEnableView GameModeEnableView;

struct Params;
struct Params {
    Triple v;
    s32 w;
};
typedef struct Params Params;

struct ActorMotionState;
struct Dest;
struct LevelActor;
struct Shared_Actor;
struct Trigger;
extern void MovingAI_UpdateTriggerDelay(struct LevelActor *actor, struct ActorMotionState *motionState);
extern void MovingAI_RequestInactiveOnEvent(void *a, struct WeaponEventSource *b);
extern void MovingAI_SetActorStateActive(void *actor);
extern void MovingAI_ClearActorStateActive(void *actor);
extern void MovingAI_InitializeDeviceHealth(struct LevelActor *actor, struct Dest *deviceState);
extern void Triggered_StartTriggerAnimation(void *actor, void *motionState, struct Trigger *trigger);
extern void Triggered_ClearCollisionAndActivate(struct Shared_Actor *actor);
extern void Triggered_DeactivateForSequence(struct Shared_Actor *actor, s32 *sequenceFlags);
extern void Triggered_ResetMotionState(void *object, void *state);
#endif
