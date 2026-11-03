#include "include_asm.h"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "COMMON/NAME.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "MENU/OPTION_AND_TEXT_LAYER_VIEWS.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "COMMON/MENU_ABBDC_VERSIONS.H"

u32 Defs_GetMemorySize(void);
int SetN64_IsModeThirteen(void);
u8 *Menu_GetDynamicItemText(TextBoundsText *);
f32 Menu_MeasureLine(u8 *, f32, f32);
void *Menu_GetListContext(s8 *);
extern f32 g_menuTextScreenHeightScale;
extern f32 g_menuTextFontHeightPadding;
extern f32 g_menuTextFontHeightScale;
extern f32 g_menuTextAlternateFontHeightScale;
extern f32 g_menuTextScreenWidthScale;
extern f32 g_menuTextAlternateScreenHeightScale;
extern TextBoundsFont g_menuFontStyles[];

static __inline__ TextBoundsFont *textBoundsFont(TextBoundsText *text) {
    s32 style = 0;
    switch ((u32)text->flags & 0x3FE0) {
    case 32: style = 0; break;
    case 64: style = 1; break;
    case 128: style = 2; break;
    case 0x100: style = 3; break;
    case 0x200: style = 4; break;
    case 0x400: style = 5; break;
    case 0x800: style = 6; break;
    case 0x1000: style = 7; break;
    case 0x2000: style = 8; break;
    default: style = 0; break;
    }
    style += MENU_LANGUAGE * 9;
    return &g_menuFontStyles[style];
}

/* Measures a text item into its metrics: size by kind (glyph run, image, three-part composite, box), then the scaled screen
 * rectangle from the item position (284 x 222 virtual screen). */
void Menu_MeasureMenuText(TextBoundsText *text, CItemInfo *metrics) {
    TextBoundsText part;
    CItemInfo first, second, third;
    TextBoundsData *data;
    TextBoundsFont *font;
    TextBoundsRecord23 *box;
    u8 *string;
    s32 count, width;
    f32 size, w, boxW, boxH, sx, sy, x, y;

    data = Menu_GetListContext(text->descriptor->listContextKey);
    metrics->m_ScaleY = g_menuTextDefaultScale;
    metrics->m_ScaleX = g_menuTextDefaultScale;
    switch (text->mode) {
    case 0:
    case 5:
        font = textBoundsFont(text);
        if (font->kind == 0) {
            size = font->width;
            if (text->mode == 5) {
                string = Menu_GetDynamicItemText(text);
            } else {
                string = ((u8 **)text->text)[MENU_LANGUAGE];
            }
            w = Menu_MeasureLine(string, size, size);
        } else {
            count = 0;
            if (text->mode == 5) {
                string = Menu_GetDynamicItemText(text);
            } else {
                string = ((u8 **)text->text)[MENU_LANGUAGE];
            }
            while (string != 0 && *string != 0 && *string != '\n') {
                string++;
                count++;
            }
            w = count * font->width;
        }
        metrics->width = w;
        if (text->flags & 0x08000000) {
            metrics->height = g_hudReferenceViewportHeight * g_menuTextScreenHeightScale;
        } else if (font->kind == 2 && g_hudReferenceViewportHeight >= 223) {
            metrics->height = (font->height + g_menuTextFontHeightPadding) * g_hudReferenceViewportHeight * g_menuTextFontHeightScale;
        } else {
            metrics->height = font->height * g_hudReferenceViewportHeight * g_menuTextFontHeightScale;
        }
        metrics->width = metrics->width * g_hudReferenceViewportWidth / 284;
        break;
    case 4:
        font = textBoundsFont(text);
        metrics->width = font->width;
        metrics->height = font->height * g_hudReferenceViewportHeight * g_menuTextAlternateFontHeightScale;
        break;
    case 1:
        if ((SetN64_IsModeThirteen() != 0 && (text->flags & 0x40000000)) ||
            (g_frontendScreenStatus.settings.local != 0 && text->flags < 0 && Defs_GetMemorySize() == 0x400000)) {
            metrics->width = 284;
            metrics->height = 222;
        } else {
            OnScreen_GetImageDimensions((s32)text->text, 0, &metrics->width, &metrics->height);
        }
        if ((text->flags & 0x10000000) && (boxW = metrics->width) != 0.0f && (boxH = metrics->height) != 0.0f) {
            sx = data->width / boxW;
            sy = data->height / boxH;
        } else {
            sx = g_hudReferenceViewportWidth * g_menuTextScreenWidthScale;
            sy = g_hudReferenceViewportHeight * g_menuTextAlternateScreenHeightScale;
        }
        metrics->m_ScaleX = sx;
        metrics->m_ScaleY = sy;
        break;
    case 2:
        first = *metrics;
        part = *text;
        part.mode = 0;
        Menu_MeasureMenuText(&part, &first);
        second = *metrics;
        part = *text;
        part.mode = 1;
        part.text = 0;
        Menu_MeasureMenuText(&part, &second);
        third = *metrics;
        part = *text;
        part.mode = 1;
        part.text = 0;
        Menu_MeasureMenuText(&part, &third);
        width = second.width + third.width;
        if (width < first.width) {
            width = first.width;
        }
        metrics->width = width;
        metrics->height = first.height + second.height + (third.height - second.height) / 2;
        break;
    case 3:
        box = text->text;
        metrics->width = box->width * data->width / g_hudReferenceViewportWidth;
        metrics->height = box->height * data->height / g_hudReferenceViewportHeight;
        break;
    default:
        metrics->width = 1;
        metrics->height = 1;
        break;
    }
    x = text->x * g_hudReferenceViewportWidth / 284;
    if (!(text->flags & 0x8000)) {
        if (text->flags & 0x4000) {
            metrics->left = metrics->right + x;
        } else {
            metrics->left = x;
        }
    }
    metrics->right = metrics->left + metrics->width * metrics->m_ScaleX;
    y = text->y * g_hudReferenceViewportHeight / 222;
    if (!(text->flags & 0x20000)) {
        if (text->flags & 0x10000) {
            metrics->m_Top = metrics->m_Bottom + y;
        } else {
            metrics->m_Top = y;
        }
    }
    metrics->m_Bottom = metrics->m_Top + metrics->height * metrics->m_ScaleY;
}
