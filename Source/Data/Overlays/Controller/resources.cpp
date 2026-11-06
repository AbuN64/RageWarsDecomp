#include "types.h"
#include "Ai/Nav/ballistic.h"
#include "Data/Actor_state_callbacks/actor_state_callback_labels.h"
#include "Ai/Nav/weaponselect.h"
#include "Ai/Nav/Attacktarget/attacktarget.h"
#include "Ai/Nav/routecost.h"
#include "Data/Ovl1_c/navigation_callback_address.h"
#include "Resources/nav_behavior_callback_rows.h"
#include "Fx/target.h"
#include "Ai/Nav/nav_selectpickupgoal.h"
#include "Linktables/actor_handler_run1_us_rev1_data.h"
#include "Ai/Nav/Patrol/patrol.h"
#include "Ai/Nav/targetfollow.h"
#include "Ai/Nav/roam.h"
#include "Ai/Nav/combat.h"
#include "Ai/Nav/nav_initpursuitstrafe.h"
#include "Ai/Nav/combatinit.h"
#include "Ai/Nav/nav_updaterangedcombat.h"
#include "Ai/Nav/nav_updateclosecombat.h"
#include "Ai/Nav/farthest.h"
#include "Ai/Nav/objectchase.h"
#include "Ai/Nav/nav_resetobjectarrivalchase.h"
#include "Ai/Nav/carrier.h"
#include "Ai/Nav/jumproute.h"

/* G_NAVREFINEBALLISTICAIMCALLBACKREFINEBALLISTICAIM.CPP */


/* G_RESOURCESENCODEDWORDSBLOCK65.CPP */


/* G_NAVROUTETHENENEMYTARGETSCALLBACKS.CPP */


/* G_RESOURCESENCODEDWORDSBLOCK24.CPP */


/* G_RESOURCESENCODEDWORDSBLOCK23.CPP */


/* G_RESOURCESENCODEDWORDSBLOCK3.CPP */


/* G_NAVSELECTPLAYERSTATECALLBACKSELECTPLAYERSTATE.CPP */


/* G_NAVPICKUPGOALCALLBACKS.CPP */


/* G_RESOURCESENCODEDWORDSBLOCK47.CPP */


/* G_NAVSELECTSECONDAMMOGROUPVARIANTTWOCALLBACKSELECTSECONDAMMOGROUPVARIANTTWO.CPP */


/* G_RESOURCESENCODEDWORDSBLOCK50.CPP */


/* G_RESOURCESENCODEDWORDSBLOCK54.CPP */


/* G_NAVCLOSEATTACKPICKUPGOALCALLBACKS.CPP */


/* G_TARGETUPDATETARGETSELECTIONCALLBACKUPDATETARGETSELECTION.CPP */


/* G_NAVSELECTPLAYERSTATECALLBACKS.CPP */


/* G_RESOURCESENCODEDWORDSBLOCK5.CPP */


/* G_NAVCHASEOBJECTGOALCALLBACKS.CPP */


/* G_RESOURCESENCODEDWORDSBLOCK14.CPP */


/* G_RESOURCESENCODEDWORDSBLOCK32.CPP */


/* G_RESOURCESENCODEDWORDSBLOCK52.CPP */


/* G_NAVSTATIONARYOBJECTGOALCALLBACKS.CPP */


/* G_NAVROUTEONLYCALLBACKS.CPP */


/* G_NAVFINALROUTETHENENEMYTARGETSCALLBACKS.CPP */


/* G_RESOURCESENCODEDWORDSBLOCK48.CPP */


/* G_RESOURCESENCODEDWORDSBLOCK58.CPP */


/* G_RESOURCESENCODEDWORDSBLOCK53.CPP */


/* G_NAVSELECTPLAYERSTATECALLBACK.CPP */


/* K_ACTORHANDLERANDNAVGOALPOINTERS.CPP */


/* CONTROLLER_STATES.CPP: nav controller states 1-11 in id order, each its enter and update handlers then its tuning words. */
#if defined(VERSION_US_REV1)
typedef struct NavControllerStateRecord {
    s32 id;
    void * enter;
    void * update;
    u32 reserved[2];
    f32 scale;
    s32 threshold;
    u32 flags;
} NavControllerStateRecord;

NavControllerStateRecord g_navControllerStateRecords[11] __attribute__((aligned(4))) = {
    { 1, (void *)&Nav_InitTargetFollowing, (void *)&Nav_UpdateTargetRouteFollow, { 0x00000000, 0x00000000 }, 1.0f, 5, 0x00000000 },
    { 2, (void *)&Nav_InitRoamingWithJumps, (void *)&Nav_UpdateRoamingWithJumps, { 0x00000000, 0x00000000 }, 1.0f, 5, 0x00000000 },
    { 3, (void *)&Nav_InitPursuitStrafe, (void *)&Nav_UpdatePursuitStrafe, { 0x00000000, 0x00000000 }, 1.0f, 5, 0x00000000 },
    { 4, (void *)&Nav_InitRangedCombat, (void *)&Nav_UpdateRangedCombat, { 0x00000000, 0x00000000 }, 1.0f, 5, 0x00000000 },
    { 5, (void *)&Nav_InitCloseCombat, (void *)&Nav_UpdateCloseCombat, { 0x00000000, 0x00000000 }, 1.0f, 5, 0x00000000 },
    { 6, (void *)&Nav_InitCombatTargetApproach, (void *)&Nav_ApproachCombatTargetAlongRoute, { 0x00000000, 0x00000000 }, 1.0f, 5, 0x00000000 },
    { 7, (void *)&Nav_InitRetreatMovement, (void *)&Nav_UpdateRetreatMovement, { 0x00000000, 0x00000000 }, 1.0f, 5, 0x00000000 },
    { 8, (void *)&Nav_ResetObjectArrivalChase, (void *)&Nav_UpdateObjectArrivalChase, { 0x00000000, 0x00000000 }, 1.0f, 5, 0x00000000 },
    { 9, (void *)&Nav_InitUnclaimedMarkerSearch, (void *)&Nav_SeekUnclaimedMarker, { 0x00000000, 0x00000000 }, 1.0f, 5, 0x00000000 },
    { 10, (void *)&Nav_InitCarrierRoute, (void *)&Nav_FollowMarkerCarrierRoute, { 0x00000000, 0x00000000 }, 1.0f, 5, 0x00000000 },
    { 11, (void *)&Nav_InitTimedJumpRoute, (void *)&Nav_UpdateTransientJumpRoute, { 0x00000000, 0x00000000 }, 1.0f, 5, 0x00000000 },
};
typedef char g_navControllerStateRecordsSizeCheck[(sizeof(g_navControllerStateRecords) == 0x160) ? 1 : -1];

/* Nav controller state 12, seek a nearby unrestricted goal; its tuning words open the player controller block that follows. */
struct {
    s32 id;
    void * enter;
    void * update;
} g_navNearbyGoalStateHandlers __attribute__((aligned(4))) = { 12, (void *)&Nav_InitNearbyUnrestrictedGoal, (void *)&Nav_SeekNearbyUnrestrictedGoal };
#endif
