#include "include_asm.h"

#if defined(VERSION_DE)
unsigned int g_deviceUpdatetriggeredmotionFloatConstants[3] = {
    0x3EAAAAAB, 0x42480000, 0x3E860A93,
};
#endif

const float k_deviceUpdateTriggeredMotionUnit[1] = {
    1.0f,
};

#if defined(VERSION_EU_X)
float k_deviceUpdatetriggeredmotionFragment[3] = {
    32.0f, 0.5f, 32.0f,
};
#endif

#if defined(VERSION_EU)
unsigned int k_DeviceUpdatetriggeredmotionData[3] = {
    0x2402FFFF, 0x14620016, 0x3C030002,
};
#endif

#if defined(VERSION_US_REV1)
float g_triggeredMotionStepHalfScaleFloats[3] = {
    32.0f, 0.5f, 32.0f,
};
#endif
