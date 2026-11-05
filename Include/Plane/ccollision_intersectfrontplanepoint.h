#ifndef PLANE_CCOLLISION_INTERSECTFRONTPLANEPOINT_H
#define PLANE_CCOLLISION_INTERSECTFRONTPLANEPOINT_H
#include "types.h"
struct Polygon;
extern s32 CCollision_IsPointInsidePolygon(struct Polygon *poly, void *testPoint);
#include "types.h"
struct Polygon;

f32 CCollision_GetSurfaceHeight(void *query, f32 x, f32 z);
struct LinkedWorldFlagsView;

#endif
