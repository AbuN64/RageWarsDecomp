#ifndef MATH_SMOS_INVOKEWIDGETCALLBACK_H
#define MATH_SMOS_INVOKEWIDGETCALLBACK_H
#include "TYPES.H"

struct Shared_WidgetIdE;
struct t_dldc;

extern s32 Smos_InvokeWidgetCallback(struct Shared_WidgetIdE *widget, struct t_dldc event);
#endif
