#ifndef MENU_MENU_H
#define MENU_MENU_H
#include "types.h"
extern void MarkMenuEventHandled();
extern s32 Menu_GetElementHandlerFlags(s32);
extern u32 Menu_GetBlockedScreenOwner(void);
s32 Menu_GetFocusedElementId(void);
#endif
