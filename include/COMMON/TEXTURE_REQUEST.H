#ifndef COMMON_TEXTURE_REQUEST_H
#define COMMON_TEXTURE_REQUEST_H
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#if defined(VERSION_US_REV1)
extern s32 g_textureVariationBypassEnabled;
extern char addrLow_Textload_PrepareTextureVariation_us_rev1;
extern char s_textureText[];
#else
extern char addrLow_Textload_PrepareTextureVariation;
extern char s_textureText_TextureRequest[];
#endif
/* Request the texture resource for this bank and variation. */
static __inline__ void *rw_request_texture(s32 *resource, s32 variation, s32 wait)
{
#if defined(VERSION_US_REV1)
    if (g_textureVariationBypassEnabled == 0) {
        return Cache_RequestResource(0, resource[0] + variation + g_texturePaletteOverrideEnabled * 128,
                              resource[0], resource[1], 0, variation,
                              &addrLow_Textload_PrepareTextureVariation_us_rev1, s_textureText, wait);
    }
    return Cache_RequestResource(0, resource[0] - 1, resource[0], resource[1],
                          0, -1, &addrLow_Textload_PrepareTextureVariation_us_rev1, s_textureText, wait);
#else
    return Cache_RequestResource(0, resource[0] + variation + g_texturePaletteOverrideEnabled * 128,
                          resource[0], resource[1], 0, variation,
                          &addrLow_Textload_PrepareTextureVariation, s_textureText_TextureRequest, wait);
#endif
}

/* Request and wait for this texture resource. */
static __inline__ void **rw_request_texture_sync(s32 *resource, s32 variation)
{
#if defined(VERSION_US_REV1)
    if (g_textureVariationBypassEnabled == 0) {
        return Cache_RequestResource(0, resource[0] + variation + g_texturePaletteOverrideEnabled * 128,
                              resource[0], resource[1], 0, variation,
                              &addrLow_Textload_PrepareTextureVariation_us_rev1, s_textureText, 1);
    }
    return Cache_RequestResource(0, resource[0] - 1, resource[0], resource[1],
                          0, -1, &addrLow_Textload_PrepareTextureVariation_us_rev1, s_textureText, 1);
#else
    return Cache_RequestResource(0, resource[0] + variation + g_texturePaletteOverrideEnabled * 128,
                          resource[0], resource[1], 0, variation,
                          &addrLow_Textload_PrepareTextureVariation, s_textureText_TextureRequest, 1);
#endif
}
#endif
