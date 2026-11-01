#ifndef MATH_INPUT_EVENT_H
#define MATH_INPUT_EVENT_H
#include "TYPES.H"
/* Shared button/axis event produced by 8029AAD8 and 8029AB24. */
typedef struct input_event {
    s16 source;
    s16 device;
    s16 kind;
    s16 control;
    s32 reserved08;
    s16 pressed;
    s16 x;
    s16 y;
    s16 z;
} input_event;
#endif
