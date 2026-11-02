#include "DATA/REST_SOURCE_RECORDS.H"
#include "include_asm.h"
#include "COMMON/ALFXPARAM.H"

#if !(defined(VERSION_US_REV1))
const float g_alFxNewConstantWords_de_eu_eu_x_us[7] = {
    3.0e+01f, 0.0f, 5.7762263e-06f, 1.0f, 0.5625f, 0.0f,
    1.0f,
};
#endif

#if defined(VERSION_US_REV1)
const float g_alFxNewConstantWords_us_rev1[6] = {
    3.0e+01f, 0.0f, 5.7762263e-06f, 1.0f, 0.5625f, 0.0f,
};

/* ROM-grounded data: src/k_alResampleNewConstantOne_us_rev1.c */
const float g_alResampleNewConstantWords[1] = {
    1.0f,
};
#endif
