#include "Data/rom_callback_word.h"
#ifndef AI_NAV_SYMBOLS_H
#define AI_NAV_SYMBOLS_H
#include "types.h"
struct AiController;
extern f32 Scaled_DistanceToNode(struct AiController *controller, s32 nodeId);
#include "types.h"
struct CNavData_t;
extern void Nav_AddGoalNode(struct CNavData_t *obj, int id);
#include "types.h"
struct AiController;

#include "types.h"
struct CNavData_t;

#include "Engine/Instance/gobjinst.h"
#include "types.h"
#include "Common/navigation_graph.h"
/* Globals and functions placed by the symbol map; no C definition exists. */
typedef s32 (*Handler)(void *aiController);
#include "Common/ccollisionsetup_t.h"
#if !defined(VERSION_US)
extern RomCallbackWord *g_aiCharacterBehaviorTables[];
#endif
extern char ACTOR_TABLE_A;
extern char ACTOR_TABLE_B;
extern char g_tlbMissExceptionVector[];
extern f32 g_navigationRetreatDistanceLimit;
extern f32 g_playerSteeringAirForward;
extern f32 g_playerSteeringAscendingPoseForward;
extern f32 g_playerSteeringDescendingPoseForward;
extern f32 g_playerSteeringFallForward;
extern f32 g_playerSteeringAirPitchForward;
extern f32 g_targetSteeringAirForward;
extern f32 g_targetSteeringAscendingPoseForward;
extern f32 g_targetSteeringDescendingPoseForward;
extern f32 g_targetSteeringFallForward;
extern f32 g_targetSteeringAirPitchForward;
/* Code labels placed by the symbol map; no C definition exists. */
struct AiController;
struct CNavData_t;
struct CVector3_t;
struct Graph;
struct NavigationSearchNode;
struct Player;
struct PlayerAimBrainView;

extern s32 Nav_SelectPlayerState(struct AiController *controller);
extern void Nav_SteerAlongRoute(struct AiController *controller);
extern f32 Nav_SteerTowardPoint(struct PlayerAimBrainView *brain, struct CVector3_t *target, f32 rate, f32 offset);
extern s32 Portal_FindNearestPointIndex(struct CNavData_t *pointSet, void *point);
extern void Portal_UpdateActorCurrentNode(struct CNavData_t *graph, struct Player *actor);
extern s32 Scaled_HasLineOfSight(struct Player **fromRef, struct Player *target);
extern f32 Scaled_ScaleCharacterSettingByDifficulty(struct AiController *controller);
extern s32 Scaled_SetBehaviourState(struct AiController *controller, s32 behaviourId);
extern void Wheel_MeasureWheelClearance(struct Player *player, s32 wheel);
extern char Nav_RebuildRequestedGoalRoute_label544[];
extern char Nav_RefineBallisticAim_label336[];
extern char Nav_SelectPickupGoal_label188[];
extern char Nav_SelectPickupGoal_label200[];
extern char Playerai_ApplyLinkedProjectileStatus_label2276[];
extern char Weaponai_UpdateHeldFire_label1064[];
extern char Weaponai_UpdateHeldFire_label744[];
extern char Weaponai_UpdateHeldFire_label752[];
extern char Weapon_FireStateEnterCallbackEntry_label948[];
extern char Weapon_FireStateEnterCallbackEntry_label1120[];
#endif
