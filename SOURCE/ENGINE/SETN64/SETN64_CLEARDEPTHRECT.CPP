#include "include_asm.h"
#include "COMMON/FONT_STYLE_AND_GLYPH_OPERATIONS.H"
#include "COMMON/GAME_SESSION.H"
#include <ultra64.h>
#include "COMMON/AIPROFILE.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include <PR/gbi.h>
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"

/* Clears the depth buffer over a rectangle: switches the colour image to the depth buffer g_depthImageBuffer in fill mode after setting render mode 0x14 through Geometry_SetModePreset, fills the rectangle with the far depth value (or, for interlaced output, alternate lines with the far value and the remaining lines with 0, by single lines or by line pairs as g_frontendCurrentVideoModeIndex selects), then restores the frame's colour image and one-cycle mode. Written with libultra-style display-list macros. */




extern s32 Geometry_SetModePreset(s32 mode);










void SetN64_ClearDepthRect(void *unused, s32 ulx, s32 lrx, s32 uly, s32 lry, s32 interlaced) {
    s32 y;

    gDPPipeSync(g_displayListCursor++);
    Geometry_SetModePreset(20);
    gDPSetColorImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, g_hudReferenceViewportWidth, (u32)((g_depthImageBuffer)));
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_FILL);
    if (!interlaced) {
        gDPSetFillColor(g_displayListCursor++, ((0xFFFCFFFC)));
        gDPFillRectangle(g_displayListCursor++, (ulx), (uly), (lrx), (lry));
    } else if (g_frontendCurrentVideoModeIndex == 0) {
        gDPSetFillColor(g_displayListCursor++, ((0xFFFCFFFC)));
        for (y = uly; y < lry; y += 2) {
            gDPFillRectangle(g_displayListCursor++, (ulx), (y), (lrx), (y));
        }
        gDPSetFillColor(g_displayListCursor++, ((0)));
        for (y = uly + 1; y < lry; y += 2) {
            gDPFillRectangle(g_displayListCursor++, (ulx), (y), (lrx), (y));
        }
    } else {
        gDPSetFillColor(g_displayListCursor++, ((0xFFFCFFFC)));
        for (y = uly; y < lry; y++) {
            if ((y & 3) < 2) {
                gDPFillRectangle(g_displayListCursor++, (ulx), (y), (lrx), (y));
            }
        }
        gDPSetFillColor(g_displayListCursor++, ((0)));
        for (y = uly; y < lry; y++) {
            if ((y & 3) >= 2) {
                gDPFillRectangle(g_displayListCursor++, (ulx), (y), (lrx), (y));
            }
        }
    }
    gDPSetColorImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, g_hudReferenceViewportWidth, (u32)((g_gameSession.ring.current->colorImage)));
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_2CYCLE);
}


/* Draw a null-terminated list of scaled strings, with an optional full-screen backdrop. */
void SetN64_DrawTextLines(void *state, s32 drawBackdrop, char **lines, s32 x, s32 y, s32 lineStep, f32 scaleX, f32 scaleY) {
    Frame *frame = g_gameSession.ring.current;
    s32 i;
    char *text;

    y = y * g_hudReferenceViewportHeight / 222;
    if (drawBackdrop) {
        SetN64_ClearDepthRect(state, 0, g_hudReferenceViewportWidth, 0, g_hudReferenceViewportHeight, 0);
        gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, 0, 0, g_hudReferenceViewportWidth - 1, g_hudReferenceViewportHeight - 1);
        gDPSetColorImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, g_hudReferenceViewportWidth, (u32)frame->colorImage);
        gDPSetCycleType(g_displayListCursor++, G_CYC_FILL);
        gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE);
        gDPSetRenderMode(g_displayListCursor++, 0, 0);
        gDPSetFillColor(g_displayListCursor++, 0x00010001);
        gDPFillRectangle(g_displayListCursor++, 0, 0, g_hudReferenceViewportWidth, g_hudReferenceViewportHeight);
    }
    OnScreen_SetupTextRendering();
    OnScreen_SetTextColors(0xFF, 0xFF, 0xFF, 200, 200, 200);
    scaleX = scaleX * g_hudReferenceViewportWidth * (1.0f / 284.0f);
    scaleY = scaleY * g_hudReferenceViewportHeight * (1.0f / 222.0f);
    scaleX *= (g_hudReferenceViewportHeight >= 223) ? 0.8f : 0.85f;
    scaleY *= 0.5f;
    OnScreen_SetTextScale(scaleX, scaleY);
    g_tutorialStatusBars.shadowX = 1;
    g_tutorialStatusBars.shadowY = 1;
    for (i = 0; lines[i] != 0; i++) {
        text = lines[i];
        Onscrn_DrawText(text, x, y, 0xFF, 1, 1, 1.0f, 1.0f);
        y = y + lineStep * scaleY;
    }
}

