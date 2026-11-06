#ifndef UI_SMOS_SM_SMNGR_H
#define UI_SMOS_SM_SMNGR_H
#include "Common/menu_screen_elements.h"
extern void MoveMenuFocus(s32 direction);
extern s32 DispatchScreenRangeEvent(s32,s32,s32,void *,s32);
extern s32 DispatchCurrentScreenEvent(s32 recurse, s32 event, s32 value, s32 argument, s32 context);
/* Menu_DrawScreenStack's tick of its last draw; zero until the first draw. */
extern s32 s_menuLastDrawTick;
/* The twelve bytes the linker places after it in SM_SMngr.cpp's data; no reader. */
typedef struct MenuDrawClockTail {
#if defined(VERSION_DE)
    float angles[3];
#elif defined(VERSION_EU)
    s32 id;
    float constants[2];
#elif defined(VERSION_US)
    char text[4];
    s32 ids[2];
#else
    char text[12];
#endif
} MenuDrawClockTail;
typedef char MenuDrawClockTailSizeCheck[sizeof(MenuDrawClockTail) == 12 ? 1 : -1];
extern MenuDrawClockTail s_menuDrawClockTail;
#endif
