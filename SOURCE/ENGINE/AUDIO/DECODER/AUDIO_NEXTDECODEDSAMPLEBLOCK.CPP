#include "COMMON/LLDIVRESULT.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AUDIO_LOADDECODEDSAMPLES.H"
#include "AUDIO/audio_nextdecodedsampleblock.H"

extern void Audio_DecodeFrame(void *stream);





void *Audio_NextDecodedSampleBlock(void) {
    struct DecodeState *base = &g_audioSampleDecodeState;
    unsigned short *counter;
    char *slots;
    unsigned short temp;

    if (base->count == 0) {
        return 0;
    }
    Audio_DecodeFrame(base);
    counter = &g_audioDecodedBlockCounter;
    temp = *counter + 1;
    *counter = temp;
    if ((unsigned int)(temp & 0xFFFF) >= 6) {
        *counter = 0;
    }
    slots = &g_audioDecodedSampleSlots;
    Audio_DecodeTransformBlock(slots + (*counter << 9), base);
    base->count = base->count - 1;
    return slots + (*counter << 9);
}

/** Return the global state word. */
unsigned int Audio_GetDecodeFramesRemaining(void) {
    return g_audioSampleDecodeState.count;
}

/** Clear the global word at VRAM 0x80151CD8. */
void Audio_ClearDecodeFramesRemaining(void) {
    g_audioSampleDecodeState.count = 0;
}
