#ifndef GFX_TEXT_ONSCREEN_DRAWSCALEDMASKEDTILEGRID_H
#define GFX_TEXT_ONSCREEN_DRAWSCALEDMASKEDTILEGRID_H
#include "types.h"
extern void OnScreen_SetupFillMode();
extern s32 OnScreen_DrawSpriteResource(s32 resourceId, s32 index, s16 screenX, s16 screenY, f32 scaleX, f32 scaleY, s32 scaled);
struct OnScreenImageTableView;
struct LoadedImageTable;
void OnScreen_GetImageEntry(struct LoadedImageTable **handle, s32 index, void **out, u8 *tag);
void OnScreen_InitMover(void *moverStorage, s16 x, s16 y);
void OnScreen_SetSecondBarTarget(void *object, int value);
struct OverlayScriptSecondaryRangeView;
struct Hud;
void OnScreen_StartSecondStatusBar(struct Hud *hud, s32 owner, s32 target);
#endif
