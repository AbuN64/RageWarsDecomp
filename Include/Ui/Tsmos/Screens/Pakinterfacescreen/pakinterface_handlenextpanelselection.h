#ifndef UI_TSMOS_SCREENS_PAKINTERFACESCREEN_PAKINTERFACE_HANDLENEXTPANELSELECTION_H
#define UI_TSMOS_SCREENS_PAKINTERFACESCREEN_PAKINTERFACE_HANDLENEXTPANELSELECTION_H
extern s32 PAKInterface_HandleNextPanelSelection(s32 unusedWidget, s32 unusedEventId, s32 playerEntryId, s32 selectionPressed, s32 fifth);
extern s32 PAKInterface_HandlePakMenuConfirm(s32 element, s32 eventId, s32 packedPlayerEvent, s32 pressState, s32 fifth);
extern s32 PAKInterface_HandlePlayerPanelBack(void *element, void *eventId, u16 player);
extern s32 PAKInterface_MoveNameCursorBackward(s32 element, s32 eventId, s32 playerEntryId, s32 selectionPressed);
#endif
