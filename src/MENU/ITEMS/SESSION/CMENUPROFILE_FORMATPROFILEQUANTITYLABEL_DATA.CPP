#include "include_asm.h"
#if defined(VERSION_EU_X)
const unsigned int k_cmenuprofileFormatprofilequantitylabelDataConstantWords[3] = {
    0x00419F50, 0x00000000, 0x00000000,
};
#endif
#if defined(VERSION_EU)
const unsigned int k_cmenuprofileFormatprofilequantitylabelDataLinkGapWords[3] = {
    0xAE6A0154, 0xCA7C382A, 0xC97B0805,
};
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char k_cmenuprofileFormatprofilequantitylabelDataTextBytes[5] =
    "%02d";
#endif
