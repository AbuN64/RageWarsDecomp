#include "COMMON/CALLBACK.H"
#include "MATH/SMOS_INVOKEWIDGETCALLBACK.H"
#include "MATH/SHARED_WIDGETIDE.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/OBJRECAT3CV2.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"

s32 Smos_InvokeWidgetCallback(struct Shared_WidgetIdE *widget, sm_dldc event) {
    WidgetCallback cb = Menu_FindKindDrawHandler(widget->id);

    if (cb != 0) {
        cb(widget, event);
        return 1;
    }
    return 0;
}

void Smos_SetAxisThreshold(int threshold) {
    g_screenManager->limit = threshold;
}

/** Return the word at offset 0x14 of the current global object. */
unsigned int Smos_GetControlRepeatLimit(void) {
    return g_screenManager->limit;
}
