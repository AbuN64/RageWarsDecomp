#include <PR/libaudio.h>
#include "include_asm.h"
#include "Common/runtime_declarations.h"
#include "Ui/Tsmos/Screens/pakinterfacescreen.h"
#include "Common/albank_s.h"
#include "types.h"

/* heapinit.c */
#if defined(VERSION_EU)
#include "Common/albank_s.h"
#include "types.h"
void alHeapInit(ALHeap *heapStorage, u8 *base, s32 byteCount) {
    s32 alignmentBytes;
    alignmentBytes = 0x10 - ((s32) base & 0xF);
    if (alignmentBytes != 0x10) {
        heapStorage->base = base + alignmentBytes;
    } else {
        heapStorage->base = base;
    }
    heapStorage->len = byteCount;
    heapStorage->count = 0;
    heapStorage->cur = heapStorage->base;
}
#endif

/* heapinit.c */
#if !(defined(VERSION_EU))
void alHeapInit(ALHeap *heap, u8 *base, s32 byteLength) {
    s32 alignmentOffset;
    alignmentOffset = 0x10 - ((s32) base & 0xF);
    if (alignmentOffset != 0x10) {
        heap->base = base + alignmentOffset;
    } else {
        heap->base = base;
    }
    heap->len = byteLength;
    heap->count = 0;
    heap->cur = heap->base;
}
#endif
