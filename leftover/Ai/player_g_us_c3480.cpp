#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char g_flyModeOffText_us_C3480[13] =
    "Fly Mode Off\000";
#endif

#if defined(VERSION_US_REV1)
const char s_flyModeOffText[13] = "Fly Mode Off";
#endif

const float g_playerFlyModeConstantWords_us_C3490[16] = {
    0.0043633236f, 0.9f, 0.0021816618f, 8.533333f,
    102.399994f, 102.399994f, 17.066666f, 8.533333f,
    102.399994f, 102.399994f, 17.066666f, 5.9733334f,
    -5.9733334f, 11.946667f, 3.1415927f, 1.5707964f,
};
