#ifndef MENU_GFX_RECT_H
#define MENU_GFX_RECT_H
#include "COMMON/TEXTURE.H"

extern void Rect_ResetRenderState(void);

extern void Rect_EmitTextureRect(s32 left, s32 top, s32 right, s32 bottom, f32 u0, f32 v0, f32 u1, f32 v1);
extern void Rect_SyncPipeline(void);
extern void Rect_SetTextureMode(s32 mode);
extern void Rect_ResetPipelineSync(void);
#endif
