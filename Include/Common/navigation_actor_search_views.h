#ifndef COMMON_NAVIGATION_ACTOR_SEARCH_VIEWS_H
#define COMMON_NAVIGATION_ACTOR_SEARCH_VIEWS_H
#include <PR/abi.h>
#include "Common/audio_callbacks.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/runtime_declarations.h"
#include "Common/argb_color.h"
#include <platform_sdk.h>
#include "Common/multiplayeroptions.h"
#include "Common/loadout.h"
#include "Common/virtual_pager.h"
#include "Common/group.h"
#include "Common/object_instance_transform_and_render_views.h"
#include "Common/manager.h"
#include "Common/cartridgereadworker.h"
#include "Common/audio_voice_slots.h"
#include "Common/soundvoicepool.h"
#include "Common/lightdata.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Common/mtx.h"
#include "Common/particle_attachment_and_owner_views.h"
#include "Common/colorentry.h"
#include "Common/worldsortentry.h"
#include "Common/results.h"
#include "Common/round_session.h"
#include "Common/menu_screen_elements.h"
#include "Common/hud_effects.h"
#include "Common/albank_s.h"
#include "Common/sequence_timing.h"
#include "Common/alparam_s.h"
#include "Common/audio_effect_chain.h"
#include "Common/ospihandle_s.h"
#include "Common/osviscale.h"
#include "Common/ctx.h"
#include "Common/audio_loaddecodedsamples.h"
#include "Common/cheatcode.h"
#include "Common/note_state.h"
#include "Common/frontend_video_mode.h"
#include "Common/archive_chunk_images.h"
#include "Common/texture.h"
#include "Common/label.h"
#include "Common/player_join_requests.h"
#include "Common/characterselectionroot.h"
#include "Common/menu_initializeoptionsscene.h"
#include "Common/weapon_unlock_presets.h"
#include "Common/resultsoptionsscreen.h"
#include "Common/match_settings.h"
#include "Common/menu_model_preview.h"
#include "Common/player_item_inventory.h"
#include "Common/objb.h"
#include "types.h"
#include "Common/measured.h"
#include "Common/unresolved_word_access_set.h"
#include "Common/unresolved_word_accesses.h"
#include "Common/measured_storage.h"
#include "Common/navigation_node_and_route_views.h"




struct Actor1DC;
extern float g_pickupCategoryNodeCost;

struct NavigationActorSearchStateView;
struct NavigationActorSearchStateView {
    char pad0[0x1454];
    char * resourceKeyRecord;
};


struct NavigationActorSearchStateView;
typedef struct NavigationActorSearchStateView NavigationActorSearchStateView;



struct Actor1DC;
typedef struct Actor1DC Actor1DC;




struct NavigationActorListEntryView;
typedef struct NavigationActorListEntryView NavigationActorListEntryView;




struct Actor1DC;
struct Actor1DC {
    char pad0[0x1D8];
    char **info;
};





struct NavigationRouteControllerView;
struct NavigationRouteControllerView {
    char pad0[4];
    s32 currentNode;
    char pad8[4];
    s32 requestedGoalNode;
    s32 destinationNode;
    s32 links[4]; /* 0x14 */
    char pad24[4];
    s32 committed; /* 0x28 */
    char pad2C[0x1BC - 0x2C];
    s32 linkState;
    s32 selection;
    char pad1C4[0x2F4 - 0x1C4];
    s32 releaseFlags[3];
};



struct NavigationRouteControllerView;
typedef struct NavigationRouteControllerView NavigationRouteControllerView;







extern float g_navigationNodeTickCostScale;







extern float g_linkedActorNodeDefaultCost;

struct NavigationActorListEntryView;
struct NavigationActorListEntryView {
    unsigned char padding_0[60];
    struct Actor1DC *actor;
};




extern s32 Weapon_PickRandomArmedWeapon(void *player);
typedef struct WeaponSelectionDefinition {
    u8 reserved0[0x8C];
    s32 ammoGroups[3][8];
} WeaponSelectionDefinition;
#endif
