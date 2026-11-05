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

struct ParticleQuadRenderSetup {
    unsigned int words0[70];
    char text1[8];
} g_particleQuadRenderSetup = {
    {
        0xE3001001, 0x00000000, 0xD7000002, 0x80008000, 0xD9F9FBFF, 0x00000000, 0xD9FFFFFF, 0x00210004,
        0xFCFF97FF, 0xFFFFFE38, 0xE200001C, 0xC8104B50, 0xDB040004, 0x00000001, 0xDB04000C, 0x00000001,
        0xDB040014, 0x0000FFFF, 0xDB04001C, 0x0000FFFF, 0x01004008, (unsigned int)g_particleQuadVertices, 0xDF000000, 0x00000000,
        0xE3001001, 0x00000000, 0xD7FF0002, 0x80008000, 0xD9F9FBFF, 0x00000000, 0xD9FFFFFF, 0x00210004,
        0xFCFF97FF, 0xFFFFFE38, 0xE200001C, 0xC8104E50, 0xDB040004, 0x00000001, 0xDB04000C, 0x00000001,
        0xDB040014, 0x0000FFFF, 0xDB04001C, 0x0000FFFF, 0xDF000000, 0x00000000, 0xE3001001, 0x00000000,
        0xD7000002, 0x80008000, 0xD9F9FBFF, 0x00000000, 0xD9FFFFFF, 0x00210004, 0xFCFF97FF, 0xFFFDFE38,
        0xE200001C, 0xC8104B50, 0xDB040004, 0x00000001, 0xDB04000C, 0x00000001, 0xDB040014, 0x0000FFFF,
        0xDB04001C, 0x0000FFFF, 0x01004008, (unsigned int)g_particleQuadVertices, 0xDF000000, 0x00000000, 0x454E5420, 0x4F4E2054,
    },
    "ENT ON T",
};
#endif
