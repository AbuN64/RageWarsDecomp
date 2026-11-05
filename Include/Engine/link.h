#ifndef ENGINE_LINK_H
#define ENGINE_LINK_H
#include "Ai/playerai_symbols.h"
#include "types.h"
#include "Common/vector4f.h"
#include "Common/resident_event_handler.h"
#include "Common/ospihandle_s.h"
#include "Common/level_actor.h"
#include "Common/world.h"
#include "Common/listheader.h"

struct WorldTrigger;
struct SceneLightVolume;
struct Trigger;
struct VertexColorMeshView {
    u8 pad00[4];
    s32 count;
    u8 records[1];
};
typedef struct VertexColorMeshView VertexColorMeshView;
struct TriggerActivationView;
typedef struct TriggerActivationView TriggerActivationView;
struct TriggerActorTransformView;
typedef struct TriggerActorTransformView TriggerActorTransformView;
struct TriggerTargetTransformView;
typedef struct TriggerTargetTransformView TriggerTargetTransformView;

extern s32 Link_SumWorldSectionCounts(void);

extern void Link_ClearActorFlagMask(struct LevelActor *object);

extern void Link_SetActorFlagMask(struct LevelActor *actor);

extern void Link_RequestOwnerTrack(s32, s32 triggerEvent, s32);

extern void Link_RequestGlobalTrack(s32);

extern void Link_CaptureActorTransform(struct TriggerActorTransformView *actor, struct TriggerTargetTransformView *transform);

extern void Link_DispatchTriggerAudio(s32, s32, struct Trigger *trigger);

extern void Link_DeactivateActorState(struct Shared_Actor *actor, s32 *stateFlags);

/* A trigger record as the sound triggers read it: six bytes of header, then the sound id (play) or the track/music resource id. */
typedef struct LinkTriggerRecord {
    u8 header[6];
    union {
        s16 soundId;
        u16 resourceId;
    };
} LinkTriggerRecord;

extern void Link_PlayTriggerSoundCallback(int platform, int triggerEvent, struct LinkTriggerRecord *trigger);

extern void Link_SelectTriggerMusic(struct LinkTriggerRecord *trigger);

extern void Link_PlayTriggerSound(struct LinkTriggerRecord *trigger);

extern void Link_SetTriggerTrackCallback(int platform, int triggerEvent, struct LinkTriggerRecord *trigger);

extern void Link_SetTriggerTrack(struct LinkTriggerRecord *trigger);

extern void Link_ClearActorStateBit(struct Shared_Actor *actor);

extern void Link_SetActorStateBit(struct Shared_Actor *object);

extern void Link_DispatchMatchingTriggers(struct Trigger *triggers, s32 count, s32 require, s32 enter, s32 exclude, s32 group, struct Player *arg);

extern s32 Link_CheckTriggerMessage(struct LinkTriggerMessageView *trigger, struct Player *player);

struct VertexColorMeshView;
void Link_AnimateVertexColors(struct VertexColorMeshView *object, u8 *colors);
extern void Link_DispatchTriggerExit(struct WorldTrigger *trigger);
extern f32 Link_GetLightAnimationOffset(struct SceneLightVolume *link);
extern s32 g_gameFrameCounter;
#endif
