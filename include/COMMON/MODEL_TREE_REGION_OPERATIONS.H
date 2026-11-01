#ifndef COMMON_MODEL_TREE_REGION_OPERATIONS_H
#define COMMON_MODEL_TREE_REGION_OPERATIONS_H
struct ModelTreeNode;
#ifndef COMMON_MODEL_TREE_REGION_OPERATIONS_DECLARATIONS_H
#define COMMON_MODEL_TREE_REGION_OPERATIONS_DECLARATIONS_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
extern void Region_UnmarkMatchingNodes(struct ModelTreeNode *modelTreeNode, u16 nodeId);

extern void Gregion_NoOperation(void);

extern void Region_ClearNodeGroupFlag(void *modelTreeNode);


extern float g_regionCeilingDefaultUp;

extern void Region_SetNodeGroupFlag(void *modelTreeNode);

extern float g_lightVolumeSphereDistanceLookup[];

extern float g_regionVerticalPolygonMeanScale;

extern float g_lightVolumeConeLookupScale;


extern float g_regionMissingPolygonHeight;

union RegionVertexReference;
typedef union RegionVertexReference RegionVertexReference;




extern float g_lightVolumeUnitIntensity;





union RegionVertexReference;
union RegionVertexReference {
    void * v0;
    u16 * v1;
};

struct RegionTriangleVertexView;
struct RegionTriangleVertexView {
    char pad0[0x4];
    char * firstVertex;
    char pad4[0x8 - 0x4 - sizeof(char*)];
    char * secondVertex;
    char pad8[0xC - 0x8 - sizeof(char*)];
    char * thirdVertex;
    char padC[0x10 - 0xC - sizeof(char*)];
    RegionVertexReference firstBranch;
    char pad10[0x14 - 0x10 - sizeof(RegionVertexReference)];
    RegionVertexReference secondBranch;
    char pad14[0x18 - 0x14 - sizeof(RegionVertexReference)];
    RegionVertexReference thirdBranch;
};




extern float g_lightVolumeSphereLookupScale;

extern float g_lightVolumePositiveBound;

struct RegionTriangleVertexView;
typedef struct RegionTriangleVertexView RegionTriangleVertexView;

extern float g_lightVolumeNegativeBound;

extern void Region_ExpandPointBounds(f32 *bounds, s32 pointCount, CVector3 *points);

extern float g_lightVolumeConeDistanceLookup[];



extern void Region_MarkMatchingNodes(struct ModelTreeNode *modelTreeNode, u16 nodeId);


/* Shared object layout established by model-tree consumers. */
struct ModelTreeNode {
    u16 modelId; /* 0x00 */
    u16 flags; /* 0x02 */
    u8 padding004[0xC];
    struct ModelTreeNode *branches[3]; /* 0x10 */
};

extern f32 Region_SetMatchingVertexHeights(u16 *modelTree, f32 height, u16 nodeId);

#endif
#endif
