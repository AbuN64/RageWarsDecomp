#ifndef AUDIO_AUDIO_NEXTDECODEDSAMPLEBLOCK_H
#define AUDIO_AUDIO_NEXTDECODEDSAMPLEBLOCK_H
#include "Common/lldivresult.h"
extern void Audio_ClearDecodeFramesRemaining();
unsigned int Audio_GetDecodeFramesRemaining(void);
void *Audio_NextDecodedSampleBlock(void);
#endif
