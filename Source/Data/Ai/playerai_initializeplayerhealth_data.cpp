#include "Data/rom_callback_word.h"
#if defined(VERSION_EU)

#include "Common/level_actor.h"


#include "Common/shared_optionsscreen.h"


#include "Common/gameplay_camera.h"


#include "include_asm.h"


#include "Weapons/weapon_switch_actions.h"


#include "Common/vector4f.h"


#include "Common/ai_behaviour_types.h"


#include "types.h"


#include "Common/runtime_declarations.h"


#include "Weapons/actor_requestactorstate.h"


#include "Render/soundelement_playflatsound.h"


#include "Common/playerprofiles.h"


#include "Common/gameplay_transition.h"


#include "Common/triple.h"


#include "Common/resourceloadstate.h"


#include "Common/model_render.h"


#include "Common/shared_gameslot.h"


#include "Common/player_sequence_state.h"


#include "Common/self.h"


#include "Common/weapon_marker_and_profile_views.h"


#include "Common/sharedplayer.h"


#include "Common/aiprofile.h"


#include "Common/animationtriggerdefinition.h"


#include "Render/playerai_toggleforcemarker.h"


#include "Weapons/charge_and_linked_actor_handles.h"


#include "Weapons/player_movement_interfaces.h"


#include "Weapons/weapon_charge_latch.h"


#include "Common/weapon_screen_message_operations.h"


#include "Weapons/startup_cues_and_side_yaw.h"


#include "Common/objb.h"


#include "Weapons/weapon_mode_origin.h"


#include "Common/obj.h"


#include "Common/weapon_special_fire.h"


#include "Common/actorresourceheader.h"


#include "Common/mtx.h"


#include "Common/shared_particleinstance.h"


#include "Game/builddirectionmatrix.h"


#include "Weapons/pitch_translation_and_spin_actions.h"


#include "Ai/Player/player_getammocapacity.h"


#include "Ai/Player/player_startplayeranimation.h"


#include "Ai/player_alternate_fire.h"


#include "Gsky/sky_posttargetedscreenmessage.h"


#include "Particle/particle_releaseownerlistoneeffects.h"


#include "Weapon/weapon.h"


#include "Weaponai/weaponai_drawredmarkerquad__weaponai.h"


#include "World/playerprofile.h"


#include "Render/weapon_initializechargeandstartupcues_data.h"


#include "Ai/weapon_updatealternatefire__weaponai.h"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Common/shared_worldfunc.h"
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "World/playerai_respawnfragtagplayer.h"
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Graphu64/graphu64_buildlookatmatrix.h"
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Menu/Pak/menu_createmenufromtemplate.h"
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#include "Common/Lone/weapon_locked_notice_text.h"
#endif


#include "Ai/ai_shared_symbols.h"


#include "Ai/weaponai.h"


#include "Ai/ai_functions.h"


#include "Ai/ai_address_labels.h"


#include "Ai/Weapon/weapon.h"


struct {
    f32 targetFacingEaseRate;
    f32 reactionReserveApproachRate;
    f32 aimRates[3];
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
} k_PlayeraiInitializeplayerhealthData __attribute__((aligned(4))) = {
    0.349999994f,
    0.00625000009f,
    { 0.166666672f, 1.0f, 1.0f },
    { 20210, 10, 20220, 10, 20230, 10, 20240, 10, -1, 0, 20550, 10, 20551, 10, 20552, 10, 20553, 10, -1, 0, 20510, 10, 20520, 10, 20530, 10, 20540, 10, -1, 0 },
    { 0, 0, 0, 0, 0 },
    -3.0f,
    0,
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    0,
    { 0x00232B44 },
    { 0x00232B74 },
    0x0,
    20000,
    1.0f,
    0,
    0x0,
    1,
    { 0x00232E04 },
    { 0x00230604 },
    0x0,
    20010,
    1.0f,
    2,
    0x0,
    2,
    { 0x00232C78 },
    { 0x00230358 },
    0x0,
    20100,
    1.0f,
    0,
    0x0,
    3,
    { 0 },
    { 0x00230358 },
    0x0,
    20110,
    1.0f,
    0,
    0x0,
    4,
    { 0x00232C98 },
    { 0x00232CFC },
    0x0,
    (void *)((char *)&k_PlayeraiInitializeplayerhealthData + 20),
    1.0f,
    3,
    0x0,
    8,
    { 0x002328B8 },
    { 0x00232470 },
    0x0,
    (void *)((char *)&k_PlayeraiInitializeplayerhealthData + 40),
    1.0f,
    3,
    0x0,
    7,
    { 0 },
    { 0x00230604 },
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
    { 0x002307E0 },
    0x0,
    20100,
    1.0f,
    0,
    0x0,
    3,
    { 0 },
    { 0x002307E0 },
    0x0,
    20110,
    1.0f,
    0,
    0x0,
    5,
    { 0x00232E48 },
    { 0x00232E74 },
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
    { 0x00232CFC },
    0x0,
    20210,
    1.0f,
    3,
    0x20,
    9,
    { 0 },
    { 0x00232CFC },
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
