#ifndef COMMON_LLDIVRESULT_H
#define COMMON_LLDIVRESULT_H
#include "types.h"

typedef struct LldivResult LldivResult;

struct LldivResult {
    s64 quot;
    s64 rem;
};

struct LldivResult;

extern s64 Libc_SignedDivide(s64, s64) __attribute__((const));

extern s64 Libc_SignedRemainder(s64, s64) __attribute__((const));

#include <PR/abi.h>
#include "Common/audio_callbacks.h"
#include "Common/sharedplayer.h"
#include "Common/particle_lighting.h"
#include "Common/runtime_declarations.h"
extern Acmd *alRaw16Pull(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p);







extern char alRaw16Pull_Address;
extern char Audio_LoadDecodedSamples_Address;

#include "Audio/audio_decodetransformblock.h"
#endif
