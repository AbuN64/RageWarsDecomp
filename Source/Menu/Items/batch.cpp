#include "include_asm.h"
#include "types.h"
#include "Common/shared_particleinstance.h"
#include "Common/Lone/particle_pitch_matrix_scratch.h"
#include "Batch/batch.h"
#include "Engine/Cache/list.h"
#include "Game/builddirectionmatrix.h"
#include "Playerai/playerai__playerai.h"
#include "Common/runtime_declarations.h"
#include "Menu/Items/Batch/batch_symbols.h"

typedef struct EntryBlock {
    s32 *entries;
    s32 half;
} EntryBlock;

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
void Batch_InitSlotPool(struct EffectSystem *pool, s32 owner) {
    s32 i;
    s32 corner;

    for (i = 0; i < 128; i++) {
        pool->particles[i].inst.definition = (ActorDefinitionHeader *)&g_particleActorDefinition;
        pool->particles[i].inst.kind = 2;
        pool->particles[i].flags = 0;
        pool->particles[i].sound = 0;
        pool->particles[i].list = 0;
    }
    List_InitializeIntrusive(&pool->free, 488, 492);
    for (i = 0; i < 128; i++) {
        List_AppendIntrusive(&pool->free, &pool->particles[i]);
    }
    List_InitializeIntrusive(&pool->groups, 496, 500);
    for (i = 0; i < 3; i++) {
        List_InitializeIntrusive(&pool->lists[i], 488, 492);
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
    pool->resource = owner;
    pool->last = 0;
}
