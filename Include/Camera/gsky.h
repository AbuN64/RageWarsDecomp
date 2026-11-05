#ifndef CAMERA_GSKY_H
#define CAMERA_GSKY_H
#include "Common/viewflags.h"
struct ThreeChannels;
extern void Gsky_GetMaskedEffectColor(struct ThreeChannels *threeChannels, s8 *red, s8 *green, s8 *blue);
extern void Gsky_StartEmitter(char *obj, f32 a, f32 b, f32 c, f32 scale, s32 value, CVector3 pos);
extern f32 Gsky_GetDistanceTo(void *gameplayCamera, CVector3 *targetPosition);
extern void Gsky_DrawPlayerListNoOp(void);
#endif
