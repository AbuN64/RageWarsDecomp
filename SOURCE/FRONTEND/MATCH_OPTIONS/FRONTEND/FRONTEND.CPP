#include "include_asm.h"
#include "COMMON/FRONTEND_RESOURCE_LOAD_STATE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/OWNERRECAT8V1.H"
#include "TYPES.H"

/* 80423280_2.CPP */
/* 80423280_2.CPP */
#if defined(VERSION_DE)
float k_FrontendEncodedWordsBlock9[2] = {
    13.0f, -5.0e+01f,
};
#endif

/* 80406A88_11.CPP */
#if defined(VERSION_EU_X)
extern void SmpButton_WrapButtonWidget(int id);

int Frontend_ClearEuxLoadingHints(void) { SmpButton_WrapButtonWidget(477); SmpButton_WrapButtonWidget(478); return 0; }
#endif

/* 80408CB0_33.CPP */
#if defined(VERSION_EU)
/* Marks two loading-screen hint slots (0x1D9 and 0x1DA) unused. */
#include "TYPES.H"
#include "COMMON/OWNERRECAT8V1.H"

s32 Frontend_ClearEuLoadingHints(void) {
    SmpButton_WrapButtonWidget(473);
    SmpButton_WrapButtonWidget(474);
    return 0;
}
#endif

/* 80423280_44.CPP */
#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* Marks two loading-screen hint slots (0x1D9 and 0x1DA) unused. */

s32 Frontend_ClearLoadingHints(void) {
    SmpButton_WrapButtonWidget(473);
    SmpButton_WrapButtonWidget(474);
    return 0;
}
#endif

/* k_FrontendEncodedWordsBlock2_Frontend.CPP */
#if defined(VERSION_US)
unsigned int k_FrontendEncodedWordsBlock2[9] = {
    0x5F335400, 0x00040000, 0x3C9374BC, 0x40A00000, 0x41500000, 0xC2480000, 0x3D23D70A, 0x41880000,
    0xC1200000,
};
#endif

/* 80423280_14.CPP */
#if defined(VERSION_EU_X)
unsigned int k_FrontendEncodedWordsBlock13[2] = {
    0x00000016, 0x3DE147AE,
};
#endif

/* 800E1A98.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800E1A98 */
unsigned int g_FrontendEncodedWordsBlock2[2] = {
    0x0000001F, 0x00000024,
};
#endif

/* 80423280_15.CPP */
#if defined(VERSION_EU)
unsigned int k_FrontendEncodedWordsBlock16[2] = {
    0x08000027, 0x08000028,
};
#endif
