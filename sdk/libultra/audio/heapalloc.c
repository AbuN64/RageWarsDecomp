#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "../../include/BUF16B.H"
#include "TYPES.H"

void    *alHeapDBAlloc(u8 *a, s32 b, ALHeap *c, s32 d, s32 e) {
    ALHeap *heap = c;
    u32 allocationStart;
    u32 allocationEnd;
    u32 allocatedAddress;

    allocationStart = (u32)heap->cur;
    allocationEnd = allocationStart + (((d * e) + 0xF) & ~0xF);
    allocatedAddress = 0;
    if ((u32)((s32)heap->base + heap->len) >= allocationEnd) {
        allocatedAddress = allocationStart;
        heap->cur = (u8 *)allocationEnd;
    }
    return (s32) allocatedAddress;
}

