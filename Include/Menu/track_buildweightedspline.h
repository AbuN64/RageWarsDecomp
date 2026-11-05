#ifndef MENU_TRACK_BUILDWEIGHTEDSPLINE_H
#define MENU_TRACK_BUILDWEIGHTEDSPLINE_H
#include "types.h"
struct Spline;
extern void Track_SolveSplineSecondDerivatives(s32 n, f32 *ys, f32 *xs, f32 *out);
extern void Track_BuildWeightedSpline(s32,CVector3 *,f32 *,struct Spline *);
#endif
