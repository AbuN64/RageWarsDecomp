#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ACCESS_S8_10F.H"
#include "TYPES.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "COMMON/OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/APPROACHLOCATION.H"
#include "COMMON/PPDECOM_UNPACKRESOURCE.H"
#include "COMMON/WORLD.H"
#include "COMMON/OBJRECAT4V7.H"
#include <ultra64.h>
#include "ENGINE/INSTANCE/GOBJINST.H"
#include "GAME/BUILDDIRECTIONMATRIX.H"

/* GOBJINST_2.CPP */
extern s32 SetN64_GetDirectoryEntry(s32 *directory, s32 bankOffset, s32 level);
extern s32 SetN64_LocatePackSection(s32, s32, s32, s32 *);
extern void Gastate_ResetAnimationReference(void *);
extern s32 Gobjinst_ChooseAnimationVariant(void *, s32, s32);

void Gobjinst_LoadModel(void *actorStorage, s32 *modelDirectory, s32 directoryBank, s32 extra) {
    s32 *animationMetadata;
    void **resource1;
    void **resource2;
    s32 *entry;
    void *modelBounds;
    void *node;
    s32 key;
    s32 found;

    ((LevelActor *)actorStorage)->resourceHandle = -1;
    ((LevelActor *)actorStorage)->resourceState = 0;
    ((LevelActor *)actorStorage)->resourceWindow = 0;
    ((LevelActor *)actorStorage)->flags &= 0xFFFBFFFF;
    key = SetN64_GetDirectoryEntry(modelDirectory, directoryBank, (u16)((LevelActor *)actorStorage)->modelIndex);
    resource1 = Cache_RequestResource(0, key, key, 24, 0, 0, 0, &g_gameObjectAnimIndexText, 1);
    if (resource1 != 0) {
        entry = *resource1;
        ((LevelActor *)actorStorage)->animationKey = SetN64_GetDirectoryEntry(entry, key, 1);
        found = Cache_RequestWordCountedResource(0, &animationMetadata, ((LevelActor *)actorStorage)->animationKey, &s_animModelsIndexText, 1);
        if (found != 0) {
            ((LevelActor *)actorStorage)->stateE7 = (u8)*animationMetadata;
            ((LevelActor *)actorStorage)->resourceAlignment = ((*animationMetadata * 4) + 15) & ~7;
            Cache_UnlockResource(0, (void *)found);
        }
        ((LevelActor *)actorStorage)->resource = SetN64_LocatePackSection((s32)entry, key, 0, &((LevelActor *)actorStorage)->resourceFlags);
        ((LevelActor *)actorStorage)->resourceKey = SetN64_GetDirectoryEntry(entry, key, 2);
        resource2 = Cache_RequestResource(0, ((LevelActor *)actorStorage)->resource,
                                 ((LevelActor *)actorStorage)->resource, ((LevelActor *)actorStorage)->resourceFlags,
                                 0, 0, 0, &g_gameObjectResetAnimInfoText, 1);
        if (resource2 != 0) {
            node = *resource2;
            modelBounds = SetN64_GetPackSection(node, 0);
            ((LevelActor *)actorStorage)->controllerUpdate(actorStorage, &((LevelActor *)actorStorage)->behaviorFlags);
            Graphu64_TransformBoundingBox(&((LevelActor *)actorStorage)->transform, (s32)modelBounds, &((LevelActor *)actorStorage)->bounds);
            Gastate_ResetAnimationReference(&((LevelActor *)actorStorage)->animationTime);
            Gastate_ResetAnimationReference((char *)&((LevelActor *)actorStorage)->animationReference);
            ((LevelActor *)actorStorage)->stateE6 = (u8)((ResourceManagerState *)SetN64_GetPackSection(node, 1))->count;
            ((LevelActor *)actorStorage)->flags |= 0x40000;
            if (extra > 0) {
                extra = Gobjinst_ChooseAnimationVariant(actorStorage, extra, -1);
            } else {
                extra = -extra;
            }
            if (extra == -1) {
                extra = 0;
            }
            ((LevelActor *)actorStorage)->nextAnimation = extra;
            ((LevelActor *)actorStorage)->animationPending = 0;
            if (((LevelActor *)actorStorage)->animation != extra) {
                ((LevelActor *)actorStorage)->animationChanged = 1;
            }
            ((LevelActor *)actorStorage)->animationState = -1;
            ((LevelActor *)actorStorage)->lean = extra;
            Cache_UnlockResource(0, resource2);
        }
        Cache_UnlockResource(0, resource1);
    }
}

/* GOBJINST_3.CPP */
/* Update or blend object rotation when the movement state permits it. */
CQuatern Insthdr_BuildActorGroundRotation(char *obj);

 /* extern */
unsigned int InstHdr_UsesGroundRotation(char *object);

 /* extern */
s32 InstHdr_GetActorMotionState(void *);

 /* extern */
void Graphu64_InterpolateQuaternionWithLinearFallback(struct CQuatern_t *, f32, struct CQuatern_t *, struct CQuatern_t *);

 /* extern */

 /* extern */
extern f32 g_actorGroundRotationBlendRates[], g_actorRotationBlendAndResourceTuning[], g_frameElapsedTime;

typedef struct CollisionInfo CollisionInfo;

extern CollisionInfo g_defaultActorCollisionInfo;

extern ScreenMessageTextView g_currentActorInstance;

extern s32 Unicol_MoveActorWithCollision(void *actor, CVector3 pos, CollisionInfo *motionSettings);

extern void Link_DispatchObjectLinks(s32 objectId, s32 triggerFlags, void *actor);

extern void Link_DispatchActorLinks(void *actor, s32 triggerFlags, void *eventContext);

void Gobjinst_UpdateActorRootDisplacement(Actor36 *actor) {
    CVector3 before, after;
    u32 flags, mode;
    void **resource;
    void *box;
    flags = actor->flags;
    if (!(flags & 0x40000)) return;
    if (g_world.mode == 4 && !(flags & 0x2000)) return;
    mode = flags & 0x300000;
    before = actor->position;
    Gobjinst_AdvanceActorRootMotion(actor);
    after = actor->position;
    actor->position = before;
    if (mode == 0 && *actor->kind != 0) {
        Graphu64_SubtractVectors(&after, &after, &before);
        Graphu64_AddVec3(&after, &after, &actor->displacement);
        Gobjinst_MoveActorWithContactCallback((void *)actor, &after);
        if (*actor->kind == 1) {
            Scene_UpdateMovementTriggers(&g_world, actor, &before, &actor->position);
        }
    }
    Gobjinst_UpdateActorGroundRotation((void *)actor);
    resource = Cache_RequestResource(0, actor->size, actor->size, actor->alignment, 0, 0, 0, s_actorModelAllocationTag, 1);
    if (resource != 0) {
        box = SetN64_GetPackSection(*resource, 0);
        actor->update(actor, actor->state);
        Graphu64_TransformBoundingBox(actor->matrix, box, &actor->box);
        Cache_UnlockResource(0, (void *)resource);
    }
}

void Gobjinst_UpdateActorGroundRotation(ActorModelLoadState *actor) {
    CQuatern vec;
    f32 rotationBlend;
    f32 rotationBlendRate;
    s32 resetRotationFlag;
    s32 rotationState;
    s32 actorFlags;
    s32 flags;
    void *rotation;
    void *rotationDestination;
    actorFlags = actor->flags;
    flags = actorFlags & 0x300000;
    if (!(actorFlags & 1) && (rotationState = InstHdr_GetActorMotionState(actor), (actor->modelHeader != NULL)) && (vec = Insthdr_BuildActorGroundRotation(actor), resetRotationFlag = actor->modelHeader->spreadHighWord & 1, (InstHdr_UsesGroundRotation(actor) != 0))) {
        if (resetRotationFlag != 0) {
            vec.x = vec.y = vec.z = 0.0f;
            vec.w = g_actorGroundRotationUnitW;
        }
        if (flags) {
            if ((!(actor->flags & 0x1000) && (rotationDestination = actor->rotation, (rotationState != 0))) || (rotationDestination = actor->rotation, (resetRotationFlag != 0))) {
                Graphu64_ApproachQuaternion(rotationDestination, &vec);
            }
        } else {
            if ((rotationState != 0) && !(actor->flags & 0x1000)) {
                rotationBlend = g_frameElapsedTime; rotationBlendRate = g_actorGroundRotationBlendRates[0];
            } else {
                rotationBlend = g_frameElapsedTime; rotationBlendRate = g_actorGroundRotationBlendRates[1];
            }
            rotationBlend = rotationBlend * rotationBlendRate;
            rotation = actor->rotation;
            if (rotationBlend > g_actorRotationBlendAndResourceTuning[0]) {
                rotationBlend = g_actorRotationBlendAndResourceTuning[0];
            }
            Graphu64_InterpolateQuaternionWithLinearFallback(rotation, rotationBlend, rotation, &vec);
        }
    }
}

void Gobjinst_MoveActorWithContactCallback(char *actor, CVector3 *destination) {
    CollisionInfo *collision;
    u16 *old_contact;
    s32 collided;
    f32 saved;
    void (*callback)(void *, void *, CollisionInfo *);

    if ((((ActorModelResourceView *)(actor))->flags & 0x10000) && ((ActorModelResourceView *)(actor))->collisionResource != 0) {
        collision = ((ActorCollisionResourceView *)(((ActorModelResourceView *)(actor))->collisionResource))->collisionInfo;
        if (collision == 0) {
            collision = &g_defaultActorCollisionInfo;
        }
        saved = ((ActorCollisionDataView *)(collision))->collisionParams.value;
        if ((u32)(((ActorModelResourceView *)(actor))->typeId - 11020) < 8) {
            ((ActorCollisionDataView *)(collision))->collisionParams.word = 0;
        }
        old_contact = ((ActorModelResourceView *)(actor))->model;
        collided = Unicol_MoveActorWithCollision(actor, *destination, collision);
        if (old_contact != ((ActorModelResourceView *)(actor))->model) {
            ((ActorModelResourceView *)(actor))->previousModel = old_contact;
        }
        ((ActorCollisionDataView *)(collision))->collisionParams.value = saved;
        if (old_contact != 0 && ((ActorModelResourceView *)(actor))->model != 0 &&
                *old_contact != *((ActorModelResourceView *)(actor))->model &&
                *((ActorModelResourceView *)(actor))->definition == 1) {
            Link_DispatchObjectLinks((s32)old_contact, 128, actor);
            Link_DispatchObjectLinks((s32)((ActorModelResourceView *)(actor))->model, 64, actor);
        }
        if (collided != 0 && !(((ActorModelResourceView *)(actor))->flags & 0x300000) &&
                *((ActorModelResourceView *)(actor))->definition == 1 && g_currentActorInstance.text != 0 &&
                *g_currentActorInstance.text == 1) {
            Link_DispatchActorLinks(g_currentActorInstance.text, 32, actor);
        }
        callback = ((struct ActorModelCallbackView *) ((char *) actor))->callback;
        if (callback != 0) {
            callback(actor, &((LevelActor *)actor)->behaviorFlags, collision);
        }
    } else {
        ((ActorModelResourceView *)(actor))->position0 = *destination;
    }
}
