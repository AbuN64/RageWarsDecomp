#include "include_asm.h"
#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ACTORREC.H"
#include "COMMON/NAVIGATION_GRAPH.H"
#include "TYPES.H"

extern void *Portal_FindSearchNode(char *, s32);

extern void *Portal_GetGraphPoint(void *, s32);

/** Find the first of an object's four nodes that starts a type-6 link, record it and return 0; return 1 when none does. */








extern Link *Portal_GetStridedTableEntry(CNavData *, int);
extern CNavData g_navigationGraph;

s32 Nav_ComputeScaledPointCentroid(ObjNavComputeScaledPointCentroid *obj) {
    CVector3 sum;
    s32 i;
    f32 scale;
    Info *info;
    CVector3 *base;
    void *global;

    sum.x = sum.y = sum.z = 0.0f;
    global = &g_navigationGraph;
    for (i = 0; i < obj->count; i++) {
        sum.x += obj->points[i].x;
        sum.y += obj->points[i].y;
        sum.z += obj->points[i].z;
    }
    if (obj->count == 0)
        return 1;

    scale = g_pointCentroidUnitScale / (f32)obj->count;
    sum.x *= scale;
    sum.y *= scale;
    sum.z *= scale;
    info = Portal_FindSearchNode(global, obj->infoIndex);
    sum.x *= info->scale;
    sum.y *= info->scale;
    sum.z *= info->scale;
    base = Portal_GetGraphPoint(global, obj->infoIndex);
    obj->result.x = base->x + sum.x;
    obj->result.y = base->y + sum.y;
    obj->result.z = base->z + sum.z;
    return 1;
}

int Nav_FindSpecialLinkedCandidate(ObjNavFindSpecialLinkedCandidate *obj) {
    int j;
    int i;
    Link *link;
    CNavData *graph = &g_navigationGraph;

    obj->node = -1;
    obj->pending = 0;
    for (j = 0; j < 4; j++) {
        for (i = 0; i < graph->m_nNavLinks; i++) {
            link = Portal_GetStridedTableEntry(graph, i);
            if (link->from == obj->nodes[j] && link->type == 6) {
                obj->hits++;
                obj->node = obj->nodes[j];
                return 0;
            }
        }
    }
    return 1;
}

