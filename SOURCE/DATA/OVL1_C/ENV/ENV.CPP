#include "DATA/REST_SOURCE_RECORDS.H"
#include "include_asm.h"
#include "COMMON/ALFXPARAM.H"

#if !(defined(VERSION_US_REV1))
const float g_EnvWords1[2] = {
    1.5258789e-05f, 1.0f,
};
#endif

#if !(defined(VERSION_US_REV1))
const float g_EnvWords2[10] = {
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
/* ROM-grounded data: src/g_EnvWords4_Env.c */
const float g_EnvWords4[2] = {
    1.5258789e-05f, 1.0f,
};

const float g_EnvWords3[10] = {
    0.0f, 0.0f, 1.875f, 0.0f, 1.75f, 0.0f,
    1.75f, 0.0f, 0.0f, 0.0f,
};
#endif
