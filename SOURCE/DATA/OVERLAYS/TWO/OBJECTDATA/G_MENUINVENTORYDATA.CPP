#include "MENU/BUILD/DEFINITION_DATA.H"

#if defined(VERSION_US_REV1)
extern char g_menuPaged_Pak_ToggleTextChoice[];
extern char g_menuPaged_Multi_EmptyItemHook[];
extern char g_menuPaged_Multi_CreateMenuWithDefaultMusicGain[];
extern char g_menuPaged_Menu_DrawMenuOptionSprite[];
extern char g_menuPaged_Menu_DrawLayeredMenuText[];
extern char g_menuPaged_Menu_DrawMenuEntries[];
extern char g_menuPaged_Menu_DrawMenuItemLabel[];
extern char g_menuPaged_Menu_DrawLocalizedMenuItemText[];
extern char g_menuPaged_Menu_TryCreateMenu[];
extern char g_menuPaged_Items_PrepareControllerReturn[];
extern char g_menuPaged_Player_FormatPlayerPartnerStatus[];
extern char g_menuPaged_Player_RespawnItemPlayer[];
extern char g_menuPaged_Player_DrawPulsingMenuSprite[];
extern char g_menuPaged_Player_UpdatePlayerRespawnDelay[];
extern char g_menuPaged_Player_ConfigurePlayerMenuFlags[];
extern char g_menuPaged_Player_ConfigureAndProbeControllerPak[];
extern char g_menuPaged_Player_ConfigureControllerPakMenu[];
extern char g_menuPaged_Items_ResetScreenModeFadeCooldown[];
extern char g_menuPaged_Items_CycleSceneMask[];
extern char g_menuPaged_Items_SelectSceneMaskText[];
extern char g_menuPaged_Items_CacheIdentifierBand[];
extern char g_menuPaged_Items_AdjustPlayerOption7B[];
extern char g_menuPaged_Items_SelectPlayerOption7BText[];
extern char g_menuPaged_Items_AdjustPlayerOption7C[];
extern char g_menuPaged_Items_SelectPlayerOption7CText[];
extern char g_menuPaged_Items_AdjustPlayerOption7D[];
extern char g_menuPaged_Items_SelectPlayerOption7DText[];
extern char g_menuPaged_Items_AdjustPlayerOption7E[];
extern char g_menuPaged_Items_SelectPlayerOption7EText[];
extern char g_menuPaged_Items_AdjustFirstListMode[];
extern char g_menuPaged_Items_SelectFirstListModeText[];
extern char g_menuPaged_Items_AdjustGameOption1F[];
extern char g_menuPaged_Items_SelectGameOption1FText[];
extern char g_menuPaged_Items_FormatPackedGameOption[];
extern char g_menuPaged_Items_AdjustPackedGameOption[];
extern char g_menuPaged_Items_AdjustPlayerOption79[];
extern char g_menuPaged_Items_FormatPlayerOption79Step[];
extern char g_menuPaged_Items_AdjustPlayerOption7A[];
extern char g_menuPaged_Items_FormatPlayerOption7AStep[];
extern char g_menuPaged_Items_SelectPlayerFlag82Text[];
extern char g_menuPaged_Items_TogglePlayerFlag82[];
extern char g_menuPaged_Items_UpdateScreenModeMenuItem[];
extern char g_menuPaged_Items_RequestScreenModeFade[];
extern char g_menuPaged_Pak_AdjustPackedButtonOption[];
extern char g_menuPaged_Pak_FormatPackedButtonOption[];
extern char g_menuPaged_Pak_StopMusicAndResetMatch[];
extern char g_menuPaged_Pak_SetRecordTypeFour[];
extern char g_menuPaged_Pak_ResumeMenuAudio[];
extern char g_menuPaged_Pak_ReturnCallbackSuccess[];
extern char g_menuPaged_Pak_OpenMenuVariantOne_de[];
extern char g_menuPaged_Pak_OpenMenuVariantTwo_de[];
extern char g_menuPaged_Pak_OpenMenuVariantThree_de[];
extern char g_menuPaged_Pak_OpenMenuVariantFour_de[];
extern char g_menuPaged_Pak_OpenMenuVariantFive_de[];
extern char g_menuPaged_Pak_RestoreAudioAndCloseMenu[];
extern char g_menuPaged_Pak_AdjustVolumeSlotTwo[];
extern char g_menuPaged_Pak_UpdateThirdVolumeLabel[];
extern char g_menuPaged_Pak_AdjustVolumeSlotZero[];
extern char g_menuPaged_Pak_UpdateFirstVolumeLabel[];
extern char g_menuPaged_Pak_AdjustModelByteZero[];
extern char g_menuPaged_Pak_AdjustModelByteOne[];
extern char g_menuPaged_Pak_AdjustVolumeSlotOne[];
extern char g_menuPaged_Pak_AdjustModelByteTwo[];
extern char g_menuPaged_Pak_AdjustModelWordAt08[];
extern char g_menuPaged_Pak_FormatVolumeSlotOne[];
extern char g_menuPaged_Pak_AdjustModelFloatAt10[];
extern char g_menuPaged_Pak_AdjustModelFloatAt14[];
extern char g_menuPaged_Pak_UpdateChoiceText[];
extern char g_menuPaged_Pak_SelectMusicPreview[];
extern char g_menuPaged_Pak_FormatMusicPreview[];
extern char g_menuPaged_Pak_SyncPrimaryByteOptionZero[];
extern char g_menuPaged_Pak_OpenMusicPreviewMenu[];
extern char g_menuPaged_Pak_SyncPrimaryByteOptionOne[];
extern char g_menuPaged_Pak_SyncPrimaryByteOptionTwo[];
extern char g_menuPaged_Pak_EnterPlayerOptions[];
extern char g_menuPaged_Pak_RestoreControllerSetup[];
extern char g_menuPaged_Pak_RenderMenuEntryCallback[];
extern char g_menuPaged_Pak_SyncSecondaryByteOptionZero[];
extern char g_menuPaged_Pak_SyncSecondaryByteOptionOne[];
extern char g_menuPaged_Pak_SyncSecondaryByteOptionTwo[];
extern char g_menuPaged_Setup_UpdateNameCursor[];
extern char g_menuPaged_Setup_AppendNameCharacter[];
extern char g_menuPaged_Setup_DrawNameCursor[];
extern char g_menuPaged_Setup_DeleteNameCharacter[];
extern char g_menuPaged_Setup_CommitPlayerName[];
extern char g_menuPaged_Setup_HasActiveGameCounters[];
extern char g_menuPaged_Pak_ToggleOwnerMode[];
extern char g_menuPaged_Pak_UpdateOwnerModeText[];
extern char g_menuPaged_Pak_AdjustOwnerNotificationOption[];
extern char g_menuPaged_Pak_UpdateOwnerNotificationOptionText[];
extern char g_menuPaged_Pak_AdjustMenuChoice[];
extern char g_menuPaged_Pak_UpdateMenuChoiceText[];
extern char g_menuPaged_Pak_OpenMenuVariantSix_us_rev1[];
extern char g_menuPaged_Pak_OpenMenuVariantSeven_us_rev1[];
extern char g_menuPaged_Pak_ToggleTextureVariationBypass[];
extern char g_menuPaged_Pak_UpdateTextureVariationBypassText[];
extern char g_menuPaged_Setup_SetupNameSpinner[];

struct {
    unsigned char red1;
    unsigned char green1;
    unsigned char blue1;
    unsigned char alpha1;
    int resource1;
    unsigned int resourceCallback1;
    unsigned int callback1;
    unsigned int initializeCallback1;
    unsigned int parameter1;
    struct MenuBuildItemData items1[45];
    struct MenuBuildDefinitionData definitions1[1];
} g_menuInventoryData = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x000007D0,
    0x0043EFD0,
    0x00000000,
    0x00000000,
    0x10D60000,
    {
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D0, 0x0043EFD0, 0x00000000, 0x00000000, 0x10D60001 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D0, 0x0043EFD0, 0x00000000, 0x00000000, 0x10D60002 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D1, 0x0043EFD0, 0x00000000, 0x00000000, 0x10E00000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D1, 0x0043EFD0, 0x00000000, 0x00000000, 0x10E00001 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D1, 0x0043EFD0, 0x00000000, 0x00000000, 0x10E00002 },
        { 0x0001, 0x0000, 0x00024010, 0x0029, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E4, 0x0043EFD0, 0x00000000, 0x00000000, 0x11080000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, 0x0043EFD0, 0x00000000, 0x00000000, 0x11940000 },
        { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, 0x800D7E20, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D2, 0x0043EFD0, 0x00000000, 0x00000000, 0x10EA0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D2, 0x0043EFD0, 0x00000000, 0x00000000, 0x10EA0001 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D2, 0x0043EFD0, 0x00000000, 0x00000000, 0x10EA0002 },
        { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080D, 0x0043EFD0, 0x00000000, 0x00000000, 0x11320000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007F9, 0x0043EFD0, 0x00000000, 0x00000000, 0x111E0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E5, 0x0043EFD0, 0x00000000, 0x00000000, 0x11090000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, 0x0043EFD0, 0x00000000, 0x00000000, 0x11940001 },
        { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, 0x800D7E24, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D3, 0x0043EFD0, 0x00000000, 0x00000000, 0x10F40000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D3, 0x0043EFD0, 0x00000000, 0x00000000, 0x10F40001 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D3, 0x0043EFD0, 0x00000000, 0x00000000, 0x10F40002 },
        { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080F, 0x0043EFD0, 0x00000000, 0x00000000, 0x11300000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007F8, 0x0043EFD0, 0x00000000, 0x00000000, 0x111C0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E6, 0x0043EFD0, 0x00000000, 0x00000000, 0x110A0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, 0x0043EFD0, 0x00000000, 0x00000000, 0x11940002 },
        { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, 0x800D7E28, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, 0x0043EFD0, 0x00000000, 0x00000000, 0x10FE0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, 0x0043EFD0, 0x00000000, 0x00000000, 0x10FE0001 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, 0x0043EFD0, 0x00000000, 0x00000000, 0x10FE0002 },
        { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080E, 0x0043EFD0, 0x00000000, 0x00000000, 0x11340000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007FC, 0x0043EFD0, 0x00000000, 0x00000000, 0x11200000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E7, 0x0043EFD0, 0x00000000, 0x00000000, 0x110B0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, 0x0043EFD0, 0x00000000, 0x00000000, 0x11940003 },
        { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, 0x800D7E2C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, 0x0043EFD0, 0x00000000, 0x00000000, 0x10FE0003 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, 0x0043EFD0, 0x00000000, 0x00000000, 0x10FE0004 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, 0x0043EFD0, 0x00000000, 0x00000000, 0x10FE0005 },
        { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080C, 0x0043EFD0, 0x00000000, 0x00000000, 0x11330000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007FB, 0x0043EFD0, 0x00000000, 0x00000000, 0x111F0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E8, 0x0043EFD0, 0x00000000, 0x00000000, 0x110C0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, 0x0043EFD0, 0x00000000, 0x00000000, 0x11940004 },
        { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, 0x800D7E30, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0001, 0x0000, 0x00024010, 0x0075, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000810, 0x0043EFD0, 0x00000000, 0x00000000, 0x11310000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007FA, 0x0043EFD0, 0x00000000, 0x00000000, 0x111D0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E9, 0x0043EFD0, 0x00000000, 0x00000000, 0x110D0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, 0x0043EFD0, 0x00000000, 0x00000000, 0x11940005 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x001E, 0x00, 0x00, 0x00, 0x00, 0x800D76FC, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Multi_CreateMenuWithDefaultMusicGain, 0x00000000 },
    },
    {
        { 0x00450DD0, 0x0031, 0x0000, (unsigned int)g_menuPaged_Multi_EmptyItemHook, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0030, 0x0000, 0x0000, 0x0000, 0x004521BC },
    },
};

unsigned int g_menuInventoryPartTwoTrailingWords[2] = {
    0x00010110, 0x00000004,
};

struct {
    struct MenuBuildItemData items1[1];
    struct MenuBuildDefinitionData definitions1[2];
} g_menuInventoryDataPart3 = {
    {
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
    },
    {
        { 0x004514E0, 0x0001, 0x0000, (unsigned int)g_menuPaged_Items_CacheIdentifierBand, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0009, 0x0000, 0x0000, 0x0000, 0x00451AF0 },
        { 0x004514E0, 0x0001, 0x0000, (unsigned int)g_menuPaged_Items_PrepareControllerReturn, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0009, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
};

unsigned int g_menuInventoryPartThreeTrailingWord[1] = {
    0xFF01F808,
};

struct {
    struct MenuBuildItemData items1[12];
} gPakSlotPromptItems = {
    {
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, 0x800D7BF0, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Player_FormatPlayerPartnerStatus, 0x00000000, 0x00000000 },
        { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_menuPaged_Player_DrawPulsingMenuSprite, 0x00000000, (unsigned int)g_menuPaged_Player_RespawnItemPlayer, 0x00000000 },
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, 0x800D7C10, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Player_FormatPlayerPartnerStatus, 0x00000000, 0x00000000 },
        { 0x0001, 0x0000, 0x20010001, 0xFFEC, 0x0000, 0xEC, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_menuPaged_Player_DrawPulsingMenuSprite, 0x00000000, (unsigned int)g_menuPaged_Player_RespawnItemPlayer, 0x00000000 },
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, 0x800D7C30, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Player_FormatPlayerPartnerStatus, 0x00000000, 0x00000000 },
        { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_menuPaged_Player_DrawPulsingMenuSprite, 0x00000000, (unsigned int)g_menuPaged_Player_RespawnItemPlayer, 0x00000000 },
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, 0x800D7C50, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Player_FormatPlayerPartnerStatus, 0x00000000, 0x00000000 },
        { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_menuPaged_Player_DrawPulsingMenuSprite, 0x00000000, (unsigned int)g_menuPaged_Player_RespawnItemPlayer, 0x00000000 },
    },
};

struct {
    struct MenuBuildDefinitionData definitions1[12];
} gPakSlotPrompts = {
    {
        { 0x00451550, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigurePlayerMenuFlags, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)g_menuPaged_Player_UpdatePlayerRespawnDelay, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x004515BC, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigurePlayerMenuFlags, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)g_menuPaged_Player_UpdatePlayerRespawnDelay, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x00451628, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigurePlayerMenuFlags, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)g_menuPaged_Player_UpdatePlayerRespawnDelay, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x00451694, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigurePlayerMenuFlags, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)g_menuPaged_Player_UpdatePlayerRespawnDelay, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x00451550, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigureAndProbeControllerPak, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x004515BC, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigureAndProbeControllerPak, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x00451628, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigureAndProbeControllerPak, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x00451694, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigureAndProbeControllerPak, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x00451550, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigureControllerPakMenu, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x004515BC, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigureControllerPakMenu, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x00451628, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigureControllerPakMenu, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x00451694, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigureControllerPakMenu, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
};

struct {
    struct MenuBuildItemData items1[16];
    struct MenuBuildDefinitionData definitions1[1];
} g_menuSettingsData = {
    {
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800D7DA4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00400041, 0x0000, 0x002F, 0x00, 0x00, 0xFF, 0x01, 0x800D75D4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_SelectSceneMaskText, (unsigned int)g_menuPaged_Items_CycleSceneMask, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D75E0, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_SelectPlayerOption7BText, (unsigned int)g_menuPaged_Items_AdjustPlayerOption7B, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D75EC, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_SelectPlayerOption7CText, (unsigned int)g_menuPaged_Items_AdjustPlayerOption7C, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D75F4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_SelectPlayerOption7DText, (unsigned int)g_menuPaged_Items_AdjustPlayerOption7D, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7600, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_SelectPlayerOption7EText, (unsigned int)g_menuPaged_Items_AdjustPlayerOption7E, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7604, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_SelectFirstListModeText, (unsigned int)g_menuPaged_Items_AdjustFirstListMode, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7610, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_SelectGameOption1FText, (unsigned int)g_menuPaged_Items_AdjustGameOption1F, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7620, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_FormatPackedGameOption, (unsigned int)g_menuPaged_Items_AdjustPackedGameOption, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7628, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_FormatPlayerOption79Step, (unsigned int)g_menuPaged_Items_AdjustPlayerOption79, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7630, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_FormatPlayerOption7AStep, (unsigned int)g_menuPaged_Items_AdjustPlayerOption7A, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7638, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_SelectPlayerFlag82Text, (unsigned int)g_menuPaged_Items_TogglePlayerFlag82, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D763C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_UpdateScreenModeMenuItem, (unsigned int)g_menuPaged_Items_RequestScreenModeFade, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7654, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Pak_FormatPackedButtonOption, (unsigned int)g_menuPaged_Pak_AdjustPackedButtonOption, 0x00000000 },
        { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0013, 0x00, 0x00, 0xFF, 0x01, 0x800D765C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Menu_TryCreateMenu, 0x00000000 },
    },
    {
        { 0x004518B0, 0x0010, 0x0000, (unsigned int)g_menuPaged_Items_ResetScreenModeFadeCooldown, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000F, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
};

unsigned int g_menuInventoryPartSeventeenFirstExtraWords[3] = {
    0x00000094, 0x08000C00, 0x00000000,
};

struct {
    struct MenuBuildItemData items1[5];
    struct MenuBuildDefinitionData definitions1[1];
    struct MenuBuildItemData items2[8];
    struct MenuBuildDefinitionData definitions2[1];
    struct MenuBuildItemData items3[7];
    struct MenuBuildDefinitionData definitions3[1];
    struct MenuBuildItemData items4[7];
    struct MenuBuildDefinitionData definitions4[1];
    struct MenuBuildItemData items5[16];
    struct MenuBuildDefinitionData definitions5[1];
    struct MenuBuildItemData items6[45];
    struct MenuBuildDefinitionData definitions6[1];
} g_menuSettingsDataPart3 = {
    {
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000041, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800D76F4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00000101, 0x0000, 0x005D, 0x00, 0x00, 0xFF, 0x01, 0x800D7A88, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010101, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, 0x800D7A90, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Pak_StopMusicAndResetMatch, 0x00000000 },
        { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7A94, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Menu_TryCreateMenu, 0x00000000 },
    },
    {
        { 0x00451B20, 0x0005, 0x0000, (unsigned int)g_menuPaged_Pak_SetRecordTypeFour, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0004, 0x0000, 0x0000, 0x0000, 0x004521BC },
    },
    {
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800E612C, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, 0x800E61C4, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Pak_AdjustModelByteZero, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800E61DC, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Pak_AdjustModelByteOne, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800E61F4, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Pak_AdjustModelByteTwo, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800E620C, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Pak_AdjustModelWordAt08, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800E6224, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Pak_AdjustModelFloatAt10, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800E623C, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Pak_AdjustModelFloatAt14, 0x00000000 },
        { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, 0x800E6254, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, (unsigned int)g_menuPaged_Pak_UpdateChoiceText, (unsigned int)g_menuPaged_Pak_ToggleTextChoice, 0x00000000 },
    },
    {
        { 0x00451BF8, 0x0008, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0001, 0x0000, 0x0000, 0x0000, 0x004521BC },
    },
    {
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800E613C, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0002, 0x0000, 0x00010041, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800E6268, (unsigned int)g_menuPaged_Menu_DrawLayeredMenuText, (unsigned int)g_menuPaged_Pak_SyncPrimaryByteOptionZero, (unsigned int)g_menuPaged_Menu_TryCreateMenu, 0x00000000 },
        { 0x0002, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800E627C, (unsigned int)g_menuPaged_Menu_DrawLayeredMenuText, (unsigned int)g_menuPaged_Pak_SyncPrimaryByteOptionOne, (unsigned int)g_menuPaged_Menu_TryCreateMenu, 0x00000000 },
        { 0x0002, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800E6290, (unsigned int)g_menuPaged_Menu_DrawLayeredMenuText, (unsigned int)g_menuPaged_Pak_SyncPrimaryByteOptionTwo, (unsigned int)g_menuPaged_Menu_TryCreateMenu, 0x00000000 },
        { 0x0002, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, 0x800E62A4, (unsigned int)g_menuPaged_Menu_DrawLayeredMenuText, (unsigned int)g_menuPaged_Pak_SyncSecondaryByteOptionZero, (unsigned int)g_menuPaged_Menu_TryCreateMenu, 0x00000000 },
        { 0x0002, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800E62B8, (unsigned int)g_menuPaged_Menu_DrawLayeredMenuText, (unsigned int)g_menuPaged_Pak_SyncSecondaryByteOptionOne, (unsigned int)g_menuPaged_Menu_TryCreateMenu, 0x00000000 },
        { 0x0002, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800E62CC, (unsigned int)g_menuPaged_Menu_DrawLayeredMenuText, (unsigned int)g_menuPaged_Pak_SyncSecondaryByteOptionTwo, (unsigned int)g_menuPaged_Menu_TryCreateMenu, 0x00000000 },
    },
    {
        { 0x00451D3C, 0x0007, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0001, 0x0000, 0x0000, 0x0000, 0x004521BC },
    },
    {
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08002001, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800D7DB4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0032, 0x00, 0x00, 0xFF, 0x01, 0x800D7DC4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Pak_UpdateFirstVolumeLabel, (unsigned int)g_menuPaged_Pak_AdjustVolumeSlotZero, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7DD4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Pak_FormatVolumeSlotOne, (unsigned int)g_menuPaged_Pak_AdjustVolumeSlotOne, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7DE4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Pak_UpdateThirdVolumeLabel, (unsigned int)g_menuPaged_Pak_AdjustVolumeSlotTwo, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7DE8, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Pak_FormatMusicPreview, (unsigned int)g_menuPaged_Pak_SelectMusicPreview, 0x00000000 },
        { 0x0000, 0x0000, 0x00410401, 0x0000, 0x0044, 0x00, 0x00, 0xFF, 0x01, 0x800D765C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Pak_RestoreAudioAndCloseMenu, 0x00000000 },
    },
    {
        { 0x00451E5C, 0x0007, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000041, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800D76D4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, 0x800D76D8, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Pak_ResumeMenuAudio, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D76DC, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Pak_ReturnCallbackSuccess, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D76E4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Pak_OpenMenuVariantOne_de, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D76EC, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Pak_OpenMenuVariantTwo_de, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7DB4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Pak_OpenMusicPreviewMenu, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7AA4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Pak_OpenMenuVariantThree_de, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D76F0, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Pak_OpenMenuVariantFour_de, 0x00000000 },
        { 0x0000, 0x0000, 0x00410101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800E6090, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, (unsigned int)g_menuPaged_Pak_UpdateOwnerModeText, (unsigned int)g_menuPaged_Pak_ToggleOwnerMode, 0x00000000 },
        { 0x0000, 0x0000, 0x00410101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800E60E4, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, (unsigned int)g_menuPaged_Pak_UpdateOwnerNotificationOptionText, (unsigned int)g_menuPaged_Pak_AdjustOwnerNotificationOption, 0x00000000 },
        { 0x0000, 0x0000, 0x00410101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800E6100, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, (unsigned int)g_menuPaged_Pak_UpdateMenuChoiceText, (unsigned int)g_menuPaged_Pak_AdjustMenuChoice, 0x00000000 },
        { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800E612C, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Pak_OpenMenuVariantSix_us_rev1, 0x00000000 },
        { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800E613C, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Pak_OpenMenuVariantSeven_us_rev1, 0x00000000 },
        { 0x0000, 0x0000, 0x00410101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800E6074, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, (unsigned int)g_menuPaged_Pak_UpdateTextureVariationBypassText, (unsigned int)g_menuPaged_Pak_ToggleTextureVariationBypass, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D76F4, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Pak_OpenMenuVariantFive_de, 0x00000000 },
    },
    {
        { 0x00451F7C, 0x0010, 0x0000, (unsigned int)g_menuPaged_Pak_EnterPlayerOptions, (unsigned int)g_menuPaged_Pak_RestoreControllerSetup, (unsigned int)g_menuPaged_Pak_RenderMenuEntryCallback, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0000, 0x0000, 0x00000041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7A5C, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800E6480, (unsigned int)g_menuPaged_Setup_DrawNameCursor, (unsigned int)g_menuPaged_Setup_UpdateNameCursor, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800E6484, (unsigned int)g_menuPaged_Setup_DrawNameCursor, (unsigned int)g_menuPaged_Setup_UpdateNameCursor, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800E6488, (unsigned int)g_menuPaged_Setup_DrawNameCursor, (unsigned int)g_menuPaged_Setup_UpdateNameCursor, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800E648C, (unsigned int)g_menuPaged_Setup_DrawNameCursor, (unsigned int)g_menuPaged_Setup_UpdateNameCursor, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010110, 0x0000, 0x000A, 0x07, 0x01, 0x20, 0x08, 0x800D7E48, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, 0x800D7E50, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, 0x800D7E58, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, 0x800D7E60, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, 0x800D7E68, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, 0x800D7E70, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, 0x800D7E78, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0x20, 0x08, 0x800D7E80, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, 0x800D7E88, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, 0x800D7E90, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, 0x800D7E98, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, 0x800D7EA0, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, 0x800D7EA8, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, 0x800D7EB0, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, 0x800D7EB8, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, 0x800D7EC0, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, 0x800D7EC8, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, 0x800D7ED0, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, 0x800D7ED8, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, 0x800D7EE0, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, 0x800D7EE8, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, 0x800D7EF0, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, 0x800D7EF8, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, 0x800D7F00, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, 0x800D7F08, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, 0x800D7F10, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, 0x800D7F18, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, 0x800D7F20, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, 0x800D7F28, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, 0x800D7F30, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, 0x800D7F38, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, 0x800D7F40, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0xE0, 0x800D7F48, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, 0x800D7F50, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, 0x800D7F58, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, 0x800D7F60, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, 0x800D7F68, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, 0x800D7F70, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_DeleteNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0xE0, 0x800D7F78, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_menuPaged_Setup_CommitPlayerName, 0x00000000 },
    },
    {
        { 0x004521E0, 0x002D, 0x0000, (unsigned int)g_menuPaged_Setup_SetupNameSpinner, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)g_menuPaged_Setup_HasActiveGameCounters, 0x0005, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
};

unsigned int g_menuInventoryPartSeventeenSecondExtraWords[2] = {
    0x00000000, 0x0C706172,
};
#endif
