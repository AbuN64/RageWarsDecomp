#ifndef GFX_TEXT_ONSCREEN_DRAWSCALEDMASKEDTILEGRID_H
#define GFX_TEXT_ONSCREEN_DRAWSCALEDMASKEDTILEGRID_H
#include "TYPES.H"
extern void OnScreen_SetupFillMode();
extern s32 OnScreen_DrawSpriteResource(s32 resourceId, s32 index, s16 screenX, s16 screenY, f32 scaleX, f32 scaleY, s32 scaled);
struct OnScreenImageTableView;
void OnScreen_GetImageEntry(struct OnScreenImageTableView **handle, s32 index, void **out, u8 *tag);
void OnScreen_InitMover(void *moverStorage, s16 x, s16 y);
void OnScreen_SetSecondBarTarget(void *object, int value);
struct OverlayScriptSecondaryRangeView;
void OnScreen_StartSecondStatusBar(struct OverlayScriptSecondaryRangeView *hud, s32 owner, s32 target);
#endif
