#if defined(VERSION_EU)

#include "Ai/Weapon/weapon.h"


#include "Common/gameplay_camera.h"


#include "include_asm.h"


#include "Common/shared_gameslot.h"


#include "Common/gameplay_transition.h"


#include "Common/pickup_entry_tables.h"


#include "types.h"


#include "Common/weapon_screen_message_operations.h"


#include "Insthdr/insthdr_getactorshadowradius.h"


#include "Pickup/pickup_cancollect.h"


#include "Pickup/pickup_definitions.h"


#include "Pickup/pickup_applyammobundle.h"


#include "Pickup/pickup_trailing_text.h"


#include "Player_updateplayercamera/player_updateplayercamera.h"


#include "Common/animationtriggerdefinition.h"


#include "Ai/weaponselect.h"


#include "Common/ballisticparams.h"


#include "Common/resourceloadstate.h"


#include "Engine/Audio/channel.h"


#include "Common/sharedplayer.h"


#include "Common/menu_abbdc_versions.h"


#include "Common/menu_match_globals.h"


#include "Ui/X_files/x_plus.h"


#include "Common/level_actor.h"


#include "Common/vector4f.h"


#include "Common/Lone/g_languageindex.h"


#include "Common/viewflags.h"


#include "Common/playerprofiles.h"


#include "Common/aiprofile.h"


#include "Common/frag_tag_scores.h"


#include "System/sound_context_music_and_voice_control.h"


#include "itemmenu.h"


#include "World/playerprofile.h"


#include "Common/triple.h"


#include "Common/round_state_variants.h"


#include "Common/runtime_declarations.h"


#include "Common/level_spawn.h"


#include "Pickup/pickup_applyspecialpickup_symbols.h"


#include "Common/track_requesttrackbykey.h"


#include "Common/world.h"


#include "pickup.h"


#include "Engine/session.h"


#include "Menu/Items/Scene/scene_setlevelactorstatebit.h"


#include "Ai/player_death_playerai.h"


#include "Common/response.h"


#include "Data/rest_source_records.h"


#include "Data/Common/g_pickuppowerupdefinitions.h"


#include "Common/Lone/weapon_locked_notice_text.h"


#include "Data/Common/g_pickupweapondefinitions.h"


#include "Data/Common/g_pickuphealthdefinitions.h"


#include "Pickup/g_pickuphealthdefinitions_symbols.h"


#include "Data/Common/g_pickupspecialdefinitions.h"

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#include "types.h"
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#include "Common/menu_match_globals.h"
#endif

#if defined(VERSION_DE)
#include "types.h"
#endif



char g_frenchCreditsLoppementEtDe[16] = "loppement et de";
#endif

#if defined(VERSION_EU_X)

#include "Ai/Weapon/weapon.h"


#include "Common/gameplay_camera.h"


#include "include_asm.h"


#include "Common/shared_gameslot.h"


#include "Common/gameplay_transition.h"


#include "Common/pickup_entry_tables.h"


#include "types.h"


#include "Common/weapon_screen_message_operations.h"


#include "Insthdr/insthdr_getactorshadowradius.h"


#include "Pickup/pickup_cancollect.h"


#include "Pickup/pickup_definitions.h"


#include "Pickup/pickup_applyammobundle.h"


#include "Pickup/pickup_trailing_text.h"


#include "Player_updateplayercamera/player_updateplayercamera.h"


#include "Common/animationtriggerdefinition.h"


#include "Ai/weaponselect.h"


#include "Common/ballisticparams.h"


#include "Common/resourceloadstate.h"


#include "Engine/Audio/channel.h"


#include "Common/sharedplayer.h"


#include "Common/menu_abbdc_versions.h"


#include "Common/menu_match_globals.h"


#include "Ui/X_files/x_plus.h"


#include "Common/level_actor.h"


#include "Common/vector4f.h"


#include "Common/Lone/g_languageindex.h"


#include "Common/viewflags.h"


#include "Common/playerprofiles.h"


#include "Common/aiprofile.h"


#include "Common/frag_tag_scores.h"


#include "System/sound_context_music_and_voice_control.h"


#include "itemmenu.h"


#include "World/playerprofile.h"


#include "Common/triple.h"


#include "Common/round_state_variants.h"


#include "Common/runtime_declarations.h"


#include "Common/level_spawn.h"


#include "Pickup/pickup_applyspecialpickup_symbols.h"


#include "Common/track_requesttrackbykey.h"


#include "Common/world.h"


#include "pickup.h"


#include "Engine/session.h"


#include "Menu/Items/Scene/scene_setlevelactorstatebit.h"


#include "Ai/player_death_playerai.h"


#include "Common/response.h"


#include "Data/rest_source_records.h"


#include "Data/Common/g_pickuppowerupdefinitions.h"


#include "Common/Lone/weapon_locked_notice_text.h"


#include "Data/Common/g_pickupweapondefinitions.h"


#include "Data/Common/g_pickuphealthdefinitions.h"


#include "Pickup/g_pickuphealthdefinitions_symbols.h"


#include "Data/Common/g_pickupspecialdefinitions.h"

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#include "types.h"
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#include "Common/menu_match_globals.h"
#endif

#if defined(VERSION_DE)
#include "types.h"
#endif



char g_frenchCreditsLoppementEtDe[16] = "loppement et de";
#endif
