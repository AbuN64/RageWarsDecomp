#ifndef BUF16B_H
#define BUF16B_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/AUDIO_INITIALIZE.H"

struct Buf16b;
struct Buf16b {
    s16 count;
    s16 _pad2;
    s16 value;
    s16 _pad6;
    s32 _pad8;
    s32 _padC;
};

struct Buf16c;
typedef struct Buf16c Buf16c;



struct Buf16c;
struct Buf16c {
    s16 count;
    s16 _pad2;
    s32 zero;
    s8 f8;
    s8 f9;
    s8 fA;
    s8 _padB;
    s32 _padC;
};

struct Buf16b;
typedef struct Buf16b Buf16b;

typedef struct SeqFreeVoice { struct SeqFreeVoice *next; char pad[0x34]; } SeqFreeVoice;

typedef struct SeqInitPlayer {
    void *next;
    struct SeqInitPlayer *self;
    void *callback;
    char padC[8];
    void *driver;
    void *target;
    s32 time;
    void *bank;
    s32 uspt, delta, state;
    u16 mask;
    s16 volume;
    u8 channels, debug;
    u8 pad36[2];
    s16 eventType;
    char pad3A[0xE];
    char queue[0x14];
    s32 frameTime;
    void *channelState;
    SeqFreeVoice *allocHead, *allocTail, *freeList;
    void *initOsc, *updateOsc, *stopOsc;
    void *loopStart, *loopEnd;
    s32 loopCount;
} SeqInitPlayer;
extern char Seqplayer_ProcessSequenceEvents_Address;
#endif
