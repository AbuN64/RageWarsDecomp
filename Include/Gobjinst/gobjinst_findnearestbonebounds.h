#ifndef GOBJINST_GOBJINST_FINDNEARESTBONEBOUNDS_H
#define GOBJINST_GOBJINST_FINDNEARESTBONEBOUNDS_H
struct LevelPlacedActorRecord;
void Gobjinst_InitializePlacedActor(void *actorStorage, struct LevelPlacedActorRecord *placement, s32 mode, s32 index);
extern void *g_actorTypeOperations[];
extern s32 Rumble_TestActorStateBit(void *, void *);

extern void Gobjinst_DispatchActorTypeUpdate(char *actor);
#endif
