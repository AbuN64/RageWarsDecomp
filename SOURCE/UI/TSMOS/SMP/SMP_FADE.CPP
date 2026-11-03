#include "COMMON/FRUSTUM.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/ANIMATION.H"
#include "TYPES.H"
#include "MATH/SMSMNGR_INITIALIZESCREENMANAGER.H"
#include "MENU/SMPFADE_REGISTERFADECLASS.H"
#include "RESMGR/resmgr_string_memory.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "include_asm.h"
#include "UI/TSMOS/SMP/SMP_FADE.H"

/* 804196C0_20.CPP */
/* Creates a 0x7C-byte fading widget: finds the frame the low half of the first argument names and
   the item the second names in the current context through GetMenuScreenOwner, Node_GetScreenData and
   Node_FindWidgetByResourceId, allocates and zeroes the widget, tags it 0xB60 with kind 8, links the frame at
   0x44 (clearing its word at 0x20 and setting 0x24 to g_fadeWidgetInitialProgress) and the item at 0x48, sets both
   scales at 0x4C and 0x50 to g_fadeWidgetInitialScale, copies the item's two colours at 0x2C and 0x30 to 0x60,
   stores the green and red differences between them over 75 steps at 0x70 and 0x74, marks it
   active at 0x78, starts it through SmpSlider_EnableTransition and SmpSlider_SetTransitionMode(1) and attaches it to the
   frame through Node_InsertWidgetBefore. Returns the widget. */

extern struct Record *Cache_AllocateMemory(s32 size);
extern void SmpSlider_EnableTransition(struct Access_s32_5C *object);
extern void SmpSlider_SetTransitionMode(struct SliderTransitionView *object, s32 mode);
extern void Node_InsertWidgetBefore(struct Tree *node, struct Tree *added);

MenuFadeWidget *SmpFade_CreateFadeWidget(s32 frameId, s32 itemId) {
    MenuFadeWidget *frame;
    s32 context;
    MenuFadeWidget *result;

    frame = Node_FindWidgetByResourceId(Node_GetScreenData(GetMenuScreenOwner()), frameId & 0xFFFF);
    context = Node_GetScreenData(GetMenuScreenOwner());
    result = Cache_AllocateMemory(124);
    XPlus_FillBytes(result, 0, 124);
    result->kindB = 2912;
    result->flags = 8;
    result->kindA = 2912;
    result->frame = frame;
    result->item = Node_FindWidgetByResourceId((void*)context, itemId & 0xFFFF);
    result->scaleX = g_fadeWidgetInitialScale;
    result->scaleY = g_fadeWidgetInitialScale;
    result->frame->progressXWord = 0;
    result->frame->progressY = g_fadeWidgetInitialProgress;
    result->copies[0] = result->item->colours[0];
    result->copies[1] = result->item->colours[1];
    result->copies[2] = result->item->colours[2];
    result->copies[3] = result->item->colours[3];
    result->greenStep = (((result->item->colours[1] & 0xFF0000) >> 16) -
                         ((result->item->colours[0] & 0xFF0000) >> 16)) / 75;
    result->redStep = (((u8 *)result->item->colours)[0] - ((u8 *)result->item->colours)[4]) / 75U;
    result->active = 1;
    SmpSlider_EnableTransition(result);
    SmpSlider_SetTransitionMode(result, 1);
    Node_InsertWidgetBefore(frame, result);
    return result;
}

void SmpFade_RegisterFadeClass(void) {
    SmSmngr_RegisterElementHandlers(2912, g_SmpSlider_DispatchTransitionEventAddress, g_SmpSlider_IgnoreFormattedMessageAddress, 3);
}

/* 800E1470.CPP */
#if !(defined(VERSION_US_REV1))
const float g_fadeWidgetSecondaryProgressConstants[2] = {
    0.33333334f, 0.05f,
};
#endif

#if defined(VERSION_US)
unsigned int k_SmpFadeEncodedWords[2] = {
    0x00000000, 0x00164D55,
};
#endif

#if defined(VERSION_EU_X)
float k_SmpFadeEncodedWordsBlock2[2] = {
    0.10810811f, 0.5f,
};
#endif

#if defined(VERSION_EU)
unsigned int k_SmpFadeEncodedWordsBlock3[2] = {
    0x0800FFE0, 0x01270134,
};
#endif

#if defined(VERSION_DE)
#if defined(VERSION_DE)
void *k_SmpFadeEncodedWordsBlock1[2] = {
    (char *)&g_actionEnterDispatchTable + 0x70,
    (char *)&g_damageDispatchTable + 0x90,
};
#endif
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_fadeWidgetProgressConstantsUsRev1_SmpFade.c */
const float g_fadeWidgetProgressConstantsUsRev1[2] = {
    0.33333334f, 0.05f,
};
#endif
