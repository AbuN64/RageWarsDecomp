#ifndef ENGINE_GEOMETRY_H
#define ENGINE_GEOMETRY_H
#include "TYPES.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"

extern s32 g_geometryEffectGeometryMode;

extern void Geometry_AlternateNoOperation(void);

extern void Geometry_DrawMaterialGroups(void);

extern void Geometry_GroupModelInstances(void);

struct TreeNode {
    unsigned int key;
    unsigned char padding[12];
    struct TreeNode *link10;
    struct TreeNode *link14;
    struct TreeNode *link18;
    struct TreeNode *link1c;
};
#endif
