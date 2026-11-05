#include "include_asm.h"
#include "types.h"
#include "Menu/widget_records.h"
#include "Common/resident_event_handler.h"
#include "Common/menu_overlay.h"
#include "Ui/Quag/N64_Eng.h"
#include "Frontend/frontend_openresourcearchive.h"
#include "Frontend/widget_drawtextwidget.h"
#include "Frontend/widget_findwidgetatpoint.h"
#include "menu.h"

#if defined(VERSION_US)

s32 Event_IgnoreWidgetValueUs(s32 unusedValue) {
    unusedValue << 0;
    return 0;
}

void Event_DrawClippedWidgetChildren(void *widget, sm_dldc args) {
    NumericWidgetChildView *record = widget;
    struct WidgetRect first;
    struct WidgetRect basis;
    struct WidgetRect value;
    struct WidgetRect transformed;
    s32 changed;

    changed = 0;
    if (Widget_ComputeWidgetBounds(&first, &basis, widget, &args) != 0) {
        if ((record->flags & 0x200) != 0) {
            N64Eng_GetClipBounds(&value.left, &value.top, &value.right, &value.bottom);
            transformed = value;
            Node_ClampRectToClip(&transformed, &basis);
            N64Eng_SetClipBounds(transformed.left, transformed.top,
                          transformed.right, transformed.bottom);
            changed = 1;
        }
        Widget_DrawVisibleSiblings(record->firstChild, args);
        if (changed != 0) {
            N64Eng_SetClipBounds(value.left, value.top, value.right, value.bottom);
        }
    }
}
#endif
