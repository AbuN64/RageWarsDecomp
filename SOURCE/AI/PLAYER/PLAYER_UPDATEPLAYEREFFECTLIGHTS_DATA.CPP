#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "TYPES.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"

/* Draws an icon sprite for a view: icons 0x2DA, 0x2E4, 0x2BC and 0x2EF to 0x2F2 sit at the centre of
   the view's viewport, any other icon is placed at a world point projected through Gsky_ProjectToScreen_PlayerUpdateplayereffectlightsData when
   the point lies in front of the view's plane and within 64 pixels of the screen g_hudReferenceViewportWidth, remapped
   into the viewport when g_motionVisibilitySettings is set; the sprite is drawn back by its scaled size less one. */





extern void Gsky_ProjectToScreen(View *, CVector3 *, f32 *, f32 *);

void Playerai_DrawProjectedAimIcon(View *view, CVector3 *point, s32 icon, f32 frame, f32 scale, f32 size) {
    f32 x;
    f32 y;
    f32 offset;

    if (icon == 730 || icon == 740 || icon == 700 || icon == 751 || icon == 752
        || icon == 753 || icon == 754) {
        x = view->viewport[2] + view->viewport[0] * 0.5f;
        y = view->viewport[3] + view->viewport[1] * 0.5f;
    } else {
        if (!(view->normal.x * point->x + view->normal.y * point->y + view->normal.z * point->z
              <= view->distance)) {
            return;
        }
        Gsky_ProjectToScreen(view, point, &x, &y);
        if (x < -64.0f || (f32) (g_hudReferenceViewportWidth + 64) < x || y < -64.0f
            || (f32) (*(&g_hudReferenceViewportWidth + 1) + 64) < y) {
            return;
        }
        if (g_gameSettings.local != 0) {
            x = view->viewport[2] + x / g_hudReferenceViewportWidth * view->viewport[0];
            y = view->viewport[3] + y / *(&g_hudReferenceViewportWidth + 1) * view->viewport[1];
        }
    }
    offset = scale * size - 1.0f;
    OnScreen_DrawSpriteResource(icon, frame, x - offset, y - offset, size, size, 1);
}
