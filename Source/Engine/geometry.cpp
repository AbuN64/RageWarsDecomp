#include "Render/rangenode.h"
#include "Anim/animation_frame.h"
#include "Common/scene_frame_and_effect_updates.h"
#include "Engine/geometry.h"
#include "Render/material_color_and_fog_views.h"
#include "Render/rangenode.h"
#include "types.h"
#include <platform_sdk.h>
#include <PR/gbi.h>
#include "Textload/textload_readtextureanimationinfo.h"
#include "Textload/textload_requesttexturevariationsync.h"
#include "Texture/textload_loadtextureframe.h"
#include "Texture/textload_loadtextureframetiles.h"
#include "Common/sessionhandlerrow.h"
#include "System/textload_resettexturecache.h"
#include "Scene/cache_allocateresourceat.h"
#include "Common/self.h"
#include "Render/player_controller_reset_views.h"
#include "LIBC.H"
#include "include_asm.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Common/sharedplayer.h"
#include "Common/resident_event_handler.h"
#include "Common/ppdecom_unpackresource.h"
#include "Common/localdecoderange.h"
#include "Common/frustum.h"
#include "Common/shared_gameslot.h"
#include "Common/rendercounters.h"
#include "Render/rumble_expandmeshmaterial.h"
#include "Fx/normalize_vector.h"
#include "Render/setn64_getpacksection.h"
#include "Ai/Player/playerai_findtransientplayer.h"
#include "Engine/Cache/cache.h"
#include "Engine/session.h"
#include "Game/builddirectionmatrix.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Engine/cache.h"
#include "Common/approachlocation.h"
#include "Common/game_session.h"
#include "Common/aiprofile.h"
#include "Common/packedmeshmaterial.h"
#include "Common/display.h"
#include "Engine/graphics_math.h"
#include "Common/runtime_declarations.h"
#include <PR/abi.h>
#include "Scene/cache_requestresource.h"
#include "Common/objb.h"
#include "Common/model_render.h"
#include "Ui/X_files/x_plus.h"
#include "Common/frontend_clock_state.h"
#include "Common/material_tree.h"
#include "Geometry/geometry_drawblendparts.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
#include "Common/graphics_matrix_and_vector_math.h"
#include "Engine/textload.h"
#include "Data/Overlays/encoded_callback.h"
#include "Data/Overlays/Actor/resources_addresses.h"
#include "Common/effectcontribution.h"
#include "Data/rest_source_records.h"
#include "Engine/events.h"
#include "Data/Overlays/Actor/constants_addresses.h"
#include "data_overlay_layouts.h"
#include "Data/Enemy/events_delivercontacteffect_data.h"
#include "System/engine_data_source.h"
#include "System/contact_effect.h"

/* GEOMETRY_SETUPMATERIAL.CPP */

/* Selects a cached RDP color-combiner mode and emits the corresponding display-list command. */
void Geometry_SetCombineMode(u32 mode) {
 if (g_geometryPreviousModePreset != mode) {
 g_geometryPreviousModePreset=mode;
 switch(mode) {
 case 0: gDPSetCombineLERP(g_displayListCursor++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, SHADE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED); break;
 case 1: gDPSetCombineLERP(g_displayListCursor++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, SHADE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, COMBINED, 0, ENVIRONMENT, 0); break;
 case 2: gDPSetCombineLERP(g_displayListCursor++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED); break;
 case 3: gDPSetCombineLERP(g_displayListCursor++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, SHADE, 0, TEXEL0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED); break;
 case 4: gDPSetCombineLERP(g_displayListCursor++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED); break;
 case 5: gDPSetCombineLERP(g_displayListCursor++, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, SHADE); break;
 case 6: gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED); break;
 case 7: gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, COMBINED, 0, ENVIRONMENT, 0); break;
 case 8: gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, ENVIRONMENT, COMBINED, ENV_ALPHA, COMBINED, 0, 0, 0, COMBINED); break;
 case 9: gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, ENVIRONMENT, COMBINED, SHADE, COMBINED, 0, 0, 0, COMBINED); break;
 case 10: gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, ENVIRONMENT, COMBINED, 0, ENVIRONMENT, 0); break;
 case 11: gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, ENVIRONMENT, COMBINED, ENV_ALPHA, COMBINED, COMBINED, 0, PRIMITIVE, 0); break;
 case 12: gDPSetCombineLERP(g_displayListCursor++, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, SHADE); break;
 case 13: gDPSetCombineLERP(g_displayListCursor++, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED); break;
 case 14: gDPSetCombineLERP(g_displayListCursor++, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, COMBINED, 0, ENVIRONMENT, 0); break;
 case 15: gDPSetCombineLERP(g_displayListCursor++, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, ENVIRONMENT, COMBINED, ENV_ALPHA, COMBINED, 0, 0, 0, COMBINED); break;
 case 16: gDPSetCombineLERP(g_displayListCursor++, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, ENVIRONMENT, COMBINED, 0, ENVIRONMENT, 0); break;
 case 17: gDPSetCombineLERP(g_displayListCursor++, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, ENVIRONMENT, COMBINED, ENV_ALPHA, COMBINED, COMBINED, 0, PRIMITIVE, 0); break;
 case 18: gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED); break;
 case 19: gDPSetCombineLERP(g_displayListCursor++, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED); break;
 case 20: gDPSetCombineLERP(g_displayListCursor++, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, COMBINED, 0, ENVIRONMENT, 0); break;
 case 21: gDPSetCombineLERP(g_displayListCursor++, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, ENVIRONMENT, COMBINED, ENV_ALPHA, COMBINED, 0, 0, 0, COMBINED); break;
 case 22: gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, ENVIRONMENT, COMBINED, SHADE, COMBINED, 0, 0, 0, COMBINED); break;
 case 23: gDPSetCombineLERP(g_displayListCursor++, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, 0, 0, 0, ENVIRONMENT, COMBINED, 0, ENVIRONMENT, 0); break;
 case 24: gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0); break;
 case 25: gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE); break;
 case 26: gDPSetCombineLERP(g_displayListCursor++, ENVIRONMENT, PRIMITIVE, TEXEL1, PRIMITIVE, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED); break;
 case 27: gDPSetCombineLERP(g_displayListCursor++, TEXEL0, 0, ENVIRONMENT, 0, TEXEL1, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED); break;
 case 28: gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE); break;
 case 29: gDPSetCombineLERP(g_displayListCursor++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0); break;
 case 30: gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, PRIMITIVE, 0, 0, 0, 1, 0, 0, 0, PRIMITIVE, 0, 0, 0, 1);
 /* Mode 30 deliberately falls through and emits the mode 31 packet too. */
 case 31: gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, ENVIRONMENT, 0, 0, 0, 1, 0, 0, 0, ENVIRONMENT, 0, 0, 0, 1); break;
 case 32: gDPSetCombineLERP(g_displayListCursor++, ENVIRONMENT, SHADE, TEXEL0, SHADE, SHADE, 0, TEXEL0, 0, ENVIRONMENT, SHADE, TEXEL0, SHADE, SHADE, 0, TEXEL0, 0); break;
 case 33: gDPSetCombineLERP(g_displayListCursor++, TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE, TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE); break;
 case 34: gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED); break;
 case 35: gDPSetCombineLERP(g_displayListCursor++, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, 0, 0, 0, PRIMITIVE, PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT, 0, 0, 0, COMBINED); break;
 case 36: gDPSetCombineLERP(g_displayListCursor++, PRIMITIVE, 0, SHADE, 0, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, COMBINED, ENVIRONMENT, COMBINED_ALPHA, ENVIRONMENT, 0, 0, 0, PRIMITIVE); break;
 case 37: gDPSetCombineLERP(g_displayListCursor++, ENVIRONMENT, 0, SHADE, 0, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, PRIMITIVE, COMBINED, COMBINED_ALPHA, COMBINED, 0, 0, 0, PRIMITIVE); break;
 case 38: gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, 1, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED); break;
 case 39: gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, 1, TEXEL0, 0, SHADE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED); break;
 case 40: gDPSetCombineLERP(g_displayListCursor++, TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0); break;
 case 41: gDPSetCombineLERP(g_displayListCursor++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, SHADE, 0, TEXEL0, 0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, SHADE, 0, TEXEL0, 0); break;
 }
 }
}

s32 Geometry_SetModePreset(s32 tailEnum) {

    if (g_geometryPreviousCombineMode == tailEnum) {
        return 0;
    }
    g_geometryPreviousCombineMode = tailEnum;

    {
        if ((u32)tailEnum > 30) {
            goto sw_mode_default;
        }
        switch (tailEnum) {
        case 0: goto sw_mode_0;
        case 1: goto sw_mode_1;
        case 2: goto sw_mode_2;
        case 3: goto sw_mode_3;
        case 4: goto sw_mode_4;
        case 5: goto sw_mode_5;
        case 6: goto sw_mode_6;
        case 7: goto sw_mode_7;
        case 8: goto sw_mode_8;
        case 9: goto sw_mode_9;
        case 10: goto sw_mode_10;
        case 11: goto sw_mode_11;
        case 12: goto sw_mode_12;
        case 13: goto sw_mode_13;
        case 14: goto sw_mode_14;
        case 15: goto sw_mode_15;
        case 16: goto sw_mode_16;
        case 17: goto sw_mode_17;
        case 18: goto sw_mode_18;
        case 19: goto sw_mode_19;
        case 20: goto sw_mode_20;
        case 21: goto sw_mode_21;
        case 22: goto sw_mode_22;
        case 23: goto sw_mode_23;
        case 24: goto sw_mode_24;
        case 25: goto sw_mode_25;
        case 26: goto sw_mode_26;
        case 27: goto sw_mode_27;
        case 28: goto sw_mode_28;
        case 29: goto sw_mode_29;
        case 30: goto sw_mode_30;
        }
    }
    switch (tailEnum) {
    case 0: sw_mode_0: {
        if (g_geometryAntialiasingEnabled) gDPSetRenderMode(g_displayListCursor++, 0x0C1849D8, 0) else gDPSetRenderMode(g_displayListCursor++, 0x0C184A50, 0);
        break;
    }
    case 1: sw_mode_1: {
        if (g_geometryAntialiasingEnabled) gDPSetRenderMode(g_displayListCursor++, g_geometryTranslucentRenderMode, 0x001049D8) else gDPSetRenderMode(g_displayListCursor++, g_geometryTranslucentRenderMode, 0x00104A50);
        break;
    }
    case 2: sw_mode_2: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, 0x0C184A50, 0);
        break;
    }
    case 3: sw_mode_3: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, 0x0C184B50, 0);
        break;
    }
    case 4: sw_mode_4: {
        if (g_geometryAntialiasingEnabled) gDPSetRenderMode(g_displayListCursor++, g_geometryTranslucentRenderMode, 0x00104DD8) else gDPSetRenderMode(g_displayListCursor++, g_geometryTranslucentRenderMode, 0x00104E50);
        break;
    }
    case 5: sw_mode_5: {
        if (g_geometryAntialiasingEnabled) gDPSetRenderMode(g_displayListCursor++, g_geometryTranslucentRenderMode, 0x001041F8) else gDPSetRenderMode(g_displayListCursor++, g_geometryTranslucentRenderMode, 0x001041F0);
        break;
    }
    case 6: sw_mode_6: {
        if (g_geometryAntialiasingEnabled) gDPSetRenderMode(g_displayListCursor++, g_geometryTranslucentRenderMode, 0x00113078) else gDPSetRenderMode(g_displayListCursor++, g_geometryTranslucentRenderMode, 0x00113078);
        break;
    }
    case 7: sw_mode_7: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, g_geometryTranslucentRenderMode, 0x00112E10);
        break;
    }
    case 8: sw_mode_8: {
        if (g_geometryAntialiasingEnabled) gDPSetRenderMode(g_displayListCursor++, g_geometryTranslucentRenderMode, 0x00112478) else gDPSetRenderMode(g_displayListCursor++, g_geometryTranslucentRenderMode, 0x00112478);
        break;
    }
    case 9: sw_mode_9: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, g_geometryTranslucentRenderMode, 0x00112438);
        break;
    }
    case 10: sw_mode_10: {
        if (g_geometryAntialiasingEnabled) gDPSetRenderMode(g_displayListCursor++, g_geometryTranslucentRenderMode, 0x00112078) else gDPSetRenderMode(g_displayListCursor++, g_geometryTranslucentRenderMode, 0x00112230);
        break;
    }
    case 11: sw_mode_11: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, g_geometryTranslucentRenderMode, 0x00112038);
        break;
    }
    case 12: sw_mode_12: {
        if (g_geometryAntialiasingEnabled) gDPSetRenderMode(g_displayListCursor++, 0x005045D8, 0) else gDPSetRenderMode(g_displayListCursor++, 0x004045D0, 0);
        break;
    }
    case 13: sw_mode_13: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, 0x00504B50, 0);
        break;
    }
    case 14: sw_mode_14: {
        if (g_geometryAntialiasingEnabled) gDPSetRenderMode(g_displayListCursor++, 0x005049D8, 0) else gDPSetRenderMode(g_displayListCursor++, 0x00504A50, 0);
        break;
    }
    case 15: sw_mode_15: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, 0x00504E50, 0);
        break;
    }
    case 16: sw_mode_16: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, 0x00504B53, 0);
        break;
    }
    case 17: sw_mode_17: {
        if (g_geometryAntialiasingEnabled) gDPSetRenderMode(g_displayListCursor++, 0x00553078, 0) else gDPSetRenderMode(g_displayListCursor++, 0x00553078, 0);
        break;
    }
    case 18: sw_mode_18: {
        if (g_geometryAntialiasingEnabled) gDPSetRenderMode(g_displayListCursor++, 0x00553048, 0) else gDPSetRenderMode(g_displayListCursor++, 0x0F0A7008, 0);
        break;
    }
    case 19: sw_mode_19: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, 0x00504340, 0);
        break;
    }
    case 20: sw_mode_20: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, 0, 0);
        break;
    }
    case 21: sw_mode_21: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, 0x00504240, 0);
        break;
    }
    case 22: sw_mode_22: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, 0x0FA54040, 0);
        break;
    }
    case 23: sw_mode_23: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, g_geometryTranslucentRenderMode, 0x00104B50);
        break;
    }
    case 24: sw_mode_24: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, g_geometryTranslucentRenderMode, 0x00104E50);
        break;
    }
    case 25: sw_mode_25: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, 0x0C184240, 0);
        break;
    }
    case 26: sw_mode_26: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, 0x0C184340, 0);
        break;
    }
    case 27: sw_mode_27: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, 0x0F0A4000, 0);
        break;
    }
    case 28: sw_mode_28: {
        if (g_geometryAntialiasingEnabled) gDPSetRenderMode(g_displayListCursor++, 0x00507048, 0) else gDPSetRenderMode(g_displayListCursor++, 0x00507040, 0);
        break;
    }
    case 29: sw_mode_29: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, g_geometryTranslucentRenderMode, 0x00104F50);
        break;
    }
    case 30: sw_mode_30: {
        Gfx *gfx = g_displayListCursor++;
        gDPSetRenderMode(gfx, g_geometryOpaqueRenderMode, 0x00104F50);
        break;
    }
    }
sw_mode_default:
    return 1;
}

/* Emits a 16 by 16 intensity texture, white tint, matrix and the selected pass list. */
void Geometry_DrawIntensityMask(void *matrix, s32 pass, u32 alpha) {
    Gfx *list;
    gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_16b, 1, g_materialIntensityMaskTexture);
    gDPSetTile(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPLoadSync(g_displayListCursor++);
    gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, 127, 1024);
    gDPPipeSync(g_displayListCursor++);
    gDPSetTile(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_8b, 2, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, 15 << 2, 15 << 2);
    gDPSetPrimColor(g_displayListCursor++, 0, 0, 255, 255, 255, alpha);
    gSPMatrix(g_displayListCursor++, matrix, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    list = g_geometryDefaultMaterialDisplayList;
    gSPDisplayList(g_displayListCursor++, ({ if (pass != 0) list = g_geometryAlternateMaterialDisplayList; list; }));
    g_geometryPreviousCombineMode = -1;
    g_geometryPreviousModePreset = -1;
    TextLoad_ResetTextureCache();
}

struct Shared_GfxMaterial {
    u32 flags;
    u8 pad4[3];
    u8 cachedTextureIndex;
    s32 textureResource;
    u8 padC[4];
    u8 primitiveRed;
    u8 primitiveGreen;
    u8 primitiveBlue;
    u8 primitiveAlpha;
    u8 environmentRed;
    u8 environmentGreen;
    u8 environmentBlue;
    u8 environmentAlpha;
    u16 textureMaskS;
    u16 textureMaskT;
};

void Geometry_SetCombineMode(u32);
s32 Geometry_SetModePreset(s32);

s32 Geometry_SetupMaterial(struct Shared_GfxMaterial *mat, s32 pass) {
    struct Shared_AnimInfo info;
    void *node;
    u32 flags;
    s32 tailEnum;
    s32 frameIndex;
    s32 variationIndex;
    s32 idx;
    u32 maskS;
    u32 maskT;
    u32 extra;
    u32 extra2;
    u32 mode;

    flags = mat->flags;
    if (g_geometryViewEffect != 0 && (flags & 0x8040) != 0x8000) {
        flags |= 2;
    }
    if ((flags & 0x100) && mat->primitiveAlpha == 0) {
        return 0;
    }
    tailEnum = -1;
    if (mat->textureResource != 0 && !(g_gameSettings.flags & 0x400) && !(g_geometryViewEffect != 0 && (flags & 0x8000))) {
        node = Textload_RequestTextureVariation(&mat->textureResource, pass);
        if (node == 0) {
            return 0;
        }
        Textload_ReadTextureAnimationInfo(node, &info);
        switch (pass) {
            case -2:
                if (info.count < 2) {
                    frameIndex = 0;
                    variationIndex = 0;
                    break;
                }
                idx = (u8)((u32)g_gameLoopFrameCount / info.frame->frameDuration);
                if (mat->cachedTextureIndex != idx) {
                    frameIndex = Graphu64_NextRandom() % info.count;
                    if (info.variationCount != 0) {
                        variationIndex = frameIndex;
                        if (variationIndex >= info.variationCount) {
                            variationIndex = 0;
                        }
                    } else {
                        variationIndex = 0;
                    }
                    mat->cachedTextureIndex = idx;
                } else {
                    frameIndex = idx % info.count;
                    variationIndex = info.variationCount ? idx % info.variationCount : 0;
                }
                break;
            case -1:
                idx = (u32)g_gameLoopFrameCount / info.frame->frameDuration;
                frameIndex = idx % info.count;
                variationIndex = (info.variationCount == 0) ? 0 : idx % info.variationCount;
                break;
            default:
                frameIndex = pass % info.count;
                if (info.variationCount != 0) {
                    variationIndex = pass % info.variationCount;
                } else {
                    variationIndex = 0;
                }
                break;
        }
        if (flags & 0x10) {
            maskS = 1 << (info.frame->shiftS + 6);
            maskT = 1 << (info.frame->shiftT + 6);
        } else {
            maskS = mat->textureMaskS;
            maskT = mat->textureMaskT;
        }
        if (flags & 0x20) {
            extra = G_TX_CLAMP;
            extra2 = G_TX_CLAMP;
        } else {
            extra = G_TX_WRAP;
            extra2 = G_TX_WRAP;
        }
        if (flags & 0x800) {
            extra |= G_TX_MIRROR;
            extra2 |= G_TX_MIRROR;
        }
#if defined(VERSION_US_REV1)
        Textload_LoadTextureFrameTiles(&mat->textureResource, node, frameIndex, variationIndex, maskS, maskT, extra, extra2, 0);
    #else
        Textload_LoadTextureFrame(&mat->textureResource, node, frameIndex, variationIndex, maskS, maskT, extra, extra2, 0);
    #endif
        if (flags & 0x2000) {
            gDPSetTextureLOD(g_displayListCursor++, G_TL_LOD);
        }
        if (g_geometryViewEffect != 0) {
            u32 avg = (u32)(mat->primitiveRed + mat->primitiveGreen + mat->primitiveBlue) / 3;
            gDPSetPrimColor(g_displayListCursor++, info.frame->primitiveMinimumLod, 0, 0, 0, avg, mat->primitiveAlpha);
        } else {
            gDPSetPrimColor(g_displayListCursor++, info.frame->primitiveMinimumLod, 0, mat->primitiveRed, mat->primitiveGreen, mat->primitiveBlue, mat->primitiveAlpha);
        }
        if (flags & 0x400) {
            if (g_geometryViewEffect != 0) {
                u32 avg = (u32)(mat->environmentRed + mat->environmentGreen + mat->environmentBlue) / 3;
                gDPSetEnvColor(g_displayListCursor++, 0, 0, avg, g_menuModelFillEnabled == 0 ? mat->primitiveAlpha : g_menuModelFillColor[3]);
            } else {
                gDPSetEnvColor(g_displayListCursor++, mat->environmentRed, mat->environmentGreen, mat->environmentBlue, g_menuModelFillEnabled == 0 ? mat->primitiveAlpha : g_menuModelFillColor[3]);
            }
            if (flags & 2) {
                if (!(flags & 0x1000)) {
                    Geometry_SetCombineMode(2);
                } else if (g_menuModelFillEnabled == 0) {
                    Geometry_SetCombineMode(0);
                } else {
                    Geometry_SetCombineMode(1);
                }
            } else if (!(flags & 0x1000)) {
                Geometry_SetCombineMode(4);
            } else {
                Geometry_SetCombineMode(3);
            }
            Cache_UnlockResource(0, node);
        } else if (flags & 2) {
            if (flags & 0x2000) {
                switch (info.frame->materialCombineKind) {
                    case 4:
                    case 5:
                        gDPSetEnvColor(g_displayListCursor++, mat->environmentRed, mat->environmentGreen, mat->environmentBlue, mat->environmentAlpha);
                        Geometry_SetCombineMode(35);
                        break;
                    default:
                        Geometry_SetCombineMode(5);
                        break;
                }
            } else if (g_menuModelFillEnabled == 0) {
                Geometry_SetCombineMode(6);
            } else {
                gDPSetEnvColor(g_displayListCursor++, g_menuModelFillColor[0], g_menuModelFillColor[1], g_menuModelFillColor[2], g_menuModelFillColor[3]);
                switch (g_menuModelFillEnabled) {
                    case 1:
                    case 2:
                        Geometry_SetCombineMode(7);
                        break;
                    case 3:
                        Geometry_SetCombineMode(8);
                        break;
                    case 7:
                        Geometry_SetCombineMode(9);
                        break;
                    case 4:
                    case 5:
                        Geometry_SetCombineMode(10);
                        break;
                    case 6:
                        gDPSetPrimColor(g_displayListCursor++, 0, 0, mat->primitiveRed, mat->primitiveGreen, mat->primitiveBlue, g_menuModelFillColor[4]);
                        Geometry_SetCombineMode(11);
                        break;
                    default:
                        break;
                }
            }
            Cache_UnlockResource(0, node);
        } else {
            if (flags & 0x2000) {
                switch (info.frame->materialCombineKind) {
                    case 4:
                        gDPSetEnvColor(g_displayListCursor++, mat->environmentRed, mat->environmentGreen, mat->environmentBlue, mat->environmentAlpha);
                        Geometry_SetCombineMode(37);
                        break;
                    case 5:
                        gDPSetEnvColor(g_displayListCursor++, mat->environmentRed, mat->environmentGreen, mat->environmentBlue, mat->environmentAlpha);
                        Geometry_SetCombineMode(36);
                        break;
                    default:
                        Geometry_SetCombineMode(12);
                        break;
                }
            } else if (g_menuModelFillEnabled == 0) {
                Geometry_SetCombineMode(13);
            } else {
                gDPSetEnvColor(g_displayListCursor++, g_menuModelFillColor[0], g_menuModelFillColor[1], g_menuModelFillColor[2], g_menuModelFillColor[3]);
                switch (g_menuModelFillEnabled) {
                    case 1:
                    case 2:
                        Geometry_SetCombineMode(14);
                        break;
                    case 3:
                        Geometry_SetCombineMode(15);
                        break;
                    case 7:
                        Geometry_SetCombineMode(9);
                        break;
                    case 4:
                    case 5:
                        Geometry_SetCombineMode(16);
                        break;
                    case 6:
                        gDPSetPrimColor(g_displayListCursor++, 0, 0, mat->primitiveRed, mat->primitiveGreen, mat->primitiveBlue, g_menuModelFillColor[4]);
                        Geometry_SetCombineMode(17);
                        break;
                    default:
                        break;
                }
            }
            Cache_UnlockResource(0, node);
        }
    } else {
        gDPPipeSync(g_displayListCursor++);
        if (g_primitiveColorOverrideEnabled != 0) {
            if (g_primitiveAlphaOverrideEnabled != 0) {
                gDPSetPrimColor(g_displayListCursor++, 0, 0, g_primitiveColorOverrideRed, g_primitiveColorOverrideGreen, g_primitiveColorOverrideBlue, g_primitiveAlphaOverride);
            } else {
                gDPSetPrimColor(g_displayListCursor++, 0, 0, g_primitiveColorOverrideRed, g_primitiveColorOverrideGreen, g_primitiveColorOverrideBlue, mat->primitiveAlpha);
            }
        } else if (g_primitiveAlphaOverrideEnabled != 0) {
            gDPSetPrimColor(g_displayListCursor++, 0, 0, mat->primitiveRed, mat->primitiveGreen, mat->primitiveBlue, g_primitiveAlphaOverride);
        } else if (flags & 0x8000) {
            if (flags & 0x40) {
                gDPSetPrimColor(g_displayListCursor++, 0, 0, 255, 0, 0, mat->primitiveAlpha);
            } else {
                gDPSetPrimColor(g_displayListCursor++, 0, 0, 255, 255, 0, mat->primitiveAlpha);
            }
        } else {
            gDPSetPrimColor(g_displayListCursor++, 0, 0, mat->primitiveRed, mat->primitiveGreen, mat->primitiveBlue, mat->primitiveAlpha);
        }
        gSPTexture(g_displayListCursor++, 0, 0, 0, 0, 0);
        if (flags & 2) {
            Geometry_SetCombineMode(18);
        } else if (g_menuModelFillEnabled == 0) {
            Geometry_SetCombineMode(19);
        } else {
            gDPSetEnvColor(g_displayListCursor++, g_menuModelFillColor[0], g_menuModelFillColor[1], g_menuModelFillColor[2], g_menuModelFillColor[3]);
            switch (g_menuModelFillEnabled) {
                case 1:
                case 2:
                    Geometry_SetCombineMode(20);
                    break;
                case 3:
                    Geometry_SetCombineMode(21);
                    break;
                case 7:
                    Geometry_SetCombineMode(22);
                    break;
                case 4:
                case 5:
                    Geometry_SetCombineMode(23);
                    break;
                case 6:
                    gDPSetPrimColor(g_displayListCursor++, 0, 0, mat->primitiveRed, mat->primitiveGreen, mat->primitiveBlue, g_menuModelFillColor[4]);
                    Geometry_SetCombineMode(17);
                    break;
                default:
                    break;
            }
        }
    }
    if ((flags & 0x100) || g_menuModelFillEnabled == 1 || g_menuModelFillEnabled == 4 || g_menuModelFillEnabled == 6) {
        if (g_menuModelFillEnabled == 0) {
            tailEnum = 3;
            if (!(flags & 0x1000)) {
                tailEnum = 1;
                if (flags & 0x200) {
                    tailEnum = 4;
                }
            }
        } else {
            tailEnum = 5;
            if (flags & 0x1000) {
                tailEnum = 3;
            }
        }
    } else if (flags & 0x80) {
        Geometry_SetModePreset(6);
    } else {
        tailEnum = 7;
        if (!(flags & 0x200)) {
            if (g_geometryTextureFilterOverride != 0) {
                tailEnum = 9;
                if (g_geometryTexturePerspectiveOverride != 0) {
                    tailEnum = 8;
                }
            } else {
                tailEnum = 11;
                if (g_geometryTexturePerspectiveOverride != 0) {
                    tailEnum = 10;
                }
            }
        }
    }
    if (tailEnum != -1) {
        Geometry_SetModePreset(tailEnum);
    }
    mode = 0x260404;
    if (flags & 0x1000) {
        mode |= g_geometryEffectGeometryMode;
    }
    gSPGeometryMode(g_displayListCursor++, mode, 0);
    mode = 0;
    if (!(flags & 0x1000)) {
        mode = g_geometryEffectGeometryMode;
    }
    if (g_menuModelFillEnabled == 7) {
        mode |= 0x20000;
    }
    if (!(flags & 0x42)) {
        mode |= 0x20000;
    }
    mode |= 0x200004;
    if (!(flags & 4)) {
        mode |= 0x400;
    }
    if (flags & 0x10) {
        mode |= 0x60000;
    }
    gSPGeometryMode(g_displayListCursor++, 0, mode);
    return 1;
}

/* GEOMETRY_EXPANDMODELCOMMANDS.CPP */



void Geometry_SetupIntensityPass(void) {
    Gfx *cmd;

    TextLoad_ResetTextureCache();

    cmd = g_displayListCursor++;
    gDPSetTextureImage(cmd, G_IM_FMT_I, G_IM_SIZ_16b, 1, &g_geometryMaterialIntensityTexture);
    cmd = g_displayListCursor++;
    gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP, 5, 0, G_TX_WRAP, 5, 0);
    cmd = g_displayListCursor++;
    gDPLoadSync(cmd);
    cmd = g_displayListCursor++;
    gDPLoadBlock(cmd, G_TX_LOADTILE, 0, 0, 255, 1024);
    cmd = g_displayListCursor++;
    gDPPipeSync(cmd);
    cmd = g_displayListCursor++;
    gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 0, G_TX_WRAP, 5, 0, G_TX_WRAP, 5, 0);
    cmd = g_displayListCursor++;
    gDPSetTileSize(cmd, G_TX_RENDERTILE, 0, 0, 124, 124);
    cmd = g_displayListCursor++;
    gSPTexture(cmd, 2048, 2048, 0, 0, G_ON);
    cmd = g_displayListCursor++;
    gDPSetTextureLUT(cmd, G_TT_NONE);
    cmd = g_displayListCursor++;
    gSPGeometryMode(cmd, 0, g_geometryEffectGeometryMode | 0x00260404);

    Geometry_SetModePreset(29);
}

/* Expand packed geometry commands into display lists while rebuilding resource offsets. */
void Geometry_ExpandModelCommands(s32 cacheContext, struct CacheResourceNode **res, s32 extra, s32 sentinel) {
    s32 len0, len1, len3, len4, len5;
    struct CacheResourceNode *allocation;
    struct Pack *old;
    struct Pack *oldList;
    struct Pack *newList;
    u8 *vertices;
    u8 *vertexData;
    s32 vertexCount;
    s32 parts, size, count, i, commandSize, offset, total;
    struct Pack *dst;
    struct Pack *srcEntry, *dstEntry;
    u8 *input;
    Gfx *output;
    s32 tag;
    u32 value, a, b, c, n, block;
    s32 b2, c2;
    s32 vertexSlot, vertexOffset;
    const u32 vertexSegment = 0x02000000;
    const u32 matrixSegment = 0x01000000;
    s32 l, q, r;
    /* Expanded material records have the same size in both passes. */
    s32 materialBytes = 32;
    void *dstData;
    void *copySource4, *copySource5, *copySource3, *copySource2, *copySource1, *copySource0;
    if (Ppdecom_UnpackResource(res, 1) != 0) {
        parts = 6;
        if (extra == 0) {
            parts = 3;
            if (sentinel != 0) parts = 4;
        }
        size = (parts * 4 + 15) & ~7;
        old = (*res)->data;
        SetN64_GetSizedPackSection(old, 0, &len0);
        size += len0;
        SetN64_GetSizedPackSection(old, 1, &len1);
        size += len1;
        oldList = SetN64_GetPackSection(old, 2);
        count = oldList->count;
        i = 0;
        size += (count * 4 + 15) & ~7;
        if (count > 0) do {
            srcEntry = SetN64_GetPackSection(oldList, i);
            size += 16;
            size += materialBytes;
            input = SetN64_GetPackSection(srcEntry, 1);
            {
                s32 countTag;
                commandSize = 0;
                while ((countTag = *input) != 0) {

                    if (countTag & 0x80) {
                        input += 2;
                        commandSize += 8;
                        if (*input & 0x80) input += 2;
                    } else {
                        countTag &= 0x60;
                        switch (countTag) {
                        case 32: input += 2; commandSize += 8; break;
                        case 64: input += 2; commandSize += 8; break;
                        case 96: input += 5; commandSize += 8; break;
                        }
                    }
                }
                size += (commandSize + 15) & ~7;
            }
            i++;
        } while (i < count);
        if (extra != 0) {
            SetN64_GetSizedPackSection(old, 3, &len3);
            size += len3;
            SetN64_GetSizedPackSection(old, 4, &len4);
            size += len4;
            SetN64_GetSizedPackSection(old, 5, &len5);
            size += len5;
        }
        if (sentinel != 0) size += 8;
        allocation = Cache_AllocResourceBlock(0, res, size);
        if (allocation != 0) {
            offset = (parts * 4 + 15) & ~7;
            old = (*res)->data;
            dst = allocation->data;
            dst->count = parts;
            dst->offsets[0] = offset;
            copySource0 = SetN64_GetSizedPackSection(old, 0, &len0);
            vertexCount = 0;
            vertices = SetN64_GetPackSection(dst, 0);
            Libc_CopyBytes(vertices, copySource0, len0);
            offset += len0;
            dst->offsets[1] = offset;
            copySource1 = SetN64_GetSizedPackSection(old, 1, &len1);
            dstData = SetN64_GetPackSection(dst, 1);
            Libc_CopyBytes(dstData, copySource1, len1);
            offset += len1;
            dst->offsets[2] = offset;
            oldList = SetN64_GetPackSection(old, 2);
            newList = SetN64_GetPackSection(dst, 2);
            count = oldList->count;
            i = 0;
            newList->count = count;
            total = (count * 4 + 15) & ~7;
            newList->offsets[0] = total;
            if (count > 0) {
                vertexData = vertices + 8;
                do {
                    srcEntry = SetN64_GetPackSection(oldList, i);
                    dstEntry = SetN64_GetPackSection(newList, i);
                    block = (srcEntry->count * 4 + 15) & ~7;
                    dstEntry->count = srcEntry->count;
                    dstEntry->offsets[0] = block;
                    copySource2 = SetN64_GetPackSection(srcEntry, 0);
                    dstData = SetN64_GetPackSection(dstEntry, 0);
                    Rumble_ExpandMeshMaterial(dstData, copySource2);
                    block += materialBytes;
                    dstEntry->offsets[1] = block;
                    input = SetN64_GetPackSection(srcEntry, 1);
                    output = SetN64_GetPackSection(dstEntry, 1);
                    if ((tag = *input) != 0) {
                        do {
                            commandSize = tag & 0x60;
                            if (tag & 0x80) {
                                value = *input++ << 8;
                                value |= *input++;
                                a = (s32)value >> 10 & 0x1F;
                                b = (s32)value >> 5 & 0x1F;
                                c = value & 0x1F;
                                if (*input & 0x80) {
                                    {
                                        s32 hi = *input++;
                                        s32 lo = *input++;
                                        value = hi << 8;
                                        value |= lo;
                                        commandSize = (s32)value >> 10 & 31;
                                        b2 = (s32)value >> 5 & 31;
                                        c2 = value & 31;
                                        gSP2Triangles(output++, a, b, c, 0, commandSize, b2, c2, 0);
                                    }
                                } else {
                                    gSP1Triangle(output++, a, b, c, 0);
                                }
                            } else {
                                switch (commandSize) {
                                case 32:
                                    value = *input++ << 8;
                                    value |= *input++;
                                    vertexSlot = (s32)value >> 5 & 31;
                                    n = value & 0x1F;
                                    if (n == 0) n = 32;
                                    vertexOffset = vertexCount;
                                    /* Segment 2 holds vertex data, following its eight-byte header. */
                                    gSPVertex(output++, (vertexData + vertexOffset * 16 - vertices) + vertexSegment, n, vertexSlot);
                                    vertexCount += n;
                                    break;
                                case 64:
                                    input++;
                                    {
                                        s32 matrixIndex = *input++;
                                        /* Segment 1 holds 64-byte matrices. */
                                        gSPMatrix(output++, matrixSegment + matrixIndex * 64,
                                                  G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
                                    }
                                    break;
                                case 96:
                                    vertexSlot = tag & 31;
                                    input++;
                                    value = *input++;
                                    l = *input++;
                                    q = *input++;
                                    r = *input++;
                                    value <<= 24;
                                    value |= l << 16;
                                    value |= q << 8;
                                    value |= r;
                                    gSPModifyVertex(output++, vertexSlot, G_MWO_POINT_ST, value);
                                    break;
                                }
                            }
                            tag = *input;
                        } while (tag != 0);
                    }
                    gSPEndDisplayList(output++);
                    dstData = SetN64_GetPackSection(dstEntry, 1);
                    commandSize = (u8 *)output - (u8 *)dstData;
                    block += (commandSize + 7) & ~7;
                    total += block;
                    dstEntry->offsets[2] = block;
                    newList->offsets[i + 1] = total;
                    i++;
                } while (i < count);
            }
            offset += total;
            dst->offsets[3] = offset;
            if (extra != 0) {
                copySource3 = SetN64_GetSizedPackSection(old, 3, &len3);
                dstData = SetN64_GetPackSection(dst, 3);
                Libc_CopyBytes(dstData, copySource3, len3);
                offset += len3;
                dst->offsets[4] = offset;
                copySource4 = SetN64_GetSizedPackSection(old, 4, &len4);
                dstData = SetN64_GetPackSection(dst, 4);
                Libc_CopyBytes(dstData, copySource4, len4);
                offset += len4;
                dst->offsets[5] = offset;
                copySource5 = SetN64_GetSizedPackSection(old, 5, &len5);
                dstData = SetN64_GetPackSection(dst, 5);
                Libc_CopyBytes(dstData, copySource5, len5);
                offset += len5;
                dst->offsets[6] = offset;
            }
            if (sentinel != 0) {
                Gfx *sentinelData = SetN64_GetPackSection(dst, 3);
                offset += 8;
                sentinelData->words.w0 = -1;
                sentinelData->words.w1 = 0;
                dst->offsets[4] = offset;
            }
        }
        Cache_ReplaceResourceBlock(0, res, allocation);
    }
}


s32 Geometry_ApplyMaterialLighting(void *model, void *lights, ModelMaterial *material) {
    CVector3 direction;
    CVector3 position;
    f32 matrix[4][4];

    if (g_geometryViewEffect != 0 && (material->flagWord & 0x8000)) {
        Graphu64_UnpackFixedMatrix((f32 *)matrix, model);
        Graphu64_GetMatrixTranslation((f32 *)matrix, &position);
        Graphu64_SubtractVectors(&direction, &((PlayerControllerReleaseView *)Playerai_GetFirstPlayer(&g_playerViewRenderContext))->previousPosition, &position);
        Graphu64_NormalizeVec3(&direction);
        {
            Gfx *cmd;
            Gfx *light;
            Gfx *ambient;

            g_geometryMaterialLightDirection[0] = direction.x * g_geometryLightDirectionScale;
            g_geometryMaterialLightDirection[1] = direction.y * g_geometryLightDirectionScale;
            g_geometryMaterialLightDirection[2] = direction.z * g_geometryLightDirectionScale;
            cmd = g_displayListCursor++;
            gMoveWd(cmd, G_MW_NUMLIGHT, 0, 0x18);
            gDma2p(g_displayListCursor++, G_MOVEMEM, (unsigned int)(g_geometryMaterialLightDirection - 8), 16, G_MV_LIGHT, 48);
            gDma2p(g_displayListCursor++, G_MOVEMEM, (unsigned int)(g_geometryMaterialLightDirection - 0x10), 16, G_MV_LIGHT, 72);
        }
        return 1;
    }
    if (lights != 0) {
        gMoveWd(g_displayListCursor++, G_MW_NUMLIGHT, 0, 0x18);
        gDma2p(g_displayListCursor++, G_MOVEMEM, (unsigned int)lights + 8, 16, G_MV_LIGHT, 48);
        gDma2p(g_displayListCursor++, G_MOVEMEM, (unsigned int)lights, 16, G_MV_LIGHT, 72);
    }
    return 0;
}

/* Draws an actor model's parts, choosing each part by the 0x38 bits of its material byte 6: on the special
 * character 0x12 the part must equal the bits for its variant (or be a fade/bonus part whose flag is set),
 * otherwise the 0x38/0x30/0x10 groups are drawn only when the matching flag (fade, bonus, glow) is set. */
void Geometry_DrawActorModelParts(void **resource, struct Player *owner, void *matrix, s32 segment, Shared_ParticleLighting *lights, void *textures, s32 pass) {
    struct Pack *header;
    void *base;
    struct Pack *parts;
    struct Pack *part;
    MeshMaterial *material;
    s32 count;
    s32 i;
    s32 hide = 0;
    s32 bonus = 0;
    s32 glow = 0;
    CGameStatus *settings;

    if (g_primaryDisplayListCapacity - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
        return;
    }
    settings = &g_gameSettings.counters;
    if (settings->enabled != 0) {
        AiProfile *state = owner->profile;
        if (state->character == 11 && state->enabled != 0) {
            hide = 0 < settings->m_nBastilleShield;
        }
    }
    if (owner->reactionFlags & 0x8000) {
        hide = 1;
    }
    if (0.0f < owner->glow) {
        glow = 1;
    }
    if (g_gameSettings.counters.m_bCTFOn != 0 && owner->profile->bonus == 1) {
        bonus = 1;
    }
    header = *resource;
    Cache_MarkResourceInUse(0, resource);
    if (segment != 0) {
        gSPSegment(g_displayListCursor++, 1, matrix);
    } else {
        gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD);
    }
    base = textures;
    if (base == 0) {
        base = SetN64_GetPackSection(header, 0);
    }
    gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
    parts = SetN64_GetPackSection(header, 2);
    count = parts->count;
    for (i = 0; i < count; i++) {
        AiProfile *state;
        part = SetN64_GetPackSection(parts, i);
        material = SetN64_GetPackSection(part, 0);
        if (i == 0) {
            Geometry_ApplyMaterialLighting(matrix, lights, material);
        }
        state = owner->profile;
        if (state->character == 18 && (g_gameSettings.counters.m_bFragTagOn == 0 || state->bonus == 0)) {
            u32 bits;
            u32 wanted;
            if (state->variant == 0) {
                wanted = 40;
            } else if (state->variant == 1) {
                wanted = 32;
            } else {
                wanted = 24;
            }
            bits = material->mode & 0x38;
            if (bits == wanted || (bits == 0x38 && hide != 0) || (bits == 0x30 && bonus != 0)) {
                if (Geometry_SetupMaterial(material, pass) != 0) {
                    void *list = SetN64_GetPackSection(part, 1);
                    gSPDisplayList(g_displayListCursor++, list);
                }
            }
        } else {
            u32 bits = material->mode & 0x38;
            if (bits == 0x38 && hide == 0) continue;
            if (bits == 0x30 && bonus == 0) continue;
            if (bits == 0x10 && glow == 0) continue;
            if (Geometry_SetupMaterial(material, pass) != 0) {
                void *list = SetN64_GetPackSection(part, 1);
                gSPDisplayList(g_displayListCursor++, list);
            }
        }
    }
}

/* GEOMETRY_GROUPMODELINSTANCES.CPP */

/* Draws the parts of a model resource that the owner has enabled, when the frame command buffer still has 3000 commands free: each part material's low two bits of byte 6 pick an owner flag at 0x102 (0x100, 0x8 or 0x2, 0x80 or 0x20 by bit 4) that must be set before Geometry_SetupMaterial accepts the material and its display list is emitted. */

void Geometry_DrawVisibleOwnerParts(void **resource, struct Owner104 *owner, s32 matrix, s32 segment, s32 lights, void *textures, s32 pass) {
    void *header;
    void *base;
    void **parts;
    void *part;
    Material *material;
    s32 count;
    s32 i;
    s32 visible;

    if (g_primaryDisplayListCapacity - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
        return;
    }
    header = *resource;
    Cache_MarkResourceInUse(0, resource);
    if (segment != 0) { gSPSegment(g_displayListCursor++, 1, matrix); }
    else { gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD); }
    base = textures;
    if (base == 0) {
        base = SetN64_GetPackSection(header, 0);
    }
    gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
    parts = SetN64_GetPackSection(header, 2);
    count = *(s32 *)parts;
    for (i = 0; i < count; i++) {
        part = SetN64_GetPackSection(parts, i);
        material = SetN64_GetPackSection(part, 0);
        if (i == 0) {
            Geometry_ApplyMaterialLighting(matrix, lights, material);
        }
        visible = 1;
        switch ((material)->flags & 3) {
        case 2:
            if (!((material)->flags & 4)) {
                if (!(owner->flags & 8)) {
                    visible = 0;
                }
            } else {
                if (!(owner->flags & 2)) {
                    visible = 0;
                }
            }
            break;
        case 3:
            if (!((material)->flags & 4)) {
                if (!(owner->flags & 0x80)) {
                    visible = 0;
                }
            } else {
                if (!(owner->flags & 0x20)) {
                    visible = 0;
                }
            }
            break;
        case 1:
            if (!(owner->flags & 0x100)) {
                visible = 0;
            }
            break;
        }
        if (visible && Geometry_SetupMaterial(material, pass) != 0) {
            Gfx *cmd;
            void *list = SetN64_GetPackSection(part, 1);

            cmd = g_displayListCursor++;
            gSPDisplayList(cmd, (unsigned int)list);
        }
    }
}

/* Returns the node keyed key in the tree under n, or the node a new key would hang from. */
static inline NodeGeometryGroupModelInstances *find_node(NodeGeometryGroupModelInstances *n, u32 key) {
    NodeGeometryGroupModelInstances *parent = ((void *) 0);

    while (n != ((void *) 0)) {
        if (n->key == key) {
            return n;
        }
        parent = n;
        if (key < n->key) {
            n = n->left;
        } else {
            n = n->right;
        }
    }
    return parent;
}

/* Files each entry of the list the resource g_modelBatchResource holds into one of two keyed trees, allocating a
 * node from g_materialGroups when its key is new, and appends one item per queued parameter in g_modelInstanceQueue
 * to that node's list; then clears the queue count g_modelInstanceQueueCount. */
void Geometry_GroupModelInstances(void) {
    s32 *list;
    s32 count;
    s32 i;
    s32 j;
    void *entry;
    ResourceSource *source;
    u32 key;
    NodeGeometryGroupModelInstances *parent;
    NodeGeometryGroupModelInstances *node;
    s32 *data;
    GeometryModelInstanceEntry *item;
    struct CacheResourceNode *param;

    if (g_modelInstanceQueueCount != 0) {
        list = SetN64_GetPackSection(*g_modelBatchResource, 2);
        count = *list;
        for (i = 0; i < count; i++) {
            entry = SetN64_GetPackSection(list, i);
            source = SetN64_GetPackSection(entry, 0);
            key = (source->id << 8) | (u8)g_modelBatchPass;
            if (source->flags & 0x700) {
                parent = find_node(g_translucentMaterialGroupTree, key);
            } else {
                parent = find_node(g_opaqueMaterialGroupTree, key);
            }
            if (parent != ((void *) 0) && parent->key == key) {
                node = parent;
            } else {
                if (g_materialGroupCount == 120) {
                    break;
                }
                node = &g_materialGroups[g_materialGroupCount++];
                node->key = key;
                node->source = source;
                node->tail = ((void *) 0);
                node->head = ((void *) 0);
                if (source->flags & 0x700) {
                    if (parent != ((void *) 0)) {
                        if (node->key < parent->key) {
                            parent->left = node;
                            node->right = ((void *) 0);
                            node->left = ((void *) 0);
                            node->next = parent;
                            node->prev = parent->prev;
                            if (parent->prev != ((void *) 0)) {
                                parent->prev->next = node;
                            }
                            parent->prev = node;
                            if (g_translucentMaterialGroupList == parent) {
                                g_translucentMaterialGroupList = node;
                            }
                        } else {
                            parent->right = node;
                            node->right = ((void *) 0);
                            node->left = ((void *) 0);
                            node->next = parent->next;
                            if (parent->next != ((void *) 0)) {
                                parent->next->prev = node;
                            }
                            node->prev = parent;
                            parent->next = node;
                        }
                    } else {
                        g_translucentMaterialGroupTree = node;
                        g_translucentMaterialGroupList = node;
                        node->right = ((void *) 0);
                        node->left = ((void *) 0);
                        node->next = ((void *) 0);
                        node->prev = ((void *) 0);
                    }
                } else {
                    if (parent != ((void *) 0)) {
                        if (node->key < parent->key) {
                            parent->left = node;
                            node->right = ((void *) 0);
                            node->left = ((void *) 0);
                            node->next = parent;
                            node->prev = parent->prev;
                            if (parent->prev != ((void *) 0)) {
                                parent->prev->next = node;
                            }
                            parent->prev = node;
                            if (g_opaqueMaterialGroupList == parent) {
                                g_opaqueMaterialGroupList = node;
                            }
                        } else {
                            parent->right = node;
                            node->right = ((void *) 0);
                            node->left = ((void *) 0);
                            node->next = parent->next;
                            if (parent->next != ((void *) 0)) {
                                parent->next->prev = node;
                            }
                            node->prev = parent;
                            parent->next = node;
                        }
                    } else {
                        g_opaqueMaterialGroupTree = node;
                        g_opaqueMaterialGroupList = node;
                        node->right = ((void *) 0);
                        node->left = ((void *) 0);
                        node->next = ((void *) 0);
                        node->prev = ((void *) 0);
                    }
                }
            }
            data = SetN64_GetPackSection(entry, 1);
            for (j = 0; j < g_modelInstanceQueueCount; j++) {
                param = &g_modelInstanceQueue[j];
                if (g_materialInstanceCount != 500) {
                    item = &g_materialInstances[g_materialInstanceCount++];
                    item->data = data;
                    item->modelParamFirst = param->data;
                    item->modelParamSecond = param->size;
                    item->modelParamThird = param->references;
                    item->sourceHalfFirst = source->copiedHalfFirst;
                    item->sourceHalfSecond = source->copiedHalfSecond;
                    item->modelParamFourth = param->flags;
                    item->next = ((void *) 0);
                    if (node->tail != ((void *) 0)) {
                        node->tail->next = item;
                    } else {
                        node->head = item;
                    }
                    node->tail = item;
                }
            }
        }
        g_modelInstanceQueueCount = 0;
    }
}

/* GEOMETRY_DRAWMATERIALGROUPS.CPP */







                          /* unable to generate initializer: unknown type */

                          /* unable to generate initializer: unknown type */

void Geometry_DrawMaterialGroups(void) {
 Group18 *group=g_opaqueMaterialGroupList,*deferred=0;
 Mesh *mesh;u16 scaleS,scaleT;u32 cmd;
 if(group)do {
  mesh=group->meshes;
  if(mesh && Geometry_SetupMaterial(group->material,group->mode)) {
   scaleT=0;scaleS=0;
   do {
    Geometry_ApplyMaterialLighting(mesh->matrix,mesh->aux,group->material);
    if(mesh->segmented){gSPSegment(g_displayListCursor++, 1, ((mesh->matrix)));}else{gSPMatrix(g_displayListCursor++, ((mesh->matrix)), G_MTX_LOAD);}
    gSPSegment(g_displayListCursor++, 2, ((mesh->vertices)));
    if(mesh->scaleS) {
     if(scaleS!=mesh->scaleS || scaleT!=mesh->scaleT) {
      if(group->material->flags&0x2000){gSPTexture(g_displayListCursor++, mesh->scaleS, mesh->scaleT, 5, 0, 1);}else{gSPTexture(g_displayListCursor++, mesh->scaleS, mesh->scaleT, 0, 0, 1);}
     }
     scaleS=mesh->scaleS;scaleT=mesh->scaleT;
    }
    gSPDisplayList(g_displayListCursor++, ((mesh->list)));
    mesh=mesh->next;
   }while(mesh);
   if(group->material->flags&0x2000) {gDPSetTextureLOD(g_displayListCursor++, G_TL_TILE);}
   if(group->material->flags&0x4000) {
    Group18 *next=group->next;group->next=deferred;deferred=group;group=next;
   } else group=group->next;
  } else group=group->next;
 }while(group);
 if(deferred) {
  group=deferred;Geometry_SetupIntensityPass();
  do {
   mesh=group->meshes;
   if(mesh) {
    gDPSetPrimColor(g_displayListCursor++, 0, 0, 0, 0, 0, group->material->alpha);
    do {
     Geometry_ApplyMaterialLighting(mesh->matrix,mesh->aux,group->material);
     if(mesh->segmented){gSPSegment(g_displayListCursor++, 1, ((mesh->matrix)));}else{gSPMatrix(g_displayListCursor++, ((mesh->matrix)), G_MTX_LOAD);}
     gSPSegment(g_displayListCursor++, 2, ((mesh->vertices)));
     gSPDisplayList(g_displayListCursor++, ((mesh->list)));
     mesh=mesh->next;
    }while(mesh);
   }
   group=group->next;
  }while(group);
 }
 group=g_translucentMaterialGroupList;
 if(group)do {
  mesh=group->meshes;
  if(mesh && Geometry_SetupMaterial(group->material,group->mode)) {
   scaleT=0;scaleS=0;
   do {
    Geometry_ApplyMaterialLighting(mesh->matrix,mesh->aux,group->material);
    if(mesh->segmented){gSPSegment(g_displayListCursor++, 1, ((mesh->matrix)));}else{gSPMatrix(g_displayListCursor++, ((mesh->matrix)), G_MTX_LOAD);}
    gSPSegment(g_displayListCursor++, 2, ((mesh->vertices)));
    if(mesh->scaleS) {
     if(scaleS!=mesh->scaleS || scaleT!=mesh->scaleT) {
      if(group->material->flags&0x2000){gSPTexture(g_displayListCursor++, mesh->scaleS, mesh->scaleT, 5, 0, 1);}else{gSPTexture(g_displayListCursor++, mesh->scaleS, mesh->scaleT, 0, 0, 1);}
     }
     scaleS=mesh->scaleS;scaleT=mesh->scaleT;
    }
    gSPDisplayList(g_displayListCursor++, ((mesh->list)));
    mesh=mesh->next;
   }while(mesh);
   if(group->material->flags&0x2000){gDPSetTextureLOD(g_displayListCursor++, G_TL_TILE);}
  }
  group=group->next;
 }while(group);
}

void Geometry_QueueModelById(s32 modelIndex, void *matrix, void *lights, s32 textures, s32 pass, s32 direct) {
        s32 *modelVariantTable;
        s32 modelResourceSize;
        s32 **objectIndexResource;
        s32 **resource;
        s32 modelResourceKey;
        s32 directoryEntryResult;
        s32 modelIndexResource;
        s32 modelVariantCount;
        s32 instanceCount;
        s8 *packSectionResult;
        QueuedModelInstance *queuedInstance;
        objectIndexResource = Cache_RequestResource(0, modelIndex, modelIndex, 24, 0, 0, 0, &s_simpObjectIndexText, 1);
        if (objectIndexResource != 0) {
                directoryEntryResult = SetN64_GetDirectoryEntry(*objectIndexResource, modelIndex, 1);
                Cache_UnlockResource(0, objectIndexResource);
                modelIndexResource = Cache_RequestWordCountedResource(0, (void **) &modelVariantTable, directoryEntryResult, &s_simpModelsIndexText, 1);
                if (modelIndexResource != 0) {
                        modelVariantCount = *modelVariantTable;
                        modelResourceKey = SetN64_LocatePackSection((s32) modelVariantTable, directoryEntryResult, textures % modelVariantCount, &modelResourceSize);
                        Cache_UnlockResource(0, (void *) modelIndexResource);
                        resource = Cache_RequestResource(0, modelResourceKey, modelResourceKey, modelResourceSize, 0, 0, &g_simpleModelResourceCallbackAddress, &s_simpModelText, direct);
                        if (resource != 0) {
                                packSectionResult = SetN64_GetPackSection(*resource, 0);
                                if (g_modelBatchResource != resource || g_modelBatchPass != pass || g_modelInstanceQueueCount == 32) {
                                        Geometry_GroupModelInstances();
                                        if (g_modelBatchResourceCount != 256) {
                                                Cache_LockResource(0, resource);
                                                g_modelBatchResources[g_modelBatchResourceCount] = resource;
                                                g_modelBatchResourceCount += 1;
                                                goto block_11;
                                        }
                                } else {
                                        block_11:
                                        g_modelBatchResource = resource;

                                        g_modelBatchPass = pass;
                                        instanceCount = g_modelInstanceQueueCount;
                                        queuedInstance = &g_modelInstanceQueue[instanceCount++];
                                        g_modelInstanceQueueCount = instanceCount;
                                        queuedInstance->matrix = matrix;
                                        queuedInstance->segmented = 0;
                                        queuedInstance->lights = lights;
                                        queuedInstance->vertices = packSectionResult;
                                }
                                Cache_UnlockResource(0, resource);
                        }
                }
        }
}




/* Draws a pack resource model as a translucent decal: skips when fewer than 3000 display-list commands are
 * left, loads the matrix (or segment 1), points segment 2 at the textures (the sixth argument overrides the
 * texture section of the pack), sets a primitive-alpha combine with the fog render mode bits and the global
 * geometry mode, then emits the display list of each part; the cached texture and combine states are
 * invalidated before and after. The fifth and seventh arguments are unread. */
void Geometry_DrawResourceModel(s32 alpha, s32 resource, void *matrix,
                     s32 segment, void *unusedLighting, s32 textureAddress, s32 unusedMode) {
    void *resourceHeader;
    void *textures;
    void *partTable;
    void *partHeader;
    void *displayList;
    Gfx *syncCommand;
    u32 geometryMode;
    s32 partCount;
    s32 partIndex;
    s32 opacity = alpha;

    if (g_primaryDisplayListCapacity - (((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) >> 3) < 3000U) {
        return;
    }
    resourceHeader = *(void **)resource;
    Cache_MarkResourceInUse(0, (void **)resource);
    if (segment != 0) {
        gSPSegment(g_displayListCursor++, 1, matrix);
    } else {
        gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD);
    }
    textures = (void *)textureAddress;
    if (textures == 0) {
        textures = SetN64_GetPackSection(resourceHeader, 0);
    }
    gSPSegment(g_displayListCursor++, 2, (u32)textures);
    partTable = SetN64_GetPackSection(resourceHeader, 2);
    g_geometryPreviousModePreset = -1;
    g_geometryPreviousCombineMode = -1;
    syncCommand = g_displayListCursor++;
    geometryMode = g_geometryEffectGeometryMode;
    partCount = *(s32 *)partTable;
    gDPPipeSync(syncCommand);
    gDPSetTextureLUT(g_displayListCursor++, G_TT_NONE);
    gSPTextureL(g_displayListCursor++, 0x8000, 0x8000, 0, 0xFF, G_TX_RENDERTILE, G_ON);
    gDPSetPrimColor(g_displayListCursor++, 0, 0, 0, 0, 0, opacity & 0xFF);
    gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE,
                     0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE);
    gDPSetRenderMode(g_displayListCursor++, g_geometryTranslucentRenderMode, G_RM_ZB_XLU_DECAL2);
    gSPGeometryMode(g_displayListCursor++, G_SHADE | G_CULL_BACK | G_FOG |
                    G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH, 0);
    geometryMode |= G_CULL_BACK;
    gSPGeometryMode(g_displayListCursor++, 0, geometryMode);
    for (partIndex = 0; partIndex < partCount; partIndex++) {
        partHeader = SetN64_GetPackSection(partTable, partIndex);
        SetN64_GetPackSection(partHeader, 0);
        displayList = SetN64_GetPackSection(partHeader, 1);
        gSPDisplayList(g_displayListCursor++, (u32)displayList);
    }
    g_geometryPreviousCombineMode = -1;
    g_geometryPreviousModePreset = -1;
}

/* GEOMETRY_DRAWCHARACTEREFFECTPARTS.CPP */

/* Draws every part of a model resource with the shared material g_tintedModelSharedMaterial when the frame's command buffer still has 3000 commands free and Geometry_SetupMaterial accepts the material: sets the render mode, selects blend 2 through Geometry_SetCombineMode_GeometryDrawcharactereffectparts, loads the model matrix (or sets it as segment 1), loads an optional two-light block, registers the resource, sets segment 2 to the given texture base or the model's own and emits each part's display list. */

void Geometry_DrawSharedMaterialModel(void **resource, s32 matrix, s32 segment, s32 lights, void *textures, s32 pass) {
    void *header;
    void *base;
    void **parts;
    void *part;
    s32 count;
    s32 i;

    if (g_primaryDisplayListCapacity - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
        return;
    }
    if (Geometry_SetupMaterial((MeshMaterial *)&g_tintedModelSharedMaterial, pass) == 0) {
        return;
    }
    gDPSetRenderMode(g_displayListCursor++, 0x0C184F50, 0);
    Geometry_SetCombineMode(2);
    if (segment != 0) { gSPSegment(g_displayListCursor++, 1, matrix); } else { gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD); }
    if (lights != 0) {
        Gfx *cmd = g_displayListCursor++;
        gMoveWd(cmd, G_MW_NUMLIGHT, 0, 0x18);
        cmd = g_displayListCursor++;
        gDma2p(cmd, G_MOVEMEM, lights + 8, 16, G_MV_LIGHT, 48);
        cmd = g_displayListCursor++;
        gDma2p(cmd, G_MOVEMEM, lights, 16, G_MV_LIGHT, 72);
    }
    Cache_MarkResourceInUse(0, resource);
    header = *resource;
    base = textures;
    if (base == 0) {
        base = SetN64_GetPackSection(header, 0);
    }
    gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
    parts = SetN64_GetPackSection(header, 2);
    count = *(s32 *)parts;
    for (i = 0; i < count; i++) {
        part = SetN64_GetPackSection(parts, i);
        SetN64_GetPackSection(part, 0);
        {
            Gfx *cmd;
            void *list = SetN64_GetPackSection(part, 1);

            cmd = g_displayListCursor++;
            gSPDisplayList(cmd, (unsigned int)list);
        }
    }
}


/* Draws every part of a model resource with the shared material g_geometryOverrideMaterial when the frame's command buffer still has 3000 commands free and Geometry_SetupMaterial accepts the material: prepares through XPlus_NextRandomInteger, flags the material 0x20 and sets g_menuModelFillEnabled, sets the render mode, loads the model matrix (or sets it as segment 1), loads an optional two-light block, registers the resource, sets segment 2 to the given texture base or the model's own and emits each part's display list, skipping parts whose material blend bits are all set unless the owner's 0x122C flag 0x400 is set. */
void Geometry_DrawOwnerFilteredPass(void **resource, PlayerDamageFlagsView *owner, void *matrix, s32 segment, Shared_ParticleLighting *lights, void *textures, s32 pass) {
    void *header;
    void *base;
    void **parts;
    void *part;
    Material *material;
    s32 count;
    s32 i;
    s32 *shared;
    Gfx **start;
    u32 used;

    XPlus_NextRandomInteger();
    start = &g_gameSession.ring.current->commands;
    shared = &g_geometryOverrideMaterial;
    *shared |= 0x20;
    used = (u32)g_displayListCursor - (u32)*start;
    g_menuModelFillEnabled = 1;
    if (g_primaryDisplayListCapacity - used / sizeof(Gfx) < 3000) {
        return;
    }
    if (Geometry_SetupMaterial(shared, pass) == 0) {
        return;
    }
    gDPSetRenderMode(g_displayListCursor++, 0x0C184DD8, 0);
    if (segment != 0) { gSPSegment(g_displayListCursor++, 1, matrix); } else { gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD); }
    if (lights != 0) {
        Gfx *cmd = g_displayListCursor++;
        gMoveWd(cmd, G_MW_NUMLIGHT, 0, 0x18);
        cmd = g_displayListCursor++;
        gDma2p(cmd, G_MOVEMEM, lights->diffuse, 16, G_MV_LIGHT, 48);
        cmd = g_displayListCursor++;
        gDma2p(cmd, G_MOVEMEM, lights, 16, G_MV_LIGHT, 72);
    }
    Cache_MarkResourceInUse(0, resource);
    header = *resource;
    base = textures;
    if (base == 0) {
        base = SetN64_GetPackSection(header, 0);
    }
    gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
    parts = SetN64_GetPackSection(header, 2);
    count = *(s32 *)parts;
    for (i = 0; i < count; i++) {
        part = SetN64_GetPackSection(parts, i);
        material = SetN64_GetPackSection(part, 0);
        if (((material)->flags & 0x38) != 0x38 || ((owner)->flags & 0x400)) {
            Gfx *cmd;
            void *list = SetN64_GetPackSection(part, 1);

            cmd = g_displayListCursor++;
            gSPDisplayList(cmd, (unsigned int)list);
        }
    }
}

/* Draws a character model's parts with the shared material g_tintedModelSharedMaterial, choosing each part by the 0x38 bits of
 * its material byte 6: on the special state 0x12 the part must equal the bits for the actor's material variant, otherwise
 * the 0x38/0x30/0x10 groups are drawn only when the matching flag (fade, bonus, glow) was computed first. */
void Geometry_DrawCharacterEffectParts(void **resource, struct Player *owner, void *matrix, s32 segment, Shared_ParticleLighting *lights, void *textures, s32 pass) {
    void *header;
    void *base;
    void **parts;
    void *part;
    MeshMaterial *material;
    s32 count;
    s32 i;
    s32 hide = 0;
    s32 bonus = 0;
    s32 glow = 0;
    s32 flags;
    MeshMaterial *shared;
    CGameStatus *settings;

    if (matrix == 0) {
        return;
    }
    settings = &g_gameSettings.counters;
    if (settings->enabled != 0) {
        AiProfile *state = owner->profile;
        if (state->character == 11 && state->enabled != 0) {
            hide = 0 < settings->m_nBastilleShield;
        }
    }
    if (owner->reactionFlags & 0x8000) {
        hide = 1;
    }
    if (0.0f < owner->glow) {
        glow = 1;
    }
    if (g_gameSettings.counters.m_bCTFOn != 0 && owner->profile->bonus == 1) {
        bonus = 1;
    }
    shared = (MeshMaterial *)&g_tintedModelSharedMaterial;
    flags = shared->flags;
    shared->flags = flags | 0x400;
    g_menuModelFillColor[0] = g_menuModelFillColor[1] = g_menuModelFillColor[2] = g_geometryDefaultTintColor;
    g_menuModelFillColor[3] = g_geometryDefaultTintAlpha;
    shared->flags = flags | 0x1402;
    g_menuModelFillEnabled = 3;
    if (g_primaryDisplayListCapacity - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
        return;
    }
    if (Geometry_SetupMaterial(shared, pass) != 0) {
        gDPSetRenderMode(g_displayListCursor++, 0x0C184DD8, 0);
        Geometry_SetCombineMode(1);
        if (segment != 0) {
            gSPSegment(g_displayListCursor++, 1, matrix);
        } else {
            gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD);
        }
        if (lights != 0) {
            Gfx *cmd = g_displayListCursor++;
            gMoveWd(cmd, G_MW_NUMLIGHT, 0, 0x18);
            cmd = g_displayListCursor++;
            gDma2p(cmd, G_MOVEMEM, lights->diffuse, 16, G_MV_LIGHT, 48);
            cmd = g_displayListCursor++;
            gDma2p(cmd, G_MOVEMEM, lights, 16, G_MV_LIGHT, 72);
        }
        Cache_MarkResourceInUse(0, resource);
        header = *resource;
        base = textures;
        if (base == 0) {
            base = SetN64_GetPackSection(header, 0);
        }
        gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
        parts = SetN64_GetPackSection(header, 2);
        count = *(s32 *)parts;
        for (i = 0; i < count; i++) {
            AiProfile *state;
            u32 bits;
            part = SetN64_GetPackSection(parts, i);
            material = SetN64_GetPackSection(part, 0);
            if (i == 0) {
                Geometry_ApplyMaterialLighting(matrix, lights, material);
            }
            state = owner->profile;
            if (state->character == 18 && (g_gameSettings.counters.m_bFragTagOn == 0 || state->bonus == 0)) {
                switch (state->variant) {
                case 0:
                    if ((material->mode & 0x38) == 0x28) {
                        if (Geometry_SetupMaterial(material, pass) != 0) {
                            void *list = SetN64_GetPackSection(part, 1);
                            Gfx *cmd = g_displayListCursor++;
                            gSPDisplayList(cmd, (unsigned int)list);
                        }
                    }
                    break;
                case 1:
                    if ((material->mode & 0x38) == 0x20) {
                        if (Geometry_SetupMaterial(material, pass) != 0) {
                            void *list = SetN64_GetPackSection(part, 1);
                            Gfx *cmd = g_displayListCursor++;
                            gSPDisplayList(cmd, (unsigned int)list);
                        }
                    }
                    break;
                case 2:
                    if ((material->mode & 0x38) == 0x18) {
                        if (Geometry_SetupMaterial(material, pass) != 0) {
                            void *list = SetN64_GetPackSection(part, 1);
                            Gfx *cmd = g_displayListCursor++;
                            gSPDisplayList(cmd, (unsigned int)list);
                        }
                    }
                    break;
                }
            } else {
                bits = material->mode & 0x38;
                if (bits == 0x38 && hide == 0) continue;
                if (bits == 0x30 && bonus == 0) continue;
                if (bits == 0x10 && glow == 0) continue;
                if (Geometry_SetupMaterial(material, pass) != 0) {
                    void *list = SetN64_GetPackSection(part, 1);
                    Gfx *cmd = g_displayListCursor++;
                    gSPDisplayList(cmd, (unsigned int)list);
                }
            }
        }
    }
    g_menuModelFillEnabled = 0;
}

/* Draws every part of a model resource with the shared material g_tintedModelSharedMaterial after setting its fixed colour
 * bytes (0x10..0x17) and flags 0x1402, when the frame's command buffer still has 3000 commands free; the first
 * part's material is registered through Geometry_ApplyMaterialLighting with the caller's two inputs. */
void Geometry_DrawModelWithSharedMaterial(void **resource, void *matrix, s32 segment, void *lights, void *textures, s32 pass) {
    void *header;
    void *base;
    void **parts;
    void *part;
    void *material;
    s32 count;
    s32 i;
    MeshMaterial *shared;
    u32 flags;
    if (matrix == 0) {
        return;
    }
    XPlus_NextRandomInteger();
    shared = (MeshMaterial *)&g_tintedModelSharedMaterial;
    flags = shared->flags;
    shared->secondaryColor[0] = 128;
    shared->secondaryColor[1] = 95;
    shared->secondaryColor[2] = 34;
    shared->secondaryColor[3] = 240;
    shared->primaryColor[0] = 219;
    shared->primaryColor[1] = 184;
    shared->primaryColor[2] = 119;
    shared->primaryColor[3] = 64;
    shared->flags = flags | 0x400;
    g_menuModelFillColor[3] = g_geometryOpaqueTintAlpha;
    shared->flags = flags | 0x1402;
    g_menuModelFillEnabled = 1;
    if (g_primaryDisplayListCapacity - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
        return;
    }
    if (Geometry_SetupMaterial(shared, pass) == 0) {
        return;
    }
    gDPSetRenderMode(g_displayListCursor++, 0x0C184DD8, 0);
    Geometry_SetCombineMode(1);
    if (segment != 0) { gSPSegment(g_displayListCursor++, 1, matrix); } else { gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD); }
    Cache_MarkResourceInUse(0, resource);
    header = *resource;
    base = textures;
    if (base == 0) {
        base = SetN64_GetPackSection(header, 0);
    }
    gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
    parts = SetN64_GetPackSection(header, 2);
    count = *(s32 *)parts;
    for (i = 0; i < count; i++) {
        part = SetN64_GetPackSection(parts, i);
        material = SetN64_GetPackSection(part, 0);
        if (i == 0) {
            Geometry_ApplyMaterialLighting(matrix, lights, material);
        }
        {
            Gfx *cmd;
            void *list = SetN64_GetPackSection(part, 1);
            cmd = g_displayListCursor++;
            gSPDisplayList(cmd, (unsigned int)list);
        }
    }
}

/* GEOMETRY_DRAWBLENDPARTS.CPP */


/* Draws the parts of a model resource tinted by an RGBA colour through the shared material g_tintedModelSharedMaterial: sets the tint mode g_menuModelFillEnabled to 3, clears the material's fog colour and sets its flags, records the colour as floats and its alpha on the material, advances the pass modulo 18, and when the frame's command buffer still has 3000 commands free and Geometry_SetupMaterial accepts the material sets the render mode, selects blend 1, registers the resource, loads the matrix (or sets it as segment 1), sets segment 2 to the given texture base or the model's own, sets the lighting on the first part and emits each part whose material blend bits are all set and accepted for the pass, clearing the tint mode afterwards. */

void Geometry_DrawTintedModelParts(void **resource, void *ownerPlayer, void *matrix, s32 segment, void *lights, void *textures, s32 pass, u8 r, u8 g, u8 b, u8 a) {
    void *header;
    void *base;
    void **parts;
    void *part;
    MeshMaterial *material;
    s32 count;
    s32 i;
    SharedModelTintMaterial *shared;
    f32 *tint;

    shared = &g_tintedModelSharedMaterial;
    g_menuModelFillEnabled = 3;
    shared->fog[0] = 0;
    shared->fog[1] = 0;
    shared->fog[2] = 0;
    shared->flags |= 0x1402;
    tint = g_menuModelFillColor;
    tint[0] = r;
    tint[1] = g;
    tint[2] = b;
    tint[3] = a;
    shared->fog[3] = a;
    pass = (pass + 1) % 18;
#if defined(VERSION_DE)
    if (g_displayListCapacityDe - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
#elif defined(VERSION_EU)
    if (g_displayListCapacityEu - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
#elif defined(VERSION_EU_X)
    if (g_displayListCapacityEuX - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
#elif defined(VERSION_US)
    if (g_displayListCapacityUs - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
#elif defined(VERSION_US_REV1)
    if (g_primaryDisplayListCapacity - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
#endif
        return;
    }
    if (Geometry_SetupMaterial(shared, pass) != 0) {
        gDPSetRenderMode(g_displayListCursor++, 0x0C184DD8, 0);
        Geometry_SetCombineMode(1);
        header = *resource;
        Cache_MarkResourceInUse(0, resource);
        if (segment != 0) gSPSegment(g_displayListCursor++, 1, matrix) else gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD);
        base = textures;
        if (base == 0) {
            base = SetN64_GetPackSection(header, 0);
        }
        gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
        parts = SetN64_GetPackSection(header, 2);
        count = *(s32 *)parts;
        for (i = 0; i < count; i++) {
            part = SetN64_GetPackSection(parts, i);
            material = SetN64_GetPackSection(part, 0);
            if (i == 0) {
                Geometry_ApplyMaterialLighting(matrix, lights, material);
            }
            if (((material)->mode & 0x38) == 0x38 && Geometry_SetupMaterial(material, pass) != 0) {
                Gfx *cmd;
                void *list = SetN64_GetPackSection(part, 1);

                cmd = g_displayListCursor++;
                gSPDisplayList(cmd, (unsigned int)list);
            }
        }
    }
    g_menuModelFillEnabled = 0;
}


void Geometry_ExpandBasicModel(s32 cacheContext, s32 modelResource) {
    Geometry_ExpandModelCommands(cacheContext, modelResource, 0, 0);
}

void Geometry_ExpandModelWithSentinel(s32 cacheContext, s32 modelResource) {
    Geometry_ExpandModelCommands(cacheContext, modelResource, 0, 1);
}

void Geometry_ExpandExtendedModel(s32 cacheContext, s32 modelResource) {
    Geometry_ExpandModelCommands(cacheContext, modelResource, 1, 0);
}

void Geometry_AlternateNoOperation(void) {
}
/* An empty function. */
void Geometry_NoOperation(void) {
}



void Geometry_InitializeModelRenderState(void) {
    char modelScale[64];

    Geometry_InvalidateMaterialKeys();
    Graphu64_BuildScaleMatrix(modelScale, g_geometryInitialScale, g_geometryInitialScale, g_geometryInitialScale);
    GraphU64_PackFixedMatrix(modelScale, &g_geometryInitialScaleMatrix);
}

void Geometry_SelectEffectModes(void) {
    if (g_geometryFogEffectEnabled != 0 || g_geometryViewEffect != 0) {
        g_geometryEffectGeometryMode = 0x10000;
        g_geometryOpaqueRenderMode = 0xC4000000;
        g_geometryTranslucentRenderMode = 0xC8000000;
        return;
    }
    g_geometryEffectGeometryMode = 0;
    g_geometryOpaqueRenderMode = 0x0C080000;
    g_geometryTranslucentRenderMode = 0x0C080000;
}

/** Reset two global indices to minus one. */
void Geometry_InvalidateMaterialKeys(void) {
    g_geometryPreviousCombineMode = -1;
    g_geometryPreviousModePreset = -1;
}

void Geometry_SetColorDither(s32 ditherMode) {
    if (g_geometryViewEffect == 0) gDPSetColorDither(g_displayListCursor++, ditherMode) else gDPSetColorDither(g_displayListCursor++, G_CD_NOISE);
}

void Geometry_BeginModelBatch(void) {
    g_modelBatchResource = 0;
    g_modelInstanceQueueCount = 0;
    g_materialGroupCount = 0;
    g_materialInstanceCount = 0;
    g_modelBatchResourceCount = 0;
    g_opaqueMaterialGroupList = 0;
    g_opaqueMaterialGroupTree = 0;
    g_translucentMaterialGroupList = 0;
    g_translucentMaterialGroupTree = 0;
}

void Geometry_FlushModelBatch(void) {
    s32 resourceHandle;
    s32 i;

    Geometry_GroupModelInstances();
    i = 0;
    Geometry_DrawMaterialGroups();
    if (g_modelBatchResourceCount > 0) {
        do {
            resourceHandle = g_modelBatchResources[i];
            Cache_MarkResourceInUse(0, resourceHandle);
            Cache_UnlockResource(0, resourceHandle);
            i += 1;
        } while (i < g_modelBatchResourceCount);
    }
}

void Geometry_DrawModelResource(void **resource, void *matrix, s32 segment, void *lights, void *textures, s32 pass) {
    void *header;
    void *base;
    void **parts;
    void *part;
    void *material;
    s32 count;
    s32 i;

    if (g_primaryDisplayListCapacity - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
        return;
    }
    header = *resource;
    Cache_MarkResourceInUse(0, resource);
    if (segment != 0) { gSPSegment(g_displayListCursor++, 1, matrix); } else { gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD); }
    base = textures;
    if (base == 0) {
        base = SetN64_GetPackSection(header, 0);
    }
    gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
    parts = SetN64_GetPackSection(header, 2);
    count = *(s32 *)parts;
    for (i = 0; i < count; i++) {
        part = SetN64_GetPackSection(parts, i);
        material = SetN64_GetPackSection(part, 0);
        if (i == 0) {
            Geometry_ApplyMaterialLighting(matrix, lights, material);
        }
        if (Geometry_SetupMaterial(material, pass) != 0) {
            Gfx *cmd;
            void *list = SetN64_GetPackSection(part, 1);

            cmd = g_displayListCursor++;
            gSPDisplayList(cmd, (unsigned int)list);
        }
    }
}

void Geometry_QueueModelInstance(void **a, void *b, s32 c, void *d, void *e, s32 f) {
    s32 instanceCount;
    void *vertexBase;
    QueuedModelInstance *queuedInstance;
    void *modelHeader;
    s32 *countp;
    s32 count;
    s32 *queueCountp;

    modelHeader = *a;
    vertexBase = e;
    if (vertexBase == 0) {
        vertexBase = SetN64_GetPackSection(modelHeader, 0);
    }
    if ((g_modelBatchResource != (s32)a) || (g_modelBatchPass != f) || (g_modelInstanceQueueCount == 32)) {
        Geometry_GroupModelInstances();
        if (g_modelBatchResourceCount != 256) {
            Cache_LockResource(0, (s32)a);
            countp = &g_modelBatchResourceCount;
            count = *countp;
            g_modelBatchResources[count] = (s32)a;
            *countp = count + 1;
            goto block_7;
        }
    } else {
block_7:
        g_modelBatchResource = (s32)a;
        g_modelBatchPass = f;
        queueCountp = &g_modelInstanceQueueCount;
        instanceCount = *queueCountp;
        queuedInstance = &g_modelInstanceQueue[instanceCount];
        instanceCount += 1;
        *queueCountp = instanceCount;
        queuedInstance->matrix = b;
        queuedInstance->segmented = c;
        queuedInstance->lights = d;
        queuedInstance->vertices = vertexBase;
    }
}

void Geometry_DrawBlendParts(void **resource, s32 drawView, s32 matrix, s32 segment, s32 lights, void *textures, s32 pass) {
    void *header;
    void *base;
    void **parts;
    void *part;
    MeshMaterial *material;
    s32 count;
    s32 i;

    if (g_primaryDisplayListCapacity - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
        return;
    }
    header = *resource;
    Cache_MarkResourceInUse(0, resource);
    if (segment != 0) { gSPSegment(g_displayListCursor++, 1, matrix); } else { gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD); }
    base = textures;
    if (base == 0) {
        base = SetN64_GetPackSection(header, 0);
    }
    gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
    parts = SetN64_GetPackSection(header, 2);
    count = *(s32 *)parts;
    for (i = 0; i < count; i++) {
        part = SetN64_GetPackSection(parts, i);
        material = SetN64_GetPackSection(part, 0);
        if (i == 0) {
            Geometry_ApplyMaterialLighting(matrix, lights, material);
        }
        if (((material)->mode & 0x38) == 0x38 && Geometry_SetupMaterial(material, pass) != 0) {
            Gfx *cmd;
            void *list = SetN64_GetPackSection(part, 1);

            cmd = g_displayListCursor++;
            gSPDisplayList(cmd, (unsigned int)list);
        }
    }
}

void Geometry_QueueDirectModel(s32 model, void *matrix, void *lights, s32 textures, s32 pass) {
    Geometry_QueueModelById(model, matrix, lights, textures, pass, 1);
}

void Geometry_QueueDeferredModel(s32 modelIndex, void *matrix, void *lights, s32 textures, s32 pass) {
    Geometry_QueueModelById(modelIndex, matrix, lights, textures, pass, 0);
}

void Geometry_DrawWithMaterialOverride(void *shared, s32 mode, void **resource, s32 matrix, s32 segment, s32 lights, void *textures, s32 pass) {
    void *header;
    void *base;
    void **parts;
    void *part;
    void *material;
    s32 count;
    s32 i;

    if (g_primaryDisplayListCapacity - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
        return;
    }
    if (Geometry_SetupMaterial(shared, pass) == 0) {
        return;
    }
    if (segment != 0) { gSPSegment(g_displayListCursor++, 1, matrix); } else { gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD); }
    if (mode != -1) {
        Geometry_SetModePreset(mode);
    }
    Cache_MarkResourceInUse(0, resource);
    header = *resource;
    base = textures;
    if (base == 0) {
        base = SetN64_GetPackSection(header, 0);
    }
    gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
    parts = SetN64_GetPackSection(header, 2);
    count = *(s32 *)parts;
    for (i = 0; i < count; i++) {
        part = SetN64_GetPackSection(parts, i);
        material = SetN64_GetPackSection(part, 0);
        if (i == 0) {
            Geometry_ApplyMaterialLighting(matrix, lights, material);
        }
        {
            Gfx *cmd;
            void *list = SetN64_GetPackSection(part, 1);

            cmd = g_displayListCursor++;
            gSPDisplayList(cmd, (unsigned int)list);
        }
    }
}

void Geometry_UnlockMaterialResources(void **modelResource) {
    void *packSectionResult;
    s32 count;
    s32 i;
    ResourceSectionReference *rec;
    s32 result;

    packSectionResult = SetN64_GetPackSection(*modelResource, 2);
    count = *(s32 *)packSectionResult;
    for (i = 0; i < count; i++) {
        rec = SetN64_GetPackSection(SetN64_GetPackSection(packSectionResult, i), 0);
        if ((rec)->resource == 0) {
            continue;
        }
        result = Textload_RequestTextureVariationSync(&(rec)->resource, -1);
        if (result == 0) {
            continue;
        }
        Cache_UnlockResource(0, result);
    }
}

void Geometry_RefreshMaterialResources(void **resource) {
    void *packSectionResult;
    s32 count;
    s32 i;
    ResourceSectionReference *rec;

    packSectionResult = SetN64_GetPackSection(*resource, 2);
    count = *(s32 *)packSectionResult;
    for (i = 0; i < count; i++) {
        rec = SetN64_GetPackSection(SetN64_GetPackSection(packSectionResult, i), 0);
        if ((rec)->resource == 0) {
            continue;
        }
        Cache_TouchResourceByKey(0, (rec)->resource);
    }
}

s32 *Geometry_CollectMaterialResources(void **modelResource, s32 variation, s32 *resourcesOut) {
    void *packSectionResult;
    s32 count;
    s32 i;
    s32 *out;
    ResourceSectionReference *rec;
    s32 result;

    out = resourcesOut;
    packSectionResult = SetN64_GetPackSection(*modelResource, 2);
    count = *(s32 *)packSectionResult;
    for (i = 0; i < count; i++) {
        rec = SetN64_GetPackSection(SetN64_GetPackSection(packSectionResult, i), 0);
        if ((rec)->resource == 0) {
            continue;
        }
        result = Textload_RequestTextureVariationSync(&(rec)->resource, variation);
        if (result != 0) {
            *out = result;
            out += 1;
        }
    }
    return out;
}

void Geometry_SetViewEffect(int viewEffect) {
    g_geometryViewEffect = viewEffect;
}

/** Return the global word at g_geometryViewEffect. */

int Geometry_GetViewEffect(void) {
    return g_geometryViewEffect;
}

/** Store four bytes in the global color-like value. */

void Geometry_SetPrimitiveColorOverride(unsigned char first, unsigned char second,
                   unsigned char third, unsigned char fourth) {
    g_primitiveColorOverrideEnabled = first;
    g_primitiveColorOverrideRed = second;
    g_primitiveColorOverrideGreen = fourth;
    g_primitiveColorOverrideBlue = third;
}

void Geometry_SetPrimitiveAlphaOverride(int enabled, int alpha) {
    g_primitiveAlphaOverrideEnabled = (unsigned char)enabled;
    g_primitiveAlphaOverride = (unsigned char)alpha;
}

void Geometry_LoadRenderMicrocode(void) {
    Gfx *cmd;

    cmd = g_displayListCursor++;
    gDPFullSync(cmd);
    gSPLoadUcodeEx(g_displayListCursor++, &g_primaryRenderMicrocodeText, &g_primaryRenderMicrocodeData, 0x800);
    cmd = g_displayListCursor++;
    gSPDisplayList(cmd, (uintptr_t) g_cameraViewDisplayListPrimary);
    cmd = g_displayListCursor++;
    gSPDisplayList(cmd, (uintptr_t) g_cameraViewDisplayListSecondary);
}

void Geometry_SwitchRenderMicrocode(void) {
    Gfx *cmd;

    cmd = g_displayListCursor++;
    gDPFullSync(cmd);
    gSPLoadUcodeEx(g_displayListCursor++, &g_alternateRenderMicrocodeText, &g_alternateRenderMicrocodeData, 0x800);
    cmd = g_displayListCursor++;
    gSPDisplayList(cmd, (uintptr_t) g_cameraViewDisplayListPrimary);
    cmd = g_displayListCursor++;
    gSPDisplayList(cmd, (uintptr_t) g_cameraViewDisplayListSecondary);
}

/** Initialize the two-word state to minus one and zero. */
void Geometry_ResetDisplayListState(int *state) {
    state[0] = -1;
    state[1] = 0;
}

/** Clear four related global state words. */
void Geometry_ClearMaterialGroups(void) {
    g_opaqueMaterialGroupList = 0;
    g_opaqueMaterialGroupTree = 0;
    g_translucentMaterialGroupList = 0;
    g_translucentMaterialGroupTree = 0;
}

void *Geometry_FindMaterialNodeOrParent(MaterialTreeNode **root, u32 materialKey)
{
  u32 nodeKey;
  MaterialTreeNode *parent;
  MaterialTreeNode *node;
  node = *root;
  parent = 0;
  if (node != 0)
  {
    loop_1:
    nodeKey = node->key;

    if (node->key)
    {
      parent = node;
    }
    else
    {
      parent = node;
    }
    if (nodeKey != materialKey)
    {
      if (materialKey < nodeKey)
      {
        node = parent->left;
      }
      else
      {
        node = parent->right;
      }
      if (node == 0)
      {
        goto block_6;
      }
      goto loop_1;
    }
  }
  else
  {
    block_6:
    node = parent;

  }
  return node;
}

/** Insert a node adjacent to the supplied node in an intrusive ordered tree. */
void Geometry_InsertMaterialNode(TreeNode **root, TreeNode **emptyRoot, TreeNode *node, TreeNode *current) {
    if (current != 0) {
        if (node->key < current->key) {
            current->link18 = node;
            node->link1c = 0;
            node->link18 = 0;
            node->link14 = current;
            node->link10 = current->link10;
            if (current->link10 != 0)
                current->link10->link14 = node;
            current->link10 = node;
            if (*root == current)
                *root = node;
        } else {
            current->link1c = node;
            node->link1c = 0;
            node->link18 = 0;
            node->link14 = current->link14;
            if (current->link14 != 0)
                current->link14->link10 = node;
            node->link10 = current;
            current->link14 = node;
        }
    } else {
        *emptyRoot = node;
        *root = node;
        node->link1c = 0;
        node->link18 = 0;
        node->link14 = 0;
        node->link10 = 0;
    }
}
#if !(defined(VERSION_US_REV1))

const float g_geometryInitialModelScale[1] = {
    2.0f,
};
#endif
#if defined(VERSION_US_REV1)

const float g_geometryDrawblendparts[1] = {
    2.0f,
};
#endif

/* GEOMETRY.CPP */




const float g_geometryLightColorMaximum[1] = {
    127.0f,
};

#if !(defined(VERSION_US_REV1))
const char s_simpleObjectIndexText[18] =
    "simp object index\000";
#endif

#if defined(VERSION_US_REV1)
const char s_simpObjectIndexText[18] = "simp object index";
#endif

#if !(defined(VERSION_US_REV1))
const char s_simpleModelsIndexText[18] =
    "simp models index\000";
#endif

#if defined(VERSION_US_REV1)
const char s_simpModelsIndexText[18] = "simp models index";
#endif

#if !(defined(VERSION_US_REV1))
const char s_simpleModelText[11] =
    "simp model\000";
#endif

#if defined(VERSION_US_REV1)
const char s_simpModelText[11] =
    "simp model";
#endif

const float g_geometryModelDistanceConstants[2] = {
    8.0e+01f, 1.6e+02f,
};

const float g_geometryModelPartDistanceConstant[1] = {
    8e+01f,
};

/* GEOMETRY_DRAWRESOURCEMODEL_DATA.CPP */

#if defined(VERSION_DE)
struct {
    u32 words0[377];
    char text1[8];
    u32 words2[34];
    char text3[8];
    u32 words4[13];
} g_resourceModelDisplayListAndEventCallbackWords_de = {
    {
        0xFFFFFF00, 0xFFFFFF00, 0x00007F00, 0x00000000, 0xD9000000, 0x00000000, 0xD9FFFFFF, 0x00000001,
        0xDB020000, 0x00000018, 0xDC08060A, (unsigned int)&g_savedPlayerModelLighting[4], 0xDC08090A, (unsigned int)g_playerModelLighting, 0xDF000000,
        0x00000000,
        0xE3000A01, 0x00000000, 0xE3000800, 0x00000000, 0xE3000F00, 0x00000000, 0xE3001001, 0x00000000,
        0xE3000D01, 0x00000000, 0xE3000C00, 0x00080000, 0xE3001201, 0x00002000, 0xE3001402, 0x00000C00,
        0xE3001700, 0x00000000, 0xE2001E01, 0x00000000, 0xE7000000, 0x00000000, 0xDF000000, 0x00000000,
        0xF5100000, 0x07000000, 0xF3000000, 0x0755C000, 0xF5101000, 0x00014050, 0xF2000000, 0x0007C07C,
        0xF5100900, 0x01010441, 0xF2000000, 0x0103C03C, 0xF5100540, 0x0200C832, 0xF2000000, 0x0201C01C,
        0xF5100350, 0x03008C23, 0xF2000000, 0x0300C00C, 0xF5100354, 0x04005014, 0xF2000000, 0x04004004,
        0xF5100356, 0x05001405, 0xF2000000, 0x05000000, 0xE3001001, 0x00000000, 0xDF000000, 0x00000000,
        0xF5100000, 0x07000000, 0xF3000000, 0x0755C000, 0xF5101000, 0x00054150, 0xF2000000, 0x0007C07C,
        0xF5100900, 0x01050541, 0xF2000000, 0x0103C03C, 0xF5100540, 0x0204C932, 0xF2000000, 0x0201C01C,
        0xF5100350, 0x03048D23, 0xF2000000, 0x0300C00C, 0xF5100354, 0x04045114, 0xF2000000, 0x04004004,
        0xF5100356, 0x05041505, 0xF2000000, 0x05000000, 0xE3001001, 0x00000000, 0xDF000000, 0x00000000,
        0xF5100000, 0x07000000, 0xF3000000, 0x0755C000, 0xF5101000, 0x00017C5F, 0xF2000000, 0x0007C07C,
        0xF5101000, 0x01014050, 0xF2000000, 0x0107C07C, 0xF5100900, 0x02010441, 0xF2000000, 0x0203C03C,
        0xF5100540, 0x0300C832, 0xF2000000, 0x0301C01C, 0xF5100350, 0x04008C23, 0xF2000000, 0x0400C00C,
        0xF5100354, 0x05005014, 0xF2000000, 0x05004004, 0xF5100356, 0x06001405, 0xF2000000, 0x06000000,
        0xE3000D01, 0x00040000, 0xE3001001, 0x00000000, 0xDF000000, 0x00000000, 0xF5100000, 0x07000000,
        0xF3000000, 0x0755C000, 0xF5101000, 0x0001785E, 0xF2000000, 0x0007C07C, 0xF5101000, 0x01014050,
        0xF2000000, 0x0107C07C, 0xF5100900, 0x02010441, 0xF2000000, 0x0203C03C, 0xF5100540, 0x0300C832,
        0xF2000000, 0x0301C01C, 0xF5100350, 0x04008C23, 0xF2000000, 0x0400C00C, 0xF5100354, 0x05005014,
        0xF2000000, 0x05004004, 0xF5100356, 0x06001405, 0xF2000000, 0x06000000, 0xE3000D01, 0x00040000,
        0xE3001001, 0x00000000, 0xDF000000, 0x00000000, 0xF5900000, 0x07000000, 0xF3000000, 0x07580000,
        0xF5800800, 0x00018060, 0xF2000000, 0x000FC0FC, 0xF5800500, 0x01014451, 0xF2000000, 0x0107C07C,
        0xF5800340, 0x02010842, 0xF2000000, 0x0203C03C, 0xF5800350, 0x0300CC33, 0xF2000000, 0x0301C01C,
        0xF5800358, 0x04009024, 0xF2000000, 0x0400C00C, 0xF580035C, 0x05005415, 0xF2000000, 0x05004004,
        0xF580035E, 0x06001806, 0xF2000000, 0x06000000, 0xE3000D01, 0x00000000, 0xE3001001, 0x00000000,
        0xDF000000, 0x00000000, 0xE3001001, 0x00000000, 0xD7000002, 0x80008000, 0xD9F9FBFF, 0x00000000,
        0xD9FFFFFF, 0x00210004, 0xFCFF97FF, 0xFFFFFE38, 0xE200001C, 0xC8104B50, 0xDB040004, 0x00000001,
        0xDB04000C, 0x00000001, 0xDB040014, 0x0000FFFF, 0xDB04001C, 0x0000FFFF, 0x01004008,
        (unsigned int)g_particleQuadVertices,
        0x06000204, 0x00040600, 0xDB040004, 0x00000005, 0xDB04000C, 0x00000005, 0xDB040014, 0x0000FFFB,
        0xDB04001C, 0x0000FFFB, 0xDF000000, 0x00000000, 0xE3001001, 0x00000000, 0xD7FF0002, 0x80008000,
        0xD9F9FBFF, 0x00000000, 0xD9FFFFFF, 0x00210004, 0xFCFF97FF, 0xFFFFFE38, 0xE200001C, 0xC8104E50,
        0xDB040004, 0x00000001, 0xDB04000C, 0x00000001, 0xDB040014, 0x0000FFFF, 0xDB04001C, 0x0000FFFF,
        0x01004008, (unsigned int)g_particleQuadVertices, 0x06000204, 0x00040600, 0xDB040004, 0x00000005, 0xDB04000C,
        0x00000005,
        0xDB040014, 0x0000FFFB, 0xDB04001C, 0x0000FFFB, 0xDF000000, 0x00000000,
        (unsigned int)g_Events_SpawnActorEffectEncodedCallback, 0x00000000,
        (unsigned int)g_Events_PlayClipEventPackedCallbackDe, 0x00000000,
        (unsigned int)g_Events_SpawnActorEffectEncodedCallback, 0x00000000,
        (unsigned int)g_Events_ApplyDirectDamagePackedCallbackDe, 0x00000004,
        (unsigned int)g_Events_ApplyRadialDamagePackedCallbackDe, 0x00000006,
        (unsigned int)g_Events_ApplyRadialDamageWithKnockbackPackedCallbackDe, 0x00000006,
        (unsigned int)g_Events_PreserveEventArgumentPackedCallbackDe, 0x0000000A,
        (unsigned int)g_Events_RunActorNodeOperationPackedCallbackDe, 0x00000010,
        ENCODED_CALLBACK_ADDRESS(Events_RunSecondNodeOperation), 0x00000010,
        (unsigned int)g_Events_SpawnActorEffectEncodedCallback, 0x00000000,
        ENCODED_CALLBACK_ADDRESS(Events_StartCameraFadeAtPoint), 0x00000000,
        (unsigned int)g_Events_ConsumeEventArgumentPackedCallbackDe, 0x00000000,
        (unsigned int)g_Events_RequestActorPositionPackedCallbackDe, 0x00000000,
        (unsigned int)g_Events_StartEnabledCameraEmitterPackedCallbackDe, 0x00000000,
        (unsigned int)g_Events_StartDisabledCameraEmitterPackedCallbackDe, 0x00000000,
        (unsigned int)g_Events_PostGameplayMessagePackedCallbackDe, 0x00000000,
        (unsigned int)g_Events_ApplyLowFlagRadialDamagePackedCallbackDe, 0x00000006,
        (unsigned int)g_Events_ApplyLowFlagRadialKnockbackPackedCallbackDe, 0x00000006,
        (unsigned int)g_Events_ApplyMidFlagRadialDamagePackedCallbackDe, 0x00000007,
        (unsigned int)g_Events_ApplyMidFlagRadialKnockbackPackedCallbackDe, 0x00000007,
        (unsigned int)g_Events_ApplyHighFlagRadialDamagePackedCallbackDe, 0x00000006,
        (unsigned int)g_Events_ApplyHighFlagRadialKnockbackPackedCallbackDe, 0x00000006,
        (unsigned int)g_Events_StartActorEmitterPackedCallbackDe, 0x00000000,
        ENCODED_CALLBACK_ADDRESS(Events_IgnoreEvent), 0x00000000,
        ENCODED_CALLBACK_ADDRESS(Events_PlayTeamClip), 0x00000000,
        (unsigned int)g_Events_SpawnFilteredActorEffectPackedCallbackDe, 0x00000000,
        (unsigned int)g_Events_FireWithinHeightRangePackedCallbackDe, 0x00000007,
        ENCODED_CALLBACK_ADDRESS(Events_SetActorEventBit), 0x00000000,
        (unsigned int)g_Events_ClearActorEventBitPackedCallbackDe, 0x00000000,
        (unsigned int)g_Events_SpawnAttachedEffectPackedCallbackDe, 0x00000000,
        (unsigned int)addrLow_Events_PlayTeamEffect, 0x00000000,
        (unsigned int)g_Events_StopClipEventPackedCallbackDe, 0x00000000,
        (unsigned int)addrLow_Events_SetActorLoopingSound_us_rev1, 0x00000000,
        (unsigned int)addrLow_Events_StopActorLoopingSound, 0x00000000,
        (unsigned int)addrLow_Events_IncrementNearbyPlayerCounter, 0x00000002,
        (unsigned int)addrLow_Events_SpawnPositionedEffect, 0x00000000,
        (unsigned int)addrLow_Events_SetActorEffectMode, 0x00000000,
        (unsigned int)addrLow_Events_DeactivateActor, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00071115, 0x15110700, 0x00000000, 0x00000003, 0x1529363E, 0x3E362815, 0x03000000,
        0x0000031C, 0x3550626E, 0x6E625038, 0x1C010000, 0x00001738, 0x5879919F, 0x9E927959, 0x36170000,
    },
    "5PbnnbP8",
    {
        0x1C010000, 0x00001738, 0x5879919F, 0x9E927959, 0x36170000, 0x00082850, 0x799FBDCE, 0xCEBE9F79,
        0x4E290800, 0x00113662, 0x91BEDFF2, 0xF2E0BD92, 0x62361000, 0x00173E6E, 0x9FCEF2FF, 0xFFF3CE9F,
        0x6D3E1500, 0x00173D6E, 0xA1CDF2FF, 0xFFF3CE9F, 0x6D401700, 0x00103662, 0x92BEDFF3, 0xF2E0BE92,
        0x62361100, 0x00072850, 0x799FBDCF, 0xCEBE9F78, 0x4E290700, 0x00001736, 0x597A92A1, 0x9F927958,
        0x36150000, 0x0000031C, 0x3650646E, 0x6E644E36, 0x1C010000, 0x00000003, 0x1528363E, 0x3D362815,
    },
    "6PdnndN6",
    {
        0x1C010000, 0x00000003, 0x1528363E, 0x3D362815, 0x03000000, 0x00000000, 0x00071015, 0x15110700,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    },
};

struct {
    u32 renderModesAndFlags[12];
    s32 fillEnabled;
    f32 fillRed;
    f32 fillGreen;
    f32 fillBlue;
    f32 fillAlpha;
    f32 fillTargetAlpha;
    u8 primitiveOverride[6];
    u8 alignmentFill[2]; /* Tail padding rounds the record up to its 4-byte alignment. */
} g_geometryDrawResourceModelWritableWords_de __attribute__((aligned(4))) = {
    { 0xffffffff, 0xffffffff, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x10000, 0xc4000000, 0xc8000000 },
    0,
    255.0f,
    255.0f,
    255.0f,
    255.0f,
    255.0f,
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x0, 0x0 }
};
typedef char g_geometryDrawResourceModelWritableWords_deSizeCheck[
    (sizeof(g_geometryDrawResourceModelWritableWords_de) == 80) ? 1 : -1];

unsigned short k_GeometryDrawresourcemodelEncodedHalfwords[8] = {
    0xA000, 0x0000, 0xA000, 0x0000, 0x00FF, 0x0000, 0x00FF, 0x0000,
};
#endif

/* SNDPLAYER.CPP */
#if defined(VERSION_EU)
EventHandlerAddressTable_euLayout g_eventHandlerAddressTable_eu = { { -256, -256, 32512, 0 }, { { 0xD9000000,
             0 }, { 0xD9FFFFFF, 1 }, { 0xDB020000, 24 }, { 0xDC08060A, (unsigned int)&g_savedPlayerModelLighting[4] },
         { 0xDC08090A, (unsigned int)&g_playerModelLighting }, { 0xDF000000, 0 } }, { { 0xE3000A01, 0 },
         { 0xE3000800, 0 }, { 0xE3000F00, 0 }, { 0xE3001001, 0 }, { 0xE3000D01, 0 }, { 0xE3000C00, 524288 },
         { 0xE3001201, 8192 }, { 0xE3001402, 3072 }, { 0xE3001700, 0 }, { 0xE2001E01, 0 }, { 0xE7000000,
             0 }, { 0xDF000000, 0 } }, { { 0xF5100000, 0x07000000 }, { 0xF3000000, 0x0755C000 }, { 0xF5101000,
             82000 }, { 0xF2000000, 508028 }, { 0xF5100900, 0x01010441 }, { 0xF2000000, 0x0103C03C },
         { 0xF5100540, 0x0200C832 }, { 0xF2000000, 0x0201C01C }, { 0xF5100350, 0x03008C23 }, { 0xF2000000,
             0x0300C00C }, { 0xF5100354, 0x04005014 }, { 0xF2000000, 0x04004004 }, { 0xF5100356, 0x05001405 },
         { 0xF2000000, 0x05000000 }, { 0xE3001001, 0 }, { 0xDF000000, 0 } }, { { 0xF5100000, 0x07000000 },
         { 0xF3000000, 0x0755C000 }, { 0xF5101000, 344400 }, { 0xF2000000, 508028 }, { 0xF5100900, 0x01050541 },
         { 0xF2000000, 0x0103C03C }, { 0xF5100540, 0x0204C932 }, { 0xF2000000, 0x0201C01C }, { 0xF5100350,
             0x03048D23 }, { 0xF2000000, 0x0300C00C }, { 0xF5100354, 0x04045114 }, { 0xF2000000, 0x04004004 },
         { 0xF5100356, 0x05041505 }, { 0xF2000000, 0x05000000 }, { 0xE3001001, 0 }, { 0xDF000000, 0 } },
     { { 0xF5100000, 0x07000000 }, { 0xF3000000, 0x0755C000 }, { 0xF5101000, 97375 }, { 0xF2000000, 508028 },
         { 0xF5101000, 0x01014050 }, { 0xF2000000, 0x0107C07C }, { 0xF5100900, 0x02010441 }, { 0xF2000000,
             0x0203C03C }, { 0xF5100540, 0x0300C832 }, { 0xF2000000, 0x0301C01C }, { 0xF5100350, 0x04008C23 },
         { 0xF2000000, 0x0400C00C }, { 0xF5100354, 0x05005014 }, { 0xF2000000, 0x05004004 }, { 0xF5100356,
             0x06001405 }, { 0xF2000000, 0x06000000 }, { 0xE3000D01, 262144 }, { 0xE3001001, 0 }, { 0xDF000000,
             0 } }, { { 0xF5100000, 0x07000000 }, { 0xF3000000, 0x0755C000 }, { 0xF5101000, 96350 }, { 0xF2000000,
             508028 }, { 0xF5101000, 0x01014050 }, { 0xF2000000, 0x0107C07C }, { 0xF5100900, 0x02010441 },
         { 0xF2000000, 0x0203C03C }, { 0xF5100540, 0x0300C832 }, { 0xF2000000, 0x0301C01C }, { 0xF5100350,
             0x04008C23 }, { 0xF2000000, 0x0400C00C }, { 0xF5100354, 0x05005014 }, { 0xF2000000, 0x05004004 },
         { 0xF5100356, 0x06001405 }, { 0xF2000000, 0x06000000 }, { 0xE3000D01, 262144 }, { 0xE3001001,
             0 }, { 0xDF000000, 0 } }, { { 0xF5900000, 0x07000000 }, { 0xF3000000, 0x07580000 }, { 0xF5800800,
             98400 }, { 0xF2000000, 1032444 }, { 0xF5800500, 0x01014451 }, { 0xF2000000, 0x0107C07C },
         { 0xF5800340, 0x02010842 }, { 0xF2000000, 0x0203C03C }, { 0xF5800350, 0x0300CC33 }, { 0xF2000000,
             0x0301C01C }, { 0xF5800358, 0x04009024 }, { 0xF2000000, 0x0400C00C }, { 0xF580035C, 0x05005415 },
         { 0xF2000000, 0x05004004 }, { 0xF580035E, 0x06001806 }, { 0xF2000000, 0x06000000 }, { 0xE3000D01,
             0 }, { 0xE3001001, 0 }, { 0xDF000000, 0 } }, { { 0xE3001001, 0 }, { 0xD7000002, 0x80008000 },
         { 0xD9F9FBFF, 0 }, { 0xD9FFFFFF, 2162692 }, { 0xFCFF97FF, -456 }, { 0xE200001C, 0xC8104B50 },
         { 0xDB040004, 1 }, { 0xDB04000C, 1 }, { 0xDB040014, 65535 }, { 0xDB04001C, 65535 }, { 0x01004008,
             (unsigned int)&g_particleQuadVertices }, { 0x06000204, 263680 }, { 0xDB040004, 5 }, { 0xDB04000C,
             5 }, { 0xDB040014, 65531 }, { 0xDB04001C, 65531 }, { 0xDF000000, 0 } }, { { 0xE3001001, 0 },
         { 0xD7FF0002, 0x80008000 }, { 0xD9F9FBFF, 0 }, { 0xD9FFFFFF, 2162692 }, { 0xFCFF97FF, -456 },
         { 0xE200001C, 0xC8104E50 }, { 0xDB040004, 1 }, { 0xDB04000C, 1 }, { 0xDB040014, 65535 }, { 0xDB04001C,
             65535 }, { 0x01004008, (unsigned int)&g_particleQuadVertices }, { 0x06000204, 263680 }, { 0xDB040004,
             5 }, { 0xDB04000C, 5 }, { 0xDB040014, 65531 }, { 0xDB04001C, 65531 }, { 0xDF000000, 0 } },
     { 82, 79, 71, 82, 65, 77, 77, 65 }, { { (unsigned int)g_playClipEventAddress, 0 }, { (unsigned int)g_spawnActorEffectAddress,
             0 }, { (unsigned int)g_applyDirectDamageAddress, 4 }, { (unsigned int)addrLow_Events_ApplyDirectDamage_us_rev1,
             6 }, { (unsigned int)g_applyRadialDamageWithKnockbackAddress, 6 }, { (unsigned int)g_preserveEventArgumentAddress,
             10 }, { (unsigned int)addrLow_Events_ApplyRadialDamageWithKnockback_us_rev1, 16 }, { (unsigned int)g_runNextNodeOperationAddress,
             16 }, { (unsigned int)g_spawnActorEffectAddress, 0 }, { (unsigned int)Events_RunSecondNodeOperation,
             0 }, { (unsigned int)g_consumeEventArgumentAddress, 0 }, { (unsigned int)g_requestActorPositionAddress,
             0 }, { (unsigned int)g_startEnabledCameraEmitterAddress, 0 }, { (unsigned int)g_startDisabledCameraEmitterAddress,
             0 }, { (unsigned int)g_postGameplayMessageAddress, 0 }, { (unsigned int)addrLow_Events_ApplyFlag100RadialDamage_eu,
             6 }, { (unsigned int)addrLow_Events_ApplyFlag100RadialKnockback_eu, 6 }, { (unsigned int)addrLow_Events_ApplyFlag200RadialDamage_eu,
             7 }, { (unsigned int)addrLow_Events_ApplyFlag200RadialKnockback_eu, 7 }, { (unsigned int)addrLow_Events_ApplyFlag400RadialDamage_eu,
             6 }, { (unsigned int)addrLow_Events_ApplyFlag400RadialKnockback_eu, 6 }, { (unsigned int)g_startActorEmitterAddress,
             0 }, { (unsigned int)g_ignoreEventAddress, 0 }, { (unsigned int)g_playTeamClipAddress, 0 },
         { (unsigned int)g_spawnFilteredActorEffectAddress, 0 }, { (unsigned int)g_fireWithinHeightRangeAddress,
             7 }, { (unsigned int)g_setActorEventBitAddress, 0 }, { (unsigned int)Events_SetActorEventBit,
             0 }, { (unsigned int)g_spawnAttachedEffectAddress, 0 }, { (unsigned int)g_playTeamEffectAddress,
             0 }, { (unsigned int)Events_SpawnActorEffect, 0 }, { (unsigned int)g_setActorLoopingSoundAddress,
             0 }, { (unsigned int)addrLow_Events_SetActorLoopingSound_us_rev1, 0 }, { (unsigned int)g_incrementNearbyPlayerCounterAddress,
             2 }, { (unsigned int)g_spawnPositionedEffectAddress, 0 }, { (unsigned int)g_setActorEffectModeAddress,
             0 }, { (unsigned int)g_deactivateActorAddress, 0 } }, { 67, 84, 69, 85, 82, 32, 68, 69 },
     { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 7, 17, 21, 21, 17, 7, 0, 0,
             0, 0, 0 }, { 0, 0, 0, 3, 21, 41, 54, 62, 62, 54, 40, 21, 3, 0, 0, 0 }, { 0, 0, 3, 28, 53,
             80, 98, 110, 110, 98, 80, 56, 28, 1, 0, 0 }, { 0, 0, 23, 56, 88, 121, 145, 159, 158, 146,
             121, 89, 54, 23, 0, 0 }, { 0, 8, 40, 80, 121, 159, 189, 206, 206, 190, 159, 121, 78, 41,
             8, 0 }, { 0, 17, 54, 98, 145, 190, 223, 242, 242, 224, 189, 146, 98, 54, 16, 0 }, { 0, 23,
             62, 110, 159, 206, 242, 255, 255, 243, 206, 159, 109, 62, 21, 0 }, { 0, 23, 61, 110, 161,
             205, 242, 255, 255, 243, 206, 159, 109, 64, 23, 0 }, { 0, 16, 54, 98, 146, 190, 223, 243,
             242, 224, 190, 146, 98, 54, 17, 0 }, { 0, 7, 40, 80, 121, 159, 189, 207, 206, 190, 159, 120,
             78, 41, 7, 0 }, { 0, 0, 23, 54, 89, 122, 146, 161, 159, 146, 121, 88, 54, 21, 0, 0 }, { 0,
             0, 3, 28, 54, 80, 100, 110, 110, 100, 78, 54, 28, 1, 0, 0 }, { 0, 0, 0, 3, 21, 40, 54, 62,
             61, 54, 40, 21, 3, 0, 0, 0 }, { 0, 0, 0, 0, 0, 7, 16, 21, 21, 17, 7, 0, 0, 0, 0, 0 }, { 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } } };
#endif

/* GEOMETRY_DRAWRESOURCEMODEL_DATA.CPP */
#if defined(VERSION_EU)
u32 g_geometryPreviousModePreset = 0xFFFFFFFF;
int g_geometryPreviousCombineMode = -1;
EngineGeometryState g_geometryPreviousModePresetBlock = {
    1, 1, 1, 1, 1, 1, 1, 0x00010000, 0xC4000000, 0xC8000000, 0,
    { 255.0f, 255.0f, 255.0f, 255.0f, 255.0f },
    { 0, 0, 0, 0 }, 0, 0, { 0, 0 }
};
ResourceModelColorMasksLayout g_resourceModelColorMasks = {
    0xA0000000, 0xA0000000,
    { 16711680, 16711680 },
};
#endif

/* ACTOR_EVENT_CALLBACK_TABLE_EU_X.CPP */

#if defined(VERSION_EU_X)
struct {
    u32 words0[377];
    char text1[8];
    u32 words2[34];
    char text3[8];
    u32 words4[13];
} g_actorEventCallbackTableWords_eu_x = {
    {
        0xFFFFFF00, 0xFFFFFF00, 0x00007F00, 0x00000000, 0xD9000000, 0x00000000, 0xD9FFFFFF, 0x00000001,
        0xDB020000, 0x00000018, 0xDC08060A, (unsigned int)&g_savedPlayerModelLighting[4], 0xDC08090A, (unsigned int)g_playerModelLighting, 0xDF000000,
        0x00000000,
        0xE3000A01, 0x00000000, 0xE3000800, 0x00000000, 0xE3000F00, 0x00000000, 0xE3001001, 0x00000000,
        0xE3000D01, 0x00000000, 0xE3000C00, 0x00080000, 0xE3001201, 0x00002000, 0xE3001402, 0x00000C00,
        0xE3001700, 0x00000000, 0xE2001E01, 0x00000000, 0xE7000000, 0x00000000, 0xDF000000, 0x00000000,
        0xF5100000, 0x07000000, 0xF3000000, 0x0755C000, 0xF5101000, 0x00014050, 0xF2000000, 0x0007C07C,
        0xF5100900, 0x01010441, 0xF2000000, 0x0103C03C, 0xF5100540, 0x0200C832, 0xF2000000, 0x0201C01C,
        0xF5100350, 0x03008C23, 0xF2000000, 0x0300C00C, 0xF5100354, 0x04005014, 0xF2000000, 0x04004004,
        0xF5100356, 0x05001405, 0xF2000000, 0x05000000, 0xE3001001, 0x00000000, 0xDF000000, 0x00000000,
        0xF5100000, 0x07000000, 0xF3000000, 0x0755C000, 0xF5101000, 0x00054150, 0xF2000000, 0x0007C07C,
        0xF5100900, 0x01050541, 0xF2000000, 0x0103C03C, 0xF5100540, 0x0204C932, 0xF2000000, 0x0201C01C,
        0xF5100350, 0x03048D23, 0xF2000000, 0x0300C00C, 0xF5100354, 0x04045114, 0xF2000000, 0x04004004,
        0xF5100356, 0x05041505, 0xF2000000, 0x05000000, 0xE3001001, 0x00000000, 0xDF000000, 0x00000000,
        0xF5100000, 0x07000000, 0xF3000000, 0x0755C000, 0xF5101000, 0x00017C5F, 0xF2000000, 0x0007C07C,
        0xF5101000, 0x01014050, 0xF2000000, 0x0107C07C, 0xF5100900, 0x02010441, 0xF2000000, 0x0203C03C,
        0xF5100540, 0x0300C832, 0xF2000000, 0x0301C01C, 0xF5100350, 0x04008C23, 0xF2000000, 0x0400C00C,
        0xF5100354, 0x05005014, 0xF2000000, 0x05004004, 0xF5100356, 0x06001405, 0xF2000000, 0x06000000,
        0xE3000D01, 0x00040000, 0xE3001001, 0x00000000, 0xDF000000, 0x00000000, 0xF5100000, 0x07000000,
        0xF3000000, 0x0755C000, 0xF5101000, 0x0001785E, 0xF2000000, 0x0007C07C, 0xF5101000, 0x01014050,
        0xF2000000, 0x0107C07C, 0xF5100900, 0x02010441, 0xF2000000, 0x0203C03C, 0xF5100540, 0x0300C832,
        0xF2000000, 0x0301C01C, 0xF5100350, 0x04008C23, 0xF2000000, 0x0400C00C, 0xF5100354, 0x05005014,
        0xF2000000, 0x05004004, 0xF5100356, 0x06001405, 0xF2000000, 0x06000000, 0xE3000D01, 0x00040000,
        0xE3001001, 0x00000000, 0xDF000000, 0x00000000, 0xF5900000, 0x07000000, 0xF3000000, 0x07580000,
        0xF5800800, 0x00018060, 0xF2000000, 0x000FC0FC, 0xF5800500, 0x01014451, 0xF2000000, 0x0107C07C,
        0xF5800340, 0x02010842, 0xF2000000, 0x0203C03C, 0xF5800350, 0x0300CC33, 0xF2000000, 0x0301C01C,
        0xF5800358, 0x04009024, 0xF2000000, 0x0400C00C, 0xF580035C, 0x05005415, 0xF2000000, 0x05004004,
        0xF580035E, 0x06001806, 0xF2000000, 0x06000000, 0xE3000D01, 0x00000000, 0xE3001001, 0x00000000,
        0xDF000000, 0x00000000, 0xE3001001, 0x00000000, 0xD7000002, 0x80008000, 0xD9F9FBFF, 0x00000000,
        0xD9FFFFFF, 0x00210004, 0xFCFF97FF, 0xFFFFFE38, 0xE200001C, 0xC8104B50, 0xDB040004, 0x00000001,
        0xDB04000C, 0x00000001, 0xDB040014, 0x0000FFFF, 0xDB04001C, 0x0000FFFF, 0x01004008,
        (unsigned int)g_particleQuadVertices,
        0x06000204, 0x00040600, 0xDB040004, 0x00000005, 0xDB04000C, 0x00000005, 0xDB040014, 0x0000FFFB,
        0xDB04001C, 0x0000FFFB, 0xDF000000, 0x00000000, 0xE3001001, 0x00000000, 0xD7FF0002, 0x80008000,
        0xD9F9FBFF, 0x00000000, 0xD9FFFFFF, 0x00210004, 0xFCFF97FF, 0xFFFFFE38, 0xE200001C, 0xC8104E50,
        0xDB040004, 0x00000001, 0xDB04000C, 0x00000001, 0xDB040014, 0x0000FFFF, 0xDB04001C, 0x0000FFFF,
        0x01004008, (unsigned int)g_particleQuadVertices, 0x06000204, 0x00040600, 0xDB040004, 0x00000005, 0xDB04000C,
        0x00000005,
        0xDB040014, 0x0000FFFB, 0xDB04001C, 0x0000FFFB, 0xDF000000, 0x00000000, 0x3F169CFB, 0x3F162965,
        (unsigned int)Events_PlayClipEvent, 0x00000000, (unsigned int)Events_SpawnActorEffect, 0x00000000,
        (unsigned int)Events_ApplyDirectDamage, 0x00000004, (unsigned int)Events_ApplyRadialDamage, 0x00000006,
        (unsigned int)Events_ApplyRadialDamageWithKnockback, 0x00000006, (unsigned int)Events_PreserveEventArgument,
        0x0000000A, (unsigned int)Events_RunActorNodeOperation, 0x00000010,
        ENCODED_CALLBACK_ADDRESS(Events_RunSecondNodeOperation), 0x00000010,
        (unsigned int)Events_SpawnActorEffect, 0x00000000,
        (unsigned int)addrLow_Events_RunSecondNodeOperation_us_rev1, 0x00000000,
        (unsigned int)Events_ConsumeEventArgument, 0x00000000, (unsigned int)Events_RequestActorPosition, 0x00000000,
        (unsigned int)Events_StartEnabledCameraEmitter, 0x00000000, (unsigned int)Events_StartDisabledCameraEmitter,
        0x00000000, (unsigned int)Events_PostGameplayMessage, 0x00000000, (unsigned int)Events_ApplyFlag100RadialDamage,
        0x00000006,
        (unsigned int)Events_ApplyFlag100RadialKnockback, 0x00000006, (unsigned int)Events_ApplyFlag200RadialDamage,
        0x00000007, (unsigned int)Events_ApplyFlag200RadialKnockback, 0x00000007,
        (unsigned int)Events_ApplyFlag400RadialDamage, 0x00000006,
        (unsigned int)Events_ApplyFlag400RadialKnockback, 0x00000006, (unsigned int)Events_StartActorEmitter,
        0x00000000, (unsigned int)Events_IgnoreEvent, 0x00000000, ENCODED_CALLBACK_ADDRESS(Events_PlayTeamClip),
        0x00000000,
        (unsigned int)Events_SpawnFilteredActorEffect, 0x00000000, (unsigned int)Events_FireWithinHeightRange,
        0x00000007, (unsigned int)Events_SetActorEventBit, 0x00000000, (unsigned int)Events_ClearActorEventBit,
        0x00000000,
        (unsigned int)Events_SpawnAttachedEffect, 0x00000000, (unsigned int)Events_PlayTeamEffect, 0x00000000,
        (unsigned int)Events_StopClipEvent, 0x00000000, (unsigned int)Events_SetActorLoopingSound, 0x00000000,
        (unsigned int)Events_StopActorLoopingSound, 0x00000000, (unsigned int)Events_IncrementNearbyPlayerCounter,
        0x00000002, (unsigned int)Events_SpawnPositionedEffect, 0x00000000, (unsigned int)Events_SetActorEffectMode,
        0x00000000,
        (unsigned int)Events_DeactivateActor, 0x00000000, 0x3EDF9547, 0x3EDE6595, 0x00000000, 0x00000000, 0x00000000,
        0x00000000,
        0x00000000, 0x00071115, 0x15110700, 0x00000000, 0x00000003, 0x1529363E, 0x3E362815, 0x03000000,
        0x0000031C, 0x3550626E, 0x6E625038, 0x1C010000, 0x00001738, 0x5879919F, 0x9E927959, 0x36170000,
    },
    "5PbnnbP8",
    {
        0x1C010000, 0x00001738, 0x5879919F, 0x9E927959, 0x36170000, 0x00082850, 0x799FBDCE, 0xCEBE9F79,
        0x4E290800, 0x00113662, 0x91BEDFF2, 0xF2E0BD92, 0x62361000, 0x00173E6E, 0x9FCEF2FF, 0xFFF3CE9F,
        0x6D3E1500, 0x00173D6E, 0xA1CDF2FF, 0xFFF3CE9F, 0x6D401700, 0x00103662, 0x92BEDFF3, 0xF2E0BE92,
        0x62361100, 0x00072850, 0x799FBDCF, 0xCEBE9F78, 0x4E290700, 0x00001736, 0x597A92A1, 0x9F927958,
        0x36150000, 0x0000031C, 0x3650646E, 0x6E644E36, 0x1C010000, 0x00000003, 0x1528363E, 0x3D362815,
    },
    "6PdnndN6",
    {
        0x1C010000, 0x00000003, 0x1528363E, 0x3D362815, 0x03000000, 0x00000000, 0x00071015, 0x15110700,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    },
};
#endif

/* GEOMETRY_DRAWRESOURCEMODEL_DATA.CPP */

#if defined(VERSION_EU_X)
struct {
    u32 renderModesAndFlags[12];
    s32 fillEnabled;
    f32 fillRed;
    f32 fillGreen;
    f32 fillBlue;
    f32 fillAlpha;
    f32 fillTargetAlpha;
    u8 primitiveOverride[6];
    u8 alignmentFill[2]; /* Tail padding rounds the record up to its 4-byte alignment. */
} g_geometryDrawResourceModelWritableWords_eu_x __attribute__((aligned(4))) = {
    { 0xffffffff, 0xffffffff, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x10000, 0xc4000000, 0xc8000000 },
    0,
    255.0f,
    255.0f,
    255.0f,
    255.0f,
    255.0f,
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x0, 0x0 }
};
typedef char g_geometryDrawResourceModelWritableWords_eu_xSizeCheck[
    (sizeof(g_geometryDrawResourceModelWritableWords_eu_x) == 80) ? 1 : -1];

unsigned short k_geometryDrawresourcemodelFragment[8] = {
    0xA000, 0x0000, 0xA000, 0x0000, 0x00FF, 0x0000, 0x00FF, 0x0000,
};
#endif

/* K_PLAYERMODELWHITELIGHTDISPLAYLIST.CPP */

#if defined(VERSION_US)
struct {
    Light light;
    Gfx commands[6];
} k_playerModelWhiteLightDisplayList = {
    { { { 0xFF, 0xFF, 0xFF }, 0, { 0xFF, 0xFF, 0xFF }, 0, { 0, 0, 127 }, 0 } },
    {
    gsSPGeometryMode(0xFFFFFF, 0x00000000),
    gsSPGeometryMode(0x000000, 0x00000001),
    gsMoveWd(2, 0x0000, 0x00000018),
    gsDma2p(G_MOVEMEM, g_playerModelLighting[0].diffuse, 16, 10, 48),
    gsDma2p(G_MOVEMEM, g_playerModelLighting, 16, 10, 72),
    gsSPEndDisplayList(),
    }
};
#endif

/* ENEMY.CPP */
#if defined(VERSION_US_REV1)

/* A light (colour, colour copy, direction) read bytewise by the RSP, then the display list words that follow it. */
struct {
    unsigned char light[16];
    unsigned int list[12];
} g_enemyLightingDisplayListStorage = {
    { 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0xD9000000, 0x00000000, 0xD9FFFFFF, 0x00000001,
      0xDB020000, 0x00000018, 0xDC08060A, (unsigned int)&g_secondaryMenuByteOptions, 0xDC08090A, (unsigned int)&g_playerModelLighting, 0xDF000000, 0x00000000 },
};
#endif
#if defined(VERSION_US) || defined(VERSION_US_REV1)

Gfx g_enemyConstants[12] = {
    gsSPSetOtherMode(G_SETOTHERMODE_H, 20, 2, 0x00000000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 23, 1, 0x00000000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 16, 1, 0x00000000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 17, 2, 0x00000000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 19, 1, 0x00080000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 12, 2, 0x00002000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 9, 3, 0x00000C00),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 8, 1, 0x00000000),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 2, 0x00000000),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};
#endif
#if defined(VERSION_US_REV1)

Gfx g_enemyMipmapTextureLoadWrapDl[16] = {
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1372, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 256, 1, 0, 0, 4, 1, 0, 4, 1),
    gsDPSetTileSize(1, 0, 0, 60, 60),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 320, 2, 0, 0, 3, 2, 0, 3, 2),
    gsDPSetTileSize(2, 0, 0, 28, 28),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 336, 3, 0, 0, 2, 3, 0, 2, 3),
    gsDPSetTileSize(3, 0, 0, 12, 12),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 340, 4, 0, 0, 1, 4, 0, 1, 4),
    gsDPSetTileSize(4, 0, 0, 4, 4),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 342, 5, 0, 0, 0, 5, 0, 0, 5),
    gsDPSetTileSize(5, 0, 0, 0, 0),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPEndDisplayList(),
};
#endif
#if defined(VERSION_US_REV1)

Gfx g_enemyMipmapTextureLoadMirrorDl[16] = {
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1372, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, 1, 5, 0, 1, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 256, 1, 0, 1, 4, 1, 1, 4, 1),
    gsDPSetTileSize(1, 0, 0, 60, 60),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 320, 2, 0, 1, 3, 2, 1, 3, 2),
    gsDPSetTileSize(2, 0, 0, 28, 28),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 336, 3, 0, 1, 2, 3, 1, 2, 3),
    gsDPSetTileSize(3, 0, 0, 12, 12),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 340, 4, 0, 1, 1, 4, 1, 1, 4),
    gsDPSetTileSize(4, 0, 0, 4, 4),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 342, 5, 0, 1, 0, 5, 1, 0, 5),
    gsDPSetTileSize(5, 0, 0, 0, 0),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPEndDisplayList(),
};
#endif
#if defined(VERSION_US_REV1)

Gfx g_enemyRgbaMipmapDoubleScaleDisplayList[19] = {
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1372, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, 0, 5, 15, 0, 5, 15),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 1, 0, 0, 5, 0, 0, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 256, 2, 0, 0, 4, 1, 0, 4, 1),
    gsDPSetTileSize(2, 0, 0, 60, 60),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 320, 3, 0, 0, 3, 2, 0, 3, 2),
    gsDPSetTileSize(3, 0, 0, 28, 28),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 336, 4, 0, 0, 2, 3, 0, 2, 3),
    gsDPSetTileSize(4, 0, 0, 12, 12),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 340, 5, 0, 0, 1, 4, 0, 1, 4),
    gsDPSetTileSize(5, 0, 0, 4, 4),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 342, 6, 0, 0, 0, 5, 0, 0, 5),
    gsDPSetTileSize(6, 0, 0, 0, 0),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 17, 2, 0x00040000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPEndDisplayList(),
};
#endif
#if defined(VERSION_US_REV1)

Gfx g_enemyRgbaMipmapQuadScaleDisplayList[19] = {
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1372, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, 0, 5, 14, 0, 5, 14),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 1, 0, 0, 5, 0, 0, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 256, 2, 0, 0, 4, 1, 0, 4, 1),
    gsDPSetTileSize(2, 0, 0, 60, 60),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 320, 3, 0, 0, 3, 2, 0, 3, 2),
    gsDPSetTileSize(3, 0, 0, 28, 28),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 336, 4, 0, 0, 2, 3, 0, 2, 3),
    gsDPSetTileSize(4, 0, 0, 12, 12),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 340, 5, 0, 0, 1, 4, 0, 1, 4),
    gsDPSetTileSize(5, 0, 0, 4, 4),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 342, 6, 0, 0, 0, 5, 0, 0, 5),
    gsDPSetTileSize(6, 0, 0, 0, 0),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 17, 2, 0x00040000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPEndDisplayList(),
};
#endif
#if defined(VERSION_US_REV1)

Gfx g_textureFrameIntensityMipmapDisplayList[19] = {
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1408, 0),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 4, 0, 0, 0, 0, 6, 0, 0, 6, 0),
    gsDPSetTileSize(0, 0, 0, 252, 252),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 2, 256, 1, 0, 0, 5, 1, 0, 5, 1),
    gsDPSetTileSize(1, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 320, 2, 0, 0, 4, 2, 0, 4, 2),
    gsDPSetTileSize(2, 0, 0, 60, 60),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 336, 3, 0, 0, 3, 3, 0, 3, 3),
    gsDPSetTileSize(3, 0, 0, 28, 28),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 344, 4, 0, 0, 2, 4, 0, 2, 4),
    gsDPSetTileSize(4, 0, 0, 12, 12),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 348, 5, 0, 0, 1, 5, 0, 1, 5),
    gsDPSetTileSize(5, 0, 0, 4, 4),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 350, 6, 0, 0, 0, 6, 0, 0, 6),
    gsDPSetTileSize(6, 0, 0, 0, 0),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 17, 2, 0x00000000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPEndDisplayList(),
};
#endif

/* GEOMETRY_DRAWINTENSITYMASK_DATA.CPP */


#if defined(VERSION_US)
Gfx k_GeometryDrawintensitymaskEncodedWords[89] = {
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1372, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 256, 1, 0, 0, 4, 1, 0, 4, 1),
    gsDPSetTileSize(1, 0, 0, 60, 60),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 320, 2, 0, 0, 3, 2, 0, 3, 2),
    gsDPSetTileSize(2, 0, 0, 28, 28),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 336, 3, 0, 0, 2, 3, 0, 2, 3),
    gsDPSetTileSize(3, 0, 0, 12, 12),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 340, 4, 0, 0, 1, 4, 0, 1, 4),
    gsDPSetTileSize(4, 0, 0, 4, 4),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 342, 5, 0, 0, 0, 5, 0, 0, 5),
    gsDPSetTileSize(5, 0, 0, 0, 0),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPEndDisplayList(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1372, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, 1, 5, 0, 1, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 256, 1, 0, 1, 4, 1, 1, 4, 1),
    gsDPSetTileSize(1, 0, 0, 60, 60),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 320, 2, 0, 1, 3, 2, 1, 3, 2),
    gsDPSetTileSize(2, 0, 0, 28, 28),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 336, 3, 0, 1, 2, 3, 1, 2, 3),
    gsDPSetTileSize(3, 0, 0, 12, 12),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 340, 4, 0, 1, 1, 4, 1, 1, 4),
    gsDPSetTileSize(4, 0, 0, 4, 4),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 342, 5, 0, 1, 0, 5, 1, 0, 5),
    gsDPSetTileSize(5, 0, 0, 0, 0),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPEndDisplayList(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1372, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, 0, 5, 15, 0, 5, 15),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 1, 0, 0, 5, 0, 0, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 256, 2, 0, 0, 4, 1, 0, 4, 1),
    gsDPSetTileSize(2, 0, 0, 60, 60),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 320, 3, 0, 0, 3, 2, 0, 3, 2),
    gsDPSetTileSize(3, 0, 0, 28, 28),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 336, 4, 0, 0, 2, 3, 0, 2, 3),
    gsDPSetTileSize(4, 0, 0, 12, 12),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 340, 5, 0, 0, 1, 4, 0, 1, 4),
    gsDPSetTileSize(5, 0, 0, 4, 4),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 342, 6, 0, 0, 0, 5, 0, 0, 5),
    gsDPSetTileSize(6, 0, 0, 0, 0),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 17, 2, 0x00040000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPEndDisplayList(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1372, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, 0, 5, 14, 0, 5, 14),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 1, 0, 0, 5, 0, 0, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 256, 2, 0, 0, 4, 1, 0, 4, 1),
    gsDPSetTileSize(2, 0, 0, 60, 60),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 320, 3, 0, 0, 3, 2, 0, 3, 2),
    gsDPSetTileSize(3, 0, 0, 28, 28),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 336, 4, 0, 0, 2, 3, 0, 2, 3),
    gsDPSetTileSize(4, 0, 0, 12, 12),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 340, 5, 0, 0, 1, 4, 0, 1, 4),
    gsDPSetTileSize(5, 0, 0, 4, 4),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 342, 6, 0, 0, 0, 5, 0, 0, 5),
    gsDPSetTileSize(6, 0, 0, 0, 0),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 17, 2, 0x00040000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPEndDisplayList(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1408, 0),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 4, 0, 0, 0, 0, 6, 0, 0, 6, 0),
    gsDPSetTileSize(0, 0, 0, 252, 252),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 2, 256, 1, 0, 0, 5, 1, 0, 5, 1),
    gsDPSetTileSize(1, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 320, 2, 0, 0, 4, 2, 0, 4, 2),
    gsDPSetTileSize(2, 0, 0, 60, 60),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 336, 3, 0, 0, 3, 3, 0, 3, 3),
    gsDPSetTileSize(3, 0, 0, 28, 28),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 344, 4, 0, 0, 2, 4, 0, 2, 4),
    gsDPSetTileSize(4, 0, 0, 12, 12),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 348, 5, 0, 0, 1, 5, 0, 1, 5),
    gsDPSetTileSize(5, 0, 0, 4, 4),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 350, 6, 0, 0, 0, 6, 0, 0, 6),
    gsDPSetTileSize(6, 0, 0, 0, 0),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 17, 2, 0x00000000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPEndDisplayList(),
};
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
#if defined(VERSION_US)
/* Display-list commands are logical 32-bit words on every host. */
Gfx g_geometryDrawIntensityMaskDisplayList[17] = {
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPTexture(0x8000, 0x8000, 0, 0, 1),
    gsSPGeometryMode(0x060400, 0x00000000),
    gsSPGeometryMode(0x000000, 0x00210004),
    gsDPSetCombineLERP(0, 0, 0, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 3, 29, 0xC8104B50),
    gsMoveWd(4, 0x0004, 0x00000001),
    gsMoveWd(4, 0x000C, 0x00000001),
    gsMoveWd(4, 0x0014, 0x0000FFFF),
    gsMoveWd(4, 0x001C, 0x0000FFFF),
    gsSPVertex(g_particleQuadVertices, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsMoveWd(4, 0x0004, 0x00000005),
    gsMoveWd(4, 0x000C, 0x00000005),
    gsMoveWd(4, 0x0014, 0x0000FFFB),
    gsMoveWd(4, 0x001C, 0x0000FFFB),
    gsSPEndDisplayList(),
};
#endif
#if defined(VERSION_US_REV1)
/* Display-list commands are logical 32-bit words on every host. */
Gfx g_geometryDrawIntensityMaskDisplayList[17] = {
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPTexture(0x8000, 0x8000, 0, 0, 1),
    gsSPGeometryMode(0x060400, 0x00000000),
    gsSPGeometryMode(0x000000, 0x00210004),
    gsDPSetCombineLERP(0, 0, 0, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 3, 29, 0xC8104B50),
    gsMoveWd(4, 0x0004, 0x00000001),
    gsMoveWd(4, 0x000C, 0x00000001),
    gsMoveWd(4, 0x0014, 0x0000FFFF),
    gsMoveWd(4, 0x001C, 0x0000FFFF),
    gsSPVertex(g_particleQuadVertices, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsMoveWd(4, 0x0004, 0x00000005),
    gsMoveWd(4, 0x000C, 0x00000005),
    gsMoveWd(4, 0x0014, 0x0000FFFB),
    gsMoveWd(4, 0x001C, 0x0000FFFB),
    gsSPEndDisplayList(),
};
#endif
#endif

/* EVENTS_DELIVERCONTACTEFFECT_DATA.CPP */

#if defined(VERSION_US)
/* Geometry_DrawResourceModel's second-pass material display list. */
Gfx g_geometryAlternateMaterialDisplayList[17] = {
    {{ 0xE3001001, 0x00000000 }},
    {{ 0xD7FF0002, 0x80008000 }},
    {{ 0xD9F9FBFF, 0x00000000 }},
    {{ 0xD9FFFFFF, 0x00210004 }},
    {{ 0xFCFF97FF, 0xFFFFFE38 }},
    {{ 0xE200001C, 0xC8104E50 }},
    {{ 0xDB040004, 0x00000001 }},
    {{ 0xDB04000C, 0x00000001 }},
    {{ 0xDB040014, 0x0000FFFF }},
    {{ 0xDB04001C, 0x0000FFFF }},
    {{ 0x01004008, 0x801408E0 }},
    {{ 0x06000204, 0x00040600 }},
    {{ 0xDB040004, 0x00000005 }},
    {{ 0xDB04000C, 0x00000005 }},
    {{ 0xDB040014, 0x0000FFFB }},
    {{ 0xDB04001C, 0x0000FFFB }},
    {{ 0xDF000000, 0x00000000 }},
};
#endif

#if defined(VERSION_US_REV1)
/* Geometry_DrawResourceModel's second-pass material display list. */
Gfx g_geometryAlternateMaterialDisplayList[17] = {
    {{ 0xE3001001, 0 }},
    {{ 0xD7FF0002, 0x80008000 }},
    {{ 0xD9F9FBFF, 0 }},
    {{ 0xD9FFFFFF, 2162692 }},
    {{ 0xFCFF97FF, -456 }},
    {{ 0xE200001C, 0xC8104E50 }},
    {{ 0xDB040004, 1 }},
    {{ 0xDB04000C, 1 }},
    {{ 0xDB040014, 65535 }},
    {{ 0xDB04001C, 65535 }},
    {{ 0x01004008, (unsigned int)g_particleQuadVertices }},
    {{ 0x06000204, 263680 }},
    {{ 0xDB040004, 5 }},
    {{ 0xDB04000C, 5 }},
    {{ 0xDB040014, 65531 }},
    {{ 0xDB04001C, 65531 }},
    {{ 0xDF000000, 0 }},
};

RestBytes8 g_contactEffectStaleFloatPairAboveHalf = {
    { 63, 22, 156, 251, 63, 22, 41, 101 },
};

ContactEffectEntry g_effectCallbackFlags[37] = { { (ContactEffectHandler)&addrLow_Events_PlayClipEvent, 0 }, { (ContactEffectHandler)&addrLow_Events_SpawnActorEffect,
             0 }, { (ContactEffectHandler)&addrLow_Events_ApplyDirectDamage_us_rev1, 4 }, { (ContactEffectHandler)&addrLow_Events_ApplyRadialDamage,
             6 }, { (ContactEffectHandler)&addrLow_Events_ApplyRadialDamageWithKnockback_us_rev1, 6 }, { (ContactEffectHandler)&addrLow_Events_PreserveEventArgument,
             10 }, { (ContactEffectHandler)&addrLow_Events_RunFirstNodeOperation, 16 }, { (ContactEffectHandler)&addrLow_Events_RunSecondNodeOperation_us_rev1,
             16 }, { (ContactEffectHandler)&addrLow_Events_SpawnActorEffect, 0 }, { (ContactEffectHandler)&addrLow_Events_StartCameraFadeAtPoint,
             0 }, { (ContactEffectHandler)&addrLow_Events_ConsumeEventArgument, 0 }, { (ContactEffectHandler)&addrLow_Events_RequestActorPosition,
             0 }, { (ContactEffectHandler)&addrLow_Events_StartEnabledCameraEmitter, 0 }, { (ContactEffectHandler)&addrLow_Events_StartDisabledCameraEmitter,
             0 }, { (ContactEffectHandler)&addrLow_Events_PostGameplayMessage, 0 }, { (ContactEffectHandler)&addrLow_Events_ApplyFlag100RadialDamage,
             6 }, { (ContactEffectHandler)&addrLow_Events_ApplyFlag100RadialKnockback, 6 }, { (ContactEffectHandler)&addrLow_Events_ApplyFlag200RadialDamage,
             7 }, { (ContactEffectHandler)&addrLow_Events_ApplyFlag200RadialKnockback, 7 }, { (ContactEffectHandler)&addrLow_Events_ApplyFlag400RadialDamage,
             6 }, { (ContactEffectHandler)&addrLow_Events_ApplyFlag400RadialKnockback, 6 }, { (ContactEffectHandler)&addrLow_Events_StartActorEmitter,
             0 }, { (ContactEffectHandler)&addrLow_Events_IgnoreEvent, 0 }, { (ContactEffectHandler)&addrLow_Events_PlayTeamClip,
             0 }, { (ContactEffectHandler)&addrLow_Events_SpawnFilteredActorEffect, 0 }, { (ContactEffectHandler)&addrLow_Events_FireWithinHeightRange,
             7 }, { (ContactEffectHandler)&addrLow_Events_SetActorEventBit, 0 }, { (ContactEffectHandler)&addrLow_Events_ClearActorEventBit,
             0 }, { (ContactEffectHandler)&addrLow_Events_SpawnAttachedEffect, 0 }, { (ContactEffectHandler)&addrLow_Events_PlayTeamEffect,
             0 }, { (ContactEffectHandler)&addrLow_Events_StopClipEvent, 0 }, { (ContactEffectHandler)&addrLow_Events_SetActorLoopingSound_us_rev1,
             0 }, { (ContactEffectHandler)&addrLow_Events_StopActorLoopingSound, 0 }, { (ContactEffectHandler)&addrLow_Events_IncrementNearbyPlayerCounter,
             2 }, { (ContactEffectHandler)&addrLow_Events_SpawnPositionedEffect, 0 }, { (ContactEffectHandler)&addrLow_Events_SetActorEffectMode,
             0 }, { (ContactEffectHandler)&addrLow_Events_DeactivateActor, 0 } };

RestBytes8 g_contactEffectStaleFloatPairBelowHalf = {
    { 62, 223, 149, 71, 62, 222, 101, 149 },
};
#endif

/* S_HAMMERTEXT.CPP */

#if defined(VERSION_US)
struct {
    char text0[8];
    unsigned int words1[76];
} s_hammerText = {
    "_HAMMER_",
    {
        (unsigned int)g_Events_PlayClipEventPackedCallbackUs, 0x00000000,
        ENCODED_CALLBACK_ADDRESS(Events_SpawnActorEffect), 0x00000000,
        (unsigned int)g_Events_ApplyDirectDamagePackedCallbackUs, 0x00000004,
        (unsigned int)g_Events_ApplyRadialDamagePackedCallbackUs, 0x00000006,
        (unsigned int)g_Events_ApplyRadialDamageWithKnockbackPackedCallbackUs, 0x00000006,
        (unsigned int)g_Events_PreserveEventArgumentPackedCallbackUs, 0x0000000A,
        (unsigned int)g_Events_RunActorNodeOperationPackedCallbackUs, 0x00000010,
        ENCODED_CALLBACK_ADDRESS(Events_RunSecondNodeOperation), 0x00000010,
        ENCODED_CALLBACK_ADDRESS(Events_SpawnActorEffect), 0x00000000,
        ENCODED_CALLBACK_ADDRESS(Events_StartCameraFadeAtPoint), 0x00000000,
        (unsigned int)g_Events_ConsumeEventArgumentPackedCallbackUs, 0x00000000,
        (unsigned int)g_Events_RequestActorPositionPackedCallbackUs, 0x00000000,
        (unsigned int)g_Events_StartEnabledCameraEmitterPackedCallbackUs, 0x00000000,
        (unsigned int)g_Events_StartDisabledCameraEmitterPackedCallbackUs, 0x00000000,
        (unsigned int)g_Events_PostGameplayMessagePackedCallbackUs, 0x00000000,
        (unsigned int)g_Events_ApplyLowFlagRadialDamagePackedCallbackUs, 0x00000006,
        (unsigned int)g_Events_ApplyLowFlagRadialKnockbackPackedCallbackUs, 0x00000006,
        (unsigned int)g_Events_ApplyMidFlagRadialDamagePackedCallbackUs, 0x00000007,
        (unsigned int)g_Events_ApplyMidFlagRadialKnockbackPackedCallbackUs, 0x00000007,
        (unsigned int)g_Events_ApplyHighFlagRadialDamagePackedCallbackUs, 0x00000006,
        (unsigned int)g_Events_ApplyHighFlagRadialKnockbackPackedCallbackUs, 0x00000006,
        (unsigned int)g_Events_StartActorEmitterPackedCallbackUs, 0x00000000,
        (unsigned int)g_Events_IgnoreEventEncodedCallback, 0x00000000,
        ENCODED_CALLBACK_ADDRESS(Events_PlayTeamClip), 0x00000000,
        (unsigned int)g_Events_SpawnFilteredActorEffectPackedCallbackUs, 0x00000000,
        (unsigned int)g_Events_FireWithinHeightRangePackedCallbackUs, 0x00000007,
        ENCODED_CALLBACK_ADDRESS(Events_SetActorEventBit), 0x00000000,
        (unsigned int)g_Events_ClearActorEventBitPackedCallbackUs, 0x00000000,
        (unsigned int)g_Events_SpawnAttachedEffectPackedCallbackUs, 0x00000000,
        (unsigned int)g_Events_PlayTeamEffectEncodedCallback, 0x00000000,
        (unsigned int)g_Events_StopClipEventPackedCallbackUs, 0x00000000,
        (unsigned int)g_Events_SetActorLoopingSoundEncodedCallback, 0x00000000,
        (unsigned int)g_Events_StopActorLoopingSoundEncodedCallback, 0x00000000,
        (unsigned int)addrLow_Events_SetActorLoopingSound_us_rev1, 0x00000002,
        (unsigned int)g_Events_SpawnPositionedEffectEncodedCallback, 0x00000000,
        (unsigned int)g_Events_SetActorEffectModeEncodedCallback, 0x00000000,
        (unsigned int)g_Events_DeactivateActorEncodedCallback, 0x00000000, 0x75042E65, 0x6F735200,
    },
};
#endif

/* GEOMETRY_DRAWINTENSITYMASK_DATA.CPP */

#if defined(VERSION_US) || defined(VERSION_US_REV1)
unsigned char g_materialIntensityMaskTexture[256] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x07, 0x11, 0x15, 0x15, 0x11, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x03, 0x15, 0x29, 0x36, 0x3E, 0x3E, 0x36, 0x28, 0x15, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
    0x1C, 0x35, 0x50, 0x62, 0x6E, 0x6E, 0x62, 0x50, 0x38, 0x1C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x17, 0x38,
    0x58, 0x79, 0x91, 0x9F, 0x9E, 0x92, 0x79, 0x59, 0x36, 0x17, 0x00, 0x00, 0x00, 0x08, 0x28, 0x50, 0x79,
    0x9F, 0xBD, 0xCE, 0xCE, 0xBE, 0x9F, 0x79, 0x4E, 0x29, 0x08, 0x00, 0x00, 0x11, 0x36, 0x62, 0x91, 0xBE,
    0xDF, 0xF2, 0xF2, 0xE0, 0xBD, 0x92, 0x62, 0x36, 0x10, 0x00, 0x00, 0x17, 0x3E, 0x6E, 0x9F, 0xCE, 0xF2,
    0xFF, 0xFF, 0xF3, 0xCE, 0x9F, 0x6D, 0x3E, 0x15, 0x00, 0x00, 0x17, 0x3D, 0x6E, 0xA1, 0xCD, 0xF2, 0xFF,
    0xFF, 0xF3, 0xCE, 0x9F, 0x6D, 0x40, 0x17, 0x00, 0x00, 0x10, 0x36, 0x62, 0x92, 0xBE, 0xDF, 0xF3, 0xF2,
    0xE0, 0xBE, 0x92, 0x62, 0x36, 0x11, 0x00, 0x00, 0x07, 0x28, 0x50, 0x79, 0x9F, 0xBD, 0xCF, 0xCE, 0xBE,
    0x9F, 0x78, 0x4E, 0x29, 0x07, 0x00, 0x00, 0x00, 0x17, 0x36, 0x59, 0x7A, 0x92, 0xA1, 0x9F, 0x92, 0x79,
    0x58, 0x36, 0x15, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1C, 0x36, 0x50, 0x64, 0x6E, 0x6E, 0x64, 0x4E, 0x36,
    0x1C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x15, 0x28, 0x36, 0x3E, 0x3D, 0x36, 0x28, 0x15, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x10, 0x15, 0x15, 0x11, 0x07, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00,
};
#endif

/* XPLUS_NEXTRANDOMINTEGER_DATA.CPP */
#if defined(VERSION_US)
u32 g_geometryPreviousModePreset = 0xFFFFFFFF;
int g_geometryPreviousCombineMode = -1;
EngineGeometryState g_geometryPreviousModePresetBlock = {
    1, 1, 1, 1, 1, 1, 1, 0x00010000, 0xC4000000, 0xC8000000, 0,
    { 255.0f, 255.0f, 255.0f, 255.0f, 255.0f },
    { 0, 0, 0, 0 }, 0, 0, { 0, 0 }
};
#endif

/* S_ROBERTSOTEXT.CPP */
#if defined(VERSION_US)

unsigned int g_robertsoTextColorMasks[4] = {
    0xA0000000, 0xA0000000, 0x00FF0000, 0x00FF0000,
};
#endif

/* X_PLUS_DATA.CPP */
#if defined(VERSION_US_REV1)
u32 g_geometryPreviousModePreset = 0xFFFFFFFF;
int g_geometryPreviousCombineMode = -1;
EngineGeometryState g_geometryPreviousModePresetBlock = {
    1, 1, 1, 1, 1, 1, 1, 0x00010000, 0xC4000000, 0xC8000000, 0,
    { 255.0f, 255.0f, 255.0f, 255.0f, 255.0f },
    { 0, 0, 0, 0 }, 0, 0, { 0, 0 }
};
MaterialPlusModeConstantsUsRev1Layout g_xPlusData = {
    { 0xA0000000, 0xA0000000, 16711680, 16711680 }
};
#endif
