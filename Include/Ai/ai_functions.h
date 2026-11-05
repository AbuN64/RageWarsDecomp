#ifndef AI_AI_FUNCTIONS_H
#define AI_AI_FUNCTIONS_H
#include "types.h"
#include "Common/actorrec.h"
#include "Common/brain.h"
#include "Common/gameplay_transition.h"
struct Player;
#include "Common/level_actor.h"
#include "Common/measured_storage.h"
#include "Common/navigation_actor_search_views.h"
#include "Common/route_chase_records.h"
#include "Common/runtime_declarations.h"
#include "Common/self.h"
#include "Common/vector4f.h"
struct Brain;
struct NavigationSearchNode;
struct RouteChaseActor;
struct ActorRec;
struct CloseAttackActor;
struct LevelActor;
struct MovingPlatformActorView;
struct MovingPlatformMotionStateView;
struct NavigationRouteControllerView;
struct PatrolActor;
struct Result;
struct Rider;
struct Shared_Actor;
struct TurretRiderTargetView;
struct WeaponFireState;
/* AI functions referenced by address from dispatch tables in the AI slice. */
int Nav_SelectSecondAmmoGroupVariantOne(void *controller);
int Nav_SelectSecondAmmoGroupVariantTwo(void *controller);
int Nav_SelectWeaponFromFirstAmmoGroup(void *controller);
int Nav_SelectWeaponFromSecondAmmoGroup(void *controller);
int Nav_SelectWeaponFromThirdAmmoGroup(void *controller);
s32 Nav_CheckCloseAttackRoute(struct Brain *brain);
struct AiController;
s32 Nav_CollectEnemyTargets(struct AiController *brain);
s32 Nav_RebuildRequestedGoalRoute(void *controller);
s32 Nav_RefineBallisticAim(struct ActorRec *actor);
s32 Nav_UpdateRouteIntermediateGoal(struct NavigationRouteControllerView *owner);
void Nav_InitCloseCombat(struct CloseAttackActor *actor);
void Nav_UpdateObjectArrivalChase(struct RouteChaseActor *actor);
void Nav_UpdatePatrolRoute(struct PatrolActor *actor);
void Nav_UpdatePursuitStrafe(struct Player *actor);
void Playerai_BeginRoundEndWait(struct Player *widget);
void Playerai_EnterMovingSequenceState(void *player, void *body);
void Playerai_EnterStoppedSequenceState(void *player, void *body);
void Playerai_InitializeActorModelEffect(void *effectPlayerState, void *sourceActor);
void Playerai_RequestLifeRegenerationTrack(s32 requestValue);
void Playerai_StartSwimmingRaptorChestbursterDeathSequence(void *player, void *sequenceActor);
void Playerai_UpdateRoundEndViewAngles(s32 player, s32 body);
void Playerai_UpdateRunEndTransition(void *runEndPlayer);
void Weapon_AdvanceSpinAndTriggerMode(struct WeaponActorStateView *actor, void *attack);
void Weapon_InitializeChargeAndLoopSound(struct Player *actorView, struct WeaponFireState *fireState);
void Weapon_ResetControllerAndSpin(struct LevelActor *actor, struct WeaponFireState *fireState);
void Weapon_ApplySwitchAndSetSingleRound(void *part, struct WeaponSwitchActionView *body);
void Weapon_UpdateIdleWeaponSelection(struct LevelActor *levelActor, void *weaponFireState);
void Weapon_UpdateTriggerReleaseState(void *actor, void *attack);
void Weaponai_SelectReleasedFireState(struct WeaponActorStateView *actor, void *stateController);
void Weaponai_UpdateAfterAmmoModeChange(struct LevelActor *levelActor, void *weaponSlot);
void Weaponai_UpdateAlternateFire(void *actor, void *attack);
void Weaponai_UpdateHeldFire(struct Shared_Actor *actor, struct WeaponFireState *attack);
void Weaponai_UpdateSpinAndAlternateFire(struct Shared_Actor *actor, struct WeaponFireState *fire);
/* Functions defined in other modules or placed by the symbol map, declared once for the AI slice. */
struct AiController;
struct Graph;
void AI_DynTurretGetTargetInfo(struct SharedPlayer *player, struct TurretRiderTargetView *rider, struct Result *result);
s32 Cbarrel_TestTargetEyeObstruction(void *, void *, void *);
f32 Menu_MeasureLine(u8 *p, f32 sx, f32 sy);
void Player_BuildAimMarkerMatrices(struct SharedPlayer *, CVector3 *, CVector3 *);
void Player_ResetPlayerForRound(void *, s32, s32);
struct TransientDamagePlayerView;
struct TransientPlayerDamagePacket;
void Playerai_CreditDamageSource(struct TransientDamagePlayerView *damagedPlayer, struct TransientPlayerDamagePacket *damagePacket);
void *Playerai_GetRouteCursorNextPoint(struct Cursor *);
f32 Rumble_SamplePackedFloatRange(s32 packedRange);
void Triggered_PositionPlatformRider(struct MovingPlatformActorView *, struct MovingPlatformMotionStateView *);
void Turret_Move(struct Owner *owner, struct Rider *rider, s32 mode, struct SharedPlayer *target);
s32 XPlus_NextRandomInteger(void);
/* Navigation functions defined in the AI slice and called across its files. */
struct CNavData_t;
struct NavigationSearchNode;
void Portal_SearchPath(CNavData *graph, struct NavigationSearchNode *start);
struct CNavData_t;
int Portal_FindLinkIndex(struct CNavData_t *graph, int from, int to);
#endif
