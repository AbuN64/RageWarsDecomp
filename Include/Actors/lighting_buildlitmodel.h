#ifndef ACTORS_LIGHTING_BUILDLITMODEL_H
#define ACTORS_LIGHTING_BUILDLITMODEL_H
#include "Common/propgeometry.h"
struct Bounds; struct FixedPointMatrix; extern s32 Lighting_BuildLitModel(s32 modelResource, void *lightResource, struct Bounds *bounds, struct FixedPointMatrix *matrices, s32 skinned, u8 *wanted);
#endif
