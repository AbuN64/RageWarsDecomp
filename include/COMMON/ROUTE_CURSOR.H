#ifndef COMMON_ROUTE_CURSOR_H
#define COMMON_ROUTE_CURSOR_H
#include "TYPES.H"
struct RouteCursorState {
    s8 state;
    s8 clip;
    s16 frame;
    s16 previous;
};
#endif
