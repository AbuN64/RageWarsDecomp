#ifndef ONSCRN_ONSCREEN_DRAWSCALEDMASKEDTILEGRID_H
#define ONSCRN_ONSCREEN_DRAWSCALEDMASKEDTILEGRID_H
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
extern s32 OnScreen_StartMoverScript(void *widget, s32 *);
extern void OnScreen_SetFirstBarTarget(char *object, int value);
extern void OnScreen_DrawStatusBars(void *);
extern f32 OnScreen_GetGlyphWidth(void);
extern s32 OnScreen_DrawSpriteResource(s32, s32, s16, s16, f32, f32, s32);
extern void OnScreen_LoadFontTexture(void);
extern u8 *OnScreen_GetFontTexture(void);
extern void OnScreen_DrawMaskedTileGrid(u16 *grid, s16 x0, s32 y);
extern void OnScreen_DrawScaledMaskedTileGrid(u16 *grid, f32 x0, f32 y, f32 sx, f32 sy);
#endif
