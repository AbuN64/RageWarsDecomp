#include "Common/runtime_declarations.h"
#include "Common/rg.h"
#include "System/engine_data_source.h"
#include "Menu/Build/definition_data.h"
#include "Engine/cheats.h"

/* G_MENUCHEATCODEDATA.CPP */

#if defined(VERSION_US_REV1)

/* Address of a byte inside a menu data block that has no symbol of its own: the block's symbol plus the offset into it. */
#define MENU_DATA_ADDRESS(block, byteOffset) ((unsigned int)&(block) + (byteOffset))

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
} g_menuItemFragmentLeading = {
    0x00000000,
    {
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_pakOwnerChannelLabelFixed, 0x28), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel, (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
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
    MENU_DATA_ADDRESS(g_pakOwnerChannelLabelFixed, 0x2C),
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
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_pakOwnerChannelLabelFixed, 0x30), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel, (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_pakOwnerChannelLabelFixed, 0x34), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel, (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_pakOwnerChannelLabelFixed, 0x38), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel, (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_pakOwnerChannelLabelFixed, 0x3C), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel, (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_pakOwnerChannelLabelFixed, 0x40), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel, (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0003, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Snapshot_UpdateSpaceLabel_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_UpdateManagerChannelLabel_PagedAddress, (unsigned int)Snapshot_HandleMenuAction_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_pakSaveMenuSnapshotChoiceLabels, 0x4), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_SetManagerHeading_PagedAddress, (unsigned int)Snapshot_CloseNoteBrowser_PagedAddress, 0x00000000 },
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
        { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_pakNoteLabelSlots, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_UpdateAlternatePromptLabel_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_DispatchPreviewHandle_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_difficultyHardText, 0xC), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_FormatPreviewDottedTriple_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_UpdatePreviewDepthLabel_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_difficultyHardText, 0x4), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_FormatPreviewPageCount_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_difficultyHardText, 0x8), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_FormatPreviewValue_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_pakAlternateActionLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_UpdateAlternateActionLabel_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010040, 0x007D, 0x000A, 0x00, 0x01, 0x00, 0x00, MENU_DATA_ADDRESS(g_captureFlagVictimFollowupMessage, 0xC), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00408870, 0x00000000 },
        { 0x0000, 0x0000, 0x00024040, 0x000A, 0x0000, 0xFF, 0x00, 0x00, 0x00, (unsigned int)g_menuNoLabelSlot, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Timer_OpenSelectedPrompt_PagedAddress, 0x00000000 },
    },
    {
        { 0x0044F16C, 0x000A, 0x0000, (unsigned int)Timer_EnableAlternatePrompt_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0008, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F16C, 0x000A, 0x0000, (unsigned int)Timer_DisableAlternatePrompt_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0009, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_pakPreviewKindLabelProfile, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Timer_UpdatePreviewKindLabel_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0032, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Status_FormatRightAlignedPreviewName_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_pakStatusLabelTemplate, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Status_UpdateStatusText_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_pakStatusLabelTemplate, 0x4), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_FormatPreviewFourDigitValue_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_pakStatusLabelTemplate, 0x8), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Snapshot_UpdateScoreTitle_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0010, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_pakAlternateActionLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_UpdateProfileActionLabel_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010040, 0x007D, 0x000A, 0x00, 0x01, 0x00, 0x00, MENU_DATA_ADDRESS(g_captureFlagVictimFollowupMessage, 0xC), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Pak_ConfirmProfileOrDeleteNote_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024040, 0x000A, 0x0000, 0xFF, 0x00, 0x00, 0x00, (unsigned int)g_menuNoLabelSlot, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Pak_OpenProfileActionPrompt_PagedAddress, 0x00000000 },
    },
    {
        { 0x0044F31C, 0x0009, 0x0000, (unsigned int)Timer_EnableProfilePreview_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F31C, 0x0009, 0x0000, (unsigned int)Timer_ClearProfilePreview_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0008, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F31C, 0x0009, 0x0000, (unsigned int)Timer_DisablePreviewSelection_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0008, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectPromptActionHeading_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectPromptTextGroupOne_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectPromptTextGroupTwo_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectPromptTextGroupThree_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectPromptTextGroupFour_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectPromptTextGroupFive_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0019, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_SelectModalPromptLabelStateOtherText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectModalPromptLabel_PagedAddress, (unsigned int)Pak_ClosePromptByKind_PagedAddress, 0x00000000 },
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
        { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_pakPromptLineCells[PAK_PROMPT_ROW_KIND15][4], 0x4), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectOperationHeading_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectOperationDescription_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_FormatOperationChannelLabel_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_pakChannelLabelTexts, 0x4), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Pak_OpenPakChannel_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_pakChannelLabelTexts, 0x8), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Pak_OpenPakStatusPrompt_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectPakLoadHeading_PagedAddress, (unsigned int)Pak_CancelPakAction_PagedAddress, 0x00000000 },
    },
    {
        { 0x0044F850, 0x0008, 0x0000, (unsigned int)Pak_EnableOperationHeading_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Pak_CheckOperationPakChange_PagedAddress, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F850, 0x0008, 0x0000, (unsigned int)Pak_DisableOperationHeading_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Pak_CheckOperationPakChange_PagedAddress, 0x0005, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Pak_SelectPakOperationTextOne_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0023, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Frontend_SelectPakOperationTextTwo_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Frontend_SelectPakOperationTextThree_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Frontend_SelectPakOperationTextFour_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Frontend_SelectPakOperationTextFive_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00012001, 0x0000, 0x0023, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_pakConfirmationDefaultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Frontend_SelectPakConfirmationLabel_PagedAddress, (unsigned int)Pak_ConfirmPendingOperation_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00012001, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (unsigned int)s_nodeDefaultFieldText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Frontend_SelectPakActionLabel_PagedAddress, (unsigned int)Timer_CancelPendingOperation_PagedAddress, 0x00000000 },
    },
    {
        { 0x0044F9B8, 0x0008, 0x0000, (unsigned int)Pak_SelectPakOperationZero_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Pak_CheckPakActionChange_PagedAddress, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F9B8, 0x0008, 0x0000, (unsigned int)Pak_SelectPakOperationOne_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Pak_CheckPakActionChange_PagedAddress, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F9B8, 0x0008, 0x0000, (unsigned int)Pak_SelectPakOperationTwo_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Pak_CheckPakActionChange_PagedAddress, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F9B8, 0x0008, 0x0000, (unsigned int)Pak_SelectPakOperationThree_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Pak_CheckPakActionChange_PagedAddress, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x0044F9B8, 0x0008, 0x0000, (unsigned int)Pak_SelectPakOperationFour_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Pak_CheckPakActionChange_PagedAddress, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
};

/* Bytes the original holds up to the next 16-byte object boundary; no instruction reads them. */
unsigned int g_menuCheatCodeDataLeadingPadding[1] = { 0x00010201 };

struct MenuCheatCodeData g_menuCheatCodeData[12] = {
    { MENU_DATA_ADDRESS(g_residentTextFragmentB, 0x24), MENU_DATA_ADDRESS(g_optionFlagsChangedMessageText, 0x18), 0x00000020, 0x00000001 },
    { MENU_DATA_ADDRESS(g_residentTextFragmentB, 0x14), MENU_DATA_ADDRESS(g_optionFlagsChangedMessageText, 0x20), 0x00000080, 0x00000001 },
    { (unsigned int)&g_playerOptionAutoAimOnText, MENU_DATA_ADDRESS(g_optionFlagsChangedMessageText, 0x24), 0x00000100, 0x00000001 },
    { (unsigned int)g_residentTextFragmentB, MENU_DATA_ADDRESS(g_optionFlagsChangedMessageText, 0x1C), 0x00000040, 0x00000001 },
    { MENU_DATA_ADDRESS(g_residentTextStorageB, 0x20), MENU_DATA_ADDRESS(g_optionFlagsChangedMessageText, 0x28), 0x00000200, 0x00000001 },
    { MENU_DATA_ADDRESS(g_residentTextStorageB, 0xC), MENU_DATA_ADDRESS(g_optionFlagsChangedMessageText, 0x2C), 0x00000400, 0x00000001 },
    { (unsigned int)g_residentTextStorageB, MENU_DATA_ADDRESS(g_optionFlagsChangedMessageText, 0x30), 0x00000800, 0x00000001 },
    { (unsigned int)&g_playerOptionControlSideLeftText, MENU_DATA_ADDRESS(g_optionFlagsChangedMessageText, 0x34), 0x00001000, 0x00000001 },
    { MENU_DATA_ADDRESS(g_residentTextFragmentA, 0xC), MENU_DATA_ADDRESS(g_optionFlagsChangedMessageText, 0x3C), 0x00004000, 0x00000001 },
    { (unsigned int)g_residentTextFragmentA, MENU_DATA_ADDRESS(g_optionFlagsChangedMessageText, 0x40), 0x00008000, 0x00000001 },
    { (unsigned int)&g_playerOptionControlTypeExpertText, (unsigned int)g_GfxGetnormalizedcounterEncodedWords, 0xFFFFFFFF, 0x00000001 },
    { (unsigned int)g_residentTextStorageA, (unsigned int)k_GfxGetnormalizedcounterEncodedWords, 0x0400C7E0, 0x00000001 },
};

struct {
    struct MenuBuildItemData items1[33];
    struct MenuBuildDefinitionData definitions1[1];
    struct MenuBuildItemData items2[20];
    struct MenuBuildDefinitionData definitions2[1];
} g_menuPakOptionsDataAfterCheatCodeData = {
    {
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_optionLabelSlots, 0xC), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00210041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_encodedCheatCode, 0x18), (unsigned int)Option_DrawFirstTextItem_PagedAddress, (unsigned int)Option_UpdateFirstTextItem_PagedAddress, (unsigned int)Option_SelectFirstTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0014, 0x06, 0x01, 0xFF, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x4), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFE, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0xC), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFD, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x14), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFC, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x1C), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFB, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x24), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFA, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x2C), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x34), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0008, 0x06, 0x01, 0xF9, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x3C), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x44), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x4C), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x54), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x5C), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x64), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x6C), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0008, 0x06, 0x01, 0xF9, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x74), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x7C), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x84), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x8C), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x94), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x9C), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0xA4), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0008, 0x06, 0x01, 0xF9, 0x08, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0xAC), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0xB4), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x06, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0xBC), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x05, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0xC4), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x04, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0xCC), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x03, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x12C), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectPenultimateLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x02, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x134), (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)Option_SelectLastLocalizedTextItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0014, 0x00, 0x00, 0x00, 0x00, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateLabelAfterLocalizedText_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00310201, 0x0000, 0x0018, 0x00, 0x00, 0xFE, 0xE2, MENU_DATA_ADDRESS(g_optionLabelSlots, 0x1C), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Menu_TryCreateMenu, 0x00000000 },
    },
    {
        { 0x0044FC50, 0x0021, 0x0000, (unsigned int)Option_InitializeThirtyThreeItemDefinition_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_optionLabelSlots, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuOptionInvincibilityDisabledText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionInvincibilityItem_PagedAddress, (unsigned int)Option_ToggleOptionInvincibility_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuOptionInfiniteLivesDisabledText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionInfiniteLivesItem_PagedAddress, (unsigned int)Option_ToggleOptionInfiniteLives_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuOptionAllWeaponsDisabledText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionAllWeaponsItem_PagedAddress, (unsigned int)Option_ToggleOptionAllWeapons_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuOptionUnlimitedAmmoDisabledText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionUnlimitedAmmoItem_PagedAddress, (unsigned int)Option_ToggleOptionUnlimitedAmmo_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuOptionAllSpecialObjectsDisabledText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionAllSpecialObjectsItem_PagedAddress, (unsigned int)Option_ToggleOptionAllSpecialObjects_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuOptionBigHeadModeDisabledText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBigHeadModeItem_PagedAddress, (unsigned int)Option_ToggleOptionBigHeadMode_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuOptionTinyModeDisabledText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionTinyModeItem_PagedAddress, (unsigned int)Option_ToggleOptionTinyMode_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuOptionBigHandsFeetModeDisabledText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBigHandsFeetModeItem_PagedAddress, (unsigned int)Option_ToggleOptionBigHandsFeetMode_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuOptionStickModeDisabledText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionStickModeItem_PagedAddress, (unsigned int)Option_ToggleOptionStickMode_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuOptionPenAndInkModeDisabledText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionPenAndInkModeItem_PagedAddress, (unsigned int)Option_ToggleOptionPenAndInkMode_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuOptionGouraudModeDisabledText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionGouraudModeItem_PagedAddress, (unsigned int)Option_ToggleOptionGouraudMode_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuOptionJuansCheatDisabledText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionJuansCheatItem_PagedAddress, (unsigned int)Option_ToggleOptionJuansCheat_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuOptionZachAttackCheatDisabledText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionZachAttackCheatItem_PagedAddress, (unsigned int)Option_ToggleOptionZachAttackCheat_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuOptionAllMapDisabledText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionAllMapItem_PagedAddress, (unsigned int)Option_ToggleOptionAllMap_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuOptionBlackoutDisabledText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionBlackoutItem_PagedAddress, (unsigned int)Option_ToggleOptionBlackout_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuOptionFrootyStripesDisabledText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateOptionFrootyStripesItem_PagedAddress, (unsigned int)Option_ToggleOptionFrootyStripes_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Option_UpdateLabelAfterOptionBits_PagedAddress, (unsigned int)Option_SelectLabelAfterOptionBits_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00000201, 0x0000, 0x00C0, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_optionLabelSlots, 0x1C), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Menu_TryCreateMenu, 0x00000000 },
    },
    {
        { 0x00450118, 0x0014, 0x0000, (unsigned int)Option_InitializeTwentyItemDefinition_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0013, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
};

/* Bytes the original holds up to the next 16-byte object boundary; no instruction reads them. */
unsigned int g_menuCheatCodeDataZeroTailMiddle[1] = {
    0x00000000,
};

struct {
    struct MenuBuildItemData items1[3];
    struct MenuBuildDefinitionData definitions1[1];
    struct MenuBuildItemData items2[8];
    struct MenuBuildDefinitionData definitions2[1];
    struct MenuBuildItemData items3[5];
    struct MenuBuildDefinitionData definitions3[1];
} g_menuPakOptionsDataAfterZeroTailMiddle = {
    {
        { 0x0000, 0x0000, 0x00000021, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_optionLabelSlots, 0x20), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_captureFlagVictimFollowupMessage, 0xC), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Menu_SelectLabelBeforeSessionOptionPage_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuNoLabelSlot, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Menu_HandleSessionOptionPage_PagedAddress, 0x00000000 },
    },
    {
        { 0x00450410, 0x0003, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, MENU_DATA_ADDRESS(g_profileMenuLabelWords, 0xC), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, MENU_DATA_ADDRESS(g_profileMenuLabelWords, 0x10), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, MENU_DATA_ADDRESS(g_profileMenuLabelWords, 0x14), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, MENU_DATA_ADDRESS(g_profileMenuLabelWords, 0x18), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, MENU_DATA_ADDRESS(g_profileMenuLabelWords, 0x1C), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, MENU_DATA_ADDRESS(g_profileMenuLabelWords, 0x20), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, MENU_DATA_ADDRESS(g_profileMenuLabelWords, 0x24), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0x00, 0x00, MENU_DATA_ADDRESS(g_profileMenuLabelWords, 0x8), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)CMenuProfile_ResetPlayerControllerProfile_PagedAddress, 0x00000000 },
    },
    {
        { 0x004504A0, 0x0008, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)CMenuProfile_HasRoundProgress_PagedAddress, 0x0007, 0x0000, 0x0000, 0x0000, 0x00450698 },
    },
    {
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x02, MENU_DATA_ADDRESS(k_cheatMenuTextCells, 0x8), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)CMenuProfile_SelectLeadLabelItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0008, 0x00, 0x00, 0x00, 0x00, MENU_DATA_ADDRESS(k_cheatMenuTextCells, 0xC), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)CMenuProfile_BindSelectedDebugField_PagedAddress, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0008, 0x00, 0x00, 0xFE, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)CMenuProfile_FormatProfileQuantityLabel_PagedAddress, (unsigned int)CMenuProfile_AdjustControllerSelection_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_profileModeZeroLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)CMenuProfile_UpdateProfileModeLabel_PagedAddress, (unsigned int)CMenuProfile_ToggleProfileMode_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_profileMenuLabelWords, 0x8), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)CMenuProfile_SelectLabelAfterModeToggle_PagedAddress, 0x00000000 },
    },
    {
        { 0x004505E4, 0x0005, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)CMenuProfile_HasSavedRoundProgress_PagedAddress, 0x0004, 0x0000, 0x0000, 0x0000, 0x00450758 },
    },
};

EngineMenuModelDefinition g_cheatMenuModelDefinition = {
    1120, 11, 0,
    { 0.0f, -50.0f, -900.0f }, { 2.0f, 2.0f, 2.0f },
    "\000\000\0002\000\000\000P", 0.087266475f
};

struct {
    struct MenuBuildItemData items1[3];
    struct MenuBuildDefinitionData definitions1[2];
    struct MenuBuildItemData items2[4];
    struct MenuBuildDefinitionData definitions2[1];
} g_menuPakOptionsDataBeforeAnimationStepSamples = {
    {
        { 0x0001, 0x0000, 0x30000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000387, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0003, 0x0000, 0x00410021, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x004506BC, (unsigned int)Menu_DrawMenuModel_PagedAddress, (unsigned int)CMenuProfile_UpdatePlayerModelItem_PagedAddress, (unsigned int)CMenuProfile_UpdatePlayerAnimationChoice_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0019, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(k_cheatMenuTextCells, 0x4), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)CMenuProfile_UpdateTimedPlayerDialogItem_PagedAddress, (unsigned int)CMenuProfile_OpenTimedPlayerDialog_PagedAddress, 0x00000000 },
    },
    {
        { 0x004506EC, 0x0003, 0x0000, (unsigned int)CMenuProfile_EnableOwnerControllerPak_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)CMenuProfile_HasProfileRoundProgress_PagedAddress, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x004506EC, 0x0003, 0x0000, (unsigned int)CMenuProfile_EnableControllerPakAndClearState_PagedAddress, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)CMenuProfile_HasProfileRoundProgress_PagedAddress, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0001, 0x0000, 0x30000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000387, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_inventoryLabelSlotWords, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010101, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_inventoryLabelSlotWords, 0x4), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)CMenuProfile_OpenPrimaryPlayerDialog_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_inventoryLabelSlotWords, 0x8), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)CMenuProfile_OpenAlternatePlayerDialog_PagedAddress, 0x00000000 },
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
} g_menuPakOptionsDataAfterAnimationStepSamples = {
    {
        { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000201, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_defaultPlayerNames[3], 0xC0), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x0043DD30, (unsigned int)Initial_ToggleMenuRowOption_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x0043DD30, (unsigned int)Initial_ToggleMenuRowOption_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x0043DD30, (unsigned int)Initial_ToggleMenuRowOption_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x0043DD30, (unsigned int)Initial_ToggleMenuRowOption_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x0043DD30, (unsigned int)Initial_ToggleMenuRowOption_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x0043DD30, (unsigned int)Initial_ToggleMenuRowOption_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x0043DD30, (unsigned int)Initial_ToggleMenuRowOption_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x0043DD30, (unsigned int)Initial_ToggleMenuRowOption_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010201, 0x0000, 0x002D, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_optionLabelSlots, 0x1C), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Menu_TryCreateMenu, 0x00000000 },
    },
    {
        { 0x00450894, 0x000B, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000A, 0x0000, 0x0000, 0x0000, 0x00450AD4 },
    },
    {
        { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_defaultPlayerNames[3], 0x14), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_defaultPlayerNames[3], 0xC0), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Initial_SelectMenuRowLabelItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0038, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_optionLabelSlots, 0x1C), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Menu_TryCreateMenu, 0x00000000 },
    },
    {
        { 0x00450A44, 0x0004, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00450D38 },
    },
    {
        { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_defaultPlayerNames[3], 0x4), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0036, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_defaultPlayerNames[3], 0x8), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Initial_OpenDialogWithControllerPak_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_defaultPlayerNames[3], 0xC), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Initial_OpenDialogAfterTimerReset_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0049, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_packedButtonOptionStepText, 0x8), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Initial_RequestTransitionWithPakDisabled_PagedAddress, 0x00000000 },
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
        { 0x0000, 0x0000, 0x00000081, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_defaultPlayerNames[3], 0x4), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Initial_SelectInitialController_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_defaultPlayerNames[3], 0x10), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Initial_UpdateMultiplayerAvailability_PagedAddress, (unsigned int)Initial_OpenLocalPlayerSetup_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_optionLabelSlots, 0xC), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Initial_SelectFirstTrailingLabelItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_menuToggleTorpedoLauncherDisabledText, 0x2C), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Initial_SelectSecondTrailingLabelItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_menuToggleTorpedoLauncherDisabledText, 0x28), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Initial_SelectThirdTrailingLabelItem_PagedAddress, 0x00000000 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_menuToggleTorpedoLauncherDisabledText, 0x38), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)Initial_OpenTrackPreviewMenu_PagedAddress, 0x00000000 },
    },
    {
        { 0x00450C3C, 0x0007, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
};

/* Bytes the original holds up to the next 16-byte object boundary; no instruction reads them. */
unsigned int g_menuCheatCodeDataZeroTail[1] = {
    0x00000000,
};

struct {
    struct MenuBuildItemData items1[2];
    struct MenuBuildDefinitionData definitions1[1];
} g_menuPakOptionsDataAfterZeroTail = {
    {
        { 0x0001, 0x0000, 0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000064, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00000089, 0x0000, 0x0028, 0x00, 0x00, 0x00, 0x00, MENU_DATA_ADDRESS(g_keyboardKeyLabelWords, 0x13C), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)Multi_DecreaseGameOverTimer_PagedAddress, 0x00000000, 0x00000000 },
    },
    {
        { 0x00450D60, 0x0002, 0x0000, 0x0043EF20, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)Multi_CompleteGameOverDelay_PagedAddress, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
};

/* Bytes the original holds up to the next 16-byte object boundary; no instruction reads them. */
unsigned int g_menuPakOptionsZeroTailPadding[1] = {
    0x00020000,
};

struct {
    struct MenuBuildItemData items1[3];
    short type1;
    unsigned short reserved021;
    unsigned int flags1;
    short x1;
    short y1;
} g_menuPakOptionsDataAfterZeroTailPadding = {
    {
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, MENU_DATA_ADDRESS(g_redBloodScoreText, 0x2C), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0016, 0x00, 0x00, 0x00, 0x00, MENU_DATA_ADDRESS(k_menuDigitLabelPointers, 0x4), (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
    },
    0x0001,
    0x0000,
    0x00024010,
    0x0003,
    0x0000,
};
#endif

/* Keep this source unit's macros local to its body. */
#undef MENU_DATA_ADDRESS
