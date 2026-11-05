#ifndef MENU_GFX_GFX_DRAWCLIPPEDGRADIENTQUAD_H
#define MENU_GFX_GFX_DRAWCLIPPEDGRADIENTQUAD_H
#include "Common/texture.h"
#include "Common/rectangle_draw.h"
void Combine_SetRenderMode(s32 mode);
void Combine_SetCombineMode(s32 mode);
void Combine_SetPrimitiveVertexMode(s32 mode);
void Combine_BindImageTexture(struct Texture *image);
#endif
