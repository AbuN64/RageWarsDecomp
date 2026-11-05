#include "include_asm.h"

#if defined(VERSION_US)
const unsigned char g_resultPreviewNumberFormatUs[3] = {
    0x25, 0x64, 0x00,
};
#endif

#if defined(VERSION_EU_X)
const unsigned char g_resultPreviewNumberFormatEuX[3] = {
    0x25, 0x64, 0x00,
};
#endif

#if defined(VERSION_DE) || defined(VERSION_US_REV1)
const float k_achieveFrameStep[1] = {
    0.06666667f,
};
#endif

#if defined(VERSION_DE) || defined(VERSION_US_REV1)
const unsigned char k_AchieveEncodedBytes[3] = {
    0x25, 0x64, 0x00,
};
#endif

#if defined(VERSION_EU)
const unsigned char g_resultPreviewNumberFormatEu[3] = {
    0x25, 0x64, 0x00,
};
#endif
