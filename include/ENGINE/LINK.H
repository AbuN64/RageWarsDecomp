#ifndef ENGINE_LINK_H
#define ENGINE_LINK_H
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/OSPIHANDLE_S.H"
#include "COMMON/LIGHT_VOLUME_AND_TRIGGER_VIEWS.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "COMMON/LISTHEADER.H"

struct VertexColorMeshView {
    u8 pad00[4];
    s32 count;
    u8 records[1];
};

extern s32 Link_SumWorldSectionCounts(void);

extern void Link_ClearActorFlagMask(struct LevelActor *object);

extern void Link_SetActorFlagMask(LevelActor *actor);

extern void Link_RequestOwnerTrack(s32, s32 unused1, s32);

extern void Link_RequestGlobalTrack(s32);

extern void Link_CaptureActorTransform(void *, void *);

extern void Link_DispatchTriggerAudio(s32, s32, Trigger *trigger);

extern void Link_DeactivateActorState(struct Shared_Actor *actor, s32 *stateFlags);

extern void Link_PlayTriggerSoundCallback(int unused0, int unused1, void *);

extern void Link_SelectTriggerMusic(void *);

extern void Link_PlayTriggerSound(void *);

extern void Link_SetTriggerTrackCallback(int unused0, int unused1, void *);

extern void Link_SetTriggerTrack(void *);

extern void Link_ClearActorStateBit(struct Shared_Actor *actor);

extern void Link_SetActorStateBit(void *object);

extern void Link_DispatchMatchingTriggers(Trigger *triggers, s32 count, s32 require, s32 enter, s32 exclude, s32 group, struct Player *arg);

extern s32 Link_CheckTriggerMessage(void *trigger, struct Player *player);

struct WorldSectionCountView {
    char pad0[0x1500];
    s32 sectorCount;
};
struct WorldSectionResourceView {
    unsigned char padding_0[5384];
    s32 *resource;
};
#endif
