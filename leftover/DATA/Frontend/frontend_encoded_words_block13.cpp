#if defined(VERSION_EU_X)

#include "Common/menu_options_and_results.h"


#include "Common/aiprofile.h"


#include "Common/runtime_declarations.h"


#include "Common/player_join_requests.h"


#include "options.h"


#include "types.h"


#include "Common/selectionscreenstate.h"


#include "Common/screen.h"


#include "Common/menulistscreen.h"


#include "Frontend/join_getjoinrequestrank.h"


#include "Frontend/join_randomizejoinrequestentries.h"


#include "Frontend/frontend_activatematchoptionaction.h"


#include "Scene/cache_freememory.h"


#include "Common/shared_gameslot.h"


#include "Join/join_cyclejoinrequestrank.h"


#include "Ui/Tsmos/Smp/smp_button.h"


#include "Common/shared_menureply.h"


#include "Smp/smp_button.h"


#include "N64eng/n64eng.h"


#include "Frontend/frontend_address_symbols.h"


#include "include_asm.h"


#include "Common/frontend_resource_load_state.h"


#include "Common/resident_event_handler.h"


#include "Common/menu_overlay.h"


#include "Common/format.h"


#include "data_overlay_layouts.h"


#include "Match_options/frontend_creatematchoptions.h"


#include "Common/level_goal.h"


#include "Frontend/menuimage.h"


#include "Frontend/node_findwidgetbyresourceid.h"


#include "Widget/widget_findwidgetatpoint.h"

#if defined(VERSION_EU)
#include "types.h"
#endif

#if defined(VERSION_EU)
#include "Common/menu_overlay.h"
#endif

#if defined(VERSION_EU)
#include "Frontend/frontend.h"
#endif

#if defined(VERSION_EU)
#include "Smp/smp_button.h"
#endif

#if defined(VERSION_DE)
enum { OPTIONS_TEXT = 859 };
#endif

#if defined(VERSION_DE)
#else
#if defined(VERSION_EU_X)
enum { OPTIONS_TEXT = 867 };
#endif
#endif

#if defined(VERSION_DE)
#else
#if defined(VERSION_EU_X)
#else
enum { OPTIONS_TEXT = 863 };
#endif
#endif

unsigned int k_frontendFragment[2] = {
    0x00000016, 0x3DE147AE,
};
#endif
