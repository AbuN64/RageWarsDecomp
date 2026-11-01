#ifndef AI_ENEMIES_TURRETAI_H
#define AI_ENEMIES_TURRETAI_H
#include "COMMON/OBJ.H"
extern int Turret_Anim_ACTIVATE(struct Owner *owner);
extern void Turret_Construct(struct ItemMenuSelectionView *owner, struct TurretSetupState *record);
extern void Turret_SpecialEffects(void *actor, ActorEffectEventView *event);
extern CQuatern CVector3_GetDirectionRotation2(CVector3*dir);
extern f32 k_turretInitialSpeeds;
extern s32 Turret_BuildPlaneRot(s32 out, s32 actor, struct RotationObject*rotation);

void Barrel_ApplyClampedTurn(void *actor, s32 unused1, f32 turnLimit, f32 desiredTurn);

void Barrel_UpdateTrackGoals(BarrelTrackActorView *actor, void *trackerState, BarrelTargetInfo *targetInfos, s32 updateTrackedTarget, s32 updateAnchorTarget);
#endif
