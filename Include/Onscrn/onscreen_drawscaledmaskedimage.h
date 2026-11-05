#ifndef ONSCRN_ONSCREEN_DRAWSCALEDMASKEDIMAGE_H
#define ONSCRN_ONSCREEN_DRAWSCALEDMASKEDIMAGE_H
#include "types.h"
extern void OnScreen_DrawTextureWithOpacity(void *pTexture, void *pOpacity, int XPos, int YPos, int TextureWidth, int TextureHeight);
extern void OnScreen_DrawScaledMaskedImage(void *pTexture, void *pOpacity, float XPos, float YPos, int TextureWidth, int TextureHeight, float ScaleX, float ScaleY);
extern void OnScreen_DrawIntensityTexture(void *pTexture, int XPos, int YPos, int TextureWidth, int TextureHeight);
extern void OnScreen_DrawScaledIntensityTexture(void *pTexture, f32 XPos, f32 YPos, int TextureWidth, int TextureHeight, f32 ScaleX, f32 ScaleY);

extern void Onscrn_DrawText(void *, s32, s32, s32, s32, s32, f32, f32);
#endif
