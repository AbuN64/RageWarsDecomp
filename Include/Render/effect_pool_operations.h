#ifndef RENDER_EFFECT_POOL_OPERATIONS_H
#define RENDER_EFFECT_POOL_OPERATIONS_H
#include "Common/results.h"
struct EffectSlotPool;
extern void *SetN64_GetChunkPayload(int *chunk, int *sizeOut);
extern void SetN64_InitializeEffectSlot(struct EffectSlot *effectSlot);
extern void SetN64_UpdateEffectPool(struct EffectSlotPool *world);
#endif
