#ifndef COMMON_AUDIO_LOADDECODEDSAMPLES_H
#define COMMON_AUDIO_LOADDECODEDSAMPLES_H
#include <PR/abi.h>
#include "COMMON/AUDIO_CALLBACKS.H"
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
extern float g_audioTransformSums[];


extern float g_audioSampleMaximum;




struct ALLoadFilter48_2;
typedef struct ALLoadFilter48_2 ALLoadFilter48_2;



extern float g_audioTransformCoefficientStep;

extern float g_audioTransformCosines[];


extern float g_audioTransformSines[];










struct CacheResourceBlockView;



struct ALLoadFilter48_2;
struct ALLoadFilter48_2 {
    ALFilter_s14 filter;
    void *state;
    void *lstate;
    ALRawLoop loop;
    struct ALWaveTable_s *table;
    s32 bookSize;
    ALDMAproc dma;
    void *dmaState;
    s32 sample;
    s32 lastsam;
    s32 first;
    s32 memin;
};

extern float g_audioTransformDifferences[];

extern float g_audioSampleNegativeRoundingBias;

extern float g_audioSampleMinimum;

extern float g_audioTransformPrimaryScale;

extern Acmd *Audio_LoadDecodedSamples(ALLoadFilter48_2 *filter, s16 *outp, s32 byteCount, s32 sampleOffset, Acmd *p);

extern float g_audioTransformOutputGain;

extern float g_audioTransformTertiaryScale;

extern float g_audioSamplePositiveRoundingBias;


typedef struct TransformAudioFrame {
    s16 bandScales[16];
    u8 reserved20[0xA0 - 0x20];
    s16 coefficients[256];
} TransformAudioFrame;

typedef struct DecodeState {
    s32 first;
    s32 third;
    void *source;
    s32 second;
    s32 count;
    void *cursor;
    u16 frame[336]; /* Packed decoder transport, also consumed as TransformAudioFrame. */
} DecodeState;
extern DecodeState g_audioSampleDecodeState;
extern u16 gPackedBitsLeft;
extern u16 gPackedBitMasks[17];
extern u16 gPackedSignBits[17];
extern u16 gPackedWord;
extern unsigned short g_audioDecodeBitBuffer;
extern unsigned short g_audioDecodeBitsLeft;
extern s16 g_audioDecodeFrameHeaderRead;
extern s16 g_audioTransformTablesInitialized;

/* Dictionary decoder records, shared by the block and phrase streams. */
typedef struct DecodeNode {
    u16 first;
    u16 second;
} DecodeNode;

typedef struct DecodeSample {
    u16 tag;
    u16 value;
} DecodeSample;

typedef struct DecodePhrase {
    u8 pad0[0xA0];
    DecodeSample samples[64];
    s32 count;                     /* 0x1A0 */
    u8 pad1A4[0x14];
} DecodePhrase;

typedef struct DecodeTable {
    u8 pad0[0xE];
    u16 width;
    u8 pad10[0xC];
    DecodePhrase *phrases;          /* 0x1C */
    DecodeNode *tree;               /* 0x20 */
} DecodeTable;

typedef struct DecodeBlock {
    s32 kind;
    s32 start;
    s32 length;
    s32 offset;
    DecodeTable *table;
} DecodeBlock;
extern DecodeBlock g_audioDecodeBlock[]; /* Audio_DecodeFrame block list, ends at kind 0 */
extern u16 g_audioDecodeScaleTable[16];        /* Audio_DecodeFrame per-coefficient history */
#endif
