#ifndef COMMON_MATERIAL_TREE_H
#define COMMON_MATERIAL_TREE_H
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/vector4f.h"
struct AttachmentEffectBinding;
typedef struct AttachmentEffectBinding AttachmentEffectBinding;


extern float g_randomDirectionZRangeConstants;

extern float g_matrixUnpackHomogeneousScale;



extern void Geometry_SetPrimitiveColorOverride(unsigned char first, unsigned char second, unsigned char third, unsigned char fourth);

extern float g_quaternionOppositeDirectionThreshold;

struct MaterialTreeNode;
typedef struct MaterialTreeNode MaterialTreeNode;

extern float g_quaternionAxisNormalizeScale;



extern float g_quaternionMatrixUnitScale;






extern float g_quaternionInterpolationThresholdConstants;

extern float g_matrixAndSlerpUnitConstants;

extern void Geometry_SwitchRenderMicrocode(void);




struct AttachmentEffectBinding;

extern unsigned char g_primitiveColorOverrideBlue;

extern float g_quaternionParallelDirectionThreshold;

extern float g_quaternionNormalizeConstants;

extern unsigned char g_primitiveColorOverrideEnabled;


struct ModelBoundingBox;
typedef struct ModelBoundingBox ModelBoundingBox;

struct TreeNode;

extern unsigned char g_primitiveColorOverrideGreen;



extern float g_randomDirectionRotationNormalizeConstants;

extern void Geometry_ClearMaterialGroups(void);

struct MaterialTreeNode;
struct MaterialTreeNode {
    u32 key;
    char pad4[0x14];
    struct MaterialTreeNode *left;
    struct MaterialTreeNode *right;
};

extern float g_randomDirectionPairNormalizeConstants;


struct TreeNode;
typedef struct TreeNode TreeNode;

extern float g_randomDirectionYRangeConstants;

extern void *Geometry_FindMaterialNodeOrParent(struct MaterialTreeNode **root, u32 materialKey);




struct ModelAttachmentEffect;


extern void Geometry_ResetDisplayListState(int *state);




extern void Geometry_LoadRenderMicrocode(void);

struct ModelAttachmentEffect;
typedef struct ModelAttachmentEffect ModelAttachmentEffect;

extern float g_quaternionSlerpUnitScale;

extern float g_randomDirectionNormalizeScale;

extern void Geometry_RefreshMaterialResources(void **resource);

struct ModelBoundingBox;
struct ModelBoundingBox {
    f32 min[3];
    f32 max[3];
};

extern unsigned char g_primitiveColorOverrideRed;



extern float g_quaternionIdentityW;


extern float g_inputDirectionNormalizeScale;



struct AttachmentTable;
typedef struct AttachmentTable AttachmentTable;

extern float g_quaternionDirectionUnitScale;

extern float g_quaternionInterpolationUnitScale;

struct AttachmentTable;

extern float g_quaternionHalfAngleScale;





/* Reference stored in section zero of a resource entry. */
typedef struct ResourceSectionReference {
    s32 prefix[2];
    s32 resource;
} ResourceSectionReference;
#endif
