#ifndef COLLIDE_CCOLLISION_INTERSECTSEGMENTBOX_H
#define COLLIDE_CCOLLISION_INTERSECTSEGMENTBOX_H
#include "types.h"
struct Ray; struct Box;
s32 CCollision_IntersectSegmentBox(struct Ray *ray, struct Box *box, f32 *out);
struct Ray; struct CQuatern_t;
s32 CCollision_IntersectSegmentRectangle(struct Ray *ray, struct CQuatern_t *rect, f32 *t);
#endif
