#ifndef AI_SOURCE_H
#define AI_SOURCE_H
#include <PR/abi.h>
#include "Common/audio_callbacks.h"
#include "Common/vector4f.h"
#include "Common/actor_definition.h"
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
#include "Common/sharedplayer.h"
#include "Actor/actor.h"
extern float g_actorDefaultLevelPair;

extern double g_actorMovementKindUnsignedHealthBias;

extern double g_actorHealthKindUnsignedHealthBias;

extern float g_timedJumpRouteArrivalDistance;

extern float g_actorSceneMaskSecondaryLevel;

struct AiTarget;





extern int g_navigationNodeCount;

extern float g_actorSceneMaskHealthScale;

struct NavigationChaseResetView;
struct NavigationChaseResetView {
    unsigned char padding_0[104];
    s32 target;
    unsigned char padding_6C[436];
    s32 closeAttackState;
    unsigned char padding_224[20];
    s32 arrived;
};

extern float g_actorSceneMaskHealthLimits;



struct NavigationChaseResetView;
typedef struct NavigationChaseResetView NavigationChaseResetView;



struct Source;
typedef struct Source Source;



extern f32 InstHdr_GetActorTargetHeight(u8 *player);
#endif
