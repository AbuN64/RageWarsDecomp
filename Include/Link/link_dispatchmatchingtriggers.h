#ifndef LINK_LINK_DISPATCHMATCHINGTRIGGERS_H
#define LINK_LINK_DISPATCHMATCHINGTRIGGERS_H
#include "Ai/player_death_playerai.h"
void Link_ActivateTrigger(struct TriggerActivationView *trigger);
struct Shared_Actor;
void Link_DispatchActorLinks(struct Shared_Actor *actor, s32 event, void *context);
#endif
