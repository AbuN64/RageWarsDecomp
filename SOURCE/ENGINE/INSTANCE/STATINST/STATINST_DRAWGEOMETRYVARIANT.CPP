#include "COMMON/MODEL_RENDER.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include "COMMON/MANAGER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/LEVEL_SPAWN.H"
#include "COMMON/PROPGEOMETRY.H"
#include "TYPES.H"
#include "ACTORS/LIGHTING_BUILDLITMODEL.H"
#include "SCENE/RESOURCE_BINDING_AND_FADE_VIEWS.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
extern s32 g_gameFrameCounter;

/* Returns the matching resource entry index, or minus one when absent. */

extern void *Statinst_AcquireGeometry(ResourceOwner *owner,s32 index);

extern void Geometry_UnlockMaterialResources(void **modelResource);

extern void Cache_UnlockResource(s32 cache, s32 resource);

extern s32 g_litGeometryResourceKeyFlags;

extern char g_Statinst_BuildLitGeometryResourceAddress;

extern char s_staticLitGeometryResourceTag[];

void Statinst_DrawDistanceFadedModel(void *);

void Statinst_DrawModel(void *);


extern void Cache_TouchResourceByKey(s32 cache, s32 resourceKey);

extern s32 *Geometry_CollectMaterialResources(void **modelResource, s32 variation, s32 *resourcesOut);


extern void Cache_MarkResourceInUse(s32, struct CacheResourceNode *);

extern void Link_AnimateVertexColors(void *object, void *colors);

extern void Geometry_QueueModelInstance(void **, void *, s32, void *, void *, s32);

extern void Cache_UnlockResource(s32, s32);

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

/** Return the nested signed byte unless flag 0x40 suppresses it. */
int Statinst_GetPropModelIndex(char *object) {
    if (((ActorResourceStatusView *)(object))->statusFlags & 0x40) {
        return 0;
    }
    return ((struct GeometryVariantByteView *) ((ActorResourceStatusView *) object)->geometryVariant)->propModelIndex;
}

/** Read the signed byte at offset 0xE from the object's linked record. */
signed char Statinst_GetPropGeometryIndex(struct PlacedProp *object) {
    void *linked = object->model;
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

/** Advance the wrapping counter g_staticObjectResourceSerial, resetting to 0x380000 at 0x3FFFFF. */
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

void Statinst_DrawGeometryVariant(OwnerStaticInstanceDrawGeometryVariant *owner, s32 unused, s32 remaining, s32 key) {
    void *instance;
    CachedResource *resource;
    s32 *header;
    char *data;

    instance = Statinst_AcquireGeometry(owner, key);
    if (instance == 0) {
        return;
    }
    resource = Cache_RequestPairedResource(0, owner->flagsD0 | g_litGeometryResourceKeyFlags, instance, (CachedResource *)owner->resourceDescriptor, 8, owner, &g_Statinst_BuildLitGeometryResourceAddress,
                             s_staticLitGeometryResourceTag, 0);
    if (resource != 0) {
        Cache_MarkResourceInUse(0, (s32)resource);
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
        Cache_UnlockResource(0, (s32)resource);
    }
    Cache_UnlockResource(0, (s32)instance);
    owner->colorFrame = (u8)g_gameFrameCounter;
}

/** Select one of two signed bytes according to a doubled nested count. */
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
