#ifndef BATCH_BATCH_H
#define BATCH_BATCH_H
struct EntryBlock;
void Batch_InitEntryBatch(struct EntryBlock *batch, s32 *entries, s32 count);
struct SlotPool;
void Batch_InitSlotPool(struct SlotPool *pool, s32 owner);
#endif
