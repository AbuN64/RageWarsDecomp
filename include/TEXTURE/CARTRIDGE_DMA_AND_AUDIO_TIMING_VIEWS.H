#ifndef TEXTURE_CARTRIDGE_DMA_AND_AUDIO_TIMING_VIEWS_H
#define TEXTURE_CARTRIDGE_DMA_AND_AUDIO_TIMING_VIEWS_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"

typedef struct AudioInitializeTiming { u32 frequency, frameTime, samples; } AudioInitializeTiming;
struct Chunk {
    u32 source; /* cartridge device address */
    void *destination;
    s32 length;
    void *queue;
    s32 value;
};
struct CartridgeReadRequest {
    u32 devAddr;
    void *buffer;
    s32 size;
    void *replyQueue;
    void *replyMsg;
    s32 active; /* 0x14 */
    void *next;
    void *prev;
};
struct Item57BD4 {
    s16 exclusiveKey;
    s16 priority;
    s16 reservedHalf;
    u16 flags;
};
struct Window;
/* The audio DMA state (libultra dmaNew pattern): the in-use and free cartridge read windows. */
struct AudioDmaState {
    u8 initialized;
    unsigned char padding_1[3];
    struct Window *firstUsed;
    struct Window *firstFree;
};
extern struct AudioDmaState g_audioDmaState;
typedef struct CacheCountdownEntry { struct CacheCountdownEntry *next; char pad4[4]; u16 state; } CacheCountdownEntry;
#endif
