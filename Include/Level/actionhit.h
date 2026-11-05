#ifndef LEVEL_ACTIONHIT_H
#define LEVEL_ACTIONHIT_H
#include "Common/breakable_hits.h"

extern void Action_EnableTriggerActor(struct Trigger *trigger);
extern void Action_DisableTriggerActor(struct Trigger *trigger);
extern void Action_SetEnterHandler(void *ownerActor, struct Dest *enterHandler);
#endif
