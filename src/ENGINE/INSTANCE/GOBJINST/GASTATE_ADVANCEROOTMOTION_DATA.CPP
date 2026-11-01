#include "COMMON/ACTORRESOURCEHEADER.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"
#include "COMMON/OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS.H"
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/GAMEPLAY_ROUND_RULES.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/OBJRECAT5F14.H"
#include "ENGINE/INSTANCE/GASTATE_ADVANCEROOTMOTION_DATA.H"
#include "GAME/BUILDDIRECTIONMATRIX.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include "AI/ENEMIES/TURRETAI.H"
#include "include_asm.h"

/* GOBJINST_4.CPP */
extern void Gastate_SwitchRequestedAnimation(void *, s32, s32, s32, s32 *, void *);

extern s32 Gastate_IsAnimationResourceRetained(void *);

extern void Gastate_AdvanceRootMotion(void *, CVector3 *, f32 *, void *);

extern void *Gastate_GetAnimationPoseSection(void *);

extern void Graphu64_InterpolateVector(CVector3 *, f32, CVector3 *, CVector3 *);

extern f32 g_frameElapsedTime;

extern char g_actorRotationBlendAndResourceTuning;

/* Fires the effect events of an object's animation that fall within a frame window: only for the object's
 * own animation at 0x104 or an object flagged 0x4000000; each event whose frame lies in [from, to) is
 * placed from its local point through the object's matrix when it names no bone, otherwise through its
 * bone matrix (or at the object's position when it has none), and for models 0x44E, 0x451 and 0x453 an
 * effect flagged 4 fires only if its bone's hit box shares the object's mask; each fired event spawns its
 * effect through Events_DeliverContactEffect_ActorAnimationRootAndEventOperations and is counted in g_actorRootMotionSampleCount. */

extern CROMEventEntry *Gastate_GetAnimationEventEntries(void *);

extern s32 *Gobjinst_RequestAnimatedModelVariant(char *, s8);

extern void Graphu64_ConvertMatrixToFloat(f32 *, char *);

extern void Events_DeliverContactEffect(char *, char *, u16, s32, CVector3, struct IntPair);

/* Returns an actor's aiming orientation: a controlled actor turns a quarter turn about the vertical from its
 * weapon's orientation at 0x140, or from the player's own orientation from Player_BuildPlayerOrientation when unarmed; an
 * actor of kind 4 composes a pitch from 0x294 with a yaw from its heading 0x6C and applies them to its body
 * orientation from Turret_BuildPlaneRot; any other actor turns its orientation at 0x5C by its heading. Quaternions
 * are composed through MultiplyQuaternions, keeping the latest sine in g_turretAimSine. */

extern void MultiplyQuaternions(CQuatern *, CQuatern *, CQuatern *);

extern void Player_BuildPlayerOrientation(void *, CQuatern *);

/* Returns an actor's aim with auto-aim applied: with no assist cone the actor's aiming orientation from
 * Gobjinst_BuildActorAimQuaternion is returned unchanged; otherwise, of the live entities other than the actor (not flagged 1,
 * with a body at 0x174), the one whose aim point (half its height above its top) lies most nearly along the
 * aim direction from the given point, within the cone (in degrees, halved), pulls the aim toward it by an
 * angle that fades with the fourth root of how far off-axis it is. The applied correction is also written
 * to the optional assist quaternion (identity when nothing is in range). */

extern void MatrixFromQuaternion(f32 *q, f32 *m);

extern f32 Gobjinst_GetActorHeight(char *);

extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);

extern void Graphu64_CrossVectors(CVector3 *, CVector3 *, CVector3 *);

extern void Graphu64_ScaleVector(CVector3 *out, CVector3 *in, f32 scale);

/* Sways a model part: from the frame count g_gameFrameCounter, a per-part phase ((flags & 0x38) * 50, plus 40
 * unless flag 4 is set) and the part's time divided by 113, it reads a 120-step sine table at g_actorMatrixWobbleSamples to
 * build a rotation axis and angle for the part's sway mode (2: about a wobbling z/y axis, 0x82: doubled
 * about a wobbling x/y axis, 0x40: doubled about a fully wobbling axis, 1: 0.7 of the swing about y) and
 * applies that rotation to the part's matrix about its own origin; other modes leave it unchanged. */

extern s32 g_gameFrameCounter;

extern void CopyMatrix(f32 *, f32 *);

extern void TranslateMatrix(f32 *, f32, f32, f32);

extern void Graphu64_BuildAxisAngleMatrix(f32 *, f32, f32, f32, f32);

extern void Graphu64_MultiplyAffineMatrices(f32 *, f32 *, f32 *);

const float g_actorRootMotionCubicCoefficients[2] = {
    -2.0f, 3.0f,
};
void Gobjinst_AdvanceActorRootMotion(void *actor) {
    CVector3 first;
    CVector3 second;
    CVector3 saved;
    CVector3 moved;
    MatrixF matrix;
    s32 active;
    f32 first_value;
    f32 second_value;
    void **resource;
    void *track0;
    void *track1;
    f32 value;

    if (g_world.mode == 4) {
        if ((s8)((Actor36 *)actor)->currentTrack.active == 0)
            ((Actor36 *)actor)->currentTrack.blending = 1;
        if ((s8)((Actor36 *)actor)->previousTrack.active == 0)
            ((Actor36 *)actor)->previousTrack.blending = 1;
        if ((s8)((Actor36 *)actor)->currentTrack.active == 0 && !(((Actor36 *)actor)->flags & 0x400))
            return;
        if (!(((Actor36 *)actor)->flags & 0x2000))
            return;
    }

    resource = Cache_RequestResource(0, ((Actor36 *)actor)->animationKey, ((Actor36 *)actor)->animationKey,
        ((((Actor36 *)actor)->animationCount * 4) + 15) & ~7, 4, 0, 0,
        &g_actorRotationBlendAndResourceTuning + 4, 0);
    if (resource == 0)
        return;

    track0 = &((Actor36 *)(actor))->currentTrack;
    track1 = &((Actor36 *)(actor))->previousTrack;
    Gastate_SwitchRequestedAnimation(track0, (s32)*resource, ((Actor36 *)actor)->animationKey, 1, &active, track1);
    if (Gastate_IsAnimationResourceRetained(track0) != 0) {
        void *entry;
        Gastate_AdvanceRootMotion(track0, &first, &first_value, actor);
        value = first_value;
        saved = first;
        if (active != 0 && ((Anim *)track1)->current != -1) {
            u16 count;
            entry = Gastate_GetAnimationPoseSection(track0);
            if (((AnimationBlendEntry *)entry)->frames != 0) {
                ((Actor36 *)actor)->flags |= 0x400;
                count = ((AnimationBlendEntry *)entry)->frames;
                ((Actor36 *)actor)->blendTime = 0.0f;
                ((Actor36 *)actor)->blendFrames = count;
                ((Actor36 *)actor)->blendStart = ((AnimationBlendEntry *)entry)->start;
                ((Actor36 *)actor)->blendEnd = ((AnimationBlendEntry *)entry)->end;
            } else {
                ((Actor36 *)actor)->flags &= ~0x400;
            }
        }
        if (((Actor36 *)actor)->flags & 0x400) {
            Gastate_SwitchRequestedAnimation(track1, (s32)*resource, ((Actor36 *)actor)->animationKey, 0, 0, 0);
            if (Gastate_IsAnimationResourceRetained(track1) != 0) {
                f32 time;
                f32 end;
                time = ((Actor36 *)actor)->blendTime + g_frameElapsedTime;
                end = (f32)((Actor36 *)actor)->blendFrames;
                ((Actor36 *)actor)->blendTime = time;
                if (end < time) {
                    ((Actor36 *)actor)->flags &= ~0x400;
                } else {
                    f32 a = (f32)((Actor36 *)actor)->blendEnd;
                    f32 b = (f32)((Actor36 *)actor)->blendStart;
                    f32 t = time / (end + g_frameElapsedTime);
                    ((Actor36 *)actor)->blend = (((a + g_actorRootMotionBlendCoefficients + b) * t * t * t) +
                        ((((&g_actorRootMotionBlendCoefficients)[1] - a) - (2.0f * b)) * t * t) + (b * t));
                    Gastate_AdvanceRootMotion(&((Actor36 *)(actor))->previousTrack, &second, &second_value, actor);
                    Graphu64_InterpolateVector(&saved, ((Actor36 *)actor)->blend, &second, &first);
                    value = Graphu64_InterpolateWrappedValue(((Actor36 *)actor)->blend, second_value, first_value);
                }
                Gastate_ReleaseAnimationResource(track1);
            } else {
                ((Actor36 *)actor)->flags &= ~0x400;
            }
        }
        Gastate_ReleaseAnimationResource(track0);
        if (((Actor36 *)actor)->flags & 0x20000) {
            ((Actor36 *)actor)->heading -= value;
            Graphu64_WrapPeriodicValue(&((Actor36 *)(actor))->heading);
            saved.z = saved.y;
            saved.y = 0.0f;
            BuildYawMatrix(&matrix, ((Actor36 *)actor)->heading);
            Graphu64_TransformPoint(&matrix, &saved, &moved);
            ((Actor36 *)actor)->position.x += moved.x * ((Actor36 *)actor)->scaleX;
            ((Actor36 *)actor)->position.z += moved.z * ((Actor36 *)actor)->scaleZ;
        } else if (!(((Actor36 *)actor)->flags & 0x300000) && ((Actor36 *)actor)->ownerId == 311) {
            ((Actor36 *)actor)->heading -= value;
            Graphu64_WrapPeriodicValue(&((Actor36 *)(actor))->heading);
        }
    }
    Cache_UnlockResource(0, resource);
}

void Gobjinst_DispatchAnimationIntervalEvents(char *obj, void *anim, f32 from, f32 to) {
    CVector3 pos;
    CVector3 local;
    f32 matrix[16];
    CROMEventEntry *events;
    s32 count;
    s32 i;
    s32 checkMask;
    s32 fire;
    s32 *resource;
    struct ActorAnimationEventTable *table;

    if (!(((struct RootMotionActorView *) obj)->flags & 0x4000000) && anim != &((LevelActor *)obj)->animationTime) {
        return;
    }
    switch (((struct RootMotionActorView *) obj)->type) {
    case 1102:
    case 1105:
    case 1107:
        checkMask = 1;
        break;
    default:
        checkMask = 0;
        break;
    }
    table = 0;
    events = Gastate_GetAnimationEventEntries(anim);
    count = Gastate_GetAnimationEventCount(anim);
    resource = 0;
    for (i = 0; i < count; i++) {
        if (from <= (f32)events[i].frame && (f32)events[i].frame < to) {
            fire = 1;
            if (events[i].bone == -1) {
                local.x = events[i].local.x;
                local.y = events[i].local.z;
                local.z = events[i].local.y;
                Graphu64_TransformPoint(&((LevelActor *)obj)->transform, &local, &pos);
            } else {
                if (checkMask && (g_animationEventEffectDescriptors[events[i].effect].offset & 4)) {
                    if (resource == 0) {
                        resource = Gobjinst_RequestAnimatedModelVariant(obj, ((struct RootMotionActorView *) obj)->team);
                        if (resource == 0) {
                            goto masked;
                        }
                        table = SetN64_GetPackSection(*resource, 5);
                    }
                    fire = ((struct AnimationEventMaskView *) (((char *) table) + ((events[i].bone * table->entrySize) + ((char *)&((struct ActorAnimationEventTable *)0)->records - (char *)0) + ((char *)&((ModelBoneRecord *)0)->eventMask - (char *)0))))->value & ((struct RootMotionActorView *) obj)->boneMask;
                }
            masked:
                if (fire == 0) {
                    continue;
                }
                if (((struct RootMotionActorView *) obj)->previousPoseMatrices != 0) {
                    Graphu64_ConvertMatrixToFloat(matrix, ((struct RootMotionActorView *) obj)->previousPoseMatrices + (events[i].bone << 6));
                    Graphu64_TransformPoint(matrix, &events[i].local, &pos);
                } else {
                    pos = ((struct RootMotionActorView *) obj)->position0;
                }
            }
            if (fire != 0) {
                Events_DeliverContactEffect(obj, obj, events[i].effect, -1, pos, events[i].params);
                g_actorRootMotionSampleCount++;
            }
        }
    }
    if (resource != 0) {
        Cache_UnlockResource(0, resource);
    }
}

CQuatern Gobjinst_BuildActorAimQuaternion(char *actor) {
    CQuatern result;
    CQuatern pitch;
    CQuatern yaw;
    CQuatern both;
    CQuatern base;
    CQuatern own;
    char *player;
    char *weapon;
    f32 angle;
    f32 sine;

    if (((LevelActor *)actor)->flags & 0x300000) {
        player = ((LevelActor *)actor)->controller;
        weapon = ((Shared_ActorView *)player)->message;
        if (weapon != 0) {
            angle = 1.5707964f;
            g_turretAimSine = Gu_Sinf(angle);
            yaw.x = 0.0f;
            yaw.y = g_turretAimSine;
            yaw.z = 0.0f;
            yaw.w = Math_Cosf(angle);
            MultiplyQuaternions(&result, &yaw, &((PlayerCameraTargetView *)weapon)->orientation);
        } else {
            angle = 1.5707964f;
            Player_BuildPlayerOrientation(player, &own);
            g_turretAimSine = Gu_Sinf(angle);
            yaw.x = 0.0f;
            yaw.y = g_turretAimSine;
            yaw.z = 0.0f;
            yaw.w = Math_Cosf(angle);
            MultiplyQuaternions(&result, &yaw, &own);
        }
    } else if (((LevelActor *)actor)->definition->kind == 4) {
        sine = Gu_Sinf(((LevelActor *)actor)->pitch * 0.5f);
        pitch.x = sine;
        pitch.y = 0.0f;
        pitch.z = 0.0f;
        angle = ((LevelActor *)actor)->pitch * 0.5f;
        g_turretAimSine = sine;
        pitch.w = Math_Cosf(angle);
        sine = Gu_Sinf((((LevelActor *)actor)->yaw + 3.1415927f) * 0.5f);
        yaw.x = 0.0f;
        yaw.y = sine;
        yaw.z = 0.0f;
        angle = (((LevelActor *)actor)->yaw + 3.1415927f) * 0.5f;
        g_turretAimSine = sine;
        yaw.w = Math_Cosf(angle);
        MultiplyQuaternions(&both, &pitch, &yaw);
        Turret_BuildPlaneRot(&base, actor, &((LevelActor *)actor)->behaviorFlags);
        MultiplyQuaternions(&result, &both, &base);
    } else {
        sine = Gu_Sinf((((LevelActor *)actor)->yaw + 3.1415927f) * 0.5f);
        yaw.x = 0.0f;
        yaw.y = sine;
        yaw.z = 0.0f;
        angle = (((LevelActor *)actor)->yaw + 3.1415927f) * 0.5f;
        g_turretAimSine = sine;
        yaw.w = Math_Cosf(angle);
        MultiplyQuaternions(&result, &yaw, &((LevelActor *)actor)->rotation);
    }
    return result;
}

CQuatern Gobjinst_BuildAssistedAimQuaternion(char *actor, CVector3 point, CQuatern *assist, f32 cone) {
    CVector3 dir;
    CVector3 local;
    CVector3 aim;
    CVector3 axis;
    CVector3 best;
    CVector3 center;
    CQuatern base;
    CQuatern turn;
    CQuatern result;
    f32 matrix[16];
    char *entity;
    char *target;
    s32 count;
    s32 i;
    f32 bestDot;
    f32 dot;
    f32 angle;

    local.x = 0.0f;
    local.y = 0.0f;
    local.z = 1.0f;
    base = Gobjinst_BuildActorAimQuaternion(actor);
    if (cone == 0.0f) {
        if (assist != 0) {
            assist->x = assist->y = assist->z = 0.0f;
            assist->w = 1.0f;
        }
        return base;
    }
    MatrixFromQuaternion(&base, matrix);
    Graphu64_TransformPoint(matrix, &local, &aim);
    i = 0;
    target = 0;
    bestDot = Math_Cosf(cone * 0.008726647f);
    count = g_world.registeredCount;
    for (; i < count; i++) {
        entity = g_playerAimCandidateActors[i];
        if (entity == actor || (((LevelActor *)(entity))->flags & 1) || ((LevelActor *)(entity))->active == 0) {
            continue;
        }
        center = ((LevelActor *)(entity))->position0;
        center.y += ((LevelActor *)(entity))->eyeHeight;
        center.y += Gobjinst_GetActorHeight(entity) * 0.5f;
        Graphu64_SubtractVectors(&dir, &center, &point);
        Graphu64_NormalizeVec3(&dir);
        dot = aim.x * dir.x + aim.y * dir.y + aim.z * dir.z;
        if (bestDot < dot) {
            bestDot = dot;
            best = dir;
            target = entity;
        }
    }
    if (target != 0) {
        Graphu64_CrossVectors(&axis, &aim, &best);
        Graphu64_NormalizeVec3(&axis);
        angle = Graphu64_ArcCos(bestDot);
        angle *= Gu_Sqrtf(Gu_Sqrtf(1.0f - angle / (cone * 0.008726647f)));
        angle *= 0.5f;
        g_turretAimSine = Gu_Sinf(angle);
        turn.x = axis.x * g_turretAimSine;
        turn.y = axis.y * g_turretAimSine;
        turn.z = axis.z * g_turretAimSine;
        turn.w = Math_Cosf(angle);
        MultiplyQuaternions(&result, &base, &turn);
        if (assist != 0) {
            *assist = turn;
        }
        return result;
    }
    if (assist != 0) {
        assist->x = assist->y = assist->z = 0.0f;
        assist->w = 1.0f;
    }
    return base;
}

void Gobjinst_ApplyImpactBoneTwist(char *actor, char *twistState, char *boneMatrix, CVector3 impactPosition,
                   CVector3 impactDirection, s32 hitBoneIndex) {
    CVector3 twistAxis;
    CVector3 boneOrigin;
    CVector3 perpendicularDirection;
    s32 *modelResource;
    s32 *boneTable;
    s32 ancestorBoneIndex;
    s32 chainSlot;
    char *boneEntry;

    if (twistState[52] != 60) {
      if (twistState[18] < 23) {
       modelResource = Gobjinst_RequestAnimatedModelVariant(actor, actor[1]);
       if (modelResource != 0) {
        boneTable = SetN64_GetPackSection((void *)*modelResource, 5);
        boneEntry = (char *)boneTable + ((hitBoneIndex * *boneTable) + 8);
        ancestorBoneIndex = hitBoneIndex;
        if ((((ModelBoneRecord *)boneEntry)->flags & 3) == 3) {
            Cache_UnlockResource(0, modelResource);
            return;
        }
        chainSlot = 0;
        do {
            *(twistState + chainSlot + ((char *)&((ActorBoneTwistState *)0)->ancestorBones - (char *)0)) = ancestorBoneIndex;
            ancestorBoneIndex = boneEntry[100];
            chainSlot++;
            if (ancestorBoneIndex != -1) {
                boneEntry = (char *)boneTable + ((ancestorBoneIndex * *boneTable) + 8);
            }
        } while (chainSlot < 4);
        Cache_UnlockResource(0, modelResource);
        twistState[18] = 25;
        boneOrigin.x = ((Matrix *)boneMatrix)->m[12];
        boneOrigin.y = ((Matrix *)boneMatrix)->m[13];
        boneOrigin.z = ((Matrix *)boneMatrix)->m[14];
        Graphu64_SubtractVectors(&impactPosition, &impactPosition, &boneOrigin);
        Graphu64_CrossVectors(&twistAxis, &impactPosition, &impactDirection);
        Graphu64_NormalizeVec3(&twistAxis);
        Graphu64_NormalizeVec3(&impactPosition);
        Graphu64_NormalizeVec3(&impactDirection);
        Graphu64_CrossVectors(&perpendicularDirection, &twistAxis, &impactPosition);
        Graphu64_ScaleVector(&twistAxis, &twistAxis,
                      (perpendicularDirection.x * impactDirection.x) + (perpendicularDirection.y * impactDirection.y) +
                          (perpendicularDirection.z * impactDirection.z));
        Graphu64_NormalizeVec3(&twistAxis);
        ((Field_Vec_18 *)(twistState))->value = twistAxis;
       }
      }
    }
}

void Gobjinst_ApplyTimedMatrixWobble(s32 time, s32 flags, f32 *matrix) {
    f32 rotation[16];
    f32 inverse[16];
    CVector3 origin;
    CVector3 axis;
    u32 t;
    f32 angle;
    f32 flip;
    s32 mode;

    t = g_gameFrameCounter;
    t += (flags & 0x38) * 50;
    t += (u32)(time & 0xFFFF) / 113;
    if (!(flags & 4)) {
        t += 40;
    }
    axis.x = 0.0f;
    axis.z = 0.0f;
    axis.y = 1.0f;
    mode = flags & 0xC3;
    if (mode == 2) {
        axis.z = 1.0f;
        axis.x = 0.0f;
        angle = g_actorMatrixWobbleSamples.value[t % 120] - 0.5f;
        axis.y = g_actorMatrixWobbleSamples.value[(t + 12) % 120];
    } else if (mode == 130) {
        axis.x = 1.0f;
        axis.z = 0.0f;
        angle = g_actorMatrixWobbleSamples.value[t % 120] - 0.5f;
        axis.y = g_actorMatrixWobbleSamples.value[(t + 12) % 120];
        angle *= 2.0f;
    } else if (mode == 64) {
        angle = g_actorMatrixWobbleSamples.value[(t + 30) % 120] - 0.5f;
        axis.x = g_actorMatrixWobbleSamples.value[(t + 12) % 120];
        axis.y = g_actorMatrixWobbleSamples.value[(t + 42) % 120];
        axis.z = g_actorMatrixWobbleSamples.value[(t + 110) % 120];
        angle *= 2.0f;
    } else if (mode == 1) {
        angle = g_actorMatrixWobbleSamples.value[(t + 70) % 120] - 0.5f;
        angle *= 0.7f;
    } else {
        return;
    }
    Graphu64_NormalizeVec3(&axis);
    origin.x = matrix[12];
    origin.y = matrix[13];
    origin.z = matrix[14];
    CopyMatrix(inverse, matrix);
    flip = -1.0f;
    Graphu64_ScaleVector(&origin, &origin, flip);
    TranslateMatrix(inverse, origin.x, origin.y, origin.z);
    Graphu64_BuildAxisAngleMatrix(rotation, angle, axis.x, axis.y, axis.z);
    Graphu64_MultiplyAffineMatrices(matrix, inverse, rotation);
    Graphu64_ScaleVector(&origin, &origin, flip);
    TranslateMatrix(matrix, origin.x, origin.y, origin.z);
}

/* 800C8710_23.CPP */

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/AdvanceRootMotionEmptyPoolSection.c */
#endif
