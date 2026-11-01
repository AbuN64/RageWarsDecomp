#ifndef ENGINE_RUMBLE_H
#define ENGINE_RUMBLE_H
#include "TYPES.H"
#include "COMMON/ACTORRECAT5E0.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"

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

extern void Rumble_InitEffectNode(RumbleEffectNode *effectNode, Clip *effectClip, CVector3 effectPosition, f32 valueStart, f32 valueEnd, void **ownerSlot);
extern s32 Rumble_TestEffectHandleCompletion(RumbleEffectNode *effectNode);
extern void Rumble_ClearEffectOwnerSlot(char *object);
extern f32 Rumble_EvaluateSpatialEffectNode(f32 *effectNode, u32 positionXBits, u32 positionYBits, u32 positionZBits);
#endif
