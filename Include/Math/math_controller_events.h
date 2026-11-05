#ifndef MATH_MATH_CONTROLLER_EVENTS_H
#define MATH_MATH_CONTROLLER_EVENTS_H
#include "Common/callback.h"
#include "Math/input_event.h"

struct input_event;
extern void DispatchControllerAxisEvents(struct input_event *event);
extern void Controller_DispatchControllerEvent(struct input_event *event);
extern void DispatchControllerButtonEvent(struct input_event *event);
extern void Controller_SendControllerButtonEvent(s16 port, s16 control, s32 pressed);
extern void Controller_SendControllerStickEvent(s16 port, s32 stick_x, s32 stick_y);

extern void Controller_SetControllerEventFilter(s32 (*filter)(void));

extern void Controller_AllocateControllerContext(void);
extern void Controller_FreeControllerContext(void);
#endif
