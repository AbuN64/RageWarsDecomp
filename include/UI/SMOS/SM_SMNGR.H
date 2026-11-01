#ifndef UI_SMOS_SM_SMNGR_H
#define UI_SMOS_SM_SMNGR_H
#include "COMMON/INTEGERSTATE530.H"
extern void MoveMenuFocus(s32 direction);
extern s32 DispatchScreenRangeEvent(s32,s32,s32,void *,s32);
extern s32 DispatchCurrentScreenEvent(s32 recurse, s32 event, s32 value, s32 argument, s32 context);
#endif
