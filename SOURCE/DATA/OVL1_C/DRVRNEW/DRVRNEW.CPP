#include "DATA/REST_SOURCE_RECORDS.H"
#include "include_asm.h"
#include "COMMON/ALFXPARAM.H"

/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
const RestLinkerAlignmentFill8 g_Drvrnew1LinkerAlignmentFill625 = {
    { 63, 16, 0, 0, 0, 0, 0, 0 },
};

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_US)
const float k_DrvrnewEncodedWords[2] = {
    6.5f, 0.0f,
};
#endif


#if defined(VERSION_EU)
float k_DrvrnewEncodedWordsBlock2[2] = {
    1.0f, 1.7904929f,
};
#endif

#if defined(VERSION_DE)
char k_DrvrnewEncodedBytes[8] =
    "o/env.c\000";
#endif
