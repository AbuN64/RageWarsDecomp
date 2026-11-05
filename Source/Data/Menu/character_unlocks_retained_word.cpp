#if defined(VERSION_US_REV1)

#include "Rsp/random_direction_and_affine_math.h"


#include "include_asm.h"


#include "Common/video_dimensions.h"


#include "Common/Lone/hud_reference_viewport_height.h"


#include "Render/material_color_and_fog_views.h"


#include "Common/characterselectionroot.h"


#include "Common/sharedplayer.h"


#include "Common/selectionscreenstate.h"


#include <PR/gbi.h>


#include <platform_sdk.h>


#include "types.h"


#include "Frontend/widget_findwidgetatpoint.h"


#include "Frontend/frontend_drawmodelpreview.h"


#include "Common/shared_gameslot.h"


#include "Frontend/smp_overlay.h"


#include "Common/sharedtrackobjectprefix.h"


#include "Common/sessionhandlerrow.h"


#include "Common/runtime_declarations.h"


#include "Engine/defs.h"


#include "Common/shared_menureply.h"


#include "Menu/g_menuplayerscissorrects.h"


#include "Common/playerprofiles.h"


#include "World/playerprofile.h"


#include "Menu/selection.h"


#include "Menu/Character_unlocks/character_unlocks_symbols.h"


#include "Data/rest_source_records.h"


#include "data_overlay_layouts.h"


#include "Frontend/frontend.h"

#if defined(VERSION_DE)
enum { UNLOCK_MARK = 129 };
#endif

#if defined(VERSION_DE)
#elif defined(VERSION_EU_X)
enum { UNLOCK_MARK = 135 };
#endif

#if defined(VERSION_DE)
#elif defined(VERSION_EU_X)
#else
enum { UNLOCK_MARK = 131 };
#endif

unsigned int g_characterUnlocksRetainedWord[1] = {
    0x00442454,
};
#endif
