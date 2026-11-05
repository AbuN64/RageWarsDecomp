#ifndef UI_SMOS_SM_SMNGR_H
#define UI_SMOS_SM_SMNGR_H
#include "Common/menu_screen_elements.h"
extern void MoveMenuFocus(s32 direction);
extern s32 DispatchScreenRangeEvent(s32,s32,s32,void *,s32);
extern s32 DispatchCurrentScreenEvent(s32 recurse, s32 event, s32 value, s32 argument, s32 context);
/* s_smackFormat (SM_SMngr.cpp) holds a different record per version; menu.cpp reads its first word as the last tick. */
#if defined(VERSION_DE)
extern float s_smackFormat[4];
#elif defined(VERSION_EU)
extern struct RestSmackFormat s_smackFormat;
#elif defined(VERSION_US)
extern struct RestSmackFormatVariant2 s_smackFormat;
#else
extern char s_smackFormat[16];
#endif
#endif
