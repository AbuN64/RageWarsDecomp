#include "include_asm.h"
#include "COMMON/NODERECAT2A8.H"
#include "COMMON/AUDIO_CALLBACKS.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/RECTANGLE_DRAW.H"
#include "FRONTEND/TEXT_RENDER.H"
#include "COMMON/WIDGETRECAT1A.H"
#include "COMMON/SLOTRECATCV1.H"
#include "COMMON/WIDGETRECAT34.H"
#include "COMMON/TEXTURE.H"
#include "TYPES.H"
#include "FRONTEND/WIDGET_DRAWTEXTWIDGET.H"
#include "FRONTEND/FRONTEND_OPENRESOURCEARCHIVE.H"
#include "MENU/GFX/COMBINE_CONFIGUREPRIMITIVERENDERFLAGS.H"
#include "UI/QUAG/N64_ENG.H"
#include "MATH/SMOS_INVOKEWIDGETCALLBACK.H"
#include "FRONTEND/NODE_GETIMAGETEXTURE.H"

extern BatchRec g_textBatches[];
extern struct CacheResourceBlockView g_frontendClipBounds;
extern s32 Widget_ComputeWidgetBounds(struct CacheResourceBlockView *, struct CacheResourceBlockView *, WidgetLayout *widget, sm_dldc *);
/* Flushes the queued text sprite batches: when any are queued it selects render mode 0x53333 if
   not already active, saves the clip rectangle and applies the queue's own, then walks the texture
   pages from the lowest first page to the highest last page among the batches, loading each page
   once through Node_GetBankTileTexture and Combine_BindImageTexture (stopping the page when it cannot load) and drawing
   every batch's run of sprites on that page at depth 10 through Rect_DrawRect; finally it restores
   the clip rectangle and empties the queue. */














extern s32 Node_GetBankTileTexture(s32 page, s32 a, s32 b);

extern void Combine_BindImageTexture(s32 texture);

static inline void Widget_RestoreClipBounds(struct CacheResourceBlockView *clip) {
    N64Eng_SetClipBounds(clip->first, clip->third, clip->second, clip->fourth);
}

extern s32 Node_ClampRectToClip(struct CacheResourceBlockView *rect, struct CacheResourceBlockView *clip);


static inline s32 Widget_OverlapsTextBatchForClear(struct CacheResourceBlockView *area) {
    BatchRec *batch;
    s32 i;

    for (i = 0; i < g_textBatchCount; i++) {
        batch = &g_textBatches[i];
        if (area->second < batch->area.first || batch->area.second < area->first || area->fourth < batch->area.third ||
            batch->area.fourth < area->third) {
            continue;
        }
        return 1;
    }
    return 0;
}

extern void Rect_DrawGradientRectangle(f32 x, f32 y, s32 z, f32 width, f32 height, s32 c0, s32 c1, s32 c2, s32 c3);

static inline s32 Widget_OverlapsTextBatchForDraw(struct CacheResourceBlockView *area) {
    BatchRec *batch;
    s32 i;

    for (i = 0; i < g_textBatchCount; i++) {
        batch = &g_textBatches[i];
        if (area->second < batch->area.first || batch->area.second < area->first || area->fourth < batch->area.third ||
            batch->area.fourth < area->third) {
            continue;
        }
        return 1;
    }
    return 0;
}

s32 XPlus_StringLength(u8 *);

GlyphBuffer *Node_GetGlyphBuffer(s32);

void XPlus_SortArray(char *, s32, s32, s32 (*)(char *, char *));

static inline void textBegin(u8 font, u8 style) {
    N64Eng_GetClipBounds(&g_frontendClipBounds.first, &g_frontendClipBounds.third,
                   &g_frontendClipBounds.second, &g_frontendClipBounds.fourth);
    g_textBatchFontId = (s8)font;
    g_textBatchStyle = (s8)style;
    g_textGlyphBuffer = Node_GetGlyphBuffer((s8)font);
    g_textGlyphSpacing = Node_GetFontLetterSpacing((s8)font);
    g_textLineHeight = Node_GetFontMetricAtC((s8)font);
    g_textVerticalOffset = Node_GetFontMetricAtA((s8)font);
}

static inline s32 textOverlaps(BatchRec *next) {
    s32 i;
    BatchRec *batch;
    for (i = 0; i < g_textBatchCount; i++) {
        batch = &g_textBatches[i];
        if (next->area.second < batch->area.first || batch->area.second < next->area.first ||
            batch->area.third > next->area.fourth || batch->area.fourth < next->area.third) continue;
        return 1;
    }
    return 0;
}

static inline s32 textClipChanged(struct CacheResourceBlockView *current) {
    if (current->first != g_frontendClipBounds.first) return 1;
    if (current->third != g_textClipTop) return 1;
    if (current->second != g_textClipRight) return 1;
    return current->fourth != g_textClipBottom;
}

void Widget_FlushTextBatches(void) {
    u16 first;
    u16 last;
    u16 page;
    s32 i;
    s32 current;
    s32 loaded;
    s32 texture;
    struct CacheResourceBlockView clip;
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
    N64Eng_GetClipBounds(&clip.first, &clip.third, &clip.second, &clip.fourth);
    N64Eng_SetClipBounds(g_frontendClipBounds.first, g_textClipTop, g_textClipRight, g_textClipBottom);
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
    struct CacheResourceBlockView box;
    struct CacheResourceBlockView area;
    struct CacheResourceBlockView saved;
    struct CacheResourceBlockView clip;
    s32 clipped;
    s32 texture;
    s32 color;

    clipped = 0;
    if (Widget_ComputeWidgetBounds(&area, &box, widget, &args) == 0) {
        return;
    }
    if (widget->flags & 0x200) {
        N64Eng_GetClipBounds(&saved.first, &saved.third, &saved.second, &saved.fourth);
        clip = saved;
        if (Node_ClampRectToClip(&clip, &box) == 0) {
            return;
        }
        clipped = 1;
        N64Eng_SetClipBounds(clip.first, clip.third, clip.second, clip.fourth);
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
    Rect_DrawRect(area.first, area.third, 0.0f, area.second - area.first + 1, area.fourth - area.third + 1, color);
    if (clipped) {
        N64Eng_SetClipBounds(saved.first, saved.third, saved.second, saved.fourth);
    }
}

void Widget_DrawGradientWidget(WidgetLayout *widget, sm_dldc args) {
    struct CacheResourceBlockView box;
    struct CacheResourceBlockView area;
    struct CacheResourceBlockView saved;
    struct CacheResourceBlockView clip;
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
        N64Eng_GetClipBounds(&saved.first, &saved.third, &saved.second, &saved.fourth);
        clip = saved;
        if (Node_ClampRectToClip(&clip, &box) == 0) {
            return;
        }
        clipped = 1;
        N64Eng_SetClipBounds(clip.first, clip.third, clip.second, clip.fourth);
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
    Rect_DrawGradientRectangle(area.first, area.third, 0.0f, area.second - area.first + 1, area.fourth - area.third + 1,
                  (widget->colors[0] & 0xFFFFFF) | ((args.alpha * (u8)(widget->colors[0] >> 24) / 255) << 24),
                  (widget->colors[1] & 0xFFFFFF) | ((args.alpha * (u8)(widget->colors[1] >> 24) / 255) << 24),
                  (widget->colors[2] & 0xFFFFFF) | ((args.alpha * (u8)(widget->colors[2] >> 24) / 255) << 24),
                  (widget->colors[3] & 0xFFFFFF) | ((args.alpha * (u8)(widget->colors[3] >> 24) / 255) << 24));
    if (clipped) {
        N64Eng_SetClipBounds(saved.first, saved.third, saved.second, saved.fourth);
    }
}

void Widget_DrawTextWidget(TextWidget *widget, sm_dldc args) {
    struct CacheResourceBlockView box, saved, clip, area, current;
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
        N64Eng_GetClipBounds(&saved.first, &saved.third, &saved.second, &saved.fourth);
        clip = saved;
        if (!Node_ClampRectToClip(&clip, &box)) return;
        clipped = 1;
        N64Eng_SetClipBounds(clip.first, clip.third, clip.second, clip.fourth);
    }
    length = XPlus_StringLength(text);
    if (args.flags & 0x100) { font=widget->fontSelected; style=widget->styleSelected; }
    else if (args.flags & 0x40) { font=widget->fontAlt; style=widget->styleAlt; }
    else { font=widget->font; style=widget->style; }
    if ((s8)font == -1) font=widget->font;
    if ((s8)style == -1) style=widget->style;
    if (g_textBatchCount) {
        N64Eng_GetClipBounds(&current.first, &current.third, &current.second, &current.fourth);
        mismatch = textClipChanged(&current);
        if (mismatch || g_textBatchFontId != (s8)font || g_textBatchStyle != (s8)style) {
            if (g_textBatchCount) Widget_FlushTextBatches();
            textBegin(font, style);
        }
    } else textBegin(font, style);
    width = Node_MeasureTextPrefix((s8)font, text, length) * args.XScale;
    x = 0.0f;
    switch (widget->align & 3) {
        case 0: x=area.first; break;
        case 1: x=(area.first+area.second)/2-width/2; break;
        case 2: {s32 edge=area.second; ++edge; x=edge-width;} break;
    }
    y = 0.0f;
    switch (widget->align & 12) {
        case 0: y=area.third; y-=g_textVerticalOffset*args.YScale; break;
        case 4:
            y=(area.third+area.fourth)/2; y-=g_textVerticalOffset*args.YScale; y-=(g_textLineHeight/2)*args.YScale; break;
        case 8:
            sub=(g_textLineHeight+g_textVerticalOffset)*args.YScale;
            y=area.fourth; y-=sub; break;
    }
    batch=&g_textBatches[g_textBatchCount];
    tempX=x; batch->area.first=tempX; batch->area.second=tempX+width;
    tempY=(s32)y+(s32)(g_textVerticalOffset*args.YScale);
    batch->area.third=tempY; batch->area.fourth=tempY+(s32)(g_textLineHeight*args.YScale);
    if (batch->area.first >= batch->area.second) batch->area.second=batch->area.first+1;
    if (batch->area.fourth <= batch->area.third) batch->area.fourth=batch->area.third+1;
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
    if (clipped) N64Eng_SetClipBounds(saved.first, saved.third, saved.second, saved.fourth);
    if (count>0) {
        g_textBatches[g_textBatchCount].count=count;
        XPlus_SortArray((char *)g_textBatches[g_textBatchCount].cursor, count, sizeof(TextSprite), Node_CompareRecordShortValuesRomEntry);
        g_textBatchCount++;
        if (g_textBatchCount>=16) Widget_FlushTextBatches();
    }
}

#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/WIDGETRECAT1A.H"
#include "TYPES.H"

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

extern void Widget_DrawVisibleSiblings(void *, sm_dldc);
extern s32 Menu_GetElementHandlerFlags(s32);

void Widget_DrawWidget(DraftWidget *, sm_dldc);
static inline void drawWidgetChoice(DraftWidget *widget, sm_dldc args) {
        struct CacheResourceBlockView area;
        struct CacheResourceBlockView box;
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
        struct CacheResourceBlockView box;
        struct CacheResourceBlockView saved;
        struct CacheResourceBlockView clip;
        struct CacheResourceBlockView area;
        s32 clipped;
        clipped = 0;
        g_frontendRenderStateInitialized = 0;
        if (Widget_ComputeWidgetBounds(&area, &box, widget, &args)) {
            if (widget->flags & 0x200) {
                N64Eng_GetClipBounds(&saved.first, &saved.third, &saved.second, &saved.fourth);
                clip = saved;
                if (!Node_ClampRectToClip(&clip, &box)) return;
                clipped = 1;
                N64Eng_SetClipBounds(clip.first, clip.third, clip.second, clip.fourth);
            }
            Widget_DrawVisibleSiblings(widget->child, args);
            if (clipped) N64Eng_SetClipBounds(saved.first, saved.third, saved.second, saved.fourth);
        }
}

static inline void drawWidgetGroup(DraftWidget *widget, sm_dldc args) {
        struct CacheResourceBlockView box;
        struct CacheResourceBlockView area;
        struct CacheResourceBlockView saved;
        struct CacheResourceBlockView clip;
        s32 clipped;
        clipped = 0;
        if (Widget_ComputeWidgetBounds(&area, &box, widget, &args)) {
            if (widget->flags & 0x200) {
                N64Eng_GetClipBounds(&saved.first, &saved.third, &saved.second, &saved.fourth);
                clip = saved;
                if (!Node_ClampRectToClip(&clip, &box)) return;
                clipped = 1;
                N64Eng_SetClipBounds(clip.first, clip.third, clip.second, clip.fourth);
            }
            Widget_DrawVisibleSiblings(widget->child, args);
            if (clipped) N64Eng_SetClipBounds(saved.first, saved.third, saved.second, saved.fourth);
        }
}

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
s32 Widget_ComputeWidgetBounds(struct CacheResourceBlockView *draw, struct CacheResourceBlockView *hit, WidgetLayout *widget, sm_dldc *ctx) {
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
        draw->first = centreX - drawHalfW + ctx->x;
        draw->second = centreX + drawHalfW + ctx->x;
        draw->third = centreY - drawHalfH + ctx->y;
        draw->fourth = centreY + drawHalfH + ctx->y;
    } else {
        draw->first = ctx->x + widget->x + widget->offsetX;
        draw->third = ctx->y + widget->y + widget->offsetY;
        draw->second = draw->first + widget->width - 1;
        draw->fourth = draw->third + widget->height - 1;
        drawHalfW = widget->width >> 1;
        drawHalfH = widget->height >> 1;
    }
    centreX = (f32)(widget->x + widget->width / 2) * parentScaleX;
    centreY = (f32)(widget->y + widget->height / 2) * parentScaleY;
    if (centred && useDraw) {
        *hit = *draw;
    } else if (!centred && !useDraw) {
        if (parentScaleX != 1.0f) {
            hit->first = (s32)(widget->x * parentScaleX) + ctx->x;
        } else {
            hit->first = widget->x + ctx->x;
        }
        hit->second = hit->first + widget->width;
        if (parentScaleY != 1.0f) {
            hit->third = (s32)(widget->y * parentScaleY) + ctx->y;
        } else {
            hit->third = widget->y + ctx->y;
        }
        hit->fourth = hit->third + widget->height;
    } else if (centred) {
        hit->first = centreX - drawHalfW + ctx->x;
        hit->third = centreY - drawHalfH + ctx->y;
        hit->second = centreX + drawHalfW + ctx->x;
        hit->fourth = centreY + drawHalfH + ctx->y;
    } else {
        hit->first = centreX - halfW + widget->offsetX + ctx->x;
        hit->third = centreY - halfH + widget->offsetY + ctx->y;
        hit->second = centreX + halfW + widget->offsetX + ctx->x;
        hit->fourth = centreY + halfH + widget->offsetY + ctx->y;
    }
    if (hit->first < 0) {
        hit->first = 0;
    } else if (hit->first > g_frontendViewportWidth) {
        return 0;
    }
    if (hit->second < 0) {
        return 0;
    }
    if (hit->second > g_frontendViewportWidth) {
        hit->second = g_frontendViewportWidth;
    }
    if (hit->third < 0) {
        hit->third = 0;
    } else if (hit->third > g_frontendViewportHeight) {
        return 0;
    }
    if (hit->fourth < 0) {
        return 0;
    }
    if (hit->fourth > g_frontendViewportHeight) {
        hit->fourth = g_frontendViewportHeight;
    }
    if (hit->second <= hit->first) {
        hit->second = hit->first + 1;
    }
    if (hit->fourth <= hit->third) {
        hit->fourth = hit->third + 1;
    }
    ctx->x = draw->first;
    ctx->y = draw->third;
    ctx->Rgn = *draw;
    return 1;
}
