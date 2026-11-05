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

unsigned int g_fxDisplayListSwitchCases[9] = { 0x32242C, 0x322444, 0x322474, 0x3224D8, 0x322510, 0x322580, 0x322630, 0x322748, 0x322774 };
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

unsigned int g_fxDisplayListSwitchCases[9] = { 0x32242C, 0x322444, 0x322474, 0x3224D8, 0x322510, 0x322580, 0x322630, 0x322748, 0x322774 };
#endif
