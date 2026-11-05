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

char g_fxAssertFreeVertsNonNegative[24] = "pThis->m_VtxsFree >= 0";

char g_fxAssertSwooshNodeSet[40] = "pSwoosh->m_pROMSwoosh->m_nNode != -1";

float g_fxSwooshNodeConstants[3] = { 1.52587887e-07f, 0.00999999978f, 29.257143f };

char g_fxAssertParticleType[40] = "pParticle->ah.ih.m_Type == I_PARTICLE";

char g_fxAssertParticleNotNull[12] = "pParticle";

char g_fxAssertRomHotPointNotNull[16] = "pROMHotPoint";

char g_fxAssertRomEndHotPointNotNull[16] = "pROMEndHotPoint";

char g_fxAssertSeveralCamerasActive[40] = "GetCameraPool()->m_ActiveList.Size > 1";

char g_fxAssertDisplayListGrows[28] = "pThis->m_pDList < pDList";

float g_fxDisplayListColorScale[3] = { 255.0f, 1.0f, 1.0f };
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

char g_fxAssertFreeVertsNonNegative[24] = "pThis->m_VtxsFree >= 0";

char g_fxAssertSwooshNodeSet[40] = "pSwoosh->m_pROMSwoosh->m_nNode != -1";

float g_fxSwooshNodeConstants[3] = { 1.52587887e-07f, 0.00999999978f, 29.257143f };

char g_fxAssertParticleType[40] = "pParticle->ah.ih.m_Type == I_PARTICLE";

char g_fxAssertParticleNotNull[12] = "pParticle";

char g_fxAssertRomHotPointNotNull[16] = "pROMHotPoint";

char g_fxAssertRomEndHotPointNotNull[16] = "pROMEndHotPoint";

char g_fxAssertSeveralCamerasActive[40] = "GetCameraPool()->m_ActiveList.Size > 1";

char g_fxAssertDisplayListGrows[28] = "pThis->m_pDList < pDList";

float g_fxDisplayListColorScale[3] = { 255.0f, 1.0f, 1.0f };
#endif
