#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RECORD.H"
#include "TYPES.H"
#include "UI/QUAG/E_SMEM.H"
#include "COMMON/OBJRECAT3CV2.H"
#include "RESMGR/FRAME_HEAP_LIFETIME.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "RESMGR/FRAME_HEAP_MARKS.H"
#include "include_asm.h"

/* Sets one heap usage stat {current, lowest, highest}: current = value clamped to +-1e8, then widens the range. */
#define FRAMEHEAP_SET_STAT(stat, value) (stat)[0] = (value); if ((stat)[0] < -100000000.0f) (stat)[0] = -100000000.0f; if ((stat)[0] > 100000000.0f) (stat)[0] = 100000000.0f; if ((stat)[0] < (stat)[1]) (stat)[1] = (stat)[0]; if ((stat)[2] < (stat)[0]) (stat)[2] = (stat)[0];
/* Points the frame heap at buffer g_frameHeapBuffers[g_frameHeapBufferIndex]: low end = base, high end = base + size, mark stack
 * [0] = base at depth 0; free space = size, low and high usage = 0. Called after the buffers are allocated and on
 * each buffer swap. */
void ESmem_ResetFrameHeap(void) {
    f32 size;
    size = (f32)g_frameHeapBufferBytes;
    g_frameHeapLowCursor = g_frameHeapBuffers[g_frameHeapBufferIndex];
    g_frameHeapHighCursor = g_frameHeapBuffers[g_frameHeapBufferIndex] + g_frameHeapBufferBytes;
    g_frameHeapLowMarks[0] = g_frameHeapLowCursor;
    g_frameHeapMarkDepth = 0;
    FRAMEHEAP_SET_STAT(g_frameHeapFreeByteStats, size);
    FRAMEHEAP_SET_STAT(g_frameHeapLowUsageStats, 0.0f);
    FRAMEHEAP_SET_STAT(g_frameHeapHighUsageStats, 0.0f);
}

s32 ESmem_AllocateFrameHeapLow(s32 byteCount) {
    s32 amount;
    s32 result;
    f32 value;

    amount = (byteCount + 7) & -8;
    value = g_frameHeapLowUsageStats[0] + (f32)amount;
    result = g_frameHeapLowCursor;
    g_frameHeapLowCursor = result + amount;
    g_frameHeapLowUsageStats[0] = value;
    if (value < g_frameHeapLowAllocationStatLowerLimit) {
        g_frameHeapLowUsageStats[0] = g_frameHeapLowAllocationStatLowerLimit;
    }
    if (g_frameHeapLowUsageStats[0] > *(&g_frameHeapLowAllocationStatLowerLimit + 1)) {
        g_frameHeapLowUsageStats[0] = *(&g_frameHeapLowAllocationStatLowerLimit + 1);
    }
    if (g_frameHeapLowUsageStats[0] < g_frameHeapLowUsageStats[1]) {
        g_frameHeapLowUsageStats[1] = g_frameHeapLowUsageStats[0];
    }
    if (g_frameHeapLowUsageStats[2] < g_frameHeapLowUsageStats[0]) {
        g_frameHeapLowUsageStats[2] = g_frameHeapLowUsageStats[0];
    }

    g_frameHeapFreeByteStats[0] += (f32)-amount;
    value = g_frameHeapFreeByteStats[0];
    if (value < g_frameHeapLowAllocationStatLowerLimit) {
        g_frameHeapFreeByteStats[0] = g_frameHeapLowAllocationStatLowerLimit;
    }
    if (*(&g_frameHeapLowAllocationStatLowerLimit + 1) < g_frameHeapFreeByteStats[0]) {
        g_frameHeapFreeByteStats[0] = *(&g_frameHeapLowAllocationStatLowerLimit + 1);
    }
    if (g_frameHeapFreeByteStats[0] < g_frameHeapFreeByteStats[1]) {
        g_frameHeapFreeByteStats[1] = g_frameHeapFreeByteStats[0];
    }
    if (g_frameHeapFreeByteStats[2] < g_frameHeapFreeByteStats[0]) {
        g_frameHeapFreeByteStats[2] = g_frameHeapFreeByteStats[0];
    }
    return result;
}

void ESmem_RestoreFrameHeapMark(void) {
    s32 index;
    s32 value;
    s32 amount;
    f32 fvalue;

    index = g_frameHeapMarkDepth;
    value = g_frameHeapLowMarks[index];
    amount = value - g_frameHeapLowCursor;
    fvalue = g_frameHeapLowUsageStats[0] + (f32)-amount;
    g_frameHeapMarkDepth = index - 1;
    g_frameHeapLowCursor = value;
    g_frameHeapLowUsageStats[0] = fvalue;
    if (fvalue < g_frameHeapRestoreStatLowerLimit) {
        g_frameHeapLowUsageStats[0] = g_frameHeapRestoreStatLowerLimit;
    }
    if (g_frameHeapLowUsageStats[0] > *(&g_frameHeapRestoreStatLowerLimit + 1)) {
        g_frameHeapLowUsageStats[0] = *(&g_frameHeapRestoreStatLowerLimit + 1);
    }
    if (g_frameHeapLowUsageStats[0] < g_frameHeapLowUsageStats[1]) {
        g_frameHeapLowUsageStats[1] = g_frameHeapLowUsageStats[0];
    }
    if (g_frameHeapLowUsageStats[2] < g_frameHeapLowUsageStats[0]) {
        g_frameHeapLowUsageStats[2] = g_frameHeapLowUsageStats[0];
    }

    g_frameHeapFreeByteStats[0] += (f32)amount;
    if (g_frameHeapFreeByteStats[0] < g_frameHeapRestoreStatLowerLimit) {
        g_frameHeapFreeByteStats[0] = g_frameHeapRestoreStatLowerLimit;
    }
    if (*(&g_frameHeapRestoreStatLowerLimit + 1) < g_frameHeapFreeByteStats[0]) {
        g_frameHeapFreeByteStats[0] = *(&g_frameHeapRestoreStatLowerLimit + 1);
    }
    if (g_frameHeapFreeByteStats[0] < g_frameHeapFreeByteStats[1]) {
        g_frameHeapFreeByteStats[1] = g_frameHeapFreeByteStats[0];
    }
    if (g_frameHeapFreeByteStats[2] < g_frameHeapFreeByteStats[0]) {
        g_frameHeapFreeByteStats[2] = g_frameHeapFreeByteStats[0];
    }
}

s32 ESmem_AllocateFrameHeapHigh(s32 byteCount) {
    s32 amount;
    s32 result;

    amount = (byteCount + 7) & -8;
    g_frameHeapHighUsageStats[0] += (f32)amount;
    result = g_frameHeapHighCursor - amount;
    g_frameHeapHighCursor = result;
    if (g_frameHeapHighUsageStats[0] < g_frameHeapHighAllocationStatLowerLimit) {
        g_frameHeapHighUsageStats[0] = g_frameHeapHighAllocationStatLowerLimit;
    }
    if (g_frameHeapHighUsageStats[0] > *(&g_frameHeapHighAllocationStatLowerLimit + 1)) {
        g_frameHeapHighUsageStats[0] = *(&g_frameHeapHighAllocationStatLowerLimit + 1);
    }
    if (g_frameHeapHighUsageStats[0] < g_frameHeapHighUsageStats[1]) {
        g_frameHeapHighUsageStats[1] = g_frameHeapHighUsageStats[0];
    }
    if (g_frameHeapHighUsageStats[2] < g_frameHeapHighUsageStats[0]) {
        g_frameHeapHighUsageStats[2] = g_frameHeapHighUsageStats[0];
    }

    g_frameHeapFreeByteStats[0] += (f32)-amount;
    if (g_frameHeapFreeByteStats[0] < g_frameHeapHighAllocationStatLowerLimit) {
        g_frameHeapFreeByteStats[0] = g_frameHeapHighAllocationStatLowerLimit;
    }
    if (*(&g_frameHeapHighAllocationStatLowerLimit + 1) < g_frameHeapFreeByteStats[0]) {
        g_frameHeapFreeByteStats[0] = *(&g_frameHeapHighAllocationStatLowerLimit + 1);
    }
    if (g_frameHeapFreeByteStats[0] < g_frameHeapFreeByteStats[1]) {
        g_frameHeapFreeByteStats[1] = g_frameHeapFreeByteStats[0];
    }
    if (g_frameHeapFreeByteStats[2] < g_frameHeapFreeByteStats[0]) {
        g_frameHeapFreeByteStats[2] = g_frameHeapFreeByteStats[0];
    }
    return result;
}

extern struct Record *Cache_AllocateMemory(s32 size);


void ESmem_InitializeFrameHeaps(s32 heapBytes) {
    extern void ESmem_ResetFrameHeap(void);
    s32 size;

    size = (heapBytes + 7) & ~7;
    g_frameHeapBuffers[0] = Cache_AllocateMemory(size);
    g_frameHeapBuffers[1] = Cache_AllocateMemory(size);
    g_frameHeapBufferBytes = size;
    g_frameHeapBufferIndex = 0;
    ESmem_ResetFrameHeap();
    g_frameHeapsAllocated = 1;
}

void ESmem_FreeFrameHeaps(void) {
    if (g_frameHeapsAllocated != 0) {
        Cache_FreeMemory(g_frameHeapBuffers[0]);
        Cache_FreeMemory(g_frameHeapBuffers[1]);
        g_frameHeapBuffers[0] = 0;
        g_frameHeapBuffers[1] = 0;
        g_frameHeapsAllocated = 0;
    }
}

void ESmem_SwapFrameHeap(void) {
    void ESmem_ResetFrameHeap(void);
    g_frameHeapBufferIndex = 1 - g_frameHeapBufferIndex;
    ESmem_ResetFrameHeap();
}

void ESmem_PushFrameHeapMark(void) {
    g_frameHeapLowMarks[++g_frameHeapMarkDepth] = g_frameHeapLowCursor;
}

/** Propagate each array's boundary sample into its two wrap-around slots. */
void ESmem_ResetFrameHeapUsageRanges(void) {
    float *p0 = &g_frameHeapFreeByteStats[1];
    float *p1 = &g_frameHeapLowUsageStats[1];
    float *p2 = &g_frameHeapHighUsageStats[1];
    float a = p0[-1];
    float b = p1[-1];
    float c = p2[-1];
    p0[0] = a;
    p0[1] = a;
    p1[0] = b;
    p1[1] = b;
    p2[0] = c;
    p2[1] = c;
}

#if !(defined(VERSION_US_REV1))
const float g_frameHeapLowAllocationStatLowerLimit_StorageWords[2] = {
    -100000000.0f, 100000000.0f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_ESmem_AllocateFrameHeapLowConstantWords_ESmem.c */
const float g_ESmem_AllocateFrameHeapLowConstantWords[2] = {
    -100000000.0f, 100000000.0f,
};
#endif

#if !(defined(VERSION_US_REV1))
const float g_frameHeapRestoreStatLowerLimit_StorageWords[2] = {
    -100000000.0f, 100000000.0f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_ESmem_RestoreFrameHeapMarkConstantWords_ESmem.c */
const float g_ESmem_RestoreFrameHeapMarkConstantWords[2] = {
    -100000000.0f, 100000000.0f,
};
#endif

#if !(defined(VERSION_US_REV1))
const float g_frameHeapHighAllocationStatLowerLimit_StorageWords[2] = {
    -100000000.0f, 100000000.0f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_ESmem_AllocateFrameHeapHighConstantWords_ESmem.c */
const float g_ESmem_AllocateFrameHeapHighConstantWords[2] = {
    -100000000.0f, 100000000.0f,
};
#endif
