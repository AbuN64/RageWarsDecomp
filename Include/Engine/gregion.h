#ifndef ENGINE_GREGION_H
#define ENGINE_GREGION_H
#include "Engine/folded_constants.h"




#include "Common/packed.h"
#include "Common/model_tree_region_operations.h"
#include "Common/vector.h"

struct Node75 {
    u16 reservedHalf;
    u16 flags; /* +0x02: Scene_FindFloorPolygon, mask0x40 */
    CVector3 *prev;
    CVector3 *cur;
    CVector3 *next;
    u8 reserved10[0x10]; /* ROM advances terrain records by0x20 */
};
typedef struct Node75 Node75;

struct Packed;
extern CQuatern *Region_GetPolygonUpQuat(CQuatern *out, struct Triangle *polygon);
extern CQuatern *Region_GetCachedUpQuat(CQuatern *out, struct Triangle *polygon);
extern void Region_ScaleWordsToFloats(void *wordStorage);
extern void Region_DecodePackedRegion(CGameRegion *dst, struct Packed *src, char *base, int vertexCount, char *extra);
extern s32 Region_IsPointInTriangleXZ(struct Node75 *triangle, f32 x, f32 z);
extern CVector3 *Region_GetNodeEdgeCross(CVector3 *out, struct Node75 *node);
extern CVector3 *Region_GetCachedCeilingNormal(CVector3 *out, struct Node75 *node);
extern f32 Region_GetTriangleEdgeAngle(struct Triangle *triangle, s32 edgeIndex);
extern void Region_SetNodeGroupFlag(struct ModelTreeNode *modelTreeNode);
extern void Region_ClearNodeGroupFlag(struct ModelTreeNode *modelTreeNode);
extern void Region_MarkMatchingNodes(struct ModelTreeNode *modelTreeNode, u16);
extern void Region_UnmarkMatchingNodes(struct ModelTreeNode *modelTreeNode, u16);
extern f32 Region_SetMatchingVertexHeights(u16 *, f32, u16);
extern void Region_ExpandPointBounds(f32 *, s32, CVector3 *);
extern void Region_ComputeHorizontalBounds(void *, s32, void *);
struct CVector3_t;
void Region_ComputePointBounds(f32 *pointBounds, s32 pointCount, struct CVector3_t *pointCursor);
struct Node75;
f32 Region_GetPolygonHeight(struct Node75 *node, f32 x, f32 z);
f32 Region_SetNodeGroupHeight(u16 *modelTreeNode, f32 height);
extern void Gregion_ShiftColorHue(u8 hue, u8 red_arg, u8 green_arg, u8 blue_arg, u8 *red_out, u8 *green_out, u8 *blue_out);
extern void Gregion_DarkenColor(unsigned char percent, unsigned char r, unsigned char g, unsigned char b, unsigned char *outR, unsigned char *outG, unsigned char *outB);
extern u8 Region_GetModelBlendByte59(s32 modelId);
extern u8 Region_GetModelBlendByte58(s32 modelId);
extern struct Triangle *g_regionCachedEdgePolygon;
extern struct Triangle *g_regionCachedNormalPolygon;
struct CVector3_t; extern void Gregion_ExpandHorizontalBounds(f32 *bounds, s32 pointCount, struct CVector3_t *points);
struct Triangle; extern s32 Region_TestPolygonSlopeFlag(struct Triangle *polygon);
#endif
