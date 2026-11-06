#include "Common/world.h"
#include "Common/Lone/screen_image_resources_enabled.h"
#include "Common/Lone/g_defaultcamerasurfacetype.h"
#include "Common/sharedplayer.h"
#include "Common/animation_pool.h"
#include "Common/version_calls.h"
#include "types.h"
#include "Scene/cache_requestresource.h"
#include "Scene/cache_allocateresourceat.h"
#include "Engine/Cache/list.h"
#include "Render/setn64_getpacksection.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Engine/scene_drawtransitioncoloroverlay.h"
#include "Engine/session.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "common.h"
#include "Engine/scene.h"
#include "Engine/Instance/gobjinst.h"
#include "Common/heap_arena_entry.h"
#include "Animpool/animpool_spawndescribedsceneeffect.h"
#include "Common/runtime_declarations.h"
#include "Common/vector4f.h"
#include "Animpool/animpool_readsignedbits.h"
#include "include_asm.h"
#include "Data/rest_source_records.h"
#include "Engine/gobjinst_findnearestbonebounds.h"

/* ANIMPOOL.CPP */

/* Spawns the effect of an item variant: resolves the variant's effect id, loads its descriptor and first record, takes the effect count from the record's model and turns the colour vector by the record's angle, then spawns the effect through the inline spawner of Animpool_SpawnDescribedSceneEffect with the given owner, position, scale, direction and counted reference, releasing both resources. */


struct Shared_World;

static inline SceneEffect *take_effect(struct CAnimPool *scene, s32 *ref) {
    SceneEffect *effect;
    if (g_world.visibilityEnabled == 0 && (unsigned int)scene->UsedList.count >= 3) {
        return 0;
    }
    effect = scene->FreeList.head;
    if (effect != 0) {
        List_RemoveIntrusive(&scene->FreeList, effect);
        List_PrependIntrusive(&scene->UsedList, effect);
        effect->ref = ref;
        if (ref != 0) {
            *ref += 1;
        }
    }
    return effect;
}
static inline SceneEffect *spawn_effect(struct CAnimPool *scene, s32 id, s32 variant, s32 count, s32 owner, CVector3 position,
                                   f32 scale, CVector3 direction, CVector3 color, s32 *ref) {
    SceneEffect *effect;
    if (g_screenImageResourcesEnabled == 0) {
        return 0;
    }
    if (count == 0) {
        return 0;
    }
    if (id == -1) {
        id = Scene_FindModelIdIndex(&g_world, variant);
        if (id == -1) {
            return 0;
        }
    }
    if ((unsigned int)(variant + 1) < 2) {
        variant = Scene_GetModelIdAtIndex(&g_world, id);
    }
    effect = take_effect(scene, ref);
    if (effect == 0) {
        return 0;
    }
    Gobjinst_InitializeActor(effect, id, variant, g_defaultCameraSurfaceType, count, -1, owner, scale, position, 0x80000, color, direction, 0);
    Gobjinst_DispatchActorTypeUpdate(effect);
    return effect;
}
SceneEffect *Animpool_SpawnAnimationObject(struct CAnimPool *scene, s32 variant, s32 owner, CVector3 position, f32 scale, CVector3 direction,
                      CVector3 color, s32 *ref) {
    SceneEffect *effect;
    s32 id;
    s32 key;
    void **descriptor;
    void **resource;
    RecordAnimPoolSpawnAnimationObject *record;
    s32 count;
    s32 size;
    s32 clip;
    effect = 0;
    id = Scene_FindModelIdIndex(&g_world, variant);
    if (id != -1) {
        key = SetN64_GetDirectoryEntry((s32)g_world.indexedDirectory, g_world.indexedBank, id);
        descriptor = Cache_RequestResource(0, key, key, 24, 0, 0, 0, &s_animObjectIndexText, 1);
        if (descriptor != 0) {
            clip = SetN64_LocatePackSection(*descriptor, key, 0, &size);
            resource = Cache_RequestResource(0, clip, clip, size, 0, 0, 0, &s_animObjectInfoText, 1);
            if (resource != 0) {
                record = SetN64_GetPackSection(*resource, 0);
                count = Scene_GetActorDefinition(&g_world, record->count);
                Graphu64_ScaleVector(&color, &color, Menu_ExpandFloatHighWord(record->angle));
                effect = spawn_effect(scene, id, variant, count, owner, position, scale, direction, color, ref);
                Cache_UnlockResource(0, resource);
            }
            Cache_UnlockResource(0, descriptor);
        }
    }
    return effect;
}

/* ANIMPOOL_SPAWNDESCRIBEDSCENEEFFECT.CPP */

/* Spawns the effect a description asks for: the spawn of Animpool_SpawnSceneEffect (id resolution, free node, init
 * through Gobjinst_InitializeActor and start) inlined with the id, variant, count, owner, position, scale, direction
 * and colour taken from the description record and no counted reference. */

static inline SceneEffect *take_effect_animpool_spawndescribedsceneeffect(struct CAnimPool *scene, s32 *ref) {
    SceneEffect *effect;

    if (g_world.visibilityEnabled == 0 && (unsigned int)scene->UsedList.count >= 3) {
        return 0;
    }
    effect = scene->FreeList.head;
    if (effect != 0) {
        List_RemoveIntrusive(&scene->FreeList, effect);
        List_PrependIntrusive(&scene->UsedList, effect);
        effect->ref = ref;
        if (ref != 0) {
            *ref += 1;
        }
    }
    return effect;
}

static inline SceneEffect *spawn_effect_animpool_spawndescribedsceneeffect(struct CAnimPool *scene, s32 id, s32 variant, s32 count, s32 owner, CVector3 position,
                                   f32 scale, CVector3 direction, CVector3 color, s32 *ref) {
    SceneEffect *effect;

    if (g_screenImageResourcesEnabled == 0) {
        return 0;
    }
    if (count == 0) {
        return 0;
    }
    if (id == -1) {
        id = Scene_FindModelIdIndex(&g_world, variant);
        if (id == -1) {
            return 0;
        }
    }
    if ((unsigned int)(variant + 1) < 2) {
        variant = Scene_GetModelIdAtIndex(&g_world, id);
    }
    effect = take_effect_animpool_spawndescribedsceneeffect(scene, ref);
    if (effect == 0) {
        return 0;
    }
    Gobjinst_InitializeActor(effect, id, variant, g_defaultCameraSurfaceType, count, -1, owner, scale, position, 0x80000, color, direction, 0);
    Gobjinst_DispatchActorTypeUpdate(effect);
    return effect;
}

SceneEffect *Animpool_SpawnDescribedSceneEffect(struct CAnimPool *scene, EffectDesc *desc) {
    return spawn_effect_animpool_spawndescribedsceneeffect(scene, desc->id, desc->variant, desc->count, desc->owner, desc->position, desc->scale,
                        desc->direction, desc->color, 0);
}

s32 Animpool_ReleaseSceneEffect(struct SceneEffect *node) {
    s32 *counter;

    counter = node->ref;
    node->actor.active = 0;
    if (counter != 0) {
        *counter -= 1;
    }
    List_RemoveIntrusive(&g_spawnedActorList, node);
    return List_AppendIntrusive(&g_sceneEffectSpawnList, node);
}

/* ANIMPOOL_SPAWNSCENEEFFECT.CPP */

/* Spawns an effect in a scene when effects are enabled and a count is given: resolves a missing effect id
 * from the variant (Scene_FindModelIdIndex, giving up when unknown) and a default variant from the id
 * (Scene_GetModelIdAtIndex), takes a node from the scene's free list when allowed (always with visibilityEnabled_AnimpoolSpawnsceneeffect, otherwise
 * while fewer than three are active), moves it to the active list and attaches the counted reference, then
 * initialises it through Gobjinst_InitializeActor with the position, scale, direction and colour vectors and starts it
 * with Gobjinst_DispatchActorTypeUpdate. Returns the effect or 0. */

static inline SceneEffect *take_effect_animpool_spawnsceneeffect(struct CAnimPool *scene, s32 *ref) {
    SceneEffect *effect;

    if (g_world.visibilityEnabled == 0 && (unsigned int)scene->UsedList.count >= 3) {
        return 0;
    }
    effect = scene->FreeList.head;
    if (effect != 0) {
        List_RemoveIntrusive(&scene->FreeList, effect);
        List_PrependIntrusive(&scene->UsedList, effect);
        effect->ref = ref;
        if (ref != 0) {
            *ref += 1;
        }
    }
    return effect;
}

/* Culls a scene's active effects against the view box: effects whose bounds overlap the box ending at
 * g_cameraVolumeBounds.max are passed to Scene_RegisterActorInSceneLists and, when idle, drop their counted reference; the others are
 * reset, release their reference, and are unlinked from the active list (List_RemoveIntrusive) and returned to
 * the free list (List_AppendIntrusive). */




struct Shared_World; struct LevelActor;

static inline s32 overlaps(SceneEffect *effect, f32 *max) {
    if (max[0] > effect->actor.bounds.min.x && max[-3] < effect->actor.bounds.max.x && max[2] > effect->actor.bounds.min.z &&
        max[-1] < effect->actor.bounds.max.z && max[1] > effect->actor.bounds.min.y && max[-2] < effect->actor.bounds.max.y) {
        return 1;
    }
    return 0;
}

SceneEffect *Animpool_SpawnSceneEffect(struct CAnimPool *scene, s32 id, s32 variant, s32 count, s32 owner, CVector3 position, f32 scale,
                      CVector3 direction, CVector3 color, s32 *ref) {
    SceneEffect *effect;

    if (g_screenImageResourcesEnabled == 0 || count == 0) {
        return 0;
    }
    if (id == -1) {
        id = Scene_FindModelIdIndex(&g_world, variant);
        if (id == -1) {
            return 0;
        }
    }
    if ((unsigned int)(variant + 1) < 2) {
        variant = Scene_GetModelIdAtIndex(&g_world, id);
    }
    effect = take_effect_animpool_spawnsceneeffect(scene, ref);
    if (effect == 0) {
        return 0;
    }
    Gobjinst_InitializeActor(effect, id, variant, g_defaultCameraSurfaceType, count, -1, owner, scale, position, 0x80000, color, direction, 0);
    Gobjinst_DispatchActorTypeUpdate(effect);
    return effect;
}

void Animpool_UpdateSceneEffects(struct CAnimPool *scene, s32 world) {
    SceneEffect *effect;
    SceneEffect *next;
    f32 *max;

    effect = scene->UsedList.head;
    if (effect == 0) {
        return;
    }
    do {
        max = &g_cameraVolumeBounds.max;
    next_effect:
        next = effect->next;
        if (overlaps(effect, max)) {
            Scene_RegisterActorInSceneLists(world, &effect->actor);
            if (effect->ref != 0 && effect->actor.active == 0) {
                *effect->ref -= 1;
                effect->ref = 0;
            }
        } else {
            effect->actor.active = 0;
            effect->actor.flags &= ~0x200;
            if (effect->ref != 0) {
                *effect->ref -= 1;
            }
            List_RemoveIntrusive(&scene->UsedList, effect);
            List_AppendIntrusive(&scene->FreeList, effect);
        }
        effect = next;
    } while (0);
    if (effect != 0) {
        goto next_effect;
    }
}

void *Animpool_AcquireSceneEffect(s32 effectPool, s32 *referenceCount) {
    struct CAnimPool *pool = (struct CAnimPool *)effectPool;
    SceneEffect *acquiredEffect;

    if ((g_world.visibilityEnabled != 0) || ((u32)pool->UsedList.count < 3)) {
        acquiredEffect = pool->FreeList.head;
        if (acquiredEffect != 0) {
            List_RemoveIntrusive(&pool->FreeList, acquiredEffect);
            List_PrependIntrusive(&pool->UsedList, acquiredEffect);
            (acquiredEffect)->ref = referenceCount;
            if (referenceCount != 0) {
                *referenceCount += 1;
            }
        }
        return acquiredEffect;
    }
    return 0;
}

/* ANIMPOOL_RELEASEPOOLEDEFFECT.CPP */





void AnimPool_ReleasePooledEffect(struct CAnimPool *animationPool, struct SceneEffect *effectNode) {
    s32 *referenceCount;

    referenceCount = effectNode->ref;
    effectNode->actor.active = 0;
    if (referenceCount != 0) {
        *referenceCount -= 1;
    }
    List_RemoveIntrusive(&animationPool->UsedList, effectNode);
    List_AppendIntrusive(&animationPool->FreeList, effectNode);
}

/* G_ANIMOBJECTINDEXTEXT.CPP */

#if !(defined(VERSION_US_REV1))
const char g_animObjectIndexText[18] =
    "anim object index\000";
#endif

#if defined(VERSION_US_REV1)
const char s_animObjectIndexText[18] = "anim object index";
#endif

/* G_ANIMOBJECTINFOTEXT.CPP */

#if defined(VERSION_EU)
const char g_animObjectInfoText[20] =
    "anim object info\000\102\000\010";
const unsigned int g_animationFramePrepareTag[2] = {
    0x00042403, 0x00621821,
};
#elif !(defined(VERSION_US_REV1))
const char g_animObjectInfoText[17] =
    "anim object info\000";
#endif

#if defined(VERSION_DE)
const float k_gastatePrepareAnimationFramesScales[2] = {
    1.0f, 0.1f,
};
#endif

#if defined(VERSION_US)
char s_GAnimobjectinfotextColorTText[11] =
    "ColorT\000\000\005\000\000";
#endif


#if defined(VERSION_EU_X)
char s_GAnimobjectinfotextEvelNameText[11] =
    "evel name\000\000";
#endif






#if defined(VERSION_US_REV1)
const char s_animObjectInfoText[17] =
    "anim object info";
#endif

/* XPRINTF.CPP */
#if defined(VERSION_US_REV1)
unsigned char g_xprintfBytes[3] = {
    0x65, 0x76, 0x65,
};
char s_nameText[8] = "l name";
#endif
