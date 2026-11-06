#include "Common/screen.h"
#include "include_asm.h"
#if ((defined(VERSION_US)))
#include "Common/widget_tree.h"
#endif
#if ((defined(VERSION_US)))
#include "Frontend/frontend_updateslidergeometry.h"
#endif
#if ((defined(VERSION_US)))
#include "menu.h"
#endif

#if defined(VERSION_US)

/* Slider messages: the first group are input directions, the 0x1000 range reads and writes the slider. */
#define SLIDER_MSG_INCREASE_A 5
#define SLIDER_MSG_DECREASE_A 6
#define SLIDER_MSG_DECREASE_B 7
#define SLIDER_MSG_INCREASE_B 8
#define SLIDER_MSG_GET_VALUE 4096
#define SLIDER_MSG_GET_MIN 4098
#define SLIDER_MSG_GET_MAX 4099
#define SLIDER_MSG_SET_RANGE 4100
#define SLIDER_MSG_SET_VALUE 4101
#define SLIDER_MSG_GET_STEP 4102
#define SLIDER_MSG_SET_STEP 4103
#define SLIDER_MSG_GET_FLAGS 4104
#define SLIDER_MSG_SET_FLAGS 4105
#define SLIDER_MSG_VALUE_CHANGED 4106

/* Tells the slider geometry and the parent screen that the slider changed. */
static inline void Slider_NotifyChanged_slider(Slider *slider) {
    Frontend_UpdateSliderGeometry(slider);
    Menu_RouteElementEvent(GetMenuScreenOwner(), SLIDER_MSG_VALUE_CHANGED, slider->parentId, slider->value, 0);
    MarkMenuEventHandled();
}

/* Clamps the slider value into its range, then answers a read message with the requested field,
   or applies an input or write message and notifies the parent. Returns zero for everything else. */
s32 Event_HandleSliderMessage(Slider *slider, s32 msg, s32 value, s32 inputState) {
    s32 result;
    Slider *widget = slider;

    if (widget->value < widget->min) {
        widget->value = widget->min;
    }
    if (widget->value > widget->max) {
        widget->value = widget->max;
    }

    switch (msg) {
        case 5:
        case 8:
            if (inputState != 0) {
                s32 v = widget->value + widget->step;
                s32 hi = widget->max;
                widget->value = v;
                if (hi < v) {
                    widget->value = hi;
                }
            }
            goto post;

        case 6:
        case 7:
            if (inputState != 0) {
                s32 v = widget->value - widget->step;
                s32 lo = widget->min;
                widget->value = v;
                if (v < lo) {
                    widget->value = lo;
                }
            }
            goto post;

        case 4096:
            result = widget->value;
            goto end;

        case 4098:
            result = widget->min;
            goto end;

        case 4099:
            result = widget->max;
            goto end;

        case 4102:
            result = widget->step;
            goto end;

        case 4104:
            result = widget->flags;
            goto end;

        case 4101:
            if (value < widget->min) {
                goto post;
            }
            if (widget->max < value) {
                goto post;
            }
            widget->value = value;
            goto post;

        case 4100:
            if (widget->min < value) {
                widget->max = value;
            }
            if (inputState < widget->max) {
                widget->min = inputState;
            }
            goto post;

        case 4103:
            if (value < (widget->max - widget->min)) {
                widget->step = value;
            }
            goto post;

        case 4105:
            widget->flags = value;
            goto post;

        default:
            result = 0;
            goto end;
    }

post:
    Frontend_UpdateSliderGeometry(widget);
    Menu_RouteElementEvent(GetMenuScreenOwner(), 4106, slider->parentId, widget->value, 0);
    MarkMenuEventHandled();
    result = 0;

end:
    return result;
}
#endif
