#ifndef MENU_TITLE_MENU_DISPATCHTITLEBUTTONCOLUMNEVENT_SYMBOLS_H
#define MENU_TITLE_MENU_DISPATCHTITLEBUTTONCOLUMNEVENT_SYMBOLS_H
#include "types.h"
#if (defined(VERSION_DE))
typedef s32 (*TitleButtonColumnEventHandler)(void *, s32, s32, s32, s32);
extern TitleButtonColumnEventHandler g_titleButtonColumnEventHandlers;
#endif
#endif
