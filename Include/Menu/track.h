#ifndef MENU_TRACK_H
#define MENU_TRACK_H
#include "Common/vector.h"
#include "types.h"
extern CVector3 Track_GetTrackEyePosition(f32);


extern f32 Track_EvaluateTrackScalar(f32 t);
extern void Track_SolveSplineSecondDerivatives(s32 n, f32 *ys, f32 *xs, f32 *out);
#endif
