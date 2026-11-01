#ifndef COMMON_ALDELAY28_H
#define COMMON_ALDELAY28_H
#include "COMMON/AUDIO_CALLBACKS.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
extern float g_matrixFixedToFloatScale;

struct ALDelay28;
typedef struct ALDelay28 ALDelay28;

struct CallbackStateC;



struct ALResampler_s28;
struct ALResampler_s28 {
    ALFilter_s14 filter;
    void *state;
    f32 ratio;
    s32 upitch;
    f32 delta;
    s32 first;
};

struct ALFilter_s14_2;
typedef struct ALFilter_s14_2 ALFilter_s14_2;

struct ALFilter_s14_2;
struct ALFilter_s14_2 {
    struct ALFilter_s14_2 *source;
    ALCmdHandler handler;
    void *setParam;
    s16 inp;
    s16 outp;
    s32 type;
};

struct ALResampler_s;
struct ALResampler_s {
    ALFilter_s14_2 filter;
    void *state;
    f32 ratio;
    s32 upitch;
    f32 delta;
    s32 first;
    void *ctrlList;
    void *ctrlTail;
    s32 motion;
};



struct ALResampler_s28;
typedef struct ALResampler_s28 ALResampler_s28;

struct ALDelay28;
struct ALDelay28 {
    u32 input;
    u32 output;
    s16 ffcoef;
    s16 fbcoef;
    s16 gain;
    f32 rsinc;
    f32 rsval;
    s32 rsdelta;
    f32 rsgain;
    void *lp;
    ALResampler_s28 *rs;
};


struct ALResampler_s;
typedef struct ALResampler_s ALResampler_s;

struct AudioReverbParameterStateView;
typedef struct AudioReverbParameterStateView AudioReverbParameterStateView;

struct ALFx;
typedef struct ALFx ALFx;





extern float g_audioResamplerInverseFixedPointUnit;

extern float g_matrixIdentityUnitValue;


extern float g_matrixFloatIdentityUnitValue;

extern float g_matrixFloatToFixedScale;

struct AudioReverbParameterStateView;


struct CallbackStateC;
typedef struct CallbackStateC CallbackStateC;

struct ALFx;
struct ALFx {
    ALFilter_s14 filter;
    s16 *base;
    s16 *input;
    u32 length;
    ALDelay28 *delay;
    u8 section_count;
    void *paramHdl;
};

extern float g_audioResamplerMaximumRatio;

typedef struct ALFilter_u1 {
    struct ALFilter_u1 *source;
    ALCmdHandler handler;
    void *setParam;
    s16 inp;
    s16 outp;
    s32 type;
} ALFilter_u1;
extern char g_audioSaveAssertConditionText[];
extern const unsigned char g_audioSaveText[];
#endif
