#include "COMMON/OBJB.H"
#include "MENU/SCENE_RESOURCE_PREVIEW_AND_COLLISION_VIEWS.H"
#include "COMMON/S1.H"
#include "TYPES.H"

/* Initialises the two lists at offsets 0x8B4 and 0x8A0 of a pool with node offsets 0 and 4
   through List_InitializeIntrusive, adds the pool's four entries of 0x228 bytes to the second list through
   List_AppendIntrusive and clears the halfword at 0x8C8. */




void Pool_InitEntryPool(MenuEntryPoolCountView *pool) {
    s32 i;
    struct MenuEntryPoolEntry *entry;

    List_InitializeIntrusive(&pool->active, 0, 4);
    List_InitializeIntrusive(&pool->free, 0, 4);
    for (i = 0, entry = pool->entries; i < 4; i++, entry++) {
        List_AppendIntrusive(&pool->free, entry);
    }
    pool->count = 0;
}
