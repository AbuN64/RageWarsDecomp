#include "include_asm.h"
#include "../../include/libgultra.h"
#include "COMMON/SHAREDRECV4.H"
#include "TYPES.H"
#include "../../include/libgultra/alunlink.h"





s32 _allocatePVoice(void *synth, void **selectedVoice, s16 requestedPriority) {
    s16 lowestPriority;
    s32 voiceStolen;
    s32 stolenResultCopy;
    void *candidateVoice;

    lowestPriority = requestedPriority;
    candidateVoice = ((AudioSynthVoiceAllocatorView *)synth)->pLameList.next;
    voiceStolen = 0;
    if ((candidateVoice != 0) || (candidateVoice = ((AudioSynthVoiceAllocatorView *)synth)->pFreeList.next, (candidateVoice != 0))) {
        *selectedVoice = candidateVoice;
        alUnlink(candidateVoice);
        alLink(candidateVoice, &((AudioSynthVoiceAllocatorView *)synth)->pAllocList.next);
    } else {
        candidateVoice = ((AudioSynthVoiceAllocatorView *)synth)->pAllocList.next;
        stolenResultCopy = voiceStolen;
        if (candidateVoice != 0) {
            do {
                if ((lowestPriority >= ((AudioPhysicalVoiceStealView *)candidateVoice)->vvoice->limit) &&
                    (((AudioPhysicalVoiceStealView *)candidateVoice)->offset == 0)) {
                    *selectedVoice = candidateVoice;
                    voiceStolen = 1;
                    lowestPriority = (s16)(u16)((AudioPhysicalVoiceStealView *)candidateVoice)->vvoice->limit;
                }
                candidateVoice = ((AudioPhysicalVoiceStealView *)candidateVoice)->next;
                stolenResultCopy = voiceStolen;
            } while (candidateVoice != 0);
        }
    }
    return voiceStolen;
}

