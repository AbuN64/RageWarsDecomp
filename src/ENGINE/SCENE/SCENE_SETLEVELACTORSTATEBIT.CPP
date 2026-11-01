#include "COMMON/WORLDRECAT1B6A4.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "ENGINE/SCENE.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/WORLD.H"
#include "COMMON/LIGHT_VOLUME_AND_TRIGGER_VIEWS.H"
#include "COMMON/WORLDSORTENTRY.H"
#include "COMMON/ENTRYRECAT8V4.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "TYPES.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"

/* SCENE_7.CPP */
extern void SetN64_GetPackSectionSize(s32 table, s32 index);

void Scene_SetLevelActorStateBit(void *world, s32 index, s32 actorIndex, s32 enabled) {
    void *entry;
    struct Def *cond;
    void *levelResources;
    void *table;
    u8 *base1;
    u8 *base2;
    s32 mask;
    s32 idx;
    s32 idx2;

    if (((Shared_World *)world)->mode == 2) {
        return;
    }
    if (((Shared_World *)world)->level == index) {
        entry = (char *)&((LevelActorArrayView *)world)->actors[(s32)actorIndex];
        cond = (struct Def *)((LevelActor *)entry)->definition;
        if ((u32) (cond->type - 9) < 2) {
            if (cond->flags & 0x200) {
                return;
            }
        }
    }
    levelResources = ((Shared_World *)world)->bitSections;
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(levelResources, 0), (s32) index), 0);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    base1 = (u8 *) SetN64_GetPackSection(table, 1);
    base2 = base1;
    mask = 1 << (actorIndex & 7);
    if (enabled != 0) {
        idx = actorIndex;
        if ((s32) actorIndex < 0) {
            idx = actorIndex + 7;
        }
        base1[idx >> 3] |= mask;
        return;
    }
    idx2 = actorIndex;
    if (idx2 < 0) {
        idx2 += 7;
    }
    base2[idx2 >> 3] &= ~mask;
}

void Scene_SetRecordBitForLevel(Field_void_80 *worldState, s32 index, s32 recordBitIndex, s32 enabled) {
    void *table;
    u8 *base1;
    u8 *base2;
    s32 mask;
    s32 idx;
    s32 idx2;

    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(worldState->value, 0), index), 1);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    base1 = (u8 *) SetN64_GetPackSection(table, 1);
    base2 = base1;
    mask = 1 << (recordBitIndex & 7);
    if (enabled != 0) {
        idx = recordBitIndex;
        if (recordBitIndex < 0) {
            idx = recordBitIndex + 7;
        }
        base1[idx >> 3] |= mask;
        return;
    }
    idx2 = recordBitIndex;
    if (idx2 < 0) {
        idx2 += 7;
    }
    base2[idx2 >> 3] &= ~mask;
}

void Scene_SetLevelRecordStateBit(void *world, struct LevelBitRecord *levelBitRecord, s32 recordIndex) {
    s32 bitIndex;
    void *levelResources;
    s32 levelIndex;
    void *table;
    u8 *base1;
    u8 *base2;
    s32 mask;
    s32 idx;
    s32 idx2;

    bitIndex = levelBitRecord->bitIndex;
    levelResources = ((WorldSceneDispatchEnabledEntityTrigger *)(world))->levels;
    levelIndex = ((WorldSceneDispatchEnabledEntityTrigger *)(world))->level;
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(levelResources, 0), levelIndex), 1);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    base1 = (u8 *) SetN64_GetPackSection(table, 1);
    base2 = base1;
    mask = 1 << (bitIndex & 7);
    if (recordIndex != 0) {
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

s32 Scene_TestLevelRecordStateBit(void *world, struct LevelBitRecord *levelBitRecord) {
    s32 bitIndex;
    void *levelResources;
    s32 levelIndex;
    void *table;
    u8 *recordBits;
    s32 mask;

    bitIndex = levelBitRecord->bitIndex;
    levelResources = ((WorldSceneDispatchEnabledEntityTrigger *)(world))->levels;
    levelIndex = ((WorldSceneDispatchEnabledEntityTrigger *)(world))->level;
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(levelResources, 0), levelIndex), 1);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    recordBits = (u8 *) SetN64_GetPackSection(table, 1);
    mask = 1 << (bitIndex & 7);
    if (bitIndex < 0) {
        bitIndex += 7;
    }
    return (recordBits[bitIndex >> 3] & mask) != 0;
}

void Scene_SetTriggerBitForLevel(Field_void_80 *worldState, s32 index, s32 triggerBitIndex, s32 enabled) {
    void *table;
    u8 *base1;
    u8 *base2;
    s32 mask;
    s32 idx;
    s32 idx2;

    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(worldState->value, 0), index), 2);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    base1 = (u8 *) SetN64_GetPackSection(table, 1);
    base2 = base1;
    mask = 1 << (triggerBitIndex & 7);
    if (enabled != 0) {
        idx = triggerBitIndex;
        if (triggerBitIndex < 0) {
            idx = triggerBitIndex + 7;
        }
        base1[idx >> 3] |= mask;
        return;
    }
    idx2 = triggerBitIndex;
    if (idx2 < 0) {
        idx2 += 7;
    }
    base2[idx2 >> 3] &= ~mask;
}

void Scene_SetTriggerStateBit(void *world, void *trigger, s32 triggerIndex) {
    struct TriggerStateBitDescriptor *item = trigger;
    s32 bitIndex;
    void *levelResources;
    s32 levelIndex;
    void *table;
    u8 *base1;
    u8 *base2;
    s32 mask;
    s32 idx;
    s32 idx2;

    bitIndex = item->bitIndex;
    levelResources = ((WorldSceneDispatchEnabledEntityTrigger *)(world))->levels;
    levelIndex = ((WorldSceneDispatchEnabledEntityTrigger *)(world))->level;
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(levelResources, 0), levelIndex), 2);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    base1 = (u8 *) SetN64_GetPackSection(table, 1);
    base2 = base1;
    mask = 1 << (bitIndex & 7);
    if (triggerIndex != 0) {
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

s32 Scene_TestTriggerStateBit(Shared_World *world, void *trigger) {
    s32 bitIndex;
    void *levelResources;
    s32 levelIndex;
    void *table;
    u8 *stateBits;
    s32 mask;

    bitIndex = ((Record14 *)trigger)->reserved13;
    levelResources = world->bitSections;
    levelIndex = world->level;
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(levelResources, 0), levelIndex), 2);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    stateBits = (u8 *) SetN64_GetPackSection(table, 1);
    mask = 1 << (bitIndex & 7);
    if (bitIndex < 0) {
        bitIndex += 7;
    }
    return (stateBits[bitIndex >> 3] & mask) != 0;
}

/* Finds an identifier in the object's list and returns its mapped byte from the resource record, or -1 when absent. */
s32 Scene_GetTriggerCounterById(SceneTriggerCounterOwnerView *counterOwner, s32 counterId) {
    s32 i;
    void *record;
    Table *list = counterOwner->list;
    s32 count = list->count;
    s32 *ids = list->deltas;

    for (i = 0; i < count; i++) {
        if (ids[i] == counterId) {
            record = SetN64_GetPackSection(counterOwner->resource, 1);
            SetN64_GetPackSection(record, 0);
            return ((u8 *)SetN64_GetPackSection(record, 1))[i];
        }
    }
    return -1;
}

/* SCENE_8.CPP */
void Scene_DecrementTriggerCounter(void *world, s32 triggerIndex) {
    u8 *counter;
    void *counterSections;
    counterSections = SetN64_GetPackSection((((struct Field_void_80 *) ((s8 *) world))->value), 1);
    SetN64_GetPackSection(counterSections, 0);
    counter = SetN64_GetPackSection(counterSections, 1) + triggerIndex;
    *counter -= 1;
}

/* SCENE_9.CPP */
extern s32 Defs_FindSortedValue(void *entries, s32 entryCount, s32 wantedValue);

extern s32 SetN64_LocatePackSection(void *directory, s32 bankOffset, s32 sectionIndex, s32 *sectionSizeOut);

extern s32 g_cResource_UnpackRequestEntry;

s32 Scene_TestTriggerCounterZero(void *world, s32 triggerIndex) {
    void *packSectionResult;
    u8 *result;

    packSectionResult = SetN64_GetPackSection((((struct Field_void_80 *) ((s8 *) world))->value), 1);
    SetN64_GetPackSection(packSectionResult, 0);
    result = (u8 *)((char *)SetN64_GetPackSection(packSectionResult, 1)) + triggerIndex;
    return *result == 0;
}

void *Scene_RequestBinaryResourceByKey(Shared_World *world, s32 resourceId, s32 mode, s32 direct) {
    StridedTable *table;
    s32 idx;
    s32 resourceSize;
    s32 result;

    table = world->lookupTable;
    idx = Defs_FindSortedValue(table->data, table->count, resourceId);
    if (idx == -1) {
        return 0;
    }
    result = SetN64_LocatePackSection(world->lookupDirectory, world->lookupBank, idx, &resourceSize);
    return Cache_RequestResource(0, result, result, resourceSize, mode, 0, &g_cResource_UnpackRequestEntry, &s_binaryBlockText, direct);
}

/* Starts a sound effect from the world's sound table: looks the id up (0 or unknown returns 0),
 * picks the effect's behaviour table (ids 5 and 7 have their own, everything else the default), sets
 * the loop/priority bits 0x4 or 0x18 from the id's range, and queues it through Cache_RequestResource. */
extern s32 g_cResource_UnpackRequestEntry, g_scene_UnpackImagesWithLowBoostEntry, g_scene_UnpackImagesWithHighBoostEntry;
extern s32 s_graphicsetText;
s32 Scene_StartWorldEffect(Shared_World *world, s32 id, s32 flags, s32 extra) {
    s32 index;
    s32 *behaviour;
    s32 handle;
    s32 out;

    if (id == 0) {
        return 0;
    }
    index = Defs_FindSortedValue(world->resourceKindTable->entries, world->resourceKindTable->count, id);
    if (index == -1) {
        return 0;
    }
    switch (id) {
    case 5:
        behaviour = &g_scene_UnpackImagesWithLowBoostEntry;
        break;
    case 7:
        behaviour = &g_scene_UnpackImagesWithHighBoostEntry;
        break;
    default:
        behaviour = &g_cResource_UnpackRequestEntry;
        break;
    }
    switch (id) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 100:
    case 101:
    case 102:
    case 103:
    case 104:
        flags |= 0x18;
        break;
    default:
        flags |= 4;
        break;
    }
    handle = SetN64_LocatePackSection(world->resourceKindDirectory, world->resourceKindBank, index, &out);
    return Cache_RequestResource(0, handle, handle, out, flags, world, behaviour, &s_graphicsetText, extra);
}
