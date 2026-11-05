#ifndef UI_SMOS_SCREEN_EVENTS_H
#define UI_SMOS_SCREEN_EVENTS_H
#include "types.h"

struct ScreenEventTreeNode;
extern void Smos_DispatchDescendantScreenEvent(struct ScreenEventTreeNode *, s32, s32, s32, s32, s32);
#endif
