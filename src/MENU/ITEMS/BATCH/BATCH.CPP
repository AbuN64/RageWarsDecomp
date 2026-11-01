#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/LONE/PARTICLE_PITCH_MATRIX_SCRATCH.H"

extern void List_InitializeIntrusive(void *list, s32 nextOffset, s32 prevOffset);
extern void List_AppendIntrusive(void *list, void *node);
extern void Playerai_InitializeCompactAnimationState(void *definition);
extern void BuildPitchMatrix(void *matrix, f32 angle);
extern s32 g_particleActorDefinition;

typedef struct EntryBlock {
    s32 *entries;
    s32 half;
} EntryBlock;

typedef struct PoolVertex {
    s16 x;
    s16 y;
    s16 z;
    s16 flag;
    s16 s;
    s16 t;
    u8 color[4];
} PoolVertex;

extern PoolVertex g_particleSpriteVertices[4];

typedef struct PoolSlot {
    u8 kind;                                   /* +0x0 */
    char pad1[0x17];
    s32 *definition;                           /* +0x18 */
    char pad1C[0x5C - 0x1C];
    s32 word5C;                                /* +0x5C */
    char pad60[0x1DC - 0x60];
    s32 word1DC;                               /* +0x1DC */
    char pad1E0[4];
    s32 word1E4;                               /* +0x1E4 */
    char pad1E8[0x1F8 - 0x1E8];
} PoolSlot;

typedef struct SlotPool {
    PoolSlot slots[128];                /* +0x0 */
    char freeList[20];                       /* +0xFC00 */
    char liveList[20];                       /* +0xFC14 */
    char groups[3][0x14];                      /* +0xFC28 */
    s32 owner;                                 /* +0xFC64 */
    s32 count;                                 /* +0xFC68 */
} SlotPool;

/* Sets up a batch of count 0x40-byte entries starting at entries: remembers the block and half its count, runs
 * guMtxIdent on every entry, then hands the batch to Map_ResetFramePool. */
void Batch_InitEntryBatch(EntryBlock *batch, s32 *entries, s32 count) {
    s32 i;

    batch->entries = entries;
    batch->half = count / 2;
    for (i = 0; i < count; i++) {
        guMtxIdent(&entries[i * 16]);
    }
    Map_ResetFramePool(batch);
}

/* Initialises a pool of 128 slots of 0x1F8 bytes: every slot gets kind 2, the shared definition g_particleActorDefinition and
 * cleared words; the free list takes all slots, then the live list and the three group lists are emptied. Sets
 * the unit quad g_particleSpriteVertices (corner signs and texture corners per vertex, white), builds the matrix g_particlePitchMatrixScratch
 * for a quarter turn and records the owner word. */
void Batch_InitSlotPool(SlotPool *pool, s32 owner) {
    s32 i;
    s32 corner;

    for (i = 0; i < 128; i++) {
        pool->slots[i].definition = &g_particleActorDefinition;
        pool->slots[i].kind = 2;
        pool->slots[i].word5C = 0;
        pool->slots[i].word1DC = 0;
        pool->slots[i].word1E4 = 0;
    }
    List_InitializeIntrusive(pool->freeList, 488, 492);
    for (i = 0; i < 128; i++) {
        List_AppendIntrusive(pool->freeList, &pool->slots[i]);
    }
    List_InitializeIntrusive(pool->liveList, 496, 500);
    for (i = 0; i < 3; i++) {
        List_InitializeIntrusive(pool->groups[i], 488, 492);
    }
    Playerai_InitializeCompactAnimationState(&g_particleActorDefinition);
    for (corner = 0; corner < 4; corner++) {
        PoolVertex *v = &g_particleSpriteVertices[corner];
        switch (corner) {
        case 0:
            v->x = -1;
            v->y = 1;
            v->s = -0x8000;
            v->t = -0x8000;
            break;
        case 1:
            v->x = 1;
            v->y = 1;
            v->s = 0;
            v->t = -0x8000;
            break;
        case 2:
            v->x = 1;
            v->y = -1;
            v->s = 0;
            v->t = 0;
            break;
        case 3:
            v->x = -1;
            v->y = -1;
            v->s = -0x8000;
            v->t = 0;
            break;
        }
        v->z = 0;
        v->flag = 0;
        v->color[0] = 0xFF;
        v->color[1] = 0xFF;
        v->color[2] = 0xFF;
        v->color[3] = 0xFF;
    }
    BuildPitchMatrix(g_particlePitchMatrixScratch, 1.5707964f);
    pool->owner = owner;
    pool->count = 0;
}

