#include "TYPES.H"

#include "include_asm.h"

/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
#if defined(VERSION_DE)
s32 g_audioAbortdisktransferDataConstantWords = 4194049;
#endif
#if defined(VERSION_EU)
s32 g_audioAbortdisktransferDataConstantWords = 4194049;
#endif
#if defined(VERSION_EU_X)
s32 g_audioAbortdisktransferDataConstantWords = 4194049;
#endif
#if defined(VERSION_US)
s32 g_audioAbortdisktransferDataConstantWords = 4194049;
#endif
#if defined(VERSION_US_REV1)
s32 g_audioAbortdisktransferDataConstantWords = 4194049;
#endif

#if defined(VERSION_US)
#if defined(VERSION_US)
char s_audioRetainedTextFragment_us[4] __attribute__((aligned(4))) = "RD_L";
#endif
#endif

#if defined(VERSION_EU)
#if defined(VERSION_EU)
extern char g_audioDiskTransferLinkTable[];
#if defined(VERSION_EU)
void * g_audioDiskTransferLinkTableEntryPointer_eu[1] = {
    (void *)g_audioDiskTransferLinkTable + 0x18
};
#endif
#endif
#endif

#if defined(VERSION_DE)
#if defined(VERSION_DE)
extern char g_osaisetfrequencyDataConstantWords[];
#if defined(VERSION_DE)
void * g_osAiSetFrequencyConstantWordsPointer_de[1] = {
    (void *)&g_osaisetfrequencyDataConstantWords
};
#endif
#endif
#endif
