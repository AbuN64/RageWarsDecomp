#ifndef FRONTEND_MENU_IMAGE_H
#define FRONTEND_MENU_IMAGE_H
#include "FRONTEND/ENTRYRECAT4D4.H"

extern void Frontend_ResetEquipmentFromCharacter(void);
extern s32 Frontend_CountActiveEquipmentPanels(void);
extern s32 Frontend_DispatchEquipmentEvent(void *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount);
extern void Frontend_SelectEquipmentColumn(s32, s32);
#endif
