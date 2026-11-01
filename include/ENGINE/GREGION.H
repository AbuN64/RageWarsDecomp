#ifndef ENGINE_GREGION_H
#define ENGINE_GREGION_H
#include "COMMON/PACKED.H"
#include "COMMON/MODEL_TREE_REGION_OPERATIONS.H"
extern CQuatern *Region_GetPolygonUpQuat(CQuatern *out, Triangle *polygon);
extern CQuatern *Region_GetCachedUpQuat(CQuatern *out, Triangle *polygon);
extern void Region_ScaleWordsToFloats(void *wordStorage);
extern void Region_DecodePackedRegion(CGameRegion *dst, Packed *src, char *base, int unused, char *extra);
extern s32 Region_IsPointInTriangleXZ(Node75 *triangle, f32 x, f32 z);
extern CVector3 *Region_GetNodeEdgeCross(CVector3 *out, Node75 *node);
extern CVector3 *Region_GetCachedCeilingNormal(CVector3 *out, Node75 *node);
extern f32 Region_GetTriangleEdgeAngle(void *triangle, s32 edgeIndex);
extern void Region_SetNodeGroupFlag(void *modelTreeNode);
extern void Region_ClearNodeGroupFlag(void *modelTreeNode);
extern void Region_MarkMatchingNodes(struct ModelTreeNode *modelTreeNode, u16);
extern void Region_UnmarkMatchingNodes(struct ModelTreeNode *modelTreeNode, u16);
extern f32 Region_SetMatchingVertexHeights(u16 *, f32, u16);
extern void Region_ExpandPointBounds(f32 *, s32, CVector3 *);
extern void Region_ComputeHorizontalBounds(void *, s32, void *);
#endif
