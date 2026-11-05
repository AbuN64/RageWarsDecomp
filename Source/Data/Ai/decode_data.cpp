#if defined(VERSION_US)

#include "Ai/Nav/roam.h"


#include "frontend_symbols.h"


#include "Common/output.h"


#include "Common/navigation_graph.h"


#include "Common/world.h"


#include "Common/vector4f.h"


#include "Common/shared_worldfunc.h"


#include "Common/runtime_declarations.h"


#include "Common/gameplay_transition.h"


#include "Common/round_state_variants.h"


#include "types.h"


#include "Common/shared_gameslot.h"


#include "Common/rendercounters.h"


#include "Common/sharedplayer.h"


#include "Common/selectionscreenstate.h"


#include "Render/player_controller_reset_views.h"


#include "Common/results.h"


#include "Engine/Cache/list.h"


#include "Weapons/actor_requestactorstate.h"


#include "Render/soundelement_playflatsound.h"


#include "Render/player_spawn_placement.h"


#include "Ai/Player/playerai_buildforcemarkertransform.h"


#include "Ai/Player/player_death__playerai.h"


#include "Ai/Player/player_placeplayerforround.h"


#include "Ai/Player/player_startplayeranimation.h"


#include "Engine/Instance/gobjinst_getactoroffsetpositionandmodel.h"


#include "Engine/scene_drawopaqueactors.h"


#include "Engine/session.h"


#include "Gsky/sky_postscaledscreenmessage.h"


#include "Link/link_dispatchmatchingtriggers.h"


#include "Menu/Items/Scene/scene_setlevelactorstatebit.h"


#include "Particle/ghot_dispatchattachmenteffects_data.h"


#include "Particle/particle_releaseownerlistoneeffects.h"


#include "Render/control_cycleactorsnapshotmode.h"


#include "Render/playerai_toggleforcemarker.h"


#include "Ai/player_death_motion.h"


#include "Engine/scene_drawtransitioncoloroverlay.h"


#include "Camera/gsky_setdamageeffect.h"


#include "Ai/player_message_history.h"


#include "Ai/player_startsourceeffect__player.h"


#include "Ai/ai_shared_symbols.h"


#include "Ai/shared_pickupgoalnode.h"


#include "Common/ballisticparams.h"


#include "Common/triple.h"


#include "Common/aiprofile.h"


#include "Common/shared_particleinstance.h"


#include "Ai/Player/player_getammocapacity.h"


#include "Gobjinst/player_drawtintedplayer_data.h"


#include "Ai/Player/player_updatefragtagselection_data_player_updatefragtagselection_data.h"


#include "Common/geometry_blend_and_instance_views.h"


#include <PR/gbi.h>


#include "Common/sessionhandlerrow.h"


#include "Fx/fx_drawboundedparticlequads.h"


#include "Engine/Geometry/geometry_setupmaterial.h"


#include "Common/weapon_marker_and_profile_views.h"


#include "Common/gameplay_camera.h"


#include "Common/weapon_screen_message_operations.h"


#include "Common/multiplayeroptions.h"


#include "Common/player_sequence_state.h"


#include "Common/resourceloadstate.h"


#include "Gobjinst/gobjinst_buildactorpose.h"


#include "Menu/Items/Scene/scene_registeractorinscenelists.h"


#include "Common/game_session.h"


#include "Engine/Setn64/setn64_cleardepthrect.h"


#include "Ai/Player/player_drawredmarkerprism_playerai.h"


#include "Gobjinst/gameobject_getactorheight.h"


#include "Ai/ai_functions.h"


#include <platform_sdk.h>


#include "Common/resident_event_handler.h"


#include "Common/obj.h"


#include "Fx/normalize_vector.h"


#include "Ai/Player/playerai_computeaimrotation.h"


#include "Game/builddirectionmatrix.h"


#include "Graphu64/graphu64_getangledistance.h"


#include "Engine/Instance/Gobjinst/gastate_advancerootmotion_data.h"


#include "Common/mtx.h"


#include "Graphu64/graphu64_packfixedmatrix.h"


#include "Particle/graphu64_matrixfromeulerxyz.h"


#include "Ai/player_symbols.h"


#include "Common/approachlocation.h"


#include "Common/Lone/particle_collision_probe_result.h"


#include "Weapons/aim_types.h"


#include "Ai/Player/playerai_updateaimandlockmarker.h"


#include "Ai/Player/player_buildplayerviewtransform.h"


#include "Libsn/nav_isballisticarcobstructed_data.h"


#include "Common/Lone/collision_current_actor.h"


#include "Common/legacy_collision_actor.h"


#include "Common/sharedtrackobjectprefix.h"


#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"


#include "Gsky/gsky_projecttoscreen.h"


#include "Rsp/random_direction_and_affine_math.h"


#include "include_asm.h"


#include "Common/audio_voice_slots.h"


#include "Common/menu_model_preview.h"


#include "Common/scene_frame_and_effect_updates.h"


#include "Common/gameplay_movement.h"


#include "Common/effectrender.h"


#include "Common/objb.h"


#include "Ai/Player/player_updateplayereffectlights.h"


#include "Engine/gdynlight.h"


#include "Placeplayerlight/placeplayerlight.h"


#include "Ai/player_light_pattern_names.h"


#include "Ai/Player/playerai_drawammocounters.h"


#include "Weapons/player_movement_interfaces.h"


#include "Common/menu_match_globals.h"


#include "Engine/Audio/channel.h"


#include "Player_updateplayercamera/player_updateplayercamera.h"


#include "Graphu64/graphu64_buildlookatmatrix.h"


#include "Engine/Audio/T2SoundElement.h"


#include "Ai/cteamselect.h"


#include "Common/animationtriggerdefinition.h"


#include "Data/Player_swimming/player_swimming_sound_ids.h"


#include "Weapons/g_playerswimconstants.h"


#include "Menu/Pak/menu_createmenufromtemplate.h"


#include "Engine/ccinema_drawmessages.h"


#include "Menu/pak_load.h"


#include "Common/frag_tag_scores.h"


#include "Ai/Player/playerai_entermovingsequencestate_data.h"


#include "Common/viewflags.h"


#include "Data/Weapon_callbacks/playerai_initializeplayerhealth.h"


#include "Engine/Unicol/unicol.h"


#include "Ai/Playerai/playerai_playerai.h"


#include "Cbarrel/barrel_spawnactoreffect.h"


#include "Common/brain.h"


#include "Common/group.h"


#include "Common/reserved_shared_declarations.h"


#include "Frontend/frontend_opengameplayfrontend.h"


#include "Ui/X_files/x_plus.h"


#include "Engine/Audio/T2soundelement/sound_context_control.h"


#include "Common/weapon_select_brain.h"


#include "Common/player_action_and_pose_views.h"


#include "Ai/Player/player_updatefragtagselection_data__player_updatefragtagselection_data.h"


#include "Playerai/g_playerstext.h"


#include "Weapons/player_updatefragtagselection.h"


#include "Engine/control.h"


#include "Ui/Tsmos/tsmos_activatecontrollerstate.h"


#include "Scene/cache_allocateresourceat.h"


#include "Weapons/playerai_applystun.h"


#include "Camera/Gsky/gsky_startfade.h"


#include "Common/shared_optionsscreen.h"


#include <PR/abi.h>


#include "Common/loadout.h"


#include "Common/player_score_table.h"


#include "Common/player_pool_and_inode_cache_views.h"


#include "Ai/Player/player_model_and_held_weapon_rendering.h"


#include "Ai/Player/playerai_findtransientplayer.h"


#include "Gsky/gsky_loadprojectionmatrix.h"


#include "Gobjinst/gobjinst_buildactortransform.h"


#include "Common/actor_header.h"


#include "Common/level_actor.h"


#include "Common/resultsoptionsscreen.h"


#include "Common/playerprofiles.h"


#include "Engine/rumble.h"


#include "Gobjinst/gameobject_loadmodel.h"


#include "Engine/Cinema/cinema.h"


#include "Render/weapon_initializechargeandstartupcues_data.h"


#include "Audio/voice.h"


#include "Engine/Audio/Voice/voice.h"


#include "Particle/particle_updatesystem.h"


#include "Common/particle_lighting.h"


#include "Geometry/geometry_drawblendparts.h"


#include "Menu/Items/Scene/scene_findactortriggerrange.h"


#include "Common/gameplay_reactions.h"


#include "Render/shared_reactioninteraction.h"


#include "../../sdk/include/AUDIO/sprintf.H"


#include "Common/player_record_and_fragtag_views.h"


#include "Common/gameplay_round_rules.h"


#include "Common/ai_behaviour_types.h"


#include "Common/actorresourceheader.h"


#include "Scene/cache_requestresource.h"


#include "Render/setn64_getpacksection.h"


#include "Gfx/Text/playerai_applydamageovertime_data.h"


#include "Ai/Player/playerai_applydamageovertime__player_updatefragtagselection_data.h"


#include "Engine/Instance/gobjinst.h"


#include "Ai/Player/player_death_playerai.h"


#include "Common/Lone/hud_reference_viewport_height.h"


#include "Gfx/player_updatefragtagselection_data.h"


#include "Common/track_spline.h"


#include "Insthdr/insthdr_getactorshadowradius.h"


#include "Data/Gfxdata/audio_decodeframe_data.h"


#include "Ai/playerai_applydamageovertime_data__player_updatefragtagselection_data.h"


#include "World/playerprofile.h"


#include "Common/Lone/g_currentstagepreset.h"


#include "Gfx/Text/player_camera_callback.h"


#include "Sound/player_movement_scalar_view.h"


#include "Common/probe.h"


#include "Camera/gsky_resetheadbob.h"


#include "Sound/externs.h"


#include "Engine/contpad.h"


#include "Fx/contpad_initcontrollerinput.h"


#include "Common/pakqueuestate.h"


#include "Common/cache_releaseresource.h"


#include "Common/soundinfo.h"


#include "World/playerai_respawnfragtagplayer.h"


#include "Engine/gregion.h"


#include "Sound/playerai_sequence_waits.h"


#include "Ai/ai_address_labels.h"


#include "Ai/nav_symbols.h"

#if ((defined(VERSION_EU))) || ((defined(VERSION_EU_X)))
#include "Data/Player_callbacks/playerstate_link_record_rom_link_targets.h"
#endif


#include "Data/rest_source_records.h"


#include "Ui/Tsmos/Screens/pakinterface_loadgame.h"


#include "Ai/cbarrel.h"


#include "Ai/playerai_updatedelayeddamage__player.h"


#include "Ai/Weapon/weapon.h"






typedef struct { f32 x, y, z; } Position;


struct TravelTarget { u8 pad0[0x34]; Position pos; f32 height; u8 pad44[0x1A]; u8 duration; };


typedef struct PlayerModelDefinition {
    u8 header[0x18];
    s32 startHealth;
    u8 body[0xE0];
    CVector3 spawnPosition;
} PlayerModelDefinition;


float k_DecodeData[16] = {
    1.7280002f, 2.7648f, 20.736f, 1.0368001f, 0.0f, 0.0f,
    0.0f, 2.88f, 21.599998f, 1.08f, 1.7280002f, 12.960001f,
    0.64800006f, 0.0f, 0.0f, 0.0f,
};
#endif
