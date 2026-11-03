#include "COMMON/ACTOR_DEFINITION.H"
#include "include_asm.h"
#include "COMMON/RESULTS.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "RENDER/EFFECT_POOL_OPERATIONS.H"
#include "COMMON/TRIPLE.H"
#include "OVLGAME/EFFECT.H"
#include "PLAYERAI/PLAYERAI__PLAYERAI.H"

/* EFFECT.CPP */
/* EFFECT.CPP */

/* Initialises the pool of 32 effect slots in a world record: threads them into a free list (slot 0 has no
 * predecessor, slot 31 no successor), empties the live list, sets up the two shared effect definitions
 * and points every slot at the default definition through SetN64_InitializeEffectSlot. */
void Effect_InitEffectPool(EffectSlotPool *world) {
    s32 i;

    world->free = world->slots;
    world->tail = 0;
    world->head = 0;
    for (i = 0; i < EFFECT_SLOTS - 1; i++) {
        world->slots[i].next = &world->slots[i + 1];
        world->slots[i].prev = (struct EffectSlot *)((u32)world->slots + (i - 1) * sizeof(world->slots[0]));
    }
    world->slots[0].prev = 0;
    world->slots[EFFECT_SLOTS - 1].next = 0;
    Playerai_InitializeCompactAnimationState(&g_defaultEffectDefinition);
    ((ActorDefinitionHeader *)&g_defaultEffectDefinition)->kind = 8;
    ((ActorDefinitionHeader *)&g_defaultEffectDefinition)->flags = 1;
    ((ActorDefinitionHeader *)&g_defaultEffectDefinition)->send = 0;
    Playerai_InitializeCompactAnimationState(&g_boundedEffectDefinition);
    ((EffectDefinitionBounds *)&g_boundedEffectDefinition)->header.kind = 8;
    ((EffectDefinitionBounds *)&g_boundedEffectDefinition)->header.flags = 0;
    ((EffectDefinitionBounds *)&g_boundedEffectDefinition)->header.send = 0;
    ((EffectDefinitionBounds *)&g_boundedEffectDefinition)->boundsA = g_effectDefinitionDefaultBounds;
    ((EffectDefinitionBounds *)&g_boundedEffectDefinition)->boundsB = g_effectDefinitionDefaultBounds;
    for (i = 0; i < EFFECT_SLOTS; i++) {
        SetN64_InitializeEffectSlot(&world->slots[i]);
    }
}
