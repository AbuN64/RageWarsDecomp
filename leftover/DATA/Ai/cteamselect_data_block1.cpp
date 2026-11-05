#if defined(VERSION_EU)

#include "Common/gameplay_camera.h"


#include "Common/gameplay_transition.h"


#include "Particle/graphu64_matrixfromeulerxyz.h"


#include "include_asm.h"


#include "Menu/teammenu.h"


#include "Common/sharedplayer.h"


#include "Common/math_helpers.h"


#include "types.h"


#include "Common/runtime_declarations.h"


#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"


#include "Common/aiprofile.h"


#include "Common/viewflags.h"


#include "Common/shared_gameslot.h"


#include <PR/gbi.h>


#include "Common/vector4f.h"


#include "Common/weapon_screen_message_operations.h"


#include "Common/player_record_and_fragtag_views.h"


#include "Common/resourceloadstate.h"


#include "Render/soundelement_playflatsound.h"


#include <platform_sdk.h>


#include <PR/abi.h>


#include "Ai/cteamselect.h"


#include "Common/sessionhandlerrow.h"


#include "Common/triple.h"


#include "Engine/rumble.h"


#include "Game/builddirectionmatrix.h"


#include "Weaponai/weaponai_drawredmarkerquad__weaponai.h"


#include "Graphu64/graphu64_buildlookatmatrix.h"


#include "World/playerai_respawnfragtagplayer.h"


#include "Common/Lone/hud_reference_viewport_height.h"


#include "onscrn.h"


#include "Cteamselect/cteamselect_drawteamicons.h"


#include "Cteamselect/s_selectteamtext.h"


#include "Onscrn/onscreen_drawscaledmaskedimage.h"


#include "Common/sharedtrackobjectprefix.h"


#include "Common/menu_match_globals.h"


#include "Engine/Audio/channel.h"


#include "Cteamselect/cteamselect_updateteamchoiceinput.h"


#include "Cteamselect/cteamselect_updateteamwheel.h"


#include "Cteamselect/player_resetplayerforround_data.h"


#include "Ai/Cteamselect/cteamselect_initteamchoices.h"


#include "Cteamselect/cteamselect_drawteamwheel.h"


#include "Data/rest_source_records.h"


#include "Data/Ovl1_d/nav_initvisiblepursuit.h"


#include "Data/Ovl1_d/addrlow_nav_updatevisiblepursuit.h"


#include "Ai/Weapon/weapon.h"


typedef struct CWeapon_t {
    s8 m_bHolding;
    s8 m_nWeaponSlot;
} CWeapon;


struct TeamWeaponPlayer {
    u8 pad0[((char *)&((Player *)0)->weaponSlots - (char *)0)];
    CWeapon m_WeaponList[22];
    s16 m_CurrentWeapon;
};

unsigned int k_cteamselectFragment[2] = {
    0x00000000, 0x2129FFFF,
};
#endif
