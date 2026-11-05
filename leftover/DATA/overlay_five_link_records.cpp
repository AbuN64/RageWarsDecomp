#include "include_asm.h"
#include "types.h"

const float k_overlayFiveLinkRecordFloatConstantsBlock1[1] = {
    3.0f,
};

#if defined(VERSION_DE)
const f32 k_overlayFiveLinkRecordFloatConstantsBlock2 = -118.0f;
#endif
#if defined(VERSION_EU)
const f32 k_overlayFiveLinkRecordFloatConstantsBlock2 = -118.0f;
#endif
#if defined(VERSION_EU_X)
const f32 k_overlayFiveLinkRecordFloatConstantsBlock2 = -118.0f;
#endif
#if defined(VERSION_US)
const f32 k_overlayFiveLinkRecordFloatConstantsBlock2 = -118.0f;
#endif
#if defined(VERSION_US_REV1)
const f32 k_overlayFiveLinkRecordFloatConstantsBlock2 = -118.0f;
#endif

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
float k_OverlayFiveLinkRecordFloatConstantsC9F74Data[3] = {
    74.0f, 74.0f, -118.0f,
};
#endif

#if defined(VERSION_US_REV1)
float g_overlayFiveLinkRecordFloatConstants_usrev1_CFDBC[3] = {
    74.0f, 74.0f, -118.0f,
};
#endif
