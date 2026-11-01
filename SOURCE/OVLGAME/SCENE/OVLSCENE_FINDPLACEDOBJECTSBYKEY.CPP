#include "../../../sdk/include/LIBC.H"
#include "include_asm.h"
#include "COMMON/WORLD.H"
#include "COMMON/OBJB.H"
#include "MENU/SCENE_RESOURCE_PREVIEW_AND_COLLISION_VIEWS.H"
#include "COMMON/S1.H"
#include "TYPES.H"
#include "COMMON/PPDECOM_UNPACKRESOURCE.H"
#include "MENU/ITEMS/SCENE/SELECTION_PREVIEW_OPERATIONS.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "ENGINE/DEFS.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
/* Loads the preview resource into the sound buffer when idle, while the adjacent helper resets a changed selection. */
extern char g_cResource_UnpackRequestEntry[];
extern char g_gamePersistentData[];
extern char g_sceneCollisionStorage[];
extern int Control_IsSnapshotActive(void);
extern void Scene_SetSelection(ItemsPreviewStateB *,int,int);
void Scene_LoadPreviewBufferB(ItemsPreviewStateB *state) {
 int *resource;
 int id;
 if(Control_IsSnapshotActive()==0) {
  resource=Cache_RequestResource(0,state->resource,state->resource,state->bank,0,0,g_cResource_UnpackRequestEntry,g_gamePersistentData,1);
  Libc_CopyBytes(g_sceneCollisionStorage,(const void *)*resource,0x5000);
  Cache_ReleaseResource(0,resource);
 }
}
/* Loads the preview resource into the sound buffer when idle, while the adjacent helper resets a changed selection. */
extern void Scene_SetSelection(ItemsPreviewStateB *,int,int);
void Scene_ChangePreviewSelection(ItemsPreviewStateB *state,int selection) {
 if(selection!=state->selection) {
  state->changed=0;
  Scene_SetSelection(state,~selection,0);
 }
}
/* Resets part of a large state block: sets its word at offset 0x1B410 to 2 and clears the words
   at 0x1B414 to 0x1B41C and 0x1B434 to 0x1B440. */
void Scene_ResetSelectionState(char *state) {
    ((Shared_World *)state)->selectionState = 2;
    ((Shared_World *)state)->frozen = 0;
    ((Shared_World *)state)->selectionTimer = 0;
    ((Shared_World *)state)->selectionFlags = 0;
    ((Shared_World *)state)->selectionValues[0] = 0;
    ((Shared_World *)state)->selectionValues[1] = 0;
    ((Shared_World *)state)->selectionValues[2] = 0;
    ((Shared_World *)state)->selectionValues[3] = 0;
}
/* Copies up to max of a track's placed objects whose key matches into out: finds the key's index range in the track's sorted key table through Defs_FindSortedGroupRange, queues each object in that range of the given kind (any kind for -1) on a local list through List_InitializeIntrusive and List_PrependIntrusive, then takes them back off through List_CountIntrusiveNodes and List_RemoveIntrusive, copying each 20-byte object, and returns how many were copied. */
extern Node_Items_FindPlacedObjectsByKey *List_CountIntrusiveNodes(ListRec *);
s32 Scene_FindPlacedObjectsByKey(void *world, s32 kind, s32 key, Shared_Placed *out, s32 max) {
    Shared_World *track = world;
    ListRec list;
    Node_Items_FindPlacedObjectsByKey nodes[64];
    s32 first;
    s32 last;
    s32 found;
    s32 *keys;
    s32 *objectTable;
    Shared_Placed *objects;
    Node_Items_FindPlacedObjectsByKey *node;
    s32 i;
    s32 match;
    s32 count;

    found = 0;
    count = (keys = SetN64_GetPackSection(track->placedObjectTable, 0))[1];
    keys += 2;
    objectTable = SetN64_GetPackSection(track->placedObjectTable, 1);
    objects = (Shared_Placed *)(objectTable + 2);
    if (Defs_FindSortedGroupRange(keys, count, key, &first, &last) != 0) {
        List_InitializeIntrusive(&list, 4, 8);
        node = nodes;
        for (i = first; i <= last; i++) {
            match = 1;
            if (kind != -1) {
                match = objects[i].kind == kind;
            }
            if (match) {
                node->index = i;
                List_PrependIntrusive(&list, node);
                node++;
            }
        }
        for (max--; max != -1; max--) {
            if (list.count == 0) {
                return found;
            }
            node = List_CountIntrusiveNodes(&list);
            out[found++] = objects[node->index];
            List_RemoveIntrusive(&list, node);
        }
    }
    return found;
}
/* SetN64_GetPackSection sections of Shared_World.placedObjectTable: 0 holds one key per placed object,
   1 the placed objects in the same order. */
typedef struct PlacedObjectKeys {
    s32 tag;
    s32 count;
    s32 keys[1];
} PlacedObjectKeys;
typedef struct PlacedObjectList {
    s32 tag;
    s32 count;
    Shared_Placed objects[1];
} PlacedObjectList;
extern f32 Graphu64_GetPointDistance(f32 *a, f32 *b);
/* Finds the placed object of the given kind nearest to position, copies it to out and returns its key; returns 0
   when none is found or the nearest is object 0 (index 0 doubles as "none"). */
s32 Scene_FindNearestPlacedObject(Shared_World *world, f32 *position, s32 kind, Shared_Placed *out) {
    s32 i;
    s32 nearest;
    PlacedObjectKeys *keys;
    PlacedObjectList *list;
    s32 *key;
    Shared_Placed *objects;
    s32 count;
    f32 distance;
    f32 nearestDistance;
    keys = SetN64_GetPackSection(world->placedObjectTable, 0);
    count = keys->count;
    key = keys->keys;
    list = SetN64_GetPackSection(world->placedObjectTable, 1);
    nearestDistance = 3.4028235e+38f;
    objects = list->objects;
    nearest = 0;
    for (i = 0; i < count; i++) {
        if (objects[i].kind == kind) {
            distance = Graphu64_GetPointDistance(&objects[i].pos.x, position);
            if (distance < nearestDistance) {
                nearestDistance = distance;
                nearest = i;
            }
        }
    }
    if (nearest != 0) {
        *out = objects[nearest];
    }
    if (nearest != 0) {
        return key[nearest];
    }
    return 0;
}
