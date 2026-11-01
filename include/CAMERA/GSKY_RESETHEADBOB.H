#ifndef CAMERA_GSKY_RESETHEADBOB_H
#define CAMERA_GSKY_RESETHEADBOB_H
#include "COMMON/VIEWFLAGS.H"
extern void Gsky_HeadBobInitializeNoOp(void);
extern void Gsky_HeadBobUpdateNoOp(void);
extern void Gsky_ResetHeadBob(struct GameplayCamera *camera);
#endif
