#ifndef ENGINE_ANIM_GASTATE_H
#define ENGINE_ANIM_GASTATE_H
#include "Engine/folded_constants.h"



#include "Engine/Instance/gastate_advancerootmotion_data.h"
#include "types.h"


extern const f32 g_rootMotionCurrentAngleScale;
extern f32 g_rootMotionFrameAdvanceScale;
extern const f32 g_rootMotionWrappedAngleScale;
extern f64 g_rootMotionAngleRestartUnsignedBias;
extern f64 g_rootMotionClampedRestartUnsignedBias;
extern f64 g_rootMotionEventRestartUnsignedBias;
extern f64 g_rootMotionPositionRestartUnsignedBias;

#endif
