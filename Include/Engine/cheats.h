#ifndef ENGINE_CHEATS_H
#define ENGINE_CHEATS_H
#include "Common/runtime_declarations.h"
#include "Data/Overlays/Portal/linktables_addresses.h"
#include "Data/Overlays/Menu/linktables_addresses.h"
#include "types.h"

#if defined(VERSION_US_REV1)
extern void *g_menuNoLabelSlot[1];
extern char s_shadowsOffText[24];
#endif
#if defined(VERSION_US_REV1)
extern char s_fancyLightingText[24];
#endif
#if defined(VERSION_US_REV1)
extern char s_infiniteAmmoOffText[24];
#endif
#if defined(VERSION_US_REV1)
extern char s_lodChgDistText[24];
#endif
#if defined(VERSION_US_REV1)
extern char s_infiniteAmmoText[24];
#endif
#if defined(VERSION_US_REV1)
extern char s_editLightText[12];
#endif
#if defined(VERSION_US_REV1)
extern char s_globalScalerText[24];
#endif
#if defined(VERSION_US_REV1)
extern char s_weaponHiddenText[24];
#endif
extern char CMenuProfile_AdjustControllerSelection_PagedAddress[];
extern char CMenuProfile_BindSelectedDebugField_PagedAddress[];
extern char CMenuProfile_EnableControllerPakAndClearState_PagedAddress[];
extern char CMenuProfile_EnableOwnerControllerPak_PagedAddress[];
extern char CMenuProfile_FormatProfileQuantityLabel_PagedAddress[];
extern char CMenuProfile_HasDialogRoundProgress_PagedAddress[];
extern char CMenuProfile_HasProfileRoundProgress_PagedAddress[];
extern char CMenuProfile_HasRoundProgress_PagedAddress[];
extern char CMenuProfile_HasSavedRoundProgress_PagedAddress[];
extern char CMenuProfile_OpenAlternatePlayerDialog_PagedAddress[];
extern char CMenuProfile_OpenPrimaryPlayerDialog_PagedAddress[];
extern char CMenuProfile_OpenTimedPlayerDialog_PagedAddress[];
extern char CMenuProfile_ResetPlayerControllerProfile_PagedAddress[];
extern char CMenuProfile_SelectLabelAfterModeToggle_PagedAddress[];
extern char CMenuProfile_SelectLeadLabelItem_PagedAddress[];
extern char CMenuProfile_ToggleProfileMode_PagedAddress[];
extern char CMenuProfile_UpdatePlayerAnimationChoice_PagedAddress[];
extern char CMenuProfile_UpdatePlayerModelItem_PagedAddress[];
extern char CMenuProfile_UpdateProfileModeLabel_PagedAddress[];
extern char CMenuProfile_UpdateTimedPlayerDialogItem_PagedAddress[];
extern char Frontend_SelectPakActionLabel_PagedAddress[];
extern char Frontend_SelectPakConfirmationLabel_PagedAddress[];
extern char Frontend_SelectPakOperationTextFive_PagedAddress[];
extern char Frontend_SelectPakOperationTextFour_PagedAddress[];
extern char Frontend_SelectPakOperationTextThree_PagedAddress[];
extern char Frontend_SelectPakOperationTextTwo_PagedAddress[];
extern char Initial_EnableMenuControllerPak_PagedAddress[];
extern char Initial_OpenDialogAfterTimerReset_PagedAddress[];
extern char Initial_OpenDialogWithControllerPak_PagedAddress[];
extern char Initial_OpenLocalPlayerSetup_PagedAddress[];
extern char Initial_OpenTrackPreviewMenu_PagedAddress[];
extern char Initial_ProbeMenuControllerPak_PagedAddress[];
extern char Initial_RequestTransitionWithPakDisabled_PagedAddress[];
extern char Initial_SelectFirstTrailingLabelItem_PagedAddress[];
extern char Initial_SelectInitialController_PagedAddress[];
extern char Initial_SelectMenuRowLabelItem_PagedAddress[];
extern char Initial_SelectSecondTrailingLabelItem_PagedAddress[];
extern char Initial_SelectThirdTrailingLabelItem_PagedAddress[];
extern char Initial_ToggleMenuRowOption_PagedAddress[];
extern char Initial_UpdateMultiplayerAvailability_PagedAddress[];
extern char Menu_DrawMenuModel_PagedAddress[];
extern char Menu_HandleSessionOptionPage_PagedAddress[];
extern char Menu_SelectLabelBeforeSessionOptionPage_PagedAddress[];
extern char Multi_CompleteGameOverDelay_PagedAddress[];
extern char Multi_DecreaseGameOverTimer_PagedAddress[];
extern char Option_DrawFirstTextItem_PagedAddress[];
extern char Option_InitializeThirtyThreeItemDefinition_PagedAddress[];
extern char Option_InitializeTwentyItemDefinition_PagedAddress[];
extern char Option_SelectFirstTextItem_PagedAddress[];
extern char Option_SelectLabelAfterOptionBits_PagedAddress[];
extern char Option_SelectLastLocalizedTextItem_PagedAddress[];
extern char Option_SelectLocalizedTextItem_PagedAddress[];
extern char Option_SelectPenultimateLocalizedTextItem_PagedAddress[];
extern char Option_ToggleOptionInvincibility_PagedAddress[];
extern char Option_ToggleOptionGouraudMode_PagedAddress[];
extern char Option_ToggleOptionJuansCheat_PagedAddress[];
extern char Option_ToggleOptionZachAttackCheat_PagedAddress[];
extern char Option_ToggleOptionAllMap_PagedAddress[];
extern char Option_ToggleOptionBlackout_PagedAddress[];
extern char Option_ToggleOptionFrootyStripes_PagedAddress[];
extern char Option_ToggleOptionInfiniteLives_PagedAddress[];
extern char Option_ToggleOptionAllWeapons_PagedAddress[];
extern char Option_ToggleOptionUnlimitedAmmo_PagedAddress[];
extern char Option_ToggleOptionAllSpecialObjects_PagedAddress[];
extern char Option_ToggleOptionBigHeadMode_PagedAddress[];
extern char Option_ToggleOptionTinyMode_PagedAddress[];
extern char Option_ToggleOptionStickMode_PagedAddress[];
extern char Option_ToggleOptionBigHandsFeetMode_PagedAddress[];
extern char Option_ToggleOptionPenAndInkMode_PagedAddress[];
extern char Option_UpdateFirstTextItem_PagedAddress[];
extern char Option_UpdateLabelAfterLocalizedText_PagedAddress[];
extern char Option_UpdateLabelAfterOptionBits_PagedAddress[];
extern char Option_UpdateOptionInvincibilityItem_PagedAddress[];
extern char Option_UpdateOptionGouraudModeItem_PagedAddress[];
extern char Option_UpdateOptionJuansCheatItem_PagedAddress[];
extern char Option_UpdateOptionZachAttackCheatItem_PagedAddress[];
extern char Option_UpdateOptionAllMapItem_PagedAddress[];
extern char Option_UpdateOptionBlackoutItem_PagedAddress[];
extern char Option_UpdateOptionFrootyStripesItem_PagedAddress[];
extern char Option_UpdateOptionInfiniteLivesItem_PagedAddress[];
extern char Option_UpdateOptionAllWeaponsItem_PagedAddress[];
extern char Option_UpdateOptionUnlimitedAmmoItem_PagedAddress[];
extern char Option_UpdateOptionAllSpecialObjectsItem_PagedAddress[];
extern char Option_UpdateOptionBigHeadModeItem_PagedAddress[];
extern char Option_UpdateOptionTinyModeItem_PagedAddress[];
extern char Option_UpdateOptionStickModeItem_PagedAddress[];
extern char Option_UpdateOptionBigHandsFeetModeItem_PagedAddress[];
extern char Option_UpdateOptionPenAndInkModeItem_PagedAddress[];
extern char Pak_CancelPakAction_PagedAddress[];
extern char Pak_CheckOperationPakChange_PagedAddress[];
extern char Pak_CheckPakActionChange_PagedAddress[];
extern char Pak_ClosePromptByKind_PagedAddress[];
extern char Pak_ConfirmPendingOperation_PagedAddress[];
extern char Pak_ConfirmProfileOrDeleteNote_PagedAddress[];
extern char Pak_DisableOperationHeading_PagedAddress[];
extern char Pak_EnableOperationHeading_PagedAddress[];
extern char Pak_FormatOperationChannelLabel_PagedAddress[];
extern char Pak_FormatPreviewFourDigitValue_PagedAddress[];
extern char Pak_OpenPakChannel_PagedAddress[];
extern char Pak_OpenPakStatusPrompt_PagedAddress[];
extern char Pak_OpenProfileActionPrompt_PagedAddress[];
extern char Pak_SelectModalPromptLabel_PagedAddress[];
extern char Pak_SelectOperationDescription_PagedAddress[];
extern char Pak_SelectOperationHeading_PagedAddress[];
extern char Pak_SelectPakLoadHeading_PagedAddress[];
extern char Pak_SelectPakOperationFour_PagedAddress[];
extern char Pak_SelectPakOperationOne_PagedAddress[];
extern char Pak_SelectPakOperationTextOne_PagedAddress[];
extern char Pak_SelectPakOperationThree_PagedAddress[];
extern char Pak_SelectPakOperationTwo_PagedAddress[];
extern char Pak_SelectPakOperationZero_PagedAddress[];
extern char Pak_SelectPromptActionHeading_PagedAddress[];
extern char Pak_SelectPromptKindEight_PagedAddress[];
extern char Pak_SelectPromptKindEleven_PagedAddress[];
extern char Pak_SelectPromptKindFifteen_PagedAddress[];
extern char Pak_SelectPromptKindFive_PagedAddress[];
extern char Pak_SelectPromptKindFour_PagedAddress[];
extern char Pak_SelectPromptKindFourteen_PagedAddress[];
extern char Pak_SelectPromptKindNinePending_PagedAddress[];
extern char Pak_SelectPromptKindNine_PagedAddress[];
extern char Pak_SelectPromptKindOne_PagedAddress[];
extern char Pak_SelectPromptKindSeven_PagedAddress[];
extern char Pak_SelectPromptKindSix_PagedAddress[];
extern char Pak_SelectPromptKindTen_PagedAddress[];
extern char Pak_SelectPromptKindThirteen_PagedAddress[];
extern char Pak_SelectPromptKindThree_PagedAddress[];
extern char Pak_SelectPromptKindTwelve_PagedAddress[];
extern char Pak_SelectPromptKindTwo_PagedAddress[];
extern char Pak_SelectPromptKindZero_PagedAddress[];
extern char Pak_SelectPromptTextGroupFive_PagedAddress[];
extern char Pak_SelectPromptTextGroupFour_PagedAddress[];
extern char Pak_SelectPromptTextGroupOne_PagedAddress[];
extern char Pak_SelectPromptTextGroupThree_PagedAddress[];
extern char Pak_SelectPromptTextGroupTwo_PagedAddress[];
extern char Pak_UpdateProfileActionLabel_PagedAddress[];
extern char Snapshot_BeginBlockLoad_PagedAddress[];
extern char Snapshot_BeginProfileLoad_PagedAddress[];
extern char Snapshot_BeginProfileSave_PagedAddress[];
extern char Snapshot_BeginSnapshotSave_PagedAddress[];
extern char Snapshot_CheckControllerPak_PagedAddress[];
extern char Snapshot_CloseNoteBrowser_PagedAddress[];
extern char Snapshot_HandleMenuAction_PagedAddress[];
extern char Snapshot_UpdateScoreTitle_PagedAddress[];
extern char Snapshot_UpdateSpaceLabel_PagedAddress[];
extern char Status_FormatRightAlignedPreviewName_PagedAddress[];
extern char Status_UpdateStatusText_PagedAddress[];
extern char Timer_CancelPendingOperation_PagedAddress[];
extern char Timer_CheckChangedMenuChannel_PagedAddress[];
extern char Timer_CheckMenuPakChange_PagedAddress[];
extern char Timer_ClearProfilePreview_PagedAddress[];
extern char Timer_DisableAlternatePrompt_PagedAddress[];
extern char Timer_DisablePreviewSelection_PagedAddress[];
extern char Timer_DispatchPreviewHandle_PagedAddress[];
extern char Timer_EnableAlternatePrompt_PagedAddress[];
extern char Timer_EnableProfilePreview_PagedAddress[];
extern char Timer_FormatPreviewDottedTriple_PagedAddress[];
extern char Timer_FormatPreviewPageCount_PagedAddress[];
extern char Timer_FormatPreviewValue_PagedAddress[];
extern char Timer_OpenSelectedPrompt_PagedAddress[];
extern char Timer_SetManagerHeading_PagedAddress[];
extern char Timer_UpdateAlternateActionLabel_PagedAddress[];
extern char Timer_UpdateAlternatePromptLabel_PagedAddress[];
extern char Timer_UpdateManagerChannelLabel_PagedAddress[];
extern char Timer_UpdateManagerStatus_PagedAddress[];
extern char Timer_UpdatePreviewDepthLabel_PagedAddress[];
extern char Timer_UpdatePreviewKindLabel_PagedAddress[];
extern char g_menuPaged_Menu_DrawLocalizedMenuItemText[];
extern char g_menuPaged_Menu_DrawMenuEntries[];
extern char g_menuPaged_Menu_DrawMenuItemLabel[];
extern char g_menuPaged_Menu_DrawMenuOptionSprite[];
extern char g_menuPaged_Menu_TryCreateMenu[];
extern char g_menuPaged_Snapshot_SelectNote[];
extern char g_menuPaged_Snapshot_UpdateNoteLabel[];
#include "Data/Overlays/Credits/objectdata_addresses.h"
extern char g_pakStatusLabelTemplate[];
extern char g_SelectModalPromptLabelStateOtherText[];
extern unsigned int k_GfxGetnormalizedcounterData[84];
extern char g_residentTextFragmentB[];
extern char g_pakPreviewKindLabelProfile[];
extern char g_residentTextStorageB[];
extern void *g_GfxGetnormalizedcounterData[1];
extern char g_pakConfirmationDefaultLabel[];
extern char g_menuOptionFrootyStripesDisabledText[];
extern char g_menuOptionStickModeDisabledText[];
extern char g_menuOptionInfiniteLivesDisabledText[];
extern char g_menuOptionUnlimitedAmmoDisabledText[];
extern char g_menuOptionAllSpecialObjectsDisabledText[];
extern char g_menuOptionZachAttackCheatDisabledText[];
extern char g_menuOptionGouraudModeDisabledText[];
extern char g_menuOptionPenAndInkModeDisabledText[];
extern char g_residentTextFragmentA[];
extern void *k_cheatMenuTextCells[];
extern void *k_menuDigitLabelPointers[];
extern struct KeyboardKeyLabelWordsLayout g_keyboardKeyLabel;
extern char g_residentTextStorageA[];
extern char g_profileModeZeroLabel[];
extern char s_nodeDefaultFieldText[];
extern void *g_inventoryLabelSlot[];
extern char g_pakAlternateActionLabel[];
extern char g_menuOptionJuansCheatDisabledText[];
extern char g_menuOptionBigHeadModeDisabledText[];
extern char g_menuOptionBigHandsFeetModeDisabledText[];
extern char g_menuOptionTinyModeDisabledText[];
extern char g_menuOptionAllWeaponsDisabledText[];
extern char g_menuOptionBlackoutDisabledText[];
extern char g_menuOptionInvincibilityDisabledText[];
extern char g_menuOptionAllMapDisabledText[];
#endif
