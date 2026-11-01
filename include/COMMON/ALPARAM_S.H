#ifndef COMMON_ALPARAM_S_H
#define COMMON_ALPARAM_S_H
#include "TYPES.H"
struct ALParam_s;
typedef struct ALParam_s ALParam_s;


extern float g_audioEnvelopeRateScale;

extern float g_resamplerInitialRatio;

struct ALFilter_s;
typedef struct ALFilter_s ALFilter_s;

struct ALFilter_s;
struct ALFilter_s {
    struct ALFilter_s *source;
    void *handler;
    s32 (*setParam)(void *, s32, void *);
    s16 inp;
    s16 outp;
    s32 type;
};

/* Filter parameter / control-update types (libultra AL_FILTER_*). */
enum {
    AL_FILTER_FREE_VOICE = 0,
    AL_FILTER_SET_SOURCE = 1,
    AL_FILTER_ADD_SOURCE = 2,
    AL_FILTER_ADD_UPDATE = 3,
    AL_FILTER_RESET = 4,
    AL_FILTER_SET_WAVETABLE = 5,
    AL_FILTER_SET_DRAM = 6,
    AL_FILTER_SET_PITCH = 7,
    AL_FILTER_SET_UNITY_PITCH = 8,
    AL_FILTER_START = 9,
    AL_FILTER_SET_STATE = 10,
    AL_FILTER_SET_VOLUME = 11,
    AL_FILTER_SET_PAN = 12,
    AL_FILTER_START_VOICE_ALT = 13,
    AL_FILTER_START_VOICE = 14,
    AL_FILTER_STOP_VOICE = 15,
    AL_FILTER_SET_FXAMT = 16
};
struct ALParam_s;
struct ALParam_s {
    struct ALParam_s *next;
    s32 delta;
    s16 type;
    union {
        s32 i;
        f32 f;
        void *p;
    } data;
    union {
        s32 i;
        f32 f;
        void *p;
    } moredata;
};
/* AL_FILTER_START_VOICE update: optional unity pitch, then the wavetable to start. */
struct ALStartParam;
typedef struct ALStartParam ALStartParam;
struct ALStartParam {
    struct ALParam_s *next;
    s32 delta;
    s16 type;
    s16 unity;
    void *wave;
};
/* AL_FILTER_FREE_VOICE update: the physical voice to return to the synth driver. */
struct PVoice_s;
struct ALFreeParam;
typedef struct ALFreeParam ALFreeParam;
struct ALFreeParam {
    struct ALParam_s *next;
    s32 delta;
    s16 type;
    struct PVoice_s *pvoice;
};

struct ALEnvMixer;
struct ALFilter_s;
struct ALParam_s;
struct ALEnvMixer {
    ALFilter_s filter;
    void *state;
    s16 pan;
    s16 volume;
    s16 cvolL;
    s16 cvolR;
    s16 dryamt;
    s16 wetamt;
    u16 lratl;
    s16 lratm;
    s16 ltgt;
    u16 rratl;
    s16 rratm;
    s16 rtgt;
    s32 delta;
    s32 segEnd;
    s32 first;
    struct ALParam_s *ctrlList;
    struct ALParam_s *ctrlTail;
    struct ALFilter_s **sources;
    s32 motion;
};

typedef signed short AudioPoleFilterState[4];

struct AudioLowPassFilter;
struct AudioLowPassFilter {
    s16 cutoff;
    s16 gain;
    union {
        s16 taps[16];
        s64 alignment;
    } coefficients;
    AudioPoleFilterState *state;
    s32 first;
};

struct AudioLowPassFilter;
typedef struct AudioLowPassFilter AudioLowPassFilter;



struct LogTab;
typedef struct LogTab LogTab;

struct LogTab;
struct LogTab {
    f64 v[8];
};

#include "libultra/audio/env.h"

struct ALEnvMixer;
typedef struct ALEnvMixer ALEnvMixer;


extern f64 frexp(f64 inputValue, s32 *exponentOut);

extern float g_audioEnvelopeFallbackRate;




#endif
