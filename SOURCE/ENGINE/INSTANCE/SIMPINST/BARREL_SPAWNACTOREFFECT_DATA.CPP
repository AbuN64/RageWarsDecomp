#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/OBJB.H"
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
#include "COMMON/SHARED_GAMESLOT.H"
#define g_gameSettingsView (*(s32 *)&g_gameSettings)

extern void Cache_ReleaseResource(void *cache, void *resource);

/** Clear the word at object offset 0x1C4. */
void Simpinst_ClearCachedResource(void *staticObject) {
    ((ObjB *)(staticObject))->cached = 0;
}

CQuatern Insthdr_BuildActorGroundRotation(char *obj);
CQuatern Simpinst_BuildGroundRotation(void *actor) {
    return Insthdr_BuildActorGroundRotation(actor);
}


extern ScalarFloatView g_simpleObjectScaleTransitionFactor;

extern ScalarFloatView g_simpleObjectScaleTransitionTarget;

extern f32 g_frameElapsedTime;

extern struct MemoryUsageStats g_defaultCameraSurfaceType;


void Simpinst_UpdateModelAndScale(void *staticObject) {
    char *o = (char *) staticObject;
    f32 elapsedScaleTime;
    f32 threshold;
    f32 final_value;

    ((ObjB *)(o))->type = Simpinst_SelectModelVariant(staticObject);
    ((ObjB *)(o))->material = ((PropGeometry *)(((ObjB *)(o))->definition))->material;

    if (g_gameSettings.simpleObjectsPaused == 0) {
        char *state = ((ObjB *)(o))->definition;
        if (*(s32 *)state == 12) {
            ((ObjB *)(o))->frameDelta = g_frameElapsedTime * ((PropGeometry *)(state))->speed;
        } else if (((ObjB *)(o))->flags & 0x10) {
            elapsedScaleTime = ((ObjB *)(o))->scaleTime + g_frameElapsedTime * g_simpleObjectScaleTransitionTiming;
            threshold = (&g_simpleObjectScaleTransitionTiming)[1];
            ((ObjB *)(o))->scaleTime = elapsedScaleTime;
            if (elapsedScaleTime < threshold) {
                ((ObjB *)(o))->scale = elapsedScaleTime * g_simpleObjectScaleTransitionFactor.value;
            } else {
                final_value = g_simpleObjectScaleTransitionTarget.value;
                ((ObjB *)(o))->flags &= 0xFFEF;
                ((ObjB *)(o))->scale = final_value;
            }
        }

        if (((ObjB *)(o))->room != 0) {
            ((ObjB *)(o))->scene = ((MenuRules *)(((ObjB *)(o))->room))->locked;
        } else {
            ((ObjB *)(o))->scene = g_defaultCameraSurfaceType.value;
        }
    }
}


void Simpinst_UpdateScaleTransition(ObjB *staticObject) {
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

void Simpinst_UpdateAnimationFrameDelta(ObjB *staticObject) {
    void *p = staticObject->definition;
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

    if (*(s32 *)((ObjB *)o)->definition == 8) {
        BuildYawMatrix(matrix, g_world.elapsed);
    } else {
        BuildYawMatrix(matrix, ((ObjB *)o)->angle);
    }

    ScaleMatrixLocal(matrix, ((ObjB *)(o))->scale, ((ObjB *)(o))->scale, ((ObjB *)(o))->scale);

    Graphu64_LimitVectorLength(&((ObjB *)(o))->position.x, 20000.0f);

    TranslateMatrix((char *) matrix, ((ObjB *)(o))->position.x, ((ObjB *)(o))->position.y + ((ObjB *)(o))->height, ((ObjB *)(o))->position.z);

    SwapMatrixUpForward(matrix);

    Graphu64_ConvertMatrixToFixed(matrix, &((ObjB *)o)->matrices[g_lightingBufferIndex]);
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

    if (modelVariant != ((ObjB *)(staticObject))->loadedType) {
        resource = Cache_RequestResource(0, ((ObjB *)(staticObject))->animationKey,
                                ((ObjB *)(staticObject))->animationKey, 24,
                                0, 0, 0, &g_simpleObjectModelResourceTagData + 4, 1);
        if (resource != 0) {
            key = SetN64_GetDirectoryEntry(*resource, ((ObjB *)(staticObject))->animationKey, 1);
            Cache_ReleaseResource(0, resource);
            found = Cache_RequestWordCountedResource(0, &modelIndexResource, key, g_simpModelsIndexText, 1);
            if (found != 0) {
                ((ObjB *)(staticObject))->resource = SetN64_LocatePackSection((s32)modelIndexResource, key,
                                                    modelVariant % *(s32 *)modelIndexResource,
                                                    &((ObjB *)(staticObject))->resourceSize);
                ((ObjB *)(staticObject))->loadedType = modelVariant;
                Cache_ReleaseResource(0, (void *)found);
            }
        }
    }
    if (((ObjB *)(staticObject))->resource != 0) {
        return Cache_RequestResource(0, ((ObjB *)(staticObject))->resource,
                             ((ObjB *)(staticObject))->resource, ((ObjB *)(staticObject))->resourceSize,
                             0, 0, &g_simpleModelResourceCallbackAddress, g_simpModelText, 0);
    }
    return 0;
}


extern s32 Scene_GetModelIdAtIndex(void *world, s32 modelIndex);

s32 Simpinst_SelectModelVariant(ObjB *staticObject) {
    void *obj;
    s32 value;
    s32 index;

    obj = staticObject->definition;
    if (*(s32 *)obj == 12) {
        return 0;
    }

    value = ((PropGeometry *)(obj))->variant;
    index = Scene_GetModelIdAtIndex(&g_world, staticObject->id);
    if (index < 1707) {
        if (index < 1705) {
            return value;
        }
        if (g_gameSettingsView & 0x800) {
            value = 1;
        }
        if (g_gameSettingsView & 0x1000) {
            value = 2;
        }
    }
    return value;
}

struct ResourceNodePair; struct CacheResourceNode; extern void Cache_ReplaceResourcePairFirst(s32 unusedCache, struct ResourceNodePair *resourcePair, struct CacheResourceNode *replacementResource);

void Simpinst_BuildLitGeometryResource(void *wanted, s32 **resourcePair) {
    s32 sourceGeometryResource;
    sourceGeometryResource = **resourcePair;
    Cache_ReplaceResourcePairFirst(0, resourcePair, Lighting_BuildLitModel(sourceGeometryResource, *((ObjB *)(wanted))->block, &((ObjB *)(wanted))->bounds, (s32)((char *)&((ObjB *)wanted)->matrices[g_lightingBufferIndex]), 0, wanted));
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
