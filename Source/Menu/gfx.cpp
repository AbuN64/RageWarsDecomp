#include "Common/texture.h"
#include "Common/runtime_declarations.h"
#include <PR/gbi.h>
#include <platform_sdk.h>
#include "types.h"
#include "Menu/Gfx/rect.h"
#include "Common/rectangle_draw.h"
#include "include_asm.h"
#include <PR/abi.h>
#include "Common/sessionhandlerrow.h"
#include "Menu/Gfx/gfx_drawclippedgradientquad.h"
#include "Menu/Gfx/rect_symbols.h"
#include "Common/sitype.h"
#include "PR/os_time.h"
#include "Menu/Gfx/gfx_symbols.h"

static inline void sync_rect(void) {
    Gfx *cmd;

    if (g_combinePipelineSyncPending == 0) {
        g_combinePipelineSyncPending = 1;
        cmd = g_displayListCursor++;
        gDPPipeSync(cmd);
    }
}

static inline void emit_rect(unsigned int w0, unsigned int w1) {
    Gfx *cmd;

    cmd = g_displayListCursor++;
    cmd->words.w0 = w0;
    cmd->words.w1 = w1;
}

/* Appends a G_TEXTURE command that turns texture sampling on or off with both scale factors at 0x8000 (1.0). */
static inline void emitTextureState_rect(s32 on) {
    Gfx *cmd = g_displayListCursor++;
    gSPTexture(cmd, 0x8000, 0x8000, 0, G_TX_RENDERTILE, on);
}

static inline void beginFrame_rect(void) {
    Gfx *g;

    g_combinePipelineSyncPending = 1;
    g = g_displayListCursor++;
    gDPPipeSync(g);
}

void Rect_DrawRect(f32 x, f32 y, f32 z, f32 width, f32 height, u32 color) {
    Combine_DrawClippedImageRectangle(x, y, z, width, height, 0.0f, 0.0f, g_fullImageTextureCoordinate, g_fullImageTextureCoordinate, color);
}

void Rect_DrawGradientRectangle(f32 x, f32 y, s32 depth, f32 z, f32 a4, s32 a5, s32 a6, s32 a7, s32 a8) {
    g_combineTexturedRectangleState = 0;
    g_combinePipelineSyncPending = 0;
    Combine_SetRenderMode(12);
    Combine_SetCombineMode(5);
    if (g_combineTextureTileMode != 7) {
        g_combineTextureTileMode = 7;
        sync_rect();
        emit_rect(0xE3000C00, 0);
    }
    if (g_combineTextureRenderMode != 14) {
        g_combineTextureRenderMode = 14;
        sync_rect();
        emitTextureState_rect(G_OFF);
    }
    if (g_combineRenderSwitches.texturingEnabled == 0) {
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
            beginFrame_rect();
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

/* Sets the environment and primitive colours from a packed 0xAARRGGBB colour when it differs from
   the last one set, g_combineRectangleColor: appends 0xFB (environment, alpha zero) and 0xFA (primitive, with
   alpha) commands to the display list g_displayListCursor_SimpleDrawcachedmodel points into. */
void Rect_SetTextureMode(s32 mode) {
    if (g_combineRenderSwitches.translucencyEnabled == 0) {
        mode = 14;
    }
    if (mode != g_combineTextureRenderMode) {
        g_combineTextureRenderMode = mode;
        if (g_combinePipelineSyncPending == 0) {
            beginFrame_rect();
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

#if defined(VERSION_EU_X)
unsigned int g_rectRetainedWords[3] = {
    0x00440460, 0x004404A0, 0x4F000000,
};
#endif

#if defined(VERSION_EU)
unsigned int k_rectPackedHalfwords[3] = {
    0x0800FF88, 0x011A011F, 0x011B011C,
};
#endif

#if defined(VERSION_DE)
float k_RectEncodedWords[3] = {
    0.01f, 1.2f, 0.05f,
};
#endif

#if defined(VERSION_US_REV1)
unsigned int g_SyncEncodedWords[3] = {
    0x0043F600, 0x0043F640, 0x4F000000,
};
#endif

const float g_rect_DrawRectConstantWords[1] = {
    1.0f,
};

#if !(defined(VERSION_EU_X) || defined(VERSION_US_REV1))
/* Ratio of the cycle counter osGetTime returns to the counter rate g_systemClockFrequency, each converted to a double. */
f64 Gfx_GetNormalizedCounter(void) {
    return Libc_SignedLongLongToDouble(osGetTime()) / Libc_SignedLongLongToDouble(g_systemClockFrequency);
}
#endif

#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
f64 Gfx_GetConvertedCounterRatio(void) {
    return Libc_SignedLongLongToDoubleUsRev1(osGetTime()) / Libc_SignedLongLongToDoubleUsRev1(g_systemClockFrequency);
}
#endif
