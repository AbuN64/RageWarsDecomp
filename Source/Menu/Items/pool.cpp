#include "Common/objb.h"
#include "Menu/scene_resource_preview_and_collision_views.h"
#include "Common/heap_arena_entry.h"
#include "types.h"
#include "Engine/Cache/list.h"
#include "Pool/pool.h"

/* Initialises the pool's active and free object lists, moves the pool's four entries onto the free
   list and clears the pool's effect mask. */
void Pool_InitEntryPool(Scene *pool) {
    s32 i;
    struct SkyLayerRuntimeView *entry;

    List_InitializeIntrusive(&pool->activeObjects, 0, 4);
    List_InitializeIntrusive(&pool->freeObjects, 0, 4);
    for (i = 0, entry = pool->entries; i < 4; i++, entry++) {
        List_AppendIntrusive(&pool->freeObjects, entry);
    }
    pool->effectMask = 0;
}
