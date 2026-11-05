#ifndef ENGINE_INSTANCE_GOBJINST_GOBJINST_BUILDTARGETAIMORIENTATION_H
#define ENGINE_INSTANCE_GOBJINST_GOBJINST_BUILDTARGETAIMORIENTATION_H
#include "Gobjinst/gameobject_getactorheight.h"
#include "Engine/Instance/Gobjinst/gastate_advancerootmotion_data.h"
#include "Common/ballisticparams.h"
#include "Common/probe.h"
#include "Common/obj.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "types.h"
#include "Fx/normalize_vector.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Ai/Player/player_getammocapacity.h"
#include "Game/builddirectionmatrix.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Common/approachlocation.h"
extern void MatrixFromQuaternion(f32 *q, f32 *m);
#endif
