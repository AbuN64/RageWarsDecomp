#include "include_asm.h"
#include "COMMON/WORLD.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/FIELD_VEC_B0.H"
#include "TYPES.H"
#include "COMMON/APPROACHLOCATION.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "GAME/CCOLLISION_COPYPOSITIONANDGETMODELFLAGS.H"

/* Tests target visibility against range and horizontal and vertical angles; volatile zero accesses and identical normalization branches preserve scheduling and register allocation. */





extern f32 Gobjinst_GetActorHeight(ActorBarrelIsTargetInViewCone *);
extern f32 Gu_Sqrtf(f32);
extern CQuatern Gobjinst_BuildActorAimQuaternion(ActorBarrelIsTargetInViewCone *);
extern void MatrixFromQuaternion(f32 *q, f32 *m);

s32 Cbarrel_IsTargetInViewCone(ActorBarrelIsTargetInViewCone *viewer, ActorBarrelIsTargetInViewCone *target, f32 range, f32 across, f32 up)
{
  CVector3 from;
  CVector3 to;
  CVector3 dir;
  CVector3 ahead;
  CVector3 forward;
  CVector3 flatDir;
  CVector3 flatForward;
  CVector3 pitchDir;
  CVector3 pitchForward;
  CQuatern rotation;
  Matrix matrix;
  f32 distance;
  f32 dirLength;
  f32 forwardLength;
  f32 angle;
  f32 zero;
  from = viewer->position;
  from.y += viewer->eye;
  from.y += Gobjinst_GetActorHeight(viewer) * 0.9f;
  to = target->position;
  to.y += target->eye;
  to.y += Gobjinst_GetActorHeight(target) * 0.9f;
  Graphu64_SubtractVectors(&dir, &to, &from);
  distance = Gu_Sqrtf(((dir.x * dir.x) + (dir.y * dir.y)) + (dir.z * dir.z));
  if (range < distance)
  {
    return 0;
  }
  rotation = Gobjinst_BuildActorAimQuaternion(viewer);
  MatrixFromQuaternion(&rotation, &matrix);
  ahead.x = 0.0f;
  ahead.y = 0.0f;
  ahead.z = distance;
  Graphu64_TransformPoint(&matrix, &ahead, &forward);
  across *= 0.5f;
  up *= 0.5f;
  flatDir.x = dir.x;
  flatDir.y = 0.0f;
  zero = *((volatile f32 *) (&flatDir.y));
  flatDir.z = dir.z;
  dirLength = Gu_Sqrtf((flatDir.x * flatDir.x) + (flatDir.z * flatDir.z));
  if (dirLength != zero)
  {
    if (across)
    {
      flatDir.x /= dirLength;
      flatDir.z /= dirLength;
    }
    else
    {
      flatDir.x /= dirLength;
      flatDir.z /= dirLength;
    }
  }
  flatForward.x = forward.x;
  flatForward.y = zero;
  flatForward.z = forward.z;
  forwardLength = Gu_Sqrtf((flatForward.x * flatForward.x) + (flatForward.z * flatForward.z));
  if (forwardLength != zero)
  {
    flatForward.x /= forwardLength;
    flatForward.z /= forwardLength;
  }
  angle = Graphu64_ArcCos(((flatDir.x * flatForward.x) + (flatDir.y * flatForward.y)) + (flatDir.z * flatForward.z));
  if (angle < zero)
  {
    angle = -angle;
  }
  if (across < angle)
  {
    return 0;
  }
  *((volatile f32 *) (&pitchDir.x)) = 0.0f;
  pitchDir.z = dirLength;
  pitchDir.y = dir.y;
  Graphu64_NormalizeVec3(&pitchDir);
  *((volatile f32 *) (&pitchForward.x)) = 0.0f;
  pitchForward.z = forwardLength;
  pitchForward.y = forward.y;
  Graphu64_NormalizeVec3(&pitchForward);
  angle = Graphu64_ArcCos(((pitchDir.x * pitchForward.x) + (pitchDir.y * pitchForward.y)) + (pitchDir.z * pitchForward.z));
  if (up < ((angle < 0.0f) ? (-angle) : (angle)))
  {
    return 0;
  }
  return 1;
}

s32 Cbarrel_UpdateTrackerAim(TrackerAimActorView *actor, Plan *tracker, TrackerAimActorView *candidate) {
    CVector3 pos,hit;
    s32 room;
    f32 unusedAimValue;
    TrackerAimActorView *unusedAimActor;
    s32 resolvedRoom;
    s32 targetKind;
    s32 unusedAimState;
    ApproachLocation *approachLocation;
    Runtime *runtime;

    if (tracker->aimTargetFlag == 0) {
        targetKind = 6;
    } else if (candidate == 0) {
        targetKind = 3;
        if (tracker->routeCursor != 0) {
            targetKind = 4;
        }
    } else {
        targetKind = 2;
        if (candidate != tracker->currentTarget) {
            if (*candidate->definition == 5) targetKind=5;
            else if(candidate->objectId==1615) targetKind=7;
            else {
                targetKind=0;
                if(!g_world.visibilityEnabled) {
                    if((!(candidate->flags&0x300000) || candidate->player->target!=actor || (targetKind=1,candidate->player->weaponState!=2)) && (!(actor->targetFlags&2) || (targetKind=1,actor->objectId==202))) targetKind=0;
                }
            }
        }
    }
    switch (targetKind) {
    case 6:
        pos = actor->pos;
        room = actor->room;
        break;
    case 4:
        approachLocation = Playerai_GetRouteCursorPoint(&tracker->routeCursor);
        pos = approachLocation->pos;
        room = approachLocation->room;
        break;
    case 3:
        pos = tracker->pos;
        room = tracker->aimRoom;
        break;
    case 7:
        approach(actor,candidate,tracker->approachTarget,&pos,&room);
        break;
    case 1:
        resolvedRoom = CCollision_CopyPositionAndGetModelFlags(actor, tracker->collisionMask, candidate->pos, candidate->room, tracker->probeParams->flagWord, &pos);
        room = resolvedRoom;
        if (resolvedRoom == 0) {
        default:
            pos = candidate->pos;
            room = candidate->room;
        }
        break;
    }
    if (CCollision_CopyProbePosition(actor, pos, room, tracker->probeParams->flagWord, &hit) != 0) {
        if (Region_IsPointInTriangleXZ(actor->room, hit.x, hit.z) != 0) {
            tracker->aimHeight = hit.y;
        } else {
            tracker->aimHeight = (f32) (hit.y + k_barrelTargetAimOffsets[0]);
        }
        Graphu64_SubtractVectors(&hit, &hit, &actor->pos);
        tracker->aimYaw = (f32) (Graphu64_GetHorizontalAngle(&hit) + k_barrelTargetAimOffsets[1]);
        return 1;
    }
    if (targetKind == 1) {
        tracker->aimHeight = pos.y;
        tracker->aimYaw = (f32) (actor->heading + Barrel_GetSignedAngleToPoint(actor, pos));
        return 1;
    }
    return 0;
}

typedef struct CollisionInfo CollisionInfo;
extern f32 g_barrelInitialBestTargetDistance;
extern CollisionInfo g_defaultProbeMotionSettings;
extern ActorInstanceHeader *g_currentActorInstance;
extern char g_playerViewRenderContext[];
extern s32 Cinema_IsSequenceInWindow(void);
extern s32 Cinema_GetSequenceRequest(void);
extern BarrelAnchorActorView *Playerai_FindNearestLivePlayer(void *players, CVector3 point, void *exclude);
extern BarrelAnchorActorView *Playerai_FindNearestPlayer(void *players, CVector3 point);
extern s32 InstHdr_FindActorModelEntry(void *actor);
extern f32 Barrel_GetEyeDistanceSquared(void *candidate, CVector3 point);
extern f32 Barrel_GetFlatDistanceSquared(void *candidate, CVector3 point);
extern s32 Insthdr_HasActorTerritory(void *actor);
extern f32 InstHdr_GetActorTerritoryRadius(void *actor);
extern s32 CCollision_SweepPoint(void *actor, CVector3 from, CVector3 to, CollisionInfo *info);

/* The two player-record fields the picker reads from a found player (lives 0x5EA, state 0x650). */
typedef struct CombatPlayerView {
    u8 pad0[0x5EA];
    s16 lives;
    u8 pad5EC[0x650 - 0x5EC];
    s16 state;
} CombatPlayerView;

/* Picks the best target for an actor: the tracker's locked target (0x78) if it has one, otherwise
 * gathers up to two candidates (the tracker's own entry at 0x68 and the nearest player found around the
 * actor), keeps the nearest within g_barrelInitialBestTargetDistance that passes the territory/visibility tests
 * (Cbarrel_UpdateTrackerAim_CbarrelSelectcombattarget and a line-of-sight probe through CCollision_SweepPoint when requested), and remembers the
 * actor's position as the tracker's home when nothing qualified. */
BarrelAnchorActorView *Cbarrel_SelectCombatTarget(BarrelAnchorActorView *actor, Tracker *tracker, s32 lineOfSight,
                                                   s32 combat) {
    BarrelAnchorActorView *candidates[128];
    ActorInstanceHeader saved;
    CVector3 target;
    BarrelAnchorActorView *best;
    BarrelAnchorActorView *candidate;
    f32 bestDistance;
    f32 distance;
    s32 count;
    s32 ok;
    s32 i;
    s32 blocked;

    if (tracker->lockedTarget != 0) {
        if (combat != 0) {
            Cbarrel_UpdateTrackerAim((TrackerAimActorView *)actor, (Plan *)tracker,
                             (TrackerAimActorView *)tracker->lockedTarget);
        }
        return tracker->lockedTarget;
    }
    count = 0;
    best = 0;
    ok = 1;
    if (Cinema_IsSequenceInWindow() != 0) {
        ok = 0;
        if (Cinema_GetSequenceRequest() >= 10) {
            ok = Cinema_GetSequenceRequest() < 61;
        }
    }
    if (ok != 0) {
        if (combat != 0) {
            candidate = tracker->self;
            if (candidate != 0) {
                candidates[count++] = candidate;
            }
        }
        if ((actor->kind[1] & 0x400) == 0) {
            if ((actor->flags100 & 0x300000) != 0) {
                candidate = Playerai_FindNearestLivePlayer(g_playerViewRenderContext, actor->pos, actor->controller);
            } else {
                candidate = Playerai_FindNearestPlayer(g_playerViewRenderContext, actor->pos);
            }
            if (candidate != 0) {
                /* i and best are both reset again before the loop */
                i = 1;
                if (((CombatPlayerView *)candidate)->lives != 0 && ((CombatPlayerView *)candidate)->state != 1) {
                    if (InstHdr_FindActorModelEntry(candidate) != 0) {
                        best = candidate;
                    } else {
                        i = 0;
                    }
                    if (candidate != 0) {
                        candidates[count++] = candidate;
                    }
                }
            }
        }
        bestDistance = g_barrelInitialBestTargetDistance;
        best = 0;
        for (i = 0; i < count; i++) {
            candidate = candidates[i];
            distance = Barrel_GetEyeDistanceSquared(candidate, actor->pos);
            if (!(distance < bestDistance)) {
                continue;
            }
            if (combat != 0) {
                if (actor->kind[0] == 1 && tracker->targetingDisabled == 0) {
                    continue;
                }
                if (Insthdr_HasActorTerritory(actor) != 0) {
                    f32 reach = Barrel_GetFlatDistanceSquared(candidate, tracker->homePos);
                    f32 range = InstHdr_GetActorTerritoryRadius(actor);
                    if (range * InstHdr_GetActorTerritoryRadius(actor) <= reach) {
                        continue;
                    }
                }
                if (Cbarrel_UpdateTrackerAim((TrackerAimActorView *)actor, (Plan *)tracker,
                                     (TrackerAimActorView *)candidate) == 0) {
                    continue;
                }
            }
            if (lineOfSight != 0) {
                saved = *(ActorInstanceHeader *)actor;
                actor->pos.y += Gobjinst_GetActorHeight((ActorBarrelIsTargetInViewCone *)actor);
                actor->pos.y += candidate->height;
                target = candidate->pos;
                target.y += Gobjinst_GetActorHeight((ActorBarrelIsTargetInViewCone *)candidate);
                target.y += candidate->height;
                blocked = CCollision_SweepPoint(actor, actor->pos, target, &g_defaultProbeMotionSettings);
                if (g_currentActorInstance == (ActorInstanceHeader *)candidate) {
                    blocked = 0;
                }
                *(ActorInstanceHeader *)actor = saved;
                if (blocked != 0) {
                    continue;
                }
            }
            bestDistance = distance;
            best = candidate;
        }
    }
    if (combat != 0 && best == 0 &&
        Cbarrel_UpdateTrackerAim((TrackerAimActorView *)actor, (Plan *)tracker, 0) == 0) {
        tracker->homePos = actor->pos;
        tracker->homeRoom = actor->room;
    }
    return best;
}

