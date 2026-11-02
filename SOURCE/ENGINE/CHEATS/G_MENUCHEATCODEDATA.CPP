#include "SYSTEM/ENGINE_DATA_SOURCE.H"
#include "MENU/BUILD/DEFINITION_DATA.H"

#if defined(VERSION_US_REV1)
extern char Snapshot_BeginProfileSave_PagedAddress[];
extern char Snapshot_BeginProfileLoad_PagedAddress[];
extern char Snapshot_CheckControllerPak_PagedAddress[];
extern char Snapshot_BeginSnapshotSave_PagedAddress[];
extern char Snapshot_BeginBlockLoad_PagedAddress[];
extern char g_menuPaged_Snapshot_SelectNote[];
extern char g_menuPaged_Snapshot_UpdateNoteLabel[];
extern char Snapshot_UpdateSpaceLabel_PagedAddress[];
extern char Snapshot_HandleMenuAction_PagedAddress[];
extern char Snapshot_CloseNoteBrowser_PagedAddress[];
extern char Snapshot_UpdateScoreTitle_PagedAddress[];
extern char Pak_ConfirmProfileOrDeleteNote_PagedAddress[];
extern char Pak_ClosePromptByKind_PagedAddress[];
extern char Pak_ConfirmPendingOperation_PagedAddress[];
extern char Timer_CancelPendingOperation_PagedAddress[];
extern char Timer_CheckMenuPakChange_PagedAddress[];
extern char Timer_CheckChangedMenuChannel_PagedAddress[];
extern char Timer_UpdateManagerStatus_PagedAddress[];
extern char Timer_UpdateManagerChannelLabel_PagedAddress[];
extern char Timer_SetManagerHeading_PagedAddress[];
extern char Timer_EnableAlternatePrompt_PagedAddress[];
extern char Timer_DisableAlternatePrompt_PagedAddress[];
extern char Timer_UpdateAlternatePromptLabel_PagedAddress[];
extern char Timer_UpdatePreviewDepthLabel_PagedAddress[];
extern char Timer_FormatPreviewPageCount_PagedAddress[];
extern char Timer_FormatPreviewValue_PagedAddress[];
extern char Timer_DispatchPreviewHandle_PagedAddress[];
extern char Timer_FormatPreviewDottedTriple_PagedAddress[];
extern char Timer_UpdateAlternateActionLabel_PagedAddress[];
extern char Timer_OpenSelectedPrompt_PagedAddress[];
extern char Timer_EnableProfilePreview_PagedAddress[];
extern char Timer_ClearProfilePreview_PagedAddress[];
extern char Timer_DisablePreviewSelection_PagedAddress[];
extern char Timer_UpdatePreviewKindLabel_PagedAddress[];
extern char Status_FormatRightAlignedPreviewName_PagedAddress[];
extern char Status_UpdateStatusText_PagedAddress[];
extern char Pak_FormatPreviewFourDigitValue_PagedAddress[];
extern char Pak_UpdateProfileActionLabel_PagedAddress[];
extern char Pak_OpenProfileActionPrompt_PagedAddress[];
extern char Pak_SelectPromptKindZero_PagedAddress[];
extern char Pak_SelectPromptKindOne_PagedAddress[];
extern char Pak_SelectPromptKindTwo_PagedAddress[];
extern char Pak_SelectPromptKindThree_PagedAddress[];
extern char Pak_SelectPromptKindFour_PagedAddress[];
extern char Pak_SelectPromptKindFive_PagedAddress[];
extern char Pak_SelectPromptKindSix_PagedAddress[];
extern char Pak_SelectPromptKindSeven_PagedAddress[];
extern char Pak_SelectPromptKindEight_PagedAddress[];
extern char Pak_SelectPromptKindNine_PagedAddress[];
extern char Pak_SelectPromptKindNinePending_PagedAddress[];
extern char Pak_SelectPromptKindTen_PagedAddress[];
extern char Pak_SelectPromptKindEleven_PagedAddress[];
extern char Pak_SelectPromptKindTwelve_PagedAddress[];
extern char Pak_SelectPromptKindThirteen_PagedAddress[];
extern char Pak_SelectPromptKindFourteen_PagedAddress[];
extern char Pak_SelectPromptKindFifteen_PagedAddress[];
extern char Pak_SelectPromptActionHeading_PagedAddress[];
extern char Pak_SelectPromptTextGroupOne_PagedAddress[];
extern char Pak_SelectPromptTextGroupTwo_PagedAddress[];
extern char Pak_SelectPromptTextGroupThree_PagedAddress[];
extern char Pak_SelectPromptTextGroupFour_PagedAddress[];
extern char Pak_SelectPromptTextGroupFive_PagedAddress[];
extern char Pak_SelectModalPromptLabel_PagedAddress[];
extern char Pak_CheckOperationPakChange_PagedAddress[];
extern char Pak_EnableOperationHeading_PagedAddress[];
extern char Pak_DisableOperationHeading_PagedAddress[];
extern char Pak_SelectOperationHeading_PagedAddress[];
extern char Pak_SelectOperationDescription_PagedAddress[];
extern char Pak_FormatOperationChannelLabel_PagedAddress[];
extern char Pak_OpenPakChannel_PagedAddress[];
extern char Pak_OpenPakStatusPrompt_PagedAddress[];
extern char Pak_CancelPakAction_PagedAddress[];
extern char Pak_SelectPakLoadHeading_PagedAddress[];
extern char Pak_CheckPakActionChange_PagedAddress[];
extern char Pak_SelectPakOperationZero_PagedAddress[];
extern char Pak_SelectPakOperationOne_PagedAddress[];
extern char Pak_SelectPakOperationTwo_PagedAddress[];
extern char Pak_SelectPakOperationThree_PagedAddress[];
extern char Pak_SelectPakOperationFour_PagedAddress[];
extern char Pak_SelectPakOperationTextOne_PagedAddress[];
extern char Frontend_SelectPakOperationTextTwo_PagedAddress[];
extern char Frontend_SelectPakOperationTextThree_PagedAddress[];
extern char Frontend_SelectPakOperationTextFour_PagedAddress[];
extern char Frontend_SelectPakOperationTextFive_PagedAddress[];
extern char Frontend_SelectPakConfirmationLabel_PagedAddress[];
extern char Frontend_SelectPakActionLabel_PagedAddress[];
extern char Option_InitializeTwentyItemDefinition_PagedAddress[];
extern char Option_SelectLabelAfterOptionBits_PagedAddress[];
extern char Option_InitializeThirtyThreeItemDefinition_PagedAddress[];
extern char Option_DrawFirstTextItem_PagedAddress[];
extern char Option_UpdateFirstTextItem_PagedAddress[];
extern char Option_SelectFirstTextItem_PagedAddress[];
extern char Option_SelectLocalizedTextItem_PagedAddress[];
extern char Option_SelectPenultimateLocalizedTextItem_PagedAddress[];
extern char Option_SelectLastLocalizedTextItem_PagedAddress[];
extern char Option_UpdateLabelAfterLocalizedText_PagedAddress[];
extern char Option_UpdateLabelAfterOptionBits_PagedAddress[];
extern char Option_ToggleOptionBit0_PagedAddress[];
extern char Option_UpdateOptionBit0Item_PagedAddress[];
extern char Option_ToggleOptionBit1_PagedAddress[];
extern char Option_UpdateOptionBit1Item_PagedAddress[];
extern char Option_ToggleOptionBit2_PagedAddress[];
extern char Option_UpdateOptionBit2Item_PagedAddress[];
extern char Option_ToggleOptionBit3_PagedAddress[];
extern char Option_UpdateOptionBit3Item_PagedAddress[];
extern char Option_ToggleOptionBit4_PagedAddress[];
extern char Option_UpdateOptionBit4Item_PagedAddress[];
extern char Option_ToggleOptionBit5_PagedAddress[];
extern char Option_UpdateOptionBit5Item_PagedAddress[];
extern char Option_ToggleOptionBit6_PagedAddress[];
extern char Option_UpdateOptionBit6Item_PagedAddress[];
extern char Option_ToggleOptionBit7_PagedAddress[];
extern char Option_UpdateOptionBit7Item_PagedAddress[];
extern char Option_ToggleOptionBit8_PagedAddress[];
extern char Option_UpdateOptionBit8Item_PagedAddress[];
extern char Option_ToggleOptionBit9_PagedAddress[];
extern char Option_UpdateOptionBit9Item_PagedAddress[];
extern char Option_ToggleOptionBit10_PagedAddress[];
extern char Option_UpdateOptionBit10Item_PagedAddress[];
extern char Option_ToggleOptionBit11_PagedAddress[];
extern char Option_UpdateOptionBit11Item_PagedAddress[];
extern char Option_ToggleOptionBit12_PagedAddress[];
extern char Option_UpdateOptionBit12Item_PagedAddress[];
extern char Option_ToggleOptionBit13_PagedAddress[];
extern char Option_UpdateOptionBit13Item_PagedAddress[];
extern char Option_ToggleOptionBit14_PagedAddress[];
extern char Option_UpdateOptionBit14Item_PagedAddress[];
extern char Option_ToggleOptionBit15_PagedAddress[];
extern char Option_UpdateOptionBit15Item_PagedAddress[];
extern char Menu_SelectLabelBeforeSessionOptionPage_PagedAddress[];
extern char Menu_HandleSessionOptionPage_PagedAddress[];
extern char CMenuProfile_HasRoundProgress_PagedAddress[];
extern char CMenuProfile_ResetPlayerControllerProfile_PagedAddress[];
extern char CMenuProfile_HasSavedRoundProgress_PagedAddress[];
extern char CMenuProfile_AdjustControllerSelection_PagedAddress[];
extern char CMenuProfile_FormatProfileQuantityLabel_PagedAddress[];
extern char CMenuProfile_ToggleProfileMode_PagedAddress[];
extern char CMenuProfile_SelectLeadLabelItem_PagedAddress[];
extern char CMenuProfile_BindSelectedDebugField_PagedAddress[];
extern char CMenuProfile_SelectLabelAfterModeToggle_PagedAddress[];
extern char CMenuProfile_UpdateProfileModeLabel_PagedAddress[];
extern char CMenuProfile_EnableOwnerControllerPak_PagedAddress[];
extern char CMenuProfile_EnableControllerPakAndClearState_PagedAddress[];
extern char CMenuProfile_HasProfileRoundProgress_PagedAddress[];
extern char CMenuProfile_OpenTimedPlayerDialog_PagedAddress[];
extern char CMenuProfile_UpdateTimedPlayerDialogItem_PagedAddress[];
extern char CMenuProfile_UpdatePlayerModelItem_PagedAddress[];
extern char CMenuProfile_HasDialogRoundProgress_PagedAddress[];
extern char CMenuProfile_OpenPrimaryPlayerDialog_PagedAddress[];
extern char CMenuProfile_OpenAlternatePlayerDialog_PagedAddress[];
extern char Initial_ToggleMenuRowOption_PagedAddress[];
extern char Initial_SelectMenuRowLabelItem_PagedAddress[];
extern char Initial_ProbeMenuControllerPak_PagedAddress[];
extern char Initial_EnableMenuControllerPak_PagedAddress[];
extern char Initial_OpenDialogWithControllerPak_PagedAddress[];
extern char Initial_OpenDialogAfterTimerReset_PagedAddress[];
extern char Initial_RequestTransitionWithPakDisabled_PagedAddress[];
extern char Initial_SelectInitialController_PagedAddress[];
extern char Initial_UpdateMultiplayerAvailability_PagedAddress[];
extern char Initial_OpenLocalPlayerSetup_PagedAddress[];
extern char Initial_SelectThirdTrailingLabelItem_PagedAddress[];
extern char Initial_SelectFirstTrailingLabelItem_PagedAddress[];
extern char Initial_SelectSecondTrailingLabelItem_PagedAddress[];
extern char Initial_OpenTrackPreviewMenu_PagedAddress[];
extern char Multi_CompleteGameOverDelay_PagedAddress[];
extern char Multi_DecreaseGameOverTimer_PagedAddress[];
extern char CMenuProfile_UpdatePlayerAnimationChoice_PagedAddress[];
extern char g_menuPaged_Menu_DrawMenuOptionSprite[];
extern char Menu_DrawMenuModel_PagedAddress[];
extern char g_menuPaged_Menu_DrawMenuEntries[];
extern char g_menuPaged_Menu_DrawMenuItemLabel[];
extern char g_menuPaged_Menu_DrawLocalizedMenuItemText[];
extern char g_menuPaged_Menu_TryCreateMenu[];

struct {
    unsigned int parameter1;
    struct MenuBuildItemData items1[1];
    short type1;
    unsigned short reserved021;
    unsigned int flags1;
    short x1;
    short y1;
    unsigned char red1;
    unsigned char green1;
    unsigned char blue1;
    unsigned char alpha1;
    int resource1;
    unsigned int resourceCallback1;
    unsigned int callback1;
    unsigned int initializeCallback1;
} g_menuItemFragment12 = {
    0x00000000,
    {
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7738, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel, (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
    },
    0x0000,
    0x0000,
    0x00011001,
    0x0000,
    0x0000,
    0x00,
    0x00,
    0xFF,
    0x01,
    0x800D773C,
    (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel,
    (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel,
    (unsigned int)g_menuPaged_Snapshot_SelectNote,
};

struct {
    unsigned int parameter1;
    struct MenuBuildItemData items1[8];
    struct MenuBuildDefinitionData definitions1[5];
    struct MenuBuildItemData items2[10];
    struct MenuBuildDefinitionData definitions2[2];
    struct MenuBuildItemData items3[9];
    struct MenuBuildDefinitionData definitions3[3];
    struct MenuBuildItemData items4[8];
    struct MenuBuildDefinitionData definitions4[17];
    struct MenuBuildItemData items5[8];
    struct MenuBuildDefinitionData definitions5[2];
    struct MenuBuildItemData items6[8];
    struct MenuBuildDefinitionData definitions6[5];
} g_menuPakOptionsData = {
    0x00000000,
    {
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7740, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel, (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7744, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel, (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7748, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel, (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D774C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel, (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7750, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel, (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0003, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Snapshot_UpdateSpaceLabel_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_UpdateManagerChannelLabel_PagedAddress, (unsigned int)Snapshot_HandleMenuAction_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, 0x800D7778, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_SetManagerHeading_PagedAddress, (unsigned int)Snapshot_CloseNoteBrowser_PagedAddress, 0x00000000 },
    },
    {
        { 0x0044EDA0, 0x0016, 0x0000, (unsigned int)Snapshot_BeginProfileLoad_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Timer_CheckMenuPakChange_PagedAddress, 0x0015, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044EDA0, 0x0016, 0x0000, (unsigned int)Snapshot_BeginProfileSave_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Timer_CheckMenuPakChange_PagedAddress, 0x0014, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044EDA0, 0x0016, 0x0000, (unsigned int)Snapshot_BeginBlockLoad_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Timer_CheckChangedMenuChannel_PagedAddress, 0x0015, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044EDA0, 0x0016, 0x0000, (unsigned int)Snapshot_BeginSnapshotSave_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Timer_CheckChangedMenuChannel_PagedAddress, 0x0014, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044EDA0, 0x0016, 0x0000, (unsigned int)Snapshot_CheckControllerPak_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Timer_UpdateManagerStatus_PagedAddress, 0x0014, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800D77CC, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_UpdateAlternatePromptLabel_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_DispatchPreviewHandle_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, 0x800D77E8, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_FormatPreviewDottedTriple_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_UpdatePreviewDepthLabel_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D77E0, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_FormatPreviewPageCount_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D77E4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_FormatPreviewValue_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, 0x800D7810, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_UpdateAlternateActionLabel_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010040, 0x007D, 0x000A, 0x00, 0x01, 0x00, 0x00, 0x800D7A90, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00408870, 0x00000000 },
        { 0x0000, 0x0000, 0x00024040, 0x000A, 0x0000, 0xFF, 0x00, 0x00, 0x00, 0x800D7A94, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Timer_OpenSelectedPrompt_PagedAddress, 0x00000000 },
    },
    {
        { 0x0044F16C, 0x000A, 0x0000, (unsigned int)Timer_EnableAlternatePrompt_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0008, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F16C, 0x000A, 0x0000, (unsigned int)Timer_DisableAlternatePrompt_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0009, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800D77EC, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_UpdatePreviewKindLabel_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0032, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Status_FormatRightAlignedPreviewName_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, 0x800D7804, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Status_UpdateStatusText_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, 0x800D7808, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_FormatPreviewFourDigitValue_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, 0x800D780C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Snapshot_UpdateScoreTitle_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0010, 0x00, 0x00, 0xFF, 0x01, 0x800D7810, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_UpdateProfileActionLabel_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010040, 0x007D, 0x000A, 0x00, 0x01, 0x00, 0x00, 0x800D7A90, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Pak_ConfirmProfileOrDeleteNote_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024040, 0x000A, 0x0000, 0xFF, 0x00, 0x00, 0x00, 0x800D7A94, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Pak_OpenProfileActionPrompt_PagedAddress, 0x00000000 },
    },
    {
        { 0x0044F31C, 0x0009, 0x0000, (unsigned int)Timer_EnableProfilePreview_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F31C, 0x0009, 0x0000, (unsigned int)Timer_ClearProfilePreview_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0008, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F31C, 0x0009, 0x0000, (unsigned int)Timer_DisablePreviewSelection_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0008, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectPromptActionHeading_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectPromptTextGroupOne_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectPromptTextGroupTwo_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectPromptTextGroupThree_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectPromptTextGroupFour_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectPromptTextGroupFive_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0019, 0x00, 0x00, 0xFF, 0x01, 0x800D7824, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectModalPromptLabel_PagedAddress, (unsigned int)Pak_ClosePromptByKind_PagedAddress, 0x00000000 },
    },
    {
        { 0x0044F4CC, 0x0008, 0x0000, (unsigned int)Pak_SelectPromptKindZero_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F4CC, 0x0008, 0x0000, (unsigned int)Pak_SelectPromptKindOne_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F4CC, 0x0008, 0x0000, (unsigned int)Pak_SelectPromptKindTwo_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F4CC, 0x0008, 0x0000, (unsigned int)Pak_SelectPromptKindThree_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F4CC, 0x0008, 0x0000, (unsigned int)Pak_SelectPromptKindFour_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F4CC, 0x0008, 0x0000, (unsigned int)Pak_SelectPromptKindFive_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F4CC, 0x0008, 0x0000, (unsigned int)Pak_SelectPromptKindSix_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F4CC, 0x0008, 0x0000, (unsigned int)Pak_SelectPromptKindSeven_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F4CC, 0x0008, 0x0000, (unsigned int)Pak_SelectPromptKindEight_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F4CC, 0x0008, 0x0000, (unsigned int)Pak_SelectPromptKindNine_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F4CC, 0x0008, 0x0000, (unsigned int)Pak_SelectPromptKindNinePending_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F4CC, 0x0008, 0x0000, (unsigned int)Pak_SelectPromptKindTen_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F4CC, 0x0008, 0x0000, (unsigned int)Pak_SelectPromptKindEleven_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F4CC, 0x0008, 0x0000, (unsigned int)Pak_SelectPromptKindTwelve_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F4CC, 0x0008, 0x0000, (unsigned int)Pak_SelectPromptKindFifteen_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F4CC, 0x0008, 0x0000, (unsigned int)Pak_SelectPromptKindThirteen_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F4CC, 0x0008, 0x0000, (unsigned int)Pak_SelectPromptKindFourteen_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800D796C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectOperationHeading_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectOperationDescription_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_FormatOperationChannelLabel_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, 0x800D7988, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Pak_OpenPakChannel_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, 0x800D798C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Pak_OpenPakStatusPrompt_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectPakLoadHeading_PagedAddress, (unsigned int)Pak_CancelPakAction_PagedAddress, 0x00000000 },
    },
    {
        { 0x0044F850, 0x0008, 0x0000, (unsigned int)Pak_EnableOperationHeading_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Pak_CheckOperationPakChange_PagedAddress, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F850, 0x0008, 0x0000, (unsigned int)Pak_DisableOperationHeading_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Pak_CheckOperationPakChange_PagedAddress, 0x0005, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectPakOperationTextOne_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0023, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Frontend_SelectPakOperationTextTwo_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Frontend_SelectPakOperationTextThree_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Frontend_SelectPakOperationTextFour_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Frontend_SelectPakOperationTextFive_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00012001, 0x0000, 0x0023, 0x00, 0x00, 0xFF, 0x01, 0x800D7A08, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Frontend_SelectPakConfirmationLabel_PagedAddress, (unsigned int)Pak_ConfirmPendingOperation_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00012001, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, 0x800D7A0C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Frontend_SelectPakActionLabel_PagedAddress, (unsigned int)Timer_CancelPendingOperation_PagedAddress, 0x00000000 },
    },
    {
        { 0x0044F9B8, 0x0008, 0x0000, (unsigned int)Pak_SelectPakOperationZero_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Pak_CheckPakActionChange_PagedAddress, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F9B8, 0x0008, 0x0000, (unsigned int)Pak_SelectPakOperationOne_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Pak_CheckPakActionChange_PagedAddress, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F9B8, 0x0008, 0x0000, (unsigned int)Pak_SelectPakOperationTwo_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Pak_CheckPakActionChange_PagedAddress, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F9B8, 0x0008, 0x0000, (unsigned int)Pak_SelectPakOperationThree_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Pak_CheckPakActionChange_PagedAddress, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F9B8, 0x0008, 0x0000, (unsigned int)Pak_SelectPakOperationFour_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Pak_CheckPakActionChange_PagedAddress, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
};

/* Alignment fill to the next 16-byte object boundary. */
unsigned int g_GMenucheatcodedataEncodedWordsBlock2AlignmentPad[1] = { 0x00010201 };

struct MenuCheatCodeData g_menuCheatCodeData[12] = {
    { 0x800E21AC, 0x800D7AE0, 0x00000020, 0x00000001 },
    { 0x800E219C, 0x800D7AE8, 0x00000080, 0x00000001 },
    { 0x800E2194, 0x800D7AEC, 0x00000100, 0x00000001 },
    { 0x800E2188, 0x800D7AE4, 0x00000040, 0x00000001 },
    { 0x800E217C, 0x800D7AF0, 0x00000200, 0x00000001 },
    { 0x800E2168, 0x800D7AF4, 0x00000400, 0x00000001 },
    { 0x800E215C, 0x800D7AF8, 0x00000800, 0x00000001 },
    { 0x800E2154, 0x800D7AFC, 0x00001000, 0x00000001 },
    { 0x800E2148, 0x800D7B04, 0x00004000, 0x00000001 },
    { 0x800E213C, 0x800D7B08, 0x00008000, 0x00000001 },
    { 0x800E2124, 0x800E5CDC, 0xFFFFFFFF, 0x00000001 },
    { 0x800E2110, 0x800E5CF8, 0x0400C7E0, 0x00000001 },
};

struct {
    struct MenuBuildItemData items1[33];
    struct MenuBuildDefinitionData definitions1[1];
    struct MenuBuildItemData items2[20];
    struct MenuBuildDefinitionData definitions2[1];
} g_menuPakOptionsDataPart3 = {
    {
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800D7AA4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00210041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, 0x800E5CC4, (unsigned int)Option_DrawFirstTextItem_PagedAddress, (unsigned int)Option_UpdateFirstTextItem_PagedAddress, (unsigned int)Option_SelectFirstTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0014, 0x06, 0x01, 0xFF, 0x07, 0x800D7E48, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFE, 0x07, 0x800D7E50, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFD, 0x07, 0x800D7E58, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFC, 0x07, 0x800D7E60, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFB, 0x07, 0x800D7E68, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFA, 0x07, 0x800D7E70, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, 0x800D7E78, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0008, 0x06, 0x01, 0xF9, 0x07, 0x800D7E80, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, 0x800D7E88, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, 0x800D7E90, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, 0x800D7E98, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, 0x800D7EA0, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, 0x800D7EA8, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, 0x800D7EB0, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0008, 0x06, 0x01, 0xF9, 0x07, 0x800D7EB8, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, 0x800D7EC0, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, 0x800D7EC8, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, 0x800D7ED0, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, 0x800D7ED8, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, 0x800D7EE0, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, 0x800D7EE8, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0008, 0x06, 0x01, 0xF9, 0x08, 0x800D7EF0, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, 0x800D7EF8, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x06, 0x800D7F00, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x05, 0x800D7F08, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x04, 0x800D7F10, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x03, 0x800D7F70, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectPenultimateLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x02, 0x800D7F78, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLastLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0014, 0x00, 0x00, 0x00, 0x00, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateLabelAfterLocalizedText_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00310201, 0x0000, 0x0018, 0x00, 0x00, 0xFE, 0xE2, 0x800D7AB4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Menu_TryCreateMenu, 0x00000000 },
    },
    {
        { 0x0044FC50, 0x0021, 0x0000, (unsigned int)Option_InitializeThirtyThreeItemDefinition_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800D7A98, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, 0x800D7B3C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBit0Item_PagedAddress, (unsigned int)Option_ToggleOptionBit0_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7B44, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBit1Item_PagedAddress, (unsigned int)Option_ToggleOptionBit1_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7B4C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBit2Item_PagedAddress, (unsigned int)Option_ToggleOptionBit2_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7B54, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBit3Item_PagedAddress, (unsigned int)Option_ToggleOptionBit3_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7B5C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBit4Item_PagedAddress, (unsigned int)Option_ToggleOptionBit4_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7B64, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBit5Item_PagedAddress, (unsigned int)Option_ToggleOptionBit5_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7B6C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBit6Item_PagedAddress, (unsigned int)Option_ToggleOptionBit6_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7B7C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBit8Item_PagedAddress, (unsigned int)Option_ToggleOptionBit8_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7B74, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBit7Item_PagedAddress, (unsigned int)Option_ToggleOptionBit7_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7B84, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBit9Item_PagedAddress, (unsigned int)Option_ToggleOptionBit9_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7B8C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBit10Item_PagedAddress, (unsigned int)Option_ToggleOptionBit10_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7B94, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBit11Item_PagedAddress, (unsigned int)Option_ToggleOptionBit11_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7B9C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBit12Item_PagedAddress, (unsigned int)Option_ToggleOptionBit12_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7BA4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBit13Item_PagedAddress, (unsigned int)Option_ToggleOptionBit13_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7BAC, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBit14Item_PagedAddress, (unsigned int)Option_ToggleOptionBit14_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7BB4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBit15Item_PagedAddress, (unsigned int)Option_ToggleOptionBit15_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateLabelAfterOptionBits_PagedAddress, (unsigned int)Option_SelectLabelAfterOptionBits_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00000201, 0x0000, 0x00C0, 0x00, 0x00, 0xFF, 0x01, 0x800D7AB4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Menu_TryCreateMenu, 0x00000000 },
    },
    {
        { 0x00450118, 0x0014, 0x0000, (unsigned int)Option_InitializeTwentyItemDefinition_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0013, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
};

/* Alignment fill to the next 16-byte object boundary. */
unsigned int g_GMenucheatcodedataEncodedWordsBlock3AlignmentPad[1] = {
    0x00000000,
};

struct {
    struct MenuBuildItemData items1[3];
    struct MenuBuildDefinitionData definitions1[1];
    struct MenuBuildItemData items2[8];
    struct MenuBuildDefinitionData definitions2[1];
    struct MenuBuildItemData items3[5];
    struct MenuBuildDefinitionData definitions3[1];
} g_menuPakOptionsDataPart5 = {
    {
        { 0x0000, 0x0000, 0x00000021, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7AB8, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, 0x800D7A90, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Menu_SelectLabelBeforeSessionOptionPage_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7A94, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Menu_HandleSessionOptionPage_PagedAddress, 0x00000000 },
    },
    {
        { 0x00450410, 0x0003, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x800D7698, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x800D769C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x800D76A0, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x800D76A4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x800D76A8, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x800D76AC, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x800D76B0, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0x00, 0x00, 0x800D7694, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)CMenuProfile_ResetPlayerControllerProfile_PagedAddress, 0x00000000 },
    },
    {
        { 0x004504A0, 0x0008, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)CMenuProfile_HasRoundProgress_PagedAddress, 0x0007, 0x0000, 0x0000, 0x0000, 0x00450698 },
    },
    {
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x02, 0x800D7668, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)CMenuProfile_SelectLeadLabelItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0008, 0x00, 0x00, 0x00, 0x00, 0x800D766C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)CMenuProfile_BindSelectedDebugField_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0008, 0x00, 0x00, 0xFE, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)CMenuProfile_FormatProfileQuantityLabel_PagedAddress, (unsigned int)CMenuProfile_AdjustControllerSelection_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, 0x800D7688, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)CMenuProfile_UpdateProfileModeLabel_PagedAddress, (unsigned int)CMenuProfile_ToggleProfileMode_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, 0x800D7694, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)CMenuProfile_SelectLabelAfterModeToggle_PagedAddress, 0x00000000 },
    },
    {
        { 0x004505E4, 0x0005, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)CMenuProfile_HasSavedRoundProgress_PagedAddress, 0x0004, 0x0000, 0x0000, 0x0000, 0x00450758 },
    },
};

EngineMenuModelDefinition g_GMenucheatcodedataEncodedWordsBlock4 = {
    1120, 11, 0,
    { 0.0f, -50.0f, -900.0f }, { 2.0f, 2.0f, 2.0f },
    "\000\000\0002\000\000\000P", 0.087266475f
};

struct {
    struct MenuBuildItemData items1[3];
    struct MenuBuildDefinitionData definitions1[2];
    struct MenuBuildItemData items2[4];
    struct MenuBuildDefinitionData definitions2[1];
} g_menuPakOptionsDataPart7 = {
    {
        { 0x0001, 0x0000, 0x30000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000387, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0003, 0x0000, 0x00410021, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x004506BC, (unsigned int)Menu_DrawMenuModel_PagedAddress, (unsigned int)CMenuProfile_UpdatePlayerModelItem_PagedAddress, (unsigned int)CMenuProfile_UpdatePlayerAnimationChoice_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0019, 0x00, 0x00, 0xFF, 0x01, 0x800D7664, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)CMenuProfile_UpdateTimedPlayerDialogItem_PagedAddress, (unsigned int)CMenuProfile_OpenTimedPlayerDialog_PagedAddress, 0x00000000 },
    },
    {
        { 0x004506EC, 0x0003, 0x0000, (unsigned int)CMenuProfile_EnableOwnerControllerPak_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)CMenuProfile_HasProfileRoundProgress_PagedAddress, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x004506EC, 0x0003, 0x0000, (unsigned int)CMenuProfile_EnableControllerPakAndClearState_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)CMenuProfile_HasProfileRoundProgress_PagedAddress, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0001, 0x0000, 0x30000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000387, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D76B8, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010101, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, 0x800D76BC, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)CMenuProfile_OpenPrimaryPlayerDialog_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D76C0, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)CMenuProfile_OpenAlternatePlayerDialog_PagedAddress, 0x00000000 },
    },
    {
        { 0x004507A0, 0x0004, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)CMenuProfile_HasDialogRoundProgress_PagedAddress, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
};

float g_cheatMenuAnimationStepSamples[16] = {
    -0.5f, -0.4f, -0.3f, -0.2f, -0.1f, 0.0f,
    0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f,
    0.7f, 0.8f, 0.9f, 1.0f,
};

struct {
    struct MenuBuildItemData items1[11];
    struct MenuBuildDefinitionData definitions1[1];
    struct MenuBuildItemData items2[4];
    struct MenuBuildDefinitionData definitions2[1];
    struct MenuBuildItemData items3[5];
    struct MenuBuildDefinitionData definitions3[2];
    struct MenuBuildItemData items4[1];
    struct MenuBuildDefinitionData definitions4[1];
    struct MenuBuildItemData items5[7];
    struct MenuBuildDefinitionData definitions5[1];
} g_menuPakOptionsDataPart9 = {
    {
        { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000201, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, 0x800D7D3C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x0043DD30, (unsigned int)Initial_ToggleMenuRowOption_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x0043DD30, (unsigned int)Initial_ToggleMenuRowOption_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x0043DD30, (unsigned int)Initial_ToggleMenuRowOption_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x0043DD30, (unsigned int)Initial_ToggleMenuRowOption_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x0043DD30, (unsigned int)Initial_ToggleMenuRowOption_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x0043DD30, (unsigned int)Initial_ToggleMenuRowOption_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x0043DD30, (unsigned int)Initial_ToggleMenuRowOption_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x0043DD30, (unsigned int)Initial_ToggleMenuRowOption_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010201, 0x0000, 0x002D, 0x00, 0x00, 0xFF, 0x01, 0x800D7AB4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Menu_TryCreateMenu, 0x00000000 },
    },
    {
        { 0x00450894, 0x000B, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000A, 0x0000, 0x0000, 0x0000, 0x00450AD4 },
    },
    {
        { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800D7C90, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7D3C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Initial_SelectMenuRowLabelItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0038, 0x00, 0x00, 0xFF, 0x01, 0x800D7AB4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Menu_TryCreateMenu, 0x00000000 },
    },
    {
        { 0x00450A44, 0x0004, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00450D38 },
    },
    {
        { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800D7C80, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0036, 0x00, 0x00, 0xFF, 0x01, 0x800D7C84, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Initial_OpenDialogWithControllerPak_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, 0x800D7C88, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Initial_OpenDialogAfterTimerReset_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0049, 0x00, 0x00, 0xFF, 0x01, 0x800D765C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Initial_RequestTransitionWithPakDisabled_PagedAddress, 0x00000000 },
    },
    {
        { 0x00450AF8, 0x0005, 0x0000, (unsigned int)Initial_ProbeMenuControllerPak_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x00450AF8, 0x0005, 0x0000, (unsigned int)Initial_EnableMenuControllerPak_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
    },
    {
        { 0x00450BF4, 0x0001, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00450D38 },
    },
    {
        { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000384, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00000081, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, 0x800D7C80, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Initial_SelectInitialController_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, 0x800D7C8C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Initial_UpdateMultiplayerAvailability_PagedAddress, (unsigned int)Initial_OpenLocalPlayerSetup_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, 0x800D7AA4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Initial_SelectFirstTrailingLabelItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, 0x800D7DA8, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Initial_SelectSecondTrailingLabelItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, 0x800D7DA4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Initial_SelectThirdTrailingLabelItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, 0x800D7DB4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Initial_OpenTrackPreviewMenu_PagedAddress, 0x00000000 },
    },
    {
        { 0x00450C3C, 0x0007, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
};

/* Alignment fill to the next 16-byte object boundary. */
unsigned int g_GMenucheatcodedataEncodedWordsAlignmentPad[1] = {
    0x00000000,
};

struct {
    struct MenuBuildItemData items1[2];
    struct MenuBuildDefinitionData definitions1[1];
} g_menuPakOptionsDataPart11 = {
    {
        { 0x0001, 0x0000, 0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000064, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00000089, 0x0000, 0x0028, 0x00, 0x00, 0x00, 0x00, 0x800D7F80, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Multi_DecreaseGameOverTimer_PagedAddress, 0x00000000, 0x00000000 },
    },
    {
        { 0x00450D60, 0x0002, 0x0000, 0x0043EF20, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Multi_CompleteGameOverDelay_PagedAddress, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
};

/* Alignment fill to the next 16-byte object boundary. */
unsigned int g_GMenucheatcodedataEncodedWordsBlock1AlignmentPad[1] = {
    0x00020000,
};

struct {
    struct MenuBuildItemData items1[3];
    short type1;
    unsigned short reserved021;
    unsigned int flags1;
    short x1;
    short y1;
} g_menuPakOptionsDataPart13 = {
    {
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800D76F8, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0016, 0x00, 0x00, 0x00, 0x00, 0x800D7E1C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
    },
    0x0001,
    0x0000,
    0x00024010,
    0x0003,
    0x0000,
};
#endif
