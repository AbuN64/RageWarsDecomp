#ifndef PAUSE_H
#define PAUSE_H
#include "Frontend/frontend.h"
extern s32 Frontend_CreatePauseMenu(struct MenuWidget *root);
extern s32 Frontend_DestroyPauseMenu(void);
extern s32 Frontend_ReturnPauseEventZero(void);
extern s32 Frontend_ReturnPauseEventZeroAlt(void);
extern s32 Frontend_SetPauseMenuInputMode(void);
#endif
