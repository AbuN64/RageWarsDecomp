#include "COMMON/OBJRECAT3CV2.H"
#include "COMMON/GFX_INITIALIZEFRONTENDSERVICES.H"
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/RECORD.H"
#include "COMMON/TEXTURE.H"
#include "UI/QUAG/N64_ENG.H"
#include "UI/QUAG/N64_ENG.H"
#include "MENU/GFX/RECT.H"
#include "MATH/SMSMNGR_INITIALIZESCREENMANAGER.H"

#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
#else
extern f64 Gfx_GetNormalizedCounter(void);
#endif

/** Store four arguments in the adjacent global state words. */
void N64Eng_SetClipBounds(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3) {
    g_numericWidgetClipLeft = a0;
    g_numericWidgetClipTop = a1;
    g_numericWidgetClipRight = a2;
    g_numericWidgetClipBottom = a3;
}

void N64Eng_GetClipBounds(s32 *leftOut, s32 *topOut, s32 *rightOut, s32 *bottomOut) {

    *leftOut = g_numericWidgetClipLeft;
    *topOut = g_numericWidgetClipTop;
    *rightOut = g_numericWidgetClipRight;
    *bottomOut = g_numericWidgetClipBottom;
}

f64 N64Eng_GetTimeSeconds(void) {
    return
#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
Gfx_GetConvertedCounterRatio
#else
Gfx_GetNormalizedCounter
#endif
() - (0.0);
}

/** Perform no operation. */
void N64Eng_RenderNoop(void) {
}

void N64Eng_ResetRenderState(void) { Rect_ResetRenderState(); }

/** Copy the global two-word record into the two output pointers. */
void N64Eng_GetScreenSize(int *widthOut, int *heightOut) {
    *widthOut = g_hudReferenceViewportWidth;
    *heightOut = g_hudReferenceViewportHeight;
}

int N64Eng_GetFrameCounter(void) {
    return g_n64UiFrameCounter;
}

/** Increment the global counter g_n64UiFrameCounter. */
void N64Eng_AdvanceFrameCounter(void) {
    g_n64UiFrameCounter += 1;
}

void N64Eng_RegisterNumericWidgetClass(void) {
    SmSmngr_RegisterElementHandlers(2917, N64Eng_DispatchNumericWidgetEvent_Address, N64Eng_DrawNumericWidgetChildren_Address, 3);
}

/* ROM-grounded data: rodata/writable/800D2C18 */
#ifdef VERSION_DE
unsigned int g_N64EngEncodedWords[2] = {
    0x00000000, 0x0000000F,
};
#endif
#ifdef VERSION_EU
unsigned int g_N64EngEncodedWords[2] = {
    0x00000000, 0x00000000,
};
#endif
#ifdef VERSION_EU_X
unsigned int g_N64EngEncodedWords[2] = {
    0x00000000, 0x74000000,
};
#endif
#ifdef VERSION_US
unsigned int g_N64EngEncodedWords[2] = {
    0x00000000, 0x50414354,
};
#endif
#ifdef VERSION_US_REV1
unsigned int g_N64EngEncodedWords[2] = {
    0x00000000, 0x20626F72,
};
#endif
