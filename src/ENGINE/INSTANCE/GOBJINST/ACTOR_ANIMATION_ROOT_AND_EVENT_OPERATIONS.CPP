#include "include_asm.h"
#include "COMMON/ACTORRESOURCEHEADER.H"
#include "ENGINE/INSTANCE/GOBJINST.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/APPROACHLOCATION.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/LOCALDECODERANGE.H"
#include "COMMON/MTX.H"
#include "TYPES.H"
#include "GAME/BUILDDIRECTIONMATRIX.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

/* GOBJINST_15.CPP */
#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
void Gobjinst_NoOperationAnimationHookUs(void) {
}
#if defined(VERSION_DE) || defined(VERSION_US_REV1)
void Gobjinst_NoOperationAnimationHook(void) {
}
#endif
#endif

#if defined(VERSION_US)
/** Perform no operation. */
void Gobjinst_NoOperationAnimationHookAlternateUs(void) {
}
#endif

/* GOBJINST_16.CPP */
/* Spawns the standing effects of an animation for an object: every event whose effect id is 6 or 7 is placed by transforming its local point through the object's matrix at 0x74 and spawned through Events_DeliverContactEffect_ActorAnimationRootAndEventOperations with its parameters. */

extern CROMEventEntry *Gastate_GetAnimationEventEntries(void *);

extern void Events_DeliverContactEffect(char *, char *, u16, s32, CVector3, struct IntPair);

extern void Cache_UnlockResource(s32 cache, s32 resource);
extern void Polytrak2_SampleVectorTrack(CGameAnimateState_t *, s32, f32, f32 *);

void *Gobjinst_GetAnimationRootOffset(Triple *outOffset, void *actor, CGameAnimateState_t *anim) {
    char *o1 = (char *) actor;
    char mtx[64];
    f32 spVec[3];
    f32 inVec[3];
    f32 outVec[3];

    Polytrak2_SampleVectorTrack(anim, 0, anim->time, spVec);
    inVec[0] = spVec[0];
    inVec[1] = spVec[2];
    inVec[2] = spVec[1];
    BuildYawMatrix(mtx, ((LevelActor *)o1)->yaw);
    Graphu64_TransformPoint(mtx, inVec, outVec);
    outVec[0] *= ((LevelActor *)o1)->scale.x;
    outVec[1] *= ((LevelActor *)o1)->scale.y;
    outVec[2] *= ((LevelActor *)o1)->scale.z;
    *outOffset = *(Triple *) outVec;
    return outOffset;
}

void Gobjinst_SpawnStandingAnimationEffects(char *obj, void *anim)
{
    CROMEventEntry *e;
    s32 count;
    s32 i;
    CVector3 pos;

    e = Gastate_GetAnimationEventEntries(anim);
    count = Gastate_GetAnimationEventCount(anim);
    for (i = 0; i < count; i++) {
        switch (e[i].effect) {
        case 6:
        case 7:
            Graphu64_TransformPoint(&((LevelActor *)obj)->transform, &e[i].local, &pos);
            Events_DeliverContactEffect(obj, obj, e[i].effect, -1, pos, e[i].params);
        }
    }
}

s32 Gobjinst_GetAnimationSectionDelta(LevelActor *actor, s32 deltaIndex) {
    void *modelResource;
    Table *deltaTable;
    s32 sectionDelta;

    if (actor->flags & 0x40000) {
        modelResource = Cache_RequestResource(0, actor->resource, actor->resource, actor->resourceFlags, 4, 0, 0, &s_actorAnimationResourceTag, 1);
        if (modelResource != 0) {
            deltaTable = SetN64_GetPackSection(*(void **) modelResource, 1);
            sectionDelta = deltaTable->deltas[deltaIndex];
            Cache_UnlockResource(0, (s32) modelResource);
            return sectionDelta;
        }
    }
    return -1;
}

int Gobjinst_ReturnUnusedAnimationStatus(void) {
    return 0;
}

void Gobjinst_ApplyHorizontalAnimationRootOffset(LevelActor *actor, CGameAnimateState_t *animation) {
    Scratch scratch;
    f32 zero;

    zero = 0.0f;
    Polytrak2_SampleVectorTrack(animation, 0, zero, scratch.first);
    Polytrak2_SampleVectorTrack(animation, 0, animation->time, scratch.second);
    scratch.in[0] = scratch.second[0] - scratch.first[0];
    scratch.in[1] = zero;
    scratch.in[2] = scratch.second[1] - scratch.first[1];
    BuildYawMatrix(scratch.matrix, actor->yaw);
    Graphu64_TransformPoint(scratch.matrix, scratch.in, scratch.out);
    scratch.position.x = actor->position0.x +
                          (scratch.out[0] * actor->scale.x);
    scratch.position.y = actor->position0.y;
    scratch.position.z = actor->position0.z +
                          (scratch.out[2] * actor->scale.z);
    InstHdr_CopyActorPositionAndModel(actor, scratch.position, &actor->position0,
                  &actor->model, 0, 0);
}
