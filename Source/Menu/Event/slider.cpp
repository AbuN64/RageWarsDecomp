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
    if (slider->value < slider->min) {
        slider->value = slider->min;
    }
    if (slider->value > slider->max) {
        slider->value = slider->max;
    }

    switch (msg) {
        case SLIDER_MSG_INCREASE_A:
        case SLIDER_MSG_INCREASE_B:
            if (inputState != 0) {
                s32 next = slider->value + slider->step;
                slider->value = next;
                if (slider->max < next) {
                    slider->value = slider->max;
                }
            }
            break;

        case SLIDER_MSG_DECREASE_A:
        case SLIDER_MSG_DECREASE_B:
            if (inputState != 0) {
                s32 next = slider->value - slider->step;
                slider->value = next;
                if (next < slider->min) {
                    slider->value = slider->min;
                }
            }
            break;

        case SLIDER_MSG_GET_VALUE:
            return slider->value;
        case SLIDER_MSG_GET_MIN:
            return slider->min;
        case SLIDER_MSG_GET_MAX:
            return slider->max;
        case SLIDER_MSG_GET_STEP:
            return slider->step;
        case SLIDER_MSG_GET_FLAGS:
            return slider->flags;

        case SLIDER_MSG_SET_VALUE:
            if (value >= slider->min && value <= slider->max) {
                slider->value = value;
            }
            break;

        case SLIDER_MSG_SET_RANGE:
            if (slider->min < value) {
                slider->max = value;
            }
            if (inputState < slider->max) {
                slider->min = inputState;
            }
            break;

        case SLIDER_MSG_SET_STEP:
            if (value < (slider->max - slider->min)) {
                slider->step = value;
            }
            break;

        case SLIDER_MSG_SET_FLAGS:
            slider->flags = value;
            break;

        default:
            return 0;
    }

    Slider_NotifyChanged_slider(slider);
    return 0;
}
#endif
