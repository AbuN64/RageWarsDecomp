#if defined(VERSION_EU_X)

#include "Common/output.h"


#include "Engine/events.h"


#include "Engine/Anim/compressed_motion.h"


#include "include_asm.h"


#include "Common/group.h"


#include "Common/sharedplayer.h"


#include "Common/level_actor.h"


#include "Common/access_s8_10f.h"


#include "Engine/Instance/gobjinst.h"


#include "Common/shared_particleinstance.h"


#include "Common/aiprofile.h"


#include "types.h"


#include "Engine/gregion.h"


#include "Gobjinst/gameobject_movetoxzkeepheight.h"


#include "Graphu64/graphu64_getangledistance.h"


#include "Common/approachlocation.h"


#include "Common/runtime_declarations.h"


#include "Common/weapon_screen_message_operations.h"


#include "Camera/collision_sweep_views.h"


#include "Common/world.h"


#include "Common/Lone/particle_collision_probe_result.h"


#include "Common/vector4f.h"


#include "Common/particle_lighting.h"


#include "Scene/cache_allocateresourceat.h"


#include "Common/listheader.h"


#include "Scene/cache_requestresource.h"


#include "Render/setn64_getpacksection.h"


#include "Engine/lists.h"


#include "Actor/actor.h"


#include "Engine/defs.h"


#include "Engine/scene_drawopaqueactors.h"


#include "Gobjinst/gameobject_loadmodel.h"


#include "Libsn/nav_isballisticarcobstructed_data.h"


#include "Particle/graphu64_matrixfromeulerxyz.h"


#include "Common/level_spawn.h"


#include "Gobjinst/gobjinst_data.h"


#include "Common/object_instance_transform_and_render_views.h"


#include "Common/resident_event_handler.h"


#include "Common/ppdecom_unpackresource.h"


#include "Common/material_tree.h"


#include <platform_sdk.h>


#include "Game/builddirectionmatrix.h"


#include "Engine/session.h"


#include "Link/link_dispatchmatchingtriggers.h"


#include "Insthdr/insthdr_getactorshadowradius.h"


#include "Common/ballisticparams.h"


#include "System/contact_effect.h"


#include "Common/actorresourceheader.h"


#include "Rsp/random_direction_and_affine_math.h"


#include "Common/gameplay_round_rules.h"


#include "Common/gameplay_transition.h"


#include "Common/animation_pool.h"


#include "Engine/Instance/gastate_advancerootmotion_data.h"


#include "Fx/normalize_vector.h"


#include "Ai/Enemies/turretai.h"


#include "Ai/Player/player_buildplayerviewtransform.h"


#include "Gobjinst/gobjinst_requestanimatedmodelvariant.h"


#include "Graphu64/graphu64_packfixedmatrix.h"


#include "System/events_delivercontacteffect.h"


#include "Gastate/GAState.h"


#include "Common/gameplay_camera.h"


#include "Common/game_session.h"


#include "Common/unsigned_quotient.h"


#include "Common/shared_gameslot.h"


#include "Engine/ghot.h"


#include "Engine/visdata_decoderegiongrid.h"


#include "Fx/fx_drawboundedparticlequads.h"


#include "Gobjinst/gobjinst_buildactorpose.h"


#include "Graphu64/graphu64_buildlookatmatrix.h"


#include "Menu/Items/Scene/scene_registeractorinscenelists.h"


#include "Common/os_timer_interrupt_internals.h"


#include "Common/viewflags.h"


#include <PR/gbi.h>


#include "Common/sessionhandlerrow.h"


#include "Common/weapon_marker_and_profile_views.h"


#include "System/textload_resettexturecache.h"


#include "Gobjinst/gastate_advancerootmotion_data.h"


#include "Render/material_color_and_fog_views.h"


#include "Common/model_render.h"


#include "Common/frag_tag_scores.h"


#include "Particle/particle_spawneffectgroup.h"


#include "Gobjinst/player_drawtintedplayer_data.h"


#include "Particle/ghot_dispatchattachmenteffects_data.h"


#include "Common/propgeometry.h"


#include "Particle/particle_releaseownerlistoneeffects.h"


#include "Common/triple.h"


#include "Engine/link.h"


#include "Engine/Instance/Gobjinst/gobjinst_drawteammaskedmodel.h"


#include "Common/math_helpers.h"


#include "Engine/gdynlight.h"


#include "Engine/Instance/gobjinst_getactoroffsetpositionandmodel.h"


#include "Engine/Instance/simpinst.h"


#include "Engine/Instance/Simpinst/simpinst_drawgroundshadow.h"


#include "Engine/Instance/gobjinst_initializeplacedactor.h"


#include "Engine/scene_drawtransitioncoloroverlay.h"


#include "Gobjinst/gobjinst_findnearestbonebounds.h"


#include "Gobjinst/gobjinst_buildactortransform.h"


#include "Gobjinst/gobjinst_buildtargetaimorientation.h"


#include "Gobjinst/gobjinst_packaffinematrixwords.h"


#include "Common/legacy_collision_actor.h"


#include "Cbarrel/barrel_spawnactoreffect.h"


#include "common.h"


#include "Common/localdecoderange.h"


#include "Common/mtx.h"


#include "Engine/Instance/Gobjinst/actor_animation_root_and_event_operations.h"


#include "Polytrak2/polytrak2_samplerotationtrack.h"


#include "Common/shared_worldfunc.h"


#include "Common/probe.h"


#include "Gobjinst/gameobject_getactorheight.h"


#include "Actors/lighting_buildlitmodel.h"


#include "Cache/cache.h"


#include "Common/obj.h"


#include "Ai/Player/player_getammocapacity.h"


#include "Engine/Instance/Gobjinst/gobjinst_buildtargetaimorientation.h"


#include "Common/format.h"


#include "data_overlay_layouts.h"


#include "Data/Overlays/Credits/linktables_addresses.h"


#include "Data/rest_source_records.h"


#include "Engine/Instance/Gobjinst/sndplayer.h"


#include "Ai/cbarrel.h"


#include "Engine/Cache/cache.h"




typedef struct Shared_PoseJointRef Shared_PoseJointRef;


struct Shared_PoseJointRef {
    s16 pos;
    s16 rot;
};


typedef struct Shared_PoseDefaultFrame Shared_PoseDefaultFrame;


struct Shared_PoseDefaultFrame {
    CVector3 pos;
    s16 rot[4];
};


typedef struct Shared_PoseTrack Shared_PoseTrack;


struct Shared_PoseTrack {
    Shared_PoseJointRef *joints;
    Shared_PoseDefaultFrame *frames;
    void *posTable;
    void *rotTable;
    s32 rotFrame0;
    s32 rotFrame1;
    s32 posFrame0;
    s32 posFrame1;
    f32 blend;
};


typedef struct Shared_PoseFlags Shared_PoseFlags;


struct Shared_PoseFlags {
    s32 frame;
    s32 blend;
    s32 mode;
};


typedef struct Shared_FrameProfile Shared_FrameProfile;


struct Shared_FrameProfile {
    u64 start;
    u32 unknown08[2];
    s32 frame;
    s32 prevCount;
    s32 count;
    u32 reservedWord;
    f32 prev;
    f32 cur;
    f32 avg;
};


typedef f32 PoseMatrix[4][4];


typedef void (*PoseCallback)(PoseMatrix, Shared_PoseContext *);


typedef struct SceneModelRef {
    u8 pad0[0x1C];
    u32 viewMask;
} SceneModelRef;


typedef struct SceneObject SceneObject;


typedef struct DrawContext {
    s32 visible;
    s32 hasSecond;
    struct GameplayCamera *camera;
    void *first;
    void *second;
    f32 *offset;
    s32 pad;
} DrawContext;


struct SceneObject {
    u8 pad0;
    s8 firstKey;
    s8 secondKey;
    u8 pad3[0x11];
    SceneModelRef *model;
    u8 pad18[0x5C];
    f32 transform[16];
    u8 padB4[0xC];
    Gfx *cached;
    s32 resource;
    u8 padC8[8];
    s32 resourceFlags;
    u8 padD4[0x14];
    Box bounds;
    u32 flags;
    u8 pad104[0x6C];
    s32 behaviorFlags;
    u8 pad174[0x108];
    void (*draw)(SceneObject *, void *, DrawContext *);
    u8 pad280[0xC];
    void (*update)(SceneObject *, void *);
};





typedef struct InteractionDescriptor { s32 kind; char pad4[0x10]; s32 flags; } InteractionDescriptor;


typedef struct InteractionLink { char pad0[0x1C]; s32 flags; char pad20[0x83C]; s32 linked; } InteractionLink;


typedef struct InteractionActor {
    u8 kind; char pad1[0x17]; InteractionDescriptor *descriptor;
    char pad1C[0xE4]; s32 flags; char pad104[0x9C]; InteractionLink *attached;
    char pad1A4[0x34]; InteractionLink *player;
} InteractionActor;

char k_GobjinstPackaffinematrixwordsEncodedBytes[12] =
    ":\240\000\000\077\\(\365\077fff";
#endif
