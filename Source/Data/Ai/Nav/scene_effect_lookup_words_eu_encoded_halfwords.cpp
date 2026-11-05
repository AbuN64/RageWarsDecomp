#if defined(VERSION_EU)

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


SceneEffectLookupWordsEuEncodedHalfwordsLayout k_SceneEffectLookupWordsEuEncodedHalfwords = {
    { 1.0f, 0.0f },
    { 4, 0, 3, 1, 0, 5, 5, 0, 3, 0, 2, 6, 6, 1, 0, 1, 8, 0, 3, 0, 8, 0, 8, 7, 7, 1, 4, 5, 5, 0, 3, 0, 8, 0, 8, 0, 8, 0, 8, 0, 0, 0, 0, 0, 0 },
    { 1.0f, 0.70710677f, 0.0f, 0.70710677f, 1.0f, 0.0f, 0.0f, 0.70710677f, 0.0f, -0.70710677f, 0.0f, 0.0f, -1.0f, -0.70710677f,
        0.0f, -0.70710677f, -1.0f, 0.0f, 0.0f, -0.70710677f, 0.0f, 0.70710677f },
    { 2163280, 2160352, 2166440, 2153984, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2157312, 2163280, 2160352, 2161200, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2157936, 2157312, 2163280, 2160352, 2163104, 2153984, 2161200, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 2157312, 2163280, 2160352, 2161200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2157312,
        2163280, 2160352, 2153520, 2151312, 2162824, 2153984, 2161200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2157312, 2163280,
        2160352, 2153520, 2151312, 2162784, 2153984, 2161200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2157312, 2163280, 2160352,
        2153520, 2162744, 2153984, 2161200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2157312, 2163280, 2160352, 2162864, 2153984,
        2161200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2157312, 2163280, 2160352, 2162904, 2153984, 2161200, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 2158464, 2157312, 2163280, 2160352, 2162904, 2153984, 2161200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 2159304, 2157312, 2163280, 2160352, 2161200, 2162784, 2153984, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2159528, 2157312,
        2163280, 2160352, 2162784, 2153984, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2159716, 2157312, 2163280, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2157312, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2157312, 2163280,
        2160352, 2162824, 2153984, 2161200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { (void *)g_navBehaviorCallbackRows[0], (void *)g_navBehaviorCallbackRows[1], (void *)g_navBehaviorCallbackRows[2],
        (void *)g_navBehaviorCallbackRows[3], (void *)g_navBehaviorCallbackRows[4], (void *)g_navBehaviorCallbackRows[5],
        (void *)g_navBehaviorCallbackRows[6], (void *)g_navBehaviorCallbackRows[7], (void *)g_navBehaviorCallbackRows[8],
        (void *)g_navBehaviorCallbackRows[9], (void *)g_navBehaviorCallbackRows[10], (void *)g_navBehaviorCallbackRows[11],
        (void *)g_navBehaviorCallbackRows[12], (void *)g_navBehaviorCallbackRows[13] },
    { 65536.0f, 2.1474836e+09f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { 2174940, 2174512, 0, 0 },
    1.0f,
    { 5, 0, 1, 2174336, 2174388, 0, 0 },
    1.0f,
    { 5, 0, 2, 2176780, 2176288, 0, 0 },
    1.0f,
    { 5, 0, 3, 2171900, 2167104, 0, 0 },
    1.0f,
    { 5, 0, 4, 2172016, 2167952, 0, 0 },
    1.0f,
    { 5, 0, 5, 2172228, 2169500, 0, 0 },
    1.0f,
    { 5, 0, 6, 2172948, 2173000, 0, 0 },
    1.0f,
    { 5, 0, 7, 2173228, 2173288, 0, 0 },
    1.0f,
    { 5, 0, 8, 2175436, 2174976, 0, 0 },
    1.0f,
    { 5, 0, 9, 2173936, 2173988, 0, 0 },
    1.0f,
    { 5, 0, 10, 2174128, 2174180, 0, 0 },
    1.0f,
    { 5, 0, 11, 2175488, 2175548, 0, 0 },
    1.0f,
    { 5, 0, 12, 2173536, 2173596, 0, 0 },
    1.0f,
    { 5, 0, 13, 2172432, 2171048, 0, 0 },
    1.0f,
    { 5, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 1701, 2, 1702, 4, 1703, 8, 1704, 16, 1705, 32, 1706, 64, 2200, 128, 2200, 256, 2200, 512,
        2200, 1024, 2200, 2048, 2200, 4096, 2200, 8192, 2200, 16384, 2200, 32768, 2200, 65536, 2200, 131072, 2200, 262144, 2200,
        524288, 2200, 1048576, 2200, 2097152, 2200, 4194304, 2200, 8388608, 2200 },
    0x01000000,
    2200,
    0x02000000,
    2200,
    0x04000000,
    2200,
    0x08000000,
    2200,
    0x10000000,
    2200,
    0x20000000,
    2200,
    2.0f,
    2200,
    (void *)&g_tlbMissExceptionVector,
    { 2200, 0, 0, 1, 2200, 0, 0 },
    { 0.01f, 2.1474836e+09f },
    { 65536, 327680, 262144, 786432, 524288, 655360, 131072, 196608 },
    { 3e+01f, 48.0f, 1.3e+02f },
};
#endif
