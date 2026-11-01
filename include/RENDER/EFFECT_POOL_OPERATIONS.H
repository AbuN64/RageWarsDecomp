#ifndef RENDER_EFFECT_POOL_OPERATIONS_H
#define RENDER_EFFECT_POOL_OPERATIONS_H
#include "COMMON/RESULTS.H"
extern void *SetN64_GetChunkPayload(int *chunk, int *sizeOut);
extern void SetN64_InitializeEffectSlot(struct EffectSlot *effectSlot);
extern void SetN64_UpdateEffectPool(EffectSlotPool *world);
#endif
