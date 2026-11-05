#ifndef COLLIDE_CCOLLISION_TESTSEGMENTDISK_H
#define COLLIDE_CCOLLISION_TESTSEGMENTDISK_H
#include "Common/vector.h"
#include "types.h"
struct CapsuleSweep;
struct Polygon;
struct CVector3_t;
s32 CCollision_TestSegmentDisk(struct CapsuleSweep *ray, struct Polygon *poly, struct CVector3_t *point, f32 radius, s32 keep);
extern s32 CCollision_IntersectFrontPlaneFraction(void *poly, void *start, void *segmentEnd, f32 *outputFraction);
extern void Graphu64_InterpolateVector(CVector3 *, f32, CVector3 *, CVector3 *);
extern s32 CCollision_IsPointInsideDisk(void *poly, void *point, f32 radius, void *testPoint);

void CCollision_ClearResultFlags(void);

void CCollision_UpdateModelSurfaceFlags(void *, u16 *);
#endif
