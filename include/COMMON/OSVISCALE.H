#ifndef COMMON_OSVISCALE_H
#define COMMON_OSVISCALE_H
#include <PR/abi.h>
#include "TYPES.H"





struct __OSViScale;
struct __OSViScale {
    f32 factor;
    u16 offset;
    u32 scale;
};

extern float g_videoScaleSignedConversionLimit;

struct ViModeContextView;
typedef struct ViModeContextView ViModeContextView;


struct VideoDeviceManager;
OSThread;
struct VideoDeviceManager {
    u32 active;
    OSThread *thread;
    OSMesgQueue *cmdQueue;
    OSMesgQueue *evtQueue;
    OSMesgQueue *acsQueue;
    s32 (*dma)(s32, u32, void *, u32);
    s32 (*edma)(void *, s32, u32, void *, u32);
};






struct VideoContextEventView;
typedef struct VideoContextEventView VideoContextEventView;

extern double g_videoScaleUnsignedBias;



struct VideoContextEventView;

struct ViVerticalScaleView;
struct ViVerticalScaleView {
    u16 state;
    unsigned char padding_2[34];
    f32 yScaleFactor;
};


struct ViModeContextView;
struct ViModeContextView {
    u16 state;
    u16 retraceCount;
    void *framep;
    OSViMode *modep;
    u32 control;
};








struct ViVerticalScaleView;
typedef struct ViVerticalScaleView ViVerticalScaleView;


typedef OSViMode Modep;


struct __OSViScale;
typedef struct __OSViScale __OSViScale;

struct ViSwapContextView;
struct ViSwapContextView {
    u16 state;
    u16 retraceCount;
    void *framep;
    OSViMode *modep;
    u32 control;
    void *msgq;
    void *msg;
    __OSViScale x;
    __OSViScale y;
};

struct StateosViSetSpecialFeatures;
typedef struct StateosViSetSpecialFeatures StateosViSetSpecialFeatures;

struct StateosViSetSpecialFeatures;
struct StateosViSetSpecialFeatures {
    u16 status;
    u16 pad2;
    u32 word4;
    Awords *inner;
    u32 flags;
};

struct VideoDeviceManager;
typedef struct VideoDeviceManager VideoDeviceManager;

struct ViSwapContextView;
typedef struct ViSwapContextView ViSwapContextView;
#endif
