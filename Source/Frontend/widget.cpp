#include "include_asm.h"
#include "Common/frontend_video_mode.h"
#include "Common/audio_callbacks.h"
#include "Common/effectrender.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"
#include "Common/rectangle_draw.h"
#include "Gfx/rect.h"
#include "Frontend/text_render.h"
#include "Common/widget_tree.h"
#include "Common/archive_chunk_images.h"
#include "Common/widget_texture_retention.h"
#include "Common/texture.h"
#include "types.h"
#include "Frontend/widget_drawtextwidget.h"
#include "Frontend/frontend_openresourcearchive.h"
#include "Menu/Gfx/combine_configureprimitiverenderflags.h"
#include "Ui/Quag/N64_Eng.h"
#include "Math/smos_invokewidgetcallback.h"
#include "Frontend/node_getimagetexture.h"
#include "Menu/Gfx/gfx_drawclippedgradientquad.h"
#include "Node/node_getbanktiletexture.h"
#include "Ui/X_files/x_plus.h"
#include "Common/Lone/frontend_viewport_width.h"
#include "Common/menu_screen_elements.h"
#include "Frontend/widget_findwidgetatpoint.h"
#include "Widget/widget_drawtextwidget.h"
#include "Frontend/frontend_address_symbols.h"
#include "Widget/widget_findwidgetatpoint.h"

void Widget_DrawVisibleSiblings(Widget *node, sm_dldc event);

/* unit WIDGET_DRAWTEXTWIDGET.CPP */
/* Flushes the queued text sprite batches: when any are queued it selects render mode 0x53333 if
   not already active, saves the clip rectangle and applies the queue's own, then walks the texture
   pages from the lowest first page to the highest last page among the batches, loading each page
   once through Node_GetBankTileTexture and Combine_BindImageTexture (stopping the page when it cannot load) and drawing
   every batch's run of sprites on that page at depth 10 through Rect_DrawRect; finally it restores
   the clip rectangle and empties the queue. */
static inline void Widget_RestoreClipBounds(struct WidgetRect *clip) {
    N64Eng_SetClipBounds(clip->left, clip->top, clip->right, clip->bottom);
}

static inline s32 Widget_OverlapsTextBatchForClear(struct WidgetRect *area) {
    BatchRec *batch;
    s32 i;

    for (i = 0; i < g_textBatchCount; i++) {
        batch = &g_textBatches[i];
        if (area->right < batch->area.left || batch->area.right < area->left || area->bottom < batch->area.top ||
            batch->area.bottom < area->top) {
            continue;
        }
        return 1;
    }
    return 0;
}

static inline s32 Widget_OverlapsTextBatchForDraw(struct WidgetRect *area) {
    BatchRec *batch;
    s32 i;

    for (i = 0; i < g_textBatchCount; i++) {
        batch = &g_textBatches[i];
        if (area->right < batch->area.left || batch->area.right < area->left || area->bottom < batch->area.top ||
            batch->area.bottom < area->top) {
            continue;
        }
        return 1;
    }
    return 0;
}

GlyphBuffer *Node_GetGlyphBuffer(s32);

static inline void textBegin(u8 font, u8 style) {
    N64Eng_GetClipBounds(&g_frontendClipBounds.left, &g_frontendClipBounds.top,
                   &g_frontendClipBounds.right, &g_frontendClipBounds.bottom);
    g_textBatchFontId = (s8)font;
    g_textBatchStyle = (s8)style;
    g_textGlyphBuffer = Node_GetGlyphBuffer((s8)font);
    g_textGlyphSpacing = Node_GetFontLetterSpacing((s8)font);
    g_textLineHeight = Node_GetFontLineHeight((s8)font);
    g_textVerticalOffset = Node_GetFontVerticalOffset((s8)font);
}

static inline s32 textOverlaps(BatchRec *next) {
    s32 i;
    BatchRec *batch;
    for (i = 0; i < g_textBatchCount; i++) {
        batch = &g_textBatches[i];
        if (next->area.right < batch->area.left || batch->area.right < next->area.left ||
            batch->area.top > next->area.bottom || batch->area.bottom < next->area.top) continue;
        return 1;
    }
    return 0;
}

static inline s32 textClipChanged(struct WidgetRect *current) {
    if (current->left != g_frontendClipBounds.left) return 1;
    if (current->top != g_textClipTop) return 1;
    if (current->right != g_textClipRight) return 1;
    return current->bottom != g_textClipBottom;
}

void Widget_FlushTextBatches(void) {
    u16 first;
    u16 last;
    u16 page;
    s32 i;
    s32 current;
    s32 loaded;
    s32 texture;
    struct WidgetRect clip;
    BatchRec *batch;
    TextSprite *sprite;

    if (g_textBatchCount == 0) {
        return;
    }
    first = 96;
    last = 0;
    if (g_widgetTextBatchMode != 0x53333 || g_frontendRenderStateInitialized == 0) {
        g_widgetTextBatchMode = 0x53333;
        Combine_ConfigurePrimitiveRenderFlags(0x53333);
        g_frontendRenderStateInitialized = 1;
    }
    N64Eng_GetClipBounds(&clip.left, &clip.top, &clip.right, &clip.bottom);
    N64Eng_SetClipBounds(g_frontendClipBounds.left, g_textClipTop, g_textClipRight, g_textClipBottom);
    for (current = 0; current < g_textBatchCount; current++) {
        sprite = g_textBatches[current].cursor;
        page = sprite->glyph;
        if (first < page) {
            page = first;
        }
        first = page;
        page = sprite[g_textBatches[current].count - 1].glyph;
        if (page < last) {
            page = last;
        }
        last = page;
    }
    for (current = first; current <= last; current++) {
        loaded = 0;
        for (i = 0; i < g_textBatchCount; i++) {
            batch = &g_textBatches[i];
            while (current == batch->cursor->glyph && batch->count > 0) {
                sprite = batch->cursor;
                if (!loaded) {
                    texture = Node_GetBankTileTexture(current & 0xFF, g_textBatchFontId, g_textBatchStyle);
                    if (texture == 0) {
                        i = g_textBatchCount;
                        break;
                    }
                    Combine_BindImageTexture(texture);
                    loaded = 1;
                }
                Rect_DrawRect(sprite->x, sprite->y, 10.0f, sprite->width, sprite->height, sprite->color);
                batch->cursor++;
                batch->count--;
            }
        }
    }
    Widget_RestoreClipBounds(&clip);
    g_textBatchCount = 0;
}

void Widget_DrawImageWidget(WidgetFrontendDrawImageWidget *widget, sm_dldc args) {
    struct WidgetRect box;
    struct WidgetRect area;
    struct WidgetRect saved;
    struct WidgetRect clip;
    s32 clipped;
    s32 texture;
    s32 color;

    clipped = 0;
    if (Widget_ComputeWidgetBounds(&area, &box, widget, &args) == 0) {
        return;
    }
    if (widget->flags & 0x200) {
        N64Eng_GetClipBounds(&saved.left, &saved.top, &saved.right, &saved.bottom);
        clip = saved;
        if (Node_ClampRectToClip(&clip, &box) == 0) {
            return;
        }
        clipped = 1;
        N64Eng_SetClipBounds(clip.left, clip.top, clip.right, clip.bottom);
    }
    if (Widget_OverlapsTextBatchForClear(&area)) {
        Widget_FlushTextBatches();
    }
    texture = Node_GetImageTexture(widget->image, 1);
    color = (args.alpha << 24) | 0xFFFFFF;
    if (g_widgetTextBatchMode != 0x53333 || g_frontendRenderStateInitialized == 0) {
        g_widgetTextBatchMode = 0x53333;
        Combine_ConfigurePrimitiveRenderFlags(0x53333);
        g_frontendRenderStateInitialized = 1;
    }
    Combine_BindImageTexture(texture);
    Rect_DrawRect(area.left, area.top, 0.0f, area.right - area.left + 1, area.bottom - area.top + 1, color);
    if (clipped) {
        N64Eng_SetClipBounds(saved.left, saved.top, saved.right, saved.bottom);
    }
}

void Widget_DrawGradientWidget(WidgetLayout *widget, sm_dldc args) {
    struct WidgetRect box;
    struct WidgetRect area;
    struct WidgetRect saved;
    struct WidgetRect clip;
    s32 clipped;

    clipped = 0;
    if (Widget_ComputeWidgetBounds(&area, &box, widget, &args) == 0) {
        return;
    }
    if (((u8)(widget->colors[0] >> 24) | (u8)(widget->colors[1] >> 24) | (u8)(widget->colors[2] >> 24) |
         (u8)(widget->colors[3] >> 24)) == 0) {
        return;
    }
    if (widget->flags & 0x200) {
        N64Eng_GetClipBounds(&saved.left, &saved.top, &saved.right, &saved.bottom);
        clip = saved;
        if (Node_ClampRectToClip(&clip, &box) == 0) {
            return;
        }
        clipped = 1;
        N64Eng_SetClipBounds(clip.left, clip.top, clip.right, clip.bottom);
    }
    if (Widget_OverlapsTextBatchForDraw(&area)) {
        Widget_FlushTextBatches();
    }
    if (g_widgetTextBatchMode != 0x53533 || g_frontendRenderStateInitialized == 0) {
        g_widgetTextBatchMode = 0x53533;
        Combine_ConfigurePrimitiveRenderFlags(0x53533);
        g_frontendRenderStateInitialized = 1;
    }
    Combine_BindImageTexture(0);
    Rect_DrawGradientRectangle(area.left, area.top, 0.0f, area.right - area.left + 1, area.bottom - area.top + 1,
                  (widget->colors[0] & 0xFFFFFF) | ((args.alpha * (u8)(widget->colors[0] >> 24) / 255) << 24),
                  (widget->colors[1] & 0xFFFFFF) | ((args.alpha * (u8)(widget->colors[1] >> 24) / 255) << 24),
                  (widget->colors[2] & 0xFFFFFF) | ((args.alpha * (u8)(widget->colors[2] >> 24) / 255) << 24),
                  (widget->colors[3] & 0xFFFFFF) | ((args.alpha * (u8)(widget->colors[3] >> 24) / 255) << 24));
    if (clipped) {
        N64Eng_SetClipBounds(saved.left, saved.top, saved.right, saved.bottom);
    }
}

void Widget_DrawTextWidget(TextWidget *widget, sm_dldc args) {
    struct WidgetRect box, saved, clip, area, current;
    s32 clipped, length, width, mismatch, count, i, tempX, tempY;
    u8 font, style;
    u8 *text;
    f32 x, y, sub; u8 *resolved;
    BatchRec *batch;
    TextSprite *sprites, *sprite;
    sm_font_char *glyph;
    u32 color; s16 glyphId;
    resolved = widget->text;
    clipped = 0;
    if (!resolved) {
        if (widget->stringId == -1) return;
        resolved = (u8 *)Node_GetStringByIndex(widget->stringId);
    }
    text=resolved;
    if (!Widget_ComputeWidgetBounds(&area, &box, widget, &args)) return;
    if (widget->flags & 0x200) {
        N64Eng_GetClipBounds(&saved.left, &saved.top, &saved.right, &saved.bottom);
        clip = saved;
        if (!Node_ClampRectToClip(&clip, &box)) return;
        clipped = 1;
        N64Eng_SetClipBounds(clip.left, clip.top, clip.right, clip.bottom);
    }
    length = XPlus_StringLength(text);
    if (args.flags & 0x100) { font=widget->fontSelected; style=widget->styleSelected; }
    else if (args.flags & 0x40) { font=widget->fontAlt; style=widget->styleAlt; }
    else { font=widget->font; style=widget->style; }
    if ((s8)font == -1) font=widget->font;
    if ((s8)style == -1) style=widget->style;
    if (g_textBatchCount) {
        N64Eng_GetClipBounds(&current.left, &current.top, &current.right, &current.bottom);
        mismatch = textClipChanged(&current);
        if (mismatch || g_textBatchFontId != (s8)font || g_textBatchStyle != (s8)style) {
            if (g_textBatchCount) Widget_FlushTextBatches();
            textBegin(font, style);
        }
    } else textBegin(font, style);
    width = Node_MeasureTextPrefix((s8)font, text, length) * args.XScale;
    x = 0.0f;
    switch (widget->align & 3) {
        case 0: x=area.left; break;
        case 1: x=(area.left+area.right)/2-width/2; break;
        case 2: {s32 edge=area.right; ++edge; x=edge-width;} break;
    }
    y = 0.0f;
    switch (widget->align & 12) {
        case 0: y=area.top; y-=g_textVerticalOffset*args.YScale; break;
        case 4:
            y=(area.top+area.bottom)/2; y-=g_textVerticalOffset*args.YScale; y-=(g_textLineHeight/2)*args.YScale; break;
        case 8:
            sub=(g_textLineHeight+g_textVerticalOffset)*args.YScale;
            y=area.bottom; y-=sub; break;
    }
    batch=&g_textBatches[g_textBatchCount];
    tempX=x; batch->area.left=tempX; batch->area.right=tempX+width;
    tempY=(s32)y+(s32)(g_textVerticalOffset*args.YScale);
    batch->area.top=tempY; batch->area.bottom=tempY+(s32)(g_textLineHeight*args.YScale);
    if (batch->area.left >= batch->area.right) batch->area.right=batch->area.left+1;
    if (batch->area.bottom <= batch->area.top) batch->area.bottom=batch->area.top+1;
    if (textOverlaps(batch)) { Widget_FlushTextBatches(); textBegin(font, style); }
    sprite=ESmem_AllocateFrameHeapHigh(length*sizeof(TextSprite));
    sprites=sprite;
    g_textBatches[g_textBatchCount].cursor=sprites;
    color=((u32)args.alpha<<24)|0xFFFFFF;
    count=0;

    for (i=0; i<length; i++) {
        glyphId=*text-32;
        sprite->glyph=glyphId;
        glyph=&g_textGlyphBuffer->glyphs[glyphId];
        sprite->color=color;
        sprite->x=x;
        sprite->y=y+glyph->BaselineOffset*args.YScale;
        sprite->width=glyph->width*args.XScale;
        sprite->height=glyph->height*args.YScale;
        text++;
        if (sprite->x<g_frontendViewportWidth && sprite->x+sprite->width>0.0f) { sprite++; count++; }
        x+=glyph->width*args.XScale; x+=g_textGlyphSpacing*args.XScale;
    }
    if (clipped) N64Eng_SetClipBounds(saved.left, saved.top, saved.right, saved.bottom);
    if (count>0) {
        g_textBatches[g_textBatchCount].count=count;
        XPlus_SortArray((char *)g_textBatches[g_textBatchCount].cursor, count, sizeof(TextSprite), Node_CompareRecordShortValuesRomEntry);
        g_textBatchCount++;
        if (g_textBatchCount>=16) Widget_FlushTextBatches();
    }
}

#include "Common/sharedplayer.h"
#include "Common/widget_tree.h"
#include "types.h"
#include "Gfx/rect.h"
#include "Widget/widget_findwidgetatpoint.h"
#include "Menu/menu.h"
#include "Frontend/frontend_address_symbols.h"
#include "Frontend/frontend.h"

typedef struct DraftWidget {
    struct DraftWidget *parent;
    struct DraftWidget *next;
    struct DraftWidget *child;
    s16 id;
    u16 type;
    u16 reservedHalfword;
    u16 flags;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    char pad1C[0x10];
    struct DraftWidget *normal;
    struct DraftWidget *selected;
    struct DraftWidget *disabled;
} DraftWidget;

void Widget_DrawWidget(DraftWidget *, sm_dldc);
static inline void drawWidgetChoice(DraftWidget *widget, sm_dldc args) {
        struct WidgetRect area;
        struct WidgetRect box;
        DraftWidget *child;
        if (Widget_ComputeWidgetBounds(&area, &box, widget, &args)) {
            if (args.flags & 0x100) child = widget->disabled;
            else if (args.flags & 0x40) child = widget->selected;
            else child = widget->normal;
            if (child) {
                args.x -= (s32)(child->x * args.XScale);
                args.y -= (s32)(child->y * args.YScale);
                Widget_DrawWidget(child, args);
            }
        }
}

static inline void drawWidgetResetGroup(DraftWidget *widget, sm_dldc args) {
        struct WidgetRect box;
        struct WidgetRect saved;
        struct WidgetRect clip;
        struct WidgetRect area;
        s32 clipped;
        clipped = 0;
        g_frontendRenderStateInitialized = 0;
        if (Widget_ComputeWidgetBounds(&area, &box, widget, &args)) {
            if (widget->flags & 0x200) {
                N64Eng_GetClipBounds(&saved.left, &saved.top, &saved.right, &saved.bottom);
                clip = saved;
                if (!Node_ClampRectToClip(&clip, &box)) return;
                clipped = 1;
                N64Eng_SetClipBounds(clip.left, clip.top, clip.right, clip.bottom);
            }

            Widget_DrawVisibleSiblings((Widget *)widget->child, args);
            if (clipped) N64Eng_SetClipBounds(saved.left, saved.top, saved.right, saved.bottom);
        }
}

static inline void drawWidgetGroup(DraftWidget *widget, sm_dldc args) {
        struct WidgetRect box;
        struct WidgetRect area;
        struct WidgetRect saved;
        struct WidgetRect clip;
        s32 clipped;
        clipped = 0;
        if (Widget_ComputeWidgetBounds(&area, &box, widget, &args)) {
            if (widget->flags & 0x200) {
                N64Eng_GetClipBounds(&saved.left, &saved.top, &saved.right, &saved.bottom);
                clip = saved;
                if (!Node_ClampRectToClip(&clip, &box)) return;
                clipped = 1;
                N64Eng_SetClipBounds(clip.left, clip.top, clip.right, clip.bottom);
            }

            Widget_DrawVisibleSiblings((Widget *)widget->child, args);
            if (clipped) N64Eng_SetClipBounds(saved.left, saved.top, saved.right, saved.bottom);
        }
}

#if defined(VERSION_US)
const unsigned int k_widgetConstantWords[1] = {
    0x10000B00,
};
#endif
void Widget_DrawWidget(DraftWidget *widget, sm_dldc args) {
    switch (widget->type) {
    case 3:
        Widget_DrawImageWidget((void *)widget, args);
        break;
    case 4:
        Widget_DrawTextWidget((void *)widget, args);
        break;
    case 6:
        Widget_DrawGradientWidget((void *)widget, args);
        break;
    case 8:
        drawWidgetChoice(widget, args);
        break;
    case 2:
        drawWidgetResetGroup(widget, args);
        break;
    case 1:
        drawWidgetGroup(widget, args);
        break;
    default: {
        s32 flags;
        flags = Menu_GetElementHandlerFlags(widget->type);
        if (!(flags & 1)) {
            N64Eng_ResetRenderState();
            g_frontendRenderStateInitialized = 0;
        }
        if (Smos_InvokeWidgetCallback((void *)widget, args) && !(flags & 1)) {
            N64Eng_RenderNoop();
            g_frontendRenderStateInitialized = 0;
        }
        break;
    }
    }
}

/* Applies a widget's flags, opacity and scale to the draw context, computes its draw rectangle
   (scaled about its centre when any scale is not 1) and its hit box, and clips the hit box to the
   screen. Returns 1 when the widget is visible, and then moves the context origin and clip to the
   draw rectangle. */
s32 Widget_ComputeWidgetBounds(struct WidgetRect *draw, struct WidgetRect *hit, WidgetLayout *widget, sm_dldc *ctx) {
    u16 flags = widget->flags;
    s32 parentFlags = ctx->flags;
    f32 parentScaleX = ctx->XScale;
    f32 parentScaleY = ctx->YScale;
    s32 centred = flags & 0x800;
    s32 useDraw = flags & 0x400;
    s32 halfW = widget->width >> 1;
    s32 halfH = widget->height >> 1;
    s32 drawHalfW;
    s32 drawHalfH;
    s32 centreX;
    s32 centreY;

    if (!(parentFlags & 0x4000)) {
        ctx->flags = parentFlags | (flags & 0x140);
    }
    ctx->flags |= widget->flags & 0x609;
    if (widget->alpha < 0xFF) {
        ctx->alpha = ctx->alpha * widget->alpha / 255;
    }
    if (ctx->flags & 1) {
        ctx->alpha >>= 1;
    }
    if (ctx->alpha == 0) {
        return 0;
    }
    if (!(widget->flags & 8)) {
        return 0;
    }
    if (ctx->XScale != 1.0f || ctx->YScale != 1.0f || widget->scaleX != 1.0f || widget->scaleY != 1.0f) {
        centreX = (widget->x + widget->offsetX + widget->width * 0.5f) * ctx->XScale;
        centreY = (widget->y + widget->offsetY + widget->height * 0.5f) * ctx->YScale;
        ctx->XScale *= widget->scaleX;
        ctx->YScale *= widget->scaleY;
        drawHalfW = widget->width * ctx->XScale * 0.5f;
        drawHalfH = widget->height * ctx->YScale * 0.5f;
        draw->left = centreX - drawHalfW + ctx->x;
        draw->right = centreX + drawHalfW + ctx->x;
        draw->top = centreY - drawHalfH + ctx->y;
        draw->bottom = centreY + drawHalfH + ctx->y;
    } else {
        draw->left = ctx->x + widget->x + widget->offsetX;
        draw->top = ctx->y + widget->y + widget->offsetY;
        draw->right = draw->left + widget->width - 1;
        draw->bottom = draw->top + widget->height - 1;
        drawHalfW = widget->width >> 1;
        drawHalfH = widget->height >> 1;
    }
    centreX = (f32)(widget->x + widget->width / 2) * parentScaleX;
    centreY = (f32)(widget->y + widget->height / 2) * parentScaleY;
    if (centred && useDraw) {
        *hit = *draw;
    } else if (!centred && !useDraw) {
        if (parentScaleX != 1.0f) {
            hit->left = (s32)(widget->x * parentScaleX) + ctx->x;
        } else {
            hit->left = widget->x + ctx->x;
        }
        hit->right = hit->left + widget->width;
        if (parentScaleY != 1.0f) {
            hit->top = (s32)(widget->y * parentScaleY) + ctx->y;
        } else {
            hit->top = widget->y + ctx->y;
        }
        hit->bottom = hit->top + widget->height;
    } else if (centred) {
        hit->left = centreX - drawHalfW + ctx->x;
        hit->top = centreY - drawHalfH + ctx->y;
        hit->right = centreX + drawHalfW + ctx->x;
        hit->bottom = centreY + drawHalfH + ctx->y;
    } else {
        hit->left = centreX - halfW + widget->offsetX + ctx->x;
        hit->top = centreY - halfH + widget->offsetY + ctx->y;
        hit->right = centreX + halfW + widget->offsetX + ctx->x;
        hit->bottom = centreY + halfH + widget->offsetY + ctx->y;
    }
    if (hit->left < 0) {
        hit->left = 0;
    } else if (hit->left > g_frontendViewportWidth) {
        return 0;
    }
    if (hit->right < 0) {
        return 0;
    }
    if (hit->right > g_frontendViewportWidth) {
        hit->right = g_frontendViewportWidth;
    }
    if (hit->top < 0) {
        hit->top = 0;
    } else if (hit->top > g_frontendViewportHeight) {
        return 0;
    }
    if (hit->bottom < 0) {
        return 0;
    }
    if (hit->bottom > g_frontendViewportHeight) {
        hit->bottom = g_frontendViewportHeight;
    }
    if (hit->right <= hit->left) {
        hit->right = hit->left + 1;
    }
    if (hit->bottom <= hit->top) {
        hit->bottom = hit->top + 1;
    }
    ctx->x = draw->left;
    ctx->y = draw->top;
    ctx->Rgn = *draw;
    return 1;
}

/* unit K_WIDGETCONSTANTWORDS.CPP */

/* unit WIDGET_FINDWIDGETATPOINT.CPP */
/* Draws a visible widget (flag 8): when Widget_ComputeWidgetBounds places it, and its draw flags ask for
   clipping (0x200), it narrows the current scissor from N64Eng_GetClipBounds to the widget's box through
   Node_ClampRectToClip_FrontendOpenresourcearchive (skipping the draw when nothing is left) and applies it with N64Eng_SetClipBounds; it then
   draws the widget through Widget_DrawWidget and restores the saved scissor if it was narrowed. */

/* Resets the state and copies the two configured values after initialization. */
void Widget_DrawVisibleWidgetClipped(Widget *widget, sm_dldc args) {
    struct WidgetRect box;
    struct WidgetRect area;
    struct WidgetRect saved;
    struct WidgetRect clip;
    sm_dldc local;
    s32 clipped;

    clipped = 0;
    if (widget->flags & 8) {
        local = args;
        if (Widget_ComputeWidgetBounds(&area, &box, widget, &local) != 0) {
            if (local.flags & 0x200) {
                N64Eng_GetClipBounds(&saved.left, &saved.top, &saved.right, &saved.bottom);
                clip = saved;
                if (Node_ClampRectToClip(&clip, &box) == 0) {
                    return;
                }
                clipped = 1;
                N64Eng_SetClipBounds(clip.left, clip.top, clip.right, clip.bottom);
            }

            Widget_DrawWidget((DraftWidget *)widget, args);
            if (clipped) {
                N64Eng_SetClipBounds(saved.left, saved.top, saved.right, saved.bottom);
            }
        }
    }
}

/* Walks a sibling node list and dispatches the by-value event to every node whose flag bit 3 is set. */
void Widget_DrawVisibleSiblings(Widget *node, sm_dldc event) {
    for (; node != 0; node = node->next) {
        if (node->flags & 8) {
            Widget_DrawWidget((DraftWidget *)node, event);
        }
    }
}

void Widget_ResetTextClipBounds(void) {

    struct WidgetRect *state;

    Widget_FlushTextBatches();
    state = &g_frontendClipBounds;
    state->top = 0;
    state->left = 0;
    state->right = g_frontendViewportWidth;
    state->bottom = g_frontendViewportHeight;
}

void Widget_SetWidgetFlag08(void *object, int enabled) {
    u16 *flags = &((Widget *)(object))->flags;
    if (enabled) {
        *flags |= 8;
    } else {
        *flags &= 0xFFF7;
    }
}

/* Sets or clears bit 1 of the flag halfword of a record according to the second
   argument. */
void Widget_SetWidgetFlag01(struct Widget *record, int enable) {
    if (enable) {
        record->flags |= 1;
    } else {
        record->flags &= ~1;
    }
}

void Widget_SetWidgetFlag40(void *object, int enabled) {
    u16 *flags = &((Widget *)(object))->flags;
    if (enabled) {
        *flags |= 0x40;
    } else {
        *flags &= 0xFFBF;
    }
}

/* Sets or clears bit 0x100 of the flag halfword of a record according to the second
   argument. */
void Widget_SetWidgetFlag100(void *object, int enable) {
    struct Widget *record = object;
    if (enable) {
        record->flags |= 0x100;
    } else {
        record->flags &= ~0x100;
    }
}

/* Stores two halfwords at offsets 0x14 and 0x16 of a record, a pair set together. */
void Widget_SetPairValues(struct Pair14 *record, s16 first, s16 second) {
    record->first = first;
    record->second = second;
}

/* Hit-tests a widget tree at point (px, py): unless a hit is already recorded it searches the
   node's later siblings first, then offsets the origin by the node's position and searches its
   children, and finally records the node itself when it has an id, its rectangle contains the
   point and FindKindHandler accepts its selector. */
void Widget_FindWidgetAtPoint(WidgetPointHitView **hit, WidgetPointHitView *node, sm_dldc args, s32 px, s32 py) {
    if (*hit != 0) {
        return;
    }
    if (node->next != 0) {
        Widget_FindWidgetAtPoint(hit, node->next, args, px, py);
    }
    if (*hit != 0) {
        return;
    }
    args.x += node->x;
    args.y += node->y;
    if (node->child != 0) {
        Widget_FindWidgetAtPoint(hit, node->child, args, px, py);
    }
    if (*hit != 0) {
        return;
    }
    if (node->id == -1) {
        return;
    }
    if (px < args.x || args.x + node->width < px || py < args.y ||
        args.y + node->height < py) {
        return;
    }
    if (FindKindHandler(node->selector) != 0) {
        *hit = node;
    }
}

/* Returns the union of the flag halfwords of every node in a linked list. */
s32 Widget_CollectSiblingFlags(struct WidgetNode *node) {
    s32 flags = 0;

    while (node != 0) {
        flags |= node->flags;
        node = node->next;
    }
    return flags;
}

/* Returns whether any node in a linked list has bit 3 set in its flag halfword. */
s32 Widget_AnyVisibleSibling(struct WidgetNode *node) {
    u32 flags = 0;

    while (node != 0) {
        flags |= node->flags;
        node = node->next;
    }
    return (flags >> 3) & 1;
}

/* Returns whether any node in a linked list has bit 0 set in its flag halfword. */
s32 Widget_AnySiblingFlag01(struct WidgetNode *node) {
    s32 flags = 0;

    while (node != 0) {
        flags |= node->flags;
        node = node->next;
    }
    return flags & 1;
}

/* Returns whether any node in a linked list has bit 6 set in its flag halfword. */
s32 Widget_AnySiblingFlag40(struct WidgetNode *node) {
    u32 flags = 0;

    while (node != 0) {
        flags |= node->flags;
        node = node->next;
    }
    return (flags >> 6) & 1;
}

/* Returns whether any node in a linked list has bit 8 set in its flag halfword. */
s32 Widget_ListHasFlag100(struct WidgetNode *node) {
    u32 flags = 0;

    while (node != 0) {
        flags |= node->flags;
        node = node->next;
    }
    return (flags >> 8) & 1;
}

/* Sums the halfword positions at offsets 0x14 and 0x16 along a linked list starting at a node and
   reports the totals through the two pointers. */
void Widget_SumNodeOffsets(struct WidgetAncestorOffsetView *node, s32 *x, s32 *y) {
    s32 sumX = node->x;
    s32 sumY = node->y;

    while (node->next != 0) {
        node = node->next;
        sumX += node->x;
        sumY += node->y;
    }
    *x = sumX;
    *y = sumY;
}

/* unit FRONTEND_DRAWEUROPEANCLIPPEDCHILDREN.CPP */
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
