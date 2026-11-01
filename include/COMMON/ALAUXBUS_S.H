#ifndef COMMON_ALAUXBUS_S_H
#define COMMON_ALAUXBUS_S_H
#include "COMMON/AUDIO_CALLBACKS.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
struct ALAuxBus_s;
typedef struct ALAuxBus_s ALAuxBus_s;

struct ALLoadFilter;
typedef struct ALLoadFilter ALLoadFilter;

struct ALParam_s1C;
struct ALParam_s1C {
    struct ALParam_s1C *next;
    s32 delta;
    s16 type;
    s32 data;
    s32 moredata;
    s32 stillmoredata;
    s32 yetstillmoredata;
};


struct ALResampler;
typedef struct ALResampler ALResampler;

struct ALParam_s1C;
typedef struct ALParam_s1C ALParam_s1C;

struct ALLoadFilter;
struct ALLoadFilter {
    char pad[0x48];
};

struct ALFilter_sC;
struct ALFilter_sC {
    struct ALFilter_sC *source;
    ALCmdHandler handler;
    ALSetParam setParam;
};

struct ALFilter_sC;
typedef struct ALFilter_sC ALFilter_sC;

struct ALSynth4C;
struct ALSynth4C {
    ALPlayer_s14 *head;
    ListLink pFreeList;
    ListLink pAllocList;
    ListLink pLameList;
    s32 paramSamples;
    s32 curSamples;
    void *dma;
    void *heap;
    void *paramList;
    void *mainBus;
    void *auxBus;
    ALFilter_sC *outputFilter;
    s32 numPVoices;
    s32 maxAuxBusses;
    s32 outputRate;
    s32 maxOutSamples;
};

typedef void ( *SharedRecV12)(void *, signed int, void *);

struct ALEnvMixer4C;


struct ALAuxBus_s;
struct ALAuxBus_s {
    ALFilter_s14 filter;
    s32 sourceCount;
    s32 maxSources;
    ALFilter_s14 **sources;
    char fx[0x4C - 0x20];
};

struct ALResampler;
struct ALResampler {
    char pad[0x34];
};



struct ALSave;
typedef struct ALSave ALSave;

struct ALMainBus_s;
struct ALMainBus_s {
    ALFilter_s14 filter;
    s32 sourceCount;
    s32 maxSources;
    ALFilter_s14 **sources;
};


struct ALSynth4C;
typedef struct ALSynth4C ALSynth4C;





struct PVoice_s;
typedef struct PVoice_s PVoice_s;

struct ALEnvMixer4C;
typedef struct ALEnvMixer4C ALEnvMixer4C;

struct Opaque_ALVoice_s;
struct PVoice_s;

struct ALMainBus_s;
typedef struct ALMainBus_s ALMainBus_s;

struct AudioStopVoiceUpdate;
typedef struct AudioStopVoiceUpdate AudioStopVoiceUpdate;


struct AudioStopVoiceUpdate;
struct AudioStopVoiceUpdate {
    s32 next;
    char pad0[0x4 - 0x0 - sizeof(s32)];
    s32 delta;
    char pad4[0x8 - 0x4 - sizeof(s32)];
    s16 type;
};



struct ALSave;
struct ALSave {
    ALFilter_s14 filter;
    s32 dramout;
    s32 first;
};
#endif
