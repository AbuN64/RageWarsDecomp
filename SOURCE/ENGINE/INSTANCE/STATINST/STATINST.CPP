#include "COMMON/MODEL_RENDER.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include "COMMON/PROPGEOMETRY.H"
#include "WORLD/STATIC_MODEL_INSTANCE_VIEWS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "TYPES.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "SCENE/RESOURCE_BINDING_AND_FADE_VIEWS.H"
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "include_asm.h"

/* STATINST.CPP */
extern s32 g_gameFrameCounter;

extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);
extern f32 g_staticObjectFadeThresholdAndAlpha[];

/* Draws an owner model with timed descriptor selection and fade setup/reset; a named descriptor-slot reference preserves reload scheduling. */

extern void *Statinst_AcquireGeometry(ResourceOwner *owner,s32 index);

extern void Link_AnimateVertexColors(void *object, void *colors);

extern void Geometry_QueueModelInstance(void **, void *, s32, void *, void *, s32);

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
 * finds its attachment table (group 3) and loads it, then for each 0x1C-byte attachment (all of them, or
 * only type 8 when all is clear) transforms its offset by the object's matrix at 0x68 and starts the
 * attachment's effect at that point through Events_DeliverContactEffect_ActorAnimationRootAndEventOperations, releasing both resources afterwards. */

extern char g_statObjectIndexText;

#if defined(VERSION_DE)
#elif defined(VERSION_EU)
extern char s_staticInstanceResourceTag[];
#elif defined(VERSION_EU_X)
extern char s_staticModelResourceTag[];
#elif defined(VERSION_US)
extern char s_staticGeometryResourceTag[];
#else
extern char s_staticPropResourceTag[];
#endif

extern s32 SetN64_LocatePackSection(s32 *, s32, s32, s32 *);

extern void Events_DeliverContactEffect(void *, void *, s32, s32, Triple, ResourceManagerState);

s32 Statinst_UpdateDistanceFade(void *prop, s32 cameraAddress) {
    OwnerStaticInstanceDrawDistanceFadedModel *owner = prop;
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

void Statinst_DrawDistanceFadedModel(OwnerStaticInstanceDrawDistanceFadedModel *owner) {
    StaticModelAnimationDescriptor *descriptor;
    s32 remaining;
    s32 key;
    void *instance;
    CachedResource *resource;
    s32 *header;
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
        resource = Cache_RequestPairedResource(0, owner->flagsD0 | g_litGeometryResourceKeyFlags, instance, (CachedResource *)owner->pairedResource, 8, owner, &g_Statinst_BuildLitGeometryResourceAddress,
                                 s_staticLitGeometryResourceTag, 0);
        if (resource != 0) {
            Cache_MarkResourceInUse(0, resource);
            header = (s32 *)resource->data;
            if (header[0] == 1) {
                char *object = (char *)header + header[1];
                char *colors = (char *)header + header[2];

                if (owner->colorFrame != (u8)g_gameFrameCounter) {
                    Link_AnimateVertexColors(object, colors);
                }
                data = object;
            } else {
                data = (char *)(header + 2);
            }
            if (g_menuModelFillEnabled != 0) {
                Geometry_DrawModelResource(instance, owner->transform, 0, 0, data, remaining);
            } else {
                Geometry_QueueModelInstance(instance, owner->transform, 0, 0, data, remaining);
            }
            Cache_UnlockResource(0, resource);
        }
        Cache_UnlockResource(0, instance);
        owner->colorFrame = (u8)g_gameFrameCounter;
    }
    g_menuModelFillEnabled = 0;
    g_menuModelFillColor[3] = g_staticObjectOpaqueAlpha;
}

void Statinst_DrawModel(ModelOwner *owner) {
    s32 remaining;
    void *instance;
    CachedResource *resource;
    s32 *header;
    char *data;

    if (owner->flagsD8 & 0x40) {
        return;
    }
    remaining = owner->descriptor->argument;
    instance = Statinst_AcquireGeometry(owner, owner->descriptor->key);
    if (instance == 0) {
        return;
    }
    resource = Cache_RequestPairedResource(0, owner->flagsD0 | g_litGeometryResourceKeyFlags, instance, (CachedResource *)owner->pairedResource, 8, owner, &g_Statinst_BuildLitGeometryResourceAddress,
                             s_staticLitGeometryResourceTag, 0);
    if (resource != 0) {
        Cache_MarkResourceInUse(0, resource);
        header = (s32 *)resource->data;
        if (header[0] == 1) {
            char *object = (char *)header + header[1];
            char *colors = (char *)header + header[2];

            if (owner->colorFrame != (u8)g_gameFrameCounter) {
                Link_AnimateVertexColors(object, colors);
            }
            data = object;
        } else {
            data = (char *)&header[2];
        }
        if (g_menuModelFillEnabled != 0) {
            Geometry_DrawModelResource(instance, owner->transform, 0, 0, data, remaining);
        } else {
            Geometry_QueueModelInstance(instance, owner->transform, 0, 0, data, remaining);
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

    model = Cache_RequestResource(0, ((PlacedProp *)object)->owner, ((PlacedProp *)object)->owner, 24, 4, 0, 0,
                          &g_statObjectIndexText, 0);
    if (model == 0) {
        return;
    }
    name = SetN64_LocatePackSection(*model, ((PlacedProp *)object)->owner, 3, &size);
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
                Graphu64_TransformPoint(((PlacedProp *)object)->matrix, &attachment->offset, &position);
                Events_DeliverContactEffect(object, object, attachment->type, -1, position, attachment->params);
            }
        }
        Cache_UnlockResource(0, table);
    }
    Cache_UnlockResource(0, model);
}

/* 800C8F30.CPP */
const char s_staticInstanceLitVerticesTag[13] = "lit vertices\000";
