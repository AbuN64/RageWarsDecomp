#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VIEWFLAGS.H"
#include "CAMERA/FADE_AND_COLOR_BLEND_VIEWS.H"
#include "TYPES.H"
#include "include_asm.h"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include <ultra64.h>
#include <PR/gbi.h>
#include "COMMON/DESCRIPTORRECAT29.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"
#include "COMMON/LENS_FLARE.H"

/* 80233920_10.CPP */
/* Clears effect state and initializes its scalar, vector and resource defaults. */

extern s32 g_defaultCameraSurfaceType[];
void Sky_InitializeLensFlareState(LensFlareEffectState *effectState) {
    f32 zeroValue;
    CVector3 *vectorDefaults;

    effectState->initialScalar.i = 0;
    zeroValue = effectState->initialScalar.f;
    effectState->enabled = 1;
    vectorDefaults = &effectState->v;
    effectState->stateWordOne = 0;
    effectState->stateWordTwo = 0;
    effectState->stateWordThree = 0;
    effectState->stateWordFour = 0;
    effectState->stateWordFive = 0;
    effectState->stateWordSix = 0;
    effectState->stateWordSeven = 0;
    vectorDefaults->z = zeroValue;
    vectorDefaults->y = zeroValue;
    effectState->v.x = zeroValue;
    effectState->scale = 1.0f;
    effectState->stateWordEight = 0;
    effectState->scalarOffset = zeroValue;
    effectState->defaultAngle = 0.174532949924469f;
    effectState->defaultStateValue = (s32) *g_defaultCameraSurfaceType;
}

/* 80238670.CPP */
typedef struct ClipView FlareActor;
extern s32 g_hudReferenceViewportWidth;
extern Gfx *g_displayListCursor;
extern f32 Gu_Sqrtf(f32);
void Sky_DrawLensFlare(FlareActor *actor, f32 x, f32 y, f32 intensity, s32 special, s32 unused) {
    FlareRadii radii = k_lensFlareRadii;
    FlareAlphas alphas = k_lensFlareAlphas;
    FlareColors colors = k_lensFlareColors;
    f32 dx, dy, distance, nx, ny;
    f32 bottom, right, left, top, edge, width, half, alpha;
    Gfx *gfx;
    s32 i;
    if (intensity == 0.0f || actor->hidden) return;
    dx = g_hudReferenceViewportWidth / 2 - x;
    dy = g_hudReferenceViewportHeight / 2 - y;
    gfx = g_displayListCursor++;
    gDPSetTextureFilter(gfx, G_TF_BILERP);
    distance = Gu_Sqrtf(dx * dx + dy * dy);
    if (!special) {
        edge = distance / Gu_Sqrtf((f32)(g_hudReferenceViewportWidth * g_hudReferenceViewportWidth) * 0.25f + (f32)(g_hudReferenceViewportHeight * g_hudReferenceViewportHeight) * 0.25f);
        if (edge > 1.0f) intensity = 0.0f;
        else intensity *= 1.0f - edge;
    }
    distance *= 0.4f;
    if ((dx < 0.0f ? -dx : dx) > (dy < 0.0f ? -dy : dy)) {
        nx = -1.0f;
        if (dx > 0.0f) nx = 1.0f;
        ny = dy / (dx < 0.0f ? -dx : dx);
    } else {
        nx = dx / (dy < 0.0f ? -dy : dy);
        ny = -1.0f;
        if (dy > 0.0f) ny = 1.0f;
    }
    if (special) {
        half = 35.2f;
        bottom = (f32)g_hudReferenceViewportHeight + half;
        right = (f32)g_hudReferenceViewportWidth + half - x;
        left = x + half;
        top = y + half;
        edge = bottom - y;
        if (!(edge <= right)) edge = right;
        if (!(edge <= top)) edge = top;
        if (!(edge <= left)) edge = left;
        if (!(edge <= half)) edge = half;
        if (edge < 0.0f) intensity = 0.0f;
        else {
            alpha = bottom - y;
            if (!(alpha <= right)) alpha = right;
            if (!(alpha <= top)) alpha = top;
            if (!(alpha <= left)) alpha = left;
            if (!(alpha <= half)) alpha = half;
            intensity *= alpha / half;
        }
        intensity = intensity > 1.0f || !(intensity < 0.0f) ? (intensity > 1.0f ? 1.0f : intensity) : 0.0f;
    }
    for (i = 0; i < 7; i++) {
        x += nx * distance;
        y += ny * distance;
        if (special && i == 0) width = 2.0f;
        else width = radii.value[i] * 0.03125f;
        width *= 0.55f;
        half = width * 16.0f;
        if (!(x > -half && x < g_hudReferenceViewportWidth + half && y > (top = -half) && y < g_hudReferenceViewportHeight + half)) return;
        if (special && i == 0) {
            gDPSetEnvColor(g_displayListCursor++, 255, 255, 255, intensity * 255.0f);
            OnScreen_DrawSpriteResource(600, 0, (s16)(s32)(x - half), (s16)(s32)(y - half), width, width, 1);
        } else {
            gDPSetEnvColor(g_displayListCursor++, colors.value[i * 3], colors.value[i * 3 + 1], colors.value[i * 3 + 2], alphas.value[i] * intensity);
            OnScreen_DrawSpriteResource(601, 0, (s16)(s32)(x - half), (s16)(s32)(y - half), width, width, 1);
        }
    }
}

/* An object that shines a lens flare: its world position, the views that see it (bit 3 + view index),
 * a pointer to its state flags (0x80000 = flare lit) and the flare brightness (0..255). Unit-private view. */
typedef struct FlareSource FlareSource;
struct FlareSource {
    char pad0[0x8];
    CVector3 position;
    char pad14[0x5C - 0x14];
    s32 viewMask;
    char pad60[0x118 - 0x60];
    s32 *state;
    char pad11C[0x198 - 0x11C];
    f32 brightness;
    char pad19C[0x1F4 - 0x19C];
    FlareSource *next;
};
typedef struct FlareSourceList { FlareSource *first; } FlareSourceList;
extern FlareSourceList g_lensFlareSources;
extern void Onscrn_SetupSpriteMode(s32);
extern s32 Geometry_SetModePreset(s32);
extern void Graphu64_ProjectPoint(void *, void *, CVector3 *);

/* Same body as Gsky_ProjectToScreen: project a world point through the view matrix to screen pixels. */
static inline void ProjectToScreen(FlareActor *view, CVector3 *point, f32 *screenX, f32 *screenY) {
    CVector3 value;
    f32 half;
    Graphu64_ProjectPoint(view->viewProjection, point, &value);
    half = (f32)(g_hudReferenceViewportWidth / 2);
    *screenX = value.x * half + half;
    *screenY = value.y * (f32)(-g_hudReferenceViewportHeight / 2) + (f32)(g_hudReferenceViewportHeight / 2);
}

/* Draws the lens flares of every lit flare source the view can see. */
void Gsky_DrawObjectFlares(FlareActor *view) {
    Gfx **gfx = &g_displayListCursor;
    Gfx *g;
    FlareSource *source;
    f32 x, y;
    s32 mask = 8 << view->index;

    Onscrn_SetupSpriteMode(100);
    Geometry_SetModePreset(26);
    g = *gfx;
    gDPSetTextureFilter(g++, G_TF_BILERP);
    *gfx = g;
    for (source = g_lensFlareSources.first; source != 0; source = source->next) {
        if ((source->viewMask & mask) && (*source->state & 0x80000)) {
            ProjectToScreen(view, &source->position, &x, &y);
            Sky_DrawLensFlare(view, x, y, source->brightness * (1.0f / 255.0f), 0, 0);
        }
    }
}
