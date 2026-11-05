#ifndef UI_UI_ADDRESS_SYMBOLS_H
#define UI_UI_ADDRESS_SYMBOLS_H
#include "Menu/Extraoptions/menu_refreshextraoptionlocks_symbols.h"
#include "Common/playerprofiles.h"

/* Addresses of code and data that exist only in the symbol map; each name is
   the address itself, so it is declared as an unsized array and used with &. */

extern char N64Eng_CancelSelectionRepeat_Address[];
extern char N64Eng_FreeNumericWidget_Address[];
extern char N64Eng_HandleNumericDecrement_Address[];
extern char N64Eng_HandleNumericIncrement_Address[];
extern char N64Eng_SetLinkedCommand100WithSound_Address[];
extern char N64Eng_SetLinkedCommand100_Address[];
extern char N64Eng_SetLinkedCommand200_Address[];
extern char TickSelectionRepeat_Address[];
extern char g_Frontend_CancelEquipmentSelectionAddress[];
extern char g_Frontend_ConfirmEquipmentSelectionAddress[];
extern char g_Frontend_FreeEquipmentScreenAddress[];
extern char g_Frontend_RestoreEquipmentSelectionsAddress[];
extern char g_Frontend_SelectNextEquipmentChoiceAddress[];
extern char g_Frontend_SelectNextEquipmentColumnAddress[];
extern char g_Frontend_SelectPreviousEquipmentChoiceAddress[];
extern char g_Frontend_SelectPreviousEquipmentChoicePackedAddress_de_eu_eu_x[];
extern char addrLow_Frontend_SelectPreviousEquipmentChoice2[];
extern char g_Frontend_UpdatePlayerCountScreenAddress[];
extern char addrLow_Menu_UpdatePakActionMenu[];
extern char g_Player_BuildItemLabelListAddress[];
extern char g_Player_CancelAlternatePlayerSettingsEntryAddress[];
extern char g_Player_CancelPlayerSettingsEntryAddress[];
extern char g_Player_ConfirmAlternatePlayerSettingsEntryAddress[];
extern char g_Player_ConfirmPlayerSettingsEntryAddress[];
extern char addrLow_Player_CreateFourPlayerResults[];
extern char addrLow_Player_DrawFourPlayerResults[];
extern char g_Player_FreeAlternatePlayerSettingsScreenAddress[];
extern char g_Player_FreePlayerSettingsScreenAddress[];
extern char g_Player_InitPlayerSettingsScreenAddress[];
extern char g_Player_SelectNextAlternatePlayerSettingsEntryAddress[];
extern char g_Player_SelectNextPlayerSettingsEntryAddress[];
extern char g_Player_SelectPreviousAlternatePlayerSettingsEntryAddress[];
extern char g_Player_SelectPreviousPlayerSettingsEntryAddress[];
extern char addrLow_Player_StartFourPlayerResults[];
extern char addrLow_Player_UpdateFourPlayerResults[];
extern char g_SmpButton_DestroyButtonControllerAddress[];
extern char g_SmpButton_DestroyListControllerAddress[];
extern char g_SmpButton_DimButtonItemsAddress[];
extern char g_SmpButton_DimButtonItemsWithSoundAddress[];
extern char g_SmpButton_DimListItemsAddress[];
extern char g_SmpButton_DimListItemsWithSoundAddress[];
extern char g_SmpButton_HighlightButtonItemsAddress[];
extern char g_SmpButton_HighlightListItemsAddress[];
extern char g_SmpButton_SelectNextListEntryAddress[];
extern char g_SmpButton_SelectPreviousListEntryAddress[];
extern char addrLow_SmpOverlay_FollowListSlotTarget_us[];
extern char addrLow_SmpOverlay_FollowTextSlotTarget_us[];
extern char addrLow_SmpOverlay_FollowChildSlotTarget_us[];
extern char addrLow_SmpOverlay_FollowOverlaySlotTarget_us[];
extern char g_SmpOverlay_ForwardSlotEventAddress[];
extern char g_SmpOverlay_FreeEventObjectAddress[];
extern char g_SmpOverlay_ReturnUnhandledEventAddress[];
extern char addrLow_SmpOverlay_SelectListWidgets_us[];
extern char g_SmpSlider_DimSliderItemsAddress[];
extern char g_alternatePlayerSettingsUnhandledEventCallbackAddress[];
extern char g_alternatePlayerSettingsUnhandledEventCallbackAddressUsRev1Alternate[];
extern char g_cMenuProfile_ResetRoundEndDelayEntry[];
extern char g_frontend_DrawSetupResultPanelsEntry[];
extern char g_menuPaged_Menu_DrawMenuEntries[];
extern char g_menuPaged_Menu_DrawMenuItemLabel[];
extern char g_menuPaged_Menu_DrawMenuOptionSprite[];
extern char g_playerSettingsUnhandledEventCallbackAddress[];
extern char g_selection_HandleCharacterVariantCycleEntry[];
extern char g_tlbMissExceptionVector[];
extern char g_weaponLockedNoticeText[];
extern u8 *g_weaponLockedNoticeTextEuX[];
extern char s_pakAssertTextObject[];
extern char s_pakAssertTextString[];
extern char s_pakDialogNoteCountFormatEuropean[];
extern char s_pakInterfaceInitialModeRange[];
extern char s_pakInterfaceScreenFalse[];
extern char s_pakInterfaceScreenIsNull[];
extern char s_pakInterfaceScreenNameIndexRange[];
extern char s_pakInterfaceScreenNotNull[];
extern char s_pakInterfaceScreenObjectNotNull[];
extern char s_pakInterfaceScreenSourceFile[];
extern char s_pakInterfaceScreenUserInRange[];
extern char s_pakNoteSizeFormatEuropean[];
extern char s_playerSlotsAssertSlotIndex[];
extern char s_playerSlotsSourceFile[];

/* Enabled flag of each pak screen option row, ids 2..8 at [0..6] and id 9 at [8]; nothing names byte [7]. */
extern u8 g_pakScreenOptionRowEnabledFlags[9];
/* Option rows 2..9 of the European pak menu: [row][enabled, disabled][language]. */
extern char *g_europeanMenuToggleRowTexts[8][2][4];
extern void *g_slotEmptyNameByLanguageEu[];
extern void *g_slotEmptyNameByLanguageEuX[];
extern s8 g_profileSlotEnabledFlags[];
extern char *g_pakUnnamedNoteTextsEuX[];
extern void SM_AcknowledgeMsg(void);
extern s32 g_pakInterfaceScreenMode;
extern s32 gnAccessingPak_CurrentMode;
extern s32 gnAccessingPak_CurrentPAK;
extern void MultiTallyScreen_ContinueGame(void);
extern void MultiTallyScreen_CoOpContinueGame(void);
extern void ScenarioTallyScreen_ContinueGame(void);
extern s32 SM_GetJoystickThreshold(void);
extern s32 GetNActive(void);
extern void TSMOS__InputEnable();
extern s32 g_scenarioArenaSelectionTable[];
extern f32 g_scenarioPreviewScale;
extern const unsigned char g_noteCountIntFormat[];
extern u8 g_controllerPakFrontendState;
extern struct CartridgeReadWorker g_cartridgeReadWorker;
#endif
