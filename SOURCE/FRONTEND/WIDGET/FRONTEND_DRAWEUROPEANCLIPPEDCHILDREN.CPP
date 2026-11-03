#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/WIDGETRECAT1A.H"
#include "UI/QUAG/N64_ENG.H"
#include "FRONTEND/FRONTEND_OPENRESOURCEARCHIVE.H"
extern s32 Widget_ComputeWidgetBounds(struct CacheResourceBlockView *draw, struct CacheResourceBlockView *hit, struct WidgetLayout *widget, struct t_dldc *ctx);


extern void Widget_DrawVisibleSiblings(MenuWidget *, sm_dldc);

#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
s32 Frontend_ReturnZeroCallback(void) {
    return 0;
}

#if defined(VERSION_EU_X)
void Frontend_DrawEuropeanClippedChildren(MenuWidget *widget, sm_dldc args) {
    Shared_Quad area;
    Shared_Quad basis;
    Shared_Quad saved;
    Shared_Quad clip;
    s32 changed;

    changed = 0;
    if (Widget_ComputeWidgetBounds(&area, &basis, widget, &args) != 0) {
        if (widget->flags & 0x200) {
            N64Eng_GetClipBounds(&saved.w[0], &saved.w[2], &saved.w[1], &saved.w[3]);
            clip = saved;
            Node_ClampRectToClip(&clip, &basis);
            N64Eng_SetClipBounds(clip.w[0], clip.w[2], clip.w[1], clip.w[3]);
            changed = 1;
        }
        Widget_DrawVisibleSiblings(widget->child, args);
        if (changed != 0) {
            N64Eng_SetClipBounds(saved.w[0], saved.w[2], saved.w[1], saved.w[3]);
        }
    }
}
#endif
#if defined(VERSION_US_REV1)
void Frontend_DrawChildListWithClip(MenuWidget *widget, sm_dldc args) {
    Shared_Quad area;
    Shared_Quad basis;
    Shared_Quad saved;
    Shared_Quad clip;
    s32 changed;

    changed = 0;
    if (Widget_ComputeWidgetBounds(&area, &basis, widget, &args) != 0) {
        if (widget->flags & 0x200) {
            N64Eng_GetClipBounds(&saved.w[0], &saved.w[2], &saved.w[1], &saved.w[3]);
            clip = saved;
            Node_ClampRectToClip(&clip, &basis);
            N64Eng_SetClipBounds(clip.w[0], clip.w[2], clip.w[1], clip.w[3]);
            changed = 1;
        }
        Widget_DrawVisibleSiblings(widget->child, args);
        if (changed != 0) {
            N64Eng_SetClipBounds(saved.w[0], saved.w[2], saved.w[1], saved.w[3]);
        }
    }
}
#endif
#endif

