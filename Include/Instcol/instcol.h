#ifndef INSTCOL_INSTCOL_H
#define INSTCOL_INSTCOL_H
#include "types.h"
struct ActorMotion;
void CInstanceCollision_BuildSweepQuery(struct ActorMotion *motion, f32 *queryStorage);
#endif
