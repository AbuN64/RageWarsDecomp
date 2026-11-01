#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/GAME_SESSION.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include <ultra64.h>
#include <PR/abi.h>
#include "COMMON/AIPROFILE.H"
#include "COMMON/OBJRECAT20V1.H"
#include <PR/gbi.h>
#include "TYPES.H"
#include "COMMON/VIDEO_DIMENSIONS.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "ENGINE/SETN64.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"

/* Clears the screen: clears the depth buffer over the whole screen through SetN64_ClearDepthRect, emits a full-screen scissor, the frame's colour image, fill cycle, combiner, no-op render mode, fill colour 0x10001 and a full-screen fill rectangle, then, when image 0x386 has a size, draws it stretched across the screen through OnScreen_DrawSpriteResource after Onscrn_SetupSpriteMode_Setn64Drawfullscreenbackdrop(255). Written with libultra-style display-list macros and the screen size read from g_hudReferenceViewportWidth and g_hudReferenceViewportHeight. */
#include "COMMON/DISPLAY.H"
extern void SetN64_ClearDepthRect(void *unused, s32 ulx, s32 lrx, s32 uly, s32 lry, s32 interlaced);

extern void Onscrn_SetupSpriteMode(s32 alpha);
void SetN64_DrawFullscreenBackdrop(void *unused) {
    Frame *frame = g_gameSession.ring.current;
    s32 width;
    s32 height;
    SetN64_ClearDepthRect(unused, 0, SCREEN_WD, 0, SCREEN_HT, 0);
    width = 0;
    height = 0;
    gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
    gDPSetColorImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, (u32)((frame->colorImage)));
    gDPSetCycleType(g_displayListCursor++, G_CYC_FILL);
    gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE);
    gDPSetRenderMode(g_displayListCursor++, ((0)), 0);
    gDPSetFillColor(g_displayListCursor++, ((0x10001)));
    gDPFillRectangle(g_displayListCursor++, 0, 0, (SCREEN_WD), (SCREEN_HT));
    OnScreen_GetImageDimensions(902, 0, &width, &height);
    if (width != 0 && height != 0) {
        Onscrn_SetupSpriteMode(0xFF);
        OnScreen_DrawSpriteResource(902, 0, 0, 0, (f32)SCREEN_WD / (f32)width, (f32)SCREEN_HT / (f32)height, 1);
    }
}
