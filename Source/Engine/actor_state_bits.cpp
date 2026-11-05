#include "include_asm.h"
#include "Common/shared_gameslot.h"
#include "Common/packedmeshmaterial.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/world.h"
#include "Common/heap_arena_entry.h"
#include "Common/snapshot_actor.h"
#include "Engine/rumble.h"
#include "types.h"
#include "Common/ballisticparams.h"
#include "Common/triple.h"
#include "Common/runtime_declarations.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Render/control_cycleactorsnapshotmode.h"
#include "Engine/Cache/list.h"
#include "Engine/scene_drawtransitioncoloroverlay.h"
#include "Common/vector4f.h"
#include "Common/level_actor.h"
#include "Common/worldsortentry.h"
#include "Render/setn64_getpacksection.h"
#include "Engine/session.h"
#include "Ai/Nav/Patrol/patrol.h"

/* RUMBLE_SETACTORSTATEBIT.CPP */




void Rumble_SetActorStateBit(Shared_World *world, LevelActor *actor, s32 enabled) {
    LevelActor *entry;
    struct Def *cond;
    void *levelStateSections;
    void *table;
    u8 *stateBytes;
    u8 *stateBytesForClear;
    s32 levelIndex;
    s32 mask;
    s32 index;
    s32 idx;
    s32 clearBitIndex;
    s32 lastOffset;
    u32 first;

    if (!((actor)->flags & 0x80000)) {
        first = (u32)world->actors;
        index = -1;
        if ((u32) actor >= first) {
            lastOffset = world->actorCapacity * 744;
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
    stateBytes = SetN64_GetPackSection(table, 1);
    stateBytesForClear = stateBytes;
    mask = 1 << (index & 7);
    if (enabled != 0) {
        idx = index;
        if (index < 0) {
            idx = index + 7;
        }
        stateBytes[idx >> 3] |= mask;
        return;
    }
    clearBitIndex = index;
    if (clearBitIndex < 0) {
        clearBitIndex += 7;
    }
    stateBytesForClear[clearBitIndex >> 3] &= ~mask;
}

s32 Rumble_TestActorStateBit(Shared_World *worldState, void *actorPointer) {
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
        first = ((u32)worldState->actors);
        index = -1;
        if ((u32) actorPointer >= first) {
            lastOffset = worldState->actorCapacity * 744;
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
    levelStateSections = worldState->bitSections;
    levelIndex = worldState->level;
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(levelStateSections, 0), levelIndex), 0);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    base = SetN64_GetPackSection(table, 1);
    mask = 1 << (index & 7);
    i = index;
    if (i < 0) {
        i += 7;
    }
    return (base[i >> 3] & mask) != 0;
}
