#if defined(VERSION_EU_X)

#include "Engine/session.h"


#include "Common/self.h"


#include "Ai/ai_functions.h"


#include "Common/level_actor.h"


#include "Common/shared_gameslot.h"


#include "Render/material_color_and_fog_views.h"


#include "Common/model_render.h"


#include <platform_sdk.h>


#include "Common/frag_tag_scores.h"


#include <PR/abi.h>


#include "Common/vector4f.h"


#include "Common/messagesemaphore.h"


#include <PR/gbi.h>


#include "types.h"


#include "Common/sharedplayer.h"


#include "Common/runtime_declarations.h"


#include "Common/resultsoptionsscreen.h"


#include "Resmgr/resmgr_string_memory.h"


#include "Ai/player_drawtintedplayer.h"


#include "Common/playerprofiles.h"


#include "Ai/player_ammo_gift.h"


#include "Ai/player_message_history.h"


#include "Weapon/weapon.h"


#include "Ui/X_files/x_plus.h"


#include "Gobjinst/player_drawtintedplayer_data.h"


#include "Ai/Playerai/playerai_playerai.h"


#include "Cbarrel/barrel_spawnactoreffect.h"


#include "Engine/Geometry/geometry_setupmaterial.h"


#include "Common/sessionhandlerrow.h"


#include "Ai/ai_shared_symbols.h"


#include "Common/weapon_marker_and_profile_views.h"


#include "Common/weapon_screen_message_operations.h"


#include "Common/aiprofile.h"


#include "Common/gameplay_transition.h"


#include "Common/player_score_table.h"


#include "Render/render_types.h"


#include "Common/menu_match_globals.h"


#include "Gsky/sky_postscaledscreenmessage.h"


#include "Render/player_returnone.h"


#include "Weapons/player_movement_interfaces.h"


#include "Render/weapon_initializechargeandstartupcues_data.h"


#include "Ai/player_alternate_fire.h"


#include "Common/player_sequence_state.h"


#include "Sound/externs.h"


#include "Common/player_action_and_pose_views.h"


#include "Sound/playerai_sequence_waits.h"


#include "include_asm.h"


#include "Common/gameplay_movement.h"


#include "Common/world.h"


#include "Common/triple.h"


#include "Common/resourceloadstate.h"


#include "Ai/Player/playerai_entermovingsequencestate_data.h"


#include "Ai/player_team_score.h"


#include "Engine/scene_drawopaqueactors.h"


#include "Insthdr/insthdr_getactorshadowradius.h"


#include "Ai/playerai_offsetactorforforcemarker_data.h"


#include "Ai/cteamselect.h"


#include "Engine/Unicol/unicol.h"


#include "Engine/Unicol/PLTFMCOL.h"


#include "Common/Lone/collision_current_actor.h"


#include "Weapons/charge_and_linked_actor_handles.h"


#include "Common/gameplay_camera.h"


#include "Common/gameplay_settings.h"


#include "World/playerai_respawnfragtagplayer.h"


#include "World/playerprofile.h"


#include "Common/geometry_blend_and_instance_views.h"


#include "Weapons/player_buildweaponhandtransform.h"


#include "Data/Weapon_callbacks/addrlow_weaponai_initializeswitchforsingleround.h"


#include "Data/Weapon_callbacks/g_weapon_resetcontrollerandspinencodedcallback.h"


#include "Data/Weapon_callbacks/addrlow_weapon_release_handles_and_exit_state_label.h"


#include "Data/Weapon_callbacks/player_health_callback_labels.h"


#include "Data/Ovl1_f/weapon_charge_callback_address.h"


#include "Data/Weapon_callbacks/addrlow_weaponai_updatealternatefire.h"


#include "Data/Weapon_callbacks/weapon_update_trigger_release_state_address.h"


#include "Data/Ovl1_d/weapon_charge_and_loop_sound_callback_address.h"


#include "Data/Ovl1_f/weapon_update_held_fire_callback_address.h"


#include "Data/Weapon_callbacks/weapon_state_callback_address.h"


#include "Data/Weapon_callbacks/weapon_startup_cue_address.h"


#include "Data/Weapon_callbacks/addrlow_weapon_advancespinandtriggermode.h"


#include "Data/Weapon_callbacks/weaponai_selectreleasedfirestate_address.h"


#include "Data/Weapon_callbacks/weapon_fire_state_table.h"


#include "Ai/Player/player_buildplayerviewtransform.h"


#include "Game/builddirectionmatrix.h"


#include "Graphu64/graphu64_getangledistance.h"


#include "Graphu64/graphu64_packfixedmatrix.h"


#include "Engine/defs.h"


#include "Particle/graphu64_matrixfromeulerxyz.h"


#include "Ui/X_files/x_stdio.h"


#include "Ai/playerprofile_symbols.h"


#include "Menu/player_initplayersettingsscreen.h"


#include "Common/selectionscreenstate.h"


#include "Common/format.h"


#include "Common/resident_event_handler.h"


#include "data_overlay_layouts.h"


#include "Data/rest_source_records.h"


#include "Ai/ai_address_labels.h"


#include "Weapons/startup_cues_and_side_yaw.h"


#include "Ai/playerai_updatedelayeddamage__player.h"


s32 k_PlayeraiTrystartplayersequenceZeroFill = 0;

float k_linktablesFragment[6] = {
    -132.0f, 64.0f, 64.0f, 24.0f, -12.0f, -48.0f,
};

float g_aiDistanceBounds[2] = {
    0.0f, 102.399994f,
};

s32 k_aiSignWords[15] = {
    1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, -1, 1,
    1, 1, 1,
};
#endif
