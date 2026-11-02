#include "include_asm.h"

/* 800C5670.CPP */
#if defined(VERSION_EU)
const float g_Setn64DrawfullscreenbackdropWords1[4] = {
    255.0f, 0.17453295f, 0.4f, 0.7f,
};
#endif

/* 800CA4B0.CPP */
#if defined(VERSION_DE) || defined(VERSION_US_REV1)
const float g_Setn64DrawfullscreenbackdropWords4[4] = {
    255.0f, 0.17453295f, 0.4f, 0.7f,
};
#endif

/* 80290990.CPP */
#if defined(VERSION_US)
/** Perform no operation. */
void SetN64_EmptyBackdropHookUs(void) {
}
#endif

/* 802909E0_15.CPP */
#if defined(VERSION_EU_X)
const float g_Setn64DrawfullscreenbackdropWords2[4] = {
    255.0f, 0.17453295f, 0.4f, 0.7f,
};
#endif

/* SETN64_DRAWFULLSCREENBACKDROP_WORDS_US.CPP */
#if defined(VERSION_US)
const float g_Setn64DrawfullscreenbackdropWords5[4] = {
    255.0f, 0.17453295f, 0.4f, 0.7f,
};
#endif
