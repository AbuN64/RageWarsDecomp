#include "COMMON/TEXTURE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "TYPES.H"
#include "MENU/GFX/RECT.H"
#include "COMMON/RECTANGLE_DRAW.H"
#include "include_asm.h"
#include <PR/abi.h>

extern Gfx *g_displayListCursor;

extern void Combine_SetRenderMode(s32 mode);

extern void Combine_SetCombineMode(s32 mode);

extern void Combine_SetPrimitiveVertexMode(s32 mode);

extern int g_combineRenderStateEnabled, g_combineCachedCombineMode, g_combineCachedPrimitiveMode, g_combineCachedRenderMode;

extern int g_combineCachedStateWord, g_combineLoadedPalette;

/* RECT.CPP */
static inline void sync(void) {
    Gfx *cmd;

    if (g_combinePipelineSyncPending == 0) {
        g_combinePipelineSyncPending = 1;
        cmd = g_displayListCursor++;
        gDPPipeSync(cmd);
    }
}

static inline void emit(unsigned int w0, unsigned int w1) {
    Gfx *cmd;

    cmd = g_displayListCursor++;
    cmd->words.w0 = w0;
    cmd->words.w1 = w1;
}

static inline void beginFrame(void) {
    Gfx *g;

    g_combinePipelineSyncPending = 1;
    g = g_displayListCursor++;
    gDPPipeSync(g);
}

void Rect_DrawRect(f32 x, f32 y, f32 unused, f32 width, f32 height, u32 color) {
    Combine_DrawClippedImageRectangle(x, y, unused, width, height, 0.0f, 0.0f, g_fullImageTextureCoordinate, g_fullImageTextureCoordinate, color);
}

void Rect_DrawGradientRectangle(f32 x, f32 y, s32 unused, f32 z, f32 a4, s32 a5, s32 a6, s32 a7, s32 a8) {
    g_combineTexturedRectangleState = 0;
    g_combinePipelineSyncPending = 0;
    Combine_SetRenderMode(12);
    Combine_SetCombineMode(5);
    if (g_combineTextureTileMode != 7) {
        g_combineTextureTileMode = 7;
        sync();
        emit(0xE3000C00, 0);
    }
    if (g_combineTextureRenderMode != 14) {
        g_combineTextureRenderMode = 14;
        sync();
        emit(0xD7000000, 0x80008000);
    }
    if (g_combineRenderSwitches.x == 0) {
        Combine_SetPrimitiveVertexMode(9);
        Combine_DrawClippedGradientQuad(x, y, z, a4, a5, a6, a7, a8);
    }
}

void Rect_ResetRenderState(void) {
    if (g_combineRenderStateEnabled != 0) {
        g_combineRenderStateEnabled = 0;
        g_combineCachedCombineMode = 0;
        g_combineTextureTileMode = 0;
        g_combineCachedPrimitiveMode = 0;
        g_combineCachedRenderMode = 0;
        g_combineTextureRenderMode = 0;
        g_combineCachedStateWord = 0;
        g_combineLoadedPalette = 0;
        g_combineRectangleColor = 0;
        g_combineTexturedRectangleState = 0;
    }
}

void Rect_SetTexturePerspectiveMode(s32 mode) {
    if (mode != g_combineTextureTileMode) {
        g_combineTextureTileMode = mode;
        if (g_combinePipelineSyncPending == 0) {
            beginFrame();
        }
        switch (mode) {
        case 6: {
            Gfx *g = g_displayListCursor++;
            gDPSetTexturePersp(g, G_TP_PERSP);
            break;
        }
        case 7: {
            Gfx *g = g_displayListCursor++;
            gDPSetTexturePersp(g, G_TP_NONE);
            break;
        }
        }
    }
}

/* Switches the texture mode (forced to 14 while g_combineTexturingEnabled is clear), emitting a full-sync command the first time and a texture-enable command for modes 13 and 14. */

/* Sets the environment and primitive colours from a packed 0xAARRGGBB colour when it differs from
   the last one set, g_combineRectangleColor: appends 0xFB (environment, alpha zero) and 0xFA (primitive, with
   alpha) commands to the display list g_displayListCursor_SimpleDrawcachedmodel points into. */

void Rect_SetTextureMode(s32 mode) {
    if (g_combineRenderSwitches.z == 0) {
        mode = 14;
    }
    if (mode != g_combineTextureRenderMode) {
        g_combineTextureRenderMode = mode;
        if (g_combinePipelineSyncPending == 0) {
            beginFrame();
        }
        if (mode == 13) gSPTexture(g_displayListCursor++, 32768, 32768, 0, 0, G_ON) else if (mode == 14) gSPTexture(g_displayListCursor++, 32768, 32768, 0, 0, G_OFF);
    }
}

void Rect_SyncPipeline(void) {
    Gfx *gfx;

    if (g_combinePipelineSyncPending == 0) {
        g_combinePipelineSyncPending = 1;
        gDPPipeSync(g_displayListCursor++);
    }
}

void Rect_ResetPipelineSync(void) {
    g_combinePipelineSyncPending = 0;
}

void Rect_SetPackedColor(u32 color) {
    Gfx *gfx;

    if (color == g_combineRectangleColor) {
        return;
    }
    g_combineRectangleColor = color;
    gfx = g_displayListCursor++;
    gDPSetEnvColor(gfx, color >> 16, (color & 0xFF00) >> 8, color, 0);
    gfx = g_displayListCursor++;

    gDPSetPrimColor(gfx, 0, 0, color >> 16, (color & 0xFF00) >> 8, color, color >> 24);
}

void Rect_EmitTextureRect(s32 left, s32 top, s32 right, s32 bottom, f32 u0, f32 v0, f32 u1, f32 v1) {
    f32 scaleU;
    f32 scaleV;
    s32 dsdx;
    s32 dtdy;
    s32 startS;
    s32 startT;

    if (g_combineBoundImage->width == 0 || g_combineBoundImage->height == 0 || left == right || top == bottom) {
        return;
    }
    scaleU = g_combineBoundImage->width << 10;
    dsdx = (s32)((u1 - u0) * scaleU) / (right - left + 1);
    scaleV = g_combineBoundImage->height << 10;
    dtdy = (s32)((v1 - v0) * scaleV) / (bottom - top + 1);
    startS = u0 * scaleU;
    startT = v0 * scaleV;
    gSPTextureRectangle(g_displayListCursor++, left * 4, top * 4, (right + 1) * 4, (bottom + 1) * 4, 0, startS >> 5, startT >> 5, dsdx, dtdy);
}

/* G_SYNCENCODEDWORDSBLOCK1.CPP */
#if defined(VERSION_EU_X)
unsigned int g_SyncEncodedWordsBlock1[3] = {
    0x00440460, 0x004404A0, 0x4F000000,
};
#endif

/* RECT.CPP */
#if defined(VERSION_EU)
unsigned int k_RectEncodedWordsBlock1[3] = {
    0x0800FF88, 0x011A011F, 0x011B011C,
};
#endif

#if defined(VERSION_DE)
float k_RectEncodedWords[3] = {
    0.01f, 1.2f, 0.05f,
};
#endif

/* G_SYNCENCODEDWORDS.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800E1444 */
unsigned int g_SyncEncodedWords[3] = {
    0x0043F600, 0x0043F640, 0x4F000000,
};
#endif

/* RECT.CPP */
/* ROM-grounded data: src/g_rect_DrawRectConstantWords_Rect.c */
const float g_rect_DrawRectConstantWords[1] = {
    1.0f,
};
