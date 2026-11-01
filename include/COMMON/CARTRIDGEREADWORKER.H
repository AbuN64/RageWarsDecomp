#ifndef COMMON_CARTRIDGEREADWORKER_H
#define COMMON_CARTRIDGEREADWORKER_H
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "COMMON/PARAMSRECAT8V3.H"
#include "COMMON/ALBANK_S.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
struct Chunk;

struct CartridgeReadWorker;
struct CartridgeReadWorker {
    u8 reserved[0x230];
    OSMesgQueue requestQueueStorage; /* +0x230 */
    OSMesg requestMessages[512]; /* +0x248 */
    OSMesgQueue completionQueueStorage; /* +0xA48 */
    OSMesg completionMessage; /* +0xA60 */
    u32 reservedA64;
    u8 stack[0x400]; /* osCreateThread stack top is &stack[sizeof(stack)] */
    u8 requests[0x5068 - 0xE68];
    IntrusiveList available; /* 0x5068 */
    IntrusiveList pending; /* 0x507C */
};






struct Item57BD4;
typedef struct Item57BD4 Item57BD4;

struct Chunk;



extern int g_audioCommandBufferIndex;


extern int g_audioCacheEntryAllocCount;

struct CartridgeReadRequest;




struct Chunk;
struct Queue;

extern u32 Sound_GetSampleDmaWindowAddress(s32 offset, s32 length);

struct Window;
typedef struct Window Window;


extern int g_audioSampleRomBase;

struct Chunk;
typedef struct Chunk Chunk;

struct Item57BD4;

struct Window;
struct Window {
    struct Window *next;
    struct Window *prev;
    u32 base;
    u32 frame;
    s32 buffer;
};

struct GameAudioContext;
struct Voice;
typedef struct Voice Voice;



extern int g_cartridgeReadWorkerPriority;

struct Voice;
struct Voice {
    s32 soundHandleIndex;
    s32 sound;
    s32 primaryKey;
    s32 secondaryKey;
    u8 reserved10[8];
    s32 left; /* +0x18 */
    s32 right; /* +0x1C */
    u8 reserved20[0xC];
    f32 attenuation; /* probe 20261019T020116365530Z */
    f32 baseAttenuation;
    f32 reservedFloat34;
    s16 priority;
    s16 channel;
    u8 reserved3C[8];
    CVector3 position; /* +0x44; probe 20261019T012703451174Z */
    u8 reserved50[4];
    s8 distanceMode;
    u8 reserved55[0x1F];
    u16 envelope[3];
    s16 envelopeFrames; /* +0x7A; probe 20261019T012704137584Z */
    u32 envelopeExtra;
    f32 envelopeValue, envelopeStep;
    u8 reserved88[0x18];
    s32 pending;
    s32 flags;
    s32 soundId;
    s32 releasePending;
    struct GameAudioContext *context; /* +0xB0; probe 20261019T012703451174Z */
    s32 reservedWordB4;
    f32 reservedFloat;
    s32 reservedWordBC, fixedPosition, musicGainScalingEnabled;
    f32 volumeScale;
};


struct CartridgeReadWorker;
typedef struct CartridgeReadWorker CartridgeReadWorker;

extern Window *g_audioDmaUsedWindowHead[];
extern u32 g_audioTaskFrameIndex;
extern u32 g_audioDmaPendingReadCount;


struct AudioDmaState;

struct CacheEntry;
struct CacheEntry {
    struct CacheEntry *next;
    void *key;
    u16 state;
    u16 size;
    s32 padC;
    char data[128];
};


struct AudioDmaState;
typedef struct AudioDmaState AudioDmaState;

struct CartridgeReadRequest;
typedef struct CartridgeReadRequest CartridgeReadRequest;


struct CacheEntry;
typedef struct CacheEntry CacheEntry;



#include "COMMON/AUDIO_QUEUES.H"
#include "COMMON/AUDIO_SYNTH.H"
extern u32 g_audioWorkerEventCount;
#endif
