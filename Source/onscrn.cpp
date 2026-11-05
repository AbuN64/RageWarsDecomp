#include "Common/game_session.h"
#include "include_asm.h"
#include "types.h"
#include <platform_sdk.h>
#include <PR/gbi.h>
#include "Common/font_style_and_glyph_operations.h"
#include "Common/world.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Common/textlayermetrics.h"
#include "Common/resident_event_handler.h"
#include "Common/sessionhandlerrow.h"
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "Menu/Items/Scene/scene_setlevelactorstatebit.h"
#include "Onscrn/text_drawtilegrid.h"
#include "Scene/cache_allocateresourceat.h"
#include "onscrn.h"
#include <PR/abi.h>
#include "Common/weapon_marker_and_profile_views.h"
#include "Ai/player_updateplayercamera.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#include "Onscrn/onscreen_drawscaledmaskedimage.h"
#include "Common/tile_grid_bytes.h"
#include "../sdk/include/LIBC.H"
#include "Common/weapon_screen_message_operations.h"
#include "Common/shared_gameslot.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Common/frustum.h"
#include "Common/statepair.h"
#include "Common/hud_effects.h"
#include "Resmgr/tsmos_updatefrontend.h"
#include "System/textload_resettexturecache.h"
#include "Common/Lone/screen_image_resources_enabled.h"
#include "Common/sharedplayer.h"
#include "Common/math_helpers.h"
#include "Common/worldsortentry.h"
#include "Common/display.h"
#include "Common/aiprofile.h"
#include "Common/pickup_entry_tables.h"
#include "Onscrn/onscreen_drawscaledmaskedtilegrid.h"
#include "Onscrn/onscreen_drawscaledmaskedtilegrid_symbols.h"
#include "Menu/pickup_drawscaledintensitytilegrid.h"
#include "Common/Lone/hud_reference_viewport_height.h"

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
    Hud *style = &g_gameSession.hud;
    struct CacheResourceNode *font;
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
                glyph = g_gameSession.hud.alternateGlyphLookup[ch];
                a = fontGlyphWidth();
                b = fontGlyphWidth();
                advance = Menu_GetGlyphAdvance(ch, next, a, b);
                break;
            case 1:
                glyph = g_gameSession.hud.glyphLookup[ch];
                advance = fontGlyphWidth();
                break;
            case 2:
                glyph = g_gameSession.hud.glyphLookup[ch];
                advance = fontGlyphWidth();
                break;
            case 3:
                glyph = g_gameSession.hud.glyphLookup[ch];
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

/* 802A8A94_3.CPP */
/* Draws a text string in the current font style g_gameSession.hud: when centring, measures it through Menu_MeasureLine at the style size scaled by the language-dependent factors for g_creditsTextDrawingEnabled, shrinks the scale so it fits 44 pixels inside the screen width g_hudReferenceViewportWidth and shifts x left by half the width; then sets the environment colour from the style with the given alpha and the primitive colour from the style, and draws the string through OnScreen_DrawTextGlyphs, first as a shadow when requested. */

extern Gfx *g_displayListCursor;
extern f32 Menu_MeasureLine(u8 *text, f32 size, f32 spacing);

void Onscrn_DrawText(void * text, s32 x, s32 y, s32 alpha, s32 centred, s32 shadow, f32 scaleX, f32 scaleY) {
    Hud *style;
    f32 sizeFactor;
    f32 spacing;
    f32 size;
    f32 width;
    f32 limit;
    f32 ratio;
    f32 fx;
    f32 fy;
    f32 w;
    f32 h;
    s32 language;

    style = &g_gameSession.hud;
    if (centred) {
        switch (g_creditsTextDrawingEnabled) {
        case 0:
            sizeFactor = 24.0f;
            break;
        case 1:
            sizeFactor = 12.0f;
            break;
        case 3:
            sizeFactor = 6.0f;
            break;
        case 4:
        case 5:
            sizeFactor = 16.0f;
            break;
        case 2:
        case 6:
            sizeFactor = 8.0f;
            break;
        default:
            sizeFactor = 1.0f;
            break;
        }
        size = style->width * scaleX * sizeFactor;
        switch (g_creditsTextDrawingEnabled) {
        case 0:
            spacing = 24.0f;
            break;
        case 1:
            spacing = 12.0f;
            break;
        case 3:
            spacing = 6.0f;
            break;
        case 4:
        case 5:
            spacing = 16.0f;
            break;
        case 2:
        case 6:
            spacing = 8.0f;
            break;
        default:
            spacing = 1.0f;
            break;
        }
        width = Menu_MeasureLine(text, size, spacing);
        limit = g_hudReferenceViewportWidth - 44;
        if (limit < width) {
            ratio = limit / width;
            scaleX *= ratio;
            width *= ratio;
        }
        x -= (s32)(width * 0.5f);
    }
    gDPPipeSync(g_displayListCursor++);
    gDPSetEnvColor(g_displayListCursor++, (u32)((style->envR)), (u32)((style->envG)), (u32)((style->envB)), (u32)((alpha)));
    gDPSetPrimColor(g_displayListCursor++, 0, 0, (u32)((style->primR)), (u32)((style->primG)), (u32)((style->primB)), 255);
    fx = x;
    w = style->width * scaleX;
    h = style->height * scaleY;
    language = g_creditsTextDrawingEnabled;
    fy = y;
    if (shadow) {
        OnScreen_DrawTextGlyphs(text, fx, fy, w, h, 1, alpha, language);
    }
    OnScreen_DrawTextGlyphs(text, fx, fy, w, h, 0, alpha, language);
}

/* Emits the render-state display-list prologue for a flat colour pass: pipeline sync, one-cycle
   mode, the two combiner/mode presets through Geometry_SetCombineMode_GeometryDrawcharactereffectparts and Geometry_SetModePreset, the environment
   colour from the argument with full alpha bits, texture enable and the texture-filter, colour-dither
   and alpha-dither mode words, the alpha dither chosen by g_frontendCurrentVideoModeIndex. */
void Onscrn_SetupSpriteMode(s32 color) {
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_2CYCLE);
    Geometry_SetCombineMode(27);
    Geometry_SetModePreset(25);
    {
        Gfx *cmd = g_displayListCursor++;
        gDPSetEnvColor(cmd, 255, 255, 255, color);
    }
    gSPTexture(g_displayListCursor++, 32768, 32768, 0, 0, G_ON);
    gDPSetTextureLUT(g_displayListCursor++, G_TT_NONE);
    gDPSetTexturePersp(g_displayListCursor++, G_TP_NONE);
    if (g_frontendCurrentVideoModeIndex == 0) { gDPSetTextureFilter(g_displayListCursor++, G_TF_POINT); } else { gDPSetTextureFilter(g_displayListCursor++, G_TF_BILERP); }
}

void OnScreen_DrawTextureWithOpacity(void *pTexture, void *pOpacity, int XPos, int YPos, int TextureWidth, int TextureHeight) {
    { gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_16b, 1, (u32)pOpacity); gDPSetTile(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 256, G_TX_LOADTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0); gDPLoadSync(g_displayListCursor++); gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((((TextureWidth*TextureHeight+3)>>2)-1))), (u32)((((1<<11)+(1>(TextureWidth/16)?1:(TextureWidth/16))-1)/(1>(TextureWidth/16)?1:(TextureWidth/16))))); gDPPipeSync(g_displayListCursor++); gDPSetTile(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_4b, (u32)(((((TextureWidth>>1)+7)>>3))), 256, G_TX_RENDERTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0); gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, (u32)(((TextureWidth-1)<<2)), (u32)(((TextureHeight-1)<<2))); }
    { gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, (u32)pTexture); gDPSetTile(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0); gDPLoadSync(g_displayListCursor++); gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((TextureWidth*TextureHeight-1))), (u32)((((1<<11)+(1>(TextureWidth*2/8)?1:(TextureWidth*2/8))-1)/(1>(TextureWidth*2/8)?1:(TextureWidth*2/8))))); gDPPipeSync(g_displayListCursor++); gDPSetTile(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, (u32)((((TextureWidth*2)+7)>>3)), 0, G_TX_RENDERTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0); gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, (u32)(((TextureWidth-1)<<2)), (u32)(((TextureHeight-1)<<2))); }
    gDPSetTile(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_4b, (u32)((TextureWidth/16)), 256, 1, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0);
    gDPSetTileSize(g_displayListCursor++, 1, 0, 0, (u32)(((TextureWidth-1)<<2)), (u32)(((TextureHeight-1)<<2)));
    { Gfx *g=g_displayListCursor++; { Gfx *_g = (Gfx *)(g); _g->words.w0 = (_SHIFTL(G_TEXRECT,24,8) | _SHIFTL((XPos+TextureWidth)<<2,12,12) | _SHIFTL((YPos+TextureHeight)<<2,0,12)); _g->words.w1 = (_SHIFTL(0,24,3) | _SHIFTL(XPos<<2,12,12) | _SHIFTL(YPos<<2,0,12)); }; { Gfx *_g = (Gfx *)(g_displayListCursor++); _g->words.w0 = (_SHIFTL(G_RDPHALF_1,24,8)); _g->words.w1 = ((unsigned int)(0)); }; { Gfx *_g = (Gfx *)(g_displayListCursor++); _g->words.w0 = (_SHIFTL(G_RDPHALF_2,24,8)); _g->words.w1 = ((unsigned int)((((u32)((1<<10)) & 0xFFFF) << ((16)))|(((u32)((1<<10)) & 0xFFFF) << ((0))))); }; }
}

void OnScreen_DrawScaledMaskedImage(void *pTexture, void *pOpacity, float XPos, float YPos, int TextureWidth, int TextureHeight, float ScaleX, float ScaleY) {
 int dsdx=1024,dtdy; int xl,yl,xh,yh;
 if(ScaleX!=0.0f) dsdx=dsdx/ScaleX;
 dtdy=1024;
 if(ScaleY!=0.0f) dtdy=dtdy/ScaleY;
 xl=XPos*g_maskedImageTextureCoordinateScale; xh=(XPos+TextureWidth*ScaleX)*g_maskedImageTextureCoordinateScale;
 yl=YPos*g_maskedImageTextureCoordinateScale; yh=(YPos+TextureHeight*ScaleY)*g_maskedImageTextureCoordinateScale;

    { gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_16b, 1, (u32)pOpacity); gDPSetTile(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 256, G_TX_LOADTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0); gDPLoadSync(g_displayListCursor++); gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((((TextureWidth*TextureHeight+3)>>2)-1))), (u32)((((1<<11)+(1>(TextureWidth/16)?1:(TextureWidth/16))-1)/(1>(TextureWidth/16)?1:(TextureWidth/16))))); gDPPipeSync(g_displayListCursor++); gDPSetTile(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_4b, (u32)(((((TextureWidth>>1)+7)>>3))), 256, G_TX_RENDERTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0); gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, (u32)(((TextureWidth-1)<<2)), (u32)(((TextureHeight-1)<<2))); }
    { gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, (u32)pTexture); gDPSetTile(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0); gDPLoadSync(g_displayListCursor++); gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((TextureWidth*TextureHeight-1))), (u32)((((1<<11)+(1>(TextureWidth*2/8)?1:(TextureWidth*2/8))-1)/(1>(TextureWidth*2/8)?1:(TextureWidth*2/8))))); gDPPipeSync(g_displayListCursor++); gDPSetTile(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, (u32)((((TextureWidth*2)+7)>>3)), 0, G_TX_RENDERTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0); gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, (u32)(((TextureWidth-1)<<2)), (u32)(((TextureHeight-1)<<2))); }
    gDPSetTile(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_4b, (u32)((TextureWidth/16)), 256, 1, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0);
    gDPSetTileSize(g_displayListCursor++, 1, 0, 0, (u32)(((TextureWidth-1)<<2)), (u32)(((TextureHeight-1)<<2)));
    { Gfx *_g = (Gfx *)(g_displayListCursor++); _g->words.w0 = (_SHIFTL(G_TEXRECT,24,8) | _SHIFTL((s16)xh > 0 ? (s16)xh : 0,12,12) | _SHIFTL((s16)yh > 0 ? (s16)yh : 0,0,12)); _g->words.w1 = (_SHIFTL(G_TX_RENDERTILE,24,3) | _SHIFTL((s16)xl > 0 ? (s16)xl : 0,12,12) | _SHIFTL((s16)yl > 0 ? (s16)yl : 0,0,12)); };
    { Gfx *_g = (Gfx *)(g_displayListCursor++); _g->words.w0 = (_SHIFTL(G_RDPHALF_1,24,8)); _g->words.w1 = ((unsigned int)((((u32)((((short)xl<0 ? ((short)dsdx<0 ? -(((((short)xl*(short)dsdx)>>7))>((0))?((((short)xl*(short)dsdx)>>7)):((0))) : -(((((short)xl*(short)dsdx)>>7))<((0))?((((short)xl*(short)dsdx)>>7)):((0)))) : 0))) & 0xFFFF) << ((16)))
      | (((u32)(((yl<0 ? ((short)dtdy<0 ? -(((((short)yl*(short)dtdy)>>7))>((0))?((((short)yl*(short)dtdy)>>7)):((0))) : -(((((short)yl*(short)dtdy)>>7))<((0))?((((short)yl*(short)dtdy)>>7)):((0)))) : 0))) & 0xFFFF) << ((0))))); };
    { Gfx *_g = (Gfx *)(g_displayListCursor++); _g->words.w0 = (_SHIFTL(G_RDPHALF_2,24,8)); _g->words.w1 = ((unsigned int)((((u32)((dsdx)) & 0xFFFF) << ((16)))|(((u32)((dtdy)) & 0xFFFF) << ((0))))); };
}

/* Appends display-list commands to g_displayListCursor_SimpleDrawcachedmodel that load a 4-bit texture block of the given size and draw it as a texture rectangle at the given position. */
void OnScreen_DrawIntensityTexture(void *pTexture, int XPos, int YPos, int TextureWidth, int TextureHeight) {
    { gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_16b, 1, (u32)pTexture); gDPSetTile(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 256, G_TX_LOADTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0); gDPLoadSync(g_displayListCursor++); gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((((TextureWidth*TextureHeight+3)>>2)-1))), (u32)((((1<<11)+(1>(TextureWidth/16)?1:(TextureWidth/16))-1)/(1>(TextureWidth/16)?1:(TextureWidth/16))))); gDPPipeSync(g_displayListCursor++); gDPSetTile(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_4b, (u32)(((((TextureWidth>>1)+7)>>3))), 256, G_TX_RENDERTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0); gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, (u32)(((TextureWidth-1)<<2)), (u32)(((TextureHeight-1)<<2))); }
    { Gfx *g=g_displayListCursor++; { Gfx *_g = (Gfx *)(g); _g->words.w0 = (_SHIFTL(G_TEXRECT,24,8) | _SHIFTL((XPos+TextureWidth)<<2,12,12) | _SHIFTL((YPos+TextureHeight)<<2,0,12)); _g->words.w1 = (_SHIFTL(0,24,3) | _SHIFTL(XPos<<2,12,12) | _SHIFTL(YPos<<2,0,12)); }; { Gfx *_g = (Gfx *)(g_displayListCursor++); _g->words.w0 = (_SHIFTL(G_RDPHALF_1,24,8)); _g->words.w1 = ((unsigned int)(0)); }; { Gfx *_g = (Gfx *)(g_displayListCursor++); _g->words.w0 = (_SHIFTL(G_RDPHALF_2,24,8)); _g->words.w1 = ((unsigned int)((((u32)((1<<10)) & 0xFFFF) << ((16)))|(((u32)((1<<10)) & 0xFFFF) << ((0))))); }; }
}

/* Appends display-list commands to g_displayListCursor_SimpleDrawcachedmodel that load a 4-bit texture block of the given size and draw it as a texture rectangle at a floating-point position, stretched by the given horizontal and vertical scales with the texture steps divided by them. */
void OnScreen_DrawScaledIntensityTexture(void *pTexture, f32 XPos, f32 YPos, int TextureWidth, int TextureHeight, f32 ScaleX, f32 ScaleY) {
    int dsdx;
    int dtdy;
    int xl, yl, xh, yh;

    dsdx = 1 << 10;
    if (ScaleX != 0.0f) {
        dsdx = dsdx / ScaleX;
    }
    dtdy = 1 << 10;
    if (ScaleY != 0.0f) {
        dtdy = dtdy / ScaleY;
    }
    xl = XPos * g_maskedImageRectangleCoordinateScale;
    xh = (XPos + TextureWidth * ScaleX) * g_maskedImageRectangleCoordinateScale;
    yl = YPos * g_maskedImageRectangleCoordinateScale;
    yh = (YPos + TextureHeight * ScaleY) * g_maskedImageRectangleCoordinateScale;
    { gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_16b, 1, (u32)pTexture); gDPSetTile(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 256, G_TX_LOADTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0); gDPLoadSync(g_displayListCursor++); gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((((TextureWidth*TextureHeight+3)>>2)-1))), (u32)((((1<<11)+(1>(TextureWidth/16)?1:(TextureWidth/16))-1)/(1>(TextureWidth/16)?1:(TextureWidth/16))))); gDPPipeSync(g_displayListCursor++); gDPSetTile(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_4b, (u32)(((((TextureWidth>>1)+7)>>3))), 256, G_TX_RENDERTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0); gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, (u32)(((TextureWidth-1)<<2)), (u32)(((TextureHeight-1)<<2))); }
    { Gfx *g=g_displayListCursor++; { Gfx *_g = (Gfx *)(g); _g->words.w0 = (_SHIFTL(G_TEXRECT,24,8) | _SHIFTL(xh,12,12) | _SHIFTL(yh,0,12)); _g->words.w1 = (_SHIFTL(0,24,3) | _SHIFTL(xl,12,12) | _SHIFTL(yl,0,12)); }; { Gfx *_g = (Gfx *)(g_displayListCursor++); _g->words.w0 = (_SHIFTL(G_RDPHALF_1,24,8)); _g->words.w1 = ((unsigned int)(0)); }; { Gfx *_g = (Gfx *)(g_displayListCursor++); _g->words.w0 = (_SHIFTL(G_RDPHALF_2,24,8)); _g->words.w1 = ((unsigned int)((((u32)((dsdx)) & 0xFFFF) << ((16)))|(((u32)((dtdy)) & 0xFFFF) << ((0))))); }; }
}

extern const float g_maskedImageTextureCoordinateScale;

void Text_DrawTileGrid(void *handle, s32 index, s32 initialX, s16 initialY, f32 scaleX, f32 scaleY, s32 scaled) {
    void *resource;
    u8 intensity;
    TextureTileGrid *grid;
    gDPPipeSync(g_displayListCursor++);
    if(handle != NULL) {
        OnScreen_GetImageEntry(handle,index,&resource,&intensity);
        grid=resource;
        if(grid != NULL) {
            if(intensity != 0) {
                if(scaled != 0) {
                    TextureTileGrid *branchGrid=grid;
                    TextureTileBlock *tile;
                    u32 width, height;
                    f32 x, y, column, row, startX;
                    y=(f32)initialY;
                    tile=(TextureTileBlock *)branchGrid->blocks;
                    height=0;
                    row=(f32)branchGrid->rows;
                    startX=(f32)(s16)initialX;
                    while(row-- != 0.0f) {
                        column=(f32)branchGrid->columns;
                        x=startX;
                        while(column-- != 0.0f) {
                            height=tile->height;
                            width=tile->width;
                            OnScreen_DrawScaledIntensityTexture(tile->pixels,x,y,width,height,scaleX,scaleY);
                            x+=(f32)width*scaleX;
                            TILE_GRID_ADVANCE(TextureTileBlock *, tile, TILE_BYTES_4BPP(width * height));
                            tile++;
                        }
                        y+=(f32)height*scaleY;
                    }
                }
                else {
                    TextureTileGrid *branchGrid=grid;
                    TextureTileBlock *tile;
                    u32 width,height;
                    s32 x,column,row;
                    s16 y;
                    y=initialY;
                    tile=(TextureTileBlock *)branchGrid->blocks;
                    height=0;
                    row=branchGrid->rows;
                    row--;
                    while(row != -1) {
                        column=branchGrid->columns;
                        column--;
                        x=(s16)initialX;
                        while(column != -1) {
                            width=tile->width;
                            height=tile->height;
                            OnScreen_DrawIntensityTexture(tile->pixels,x,y,width,height);
                            x+=width;
                            TILE_GRID_ADVANCE(TextureTileBlock *, tile, TILE_BYTES_4BPP(width * height));
                            tile++;
                            --column;
                        }
                        y=(s16)(y+height);
                        --row;
                    }
                }
            }
            else {
                if(scaled != 0) {
                    TextureTileGrid *branchGrid=grid;
                    TextureTileBlock *tile;
                    u32 width, height;
                    f32 x, y, column, row, startX;
                    y=(f32)initialY;
                    tile=(TextureTileBlock *)branchGrid->blocks;
                    height=0;
                    row=(f32)branchGrid->rows;
                    startX=(f32)(s16)initialX;
                    while(row-- != 0.0f) {
                        column=(f32)branchGrid->columns;
                        x=startX;
                        while(column-- != 0.0f) {
                            height=tile->height;
                            width=tile->width;
                            OnScreen_DrawScaledMaskedImage(tile->pixels,tile->pixels+width*height*2,x,y,width,height,scaleX,scaleY);
                            x+=(f32)width*scaleX;
                            TILE_GRID_ADVANCE(TextureTileBlock *, tile, TILE_BYTES_16BPP_PLUS_4BPP(width * height));
                            tile++;
                        }
                        y+=(f32)height*scaleY;
                    }
                }
                else {
                    TextureTileGrid *branchGrid=grid;
                    TextureTileBlock *tile;
                    u32 width,height;
                    s32 x,column,row;
                    s16 y;
                    y=initialY;
                    tile=(TextureTileBlock *)branchGrid->blocks;
                    height=0;
                    row=branchGrid->rows;
                    row--;
                    while(row != -1) {
                        column=branchGrid->columns;
                        column--;
                        x=(s16)initialX;
                        while(column != -1) {
                            width=tile->width;
                            height=tile->height;
                            OnScreen_DrawTextureWithOpacity(tile->pixels,tile->pixels+width*height*2,x,y,width,height);
                            x+=width;
                            TILE_GRID_ADVANCE(TextureTileBlock *, tile, TILE_BYTES_16BPP_PLUS_4BPP(width * height));
                            tile++;
                            --column;
                        }
                        y=(s16)(y+height);
                        --row;
                    }
                }
            }
            Cache_MarkResourceInUse(0,handle);
        }
    }
}



void OnScreen_InitMover(void *moverStorage, s16 x, s16 y)
{
  COverlay *mover = moverStorage;
  mover->handle = -1;
  mover->active = 0;
  mover->state = 0;
  mover->x = (f32) x;
  mover->y = (f32) y;
}

/* Points the widget at a mover script, marks it as running (state 2) and applies the first step. */
void OnScreen_StartMoverScript(void *widget, s32 *script) {
    ((COverlay *)widget)->script = script;
    ((COverlay *)widget)->state = 2;
    OnScreen_UpdateMoverScript(widget);
}

void OnScreen_StartFirstStatusBar(Hud *hud, s32 owner, s32 target) {
    hud->bars[0].enabled = owner;
    hud->bars[0].label = (void *)target;
    hud->bars[0].target = 100;
    OnScreen_StartMoverScript(&hud->bars[0].mover, &g_firstStatusBarMoverScript);
}

void OnScreen_StartSecondStatusBar(Hud *hud, s32 owner, s32 target) {
    hud->bars[1].enabled = owner;
    hud->bars[1].label = (void *)target;
    hud->bars[1].target = 100;
    OnScreen_StartMoverScript(&hud->bars[1].mover, &g_secondStatusBarMoverScript);
}

void OnScreen_SetFirstBarTarget(char *object, int value) {
    Hud *hud = (void *)object;
    hud->bars[0].target = value;
}

void OnScreen_SetSecondBarTarget(void *object, int value) {
    Hud *hud = (void *)object;
    hud->bars[1].target = value;
}

void OnScreen_DrawStatusBars(void *playerHud) {
    char pad[256];
    (void)pad;

    if (Tsmos_IsFrontendActive() == 1) {
        Tsmos_UpdateFrontend();
        Geometry_InvalidateMaterialKeys();
        TextLoad_ResetTextureCache();
    }
    OnScreen_SetupTextRendering();
    OnScreen_LoadTextTileModeOne();
    OnScreen_SetTextScale(g_hudStatusBarTextScale, g_hudStatusBarTextScale);
    OnScreen_SetTextColors(0xFF, 0xFF, 0xFF, 200, 200, 200);
    Onscrn_SetupSpriteMode(g_gameSettings.hudFade);
    if (((Hud *)playerHud)->bars[0].enabled != 0) {
        OnScreen_DrawStatusBar(playerHud, 1);
    }
    if (((Hud *)playerHud)->bars[1].enabled != 0) {
        OnScreen_DrawStatusBar(playerHud, 2);
    }
}

/* Width of one glyph for the current credits text drawing mode (0 to 6); any other mode gives 1. */
f32 OnScreen_GetGlyphWidth(void) {
    switch (g_creditsTextDrawingEnabled) {
    case 0:
        return 24.0f;
    case 1:
        return 12.0f;
    case 2:
    case 6:
        return 8.0f;
    case 3:
        return 6.0f;
    case 4:
    case 5:
        return 16.0f;
    default:
        return 1.0f;
    }
}

void OnScreen_GetImageEntry(LoadedImageTable **handle, s32 index, void **out, u8 *tag) {
    LoadedImageTable *table;
    ImageTableEntry *entry;

    *out = 0;
    if (handle != 0) {
        table = *handle;
        entry = &table->entries[index % table->count];
        *tag = entry->tag[0];
        *out = (u8 *)table + entry->offset;
    }
}

#if defined(VERSION_EU_X)
void OnScreen_GetImageDimensions(s32 resourceId, s32 frameIndex, s32 *widthOutput, s32 *heightOutput)
{
  void *imageEntry;
  s32 entryTag;
  void *imageData;
  s32 resourceHandle;
  if (g_screenImageResourcesEnabled != 0)
  {
    resourceHandle = Scene_StartWorldEffect(&g_world, resourceId, 0, 1);
    if (resourceHandle != 0)
    {
void OnScreen_GetImageEntry(LoadedImageTable **handle, s32 index, void **out, u8 *tag);
      imageData = imageEntry;
      *widthOutput = ((ImageSet *)imageEntry)->width;
      *heightOutput = ((ImageSet *)imageData)->height;
      Cache_UnlockResource(0, resourceHandle);
    }
  }
}
#endif

#if defined(VERSION_EU_X)
void OnScreen_SetupFillMode(void) {

    Gfx *gfx;

    gfx = g_displayListCursor++;
    gDPPipeSync(gfx);
    gfx = g_displayListCursor++;
    gDPSetCycleType(gfx, G_CYC_1CYCLE);
    Geometry_SetModePreset(21);
    Geometry_SetCombineMode(25);
}
#endif

#if defined(VERSION_EU_X)
void OnScreen_FillRectangle(s32 x0,s32 y0,s32 x1,s32 y1,u8 r,u8 g,u8 b,u8 a) {

 gDPPipeSync(g_displayListCursor++);
 gDPSetPrimColor(g_displayListCursor++, 255, 255, r, g, b, a);
 gDPFillRectangle(g_displayListCursor++, ((x0))>((0))?((x0)):((0)), ((y0))>((0))?((y0)):((0)), ((x1))>((0))?((x1)):((0)), ((y1))>((0))?((y1)):((0)));
}
#endif

#if defined(VERSION_EU_X)

void OnScreen_SetTextColors(int topRed, int topGreen, int topBlue, int alpha, int bottomGreen, int bottomBlue) {
    g_gameSession.hud.envR = topRed;
    g_gameSession.hud.envG = topGreen;
    g_gameSession.hud.envB = topBlue;
    g_gameSession.hud.primR = alpha;
    g_gameSession.hud.primG = bottomGreen;
    g_gameSession.hud.primB = bottomBlue;
}
#endif

#if defined(VERSION_EU_X)
void OnScreen_SetTextScale(float scaleX, float scaleY) {
    g_gameSession.hud.width = scaleX;
    g_gameSession.hud.height = scaleY;
}
#endif

#if defined(VERSION_EU_X)
void OnScreen_DrawTextWithShadow(u8 *text, f32 x, f32 y, f32 scaleX, f32 scaleY, s32 drawShadow, s32 alpha, s32 textFlags) {
    if (drawShadow != 0) {
        OnScreen_DrawTextGlyphs(text, x, y, scaleX, scaleY, 1, alpha, textFlags);
    }
    OnScreen_DrawTextGlyphs(text, x, y, scaleX, scaleY, 0, alpha, textFlags);
}
#endif

#if !(defined(VERSION_EU_X))

/* Emits pipe sync, primitive color and a rectangle with nonnegative coordinates. */
void OnScreen_GetImageDimensions(s32 resourceId, s32 frameIndex, s32 *outWidth, s32 *outHeight)
{
  void *image;
  s32 imageTag;
  void *imageResource;
  s32 resourceHandle;
  if (g_screenImageResourcesEnabled != 0)
  {
    resourceHandle = Scene_StartWorldEffect(&g_world, resourceId, 0, 1);
    if (resourceHandle != 0)
    {
      OnScreen_GetImageEntry(resourceHandle, frameIndex, &image, &imageTag);
      imageResource = image;
      *outWidth = ((ImageSet *)image)->width;
      *outHeight = ((ImageSet *)imageResource)->height;
      Cache_UnlockResource(0, resourceHandle);
    }
  }
}

void OnScreen_SetupFillMode(void) {

    Gfx *gfx;

    gfx = g_displayListCursor++;
    gDPPipeSync(gfx);
    gfx = g_displayListCursor++;
    gDPSetCycleType(gfx, G_CYC_1CYCLE);
    Geometry_SetModePreset(21);
    Geometry_SetCombineMode(25);
}

void OnScreen_FillRectangle(s32 x0,s32 y0,s32 x1,s32 y1,u8 r,u8 g,u8 b,u8 a) {

 gDPPipeSync(g_displayListCursor++);
 gDPSetPrimColor(g_displayListCursor++, 255, 255, r, g, b, a);
 gDPFillRectangle(g_displayListCursor++, ((x0))>((0))?((x0)):((0)), ((y0))>((0))?((y0)):((0)), ((x1))>((0))?((x1)):((0)), ((y1))>((0))?((y1)):((0)));
}

/** Store six words into the global record. */
void OnScreen_SetTextColors(int environmentRed, int environmentGreen, int environmentBlue, int primitiveRed, int primitiveGreen, int primitiveBlue) {
    g_gameSession.hud.envR = environmentRed;
    g_gameSession.hud.envG = environmentGreen;
    g_gameSession.hud.envB = environmentBlue;
    g_gameSession.hud.primR = primitiveRed;
    g_gameSession.hud.primG = primitiveGreen;
    g_gameSession.hud.primB = primitiveBlue;
}

void OnScreen_SetTextScale(float horizontalScale, float verticalScale) {
    g_gameSession.hud.width = horizontalScale;
    g_gameSession.hud.height = verticalScale;
}

void OnScreen_DrawTextWithShadow(u8 *text, f32 x, f32 y, f32 width, f32 height, s32 drawShadow, s32 alpha, s32 language) {
    if (drawShadow != 0) {
        OnScreen_DrawTextGlyphs(text, x, y, width, height, 1, alpha, language);
    }
    OnScreen_DrawTextGlyphs(text, x, y, width, height, 0, alpha, language);
}

#endif

s32 OnScreen_DrawSpriteResource(s32 resourceId, s32 index, s16 x, s16 y, f32 scaleX, f32 scaleY, s32 scaled) {

    s32 resourceHandle;

    if ((u32)(g_primaryDisplayListCapacity - (((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) >> 3)) < 1000
        || g_screenImageResourcesEnabled == 0
        || (resourceHandle = Scene_StartWorldEffect(&g_world, resourceId, 0, 1), resourceHandle == 0)) {
        return 0;
    }
    Text_DrawTileGrid(resourceHandle, index, x, y, scaleX, scaleY, scaled);
    Cache_UnlockResource(0, resourceHandle);
    return 1;
}

extern u8 g_onScreenFontTextureStorage[144];

void OnScreen_LoadFontTexture(void) {
    LoadedImageTable **handle;
    LoadedImageTable *table;
    ImageTableEntry *entry;
    ResourceView view;
    u8 entryTag;
    s32 remainder;
    void *result;
    void *base;
    g_onScreenFontTexture = 0;
    handle = Scene_StartWorldEffect(&g_world, 2, 0, 1);
    if (handle != 0) {
        table = *handle;
        view.data = 0;
        entry = &table->entries[0];
        remainder = 0 % table->count;
        entry += remainder;
        base = table;
        result = base + entry->offset;
        entryTag = entry->tag[0];
        view.type = entryTag;
        view.data = result;
        if (view.data != 0) {
            view.data += 0x10;
        }
        Libc_CopyBytes(g_onScreenFontTextureStorage, view.data, 144);
        Cache_UnlockResource(0, handle);
        g_onScreenFontTexture = g_onScreenFontTextureStorage;
    }
}

/** Return the global word at g_onScreenFontTexture. */
u8 *OnScreen_GetFontTexture(void) {
    return g_onScreenFontTexture;
}

/* Draws a grid of 16-bit image tiles with a 4-bit mask: the header holds the column and row counts,
   each tile holds its width, height, two bytes per pixel and then half a byte per pixel of mask,
   and every tile goes to OnScreen_DrawTextureWithOpacity at the running position, advancing x by the tile width and
   y by the last tile height per row. */
void OnScreen_DrawMaskedTileGrid(u16 *grid, s16 x0, s32 y) {
    s32 *tile;
    s32 rows;
    s32 cols;
    s32 x;
    s32 w;
    s32 h;
    u32 area;

    tile = (s32 *)(grid + 4);
    h = 0;
    rows = grid[1];
    while (--rows != -1) {
        x = x0;
        cols = grid[0];
        while (--cols != -1) {
            w = tile[0];
            h = tile[1];
            area = w * h;
            OnScreen_DrawTextureWithOpacity(tile + 2, (char *)tile + (area * 2 + 8), x, y, w, h);
            x += w;
            TILE_GRID_ADVANCE(s32 *, tile, TILE_BYTES_16BPP_PLUS_4BPP(area));
            tile += 2;
        }
        y += h;
    }
}

/* Draws a grid of 16-bit image tiles with a 4-bit mask scaled by sx and sy: the header holds the column
   and row counts, each tile holds its width, height, two bytes per pixel and then half a byte per pixel
   of mask, and every tile goes to OnScreen_DrawScaledMaskedImage at the running float position, advancing x by the
   scaled tile width and y by the scaled last tile height per row. Scaled counterpart of
   OnScreen_DrawMaskedTileGrid; the float counters count down with `rows-- != 0.0f` as in Pickup_DrawScaledIntensityTileGrid. */
void OnScreen_DrawScaledMaskedTileGrid(u16 *grid, f32 x0, f32 y, f32 sx, f32 sy) {
    u32 *tile;
    f32 rows;
    f32 cols;
    f32 x;
    u32 w;
    u32 h;
    u32 area;

    tile = (u32 *)(grid + 4);
    h = 0;
    rows = grid[1];
    while (rows-- != 0.0f) {
        x = x0;
        cols = grid[0];
        while (cols-- != 0.0f) {
            w = tile[0];
            h = tile[1];
            area = w * h;
            OnScreen_DrawScaledMaskedImage(tile + 2, (char *)tile + (area * 2 + 8), x, y, w, h, sx, sy);
            x += w * sx;
            TILE_GRID_ADVANCE(u32 *, tile, TILE_BYTES_16BPP_PLUS_4BPP(area));
            tile += 2;
        }
        y += h * sy;
    }
}

/* Draws a grid of 4-bit image tiles: the header holds the column and row counts, each tile holds
   its width, height and packed nibble data, and every tile goes to OnScreen_DrawIntensityTexture at the running
   position, advancing x by the tile width and y by the last tile height per row. */
void Pickup_DrawIntensityTileGrid(u16 *grid, s16 x0, s32 y) {
    s32 *tile;
    s32 rows;
    s32 cols;
    s32 x;
    s32 w;
    s32 h;

    tile = (s32 *)(grid + 4);
    h = 0;
    rows = grid[1];
    while (--rows != -1) {
        x = x0;
        cols = grid[0];
        while (--cols != -1) {
            w = tile[0];
            h = tile[1];
            OnScreen_DrawIntensityTexture(tile + 2, x, y, w, h);
            x += w;
            TILE_GRID_ADVANCE(s32 *, tile, TILE_BYTES_4BPP((u32)(w * h)));
            tile += 2;
        }
        y += h;
    }
}

/* Draws a grid of 4-bit image tiles scaled by sx and sy: the header holds the column and row
   counts, each tile holds its width, height and packed nibble data, and every tile goes to
   OnScreen_DrawScaledIntensityTexture at the running float position, advancing x by the scaled tile width and y by the
   scaled last tile height per row. Scaled counterpart of Pickup_DrawIntensityTileGrid. */
void Pickup_DrawScaledIntensityTileGrid(u16 *grid, f32 x0, f32 y, f32 sx, f32 sy) {
    u32 *tile;
    f32 rows;
    f32 cols;
    f32 x;
    u32 w;
    u32 h;

    tile = (u32 *)(grid + 4);
    h = 0;
    rows = grid[1];
    while (rows-- != 0.0f) {
        x = x0;
        cols = grid[0];
        while (cols-- != 0.0f) {
            w = tile[0];
            h = tile[1];
            OnScreen_DrawScaledIntensityTexture(tile + 2, x, y, w, h, sx, sy);
            x += w * sx;
            TILE_GRID_ADVANCE(u32 *, tile, TILE_BYTES_4BPP(w * h));
            tile += 2;
        }
        y += h * sy;
    }
}

/* Builds a 256-entry byte lookup table: every entry becomes 0xFF, then each of the count
   (key, value) byte pairs stores value at table[key]. */
void Pickup_BuildByteLookup(int hud, unsigned char *pairs, int count, unsigned char *table) {
    int i;
    unsigned char *p;
    unsigned char fill = 0xFF;

    i = 255;
    p = table + i;
    for (; i >= 0; i--) {
        *p-- = fill;
    }
    for (i = 0; i < count; i++) {
        table[pairs[0]] = pairs[1];
        pairs += 2;
    }
}

void Pickup_SetupPickupText(void) {
    char pad[256];
    (void)pad;
    OnScreen_SetupTextRendering();
    OnScreen_LoadTextTileModeOne();
    OnScreen_SetTextScale((0.699999988079071f), (0.699999988079071f));
    OnScreen_SetTextColors(0xFF, 0xFF, 0xFF, 200, 200, 200);
}

/* Draws one of the two gauges of the head-up panel, the first at hud->bars[0] and the second at
   hud->bars[1]: steps the gauge's scripted mover, walks its shown amount toward the gauge's target
   count by eight a frame up or four a frame down without passing it, fills the bar from x+80 to the
   right margin in the gauge's own colour at the options fade g_playerHudSpriteMode times 180/255, and draws the
   gauge's label at the bar's left edge. The first gauge also draws its two end caps, at the screen
   edges, unit width and one and a half times the panel scale. */
void OnScreen_DrawStatusBar(Hud *hud, s32 which) {
    Bar *bar;
    f32 scale;
    f32 wide;
    f32 target;
    f32 shift;
    s32 red;
    s32 green;
    s32 blue;
    s32 offset;
    s32 x;
    s32 y;
    s32 left;
    s32 right;
    s32 inset;
    u8 *fade;
    s32 value;

    if (Cinema_IsSequenceInWindow() != 0) {
        return;
    }
    if (SetN64_IsModeThirteen() == 0) {
        return;
    }
    wide = Frontend_GetScreenMode() == 0 ? 0.75f : 1.0f;
    scale = g_gameplayCameraList.camera->viewHeight / (f32) g_hudReferenceViewportHeight;
    scale = scale * wide;
    switch (which) {
    case 1:
        bar = &hud->bars[0];
        target = (f32) hud->bars[0].target;
        red = 29;
        green = 83;
        blue = 226;
        offset = 31;
        break;
    case 2:
        bar = &hud->bars[1];
        target = (f32) hud->bars[1].target;
        red = 139;
        green = 185;
        blue = 70;
        offset = 48;
        break;
    default:
        return;
    }
    x = (s32) bar->mover.x;
    y = (s32) (bar->mover.y + (f32) offset * scale);
    OnScreen_SetupFillMode();
    OnScreen_UpdateMoverScript(&bar->mover);
    if (bar->mover.state == 1) {
        value = bar->mover.fill;
        if ((f32) value < target) {
            value += 8;
            bar->mover.fill = value;
            if (target < (f32) value) {
                bar->mover.fill = (s32) target;
            }
        } else if (target < (f32) value) {
            value -= 4;
            bar->mover.fill = value;
            if ((f32) value < target) {
                bar->mover.fill = (s32) target;
            }
        }
    }
    left = x + 80;
    inset = x - 112;
    right = inset + g_hudReferenceViewportWidth;
    fade = &g_gameSettings.hudFade;
    OnScreen_FillRectangle(left, (s32) ((f32) y + scale * 9.0f),
                  left + ((right - left) * bar->mover.fill) / 100,
                  (s32) ((f32) y + scale * 15.0f), red, green, blue,
                  (u8) (*fade * 180 / 255));
    Onscrn_SetupSpriteMode(*fade);
    if (which == 1) {
        shift = scale * 27.0f;
        OnScreen_DrawSpriteResource(514, 0, (s16) (x + 70), (s16) (s32) (bar->mover.y + shift), 1.0f, scale * 1.5f, which);
        OnScreen_DrawSpriteResource(515, 0, (s16) (g_hudReferenceViewportWidth + x - 109), (s16) (s32) (bar->mover.y + shift), 1.0f, scale * 1.5f, which);
        OnScreen_SetupTextRendering();
        OnScreen_SetTextScale(0.4f, scale * 0.4f);
        OnScreen_SetTextColors(0xFF, 0xFF, 0xFF, 200, 200, 200);
        Onscrn_DrawText(hud->bars[0].label, left, y - 2, *fade, 0, 0, 1.0f, 1.0f);
    } else {
        OnScreen_SetupTextRendering();
        OnScreen_SetTextScale(0.4f, scale * 0.4f);
        OnScreen_SetTextColors(0xFF, 0xFF, 0xFF, 200, 200, 200);
        Onscrn_DrawText(hud->bars[1].label, left, y - 2, *fade, 0, 0, 1.0f, 1.0f);
    }
}

static inline void rectangle(s32 x0,s32 y0,s32 x1,s32 y1,s32 r,s32 g,s32 b,s32 a) {
    gDPPipeSync(g_displayListCursor++);
    gDPSetPrimColor(g_displayListCursor++,255,255,r,g,b,a);
    gDPFillRectangle(g_displayListCursor++, x0>0?x0:0,y0>0?y0:0,x1>0?x1:0,y1>0?y1:0);
}

/* Draws a signed integer of up to four digits with the font sprite set from Scene_StartWorldEffect: splits the magnitude into thousands, hundreds, tens and ones, draws a leading minus sign through OnScreen_DrawSpriteResource when negative, then draws at least minDigits digits through Text_DrawTileGrid, advancing 13 units per digit (0.7 of that for a one) scaled by the size, laid out right to left when rightAlign is set, and releases the sprite set. */
void OnScreen_UpdateMoverScript(COverlay *m) {
    s32 next;
    f32 dx;
    f32 dy;
    s32 bottom;
    s32 right;

    bottom = g_hudReferenceViewportHeight + 96;
    right = g_hudReferenceViewportWidth + 96;
    do {
        next = 0;
        switch (m->state) {
        case 0:
        case 1:
            break;
        case 2:
            if (m->script != 0) {
                switch (*m->script++) {
                case 6:
                    m->state = 0;
                    m->script = 0;
                    break;
                case 1:
                    next = 1;
                    m->x = *m->script++;
                    m->y = *m->script++;
                    break;
                case 2:
                    m->state = 3;
                    m->wait = *m->script++;
                    break;
                case 3:
                    m->active = 1;
                    m->state = 4;
                    m->targetX = *m->script++;
                    m->targetY = *m->script++;
                    m->rate = 1.0f / *m->script++;
                    break;
                case 4:
                    m->active = 1;
                    m->state = 5;
                    m->velY = 0.0f;
                    m->accelY = *m->script++ * (1.0f / 65536.0f);
                    break;
                case 5:
                    m->active = 1;
                    m->state = 6;
                    m->velX = 0.0f;
                    m->accelX = *m->script++ * (1.0f / 65536.0f);
                    break;
                default:
                    m->state = 1;
                    m->script = 0;
                    break;
                }
            } else {
                m->state = 1;
            }
            break;
        case 3:
            if (m->wait-- <= 0) {
                next = 1;
            }
            break;
        case 4:
            dx = (m->targetX - m->x) * m->rate;
            dy = (m->targetY - m->y) * m->rate;
            m->x += dx;
            m->y += dy;
            if ((dx < 0.0f ? -dx < 0.25f : dx < 0.25f) && (dy < 0.0f ? -dy < 0.25f : dy < 0.25f)) {
                m->x = m->targetX;
                m->y = m->targetY;
                next = 1;
            }
            break;
        case 5:
            m->y += m->velY;
            m->velY += m->accelY;
            if ((f32)bottom < m->y || m->y < -90.0f) {
                m->active = 0;
                next = 1;
            }
            break;
        case 6:
            m->x += m->velX;
            m->velX += m->accelX;
            if ((f32)right < m->x || m->x < -90.0f) {
                m->active = 0;
                next = 1;
            }
            break;
        }
        if (next) {
            m->state = 2;
        }
    } while (next);
}

void OnScreen_DrawBevelBox(s32 x0,s32 y0,s32 x1,s32 y1,s32 border,s32 invert,s32 red,s32 green,s32 blue,s32 alpha) {
    u8 r=red,g=green,b=blue,a=alpha;
    s32 lightR,lightG,lightB,darkR,darkG,darkB;
    lightR=invert ? r>>1 : r<<1;
    lightG=invert ? g>>1 : g<<1;
    lightB=invert ? b>>1 : b<<1;
    darkR=invert ? r<<1 : r>>1;
    darkG=invert ? g<<1 : g>>1;
    darkB=invert ? b<<1 : b>>1;
    rectangle(x0,y0,x1,y1,r,g,b,a);
    rectangle(x0,y0,x1,y0+border,lightR,lightG,lightB,a);
    rectangle(x1-border,y0,x1,y1,lightR,lightG,lightB,a);
    rectangle(x0,y1-border,x1,y1,darkR,darkG,darkB,a);
    rectangle(x0,y0,x0+border,y1,darkR,darkG,darkB,a);
}

void OnScreen_DrawSpriteNumber(s32 value, f32 x, f32 y, f32 size, f32 scaleY, s32 scaled, s32 rightAlign, s32 minDigits) {
    s32 sprites;
    s32 negative;
    s32 thousands;
    s32 hundreds;
    s32 tens;
    s32 ones;
    s32 rest;
    s32 last;
    s32 i;
    s32 place;
    s32 digit;
    f32 width;
    f32 scale;

    sprites = Scene_StartWorldEffect(&g_world, 4, 16, 1);
    if (sprites == 0) {
        return;
    }
    negative = 0;
    if (value < 0) {
        value = -value;
        negative = 1;
    }
    if (value >= 0) {
        thousands = value * 0.001f;
        rest = value - thousands * 1000;
        hundreds = rest * 0.01f;
        rest -= hundreds * 100;
        tens = rest * 0.1f;
        ones = rest - tens * 10;
        last = 3;
        if (thousands == 0) {
            last = 2;
            if (hundreds == 0) {
                last = tens != 0;
            }
        }
        if (last < minDigits - 1) {
            last = minDigits - 1;
        }
        if (negative) {
            OnScreen_DrawSpriteResource(4, 10, x, y, size, scaleY, scaled);
            x += size * 13.0f;
        }
        for (i = last; i >= 0; i--) {
            place = i;
            if (rightAlign) {
                place = last - i;
            }
            switch (place) {
            case 3:
                digit = thousands;
                break;
            case 2:
                digit = hundreds;
                break;
            case 1:
                digit = tens;
                break;
            case 0:
            default:
                digit = ones;
                break;
            }
            scale = 1.0f;
            if (digit == 1) {
                scale = 0.7f;
            }
            width = scale * (size * 13.0f);
            if (rightAlign) {
                x -= width;
            }
            if ((u32)digit < 10) {
                Text_DrawTileGrid(sprites, digit, x, y, size, scaleY, scaled);
            }
            if (!rightAlign) {
                x += width;
            }
        }
    }
    Cache_UnlockResource(0, (struct CacheResourceNode *)sprites);
}

void OnScreen_SetupTextRendering(void) {
    u8 *texture;

    texture = OnScreen_GetFontTexture();
    if (texture != 0) {

        {
            Gfx *cmd;
            cmd = g_displayListCursor++;
            gDPPipeSync(cmd);
            cmd = g_displayListCursor++;
            gDPSetCycleType(cmd, G_CYC_2CYCLE);
        }

        Geometry_SetCombineMode(26);
        Geometry_SetModePreset(21);

        g_creditsTextDrawingEnabled = 0;
        {
        Gfx *cmd;
        cmd = g_displayListCursor++;
        gSPTexture(cmd, 32768, 32768, 0, 0, G_ON);
        cmd = g_displayListCursor++;
        gDPSetTextureLUT(cmd, G_TT_NONE);
        cmd = g_displayListCursor++;
        gDPSetTexturePersp(cmd, G_TP_NONE);
        cmd = g_displayListCursor++;
        gDPSetTextureFilter(cmd, G_TF_BILERP);
        cmd = g_displayListCursor++;
        gDPSetTextureImage(cmd, G_IM_FMT_I, G_IM_SIZ_16b, 1, texture);
        cmd = g_displayListCursor++;
        gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0);
        cmd = g_displayListCursor++;
        gDPLoadSync(cmd);
        cmd = g_displayListCursor++;
        gDPLoadBlock(cmd, G_TX_LOADTILE, 0, 0, 143, 2048);
        cmd = g_displayListCursor++;
        gDPPipeSync(cmd);
        cmd = g_displayListCursor++;
        gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0);
        cmd = g_displayListCursor++;
        gDPSetTileSize(cmd, G_TX_RENDERTILE, 0, 0, 92, 92);
        cmd = g_displayListCursor++;
        gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_4b, 0, 0, 1, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0);
        cmd = g_displayListCursor++;
        gDPSetTileSize(cmd, 1, 0, 0, 60, 60);
        }

        OnScreen_SetTextColors(140, 140, 140, 140, 140, 140);
        OnScreen_SetTextScale(g_onscreenDefaultTextScale, g_onscreenDefaultTextScale);
        g_gameSession.hud.shadowX = 2;
        g_gameSession.hud.shadowY = 2;
    }
}

void OnScreen_LoadTextTileModeOne(void) {
    Gfx *cmd;
    u8 *fontTexture;

    fontTexture = OnScreen_GetFontTexture();
    if (fontTexture != 0) {
        g_creditsTextDrawingEnabled = 1;
        cmd = g_displayListCursor++;
        gDPSetTextureImage(cmd, G_IM_FMT_I, G_IM_SIZ_16b, 1, fontTexture);
        cmd = g_displayListCursor++;
        gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_16b, 0, 256, G_TX_LOADTILE, 0, G_TX_WRAP, 3, 0, G_TX_WRAP, 4, 0);
        cmd = g_displayListCursor++;
        gDPLoadSync(cmd);
        cmd = g_displayListCursor++;
        gDPLoadBlock(cmd, G_TX_LOADTILE, 0, 0, 31, 2048);
        cmd = g_displayListCursor++;
        gDPPipeSync(cmd);
        cmd = g_displayListCursor++;
        gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_4b, 1, 256, G_TX_RENDERTILE, 0, G_TX_WRAP, 3, 0, G_TX_WRAP, 4, 0);
        cmd = g_displayListCursor++;
        gDPSetTileSize(cmd, G_TX_RENDERTILE, 0, 0, 60, 28);
    }
}

void OnScreen_LoadTextTileModeTwo(void) {
    Gfx *cmd;
    u8 *fontTexture;

    fontTexture = OnScreen_GetFontTexture();
    if (fontTexture != 0) {
        g_creditsTextDrawingEnabled = 2;
        cmd = g_displayListCursor++;
        gDPSetTextureImage(cmd, G_IM_FMT_I, G_IM_SIZ_16b, 1, fontTexture);
        cmd = g_displayListCursor++;
        gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_16b, 0, 256, G_TX_LOADTILE, 0, G_TX_WRAP, 3, 0, G_TX_WRAP, 4, 0);
        cmd = g_displayListCursor++;
        gDPLoadSync(cmd);
        cmd = g_displayListCursor++;
        gDPLoadBlock(cmd, G_TX_LOADTILE, 0, 0, 31, 2048);
        cmd = g_displayListCursor++;
        gDPPipeSync(cmd);
        cmd = g_displayListCursor++;
        gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_4b, 1, 256, G_TX_RENDERTILE, 0, G_TX_WRAP, 3, 0, G_TX_WRAP, 4, 0);
        cmd = g_displayListCursor++;
        gDPSetTileSize(cmd, G_TX_RENDERTILE, 0, 0, 60, 28);
    }
}



#if defined(VERSION_US_REV1)
unsigned char * g_onScreenFontTexture = 0;
#endif

#if defined(VERSION_EU)
/* Older build's code pointer: offsets of its code, relocated at load. */
void *g_onscreenCodePointer[1] = { (void *)0x00294149 };
#endif

/* Retained data for this translation unit. */

const float g_OnScreen_DrawStatusBarsConstantWords[1] = {
    0.7f,
};

const float k_intensityTextureScale[1] = {
    4.0f,
};

const float g_maskedImageTextureCoordinateScale = 4.0f;
