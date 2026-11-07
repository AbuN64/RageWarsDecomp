#ifndef ENGINE_AUDIO_DECODE_STREAM_H
#define ENGINE_AUDIO_DECODE_STREAM_H
#include "types.h"

/* The packed-sample bit reader's state, read as halfwords by Audio_ReadPackedSamples and Audio_InitDecodeStream,
   followed by the bytes each version holds after it up to the next object. */
typedef struct AudioDecodeStream {
    u16 packedBitsLeft;
    u16 bitBuffer;
    u16 bitsLeft;
    s16 frameHeaderRead;
    s16 transformTablesInitialized;
    u16 decodedBlockCounter;
#if defined(VERSION_US)
    char textThGuardDam[12];
    unsigned int words[37];
#elif defined(VERSION_US_REV1)
    u8 zeroConstantTail[12];
#else
    unsigned int words[40];
#endif
} AudioDecodeStream;
extern AudioDecodeStream g_audioInitdecodestreamDataConstantWords;
#endif
