#include "include_asm.h"
#include "Menu/Items/items.h"
#include "Scene/cache_requestresource.h"
#include "Render/setn64_getpacksection.h"
#include "Common/objb.h"
#include "Common/world.h"
#include "Common/cache_releaseresource.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Engine/session.h"
#include "Menu/Items/Scene/scene_findactortriggerrange.h"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
const char s_gamePersistentDataText[24] =
    "game persistent data\000\000\000\000";
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const char s_gamePersistentDataText[21] =
    "game persistent data\000";
#endif
#endif

#if defined(VERSION_US_REV1)
const char g_gamePersistentData[21] =
    "game persistent data";
#endif

void Scene_CopySimpleModelHeader(void *level, void *buffer, s32 name) {
    void *table;
    s32 bytes;
    s32 key;
    s32 size;
    s32 shapeKey;
    s32 index;
    void **header;
    void **resource;
    void **shape;
    void *first;
    u32 *source;
    index = Scene_FindModelIdIndex(level, name);
    if (index == -1) {
        ((u32 *)buffer)[2] = 0;
    } else {
        size = Scene_GetIndexedModelResource(level, index);
        header = Cache_RequestResource(0, size, size, 24, 0, 0, 0, g_constructMapObjectIndex, 1);
        if (header != 0) {
            key = SetN64_GetDirectoryEntry(*header, size, 1);
            resource = Cache_RequestWordCountedResource(0, &table, key, g_constructMapSimpModelsIndex, 1);
            if (resource != 0) {
                shapeKey = SetN64_LocatePackSection(table, key, 0, &bytes);
                shape = Cache_RequestResource(0, shapeKey, shapeKey, bytes, 0, 0, &g_simpleModelResourceCallbackAddress, g_constructMapSimpleModel, 1);
                if (shape != 0) {
                    first = SetN64_GetPackSection(*shape, 2);
                    first = SetN64_GetPackSection(first, 0);
                    source = SetN64_GetPackSection(first, 0);
                    *(SimpleModelHeader *)buffer = *(SimpleModelHeader *)source;
                    Cache_ReleaseResource(0, shape);
                }
                Cache_ReleaseResource(0, resource);
            }
            Cache_ReleaseResource(0, header);
        }
    }
}
