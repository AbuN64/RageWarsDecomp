#include "include_asm.h"

/* AUDIOMGR_INIT_1.CPP */
#if defined(VERSION_US)
char s_AudiomgrInitIMsgTText[8] =
    "iMsgT\000\000@";
#endif

#if defined(VERSION_EU_X)
float k_AudiomgrInitEncodedWordsBlock2[2] = {
    1.0f, 1.0f,
};
#endif


#if defined(VERSION_DE)
float k_AudiomgrInitEncodedWords[2] = {
    0.5f, 127.0f,
};
#endif

/* AUDIOMGR_INIT_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800C8FB8 */
float g_AudiomgrInitEncodedWords[2] = {
    1.0f, 1.0f,
};
#endif
