#include "LIBC.H"
#include "include_asm.h"
#include "types.h"
#include "Render/setn64_getpacksection.h"
#include "Common/ppdecom_unpackresource.h"
#include "Engine/Cache/cache.h"
#include "Engine/session.h"
#include "Texture/textload_loadtextureframe.h"
#include "Texture/textload_loadtextureframetiles.h"
#include "Engine/cache.h"
#include "Common/scene_frame_and_effect_updates.h"
#include "Engine/textload.h"
#include "Common/sessionhandlerrow.h"
#if !(defined(VERSION_US_REV1))
#include <platform_sdk.h>
#endif
#if !(defined(VERSION_US_REV1))
#include <PR/gbi.h>
#endif
#include "Common/residentstate.h"
#include "Common/texture_request.h"
#include "Common/world.h"
#include "Textload/textload_locatetextureresource.h"
#include "Textload/textload_requesttexturevariationsync.h"
#include "Textload/textload_readtextureanimationinfo.h"
#include "Common/frustum.h"
#include "Common/runtime_declarations.h"
#include "System/textload_resettexturecache.h"
#include "Render/resident_texture_menu_views.h"
#include "Ui/X_files/x_plus.h"
#include "Engine/tengine.h"
#include "Common/resident_event_handler.h"
#include "Scene/cache_allocateresourceat.h"
#include <platform_sdk.h>
#include <PR/gbi.h>
#if defined(VERSION_US_REV1)
#include "Common/runtime_declarations.h"
#endif
#if defined(VERSION_US_REV1)
#include "Common/sessionhandlerrow.h"
#endif
#if defined(VERSION_US_REV1)
#include "Common/residentstate.h"
#endif
#if defined(VERSION_US_REV1)
#include "Render/setn64_getpacksection.h"
#endif
#if defined(VERSION_US_REV1)
#include "Texture/textload_loadtextureframetiles.h"
#endif
#if defined(VERSION_US_REV1)
#include "Common/scene_frame_and_effect_updates.h"
#endif
#if defined(VERSION_US_REV1)
#include "Engine/textload.h"
#endif
#include "Common/rotation_extraction.h"
#include "Textload/s_texturetext.h"

/* TEXTLOAD_LOADTEXTUREFRAME.CPP */


/* Recolours the RGBA5551 frames of a resource by the global or per-resource colour mode, then rebuilds it as a three-part block holding the header, one selected entry of list 1 and one of list 2. */
void Textload_PrepareTextureVariation(s32 textureResource, TextureVariationResource *handle) {
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

/* TEXTLOAD_LOCATETEXTURERESOURCE.CPP */

/** Store two words into a two-word value. */
void Textload_SetResourceLocation(int *value, int first, int second) {
    value[0] = first;
    value[1] = second;
}

void Textload_LocateTextureResource(s32 *resourcePair, s32 sectionIndex) {
    Scene_LocateTextureResource(&g_world, sectionIndex, resourcePair, resourcePair + 1);
}

/* TEXTLOAD_REQUESTTEXTUREVARIATIONSYNC.CPP */

/* Request a texture resource with synchronous loading. */
void **Textload_RequestTextureVariationSync(s32 *resource, s32 variation)
{
    return rw_request_texture_sync(resource, variation);
}

/* Request a texture resource with asynchronous loading. */
s32 **Textload_RequestTextureVariation(s32 *resource, s32 variation)
{
    return rw_request_texture(resource, variation, 0);
}

/* TEXTLOAD_READTEXTUREANIMATIONINFO.CPP */





void Textload_ReadTextureAnimationInfo(s32 **textureResource, Shared_AnimInfo *animInfo) {
    s32 *texturePack;
    s32 *packWord;

    texturePack = *textureResource;
    if (*texturePack != 0) {
        animInfo->frame = SetN64_GetPackSection(texturePack, 0);
        packWord = SetN64_GetPackSection(texturePack, 1);
        animInfo->count = *packWord;
        packWord = SetN64_GetPackSection(texturePack, 2);
        animInfo->variationCount = *packWord;
        return;
    }
    animInfo->frame = 0;
    animInfo->count = 0;
    animInfo->variationCount = 0;
}

/* TEXTLOAD_RESETTEXTURECACHE.CPP */

/** Clear the global word. */

void TextLoad_ResetTextureCache(void) {
    g_textureCacheResource = 0;
}


/** Replace the global state word. */
void Textload_SetTextureEffect(unsigned int value) {
    g_texturePaletteOverrideEnabled = value;
}

/* TEXTLOAD.CPP */

#if defined(VERSION_US_REV1)

void TextLoad_ResetArtsendTextureState(void) {
    s32 *base = &g_artsendTextureSelection;

    g_artsendTextureViewer.alternateTitle = 0;
    g_artsendTextureViewerState = 0;
    g_artsendTextureSelectionIndex = 0;
    g_artsendTextureFrameSelection = 0;
    *base = 1;
    g_artsendTextureViewerReservedWord = 0;
    g_artsendTextureSelectionChanged = 0;
    g_artsendSelectedTextureResource.resource = 0;
    g_artsendTextureResetWordA = 0;
    g_artsendTextureResetWordB = 0;
    g_artsendActionMappingSelection = 0;
    g_artsendTextureViewerEntryTable = 0;
    g_artsendTextureViewerTextureTable = 0;
    g_artsendTextureViewerPaletteTable = 0;
    g_artsendTextureViewerFrameCount = 0;

    XPlus_FillMemory((s32)(base + 9), 0, 0x2000);
    XPlus_FillMemory((s32)(base + 0x809), 0xFF, 0x100);

    *base = *g_textureResourceSectionRoot;
}
#endif

#if defined(VERSION_US_REV1)
void TextLoad_CloseArtsendTexturePreview(void) { TextLoad_ReleaseArtsendTextureResource(); }
#endif

#if defined(VERSION_US_REV1)
/** Report the global count only while its enable byte is set. */
int TextLoad_IsArtsendTexturePreviewEnabled(void) {
    int result = 0;
    if (g_artsendTextureViewer.alternateTitle != 0) {
        result = g_textureVariationBypassEnabled != 0;
    }
    return result;
}
#endif

#if defined(VERSION_US_REV1)

void TextLoad_ApplyArtsendTextureOverride(s32 resource, s32 **texture) {
    s32 enabled;
    s32 choose;

    if ((g_textureVariationBypassEnabled != 0) && (*texture != 0) && (*(s32 *)&g_artsendTextureViewerOverridesOff == 0)) {
        enabled = 0;
        if (g_artsendTextureViewer.alternateTitle != 0) {
            enabled = (u32)g_textureVariationBypassEnabled > 0U;
        }
        if (enabled != 0) {
            choose = (g_artsendTextureViewerOverridesOff.reservedWord % 10) < 3;
        } else {
            choose = 1;
        }
        if (resource == (s32)g_artsendTextureViewer.resource) {
            if (choose != 0) {
                *texture = &g_artsendTextureViewer.textureData[0];
                return;
            }
            *texture = g_artsendTextureViewer.textureOverride;
        }
    }
}
#endif

#if defined(VERSION_US_REV1)

void TextLoad_ApplyArtsendPaletteOverride(s32 resource, s32 **palette) {
    s32 paletteOverrideEnabled;
    s32 paletteOverrideSelected;

    if ((g_textureVariationBypassEnabled != 0) && (*palette != 0)) {
        if (*(s32 *)&g_artsendTextureViewerOverridesOff != 0) {
            return;
        }
        paletteOverrideEnabled = 0;
        if (g_artsendTextureViewer.alternateTitle != 0) {
            paletteOverrideEnabled = (u32)g_textureVariationBypassEnabled > 0U;
        }
        if (paletteOverrideEnabled != 0) {
            paletteOverrideSelected = (g_artsendTextureViewerOverridesOff.reservedWord % 10) < 3;
        } else {
            paletteOverrideSelected = 1;
        }
        if (resource == (s32)g_artsendTextureViewer.resource) {
            if (paletteOverrideSelected != 0) {
                *palette = &g_artsendTextureViewer.paletteData[0];
                return;
            }
            *palette = g_artsendTextureViewer.paletteOverride;
        }
    }
}

void TextLoad_SelectNextArtsendTexture(void) {
    s32 requestedTexture;

    if (g_artsendNextTextureHoldCount++ >= 3) {
        requestedTexture = g_artsendTextureSelection.index + 1;
        g_artsendNextTextureHoldCount = 0;
        g_artsendTextureSelection.changed = 1;
        g_artsendTextureSelection.index = requestedTexture;
        g_artsendTextureSelection.index = requestedTexture % g_artsendTextureSelection.count;
    }
}
#endif

#if defined(VERSION_US_REV1)

void TextLoad_SelectPreviousArtsendTexture(void) {
    s32 requestedTexture;
    s32 positiveTexture;
    s32 wrappedTexture;
    s32 *p;
    s32 old;

    old = g_artsendPreviousTextureHoldCount++;
    if (old >= 3) {
        p = &g_artsendTextureViewer.selectionIndex;
        requestedTexture = p[0] - 1;
        positiveTexture = requestedTexture + p[-1];
        wrappedTexture = positiveTexture % p[-1];
        p[2] = 1;
        *(volatile s32 *)&p[0] = requestedTexture;
        p[0] = wrappedTexture;
        if ((f32) wrappedTexture < 0.0f) {
            wrappedTexture = -wrappedTexture;
        }
        p[0] = wrappedTexture;
        g_artsendPreviousTextureHoldCount = 0;
    }
}

void TextLoad_ReleaseArtsendTextureResource(void) {
    if (g_artsendTextureViewer.resource != 0) {
        Cache_UnlockResource(0, g_artsendTextureViewer.resource);
    }
    g_artsendTextureViewer.resource = 0;
    g_artsendTextureViewer.textureOverride = 0;
    g_artsendTextureViewer.paletteOverride = 0;
    g_artsendTextureViewer.selector = 0;
}

/** Reset the record's fields, marking slot 1 active. */
void TextLoad_InitializeArtsendPreviewState(void) {
    struct ArtsendTextureMenuState *object = &g_artsendTextureViewer;

    object->alternateTitle = 0;
    object->state = 0;
    object->selectionIndex = 0;
    object->selectionValue = 0;
    object->active = 1;
    object->reservedWord = 0;
    object->titleWasShown = 0;
    object->resource = 0;
    object->textureOverride = 0;
    object->paletteOverride = 0;
    object->selector = 0;
    object->entryTable = 0;
    object->textureTable = 0;
    object->paletteTable = 0;
    object->frameCount = 0;
}

void TextLoad_DecreaseArtsendSelectionValue(void) {
    s32 *ptr;
    s32 old;
    s32 count;

    ptr = &g_artsendPreviousFrameHoldCount;
    old = (*ptr)++;
    if (old >= 3) {
        count = g_artsendTextureViewer.selectionValue;
        g_artsendTextureViewer.titleWasShown = 1;
        g_artsendPreviousFrameHoldCount = 0;
        g_artsendTextureViewer.selectionValue = count - 1;
    }
}

void TextLoad_IncreaseArtsendSelectionValue(void) {
    s32 *ptr;
    s32 old;
    s32 count;

    ptr = &g_artsendNextFrameHoldCount;
    old = (*ptr)++;
    if (old >= 3) {
        count = g_artsendTextureViewer.selectionValue;
        g_artsendTextureViewer.titleWasShown = 1;
        g_artsendNextFrameHoldCount = 0;
        g_artsendTextureViewer.selectionValue = count + 1;
    }
}

void TextLoad_SelectPreviousArtsendPage(void) {
    s32 requestedPage;
    s32 positivePage;
    s32 wrappedPage;
    s32 *p;
    s32 old;

    old = g_artsendPreviousPageHoldCount++;
    if (old >= 3) {
        p = &g_artsendTextureViewer.selectionIndex;
        requestedPage = p[0] - 5;
        positivePage = requestedPage + p[-1];
        wrappedPage = positivePage % p[-1];
        *(volatile s32 *)&p[0] = requestedPage;
        p[0] = wrappedPage;
        if ((f32) wrappedPage < 0.0f) {
            wrappedPage = -wrappedPage;
        }
        p[0] = wrappedPage;
        p[2] = 1;
        g_artsendPreviousPageHoldCount = 0;
    }
}
#endif

#if defined(VERSION_US_REV1)
/** Return the texture override pointer of the menu state. */

/* Handles one held press of the menu "next page" key: g_artsendNextPageHoldCount counts the held presses, and on the
 * fourth one the selection index g_artsendTextureViewer.selectionIndex is stepped up by five modulo the menu item count; the
 * pre-modulo index store is kept as the original program does, and the change flag word at +8 from
 * the index is set. */

void TextLoad_SelectNextArtsendPage(void) {
    s32 requestedPage;
    s32 pageCount;
    s32 wrappedPage;
    s32 *p;
    s32 old;

    old = g_artsendNextPageHoldCount++;
    if (old >= 3) {
        p = &g_artsendTextureViewer.selectionIndex;
        requestedPage = p[0] + 5;
        pageCount = p[-1];
        wrappedPage = requestedPage % pageCount;
        g_artsendNextPageHoldCount = 0;
        p[2] = 1;
        *(volatile s32 *)&p[0] = requestedPage;
        p[0] = wrappedPage;
    }
}

int TextLoad_GetArtsendTextureOverride(void) {
    return (int)g_artsendTextureViewer.textureOverride;
}

int TextLoad_GetArtsendPaletteOverride(void) {
    return (int)g_artsendTextureViewer.paletteOverride;
}

/** Compute a bit mask from the byte of the global record. */
int TextLoad_GetArtsendPrimaryButtonMask(void) {
    return 1 << g_artsendTextureViewer.selector->primaryButton;
}

int TextLoad_GetArtsendSecondaryButtonMask(void) {
    unsigned char shift = g_artsendTextureViewer.selector->secondaryButton;
    return 1 << shift;
}

/** Return the mode mask selected by the global record's leading byte. */
int TextLoad_GetArtsendModeMask(void) {
    {
        int swModeValue = g_artsendTextureViewer.selector->mode;
        if ((unsigned int)swModeValue > 5) {
            goto sw_mode_default;
        }
        switch (swModeValue) {
        case 0: goto sw_mode_0;
        case 1: goto sw_mode_1;
        case 2: goto sw_mode_2;
        case 3: goto sw_mode_1;
        case 4: goto sw_mode_4;
        case 5: goto sw_mode_1;
        }
    }
    do {
    sw_mode_0:
        return 8;
    sw_mode_1:
    sw_mode_3:
    sw_mode_5:
        return 4;
    sw_mode_2:
        return 32;
    sw_mode_4:
        return 16;
    sw_mode_default:
        return 0;

    } while (0);
}
#endif

/* TEXTLOAD_LOADTEXTUREFRAMETILES.CPP */

#if defined(VERSION_US_REV1)
/* Preserve the original SDK shift expression used by the texture commands. */



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
                {
                    gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 1, texture);
                    gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);
                    gDPLoadSync(g_displayListCursor++);
                    gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((((1 << info[2]) * (1 << info[3]) + (1)) >> (1)) - 1) < 2047 ? ((((1 << info[2]) * (1 << info[3]) + (1)) >> (1)) - 1) : 2047), (((1 << G_TX_DXT_FRAC) + (1 > ((1) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (1)) / 8)) ? 1 : ((1) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (1)) / 8))) - 1) / (1 > ((1) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (1)) / 8)) ? 1 : ((1) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (1)) / 8)))));
                    gDPPipeSync(g_displayListCursor++);
                    gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_8b, ((1 << info[2]) + 7) >> 3, 0, G_TX_RENDERTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);
                    gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, ((1 << info[2]) - 1) << 2, ((1 << info[3]) - 1) << 2); };
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
                {
                    gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 1, texture);
                    gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);
                    gDPLoadSync(g_displayListCursor++);
                    gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((((1 << info[2]) * (1 << info[3]) + (3)) >> (2)) - 1) < 2047 ? ((((1 << info[2]) * (1 << info[3]) + (3)) >> (2)) - 1) : 2047), (((1 << G_TX_DXT_FRAC) + (1 > ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8)) ? 1 : ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8))) - 1) / (1 > ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8)) ? 1 : ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8)))));
                    gDPPipeSync(g_displayListCursor++);
                    gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_4b, (((1 << info[2]) >> 1) + 7) >> 3, 0, G_TX_RENDERTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);
                    gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, ((1 << info[2]) - 1) << 2, ((1 << info[3]) - 1) << 2); };
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
                {
                    gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 1, texture);
                    gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);
                    gDPLoadSync(g_displayListCursor++);
                    gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((((1 << info[2]) * (1 << info[3]) + (3)) >> (2)) - 1) < 2047 ? ((((1 << info[2]) * (1 << info[3]) + (3)) >> (2)) - 1) : 2047), (((1 << G_TX_DXT_FRAC) + (1 > ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8)) ? 1 : ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8))) - 1) / (1 > ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8)) ? 1 : ((0) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (0)) / 8)))));
                    gDPPipeSync(g_displayListCursor++);
                    gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_4b, (((1 << info[2]) >> 1) + 7) >> 3, 0, G_TX_RENDERTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);
                    gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, ((1 << info[2]) - 1) << 2, ((1 << info[3]) - 1) << 2); };
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
                {
                    gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, texture);
                    gDPSetTile(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0, 0, G_TX_LOADTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);
                    gDPLoadSync(g_displayListCursor++);
                    gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, (((((1 << info[2]) * (1 << info[3]) + (0)) >> (0)) - 1) < 2047 ? ((((1 << info[2]) * (1 << info[3]) + (0)) >> (0)) - 1) : 2047), (((1 << G_TX_DXT_FRAC) + (1 > ((4) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (4)) / 8)) ? 1 : ((4) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (4)) / 8))) - 1) / (1 > ((4) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (4)) / 8)) ? 1 : ((4) == 0 ? ((1 << info[2]) / 16) : (((1 << info[2]) * (4)) / 8)))));
                    gDPPipeSync(g_displayListCursor++);
                    gDPSetTile(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_32b, ((2 << info[2]) + 7) >> 3, 0, G_TX_RENDERTILE, 0, wrapT, maskT, mode, wrapS, maskS, mode);
                    gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, ((1 << info[2]) - 1) << 2, ((1 << info[3]) - 1) << 2); };
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
                gSPDisplayList(g_displayListCursor++, g_textureFrameIntensityMipmapDisplayList);
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

/* TEXTLOAD_REQUESTTEXTUREVARIATIONSYNC_DATA.CPP */

#if !(defined(VERSION_US_REV1))
const char g_textloadTextureText[8] =
    "texture\000";
#endif

/* S_TEXTURETEXT.CPP */

#if defined(VERSION_US_REV1)
const char s_textureText[8] =
    "texture";
#endif
