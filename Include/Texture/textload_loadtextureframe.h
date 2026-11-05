#ifndef TEXTURE_TEXTLOAD_LOADTEXTUREFRAME_H
#define TEXTURE_TEXTLOAD_LOADTEXTUREFRAME_H
#include "Common/sky_layers.h"

struct TextureVariationResource;
/* Resource handle passed to the texture variation completion callback. */
typedef struct TextureVariationResource {
    s32 **handle;
    s32 reservedWord;
    u32 flags;
} TextureVariationResource;
void Textload_PrepareTextureVariation(s32 textureResource, struct TextureVariationResource *resource);

void Textload_LoadTextureFrame(s32 *output, void **resource, s32 frame, s32 secondary, s32 scaleS, s32 scaleT, s32 wrapS, s32 wrapT, s32 mode);
#endif
