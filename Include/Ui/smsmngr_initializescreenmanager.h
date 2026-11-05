#ifndef UI_SMSMNGR_INITIALIZESCREENMANAGER_H
#define UI_SMSMNGR_INITIALIZESCREENMANAGER_H
#include "types.h"

struct Element;
extern int SmSmngr_DeactivateCurrentScreen(s32 screenOwner);
extern struct Element *FindMenuElement(s32 id);
extern struct Element *FindMenuElement(s32);
#endif
