#include "TYPES.H"
#include <ultra64.h>
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/CACHE_RELEASERESOURCE.H"
#include "COMMON/PROPGEOMETRY.H"
#include "COMMON/OBJB.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"

extern char g_statObjectIndexText[];
extern s32 SetN64_GetDirectoryEntry(s32 *,s32,s32);
extern s32 SetN64_LocatePackSection(void *,s32,s32,s32 *);
extern void Cache_LockResource(void *,CacheResourceNode *);
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
