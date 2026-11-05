#if defined(VERSION_EU)

#include "data_overlay_layouts.h"


#include "Ai/weaponai.h"


#include "Fx/retained_screen_message_owners.h"


#include "Frontend/controllerpak_message_pool.h"


#include "Fx/eu_screen_message_setup.h"


#include "Fx/us_screen_message_data.h"


#include "Common/Lone/weapon_locked_notice_text.h"


#include "Texture/archive_image_records.h"


#include "Engine/graphics_math.h"


#include "Common/shared_particleinstance.h"


#include "Common/game_session.h"


#include "Common/world.h"


#include "include_asm.h"


#include "Common/effectcontribution.h"


#include "Render/animation_frame_and_ribbon_views.h"


#include "types.h"


#include "Common/runtime_declarations.h"


#include "System/textload_resettexturecache.h"


#include <PR/gbi.h>


#include <platform_sdk.h>


#include "Render/ribbon_draw.h"


#include "Common/self.h"


#include "Common/weapon_marker_and_profile_views.h"


#include "Common/sessionhandlerrow.h"


#include "Common/triple.h"


#include "fx.h"


#include "Engine/lists.h"


#include "Engine/scene_drawopaqueactors.h"


#include "Fx/fx_drawcoloredribbon.h"


#include "Game/builddirectionmatrix.h"


#include "Graphu64/graphu64_packfixedmatrix.h"


#include "Particle/particle_haskindzeroentry.h"


#include "Render/linked_drawtexturedribbon.h"


#include "Textload/textload_locatetextureresource.h"


#include "Particle/graphu64_matrixfromeulerxyz.h"


#include "Rsp/random_direction_and_affine_math.h"


#include <PR/abi.h>


#include "Common/vector4f.h"


#include "Common/sharedplayer.h"


#include "Common/heap_arena_entry.h"


#include "Common/geometry_blend_and_instance_views.h"


#include "Common/frustum.h"


#include "Common/hud_effects.h"


#include "Engine/Cache/list.h"


#include "Fx/fx_drawboundedparticlequads.h"


#include "Fx/fx_spawnimpactmark.h"


#include "Graphu64/graphu64_getangledistance.h"


#include "Fx/fx_address_symbols.h"


#include "Render/material_color_and_fog_views.h"


#include "Common/ballisticparams.h"


#include "Common/trigger_and_float_value_operations.h"


#include "System/timed_effect_and_item_menu_views.h"


#include "Fx/normalize_vector.h"


#include "Common/weapon_screen_message_operations.h"


#include "Common/packed_callback.h"


#include "Data/rest_source_records.h"


#include "Data/Gfxdata/audio_decodeframe_data.h"


#include "Gfxdata/audio_decodeframe_data.h"


#include "Fx/sky_postscaledscreenmessage_data.h"


#include "types.h"


#include "Menu/g_menuplayerscissorrects.h"


typedef struct FillFade {
    f32 alpha;
    f32 target;
} FillFade;

char g_fxSourcePath[36] = "C:/Projects/DM/n64/Source/fx.cpp";

char g_fxAssertThisNotNull[8] = "pThis";

char g_fxAssertInfoNotNull[8] = "pInfo";

char g_fxAssertInfoPointsNotNull[16] = "pInfo->pPoints";

char g_fxAssertInfoPointCountNonZero[16] = "pInfo->nPoints";

char g_fxAssertInfoStartHotPointsNotNull[24] = "pInfo->StartHotPoints";

char g_fxAssertInfoEndHotPointsNotNull[20] = "pInfo->EndHotPoints";

float g_fxSwooshHotPointConstants[7] = { 32.0f, 100.0f, 32.0f, 100.0f, 32.0f, 1.0f, 1.0f };

char g_fxAssertStartHotPointNotNull[16] = "pStartHotPoint";

char g_fxAssertStartHotPointOnSwooshNode[56] = "pStartHotPoint->m_nNode == pThis->m_pROMSwoosh->m_nNode";

char g_fxAssertEndHotPointNotNull[16] = "pEndHotPoint";

char g_fxAssertEndHotPointOnSwooshNode[56] = "pEndHotPoint->m_nNode == pThis->m_pROMSwoosh->m_nNode";

float g_fxSwooshEdgeConstants[28] = { 3.14159274f, 2.0f, 0.5f, 3.14159274f, 2.0f, 0.5f, 1.0f, 2.14748365e+09f, 2.14748365e+09f, 2.14748365e+09f, 2.14748365e+09f, 2.14748365e+09f, 2.14748365e+09f, 3.14159274f, 2.0f, 0.5f, 3.14159274f, 2.0f, 0.5f, 1.0f, 2.14748365e+09f, 2.14748365e+09f, 2.14748365e+09f, 2.14748365e+09f, 2.14748365e+09f, 2.14748365e+09f, 1.0f, -3.0f };

char g_fxAssertEdgeANotNull[8] = "EdgeA";

char g_fxAssertEdgeBNotNull[8] = "EdgeB";

char g_fxAssertCameraNotNull[8] = "pCamera";

char g_fxAssertEdgesApart[68] = "!CVector3__IsEqual(&EdgeA->m_vTranslation, &EdgeB->m_vTranslation)";

float g_fxEdgeSideSigns[3] = { 1.0f, -1.0f, -1.0f };

char g_fxAssertPrevEdgeNotNull[12] = "pPrevEdge";

char g_fxAssertEdgeNotNull[8] = "pEdge";

float g_fxSwooshStretchConstants[2] = { 0.00999999978f, 29.257143f };

char g_fxAssertSwooshTextureStretched[68] = "pSwoosh->m_pROMSwoosh->m_TextureType == SWOOSH_TEXTURE_TYPE_STRETCH";

char g_fxAssertRomSwooshNotNull[12] = "pROMSwoosh";

char g_fxAssertSwooshTextureSetValid[28] = "pSwoosh->m_nTextureSet >= 0";

char g_fxAssertSwooshHasEdgePair[40] = "CSwoosh__EdgeListLength(pSwoosh) >= 2";

char g_fxAssertUnreachable[8] = "FALSE";

char g_fxAssertEdge1NotNull[8] = "pEdge1";

char g_fxAssertEdge2NotNull[8] = "pEdge2";

char g_fxAssertMeTextureNotNull[12] = "pmeTexture";

float g_fxTextureUnitScale[1] = { 1.0f };
#endif

#if defined(VERSION_EU_X)

#include "data_overlay_layouts.h"


#include "Ai/weaponai.h"


#include "Fx/retained_screen_message_owners.h"


#include "Frontend/controllerpak_message_pool.h"


#include "Fx/eu_screen_message_setup.h"


#include "Fx/us_screen_message_data.h"


#include "Common/Lone/weapon_locked_notice_text.h"


#include "Texture/archive_image_records.h"


#include "Engine/graphics_math.h"


#include "Common/shared_particleinstance.h"


#include "Common/game_session.h"


#include "Common/world.h"


#include "include_asm.h"


#include "Common/effectcontribution.h"


#include "Render/animation_frame_and_ribbon_views.h"


#include "types.h"


#include "Common/runtime_declarations.h"


#include "System/textload_resettexturecache.h"


#include <PR/gbi.h>


#include <platform_sdk.h>


#include "Render/ribbon_draw.h"


#include "Common/self.h"


#include "Common/weapon_marker_and_profile_views.h"


#include "Common/sessionhandlerrow.h"


#include "Common/triple.h"


#include "fx.h"


#include "Engine/lists.h"


#include "Engine/scene_drawopaqueactors.h"


#include "Fx/fx_drawcoloredribbon.h"


#include "Game/builddirectionmatrix.h"


#include "Graphu64/graphu64_packfixedmatrix.h"


#include "Particle/particle_haskindzeroentry.h"


#include "Render/linked_drawtexturedribbon.h"


#include "Textload/textload_locatetextureresource.h"


#include "Particle/graphu64_matrixfromeulerxyz.h"


#include "Rsp/random_direction_and_affine_math.h"


#include <PR/abi.h>


#include "Common/vector4f.h"


#include "Common/sharedplayer.h"


#include "Common/heap_arena_entry.h"


#include "Common/geometry_blend_and_instance_views.h"


#include "Common/frustum.h"


#include "Common/hud_effects.h"


#include "Engine/Cache/list.h"


#include "Fx/fx_drawboundedparticlequads.h"


#include "Fx/fx_spawnimpactmark.h"


#include "Graphu64/graphu64_getangledistance.h"


#include "Fx/fx_address_symbols.h"


#include "Render/material_color_and_fog_views.h"


#include "Common/ballisticparams.h"


#include "Common/trigger_and_float_value_operations.h"


#include "System/timed_effect_and_item_menu_views.h"


#include "Fx/normalize_vector.h"


#include "Common/weapon_screen_message_operations.h"


#include "Common/packed_callback.h"


#include "Data/rest_source_records.h"


#include "Data/Gfxdata/audio_decodeframe_data.h"


#include "Gfxdata/audio_decodeframe_data.h"


#include "Fx/sky_postscaledscreenmessage_data.h"


#include "types.h"


#include "Menu/g_menuplayerscissorrects.h"


typedef struct FillFade {
    f32 alpha;
    f32 target;
} FillFade;

char g_fxSourcePath[36] = "C:/Projects/DM/n64/Source/fx.cpp";

char g_fxAssertThisNotNull[8] = "pThis";

char g_fxAssertInfoNotNull[8] = "pInfo";

char g_fxAssertInfoPointsNotNull[16] = "pInfo->pPoints";

char g_fxAssertInfoPointCountNonZero[16] = "pInfo->nPoints";

char g_fxAssertInfoStartHotPointsNotNull[24] = "pInfo->StartHotPoints";

char g_fxAssertInfoEndHotPointsNotNull[20] = "pInfo->EndHotPoints";

float g_fxSwooshHotPointConstants[7] = { 32.0f, 100.0f, 32.0f, 100.0f, 32.0f, 1.0f, 1.0f };

char g_fxAssertStartHotPointNotNull[16] = "pStartHotPoint";

char g_fxAssertStartHotPointOnSwooshNode[56] = "pStartHotPoint->m_nNode == pThis->m_pROMSwoosh->m_nNode";

char g_fxAssertEndHotPointNotNull[16] = "pEndHotPoint";

char g_fxAssertEndHotPointOnSwooshNode[56] = "pEndHotPoint->m_nNode == pThis->m_pROMSwoosh->m_nNode";

float g_fxSwooshEdgeConstants[28] = { 3.14159274f, 2.0f, 0.5f, 3.14159274f, 2.0f, 0.5f, 1.0f, 2.14748365e+09f, 2.14748365e+09f, 2.14748365e+09f, 2.14748365e+09f, 2.14748365e+09f, 2.14748365e+09f, 3.14159274f, 2.0f, 0.5f, 3.14159274f, 2.0f, 0.5f, 1.0f, 2.14748365e+09f, 2.14748365e+09f, 2.14748365e+09f, 2.14748365e+09f, 2.14748365e+09f, 2.14748365e+09f, 1.0f, -3.0f };

char g_fxAssertEdgeANotNull[8] = "EdgeA";

char g_fxAssertEdgeBNotNull[8] = "EdgeB";

char g_fxAssertCameraNotNull[8] = "pCamera";

char g_fxAssertEdgesApart[68] = "!CVector3__IsEqual(&EdgeA->m_vTranslation, &EdgeB->m_vTranslation)";

float g_fxEdgeSideSigns[3] = { 1.0f, -1.0f, -1.0f };

char g_fxAssertPrevEdgeNotNull[12] = "pPrevEdge";

char g_fxAssertEdgeNotNull[8] = "pEdge";

float g_fxSwooshStretchConstants[2] = { 0.00999999978f, 29.257143f };

char g_fxAssertSwooshTextureStretched[68] = "pSwoosh->m_pROMSwoosh->m_TextureType == SWOOSH_TEXTURE_TYPE_STRETCH";

char g_fxAssertRomSwooshNotNull[12] = "pROMSwoosh";

char g_fxAssertSwooshTextureSetValid[28] = "pSwoosh->m_nTextureSet >= 0";

char g_fxAssertSwooshHasEdgePair[40] = "CSwoosh__EdgeListLength(pSwoosh) >= 2";

char g_fxAssertUnreachable[8] = "FALSE";

char g_fxAssertEdge1NotNull[8] = "pEdge1";

char g_fxAssertEdge2NotNull[8] = "pEdge2";

char g_fxAssertMeTextureNotNull[12] = "pmeTexture";

float g_fxTextureUnitScale[1] = { 1.0f };
#endif
