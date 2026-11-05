#ifndef BATCH_BATCH_H
#define BATCH_BATCH_H
struct EntryBlock;
void Batch_InitEntryBatch(struct EntryBlock *batch, s32 *entries, s32 count);
struct SlotPool;
struct EffectSystem;
void Batch_InitSlotPool(struct EffectSystem *pool, s32 owner);
#endif
