#include "include_asm.h"
#include "ANIM/RAY180.H"
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/APPROACHLOCATION.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/GAMEPLAY_MOVEMENT.H"
#include "COMMON/MOTION_STEP.H"
#include "COMMON/WORLD.H"
#include "COMMON/OUTPUT.H"
#include "COMMON/OBJB.H"
#include "COMMON/TRIPLE.H"
#include "ENGINE/UNICOL/POLYCOL.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

extern void Graphu64_MultiplyAffineMatrices(void *, void *, void *);


extern void *Scene_GetModelRecordByIndexPointer(Shared_World *, u16 *);

extern void CPlane_BuildTriangleNormal(QueryE0 *query);

/** Swap two pairs of words. */
void CPolyCollision_SwapHits(Hit8 *leftHit, Hit8 *rightHit) {
    Hit8 temporary = *leftHit;
    *leftHit = *rightHit;
    *rightHit = temporary;
}

s32 CPolyCollision_CompareHitFractions(Hit8 *a, Hit8 *b) {
    s32 order;
    order = 1;
    if ((a->t) < (b->t)) {
        order = -1;
    }
    return order;
}

void CPolyCollision_TraceElementMesh(void *contextAddress) {
    void *collisionElement;
    void **meshResource;
    void *meshData;
    s32 *displayListTable;
    s32 displayListCount;
    s32 index;

    collisionElement = ((ContextB0 *)contextAddress)->element;
    meshResource = ((ElementE8 *)collisionElement)->resource;
    if (meshResource != 0) {
        Graphu64_MultiplyAffineMatrices(&((ContextB0 *)contextAddress)->transform, &((ElementE8 *)collisionElement)->transform, &((ContextB0 *)contextAddress)->matrix);
        meshData = *meshResource;
        ((ContextB0 *)contextAddress)->vertices = SetN64_GetPackSection(meshData, 0);
        displayListTable = SetN64_GetPackSection(meshData, 2);
        displayListCount = *displayListTable;
        index = 0;
        if (displayListCount > 0) {
            do {
                PolyCol_TraceMeshDisplayList(contextAddress, SetN64_GetPackSection((void *) displayListTable, index));
                index += 1;
            } while (index < displayListCount);
        }
    }
}

void CPolyCollision_TraceCeilingTriangle(ActorB0 *actor) {
    extern s32 CCollision_TestSegmentPolygon(ActorB0 *, QueryE0 *, s32);
    QueryE0 query;
    u8 *data;
    s32 *flags;
    void *resource;
    s32 i;
    f32 height;

    data = actor->data;
    flags = actor->flags;
    if (data != 0) {
        resource = Scene_GetModelRecordByIndexPointer(&g_world, (u16 *)data);
        if (resource != 0) {
          if ((*flags & 8) != 0) {
           if ((*flags & 0x100000) == 0) {
            query.word14 = 3;
            for (i = 0; i < 3; i++) {
                query.vectors[2 - i].x = ((CollisionBuildTriangle *)data)->fields.v[i]->x;
                query.vectors[2 - i].y = ((CollisionBuildTriangle *)data)->fields.v[i]->ceiling +
                                         actor->height;
                query.vectors[2 - i].z = ((CollisionBuildTriangle *)data)->fields.v[i]->z;
            }
            CPlane_BuildTriangleNormal(&query);
            height = query.result.y;
            if ((0.10000000149011612f) < height) {
                query.word0 = 5;
                query.word4 = ((CCollisionInfo2_t *)flags)->WaterFriction;
                query.word8 = ((CCollisionInfo2_t *)flags)->GroundBehavior;
                query.input = 0;
                query.index = -1;
                query.word10 = 0;
                if ((((Shared_Surface *)resource)->flags & 0x400000) != 0) {
                    query.wordC = 7;
                } else if ((((Shared_Surface *)resource)->flags52 & 0x80) != 0) {
                    query.wordC = 8;
                } else {
                    query.wordC = 1;
                }
                CCollision_TestSegmentPolygon(actor, &query, 1);
            }
           }
          }
        }
    }
}



#if defined(VERSION_DE)
float k_CpolycollisionTraceceilingtriangleEncodedWordsBlock1[3] = {
    -0.7071f, 204.79999f, 1.0f,
};
#endif
