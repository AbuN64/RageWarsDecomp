#include "COMMON/SCREEN.H"
#include "include_asm.h"

#if defined(VERSION_US)
#include "COMMON/WIDGETRECAT1A.H"
#include "FRONTEND/FRONTEND_UPDATESLIDERGEOMETRY.H"
#include "MENU.H"

/* Clamp the slider and handle range, value, step and parent notifications. */
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

