#ifndef RENDER_TRIGGERED_UPDATETRIGGEREDMOTION_H
#define RENDER_TRIGGERED_UPDATETRIGGEREDMOTION_H
#include "COMMON/REC.H"

extern void Triggered_SetPairedDefinitionBytes(struct LevelActor *actor, int unused, struct Trigger *triggerRecord);
extern void Triggered_DisableTriggeredActorState(struct Trigger *trigger);
extern void Triggered_EnableTriggeredActorState(struct Trigger *trigger);

extern void Triggered_InitializeMotionState(void *object, void *state);
s32 Triggered_SelectMotionSound(void *context, struct TriggeredMotionSoundOption *option);
#endif
