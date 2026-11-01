#ifndef MATH_MATH_CONTROLLER_EVENTS_H
#define MATH_MATH_CONTROLLER_EVENTS_H
#include "COMMON/CALLBACK.H"
#include "MATH/INPUT_EVENT.H"

extern void DispatchControllerAxisEvents(input_event *event);
extern void Controller_DispatchControllerEvent(input_event *event);
extern void DispatchControllerButtonEvent(input_event *event);
extern void Controller_SendControllerButtonEvent(s16 port, s16 control, s32 pressed);
extern void Controller_SendControllerStickEvent(s16 port, s32 stick_x, s32 stick_y);

extern void Controller_SetControllerEventFilter(s32 (*filter)(void));

extern void Controller_AllocateControllerContext(void);
extern void Controller_FreeControllerContext(void);
#endif
