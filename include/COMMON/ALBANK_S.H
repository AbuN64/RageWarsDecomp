#ifndef COMMON_ALBANK_S_H
#define COMMON_ALBANK_S_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
/* Relocated bank-file header read by the sound context initializer. */






























struct SequencePlayerEventView;
typedef struct SequencePlayerEventView SequencePlayerEventView;










struct SeqplayerVoicePool;
typedef struct SeqplayerVoicePool SeqplayerVoicePool;


typedef signed int ( *Lane_ALOscUpdate)(void *, float *);


struct SeqplayerVoicePool;
struct SeqplayerVoicePool {
    char pad[0x64];
    NodeGskyActivateMessagePool *head;
    NodeGskyActivateMessagePool *tail;
    NodeGskyActivateMessagePool *free;
};



extern float g_sequenceInitialPitchBend;










struct SeqplayerVoiceEvent;
struct SeqplayerVoiceEvent {
    s16 type;
    s16 pad;
    void *object;
    s32 unused;
};






typedef signed int ( *Lane_ALOscInit)(void * *, float *, unsigned char, unsigned char, unsigned char, unsigned char);



struct SeqplayerVoiceEvent;
typedef struct SeqplayerVoiceEvent SeqplayerVoiceEvent;


typedef void ( *Lane_ALOscStop)(void *);










struct SequencePlayerEventView;
struct SequencePlayerEventView {
    char pad0[0x18];
    void * sequence;
    char pad18[0x24 - 0x18 - sizeof(void*)];
    s32 microsecondsPerTick;
    char pad24[0x2C - 0x24 - sizeof(s32)];
    s32 state;
    char pad2C[0x48 - 0x2C - sizeof(s32)];
    char eventQueue;
    char pad48[0x7C - 0x48 - sizeof(char)];
    void * loopStart;
    char pad7C[0x80 - 0x7C - sizeof(void*)];
    char * loopEnd;
    char pad80[0x84 - 0x80 - sizeof(char*)];
    s32 loopCount;
};



























extern float g_sequenceChannelInitialOscillatorValue;


#endif
