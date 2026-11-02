#include "../../../sdk/include/LIBC.H"
#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RESOURCELOCKSTATE.H"
#include "COMMON/GLOBALS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/PPDECOM_UNPACKRESOURCE.H"
#include "COMMON/SCENERECAT10C0.H"
#include "SCENE/SCENE_UPDATEANDDRAWWORLD.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include <ultra64.h>
#include <PR/gbi.h>
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "ENGINE/SCENE_GRID_AND_GEOMETRY_OPERATIONS.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/ACTOR_DEFINITION.H"

/* SCENE_3.CPP */
/* Tag of the cell grid packs (the first .rodata of this unit; the items overlay reads it too). */
const char s_gridSectionText[] = "grid section";
extern DraftStreamPair g_cameraVolumeBoundsMinZ;
extern char g_cResource_UnpackRequestEntry[];
extern s32 SetN64_LocatePackSection(void *, s32, s32, s32 *);
extern void **Cache_RequestPackSection(s32, void *, s32, s32, void *, void *, void *);
extern void Cache_LockResource(void *, CacheResourceNode *);

void Scene_RequestVisibleGridSections(DraftStreamWorld *world)
{
    s32 xCount, firstX, count;
    DraftStreamCell *cells;
    DraftStreamViewer *viewers, *viewer;
    DraftStreamTable *table;
    f32 *xLow, *xHigh, *zLow, *zHigh;
    DraftStreamCell *cell;
    DraftStreamHandle *resource;
    DraftStreamEntry *entry;
    s32 zCount, lastX, firstZ, lastZ;
    s32 x, z, row, loaded, size, visible, slot;

    viewers = (void *)g_gameplayCameraList.camera;
    if (viewers) {
        firstX = count = 0;
        table = SetN64_GetPackSection(world->grid, 0);
        firstZ=0;
        xLow = table->data.coordinates;
        xCount = table->count;
        table = SetN64_GetPackSection(world->grid, 1);
        xHigh = table->data.coordinates;
        lastX = xCount - 1;
        table = SetN64_GetPackSection(world->grid, 2);
        zLow = table->data.coordinates;
        zCount = table->count;
        table = SetN64_GetPackSection(world->grid, 3);
        zHigh = table->data.coordinates;
        table = SetN64_GetPackSection(world->grid, 4);
        lastZ = zCount - 1;
        cells = table->data.cells;
        while (firstX < xCount && xHigh[firstX] < g_cameraVolumeBounds.min.x) firstX++;
        while (lastX >= 0 && g_cameraVolumeBoundsMinZ.second < xLow[lastX]) lastX--;
        while (firstZ < zCount && zHigh[firstZ] < g_cameraVolumeBoundsMinZ.first) firstZ++;
        while (lastZ >= 0 && g_cameraVolumeMaxYzPair.second < zLow[lastZ]) lastZ--;
        entry = world->entries;
        { s32 focusX,focusZ;
        if (world->specialEnabled == 1) {
            focusX = (s32)((viewers->position.x - world->originX) / world->cellX);
            focusZ = (s32)((viewers->position.z - world->originZ) / world->cellZ);
        } else focusZ = focusX = -1;
        if (focusX < 0 || focusX >= xCount || focusZ < 0 || focusZ >= zCount) world->specialPresent = 0;
        else {
            world->specialPresent = 1;
            world->special = (void *)Cache_RequestPackSection(0, world->specialTable, focusX + focusZ * xCount + 1,
                world->resourceKey, world, g_cResource_UnpackRequestEntry, "Vis Info");
            Cache_LockResource(0, (void *)world->special);
            Visdata_DecodeRegionGrid(world->specialState, focusX, focusZ, world->special->data, &viewers->position);
        }
        }
        z = firstZ;
        if(z<=lastZ) {
        row = z * xCount;
        do {
            for (x = firstX, slot=x+row; x <= lastX; x++,slot=x+row) {
                        cell = &cells[slot];
                if (cell->occupied) continue;
                visible = 0;
                for (viewer = viewers; viewer; viewer = viewer->next) {
                    if (viewer->minimum.x < cell->maxX && cell->minX < viewer->maximum.x &&
                        cell->maxZ > viewer->minimum.z && cell->minZ < viewer->maximum.z) {
                        visible = 1;
                        break;
                    }
                }
                if (visible) {
                    loaded = SetN64_LocatePackSection(world->table, world->key, slot, &size);
                    resource = Cache_RequestResource(0, loaded, loaded, size, 8, world,
                                              g_scene_BuildPlacedInstancesEntry, s_gridSectionText, 0);
                    if (resource) {
                        if (resource->data->count) {
                            entry->resource = resource;
                            entry->cell = cell;
                            entry->x = x;
                            entry->z = z;
                            entry++;
                            count++;
                            if (count == 128) goto finished;
                        } else Cache_UnlockResource(0,(void *)resource);
                    }
                }
            }
            row+=xCount; z++;
        } while(z<=lastZ);
        }
finished:
        world->entryCount = count;
        world->activeCount = count;
    }
}

/* One geometry vertex of a prop's collision mesh (stride from its section header). */
typedef struct ScenePoint { s16 x, y, z; } ScenePoint;
extern Gfx *g_displayListCursor;
extern void **Cache_AllocateResource(s32, s32, s32, char *);
extern int Statinst_GetPropModelIndex(char *object);
extern s32 Statinst_GetPropGeometryIndex(ObjectSceneDrawCachedOpaqueGeometry *object);
extern s32 *Statinst_CollectPropResources(void *prop, s32 model, s32 geometryVariant, s32 *nextResource);
extern void Statinst_DrawModel(ObjectSceneDrawCachedOpaqueGeometry *object, void *camera);
extern DraftStreamHandle *Statinst_AcquireGeometry(ObjectSceneDrawCachedOpaqueGeometry *object, s32 index);
extern void Graphu64_ConvertMatrixToFloat(f32 *dst, PackedMatrixWords *src);

void Scene_BuildCachedGeometry(DraftStreamWorld *world) {
    f32 matrix[16];
    CVector3 position;
    CVector3 transformed;
    DraftStreamHandle *resources[3000];
    ObjectSceneDrawCachedOpaqueGeometry *props[512];
    s32 resourceSize;
    s32 xCount;
    s32 z;
    s32 lastX;
    s32 lastZ;
    DraftStreamCell *cells;
    DraftStreamCell *cell;
    s32 propCount;
    ObjectSceneDrawCachedOpaqueGeometry **nextProp;
    Gfx *firstGfx;
    s32 row;
    DraftStreamHandle **nextResource;
    DraftStreamHandle *resource;
    struct CacheResourceBlockView *handle;
    DraftStreamHandle *geometry;
    DraftStreamTable *table;
    DraftStreamData *resourceData;
    DraftStreamTable *points;
    ObjectSceneDrawCachedOpaqueGeometry *prop;
    ObjectSceneDrawCachedOpaqueGeometry *objects;
    ScenePoint *point;
    s32 zCount;
    s32 x;
    s32 slot;
    s32 key;
    s32 p;
    s32 i;
    s32 count;
    s32 model;
    s32 resourceBytes;
    s32 propBytes;
    s32 gfxBytes;
    s32 offset;
    s32 *cache;
    f32 height;
    f32 maximum;
    s32 firstX;
    s32 size;

    nextResource = resources;
    nextProp = props;
    firstX = 0;
    firstGfx = g_displayListCursor;
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_2CYCLE);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RNX, FRUSTRATIO_2);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RNY, FRUSTRATIO_2);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RPX, (u16)-FRUSTRATIO_2);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RPY, (u16)-FRUSTRATIO_2);
    z = 0;
    Geometry_BeginModelBatch();
    xCount = ((DraftStreamTable *)SetN64_GetPackSection(world->grid, 0))->count;
    zCount = ((DraftStreamTable *)SetN64_GetPackSection(world->grid, 2))->count;
    cells = ((DraftStreamTable *)SetN64_GetPackSection(world->grid, 4))->data.cells;
    lastZ = zCount - 1;
    lastX = xCount - 1;
    if (z <= lastZ) {
        row = z * xCount;
        do {
            for (x = firstX; x <= lastX; x++) {
                slot = x + row;
                cell = &cells[slot];
                if (cell->occupied == 0) {
                    key = SetN64_LocatePackSection(world->table, world->key, slot, &resourceSize);
                    resource = Cache_RequestResource(0, key, key, resourceSize, 4, (s32)world, g_scene_BuildPlacedInstancesEntry, s_gridSectionText, 1);
                    if (resource != 0) {
                        resourceData = resource->data;
                        if (resourceData->count != 0) {
                            Cache_LockResource(0, (CacheResourceNode *)resource);
                            *nextResource++ = resource;
                            table = SetN64_GetPackSection(resourceData, 0);
                            propCount = table->count;
                            objects = table->data.objects;
                            for (p = 0; p < propCount; p++) {
                                prop = &objects[p];
                                if (!(prop->flags & 0x40)) {
                                    prop->resource = resource;
                                    if ((prop->flags & 4) || Statinst_GetPropModelIndex(prop) < 0) {
                                        *nextProp++ = prop;
                                    } else {
                                        model = Statinst_GetPropModelIndex(prop);
                                        nextResource = Statinst_CollectPropResources(prop, model, Statinst_GetPropGeometryIndex(prop), nextResource);
                                        Statinst_DrawModel(prop, 0);
                                    }
                                    geometry = Statinst_AcquireGeometry(prop, Statinst_GetPropGeometryIndex(prop));
                                    if (geometry != 0) {
                                        points = SetN64_GetPackSection(geometry->data, 0);
                                        count = points->count;
                                        Graphu64_ConvertMatrixToFloat(matrix, &prop->transform);
                                        for (i = 0; i < count; i++) {
                                            point = (ScenePoint *)(points->data.bytes + i * points->stride);
                                            position.x = (f32)point->x;
                                            position.y = (f32)point->y;
                                            position.z = (f32)point->z;
                                            Graphu64_TransformPoint(matrix, &position, &transformed);
                                            height = transformed.y;
                                            maximum = world->maximumHeight;
                                            if (!(height <= maximum)) height = maximum;
                                            world->maximumHeight = height;
                                        }
                                        Cache_UnlockResource(0, (CacheResourceNode *)geometry);
                                    }
                                }
                            }
                        }
                        Cache_UnlockResource(0, (CacheResourceNode *)resource);
                    }
                }
            }
            row += xCount;
            z++;
        } while (z <= lastZ);
    }
    *nextResource++ = 0;
    *nextProp++ = 0;
    Geometry_FlushModelBatch();
    /* Cache blob: header {3 sections, offsets}, then the resource list, the prop list and the display list, each 8-aligned. */
    resourceBytes = (u8 *)nextResource - (u8 *)resources;
    offset = ((resourceBytes + 7) & ~7) + 24;
    propBytes = (u8 *)nextProp - (u8 *)props;
    size = propBytes + 7;
    size &= ~7;
    count = offset;
    offset += size;
    gSPEndDisplayList(g_displayListCursor++);
    gfxBytes = (u8 *)g_displayListCursor - (u8 *)firstGfx;
    handle = Cache_AllocateResource(0, offset + ((gfxBytes + 7) & ~7), 3, "Multi player data");
    world->cacheHandle = handle;
    cache = handle->data;
    world->cache = cache;
    cache[0] = 3;
    world->cache[1] = 24;
    world->cache[2] = count;
    world->cache[3] = offset;
    Libc_CopyBytes(SetN64_GetPackSection(world->cache, 0), resources, resourceBytes);
    Libc_CopyBytes(SetN64_GetPackSection(world->cache, 1), props, propBytes);
    Libc_CopyBytes(SetN64_GetPackSection(world->cache, 2), firstGfx, gfxBytes);
    g_displayListCursor = firstGfx;
}

/* SCENE_4.CPP */
/* Draws a scene through cached display lists: loads the scene if needed (returning if that fails), calls the model's base list, and on first use records two lists in the frame's command stream, one for objects without flag 4 and one for objects with it, each drawn through Statinst_DrawModel inside a Geometry_BeginModelBatch pass and preceded by a branch past its end; finally calls the first cached list. */

void Scene_DrawCachedOpaqueGeometry(SceneSceneDrawCachedOpaqueGeometry *scene, void *camera) {
    ObjectSceneDrawCachedOpaqueGeometry **objects;
    ObjectSceneDrawCachedOpaqueGeometry *object;
    Gfx *branch;
    s32 pass;

    if (scene->loaded == 0) {
        Cache_DrainAndCompactResources(0);
        Scene_BuildCachedGeometry(scene);
        if (scene->loaded == 0) {
            return;
        }
    }
    gSPDisplayList(g_displayListCursor++, (unsigned int)SetN64_GetPackSection(scene->model, 2));
    if (scene->lists[0] == 0) {
        for (pass = 0; pass < 2; pass++) {
            scene->lists[pass] = g_displayListCursor;
            gSPBranchList(g_displayListCursor++, 0);
            Geometry_BeginModelBatch();
            objects = SetN64_GetPackSection(scene->model, 1);
            while (*objects != 0) {
                object = *objects++;
                switch (pass) {
                case 0:
                    if (!(object->flags & 4)) {
                        Statinst_DrawModel(object, camera);
                    }
                    break;
                case 1:
                    if (object->flags & 4) {
                        Statinst_DrawModel(object, camera);
                    }
                    break;
                }
            }
            Geometry_FlushModelBatch();
            gSPEndDisplayList(g_displayListCursor++);
            gSPBranchList(scene->lists[pass]++, (unsigned int)g_displayListCursor);
        }
    }
    gSPDisplayList(g_displayListCursor++, (unsigned int)scene->lists[0]);
}

extern void Cache_ReleaseResource(void *cacheContext, void *resource);

/* One sector of the world: its model resource, its x/z extent and its cell in the streaming grid. */
/* Views of the SN debug records this pass reads, with their original member names: CScene_t (0x1B930 bytes),
 * CActiveGridSection_t (0xC), CBoundsRect_t (0x10), CGameStaticInstance_t (0xE8) and CGameSimpleInstance_t (0x1C8). */
typedef struct CBoundsRect_t {
    f32 m_MinX;
    f32 m_MinZ;
    f32 m_MaxX;
    f32 m_MaxZ;
} CBoundsRect_t;
typedef struct CActiveGridSection_t {
    struct CacheResourceNode *m_pmeGridSection;
    CBoundsRect_t *m_pBoundsRect;
    u16 gridSectionX;
    u16 gridSectionZ;
} CActiveGridSection_t;
typedef struct CGameStaticInstance_t {
    char pad0[0x4];
    u16 m_nObjType; /* ih.m_nObjType */
    char pad6[0x18 - 0x6];
    ActorDefinitionHeader *m_pI; /* ih.m_pI */
    char pad1C[0x4];
    struct CacheResourceNode *m_pmeGridSection;
    char pad24[0xB8 - 0x24];
    Box m_Bounds;
    char padD0[0xD8 - 0xD0];
    u16 m_wFlags; /* 4 drawn late, 8 static event, 0x200 culled */
    char padDA[0xE8 - 0xDA];
} CGameStaticInstance_t;
typedef struct CGameSimpleInstance_t {
    char pad0[0x18];
    ActorDefinitionHeader *m_pI; /* ah.ih.m_pI */
    char pad1C[0x60 - 0x1C];
    struct CacheResourceNode *m_pmeGridSection;
    char pad64[0x17C - 0x64];
    Box m_Bounds;
    char pad194[0x19C - 0x194];
    u16 m_wFlags; /* 1 hidden, 2 frustum tested, 0x20 drawn late */
    char pad19E[0x1C0 - 0x19E];
    s32 m_VisBits;
    char pad1C4[0x4];
} CGameSimpleInstance_t;
typedef struct ScenePropSection {
    s32 kind;
    s32 count;
    CGameStaticInstance_t props[1];
} ScenePropSection;
typedef struct SceneStaticSection {
    s32 kind;
    s32 count;
    CGameSimpleInstance_t statics[1];
} SceneStaticSection;
typedef struct CScene_t {
    char pad0[0x94];
    SceneModelIdTable *m_pusObjectTypes;
    char pad98[0xB4C - 0x98];
    CGameStaticInstance_t *m_pStaticEventsInstances[64];
    s32 m_nStaticEventsInstances;
    char padC50[0x10BC - 0xC50];
    s32 m_nTransparentInstances;
    void *m_pTransparentInstances[64];
    char pad11C0[0x1504 - 0x11C0];
    s32 m_nActiveGridSections;
    CActiveGridSection_t m_ActiveGridSections[128];
    char pad1B08[0x1B6B0 - 0x1B08];
    struct CacheResourceNode *m_pmeVisibilityData;
    char m_VisData[604]; /* CVisibilityData_t */
    char pad1B910[0x1B928 - 0x1B910];
    s32 m_bVisibilityValid;
    char pad1B92C[0x1B930 - 0x1B92C];
} CScene_t;

extern s32 g_textureVariationBypassEnabled;
extern s32 g_gameLoopFrameCount;
extern SharedCameraOwnerView *Gsky_FindScreenMessage(GameplayCamera *camera);
extern s32 Visdata_TestVisibilityGridBit(void *grid, s32 x, s32 z, s32 index);
extern s32 Visdata_TestBoxAgainstFrustum(void *planes, void *bounds);
extern void Statinst_RegisterGeometryResources(CGameStaticInstance_t *prop, GameplayCamera *camera);
extern s32 Statinst_UpdateDistanceFade(void *prop, s32 cameraAddress);
extern void Statinst_DrawDistanceFadedModel(CGameStaticInstance_t *prop, GameplayCamera *camera);
extern void Simpinst_RegisterModelVariantResources(CGameSimpleInstance_t *object, GameplayCamera *camera);
struct StaticObject; extern void Simple_DrawCachedModel(struct StaticObject *obj);

static __inline__ s32 SceneFindShip(SceneModelIdTable *table) {
    s32 i;
    s32 count = table->count;
    u16 *p = table->entries;
    for (i = 0; i < count; i++) {
        if (p[i] == 51) {
            return i;
        }
    }
    return -1;
}
void Scene_DrawVisibleInstances(CScene_t *world, GameplayCamera *camera) {
    CScene_t *scene;
    CGameStaticInstance_t *props;
    CGameStaticInstance_t *prop;
    s32 model;
    s32 sectorIndex;
    s32 sectorCount;
    u32 mask;
    s32 viewMask;
    s32 shipModel;
    s32 showShip;
    SharedCameraOwnerView *player;
    CActiveGridSection_t *sector;
    CActiveGridSection_t *sectors;
    CGameSimpleInstance_t *statics;
    ScenePropSection *propSection;
    SceneStaticSection *staticSection;
    s32 propCount;
    s32 staticCount;
    s32 queued;
    s32 i;

    mask = g_gameSettings.sceneMask;
    viewMask = camera->floorSurface;
    world->m_nTransparentInstances = 0;
#if defined(VERSION_US_REV1)
    if (g_textureVariationBypassEnabled == 0 && g_gameSettings.local != 0) {
#else
    if (g_gameSettings.local != 0) {
#endif
        Scene_DrawCachedOpaqueGeometry(world, camera);
        return;
    }
    player = Gsky_FindScreenMessage(camera);
    shipModel = SceneFindShip(world->m_pusObjectTypes);
    showShip = 0;
    if (player != NULL && shipModel != -1) {
        showShip = g_gameSettings.local == 0;
    }
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_2CYCLE);
    scene = world;
    Geometry_BeginModelBatch();
    scene->m_nTransparentInstances = 0;
    if (player != NULL && (player->movementFlags & 0x100)) {
        gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RNX, FRUSTRATIO_1);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RNY, FRUSTRATIO_1);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RPX, (u16)-FRUSTRATIO_1);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RPY, (u16)-FRUSTRATIO_1);
    } else {
        gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RNX, FRUSTRATIO_2);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RNY, FRUSTRATIO_2);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RPX, (u16)-FRUSTRATIO_2);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, G_MWO_CLIP_RPY, (u16)-FRUSTRATIO_2);
    }
    sectorCount = scene->m_nActiveGridSections;
    sectors = scene->m_ActiveGridSections;
    for (sectorIndex = 0; sectorIndex < sectorCount; sectorIndex++) {
        sector = &sectors[sectorIndex];
        if (!(sector->m_pBoundsRect->m_MaxX > camera->clipBounds[0].x && sector->m_pBoundsRect->m_MinX < camera->clipBounds[1].x &&
              sector->m_pBoundsRect->m_MaxZ > camera->clipBounds[0].z && sector->m_pBoundsRect->m_MinZ < camera->clipBounds[1].z)) {
            continue;
        }
        Cache_MarkResourceInUse(0, sector->m_pmeGridSection);
        model = sector->m_pmeGridSection->data;
        propSection = SetN64_GetPackSection(model, 0);
        propCount = propSection->count;
        props = propSection->props;
        for (i = 0; i < propCount; i++) {
            prop = props;
            prop += i;
            queued = 0;
            if (!(prop->m_pI->gate & mask)) {
                continue;
            }
            prop->m_pmeGridSection = sector->m_pmeGridSection;
            if (g_gameLoopFrameCount == 0) {
                Statinst_RegisterGeometryResources(prop, camera);
            }
            if ((prop->m_wFlags & 8) && (prop->m_pI->flags & 4)) {
                queued = 1;
                if (prop->m_nObjType == shipModel) {
                    if (showShip && scene->m_nStaticEventsInstances != 64) {
                        scene->m_pStaticEventsInstances[scene->m_nStaticEventsInstances++] = prop;
                    }
                } else if (scene->m_nStaticEventsInstances != 64) {
                    scene->m_pStaticEventsInstances[scene->m_nStaticEventsInstances++] = prop;
                }
            }
            if (scene->m_bVisibilityValid != 0 &&
                Visdata_TestVisibilityGridBit(scene->m_VisData, sector->gridSectionX, sector->gridSectionZ, i) == 0) {
                continue;
            }
            if (camera->clipBounds[1].x > prop->m_Bounds.min.x && camera->clipBounds[0].x < prop->m_Bounds.max.x &&
                camera->clipBounds[1].z > prop->m_Bounds.min.z && camera->clipBounds[0].z < prop->m_Bounds.max.z &&
                camera->clipBounds[1].y > prop->m_Bounds.min.y && camera->clipBounds[0].y < prop->m_Bounds.max.y &&
                Visdata_TestBoxAgainstFrustum(camera->clipPlanes, &prop->m_Bounds)) {
                if ((prop->m_wFlags & 8) && !queued && (prop->m_nObjType != shipModel || showShip)) {
                    if (scene->m_nStaticEventsInstances != 64) {
                        scene->m_pStaticEventsInstances[scene->m_nStaticEventsInstances++] = prop;
                    }
                }
                if (Statinst_UpdateDistanceFade(prop, camera)) {
                    if (prop->m_wFlags & 4) {
                        if (scene->m_nTransparentInstances != 64) {
                            scene->m_pTransparentInstances[scene->m_nTransparentInstances++] = prop;
                        }
                    } else {
                        Statinst_DrawDistanceFadedModel(prop, camera);
                    }
                }
                prop->m_wFlags &= ~0x200;
            } else {
                prop->m_wFlags |= 0x200;
            }
        }
        staticSection = SetN64_GetPackSection(model, 1);
        staticCount = staticSection->count;
        statics = staticSection->statics;
        for (i = 0; i < staticCount; i++) {
            statics[i].m_pmeGridSection = sector->m_pmeGridSection;
            if (g_gameLoopFrameCount == 0) {
                Simpinst_RegisterModelVariantResources(&statics[i], camera);
            }
            if ((statics[i].m_pI->gate & mask) && !(statics[i].m_wFlags & 1) && (viewMask & statics[i].m_VisBits) &&
                camera->clipBounds[1].x > statics[i].m_Bounds.min.x && camera->clipBounds[0].x < statics[i].m_Bounds.max.x &&
                camera->clipBounds[1].z > statics[i].m_Bounds.min.z && camera->clipBounds[0].z < statics[i].m_Bounds.max.z &&
                camera->clipBounds[1].y > statics[i].m_Bounds.min.y && camera->clipBounds[0].y < statics[i].m_Bounds.max.y &&
                (statics[i].m_wFlags & 2) && Visdata_TestBoxAgainstFrustum(camera->clipPlanes, &statics[i].m_Bounds)) {
                if (statics[i].m_wFlags & 0x20) {
                    if (scene->m_nTransparentInstances != 64) {
                        scene->m_pTransparentInstances[scene->m_nTransparentInstances++] = &statics[i];
                    }
                } else {
                    Simple_DrawCachedModel(&statics[i]);
                }
            }
        }
    }
    Geometry_FlushModelBatch();
    if (scene->m_bVisibilityValid != 0) {
        Cache_UnlockResource(NULL, scene->m_pmeVisibilityData);
        Cache_ReleaseResource(NULL, scene->m_pmeVisibilityData);
    }
}
