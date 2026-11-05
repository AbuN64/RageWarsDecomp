#include "Data/rest_source_records.h"
#include "include_asm.h"
#include "Common/alfxparam.h"

#if !(defined(VERSION_US_REV1))
const float g_envFixedPointScaleFloats[2] = {
    1.5258789e-05f, 1.0f,
};
#endif

#if !(defined(VERSION_US_REV1))
const float g_envSevenEighthsWeightFloats[10] = {
    0.0f, 0.0f, 1.875f, 0.0f, 1.75f, 0.0f,
    1.75f, 0.0f, 0.0f, 0.0f,
};
#endif

#if defined(VERSION_US)
char s_EnvTGamText[8] =
    "_t\014m_Gam";
#endif

#if defined(VERSION_EU)
char k_EnvEncodedBytes[8] =
    "D\026\000\000\077333";
#endif

#if defined(VERSION_US_REV1)
const float g_envSixteenBitFractionScaleFloats[2] = {
    1.5258789e-05f, 1.0f,
};

const float g_envOneSevenFiveWeightFloats[10] = {
    0.0f, 0.0f, 1.875f, 0.0f, 1.75f, 0.0f,
    1.75f, 0.0f, 0.0f, 0.0f,
};
#endif
