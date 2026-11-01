#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/GAME_SESSION.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include "COMMON/SHAREDPLAYER.H"
#include <PR/abi.h>
#include <ultra64.h>
#include "TYPES.H"
#include <PR/gbi.h>
#include "ENGINE/GEOMETRY.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

/* Draws the parts of a model resource that the owner has enabled, when the frame command buffer still has 3000 commands free: each part material's low two bits of byte 6 pick an owner flag at 0x102 (0x100, 0x8 or 0x2, 0x80 or 0x20 by bit 4) that must be set before Geometry_SetupMaterial accepts the material and its display list is emitted. Adapted from Geometry_DrawModelResource with the owner argument and the per-material flag switch added. */

extern Gfx *g_displayListCursor;
#include "COMMON/DISPLAY.H"
extern void Cache_MarkResourceInUse(s32, struct CacheResourceNode *);
extern s32 Geometry_ApplyMaterialLighting(s32 matrix, s32 lights, void *material);
extern s32 Geometry_SetupMaterial(void *material, s32 pass);

void Geometry_DrawVisibleOwnerParts(void **resource, struct Owner104 *owner, s32 matrix, s32 segment, s32 lights, void *textures, s32 pass) {
    void *header;
    void *base;
    void **parts;
    void *part;
    void *material;
    s32 count;
    s32 i;
    s32 visible;

    if (g_displayListCapacityUsRev1 - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
        return;
    }
    header = *resource;
    Cache_MarkResourceInUse(0, resource);
    if (segment != 0) { gSPSegment(g_displayListCursor++, 1, matrix); }
    else { gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD); }
    base = textures;
    if (base == 0) {
        base = SetN64_GetPackSection(header, 0);
    }
    gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
    parts = SetN64_GetPackSection(header, 2);
    count = *(s32 *)parts;
    for (i = 0; i < count; i++) {
        part = SetN64_GetPackSection(parts, i);
        material = SetN64_GetPackSection(part, 0);
        if (i == 0) {
            Geometry_ApplyMaterialLighting(matrix, lights, material);
        }
        visible = 1;
        switch (((struct Material *)material)->flags & 3) {
        case 2:
            if (!(((struct Material *)material)->flags & 4)) {
                if (!(owner->flags & 8)) {
                    visible = 0;
                }
            } else {
                if (!(owner->flags & 2)) {
                    visible = 0;
                }
            }
            break;
        case 3:
            if (!(((struct Material *)material)->flags & 4)) {
                if (!(owner->flags & 0x80)) {
                    visible = 0;
                }
            } else {
                if (!(owner->flags & 0x20)) {
                    visible = 0;
                }
            }
            break;
        case 1:
            if (!(owner->flags & 0x100)) {
                visible = 0;
            }
            break;
        }
        if (visible && Geometry_SetupMaterial(material, pass) != 0) {
            Gfx *cmd;
            void *list = SetN64_GetPackSection(part, 1);

            cmd = g_displayListCursor++;
            gSPDisplayList(cmd, (unsigned int)list);
        }
    }
}
extern NodeGeometryGroupModelInstances *g_opaqueMaterialGroupTree;
extern NodeGeometryGroupModelInstances *g_opaqueMaterialGroupList;
extern NodeGeometryGroupModelInstances *g_translucentMaterialGroupTree;
extern NodeGeometryGroupModelInstances *g_translucentMaterialGroupList;
extern void **g_modelBatchResource;
extern struct CacheResourceBlockView g_modelInstanceQueue[];


/* Returns the node keyed key in the tree under n, or the node a new key would hang from. */
static inline NodeGeometryGroupModelInstances *find_node(NodeGeometryGroupModelInstances *n, u32 key) {
    NodeGeometryGroupModelInstances *parent = ((void *) 0);

    while (n != ((void *) 0)) {
        if (n->key == key) {
            return n;
        }
        parent = n;
        if (key < n->key) {
            n = n->left;
        } else {
            n = n->right;
        }
    }
    return parent;
}

/* Files each entry of the list the resource g_modelBatchResource holds into one of two keyed trees, allocating a
 * node from g_materialGroups when its key is new, and appends one item per queued parameter in g_modelInstanceQueue
 * to that node's list; then clears the queue count g_modelInstanceQueueCount. */
void Geometry_GroupModelInstances(void) {
    s32 *list;
    s32 count;
    s32 i;
    s32 j;
    void *entry;
    ResourceSource *source;
    u32 key;
    NodeGeometryGroupModelInstances *parent;
    NodeGeometryGroupModelInstances *node;
    s32 *data;
    GeometryModelInstanceEntry *item;
    struct CacheResourceBlockView *param;

    if (g_modelInstanceQueueCount != 0) {
        list = SetN64_GetPackSection(*g_modelBatchResource, 2);
        count = *list;
        for (i = 0; i < count; i++) {
            entry = SetN64_GetPackSection(list, i);
            source = SetN64_GetPackSection(entry, 0);
            key = (source->id << 8) | (u8)g_modelBatchPass;
            if (source->flags & 0x700) {
                parent = find_node(g_translucentMaterialGroupTree, key);
            } else {
                parent = find_node(g_opaqueMaterialGroupTree, key);
            }
            if (parent != ((void *) 0) && parent->key == key) {
                node = parent;
            } else {
                if (g_materialGroupCount == 120) {
                    break;
                }
                node = &g_materialGroups[g_materialGroupCount++];
                node->key = key;
                node->source = source;
                node->tail = ((void *) 0);
                node->head = ((void *) 0);
                if (source->flags & 0x700) {
                    if (parent != ((void *) 0)) {
                        if (node->key < parent->key) {
                            parent->left = node;
                            node->right = ((void *) 0);
                            node->left = ((void *) 0);
                            node->next = parent;
                            node->prev = parent->prev;
                            if (parent->prev != ((void *) 0)) {
                                parent->prev->next = node;
                            }
                            parent->prev = node;
                            if (g_translucentMaterialGroupList == parent) {
                                g_translucentMaterialGroupList = node;
                            }
                        } else {
                            parent->right = node;
                            node->right = ((void *) 0);
                            node->left = ((void *) 0);
                            node->next = parent->next;
                            if (parent->next != ((void *) 0)) {
                                parent->next->prev = node;
                            }
                            node->prev = parent;
                            parent->next = node;
                        }
                    } else {
                        g_translucentMaterialGroupTree = node;
                        g_translucentMaterialGroupList = node;
                        node->right = ((void *) 0);
                        node->left = ((void *) 0);
                        node->next = ((void *) 0);
                        node->prev = ((void *) 0);
                    }
                } else {
                    if (parent != ((void *) 0)) {
                        if (node->key < parent->key) {
                            parent->left = node;
                            node->right = ((void *) 0);
                            node->left = ((void *) 0);
                            node->next = parent;
                            node->prev = parent->prev;
                            if (parent->prev != ((void *) 0)) {
                                parent->prev->next = node;
                            }
                            parent->prev = node;
                            if (g_opaqueMaterialGroupList == parent) {
                                g_opaqueMaterialGroupList = node;
                            }
                        } else {
                            parent->right = node;
                            node->right = ((void *) 0);
                            node->left = ((void *) 0);
                            node->next = parent->next;
                            if (parent->next != ((void *) 0)) {
                                parent->next->prev = node;
                            }
                            node->prev = parent;
                            parent->next = node;
                        }
                    } else {
                        g_opaqueMaterialGroupTree = node;
                        g_opaqueMaterialGroupList = node;
                        node->right = ((void *) 0);
                        node->left = ((void *) 0);
                        node->next = ((void *) 0);
                        node->prev = ((void *) 0);
                    }
                }
            }
            data = SetN64_GetPackSection(entry, 1);
            for (j = 0; j < g_modelInstanceQueueCount; j++) {
                param = &g_modelInstanceQueue[j];
                if (g_materialInstanceCount != 500) {
                    item = &g_materialInstances[g_materialInstanceCount++];
                    item->data = data;
                    item->modelParamFirst = param->first;
                    item->modelParamSecond = param->second;
                    item->modelParamThird = param->third;
                    item->sourceHalfFirst = source->copiedHalfFirst;
                    item->sourceHalfSecond = source->copiedHalfSecond;
                    item->modelParamFourth = param->fourth;
                    item->next = ((void *) 0);
                    if (node->tail != ((void *) 0)) {
                        node->tail->next = item;
                    } else {
                        node->head = item;
                    }
                    node->tail = item;
                }
            }
        }
        g_modelInstanceQueueCount = 0;
    }
}
