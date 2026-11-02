#include "include_asm.h"
#include "TYPES.H"
#include "ANIM/RAY180.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "ENGINE/UNICOL/POLYCOL.H"
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
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"

/* 802412C0_6.CPP */
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

/* 80241940_5.CPP */
extern void Graphu64_CrossVectors(CVector3*,CVector3*,CVector3*);

void PolyCol_TraceMeshTriangle(ContextB0 *mesh,CollisionVertex **points) {
    extern s32 CCollision_TestSegmentPolygon(CapsuleSweep*,PolygonCCollisionTestSegmentPolygon*,s32);
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
    /* Vertex storage starts at 0x18 in the shared collision query. */
    byteOffset=24;
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
