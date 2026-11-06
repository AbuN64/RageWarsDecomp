#include "Common/objb.h"
#include "Common/actor_definition.h"
#include "Common/model_render.h"
#include "include_asm.h"
#include "Scene/simple_instance_record.h"
#include "Common/sharedplayer.h"
#include "Common/propgeometry.h"
#include "World/static_model_instance_views.h"
#include "Scene/cache_allocateresourceat.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Common/frustum.h"
#include <PR/gbi.h>
#include "types.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Common/sessionhandlerrow.h"
#include "Game/builddirectionmatrix.h"
#include "System/textload_resettexturecache.h"
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"
#include "Common/ballisticparams.h"
#include "Common/world.h"
#include "Common/triple.h"
#include "Engine/scene_drawtransitioncoloroverlay.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Engine/Instance/Simpinst/simple_drawcachedmodel.h"
#include "Simpinst/simpinst_drawgroundshadow.h"
#include "Common/level_actor.h"
#include "Common/vector4f.h"
#include "Common/math_helpers.h"
#include "Common/legacy_collision_actor.h"
#include "Common/material_tree.h"
#include "Engine/Instance/simpinst.h"
#include "Scene/cache_requestresource.h"
#include "Render/setn64_getpacksection.h"
#include "Particle/particle_spawneffectgroup.h"
#include "Engine/session.h"
#include "Particle/ghot_dispatchattachmenteffects_data.h"
#include "Common/approachlocation.h"
#include "Common/cache_releaseresource.h"
#include "Engine/Instance/Simpinst/simpinst_drawgroundshadow.h"
#include "Particle/particle_releaseownerlistoneeffects.h"
#include "Common/manager.h"
#include "Common/resourcelockstate.h"
#include "Geometry/geometry_drawblendparts.h"
#include "Simpinst/g_simpobjectindextext.h"
#include "Common/shared_gameslot.h"
#include "Actors/lighting_buildlitmodel.h"
#include "World/barrel_spawnactoreffect_data.h"
#include "Common/Lone/g_defaultcamerasurfacetype.h"
#include "Common/weapon_screen_message_operations.h"
#include "Cache/cache.h"
#include "Engine/Instance/gobjinst.h"
#include "Engine/Cache/cache.h"

/* SIMPLE_DRAWCACHEDMODEL.CPP */


void Simple_InitSimpleInstance(ObjB *inst, CROMSimpleInstance *rec, s32 owner, char *segments) {
    CVector3 v;
    inst->state = 3;
    inst->id = rec->type;
    inst->scene = rec->visBits;
    inst->position = rec->position;
    inst->position.y = inst->position.y + 10.24f;
    inst->angle = rec->rotY * (3.1415927f / 127.0f);
    inst->scale = 0.35f;
    inst->height = 0;
    inst->bounds.min.x = rec->position.x - rec->maxRadius;
    inst->bounds.min.y = rec->position.y - rec->maxRadius;
    inst->bounds.min.z = rec->position.z - rec->maxRadius;
    inst->bounds.max.x = rec->position.x + rec->maxRadius;
    inst->bounds.max.y = rec->position.y + rec->maxRadius;
    inst->bounds.max.z = rec->position.z + rec->maxRadius;
    inst->animationKey = owner;
    inst->loadedType = -1;
    inst->resource = 0;
    inst->resourceSize = 0;
    if (rec->variation == 0xFFFF) {
        inst->definition = &g_defaultEffectDefinition;
    } else {
        inst->definition = Scene_GetActorDefinition(&g_world, rec->variation);
    }
    if (rec->region == 0xFFFF) {
        inst->room = 0;
    } else {
        inst->room = segments + (rec->region << 5);
    }
    inst->flags = rec->flags | 2;
    inst->scaleTime = 0;
    inst->frameDelta = 0;
    inst->placementId = rec->id;
    v.x = inst->position.x;
    v.y = inst->position.y + Gobjinst_GetActorHeight(inst) * 0.5f;
    v.z = inst->position.z;
    inst->lights = g_playerModelLighting[0];
    inst->cached = 0;
}

/* Draws a static object through its cached display list, building the cache on first use: emits a branch placeholder, loads the object's model, builds its rotation (the shared g_staticObjectSharedAngle angle for type 8), scale and position raised by its height offset into the current matrix slot, draws the model with its material through Geometry_DrawModelResource and Simpinst_SpawnModelEffect unless the type is 12, ends the list, patches the placeholder to skip past it and calls the cached list. The display list writes match only as block-scoped initialisers taking g_displayListCursor_SimpleDrawcachedmodel++. */

void Simple_DrawCachedModel(ObjB *obj) {
    MatrixF matrix;
    void **resource;
    Gfx *branch;

    Geometry_InvalidateMaterialKeys();
    TextLoad_ResetTextureCache();
    if (obj->cached != 0) {
        gSPDisplayList(g_displayListCursor++, (unsigned int)obj->cached);
        return;
    }
    resource = Simpinst_RequestModelVariant(obj, obj->type);
    if (resource == 0) {
        return;
    }
    obj->cached = g_displayListCursor;
    gSPBranchList(g_displayListCursor++, 0);
    if (obj->definition->kind == 8) {
        BuildYawMatrix(&matrix, g_world.elapsed);
    } else {
        BuildYawMatrix(&matrix, obj->angle);
    }
    ScaleMatrixLocal(&matrix, obj->scale, obj->scale, obj->scale);
    Graphu64_LimitVectorLength(&obj->position, 20000.0f);
    TranslateMatrix(&matrix, obj->position.x, obj->position.y + obj->height, obj->position.z);
    SwapMatrixUpForward(&matrix);
    Graphu64_ConvertMatrixToFixed(&matrix, obj->matrices[g_lightingBufferIndex]);
    if (obj->definition->kind != 12) {
        Geometry_DrawModelResource(resource, obj->matrices[g_lightingBufferIndex], 0, &obj->lights, 0, obj->material);
        Simpinst_SpawnModelEffect(obj, resource);
    }
    gSPEndDisplayList(g_displayListCursor++);
    gSPBranchList(obj->cached++, (unsigned int)g_displayListCursor);
    gSPDisplayList(g_displayListCursor++, (unsigned int)obj->cached);
    Cache_UnlockResource(0, resource);
}

/* SIMPINST_DRAWGROUNDSHADOW.CPP */


/* Places an actor's ground shadow: the shadow size is the smaller of half the vertical offset from
 * InstHdr_GetActorShadowRadius and that minus a tenth of the actor's height above its ground height, vanishing
 * when negative; a transform is built from the actor's orientation, scaled flat by the shadow size,
 * positioned at the ground under the actor, stored as the actor's per-frame matrix and submitted through
 * Geometry_DrawIntensityMask. */

void Simpinst_SpawnModelEffect(ObjB *actor, void **resource) {
    CVector3 position;
    CQuatern rotation;
    SpawnedEffectMotionView *effect;
    f32 scale;
    s32 *node;

    if (Geometry_GetViewEffect() != 0) {
        rotation.x = rotation.y = rotation.z = 0.0f;
        rotation.w = g_simpleObjectViewEffectRotationAndHeight;
        node = SetN64_GetPackSection(*resource, 2);
        if ((*node != 0) &&
            (*((s32 *)SetN64_GetPackSection(SetN64_GetPackSection(node, 0), 0)) & 0x8000)) {
            position = actor->position;
            position.y += Gobjinst_GetActorHeight(actor) * *(&g_simpleObjectViewEffectRotationAndHeight + 1);
            Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], actor, actor, 0, 0, 148,
                          actor->effectPosition, rotation, position, 0, -1, 0);
            effect = Particle_GetLastSpawnedEffect(&g_actorParticleEffectSystem[0]);
            if (effect != 0) {
                scale = g_simpleObjectViewEffectScale;
                effect->radius = Gobjinst_GetActorRadius(actor) * scale;
                effect->height = Gobjinst_GetActorHeight(actor) * scale;
            }
        }
    }
}

void Simpinst_DrawGroundShadow(void *actor) {
    f32 matrix[16];
    CVector3 position;
    CQuatern rotation;
    f32 ground;
    f32 height;
    f32 size;
    ground = ((Shared_CollisionActor *)actor)->groundY;
    height = ((Shared_CollisionActor *)actor)->y - ground;
    if (!(RW_MIN_LT(InstHdr_GetActorShadowRadius(actor) * 0.5f, InstHdr_GetActorShadowRadius(actor) * 0.5f - height * 0.1f) < 0.0f)) {
        size = RW_MIN_LT(InstHdr_GetActorShadowRadius(actor) * 0.5f, InstHdr_GetActorShadowRadius(actor) * 0.5f - height * 0.1f);
    } else {
        size = 0.0f;
    }
    rotation = Insthdr_BuildActorGroundRotation(actor);
    position.x = ((Shared_CollisionActor *)actor)->x;
    position.z = ((Shared_CollisionActor *)actor)->z;
    position.y = ground;
    Graphu64_LimitVectorLength(&position, 20000.0f);
    MatrixFromQuaternion(&rotation.x, matrix);
    ScaleMatrixLocal(matrix, size, 1.0f, size);
    TranslateMatrix(matrix, position.x, position.y, position.z);
    Graphu64_ConvertMatrixToFixed(matrix, (char *)actor + ((g_lightingBufferIndex << 6) + ((char *)&((LevelActor *)0)->bounds - (char *)0)));
    Geometry_DrawIntensityMask((char *)actor + ((g_lightingBufferIndex << 6) + ((char *)&((LevelActor *)0)->bounds - (char *)0)), 1, 150);
}

void Simpinst_RefreshModelResourceUsage(ObjB *staticObject) {
    void *variantDirectory;
    void **resource;
    s32 key;
    s32 found;
    s32 index;

    index = staticObject->type;
    if (index != staticObject->loadedType) {
        resource = Cache_RequestResource(0, staticObject->animationKey,
            staticObject->animationKey, 24,
            0, 0, 0, &g_simpleObjectModelResourceTagData + 4, 1);
        if (resource != 0) {
            key = SetN64_GetDirectoryEntry(*resource, staticObject->animationKey, 1);
            Cache_ReleaseResource(0, resource);
            found = Cache_RequestWordCountedResource(0, &variantDirectory, key, g_simpModelsIndexText, 1);
            if (found != 0) {
                staticObject->resource = SetN64_LocatePackSection((s32)variantDirectory, key,
                    index % *(s32 *)variantDirectory,
                    &staticObject->resourceSize);
                staticObject->loadedType = index;
                Cache_ReleaseResource(0, (void *)found);
            }
        }
    }
    if (staticObject->resource != 0) {
        resource = Cache_RequestResource(0, staticObject->resource,
            staticObject->resource, staticObject->resourceSize,
            0, 0, &g_simpleModelResourceCallbackAddress, g_simpModelText, 0);
    } else {
        resource = 0;
    }
    if (resource != 0) {
        Geometry_RefreshMaterialResources(resource);
        Cache_UnlockResource(0, resource);
    }
}

/* SIMPINST.CPP */

struct ObjB;

void Simpinst_RegisterModelVariantResources(struct ObjB *object, s32 camera) {
    void *memory = object;
    ObjB *obj = memory;
    void *header;
    s32 *table;
    void **resource;
    void **found;
    CachedResource *block;
    s32 key;
    s32 index;
    index = obj->type;
    if (index != obj->loadedType) {
        resource = Cache_RequestResource(0, obj->animationKey, obj->animationKey, 24, 0, 0, 0, g_simpObjectIndexText, 1);
        if (resource != 0) {
            key = SetN64_GetDirectoryEntry(*resource, obj->animationKey, 1);
            Cache_ReleaseResource(0, resource);
            found = Cache_RequestWordCountedResource(0, &header, key, g_simpModelsIndexText, 1);
            if (found != 0) {
                table = header;
                obj->resource = SetN64_LocatePackSection(table, key, index % table[0], &obj->resourceSize);
                obj->loadedType = index;
                Cache_ReleaseResource(0, found);
            }
        }
    }
    if (obj->resource != 0) {
        resource = Cache_RequestResource(0, obj->resource, obj->resource, obj->resourceSize, 0, 0, &g_simpleModelResourceCallbackAddress, g_simpModelText, 0);
    } else {
        resource = 0;
    }
    if (resource != 0) {
        Geometry_UnlockMaterialResources(resource);
        block = Cache_RequestPairedResource(0, g_litGeometryResourceKeyFlags, (void *)resource, (CachedResource *)obj->block, 8, obj, &g_Simpinst_BuildLitGeometryResourceAddress, &s_litVerticesText, 0);
        if (block != 0) {
            Cache_UnlockResource(0, (void *)block);
        }
        Cache_UnlockResource(0, (void *)resource);
    }
}

/* BARREL_SPAWNACTOREFFECT_DATA.CPP */

/** Clear the cached resource of a static object. */
void Simpinst_ClearCachedResource(void *staticObject) {
    ((ObjB *)(staticObject))->cached = 0;
}

CQuatern Simpinst_BuildGroundRotation(void *actor) {
    return Insthdr_BuildActorGroundRotation(actor);
}

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
            ((ObjB *)(o))->scene = g_defaultCameraSurfaceType;
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

/** Stores g_frameElapsedTime times the float of the object in the float. */

void Simpinst_UpdateAnimationFrameDelta(ObjB *staticObject) {
    void *p = staticObject->definition;
    staticObject->frameDelta = (g_frameElapsedTime) * (((PropGeometry *)(p))->speed);
}

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
        if (g_gameSettings.flags & 0x800) {
            value = 1;
        }
        if (g_gameSettings.flags & 0x1000) {
            value = 2;
        }
    }
    return value;
}

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
const float g_simpleObjectScaleTransitionConstants[4] = {
    0.06666667f, 0.75f, 0.46666667f, 0.35f,
};
#endif

#if !(defined(VERSION_US_REV1))
const float g_simpleObjectAlternateScaleTransitionConstants[4] = {
    0.06666667f, 0.75f, 0.46666667f, 0.35f,
};
#endif

#if defined(VERSION_US_REV1)
const float g_simpleObjectAlternateScaleTransitionConstants[4] = {
    0.06666667f, 0.75f, 0.46666667f, 0.35f,
};
#endif

/* Keep this source unit's macros local to its body. */

/* SIMPINST_SPAWNMODELEFFECT_DATA.CPP */



/* G_SIMPOBJECTINDEXTEXT.CPP */

extern const char g_simpObjectIndexText[18];

/* G_SIMPMODELSINDEXTEXT.CPP */

extern const char g_simpModelsIndexText[18];

/* G_SIMPMODELTEXT.CPP */

extern const char g_simpModelText[11];

/* S_LITVERTICESTEXT.CPP */

#if !(defined(VERSION_US_REV1))
extern const char s_litVerticesText[13];
#endif

#if defined(VERSION_US_REV1)

#endif

/* Retained data for this translation unit. */

const float g_Simpinst_SpawnModelEffectConstants[3] = {
    1.0f, 0.5f, 0.1f,
};
#if defined(VERSION_US_REV1)
const char s_simpleObjectLitVerticesTagUsRev1[13] =
    "lit vertices";
#endif

const char g_simpObjectIndexText[18] = "simp object index";

const char g_simpModelsIndexText[18] = "simp models index";

const char g_simpModelText[11] = "simp model\000";
#if !(defined(VERSION_US_REV1))
const char s_litVerticesText[13] =
    "lit vertices\000";
#endif
