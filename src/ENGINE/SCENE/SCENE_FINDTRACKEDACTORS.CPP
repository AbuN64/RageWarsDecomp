#include "../../../sdk/include/LIBC.H"
#include "include_asm.h"
#include "COMMON/WORLDRECAT1B6A4.H"
#include "COMMON/MEASUREDRECAT14V4.H"
#include "COMMON/MEASUREDRECAT14V2.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "COMMON/MANAGER.H"
#include "COMMON/LIGHT_VOLUME_AND_TRIGGER_VIEWS.H"
#include "COMMON/SCENERECAT10C0.H"
#include "COMMON/COLORENTRY.H"
#include "ENGINE/SCENE.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "SCENE/SCENE_FINDTRACKEDACTORS.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "ENGINE/DEFS.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "COMMON/CACHE_RELEASERESOURCE.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/WORLDSORTENTRY.H"

/* SCENE_14.CPP */

extern s32 SetN64_GetDirectoryEntry(s32 *directory, s32 bankOffset, s32 level);

extern s32 Cache_RequestWordCountedResourcePinned(s32 cacheAddress, s32 *handle, s32 resourceKey, void *loadTag);

extern void **Cache_RequestPackSection(s32 cacheAddress, s32 handle, s32 sectionSelector, s32 resourceKey, s32 world, s32 resourceTag, void *loadTag);



extern void Scene_ReleaseCachedLevelData(Shared_World *world);

extern s32 SetN64_LocatePackSection(s32, s32, s32, s32 *);

extern s32 g_cResource_UnpackRequestEntry;

extern void Cache_UnlockResource(s32 cacheContext, s32 resource);

s32 SetN64_CollectVisibleEffectNodes(s32, s32);

/* Advances the fractional animation clock and updates every active object with the resulting tick flag. */

extern void Statinst_DispatchAttachmentEvents(s32, s32);

/* Releases the resource of each of the owner's listed entries through Cache_UnlockResource, then clears the counters at 0x944, 0xC4C and 0x10BC, and moves the entry count to 0x1500 and zeroes it. */

void *Scene_GetPlatformRoutePoint(void *a, s32 b, s32 c) {
    void *r1;
    ResidentDataChunk *r2;
    s32 field;

    r1 = SetN64_GetPackSection(((Shared_World *)a)->routeCount, b);
    r2 = SetN64_GetPackSection(r1, 1);
    field = r2->width;
    return r2->data + (c * field);
}

s32 Scene_FindNearestRouteFrame(void *worldPointer, s32 routeIndex, void *queryPosition) {
    CVector3 position;
    AnimationPoseFrameSet *list;
    Shared_World *world = worldPointer;
    AnimationPoseFrame *item;
    f32 distSq;
    f32 bestDist;
    f32 bestIndex;
    s32 count;
    s32 index;

    bestIndex = g_nearestRouteFrameAbsentIndex;
    bestDist = 0.0f;
    index = 0;
    list = SetN64_GetPackSection(SetN64_GetPackSection(world->routeCount, routeIndex), 1);
    count = list->count;
    item = list->frames;
    if (count > 0) {
        do {
            Graphu64_SubtractVectors(&position, queryPosition, item);
            distSq = (position.x * position.x) +
                     (position.y * position.y) +
                     (position.z * position.z);
            if ((bestIndex < 0.0f) || (distSq < bestDist)) {
                bestIndex = (f32)index;
                bestDist = distSq;
            }
            index += 1;
            item++;
        } while (index < count);
    }
    return (s32)bestIndex;
}

void Scene_CopyLevelName(Shared_World *world, s32 type, void *levelName, s32 maximumBytes) {
    s32 specialTable;
    s32 resourceKey;
    s32 levelIndexHandle;
    CachedResource *node;
    s32 count;

    resourceKey = SetN64_GetDirectoryEntry(world->resourceDirectory, world->resourceBank, type);
    levelIndexHandle = Cache_RequestWordCountedResourcePinned(0, &specialTable, resourceKey, g_levelIndexText);
    node = Cache_RequestPackSection(0, specialTable, 8, resourceKey, (s32)world, 0, &g_sceneLevelNameRequestTagDe + 4);
    count = node->dataSize;
    if (maximumBytes < count) {
        count = maximumBytes;
    }
    Libc_CopyBytes(levelName, node->data, count);
    Cache_ReleaseResource(0, (s32)node);
    if (world->level != type) {
        Cache_ReleaseResource(0, levelIndexHandle);
    }
}

void *Scene_GetBlLevelData(void *world, s32 record) {
    s32 sectionSize;
    void **resource;
    s32 key;
    s32 size;
    s32 one;

    if (((struct RegionFreeBlockSizeView *)(world))->value == 0 || ((struct WorldTrackedRecordView *)(world))->value != record) {
        Scene_ReleaseCachedLevelData(world);
        if (((struct WorldResourceKeyView *)(world))->value != 0) {
            size = 16;
            one = 1;
            resource = Cache_RequestResource(0, ((struct WorldResourceKeyView *)(world))->value,
                                     ((struct WorldResourceKeyView *)(world))->value,
                                     ((struct RegionAllocatedBlockSizeView *)(world))->value, size, 0, 0,
                                     g_sceneResourceRequestSpareDe, one);
            if (resource != 0) {
                key = SetN64_LocatePackSection((s32)*resource, ((struct WorldResourceKeyView *)(world))->value,
                                    record, &sectionSize);
                Cache_ReleaseResource(0, resource);
                if ((((struct WorldResourceHandleView *)(world))->value =
                     Cache_RequestResource(0, key, key, sectionSize, size, 0,
                                   &g_cResource_UnpackRequestEntry, g_sceneUnpackRequestSpare, one)) != 0) {
                    ((struct WorldTrackedRecordView *)(world))->value = record;
                } else {
                    return 0;
                }
            }
        }
    }
    if (((struct WorldResourceHandleView *)(world))->value != 0) {
        return *((struct SceneLevelNameView *)(world))->value;
    }
    return 0;
}

void Scene_ReleaseCachedGeometry(void *world) {
    SceneSceneDrawCachedOpaqueGeometry *object = world;
    s32 *list;
    s32 val;

    if (object->loaded != 0) {
        list = (s32 *) SetN64_GetPackSection(object->model, 0);
        if (*list != 0) {
            do {
                val = *list;
                list += 1;
                Cache_UnlockResource(0, val);
            } while (*list != 0);
        }
        Cache_ReleaseResource(0, object->loaded);
        object->loaded = 0;
        object->model = 0;
    }
}

void Scene_CollectVisibleEffects(s32 results) {
    SetN64_CollectVisibleEffectNodes(results + 0x11778, results);
}

/** Clear the object field at offset 0x10BC. */
void Scene_ClearTransparentInstanceCount(void *object) {
    SceneActiveResourceCountView *record = object;
    record->activeResourceCount = 0;
}

/** Clear the scene counters and linked state fields. */
void Scene_ClearSceneObjectCounts(void *object) {
    ((Shared_World *)object)->interactiveCount = 0;
    ((Shared_World *)object)->moverCount = 0;
    ((Shared_World *)object)->queuedCount = 0;
    ((Shared_World *)object)->registeredCount = 0;
    ((Shared_World *)object)->kind1Count = 0;
    ((Shared_World *)object)->flaggedCount = 0;
    ((Shared_World *)object)->kind5Count = 0;
    ((Shared_World *)object)->model64FCount = 0;
    ((Shared_World *)object)->model64DCount = 0;
    ((Shared_World *)object)->drawableCount = 0;
    ((Shared_World *)object)->sectorCount = 0;
}

void Scene_UpdateStaticEventInstances(StateSceneUpdateStaticEventInstances *scene)
{
  f32 nextEventPhase;
  s32 object;
  int first_index;
  s32 instanceIndex;
  s32 dispatchAll;

  nextEventPhase = scene->eventPhase + 1.0f;
  scene->eventPhase = nextEventPhase;
  dispatchAll = 1;
  if (!(nextEventPhase > 0.0f))
  {
    dispatchAll = 0;
  }
  if (dispatchAll != 0)
  {
    scene->eventPhase = (f32) (nextEventPhase - ((f32) (((s32) nextEventPhase) + 1)));
  }
  instanceIndex = (first_index = 0);
  if (scene->trackedInstanceCount > first_index)
  {
    do
    {
      object = scene->values[instanceIndex];
      Statinst_DispatchAttachmentEvents(object, dispatchAll);
      instanceIndex += 1;
    }
    while (instanceIndex < scene->trackedInstanceCount);
  }
}

s32 Scene_GetLevelActorIndex(void *container, void *actorStorage) {
    Container *scene = container;
    LevelActor *actor = actorStorage;
    void *base;

    if (actor->flags & 0x80000) {
        return -1;
    }
    base = scene->actors;
    if (actorStorage >= base &&
        (char *)actorStorage <= (char *)base + ((u32)scene->actorCount * sizeof(LevelActor) - sizeof(LevelActor))) {
        return ((u32)actorStorage - (u32)base) / 744;
    }
    return -1;
}

void Scene_FindSelectedTriggerRange(char *world, s32 useAlternateRecords, s32 group, s32 *recordsOutput, s32 *countOutput) {
    s32 firstRecordIndex;
    s32 lastRecordIndex;
    s32 recordIndex;
    s32 recordCount;
    s32 offset;

    if (useAlternateRecords != 0) {
        recordIndex = (s32)((Shared_World *)world)->alternateRecordIndex;
        recordCount = ((Shared_World *)world)->alternateRecordCount;
    } else {
        recordIndex = (s32)((Shared_World *)world)->recordIndex;
        recordCount = ((Shared_World *)world)->recordCount;
    }
    if (Defs_FindSortedGroupRange(recordIndex, recordCount, group, &firstRecordIndex, &lastRecordIndex) != 0) {
        offset = firstRecordIndex * 20;
        if (useAlternateRecords != 0) {
            *recordsOutput = (s32)((Shared_World *)world)->alternateRecordArray + offset;
        } else {
            *recordsOutput = (s32)((Shared_World *)world)->recordArray + offset;
        }
        *countOutput = (lastRecordIndex - firstRecordIndex) + 1;
    } else {
        *recordsOutput = 0;
        *countOutput = 0;
    }
}

void Scene_UnlockActiveSectionResources(OwnerSceneUnlockActiveSectionResources *owner) {
    s32 i;
    s32 n;
    s32 count;
    Triple *entries;

    n = owner->count;
    entries = owner->entries;
    for (i = 0; i < n; i++) {
        Cache_UnlockResource(0, entries[i].x);
    }
    count = owner->count;
    owner->reservedWord944 = 0;
    owner->reservedWordC4C = 0;
    owner->activeResourceCount = 0;
    owner->count = 0;
    owner->prevCount = count;
}

void Scene_ResetTransitionViewport(void) {
    s32 viewportWidth;
    s32 viewportHeight;

    Cinema_SetLoopMode(0);
    Cinema_SetResponse(g_sceneTransitionCinemaResponseDe);
    viewportWidth = 480;
    if (g_frontendCurrentVideoModeIndex == 0) {
        viewportWidth = 380;
        viewportHeight = 220;
    } else {
        viewportHeight = 360;
    }
    Cinema_SetViewport(viewportWidth, viewportHeight, 0, 0);
}

void Scene_CacheBlLevelData(void *world, s32 sectionIndex) {
    s32 sectionSize;
    void **resource;
    s32 key;
    s32 size;
    s32 one;

    if (((struct RegionFreeBlockSizeView *)(world))->value == 0 || ((struct WorldTrackedRecordView *)(world))->value != sectionIndex) {
        Scene_ReleaseCachedLevelData(world);
        if (((struct WorldResourceKeyView *)(world))->value != 0) {
            size = 16;
            one = 1;
            resource = Cache_RequestResource(0, ((struct WorldResourceKeyView *)(world))->value,
                                     ((struct WorldResourceKeyView *)(world))->value,
                                     ((struct RegionAllocatedBlockSizeView *)(world))->value, size, 0, 0,
                                     g_sceneResourceRequestSpareDe, one);
            if (resource != 0) {
                key = SetN64_LocatePackSection((s32)*resource, ((struct WorldResourceKeyView *)(world))->value,
                                    sectionIndex, &sectionSize);
                Cache_ReleaseResource(0, resource);
                if ((((struct WorldResourceHandleView *)(world))->value =
                     Cache_RequestResource(0, key, key, sectionSize, size, 0,
                                   &g_cResource_UnpackRequestEntry, g_sceneUnpackRequestSpare, one)) != 0) {
                    ((struct WorldTrackedRecordView *)(world))->value = sectionIndex;
                }
            }
        }
    }
}

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
float k_SceneFindtrackedactorsEncodedWords[3] = {
    1.0f, 1.0f, 1.0f,
};
#endif

/* 8028B64C_9.CPP */
extern void SetN64_GetPackSectionSize(s32 table, s32 index);

void Scene_ReleaseCachedLevelData(Shared_World *world) {
    void *handle;

    handle = world->resourceHandle;
    if (handle != 0) {
        Cache_ReleaseResource(0, handle);
        world->resourceHandle = 0;
        world->resourceKey = -1;
    }
}

void Scene_AccessLevelStateSection(struct WorldSceneDispatchEnabledEntityTrigger *world, s32 usePrimaryLevels, s32 index, s32 levelIndex) {
    void *base;
    void *table;

    if (usePrimaryLevels != 0) {
        base = world->levels;
    } else {
        base = world->secondaryLevels;
    }
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(base, 0), levelIndex), index);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    SetN64_GetPackSection(table, 1);
}

void Scene_SetSelectedLevelStateBit(struct WorldSceneDispatchEnabledEntityTrigger *world, s32 usePrimaryLevels, s32 index, s32 levelIndex, s32 bitIndex, s32 enabled) {
    void *base;
    void *table;
    u8 *base1;
    u8 *base2;
    s32 mask;
    s32 idx;
    s32 idx2;

    if (usePrimaryLevels != 0) {
        base = world->levels;
    } else {
        base = world->secondaryLevels;
    }
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(base, 0), levelIndex), index);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    base1 = (u8 *) SetN64_GetPackSection(table, 1);
    base2 = base1;
    mask = 1 << (bitIndex & 7);
    if (enabled != 0) {
        idx = bitIndex;
        if (bitIndex < 0) {
            idx = bitIndex + 7;
        }
        base1[idx >> 3] |= mask;
        return;
    }
    idx2 = bitIndex;
    if (idx2 < 0) {
        idx2 += 7;
    }
    base2[idx2 >> 3] &= ~mask;
}

s32 Scene_TestSelectedLevelStateBit(struct WorldSceneDispatchEnabledEntityTrigger *world, s32 usePrimaryLevels, s32 index, s32 levelIndex, s32 bitIndex) {
    void *base;
    void *table;
    u8 *stateBits;
    s32 mask;
    s32 i;

    if (usePrimaryLevels != 0) {
        base = world->levels;
    } else {
        base = world->secondaryLevels;
    }
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(base, 0), levelIndex), index);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32)table, 1);
    stateBits = (u8 *)SetN64_GetPackSection(table, 1);
    mask = 1 << (bitIndex & 7);
    i = bitIndex;
    if (i < 0) {
        i += 7;
    }
    return (stateBits[i >> 3] & mask) != 0;
}

s32 Scene_TestSecondaryLevelBit(void *worldStorage, s32 index, s32 bitIndex) {
    Shared_World *world = worldStorage;
    void *table;
    u8 *stateBits;
    s32 mask;
    s32 i;

    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(world->secondaryLevels, 0), index), 0);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32)table, 1);
    stateBits = (u8 *)SetN64_GetPackSection(table, 1);
    mask = 1 << (bitIndex & 7);
    i = bitIndex;
    if (i < 0) {
        i += 7;
    }
    return (stateBits[i >> 3] & mask) != 0;
}

s32 Scene_TestActorBitForLevel(Field_void_80 *world, s32 index, s32 actorIndex) {
    void *table;
    u8 *stateBits;
    s32 mask;
    s32 i;

    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(world->value, 0), index), 0);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32)table, 1);
    stateBits = (u8 *)SetN64_GetPackSection(table, 1);
    mask = 1 << (actorIndex & 7);
    i = actorIndex;
    if (i < 0) {
        i += 7;
    }
    return (stateBits[i >> 3] & mask) != 0;
}

s32 Scene_TestRecordBitForLevel(Field_void_80 *world, s32 index, s32 recordIndex) {
    void *table;
    u8 *stateBits;
    s32 mask;
    s32 i;

    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(world->value, 0), index), 1);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32)table, 1);
    stateBits = (u8 *)SetN64_GetPackSection(table, 1);
    mask = 1 << (recordIndex & 7);
    i = recordIndex;
    if (i < 0) {
        i += 7;
    }
    return (stateBits[i >> 3] & mask) != 0;
}

s32 Scene_TestTriggerBitForLevel(Field_void_80 *world, s32 index, s32 triggerIndex) {
    void *table;
    u8 *stateBits;
    s32 mask;
    s32 i;

    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(world->value, 0), index), 2);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32)table, 1);
    stateBits = (u8 *)SetN64_GetPackSection(table, 1);
    mask = 1 << (triggerIndex & 7);
    i = triggerIndex;
    if (i < 0) {
        i += 7;
    }
    return (stateBits[i >> 3] & mask) != 0;
}

/* world_actorscan.CPP */
s32 Scene_GetTriggerCounterAddress(Shared_World *world, s32 triggerIndex) {
    void *packSectionResult;
    packSectionResult = SetN64_GetPackSection(world->bitSections, 1);
    SetN64_GetPackSection(packSectionResult, 0);
    return SetN64_GetPackSection(packSectionResult, 1) + triggerIndex;
}

void Scene_SwapDistanceSortEntries(WorldSortEntry *left, WorldSortEntry *right) {
    WorldSortEntry tmp;

    tmp = *left;
    *left = *right;
    *right = tmp;
}

s32 Scene_CompareDistanceAscending(WorldSortEntry *left, WorldSortEntry *right) {
    s32 result;
    result = 1;
    if ((left->distance) < (right->distance)) {
        result = -1;
    }
    return result;
}

s32 Scene_CompareDistanceDescending(WorldSortEntry *left, WorldSortEntry *right)
{
  f32 leftDistance;
  s32 sortOrder;
  leftDistance = left->distance;
  sortOrder = 1;
  if ((right->distance) < leftDistance)
  {
    sortOrder = -1;
  }
  return sortOrder;
}

void Scene_CollectTypeFourteenActors(Shared_World *world) {
    s32 found;
    s32 clear_index;
    LevelActor *record;
    struct Shared_Pickup **clear_ptr;
    struct Shared_Pickup **out;
    s32 wanted_type;

    found = 0;
    clear_index = 15;
    record = world->actors;
    world->specialActorCount = 0;
    do {
        world->specialActors[clear_index] = 0;
        clear_index--;
    } while (clear_index >= 0);

    if (world->actorCount > 0) {
        clear_index = 0;
        wanted_type = 14;
        do {
            if (((struct Def *)record->definition)->type == wanted_type) {
                world->specialActors[found] = record;
                found++;
            }
            if (found >= 16) {
                break;
            }
            clear_index++;
            if (clear_index >= world->actorCount) {
                break;
            }
            record++;
        } while (1);
    }
    world->specialActorCount = found;
}

extern LevelActor *g_sceneTrackedActors[4];
extern LevelActor *g_fragTagObjectiveActor;
extern s32 Scene_GetModelIdAtIndex(Shared_World *world, s32 id);
void Scene_FindTrackedActors(Shared_World *world) {
    LevelActor *actor = world->actors;
    s32 i;
    g_fragTagObjectiveActor = 0;
    for (i = 0; i < 4; i++) {
        g_sceneTrackedActors[i] = 0;
    }
    for (i = 0; i < world->actorCount; actor++, i++) {
        struct Def *def = (struct Def *)actor->definition;
        if (def->type == 3) {
            if (Scene_GetModelIdAtIndex(&g_world, def->id) == 3031) {
                g_fragTagObjectiveActor = actor;
                return;
            }
        } else if (def->type == 10) {
            switch (actor->type) {
            case 1619:
                g_sceneTrackedActors[0] = actor;
                break;
            case 1620:
                g_sceneTrackedActors[1] = actor;
                break;
            case 1621:
                g_sceneTrackedActors[2] = actor;
                break;
            case 1622:
                g_sceneTrackedActors[3] = actor;
                break;
            }
        }
    }
}
