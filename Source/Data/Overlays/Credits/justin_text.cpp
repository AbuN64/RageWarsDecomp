#if defined(VERSION_US_REV1)

#include "Weapon_state_tables/weapon_state_tables.h"


#include "Ai/Weapon/weapon.h"


#include "Engine/Audio/channel.h"


#include "Weapons/pitch_translation_and_spin_actions.h"


#include "Data/Ovl1_f/ovl1_f.h"


#include "Ai/ai_functions.h"


#include "types.h"


#include "include_asm.h"


#include "Data/Overlays/encoded_callback.h"


#include "Data/Overlays/Credits/linktables_addresses.h"


#include "Ai/weaponai.h"


#include "Weapons/charge_and_linked_actor_handles.h"


#include "Common/runtime_declarations.h"

#if defined(VERSION_EU)
#include "Data/Ovl1_g/weapon_update_callback_addresses.h"
#endif

#if defined(VERSION_EU)
#include "Data/Ovl1_g/weapon_spin_feedback_callback_address.h"
#endif

#if defined(VERSION_EU_X)
#include "Data/Ovl1_g/weapon_update_callback_addresses.h"
#endif

#if defined(VERSION_EU_X)
#include "Data/Ovl1_g/weapon_spin_feedback_callback_address.h"
#endif


char s_justinText[8] = "JUSTIN W";
#endif
