#ifndef LINKDATA_GERMAN_LINK_DATA_H
#define LINKDATA_GERMAN_LINK_DATA_H
#include "types.h"
#if defined(VERSION_DE)
extern void *g_slotSelectionNameText[]; /* table of pointers */
extern void *g_slotSelectionMenuText[]; /* table of pointers */
extern void *g_slotSelectionMenuPointerText[]; /* table of pointers */
extern void *g_resultsModeMessage[]; /* table of pointers */
extern void *g_slotAchievementTextPointers_DurchgefbhrtWarehouse[]; /* table of pointers */
extern char addrLow_SmpList_HandleStopEvent[];
extern char addrLow_SmpOverlay_ReturnUnhandledPakDialogEvent[];
extern char g_Frontend_GetMenuImageStateTailAddress[];
extern char g_Frontend_SelectNextJoinModelAddress_de[];
extern char g_Frontend_SelectPreviousJoinModelAddress_de[];
extern char g_Join_CycleJoinRequestRankAddress_de[];
extern char g_Join_DestroyJoinOptionsMenuAddress_de[];
extern char g_Join_PulseJoinSelectionHighlightAddress_de[];
extern char g_Join_RequestJoinOptionsExitAddress_de[];
extern char g_Join_RequestJoinOptionsExitAlternateAddress_de[];
extern char g_Join_SelectNextJoinRowAddress_de[];
extern char g_Join_SelectPreviousJoinRowAddress_de[];
extern char g_Level_GetScreenEventTableNextAddress[];
extern char g_Menu_CreateGermanCourseOptionsAddress[];
extern char g_focus_FreeMenuBlockEntry[];
extern char g_frontend_AnimateSlotSelectionMenuEntry[];
extern char g_frontend_CreateSlotSelectionMenuEntry[];
extern char g_gfx_BlinkVideoUnlessBypassedEntry[];
extern char g_initial_ToggleMenuRowOptionEntry[];
extern char g_menu_BeginSelectionMenuExitEntry[];
extern char g_menu_ConsumeSelectionMenuEventEntry[];
extern char g_menu_DrawMenuBlockModelEntry[];
extern char g_menu_HandleNextProfileEventEntry[];
extern char g_menu_PositionSelectionMenuModelEntry[];
extern char g_node_DestroyGridListEntry[];
extern char g_node_SelectNextGridColumnEntry[];
extern char g_node_SelectNextGridRowEntry[];
extern char g_node_SelectPreviousGridColumnEntry[];
extern char g_node_SelectPreviousGridRowEntry[];
extern char g_smpButton_DestroyButtonControllerEntry[];
extern char g_smpButton_DestroyListControllerEntry[];
extern char g_smpButton_DimButtonItemsEntry[];
extern char g_smpButton_DimButtonItemsWithSoundEntry[];
extern char g_smpButton_DimListItemsEntry[];
extern char g_smpButton_DimListItemsWithSoundEntry[];
extern char g_smpButton_HighlightButtonItemsEntry[];
extern char g_smpButton_HighlightListItemsEntry[];
extern char g_smpButton_SelectNextListEntryEntry[];
extern char g_smpButton_SelectPreviousListEntryEntry[];
extern char g_smpFlicker_DestroyControllerEntry[];
extern char g_smpFlicker_UpdateFlickerEntry[];
extern char g_smpFrameAnim_DestroyControllerEntry[];
extern char g_smpFrameAnim_UpdateFrameSequenceEntry[];
extern char g_smpList_HandleDecrementInputEntry[];
extern char g_smpList_HandleIncrementInputEntry[];
extern char g_smpList_HandleStopEventEntry[];
extern char g_smpList_ResetEntryCommandsEntry[];
extern char g_smpList_UpdateSliderMotionEntry[];
extern char g_smpOverlay_ConsumePakDialogEventEntry[];
extern char g_smpOverlay_CreatePakDialogEntry[];
extern char g_smpOverlay_DestroyPakDialogEntry[];
extern char addrLow_SmpOverlay_FollowListSlotTarget_de[];
extern char addrLow_SmpOverlay_FollowTextSlotTarget_de[];
extern char addrLow_SmpOverlay_FollowChildSlotTarget_de[];
extern char addrLow_SmpOverlay_FollowOverlaySlotTarget_de[];
extern char g_smpOverlay_ForwardSlotEventEntry[];
extern char g_smpOverlay_FreeEventObjectEntry[];
extern char g_smpOverlay_HandlePakDialogChoiceEntry[];
extern char g_smpOverlay_ReturnUnhandledEventEntry[];
extern char addrLow_SmpOverlay_SelectListWidgets_de[];
extern char g_smpOverlay_TickPakDialogEntry[];
extern char g_smpSlider_DestroyControllerEntry[];
extern char g_smpSlider_DimSliderItemsEntry[];
extern char g_smpSlider_HighlightSliderItemsEntry[];
extern char g_smp_UpdateFadeProgressEntry[];
#endif
extern s32 SmpList_HandleStopEvent(struct SliderStepRecord *object, void *eventKind, u32 event, s32 value);
extern s32 SmpOverlay_ReturnUnhandledPakDialogEvent(void);
/* Runs of empty 4-byte text cells. */

#endif
