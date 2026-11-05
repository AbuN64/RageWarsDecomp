#if defined(VERSION_US)

#include "include_asm.h"


#include "Common/screen.h"


#include "Common/selectionscreenstate.h"


#include "Common/label.h"


#include "Render/soundelement_playflatsound.h"


#include "types.h"


#include "Common/menu_screen_elements.h"


#include "Common/shared_menureply.h"


#include "Common/menu_screen_setup.h"


#include "Common/runtime_declarations.h"


#include "Common/sharedplayer.h"


#include "Ui/Tsmos/Screens/scenariosetupscreen.h"


#include "Frontend/smp_overlay.h"


#include "Render/material_color_and_fog_views.h"


#include "Common/menu_options_and_results.h"


#include "Common/gameplay_settings.h"


#include "Rsp/random_direction_and_affine_math.h"


#include "Common/level_goal.h"


#include "Common/active.h"


#include "Common/shared_gameslot.h"


#include "Frontend/stage_placestageopponents.h"


#include "System/sound_context_music_and_voice_control.h"


#include "Achieve/achieve.h"


#include "Frontend/screen.h"


#include "Ui/Tsmos/TSMOS.h"


#include "Ui/X_files/x_plus.h"


#include "Random/random_setuprandomteams.h"


#include "Common/stagepreset.h"


#include "Common/playerprofiles.h"


#include "LIBC.H"


#include "Camera/camera_address_symbols.h"


#include "Common/Lone/hud_reference_viewport_height.h"


#include "Common/osviscale.h"


#include "Common/frontend_video_mode.h"


#include "Common/widget_tree.h"


#include "Frontend/frontend_updateslidergeometry.h"


#include "menu.h"


#include "Frontend/frontend_returnwithoutaction.h"


#include "Common/player_join_requests.h"


#include "Common/characterselectionroot.h"


#include "Frontend/frontend_address_symbols.h"

#if defined(VERSION_US_REV1) || defined(VERSION_US) || defined(VERSION_EU) || defined(VERSION_DE) || defined(VERSION_EU_X)
#include "Common/selectionscreenstate.h"
#endif

#if defined(VERSION_US_REV1) || defined(VERSION_US) || defined(VERSION_EU) || defined(VERSION_DE) || defined(VERSION_EU_X)
#include "Common/label.h"
#endif

#if defined(VERSION_US_REV1) || defined(VERSION_US) || defined(VERSION_EU) || defined(VERSION_DE) || defined(VERSION_EU_X)
#include "Common/animation.h"
#endif

#if defined(VERSION_US_REV1) || defined(VERSION_US) || defined(VERSION_EU) || defined(VERSION_DE) || defined(VERSION_EU_X)
#include "types.h"
#endif

#if defined(VERSION_US_REV1) || defined(VERSION_US) || defined(VERSION_EU) || defined(VERSION_DE) || defined(VERSION_EU_X)
#include "Frontend/smp_overlay.h"
#endif

#if defined(VERSION_US_REV1) || defined(VERSION_US) || defined(VERSION_EU) || defined(VERSION_DE) || defined(VERSION_EU_X)
#include "Smp_overlay/smp_overlay.h"
#endif


#include <PR/gbi.h>


#include <platform_sdk.h>


#include "Common/sharedtrackobjectprefix.h"


#include "Common/sessionhandlerrow.h"


#include "Common/menu_screen_elements.h"


#include "Common/cheatcode.h"


#include "Engine/control.h"


#include "types.h"


#include "Frontend/scenario_result_rows.h"


#include "Ui/Tsmos/Screens/scenariosetupscreen.h"


#include "Preview/preview.h"


#include "Frontend/frontend_address_symbols.h"


#include <platform_sdk.h>


#include "Common/boot_tv_type.h"


#include "Frontend/screen.h"


#include "Frontend/screen_video_mode.h"


#include "Common/g_frontendkeepcurrentvideomodeonce.h"


#include "Common/g_selectionmessagestage.h"


#include "Resources/frontend_applyvideomode_data.h"


#include "Frontend/frontend_address_symbols.h"

#if defined(VERSION_EU_X) || defined(VERSION_US_REV1) || defined(VERSION_DE) || defined(VERSION_EU)
#include "types.h"
#endif

#if defined(VERSION_EU_X) || defined(VERSION_US_REV1) || defined(VERSION_DE) || defined(VERSION_EU)
#include "Common/runtime_declarations.h"
#endif

#if defined(VERSION_US)
#include "Common/resident_event_handler.h"
#endif

#if defined(VERSION_US)
#include "Common/multiplayeroptions.h"
#endif

#if defined(VERSION_US)
#include "Frontend/frontend_address_symbols.h"
#endif

#if defined(VERSION_US)
#include "Common/ccollisionsetup_t.h"
#endif

#if defined(VERSION_US)
#include "Common/runtime_declarations.h"
#endif

#if defined(VERSION_US)
#include "Common/effectrender.h"
#endif

#if defined(VERSION_US)
#include "Libsn/nav_isballisticarcobstructed_data.h"
#endif

#if defined(VERSION_US)
#include "Common/legacy_collision_actor.h"
#endif

#if defined(VERSION_US)
#include "frontend_symbols.h"
#endif

#if defined(VERSION_US)
#include "Frontend/frontend.h"
#endif


typedef union VideoInterval {
    u32 packed;
    struct {
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        u16 last, first;
#else
        u16 first, last;
#endif
    } half;
} VideoInterval;


typedef union VideoHorizontal {
    u32 packed;
    struct {
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        u32 last : 16; s32 first : 16;
#else
        s32 first : 16; u32 last : 16;
#endif
    } edge;
} VideoHorizontal;


struct VideoViewList {
    FrontendScreenViewport *head;
    char reserved[0x1C];
    FrontendScreenViewport defaultView;
};

unsigned int k_FrontendEncodedWords[3] = {
    0x66000000, 0x04000000, 0x00001352,
};
#endif
