#include "COMMON/SCREEN.H"
#include "COMMON/WIDGETRECAT1A.H"
#include "FRONTEND/FRONTEND_UPDATESLIDERGEOMETRY.H"
#include "MENU.H"
#include "FRONTEND/FRONTEND_RETURNWITHOUTACTION.H"
#include "include_asm.h"
#include "TYPES.H"

/* SLIDER.CPP */
/* 8040B45C_27.CPP */
/* 8040B45C_27.CPP */
#if defined(VERSION_EU_X) || defined(VERSION_US_REV1) || defined(VERSION_DE) || defined(VERSION_EU)
/* Slider widget message handler: clamps the current value into range, then dispatches on the
   message to get/set the value, range, step or user word, adjusts by one step, or posts the new
   value to the parent. */
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"

s32 Frontend_HandleSliderMessage(Slider *slider, s32 msg, s32 valueOrUpperBound, s32 notifyOrLowerBound) {
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
            if (notifyOrLowerBound != 0) {
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
            if (notifyOrLowerBound != 0) {
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
            if (valueOrUpperBound < widget->min) {
                goto post;
            }
            if (widget->max < valueOrUpperBound) {
                goto post;
            }
            widget->value = valueOrUpperBound;
            goto post;

        case 4100:
            if (widget->min < valueOrUpperBound) {
                widget->max = valueOrUpperBound;
            }
            if (notifyOrLowerBound < widget->max) {
                widget->min = notifyOrLowerBound;
            }
            goto post;

        case 4103:
            if (valueOrUpperBound < (widget->max - widget->min)) {
                widget->step = valueOrUpperBound;
            }
            goto post;

        case 4105:
            widget->flags = valueOrUpperBound;
            goto post;

        default:
            result = 0;
            goto end;
    }

post:
    Frontend_UpdateSliderGeometry((Slider *)widget);
    Menu_RouteElementEvent(GetMenuScreenOwner(), 4106, slider->parentId, widget->value, 0);
    MarkMenuEventHandled();
    result = 0;

end:
    return result;
}
#endif

/* 8040B45C_28.CPP */
#if !(defined(VERSION_US))
/** Perform no work. */
void Frontend_ReturnWithoutAction(void) {
}
#endif

/* 8040B45C_29.CPP */
/* Lays out a slider from its value: scales value - min over max - min onto the track span, then
   for a vertical slider (flag 1) sets the fill's y and height and centres the thumb vertically on
   that edge, and for a horizontal slider sets the fill's width and moves the thumb from the fill's
   x by that edge less half its width. */

void Frontend_UpdateSliderGeometry(Slider *slider) {
    s32 pos;

    if (slider->flags & 1) {
        pos = (slider->bottom - slider->top) * (slider->value - slider->min) / (slider->max - slider->min);
        slider->fill->y = pos;
        slider->fill->height = slider->bottom - pos;
        if (slider->thumb != 0) {
            slider->thumb->y = pos - slider->thumb->height / 2;
        }
    } else {
        pos = (slider->right - slider->left) * (slider->value - slider->min) / (slider->max - slider->min);
        slider->fill->width = pos;
        if (slider->thumb != 0) {
            slider->thumb->x = slider->fill->x - (pos - slider->thumb->width / 2);
        }
    }
}
