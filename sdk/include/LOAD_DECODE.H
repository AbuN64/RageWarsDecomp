#ifndef LOAD_DECODE_H
#define LOAD_DECODE_H
#include "TYPES.H"
#include <PR/abi.h>
#include "COMMON/AUDIO_LOADDECODEDSAMPLES.H"

extern u32 Sound_GetCachedAudioBlockAddress(void *book, s32 size); /* game ADPCM codebook cache */
extern Acmd *_decodeChunk(Acmd *ptr, ALLoadFilter48_2 *f, s32 tsam, s32 nbytes, s16 outp, s16 inp,
                           u32 flags); /* _decodeChunk */
#endif
