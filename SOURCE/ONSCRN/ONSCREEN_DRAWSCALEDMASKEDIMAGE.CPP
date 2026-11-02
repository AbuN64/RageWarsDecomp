#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include "include_asm.h"
#include "COMMON/FONT_STYLE_AND_GLYPH_OPERATIONS.H"
#include "ONSCRN.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/gbi.h>
#include <PR/abi.h>

/* 802A8A94_3.CPP */
/* Draws a text string in the current font style g_tutorialStatusBars: when centring, measures it through Menu_MeasureLine at the style size scaled by the language-dependent factors for g_creditsTextDrawingEnabled, shrinks the scale so it fits 44 pixels inside the screen width g_hudReferenceViewportWidth and shifts x left by half the width; then sets the environment colour from the style with the given alpha and the primitive colour from the style, and draws the string through OnScreen_DrawTextGlyphs, first as a shadow when requested. */

extern Gfx *g_displayListCursor;
extern f32 Menu_MeasureLine(u8 *text, f32 size, f32 spacing);

void Onscrn_DrawText(void * text, s32 x, s32 y, s32 alpha, s32 centred, s32 shadow, f32 scaleX, f32 scaleY) {
    FontStyle *style;
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

    style = &g_tutorialStatusBars;
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

extern void Geometry_SetCombineMode(u32 mode);
extern s32 Geometry_SetModePreset(s32 tailEnum);

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

/* Appends display-list commands to g_displayListCursor_SimpleDrawcachedmodel that load a 4-bit texture block of the given size and draw it as a texture rectangle at the given position. Adapted from OnScreen_DrawTextureWithOpacity with the palette block and the second texture block removed and its first block's image pointer taken from the texture argument. */

void OnScreen_DrawIntensityTexture(void *pTexture, int XPos, int YPos, int TextureWidth, int TextureHeight) {
    { gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_16b, 1, (u32)pTexture); gDPSetTile(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 256, G_TX_LOADTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0); gDPLoadSync(g_displayListCursor++); gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((((TextureWidth*TextureHeight+3)>>2)-1))), (u32)((((1<<11)+(1>(TextureWidth/16)?1:(TextureWidth/16))-1)/(1>(TextureWidth/16)?1:(TextureWidth/16))))); gDPPipeSync(g_displayListCursor++); gDPSetTile(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_4b, (u32)(((((TextureWidth>>1)+7)>>3))), 256, G_TX_RENDERTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0); gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, (u32)(((TextureWidth-1)<<2)), (u32)(((TextureHeight-1)<<2))); }
    { Gfx *g=g_displayListCursor++; { Gfx *_g = (Gfx *)(g); _g->words.w0 = (_SHIFTL(G_TEXRECT,24,8) | _SHIFTL((XPos+TextureWidth)<<2,12,12) | _SHIFTL((YPos+TextureHeight)<<2,0,12)); _g->words.w1 = (_SHIFTL(0,24,3) | _SHIFTL(XPos<<2,12,12) | _SHIFTL(YPos<<2,0,12)); }; { Gfx *_g = (Gfx *)(g_displayListCursor++); _g->words.w0 = (_SHIFTL(G_RDPHALF_1,24,8)); _g->words.w1 = ((unsigned int)(0)); }; { Gfx *_g = (Gfx *)(g_displayListCursor++); _g->words.w0 = (_SHIFTL(G_RDPHALF_2,24,8)); _g->words.w1 = ((unsigned int)((((u32)((1<<10)) & 0xFFFF) << ((16)))|(((u32)((1<<10)) & 0xFFFF) << ((0))))); }; }
}

/* Appends display-list commands to g_displayListCursor_SimpleDrawcachedmodel that load a 4-bit texture block of the given size and draw it as a texture rectangle at a floating-point position, stretched by the given horizontal and vertical scales with the texture steps divided by them. Adapted from OnScreen_DrawIntensityTexture with the position made floating point, the rectangle corners scaled by g_maskedImageRectangleCoordinateScale and the scale factors applied to the extent and the texture step. */

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

/* 802A8A94_7.CPP */
/* ROM-grounded data: src/g_maskedImageTextureCoordinateScaleWordsUsRev1_OnscreenDrawscaledmaskedimage.c */
const float g_maskedImageTextureCoordinateScaleWordsUsRev1[1] = {
    4.0f,
};
