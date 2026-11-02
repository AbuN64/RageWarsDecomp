#include "TYPES.H"
#include "COMMON/MANAGER.H"
#include "COMMON/RESOURCELOCKSTATE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/CACHE_RELEASERESOURCE.H"
#include "COMMON/PROPGEOMETRY.H"
#include "WORLD/STATIC_MODEL_INSTANCE_VIEWS.H"
#include "COMMON/OBJB.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"

struct ObjB;
extern CachedResource *Cache_RequestPairedResource(s32, s32, CachedResource *, CachedResource *, s32, void *, void *, void *, s32);
extern s32 SetN64_GetDirectoryEntry(s32 *, s32, s32);
extern s32 SetN64_LocatePackSection(void *, s32, s32, s32 *);
extern void Cache_UnlockResource(void *, CacheResourceNode *);
extern void Geometry_UnlockMaterialResources(void **);
void Simpinst_RegisterModelVariantResources(struct ObjB *object, s32 unused) {
    void *memory = object;
    ResourceObject23 *obj = memory;
    void *header;
    s32 *table;
    void **resource;
    void **found;
    CachedResource *block;
    s32 key;
    s32 index;
    index = obj->type;
    if (index != obj->loadedType) {
        resource = Cache_RequestResource(0, obj->model, obj->model, 24, 0, 0, 0, g_simpObjectIndexText, 1);
        if (resource != 0) {
            key = SetN64_GetDirectoryEntry(*resource, obj->model, 1);
            Cache_ReleaseResource(0, resource);
            found = Cache_RequestWordCountedResource(0, &header, key, g_simpModelsIndexText, 1);
            if (found != 0) {
                table = header;
                obj->resourceName = SetN64_LocatePackSection(table, key, index % table[0], &obj->resourceSize);
                obj->loadedType = index;
                Cache_ReleaseResource(0, found);
            }
        }
    }
    if (obj->resourceName != 0) {
        resource = Cache_RequestResource(0, obj->resourceName, obj->resourceName, obj->resourceSize, 0, 0, &g_simpleModelResourceCallbackAddress, g_simpModelText, 0);
    } else {
        resource = 0;
    }
    if (resource != 0) {
        Geometry_UnlockMaterialResources(resource);
        block = Cache_RequestPairedResource(0, g_litGeometryResourceKeyFlags, (void *)resource, obj->blockNode, 8, obj, &g_Simpinst_BuildLitGeometryResourceAddress, &s_litVerticesText, 0);
        if (block != 0) {
            Cache_UnlockResource(0, (void *)block);
        }
        Cache_UnlockResource(0, (void *)resource);
    }
}
