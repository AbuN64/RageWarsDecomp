#if defined(VERSION_US_REV1)

#include "types.h"


#include "Data/Player_callbacks/playerstate_callback_rom_entry.h"


#include "Data/Overlays/Playerstate/linktables_addresses.h"


#include "Ai/player_team_score.h"


#include "Common/player_action_and_pose_views.h"


#include "Data/Player_callbacks/playerstate_link_record_rom_link_targets.h"


#include "Common/aiprofile.h"


#include "Data/Player_callbacks/player_sequence_callback_addresses.h"


#include "Data/Ovltbl/player_state_callback_link_targets.h"


#include "Common/player_sequence_state.h"


#include "Data/Player_callbacks/player_empty_action_hook_addresses.h"

#if defined(VERSION_US_REV1)
#include "Common/runtime_declarations.h"
#endif

#if defined(VERSION_US_REV1)
#include "Common/effectrender.h"
#endif

#if defined(VERSION_US_REV1)
#include "Common/effectrender.h"
#endif

#if defined(VERSION_US_REV1)
#include "Common/effectrender.h"
#endif


struct {
    s32 timer;
    s32 parameter;
} g_playerStateLinkRecordConstantWords __attribute__((aligned(4))) = {
    0,
    7011
};
#endif
