#ifndef FRONTEND_MENUIMAGE_H
#define FRONTEND_MENUIMAGE_H
#include "FRONTEND/ENTRYRECAT4D4.H"

/* The seven words initialized together by Frontend_InitMenuImage. */
typedef struct MenuImageState {
    s32 resource;
    s32 color[3];
    s32 step;
    s32 frame;
    s32 state;
} MenuImageState;
extern s32 Frontend_GetMenuImageFrame(s32 *record);
extern s32 Frontend_IsMenuImageTransitionComplete(s32 *record);
extern void Frontend_SetMenuImageResource(s32 *, s32);
extern void Frontend_SetMenuImageColor(s32 *, s32, s32, s32);
extern void Frontend_AdvanceMenuImageTransition(s32*record);
#endif
