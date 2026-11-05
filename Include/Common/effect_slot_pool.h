#ifndef COMMON_EFFECT_SLOT_POOL_H
#define COMMON_EFFECT_SLOT_POOL_H
#include "types.h"
#include "Common/vector.h"
struct ActorDefinitionHeader;
/* The world record opens with a pool of 32 effect slots of 0x1E0 bytes each (Effect_InitEffectPool). */
#define EFFECT_SLOTS 32
#define EFFECT_STRIDE 0x1E0
/* One separately allocated 0x1E0-byte bounded effect with its free/live links. */
typedef struct EffectSlot EffectSlot;
struct EffectSlot {
    s8 active;
    char pad1[3];
    s16 model;
    char pad6[2];
    CVector3 position;
    s32 owner;
    struct ActorDefinitionHeader *definition;
    CVector3 rotation;
    char pad28[0x28];
    s32 resource;
    s32 animation;
    s32 frame;
    s32 frameState;
    char pad60[0x108];
    s32 collisionState;
    f32 collisionScale;
    s32 collisionFlags;
    s32 angle;
    s32 angleState;
    f32 minX;
    f32 minY;
    f32 minZ;
    f32 maxX;
    f32 maxY;
    f32 maxZ;
    s32 boundsState;
    char pad198[4];
    /* The producer stores a halfword; visibility reads the same address as a word.
       Native little-endian visibility uses flags, as the word mask is big-endian. */
    union { u16 flags; s32 visibilityFlags; }; /* +0x19C */
    char pad1A0[0x24];
    s32 effectState;
    f32 lifetime;
    f32 lifetimeState;
    s32 state;
    s32 *counter;
    struct EffectSlot *prev;
    struct EffectSlot *next;
};
struct EffectSlotPool {
    struct EffectSlot slots[EFFECT_SLOTS];
    struct EffectSlot *free;
    struct EffectSlot *head;
    struct EffectSlot *tail;
};
typedef struct EffectSlotPool EffectSlotPool;
#endif
