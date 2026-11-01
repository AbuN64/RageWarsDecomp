#ifndef ENGINE_MAP_H
#define ENGINE_MAP_H
#include "TYPES.H"
struct MapBlockAllocatorView {
    char pad0[0x8];
    s32 remainingBlocks;
    char pad8[0xC - 0x8 - sizeof(s32)];
    s32 nextBlockAddress;
};
#endif
