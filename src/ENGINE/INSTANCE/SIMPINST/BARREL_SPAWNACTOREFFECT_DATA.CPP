#include "COMMON/WORLD.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "WORLD/STATIC_MODEL_INSTANCE_VIEWS.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/PROPGEOMETRY.H"
#include "TYPES.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "ACTORS/LIGHTING_BUILDLITMODEL.H"
#include "GAME/BUILDDIRECTIONMATRIX.H"
#include "WORLD/BARREL_SPAWNACTOREFFECT_DATA.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "include_asm.h"

extern void Cache_ReleaseResource(void *cache, void *resource);

/** Clear the word at object offset 0x1C4. */
void Simpinst_ClearCachedResource(void *staticObject) {
    ((StaticObject *)(staticObject))->cached = 0;
}

CQuatern Insthdr_BuildActorGroundRotation(void *);
CQuatern Simpinst_BuildGroundRotation(void *actor) {
    return Insthdr_BuildActorGroundRotation(actor);
}


extern ScalarFloatView g_simpleObjectScaleTransitionFactor;

extern ScalarFloatView g_simpleObjectScaleTransitionTarget;

extern f32 g_frameElapsedTime;

extern struct MemoryUsageStats g_defaultCameraSurfaceType;
extern ModelEffectSpawnState g_simpleObjectPauseState;

void Simpinst_UpdateModelAndScale(void *staticObject) {
    char *o = (char *) staticObject;
    f32 elapsedScaleTime;
    f32 threshold;
    f32 final_value;

    ((StaticObject *)(o))->model = Simpinst_SelectModelVariant(staticObject);
    ((StaticObject *)(o))->material = ((PropGeometry *)(((StaticObject *)(o))->type))->material;

    if (g_simpleObjectPauseState.paused == 0) {
        char *state = ((StaticObject *)(o))->type;
        if (*(s32 *)state == 12) {
            ((StaticObject *)(o))->frameDelta = g_frameElapsedTime * ((PropGeometry *)(state))->speed;
        } else if (((StaticObject *)(o))->flags & 0x10) {
            elapsedScaleTime = ((StaticObject *)(o))->scaleTime + g_frameElapsedTime * g_simpleObjectScaleTransitionTiming;
            threshold = (&g_simpleObjectScaleTransitionTiming)[1];
            ((StaticObject *)(o))->scaleTime = elapsedScaleTime;
            if (elapsedScaleTime < threshold) {
                ((StaticObject *)(o))->scale = elapsedScaleTime * g_simpleObjectScaleTransitionFactor.value;
            } else {
                final_value = g_simpleObjectScaleTransitionTarget.value;
                ((StaticObject *)(o))->flags &= 0xFFEF;
                ((StaticObject *)(o))->scale = final_value;
            }
        }

        if (((StaticObject *)(o))->room != 0) {
            ((StaticObject *)(o))->scene = ((MenuRules *)(((StaticObject *)(o))->room))->locked;
        } else {
            ((StaticObject *)(o))->scene = g_defaultCameraSurfaceType.value;
        }
    }
}


void Simpinst_UpdateScaleTransition(StaticObject *staticObject) {
    f32 elapsedScaleTime;
    f32 threshold;
    f32 final_value;

    if (staticObject->flags & 0x10) {
        elapsedScaleTime = staticObject->scaleTime +
                  g_frameElapsedTime * g_simpleObjectAlternateScaleTransitionTiming;
        threshold = (&g_simpleObjectAlternateScaleTransitionTiming)[1];
        staticObject->scaleTime = elapsedScaleTime;
        if (elapsedScaleTime < threshold) {
            staticObject->scale = elapsedScaleTime * g_simpleObjectAlternateScaleTransitionFactor;
            return;
        }
        final_value = g_simpleObjectAlternateScaleTransitionTarget;
        staticObject->flags &= 0xFFEF;
        staticObject->scale = final_value;
    }
}

/** Stores g_frameElapsedTime times the float at 0x20 of the object at 0x18 in the float at 0x1A4. */

void Simpinst_UpdateAnimationFrameDelta(StaticObject *staticObject) {
    void *p = staticObject->type;
    staticObject->frameDelta = (g_frameElapsedTime) * (((PropGeometry *)(p))->speed);
}

extern void ScaleMatrixLocal(void *matrix, f32 sx, f32 sy, f32 sz);
extern s32 Graphu64_LimitVectorLength(f32 *vectorComponents, f32 maximumLength);
extern void TranslateMatrix(char *object, float x, float y, float z);
extern void SwapMatrixUpForward(void *object);
extern void Graphu64_ConvertMatrixToFixed(void *src, void *dst);


void Simpinst_BuildObjectTransform(void *staticObject) {
    char *o = (char *) staticObject;
    f32 matrix[16];

    if (*(s32 *)((StaticObject *)o)->type == 8) {
        BuildYawMatrix(matrix, g_world.elapsed);
    } else {
        BuildYawMatrix(matrix, ((StaticObject *)o)->angle);
    }

    ScaleMatrixLocal(matrix, ((StaticObject *)(o))->scale, ((StaticObject *)(o))->scale, ((StaticObject *)(o))->scale);

    Graphu64_LimitVectorLength(&((StaticObject *)(o))->position.x, 20000.0f);

    TranslateMatrix((char *) matrix, ((StaticObject *)(o))->position.x, ((StaticObject *)(o))->position.y + ((StaticObject *)(o))->height, ((StaticObject *)(o))->position.z);

    SwapMatrixUpForward(matrix);

    Graphu64_ConvertMatrixToFixed(matrix, &((StaticObject *)o)->matrices[g_lightingBufferIndex]);
}

extern void **Cache_RequestWordCountedResource(s32 unusedCache, void **resourceHandle, s32 resourceKey, void *loadTag, s32 direct);
extern s32 SetN64_GetDirectoryEntry(s32 *, s32, s32);
extern s32 SetN64_LocatePackSection(s32, s32, s32, s32 *);

extern char g_simpleModelResourceCallbackAddress;

void **Simpinst_RequestModelVariant(void *staticObject, s32 modelVariant) {
    void *modelIndexResource;
    void **resource;
    s32 key;
    s32 found;

    if (modelVariant != ((SliderStepRecord *)(staticObject))->activeState) {
        resource = Cache_RequestResource(0, ((Access_s32_50 *)(staticObject))->field,
                                ((Access_s32_50 *)(staticObject))->field, 24,
                                0, 0, 0, &g_simpleObjectModelResourceTagData + 4, 1);
        if (resource != 0) {
            key = SetN64_GetDirectoryEntry(*resource, ((Access_s32_50 *)(staticObject))->field, 1);
            Cache_ReleaseResource(0, resource);
            found = Cache_RequestWordCountedResource(0, &modelIndexResource, key, g_simpModelsIndexText, 1);
            if (found != 0) {
                ((StaticObject *)(staticObject))->resource = SetN64_LocatePackSection((s32)modelIndexResource, key,
                                                    modelVariant % *(s32 *)modelIndexResource,
                                                    &((Access_s32_5C *)(staticObject))->field);
                ((SliderStepRecord *)(staticObject))->activeState = modelVariant;
                Cache_ReleaseResource(0, (void *)found);
            }
        }
    }
    if (((StaticObject *)(staticObject))->resource != 0) {
        return Cache_RequestResource(0, ((StaticObject *)(staticObject))->resource,
                             ((StaticObject *)(staticObject))->resource, ((Access_s32_5C *)(staticObject))->field,
                             0, 0, &g_simpleModelResourceCallbackAddress, g_simpModelText, 0);
    }
    return 0;
}


extern s32 g_gameSettings;
extern s32 Scene_GetModelIdAtIndex(void *world, s32 modelIndex);

s32 Simpinst_SelectModelVariant(StaticObject *staticObject) {
    void *obj;
    s32 value;
    s32 index;

    obj = staticObject->type;
    if (*(s32 *)obj == 12) {
        return 0;
    }

    value = ((PropGeometry *)(obj))->variant;
    index = Scene_GetModelIdAtIndex(&g_world, staticObject->id);
    if (index < 1707) {
        if (index < 1705) {
            return value;
        }
        if (g_gameSettings & 0x800) {
            value = 1;
        }
        if (g_gameSettings & 0x1000) {
            value = 2;
        }
    }
    return value;
}

extern void Cache_ReplaceResourcePairFirst(s32 a, s32 **b, s32 c);

void Simpinst_BuildLitGeometryResource(void *wanted, s32 **resourcePair) {
    s32 sourceGeometryResource;
    sourceGeometryResource = **resourcePair;
    Cache_ReplaceResourcePairFirst(0, resourcePair, Lighting_BuildLitModel(sourceGeometryResource, *((StaticObject *)(wanted))->renderResource, &((StaticObject *)(wanted))->effect[0], (s32)((char *)&((StaticObject *)wanted)->matrices[g_lightingBufferIndex]), 0, wanted));
}

#if !(defined(VERSION_US_REV1))
const float g_simpleObjectScaleTransitionConstants[4] = {
    0.06666667f, 0.75f, 0.46666667f, 0.35f,
};
#endif

#if defined(VERSION_US_REV1)
const float g_simpleObjectScaleTransitionConstantsUsRev1[4] = {
    0.06666667f, 0.75f, 0.46666667f, 0.35f,
};
#endif

#if !(defined(VERSION_US_REV1))
const float g_simpleObjectAlternateScaleTransitionConstants[4] = {
    0.06666667f, 0.75f, 0.46666667f, 0.35f,
};
#endif

#if defined(VERSION_US_REV1)
const float g_simpleObjectAlternateScaleTransitionConstantsUsRev1[4] = {
    0.06666667f, 0.75f, 0.46666667f, 0.35f,
};
#endif
