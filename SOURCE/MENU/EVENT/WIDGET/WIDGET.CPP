#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/OWNERRECAT8V1.H"
#include "UI/QUAG/N64_ENG.H"

#if defined(VERSION_US)
extern s32 Widget_ComputeWidgetBounds(struct CacheResourceBlockView *draw, struct CacheResourceBlockView *hit, struct WidgetLayout *widget, struct t_dldc *ctx);

extern void N64Eng_GetClipBounds(u32 *, u32 *, u32 *, u32 *);

extern s32 Node_ClampRectToClip(struct CacheResourceBlockView *rect, struct CacheResourceBlockView *clip);


extern void Widget_DrawVisibleSiblings(void *, Args);

s32 Event_IgnoreWidgetValueUs(s32 unusedValue) {
    unusedValue << 0;
    return 0;
}

void Event_DrawClippedWidgetChildren(void *widget, Args args) {
    NumericWidgetChildView *record = widget;
    QuadN64EngDrawNumericWidgetChildren first;
    QuadN64EngDrawNumericWidgetChildren basis;
    QuadN64EngDrawNumericWidgetChildren value;
    QuadN64EngDrawNumericWidgetChildren transformed;
    s32 changed;

    changed = 0;
    if (Widget_ComputeWidgetBounds(&first, &basis, widget, &args) != 0) {
        if ((record->flags & 0x200) != 0) {
            N64Eng_GetClipBounds(&value.x, &value.z, &value.y, &value.w);
            transformed = value;
            Node_ClampRectToClip(&transformed, &basis);
            N64Eng_SetClipBounds(transformed.x, transformed.z,
                          transformed.y, transformed.w);
            changed = 1;
        }
        Widget_DrawVisibleSiblings(record->firstChild, args);
        if (changed != 0) {
            N64Eng_SetClipBounds(value.x, value.z, value.y, value.w);
        }
    }
}
#endif

