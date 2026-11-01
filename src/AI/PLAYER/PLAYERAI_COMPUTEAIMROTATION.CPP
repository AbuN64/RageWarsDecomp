#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/WORLD.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include <ultra64.h>
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/OBJ.H"
#include "COMMON/RESOURCELOADSTATE.H"
#include "COMMON/TRIPLE.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"

s32 Cbarrel_TestTargetEyeObstruction(void *, void *, void *);
/* Whether the target's view reports an active shield. */
static inline s32 Weapons_TargetShielded(TargetLockTargetView *target) {
    View *view = target->view;
    if (view == NULL) {
        return 0;
    }
    return view->shieldActive != 0;
}
/* Checks whether the player's current weapon can lock onto the target. Kind 0 and 7 targets never lock. */
s32 Playerai_CanLockTarget(TargetLockAttackerView *attacker, TargetLockTargetView *target) {
    s16 weapon;
    s8 mode;
    s32 canLock;

    weapon = attacker->weaponId;
    if (weapon == 18) {
        if (target->renderFlags & 0x300000) {
            if (!(target->definition->flags & 0x20)) {
                return 0;
            }
            mode = target->targetLockState;
            if (mode == 38 || mode == weapon || target->health == 0) {
                return 0;
            }
            if (!Weapons_TargetShielded(target)) {
                return Cbarrel_TestTargetEyeObstruction(attacker, &attacker->targetProbeState, target) == 0;
            }
            return 0;
        }
        if (target->definition->kind == 1) {
            if (!(target->definition->flags & 0x2400)) {
                return 0;
            }
            mode = target->targetLockState;
            if (mode == 33 || mode == 52 || mode == 60 || mode == 61) {
                return 0;
            }
            if (target->health != 0) {
                return Cbarrel_TestTargetEyeObstruction(attacker, &attacker->targetProbeState, target) == 0;
            }
            return 0;
        }
    }
    switch (target->definition->kind) {
    case 4:
        if (target->health != 0) {
            return Cbarrel_TestTargetEyeObstruction(attacker, &attacker->targetProbeState, target) == 0;
        }
        return 0;
    case 0:
    case 7:
        return 0;
    case 11:
        canLock = 0;
        mode = target->targetLockState;
        if (mode != 38 && mode != 18 && target->health != 0 && !Weapons_TargetShielded(target)) {
            canLock = 1;
        }
        return canLock;
    }
    return 0;
}

/* These contiguous globals place the actor-list pointer 0x1285 bytes before the enable flag. */
#include "ENGINE/INSTANCE/GOBJINST_GETACTOROFFSETPOSITIONANDMODEL.H"
struct TargetLockAttackerView;
struct TargetLockTargetView;
extern s32 Playerai_CanLockTarget(TargetLockAttackerView *, TargetLockTargetView *);
extern void Graphu64_CrossVectors(CVector3 *, CVector3 *, CVector3 *);
extern CQuatern Gobjinst_BuildActorAimQuaternion(char *);
extern void MultiplyQuaternions(void *, void *, void *);

CQuatern Playerai_ComputeAimRotation(DraftAimPlayer *player, DraftAimPlayer **target,
                            CVector3 *targetPosition)
{
    CVector3 candidate, direction, origin;
    CVector3 bestPosition;
    CVector3 forward, unit;
    CVector3 bestDirection;
    CVector3 axis;
    CQuatern correction, facing, result;
    DraftAimPlayer *other, *best;
    AimGlobals *globals;
    u8 *enable;
    f32 angle, dot, threshold, half, amount, scale;
    s32 count, i, firstSpecial, secondSpecial;

    bestPosition.x = 0.0f;
    bestPosition.y = 0.0f;
    bestPosition.z = 0.0f;
    bestDirection.x = 0.0f;
    bestDirection.y = 0.0f;
    bestDirection.z = 0.0f;
    result.x = result.y = result.z = bestPosition.x;
    result.w = g_playerAimDefaultRotationW;
    best = 0;
    if (player->weapon != -1) angle = ((DraftAimWeapon *)g_weaponInfoByType[player->weapon])->angle;
    else angle = bestPosition.x;
    threshold = Math_Cosf(angle * g_playerAimConeAngleScale);
    if (angle != 0.0f) {
        unit.x = 0.0f;
        unit.y = 0.0f;
        unit.z = g_playerAimForwardDistance;
        Gobjinst_TransformVectorByActorAim(&forward, player, unit);
        origin = player->position;
        origin.y += Playerai_GetObjectOwnerHeight(player);
        enable = &g_frontendScreenStatus.settings.local;
        if (*enable) {
            other = ((AimGlobals *)(enable - ((char *)&((AimGlobals *)0)->enabled - (char *)0)))->head;
            if (other) {
                firstSpecial = 18;
                scale = g_playerAimPrimaryTurnScale;
                do {
                if (Playerai_CanLockTarget((void *)player, (void *)other) && other != player) {
                    if (player->weapon == firstSpecial) candidate = other->specialAim;
                    else {
                        candidate = other->position;
                        candidate.y += other->height;
                        candidate.y += Gobjinst_GetActorHeight(other) * scale;
                    }
                    Graphu64_SubtractVectors(&direction, &candidate, &origin);
                    Graphu64_NormalizeVec3(&direction.x);
                    dot = forward.x * direction.x + forward.y * direction.y +
                          forward.z * direction.z;
                    if (threshold < dot) {
                        threshold = dot;
                        bestPosition = candidate;
                        best = other;
                    }
                }
                            } while ((other = other->next) != 0);
            }
        }
        count = g_world.registeredCount;
        i = 0;
        if (i < count) {
            secondSpecial = 18;
            scale = g_playerAimSecondaryTurnScale;
            do {
            other = (void *)g_playerAimCandidateActors[i];
            if (Playerai_CanLockTarget((void *)player, (void *)other)) {
                if (player->weapon == secondSpecial) candidate = other->specialAim;
                else {
                    candidate = other->position;
                    candidate.y += other->height;
                    candidate.y += Gobjinst_GetActorHeight(other) * scale;
                }
                Graphu64_SubtractVectors(&direction, &candidate, &origin);
                Graphu64_NormalizeVec3(&direction.x);
                dot = forward.x * direction.x + forward.y * direction.y +
                      forward.z * direction.z;
                if (threshold < dot) {
                    threshold = dot;
                    best = other;
                    bestPosition = candidate;
                    bestDirection = direction;
                }
            }
                        i++;
            } while (i < count);
        }
    }
    *target = best;
    *targetPosition = bestPosition;
    if (best) {
        Graphu64_CrossVectors(&axis, &forward, &bestDirection);
        Graphu64_NormalizeVec3(&axis.x);
        scale = g_playerAimFallbackTurnScale;
        threshold = Graphu64_ArcCos(threshold);
        amount = Gu_Sqrtf(g_playerAimTurnRootBase - threshold / (angle * scale));
        amount = Gu_Sqrtf(amount);
        threshold *= amount;
        threshold *= scale;
        amount = Gu_Sinf(threshold);
        correction.x = axis.x * amount;
        correction.y = axis.y * amount;
        correction.z = axis.z * amount;
        g_turretAimSine = amount;
        correction.w = Math_Cosf(threshold);
        facing = Gobjinst_BuildActorAimQuaternion((char *)player);
        MultiplyQuaternions(&result, &facing, &correction);
    }
    return result;
}
