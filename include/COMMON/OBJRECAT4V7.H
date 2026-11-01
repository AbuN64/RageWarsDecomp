#ifndef COMMON_OBJRECAT4V7_H
#define COMMON_OBJRECAT4V7_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
struct AttachmentEffectBinding;
typedef struct AttachmentEffectBinding AttachmentEffectBinding;

extern float g_fullFixedMatrixElement13ConversionConstants;

extern float g_randomDirectionZRangeConstants;

extern float g_matrixUnpackHomogeneousScale;

extern float g_fullFixedMatrixElement4ConversionConstants;

extern float g_affineFixedMatrixElement2ConversionConstants;

extern void Geometry_SetPrimitiveColorOverride(unsigned char first, unsigned char second, unsigned char third, unsigned char fourth);

extern float g_quaternionOppositeDirectionThreshold;

struct MaterialTreeNode;
typedef struct MaterialTreeNode MaterialTreeNode;

extern float g_quaternionAxisNormalizeScale;

struct AttachmentEffectActorView;
typedef struct AttachmentEffectActorView AttachmentEffectActorView;

extern float g_fullFixedMatrixElement8ConversionConstants;

extern float g_quaternionMatrixUnitScale;


extern float g_affineFixedMatrixElement14ConversionConstants;

extern float g_affineFixedMatrixElement9ConversionConstants;

extern float g_affineFixedMatrixElement5ConversionConstants;

extern float g_fullFixedMatrixElement9ConversionConstants;

extern float g_quaternionInterpolationThresholdConstants;

extern float g_matrixAndSlerpUnitConstants;

extern void Geometry_SwitchRenderMicrocode(void);

extern float g_fullFixedMatrixElement3ConversionConstants;

extern float g_fullFixedMatrixElement2ConversionConstants;

extern float g_fullFixedMatrixElement6ConversionConstants;

struct AttachmentEffectBinding;

extern unsigned char g_primitiveColorOverrideBlue;

extern float g_quaternionParallelDirectionThreshold;

extern float g_quaternionNormalizeConstants;

extern unsigned char g_primitiveColorOverrideEnabled;

extern float g_affineFixedMatrixElement4ConversionConstants;

struct ModelBoundingBox;
typedef struct ModelBoundingBox ModelBoundingBox;

struct TreeNode;

extern unsigned char g_primitiveColorOverrideGreen;

extern float g_fullFixedMatrixElement10ConversionConstants;

extern float g_affineFixedMatrixElement13ConversionConstants;

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

extern float g_affineFixedMatrixElement6ConversionConstants;

struct TreeNode;
typedef struct TreeNode TreeNode;

extern float g_randomDirectionYRangeConstants;

extern void *Geometry_FindMaterialNodeOrParent(MaterialTreeNode **root, u32 materialKey);

extern float g_fullFixedMatrixElement5ConversionConstants;

extern float g_affineFixedMatrixElement8ConversionConstants;

extern float g_fullFixedMatrixElement7ConversionConstants;

struct ModelAttachmentEffect;

extern float g_fullFixedMatrixElement12ConversionConstants;

extern void Geometry_ResetDisplayListState(int *state);

extern float g_fullFixedMatrixElement15ConversionConstants;

extern float g_fullFixedMatrixElement1ConversionConstants;

extern float g_affineFixedMatrixElement1ConversionConstants;

extern void Geometry_LoadRenderMicrocode(void);

struct ModelAttachmentEffect;
typedef struct ModelAttachmentEffect ModelAttachmentEffect;

extern float g_quaternionSlerpUnitScale;

extern float g_randomDirectionNormalizeScale;

extern void Geometry_RefreshMaterialResources(void **modelResource);

struct ModelBoundingBox;
struct ModelBoundingBox {
    f32 min[3];
    f32 max[3];
};

extern unsigned char g_primitiveColorOverrideRed;


extern float g_affineFixedMatrixElement0ConversionConstants;

extern float g_quaternionIdentityW;


extern float g_inputDirectionNormalizeScale;

extern float g_fullFixedMatrixElement14ConversionConstants;

extern float g_fullFixedMatrixElement11ConversionConstants;

struct AttachmentTable;
typedef struct AttachmentTable AttachmentTable;

extern float g_quaternionDirectionUnitScale;

extern float g_quaternionInterpolationUnitScale;

struct AttachmentTable;

extern float g_quaternionHalfAngleScale;

extern float g_affineFixedMatrixElement10ConversionConstants;

struct AttachmentEffectActorView;

extern float g_affineFixedMatrixElement12ConversionConstants;


/* Reference stored in section zero of a resource entry. */
typedef struct ResourceSectionReference {
    s32 prefix[2];
    s32 resource;
} ResourceSectionReference;
#endif
