#ifndef VOICE_START_AND_PARAMETER_UPDATE_VIEWS_H
#define VOICE_START_AND_PARAMETER_UPDATE_VIEWS_H
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/small_records.h"
struct AudioStartVoiceUpdate;
typedef struct AudioStartVoiceUpdate AudioStartVoiceUpdate;

struct AudioVolumeControlUpdate;
typedef struct AudioVolumeControlUpdate AudioVolumeControlUpdate;

struct AudioVoicePriorityView;
struct AudioVoicePriorityView {
    char pad0[0x16];
    unsigned short priority;
};

typedef void ( *SharedRecV3)(void *, signed int, void *);


struct ALStartParamAlt;
struct ALParam_s;
struct ALStartParamAlt {
    struct ALParam_s *next;
    s32 delta;
    s16 type;
    s16 unity;
    f32 pitch;
    s16 volume;
    u8 pan;
    u8 fxMix;
    s32 samples;
    void *wave;
};

struct ALStartParamAlt;
typedef struct ALStartParamAlt ALStartParamAlt;



struct AudioVoicePriorityView;
typedef struct AudioVoicePriorityView AudioVoicePriorityView;

struct AudioStartVoiceUpdate;
struct AudioStartVoiceUpdate {
    s32 next;
    s32 delta;
    s16 type;
    u16 unity;
    s32 wave;
};

typedef void ( *SharedRecV10)(void *, signed int, void *);

struct AudioVolumeControlUpdate;
struct AudioVolumeControlUpdate {
    s32 next;
    char pad0[0x4 - 0x0 - sizeof(s32)];
    s32 delta;
    char pad4[0x8 - 0x4 - sizeof(s32)];
    s16 type;
    char pad8[0xC - 0x8 - sizeof(s16)];
    s32 volume;
    char padC[0x10 - 0xC - sizeof(s32)];
    s32 samples;
};
#endif
