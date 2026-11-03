#ifndef GRAPHU64_GRAPHU64_BUILDLOOKATMATRIX_H
#define GRAPHU64_GRAPHU64_BUILDLOOKATMATRIX_H
struct CVector3_t;
struct Node75;
struct CVector3_t *Graphu64_GetCachedSurfaceNormal(struct CVector3_t *out, struct Node75 *node);
f32 Graphu64_GetTrianglePlaneHeight(struct Node75 *node, f32 x, f32 z);
#endif
