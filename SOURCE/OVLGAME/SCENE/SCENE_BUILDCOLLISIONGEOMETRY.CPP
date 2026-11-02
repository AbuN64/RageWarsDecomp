
/* Packs a collision mesh into one allocated block: copies the node's vertex list, the triangle source
   and the trailing chunk behind a five-offset header, builds a 0x20-byte triangle record per source
   face, lowers the world's minimum height to every triangle vertex, and flags triangles whose group
   bit, callback or neighbours mark them with the default surface mask. */
#include "TYPES.H"
#include "COMMON/LONE/g_defaultCameraSurfaceType.H"
#include "COMMON/PACKED.H"
#include "COMMON/RESOURCELOCKSTATE.H"
#include "COMMON/PPDECOM_UNPACKRESOURCE.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/SHARED_MENUREPLY.H"
#include "COMMON/OBJB.H"
#include "MENU/SCENE_RESOURCE_PREVIEW_AND_COLLISION_VIEWS.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
struct CacheResourceBlockView;
extern struct CacheResourceBlockView *Cache_AllocResourceBlock(s32 cache, void *handle, s32 total);
extern void Cache_ReplaceResourceBlock(s32 unused, struct CacheResourceBlockView **handle, struct CacheResourceBlockView *replacement);













extern s32 SetN64_GetSizedPackSection(s32 node, s32 index, s32 *size);
extern s32 SetN64_GetPackSectionSize(s32 *node, s32 index);

static inline s32 testBit(s32 n, u8 *bits) {
    s32 mask = 1 << (n & 7);

    return bits[n / 8] & mask;
}

void Scene_BuildCollisionGeometry(CollisionBuildWorld *world, CollisionBuildMeshHandle **handle) {
    s32 size0;
    s32 size1;
    s32 size3;
    void *chunk;
    s32 tableSize;
    char *base;
    CollisionBuildVertex *verts;
    CollisionBuildTriangle *tris;
    CollisionBuildMeshHandle *block;
    int *node;
    void *first;
    CollisionBuildVertexList *vlist;
    CollisionBuildList *flist;
    s32 ntris;
    CollisionBuildHeader *hdr;
    s32 offset;
    char *dst;
    char *vdst;
    CollisionBuildVertexList *copiedVertices;
    CollisionBuildTriangleList *copiedTriangles;
    s32 nverts;
    s32 i;
    s32 j;
    s32 k;
    CollisionBuildTriangle *tri;
    CollisionBuildFace *face;
    f32 y;
    int *group;
    s32 index;
    u8 *bits;

    if (Ppdecom_UnpackResource((void*)handle, 1) != 0) {
        node = (*handle)->payload.data;
        first = ((void *(*)(int *,s32,s32 *))SetN64_GetSizedPackSection)(node, 0, &size0);
        vlist = ((void *(*)(int *,s32,s32 *))SetN64_GetSizedPackSection)(node, 1, &size1);
        flist = (void*)SetN64_GetPackSection(node, 2);
        ntris = flist->count;
        chunk = ((void *(*)(int *,s32,s32 *))SetN64_GetSizedPackSection)(node, 3, &size3);
        tableSize = (ntris << 5) | 8;
        block = (void*)Cache_AllocResourceBlock(0, handle, size0 + 24 + size1 + tableSize + size3);
        if (block != 0) {
            offset = 24;
            hdr = block->payload.data;
            i = 0;
            hdr->count = 0;
            hdr->offsets[0] = offset;
            SetN64_TransposeRecords(first, (char *) hdr + offset, 0);
            hdr->count = 1;
            offset += size0;
            vdst = (char *) hdr + offset;
            hdr->offsets[1] = offset;
            SetN64_TransposeRecords(vlist, vdst, 0);
            hdr->count = 2;
            offset += size1;
            dst = (char *) hdr + offset;
            hdr->offsets[2] = offset;
            SetN64_TransposeRecords(flist, dst, 1);
            face = flist->items;
            copiedTriangles=(void*)dst;
            copiedTriangles->kind = 32;
            copiedTriangles->count = ntris;
            base = (char *) hdr;
            tris = copiedTriangles->items;
            nverts = vlist->count;
            copiedVertices=(void*)vdst;
            verts = copiedVertices->items;
            for (i = 0; i < nverts; i++) {
                Region_ScaleWordsToFloats(&verts[i]);
            }
            for (j = 0; j < ntris; j++) {
                tri = &tris[j];
                /* The caller supplies a sixth bounds value; the decoder uses the first five. */
                ((void (*)(CGameRegion *,Packed *,char *,int,char *,int))Region_DecodePackedRegion)(&tri->canonical, &face[j], (char*)verts, nverts, (char*)tris, ntris);
                for (i = 0; i < 3; i++) {
                    y = tri->fields.v[i]->y;
                    if (!(y <= world->minY)) {
                        y = world->minY;
                    }
                    world->minY = y;
                }
                index = world->group;
                group = (void*)SetN64_GetPackSection((void*)SetN64_GetPackSection((void*)SetN64_GetPackSection(world->tree, 0), index), 0);
                SetN64_GetPackSection(group, 0);
                SetN64_GetPackSectionSize(group, 1);
                bits = (void*)SetN64_GetPackSection(group, 1);
                if (testBit(j, bits)) {
                    tri->fields.flags |= 0x400;
                }
                if (!(tri->fields.mask & g_defaultCameraSurfaceType)) {
                    tri->fields.mask = g_defaultCameraSurfaceType;
                }
                if (Cinema_IsSequenceInWindow() != 0) {
                    tri->fields.mask = g_defaultCameraSurfaceType;
                }
                if (tri->fields.flags & 0x2000) {
                    tri->fields.mask = g_defaultCameraSurfaceType;
                }
            }
            for (j = 0; j < ntris; j++) {
                tri = &tris[j];
                for (k = 0; k < 3; k++) {
                    if (tri->fields.adj[k] != 0 && (tri->fields.adj[k]->fields.flags & 0x2000)) {
                        { s32 *surface = &tri->fields.mask; *surface = g_defaultCameraSurfaceType; }
                    }
                }
            }
            offset += tableSize;
            hdr->count = 3;
            hdr->offsets[3] = offset;
            SetN64_TransposeRecords(chunk, base + offset, 0);
            hdr->count = 4;
            offset += size3;
            hdr->offsets[4] = offset;
        }
        Cache_ReplaceResourceBlock(0, (void*)handle, (void*)block);
    }
}
