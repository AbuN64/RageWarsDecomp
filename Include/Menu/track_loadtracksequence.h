#ifndef MENU_TRACK_LOADTRACKSEQUENCE_H
#define MENU_TRACK_LOADTRACKSEQUENCE_H
#include "Common/track_spline.h"
struct SplineNode;
extern s32 Track_LoadTrackSequence(s32 resource);
extern CVector3 Track_EvaluateCameraSpline(struct SplineNode *keys, s32 count, f32 t);
#endif
