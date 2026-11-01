#include "include_asm.h"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "MENU/STATE.H"
#include "TYPES.H"
#include "UI/QUAG/N64_ENG.H"

/* MENU_DRAWCLIPPEDWIDGETSIBLINGS.CPP */
#if defined(VERSION_EU)
/* 80408CB0_13.CPP */
int Menu_ReturnZeroEuropean(void) {
    return 0;
}
#endif
#if defined(VERSION_DE)
int Menu_ReturnZeroGerman(void) {
    return 0;
}
#endif
#if defined(VERSION_DE) || defined(VERSION_EU)
/* Processes a widget with clipping and drawing operations. */
extern s32 Widget_ComputeWidgetBounds(struct CacheResourceBlockView *draw, struct CacheResourceBlockView *hit, struct WidgetLayout *widget, struct t_dldc *ctx);
extern void N64Eng_GetClipBounds(s32 *, s32 *, s32 *, s32 *);
extern s32 Node_ClampRectToClip(struct CacheResourceBlockView *rect, struct CacheResourceBlockView *clip);
extern void Widget_DrawVisibleSiblings(void *, Args);
void Menu_DrawClippedWidgetSiblings(void *widget, Args args) {
    NumericWidgetChildView *record = widget;
    struct CacheResourceBlockView first;
    struct CacheResourceBlockView basis;
    struct CacheResourceBlockView value;
    struct CacheResourceBlockView transformed;
    s32 changed;

    changed = 0;
    if (Widget_ComputeWidgetBounds(&first, &basis, widget, &args) != 0) {
        if ((record->flags & 0x200) != 0) {
            N64Eng_GetClipBounds(&value.first, &value.third, &value.second, &value.fourth);
            transformed = value;
            Node_ClampRectToClip(&transformed, &basis);
            N64Eng_SetClipBounds(transformed.first, transformed.third, transformed.second, transformed.fourth);
            changed = 1;
        }
        Widget_DrawVisibleSiblings(record->firstChild, args);
        if (changed != 0) {
            N64Eng_SetClipBounds(value.first, value.third, value.second, value.fourth);
        }
    }
}
#endif
