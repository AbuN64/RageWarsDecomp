#include "include_asm.h"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/gbi.h>
#include "COMMON/FONT_STYLE_AND_GLYPH_OPERATIONS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/WORLD.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/TEXTLAYERMETRICS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "MENU/PAK/MENU_CREATEMENUFROMTEMPLATE.H"

/* 802A8A94_2.CPP */
extern CacheResourceNode *Scene_StartWorldEffect(Shared_World *, s32, s32, s32);
extern void Text_DrawTileGrid(CacheResourceNode *, s32, s16, s16, f32, f32, s32);
extern void Cache_UnlockResource(void *, CacheResourceNode *);

/* The advance and kerning scale follow the currently selected font. */
static inline f32 fontGlyphWidth(void)
{
    f32 result;
    switch (g_creditsTextDrawingEnabled) {
    case 0: result = 24.0f; break;
    case 1: result = 12.0f; break;
    case 3: result = 6.0f; break;
    case 4: case 5: result = 16.0f; break;
    case 2: case 6: result = 8.0f; break;
    default: result = 1.0f; break;
    }
    return result;
}

void OnScreen_DrawTextGlyphs(u8 *text, f32 x, f32 y, f32 width, f32 height, s32 shadow, s32 alpha, s32 language)
{
    FontStyle *style = &g_tutorialStatusBars;
    CacheResourceNode *font;
    s32 special = 0;
    s32 resource;
    u8 ch, next, glyph;
    f32 advance, sx, sy, a, b;

    gDPPipeSync(g_displayListCursor++);
    if (shadow) {
        gDPSetEnvColor(g_displayListCursor++, 0, 0, 0, alpha);
        gDPSetPrimColor(g_displayListCursor++, 0, 0, 0, 0, 0, 255);
        x += style->shadowX * (g_hudReferenceViewportWidth / 284);
        y += style->shadowY * (g_hudReferenceViewportHeight / 222);
    } else {
        gDPSetEnvColor(g_displayListCursor++, style->envR, style->envG, style->envB, alpha);
        gDPSetPrimColor(g_displayListCursor++, 0, 0, style->primR, style->primG, style->primB, 255);
    }
    switch (language) {
    default: case 0: resource = 2; break;
    case 1: resource = 1; special = 1; break;
    case 2: case 3: resource = 6; break;
    case 4: case 5: resource = 5; break;
    case 6: resource = 7; break;
    }
    font = Scene_StartWorldEffect(&g_world, resource, 16, 1);
    if (font) {
        while (text && (ch = *text) && ch != 10) {
            next = text[1];
            switch (language) {
            default: case 0:
                glyph = g_fontAlternateGlyphLookup[ch];
                a = fontGlyphWidth();
                b = fontGlyphWidth();
                advance = Menu_GetGlyphAdvance(ch, next, a, b);
                break;
            case 1:
                glyph = g_fontGlyphLookup[ch];
                advance = fontGlyphWidth();
                break;
            case 2:
                glyph = g_fontGlyphLookup[ch];
                advance = fontGlyphWidth();
                break;
            case 3:
                glyph = g_fontGlyphLookup[ch];
                advance = fontGlyphWidth();
                break;
            case 4:
                glyph = ch;
                if (ch == 255) glyph = 255;
                advance = fontGlyphWidth();
                break;
            case 5:
                glyph = ch;
                if (ch == 255) glyph = 255;
                advance = fontGlyphWidth();
                break;
            case 6:
                glyph = ch;
                if (ch == 255) glyph = 255;
                advance = fontGlyphWidth();
                break;
            }
            sx = width;
            sy = height;
            if (special && (glyph == 37 || glyph == 43 || glyph == 61)) {
                sx = g_hudReferenceViewportWidth * (1.0f / 284.0f);
                sy = g_hudReferenceViewportHeight * (1.0f / 222.0f);
            }
            if (glyph != 255) {
                Text_DrawTileGrid(font, glyph, (s16)x, (s16)y, sx, sy, 1);
            }
            x += advance * sx;
            text++;
        }
        Cache_UnlockResource(0, font);
    }
}

/* 800CB2D4.CPP */

