#include "include_asm.h"

const float g_unpackFixedMatrixInverseFixedOne_us_C5300[1] = {
    1.5258789e-05f,
};

const float g_convertMatrixToFloatInverseScaleAndOne_us_C5304[2] = {
    1.5258789e-05f, 1.0f,
};

const float g_interpolateQuaternionArcOne_us_C530C[1] = {
    1.0f,
};

const float g_interpolateQuaternionWithLinearFallbackThreshold_us_C5310[2] = {
    0.70710677f, 1.0f,
};

const float g_interpolateQuaternionWithLinearFallbackConstants_us_C5318[1] = {
    1.0f,
};

#if !(defined(VERSION_US_REV1))
const float g_blendRandomDirectionUnitPair_us_C531C[2] = {
    1.0f, 1.0f,
};
#endif

#if defined(VERSION_US_REV1)
const float g_blendRandomDirectionClampOnes_usrev1_CA4DC[2] = {
    1.0f, 1.0f,
};
#endif

const float g_blendRandomXDirectionConstants1_us_C5324[1] = {
    0.0001f,
};

#if !(defined(VERSION_US_REV1))
const float g_quaternionLerpOnes_us_C5328[2] = {
    1.0f, 1.0f,
};
#endif

#if !(defined(VERSION_US_REV1))
const float g_blendRandomYDirectionConstants_us_C5330[4] = {
    1.0e+04f, 0.0001f, 1.0f, 1.0f,
};
#endif

#if defined(VERSION_US_REV1)
const float g_blendRandomXDirectionConstants2_usrev1_CA4E8[2] = {
    1.0f, 1.0f,
};

const float g_blendRandomYDirectionScaleEpsilonOnes_usrev1_CA4F0[4] = {
    1.0e+04f, 0.0001f, 1.0f, 1.0f,
};
#endif

#if !(defined(VERSION_US_REV1))
const float g_blendRandomZDirectionConstants_us_C5340[4] = {
    1.0e+04f, 0.0001f, 1.0f, 1.0f,
};
#endif

#if defined(VERSION_US_REV1)
const float g_blendRandomZDirectionScaleEpsilonOnes_usrev1_CA500[4] = {
    1.0e+04f, 0.0001f, 1.0f, 1.0f,
};
#endif

const float g_buildDirectionQuaternionNearUnitConstants_us_C5350[6] = {
    1.0f, 1.0f, 0.99999f, 0.99999f, 1.0f, 0.5f,
};
