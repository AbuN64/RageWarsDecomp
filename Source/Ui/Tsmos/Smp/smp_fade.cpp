#include "Common/animation.h"
#include "Common/triple.h"
#include "include_asm.h"
#include "Common/frustum.h"
#include "Common/menu_screen_elements.h"
#include "types.h"
#include "Math/smsmngr_initializescreenmanager.h"
#include "Menu/smpfade_registerfadeclass.h"
#include "Resmgr/resmgr_string_memory.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Ui/Tsmos/Smp/smp_fade.h"
#include "Common/selectionscreenstate.h"
#include "Common/screen.h"
#include "Ui/smp_slider.h"
#include "Frontend/node_insertwidgetbefore.h"

s32 Smp_UpdateFadeProgress(MenuFadeWidget *object) {
    MenuFadeWidget *owner = object;
    f32 value, target, result;
    MenuFadeWidget *frame;
    if (object->running == 1) {
        switch (object->phase) {
        case 1:
            frame = object->frame;
            target = g_fadeProgressTarget;
            value = frame->progressX;
            if (value != target) {
                if (value < target) {
                    result = value + object->scaleX;
                    if (result < 0.0f) result = 0.0f;
                    else if (target < result) result = target;
                    frame->progressX = result;
                } else frame->progressX = value - g_fadeProgressRetreatStep;
            } else {
                value = frame->progressY;
                if (value != target) {
                    if (value < target) {
                        frame->progressY = value + object->scaleY;
                        object = object->frame;
                        if (target < object->progressY) object->progressY = g_fadeProgressMinimum;
                    } else {
                        frame->progressY = target;
                        object->phase = 3;
                    }
                }
            }
            break;
        case 2:
            frame = object->frame;
            target = g_fadeProgressAlternateTarget;
            value = frame->progressY;
            if (target < value - target) {
                if (target < value) {
                    result = value - object->scaleY;
                    if (result < target) result = target;
                    else if (g_fadeProgressHorizontalMaximum < result) result = g_fadeProgressHorizontalMaximum;
                    frame->progressY = result;
                } else frame->progressY = value + g_fadeProgressAdvanceStep;
            } else {
                value = frame->progressX;
                if (value != 0.0f) {
                    if (0.0f < value) {
                        result = value - object->scaleX;
                        if (result < 0.0f) result = 0.0f;
                        else if (g_fadeProgressMaximum < result) result = g_fadeProgressMaximum;
                        frame->progressX = result;
                    } else frame->progressX = value + g_fadeProgressHorizontalAdvanceStep;
                } else owner->phase = 4;
            }
            break;
        case 3: break;
        }
    }
    return 0;
}

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
const float g_fadeProgressConstants[8] = {
    1.0f, 0.01f, 1.2f, 0.05f, 1.0f, 0.01f,
    1.0f, 0.01f,
};
#endif

/* Creates a fading widget between a frame and an item: finds the frame named by the low half of frameId and the item named
   by itemId in the current screen, allocates and zeroes the widget, links the frame and the item, resets the frame's
   progress to g_fadeWidgetInitialProgress, sets both scales to g_fadeWidgetInitialScale, copies the item's four colours and
   computes the green and red step per tick of the fade over 75 steps. Marks the widget active, starts it through
   SmpSlider_EnableTransition and SmpSlider_SetTransitionMode(1) and attaches it to the frame through Node_InsertWidgetBefore.
   Returns the widget. */

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
    result->redStep = (((u32)result->item->colours[0] >> 24) - ((u32)result->item->colours[1] >> 24)) / 75U;
    result->active = 1;
    SmpSlider_EnableTransition(result);
    SmpSlider_SetTransitionMode(result, 1);
    Node_InsertWidgetBefore(frame, result);
    return result;
}

void SmpFade_RegisterFadeClass(void) {
    SmSmngr_RegisterElementHandlers(2912, g_SmpSlider_DispatchTransitionEventAddress, g_SmpSlider_IgnoreFormattedMessageAddress, 3);
}

#if !(defined(VERSION_US_REV1))
const float g_fadeWidgetSecondaryProgressConstants[2] = {
    0.33333334f, 0.05f,
};
#endif

#if defined(VERSION_US)
unsigned int k_SmpFadeData[2] = {
    0x00000000, 0x00164D55,
};
#endif

#if defined(VERSION_EU_X)
float g_smpFadeScaleConstants[2] = {
    0.10810811f, 0.5f,
};
#endif

#if defined(VERSION_EU)
unsigned int g_smpFadeUnreferencedWordsEu[2] = {
    0x0800FFE0, 0x01270134,
};
#endif

#if defined(VERSION_DE)
void *g_smpFadeDispatchEntryPointers[2] = {
    &g_actionEnterDispatchTable[0x70],
    &g_damageDispatchTable[0x90],
};
#endif

#if defined(VERSION_US_REV1)
const float g_fadeWidgetProgressConstants[2] = {
    0.33333334f, 0.05f,
};
#endif

#if defined(VERSION_US_REV1)
float g_fadeWidgetPulseConstants[2] = {
    0.10810811f, 0.5f,
};
#endif
