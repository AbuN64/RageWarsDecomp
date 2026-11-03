#ifndef LINK_LINK_DISPATCHMATCHINGTRIGGERS_H
#define LINK_LINK_DISPATCHMATCHINGTRIGGERS_H
void Link_ActivateTrigger(void *trigger);
struct Shared_Actor;
void Link_DispatchActorLinks(struct Shared_Actor *actor, s32 event, void *context);
#endif
