#ifndef COMMON_CONTREADFORMAT_H
#define COMMON_CONTREADFORMAT_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
struct ContReadFormat;
typedef struct ContReadFormat ContReadFormat;

struct ALSynthalSndpNew;
struct ALSynthalSndpNew {
    ALPlayer_s14 *head;
};

struct ALSndPlayeralSndpNew;
struct ALSynthalSndpNew;
struct ALSndPlayeralSndpNew {
    ALPlayer_s14 node;
    ALEventQueue evtq;
    ALEvent nextEvent;
    struct ALSynthalSndpNew *drvr;
    s32 target;
    void *sndState;
    s32 maxSounds;
    s32 frameTime;
    s32 nextDelta;
    s32 curTime;
};

struct ALGlobalsalSndpNew;
typedef struct ALGlobalsalSndpNew ALGlobalsalSndpNew;

extern int g_controllerInitialized;



struct ALSoundState;
typedef struct ALSoundState ALSoundState;

struct ALSndPlayeralSndpNew;
typedef struct ALSndPlayeralSndpNew ALSndPlayeralSndpNew;


struct ALSynthalSndpNew;
typedef struct ALSynthalSndpNew ALSynthalSndpNew;

struct ALGlobalsalSndpNew;
struct ALGlobalsalSndpNew {
    ALSynthalSndpNew drvr;
};

struct ContReadFormat;
struct ContReadFormat {
    u8 dummy;
    u8 txsize;
    u8 rxsize;
    u8 cmd;
    u16 button;
    s8 stick_x;
    s8 stick_y;
};

struct ContPad;
struct ContPad {
    u16 button;
    s8 stick_x;
    s8 stick_y;
    u8 error;
};


struct ALSoundState;
struct ALSoundState {
    ALVoice voice;
    void *sound;
    s16 priority;
    f32 pitch;
    s32 state;
    s16 vol;
    u8 pan;
    u8 fxMix;
};


struct ContPad;
typedef struct ContPad ContPad;
#endif
