#ifndef COMMON_AUDIO_INITIALIZE_H
#define COMMON_AUDIO_INITIALIZE_H
#include "TYPES.H"
#include "COMMON/AUDIO_QUEUES.H"
#include "COMMON/ITEMRECAT20V1.H"
typedef struct AudioTask {
    u32 type, flags;
    void *boot; u32 bootSize;
    void *code; u32 codeSize;
    void *codeData; u32 codeDataSize;
    void *stack; u32 stackSize;
    void *output; u32 outputSize;
    void *commands; u32 commandSize;
    void *yield; u32 yieldSize;
} AudioTask;
typedef struct AudioWork {
    s16 *samples;
    u8 reserved4[0x14]; AudioTask task;
    OSMesgQueue *queue;
    struct AudioWork *message;
    u8 reserved60[0x10];
} AudioWork;
typedef struct AudioCacheEntry {
    struct AudioCacheEntry *next, *prev;
    u32 state;
    u8 reserved0C[4];
    void *buffer; /* +0x10: 80256880 allocator stores, entries stride 0x14. */
} AudioCacheEntry;
#endif
