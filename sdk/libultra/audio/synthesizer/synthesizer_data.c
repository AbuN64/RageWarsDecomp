#include "include_asm.h"
#include "Common/alfxparam.h"
#include "Synthesizer/synthesizer_data.h"

const char s_audioSynthesizerText[20] = "audio/synthesizer.c";

/* ROM-grounded data: src/g__timeToSamplesConstantsUsRev1_Synthesizer.c */
const unsigned int g__timeToSamplesConstants[2] = {
    0x358637BD, 0x3F000000,
};

/* ROM-grounded data: src/g__timeToSamplesNoRoundConstantsUsRev1_Synthesizer.c */
const unsigned int g__timeToSamplesNoRoundConstants[2] = {
    0x358637BD, 0x3F000000,
};

#if defined(VERSION_US)
unsigned int k_SynthesizerEncodedWords[2] = {
    0x08000600, 0x00000000,
};
#endif

#if defined(VERSION_EU_X)
unsigned int k_synthesizerPackedWords[2] = {
    0x00000000, 0x000052DA,
};
#endif

#if defined(VERSION_EU)
unsigned int k_synthesizerOffsetPair[2] = {
    0x00230180, 0x002300D4,
};
#endif

#if defined(VERSION_DE)
unsigned int k_synthesizerPointerPair[2] = {
    0x002B3FBC, 0x002B3FCC,
};
#endif
