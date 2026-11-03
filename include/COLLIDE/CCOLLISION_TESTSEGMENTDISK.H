#ifndef COLLIDE_CCOLLISION_TESTSEGMENTDISK_H
#define COLLIDE_CCOLLISION_TESTSEGMENTDISK_H
struct CapsuleSweep;
struct Polygon;
struct CVector3_t;
s32 CCollision_TestSegmentDisk(struct CapsuleSweep *ray, struct Polygon *poly, struct CVector3_t *point, f32 radius, s32 keep);
#endif
