#ifndef UI_TSMOS_TSMOS_H
#define UI_TSMOS_TSMOS_H
#include "TYPES.H"
extern u8 g_Level_GetScreenEventTableAddress[];
extern char s_frontendResourceArchiveNameEuX[];

struct StatePair {
    f32 value;
    s32 state;
};

extern void Tsmos_RequestFrontendShutdown(void);
extern void Tsmos_ScaleCurrentScreen(void);

extern void Tsmos_ShutdownFrontend(void);
#endif
