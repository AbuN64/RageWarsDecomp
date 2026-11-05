#include "Common/callback.h"
#include "Math/smos_invokewidgetcallback.h"
#include "Math/shared_widgetide.h"
#include "Common/menu_screen_elements.h"
#include "Common/rotation_extraction.h"
#include "types.h"
#include "Common/sharedplayer.h"

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

/** Return how many control repeats the screen manager allows. */
unsigned int Smos_GetControlRepeatLimit(void) {
    return g_screenManager->limit;
}
