#ifndef GREGION_GREGION_H
#define GREGION_GREGION_H
#include "types.h"
struct Triangle;
s32 Region_TestPolygonSlopeFlag(struct Triangle *polygon);
struct CVector3_t; struct Node75;
struct CVector3_t *Region_GetNodeNormal(struct CVector3_t *out, struct Node75 *node);
#endif
