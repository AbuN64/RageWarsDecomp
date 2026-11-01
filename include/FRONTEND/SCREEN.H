#ifndef FRONTEND_SCREEN_H
#define FRONTEND_SCREEN_H
#include "TYPES.H"
extern void Frontend_ApplyVideoMode(void);
extern void Frontend_SetVideoViewport(s32 width, s32 height, s32 x, s32 y, s32 borderX, s32 borderY);
extern void Frontend_AdvanceVideoMode(void);
extern void Frontend_ApplyScreenModeValue(s32 value);
extern void Frontend_StartScreenModeFade(void);
extern void Frontend_UpdateScreenMode(void);
extern void Frontend_RequestScreenMode(s32 value);
#endif
