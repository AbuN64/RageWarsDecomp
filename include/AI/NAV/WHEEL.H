#ifndef AI_NAV_WHEEL_H
#define AI_NAV_WHEEL_H
#include "COMMON/SELF.H"
extern int Wheel_PreviousDirectionSector(int sector);
extern int Wheel_AdvanceWheelProbe(WheelProbeClipState *p);
extern int Wheel_NextDirectionSector(int sector);
#endif
