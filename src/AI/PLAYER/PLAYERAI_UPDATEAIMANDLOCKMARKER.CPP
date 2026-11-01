#include "TYPES.H"
#include "COMMON/LONE/PARTICLE_COLLISION_PROBE_RESULT.H"
#include "COMMON/VECTOR4F.H"
#include <ultra64.h>
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"

#include "WEAPONS/AIM_TYPES.H"






extern const f32 g_playerAimSpringAcceleration;
extern const f32 g_playerAimSpringDamping;
extern const f32 g_playerAimProbeDistance;
extern const f32 g_playerAimLockProbeDistance;
extern const f32 g_playerAimLockDelay;
extern const f32 g_playerAimProbeRadius;
extern const f32 g_playerAimTargetSpringScale;
extern const f32 g_playerAimTargetHeightScale;
extern f32 g_frameElapsedTime;
extern AimHit *g_collisionCurrentActor;
extern char g_playerCollisionProbe;
extern void *g_weaponInfoByType[];
void CopyMatrix(f32 *, f32 *);
void Player_BuildPlayerViewTransform(void *, f32 *);
void Player_GetPlayerViewTranslation(void *, f32 *);
s32 CCollision_SweepPoint(char *, CVector3, CVector3, s32);
void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);
void Graphu64_AddVec3(CVector3 *, CVector3 *, CVector3 *);
void Graphu64_ScaleVector(CVector3 *, CVector3 *, f32);
f32 Gu_Sqrtf(f32);
void Player_BuildAimMarkerMatrices(struct SharedPlayer *, CVector3 *, CVector3 *);
CQuatern Playerai_ComputeAimRotation(void *, AimActor **, void *);
CQuatern Gobjinst_BuildActorAimQuaternion(char *);
typedef struct TargetLockAttackerView TargetLockAttackerView;
typedef struct TargetLockTargetView TargetLockTargetView;
s32 Playerai_CanLockTarget(TargetLockAttackerView *, TargetLockTargetView *);
f32 Gobjinst_GetActorHeight(void *);
void Playerai_UpdateAimAndLockMarker(AimPlayer *player) {
    AimOutput aimResult;
    CVector3 localForward;
    CVector3 smoothOffset;
    CVector3 desired;
    f32 matrix[16];
    CVector3 current;
    CQuatern aimRotation;
    AimWeapon *weapon;
    AimOutput probeLow;
    CQuatern probeHigh;
    CVector3 direction;
    AimActor *lockedTarget, *probeTarget;
    CVector3 *aimOffsetOutput, *smoothPosition, *outputPosition, *unusedAimOffset, *smoothVelocity, *outputVelocity;
    f32 smoothingFactor, springAcceleration, springDamping, hitDistance, lockElapsed, targetSwitchDelay, initialLockDelay;
    s16 selectedWeapon, unusedWeaponVariant;
    s32 aimIcon;
    s32 unusedWeaponFlags, allowFallbackLock, lockedIcon;
    AimActor *rayHitActor, *target;
    AimView *view;
    lockedTarget = NULL;
    view = player->view;
    springAcceleration = g_playerAimSpringAcceleration;
    springDamping = g_playerAimSpringDamping;
    if (view) { switch (view->mode) { case 1: Player_BuildPlayerViewTransform(player, matrix); Player_GetPlayerViewTranslation(player, &current.x); break; default: CopyMatrix(matrix, view->matrix); current = view->origin; break; } } else { Player_BuildPlayerViewTransform(player, matrix); Player_GetPlayerViewTranslation(player, &current.x); }
    localForward.x = 0.0f;
    localForward.y = 0;
    localForward.z = g_playerAimProbeDistance;
    Graphu64_TransformPoint(matrix, &localForward, &desired);
    if (CCollision_SweepPoint((char *)player, current, desired, (s32) &g_particleCollisionProbeResult) != 0) {
        player->aim = g_collisionCurrentActor->point;
        player->normal = g_collisionCurrentActor->normal;
        player->target = g_collisionCurrentActor->actor;
    } else {
        player->aim = desired;
        player->target = NULL;
    }
    localForward.x = 0.0f;
    localForward.y = 0;
    localForward.z = g_playerAimLockProbeDistance;
    Graphu64_TransformPoint(matrix, &localForward, &desired);
    if (player->enabled != 0) {
        if ((CCollision_SweepPoint((char *)player, current, desired, (s32) &g_playerCollisionProbe) != 0) && (rayHitActor = g_collisionCurrentActor->actor, (rayHitActor != NULL))) {
            if (rayHitActor->kind == 1) {
                if (rayHitActor->flags & 0x300000) {
                    Graphu64_SubtractVectors((CVector3 *)&aimRotation, &rayHitActor->pos, &player->worldPosition);
                    hitDistance = Gu_Sqrtf((aimRotation.x * aimRotation.x) + (aimRotation.y * aimRotation.y) + (aimRotation.z * aimRotation.z));
                    direction = localForward;
                    Graphu64_NormalizeVec3(&direction);
                    Graphu64_ScaleVector(&probeLow.xyz, &direction, hitDistance);
                    Graphu64_TransformPoint(matrix, &probeLow.xyz, (CVector3 *)&probeHigh);
                    player->aim2 = (*(CVector3 *)&probeHigh);
                    Player_BuildAimMarkerMatrices((void *)player, (CVector3 *)&probeHigh, &g_collisionCurrentActor->normal);
                } else {
                    goto block_14;
                }
            } else {
                goto block_15;
            }
        } else {
block_14:
block_15:
            player->aim2 = player->aim;
            Player_BuildAimMarkerMatrices((void *)player, &player->aim, &g_collisionCurrentActor->normal);
        }
    } else {
        player->aim2 = desired;
    }
    if (player->selectedWeapon == 1 && player->weaponActionMode == 2) {
        aimIcon = 710;
    } else {
        weapon=g_weaponInfoByType[player->selectedWeapon]; aimIcon=weapon->idle;
    }
    selectedWeapon = player->selectedWeapon;
    lockedIcon = aimIcon + 100;
    allowFallbackLock = 1;
    if ((selectedWeapon == 1) || (selectedWeapon == 18)) {
        targetSwitchDelay = g_playerAimLockDelay;
        initialLockDelay = targetSwitchDelay;
    } else {
        targetSwitchDelay = 0.0f;
        initialLockDelay = 0.0f;
    }
    switch (player->selectedWeapon) {
    case 7:
        if (player->alternateAimMode != 0) {
            aimIcon = 740;
            lockedIcon = -1;
        }
        break;
    case 2:
        if (player->alternateAimMode != 0) {
            aimIcon = 700;
            lockedIcon = -1;
        }
        break;
    case 1:
    case 18:
        aimRotation = Playerai_ComputeAimRotation(player, &lockedTarget, &aimResult.words);
        allowFallbackLock = 0;
        break;
    default:
        lockedIcon = -1;
        break;
    }
    aimRotation = Gobjinst_BuildActorAimQuaternion((char *)player);
    player->rotation = aimRotation;
    probeLow.xyz = player->aim;
    probeLow.xyz.x -= g_playerAimProbeRadius;
    (*(CVector3 *)&probeHigh) = player->aim;
    (*(CVector3 *)&probeHigh).x += g_playerAimProbeRadius;
    probeLow.xyz = player->aim;
    probeLow.xyz.z -= g_playerAimProbeRadius;
    (*(CVector3 *)&probeHigh) = player->aim;
    (*(CVector3 *)&probeHigh).z += g_playerAimProbeRadius;
    probeLow.xyz = player->aim;
    probeLow.xyz.y -= g_playerAimProbeRadius;
    (*(CVector3 *)&probeHigh) = player->aim;
    (*(CVector3 *)&probeHigh).y += g_playerAimProbeRadius;
    if (lockedTarget == NULL) {
        aimResult.xyz = desired;
        if ((player->controller->active != 0) && (allowFallbackLock != 0)) {
            probeHigh = Playerai_ComputeAimRotation(player, &probeTarget, &probeLow.words);
            if (probeTarget != NULL) {
                player->rotation = probeHigh;
            }
        }
        if (lockedTarget == NULL) {
            player->lockedTarget = NULL;
        }
    }
    if (aimIcon == -1) {
        player->lockState = 0;
    } else if (player->lockState == 0) {
        player->lockState = 1;
        player->out = desired;
        player->velocity.x = 0;
        player->velocity.y = 0;
        player->velocity.z = 0;
        player->smooth = desired;
        player->smoothVelocity.x = 0;
        player->smoothVelocity.y = 0;
        player->smoothVelocity.z = 0;
    }
    smoothPosition = &player->smooth;
    smoothingFactor = g_playerAimTargetSpringScale;
    Graphu64_SubtractVectors(&smoothOffset, &aimResult.xyz, smoothPosition);
    Graphu64_ScaleVector(&smoothOffset, &smoothOffset, springAcceleration * smoothingFactor);
    smoothVelocity = &player->smoothVelocity;
    Graphu64_AddVec3(smoothVelocity, smoothVelocity, &smoothOffset);
    Graphu64_AddVec3(smoothPosition, smoothPosition, smoothVelocity);
    Graphu64_ScaleVector(smoothVelocity, smoothVelocity, springDamping * smoothingFactor);
    if (lockedTarget != NULL) {
        weapon=g_weaponInfoByType[player->selectedWeapon]; player->lockedAimModelResource=weapon->locked+100;
    } else {
        player->lockedAimModelResource = lockedIcon;
    }
    switch (player->lockState) {
    case 1:
        if ((lockedTarget == NULL) || (player->lockedTarget != lockedTarget)) {
            player->lockedTarget = lockedTarget;
            player->lockTimer = 0.0f;
        }
        lockElapsed = player->lockTimer + g_frameElapsedTime;
        player->lockTimer = lockElapsed;
        if (initialLockDelay <= lockElapsed) {
            player->lockState = 2;
            player->lockTimer = 0.0f;
        }
        goto reset_position;
    case 2:
            if (player->candidateTarget != lockedTarget) {
                player->candidateTarget = lockedTarget;
                player->lockTimer = 0.0f;
            } else {
                player->lockTimer += g_frameElapsedTime;
            }
            if ((lockedTarget != NULL) && (player->lockedTarget != lockedTarget) && (targetSwitchDelay <= player->lockTimer)) {
                player->lockedTarget = lockedTarget;
                player->lockTimer = 0.0f;
            }
            target = player->lockedTarget;
            lockedTarget = target;
            if (target != NULL) {
                if (Playerai_CanLockTarget((void *)player, (void *)target) == 0) {
                    player->lockState = 1;
                    player->lockTimer = 0.0f;
                }
                if (player->selectedWeapon == 18) {
                    aimResult.xyz = lockedTarget->focus;
                } else {
                    aimResult.xyz = lockedTarget->pos;
                    aimResult.xyz.y = aimResult.xyz.y + lockedTarget->height;
                    aimResult.xyz.y += Gobjinst_GetActorHeight(lockedTarget) * g_playerAimTargetHeightScale;
                }
                if (player->selectedWeapon == 1 && player->weaponActionMode == 2) {
                    aimIcon = 711;
                } else {
                    weapon=g_weaponInfoByType[player->selectedWeapon]; aimIcon=weapon->locked;
                }
            } else {
                goto reset_position;
            }
        break;
    case 0:
reset_position:
        aimResult.xyz = desired;
        break;
    default:
        break;
    }
    aimOffsetOutput = &smoothOffset;
    outputPosition = &player->out;
    Graphu64_SubtractVectors(aimOffsetOutput, &aimResult.xyz, outputPosition);
    Graphu64_ScaleVector(&smoothOffset, &smoothOffset, springAcceleration);
    outputVelocity = &player->velocity;
    Graphu64_AddVec3(outputVelocity, outputVelocity, &smoothOffset);
    Graphu64_AddVec3(outputPosition, outputPosition, outputVelocity);
    Graphu64_ScaleVector(outputVelocity, outputVelocity, springDamping);
    player->aimModelResource = (s32) aimIcon;
}
