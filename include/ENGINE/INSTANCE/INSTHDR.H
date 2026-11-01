#ifndef ENGINE_INSTANCE_INSTHDR_H
#define ENGINE_INSTANCE_INSTHDR_H
#include "COMMON/PROBE.H"
#include "COMMON/OBJB.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"

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
#endif
