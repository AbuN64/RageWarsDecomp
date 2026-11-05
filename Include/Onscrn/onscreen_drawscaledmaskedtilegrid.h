#ifndef ONSCRN_ONSCREEN_DRAWSCALEDMASKEDTILEGRID_H
#define ONSCRN_ONSCREEN_DRAWSCALEDMASKEDTILEGRID_H
#include "Common/weapon_screen_message_operations.h"
extern void OnScreen_StartMoverScript(void *widget, s32 *);
extern void OnScreen_SetFirstBarTarget(char *object, int value);
extern void OnScreen_DrawStatusBars(void *);
extern f32 OnScreen_GetGlyphWidth(void);
extern s32 OnScreen_DrawSpriteResource(s32, s32, s16, s16, f32, f32, s32);
extern void OnScreen_LoadFontTexture(void);
extern u8 *OnScreen_GetFontTexture(void);
extern void OnScreen_DrawMaskedTileGrid(u16 *grid, s16 x0, s32 y);
extern void OnScreen_DrawScaledMaskedTileGrid(u16 *grid, f32 x0, f32 y, f32 sx, f32 sy);
extern void OnScreen_FillRectangle(s32 x0,s32 y0,s32 x1,s32 y1,u8 r,u8 g,u8 b,u8 a);

struct Hud;
extern void OnScreen_StartFirstStatusBar(struct Hud *hud, s32 owner, s32 target);
extern void OnScreen_DrawTextWithShadow(u8 *text, f32 x, f32 y, f32 scaleX, f32 scaleY, s32 drawShadow, s32 alpha, s32 textFlags);
#endif
