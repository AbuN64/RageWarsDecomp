#include "Data/rom_callback_word.h"
#include "Data/rom_callback_word.h"
#if defined(VERSION_DE)

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



float k_constantsFragment[6] = {
    -132.0f, 64.0f, 64.0f, 24.0f, -12.0f, -48.0f,
};

float g_aiDistanceBounds[2] = {
    0.0f, 102.399994f,
};
s32 g_playerSequenceAxisSigns[15] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1,
};



struct {
    f32 targetFacingEaseRate;
    f32 reactionReserveApproachRate;
    s16 precedingAnimationTriples[6];
    f32 aimScale;
    s16 weaponAnimationDurationPairs[30];
    s32 handMirrorAxesAndFlags[5];
    f32 weaponRestOffset;
    void * nextTable;
    u32 stateTableHeaderReserved[7];
    s32 state0Id;
    RomCallbackWord state0Enter;
    RomCallbackWord state0Update;
    u32 state0Reserved;
    s32 state0Animation;
    f32 state0Rate;
    s32 state0Threshold;
    u32 state0Flags;
    s32 state1Id;
    RomCallbackWord state1Enter;
    RomCallbackWord state1Update;
    u32 state1Reserved;
    s32 state1Animation;
    f32 state1Rate;
    s32 state1Threshold;
    u32 state1Flags;
    s32 state2Id;
    RomCallbackWord state2Enter;
    RomCallbackWord state2Update;
    u32 state2Reserved;
    s32 state2Animation;
    f32 state2Rate;
    s32 state2Threshold;
    u32 state2Flags;
    s32 state3Id;
    RomCallbackWord state3Enter;
    RomCallbackWord state3Update;
    u32 state3Reserved;
    s32 state3Animation;
    f32 state3Rate;
    s32 state3Threshold;
    u32 state3Flags;
    s32 state4Id;
    RomCallbackWord state4Enter;
    RomCallbackWord state4Update;
    u32 state4Reserved;
    void * state4AnimationList;
    f32 state4Rate;
    s32 state4Threshold;
    u32 state4Flags;
    s32 state5Id;
    RomCallbackWord state5Enter;
    RomCallbackWord state5Update;
    u32 state5Reserved;
    void * state5AnimationList;
    f32 state5Rate;
    s32 state5Threshold;
    u32 state5Flags;
    s32 state6Id;
    RomCallbackWord state6Enter;
    RomCallbackWord state6Update;
    u32 state6Reserved;
    s32 state6Animation;
    f32 state6Rate;
    s32 state6Threshold;
    u32 state6Flags;
    s32 state7Id;
    RomCallbackWord state7Enter;
    RomCallbackWord state7Update;
    u32 state7Reserved;
    s32 state7Animation;
    f32 state7Rate;
    s32 state7Threshold;
    u32 state7Flags;
    void * table8Next;
    u32 table8HeaderReserved[7];
    s32 state9Id;
    RomCallbackWord state9Enter;
    RomCallbackWord state9Update;
    u32 state9Reserved;
    s32 state9Animation;
    f32 state9Rate;
    s32 state9Threshold;
    u32 state9Flags;
    s32 state10Id;
    RomCallbackWord state10Enter;
    RomCallbackWord state10Update;
    u32 state10Reserved;
    s32 state10Animation;
    f32 state10Rate;
    s32 state10Threshold;
    u32 state10Flags;
    s32 state11Id;
    RomCallbackWord state11Enter;
    RomCallbackWord state11Update;
    u32 state11Reserved;
    s32 state11Animation;
    f32 state11Rate;
    s32 state11Threshold;
    u32 state11Flags;
    s32 state12Id;
    RomCallbackWord state12Enter;
    RomCallbackWord state12Update;
    u32 state12Reserved;
    s32 state12Animation;
    f32 state12Rate;
    s32 state12Threshold;
    u32 state12Flags;
    void * table13Next;
    u32 table13HeaderReserved[7];
    s32 state14Id;
    RomCallbackWord state14Enter;
    RomCallbackWord state14Update;
    u32 state14Reserved;
    s32 state14Animation;
    f32 state14Rate;
    s32 state14Threshold;
    u32 state14Flags;
    s32 state15Id;
    RomCallbackWord state15Enter;
    RomCallbackWord state15Update;
    u32 state15Reserved;
    s32 state15Animation;
    f32 state15Rate;
    s32 state15Threshold;
    u32 state15Flags;
    s32 state16Id;
    RomCallbackWord state16Enter;
    RomCallbackWord state16Update;
    u32 state16Reserved;
    s32 state16Animation;
    f32 state16Rate;
    s32 state16Threshold;
    u32 state16Flags;
    s32 state17Id;
    RomCallbackWord state17Enter;
    RomCallbackWord state17Update;
    u32 state17Reserved;
    s32 state17Animation;
    f32 state17Rate;
    s32 state17Threshold;
    u32 state17Flags;
    s32 state18Id;
    RomCallbackWord state18Enter;
    RomCallbackWord state18Update;
    u32 state18Reserved;
    s32 state18Animation;
    f32 state18Rate;
    s32 state18Threshold;
    u32 state18Flags;
} g_weaponSwitchStateWordsDe __attribute__((aligned(4))) = {
    0.349999994f,
    0.00625000009f,
    { 20210, 10, 20220, 10, 20230, 10 },
    1.0f,
    { 20210, 10, 20220, 10, 20230, 10, 20240, 10, -1, 0, 20550, 10, 20551, 10, 20552, 10, 20553, 10, -1, 0, 20510, 10, 20520, 10, 20530, 10, 20540, 10, -1, 0 },
    { 0, 0, 0, 0, 0 },
    -3.0f,
    0,
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    0,
    { 0x0022FF04 },
    { 0x00232B64 },
    0x0,
    20000,
    1.0f,
    0,
    0x0,
    1,
    { 0x00232DF4 },
    { 0x00230630 },
    0x0,
    20010,
    1.0f,
    2,
    0x0,
    2,
    { 0x00232C68 },
    { 0x002303A0 },
    0x0,
    20100,
    1.0f,
    0,
    0x0,
    3,
    { 0 },
    { 0x002303A0 },
    0x0,
    20110,
    1.0f,
    0,
    0x0,
    4,
    { 0x00232C88 },
    { 0x00232CEC },
    0x0,
    (void *)((char *)&g_weaponSwitchStateWordsDe + 24),
    1.0f,
    3,
    0x0,
    8,
    { 0x002328D8 },
    { 0x002323A4 },
    0x0,
    (void *)((char *)&g_weaponSwitchStateWordsDe + 44),
    1.0f,
    3,
    0x0,
    7,
    { 0 },
    { 0x00230630 },
    0x0,
    20249,
    1.0f,
    3,
    0x0,
    -1,
    { 0 },
    { 0 },
    0x0,
    0,
    0.0f,
    0,
    0x0,
    (void *)&g_weaponFireStateCallbackTable,
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    2,
    { 0 },
    { 0x002307FC },
    0x0,
    20100,
    1.0f,
    0,
    0x0,
    3,
    { 0 },
    { 0x002307FC },
    0x0,
    20110,
    1.0f,
    0,
    0x0,
    5,
    { 0x00232E38 },
    { 0x00232E64 },
    0x0,
    20200,
    1.0f,
    3,
    0x0,
    -1,
    { 0 },
    { 0 },
    0x0,
    0,
    0.0f,
    0,
    0x0,
    (void *)&g_weaponFireStateCallbackTable,
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    4,
    { 0 },
    { 0x00230B04 },
    0x0,
    20200,
    1.0f,
    3,
    0x0,
    8,
    { 0 },
    { 0x00230B04 },
    0x0,
    20200,
    1.0f,
    3,
    0x20,
    5,
    { 0 },
    { 0x00232CEC },
    0x0,
    20210,
    1.0f,
    3,
    0x20,
    9,
    { 0 },
    { 0x00232CEC },
    0x0,
    20550,
    1.0f,
    3,
    0x20,
    -1,
    { 0 },
    { 0 },
    0x0,
    0,
    0.0f,
    0,
    0x0,
};
#endif
