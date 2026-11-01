#include "COMMON/PACKEDMESHMATERIAL.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "ENGINE/RUMBLE.H"
#include "COMMON/WORLDSORTENTRY.H"
#include "TYPES.H"
#include "RENDER/SETN64_GETPACKSECTION.H"


extern void SetN64_GetPackSectionSize(s32 table, s32 index);

void Rumble_SetActorStateBit(Shared_World *world, void *actor, s32 enabled) {
    LevelActor *entry;
    struct Def *cond;
    void *levelStateSections;
    void *table;
    u8 *base1;
    u8 *base2;
    s32 levelIndex;
    s32 mask;
    s32 index;
    s32 idx;
    s32 idx2;
    s32 lastOffset;
    u32 first;

    if (!(((LevelActor *)actor)->flags & 0x80000)) {
        first = (u32)world->actors;
        index = -1;
        if ((u32) actor >= first) {
            lastOffset = world->actorCount * 744;
            lastOffset -= 744;
            if (first + lastOffset >= (u32) actor) {
                index = ((u32) actor - first) / 744;
            }
        }
    } else {
        index = -1;
    }
    if (index == -1) {
        return;
    }
    levelIndex = world->level;
    if (world->mode == 2) {
        return;
    }
    entry = &world->actors[index];
    cond = (struct Def *)entry->definition;
    if ((u32) (cond->type - 9) < 2) {
        if (cond->flags & 0x200) {
            return;
        }
    }
    levelStateSections = world->bitSections;
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(levelStateSections, 0), levelIndex), 0);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    base1 = (u8 *) SetN64_GetPackSection(table, 1);
    base2 = base1;
    mask = 1 << (index & 7);
    if (enabled != 0) {
        idx = index;
        if (index < 0) {
            idx = index + 7;
        }
        base1[idx >> 3] |= mask;
        return;
    }
    idx2 = index;
    if (idx2 < 0) {
        idx2 += 7;
    }
    base2[idx2 >> 3] &= ~mask;
}

s32 Rumble_TestActorStateBit(void *worldState, void *actorPointer) {
    Shared_World *world = worldState;
    LevelActor *actor = actorPointer;
    void *levelStateSections;
    void *table;
    u8 *base;
    s32 levelIndex;
    s32 mask;
    s32 index;
    s32 i;
    s32 lastOffset;
    u32 first;

    if (!(actor->flags & 0x80000)) {
        first = ((u32)world->actors);
        index = -1;
        if ((u32) actorPointer >= first) {
            lastOffset = world->actorCount * 744;
            lastOffset -= 744;
            if (first + lastOffset >= (u32) actorPointer) {
                index = ((u32) actorPointer - first) / 744;
            }
        }
    } else {
        index = -1;
    }
    if (index == -1) {
        return 0;
    }
    levelStateSections = world->bitSections;
    levelIndex = world->level;
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(levelStateSections, 0), levelIndex), 0);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    base = (u8 *) SetN64_GetPackSection(table, 1);
    mask = 1 << (index & 7);
    i = index;
    if (i < 0) {
        i += 7;
    }
    return (base[i >> 3] & mask) != 0;
}
