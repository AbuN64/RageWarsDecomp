#ifndef COMMON_SOUND_PLAYER_PARAMETER_EVENTS_H
#define COMMON_SOUND_PLAYER_PARAMETER_EVENTS_H
#include "types.h"
#include "Common/runtime_declarations.h"

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
#endif
