#ifndef COMMON_NAVIGATION_ACTOR_SEARCH_VIEWS_H
#define COMMON_NAVIGATION_ACTOR_SEARCH_VIEWS_H
#include <PR/abi.h>
#include "COMMON/AUDIO_CALLBACKS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
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
#include "COMMON/MEASURED_STORAGE.H"
#include "COMMON/NAVIGATION_NODE_AND_ROUTE_VIEWS.H"




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
    Actor1DC *actor;
};




extern s32 Weapon_PickRandomArmedWeapon(void *player);
typedef struct WeaponSelectionDefinition {
    u8 reserved0[0x8C];
    s32 ammoGroups[3][8];
} WeaponSelectionDefinition;
#endif
