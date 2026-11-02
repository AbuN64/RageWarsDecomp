#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/ACTORRESOURCEHEADER.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "TYPES.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "ENGINE/INSTANCE/GOBJINST_GETACTOROFFSETPOSITIONANDMODEL.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/LEGACY_COLLISION_ACTOR.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

/* GOBJINST_12.CPP */
/* Draws an actor's attached model: when the actor has one, allocates a matrix from the pool g_actorMatrixPool,
 * fills it with the given transform multiplied by the camera matrix (Graphu64_MultiplyMatrices, Graphu64_ClampMatrixToFixedRange,
 * GraphU64_PackFixedMatrix), loads it into the display list, draws the model through Geometry_DrawResourceModel with the
 * actor's per-frame state for the current frame, then reloads the camera's per-frame matrix. */

extern s32 Map_ReserveEntries(void *, s32);

extern void Graphu64_ClampMatrixToFixedRange(f32 *);

extern void GraphU64_PackFixedMatrix(f32 *, s32);

/* Moves an actor toward a point given relative to it: the offset is turned by the actor's facing and added to its position (or, for a mirrored actor with a parent, negated in x and z and transformed by the parent's matrix at 0x160), then passed to InstHdr_CopyActorPositionAndModel with both final flags set. */

extern void Graphu64_AddVec3(CVector3 *out, CVector3 *a, CVector3 *b);

extern void InstHdr_CopyActorPositionAndModel(void *actor, CVector3 target, void *positionOut, s32 *modelOut, s32 unused6, s32 unused7);

void Gobjinst_DrawModelWithProjection(void *actor, Camera *camera, f32 *transform, u8 layer) {
    struct LevelActor *object = actor;
    f32 mf[16];
    s32 mtx;
    s32 matrices;
    Gfx *restore;
    Gfx *load;
    s32 offset;

    if (object->animationMatrices != 0) {
        mtx = Map_ReserveEntries(&g_actorMatrixPool, 1);
        if (mtx != 0) {
            matrices = camera->matrices;
            Graphu64_MultiplyMatrices(mf, transform, (f32 *)(matrices + 480));
            Graphu64_ClampMatrixToFixedRange(mf);
            GraphU64_PackFixedMatrix(mf, mtx);
            gSPMatrix(g_displayListCursor++, mtx, G_MTX_LOAD | G_MTX_PROJECTION);
            Geometry_DrawResourceModel(layer, camera->style, object->animationMatrices, 1,
                          &object->lighting[g_lightingBufferIndex], 0, object->renderPass);
            restore = g_displayListCursor++;
            offset = (g_lightingBufferIndex << 6) + 896;
            gSPMatrix(restore, matrices + offset, G_MTX_LOAD | G_MTX_PROJECTION);
        }
    }
}

void Gobjinst_GetActorOffsetPositionAndModel(char *actor, CVector3 offset, void *positionOut, s32 *modelOut)
{
    CVector3 turned;
    CVector3 target;

    if (((ActorAnimationResourceView *)(actor))->flags & 0x300000) {
        char *parent;

        offset.x = -offset.x;
        offset.z = -offset.z;
        parent = ((struct ActorOwnerView *) ((ActorAnimationResourceView *) actor)->owner)->owner;
        if (parent != 0) {
            Graphu64_TransformPoint((char *)&((GameplayCamera *)parent)->viewOrient, &offset, &target);
        } else {
            Gobjinst_TransformVectorByActorAim(&turned, actor, offset);
            Graphu64_AddVec3(&target, &((ActorAnimationResourceView *)(actor))->position, &turned);
        }
    } else {
        Gobjinst_TransformVectorByActorAim(&turned, actor, offset);
        Graphu64_AddVec3(&target, &((ActorAnimationResourceView *)(actor))->position, &turned);
    }
    InstHdr_CopyActorPositionAndModel(actor, target, positionOut, modelOut, 1, 1);
}

/* GOBJINST_13.CPP */
extern CQuatern Gobjinst_BuildActorAimQuaternion(void *actor);

extern void MatrixFromQuaternion(f32 *q, f32 *m);

extern void Barrel_UpdateActorController(void *a, void *b);

extern void **Gobjinst_RequestAnimatedModelVariant(void *actor, s32 variantIndex);

extern void Cache_UnlockResource(void *cache, void *resource);

CVector3 *Gobjinst_TransformVectorByActorAim(CVector3 *outVector, void *actor, CVector3 localVector) {
    CQuatern aimOrientation;
    s32 aimMatrix[16];
    CVector3 transformedVector;

    aimOrientation = Gobjinst_BuildActorAimQuaternion(actor);
    MatrixFromQuaternion(&aimOrientation, aimMatrix);
    Graphu64_TransformPoint(aimMatrix, &localVector, &transformedVector);
    *outVector = transformedVector;
    return outVector;
}

s32 Gobjinst_TestActorTriangleVerticalClearance(Shared_CollisionActor *actor) {
    CVector3 direction;
    Node75 *node;
    f32 upper;
    f32 upperNext;
    f32 lower;
    f32 lowerNext;
    f32 sine;
    f32 cosine;

    node = (void *)actor->collision;
    if (node != 0) {
        upper = node->cur->y;
        if (node->prev->y <= upper) {
        } else {
            upper = node->prev->y;
        }
        upperNext = node->next->y;
        if (upper <= upperNext) {
        } else {
            upperNext = upper;
        }
        lower = node->cur->y;
        if (lower <= node->prev->y) {
        } else {
            lower = node->prev->y;
        }
        lowerNext = node->next->y;
        if (lowerNext <= lower) {
        } else {
            lowerNext = lower;
        }
        if (upperNext < actor->y) {
            return 0;
        }
        if (actor->y < lowerNext) {
            return 0;
        }
        sine = Gu_Sinf(actor->angle);
        cosine = Math_Cosf(actor->angle);
        Region_GetNodeEdgeCross(&direction, node);
        if (direction.x * -sine + direction.z * -cosine < 0.0f) {
            return 1;
        }
    }
    return 0;
}

/** Return the global float at g_actorDefaultOffsetValue. */

float Gobjinst_GetActorOffsetDefault(void) {
    return g_actorDefaultOffsetValue;
}

/** Thin wrapper forwarding base and an offset of it to Barrel_UpdateActorController. */
void Gobjinst_UpdateActorController(LevelActor *base) {
    Barrel_UpdateActorController(base, &base->behaviorFlags);
}

/** Set or clear status bit two according to the supplied boolean. */
void Gobjinst_SetAttachmentEffectBitTwo(void *object, int enabled) {
    ActorEffectFlagsView *object_record = object;
    unsigned int *flags = &object_record->effectFlags;
    if (enabled) {
        *flags |= 2;
    } else {
        *flags &= ~2U;
    }
}

s32 Gobjinst_GetModelRenderMode(void *typedActor) {
    void **modelResource;
    char *modelMetadata;
    s32 result;

    result = -1;
    modelResource = Gobjinst_RequestAnimatedModelVariant(typedActor, ((LevelActor *)typedActor)->team);
    if (modelResource != 0) {
        modelMetadata = SetN64_GetPackSection((int *)*modelResource, 5);
        result = ((struct ActorFrameMetadata *)modelMetadata)->renderMode;
        Cache_UnlockResource(0, modelResource);
    }
    return result;
}
