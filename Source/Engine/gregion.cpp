#include "Common/packed.h"
#include "Common/obj.h"
#include "Common/runtime_declarations.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "types.h"
#include "Fx/normalize_vector.h"
#include "Common/model_tree_region_operations.h"
#include "Common/aiprofile.h"
#include "Common/world.h"
#include "Common/objb.h"
#include "include_asm.h"
#include "Engine/gregion.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Graphu64/graphu64_buildlookatmatrix.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Common/approachlocation.h"
#include "Common/ballisticparams.h"
#include "Lists/externs.h"
#include "Common/math_helpers.h"
#include "Common/triple.h"

/* GREGION.CPP */


/* Returns the rotation quaternion that tilts the up axis onto a polygon's unit normal (recomputed from its edges into g_regionCachedEdgeCross and normalised into g_regionCachedUnitNormal whenever the polygon differs from the last one, straight up for no polygon), recording the half-angle sine in g_turretAimSine and giving the identity when the normal is vertical. */
static inline void edge(CVector3 *out, CVector3 *a, CVector3 *b) {
    Graphu64_SubtractVectors(out, a, b);
}

static inline void normalize_copy(CVector3 *out, CVector3 *in) {
    *out = *in;
    Graphu64_NormalizeVec3(out);
}

CQuatern *Region_GetPolygonUpQuat(CQuatern *out, Triangle *polygon) {
    CVector3 normal;
    CVector3 up;
    CVector3 axis;
    CQuatern result;
    CVector3 edge0;
    CVector3 edge1;
    f32 one;
    f32 len;
    f32 angle;
    f32 scale;

    if (polygon == 0) {
        *(s32 *)&g_regionCachedUnitNormal = 0;
        g_regionNormalDefaultUpZ = 0;
        g_regionNormalDefaultUpY = 1.0f;
    } else if (polygon != g_regionCachedNormalPolygon) {
        if (polygon == 0) {
            *(s32 *)&g_regionCachedEdgeCross = 0;
            g_regionEdgeDefaultUpZ = 0;
            g_regionEdgeDefaultUpY = 1.0f;
        } else if (polygon != g_regionCachedEdgePolygon) {
            edge(&edge0, polygon->vertices[1], polygon->vertices[0]);
            edge(&edge1, polygon->vertices[2], polygon->vertices[1]);
            Graphu64_CrossVectors(&g_regionCachedEdgeCross, &edge0, &edge1);
        }
        g_regionCachedEdgePolygon = polygon;
        normalize_copy(&g_regionCachedUnitNormal, &g_regionCachedEdgeCross);
    }
    one = 1.0f;
    g_regionCachedNormalPolygon = polygon;
    normal = g_regionCachedUnitNormal;
    up.x = 0.0f;
    up.y = one;
    up.z = 0.0f;
    Graphu64_CrossVectors(&axis, &up, &normal);
    len = Gu_Sqrtf(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
    if (len == 0.0f) {
        result.z = 0.0f;
        result.y = 0.0f;
        result.x = 0.0f;
        result.w = one;
    } else {
        Graphu64_ScaleVector(&axis, &axis, one / len);
        angle = Graphu64_ArcCos(up.x * normal.x + up.y * normal.y + up.z * normal.z);
        angle *= 0.5f;
        scale = Gu_Sinf(angle);
        result.x = axis.x * scale;
        result.y = axis.y * scale;
        result.z = axis.z * scale;
        g_turretAimSine = scale;
        result.w = Math_Cosf(angle);
    }
    *out = result;
    return out;
}

CQuatern *Region_GetCachedUpQuat(CQuatern *out, Triangle *polygon) {
    CVector3 a;
    CVector3 up;
    CVector3 axis;
    CQuatern result;
    float len;
    float angle;
    float scale;
    float one;

    Graphu64_GetCachedSurfaceNormal(&a, polygon);
    one = g_regionUpQuaternionConstants[1];
    up.x = 0;
    up.y = one;
    up.z = 0;
    Graphu64_CrossVectors(&axis, &up, &a);
    len = Gu_Sqrtf(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
    if (len == 0) {
        result.z = 0;
        result.y = 0;
        result.x = 0;
        result.w = one;
    } else {
        Graphu64_ScaleVector(&axis, &axis, one / len);
        angle = Graphu64_ArcCos(up.x * a.x + up.y * a.y + up.z * a.z);
        angle *= g_regionUpQuaternionHalfAngleScale;
        scale = Gu_Sinf(angle);
        result.x = axis.x * scale;
        result.y = axis.y * scale;
        result.z = axis.z * scale;
        g_turretAimSine = scale;
        result.w = Math_Cosf(angle);
    }
    *out = result;
    return out;
}

/* Returns whether a polygon counts as a wall: without flag 0x2000 it returns its flag 8, and otherwise it takes the polygon's unit normal (recomputed from its edges into g_regionCachedEdgeCross and normalised into g_regionCachedUnitNormal whenever the polygon differs from the last one) and returns whether the normal's upward component is at most g_regionWallSlopeThreshold. */

s32 Region_TestPolygonSlopeFlag(Triangle *polygon) {
    CVector3 up;
    CVector3 normal;
    CVector3 edge0;
    CVector3 edge1;

    if (polygon == 0) {
        return 0;
    }
    if (!(polygon->flags & 0x2000)) {
        return polygon->flags & 8;
    }
    up.x = 0.0f;
    up.y = *(&g_regionUpQuaternionHalfAngleScale + 1);
    up.z = 0.0f;
    if (polygon != g_regionCachedNormalPolygon) {
        if (polygon == 0) {
            *(s32 *)&g_regionCachedEdgeCross = 0;
            g_regionEdgeDefaultUpY = *(&g_regionUpQuaternionHalfAngleScale + 1);
            g_regionEdgeDefaultUpZ = 0;
        } else if (polygon != g_regionCachedEdgePolygon) {
            edge(&edge0, polygon->vertices[1], polygon->vertices[0]);
            edge(&edge1, polygon->vertices[2], polygon->vertices[1]);
            Graphu64_CrossVectors(&g_regionCachedEdgeCross, &edge0, &edge1);
        }
        g_regionCachedEdgePolygon = polygon;
        normalize_copy(&g_regionCachedUnitNormal, &g_regionCachedEdgeCross);
    }
    normal = g_regionCachedUnitNormal;
    g_regionCachedNormalPolygon = polygon;
    if (normal.x * up.x + normal.y * up.y + normal.z * up.z <= g_regionWallSlopeThreshold) {
        return 1;
    }
    return 0;
}

void Region_ComputePointBounds(f32 *pointBounds, s32 pointCount, CVector3 *pointCursor)
{
    s32 i;

    i = 0;
    if (pointCount != 0) {
        pointBounds[0] = pointCursor->x;
        pointBounds[1] = pointCursor->y;
        pointBounds[2] = pointCursor->z;
        pointBounds[3] = pointCursor->x;
        pointBounds[4] = pointCursor->y;
        pointCount -= 1;
        pointBounds[5] = pointCursor->z;
        pointCursor += 1;

        if (pointCount > 0) {
bounds_loop:
                {
                    f32 value = pointCursor->x;
                    f32 bound = pointBounds[0];
                    if (!(value <= bound)) {
                        value = bound;
                    }
                    pointBounds[0] = value;
                }

                {
                    f32 value = pointCursor->y;
                    f32 bound = pointBounds[1];
                    if (!(value <= bound)) {
                        value = bound;
                    }
                    pointBounds[1] = value;
                }

                {
                    f32 value = pointCursor->z;
                    f32 bound = pointBounds[2];
                    if (!(value <= bound)) {
                        value = bound;
                    }
                    pointBounds[2] = value;
                }

                {
                    f32 value = pointCursor->x;
                    f32 bound = pointBounds[3];
                    if (!(bound <= value)) {
                        value = bound;
                    }
                    pointBounds[3] = value;
                }

                {
                    f32 value = pointCursor->y;
                    f32 bound = pointBounds[4];
                    if (!(bound <= value)) {
                        value = bound;
                    }
                    pointBounds[4] = value;
                }

                {
                    f32 value = pointCursor->z;
                    f32 bound = pointBounds[5];
                    if (!(bound <= value)) {
                        value = bound;
                    }
                    pointBounds[5] = value;
                }

                i += 1;
                pointCursor += 1;
            if (i < pointCount) goto bounds_loop;
        }
    }
}

/* Returns the normalised cross product of a path node's two edge vectors, cached in g_regionCachedUnitNormal for the last node seen, with a default up vector for a null node.
 */

static inline CVector3 *cross_edges(CVector3 *out, Node75 *node) {
    CVector3 a;
    CVector3 b;

    if (node == 0) {
        g_regionCachedEdgeCross.x = 0;
        g_regionCachedEdgeCross.z = 0;
        g_regionCachedEdgeCross.y = g_regionCachedEdgeDefaultUp;
    } else if ((Triangle *)node != g_regionCachedEdgePolygon) {
        Graphu64_SubtractVectors(&a, node->cur, node->prev);
        Graphu64_SubtractVectors(&b, node->next, node->cur);
        Graphu64_CrossVectors(&g_regionCachedEdgeCross, &a, &b);
    }
    g_regionCachedEdgePolygon = (Triangle *)node;
    *out = g_regionCachedEdgeCross;
    return out;
}

void Region_ScaleWordsToFloats(void *wordStorage) {
    s32 *ip = (s32 *)wordStorage;
    f32 *fp = (f32 *)wordStorage;
    f32 scale = g_regionWordToFloatScaleDe;
    fp[0] = (f32)ip[0] * scale;
    fp[1] = (f32)ip[1] * scale;
    fp[2] = (f32)ip[2] * scale;
    fp[3] = (f32)ip[3] * scale;
}

/* Decodes a packed header into its runtime form: copies the two leading shorts and the following flags word,
   and for each of three channels resolves a 16-byte-scaled offset against base and a 32-byte-scaled
   offset against extra, leaving the latter null when it is 0xFFFF. */

void Region_DecodePackedRegion(CGameRegion *dst, Packed *src, char *base, int vertexCount, char *extra) {
    int i;

    dst->kind = src->kind;
    dst->flags = src->flags;
    dst->mask = src->mask;
    for (i = 0; i < 3; i++) {
        dst->first[i] = base + src->first[i] * 16;
        if (src->second[i] == 0xFFFF) {
            dst->second[i] = 0;
        } else {
            dst->second[i] = extra + src->second[i] * 32;
        }
    }
}

s32 Region_IsPointInTriangleXZ(Node75 *triangle, f32 x, f32 z) {
    s32 i;
    CVector3 *vertexA;
    CVector3 *vertexB;

    if (triangle == 0) {
        return 1;
    }

    for (i = 0; i < 3; i++) {
        vertexA = ((Triangle *)triangle)->vertices[i];
        vertexB = ((Triangle *)triangle)->vertices[(i + 1) % 3];
        if (((vertexB->z -
              vertexA->z) *
             (x - vertexA->x)) +
                ((vertexA->x - vertexB->x) *
                 (z - vertexA->z)) <
            0.0f) {
            return 0;
        }
    }

    return 1;
}

CVector3 *Region_GetNodeEdgeCross(CVector3 *out, Node75 *node) {
    CVector3 a;
    CVector3 b;
    CVector3 *bPtr;

    if (node == 0) {
        g_regionCachedEdgeCross.x = 0;
        g_regionCachedEdgeCross.z = 0;
        g_regionCachedEdgeCross.y = g_regionEdgeCrossDefaultUp[0];
    } else if ((Triangle *)node != g_regionCachedEdgePolygon) {
        Graphu64_SubtractVectors(&a, node->cur, node->prev);
        bPtr = &b;
        Graphu64_SubtractVectors(bPtr, node->next, node->cur);
        Graphu64_CrossVectors(&g_regionCachedEdgeCross, &a, bPtr);
    }
    *out = g_regionCachedEdgeCross;
    g_regionCachedEdgePolygon = (Triangle *)node;
    return out;
}

CVector3 *Region_GetNodeNormal(CVector3 *out, Node75 *node) {
    if (node == 0) {
        g_regionCachedUnitNormal.x = 0;
        g_regionCachedUnitNormal.z = 0;
        g_regionCachedUnitNormal.y = g_regionNormalDefaultUp[0];
    } else if ((Triangle *)node != g_regionCachedNormalPolygon) {
        cross_edges(&g_regionCachedUnitNormal, node);
        Graphu64_NormalizeVec3(&g_regionCachedUnitNormal);
    }
    *out = g_regionCachedUnitNormal;
    g_regionCachedNormalPolygon = (Triangle *)node;
    return out;
}

/* Returns the height of a path node's triangle plane at (x, z) from the cached edge cross product in g_regionCachedEdgeCross, or the mean vertex height when the plane is vertical.
 */

static inline void cross_node_edges(Node75 *node) {
    CVector3 a;
    CVector3 b;

    Graphu64_SubtractVectors(&a, node->cur, node->prev);
    Graphu64_SubtractVectors(&b, node->next, node->cur);
    Graphu64_CrossVectors(&g_regionCachedEdgeCross, &a, &b);
}


f32 Region_GetPolygonHeight(Node75 *node, f32 x, f32 z) {
    CVector3 normal;
    CVector3 point;

    if (node == 0) {
        return g_regionMissingPolygonHeight[0];
    }
    if ((Triangle *)node != g_regionCachedEdgePolygon) {
        cross_node_edges(node);
    }
    normal = g_regionCachedEdgeCross;
    g_regionCachedEdgePolygon = (Triangle *)node;
    if (normal.y == 0.0f) {
        return (node->prev->y + node->cur->y + node->next->y) * g_regionVerticalPolygonMeanScale;
    }
    point = *node->prev;
    return (((point.z - z) * normal.z) +
            ((point.x - x) * normal.x) + (point.y * normal.y)) /
           normal.y;
}

CVector3 *Region_GetCachedCeilingNormal(CVector3 *out, Node75 *node) {
    CVector3 a;
    CVector3 b;
    CollisionBuildVertex *p;
    CollisionBuildVertex *q;

    if (node == 0) {
        g_cachedCeilingCrossProduct.x = 0;
        g_cachedCeilingCrossProduct.z = 0;
        g_cachedCeilingCrossProduct.y = g_regionCeilingDefaultUp[0];
    } else if ((int)node != g_cachedCeilingCrossProductNode) {
        p = node->cur;
        q = node->prev;
        a.x = p->x - q->x;
        p = node->cur;
        q = node->prev;
        a.y = p->ceiling - q->ceiling;
        p = node->cur;
        q = node->prev;
        a.z = p->z - q->z;
        p = node->next;
        q = node->cur;
        b.x = p->x - q->x;
        p = node->next;
        q = node->cur;
        b.y = p->ceiling - q->ceiling;
        p = node->next;
        q = node->cur;
        b.z = p->z - q->z;
        Graphu64_CrossVectors(&g_cachedCeilingCrossProduct, &b, &a);
    }
    *out = g_cachedCeilingCrossProduct;
    g_cachedCeilingCrossProductNode = (int)node;
    return out;
}

s32 Region_GetModelBlendByte58(s32 modelId) {
    ModelBlend *blend = Scene_GetModelRecordByIndexPointer(&g_world, modelId);
    if (blend == 0) {
        return 0;
    }
    return blend->byte58;
}

s32 Region_GetModelBlendByte59(s32 modelId) {
    ModelBlend *blend = Scene_GetModelRecordByIndexPointer(&g_world, modelId);
    if (blend == 0) {
        return 0;
    }
    return blend->byte59;
}

f32 Region_GetTriangleEdgeAngle(Triangle *triangle, s32 edgeIndex) {
    CVector3 *edgeEnd;
    CVector3 *edgeStart;
    f32 dx, dz;
    f32 mag;
    f32 result;

    edgeStart = triangle->vertices[edgeIndex];
    edgeEnd = triangle->vertices[(edgeIndex + 1) % 3];
    dx = edgeEnd->x - edgeStart->x;
    dz = edgeEnd->z - edgeStart->z;
    mag = Gu_Sqrtf((dx * dx) + (dz * dz));
    if (mag == 0.0f) {
        return 0.0f;
    }
    result = Graphu64_ArcCos(dx / mag);
    if (!(dz < 0.0f)) {
        result = -result;
    }
    return result;
}

void Region_SetNodeGroupFlag(struct ModelTreeNode *modelTreeNode) {
    if ((modelTreeNode != 0) && (modelTreeNode->flags & 2)) {
        Region_MarkMatchingNodes(modelTreeNode, modelTreeNode->modelId);
    }
}

void Region_ClearNodeGroupFlag(struct ModelTreeNode *modelTreeNode) {
    if ((modelTreeNode != 0) && (modelTreeNode->flags & 2)) {
        Region_UnmarkMatchingNodes(modelTreeNode, modelTreeNode->modelId);
    }
}

f32 Region_SetNodeGroupHeight(u16 *modelTreeNode, f32 height) {
    f32 result = height;
    if (modelTreeNode != 0) {
        result = Region_SetMatchingVertexHeights(modelTreeNode, height, *modelTreeNode);
    }
    return result;
}

void Region_MarkMatchingNodes(struct ModelTreeNode *modelTreeNode, u16 matchingModelId) {
    u16 modelId;
    u16 flags;
    void *branch;

    modelId = modelTreeNode->modelId;
    if (modelId == matchingModelId) {
        flags = modelTreeNode->flags;
        if (!(flags & 4)) {
            branch = modelTreeNode->branches[0];
            modelTreeNode->flags = flags | 4;
            if (branch != 0) {
                Region_MarkMatchingNodes(branch, modelId);
            }
            branch = modelTreeNode->branches[1];
            if (branch != 0) {
                Region_MarkMatchingNodes(branch, modelId);
            }
            branch = modelTreeNode->branches[2];
            if (branch != 0) {
                Region_MarkMatchingNodes(branch, modelId);
            }
        }
    }
}

void Region_UnmarkMatchingNodes(struct ModelTreeNode *modelTreeNode, u16 matchingModelId) {
    u16 modelId;
    u16 flags;
    void *branch;

    modelId = modelTreeNode->modelId;
    if (modelId == matchingModelId) {
        flags = modelTreeNode->flags;
        if (flags & 4) {
            branch = modelTreeNode->branches[0];
            modelTreeNode->flags = flags & 0xFFFB;
            if (branch != 0) {
                Region_UnmarkMatchingNodes(branch, modelId);
            }
            branch = modelTreeNode->branches[1];
            if (branch != 0) {
                Region_UnmarkMatchingNodes(branch, modelId);
            }
            branch = modelTreeNode->branches[2];
            if (branch != 0) {
                Region_UnmarkMatchingNodes(branch, modelId);
            }
        }
    }
}

f32 Region_SetMatchingVertexHeights(u16 *modelTreeNode, f32 height, u16 modelId) {
    u16 *node = modelTreeNode;
    u16 id = modelId;

    if (*node == id) {
        if (((struct PaddedFloatView *) ((RegionTriangleVertexView *) node)->firstVertex)->value != height ||
            ((struct PaddedFloatView *) ((RegionTriangleVertexView *) node)->secondVertex)->value != height ||
            ((struct PaddedFloatView *) ((RegionTriangleVertexView *) node)->thirdVertex)->value != height) {
            ((struct PaddedFloatView *) ((RegionTriangleVertexView *) node)->firstVertex)->value = height;
            ((struct PaddedFloatView *) ((RegionTriangleVertexView *) node)->secondVertex)->value = height;
            ((struct PaddedFloatView *) ((RegionTriangleVertexView *) node)->thirdVertex)->value = height;

            if (((RegionTriangleVertexView *)(node))->firstBranch.v0 != 0) {
                Region_SetMatchingVertexHeights(((RegionTriangleVertexView *)(node))->firstBranch.v1, height, id);
            }
            if (((RegionTriangleVertexView *)(node))->secondBranch.v0 != 0) {
                Region_SetMatchingVertexHeights(((RegionTriangleVertexView *)(node))->secondBranch.v1, height, id);
            }
            if (((RegionTriangleVertexView *)(node))->thirdBranch.v0 != 0) {
                Region_SetMatchingVertexHeights(((RegionTriangleVertexView *)(node))->thirdBranch.v1, height, id);
            }
        }
    }
}

void Region_ExpandPointBounds(f32 *bounds, s32 pointCount, CVector3 *points)
{
    s32 i;
    i = 0;
    if (pointCount > 0) {
        do {
            {
                f32 value = points[i].x;
                f32 bound = bounds[0];
                if (!(value <= bound)) {
                    value = bound;
                }
                bounds[0] = value;
            }
            {
                f32 value = points[i].y;
                f32 bound = bounds[1];
                if (!(value <= bound)) {
                    value = bound;
                }
                bounds[1] = value;
            }
            {
                f32 value = points[i].z;
                f32 bound = bounds[2];
                if (!(value <= bound)) {
                    value = bound;
                }
                bounds[2] = value;
            }
            {
                f32 value = points[i].x;
                f32 bound = bounds[3];
                if (!(bound <= value)) {
                    value = bound;
                }
                bounds[3] = value;
            }
            {
                f32 value = points[i].y;
                f32 bound = bounds[4];
                if (!(bound <= value)) {
                    value = bound;
                }
                bounds[4] = value;
            }
            {
                f32 value = points[i].z;
                f32 bound = bounds[5];
                if (!(bound <= value)) {
                    value = bound;
                }
                bounds[5] = value;
            }
            i += 1;
        } while (i < pointCount);
    }
}

void Region_ComputeHorizontalBounds(void *boundsStorage, s32 pointCount, void *pointStorage) {
    f32 *bounds = boundsStorage;
    CVector3 *points = pointStorage;
    f32 pointX;
    f32 pointZ;

    if (pointCount != 0) {
        pointX = points->x;
        bounds[2] = pointX;
        bounds[0] = pointX;
        pointZ = points->z;
        bounds[3] = pointZ;
        bounds[1] = pointZ;
        Gregion_ExpandHorizontalBounds(boundsStorage, pointCount - 1, points + 1);
    }
}

#if !(defined(VERSION_US_REV1))
const float g_regionUnitHalfPair[2] = {
    1.0f, 0.5f,
};
#endif

#if defined(VERSION_US_REV1)
const float g_regionUnitHalfPair[2] = {
    1.0f, 0.5f,
};
#endif

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)

#endif



extern const float g_regionEdgeCrossDefaultUp[1];

extern const float g_regionNormalDefaultUp[2];

extern const float g_regionMissingPolygonHeight[2];

extern const float g_regionCeilingDefaultUp[1];

#if defined(VERSION_EU_X)
float g_regionEpsilonPair[2] = {
    -1.0e-06f, 1.0e-06f,
};
#endif

/* GREGION_EXPANDHORIZONTALBOUNDS.CPP */

/** Expand the four-float X/Z bounds in bounds over pointCount packed vectors. */
void Gregion_ExpandHorizontalBounds(f32 *bounds, s32 pointCount, CVector3 *points)
{
    f32 value;
    f32 bound;
    s32 i;
    i = 0;
    if (pointCount > 0) {
        do {
            value = points[i].x;
            bound = bounds[0];
            if (!(value <= bound)) {
                value = bound;
            }
            bounds[0] = value;
            value = points[i].z;
            bound = bounds[1];
            if (!(value <= bound)) {
                value = bound;
            }
            bounds[1] = value;
            value = points[i].x;
            bound = bounds[2];
            if (!(bound <= value)) {
                value = bound;
            }
            bounds[2] = value;
            value = points[i].z;
            bound = bounds[3];
            if (!(bound <= value)) {
                value = bound;
            }
            bounds[3] = value;
            i += 1;
        } while (i < pointCount);
    }
}
/** Empty entry point that sits directly after Gregion_ExpandHorizontalBounds. */
void Gregion_NoOperation(void)
{
}

#if defined(VERSION_US)
/* Bytes the original holds up to the next 16-byte object boundary; no instruction reads them. */
unsigned char g_horizontalBoundsPaddingBytes[4] = { 0x00, 0x06, 0x00, 0x00 };
#endif

/* GREGION_SHIFTCOLORHUE.CPP */

extern const float g_regionHueWeightScales[3];

void Gregion_ShiftColorHue(s8 hue, u8 redArg, u8 greenArg, u8 blueArg,
    u8 *redOut, u8 *green_out, u8 *blue_out) {
    s32 phase;
    s32 distance0, distance1, distance2;
    s32 phase2;
    s32 w0, w1, w2;
    s32 red, green, blue;
    s32 p0, p1, p2, p3, p4, p5, p6, p7, p8;
    s32 mixedRed, mixed_green, mixed_blue, largest;
    f32 originalMax, mixed_max;

    phase = (s8)hue;
    if (phase != 0) {
        if (phase < 0) {
            distance0 = phase + 85;
            if (distance0 >= 0) w0 = (s32)((f32)(distance0 * 100) * g_regionHueWeightScales[0]);
            else w0 = 0;
        } else {
            distance0 = 85 - phase;
            if (distance0 >= 0) w0 = (s32)((f32)(distance0 * 100) * g_regionHueWeightScales[0]);
            else w0 = 0;
        }
        distance1 = (s8)hue;
        if (distance1 < -85) {
            distance1 += 170;
            w1 = (s32)((f32)(distance1 * 100) * g_regionHueWeightScales[1]);
        } else {
            distance1 = -distance1;
            if (distance1 >= 0) w1 = (s32)((f32)(distance1 * 100) * g_regionHueWeightScales[1]);
            else w1 = 0;
        }
        phase2 = (s8)hue;
        if (phase2 > 85) {
            distance2 = 170 - phase2;
            w2 = (s32)((f32)(distance2 * 100) * g_regionHueWeightScales[2]);
        } else {
            if (phase2 >= 0) w2 = (s32)((f32)(phase2 * 100) * g_regionHueWeightScales[2]);
            else w2 = 0;
        }

        blue = (u8)blueArg;
        red = (u8)redArg;
        green = (u8)greenArg;
        p0 = w1 * blue;
        p1 = w0 * red;
        p2 = w2 * green;
        p3 = w1 * red;
        p4 = w0 * green;
        p5 = w2 * blue;
        p6 = w1 * green;
        p7 = w0 * blue;
        p8 = w2 * red;
        mixedRed = p0 + p1 + p2;
        mixed_green = p3 + p4 + p5;
        mixed_blue = p6 + p7 + p8;
        originalMax = RW_MAX_GT((u8)redArg,
            RW_MAX_GT((u8)greenArg, (u8)blueArg));
        largest = mixed_blue;
        if (largest < mixed_green) largest = mixed_green;
        if (largest < mixedRed) largest = mixedRed;
        mixed_max = (f32)largest;
        if (mixed_max != 0.0f) {
            *redOut = (u32)((f32)mixedRed * originalMax / mixed_max);
            *green_out = (u32)((f32)mixed_green * originalMax / mixed_max);
            *blue_out = (u32)((f32)mixed_blue * originalMax / mixed_max);
        } else {
            *redOut = redArg;
            *green_out = greenArg;
            *blue_out = blueArg;
        }
    } else {
        *redOut = redArg;
        *green_out = greenArg;
        *blue_out = blueArg;
    }
}

/* Blends a colour toward the grey of its brightest channel: with amount (0-100) zero it copies r, g, b to the outputs, otherwise each output is (channel * (100 - amount) + max(r, g, b) * amount) / 100. */
void Gregion_DesaturateColor(u8 amount, u8 r, u8 g, u8 b, u8 *outR, u8 *outG, u8 *outB) {
    s32 rest;
    s32 top;
    if (amount != 0) {
        rest = 100 - amount;
        top = RW_MAX_GT(r, RW_MAX_GT(g, b));
        *outR = (r * rest + top * amount) * 0.01f;
        *outG = (g * rest + top * amount) * 0.01f;
        *outB = (b * rest + top * amount) * 0.01f;
    } else {
        *outR = r;
        *outG = g;
        *outB = b;
    }
}

/* Darkens a colour by a percentage: with a non-zero percentage each channel becomes the channel scaled by one hundredth of (100 minus the percentage), and with zero the channels are copied unchanged. */
void Gregion_DarkenColor(unsigned char percent, unsigned char r, unsigned char g, unsigned char b,
                   unsigned char *outR, unsigned char *outG, unsigned char *outB) {
    int remaining;
    if (percent != 0) {
        remaining = 100 - percent;
        *outR = (unsigned int)(r * 0.01f * remaining);
        *outG = (unsigned int)(g * 0.01f * remaining);
        *outB = (unsigned int)(b * 0.01f * remaining);
    } else {
        *outR = r;
        *outG = g;
        *outB = b;
    }
}

/* Retained data for this translation unit. */
#if !(defined(VERSION_US_REV1))
const float g_getCachedUpQuatConstants[2] = {
    1.0f, 0.5f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_testPolygonSlopeFlagConstants[2] = {
    1.0f, 0.5f,
};
#endif

const float g_scaleWordsToFloatsConstants[1] = {
    0.029296875f,
};

const float g_regionEdgeCrossDefaultUp[1] = {
    1.0f,
};

const float g_regionNormalDefaultUp[2] = {
    1.0f, 1.0f,
};

const float g_regionMissingPolygonHeight[2] = {
    -14336.0f, 0.33333334f,
};

const float g_regionCeilingDefaultUp[1] = {
    -1.0f,
};

const float g_regionHueWeightScales[3] = {
    0.011764706f, 0.011764706f, 0.011764706f,
};
