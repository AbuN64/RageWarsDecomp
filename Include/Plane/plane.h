#ifndef PLANE_PLANE_H
#define PLANE_PLANE_H
#include "types.h"
struct Plane;
f32 CPlane_GetSlopeAngle(struct Plane *p,f32 x0,f32 z0,f32 x1,f32 z1);
#endif
