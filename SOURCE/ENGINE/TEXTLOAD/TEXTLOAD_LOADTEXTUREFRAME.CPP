#include "../../../sdk/include/LIBC.H"
#include "include_asm.h"
#include "TYPES.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "COMMON/PPDECOM_UNPACKRESOURCE.H"
#include "ENGINE/CACHE/CACHE.H"
#include "ENGINE/SETN64.H"
#include "TEXTURE/TEXTLOAD_LOADTEXTUREFRAME.H"
#include "TEXTURE/TEXTLOAD_LOADTEXTUREFRAMETILES.H"

extern unsigned int g_texturePaletteOverrideEnabled;




extern s32 **Cache_AllocResourceBlock(s32, void *, s32);



typedef struct {
    s32 **handle;
    s32 reservedWord;
    u32 flags;
} Resource;

/* Recolours the RGBA5551 frames of a resource by the global or per-resource colour mode, then rebuilds it as a three-part block holding the header, one selected entry of list 1 and one of list 2. */
void Textload_PrepareTextureVariation(s32 textureResource, Resource *handle) {
    u32 size;
    s32 rem1;
    s32 rem2;
    s32 *obj;
    s32 *list2;
    s32 *list1;
    s32 count;
    s32 mode;
    s32 i;
    s32 j;
    s32 n;
    s32 kind;
    s32 len0;
    s32 len1;
    s32 len2;
    s32 off1;
    s32 off2;
    s32 total;
    s32 **res;
    s32 *hdr;
    s32 *entry;

    if (Ppdecom_UnpackResource(handle, textureResource >= 0) == 0) {
        return;
    }
    obj = *handle->handle;
    if (*obj == 0) {
        return;
    }
    list2 = SetN64_GetPackSection(obj, 2);
    count = *list2;
    if (count != 0) {
        rem2 = textureResource % count;
    } else {
        rem2 = 0;
    }
    list1 = SetN64_GetPackSection(obj, 1);
    rem1 = textureResource % *list1;
    if (g_texturePaletteOverrideEnabled != 0) {
        mode = 4;
    } else {
        mode = handle->flags >> 30;
    }
    if (mode != 0) {
        kind = *(u8 *)SetN64_GetPackSection(obj, 0);
        if (kind < 2) if (kind >= 0) {
            for (i = 0; i < count; i++) {
                u16 *data = SetN64_GetSizedPackSection(list2, i, &size);
                n = size >> 1;
                for (j = 0; j < n; j++) {
                    u32 r = (data[j] >> 8) & 0xF8;
                    u32 g = (data[j] >> 3) & 0xF8;
                    u32 b = (data[j] << 2) & 0xF8;
                    u32 a = data[j] & 1;
                    switch (mode) {
                    case 1:
                        data[j] = (g << 8) | (r << 3) | (b >> 2) | a;
                        break;
                    case 2:
                        data[j] = (r << 8) | (r << 3) | (b >> 2) | a;
                        break;
                    case 3:
                        data[j] = (g << 8) | (g << 3) | (b >> 2) | a;
                        break;
                    case 4:
                        data[j] = (r + b + g) / 12 | a;
                        break;
                    }
                }
            }
        }
    }
    if (textureResource < 0) {
        return;
    }
    len0 = SetN64_GetPackSectionSize(obj, 0);
    len1 = SetN64_GetPackSectionSize(list1, rem1) + 16;
    if (count != 0) {
        len2 = SetN64_GetPackSectionSize(list2, rem2) + 16;
    } else {
        len2 = 8;
    }
    total = ((len0 + 7) & ~7) + 24;
    off1 = total;
    total += (len1 + 7) & ~7;
    off2 = total;
    total += (len2 + 7) & ~7;
    res = Cache_AllocResourceBlock(0, handle, total);
    if (res != 0) {
        hdr = *res;
        hdr[0] = 3;
        hdr[1] = 24;
        hdr[2] = off1;
        hdr[3] = off2;
        Libc_CopyBytes(SetN64_GetPackSection(hdr, 0), SetN64_GetPackSection(obj, 0), SetN64_GetPackSectionSize(obj, 0));
        entry = SetN64_GetPackSection(hdr, 1);
        entry[0] = 1;
        entry[1] = 16;
        Libc_CopyBytes(SetN64_GetPackSection(entry, 0), SetN64_GetPackSection(list1, rem1), SetN64_GetPackSectionSize(list1, rem1));
        entry = SetN64_GetPackSection(hdr, 2);
        if (count != 0) {
            entry[0] = 1;
            entry[1] = 16;
            Libc_CopyBytes(SetN64_GetPackSection(entry, 0), SetN64_GetPackSection(list2, rem2), SetN64_GetPackSectionSize(list2, rem2));
        } else {
            entry[0] = 0;
        }
    }
    Cache_ReplaceResourceBlock(0, handle, res);
}

#if !(defined(VERSION_US_REV1))
#include <ultra64.h>
#include <PR/gbi.h>

extern void Cache_MarkResourceInUse(s32, struct CacheResourceNode *);
extern Gfx *g_displayListCursor;
extern int g_textureCacheResource;
extern s32 g_textureCacheFrame;
extern s32 g_textureCacheVariation;
extern s32 g_textureCacheWrapS;
extern s32 g_textureCacheWrapT;
extern Gfx g_textureTileDefaultDisplayList[16], g_textureTileWrappedDisplayList[16], g_textureTileAlternateDisplayList[19], g_textureTilePaletteDisplayList[19], g_textureTileFinishDisplayList[19];

/* Non-rev1 copy of Textload_LoadTextureFrameTiles (the texture state setter): the same gDP texture/TLUT load per header
   format, without rev1's two resource relocation calls before the switch. */
void Textload_LoadTextureFrame(s32 *output, void **resource, s32 frame, s32 secondary, s32 scaleS, s32 scaleT, s32 wrapS, s32 wrapT, s32 mode) {
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
        if (g_textureCacheResource != (s32)resource || g_textureCacheVariation != secondary) paletteChanged = 1;
    } else {
        paletteChanged = 0;
        palette = 0;
    }
    changed = 0;
    if (g_textureCacheResource != (s32)resource || g_textureCacheFrame != frame || g_textureCacheWrapS != wrapS || g_textureCacheWrapT != wrapT) {
        changed = 1;
    }
    if (changed || paletteChanged) {
        g_textureCacheResource = (s32)resource;
        g_textureCacheFrame = frame;
        g_textureCacheVariation = secondary;
        g_textureCacheWrapS = wrapS;
        g_textureCacheWrapT = wrapT;
        maskS = 0;
        if (!(wrapS & G_TX_CLAMP)) {
            maskS = info[2];
        }
        maskT = 0;
        if (!(wrapT & G_TX_CLAMP)) {
            maskT = info[3];
        }
        switch (info[0]) {
        case 0:
            if (changed) {
                gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 1, texture);
                gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);
                gDPLoadSync(g_displayListCursor++);
                gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((((1 << info[2]) * (1 << info[3]) + (1)) >> (1)) - 1) < 2047 ? ((((1 << info[2]) * (1 << info[3]) + (1)) >> (1)) - 1) : 2047), (((1 << G_TX_DXT_FRAC) + (1 > ((1) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (1)) / 8)) ? 1 : ((1) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (1)) / 8))) - 1) / (1 > ((1) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (1)) / 8)) ? 1 : ((1) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (1)) / 8)))));
                gDPPipeSync(g_displayListCursor++);
                gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_8b, ((1 << info[2]) + 7) >> 3, 0, G_TX_RENDERTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);
                gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, ((1 << info[2]) - 1) << 2, ((1 << info[3]) - 1) << 2);
                gDPSetTextureLUT(g_displayListCursor++, G_TT_RGBA16);
            }
            if (paletteChanged) {
                gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, palette);
                gDPTileSync(g_displayListCursor++);
                gDPSetTile(g_displayListCursor++, 0, 0, 0, 256, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
                gDPLoadSync(g_displayListCursor++);
                gDPLoadTLUTCmd(g_displayListCursor++, G_TX_LOADTILE, 255);
                gDPPipeSync(g_displayListCursor++);
            }
            break;
        case 1:
            if (changed) {
                gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 1, texture);
                gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);
                gDPLoadSync(g_displayListCursor++);
                gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((((1 << info[2]) * (1 << info[3]) + (3)) >> (2)) - 1) < 2047 ? ((((1 << info[2]) * (1 << info[3]) + (3)) >> (2)) - 1) : 2047), (((1 << G_TX_DXT_FRAC) + (1 > ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8)) ? 1 : ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8))) - 1) / (1 > ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8)) ? 1 : ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8)))));
                gDPPipeSync(g_displayListCursor++);
                gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_4b, (((1 << info[2]) >> 1) + 7) >> 3, 0, G_TX_RENDERTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);
                gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, ((1 << info[2]) - 1) << 2, ((1 << info[3]) - 1) << 2);
                gDPSetTextureLUT(g_displayListCursor++, G_TT_RGBA16);
            }
            if (paletteChanged) {
                gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, palette);
                gDPTileSync(g_displayListCursor++);
                gDPSetTile(g_displayListCursor++, 0, 0, 0, 256, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
                gDPLoadSync(g_displayListCursor++);
                gDPLoadTLUTCmd(g_displayListCursor++, G_TX_LOADTILE, 15);
                gDPPipeSync(g_displayListCursor++);
            }
            break;
        case 3:
            if (changed) {
                gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 1, texture);
                gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);
                gDPLoadSync(g_displayListCursor++);
                gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((((1 << info[2]) * (1 << info[3]) + (3)) >> (2)) - 1) < 2047 ? ((((1 << info[2]) * (1 << info[3]) + (3)) >> (2)) - 1) : 2047), (((1 << G_TX_DXT_FRAC) + (1 > ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8)) ? 1 : ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8))) - 1) / (1 > ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8)) ? 1 : ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8)))));
                gDPPipeSync(g_displayListCursor++);
                gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_4b, (((1 << info[2]) >> 1) + 7) >> 3, 0, G_TX_RENDERTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);
                gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, ((1 << info[2]) - 1) << 2, ((1 << info[3]) - 1) << 2);
                gDPSetTextureLUT(g_displayListCursor++, G_TT_IA16);
            }
            if (paletteChanged) {
                gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, palette);
                gDPTileSync(g_displayListCursor++);
                gDPSetTile(g_displayListCursor++, 0, 0, 0, 256, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
                gDPLoadSync(g_displayListCursor++);
                gDPLoadTLUTCmd(g_displayListCursor++, G_TX_LOADTILE, 15);
                gDPPipeSync(g_displayListCursor++);
            }
            break;
        case 2:
            if (changed) {
                gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, texture);
                gDPSetTile(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0, 0, G_TX_LOADTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);
                gDPLoadSync(g_displayListCursor++);
                gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((((1 << info[2]) * (1 << info[3]) + (0)) >> (0)) - 1) < 2047 ? ((((1 << info[2]) * (1 << info[3]) + (0)) >> (0)) - 1) : 2047), (((1 << G_TX_DXT_FRAC) + (1 > ((4) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (4)) / 8)) ? 1 : ((4) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (4)) / 8))) - 1) / (1 > ((4) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (4)) / 8)) ? 1 : ((4) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (4)) / 8)))));
                gDPPipeSync(g_displayListCursor++);
                gDPSetTile(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_32b, ((2 << info[2]) + 7) >> 3, 0, G_TX_RENDERTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);
                gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, ((1 << info[2]) - 1) << 2, ((1 << info[3]) - 1) << 2);
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
                    list = g_textureTileAlternateDisplayList;
                    break;
                case 3:
                    list = g_textureTilePaletteDisplayList;
                    break;
                case 1:
                    gDPSetTextureDetail(g_displayListCursor++, G_TD_SHARPEN);
                    list = g_textureTileDefaultDisplayList;
                    if (wrapS & 1) list = g_textureTileWrappedDisplayList;
                    break;
                case 0:
                    gDPSetTextureDetail(g_displayListCursor++, G_TD_CLAMP);
                    list = g_textureTileDefaultDisplayList;
                    if (wrapS & 1) list = g_textureTileWrappedDisplayList;
                    break;
                }
                gSPDisplayList(g_displayListCursor++, list);
            }
            break;
        case 5:
            if (changed) {
                gDPPipeSync(g_displayListCursor++);
                gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_16b, 1, texture);
                gSPDisplayList(g_displayListCursor++, g_textureTileFinishDisplayList);
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
