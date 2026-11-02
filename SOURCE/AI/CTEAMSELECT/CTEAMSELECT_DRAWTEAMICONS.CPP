#include "MENU/TEAMMENU.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "AI/CTEAMSELECT.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "TYPES.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"
#include "ONSCRN.H"



extern s32 g_hudReferenceViewportWidth;



 /* "Select Team" */



extern void Onscrn_DrawText(void *, s32, s32, s32, s32, s32, f32, f32);

void Cteamselect_DrawTeamIcons(struct TeamMenu *menu, TeamMenuIconView *items, s32 count, WeaponMenuPlayer *player) {
    s32 width;
    s32 height;
    f32 fade;
    s32 level;
    f32 scaleX;
    f32 scaleY;
    f32 x;
    f32 y;
    f32 alpha;
    s32 red;
    s32 green;
    s32 blue;
    WeaponMenuView *view;
    WeaponMenuView *titleView;
    f32 *viewport;
    TeamMenuIconView *item;

    titleView = player->view;
    level = g_gameSettings.hudFade + 64;
    fade = menu->open * (level < 256 ? level : 255.0f);
    item = items;
    while (--count != -1) {
        view = player->view;
        scaleX = view->viewport[0] * (1.0f / 320.0f);
        scaleY = view->viewport[1] * (1.0f / 240.0f);
        viewport = view->viewport;
        x = viewport[2] + viewport[0] * 0.5f + item->position.x * 0.5f * viewport[0];
        y = viewport[3] + viewport[1] * 0.5f + item->position.y * 0.5f * viewport[1];
        alpha = item->width;
        if (item->icon != 0) {
            OnScreen_GetImageDimensions(item->icon, 0, &width, &height);
            if (menu->cursor == item->slot) {
                red = Math_Cosf(menu->spin) * 63.0f + 192.0f;
                alpha = 1.0f;
                green = red;
                blue = red;
            } else {
                red = 150;
                green = red;
                blue = red;
                alpha *= 0.75f;
            }
            gDPSetEnvColor(g_displayListCursor++, red, green, blue, alpha * fade);
            OnScreen_DrawSpriteResource(item->icon, 0, x - width * item->height * scaleX * 0.5f,
                          y - height * item->height * scaleY * 0.5f,
                          scaleX * item->height, scaleY * item->height, 1);
        }
        item++;
    }
    scaleY = titleView->viewport[1] / g_hudReferenceViewportHeight;
    scaleX = titleView->viewport[0] / g_hudReferenceViewportWidth;
    OnScreen_SetupTextRendering();
    OnScreen_SetTextScale(0.6f, 0.6f);
    OnScreen_SetTextColors(0xFF, 0xFF, 0xFF, 200, 200, 200);
    x = viewport[2] + viewport[0] * 0.5f;
    y = viewport[3] + viewport[1] * 0.5f;
    Onscrn_DrawText(s_selectTeamText, x, y, 200, 1, 1, scaleX, scaleY);
}

/* Returns the cardinal team-menu slot, or -1 inside the deadzone/diagonals. */
s32 Cteamselect_GetFourWayStickSlot(void *object) {
    StickPlayer *player = object;
    StickInput *input = player->input;
    s8 x = input->x;
    s8 y = input->y;
    if (x*x + y*y < 3600) return -1;
    if (((f32)(((f32)x < 0.0f ? -x : x) - ((f32)y < 0.0f ? -y : y)) < 0.0f ? -(((f32)x < 0.0f ? -x : x) - ((f32)y < 0.0f ? -y : y)) : (((f32)x < 0.0f ? -x : x) - ((f32)y < 0.0f ? -y : y))) < 46 && x && y) goto diagonal;

    if (((f32)x < 0.0f ? -x : x) > ((f32)y < 0.0f ? -y : y)) { s32 r = 1; if (x <= 0) r = 3; return r; }
    return (y <= 0) << 1;

diagonal:
    return -1;
}
