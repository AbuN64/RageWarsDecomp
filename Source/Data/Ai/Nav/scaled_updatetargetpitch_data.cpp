#if defined(VERSION_US)

#include "Common/output.h"


#include "frontend_symbols.h"


#include "Common/game_session.h"


#include "Common/vector4f.h"


#include "include_asm.h"


#include "Common/ai_behaviour_types.h"


#include "types.h"


#include "Common/runtime_declarations.h"


#include "Weapons/player_movement_interfaces.h"


#include "Common/navigation_graph.h"


#include "Common/shared_gameslot.h"


#include "Common/rendercounters.h"


#include "Fx/normalize_vector.h"


#include "Common/navigation_node_and_route_views.h"


#include "Common/rec.h"


#include "Ai/Nav/nav_updatecomputerplayerstatus.h"


#include "Common/sharedplayer.h"


#include "Ai/Player/scaled_updatetargetpitch.h"


#include "Behaviour/behaviour.h"


#include "Engine/contpad.h"


#include "Frontend/player.h"


#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"


#include "Insthdr/insthdr_getactorshadowradius.h"


#include "Ai/Cbarrel/barrel_getsignedangletopoint.h"


#include "Ai/Player/player_getammocapacity.h"


#include "Common/font_style_and_glyph_operations.h"


#include "Ai/shared_pickupgoalnode.h"


#include "Common/triple.h"


#include "Ai/nav_symbols.h"


#include "Particle/graphu64_matrixfromeulerxyz.h"


#include "Ai/ai_functions.h"


#include "Common/Lone/particle_collision_probe_result.h"


#include "Common/aiprofile.h"


#include "Common/weapon_screen_message_operations.h"


#include "Common/ballisticparams.h"


#include "Common/integerstate2c.h"


#include "Ai/Player/player_placeplayerforround.h"


#include "Render/playerai_toggleforcemarker.h"


#include "Libsn/nav_isballisticarcobstructed_data.h"


#include "Ai/portal_isnodemovementblocked.h"


#include "Engine/Unicol/unicol.h"


#include "Common/Lone/collision_current_actor.h"


#include "Ai/ai_shared_symbols.h"


#include "Data/rest_source_records.h"


#include "Ai/Nav/Scaled/g_actorradialdirections_wheel.h"


#include "Ai/Nav/carrier.h"


#include "Ai/Nav/combatinit.h"


#include "Ai/Nav/farthest.h"


#include "Ai/Nav/jumproute.h"


#include "Ai/Nav/nav_initpursuitstrafe.h"


#include "Ai/Nav/nav_resetobjectarrivalchase.h"


#include "Ai/Nav/nav_selectpickupgoal.h"


#include "Ai/Nav/nav_updateclosecombat.h"


#include "Ai/Nav/nav_updaterangedcombat.h"


#include "Ai/Nav/nav_updatevisiblepursuit.h"


#include "Ai/Nav/roam.h"


#include "Ai/Nav/targetfollow.h"


#include "Ai/Nav/wheel.h"


#include "Attack/attack.h"


#include "Fx/target.h"


#include "Game/weaponselect.h"


#include "pickup.h"


#include "Data/Ovl1_c/navigation_callback_address.h"


#include "Data/Ovl1_d/nav_initvisiblepursuit.h"


#include "Data/Ovl1_d/addrlow_nav_updatevisiblepursuit.h"


#include "Data/Actor_state_callbacks/actor_state_callback_labels.h"


unsigned int k_ScaledUpdatetargetpitchData[1] = {
    0x0B000000,
};
#endif
