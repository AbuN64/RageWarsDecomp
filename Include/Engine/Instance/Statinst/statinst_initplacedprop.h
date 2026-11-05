#ifndef ENGINE_INSTANCE_STATINST_STATINST_INITPLACEDPROP_H
#define ENGINE_INSTANCE_STATINST_STATINST_INITPLACEDPROP_H
#include "Gobjinst/gameobject_movetoxzkeepheight.h"
#include "Engine/graphics_math.h"
#include "Common/objb.h"
#include "Common/world.h"
#include "Common/Lone/g_defaultcamerasurfacetype.h"
#include "Common/propgeometry.h"
#include "types.h"
#include "common.h"
#include "Engine/scene_drawtransitioncoloroverlay.h"
#include "Game/builddirectionmatrix.h"
#include "Insthdr/insthdr_getactorshadowradius.h"
struct ObjA;
struct PlacedPropRecord;
extern s32 g_gameFrameCounter;

extern void MatrixFromQuaternion(f32 *q, f32 *m);
#endif
