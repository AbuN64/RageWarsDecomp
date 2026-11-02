#include "include_asm.h"

#if defined(VERSION_EU)
const char g_animObjectInfoText[20] =
    "anim object info\000\102\000\010";
const unsigned int k_gastatePrepareAnimationFramesWords[2] = {
    0x00042403, 0x00621821,
};
#elif !(defined(VERSION_US_REV1))
const char g_animObjectInfoText[17] =
    "anim object info\000";
#endif

#if defined(VERSION_DE)
const float k_gastatePrepareAnimationFramesOneAndTenthFloats[2] = {
    1.0f, 0.1f,
};
#endif

#if defined(VERSION_US)
char s_GAnimobjectinfotextColorTText[11] =
    "ColorT\000\000\005\000\000";
#endif


#if defined(VERSION_EU_X)
char s_GAnimobjectinfotextEvelNameText[11] =
    "evel name\000\000";
#endif






#if defined(VERSION_US_REV1)
const char s_animObjectInfoText[17] =
    "anim object info";
#endif
