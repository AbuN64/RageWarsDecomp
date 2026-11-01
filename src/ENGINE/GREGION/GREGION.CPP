#include "COMMON/PACKED.H"
#include "COMMON/OBJ.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "TYPES.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/MODEL_TREE_REGION_OPERATIONS.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/WORLD.H"
#include "COMMON/OBJB.H"
#include "include_asm.h"

/* 8027451C_2.CPP */
/* Returns the rotation quaternion that tilts the up axis onto a polygon's unit normal (recomputed from its edges into g_regionCachedEdgeCross and normalised into g_regionCachedUnitNormal whenever the polygon differs from the last one, straight up for no polygon), recording the half-angle sine in g_turretAimSine and giving the identity when the normal is vertical. Adapted from Region_GetCachedUpQuatDe with the cached polygon normal of Region_TestPolygonSlopeFlag replacing Graphu64_GetCachedSurfaceNormal and the default normals written through their separate cells. */

extern Triangle *g_regionCachedEdgePolygon;

extern Triangle *g_regionCachedNormalPolygon;

extern void Graphu64_SubtractVectors(CVector3 *out, CVector3 *a, CVector3 *b);

extern void Graphu64_CrossVectors(CVector3 *out, CVector3 *a, CVector3 *b);

extern void Graphu64_ScaleVector(CVector3 *out, CVector3 *in, f32 scale);

extern f32 Gu_Sqrtf(f32);

static inline void edge(CVector3 *out, CVector3 *a, CVector3 *b) {
    Graphu64_SubtractVectors(out, a, b);
}

static inline void normalize_copy(CVector3 *out, CVector3 *in) {
    *out = *in;
    Graphu64_NormalizeVec3(out);
}

extern void Graphu64_GetCachedSurfaceNormal(CVector3 *);

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

    Graphu64_GetCachedSurfaceNormal(&a);
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

/* 8027451C_3.CPP */
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

/* 8027451C_4.CPP */

/* Returns the normalised cross product of a path node's two edge vectors, cached in g_regionCachedUnitNormal for the last node seen, with a default up vector for a null node.
   Adapted from Graphu64_GetCachedSurfaceNormal with the edge vectors computed through the Graphu64_SubtractVectors subtract helper, the cross product arguments in forward order, and the cache globals changed. */

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

/* Decodes a packed header into its runtime form: copies the two leading shorts and the word at 0x10,
   and for each of three channels resolves a 16-byte-scaled offset against base and a 32-byte-scaled
   offset against extra, leaving the latter null when it is 0xFFFF. */

void Region_DecodePackedRegion(CGameRegion *dst, Packed *src, char *base, int unused, char *extra) {
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
    CVector3 *b_ptr;

    if (node == 0) {
        g_regionCachedEdgeCross.x = 0;
        g_regionCachedEdgeCross.z = 0;
        g_regionCachedEdgeCross.y = g_regionEdgeCrossDefaultUp;
    } else if ((Triangle *)node != g_regionCachedEdgePolygon) {
        Graphu64_SubtractVectors(&a, node->cur, node->prev);
        b_ptr = &b;
        Graphu64_SubtractVectors(b_ptr, node->next, node->cur);
        Graphu64_CrossVectors(&g_regionCachedEdgeCross, &a, b_ptr);
    }
    *out = g_regionCachedEdgeCross;
    g_regionCachedEdgePolygon = (Triangle *)node;
    return out;
}

CVector3 *Region_GetNodeNormal(CVector3 *out, Node75 *node) {
    if (node == 0) {
        g_regionCachedUnitNormal.x = 0;
        g_regionCachedUnitNormal.z = 0;
        g_regionCachedUnitNormal.y = g_regionNormalDefaultUp;
    } else if ((Triangle *)node != g_regionCachedNormalPolygon) {
        cross_edges(&g_regionCachedUnitNormal, node);
        Graphu64_NormalizeVec3(&g_regionCachedUnitNormal);
    }
    *out = g_regionCachedUnitNormal;
    g_regionCachedNormalPolygon = (Triangle *)node;
    return out;
}

/* 80275E44.CPP */
/* Returns the height of a path node's triangle plane at (x, z) from the cached edge cross product in g_regionCachedEdgeCross, or the mean vertex height when the plane is vertical.
   Adapted from Region_GetPolygonHeightDe with the edge vectors computed through the Graphu64_SubtractVectors subtract helper inside a static inline helper, the vertex read as a whole vector with y at offset 4, the null result a rodata constant, and the cache globals changed. */

static inline void cross_node_edges(Node75 *node) {
    CVector3 a;
    CVector3 b;

    Graphu64_SubtractVectors(&a, node->cur, node->prev);
    Graphu64_SubtractVectors(&b, node->next, node->cur);
    Graphu64_CrossVectors(&g_regionCachedEdgeCross, &a, &b);
}

extern void *Scene_GetModelRecordByIndexPointer(Shared_World *world, s32 modelId);

extern void Gregion_ExpandHorizontalBounds(void *bounds, s32 pointCount, void *points);

f32 Region_GetPolygonHeight(Node75 *node, f32 x, f32 z) {
    CVector3 normal;
    CVector3 point;

    if (node == 0) {
        return g_regionMissingPolygonHeight;
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
        g_cachedCeilingCrossProduct.y = g_regionCeilingDefaultUp;
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

u8 Region_GetModelBlendByte58(s32 modelId) {
    ModelBlend *blend = Scene_GetModelRecordByIndexPointer(&g_world, modelId);
    if (blend == 0) {
        return 0;
    }
    return blend->byte58;
}

u8 Region_GetModelBlendByte59(s32 modelId) {
    ModelBlend *blend = Scene_GetModelRecordByIndexPointer(&g_world, modelId);
    if (blend == 0) {
        return 0;
    }
    return blend->byte59;
}

f32 Region_GetTriangleEdgeAngle(void *triangle, s32 edgeIndex) {
    Triangle *polygon = triangle;
    CVector3 *v0;
    CVector3 *v1;
    f32 dx, dz;
    f32 mag;
    f32 result;

    v1 = polygon->vertices[edgeIndex];
    v0 = polygon->vertices[(edgeIndex + 1) % 3];
    dx = v0->x - v1->x;
    dz = v0->z - v1->z;
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

void Region_SetNodeGroupFlag(void *modelTreeNode) {
    struct ModelTreeNode *node = modelTreeNode;
    if ((modelTreeNode != 0) && (node->flags & 2)) {
        Region_MarkMatchingNodes(modelTreeNode, node->modelId);
    }
}

void Region_ClearNodeGroupFlag(void *modelTreeNode) {
    struct ModelTreeNode *node = modelTreeNode;
    if ((modelTreeNode != 0) && (node->flags & 2)) {
        Region_UnmarkMatchingNodes(modelTreeNode, node->modelId);
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

/* 800C9ACC.CPP */
#if !(defined(VERSION_US_REV1))
const float k_GregionEncodedWords[2] = {
    1.0f, 0.5f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/k_GregionEncodedWordsBlock1Source.c */
const float k_GregionEncodedWordsBlock1[2] = {
    1.0f, 0.5f,
};
#endif

/* 800C9AD4.CPP */
#if !(defined(VERSION_US_REV1))
const float g_Region_GetCachedUpQuatConstantWords[2] = {
    1.0f, 0.5f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_Region_TestPolygonSlopeFlagConstantWordsSource.c */
const float g_Region_TestPolygonSlopeFlagConstantWords[2] = {
    1.0f, 0.5f,
};
#endif

/* 800C9ADC.CPP */
/* ROM-grounded data: src/g_Region_ScaleWordsToFloatsConstantWordsSource.c */
const float g_Region_ScaleWordsToFloatsConstantWords[1] = {
    0.029296875f,
};

/* 800C9AE0.CPP */
/* ROM-grounded data: src/g_regionEdgeCrossDefaultUp_StorageWordsSource.c */
const float g_regionEdgeCrossDefaultUp_StorageWords[1] = {
    1.0f,
};

/* 800C9AE4.CPP */
/* ROM-grounded data: src/g_regionNormalDefaultUp_StorageWordsSource.c */
const float g_regionNormalDefaultUp_StorageWords[2] = {
    1.0f, 1.0f,
};

/* 800C9AEC.CPP */
/* ROM-grounded data: src/g_regionMissingPolygonHeight_StorageWordsSource.c */
const float g_regionMissingPolygonHeight_StorageWords[2] = {
    -14336.0f, 0.33333334f,
};

/* 800C9AF4.CPP */
/* ROM-grounded data: src/g_regionCeilingDefaultUp_StorageWordsSource.c */
const float g_regionCeilingDefaultUp_StorageWords[1] = {
    -1.0f,
};


#if defined(VERSION_EU_X)
float k_GregionEncodedWordsBlock5[2] = {
    -1.0e-06f, 1.0e-06f,
};
#endif


