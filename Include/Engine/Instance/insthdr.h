#ifndef ENGINE_INSTANCE_INSTHDR_H
#define ENGINE_INSTANCE_INSTHDR_H
#include "types.h"
extern f32 InstHdr_GetActorTerritoryRadius(void *object);
#include "Common/vector.h"
extern void *SetN64_SpawnModelEffect(char *container, s32 *referenceCounter, s32 modelId, CVector3 rotation, CVector3 position, s32 effectOwner, f32 initialLifetime);
#include "Frontend/frontend.h"
#include "Ai/portal_isnodemovementblocked.h"
#include "Common/probe.h"
#include "Common/objb.h"
#include "types.h"

struct ActorSurfaceSampleVector;

typedef struct ActorSurfaceSampleVector ActorSurfaceSampleVector;

struct ActorSurfaceHeightView;

typedef struct ActorSurfaceHeightView ActorSurfaceHeightView;

struct InstanceItemValueView;

struct InstanceItemValueView {
    unsigned char kind;
    char pad[0x33];
    void *value;
    unsigned flags;
};

extern int InstHdr_GetTypeOneItemValue(void *actorStorage);
struct Shared_CollisionActor;
extern f32 InstHdr_GetActorGroundHeight(struct Shared_CollisionActor *actor, s32 unusedFlag);
extern s32 InstHdr_CanActorCastShadow(void *actor);

struct ActorSurfaceHeightView {
    unsigned char padding_0[12];
    f32 surfaceBaseHeight;
    unsigned char padding_10[4];
    void *groundTriangle;
};

struct LevelActor;

extern int InstHdr_IsDefinitionKindOne(struct LevelActor *actor);

struct ActorSurfaceSampleVector {
    f32 a;
    s32 b;
    f32 c;
};

struct ActorSurfaceKeyView;

struct StateFlags;

struct ActorSurfaceKeyView {
    char pad[0x14];
    struct StateFlags *key;
};

extern s32 InstHdr_IsActorControllerActive(char *actor);

extern float g_defaultActorShadowRadius;

extern void Insthdr_PlayActorGraphSound(void *actor, CVector3 position, s32 sound, f32 volume);
extern s32 Insthdr_GetModelPropertyFlag1(void *obj);
extern s32 Insthdr_GetModelPropertyFlag2(void *obj);
extern void Graphu64_InterpolateQuaternionWithLinearFallback(CQuatern *, f32, CQuatern *, CQuatern *);


extern int InstHdr_GetActorMotionIndex(void *record);
extern s32 InstHdr_HasEnabledMotionHooks(void *actor);
#endif
