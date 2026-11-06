#include "Common/output.h"
#include "Common/aiprofile.h"
#include "Common/level_actor.h"
#include "include_asm.h"
#include "Common/world.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "types.h"
#include "Common/approachlocation.h"
#include "Fx/normalize_vector.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Game/ccollision_copypositionandgetmodelflags.h"
#include "Ai/Player/player_getammocapacity.h"
#include "Cbarrel/barrel_spawnflaggedeffects.h"
#include "Cbarrel/cbarrel_selectcombattarget.h"
#include "Insthdr/insthdr_getactorshadowradius.h"
#include "Engine/Instance/insthdr.h"
#include "Engine/Cinema/cinema.h"
#include "Game/builddirectionmatrix.h"
#include "Engine/Unicol/unicol.h"
#include "Engine/Instance/Gobjinst/gastate_advancerootmotion_data.h"
#include "Gobjinst/gameobject_getactorheight.h"
#include "Common/ballisticparams.h"
#include "Common/triple.h"
#include "Ai/ai_shared_symbols.h"
#include "Menu/pak_load.h"
#include "Rsp/random_direction_and_affine_math.h"
#include "Common/math_helpers.h"
#include "Ai/cbarrel.h"
#include "Cbarrel/cbarrel_resolvetrackgoal_data.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Ai/Playerai/playerai_playerai.h"
#include "Ai/Cbarrel/barrel_getsignedangletopoint.h"
#include "Ai/barrel_getfacingside.h"
#include <platform_sdk.h>
#include "Common/probe.h"
#include "Engine/Instance/gobjinst_getactoroffsetpositionandmodel.h"
#include "Engine/Instance/gobjinst.h"
#include "Common/shared_gameslot.h"
#include "Common/rendercounters.h"
#include "Common/runtime_declarations.h"
#include "Particle/particle_spawneffectgroup.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/rec.h"
#include "Actor/actor_updateactorstateanimation.h"
#include "Actor/nav_applysupportingplatformmotion.h"
#include "Cbarrel/barrel_spawnactoreffect.h"
#include "Engine/ghot.h"
#include "Particle/ghot_dispatchattachmenteffects_data.h"
#include "World/barrel_spawnactoreffect_data.h"
#include "Common/listheader.h"
#include "Engine/lists.h"
#include "Common/route_chase_records.h"
#include "Common/gameplay_transition.h"
#include "Common/multiplayeroptions.h"
#include "Libsn/nav_isballisticarcobstructed_data.h"
#include "Ai/cbarrel_resolvetrackgoal.h"
#include "Common/funcptr.h"
#include "Common/audio_voice_slots.h"
#include "Common/soundvoicepool.h"
#include "Common/menu_model_preview.h"
#include "Weapons/barrel_geteyedistancesquared.h"
#include "Menu/teammenu.h"
#include "Audio/voice.h"
#include "Engine/Audio/Voice/voice.h"
#include "Gobjinst/gameobject_loadmodel.h"

typedef struct CAIMovementInfo {
    CVector3 first;
    CVector3 first_normalized;
    f32 first_length;
    CVector3 flat;
    CVector3 flat_normalized;
    f32 flat_length;
    f32 height;
} CAIMovementInfo;
typedef struct CActor_t {
    u8 type;
    u8 pad001[0x1B];
    CVector3 position;
    u8 pad028[0xBC];
    u16 objectId;
    u8 pad0E6[0x10A];
    s32 eventValue;
    u8 pad1F4[0xA8];
    s32 eventCount;
} CActor_t;
typedef struct BarrelWordPair {
    int words[2];
} BarrelWordPair;
typedef struct Location {
    CVector3 pos;
    s32 room;
    f32 heading; /* 0x10 */
    u16 flags; /* 0x14 */
} Location;
typedef struct BarrelSequenceCursor {
    void *base;
    u16 *cur;
} BarrelSequenceCursor;
typedef struct SourceBarrelUpdateActorController {
    char pad0[8];
    Triple position;
    char pad14[4];
    s32 *kind;
    char pad1c[0x50];
    f32 height;
    char pad70[0x90];
    s32 flags;
    char pad104[0x98];
    s32 active;
} SourceBarrelUpdateActorController;
typedef struct DestBarrelUpdateActorController {
    char pad0[0x40];
    f32 value;
    char pad44[4];
    Triple old_position;
    Triple position;
    f32 height;
    char pad64[0x69];
    u8 timer;
    char padce[0x2E];
    CompactOptionsPageView *aux;
    char pad100[8];
    void (*callback)(SourceBarrelUpdateActorController *, struct DestBarrelUpdateActorController *);
} DestBarrelUpdateActorController;
typedef struct CTeamSelectTeam_t {
    s32 reservedWord0;
    s32 reservedWord4;
    f32 x;
    f32 y;
    f32 z;
} CTeamSelectTeam;
struct DamagePacketWords { s32 source, damage, radiusBits, damageFlags, shield; };

/* Tests target visibility against range and horizontal and vertical angles; volatile zero accesses and identical
 * normalization branches preserve scheduling and register allocation. */



s32 Cbarrel_IsTargetInViewCone(LevelActor *viewer, LevelActor *target, f32 range, f32 across, f32 up)
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
  from = viewer->position0;
  from.y += viewer->eyeHeight;
  from.y += Gobjinst_GetActorHeight(viewer) * 0.9f;
  to = target->position0;
  to.y += target->eyeHeight;
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

s32 Cbarrel_UpdateTrackerAim(LevelActor *actor, Plan *tracker, LevelActor *candidate) {
    CVector3 pos,hit;
    s32 room;
    f32 unusedAimValue;
    LevelActor *unusedAimActor;
    s32 resolvedRoom;
    s32 targetKind;
    s32 unusedAimState;
    ApproachLocation *approachLocation;
    Player *runtime;

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
            if (candidate->definition->kind == 5) targetKind=5;
            else if(candidate->type==1615) targetKind=7;
            else {
                targetKind=0;
                if(!g_world.visibilityEnabled) {
                    if((!(candidate->flags&0x300000) || ((Player *)candidate->controller)->controllerOwner!=actor || (targetKind=1,((Player *)candidate->controller)->controllerMode!=2)) && (!(actor->renderFlags&2) || (targetKind=1,actor->type==202))) targetKind=0;
                }
            }
        }
    }
    switch (targetKind) {
    case 6:
        pos = actor->position0;
        room = actor->model;
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
        approach(actor, candidate, tracker->approachTarget, &pos, &room);
        break;
    case 1:
        resolvedRoom = CCollision_CopyPositionAndGetModelFlags(actor, tracker->collisionMask, candidate->position0, candidate->model, tracker->probeParams->flagWord, &pos);
        room = resolvedRoom;
        if (resolvedRoom == 0) {
        default:
            pos = candidate->position0;
            room = candidate->model;
        }
        break;
    }
    if (CCollision_CopyProbePosition(actor, pos, room, tracker->probeParams->flagWord, &hit) != 0) {
        if (Region_IsPointInTriangleXZ(actor->model, hit.x, hit.z) != 0) {
            tracker->aimHeight = hit.y;
        } else {
            tracker->aimHeight = (f32) (hit.y + k_barrelTargetAimOffsets[0]);
        }
        Graphu64_SubtractVectors(&hit, &hit, &actor->position0);
        tracker->aimYaw = (f32) (Graphu64_GetHorizontalAngle(&hit) + k_barrelTargetAimOffsets[1]);
        return 1;
    }
    if (targetKind == 1) {
        tracker->aimHeight = pos.y;
        tracker->aimYaw = (f32) (actor->yaw + Barrel_GetSignedAngleToPoint(actor, pos));
        return 1;
    }
    return 0;
}

typedef struct CollisionInfo CollisionInfo;


/* The nearest-player queries return entries in the shared player list. */

/* Picks the best target for an actor: the tracker's locked target if it has one, otherwise
 * gathers up to two candidates (the tracker's own entry and the nearest player found around the
 * actor), keeps the nearest within g_barrelInitialBestTargetDistance that passes the territory/visibility tests
 * (Cbarrel_UpdateTrackerAim_CbarrelSelectcombattarget and a line-of-sight probe through CCollision_SweepPoint when requested), and remembers the
 * actor's position as the tracker's home when nothing qualified. */
LevelActor *Cbarrel_SelectCombatTarget(LevelActor *actor, Tracker *tracker, s32 lineOfSight,
                                                   s32 combat) {
    LevelActor *candidates[128];
    struct ActorInstanceHeader saved;
    CVector3 target;
    LevelActor *best;
    LevelActor *candidate;
    f32 bestDistance;
    f32 distance;
    s32 count;
    s32 ok;
    s32 i;
    s32 blocked;

    if (tracker->lockedTarget != 0) {
        if (combat != 0) {
            Cbarrel_UpdateTrackerAim((LevelActor *)actor, (Plan *)tracker,
                             (LevelActor *)tracker->lockedTarget);
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
        if ((actor->definition->gate & 0x400) == 0) {
            if ((((LevelActor *)actor)->flags & 0x300000) != 0) {
                candidate = Playerai_FindNearestLivePlayer(&g_playerViewRenderContext, actor->position0, actor->controller);
            } else {
                candidate = Playerai_FindNearestPlayer(&g_playerViewRenderContext, actor->position0);
            }
            if (candidate != 0) {
                /* i and best are both reset again before the loop */
                i = 1;
                if (((SharedPlayer *)candidate)->views5E8.view5EA_3.respawns != 0 && ((SharedPlayer *)candidate)->views5E8.view650_16.state != 1) {
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
            distance = Barrel_GetEyeDistanceSquared(candidate, actor->position0);
            if (!(distance < bestDistance)) {
                continue;
            }
            if (combat != 0) {
                if (actor->definition->kind == 1 && tracker->targetingDisabled == 0) {
                    continue;
                }
                if (Insthdr_HasActorTerritory(actor) != 0) {
                    f32 reach = Barrel_GetFlatDistanceSquared(candidate, tracker->homePos);
                    f32 range = InstHdr_GetActorTerritoryRadius(actor);
                    if (range * InstHdr_GetActorTerritoryRadius(actor) <= reach) {
                        continue;
                    }
                }
                if (Cbarrel_UpdateTrackerAim((LevelActor *)actor, (Plan *)tracker,
                                     (LevelActor *)candidate) == 0) {
                    continue;
                }
            }
            if (lineOfSight != 0) {
                saved = *(struct ActorInstanceHeader *)actor;
                actor->position0.y += Gobjinst_GetActorHeight((LevelActor *)actor);
                actor->position0.y += candidate->eyeHeight;
                target = candidate->position0;
                target.y += Gobjinst_GetActorHeight((LevelActor *)candidate);
                target.y += candidate->eyeHeight;
                blocked = CCollision_SweepPoint(actor, actor->position0, target, &g_defaultProbeMotionSettings);
                if (g_currentActorInstance.instance0 == (LevelActor *)candidate) {
                    blocked = 0;
                }
                *(struct ActorInstanceHeader *)actor = saved;
                if (blocked != 0) {
                    continue;
                }
            }
            bestDistance = distance;
            best = candidate;
        }
    }
    if (combat != 0 && best == 0 &&
        Cbarrel_UpdateTrackerAim((LevelActor *)actor, (Plan *)tracker, 0) == 0) {
        tracker->homePos = actor->position0;
        tracker->homeRoom = actor->model;
    }
    return best;
}



struct Cursor;




extern void InstHdr_CopyActorPositionAndModel(LevelActor *levelActor, CVector3 pos, CVector3 *outPos, s32 *outRoom, s32 copyFlags, s32 copyMode);

extern f32 Graphu64_GetHorizontalAngle(CVector3 *direction);
extern void Graphu64_AddVec3(CVector3 *result, CVector3 *left, CVector3 *right);
extern void Graphu64_SubtractVectors(CVector3 *result, CVector3 *left, CVector3 *right);



/* Places the goal beside kind-7 targets: pushed away from the anchor by both extents. */
static inline void Weapons_PlaceGoalBeside(LevelActor *actor, LevelActor *target, LevelActor *anchor, CVector3 *outPos, s32 *outRoom) {
    CVector3 dir;
    CVector3 goal;
    if (anchor != 0) {
        Graphu64_SubtractVectors(&dir, &target->position0, &anchor->position0);
        dir.y = 0.0f;
        Graphu64_NormalizeVec3(&dir);
    } else {
        dir.x = 0.0f;
        dir.y = 0.0f;
        dir.z = 0.0f;
    }
    Graphu64_ScaleVector(&dir, &dir, Gobjinst_GetActorRadius(target) + Gobjinst_GetActorRadius(actor) + g_goalBesideActorClearance);
    Graphu64_AddVec3(&goal, &target->position0, &dir);
    InstHdr_CopyActorPositionAndModel(target, goal, outPos, outRoom, 0, 0);
}
/** Picks what the tracker aims at (its target, itself, a slot or home point, or the actor) and
    fills out with the kind, target, reach, goal position and its offset from the actor, both in 3D
    and flattened to the ground plane. The third parameter is overwritten: it serves as the boost flag. */
void Cbarrel_ResolveTrackGoal(LevelActor *actor, Tracker *tracker, s32 boost, BarrelTargetInfo *out) {
    CVector3 pos;
    CVector3 probe;
    CVector3 away;
    CVector3 delta;
    s32 room;
    LevelActor *target;
    s32 kind;
    s32 mode;
    f32 range;
    f32 gap;
    f32 angle;
    f32 reach;
    Location *loc;
    boost = 0; /* the shared tracker-callback slot (otherwise unread, as in Barrel_FillAnchorTargetInfo) holds the boost flag */
    if (actor->definition->kind != 1) {
        mode = -1;
    }
    if (tracker->team == g_world.kind1Cursor) {
        if ((tracker->flags & 0x40000) && tracker->lockedTarget == 0) {
            if (Cbarrel_UpdateTrackerAim(actor, (Plan *)tracker, tracker->target) == 0) {
                tracker->flags &= ~0x40000;
            }
        } else {
            tracker->target = Cbarrel_SelectCombatTarget(actor, tracker, 0, 1);
        }
    }
    target = tracker->target;
    kind = 6;
    if (tracker->active != 0) {
        if (target == 0) {
            kind = 3;
            if (tracker->slot != 0) {
                kind = 4;
            }
        } else if (target == tracker->self) {
            kind = 2;
        } else if (target->definition->kind == 5) {
            kind = 5;
        } else if (target->type == 1615) {
            kind = 7;
        } else if (g_world.visibilityEnabled != 0) {
            kind = 0;
        } else if (((target->flags & 0x300000) && ((Controller *)target->controller)->owner == actor &&
                    ((Controller *)target->controller)->state == 2) ||
                   ((actor->renderFlags & 2) && actor->type != 202)) {
            kind = 1;
        } else {
            kind = 0;
        }
    }
    if (target != 0) {
        if (kind == 7) {
            Weapons_PlaceGoalBeside(actor, target, tracker->anchor, &pos, &room);
        } else {
            pos = target->position0;
            room = target->model;
            if (mode == 1) {
                pos.y += target->eyeHeight + Gobjinst_GetActorHeight(target) * (*(float *)&g_trackGoalTargetHeightFactor);
            }
        }
        gap = Gobjinst_GetActorRadius(target) + Gobjinst_GetActorRadius(actor);
        switch (kind) {
            case 2:
                gap += (*(float *)&k_barrelTrackGoalApproachPadding);
            default:
                boost = 1;
                break;
            case 5:
            case 7:
                boost = 1;
                gap = 0.0f;
                break;
        }
    } else {
        gap = Gobjinst_GetActorRadius(actor);
        switch (kind) {
            case 4:
                loc = (Location *)Playerai_GetRouteCursorPoint(&tracker->slot);
                pos = loc->pos;
                gap = 0.0f;
                room = loc->room;
                if (tracker->slot == 2 || tracker->slot == kind) {
                    boost = 1;
                }
                break;
            case 3:
                pos = tracker->homePos;
                room = tracker->homeRoom;
                boost = 1;
                break;
            case 6:
                pos = actor->position0;
                room = actor->model;
                if (mode == 2) {
                    pos.y = InstHdr_GetModelRecordValue20(actor);
                }
                break;
        }
    }
    Graphu64_AddVec3(&pos, &pos, &tracker->offset);
    if (gap > 0.0f) {
        Graphu64_SubtractVectors(&away, &actor->position0, &pos);
        angle = Graphu64_GetHorizontalAngle(&away);
        pos.x -= gap * Gu_Sinf(angle);
        pos.z -= gap * Math_Cosf(angle);
    }
    if (mode == 2) {
        pos.y = RW_MIN_LT(pos.y, InstHdr_GetModelRecordValue20(actor));
    }
    if (boost) {
        reach = InstHdr_GetActorReach(actor);
        probe.x = actor->position0.x + reach * Gu_Sinf(tracker->angle);
        probe.y = tracker->height;
        probe.z = actor->position0.z + reach * Math_Cosf(tracker->angle);
        range = Barrel_FindClearAimAngle(actor, probe, target, (*(float *)&k_barrelClearAimSearchRange));
        pos.y = tracker->height;
    } else {
        range = Barrel_GetSignedAngleToPoint(actor, pos);
    }
    Graphu64_SubtractVectors(&delta, &pos, &actor->position0);
    out->kind = kind;
    out->target = target;
    out->m_DeltaAngle = range;
    out->m_vTargetPos = pos;
    out->m_vDeltaTargetPos = delta;
    out->m_DistFrom = Gu_Sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
    delta.y = 0.0f;
    pos.y = 0.0f;
    out->m_vXZTargetPos = pos;
    out->m_vXZDeltaTargetPos = delta;
    out->m_XZDistFrom = Gu_Sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
}





/* 80213ED4_4.CPP */
/* Picks an actor's target (the tracked enemy when the aim point is chosen, else the nearest permitted target from Cbarrel_SelectCombatTarget), classifies it into one of eight kinds, and fills the target record with the kind, target, height difference, position, direction and distance, both in full and flattened to the horizontal plane. */


extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);
static inline s32 Barrel_ClassifyAnchorTarget(LevelActor *self, Tracker *ctx, LevelActor *target) {
    if (ctx->active == 0) {
        return 6;
    }
    if (target == NULL) {
        if (ctx->slot != 0) {
            return 4;
        }
        return 3;
    }
    if (target == ctx->self) {
        return 2;
    }
    if (target->definition->kind == 5) {
        return 5;
    }
    if (target->type == 1615) {
        return 7;
    }
    if (g_world.visibilityEnabled == 0) {
        if ((target->flags & 0x300000) && ((Controller *)target->controller)->owner == self
            && ((Controller *)target->controller)->state == 2) {
            return 1;
        }
        if ((self->renderFlags & 2) && self->type != 202) {
            return 1;
        }
    }
    return 0;
}
void Barrel_FillAnchorTargetInfo(LevelActor *actor, Tracker *tracker, s32 boostFlag, BarrelTargetInfo *targetInfo) {
    CVector3 pos;
    CVector3 delta;
    f32 height;
    s32 kind;
    LevelActor *target;
    Location *point;
    if ((tracker->team == g_world.kind1Cursor) && !(actor->definition->gate & 0x400) && (!(tracker->flags & 0x80000) || (tracker->lockedTarget != 0))) {
        tracker->anchor = Cbarrel_SelectCombatTarget(actor, tracker, 1, 0);
    }
    if ((actor->definition->kind == 1) && (tracker->mode == 11)
        && Barrel_ClassifyAnchorTarget(actor, tracker, tracker->target) == 4) {
        target = tracker->target;
        kind = 4;
    } else {
        target = tracker->anchor;
        kind = Barrel_ClassifyAnchorTarget(actor, tracker, target);
    }
    if (target != NULL) {
        pos = target->position0;
        height = Barrel_GetSignedAngleToPoint(actor, pos);
    } else {
        switch (kind) {
            case 4:
                point = (Location *)Playerai_GetRouteCursorPoint(&tracker->slot);
                pos = point->pos;
                if (point->flags & 1) {
                    height = point->heading * 0.0174532942f - actor->yaw;
                } else {
                    height = Barrel_GetSignedAngleToPoint(actor, pos);
                }
                break;
            case 3:
                pos = tracker->homePos;
                height = tracker->homeYaw - actor->yaw;
                break;
            case 6:
                pos = actor->position0;
                height = 0.0f;
                break;
        }
    }
    Graphu64_WrapPeriodicValue(&height);
    Graphu64_SubtractVectors(&delta, &pos, &actor->position0);
    targetInfo->m_DeltaAngle = height;
    targetInfo->kind = kind;
    targetInfo->target = target;
    targetInfo->m_vTargetPos = pos;
    targetInfo->m_vDeltaTargetPos = delta;
    targetInfo->m_DistFrom = Gu_Sqrtf((delta.x * delta.x) + (delta.y * delta.y) + (delta.z * delta.z));
    delta.y = 0.0f;
    pos.y = 0;
    targetInfo->m_vXZTargetPos = pos;
    targetInfo->m_vXZDeltaTargetPos = delta;
    targetInfo->m_XZDistFrom = Gu_Sqrtf((delta.x * delta.x) + (delta.y * delta.y) + (delta.z * delta.z));
}



/* Aim toward a point; when obstructed, try progressively wider left/right
 * directions and choose the first clear probe. */
static inline f32 Weapons_ProbeHeading(Actor_u1 *actor, CVector3 point) {
    f32 dx;
    f32 dz;
    f32 dist;
    f32 sine;
    f32 cosine;
    f32 dot;
    f32 angle;

    dx = point.x - actor->position.x;
    dz = point.z - actor->position.z;
    dist = Gu_Sqrtf(dx * dx + dz * dz);
    if (dist == 0.0f) {
        return 0.0f;
    }
    do {
        sine = Gu_Sinf(actor->yaw);
    } while (0);
    cosine = -Math_Cosf(actor->yaw);
    dot = (dx * -sine + dz * cosine) / dist;
    dot = ((RW_MIN(dot, 1.0f)) < (-1.0f) ? (-1.0f) : (RW_MIN(dot, 1.0f)));
    angle = Graphu64_ArcCos(dot);
    if (!(dx * cosine + dz * sine > 0.0f)) {
        angle = -angle;
    }
    return angle;
}
f32 Barrel_FindClearAimAngle(Actor_u1 *actor, CVector3 point, s32 target, f32 distance) {
    CVector3 probe;
    char *hit;
    f32 heading = Weapons_ProbeHeading(actor, point);
    f32 cosine, sine, offset, angle, bias;
    s32 step, side, parity;
    if ((actor->flags & 0x200) && Gobjinst_ProbeActorMovement(actor, point, &hit)) {
        if (target != 0 && g_currentActorInstance.instance0 == target) return heading;
        parity = ((u32)actor % 744U) & 1;
        probe.y = actor->position.y;
        for (step = 1; step < 6; step++) {
            offset = (f32)step * (RW_PI_F6 / 6.0f);
            for (side = 0; side < 2; side++) {
                angle = heading;
                if (side != parity) {
                    angle += offset;
                    bias = (RW_PI_F6 / 12.0f);
                } else {
                    angle -= offset;
                    bias = (-RW_PI_F6 / 12.0f);
                }
                cosine = Gu_Sinf(actor->yaw + 3.1415927f + angle);
                probe.x = actor->position.x + cosine * (distance * Gobjinst_GetActorRadius(actor));
                sine = Math_Cosf(actor->yaw + 3.1415927f + angle);
                probe.z = actor->position.z + sine * (distance * Gobjinst_GetActorRadius(actor));
                if (!Gobjinst_ProbeActorMovement(actor, probe, 0)) {
                    angle += bias;
                    Graphu64_WrapPeriodicValue(&angle);
                    return angle;
                }
            }
        }
    }
    return heading;
}


/* Barrel_GetSignedAngleToPoint's body: the signed angle between the actor's facing and the direction to the point. */
static inline f32 angleTo(LevelActor *actor, CVector3 point) {
    f32 dx;
    f32 dz;
    f32 dist;
    f32 sine;
    f32 cosine;
    f32 dot;
    f32 angle;

    dx = point.x - actor->position0.x;
    dz = point.z - actor->position0.z;
    dist = Gu_Sqrtf(dx * dx + dz * dz);
    if (dist == 0.0f) {
        return 0.0f;
    }
    do {
        sine = Gu_Sinf(actor->yaw);
    } while (0);
    cosine = -Math_Cosf(actor->yaw);
    dot = (dx * -sine + dz * cosine) / dist;
    dot = ((RW_MIN(dot, 1.0f)) < ((-1.0f)) ? ((-1.0f)) : (RW_MIN(dot, 1.0f)));
    angle = Graphu64_ArcCos(dot);
    if (!(dx * cosine + dz * sine > 0.0f)) {
        angle = -angle;
    }
    return angle;
}

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

/* Whether the target faces the actor within a cone, and from which side. The target must be armed: a player with ammo
 * for its current weapon and the fire button held, an AI in anim type 0x10CC or later (kind 1) or in mode 0x3F
 * (kind 4). Targets 70 to 110 degrees off the actor's heading are skipped. The line from the actor (its height
 * clamped to the target's aim point) to the target is compared with the target's forward vector: 0 when the angle
 * between them is not under half the cone, else -1 or 1 for the side. */
s32 Barrel_GetFacingSide(LevelActor *self, void *trackerState, LevelActor *target, f32 cone) {
    CVector3 dir;
    CVector3 facing;
    CVector3 forward;
    CVector3 from;
    CVector3 to;
    struct Controller *controller;
    f32 low;
    f32 high;
    f32 angle;

    if (target == NULL) {
        return 0;
    }
    if (target->flags & 0x300000) {
        controller = target->controller;
        if (Player_HasAmmoForMode(controller, controller->currentWeapon) <= 0) {
            return 0;
        }
        if (!(controller->buttons & 0x2000)) {
            return 0;
        }
    } else {
        switch (target->definition->kind) {
        case 1:
            if (target->animationType < 4300) {
                return 0;
            }
            break;
        case 4:
            if (((s8)target->aiMode) != 63) {
                return 0;
            }
            break;
        default:
            return 0;
        }
    }
    low = self->position0.y + self->eyeHeight;
    high = low + Gobjinst_GetActorHeight(self);
    to.x = target->position0.x;
    to.y = target->position0.y + target->eyeHeight + Gobjinst_GetActorHeight(target) * 0.9f;
    to.z = target->position0.z;
    from.x = self->position0.x;
    from.z = self->position0.z;
    if (high < to.y) {
        from.y = high;
    } else if (to.y < low) {
        from.y = low;
    } else {
        from.y = to.y;
    }
    angle = ABS(angleTo(self, to));
    if (angle > 70.0f * RW_PI_F6 / 180.0f && angle < 110.0f * RW_PI_F6 / 180.0f) {
        return 0;
    }
    Graphu64_SubtractVectors(&dir, &from, &to);
    Graphu64_NormalizeVec3(&dir);
    forward.x = 0.0f;
    forward.y = 0.0f;
    forward.z = 1.0f;
    Gobjinst_TransformVectorByActorAim(&facing, target, forward);
    if (Graphu64_ArcCos(dir.x * facing.x + dir.y * facing.y + dir.z * facing.z) < cone * 0.5f) {
        if (dir.x * -facing.z + dir.z * facing.x < 0.0f) {
            return -1;
        }
        return 1;
    }
    return 0;
}

#undef ABS

s32 Barrel_GetImpactSlot(void *actorObject)
{
    char *actor = actorObject;
    CGameStatus *audio;
    s32 type;

    type = InstHdr_GetActorType(actor);
    switch (type) {
    case 1:
    case 2:
        return 0;
    case 3:
    case 4:
        return 1;
    case 5:
    case 6:
        return 2;
    case 7:
    case 8:
        return 3;
    case 9:
    case 10:
    case 100:
    case 102:
    case 1120:
    case 1121:
    case 1122:
    case 1123:
    case 1126:
        if (*(u8 *)actor == 1) {
            if ((((LevelActor *)actor)->flags & 0x300000) != 0) {
                if ((((Player *)actor)->reactionFlags & 0x18400) != 0) {
                    return 9;
                }
                audio = &g_gameSettings.counters;
                if (audio->enabled != 0 &&
                    ((Player *)actor)->profile->character == 11 &&
                    audio->m_nBastilleShield > 0) {
                    return 9;
                }
            }
        }
        return 4;
    case 11:
    case 12:
        return 5;
    case 13:
    case 14:
        return 6;
    case 15:
    case 16:
        return 7;
    case 17:
    case 18:
        return 8;
    case 19:
    case 20:
    case 103:
        return 9;
    default:
        return 3;
    }
}

/* The call sites in Events_SpawnFilteredActorEffect, Ghot_DispatchAttachmentEffects and Events_SpawnActorEffect
 * pass a fourth incoming slot; the callee never reads it. The signature here
 * is the one those callers and this definition agree on across the ROM. */



void Barrel_SpawnActorEffect(void *actor, s32 kind, Triple input, s32 spawnFlags) {
    Triple copiedInput;
    CVector3 position;
    CQuatern rotation;
    s32 actorField;
    CActor_t *typedActor;
    s32 mode;
    s32 eventValue;
    s32 value;

    typedActor = 0;
    mode = 1;
    InstHdr_CopyActorPositionAndModel(actor, *(CVector3 *)&input, (CVector3 *)&copiedInput, &actorField, 0, mode);
    eventValue = 0;

    switch (((CActor_t *)actor)->type) {
    case 0:
    case 2:
        position.x = position.y = position.z = 0.0f;
        rotation.x = rotation.y = rotation.z = 0.0f;
        rotation.w = k_barrelEffectQuaternionValues[1];
        break;

    case 1:
        typedActor = actor;
        position = typedActor->position;
        rotation = Gobjinst_BuildActorAimQuaternion(typedActor);
        eventValue = typedActor->eventValue;
        if (Gobjinst_GetModelRenderMode(typedActor) == 5) {
            mode = 3;
        }
        break;

    case 3:
        position = ((CActor_t *)actor)->position;
        rotation = Simpinst_BuildGroundRotation(actor);
        break;
    }

    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], actor, actor, 0, eventValue, kind,
                  position, rotation, *(CVector3 *)&copiedInput, 0, -1, mode);

    if ((((CActor_t *)actor)->type == 1) && (typedActor->objectId == 1036)) {
        value = typedActor->eventCount - 1;
        if (value < 0) {
            value = 0;
        }
        typedActor->eventCount = value;
    }
}

void Barrel_FillDamagePacket(void *packet, s32 damageSource, s32 damage, f32 radius, s32 damageFlags, s32 shield) {
    (((struct DamagePacketWords *) packet)->source) = damageSource;
    (((struct DamagePacketWords *) packet)->damage) = damage;
    *(f32 *)&((struct DamagePacketWords *)packet)->radiusBits = radius;
    (((struct DamagePacketWords *) packet)->damageFlags) = damageFlags;
    (((struct DamagePacketWords *) packet)->shield) = shield;
}


void Barrel_UpdateActorController(SourceBarrelUpdateActorController *src, DestBarrelUpdateActorController *dst) {
    if ((dst->aux != 0) && (dst->aux->flagWord == -1)) {
        Barrel_StopActorLoopingSound(src, dst);
    }
    if (dst->timer != 0) {
        dst->timer--;
        g_frameElapsedTime = 0.0f;
        return;
    }
    if ((src->active != 0) && (src->kind != 0)) {
        if (*src->kind == 2) {
            dst->old_position = src->position;
            dst->height = src->height;
        }
        dst->position = src->position;
        dst->value += g_frameElapsedTime;
        if (src->flags & 0x10000) {
            Actor_ApplySupportingPlatformMotion(src, dst);
        }
        if (dst->callback != 0) {
            dst->callback(src, dst);
        }
        Actor_UpdateActorStateAnimation(src, dst);
        if (*src->kind != 2) {
            dst->old_position = src->position;
            dst->height = src->height;
        }
    }
}


void Barrel_ComputeTargetOffset(Player *player, ActorMotionState *motionState, CAIMovementInfo *result) {
    Graphu64_SubtractVectors(&result->first, &player->pos,
                  &motionState->position);
    result->first_normalized = result->first;
    Graphu64_NormalizeVec3(&result->first_normalized.x);
    result->first_length = Gu_Sqrtf(
        result->first.x * result->first.x +
        result->first.y * result->first.y +
        result->first.z * result->first.z);
    result->flat.x = result->first.x;
    result->flat.y = 0.0f;
    result->flat.z = result->first.z;
    result->flat_normalized = result->flat;
    Graphu64_NormalizeVec3(&result->flat_normalized.x);
    result->flat_length = Gu_Sqrtf(
        result->flat.x * result->flat.x +
        result->flat.y * result->flat.y +
        result->flat.z * result->flat.z);
    result->height = player->heading -
                     motionState->height;
}

/* Picks a random entry from a table of mask and id records ending in -1: every id whose mask shares
   a bit with flags and that Gobjinst_ChooseAnimationVariant finds for the owner is added to a weighted picker with
   weight 10, a zero mask ends the search once something was added, the first id is added when the
   picker is still empty, and the pick is returned when Gobjinst_ChooseAnimationVariant finds it, otherwise the first
   id. */


s32 Cbarrel_SelectWeightedAnimation(s32 owner, s32 trackerState, struct IntPair *table, s32 flags) {
    WeightedTable picker;
    s32 first;
    s16 pick;

    Lists_ClearWeightedTable(&picker);
    first = table->second;
    while (table->first != -1) {
        if (table->first == 0 && picker.count != 0) {
            goto choose;
        }
        if ((flags & table->first) && Gobjinst_ChooseAnimationVariant(owner, table->second, -1) != -1) {
            Lists_AppendWeightedEntry(&picker, (s16) table->second, 10);
        }
        table++;
    }
    if (picker.count == 0) {
        Lists_AppendWeightedEntry(&picker, (s16) first, 10);
    }
choose:
    pick = Lists_ChooseWeightedTableEntry(&picker);
    if (Gobjinst_ChooseAnimationVariant(owner, pick, -1) == -1) {
        return first;
    }
    return pick;
}

void Barrel_ApplyClampedTurn(void *actor, s32 motionState, f32 turnLimit, f32 desiredTurn) {
    f32 negatedTurnLimit;
    f32 yawStep;
    f32 stepMagnitude;
    f32 requestedTurn;

    negatedTurnLimit = turnLimit;
    yawStep = desiredTurn;
    requestedTurn = yawStep;
    if (negatedTurnLimit < yawStep || (negatedTurnLimit = -negatedTurnLimit, yawStep < negatedTurnLimit)) {
        yawStep = negatedTurnLimit;
    }
    yawStep = yawStep * g_frameElapsedTime;
    stepMagnitude = yawStep;
    if (yawStep < 0.0f) {
        stepMagnitude = -yawStep;
    }
    if (requestedTurn < 0.0f) {
        if (-requestedTurn < stepMagnitude) {
            goto clamp;
        }
    } else if (requestedTurn < stepMagnitude) {
clamp:
        yawStep = requestedTurn;
    }
    Barrel_AddActorYaw(actor, yawStep);
}

void Cbarrel_TurnTowardClearAim(void *actor, s32 unusedEvent, CTeamSelectTeam *target, f32 maximumTurn) {
    f32 negatedMaximumTurn;
    f32 turnStep;
    f32 stepMagnitude;
    f32 clearAimAngle;

    if (target != 0) {
        turnStep = Barrel_FindClearAimAngle(actor, *(CVector3 *)&target->x,
                           (s32)target, g_barrelClearAimClearance);
        clearAimAngle = turnStep;
        if (maximumTurn < turnStep) {
            turnStep = maximumTurn;
        } else {
            negatedMaximumTurn = -maximumTurn;
            if (turnStep < negatedMaximumTurn) {
                turnStep = negatedMaximumTurn;
            }
        }
        turnStep = turnStep * g_frameElapsedTime;
        stepMagnitude = turnStep;
        if (turnStep < 0.0f) {
            stepMagnitude = -turnStep;
        }
        if (clearAimAngle < 0.0f) {
            if (-clearAimAngle < stepMagnitude) {
                goto clamp;
            }
        } else if (clearAimAngle < stepMagnitude) {
clamp:
            turnStep = clearAimAngle;
        }
        Barrel_AddActorYaw(actor, turnStep);
    }
}

s32 Cbarrel_ClassifyTrackTarget(LevelActor *actor, RouteChaseBot *routeChaseBot, LevelActor *target) {
    void *controller;

    if (routeChaseBot->node == 0) {
        return 6;
    }
    if (target == 0) {
        if (routeChaseBot->routeReady != 0) {
            return 4;
        }
        return 3;
    }
    if (target == routeChaseBot->target) {
        return 2;
    }
    if (target->definition->kind == 5) {
        return 5;
    }
    if (target->type == 1615) {
        return 7;
    }
    if (g_world.visibilityEnabled == 0) {
        if (target->flags & 0x300000) {
            controller = target->controller;
            if ((((Player *)controller)->controllerOwner == actor) &&
                (((Player *)controller)->controllerMode == 2)) {
                return 1;
            }
        }
        if (actor->renderFlags & 2) {
            if (actor->type != 202) {
                return 1;
            }
        }
    }
    return 0;
}

struct CollisionInfo;


s32 Cbarrel_TestFlaggedAimObstruction(LevelActor *probingActor, void *trackerState, LevelActor *target) {
    u8 saved[0x50];
    CVector3 desired;
    f32 scale;

    __builtin_memcpy(saved, probingActor, sizeof(saved));
    scale = g_barrelFlaggedAimProbeScale;
    ((DraftAimPlayer *)probingActor)->position.y += Gobjinst_GetActorHeight(probingActor) * scale;
    ((DraftAimPlayer *)probingActor)->position.y += ((DraftAimPlayer *)probingActor)->height;

    desired = ((LevelActor *)(target))->position0;
    desired.y += Gobjinst_GetActorHeight(target) * scale;
    desired.y += ((LevelActor *)(target))->eyeHeight;

    CCollision_SweepPoint(probingActor, ((Player *)(probingActor))->pos, desired, &g_particleCollisionProbeResult);
    __builtin_memcpy(probingActor, saved, sizeof(saved));

    if (g_collisionProbePrimaryActor != 0 && (g_collisionProbePrimaryActor->flags & 2)) {
        return 1;
    }
    if (g_collisionProbeSecondaryActor != 0 && (g_collisionProbeSecondaryActor->flags & 2)) {
        return 1;
    }
    return 0;
}

struct CollisionInfo;




s32 Cbarrel_TestTargetEyeObstruction(LevelActor *attacker, void *trackerState, LevelActor *target) {
    u8 saved[0x50];
    CVector3 desired;
    s32 collisions;

    __builtin_memcpy(saved, attacker, sizeof(saved));
    ((struct LevelActor *)attacker)->position0.y += Gobjinst_GetActorHeight(attacker);
    ((struct LevelActor *)attacker)->position0.y += ((LevelActor *)(target))->eyeHeight;

    desired = ((LevelActor *)(target))->position0;
    desired.y += Gobjinst_GetActorHeight(target);
    desired.y += ((LevelActor *)(target))->eyeHeight;

    collisions = CCollision_SweepPoint(attacker, ((struct LevelActor *)attacker)->position0, desired, &g_defaultProbeMotionSettings);
    if (g_currentActorInstance.instance0 == target)
        collisions = 0;

    __builtin_memcpy(attacker, saved, sizeof(saved));
    return collisions;
}

void Cbarrel_LockTrackerTarget(void *ownerActor, void *trackerState, struct LevelActor *target, float lockDuration) {
    Tracker *tracker = trackerState;
    tracker->lockedTarget = target;
    tracker->targetTimer = lockDuration;
}

void Barrel_UpdateTrackGoals(LevelActor *actor, void *trackerState, BarrelTargetInfo *targetInfos, s32 updateTrackedTarget, s32 updateAnchorTarget) {
    Tracker *tracker = trackerState;
    CVector3 first;
    CVector3 second;
    f32 lockTimeLeft;
    f32 targetTimer;

    targetTimer = tracker->targetTimer;
    if (targetTimer > 0.0f) {
        lockTimeLeft = targetTimer - g_frameElapsedTime;
        tracker->targetTimer = lockTimeLeft;
        if (lockTimeLeft <= 0.0f) {
            tracker->lockedTarget = 0;
            tracker->targetTimer = 0.0f;
        }
    }
    if (updateTrackedTarget != 0) {
        Cbarrel_ResolveTrackGoal(actor, tracker, (s32)tracker->target, &targetInfos[1]);
    } else {
        BarrelTargetInfo *out = &targetInfos[1];
        first = actor->position0;
        second.x = 0;
        second.y = 0;
        second.z = 0;
        out->kind = 3;
        out->target = 0;
        out->m_DeltaAngle = 0;
        out->m_vTargetPos = first;
        out->m_vDeltaTargetPos = second;
        out->m_DistFrom = 0;
        second.y = 0;
        first.y = 0;
        out->m_vXZTargetPos = first;
        out->m_vXZDeltaTargetPos = second;
        out->m_XZDistFrom = 0;
    }
    if (updateAnchorTarget != 0) {
        Barrel_FillAnchorTargetInfo(actor, tracker, (s32)tracker->anchor, targetInfos);
        return;
    }
    first = actor->position0;
    second.x = 0;
    second.y = 0;
    second.z = 0;
    targetInfos->kind = 3;
    targetInfos->target = 0;
    targetInfos->m_DeltaAngle = 0;
    targetInfos->m_vTargetPos = first;
    targetInfos->m_vDeltaTargetPos = second;
    targetInfos->m_DistFrom = 0;
    second.y = 0;
    first.y = 0;
    targetInfos->m_vXZTargetPos = first;
    targetInfos->m_vXZDeltaTargetPos = second;
    targetInfos->m_XZDistFrom = 0;
}

/* Returns the signed angle between an actor's facing and the direction to a point on the ground plane:
   normalises the offset from the actor to the point, takes its dot product with the facing
   built from the sine and cosine of the yaw, clamps it to -1..1, converts it through the arc
   cosine Graphu64_ArcCos and negates it when the point lies on the other side, or returns zero when the
   point is at the actor. Scheduler lever, disclosed: the sine read sits in a do-while (0) block. */

f32 Barrel_GetSignedAngleToPoint(void *actor, CVector3 point) {
    f32 dx;
    f32 dz;
    f32 dist;
    f32 sine;
    f32 cosine;
    f32 dot;
    f32 angle;
    dx = point.x - ((struct LevelActor *)actor)->position0.x;
    dz = point.z - ((struct LevelActor *)actor)->position0.z;
    dist = Gu_Sqrtf(dx * dx + dz * dz);
    if (dist == 0.0f) {
        return 0.0f;
    }
    do {
        sine = Gu_Sinf(((struct LevelActor *)actor)->yaw);
    } while (0);
    cosine = -Math_Cosf(((struct LevelActor *)actor)->yaw);
    dot = (dx * -sine + dz * cosine) / dist;
    dot = ((RW_MIN(dot, 1.0f))<((-1.0f))?((-1.0f)):(RW_MIN(dot, 1.0f)));
    angle = Graphu64_ArcCos(dot);
    if (dx * cosine + dz * sine > 0.0f) {
        return angle;
    }
    return -angle;
}

#if defined(VERSION_US)
extern const float g_barrelFlaggedEffectRandomRanges[];
#endif

/* 80213ED4_19.CPP */
void Barrel_AddActorYaw(LevelActor *actor, f32 yawDelta) {
    actor->yaw = (f32) (actor->yaw + yawDelta);
    ((s32 (*)(void *))Graphu64_WrapPeriodicValue)(&actor->yaw);
}

void Barrel_SpawnFlaggedEffects(Player *actor, s32 *emittedFlags, s32 emissionFlag, s32 primaryEffectMask, s32 secondaryEffectMask) {
    s32 *entry;

    if ((emittedFlags[0] & emissionFlag) != 0) {
        return;
    }

    emittedFlags[0] |= emissionFlag;
    entry = g_barrelPrimaryFlagSoundTable;
    if (entry[0] != 0) {
        do {
            if ((primaryEffectMask & entry[0]) != 0) {
                Insthdr_PlayActorGraphSound(actor,
                              actor->pos,
                              entry[1],
                              Graphu64_RandomBetween(g_barrelFlaggedEffectRandomRanges[0], k_barrelPrimarySoundRandomMaximum));
            }
            entry += 2;
        } while (entry[0] != 0);
    }

    entry = g_barrelSecondaryFlagSoundTable;
    if (entry[0] != 0) {
        do {
            if ((secondaryEffectMask & entry[0]) != 0) {
                Insthdr_PlayActorGraphSound(actor,
                              actor->pos,
                              entry[1],
                              Graphu64_RandomBetween(k_barrelSecondarySoundRandomMinimum, k_barrelSecondarySoundRandomMaximum));
            }
            entry += 2;
        } while (entry[0] != 0);
    }
}

/** Store one word into both elements of a two-word value. */
void Barrel_FillWordPair(int *value, int word) {
    value[0] = word;
    value[1] = word;
}

/** Read the next u16 from the cursor stream, wrapping back to base on the -1 sentinel. */
s16 Barrel_ReadLoopingSequenceValue(BarrelSequenceCursor *sequence) {
    u16 *cur;
    u16 value;

    cur = sequence->cur;
    value = *cur;
    cur += 1;
    sequence->cur = cur;
    if (*(s16 *) cur == -1) {
        sequence->cur = sequence->base;
    }
    return (s16) value;
}

/* Runs the hook with the arguments this function was called with: its callers pass the actor, its hook state
 * and the damage record, and the hook reads them from the same argument registers. */
void Barrel_RunDamageHook(void *actor, struct ActorDamageHookView *callbackState, void *damage) {
    FuncPtr fn = callbackState->callback;
    if (fn != 0) {
        ((void (*)(void *, void *, void *))fn)(actor, callbackState, damage);
    }
}


/** Subtract obj->y from vectorY in-place via Graphu64_SubtractVectors, then return the squared length of (vectorX, vectorY', vectorZ). */
f32 Barrel_GetEyeDistanceSquared(void *candidate, CVector3 viewpoint) {
    f32 eyeDeltaY;

    Graphu64_SubtractVectors(&viewpoint, &viewpoint, &((LevelActor *)(candidate))->position0);
    eyeDeltaY = viewpoint.y - ((LevelActor *)(candidate))->eyeHeight;
    viewpoint.y = eyeDeltaY;
    return (viewpoint.x * viewpoint.x) + (eyeDeltaY * eyeDeltaY) + (viewpoint.z * viewpoint.z);
}

/* Squared XZ distance to a point using the existing by-value vector ABI. */
f32 Barrel_GetFlatDistanceSquared(LevelActor *actor, CVector3 point)
{
    f32 dx = point.x - actor->position0.x;
    f32 dz = point.z - actor->position0.z;
    return dx * dx + dz * dz;
}

void Barrel_IgnoreEffectCallback(void *effectActor, void *effectState, BarrelWordPair effectWords) {
}


void Barrel_SetLoopingSound(void *actor, void *stateController, s32 sixth) {
    CLoopingSoundData *node;
    void *fallback;
    s32 kind;

    node = ((Dest *)stateController)->sound;
    fallback = (void *)-1;
    if (node != 0) {
        if (node->state == sixth) {
            return;
        }
        SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), ((Dest *)stateController)->sound);
    }

    kind = *(u8 *)actor;
    if (kind != 0) {
        if (kind >= 0) {
            if (kind < 3) {
                fallback = actor;
            }
        }
    } else {
        fallback = (void *)((LevelActor *)actor)->resourceFlags;
    }

    ((Dest *)stateController)->sound =
        SoundVoicePool_PlaySpatialSound(SoundVoicePool_GetGlobalState(), sixth, &((LevelActor *)actor)->position0,
                      &((LevelActor *)actor)->position0, (s32)fallback);
}

void Barrel_StopActorLoopingSound(void *actor, void *soundState) {
    void *owner = 0;
    u8 type = *(u8 *)actor;

    switch (type) {
    case 1:
    case 2:
        owner = actor;
        break;
    case 0:
        owner = (void *)((LevelActor *)actor)->resourceFlags;
        break;
    }

    if (((Dest *)soundState)->sound != 0) {
        SoundElement_StopAudioBySecondaryValue(owner);
        if (((Dest *)soundState)->sound != 0) {
            SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), ((Dest *)soundState)->sound);
            ((Dest *)soundState)->sound = 0;
        }
    }
}


void Barrel_FindOffsetApproachPosition(void *actor, s32 trackerState, void *target, Player *player,
                   void *positionOut, s32 *modelFlagsOut) {
    CVector3 offset;
    CVector3 position;
    f32 distance;

    if (player != 0) {
        Graphu64_SubtractVectors(&offset, &((Player *)(target))->pos,
                       &player->pos);
        offset.y = 0.0f;
        Graphu64_NormalizeVec3(&offset.x);
    } else {
        offset.x = 0.0f;
        offset.y = 0.0f;
        offset.z = 0.0f;
    }

    distance = Gobjinst_GetActorRadius(target) + Gobjinst_GetActorRadius(actor) + g_barrelApproachClearance;
    Graphu64_ScaleVector(&offset, &offset, distance);
    Graphu64_AddVec3(&position, &((Player *)(target))->pos, &offset);
    InstHdr_CopyActorPositionAndModel(target, position, positionOut, modelFlagsOut, 0, 0);
}

void Barrel_ClearTargetInfo(LevelActor *actorView, void *trackerState, BarrelTargetInfo *targetInfo) {
    CVector3 local1;
    CVector3 local2;

    local1 = actorView->position0;
    local2.x = 0;
    local2.y = 0;
    local2.z = 0;
    targetInfo->kind = 3;
    targetInfo->target = 0;
    targetInfo->m_DeltaAngle = 0;
    targetInfo->m_vTargetPos = local1;
    targetInfo->m_vDeltaTargetPos = local2;
    targetInfo->m_DistFrom = 0;
    local2.y = 0;
    local1.y = 0;
    targetInfo->m_vXZTargetPos = local1;
    targetInfo->m_vXZDeltaTargetPos = local2;
    targetInfo->m_XZDistFrom = 0;
}

void Barrel_SpawnEffectsFromMask(Player *actor, s32 trackerState, s32 effectMask, s32 *entry) {
    if (entry[0] != 0) {
        do {
            if ((effectMask & entry[0]) != 0) {
                Insthdr_PlayActorGraphSound(actor,
                              actor->pos,
                              entry[1],
                              Graphu64_RandomBetween(g_barrelEffectSoundMinimumPitch, g_barrelEffectSoundMaximumPitch));
            }
            entry += 2;
        } while (entry[0] != 0);
    }
}



extern const float g_goalBesideActorClearance;
extern const float g_trackGoalTargetHeightFactor;
extern const float k_barrelTrackGoalApproachPadding;
extern const float k_barrelClearAimSearchRange;

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* (flag mask, sound id) pairs walked by Barrel_SpawnFlaggedEffects for the primary effect mask: bits 0-5 play sounds 1701-1706, every other bit sound 2200;
   the {0, 0} terminator is the first pair of the following table's data */
s32 g_barrelPrimaryFlagSoundTable[64] = {
    0x00000001, 1701,
    0x00000002, 1702,
    0x00000004, 1703,
    0x00000008, 1704,
    0x00000010, 1705,
    0x00000020, 1706,
    0x00000040, 2200,
    0x00000080, 2200,
    0x00000100, 2200,
    0x00000200, 2200,
    0x00000400, 2200,
    0x00000800, 2200,
    0x00001000, 2200,
    0x00002000, 2200,
    0x00004000, 2200,
    0x00008000, 2200,
    0x00010000, 2200,
    0x00020000, 2200,
    0x00040000, 2200,
    0x00080000, 2200,
    0x00100000, 2200,
    0x00200000, 2200,
    0x00400000, 2200,
    0x00800000, 2200,
    0x01000000, 2200,
    0x02000000, 2200,
    0x04000000, 2200,
    0x08000000, 2200,
    0x10000000, 2200,
    0x20000000, 2200,
    0x40000000, 2200,
    0x80000000, 2200,
};
#endif

#if defined(VERSION_US_REV1)
extern const float g_barrelFlaggedEffectRandomRanges[4];
#endif

/* Retained data for this translation unit. */

const float k_barrelGetFacingSideUnit[1] = {
    1.0f,
};

const float k_BarrelGetfacingsideData[1] = {
    1.5f,
};

const float k_barrelGetFacingSideThreshold[1] = {
    0.8f,
};
#if defined(VERSION_US_REV1)
const float k_cbarrelUpdateTrackerAimConstants[3] = {
    51.199997f, 51.199997f, 3.1415927f,
};
#endif
#if defined(VERSION_US_REV1)
const float k_CbarrelUpdatetrackeraimMaxFiniteFloatWords[1] = {
    3.4028235e+38f,
};
#endif
#if defined(VERSION_US)
const float g_barrelFlaggedEffectRandomRanges[] = {
    450.0f, 600.0f, 450.0f, 600.0f,
};
#endif

const float g_goalBesideActorClearance = 51.19999695f;

const float g_trackGoalTargetHeightFactor = 0.8999999762f;

const float k_barrelTrackGoalApproachPadding = 102.3999939f;

const float k_barrelClearAimSearchRange = 1.5f;
#if defined(VERSION_US_REV1)
const float g_barrelFlaggedEffectRandomRanges[4] = {
    4.5e+02f, 6e+02f, 4.5e+02f, 6e+02f,
};
#endif
