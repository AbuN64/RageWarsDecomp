#if defined(VERSION_US_REV1)

#include "Ai/Weapon/weapon.h"


#include "Engine/events.h"


#include "Common/output.h"


#include "frontend_symbols.h"


#include "Common/ai_behaviour_types.h"


#include "Common/navigation_graph.h"


#include "Common/navigation_node_and_route_views.h"


#include "types.h"


#include "Ai/Nav/search_node_state.h"


#include "include_asm.h"


#include "Common/navigation_actor_search_views.h"


#include "Common/vector4f.h"


#include "Common/aiprofile.h"


#include "Ai/Nav/pickuptarget.h"


#include "Ai/portal_searchpath.h"


#include "Ai/portal_isnodemovementblocked.h"


#include "Ai/Nav/Route/route.h"


#include "Ai/shared_pickupgoalnode.h"


#include "Ai/nav_symbols.h"


#include "Common/actorrec.h"


#include "Common/runtime_declarations.h"


#include "Common/sharedplayer.h"


#include "Fx/normalize_vector.h"


#include "pickup.h"


#include "Particle/graphu64_matrixfromeulerxyz.h"


#include "Ai/ai_functions.h"

#if defined(VERSION_DE)
#include "Data/Actor_state_callbacks/actor_state_callback_labels.h"
#endif


#include "Common/output.h"


#include "Common/Lone/particle_collision_probe_result.h"


#include "Common/ppdecom_unpackresource.h"


#include "Engine/defs.h"


#include "Render/setn64_getpacksection.h"


#include "Math/doublebits.h"


#include "Libsn/nav_isballisticarcobstructed_data.h"


#include "Engine/Unicol/unicol.h"


#include "Common/shared_optionsscreen.h"


#include "Common/gameplay_reaction_rules.h"


#include "Common/gameplay_transition.h"


#include "Common/triple.h"


#include "Common/shared_gameslot.h"


#include "Ai/Nav/nav_evaluatecaptureflagmarkersearch.h"


#include "Ai/Nav/teammarker.h"


#include "Ai/Player/scaled_updatetargetpitch.h"


#include "Ai/ai_shared_symbols.h"

#if defined(VERSION_DE)
#include "Data/Ovl1_c/navigation_callback_address.h"
#endif


#include "Common/level_actor.h"


#include "Ai/Nav/nav_setpickupgoalweights.h"


#include "Ai/Nav/searchnode.h"


#include "Ai/Nav/nav_selectpickupgoal.h"


#include "Ai/Nav/nav_selectpickupgoaleu.h"


#include "Common/measured_storage.h"


#include "Common/route_chase_records.h"


#include "Common/rec.h"


#include "Common/self.h"


#include "Ai/Player/player_getammocapacity.h"


#include "Fx/target.h"


#include <platform_sdk.h>


#include "Common/ballisticparams.h"


#include "Common/weapon_select_brain.h"


#include "Game/weaponselect.h"


#include "Data/rest_source_records.h"


#include "Particle/particle_releaseownerlistoneeffects.h"


#include "World/playerai_respawnfragtagplayer.h"


#include "Common/resourceloadstate.h"


#include "Common/brain.h"


#include "Attack/attack.h"


#include "Common/vector.h"


#include "Ai/Nav/nav_updaterangedcombat.h"


#include "Ai/Nav/nav_updateclosecombat.h"


#include "Common/weapon_marker_and_profile_views.h"


#include "Ai/Nav/nav_updatevisiblepursuit.h"


#include "Ai/Nav/nav_initpursuitstrafe.h"


#include "Ai/Nav/combatinit.h"


#include "Rsp/random_direction_and_affine_math.h"


#include "Ai/Nav/wheel.h"


#include "Ai/Nav/Portal/portal_updatealternatingactionbursts.h"


#include "Behaviour/behaviour.h"


#include "Frontend/player.h"


#include "Ai/route_relation_grid.h"


#include "Common/shared_worldfunc.h"


#include "Ai/Nav/farthest.h"


#include "Ai/source.h"


#include "Ai/Nav/carrier.h"


#include "Common/format.h"


#include "Common/resident_event_handler.h"


#include "data_overlay_layouts.h"


#include "Ai/Nav/nav_resetobjectarrivalchase.h"


#include "Ai/objectchase.h"


#include "Common/player_sequence_state.h"


#include "Ai/Nav/jumproute.h"


#include "Ai/Nav/roam.h"



















#if defined(VERSION_DE)
#endif

#if !defined(VERSION_DE)
#endif

#if !defined(VERSION_DE)
#endif

#if !defined(VERSION_DE)
#endif



float g_FindData[3] = {
    1.024f, -1.024f, 2.0f,
};
#endif
