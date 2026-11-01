#ifndef COMMON_COMPRESSED_SEQUENCE_AND_EVENT_VIEWS_H
#define COMMON_COMPRESSED_SEQUENCE_AND_EVENT_VIEWS_H
#include "TYPES.H"
#include "COMMON/ALBANK_S.H"
#include "COMMON/ITEMRECAT20V1.H"
struct CompressedSequenceMetaEvent;
typedef struct CompressedSequenceMetaEvent CompressedSequenceMetaEvent;

extern float g_compressedSecondsToTicksSignedLimit;















extern double g_compressedTicksToSecondsDivisionUnsignedBias;


struct InitParams;
struct InitParams {
    s32 count38;
    s32 count1C;
    u8 kind;
    u8 debugFlags;
    u8 pad0A[2];
    void *context;
    Lane_ALOscInit value10;
    Lane_ALOscUpdate value14;
    Lane_ALOscStop value18;
};

extern double g_compressedTicksToSecondsTempoUnsignedBias;

struct CompressedSequenceTempoAndQueueView;
typedef struct CompressedSequenceTempoAndQueueView CompressedSequenceTempoAndQueueView;

struct CompressedSequenceEventQueueHead;
typedef struct CompressedSequenceEventQueueHead CompressedSequenceEventQueueHead;



struct CompressedSequenceEventLink;
typedef struct CompressedSequenceEventLink CompressedSequenceEventLink;

extern double g_compressedSequenceDivisionUnsignedBias;







struct CompressedSequenceEventNode;
struct CompressedSequenceEventNode {
    struct CompressedSequenceEventNode *prev;
    struct CompressedSequenceEventNode *next;
    s32 value;
    short type;
};

struct CompressedSequenceEventNode;
struct CompressedSequenceEventQueueHead;
struct CompressedSequenceEventQueueHead {
    char pad0[0x8];
    struct CompressedSequenceEventNode * allocatedEvents;
};

struct CompressedSequenceEventNode;
typedef struct CompressedSequenceEventNode CompressedSequenceEventNode;

struct CompressedSequenceAllocatedEventsView;
struct CompressedSequenceAllocatedEventsView {
    unsigned char padding[80];
    CompressedSequenceEventNode * link;
};





struct InitParams;
typedef struct InitParams InitParams;

extern float g_compressedSecondsToTicksMicrosecondScale;

struct DecodeResult;
struct DecodeResult {
    s16 type;
    u8 pad2[6];
    u8 status;
    u8 first_data;
    u8 second_data;
    u8 extra1;
    u32 extra2;
};



struct CompressedSequenceAllocatedEventsView;
typedef struct CompressedSequenceAllocatedEventsView CompressedSequenceAllocatedEventsView;

extern float g_compressedTicksToSecondsMicrosecondScale;







struct CompressedSequenceEventLink;
struct CompressedSequenceEventLink {
    CompressedSequenceEventNode * link;
};






extern float g_compressedSequenceQuarterNoteUnit;

struct CompressedSequenceMetaEvent;
struct CompressedSequenceMetaEvent {
    s16 type;
    u8 pad2[6];
    u8 status;
    u8 metaType;
    u8 padA;
    u8 tempoHigh;
    u8 tempoMid;
    u8 tempoLow;
    u8 padE[2];
};

extern double g_compressedSecondsToTicksTempoUnsignedBias;



struct DecodeResult;
typedef struct DecodeResult DecodeResult;



extern double g_compressedSecondsToTicksDivisionUnsignedBias;

struct CompressedSequenceTempoAndQueueView;
struct CompressedSequenceTempoAndQueueView {
    char pad0[0x24];
    s32 uspt;
    char pad24[0x48 - 0x24 - sizeof(s32)];
    char evtq;
};

#endif
