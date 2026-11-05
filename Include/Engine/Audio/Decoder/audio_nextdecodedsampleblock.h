#ifndef ENGINE_AUDIO_DECODER_AUDIO_NEXTDECODEDSAMPLEBLOCK_H
#define ENGINE_AUDIO_DECODER_AUDIO_NEXTDECODEDSAMPLEBLOCK_H
#include "Common/lldivresult.h"
#include "Common/runtime_declarations.h"
#include "Common/audio_loaddecodedsamples.h"
#include "Audio/audio_nextdecodedsampleblock.h"
struct DecodeState;
extern s32 Audio_DecodeFrame(struct DecodeState *stream);
#endif
