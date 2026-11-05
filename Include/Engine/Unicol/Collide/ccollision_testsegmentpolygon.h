#ifndef ENGINE_UNICOL_COLLIDE_CCOLLISION_TESTSEGMENTPOLYGON_H
#define ENGINE_UNICOL_COLLIDE_CCOLLISION_TESTSEGMENTPOLYGON_H
#include "Collide/ccollision_testsegmentdisk.h"
#include "Common/sky_layers.h"
#include "Common/sharedplayer.h"
#include "Common/output.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Engine/Unicol/collide.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Plane/ccollision_intersectfrontplanepoint.h"
#include "Rsp/random_direction_and_affine_math.h"
extern s32 CCollision_IntersectFrontPlaneFraction(void *poly, void *start, void *segmentEnd, f32 *outputFraction);
#endif
