#ifndef ENGINE_UNICOL_POLYCOL_CPOLYCOLLISION_TRACECEILINGTRIANGLE_H
#define ENGINE_UNICOL_POLYCOL_CPOLYCOLLISION_TRACECEILINGTRIANGLE_H
#include "Engine/Unicol/Polycol/polycol_tracemeshtriangle.h"
#include "Anim/collision_ray.h"
#include "types.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/resident_event_handler.h"
#include "Common/approachlocation.h"
#include "Common/ballisticparams.h"
#include "Common/gameplay_movement.h"
#include "Common/motion_step.h"
#include "Common/world.h"
#include "Common/output.h"
#include "Common/objb.h"
#include "Common/triple.h"
#include "Engine/Unicol/polycol.h"
#include "Render/setn64_getpacksection.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
extern void CPlane_BuildTriangleNormal(void *query);
#endif
