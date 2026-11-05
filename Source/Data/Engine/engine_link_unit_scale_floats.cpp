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

float g_engineLinkUnitScaleFloats[3] = {
    1.0f, 1.0f, 1.0f,
};
#endif
