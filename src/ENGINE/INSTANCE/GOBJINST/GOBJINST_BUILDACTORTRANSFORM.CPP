#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/MODEL_RENDER.H"
#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"
#include "COMMON/LISTHEADER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS.H"
#include "TYPES.H"
#include "ENGINE/INSTANCE/GOBJINST.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "ENGINE/LISTS.H"

extern s32 Cinema_IsSequenceInWindow(void);
extern CQuatern Gobjinst_BuildActorDirectionTilt(void *input);


extern void MultiplyQuaternions(CQuatern *productQuaternion, CQuatern *leftQuaternion, CQuatern *rightQuaternion);
extern void MatrixFromQuaternion(f32 *q, f32 *m);
extern void ScaleMatrixLocal(void *matrix, f32 sx, f32 sy, f32 sz);
extern s32 Graphu64_LimitVectorLength(f32 *vectorComponents, f32 maximumLength);
extern void TranslateMatrix(char *, f32, f32, f32);
extern void SwapMatrixUpForward(void *);


void Gobjinst_BuildActorTransform(void *levelActor) {
    CQuatern trig;
    CQuatern product;
    CQuatern copy;
    CQuatern *copy_ptr;
    CQuatern *product_ptr;
    char *transform;
    f32 scale;
    f32 sine;
    f32 angle;

    copy = ((struct LevelActor *)(levelActor))->rotation;
    copy_ptr = &copy;
    if (Cinema_IsSequenceInWindow() != 0) {
        copy = Gobjinst_BuildActorDirectionTilt(levelActor);
    }

    angle = ((struct LevelActor *)(levelActor))->yaw;
    scale = (0.5f);
    sine = Gu_Sinf(angle * scale);
    trig.x = 0.0f;
    trig.y = sine;
    trig.z = 0.0f;
    angle = ((struct LevelActor *)(levelActor))->yaw * scale;
    g_turretAimSine = sine;
    trig.w = Math_Cosf(angle);

    product_ptr = &product;
    MultiplyQuaternions(product_ptr, &trig, copy_ptr);
    transform = &((struct LevelActor *)(levelActor))->transform[0];
    MatrixFromQuaternion(product_ptr, transform);
    ScaleMatrixLocal(transform, ((struct LevelActor *)(levelActor))->scale.x,
                    ((struct LevelActor *)(levelActor))->scale.y,
                    ((struct LevelActor *)(levelActor))->scale.z);
    Graphu64_LimitVectorLength(&((struct LevelActor *)(levelActor))->position0.x, 20000.0f);
    TranslateMatrix(transform, ((struct LevelActor *)(levelActor))->position0.x,
                   ((struct LevelActor *)(levelActor))->position0.y,
                   ((struct LevelActor *)(levelActor))->position0.z);
    SwapMatrixUpForward(transform);
}

void Gobjinst_NoOperation(void) {
}

void Gobjinst_QueueAnimation(void *actorStorage, unsigned int animationIndex)
{
  ((struct LevelActor *)(actorStorage))->nextAnimation = animationIndex;
  ((struct LevelActor *)(actorStorage))->animationPending = 0;
  if ((((struct LevelActor *)(actorStorage))->animation) != animationIndex)
  {
    ((struct LevelActor *)(actorStorage))->animationChanged = 1;
  }
}

void Gobjinst_RestartAnimation(void *actorAnimationState) {
    (((struct ActorAnimationResetState *) ((s8 *) actorAnimationState))->animationChanged) = 1;
    (((struct ActorAnimationResetState *) ((s8 *) actorAnimationState))->animationTime) = 0;
    (((struct ActorAnimationResetState *) ((s8 *) actorAnimationState))->animationPending) = 0;
    (((struct ActorAnimationResetState *) ((s8 *) actorAnimationState))->flags) = (s32) ((((struct ActorAnimationResetState *) ((s8 *) actorAnimationState))->flags) & ~0x400);
}

extern s32 Gobjinst_ChooseAnimationVariant(void *, s32, s32);


s32 Gobjinst_RequestAnimationKind(void *a, s32 c, s32 flag) {
    s32 selectedAnimation = Gobjinst_ChooseAnimationVariant(a, c, -1);

    if (selectedAnimation != -1) {
        return Gobjinst_RequestAnimationIndex(a, selectedAnimation, flag);
    }
    return 0;
}

extern void Gobjinst_QueueAnimation(void *actor, u32 animationId);

s32 Gobjinst_RequestAnimationIndex(void *levelActor, s32 animationIndex, s32 allowDuringBlend) {
    if (animationIndex < 0 || (allowDuringBlend == 0 && (((struct LevelActor *)(levelActor))->flags & 0x400))) {
        return 0;
    }
    Gobjinst_QueueAnimation(levelActor, (u32) animationIndex);
    return 1;
}

extern void Lists_ClearWeightedTable(WeightedTable *object);
extern s32 Gobjinst_ChooseAnimationVariant(void *owner, s32 animationKind, s32 excludedEntry);

s16 Gobjinst_ChooseAvailableAnimationKind(void *actor, s16 *callback, s32 excludedAnimation) {
    WeightedTable eligibleKinds;
    u16 animationKind;

    Lists_ClearWeightedTable(&eligibleKinds);
    animationKind = *(u16 *) callback;
    if (*callback != -1) {
        do {
            if (Gobjinst_ChooseAnimationVariant(actor, (s32) (s16) animationKind, excludedAnimation) != -1) {
                Lists_AppendWeightedEntry(&eligibleKinds, callback[0], callback[1]);
            }
            callback += 2;
            animationKind = *(u16 *) callback;
        } while (*callback != -1);
    }
    return Lists_ChooseWeightedTableEntry(&eligibleKinds);
}

extern s32 *Gobjinst_RequestAnimatedModelVariant(void *actor, s8 variantIndex);
extern s32 Gobjinst_BuildActorPose(void *actor, s32 modelPack, void *model);
extern void Cache_UnlockResource(s32 cache, s32 resource);

s32 Gobjinst_BuildAnimatedPose(void *actorStorage, s32 resourceRequestMode)
{
  void *resource;
  s32 *entry;
  s32 value;
  s32 result;
  result = 0;
  if ((((struct LevelActor *)(actorStorage))->flags) & 0x40000)
  {
    if (resource)
    {
      resource = Cache_RequestResource(0, ((struct LevelActor *)(actorStorage))->resource, ((struct LevelActor *)(actorStorage))->resource, ((struct LevelActor *)(actorStorage))->resourceFlags, 0, 0, 0, (&g_actorAnimatedModelResourceTuning) + 4, resourceRequestMode);
    }
    else
    {
      resource = Cache_RequestResource(0, ((struct LevelActor *)(actorStorage))->resource, ((struct LevelActor *)(actorStorage))->resource, ((struct LevelActor *)(actorStorage))->resourceFlags, 0, 0, 0, (&g_actorAnimatedModelResourceTuning) + 4, resourceRequestMode);
    }
    if (resource == 0)
    {
      return result;
    }
    entry = Gobjinst_RequestAnimatedModelVariant(actorStorage, ((struct LevelActor *)(actorStorage))->team);
    if (entry != 0)
    {
      value = *entry;
      result = Gobjinst_BuildActorPose(actorStorage, value, SetN64_GetPackSection(*((void **) resource), 0));
      Cache_UnlockResource(0, (s32) entry);
    }
    Cache_UnlockResource(0, (s32) resource);
  }
  return result;
}

void Gobjinst_RotatePoseMatrixBuffers(void *actorRenderState) {
    s32 previousPoseMatrices;
    previousPoseMatrices = (((struct ActorPoseBufferState *) ((s8 *) actorRenderState))->poseMatrices);
    (((struct ActorPoseBufferState *) ((s8 *) actorRenderState))->poseMatrices) = 0;
    (((struct ActorPoseBufferState *) ((s8 *) actorRenderState))->clearedWordFirst) = 0;
    (((struct ActorPoseBufferState *) ((s8 *) actorRenderState))->clearedWordSecond) = 0;
    (((struct ActorPoseBufferState *) ((s8 *) actorRenderState))->flags) = (s32) ((((struct ActorPoseBufferState *) ((s8 *) actorRenderState))->flags) & ~0x200);
    (((struct ActorPoseBufferState *) ((s8 *) actorRenderState))->previousPoseMatrices) = previousPoseMatrices;
}

extern s32 g_lightingBufferIndex;
extern void GameObject_DrawActorShadow(char *obj, s32 unused, char *info);
extern void Gobjinst_SpawnAnimatedModelViewEffect(void *actor, void *lookup);

void Gobjinst_DrawMaskedModel(void *actor, void *unusedShadowContext, void *renderSettings) {
    s8 index;
    s32 one;

    index = ((struct LevelActor *)(actor))->team;
    if (index != -1) {
        ((struct LevelActor *)(actor))->mask = 1 << index;
        if (((struct ActorRenderSettings *)(renderSettings))->drawShadow != 0) {
            GameObject_DrawActorShadow(actor, unusedShadowContext, renderSettings);
        }
        if (*(s32 *)renderSettings != 0) {
            one = 1;
            Geometry_DrawModelResource(((struct ActorRenderSettings *)(renderSettings))->view,
                          ((struct LevelActor *)(actor))->animationMatrices, one,
                          (char *)&((LevelActor *)actor)->lighting + (((g_lightingBufferIndex << one) + g_lightingBufferIndex) << 3),
                          0, ((struct LevelActor *)(actor))->renderPass);
            Gobjinst_SpawnAnimatedModelViewEffect(actor, renderSettings);
        }
    }
}


void Gobjinst_DrawMaskedModelWithLighting(void *actor, void *unusedShadowContext, void *renderSettings, Block24 *lighting) {
    s8 index;
    s32 one;

    ((ActorLightingBlockView *)actor)->blocks[g_lightingBufferIndex] = *lighting;
    index = ((struct LevelActor *)(actor))->team;
    if (index != -1) {
        ((struct LevelActor *)(actor))->mask = 1 << index;
        if (((struct ActorRenderSettings *)(renderSettings))->drawShadow != 0) {
            GameObject_DrawActorShadow(actor, unusedShadowContext, renderSettings);
        }
        if (*(s32 *)renderSettings != 0) {
            one = 1;
            Geometry_DrawModelResource(((struct ActorRenderSettings *)(renderSettings))->view,
                          ((struct LevelActor *)(actor))->animationMatrices, one,
                          (char *)&((LevelActor *)actor)->lighting + (((g_lightingBufferIndex << one) + g_lightingBufferIndex) << 3),
                          0, ((struct LevelActor *)(actor))->renderPass);
            Gobjinst_SpawnAnimatedModelViewEffect(actor, renderSettings);
        }
    }
}
