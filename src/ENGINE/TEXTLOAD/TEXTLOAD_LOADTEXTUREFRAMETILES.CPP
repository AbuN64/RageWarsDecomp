#include <ultra64.h>
#include "TYPES.H"
#include <PR/gbi.h>

#if defined(VERSION_US_REV1)
/* Preserve the original SDK shift expression used by the texture commands. */
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/RESIDENTSTATE.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

extern void Cache_MarkResourceInUse(s32, struct CacheResourceNode *);
extern Gfx g_textureFrameDefaultDisplayList[], g_textureFrameWrappedDisplayList[], g_textureFrameAlternateDisplayList[], g_textureFramePaletteDisplayList[], g_enemyConstantWordsBlock5[];


void Textload_LoadTextureFrameTiles(s32 *output, void **resource, s32 frame, s32 secondary, s32 scaleS, s32 scaleT, s32 wrapS, s32 wrapT, s32 mode) {
    s32 *texture;
    s32 *palette;
    void *header;
    void *entries;
    u8 *info;
    s32 changed;
    s32 paletteChanged;
    u8 maskS;
    u8 maskT;
    s32 level;
    s32 tile;
    Gfx *list;

    Cache_MarkResourceInUse(0, resource);
    header = *resource;
    info = SetN64_GetPackSection(header, 0);
    texture = SetN64_GetPackSection(SetN64_GetPackSection(header, 1), frame);
    entries = SetN64_GetPackSection(header, 2);
    if (*(s32 *)entries != 0) {
        palette = SetN64_GetPackSection(entries, secondary);
        paletteChanged = 0;
        if (g_textureCacheResource != (s32)resource || g_textureFrameCacheVariation != secondary) paletteChanged = 1;
    } else {
        paletteChanged = 0;
        palette = 0;
    }
    changed = 0;
    if (g_textureCacheResource != (s32)resource || g_textureFrameCacheFrame != frame || g_textureFrameCacheWrapS != wrapS || g_textureFrameCacheWrapT != wrapT) {
        changed = 1;
    }
    if (changed || paletteChanged) {
        g_textureCacheResource = (s32)resource;
        g_textureFrameCacheFrame = frame;
        g_textureFrameCacheVariation = secondary;
        g_textureFrameCacheWrapS = wrapS;
        g_textureFrameCacheWrapT = wrapT;
        maskS = 0;
        if (!(wrapS & G_TX_CLAMP)) {
            maskS = info[2];
        }
        maskT = 0;
        if (!(wrapT & G_TX_CLAMP)) {
            maskT = info[3];
        }
        TextLoad_ApplyArtsendTextureOverride((s32)resource, &texture);
        TextLoad_ApplyArtsendPaletteOverride((s32)resource, &palette);
        switch (info[0]) {
        case 0:
            if (changed) {
                {      gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 1, texture);      gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);      gDPLoadSync(g_displayListCursor++);      gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((((1 << info[2]) * (1 << info[3]) + (1)) >> (1)) - 1) < 2047 ? ((((1 << info[2]) * (1 << info[3]) + (1)) >> (1)) - 1) : 2047), (((1 << G_TX_DXT_FRAC) + (1 > ((1) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (1)) / 8)) ? 1 : ((1) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (1)) / 8))) - 1) / (1 > ((1) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (1)) / 8)) ? 1 : ((1) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (1)) / 8)))));      gDPPipeSync(g_displayListCursor++);      gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_8b, ((1 << info[2]) + 7) >> 3, 0, G_TX_RENDERTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);      gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, ((1 << info[2]) - 1) << 2, ((1 << info[3]) - 1) << 2); };
                gDPSetTextureLUT(g_displayListCursor++, G_TT_RGBA16);
            }
            if (paletteChanged) {
                     gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, palette);      gDPTileSync(g_displayListCursor++);      gDPSetTile(g_displayListCursor++, 0, 0, 0, 256, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);      gDPLoadSync(g_displayListCursor++);      gDPLoadTLUTCmd(g_displayListCursor++, G_TX_LOADTILE, 255);      gDPPipeSync(g_displayListCursor++);
            }
            break;
        case 1:
            if (changed) {
                {      gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 1, texture);      gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);      gDPLoadSync(g_displayListCursor++);      gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((((1 << info[2]) * (1 << info[3]) + (3)) >> (2)) - 1) < 2047 ? ((((1 << info[2]) * (1 << info[3]) + (3)) >> (2)) - 1) : 2047), (((1 << G_TX_DXT_FRAC) + (1 > ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8)) ? 1 : ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8))) - 1) / (1 > ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8)) ? 1 : ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8)))));      gDPPipeSync(g_displayListCursor++);      gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_4b, (((1 << info[2]) >> 1) + 7) >> 3, 0, G_TX_RENDERTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);      gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, ((1 << info[2]) - 1) << 2, ((1 << info[3]) - 1) << 2); };
                gDPSetTextureLUT(g_displayListCursor++, G_TT_RGBA16);
            }
            if (paletteChanged) {
                     gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, palette);      gDPTileSync(g_displayListCursor++);      gDPSetTile(g_displayListCursor++, 0, 0, 0, 256, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);      gDPLoadSync(g_displayListCursor++);      gDPLoadTLUTCmd(g_displayListCursor++, G_TX_LOADTILE, 15);      gDPPipeSync(g_displayListCursor++);
            }
            break;
        case 3:
            if (changed) {
                {      gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 1, texture);      gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);      gDPLoadSync(g_displayListCursor++);      gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((((1 << info[2]) * (1 << info[3]) + (3)) >> (2)) - 1) < 2047 ? ((((1 << info[2]) * (1 << info[3]) + (3)) >> (2)) - 1) : 2047), (((1 << G_TX_DXT_FRAC) + (1 > ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8)) ? 1 : ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8))) - 1) / (1 > ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8)) ? 1 : ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8)))));      gDPPipeSync(g_displayListCursor++);      gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_4b, (((1 << info[2]) >> 1) + 7) >> 3, 0, G_TX_RENDERTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);      gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, ((1 << info[2]) - 1) << 2, ((1 << info[3]) - 1) << 2); };
                gDPSetTextureLUT(g_displayListCursor++, G_TT_IA16);
            }
            if (paletteChanged) {
                     gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, palette);      gDPTileSync(g_displayListCursor++);      gDPSetTile(g_displayListCursor++, 0, 0, 0, 256, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);      gDPLoadSync(g_displayListCursor++);      gDPLoadTLUTCmd(g_displayListCursor++, G_TX_LOADTILE, 15);      gDPPipeSync(g_displayListCursor++);
            }
            break;
        case 2:
            if (changed) {
                {      gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, texture);      gDPSetTile(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0, 0, G_TX_LOADTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);      gDPLoadSync(g_displayListCursor++);      gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((((1 << info[2]) * (1 << info[3]) + (0)) >> (0)) - 1) < 2047 ? ((((1 << info[2]) * (1 << info[3]) + (0)) >> (0)) - 1) : 2047), (((1 << G_TX_DXT_FRAC) + (1 > ((4) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (4)) / 8)) ? 1 : ((4) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (4)) / 8))) - 1) / (1 > ((4) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (4)) / 8)) ? 1 : ((4) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (4)) / 8)))));      gDPPipeSync(g_displayListCursor++);      gDPSetTile(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_32b, ((2 << info[2]) + 7) >> 3, 0, G_TX_RENDERTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);      gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, ((1 << info[2]) - 1) << 2, ((1 << info[3]) - 1) << 2); };
                gDPSetTextureLUT(g_displayListCursor++, G_TT_NONE);
            }
            break;
        case 4:
            if (changed) {
                gDPPipeSync(g_displayListCursor++);
                gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture);
                switch (info[5]) {
                case 2:
                default:
                    list = g_textureFrameAlternateDisplayList;
                    break;
                case 3:
                    list = g_textureFramePaletteDisplayList;
                    break;
                case 1:
                    gDPSetTextureDetail(g_displayListCursor++, G_TD_SHARPEN);
                    list = g_textureFrameDefaultDisplayList;
                    if (wrapS & 1) list = g_textureFrameWrappedDisplayList;
                    break;
                case 0:
                    gDPSetTextureDetail(g_displayListCursor++, G_TD_CLAMP);
                    list = g_textureFrameDefaultDisplayList;
                    if (wrapS & 1) list = g_textureFrameWrappedDisplayList;
                    break;
                }
                gSPDisplayList(g_displayListCursor++, list);
            }
            break;
        case 5:
            if (changed) {
                gDPPipeSync(g_displayListCursor++);
                gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_16b, 1, texture);
                gSPDisplayList(g_displayListCursor++, g_enemyConstantWordsBlock5);
            }
            break;
        }
    } else {
        gDPPipeSync(g_displayListCursor++);
    }
    switch (info[0]) {
    case 4: level = 5; tile = 0; break;
    case 5: level = 6; tile = 0; break;
    default: level = 0; tile = 0; break;
    }
    gSPTexture(g_displayListCursor++, scaleS, scaleT, level, tile, G_ON);
}
#endif
