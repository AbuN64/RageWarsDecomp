#ifndef ENGINE_UNICOL_COLLIDE_CCOLLISION_TESTOFFSETPOLYGON_H
#define ENGINE_UNICOL_COLLIDE_CCOLLISION_TESTOFFSETPOLYGON_H
#include "Collide/ccollision_testsegmentdisk.h"
#include "Common/sharedplayer.h"
#include "Common/output.h"
#include "types.h"
#include "Engine/Unicol/plane.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Common/approachlocation.h"
extern f32 g_collisionSlackThresholdFactors_de[];
extern s32 CCollision_IntersectFrontPlaneFraction(void *poly, void *start, void *segmentEnd, f32 *outputFraction);
#endif
