#ifndef AI_NAV_WHEEL_H
#define AI_NAV_WHEEL_H
#include "Common/self.h"
struct WheelProbeClipState;
extern int Wheel_PreviousDirectionSector(int sector);
extern int Wheel_AdvanceWheelProbe(struct WheelProbeClipState *p);
extern int Wheel_NextDirectionSector(int sector);
extern s32 Wheel_GetDirectionSector(f32 angle);

#endif
