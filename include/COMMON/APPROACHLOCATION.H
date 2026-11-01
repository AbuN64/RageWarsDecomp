#ifndef COMMON_APPROACHLOCATION_H
#define COMMON_APPROACHLOCATION_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RENDERSORTRECORD.H"
#include "COMMON/PROBE.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"

typedef struct { CVector3 pos; s32 room; } ApproachLocation;
extern f32 k_barrelTargetAimOffsets[],g_actorApproachRadiusMargin;
extern f32 Barrel_GetSignedAngleToPoint(void *actor, struct CVector3_t point);
extern f32 Gobjinst_GetActorRadius(Actor_u1 *);
extern f32 Graphu64_GetHorizontalAngle(CVector3 *);
struct Cursor;
extern ApproachLocation *Playerai_GetRouteCursorPoint(struct Cursor *);
extern s32 CCollision_CopyProbePosition(TrackerAimActorView *,CVector3,s32,s32,CVector3 *);
struct Node75;
extern s32 Region_IsPointInTriangleXZ(struct Node75 *,f32,f32);
extern void InstHdr_CopyActorPositionAndModel(TrackerAimActorView *,CVector3,CVector3 *,s32 *,s32,s32);
extern void Graphu64_AddVec3(CVector3 *,CVector3 *,CVector3 *);
extern void Graphu64_SubtractVectors(CVector3 *,CVector3 *,CVector3 *);
extern void Graphu64_ScaleVector(CVector3 *,CVector3 *,f32);
static inline void approach(TrackerAimActorView *actor,TrackerAimActorView *target,TrackerAimActorView *referenceActor,CVector3 *posp,s32 *roomp) {
 CVector3 delta,offset; f32 targetRadius;
        if (referenceActor != 0) {
            Graphu64_SubtractVectors(&delta, &target->pos, &referenceActor->pos);
            delta.y = 0;
            Graphu64_NormalizeVec3(&delta);
        } else {
            delta.x = 0;
            delta.y = 0;
            delta.z = 0;
        }
        targetRadius = Gobjinst_GetActorRadius(target);
        Graphu64_ScaleVector(&delta, &delta, targetRadius + Gobjinst_GetActorRadius(actor) + g_actorApproachRadiusMargin);
        Graphu64_AddVec3(&offset, &target->pos, &delta);
        InstHdr_CopyActorPositionAndModel(target, offset, posp, roomp, 0, 0);
}
#endif
