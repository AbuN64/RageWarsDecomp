#ifndef ENGINE_RUMBLE_H
#define ENGINE_RUMBLE_H
#include "types.h"
#include "Common/vector.h"
struct IntrusiveList;
struct Clip;

struct RumbleEffectNode {
    struct RumbleEffectNode *previous;
    struct RumbleEffectNode *next;
    struct Clip *key;
    CVector3 position;
    f32 value0;
    f32 value1;
    u32 amplitudeHandle; /* 0x20 */
    char pad24[8];
    u32 lifetimeHandle; /* 0x2C */
    char pad30[8];
    struct RumbleEffectNode **owner;
};
typedef struct RumbleEffectNode RumbleEffectNode;

/* Shared free/active node pool initialized by Rumble_InitPoolNodes_Controller. */
struct RumbleNodePoolView {
    IntrusiveList free;
    IntrusiveList active;
    s32 baseLevel;
};
#include "types.h"
#include "Common/snapshot_actor.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"


struct Clip;
struct RumbleEffectNode;
struct RumbleSpatialPoolView;

typedef struct RumbleSpatialPoolView RumbleSpatialPoolView;

struct RumbleSpatialPoolView {
    char pad0[0x14];
    IntrusiveList activeEffects;
    char pad14[0x28 - 0x14 - sizeof(IntrusiveList)];
    union { s32 baseLevelWord; f32 baseLevel; };
};

struct RumbleEffectNode;

struct RumbleNodePoolView;

extern float g_spatialEffectFalloffUnitGain;

struct RumbleSpatialEffectNode;

struct RumbleSpatialEffectNode {
    char pad0[4];
    struct RumbleSpatialEffectNode *next;
    void * effectClip;
    char pad8[0xC - 0x8 - sizeof(void*)];
    union { Triple positionTriple; CVector3 position; };
    char padC[0x18 - 0xC - sizeof(Triple)];
    f32 radius;
    char pad18[0x1C - 0x18 - sizeof(f32)];
    f32 strength;
    char pad1C[0x20 - 0x1C - sizeof(f32)];
    union {
        struct { unsigned int amplitudeCurveWord; char pad20[8]; };
        SampledEffectCurveState amplitudeCurve;
    };
    union {
        struct { unsigned int lifetimeCurveWord; char pad2C[8]; };
        SampledEffectCurveState lifetimeCurve;
    };
    void ** ownerSlot;
};

typedef struct RumbleSpatialEffectNode RumbleSpatialEffectNode;

typedef struct RumbleNodePoolView RumbleNodePoolView;

extern void Rumble_InitEffectNode(struct RumbleEffectNode *effectNode, struct Clip *effectClip, CVector3 effectPosition, f32 valueStart, f32 valueEnd, void **ownerSlot);
extern s32 Rumble_TestEffectHandleCompletion(struct RumbleEffectNode *effectNode);
extern void Rumble_ClearEffectOwnerSlot(char *object);
extern f32 Rumble_EvaluateSpatialEffectNode(struct RumbleEffectNode *effectNode, u32 positionXBits, u32 positionYBits, u32 positionZBits);
void Rumble_FreeAllPoolNodes(struct RumbleNodePoolView *effectPool);
void Rumble_InitPoolNodes(struct RumbleNodePoolView *effectPool, void *nodeStorage, s32 nodeCount);
struct ActorFlagsWordView;
void Rumble_SetEffectOwnerSlot(struct ActorFlagsWordView *effectNode, int ownerSlotAddress);
extern struct RumbleEffectNode *Rumble_AllocatePoolNode(struct RumbleNodePoolView *pool, struct Clip *key, CVector3 position, f32 value0, f32 value1, struct RumbleEffectNode **owner);
#endif
