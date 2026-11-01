#include "include_asm.h"

/* 800E0DA8.CPP */
#if !(defined(VERSION_US_REV1))
const char k_GPakformatint1EncodedWords[4] =
    "   \000";
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char g_pakChannelNumberFormat_GPakformatint1[4] =
    "%1d";
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char g_pakFormatInt2[4] =
    "%2d";
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char s_snapshotThreePartNumberFormat[14] =
    "%3d.%02d.%02d\000";
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/s_pakThreeSpacesText.c */
const char k_GPakformatint1EncodedBytes[4] =
    "   \000";
#endif

/* 800E0DAC.CPP */
#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/* ROM-grounded data: rodata/shared/800E0DAC */
const char g_pakFormatInt1[4] =
    "%1d\000";
#endif

/* 800E0DB0.CPP */
#if defined(VERSION_DE) || defined(VERSION_US)
const char k_GPakformatint1EncodedWordsBlock1[4] =
    "%2d";
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_pakFormatInt2.c */
const char k_GPakformatint1EncodedBytesBlock1[4] =
    "%2d";
#endif
