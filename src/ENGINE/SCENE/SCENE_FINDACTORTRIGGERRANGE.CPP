#include "COMMON/WORLDRECAT1B6A4.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "COMMON/PACKED.H"
#include "COMMON/LIGHT_VOLUME_AND_TRIGGER_VIEWS.H"
#include "TYPES.H"
#include "ENGINE/DEFS.H"
#include "COMMON/APPROACHLOCATION.H"
extern s32 SetN64_LocatePackSection(void *directory, s32 bankOffset, s32 sectionIndex, s32 *sectionSizeOut);

extern void SetN64_SpawnModelEffect(s32, s32, s32, Triple, Triple, s32, f32);


extern f32 Region_GetPolygonHeight(void *, f32, f32);

extern f32 Graphu64_GetTrianglePlaneHeight(void *node, f32 x, f32 z);

extern s32 SetN64_GetDirectoryEntry(s32 *directory, s32 bankOffset, s32 level);

extern void Link_ActivateTrigger(void *trigger);

void Scene_SpawnUnrotatedEffect(s32 worldAddress, s32 ownerId, Triple position, s32 modelId, f32 lifetime) {
    Triple zero;

    zero.x = 0;
    zero.y = 0;
    zero.z = 0;
    SetN64_SpawnModelEffect(&((Shared_World *)worldAddress)->system11778, 0, modelId, zero, position, ownerId, lifetime);
}

void *Scene_ResolveFloorPolygon(void *triangle, CVector3 *position) {
    f32 lower;
    f32 upper;
    f32 value;

    if (triangle != 0 &&
        Region_IsPointInTriangleXZ(triangle, position->x,
                          position->z) != 0) {
        if (!(((Triangle *)triangle)->flags & 0x40)) {
            return triangle;
        }
        lower = Region_GetPolygonHeight(triangle,
            position->x, position->z);
        upper = Graphu64_GetTrianglePlaneHeight(triangle,
            position->x, position->z);
        value = position->y;
        if (lower <= value && value <= upper) {
            return triangle;
        }
    }
    return Scene_FindFloorPolygon(&g_world, position);
}

/* Searches the counted pointer list at offset 0x1B620 of a world record for the first entry whose definition id at 0x18->0xC equals the given id, returning it or null. */







SceneDefinitionActorView *Scene_FindSwitchByDefinitionId(World *world, s32 id) {
    s32 i;
    SceneDefinitionActorView *found = 0;

    for (i = 0; i < world->count; i++) {
        if (world->list[i]->def->input == id) {
            found = world->list[i];
            break;
        }
    }
    return found;
}

void Scene_LocateTextureResource(void *world, s32 sectionIndex, s32 *resourceAddressOutput, s32 *sectionSizeOut) {
    *resourceAddressOutput = SetN64_LocatePackSection((((struct SceneCounterPairView *) ((s8 *) world))->packDirectory), (((struct SceneCounterPairView *) ((s8 *) world))->packBankOffset), sectionIndex, sectionSizeOut);
}

s32 Scene_GetIndexedModelResource(Shared_World *world, s32 type) {
    s32 *directory = world->indexedDirectory;

    if (type < *directory) {
        return SetN64_GetDirectoryEntry(directory, world->indexedBank, type);
    }
    return 0;
}

s32 Scene_FindAlternateTriggerRange(char *world, u16 *triggerIds, s32 *firstIndex, s32 *lastIndex) {
    s32 groupFirst;
    s32 groupLast;
    s32 matchCount;
    s32 alternateRecordIndex;
    s32 alternateRecordCount;

    matchCount = Defs_FindSortedGroupRange(alternateRecordIndex, alternateRecordCount, *triggerIds,
        (alternateRecordIndex = (s32)((Shared_World *)world)->alternateRecordIndex,
         alternateRecordCount = ((Shared_World *)world)->alternateRecordCount, &groupFirst), &groupLast);
    if (matchCount != 0) {
        *firstIndex = (s32)((Shared_World *)world)->alternateRecordArray + (groupFirst * 20);
        matchCount = (groupLast - groupFirst) + 1;
        *lastIndex = matchCount;
    } else {
        *firstIndex = 0;
        *lastIndex = 0;
    }
    return matchCount;
}

void Scene_FindActorTriggerRange(char *world, void *levelActor, s32 *firstIndex, s32 *lastIndex) {
    s32 groupFirst;
    s32 last;
    s32 index;
    u32 first;
    s32 lastOffset;
    s32 sortedGroupRangeResult;
    s32 recordIndex;
    s32 recordCount;

    if (!(((LevelActor *)levelActor)->flags & 0x80000)) {
        first = (u32)((Shared_World *)world)->actors;
        index = -1;
        if ((u32)levelActor >= first) {
            lastOffset = ((Shared_World *)world)->actorCount * 744;
            lastOffset -= 744;
            if (first + lastOffset >= (u32)levelActor) {
                index = ((u32)levelActor - first) / 744;
            }
        }
    } else {
        index = -1;
    }
    if (index == -1) {
        *lastIndex = 0;
        return;
    }
    sortedGroupRangeResult = Defs_FindSortedGroupRange(recordIndex, recordCount, index,
        (recordIndex = (s32)((Shared_World *)world)->recordIndex,
         recordCount = ((Shared_World *)world)->recordCount, &groupFirst), &last);
    if (sortedGroupRangeResult != 0) {
        *firstIndex = (s32)((Shared_World *)world)->recordArray + (groupFirst * 20);
        *lastIndex = (last - groupFirst) + 1;
    } else {
        *firstIndex = 0;
        *lastIndex = 0;
    }
}

void Scene_ActivateTriggersOfKind(Shared_World *world, s32 triggerKind) {
    s32 primaryRemaining;
    s32 alternateRemaining;
    Record14 *trigger;
    Record14 *alternateTrigger;

    primaryRemaining = world->recordCount;
    trigger = world->recordArray;
    primaryRemaining -= 1;
    if (primaryRemaining != -1) {
        do {
            if (trigger->kind == triggerKind) {
                Link_ActivateTrigger(trigger);
            }
            primaryRemaining -= 1;
            trigger = trigger + 1;
        } while (primaryRemaining != -1);
    }
    alternateTrigger = world->alternateRecordArray;
    alternateRemaining = world->alternateRecordCount;
    alternateRemaining -= 1;
    if (alternateRemaining != -1) {
        do {
            if (alternateTrigger->kind == triggerKind) {
                Link_ActivateTrigger(alternateTrigger);
            }
            alternateRemaining -= 1;
            alternateTrigger = alternateTrigger + 1;
        } while (alternateRemaining != -1);
    }
}

s32 Scene_TestTriggerKindFlags(char *object, s32 type) {
    s32 index;
    Record14 *record;
    u8 *flags;

    index = ((Shared_World *)object)->recordCount;
    record = ((Shared_World *)object)->recordArray;
    index--;
    if (index != -1) {
        flags = &record->flags;
        do {
            if (flags[1] == type &&
                (*flags & 0x40) == 0) {
                return 0;
            }
            index--;
            flags += sizeof(Record14);
        } while (index != -1);
    }

    index = ((Shared_World *)object)->alternateRecordCount;
    record = ((Shared_World *)object)->alternateRecordArray;
    index--;
    if (index != -1) {
        do {
            if (record->kind == type &&
                (record->flags & 0x40) == 0) {
                return 0;
            }
            index--;
            record++;
        } while (index != -1);
    }

    return 1;
}
