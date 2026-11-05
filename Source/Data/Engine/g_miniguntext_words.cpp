#if defined(VERSION_US_REV1)

#include "Engine/cache.h"


#include "Engine/Instance/gobjinst.h"


#include "include_asm.h"


#include "Gamecore/externs.h"


#include "Common/runtime_declarations.h"


#include "Engine/link.h"


#include "Common/effectcontribution.h"


#include "types.h"


#include "Common/math_helpers.h"


#include "Common/world.h"


#include "Common/sharedplayer.h"


#include "Render/setn64_getpacksection.h"


#include "Actors/vertex_light_and_actor_views.h"


#include "Common/vector4f.h"


#include "Common/level_actor.h"


#include "Common/listheader.h"


#include "Common/trigger_and_float_value_operations.h"


#include "System/sound_context_music_and_voice_control.h"


#include "Common/navigation_node_and_route_views.h"


#include "Common/Lone/g_languageindex.h"


#include "Common/gameplay_sound_table.h"


#include "Render/soundelement_playflatsound.h"


#include "Engine/Audio/T2SoundElement.h"


#include "Engine/geometry.h"


#include "Common/triple.h"


#include "Common/menu_match_globals.h"


#include "Actionai/action_updatebreakableproximity.h"


#include "Animpool/animpool_spawndescribedsceneeffect.h"


#include "Cbarrel/barrel_spawnflaggedeffects.h"


#include "Gsky/sky_posttargetedscreenmessage.h"


#include "Link/link_dispatchmatchingtriggers.h"


#include "Menu/Items/Scene/scene_findactortriggerrange.h"


#include "Menu/Items/Scene/scene_registeractorinscenelists.h"


#include "Menu/Items/Scene/scene_setlevelactorstatebit.h"


#include "Track/track_drawtrackoverlay.h"


#include "Common/track_requesttrackbykey.h"


#include "Render/timed_session_transitions.h"


#include "Engine/scene.h"


#include "Data/rest_source_records.h"


#include "libultra/ACTOR_STATE_TABLE_END_DATA.H"


#include "Engine/particle.h"


#include "Engine/lighting.h"


typedef void (*NavPrimaryFn)(NavigationPlatform *, void *, Trigger *);


typedef void (*NavSecondaryFn)(Trigger *);


typedef struct NavCallbackPair { NavPrimaryFn primary; NavSecondaryFn secondary; } NavCallbackPair;

s32 g_GMiniguntextWords[1] = {
    1,
};

u16 g_colorJitterSignedBytePairs[46] = {
    63481, 63733, 2062, 6412, 4631, 6670,
    64750, 62179, 55266, 58855, 58845, 58090,
    57829, 61426, 2, 65267, 62455, 1282,
    65033, 6175, 8733, 5400, 2573, 65018,
    275, 7975, 7454, 5140, 65521, 59116,
    59617, 58344, 59121, 61698, 4360, 1809,
    3593, 3084, 1036, 1290, 3333, 65022,
    63223, 63723, 60392, 22272,
};
#endif
