#ifndef DATA_INITIALIZED_RUNTIME_BUFFERS_H
#define DATA_INITIALIZED_RUNTIME_BUFFERS_H
#include "TYPES.H"

/* These ROM images occupy memory reused for runtime buffers. The word view
 * retains the linker's original address relocations; the other view describes
 * the byte names or 64-bit-aligned OS/RSP storage used after initialization. */
typedef union SavedPlayerNameBufferImage {
    u32 initialized[1369];
    u8 names[5476];
} SavedPlayerNameBufferImage;

typedef union GraphicsTaskYieldBufferImage {
    u32 initialized[1280];
    u64 yield[640];
} GraphicsTaskYieldBufferImage;

typedef union AudioWorkerStackImage {
    u32 initialized[2560];
    u64 stack[1280];
} AudioWorkerStackImage;

#endif
