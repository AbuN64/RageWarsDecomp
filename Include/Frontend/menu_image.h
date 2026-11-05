#ifndef FRONTEND_MENU_IMAGE_H
#define FRONTEND_MENU_IMAGE_H
#include "Frontend/results_player_panels.h"

extern void Frontend_ResetEquipmentFromCharacter(void);
extern s32 Frontend_CountActiveEquipmentPanels(void);
extern s32 Frontend_DispatchEquipmentEvent(void *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount);
extern void Frontend_SelectEquipmentColumn(s32, s32);
struct MenuImageState;
void Frontend_DrawMenuImage(struct MenuImageState *menu);
extern int Frontend_CancelEquipmentSelection(int a,int b,unsigned int player);
extern s32 Frontend_FreeEquipmentScreen(void);
extern s32 Frontend_RestoreEquipmentSelections(void *first, void *second, u32 event, s32 held);
extern s32 Frontend_SelectNextEquipmentChoice(void *first, void *second, s32 slot, s32 active);
extern s32 Frontend_SelectNextEquipmentColumn(void *first, void *second, s32 slot, s32 active);
extern s32 Frontend_SelectPreviousEquipmentChoice(void *first, void *second, s32 slot, s32 active);
extern s32 Frontend_SelectPreviousEquipmentColumn(void *first, void *second, s32 slot, s32 active);
#endif
