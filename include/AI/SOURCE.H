#ifndef AI_SOURCE_H
#define AI_SOURCE_H
#include <PR/abi.h>
#include "COMMON/AUDIO_CALLBACKS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ACTOR_DEFINITION.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ARGB_COLOR.H"
#include <ultra64.h>
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/LOADOUT.H"
#include "COMMON/OWNERRECAT8V2.H"
#include "COMMON/GROUP.H"
#include "COMMON/OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS.H"
#include "COMMON/MANAGER.H"
#include "COMMON/CARTRIDGEREADWORKER.H"
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/SOUNDVOICEPOOL.H"
#include "COMMON/LIGHTDATA.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/MTX.H"
#include "COMMON/PARTICLE_ATTACHMENT_AND_OWNER_VIEWS.H"
#include "COMMON/COLORENTRY.H"
#include "COMMON/WORLDSORTENTRY.H"
#include "COMMON/RESULTS.H"
#include "COMMON/OBJRECAT26DD8.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/OBJRECAT18V6.H"
#include "COMMON/ALBANK_S.H"
#include "COMMON/OBJRECAT18V1.H"
#include "COMMON/ALPARAM_S.H"
#include "COMMON/ALDELAY28.H"
#include "COMMON/OSPIHANDLE_S.H"
#include "COMMON/OSVISCALE.H"
#include "COMMON/CTX.H"
#include "COMMON/AUDIO_LOADDECODEDSAMPLES.H"
#include "COMMON/CHEATCODE.H"
#include "COMMON/ENTRYRECAT0V3.H"
#include "COMMON/NODERECAT2A8.H"
#include "COMMON/SLOTRECATCV1.H"
#include "COMMON/TEXTURE.H"
#include "COMMON/LABEL.H"
#include "COMMON/REQUESTRECAT10.H"
#include "COMMON/CHARACTERSELECTIONROOT.H"
#include "COMMON/MENU_INITIALIZEOPTIONSSCENE.H"
#include "COMMON/STATERECAT91.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "COMMON/SETTINGSRECAT24.H"
#include "COMMON/OBJECTRECAT28.H"
#include "COMMON/PLAYERRECAT64E.H"
#include "COMMON/OBJB.H"
#include "TYPES.H"
#include "COMMON/MEASUREDRECAT0V1.H"
#include "COMMON/MEASURED.H"
#include "COMMON/MEASUREDRECAT14V4.H"
#include "COMMON/MEASUREDRECAT14V2.H"
#include "COMMON/SHAREDPLAYER.H"
extern float g_actorDefaultLevelPair;

extern double g_actorKindOneUnsignedHealthBias;

extern double g_actorKindFourUnsignedHealthBias;

extern float g_timedJumpRouteArrivalDistance;

extern float g_actorSceneMaskTwentySecondaryLevel;

struct AiTarget;




struct Source;
struct Source {
    u8 pad0;
    s8 first; /* +0x1..0x3: copied from the definition by Actor_ApplyActorDefinition */
    s8 second;
    s8 send;
    u8 pad4[4];
    CVector3 position;
    void *surface; /* +0x14: Actor_InitSpawnedActor ground query */
    ActorDefinitionHeader *definition;
    CVector3 velocity;
    u8 pad28[0x10];
    s32 flags38;
    u8 pad3c[0x30];
    f32 height;
    u8 reserved070[0x90];
    u32 flags; /* +0x100; probe 20261019T012702233005Z */
};

extern int g_navigationNodeCount;

extern float g_actorSceneMaskTwentyHealthScale;

struct NavigationChaseResetView;
struct NavigationChaseResetView {
    unsigned char padding_0[104];
    s32 target;
    unsigned char padding_6C[436];
    s32 resetWord220;
    unsigned char padding_224[20];
    s32 arrived;
};

extern float g_actorSceneMaskEightHealthLimits;



struct NavigationChaseResetView;
typedef struct NavigationChaseResetView NavigationChaseResetView;



struct Source;
typedef struct Source Source;



extern f32 InstHdr_GetActorTargetHeight(u8 *player);
#endif
