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



char g_frenchPressAnyKey[36] = "APPUYEZ SUR N'IMPORTE QUELLE TOUCHE";

char g_creditsTextVisitOurWebsiteAtWwwAcclaimNetLowercase[40] = "visit our website at www.acclaim.net";

char g_frenchCreditsLauraAlexEricTeresaChetCatEt[44] = "laura alex eric teresa chet cat et jodie";

char g_frenchCreditsKtMikeSqueakDroopyBillRobDan[44] = "kt mike squeak droopy bill rob dan moogie";

char g_creditsTextMachelleEtVincentLowercase[20] = "machelle et vincent";

char g_creditsTextMmmmmmmViperLowercase[16] = "mmmmmmm. viper";

char g_creditsTextMichaelSimmonsLowercase[16] = "michael simmons";

char g_frenchCreditsBrettGow[12] = "brett gow";

char g_creditsTextTomBassLowercase[12] = "tom bass";

char g_frenchCreditsDonJackson[12] = "don jackson";

char g_frenchCreditsCasperFieldFerHangin[28] = "casper field - fer hangin";

char g_frenchCreditsEchoFarmFerDaTunes[28] = "echo farm - fer da tunes";

char g_frenchCreditsGinaNomellini[16] = "gina nomellini";

char g_creditsTextTheZachsterLowercase[16] = "the zachster";

char g_creditsTextMaxxbassParKsWavesLowercase[24] = "maxxbass par ks waves";

char g_frenchCreditsJefferyGreenDeSweetwater[28] = "jeffery green de sweetwater";

char g_frenchCreditsCjDeEventide[16] = "cj de eventide";

char g_frenchCreditsDeniseAdamsDeAcclaimPartnersInc[40] = "denise adams de acclaim partners inc";

char g_creditsTextMikePruittDeActorsClearinghouseLowercase[36] = "mike pruitt de actors clearinghouse";

char g_frenchCreditsDaveEtMattDeSatelliteStudio[36] = "dave et matt de satellite studio";

char g_creditsTextMariaParadisoLowercase[16] = "maria paradiso";

char g_creditsTextSteveEtColleenDienstbierLowercase[28] = "steve et colleen dienstbier";

char g_frenchCreditsDanEtBarbaraDienstbier[28] = "dan et barbara dienstbier";

char g_frenchCreditsJaneBroumleyPourSaPatience[32] = "jane broumley pour sa patience";
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



char g_frenchPressAnyKey[36] = "APPUYEZ SUR N'IMPORTE QUELLE TOUCHE";

char g_creditsTextVisitOurWebsiteAtWwwAcclaimNetLowercase[40] = "visit our website at www.acclaim.net";

char g_frenchCreditsLauraAlexEricTeresaChetCatEt[44] = "laura alex eric teresa chet cat et jodie";

char g_frenchCreditsKtMikeSqueakDroopyBillRobDan[44] = "kt mike squeak droopy bill rob dan moogie";

char g_creditsTextMachelleEtVincentLowercase[20] = "machelle et vincent";

char g_creditsTextMmmmmmmViperLowercase[16] = "mmmmmmm. viper";

char g_creditsTextMichaelSimmonsLowercase[16] = "michael simmons";

char g_frenchCreditsBrettGow[12] = "brett gow";

char g_creditsTextTomBassLowercase[12] = "tom bass";

char g_frenchCreditsDonJackson[12] = "don jackson";

char g_frenchCreditsCasperFieldFerHangin[28] = "casper field - fer hangin";

char g_frenchCreditsEchoFarmFerDaTunes[28] = "echo farm - fer da tunes";

char g_frenchCreditsGinaNomellini[16] = "gina nomellini";

char g_creditsTextTheZachsterLowercase[16] = "the zachster";

char g_creditsTextMaxxbassParKsWavesLowercase[24] = "maxxbass par ks waves";

char g_frenchCreditsJefferyGreenDeSweetwater[28] = "jeffery green de sweetwater";

char g_frenchCreditsCjDeEventide[16] = "cj de eventide";

char g_frenchCreditsDeniseAdamsDeAcclaimPartnersInc[40] = "denise adams de acclaim partners inc";

char g_creditsTextMikePruittDeActorsClearinghouseLowercase[36] = "mike pruitt de actors clearinghouse";

char g_frenchCreditsDaveEtMattDeSatelliteStudio[36] = "dave et matt de satellite studio";

char g_creditsTextMariaParadisoLowercase[16] = "maria paradiso";

char g_creditsTextSteveEtColleenDienstbierLowercase[28] = "steve et colleen dienstbier";

char g_frenchCreditsDanEtBarbaraDienstbier[28] = "dan et barbara dienstbier";

char g_frenchCreditsJaneBroumleyPourSaPatience[32] = "jane broumley pour sa patience";
#endif
