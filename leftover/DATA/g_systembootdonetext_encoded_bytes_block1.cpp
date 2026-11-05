#if defined(VERSION_EU_X)

#include "Common/hud_effects.h"


#include "System/timed_effect_and_item_menu_views.h"


#include "Common/sharedplayer.h"


#include <PR/gbi.h>


#include <platform_sdk.h>


#include "Common/math_helpers.h"


#include "Common/sessionhandlerrow.h"


#include "types.h"


#include "Common/shared_gameslot.h"


#include "Common/runtime_declarations.h"


#include "Common/vector4f.h"


#include "Common/aiprofile.h"


#include "Common/gameplay_camera.h"


#include "Common/boot_memory_and_thread_boundaries.h"


#include "Common/alfxparam.h"


#include <PR/os_internal_si.h>


#include "Render/setn64_startsessionthreads.h"


#include "itemmenu.h"


#include "Ui/X_files/x_plus.h"


#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"


#include "Common/snapshot_actor.h"


#include "include_asm.h"


#include "Constants/setup_updatenamecursor_data.h"


#include "Data/initialized_runtime_buffers.h"


#include "Render/setn64_updatefadetransition.h"


#include "itemmenu_symbols.h"


unsigned char k_gSystembootdonetextFragment[1] = {
    0x20,
};
#endif
