#include "COMMON/ANIMATION.H"
#include "COMMON/TRIPLE.H"
#include "include_asm.h"

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
