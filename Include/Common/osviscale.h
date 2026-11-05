#ifndef COMMON_OSVISCALE_H
#define COMMON_OSVISCALE_H
#include <PR/abi.h>
#include "types.h"

struct __OSViScale;
struct __OSViScale {
    f32 factor;
    u16 offset;
    u32 scale;
};

/* libultra VI context: two 0x30-byte records, with 4-byte alignment. */
typedef struct __OSViContext {
    u16 state;
    u16 retraceCount;
    void *framep;
    OSViMode *modep;
    u32 control;
    OSMesgQueue *msgq;
    OSMesg msg;
    struct __OSViScale x;
    struct __OSViScale y;
} __OSViContext;

extern float g_videoScaleSignedConversionLimit;

struct VideoDeviceManager;
struct VideoDeviceManager {
    u32 active;
    OSThread *thread;
    OSMesgQueue *cmdQueue;
    OSMesgQueue *evtQueue;
    OSMesgQueue *acsQueue;
    s32 (*dma)(s32, u32, void *, u32);
    s32 (*edma)(void *, s32, u32, void *, u32);
};

extern double g_videoScaleUnsignedBias;

typedef OSViMode Modep;

struct __OSViScale;
typedef struct __OSViScale __OSViScale;

struct VideoDeviceManager;
typedef struct VideoDeviceManager VideoDeviceManager;

#endif
