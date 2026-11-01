#include "include_asm.h"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/gbi.h>
#include "COMMON/TRIPLE.H"

/* Draw the inset viewport border with black bands and a one-pixel outline. */
void Geometry_InvalidateMaterialKeys(void);
extern Gfx *g_displayListCursor;

void Track_DrawLetterboxBorder(s32 inset) {
    f32 left;
    f32 top;
    f32 width;
    f32 height;
    Geometry_InvalidateMaterialKeys();
    left = 0.0f;
    top = (f32)inset;
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_1CYCLE);
    gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE);
    gDPSetRenderMode(g_displayListCursor++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    width = (f32)g_hudReferenceViewportWidth;
    gDPSetPrimColor(g_displayListCursor++, 0, 0, 0, 0, 0, 0);
    height = (f32)(g_hudReferenceViewportHeight - inset * 2);
    gDPFillRectangle(g_displayListCursor++, left, top, (width - 1.0f), (top + (2.0f)));
    gDPFillRectangle(g_displayListCursor++, left, ((top + height) - (2.0f)), ((left + width) - (1.0f)), ((top + height) - (1.0f)));
    gDPFillRectangle(g_displayListCursor++, left, top, (left + (2.0f)), ((top + height) - 1.0f));
    gDPFillRectangle(g_displayListCursor++, ((left + width) - (2.0f)), top, ((left + width) - (1.0f)), ((top + height) - (1.0f)));
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_FILL);
    gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE);
    gDPSetRenderMode(g_displayListCursor++, 0, 0);
    gDPSetFillColor(g_displayListCursor++, 0x10001);
    gDPFillRectangle(g_displayListCursor++, left, top, ((left + width) - 1.0f), top);
    gDPFillRectangle(g_displayListCursor++, left, ((top + height) - (1.0f)), ((left + width) - (1.0f)), ((top + height) - (1.0f)));
    gDPFillRectangle(g_displayListCursor++, left, top, left, ((top + height) - (1.0f)));
    gDPFillRectangle(g_displayListCursor++, ((left + width) - (1.0f)), top, (left + width), ((top + height) - (1.0f)));
}

#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"

#define MENU_CLAMP_PIXEL(value) \
    ({ s32 edge = (value); if (edge < 0) edge = 0; edge; })
#define MENU_CLAMP_HEIGHT(value) \
    ({ f32 edge = (value); if (!(edge >= 0.0f)) edge = 0.0f; edge; })

/* Fade letterbox bands around the active track and draw the viewport border. */
void Track_DrawLetterboxBands(void) {
    f32 fade = 1.0f;
    f32 height, span;
    height = ((f32)g_hudReferenceViewportHeight - (f32)g_hudReferenceViewportWidth / g_cinemaSequenceState->spec.aspectRatio) * 0.5f;
    span = 0.3f;
    if (g_cinemaSequenceState->time < g_cinemaSequenceState->start) {
        fade = g_cinemaSequenceState->start - g_cinemaSequenceState->time;
        fade /= span;
        if (1.0f < fade) fade = 1.0f;
        fade = 1.0f - fade;
    }
    if (g_cinemaSequenceState->time > g_cinemaSequenceState->end) {
        fade = g_cinemaSequenceState->time - g_cinemaSequenceState->end;
        fade /= span;
        if (1.0f < fade) fade = 1.0f;
        fade = 1.0f - fade;
    }
    height = height * fade;
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_1CYCLE);
    Geometry_SetModePreset(19);
    Geometry_SetCombineMode(25);
    gDPSetPrimColor(g_displayListCursor++, 255, 255, 0, 0, 0, 255);
    gDPFillRectangle(g_displayListCursor++, 0, 0, MENU_CLAMP_PIXEL(g_hudReferenceViewportWidth), MENU_CLAMP_PIXEL((s32)height));
    gDPFillRectangle(g_displayListCursor++, 0, (u32)MENU_CLAMP_HEIGHT((f32)g_hudReferenceViewportHeight - height), MENU_CLAMP_PIXEL(g_hudReferenceViewportWidth), MENU_CLAMP_PIXEL(g_hudReferenceViewportHeight));
    Track_DrawLetterboxBorder((s32)height);
}

#undef MENU_CLAMP_PIXEL
#undef MENU_CLAMP_HEIGHT
