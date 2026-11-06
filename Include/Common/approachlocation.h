#ifndef COMMON_APPROACHLOCATION_H
#define COMMON_APPROACHLOCATION_H
#include "types.h"
#include "Common/probe.h"
extern f32 Gobjinst_GetActorRadius(Actor_u1 *actor);
#include "types.h"
#include "Common/probe.h"

#include "Common/small_records.h"
#include "Ai/Playerai/playerai_playerai.h"
#include "Ai/Cbarrel/barrel_getsignedangletopoint.h"
#include "Common/level_actor.h"
struct LevelActor;
struct LevelActor;
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/rendersortrecord.h"
#include "Common/probe.h"
#include "Fx/normalize_vector.h"
#include "Graphu64/graphu64_getangledistance.h"

extern f32 k_barrelTargetAimOffsets[],g_actorApproachRadiusMargin;

extern f32 Graphu64_GetHorizontalAngle(CVector3 *);
struct Cursor;
extern s32 CCollision_CopyProbePosition(struct LevelActor *,CVector3,s32,s32,CVector3 *);
struct Node75;
extern s32 Region_IsPointInTriangleXZ(struct Node75 *,f32,f32);
extern void InstHdr_CopyActorPositionAndModel(struct LevelActor *,CVector3,CVector3 *,s32 *,s32,s32);
extern void Graphu64_AddVec3(CVector3 *,CVector3 *,CVector3 *);
extern void Graphu64_SubtractVectors(CVector3 *,CVector3 *,CVector3 *);
extern void Graphu64_ScaleVector(void *scaledVector, void *inputVector, f32 scaleFactor);

static inline void approach(struct LevelActor *actor,struct LevelActor *target,struct LevelActor *referenceActor,CVector3 *posp,s32 *roomp) {
 CVector3 delta,offset; f32 targetRadius;
        if (referenceActor != 0) {
            Graphu64_SubtractVectors(&delta, &target->position0, &referenceActor->position0);
            delta.y = 0;
            Graphu64_NormalizeVec3(&delta);
        } else {
            delta.x = 0;
            delta.y = 0;
            delta.z = 0;
        }
        targetRadius = Gobjinst_GetActorRadius(target) + Gobjinst_GetActorRadius(actor) + g_actorApproachRadiusMargin;
        Graphu64_ScaleVector(&delta, &delta, targetRadius);
        Graphu64_AddVec3(&offset, &target->position0, &delta);
        InstHdr_CopyActorPositionAndModel(target, offset, posp, roomp, 0, 0);
}
#endif
