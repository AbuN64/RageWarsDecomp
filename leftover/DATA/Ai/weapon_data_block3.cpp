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


unsigned int k_weaponRegisterMoveInstruction[1] = {
    0x02603821,
};
#endif
