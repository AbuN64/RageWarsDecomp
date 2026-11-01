#ifndef COMMON_FRUSTUM_H
#define COMMON_FRUSTUM_H
#include "TYPES.H"

extern f32 Visdata_EvaluatePlaneAtPoint(f32 *a, f32 *b);

struct Frustum;

extern f32 Visdata_GetPlaneSegmentFraction(f32 *plane, f32 *segmentStart, f32 *segmentEnd);

struct Frustum;
typedef struct Frustum Frustum;

extern float g_planeParallelSegmentFraction;

extern s32 Visdata_TestBoxAgainstPlane(f32 *plane, f32 *boxBounds);

extern void *Node_GetScreenData(s32 index);

s32 Node_IsValidScreenIndex(s32);
#endif
