#include "Common/objb.h"
#include "Common/world.h"
#include "Common/sharedplayer.h"
#include "Common/propgeometry.h"
#include "Common/manager.h"
#include "types.h"
#include "Game/builddirectionmatrix.h"
#include "Engine/scene_drawtransitioncoloroverlay.h"
#include "Insthdr/insthdr_getactorshadowradius.h"
#include "Common/Lone/g_defaultcamerasurfacetype.h"
#include "Engine/Instance/Statinst/statinst_initializeplacedprop.h"
#include "common.h"
#include "Engine/Instance/Statinst/statinst_initplacedprop.h"
#include "Engine/Instance/gobjinst.h"
#include "Menu/scene_resource_preview_and_collision_views.h"
#include "Common/model_render.h"
#include "Render/material_color_and_fog_views.h"
#include "World/static_model_instance_views.h"
#include "Common/runtime_declarations.h"
#include "Common/gameplay_camera.h"
#include "Scene/cache_requestresource.h"
#include "Scene/cache_allocateresourceat.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "include_asm.h"
#include "Engine/link.h"
#include "Engine/session.h"
#include "Statinst/statinst_acquiregeometry.h"
#include "Common/approachlocation.h"
#include "System/events_delivercontacteffect.h"
#include "Engine/Instance/Statinst/statinst.h"
#include "Statinst/g_statobjectindextext.h"
#include <platform_sdk.h>
#include "Common/resident_event_handler.h"
#include "Common/cache_releaseresource.h"
#include "Common/shared_gameslot.h"
#include "Common/aiprofile.h"
#include "Common/level_actor.h"
#include "Common/level_spawn.h"
#include "Actors/lighting_buildlitmodel.h"
#include "Render/setn64_getpacksection.h"
#include "Geometry/geometry_drawblendparts.h"
#include "Engine/Instance/Statinst/statinst_drawgeometryvariant.h"
#include "Statinst/statinst.h"
#include "Engine/Cache/cache.h"

/* STATINST_INITIALIZEPLACEDPROP.CPP */

/* Initialises a placed prop from its compact record: resets its state and owner, loads its model and
 * caches the squared model radius, places it on the grid by multiplying the record's byte cell
 * coordinates by the caller's cell spacing and its packed height by 5.12, mirrors either axis for
 * flags 0x10 and 0x20, turns it by the quarter turn the low two bits of the same byte select, builds
 * scale and position into a matrix copied into the object, sets its bounding box either as a fixed
 * cube for flag 0x40 or from the record's six signed extents at a tenth of a cell with a half-unit
 * margin, copies the position, links its path segment and takes the next colour key and colour
 * frame. This is the compact-record twin of Statinst_InitializePlacedPropFullRecord_eu, which does the same work from a record
 * carrying full floats. The rounded literals are the cartridge's: 5.12 is 0x40A3D70A, 102.4 is
 * 0x42CCCCCC and 10.24 is 0x4123D70A. */

/* The record is packed into 0x1C bytes: the cell coordinates, the height and the six extents are
 * bytes scaled on the way in, where Statinst_InitializePlacedPropFullRecord_eu's record carries the same quantities as floats. */

static inline s32 advancePropKey(void) {
    s32 next;

    next = g_staticObjectResourceSerial + 1;
    g_staticObjectResourceSerial = next;
    if (next == 0x3FFFFF) {
        g_staticObjectResourceSerial = 0x380000;
    }
    return g_staticObjectResourceSerial;
}

void Statinst_InitializePlacedProp(ObjA *prop, PackedPlacedPropDefinition *record, s32 owner, char *segments, f32 spacing) {
    char matrix[64];
    CVector3 position;
    PropGeometry *model;
    f32 turn;
    f32 x;
    f32 z;

    Insthdr_ResetInstanceRenderIndices(prop);
    prop->state = 0;
    prop->id = record->id;
    prop->owner = owner;
    prop->renderIndex = -1;
    prop->renderState[0] = 0;
    prop->renderState[1] = 0;
    prop->renderState[2] = 0;
    turn = 0.0f;
    prop->descriptor = Scene_GetActorDefinition(&g_world, record->model);
    prop->fade = 16;
    prop->timer = 0;
    model = (PropGeometry *)prop->descriptor;
    model->radiusSquared = model->radius * model->radius;
    x = record->cellX * spacing;
    position.x = x;
    if (record->placement & 0x10) {
        position.x = -x;
    }
    z = record->cellZ * spacing;
    position.z = z;
    if (record->placement & 0x20) {
        position.z = -z;
    }
    position.y = record->height * 5.119999886f;
    switch (record->placement & 3) {
    case 0:
        turn = 0.0f;
        break;
    case 1:
        turn = 1.570796490f;
        break;
    case 2:
        turn = 3.141592979f;
        break;
    case 3:
        turn = 4.712389469f;
        break;
    }
    prop->flagsD8 = record->flags;
    BuildYawMatrix(matrix, turn);
    ScaleMatrixLocal(matrix, record->scale, record->scale, record->scale);
    TranslateMatrix(matrix, position.x, position.y, position.z);
    SwapMatrixUpForward(matrix);
    if (prop->flagsD8 & 0x40) {
        prop->bounds.min.x = position.x - 102.3999939f;
        prop->bounds.min.y = position.y - 102.3999939f;
        prop->bounds.min.z = position.z - 102.3999939f;
        prop->bounds.max.x = position.x + 102.3999939f;
        prop->bounds.max.y = position.y + 102.3999939f;
        prop->bounds.max.z = position.z + 102.3999939f;
        prop->surfaceType = g_defaultCameraSurfaceType;
    } else {
        prop->bounds.min.x = position.x + record->extents[0] * 10.23999977f - 0.5f;
        prop->bounds.min.y = position.y + record->extents[2] * 10.23999977f - 0.5f;
        prop->bounds.min.z = position.z + record->extents[4] * 10.23999977f - 0.5f;
        prop->bounds.max.x = position.x + record->extents[1] * 10.23999977f + 0.5f;
        prop->bounds.max.y = position.y + record->extents[3] * 10.23999977f + 0.5f;
        prop->bounds.max.z = position.z + record->extents[5] * 10.23999977f + 0.5f;
        prop->surfaceType = record->value;
    }
    CopyMatrix(prop->matrix, matrix);
    Graphu64_ConvertMatrixToFixed(matrix, &prop->transform);
    prop->position = position;
    if (record->segment == 0xFFFF) {
        prop->segment = 0;
    } else {
        prop->segment = segments + record->segment * 32;
    }
    prop->flagsD0 = advancePropKey() << 10;
    prop->colorFrame = (u8)g_gameFrameCounter - 1;
#if defined(VERSION_DE)
    if ((u32)(InstHdr_GetActorType(prop) - 9) < 2) {
        prop->flagsD8 |= 0x50;
    }
#endif
}

/* STATINST_INITPLACEDPROP.CPP */

/* Initialises a placed prop from its record: resets its state and owner, loads its model and caches the squared model radius, builds its rotation from the record's packed quaternion, scale and position into a matrix copied into the object, sets its bounding box either as a fixed cube for flag 0x40 or from the record's six extents through Menu_ExpandFloatHighWord with a half-unit margin, copies the position, links its path segment and takes the next colour key and colour frame. The fixed cube is written through do-while(0) vector macros, which the stores' order needs, and 102.4 is the cartridge's rounded 0x42CCCCCC. */

static inline s32 advancePropKey_statinst_initplacedprop(void) {
    s32 next;

    next = g_staticObjectResourceSerial + 1;
    g_staticObjectResourceSerial = next;
    if (next == 0x3FFFFF) {
        g_staticObjectResourceSerial = 0x380000;
    }
    return g_staticObjectResourceSerial;
}

void Statinst_InitPlacedProp(ObjA *prop, PlacedPropRecord *record, s32 owner, char *segments) {
    f32 rotation[4];
    char matrix[64];
    PropGeometry *model;

    Insthdr_ResetInstanceRenderIndices(prop);
    prop->state = 0;
    prop->id = record->id;
    prop->owner = owner;
    prop->renderIndex = -1;
    prop->renderState[0] = 0;
    prop->renderState[1] = 0;
    prop->renderState[2] = 0;
    prop->descriptor = Scene_GetActorDefinition(&g_world, record->model);
    prop->fade = 16;
    prop->timer = 0;
    model = (PropGeometry *)prop->descriptor;
    model->radiusSquared = model->radius * model->radius;
    prop->flagsD8 = record->flags;
    rotation[0] = record->rotation[0] * 0.007874016f;
    rotation[1] = record->rotation[1] * 0.007874016f;
    rotation[2] = record->rotation[2] * 0.007874016f;
    rotation[3] = record->rotation[3] * 0.007874016f;
    Graphu64_NormalizeQuaternion(rotation);
    MatrixFromQuaternion(rotation, matrix);
    ScaleMatrixLocal(matrix, record->scale.x, record->scale.y, record->scale.z);
    TranslateMatrix(matrix, record->position.x, record->position.y, record->position.z);
    SwapMatrixUpForward(matrix);
    if (prop->flagsD8 & 0x40) {
        do { (prop->bounds.min).x = (record->position).x - (102.399994f); (prop->bounds.min).y = (record->position).y - (102.399994f); (prop->bounds.min).z = (record->position).z - (102.399994f); } while (0);
        do { (prop->bounds.max).x = (record->position).x + (102.399994f); (prop->bounds.max).y = (record->position).y + (102.399994f); (prop->bounds.max).z = (record->position).z + (102.399994f); } while (0);
        prop->surfaceType = g_defaultCameraSurfaceType;
    } else {
        prop->bounds.min.x = RW_BITS_TO_FLOAT(record->extents[0]) + record->position.x - 0.5f;
        prop->bounds.min.y = RW_BITS_TO_FLOAT(record->extents[1]) + record->position.y - 0.5f;
        prop->bounds.min.z = RW_BITS_TO_FLOAT(record->extents[2]) + record->position.z - 0.5f;
        prop->bounds.max.x = RW_BITS_TO_FLOAT(record->extents[3]) + record->position.x + 0.5f;
        prop->bounds.max.y = RW_BITS_TO_FLOAT(record->extents[4]) + record->position.y + 0.5f;
        prop->bounds.max.z = RW_BITS_TO_FLOAT(record->extents[5]) + record->position.z + 0.5f;
        prop->surfaceType = record->value;
    }
    CopyMatrix(prop->matrix, matrix);
    Graphu64_ConvertMatrixToFixed(matrix, &prop->transform);
    prop->position = record->position;
    if (record->segment == 0xFFFF) {
        prop->segment = 0;
    } else {
        prop->segment = segments + record->segment * 32;
    }
    prop->flagsD0 = advancePropKey_statinst_initplacedprop() << 10;
    prop->colorFrame = (u8)g_gameFrameCounter - 1;
#if defined(VERSION_DE)
    if ((u32)(InstHdr_GetActorType(prop) - 9) < 2) {
        prop->flagsD8 |= 0x50;
    }
#endif
}

/* STATINST.CPP */

/* Draws an owner model with timed descriptor selection and fade setup/reset; a named descriptor-slot reference preserves reload scheduling. */

static inline int select_key(StaticModelAnimationDescriptor *descriptor, u32 timer) {
    int key;
    if (timer >= (u32)(descriptor->period * 2)) {
        key = descriptor->key2;
    } else {
        key = descriptor->key;
    }
    return key;
}

/* Starts the effects attached to an object's model: loads the model resource named by the object's id,
 * finds its attachment table (group 3) and loads it, then for each attachment (all of them, or
 * only type 8 when all is clear) transforms its offset by the object's matrix and starts the
 * attachment's effect at that point through Events_DeliverContactEffect_ActorAnimationRootAndEventOperations, releasing both resources afterwards. */


s32 Statinst_UpdateDistanceFade(void *prop, s32 cameraAddress) {
    ObjA *owner = prop;
    GameplayCamera *camera = (void *)cameraAddress;
    CVector3 cameraOffset;
    f32 distanceSquared;
    f32 threshold;
    s32 unsignedDistanceSquared;
    s8 nextFade;
    s32 selectedResourceKey;
    u16 flagsD8Value;
    u16 updatedRenderFlags;
    u8 next_timer;
    StaticModelAnimationDescriptor *descriptor;

    Graphu64_SubtractVectors(&cameraOffset, &camera->position,
        &owner->position);
    distanceSquared = cameraOffset.x * cameraOffset.x + cameraOffset.y * cameraOffset.y + cameraOffset.z * cameraOffset.z;
    threshold = g_staticObjectFadeThresholdAndAlpha[0];
    if (!(threshold <= distanceSquared)) {
        unsignedDistanceSquared = (s32)distanceSquared;
    } else {
        unsignedDistanceSquared = (s32)(distanceSquared - threshold) | 0x80000000;
    }
    descriptor = owner->descriptor;
    owner->timer = unsignedDistanceSquared;
    if ((u32)unsignedDistanceSquared >= (u32)(descriptor->period * 2)) {
        selectedResourceKey = descriptor->key2;
    } else {
        selectedResourceKey = descriptor->key;
    }

    if (selectedResourceKey == -1) {
        if (owner->fade <= 0) {
            owner->fade = 0;
            owner->flagsD8 =
                owner->flagsD8 | 4;
            return 0;
        }
        flagsD8Value = owner->flagsD8;
        if (flagsD8Value & 0x200) {
            owner->flagsD8 = flagsD8Value | 4;
            owner->fade = 0;
            return 0;
        }
        nextFade = (u8)owner->fade - 1;
        owner->fade = nextFade;
        if (nextFade < 0) {
            owner->fade = 0;
        }
        updatedRenderFlags = owner->flagsD8 | 4;
        goto block_20;
    } else if (owner->fade < 8) {
        next_timer = (u8)owner->fade + 1;
        if (owner->flagsD8 & 0x200) {
            owner->fade = 8;
            owner->flagsD8 =
                owner->flagsD8 & 0xFFFB;
        } else {
            owner->fade =
                next_timer;
            updatedRenderFlags = owner->flagsD8 | 4;
            block_20:
            owner->flagsD8 = updatedRenderFlags;
        }
    } else {
        owner->fade = 8;
    }
    return 1;
}

void Statinst_DrawDistanceFadedModel(ObjA *owner) {
    StaticModelAnimationDescriptor *descriptor;
    s32 remaining;
    s32 key;
    void *instance;
    CachedResource *resource;
    LitModelResourceHeader *header;
    char *data;
    f32 alpha;

    if (owner->flagsD8 & 0x40) {
        return;
    }
    descriptor = owner->descriptor;
    remaining = descriptor->argument;
    key = select_key(descriptor, owner->timer);
    if (key == -1) {
        if (owner->fade <= 0) {
            return;
        }
        g_menuModelFillEnabled = 1;
        g_menuModelFillColor[3] = owner->fade << 5;
        { StaticModelAnimationDescriptor **slot = &owner->descriptor; key = (*slot)->key; }
    } else {
        if (owner->fade < 8) {
            g_menuModelFillEnabled = 1;
            alpha = owner->fade << 5;
        } else {
            alpha = g_staticObjectFadeThresholdAndAlpha[1];
            g_menuModelFillEnabled = 0;
        }
        g_menuModelFillColor[3] = alpha;
    }
    instance = Statinst_AcquireGeometry(owner, key);
    if (instance != 0) {
        resource = Cache_RequestPairedResource(0, owner->flagsD0 | g_litGeometryResourceKeyFlags, instance, (CachedResource *)(s32)owner->block, 8, owner, &g_Statinst_BuildLitGeometryResourceAddress,
            s_staticLitGeometryResourceTag, 0);
        if (resource != 0) {
            Cache_MarkResourceInUse(0, resource);
            header = (LitModelResourceHeader *)resource->data;
            if (header->layout == 1) {
                char *object = (char *)header + header->objectOffset;
                char *colors = (char *)header + header->vertexColorOffset;

                if (owner->colorFrame != (u8)g_gameFrameCounter) {
                    Link_AnimateVertexColors(object, colors);
                }
                data = object;
            } else {
                data = (char *)&header->vertexColorOffset;
            }
            if (g_menuModelFillEnabled != 0) {
                Geometry_DrawModelResource(instance, &owner->transform, 0, 0, data, remaining);
            } else {
                Geometry_QueueModelInstance(instance, &owner->transform, 0, 0, data, remaining);
            }
            Cache_UnlockResource(0, resource);
        }
        Cache_UnlockResource(0, instance);
        owner->colorFrame = (u8)g_gameFrameCounter;
    }
    g_menuModelFillEnabled = 0;
    g_menuModelFillColor[3] = g_staticObjectOpaqueAlpha;
}

void Statinst_DrawModel(ObjA *owner) {
    s32 remaining;
    void *instance;
    CachedResource *resource;
    LitModelResourceHeader *header;
    char *data;

    if (owner->flagsD8 & 0x40) {
        return;
    }
    remaining = owner->descriptor->argument;
    instance = Statinst_AcquireGeometry(owner, owner->descriptor->key);
    if (instance == 0) {
        return;
    }
    resource = Cache_RequestPairedResource(0, owner->flagsD0 | g_litGeometryResourceKeyFlags, instance, (CachedResource *)(s32)owner->block, 8, owner, &g_Statinst_BuildLitGeometryResourceAddress,
        s_staticLitGeometryResourceTag, 0);
    if (resource != 0) {
        Cache_MarkResourceInUse(0, resource);
        header = (LitModelResourceHeader *)resource->data;
        if (header->layout == 1) {
            char *object = (char *)header + header->objectOffset;
            char *colors = (char *)header + header->vertexColorOffset;

            if (owner->colorFrame != (u8)g_gameFrameCounter) {
                Link_AnimateVertexColors(object, colors);
            }
            data = object;
        } else {
            data = (char *)&header->vertexColorOffset;
        }
        if (g_menuModelFillEnabled != 0) {
            Geometry_DrawModelResource(instance, &owner->transform, 0, 0, data, remaining);
        } else {
            Geometry_QueueModelInstance(instance, &owner->transform, 0, 0, data, remaining);
        }
        Cache_UnlockResource(0, resource);
    }
    Cache_UnlockResource(0, instance);
    owner->colorFrame = (u8)g_gameFrameCounter;
}

void Statinst_DispatchAttachmentEvents(void *object, s32 all) {
    s32 **model;
    s32 **table;
    s32 *header;
    Attachment *attachment;
    Attachment *entries;
    Triple position;
    s32 name;
    s32 size;
    s32 count;
    s32 i;

    model = Cache_RequestResource(0, ((ObjA *)object)->owner, ((ObjA *)object)->owner, 24, 4, 0, 0,
        &g_statObjectIndexText, 0);
    if (model == 0) {
        return;
    }
    name = SetN64_LocatePackSection(*model, ((ObjA *)object)->owner, 3, &size);
#if defined(VERSION_DE)
    table = Cache_RequestResource(0, name, name, size, 0, 0, 0, s_staticObjectResourceTag, 0);
#elif defined(VERSION_EU)
    table = Cache_RequestResource(0, name, name, size, 0, 0, 0, s_staticInstanceResourceTag, 0);
#elif defined(VERSION_EU_X)
    table = Cache_RequestResource(0, name, name, size, 0, 0, 0, s_staticModelResourceTag, 0);
#elif defined(VERSION_US)
    table = Cache_RequestResource(0, name, name, size, 0, 0, 0, s_staticGeometryResourceTag, 0);
#else
    table = Cache_RequestResource(0, name, name, size, 0, 0, 0, s_staticPropResourceTag, 0);
#endif
    if (table != 0) {
        header = *table;
        count = header[1];
        entries = (Attachment *)(header + 2);
        for (i = 0; i < count; i++) {
            attachment = &entries[i];
            if (all != 0 || attachment->type == 8) {
                Graphu64_TransformPoint(((ObjA *)object)->matrix, &attachment->offset, &position);
                Events_DeliverContactEffect(object, object, attachment->type, -1, *(CVector3 *)&position, *(ContactEffectStyle *)&attachment->params);
            }
        }
        Cache_UnlockResource(0, table);
    }
    Cache_UnlockResource(0, model);
}



/* STATINST_ACQUIREGEOMETRY.CPP */


void *Statinst_AcquireGeometry(ResourceOwner *owner,s32 index) {
    void **block;
    void *allocation;
    s32 key;
    void *table;
    s32 *entries;
    if (owner->resource != 0) {
        Cache_LockResource(0,owner->resource);
        return owner->resource;
    }
    if (index != owner->index) {
        block = Cache_RequestResource(0,owner->key,owner->key,24,0,0,0,g_statObjectIndexText,1);
        if (block != 0) {
            key = SetN64_GetDirectoryEntry(*block,owner->key,1);
            Cache_ReleaseResource(0,block);
            allocation = Cache_RequestWordCountedResource(0,&table,key,s_statModelsIndexText,1);
            if (allocation != 0) {
                entries = table;
                owner->selected = SetN64_LocatePackSection(table,key,index % *entries,&owner->size);
                owner->index = index;
                Cache_ReleaseResource(0,allocation);
            }
        }
    }
    if (owner->selected != 0) {
        return Cache_RequestResource(0,owner->selected,owner->selected,owner->size,0,0,g_Geometry_ExpandBasicModelAddressDe,s_statModelText,0);
    } else { return 0; }
}

/* STATINST_DRAWGEOMETRYVARIANT.CPP */

/* Returns the matching resource entry index, or minus one when absent. */

int Statinst_FindPlacedPropIndex(void *wanted,int key) {
    int result=-1; int i,count,offset; char *entries;
    LevelNode *h=SetN64_GetPackSection(key,0);
    count=h->count; entries=(char *)h->records;
    i=0; if(count>0) {offset=i; do {if(entries+offset!=wanted) {i++;offset+=232;} else {result=i;break;}}while(i<count);}return result;}

void Statinst_RegisterGeometryResources(void *owner) {
    struct ResourceBinding *o = (struct ResourceBinding *) owner;
    void *geometryResource;
    CachedResource *ret2;

    if (!(o->status & 0x40)) {
        geometryResource = Statinst_AcquireGeometry(owner, o->variant);
        if (geometryResource != 0) {
            Geometry_UnlockMaterialResources((void **) geometryResource);
            ret2 = Cache_RequestPairedResource(0, o->registrationFlags | g_litGeometryResourceKeyFlags, geometryResource, (CachedResource *)o->resource, 8, owner, &g_Statinst_BuildLitGeometryResourceAddress, s_staticLitGeometryResourceTag, 0);
            if (ret2 != 0) {
                Cache_UnlockResource(0, (s32)ret2);
            }
            Cache_UnlockResource(0, (s32) geometryResource);
        }
    }
}

/** Return the prop's model index, or 0 when the 0x40 status flag suppresses it. */
int Statinst_GetPropModelIndex(char *object) {
    if (((ActorResourceStatusView *)(object))->statusFlags & 0x40) {
        return 0;
    }
    return ((struct GeometryVariantByteView *) ((ActorResourceStatusView *) object)->geometryVariant)->propModelIndex;
}

/** Return the geometry index (near value) of the prop's linked fade definition. */
s32 Statinst_GetPropGeometryIndex(struct ObjA *object) {
    void *linked = object->descriptor;
    return ((struct ResourceFadeDefinition *)linked)->nearValue;
}

void Statinst_DrawForGameMode(void *owner) {
    if (g_gameSettings.local != 0) {
        Statinst_DrawModel(owner);
        return;
    }
    Statinst_DrawDistanceFadedModel(owner);
}

void Statinst_RefreshResourceUsage(void *resourceBinding) {
    struct ResourceBinding *binding = resourceBinding;
    if (!(binding->status & 0x40) && (binding->colorFrame != (u8)g_gameFrameCounter)) {
        Cache_TouchResourceByKey(0, binding->registrationFlags | g_litGeometryResourceKeyFlags);
    }
}

s32 *Statinst_CollectPropResources(void *prop, s32 model, s32 geometryVariant, s32 *nextResource) {
    struct ResourceBinding *o = (struct ResourceBinding *) prop;
    void *geometryResource;
    s32 *resourceCursor;
    CachedResource *ret2;

    resourceCursor = nextResource;
    geometryResource = Statinst_AcquireGeometry(prop, geometryVariant);
    if (geometryResource != 0) {
        o->loadedResource = geometryResource;
        *resourceCursor = (s32) geometryResource;
        resourceCursor = Geometry_CollectMaterialResources(geometryResource, model, resourceCursor + 1);
        ret2 = Cache_RequestPairedResource(0, o->registrationFlags | g_litGeometryResourceKeyFlags, geometryResource, (CachedResource *)o->resource, 8, prop, &g_Statinst_BuildLitGeometryResourceAddress, s_staticLitGeometryResourceTag, 1);
        if (ret2 != 0) {
            *resourceCursor = (s32)ret2;
            resourceCursor += 1;
        }
    }
    return resourceCursor;
}

/** Advance the wrapping counter g_staticObjectResourceSerial, resetting to 0x380000. */
int Statinst_AdvanceResourceKey(void) {
    int nextResourceKey;

    nextResourceKey = g_staticObjectResourceSerial + 1;
    g_staticObjectResourceSerial = nextResourceKey;
    if (nextResourceKey == 0x3FFFFF) {
        g_staticObjectResourceSerial = 0x380000;
    }
    return g_staticObjectResourceSerial;
}

void Statinst_BuildLitGeometryResource(void *wanted, s32 **resourcePair)
{
    struct ResourceBinding *binding = wanted;
    s32 sourceGeometry;
    sourceGeometry = *(*resourcePair);
    Cache_ReplaceResourcePairFirst(0, resourcePair, Lighting_BuildLitModel(sourceGeometry, *binding->resource, binding->runtimeState, (s32)binding->transform, 0, wanted));
}

void Statinst_DrawGeometryVariant(OwnerStaticInstanceDrawGeometryVariant *owner, s32 drawContext, s32 remaining, s32 key) {
    void *instance;
    CachedResource *resource;
    LitModelResourceHeader *header;
    char *data;

    instance = Statinst_AcquireGeometry(owner, key);
    if (instance == 0) {
        return;
    }
    resource = Cache_RequestPairedResource(0, owner->flagsD0 | g_litGeometryResourceKeyFlags, instance, (CachedResource *)owner->resourceDescriptor, 8, owner, &g_Statinst_BuildLitGeometryResourceAddress,
        s_staticLitGeometryResourceTag, 0);
    if (resource != 0) {
        Cache_MarkResourceInUse(0, (s32)resource);
        header = (LitModelResourceHeader *)resource->data;
        if (header->layout == 1) {
            char *object = (char *)header + header->objectOffset;
            char *colors = (char *)header + header->vertexColorOffset;

            if (owner->colorFrame != (u8)g_gameFrameCounter) {
                Link_AnimateVertexColors(object, colors);
            }
            data = object;
        } else {
            data = (char *)&header->vertexColorOffset;
        }
        if (g_menuModelFillEnabled != 0) {
            Geometry_DrawModelResource(instance, owner->transform, 0, 0, data, remaining);
        } else {
            Geometry_QueueModelInstance(instance, owner->transform, 0, 0, data, remaining);
        }
        Cache_UnlockResource(0, (s32)resource);
    }
    Cache_UnlockResource(0, (s32)instance);
    owner->colorFrame = (u8)g_gameFrameCounter;
}

/** Return the near value while the resource state is below twice the threshold, else the far value. */
int Statinst_SelectDistanceVariant(void *object) {
    LevelActor *actor = object;
    struct ResourceFadeDefinition *nested = (struct ResourceFadeDefinition *)actor->definition;
    if ((u32)actor->resourceState <
        nested->threshold * 2) {
        return nested->nearValue;
    }
    return nested->farValue;
}

s8 Statinst_SelectGameModeVariant(LevelActor *actor) {
    void *definition;

    if (g_gameSettings.local != 0) {
        return ((struct ResourceFadeDefinition *)actor->definition)->nearValue;
    }
    definition = actor->definition;
    if ((u32)actor->resourceState < ((struct ResourceFadeDefinition *)definition)->threshold * 2) {
        return ((struct ResourceFadeDefinition *)definition)->nearValue;
    }
    return ((struct ResourceFadeDefinition *)definition)->farValue;
}

/* STATINST_UPDATEDISTANCEFADE_DATA.CPP */





/* G_STATOBJECTINDEXTEXT.CPP */

const char g_statObjectIndexText[] = "stat object index"
#if defined(VERSION_EU_X)
"\000\000"
#endif
;

/* STATINST_DISPATCHATTACHMENTEVENTS_DATA.CPP */

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)

#endif

/* S_STATMODELSINDEXTEXT.CPP */

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
extern const char s_statModelsIndexText[18];
#endif

#if defined(VERSION_US_REV1)

#endif

/* G_STATMODELTEXT.CPP */

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)
extern const char s_statModelText[11];
#endif

/* Retained data for this translation unit. */

const char s_staticInstanceLitVerticesTag[13] = "lit vertices\000";

const float g_Statinst_UpdateDistanceFadeConstants[1] = {
    2.1474836e+09f,
};

const float g_Statinst_DrawDistanceFadedModelConstants[2] = {
    255.0f, 255.0f,
};
#if !(defined(VERSION_US_REV1))
const char g_staticEventsText[14] =
    "static events\000";
#endif
#if defined(VERSION_US_REV1)
const char s_staticEventsTagUsRev1[14] = "static events";
#endif
#if defined(VERSION_US_REV1)
const char g_statModelsIndexText[] = "stat models index"
"\000\000"
;
#endif
#if !(defined(VERSION_US_REV1))
const char g_statModelText[11] =
    "stat model\000";
#endif
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const char s_statModelsIndexText[18] =
    "stat models index\000";
#endif
#if defined(VERSION_US_REV1)
const char s_statModelText[11] =
    "stat model";
#endif
