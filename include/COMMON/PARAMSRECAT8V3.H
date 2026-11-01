#ifndef COMMON_PARAMSRECAT8V3_H
#define COMMON_PARAMSRECAT8V3_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"

struct SoundPlayerWordParameterEvent;
struct SoundPlayerWordParameterEvent {
    s16 f0;
    s32 f4;
    f32 f8;
};

union ALSndpEvent;
union ALSndpEvent {
    ALEvent msg;
    struct {
        s16 type;
        void *state;
    } common;
};



union ALSndpEvent;




struct SoundPlayerByteParameterEvent;
typedef struct SoundPlayerByteParameterEvent SoundPlayerByteParameterEvent;



union ALSndpEvent;
typedef union ALSndpEvent ALSndpEvent;



struct SoundPlayerByteParameterEvent;
struct SoundPlayerByteParameterEvent {
    s16 f0;
    s32 f4;
    s8 f8;
};

struct SoundPlayerWordParameterEvent;
typedef struct SoundPlayerWordParameterEvent SoundPlayerWordParameterEvent;


extern const f32 g_soundPlayerMinimumPitch;
#endif
