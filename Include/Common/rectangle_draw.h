#ifndef COMMON_RECTANGLE_DRAW_H
#define COMMON_RECTANGLE_DRAW_H
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Ui/Quag/N64_Eng.h"

struct PrimitiveRenderSwitches;
/* Five cached flag groups written together by Combine_ConfigurePrimitiveRenderFlags. */
struct PrimitiveRenderSwitches {
    s32 texturingEnabled;
    s32 combineEnabled;
    s32 translucencyEnabled;
    s32 coverageBlend;
    s32 depthBufferEnabled;
};
typedef struct PrimitiveRenderSwitches PrimitiveRenderSwitches;
extern struct PrimitiveRenderSwitches g_combineRenderSwitches;
extern s32 g_combineTextureTileMode;
extern s32 g_combineTextureRenderMode;
extern s32 g_combineRectangleColor;
extern s32 g_combineTexturedRectangleState;

void Combine_DrawClippedGradientQuad(f32 x, f32 y, f32 width, f32 height, u32 c0, u32 c1, u32 c2, u32 c3);

void Combine_DrawClippedImageRectangle(f32 x, f32 y, f32 unusedDepth, f32 width, f32 height, f32 u0, f32 v0, f32 u1, f32 v1, u32 color);
void Rect_DrawRect(f32 x, f32 y, f32 z, f32 width, f32 height, u32 color);
#endif
