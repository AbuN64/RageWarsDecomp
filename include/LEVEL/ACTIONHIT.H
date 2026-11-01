#ifndef LEVEL_ACTIONHIT_H
#define LEVEL_ACTIONHIT_H
#include "COMMON/OBJRECAT30.H"

extern void Action_EnableTriggerActor(struct Trigger *trigger);
extern void Action_DisableTriggerActor(struct Trigger *trigger);
extern void Action_SetEnterHandler(void *unused0, struct Dest *enterHandler);
#endif
