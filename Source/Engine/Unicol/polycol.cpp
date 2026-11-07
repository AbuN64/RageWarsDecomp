#include "Common/level_actor.h"
#include "types.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/runtime_declarations.h"
#include "Common/ppdecom_unpackresource.h"
#include "Anim/collision_ray.h"
#include "Engine/Unicol/polycol.h"
#include "Render/setn64_getpacksection.h"
#include "Collide/ccollision_testsegmentdisk.h"
#include "Engine/Unicol/plane.h"
#include "Ppdecom/ppdecom_quicksortrecords.h"
#include "Engine/Unicol/Polycol/polycol_tracegeometry.h"
#include "Collide/ccollision_intersectsegmentbox.h"
#include "Engine/Unicol/Instcol/instcol.h"
#include "include_asm.h"
#include "Common/resident_event_handler.h"
#include "Common/approachlocation.h"
#include "Common/ballisticparams.h"
#include "Common/gameplay_movement.h"
#include "Common/motion_step.h"
#include "Common/world.h"
#include "Common/output.h"
#include "Common/objb.h"
#include "Common/triple.h"
#include "Fx/normalize_vector.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Engine/Unicol/Polycol/polycol_tracemeshtriangle.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
#include "Engine/Unicol/Polycol/cpolycollision_traceceilingtriangle.h"

/* POLYCOL_TRACEGEOMETRY.CPP */

/* Gathers the pieces a ray sweeps through: for each entry of the counted table in g_worldCollisionElementTable whose
 * rectangle, grown by the ray's radius, overlaps the ray's rectangle and is hit by it, each visible element
 * of the entry's resource whose grown box overlaps the ray's box and is hit is recorded with its hit
 * parameter (at most 128). The hits are sorted and, while nearer than the ray's current nearest hit, each
 * is handed to CPolyCollision_TraceElementMesh with a context holding the ray, its look-at matrix and segment spacing. */

s32 CPolyCollision_TraceBoxFaces(void *ray, void *unusedPlatform, void *corners, s32 *quad) {
    s32 result;

    result = 0;
    if (((struct PlatformMovementView *) ray)->movementY > 0.0f) {
        *quad = 2;
        Plane_BuildBoxFace1(quad, corners);
        result = CCollision_TestSegmentPolygon(ray, quad, 1);
    }
    if ((((struct PlatformMovementView *) ray)->movementX != 0.0f) || (((struct PlatformMovementView *) ray)->movementZ != 0.0f)) {
        *quad = 3;
        Plane_BuildBoxFace2(quad, corners);
        result |= CCollision_TestSegmentPolygon(ray, quad, 1);
        Plane_BuildBoxFace3(quad, corners);
        result |= CCollision_TestSegmentPolygon(ray, quad, 1);
        Plane_BuildBoxFace4(quad, corners);
        result |= CCollision_TestSegmentPolygon(ray, quad, 1);
        Plane_BuildBoxFace5(quad, corners);
        result |= CCollision_TestSegmentPolygon(ray, quad, 1);
    }
    if (((struct PlatformMovementView *) ray)->movementY < 0.0f) {
        *quad = 9;
        Plane_BuildBoxFace0(quad, corners);
        result |= CCollision_TestSegmentPolygon(ray, quad, 1);
    }
    return result;
}

s32 CPolyCollision_TraceCylinderFaces(void *ray, void *platform, void *corners, s32 *contactPolygon) {
    f32 radius;
    s32 hitFound;
    void *point;

    hitFound = 0;
    point = platform + 8;
    radius = ((struct PlatformHeightView *) ((struct LevelActor *) platform)->definition)->cylinderRadius + ((struct PlatformRadiusMovementView *) ray)->radius;
    if ((((struct PlatformRadiusMovementView *) ray)->movementX != 0.0f) || (((struct PlatformRadiusMovementView *) ray)->movementZ != 0.0f)) {
        *contactPolygon = 3;
        hitFound = CCollision_TestRayCylinder(ray, point, radius, ((struct PlatformActivityPhaseView *) corners)->top, ((struct PlatformActivityPhaseView *) corners)->bottom, 1, contactPolygon, 1);
    }
    if (((struct PlatformRadiusMovementView *) ray)->movementY > 0.0f) {
        *contactPolygon = 2;
        Plane_BuildBoxFace1(contactPolygon, corners);
        hitFound |= CCollision_TestSegmentDisk(ray, contactPolygon, point, radius, 1);
    }
    if (((struct PlatformRadiusMovementView *) ray)->movementY < 0.0f) {
        *contactPolygon = 9;
        Plane_BuildBoxFace0(contactPolygon, corners);
        hitFound |= CCollision_TestSegmentDisk(ray, contactPolygon, point, radius, 1);
    }
    return hitFound;
}

void CPolyCollision_TraceWorldElements(Ray180 *ray) {
    Box box;
    CQuatern rect;
    ContextB0 ctx;
    Hit8 hits[128];
    f32 t;
    CVector3 *start;
    CVector3 *end;
    Hit8 *hit;
    EntryC *table;
    ModelF0 *model;
    ElementE8 *element;
    s32 count;
    s32 hitCount;
    s32 segments;
    s32 remaining;
    s32 i;
    s32 j;

    start = &ray->start;
    end = &ray->end;
    ctx.ray = ray;
    ctx.start = start;
    ctx.end = end;
    ctx.reach = ray->scale * ray->nearest + ray->radius;
    if (ray->spacing != 0.0f) {
        segments = ((2) > ((s32) (ray->length / ray->spacing) + 1) ? (2) : ((s32) (ray->length / ray->spacing) + 1));
        ctx.segments = segments;
        ctx.step = (ray->length - 2.0f * ray->spacing) / (f32) (segments - 1);
    } else {
        ctx.segments = 1;
        ctx.step = 1.0f;
    }
    hit = hits;
    hitCount = 0;
    table = g_worldCollisionElementTable.entries;
    count = g_worldCollisionElementTable.count;
    for (i = 0; i < count; i++) {
        rect.x = table[i].rect->x - ray->radius;
        rect.y = table[i].rect->y - ray->radius;
        rect.z = table[i].rect->z + ray->radius;
        rect.w = table[i].rect->w + ray->radius;
        if (ray->rect.x < rect.z && rect.x < ray->rect.z && ray->rect.y < rect.w &&
            rect.y < ray->rect.w && CCollision_IntersectSegmentRectangle(ray, &rect, &t) != 0) {
            model = SetN64_GetPackSection(*table[i].resource, 0);
            remaining = model->count;
            element = model->elements;
            while (--remaining != -1) {
                if (hitCount >= 128) {
                    break;
                }
                if (!(element->flags & 0x10)) {
                    box.min.x = element->box.min.x - ray->radius;
                    box.min.y = element->box.min.y - ray->radius;
                    box.min.z = element->box.min.z - ray->radius;
                    box.max.x = element->box.max.x + ray->radius;
                    box.max.y = element->box.max.y + ray->radius;
                    box.max.z = element->box.max.z + ray->radius;
                    if (box.min.x < ray->box.max.x && ray->box.min.x < box.max.x && box.min.z < ray->box.max.z &&
                        ray->box.min.z < box.max.z && box.min.y < ray->box.max.y && ray->box.min.y < box.max.y &&
                        CCollision_IntersectSegmentBox(ray, &box, &t) != 0) {
                        hitCount++;
                        hit->element = element;
                        hit->t = t;
                        hit++;
                    }
                }
                element++;
            }
        }
    }
    if (hitCount != 0) {
        Graphu64_ComputeViewMatrix(&ctx.matrix, start, end, &g_collisionTraceViewUpVector);
        PpDecom_QuickSortRecords((char *) hits, hitCount, sizeof(Hit8), CPolyCollision_CompareSortedHits, CPolyCollision_SwapSortedHits);
        hit = hits;
        for (j = 0; j < hitCount; j++, hit++) {
            if (!(hit->t < ray->nearest)) {
                break;
            }
            element = hit->element;
            ctx.element = element;
            ctx.kind = Barrel_GetImpactSlot(element);
            if (ctx.kind == 9) {
                ctx.isKind9 = 1;
            } else {
                ctx.isKind9 = 0;
            }
            CPolyCollision_TraceElementMesh(&ctx);
        }
    }
}

/* POLYCOL_TRACEMESHTRIANGLE.CPP */

/* Walks one mesh display list of the element being traced: VTX commands transform their model vertices
 * into the trace space and record per-vertex clip bits, TRI1/TRI2 commands trace every triangle whose
 * vertices are not all outside one clip plane, ENDDL stops. Section 0 of the resource holds the mesh
 * flags, section 1 the commands. */
void PolyCol_TraceMeshDisplayList(ContextB0 *context, void *resource) {
    CollisionVertex vertices[32];
    CollisionVertex *triangle[3];
    CVector3 point;
    CollisionVertex *saved;
    CollisionVertex *vertex;
    u32 *flags;
    u32 *commands = resource;
    u8 opcode;
    s32 reverse;
    s32 count;
    s16 *source;
    Ray180 *ray;
    flags = SetN64_GetPackSection(commands, 0);
    ray = context->ray;
    context->flags = *flags;
    reverse = *flags & 4;
    switch (context->kind) {
    case 1:
    case 7:
    case 8:
        reverse = 1;
        break;
    }
    commands = SetN64_GetPackSection(commands, 1);
    do {
        opcode = ((u8 *)commands)[COMMAND_HIGH];
        switch (opcode) {
        case MESH_CMD_TRI2:
            TRACE_TRIANGLE(context, vertices, triangle, commands + 1, reverse, saved);
/* fall through */
        case MESH_CMD_TRI1:
            TRACE_TRIANGLE(context, vertices, triangle, commands, reverse, saved);
            break;
        case MESH_CMD_VTX:
/* Segmented address of the first 16-byte model vertex, count, and the last slot it loads. */
            source = (s16 *)((commands[1] & 0xFFFFFF) + (u32)context->vertices);
            count = (commands[0] >> 12) & 0xFF;
            vertex = &vertices[((commands[0] & 0xFE) >> 1) - count];
            do {
                vertex->position = source;
                point.x = source[0];
                point.y = source[1];
                point.z = source[2];
                vertex->x = context->transform.m[0][0] * point.x + context->transform.m[1][0] * point.y +
                    context->transform.m[2][0] * point.z + context->transform.m[3][0];
                vertex->clipFlags = Clip_AxisOutside(&vertex->x, &ray->radius, 0);
                vertex->y = context->transform.m[0][1] * point.x + context->transform.m[1][1] * point.y +
                    context->transform.m[2][1] * point.z + context->transform.m[3][1];
                vertex->clipFlags |= Clip_AxisOutside(&vertex->y, &ray->radius, 2);
                vertex->z = context->transform.m[0][2] * point.x + context->transform.m[1][2] * point.y +
                    context->transform.m[2][2] * point.z + context->transform.m[3][2];
                vertex->clipFlags |= Clip_BeyondPositive(&vertex->z, &ray->radius) << 4;
                vertex->clipFlags |= Clip_BeyondNegative(&vertex->z, &context->reach) << 5;
                source += 8;
                vertex++;
                count--;
            } while (count != 0);
            break;
        }
        commands += 2;
    } while (opcode != MESH_CMD_ENDDL);
}

void PolyCol_TraceMeshTriangle(ContextB0 *mesh,CollisionVertex **points) {
    CVector3 vertex;
    CVector3 edgeA;
    CVector3 edgeB;
    Polygon polygon;
    CVector3 offset;
    CCollisionInfo2_t *surface;
    CapsuleSweep *ray;
    s32 i;
    s32 byteOffset;
    s32 sideType;
    CollisionVertex **cursor;
    Polygon *base;
    f32 shift;
    f32 px=points[1]->x;
    f32 p0x=points[0]->x;
    f32 py=points[1]->y;
    if (0.0f <= (px-p0x)*(points[2]->y-py) - (py-points[0]->y)*(points[2]->x-px)) return;
    i=0;
    base=&polygon;
    byteOffset=offsetof(Polygon, vertices);
    cursor=points;
    ray=mesh->ray;
    polygon.vertexCount=3;
    do {
        s16 *position=(*cursor)->position;
        vertex.x=(f32)position[0];
        vertex.y=(f32)position[1];
        vertex.z=(f32)position[2];
        Graphu64_TransformPoint(&mesh->element->transform,&vertex,(char *)base+byteOffset);
        byteOffset+=(s32)sizeof(polygon.vertices[0]);
        cursor++;
        i++;
    } while(i<3);
    Graphu64_SubtractVectors(&edgeA,&polygon.vertices[1],&polygon.vertices[0]);
    Graphu64_SubtractVectors(&edgeB,&polygon.vertices[2],&polygon.vertices[1]);
    Graphu64_CrossVectors(&polygon.normal,&edgeB,&edgeA);
    Graphu64_NormalizeVec3(&polygon.normal);
    surface=ray->surface;
    polygon.input=mesh->element;
    polygon.index=-1;
    polygon.category=mesh->kind;
    polygon.flags=mesh->flags;
    switch(mesh->kind) {
    case 1: case 7: case 8: {
            if(!(surface->dwFlags&8)) return;
            if(surface->dwFlags&0x80000) return;
            polygon.type=6;
            polygon.response=surface->WaterFriction;
            polygon.kind=7;
            CCollision_TestSegmentPolygon(ray,&polygon,1);
            polygon.type=5;
            polygon.kind=(surface->dwFlags&0x100000)?7:surface->GroundBehavior;
            if(polygon.normal.y!=0.0f) shift=ray->height;
            else shift=0.0f;
            i=0;
            do {
                polygon.vertices[i].y += shift;
                i++;
            } while(i<3);
            break;
        }
    default: {
            if(polygon.normal.y<0.0f) {
                if(-polygon.normal.y<g_collisionDownwardNormalThreshold) goto flatFace;
            } else if(polygon.normal.y<g_collisionUpwardNormalThreshold) {
                flatFace:
                polygon.type=((ray->flags&0x1000) || !(mesh->flags&0x10000000)) ? 3 : 4;
                polygon.response=0.0f;
                polygon.kind=surface->WallBehavior;
                goto dispatch;
            }
            sideType=2;
            if(!(polygon.normal.y<0.0f)) sideType=1;
            polygon.type=sideType;
            polygon.response=surface->GroundFriction;
            polygon.kind=surface->GroundBehavior;
            break;
        }
    }
    dispatch:
    if((u32)(polygon.type-5)<2) {
        CCollision_TestOffsetPolygon(ray,0,ray->radius,&polygon,1);
    } else if(ray->radius==0.0f && ray->secondaryRadius==0.0f) {
        CCollision_TestSegmentPolygon(ray,&polygon,1);
    } else {
        offset.x=0.0f;
        offset.y=ray->radius;
        offset.z=0.0f;
        i=mesh->segments;
        while(--i!=-1) {
            if(i==mesh->segments-1) {
                if(polygon.type==2) goto skipSweep;
                goto sweep;
            } else if(i==0) {
                if(polygon.type==1) goto skipSweep;
                goto sweep;
            } else if((u32)(polygon.type-1)>=2) {
                sweep:
                CCollision_TestOffsetPolygon(ray,&offset,ray->radius,&polygon,1);
            }
            skipSweep:
            offset.y+=mesh->step;
        }
    }
}

/* CPOLYCOLLISION_TRACECEILINGTRIANGLE.CPP */

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
float k_CpolycollisionTraceceilingtriangleConstants[3] = {
    -0.7071f, 204.79999f, 1.0f,
};
#endif

/* POLYCOL.CPP */

const float g_collisionDownwardNormalThreshold = 0.7f;
const float g_collisionUpwardNormalThreshold = 0.7f;
