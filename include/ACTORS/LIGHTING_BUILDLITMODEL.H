#ifndef ACTORS_LIGHTING_BUILDLITMODEL_H
#define ACTORS_LIGHTING_BUILDLITMODEL_H
#include "COMMON/PROPGEOMETRY.H"
struct Bounds; struct PackedMatrixWords; extern s32 Lighting_BuildLitModel(s32 modelResource, void *lightResource, struct Bounds *bounds, struct PackedMatrixWords *matrices, s32 skinned, u8 *wanted);
#endif
