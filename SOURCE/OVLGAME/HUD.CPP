#include "MENU/PICKUP_DRAWSCALEDINTENSITYTILEGRID.H"
#include "include_asm.h"
#include "TYPES.H"
#include "ONSCRN/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"
#include "ENGINE/CACHE/LIST.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"
#include "OVLGAME/HUD.H"

/* HUD.CPP */
extern void Lists_InitFromPool(void *lists, void *pool, s32 stride, s32 count);

extern void Lists_ClearHeader(void *list);

extern s32 Lists_Append(void *list, void *node);





extern void Fx_UpdateEffectLists(s32 owner);



extern unsigned char g_hudPrimaryByteLookupSource[];

extern unsigned char g_hudSecondaryByteLookupSource[];

extern s32 g_hudFirstPanelMoverScript;

extern s32 g_hudSecondPanelMoverScript;

typedef struct ActorWorld {
    s32 mode;                                  /* +0x0 */
    char pad4[0x2588 - 4];
    s32 cursor;                                /* +0x2588 */
    char pad258C[4];
    char actors[96][0xB8];                   /* +0x2590 */
    char actorList[12];                       /* +0x6A90 */
    char shapePool[32 * 84];               /* +0x6A9C */
    char shapeLists[24];                     /* +0x751C */
    char tailPool[3 * 28];                   /* +0x7534 */
    char tailLists[24];                      /* +0x7588 */
    char records[100][0x50];                  /* +0x75A0 */
    char cells[10][0x14];                      /* +0x94E0 */
    char recordList[20];                     /* +0x95A8 */
} ActorWorld;

typedef struct HudTables {
    char pad0[0x90];
    s32 words[4];                              /* +0x90 */
    char padA0[0xC8 - 0xA0];
    unsigned char tableA[256];               /* +0xC8 */
    unsigned char tableB[256];               /* +0x1C8 */
} HudTables;

typedef struct PanelMovers {
    char first[64];                          /* +0x0 */
    s32 firstTarget;                           /* +0x40 */
    char pad44[4];
    char second[64];                         /* +0x48 */
    s32 secondTarget;                          /* +0x88 */
} PanelMovers;

/* HUD.CPP */
/* Initialises the actor world: builds the two list pools (0x20 shapes of 0x54 bytes, 3 tails of 0x1C), links the
 * 96 actors of 0xB8 bytes into the actor list, empties the record list and its 10 cells, links the 100 records of
 * 0x50 bytes into it, clears the mode and cursor words and finishes through Fx_UpdateEffectLists. */
void Hud_InitializeWorldActorPools(ActorWorld *world) {
    s32 i;

    Lists_InitFromPool(world->shapeLists, world->shapePool, 84, 32);
    Lists_InitFromPool(world->tailLists, world->tailPool, 28, 3);
    Lists_ClearHeader(world->actorList);
    for (i = 0; i < 96; i++) {
        Lists_Append(world->actorList, world->actors[i]);
    }
    List_InitializeIntrusive(world->recordList, 0, 4);
    for (i = 0; i < 10; i++) {
        List_InitializeIntrusive(world->cells[i], 0, 4);
    }
    for (i = 0; i < 100; i++) {
        List_AppendIntrusive(world->recordList, world->records[i]);
    }
    world->mode = 0;
    world->cursor = 0;
    Fx_UpdateEffectLists(world);
}

/* Resets the hud: clears the four words at 0x90, runs Hud_EmptyCallback and OnScreen_LoadFontTexture, then fills the two
 * 0x100-byte tables at 0xC8 and 0x1C8 from the pair lists g_hudPrimaryByteLookupSource and g_hudSecondaryByteLookupSource (0x75 pairs each, 0x5C in de). */
void Hud_ResetHudCharTables(HudTables *hud) {
#if defined(VERSION_DE)
    s32 pairs = 92;
#else
    s32 pairs = 117;
#endif
    hud->words[0] = 0;
    hud->words[1] = 0;
    hud->words[2] = 0;
    hud->words[3] = 0;
    Hud_EmptyCallback();
    OnScreen_LoadFontTexture();
    Pickup_BuildByteLookup((int)hud, g_hudPrimaryByteLookupSource, pairs, hud->tableA);
    Pickup_BuildByteLookup((int)hud, g_hudSecondaryByteLookupSource, pairs, hud->tableB);
}

void Hud_EmptyCallback(void) {
}

/* Starts the panel's two movers: each is reset to (0, -0x28) and (0, -0x14) with its target word cleared, and
 * given its frame table (g_hudFirstPanelMoverScript, g_hudSecondPanelMoverScript) through OnScreen_StartMoverScript. */
void Hud_StartPanelMovers(PanelMovers *panel) {
    panel->firstTarget = 0;
    OnScreen_InitMover(panel->first, 0, -40);
    OnScreen_StartMoverScript(panel->first, &g_hudFirstPanelMoverScript);
    panel->secondTarget = 0;
    OnScreen_InitMover(panel->second, 0, -20);
    OnScreen_StartMoverScript(panel->second, &g_hudSecondPanelMoverScript);
}

/* OBJECTDATA.CPP */
#if defined(VERSION_EU)
extern char g_Snapshot_BeginProfileSavePackedAddress24[];
extern char g_Snapshot_BeginProfileLoadPackedAddress24[];
extern char g_Snapshot_CheckEuropeanSaveAvailabilityPackedAddress24[];
extern char g_Snapshot_BeginSnapshotSavePackedAddress24[];
extern char g_Snapshot_BeginBlockLoadPackedAddress24[];
extern char g_Snapshot_SelectNotePackedAddress24[];
extern char g_Snapshot_UpdateNoteLabelPackedAddress24[];
extern char g_Snapshot_UpdateSpaceLabelPackedAddress24[];
extern char g_Snapshot_HandleMenuActionPackedAddress24[];
extern char g_Snapshot_CloseNoteBrowserPackedAddress24[];
extern char g_Pak_ConfirmProfileOrDeleteNotePackedAddress24_Objectdata[];
extern char g_Pak_ClosePromptByKindPackedAddress24_Objectdata[];
extern char g_Pak_ConfirmPendingOperationPackedAddress24_Objectdata[];
extern char g_Timer_CancelPendingOperationPackedAddress24_Objectdata[];
extern char g_Timer_CheckMenuPakChangePackedAddress24_Objectdata[];
extern char g_Timer_CheckChangedMenuChannelPackedAddress24_Objectdata[];
extern char g_Timer_UpdateManagerStatusPackedAddress24_Objectdata[];
extern char g_Timer_UpdateManagerChannelLabelPackedAddress24_Objectdata[];
extern char g_Timer_UpdateOwnerChannelLabelPackedAddress24[];
extern char addrLow_Timer_UpdateAlternateActionLabel[];
extern char g_Timer_SetManagerHeadingPackedAddress24_Objectdata[];
extern char g_Timer_EnableAlternatePromptPackedAddress24_Objectdata[];
extern char addrLow_Timer_UpdatePreviewKindLabel[];
extern char g_Timer_UpdateAlternatePromptLabelPackedAddress24_Objectdata[];
extern char g_Timer_UpdatePreviewDepthLabelPackedAddress24_Objectdata[];
extern char g_Timer_FormatPreviewPageCountPackedAddress24_Objectdata[];
extern char g_Timer_FormatPreviewValuePackedAddress24_Objectdata[];
extern char g_Timer_DispatchPreviewHandlePackedAddress24[];
extern char g_Timer_FormatPreviewDottedTriplePackedAddress24_Objectdata[];
extern char g_Timer_UpdateAlternateActionLabelPackedAddress24_Objectdata[];
extern char g_Timer_OpenSelectedPromptPackedAddress24_Objectdata[];
extern char g_Timer_EnableProfilePreviewPackedAddress24_Objectdata[];
extern char g_Timer_ClearProfilePreviewPackedAddress24_Objectdata[];
extern char g_Timer_DisablePreviewSelectionPackedAddress24[];
extern char addrLow_Pak_SelectPromptKindFive[];
extern char g_Menu_FormatLocalizedPakStatusPackedAddress24[];
extern char g_Pak_FormatPreviewFourDigitValuePackedAddress24_Objectdata[];
extern char g_Pak_UpdateProfileActionLabelPackedAddress24_Objectdata[];
extern char g_Pak_OpenProfileActionPromptPackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptKindZeroPackedAddress24_Objectdata[];
extern char addrLow_Pak_SelectPromptTextGroupThree[];
extern char g_Pak_SelectPromptKindTwoPackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptKindThreePackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptKindFourPackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptKindFivePackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptKindSixPackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptKindSevenPackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptKindEightPackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptKindNinePackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptKindNinePendingPackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptKindTenPackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptKindElevenPackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptKindTwelvePackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptKindThirteenPackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptKindFourteenPackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptKindFifteenPackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptActionHeadingPackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptTextGroupOnePackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptTextGroupTwoPackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptTextGroupThreePackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptTextGroupFourPackedAddress24_Objectdata[];
extern char g_Pak_SelectPromptTextGroupFivePackedAddress24_Objectdata[];
extern char g_Pak_SelectModalPromptLabelPackedAddress24_Objectdata[];
extern char g_Pak_CheckOperationPakChangePackedAddress24_Objectdata[];
extern char g_Pak_EnableOperationHeadingPackedAddress24_Objectdata[];
extern char g_Pak_DisableOperationHeadingPackedAddress24[];
extern char g_Pak_SelectOperationHeadingPackedAddress24_Objectdata[];
extern char g_Pak_SelectOperationDescriptionPackedAddress24_Objectdata[];
extern char g_Pak_FormatOperationChannelLabelPackedAddress24_Objectdata[];
extern char g_Pak_OpenPakChannelPackedAddress24_Objectdata[];
extern char g_Pak_OpenPakStatusPromptPackedAddress24_Objectdata[];
extern char g_Pak_CancelPakActionPackedAddress24_Objectdata[];
extern char g_Pak_SelectPakLoadHeadingPackedAddress24_Objectdata[];
extern char addrLow_Menu_SelectPakOperationActionLabel[];
extern char g_Pak_SelectPakOperationZeroPackedAddress24_Objectdata[];
extern char g_Pak_SelectPakOperationOnePackedAddress24_Objectdata[];
extern char g_Pak_SelectPakOperationTwoPackedAddress24_Objectdata[];
extern char g_Pak_SelectPakOperationThreePackedAddress24_Objectdata[];
extern char g_Pak_SelectPakOperationFourPackedAddress24_Objectdata[];
extern char g_Pak_SelectPakOperationTextOnePackedAddress24_Objectdata[];
extern char g_Frontend_SelectPakOperationTextTwoPackedAddress24_Objectdata[];
extern char g_Frontend_SelectPakOperationTextThreePackedAddress24_Objectdata[];
extern char g_Frontend_SelectPakOperationTextFourPackedAddress24_Objectdata[];
extern char g_Frontend_SelectPakOperationTextFivePackedAddress24_Objectdata[];
extern char g_Frontend_SelectPakConfirmationLabelPackedAddress24_Objectdata[];
extern char g_Menu_SelectEuropeanPakActionLabelPackedAddress24[];
extern char g_Encoded_HandleUnlockedLevelSelectionPackedAddress24_Objectdata[];
extern char g_Encoded_ResetTextEntryResultPackedAddress24_Objectdata[];
extern char g_Encoded_DrawTextEntryCursorPackedAddress24_Objectdata[];
extern char g_Encoded_UpdateTextEntryCursorPackedAddress24_Objectdata[];
extern char g_Encoded_TextEntryReturnZeroPackedAddress24_Objectdata[];
extern char g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata[];
extern char g_Encoded_DeletePreviousTextEntryCharacterPackedAddress24_Objectdata[];
extern char g_Encoded_ApplyCheatCodePackedAddress24_Objectdata[];
extern char g_Encoded_SetTextEntryResultLabelPackedAddress24_Objectdata[];
extern char g_Menu_SetSelectedLevelLabelPackedAddress24_Objectdata[];
extern char g_Pak_ToggleTextChoicePackedAddress24_Objectdata[];
extern char g_Option_UpdateOptionBit0ItemPackedAddress24_Objectdata[];
extern char g_Option_ToggleOptionBit1PackedAddress24_Objectdata[];
extern char g_Option_UpdateOptionBit1ItemPackedAddress24_Objectdata[];
extern char g_Option_ToggleOptionBit2PackedAddress24_Objectdata[];
extern char g_Option_UpdateOptionBit2ItemPackedAddress24_Objectdata[];
extern char g_Option_ToggleOptionBit3PackedAddress24_Objectdata[];
extern char g_Option_UpdateOptionBit3ItemPackedAddress24_Objectdata[];
extern char g_Option_ToggleOptionBit4PackedAddress24_Objectdata[];
extern char g_Option_UpdateOptionBit4ItemPackedAddress24_Objectdata[];
extern char g_Option_ToggleOptionBit5PackedAddress24_Objectdata[];
extern char g_Option_UpdateOptionBit5ItemPackedAddress24_Objectdata[];
extern char g_Option_ToggleOptionBit6PackedAddress24_Objectdata[];
extern char g_Option_UpdateOptionBit6ItemPackedAddress24_Objectdata[];
extern char addrLow_CMenuProfile_EnableControllerPakAndClearState[];
extern char g_Option_UpdateOptionBit7ItemPackedAddress24_Objectdata[];
extern char g_Option_ToggleOptionBit8PackedAddress24_Objectdata[];
extern char g_Option_UpdateOptionBit8ItemPackedAddress24_Objectdata[];
extern char g_Option_ToggleOptionBit9PackedAddress24_Objectdata[];
extern char g_Option_UpdateOptionBit9ItemPackedAddress24_Objectdata[];
extern char g_Option_ToggleOptionBit10PackedAddress24_Objectdata[];
extern char g_Option_UpdateOptionBit10ItemPackedAddress24_Objectdata[];
extern char g_Option_ToggleOptionBit11PackedAddress24_Objectdata[];
extern char g_Option_UpdateOptionBit11ItemPackedAddress24_Objectdata[];
extern char g_Option_ToggleOptionBit12PackedAddress24_Objectdata[];
extern char g_Option_UpdateOptionBit12ItemPackedAddress24_Objectdata[];
extern char g_Option_ToggleOptionBit13PackedAddress24_Objectdata[];
extern char g_Option_UpdateOptionBit13ItemPackedAddress24_Objectdata[];
extern char g_Option_ToggleOptionBit14PackedAddress24_Objectdata[];
extern char g_Option_UpdateOptionBit14ItemPackedAddress24_Objectdata[];
extern char g_Option_ToggleOptionBit15PackedAddress24_Objectdata[];
extern char g_Option_UpdateOptionBit15ItemPackedAddress24_Objectdata[];
extern char g_Items_ForwardRulesLockPackedAddress24[];
extern char g_Items_HandleSessionOptionPagePackedAddress24[];
extern char g_Items_SelectOptionRowLabelPackedAddress24[];
extern char g_CMenuProfile_HasRoundProgressPackedAddress24_Objectdata[];
extern char g_CMenuProfile_ResetPlayerControllerProfilePackedAddress24_Objectdata[];
extern char g_CMenuProfile_HasSavedRoundProgressPackedAddress24_Objectdata[];
extern char g_CMenuProfile_AdjustControllerSelectionPackedAddress24_Objectdata[];
extern char g_CMenuProfile_FormatProfileQuantityLabelPackedAddress24_Objectdata[];
extern char g_CMenuProfile_ToggleProfileModePackedAddress24_Objectdata[];
extern char g_CMenuProfile_OpenPrimaryProfileMenuPackedAddress24_Objectdata[];
extern char g_CMenuProfile_BindSelectedDebugFieldPackedAddress24_Objectdata[];
extern char g_CMenuProfile_OpenSecondaryProfileMenuPackedAddress24_Objectdata[];
extern char g_CMenuProfile_UpdateProfileModeLabelPackedAddress24_Objectdata[];
extern char g_CMenuProfile_EnableOwnerControllerPakPackedAddress24_Objectdata[];
extern char g_CMenuProfile_EnableControllerPakAndClearStatePackedAddress24_Objectdata[];
extern char g_CMenuProfile_HasProfileRoundProgressPackedAddress24_Objectdata[];
extern char g_CMenuProfile_OpenTimedPlayerDialogPackedAddress24_Objectdata[];
extern char g_CMenuProfile_ProfileModeReturnZeroPackedAddress24_Objectdata[];
extern char g_CMenuProfile_UpdatePlayerAnimationChoicePackedAddress24_Objectdata[];
extern char g_CMenuProfile_GameSpeedReturnZeroPackedAddress24_Objectdata[];
extern char g_CMenuProfile_HasDialogRoundProgressPackedAddress24_Objectdata[];
extern char g_CMenuProfile_OpenPrimaryPlayerDialogPackedAddress24_Objectdata[];
extern char g_CMenuProfile_OpenAlternatePlayerDialogPackedAddress24_Objectdata[];
extern char g_Initial_ToggleMenuRowOptionPackedAddress24_Objectdata[];
extern char g_Initial_OpenMatchSetupMenuPackedAddress24_Objectdata[];
extern char g_Initial_ProbeMenuControllerPakPackedAddress24_Objectdata[];
extern char g_Initial_EnableMenuControllerPakPackedAddress24_Objectdata[];
extern char g_Initial_OpenDialogWithControllerPakPackedAddress24_Objectdata[];
extern char g_Initial_OpenDialogAfterTimerResetPackedAddress24_Objectdata[];
extern char g_Initial_RequestTransitionWithPakDisabledPackedAddress24_Objectdata[];
extern char g_Initial_SelectInitialControllerPackedAddress24_Objectdata[];
extern char g_Initial_UpdateMultiplayerAvailabilityPackedAddress24_Objectdata[];
extern char g_Initial_OpenLocalPlayerSetupPackedAddress24_Objectdata[];
extern char g_Initial_OpenDialog450E9CPackedAddress24_Objectdata[];
extern char g_Initial_OpenDialog44F4A4PackedAddress24_Objectdata[];
extern char g_Initial_OpenDialog44F798PackedAddress24_Objectdata[];
extern char g_Initial_OpenTrackPreviewMenuPackedAddress24_Objectdata[];
extern char g_Initial_ResetPlayerGameOverTimerPackedAddress24_Objectdata[];
extern char g_Multi_CompleteGameOverDelayPackedAddress24_Objectdata[];
extern char g_Multi_DecreaseGameOverTimerPackedAddress24_Objectdata[];
extern char g_Multi_EmptyItemHookPackedAddress24_Objectdata[];
extern char g_Multi_CreateMenuWithDefaultMusicGainPackedAddress24_Objectdata[];
extern char g_Menu_DrawMenuOptionSpritePackedAddress24[];
extern char g_Menu_DrawMenuModelPackedAddress24_Objectdata[];
extern char g_Menu_DrawMenuEntriesPackedAddress24[];
extern char g_Menu_DrawMenuItemLabelPackedAddress24[];
extern char g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata[];
extern char g_Menu_TryCreateMenuPackedAddress24_Objectdata[];
extern char g_Items_PrepareControllerReturnPackedAddress24_Objectdata[];
extern char g_Player_FormatPlayerPartnerStatusPackedAddress24_Objectdata[];
extern char g_Player_RespawnItemPlayerPackedAddress24_Objectdata[];
extern char g_Player_DrawPulsingMenuSpritePackedAddress24_Objectdata[];
extern char g_Player_UpdatePlayerRespawnDelayPackedAddress24_Objectdata[];
extern char g_Player_ConfigurePlayerMenuFlagsPackedAddress24_Objectdata[];
extern char g_Player_ConfigureAndProbeControllerPakPackedAddress24_Objectdata[];
extern char g_Player_ConfigureControllerPakMenuPackedAddress24_Objectdata[];
extern char g_Items_ResetScreenModeFadeCooldownPackedAddress24_Objectdata[];
extern char g_Items_CycleSceneMaskPackedAddress24_Objectdata[];
extern char g_Items_SelectSceneMaskTextPackedAddress24_Objectdata[];
extern char g_Items_AdjustPlayerOption7BPackedAddress24_Objectdata[];
extern char g_Items_SelectPlayerOption7BTextPackedAddress24_Objectdata[];
extern char g_Items_AdjustPlayerOption7CPackedAddress24_Objectdata[];
extern char g_Items_SelectPlayerOption7CTextPackedAddress24_Objectdata[];
extern char g_Items_AdjustPlayerOption7DPackedAddress24_Objectdata[];
extern char g_Items_SelectPlayerOption7DTextPackedAddress24_Objectdata[];
extern char g_Items_AdjustPlayerOption7EPackedAddress24_Objectdata[];
extern char g_Items_SelectPlayerOption7ETextPackedAddress24_Objectdata[];
extern char g_Items_AdjustFirstListModePackedAddress24_Objectdata[];
extern char g_Items_SelectFirstListModeTextPackedAddress24_Objectdata[];
extern char g_Items_AdjustGameOption1FPackedAddress24_Objectdata[];
extern char g_Items_SelectGameOption1FTextPackedAddress24_Objectdata[];
extern char g_Items_FormatPackedGameOptionPackedAddress24_Objectdata[];
extern char g_Items_AdjustPackedGameOptionPackedAddress24_Objectdata[];
extern char g_Items_AdjustPlayerOption79PackedAddress24_Objectdata[];
extern char g_Items_FormatPlayerOption79StepPackedAddress24_Objectdata[];
extern char g_Items_AdjustPlayerOption7APackedAddress24_Objectdata[];
extern char g_Items_FormatPlayerOption7AStepPackedAddress24_Objectdata[];
extern char g_Items_SelectPlayerFlag82TextPackedAddress24_Objectdata[];
extern char g_Items_TogglePlayerFlag82PackedAddress24_Objectdata[];
extern char g_Items_UpdateScreenModeMenuItemPackedAddress24_Objectdata[];
extern char g_Items_RequestScreenModeFadePackedAddress24_Objectdata[];
extern char g_Pak_AdjustPackedButtonOptionPackedAddress24_Objectdata[];
extern char g_Pak_FormatPackedButtonOptionPackedAddress24_Objectdata[];
extern char g_Items_AdjustLanguagePackedAddress24_Objectdata[];
extern char g_CItemValue_BindItemValueFieldPackedAddress24[];
extern char g_Pak_StopMusicAndResetMatchPackedAddress24_Objectdata[];
extern char g_Pak_SetRecordTypeFourPackedAddress24_Objectdata[];
extern char g_Pak_ResumeMenuAudioPackedAddress24_Objectdata[];
extern char g_Pak_ReturnCallbackSuccessPackedAddress24_Objectdata[];
extern char g_Pak_AllocateMenuSlotOnePackedAddress24[];
extern char g_Pak_AllocateMenuSlotTwoPackedAddress24[];
extern char g_Pak_AllocateMenuSlotThreePackedAddress24[];
extern char g_Pak_AllocateMenuSlotFourPackedAddress24[];
extern char g_Pak_AllocateMenuSlotFivePackedAddress24[];
extern char g_Pak_AllocateMenuSlotSixPackedAddress24[];
extern char g_Pak_RestoreAudioAndCloseMenuPackedAddress24_Objectdata[];
extern char g_Pak_AdjustVolumeSlotTwoPackedAddress24_Objectdata[];
extern char g_Pak_UpdateThirdVolumeLabelPackedAddress24_Objectdata[];
extern char g_Pak_AdjustVolumeSlotZeroPackedAddress24_Objectdata[];
extern char g_Pak_UpdateFirstVolumeLabelPackedAddress24_Objectdata[];
extern char g_Pak_AdjustVolumeSlotOnePackedAddress24_Objectdata[];
extern char g_Pak_FormatVolumeSlotOnePackedAddress24_Objectdata[];
extern char g_Pak_SelectMusicPreviewPackedAddress24_Objectdata[];
extern char g_Pak_FormatMusicPreviewPackedAddress24_Objectdata[];
extern char g_Pak_OpenMusicPreviewMenuPackedAddress24_Objectdata[];
extern char g_Pak_EnterPlayerOptionsPackedAddress24_Objectdata[];
extern char g_Pak_RestoreControllerSetupPackedAddress24_Objectdata[];
extern char g_Pak_RenderMenuEntryCallbackPackedAddress24_Objectdata[];
extern char g_Setup_SetupNameSpinnerPackedAddress24_Objectdata[];
extern char g_Setup_UpdateNameCursorPackedAddress24_Objectdata[];
extern char g_Setup_AppendNameCharacterPackedAddress24_Objectdata[];
extern char g_Setup_DrawNameCursorPackedAddress24_Objectdata[];
extern char g_Setup_DeleteNameCharacterPackedAddress24_Objectdata[];
extern char g_Setup_CommitPlayerNamePackedAddress24_Objectdata[];
extern char g_Setup_HasActiveGameCountersPackedAddress24_Objectdata[];
struct {
    unsigned int words0[1724];
    float floats1[1];
    unsigned int words2[1];
    char text3[4];
    unsigned int words4[1848];
} g_overlayTwoThreeObjectLinkWords = {
    {
        0x8E2205D8, 0xA0400080, 0xAE2005E0, 0x00010000, 0x90000000, 0x00000000, 0x0000FF01, 0x00000385,
        (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000041, 0x0000000A, 0x0000FF01,
        0x800E25E4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Timer_UpdateOwnerChannelLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x0000FFF8,
        0x0000FF01, 0x800E2744, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)addrLow_Timer_UpdateAlternateActionLabel, 0x00000000, 0x00000000, 0x00000000, 0x00011001,
        0x00000006, 0x0000FF01, 0x800E25F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Snapshot_UpdateNoteLabelPackedAddress24, (unsigned int)g_Snapshot_SelectNotePackedAddress24, 0x00000000, 0x00000000,
        0x00011001, 0x00000000, 0x0000FF01, 0x800E2604, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Snapshot_UpdateNoteLabelPackedAddress24, (unsigned int)g_Snapshot_SelectNotePackedAddress24, 0x00000000,
        0x00000000, 0x00011001, 0x00000000, 0x0000FF01, 0x800E2614, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Snapshot_UpdateNoteLabelPackedAddress24, (unsigned int)g_Snapshot_SelectNotePackedAddress24,
        0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, 0x800E2624, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Snapshot_UpdateNoteLabelPackedAddress24,
        (unsigned int)g_Snapshot_SelectNotePackedAddress24, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, 0x800E2634, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24,
        (unsigned int)g_Snapshot_UpdateNoteLabelPackedAddress24, (unsigned int)g_Snapshot_SelectNotePackedAddress24, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, 0x800E2644,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Snapshot_UpdateNoteLabelPackedAddress24, (unsigned int)g_Snapshot_SelectNotePackedAddress24, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01,
        0x800E2654, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Snapshot_UpdateNoteLabelPackedAddress24, (unsigned int)g_Snapshot_SelectNotePackedAddress24, 0x00000000, 0x00000000, 0x00011001, 0x00000000,
        0x0000FF01, 0x800E2664, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Snapshot_UpdateNoteLabelPackedAddress24, (unsigned int)g_Snapshot_SelectNotePackedAddress24, 0x00000000, 0x00000000, 0x00011001,
        0x00000000, 0x0000FF01, 0x800E2674, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Snapshot_UpdateNoteLabelPackedAddress24, (unsigned int)g_Snapshot_SelectNotePackedAddress24, 0x00000000, 0x00000000,
        0x00011001, 0x00000000, 0x0000FF01, 0x800E2684, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Snapshot_UpdateNoteLabelPackedAddress24, (unsigned int)g_Snapshot_SelectNotePackedAddress24, 0x00000000,
        0x00000000, 0x00011001, 0x00000000, 0x0000FF01, 0x800E2694, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Snapshot_UpdateNoteLabelPackedAddress24, (unsigned int)g_Snapshot_SelectNotePackedAddress24,
        0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, 0x800E26A4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Snapshot_UpdateNoteLabelPackedAddress24,
        (unsigned int)g_Snapshot_SelectNotePackedAddress24, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, 0x800E26B4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24,
        (unsigned int)g_Snapshot_UpdateNoteLabelPackedAddress24, (unsigned int)g_Snapshot_SelectNotePackedAddress24, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, 0x800E26C4,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Snapshot_UpdateNoteLabelPackedAddress24, (unsigned int)g_Snapshot_SelectNotePackedAddress24, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01,
        0x800E26D4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Snapshot_UpdateNoteLabelPackedAddress24, (unsigned int)g_Snapshot_SelectNotePackedAddress24, 0x00000000, 0x00000000, 0x00011001, 0x00000000,
        0x0000FF01, 0x800E26E4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Snapshot_UpdateNoteLabelPackedAddress24, (unsigned int)g_Snapshot_SelectNotePackedAddress24, 0x00000000, 0x00000000, 0x00011001,
        0x00000003, 0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Snapshot_UpdateSpaceLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000,
        0x00010041, 0x0000000A, 0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Timer_UpdateManagerChannelLabelPackedAddress24_Objectdata, (unsigned int)g_Snapshot_HandleMenuActionPackedAddress24, 0x00000000,
        0x00000000, 0x00010041, 0x00000004, 0x0000FF01, 0x800E2784, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Timer_SetManagerHeadingPackedAddress24_Objectdata, (unsigned int)g_Snapshot_CloseNoteBrowserPackedAddress24,
        0x00000000, 0x0044F420, 0x00160000, (unsigned int)g_Snapshot_BeginProfileLoadPackedAddress24, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)g_Timer_CheckMenuPakChangePackedAddress24_Objectdata, 0x00150000,
        0x00000000, 0x00000000, 0x0044F420, 0x00160000, (unsigned int)g_Snapshot_BeginProfileSavePackedAddress24, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)g_Timer_CheckMenuPakChangePackedAddress24_Objectdata,
        0x00140000, 0x00000000, 0x00000000, 0x0044F420, 0x00160000, (unsigned int)g_Snapshot_BeginBlockLoadPackedAddress24, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24,
        (unsigned int)g_Timer_CheckChangedMenuChannelPackedAddress24_Objectdata, 0x00150000, 0x00000000, 0x00000000, 0x0044F420, 0x00160000, (unsigned int)g_Snapshot_BeginSnapshotSavePackedAddress24, 0x00000000,
        (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)g_Timer_CheckChangedMenuChannelPackedAddress24_Objectdata, 0x00140000, 0x00000000, 0x00000000, 0x0044F420, 0x00160000, (unsigned int)g_Snapshot_CheckEuropeanSaveAvailabilityPackedAddress24,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)g_Timer_UpdateManagerStatusPackedAddress24_Objectdata, 0x00140000, 0x00000000, 0x00000000, 0x00010000, 0x90000000,
        0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x08000801, 0x00000008, 0x0000FF01, 0x800E28D4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Timer_UpdateAlternatePromptLabelPackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00000000, 0x00010041, 0x00000014, 0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Timer_DispatchPreviewHandlePackedAddress24, 0x00000000,
        0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, 0x800E2944, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Timer_FormatPreviewDottedTriplePackedAddress24_Objectdata,
        0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x0000000A, 0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24,
        (unsigned int)g_Timer_UpdatePreviewDepthLabelPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, 0x800E2924,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Timer_FormatPreviewPageCountPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01,
        0x800E2934, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Timer_FormatPreviewValuePackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000014,
        0x0000FF01, 0x800E29E4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Timer_UpdateAlternateActionLabelPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010040,
        0x007D000A, 0x00010000, 0x800E33E4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00408A58, 0x00000000, 0x00000000,
        0x00024040, 0x000A0000, 0xFF000000, 0x800E33F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Timer_OpenSelectedPromptPackedAddress24_Objectdata, 0x00000000,
        0x0044F7EC, 0x000A0000, (unsigned int)g_Timer_EnableAlternatePromptPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00080000, 0x00000000,
        0x00000000, 0x0044F7EC, 0x000A0000, (unsigned int)addrLow_Timer_UpdatePreviewKindLabel, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00090000,
        0x00000000, 0x00000000, 0x00010000, 0x90000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000021, 0x00000008, 0x0000FF01, 0x800E2954,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)addrLow_Pak_SelectPromptKindFive, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000032, 0x0000FF01,
        0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x0040AB6C, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000002,
        0x0000FF01, 0x800E29B4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Menu_FormatLocalizedPakStatusPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00010041,
        0x00000002, 0x0000FF01, 0x800E29C4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Pak_FormatPreviewFourDigitValuePackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000,
        0x00010041, 0x00000002, 0x0000FF01, 0x800E29D4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00408CAC, 0x00000000, 0x00000000,
        0x00000000, 0x00010041, 0x00000010, 0x0000FF01, 0x800E29E4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Pak_UpdateProfileActionLabelPackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00000000, 0x00010040, 0x007D000A, 0x00010000, 0x800E33E4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000,
        (unsigned int)g_Pak_ConfirmProfileOrDeleteNotePackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024040, 0x000A0000, 0xFF000000, 0x800E33F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24,
        0x00000000, (unsigned int)g_Pak_OpenProfileActionPromptPackedAddress24_Objectdata, 0x00000000, 0x0044F99C, 0x00090000, (unsigned int)g_Timer_EnableProfilePreviewPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24,
        0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044F99C, 0x00090000, (unsigned int)g_Timer_ClearProfilePreviewPackedAddress24_Objectdata, 0x00000000,
        (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00080000, 0x00000000, 0x00000000, 0x0044F99C, 0x00090000, (unsigned int)g_Timer_DisablePreviewSelectionPackedAddress24,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00080000, 0x00000000, 0x00000000, 0x00010000, 0x90000000,
        0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x08000021, 0x00000008, 0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Pak_SelectPromptActionHeadingPackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00000000, 0x00010041, 0x0000001E, 0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Pak_SelectPromptTextGroupOnePackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Pak_SelectPromptTextGroupTwoPackedAddress24_Objectdata,
        0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24,
        (unsigned int)g_Pak_SelectPromptTextGroupThreePackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, 0x800E41F4,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Pak_SelectPromptTextGroupFourPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01,
        0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Pak_SelectPromptTextGroupFivePackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000019,
        0x0000FF01, 0x800E2A34, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Pak_SelectModalPromptLabelPackedAddress24_Objectdata, (unsigned int)g_Pak_ClosePromptByKindPackedAddress24_Objectdata, 0x00000000, 0x0044FB4C, 0x00080000,
        (unsigned int)g_Pak_SelectPromptKindZeroPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044FB4C,
        0x00080000, (unsigned int)addrLow_Pak_SelectPromptTextGroupThree, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00070000, 0x00000000, 0x00000000,
        0x0044FB4C, 0x00080000, (unsigned int)g_Pak_SelectPromptKindTwoPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00070000, 0x00000000,
        0x00000000, 0x0044FB4C, 0x00080000, (unsigned int)g_Pak_SelectPromptKindThreePackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00070000,
        0x00000000, 0x00000000, 0x0044FB4C, 0x00080000, (unsigned int)g_Pak_SelectPromptKindFourPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000,
        0x00070000, 0x00000000, 0x00000000, 0x0044FB4C, 0x00080000, (unsigned int)g_Pak_SelectPromptKindFivePackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24,
        0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044FB4C, 0x00080000, (unsigned int)g_Pak_SelectPromptKindSixPackedAddress24_Objectdata, 0x00000000,
        (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044FB4C, 0x00080000, (unsigned int)g_Pak_SelectPromptKindSevenPackedAddress24_Objectdata,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044FB4C, 0x00080000,
        (unsigned int)g_Pak_SelectPromptKindEightPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044FB4C,
        0x00080000, (unsigned int)g_Pak_SelectPromptKindNinePackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00070000, 0x00000000, 0x00000000,
        0x0044FB4C, 0x00080000, (unsigned int)g_Pak_SelectPromptKindNinePendingPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00070000, 0x00000000,
        0x00000000, 0x0044FB4C, 0x00080000, (unsigned int)g_Pak_SelectPromptKindTenPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00070000,
        0x00000000, 0x00000000, 0x0044FB4C, 0x00080000, (unsigned int)g_Pak_SelectPromptKindElevenPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000,
        0x00070000, 0x00000000, 0x00000000, 0x0044FB4C, 0x00080000, (unsigned int)g_Pak_SelectPromptKindTwelvePackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24,
        0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044FB4C, 0x00080000, (unsigned int)g_Pak_SelectPromptKindFifteenPackedAddress24_Objectdata, 0x00000000,
        (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044FB4C, 0x00080000, (unsigned int)g_Pak_SelectPromptKindThirteenPackedAddress24_Objectdata,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044FB4C, 0x00080000,
        (unsigned int)g_Pak_SelectPromptKindFourteenPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x00010000,
        0x90000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x08000021, 0x00000008, 0x0000FF01, 0x800E2F54, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00010041, 0x00000028, 0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Pak_SelectOperationHeadingPackedAddress24_Objectdata,
        0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24,
        (unsigned int)g_Pak_SelectOperationDescriptionPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, 0x800E41F4,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Pak_FormatOperationChannelLabelPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000014, 0x0000FF01,
        0x800E2FC4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Pak_OpenPakChannelPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010041, 0x00000005,
        0x0000FF01, 0x800E2FD4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Pak_OpenPakStatusPromptPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010041,
        0x00000005, 0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Pak_SelectPakLoadHeadingPackedAddress24_Objectdata, (unsigned int)g_Pak_CancelPakActionPackedAddress24_Objectdata, 0x00000000, 0x0044FED0,
        0x00080000, (unsigned int)g_Pak_EnableOperationHeadingPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)g_Pak_CheckOperationPakChangePackedAddress24_Objectdata, 0x00070000, 0x00000000, 0x00000000,
        0x0044FED0, 0x00080000, (unsigned int)g_Pak_DisableOperationHeadingPackedAddress24, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)g_Pak_CheckOperationPakChangePackedAddress24_Objectdata, 0x00050000, 0x00000000,
        0x00000000, 0x00010000, 0x90000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x08000801, 0x00000008, 0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24,
        (unsigned int)g_Pak_SelectPakOperationTextOnePackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000023, 0x0000FF01, 0x800E41F4,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Frontend_SelectPakOperationTextTwoPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000004, 0x0000FF01,
        0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Frontend_SelectPakOperationTextThreePackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000004,
        0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Frontend_SelectPakOperationTextFourPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010041,
        0x00000004, 0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Frontend_SelectPakOperationTextFivePackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000,
        0x00012001, 0x00000023, 0x0000FF01, 0x800E31C4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Frontend_SelectPakConfirmationLabelPackedAddress24_Objectdata, (unsigned int)g_Pak_ConfirmPendingOperationPackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00012001, 0x00000005, 0x0000FF01, 0x800E31D4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Menu_SelectEuropeanPakActionLabelPackedAddress24, (unsigned int)g_Timer_CancelPendingOperationPackedAddress24_Objectdata,
        0x00000000, 0x00450038, 0x00080000, (unsigned int)g_Pak_SelectPakOperationZeroPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)addrLow_Menu_SelectPakOperationActionLabel, 0x00070000,
        0x00000000, 0x00000000, 0x00450038, 0x00080000, (unsigned int)g_Pak_SelectPakOperationOnePackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)addrLow_Menu_SelectPakOperationActionLabel,
        0x00070000, 0x00000000, 0x00000000, 0x00450038, 0x00080000, (unsigned int)g_Pak_SelectPakOperationTwoPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24,
        (unsigned int)addrLow_Menu_SelectPakOperationActionLabel, 0x00070000, 0x00000000, 0x00000000, 0x00450038, 0x00080000, (unsigned int)g_Pak_SelectPakOperationThreePackedAddress24_Objectdata, 0x00000000,
        (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)addrLow_Menu_SelectPakOperationActionLabel, 0x00070000, 0x00000000, 0x00000000, 0x00450038, 0x00080000, (unsigned int)g_Pak_SelectPakOperationFourPackedAddress24_Objectdata,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)addrLow_Menu_SelectPakOperationActionLabel, 0x00070000, 0x00000000, 0x00000000, 0x00052880, 0x800EE7FC,
        0x800E3524, 0x00000020, 0x00000001, 0x800EE7EC, 0x800E3544, 0x00000080, 0x00000001, 0x800EE7E4,
        0x800E3554, 0x00000100, 0x00000001, 0x800EE7D8, 0x800E3534, 0x00000040, 0x00000001, 0x800EE7CC,
        0x800E3564, 0x00000200, 0x00000001, 0x800EE7B8, 0x800E3574, 0x00000400, 0x00000001, 0x800EE7AC,
        0x800E3584, 0x00000800, 0x00000001, 0x800EE7A4, 0x800E3594, 0x00001000, 0x00000001, 0x800EE798,
        0x800E35B4, 0x00004000, 0x00000001, 0x800EE78C, 0x800E35C4, 0x00008000, 0x00000001, 0x800EE774,
        0x800F2308, 0xFFFFFFFF, 0x00000001, 0x800EE760, 0x800F2330, 0x0400C7E0, 0x00000001, 0x00010000,
        0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x08000801, 0x00000008, 0x0000FF01, 0x800E3434, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00210041, 0x00000014, 0x0000FF01, 0x800F22E4, (unsigned int)g_Encoded_DrawTextEntryCursorPackedAddress24_Objectdata, (unsigned int)g_Encoded_UpdateTextEntryCursorPackedAddress24_Objectdata,
        (unsigned int)g_Encoded_TextEntryReturnZeroPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010050, 0x00500014, 0x0601FF07, 0x800E42B8, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata,
        0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01FE07, 0x800E42CC,
        (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01FD07,
        0x800E42E0, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFF01FC07, 0x800E42F4, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024050,
        0x00080000, 0xFF01FB07, 0x800E4308, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00024050, 0x00080000, 0xFF01FA07, 0x800E431C, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00024050, 0x00080000, 0xFFFAF907, 0x800E4330, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata,
        0x00000000, 0x00000000, 0x00010050, 0x00500008, 0x0601F907, 0x800E4344, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000,
        (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, 0x800E4358, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata,
        0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, 0x800E436C,
        (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907,
        0x800E4380, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFF01F907, 0x800E4394, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024050,
        0x00080000, 0xFF01F907, 0x800E43A8, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00024050, 0x00080000, 0xFFFAF907, 0x800E43BC, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00010050, 0x00500008, 0x0601F907, 0x800E43D0, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata,
        0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, 0x800E43E4, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000,
        (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, 0x800E43F8, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata,
        0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, 0x800E440C,
        (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907,
        0x800E4420, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFF01F907, 0x800E4434, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024050,
        0x00080000, 0xFFFAF907, 0x800E4448, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00010050, 0x00500008, 0x0601F908, 0x800E445C, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00024050, 0x00080000, 0xFF01F907, 0x800E4470, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata,
        0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F906, 0x800E4484, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000,
        (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F905, 0x800E4498, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata,
        0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F904, 0x800E44AC,
        (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_InsertTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F903,
        0x800E459C, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_DeletePreviousTextEntryCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFFFAF902, 0x800E45B0, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Encoded_ApplyCheatCodePackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00011001,
        0x00000014, 0x00000000, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Encoded_SetTextEntryResultLabelPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000,
        0x00310201, 0x00000018, 0x0000FEE2, 0x800E3474, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Menu_TryCreateMenuPackedAddress24_Objectdata, 0x00000000,
        0x004502D0, 0x00210000, (unsigned int)g_Encoded_ResetTextEntryResultPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00020000, 0x00000000,
        0x00000000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x08000021, 0x00000008, 0x0000FF01, 0x800E3404, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00411001, 0x0000000C, 0x0000FF01, 0x800E3694,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Option_UpdateOptionBit0ItemPackedAddress24_Objectdata, (unsigned int)g_Pak_ToggleTextChoicePackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01,
        0x800E36B4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Option_UpdateOptionBit1ItemPackedAddress24_Objectdata, (unsigned int)g_Option_ToggleOptionBit1PackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00411001, 0x00000000,
        0x0000FF01, 0x800E36D4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Option_UpdateOptionBit2ItemPackedAddress24_Objectdata, (unsigned int)g_Option_ToggleOptionBit2PackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00411001,
        0x00000000, 0x0000FF01, 0x800E36F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Option_UpdateOptionBit3ItemPackedAddress24_Objectdata, (unsigned int)g_Option_ToggleOptionBit3PackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00411001, 0x00000000, 0x0000FF01, 0x800E3714, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Option_UpdateOptionBit4ItemPackedAddress24_Objectdata, (unsigned int)g_Option_ToggleOptionBit4PackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00411001, 0x00000000, 0x0000FF01, 0x800E3734, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Option_UpdateOptionBit5ItemPackedAddress24_Objectdata, (unsigned int)g_Option_ToggleOptionBit5PackedAddress24_Objectdata,
        0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, 0x800E3754, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Option_UpdateOptionBit6ItemPackedAddress24_Objectdata,
        (unsigned int)g_Option_ToggleOptionBit6PackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, 0x800E3794, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24,
        (unsigned int)g_Option_UpdateOptionBit8ItemPackedAddress24_Objectdata, (unsigned int)g_Option_ToggleOptionBit8PackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, 0x800E3774,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Option_UpdateOptionBit7ItemPackedAddress24_Objectdata, (unsigned int)addrLow_CMenuProfile_EnableControllerPakAndClearState, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01,
        0x800E37B4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Option_UpdateOptionBit9ItemPackedAddress24_Objectdata, (unsigned int)g_Option_ToggleOptionBit9PackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00411001, 0x00000000,
        0x0000FF01, 0x800E37D4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Option_UpdateOptionBit10ItemPackedAddress24_Objectdata, (unsigned int)g_Option_ToggleOptionBit10PackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00411001,
        0x00000000, 0x0000FF01, 0x800E37F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Option_UpdateOptionBit11ItemPackedAddress24_Objectdata, (unsigned int)g_Option_ToggleOptionBit11PackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00411001, 0x00000000, 0x0000FF01, 0x800E3814, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Option_UpdateOptionBit12ItemPackedAddress24_Objectdata, (unsigned int)g_Option_ToggleOptionBit12PackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00411001, 0x00000000, 0x0000FF01, 0x800E3834, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Option_UpdateOptionBit13ItemPackedAddress24_Objectdata, (unsigned int)g_Option_ToggleOptionBit13PackedAddress24_Objectdata,
        0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, 0x800E3854, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Option_UpdateOptionBit14ItemPackedAddress24_Objectdata,
        (unsigned int)g_Option_ToggleOptionBit14PackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, 0x800E3874, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24,
        (unsigned int)g_Option_UpdateOptionBit15ItemPackedAddress24_Objectdata, (unsigned int)g_Option_ToggleOptionBit15PackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, 0x800E41F4,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Menu_SetSelectedLevelLabelPackedAddress24_Objectdata, (unsigned int)g_Encoded_HandleUnlockedLevelSelectionPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000201, 0x000000C0, 0x0000FF01,
        0x800E3474, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Menu_TryCreateMenuPackedAddress24_Objectdata, 0x00000000, 0x00450798, 0x00140000, 0x0043D430,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00130000, 0x00000000, 0x00000000, 0x8FBF0018, 0x00000000,
        0x00000021, 0x00000000, 0x0000FF01, 0x800E3484, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00010081, 0x00000028, 0x0000FF01, 0x800E33E4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Items_ForwardRulesLockPackedAddress24,
        0x00000000, 0x00000000, 0x00010081, 0x00000000, 0x0000FF01, 0x800E33F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000,
        (unsigned int)g_Items_HandleSessionOptionPagePackedAddress24, 0x00000000, 0x00450A90, 0x00030000, 0x00000000, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000,
        0x00010000, 0x00000000, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x00000000, 0x800E2404,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x00000000,
        0x800E2414, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011001, 0x00000000,
        0x00000000, 0x800E2424, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011001,
        0x00000000, 0x00000000, 0x800E2434, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00011001, 0x00000000, 0x00000000, 0x800E2444, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00011001, 0x00000000, 0x00000000, 0x800E2454, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x00000000, 0x800E2464, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x00000000, 0x800E23F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24,
        0x00000000, (unsigned int)g_CMenuProfile_ResetPlayerControllerProfilePackedAddress24_Objectdata, 0x00000000, 0x00450B20, 0x00080000, 0x00000000, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24,
        (unsigned int)g_CMenuProfile_HasRoundProgressPackedAddress24_Objectdata, 0x00070000, 0x00000000, 0x00450D18, 0x00000000, 0x00011001, 0x00000000, 0x0000FF02,
        0x800E2344, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_CMenuProfile_OpenPrimaryProfileMenuPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010101, 0x00000008,
        0x00000000, 0x800E2354, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_CMenuProfile_BindSelectedDebugFieldPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00411001,
        0x00000008, 0x0000FE01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_CMenuProfile_FormatProfileQuantityLabelPackedAddress24_Objectdata, (unsigned int)g_CMenuProfile_AdjustControllerSelectionPackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00411001, 0x00000002, 0x0000FF01, 0x800E23C4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_CMenuProfile_UpdateProfileModeLabelPackedAddress24_Objectdata, (unsigned int)g_CMenuProfile_ToggleProfileModePackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00010041, 0x00000005, 0x0000FF01, 0x800E23F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_CMenuProfile_OpenSecondaryProfileMenuPackedAddress24_Objectdata,
        0x00000000, 0x00450C64, 0x00050000, 0x00000000, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)g_CMenuProfile_HasSavedRoundProgressPackedAddress24_Objectdata, 0x00040000,
        0x00000000, 0x00450DD8, 0x00000460, 0x0000000B, 0x00000000, 0x00000000, 0xC2480000, 0xC4610000,
        0x40000000, 0x40000000, 0x40000000, 0x00000032, 0x00000050, 0x3DB2B8C4, 0x00010000, 0x30000000,
        0x00000000, 0x0000FF01, 0x00000387, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00030000,
        0x00410021, 0x00000000, 0x0000FF01, 0x00450D3C, (unsigned int)g_Menu_DrawMenuModelPackedAddress24_Objectdata, (unsigned int)g_CMenuProfile_GameSpeedReturnZeroPackedAddress24_Objectdata, (unsigned int)g_CMenuProfile_UpdatePlayerAnimationChoicePackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00010081, 0x00000019, 0x0000FF01, 0x800E2334, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_CMenuProfile_ProfileModeReturnZeroPackedAddress24_Objectdata, (unsigned int)g_CMenuProfile_OpenTimedPlayerDialogPackedAddress24_Objectdata,
        0x00000000, 0x00450D6C, 0x00030000, (unsigned int)g_CMenuProfile_EnableOwnerControllerPakPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)g_CMenuProfile_HasProfileRoundProgressPackedAddress24_Objectdata, 0x00010000,
        0x00000000, 0x00000000, 0x00450D6C, 0x00030000, (unsigned int)g_CMenuProfile_EnableControllerPakAndClearStatePackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)g_CMenuProfile_HasProfileRoundProgressPackedAddress24_Objectdata,
        0x00010000, 0x00000000, 0x00000000, 0x00010000, 0x30000000, 0x00000000, 0x0000FF01, 0x00000387,
        (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010081, 0x00000000, 0x0000FF01,
        0x800E2484, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010101, 0x0000000C,
        0x0000FF01, 0x800E2494, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_CMenuProfile_OpenPrimaryPlayerDialogPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010101,
        0x00000000, 0x0000FF01, 0x800E24A4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_CMenuProfile_OpenAlternatePlayerDialogPackedAddress24_Objectdata, 0x00000000, 0x00450E20,
        0x00040000, 0x00000000, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)g_CMenuProfile_HasDialogRoundProgressPackedAddress24_Objectdata, 0x00020000, 0x00000000, 0x00000000,
        0xBF000000, 0xBECCCCCD, 0xBE99999A, 0xBE4CCCCD, 0xBDCCCCCD, 0x00000000, 0x3DCCCCCD, 0x3E4CCCCD,
        0x3E99999A, 0x3ECCCCCD, 0x3F000000, 0x3F19999A, 0x3F333333, 0x3F4CCCCD, 0x3F666666, 0x3F800000,
    },
    { 0.7f },
    {
        0x3F4CCCCD, 0x3F666666, 0x3F800000, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385,
    },
    "\?fff",
    {
        0x3F800000, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x08000201, 0x0000000C, 0x0000FF01, 0x800E3E94, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00410041, 0x0000001E, 0x0000FF01, 0x800E41F4,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Items_SelectOptionRowLabelPackedAddress24, (unsigned int)g_Initial_ToggleMenuRowOptionPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01,
        0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Items_SelectOptionRowLabelPackedAddress24, (unsigned int)g_Initial_ToggleMenuRowOptionPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000,
        0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Items_SelectOptionRowLabelPackedAddress24, (unsigned int)g_Initial_ToggleMenuRowOptionPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00410041,
        0x00000000, 0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Items_SelectOptionRowLabelPackedAddress24, (unsigned int)g_Initial_ToggleMenuRowOptionPackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00410041, 0x00000000, 0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Items_SelectOptionRowLabelPackedAddress24, (unsigned int)g_Initial_ToggleMenuRowOptionPackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Items_SelectOptionRowLabelPackedAddress24, (unsigned int)g_Initial_ToggleMenuRowOptionPackedAddress24_Objectdata,
        0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Items_SelectOptionRowLabelPackedAddress24,
        (unsigned int)g_Initial_ToggleMenuRowOptionPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800E41F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24,
        (unsigned int)g_Items_SelectOptionRowLabelPackedAddress24, (unsigned int)g_Initial_ToggleMenuRowOptionPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010201, 0x0000002D, 0x0000FF01, 0x800E3474,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Menu_TryCreateMenuPackedAddress24_Objectdata, 0x00000000, 0x00450F14, 0x000B0000, 0x00000000, 0x00000000,
        (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x000A0000, 0x00000000, 0x00451154, 0x00010000, 0x10000000, 0x00000000,
        0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000021,
        0x00000008, 0x0000FF01, 0x800E3BE4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00010081, 0x00000000, 0x0000FF01, 0x800E3E94, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Initial_OpenMatchSetupMenuPackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00010201, 0x00000038, 0x0000FF01, 0x800E3474, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Menu_TryCreateMenuPackedAddress24_Objectdata,
        0x00000000, 0x004510C4, 0x00040000, 0x00000000, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00020000,
        0x00000000, 0x004513B8, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000801, 0x00000008, 0x0000FF01, 0x800E3BA4,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010081, 0x00000036, 0x0000FF01,
        0x800E3BB4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Initial_OpenDialogWithControllerPakPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010081, 0x00000004,
        0x0000FF01, 0x800E3BC4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Initial_OpenDialogAfterTimerResetPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010201,
        0x00000049, 0x0000FF01, 0x800E2314, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Initial_RequestTransitionWithPakDisabledPackedAddress24_Objectdata, 0x00000000, 0x00451178,
        0x00050000, (unsigned int)g_Initial_ProbeMenuControllerPakPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00020000, 0x00000000, 0x00000000,
        0x00451178, 0x00050000, (unsigned int)g_Initial_EnableMenuControllerPakPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00020000, 0x00000000,
        0x00000000, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000,
        0x00000000, 0x00000000, 0x00451274, 0x00010000, 0x00000000, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000,
        0x00020000, 0x00000000, 0x004513B8, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000384,
        (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000081, 0x0000001E, 0x0000FF01,
        0x800E3BA4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Initial_SelectInitialControllerPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010081, 0x0000000C,
        0x0000FF01, 0x800E3BD4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Initial_UpdateMultiplayerAvailabilityPackedAddress24_Objectdata, (unsigned int)g_Initial_OpenLocalPlayerSetupPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010081,
        0x0000000C, 0x0000FF01, 0x800E3434, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Initial_OpenDialog44F4A4PackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00010081, 0x0000000C, 0x0000FF01, 0x800E4044, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Initial_OpenDialog44F798PackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00010081, 0x0000000C, 0x0000FF01, 0x800E4034, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Initial_OpenDialog450E9CPackedAddress24_Objectdata,
        0x00000000, 0x00000000, 0x00010081, 0x0000000C, 0x0000FF01, 0x800E4074, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000,
        (unsigned int)g_Initial_OpenTrackPreviewMenuPackedAddress24_Objectdata, 0x00000000, 0x004512BC, 0x00070000, 0x00000000, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000,
        0x00010000, 0x00000000, 0x00000000, 0x26640014, 0x00010000, 0x00000000, 0x00000000, 0x00000000,
        0x00000064, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000089, 0x00000028,
        0x00000000, 0x800E45C4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Multi_DecreaseGameOverTimerPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x004513E0, 0x00020000,
        (unsigned int)g_Initial_ResetPlayerGameOverTimerPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)g_Multi_CompleteGameOverDelayPackedAddress24_Objectdata, 0x00010000, 0x00000000, 0x00000000, 0x0C0A3FB1,
        0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x08000801, 0x00000008, 0x0000FF01, 0x800E2584, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00010080, 0x00230016, 0x00000000, 0x800E4214, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24,
        0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D0,
        0x0043FD00, 0x00000000, 0x00000000, 0x10D60000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D0, 0x0043FD00, 0x00000000, 0x00000000, 0x10D60001, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D0, 0x0043FD00, 0x00000000, 0x00000000, 0x10D60002, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x000007D1, 0x0043FD00, 0x00000000, 0x00000000, 0x10E00000, 0x00010000,
        0x00024010, 0x00030000, 0x00000000, 0x000007D1, 0x0043FD00, 0x00000000, 0x00000000, 0x10E00001,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D1, 0x0043FD00, 0x00000000, 0x00000000,
        0x10E00002, 0x00010000, 0x00024010, 0x00290000, 0x00000000, 0x000007E4, 0x0043FD00, 0x00000000,
        0x00000000, 0x11080000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043FD00,
        0x00000000, 0x00000000, 0x11940000, 0x00000000, 0x00010080, 0x00230003, 0x00000000, 0x800E4224,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D2, 0x0043FD00, 0x00000000, 0x00000000, 0x10EA0000, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D2, 0x0043FD00, 0x00000000, 0x00000000, 0x10EA0001, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x000007D2, 0x0043FD00, 0x00000000, 0x00000000, 0x10EA0002, 0x00010000,
        0x00024010, 0x003C0000, 0x00000000, 0x0000080D, 0x0043FD00, 0x00000000, 0x00000000, 0x11320000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007F9, 0x0043FD00, 0x00000000, 0x00000000,
        0x111E0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007E5, 0x0043FD00, 0x00000000,
        0x00000000, 0x11090000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043FD00,
        0x00000000, 0x00000000, 0x11940001, 0x00000000, 0x00010080, 0x00230003, 0x00000000, 0x800E4234,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D3, 0x0043FD00, 0x00000000, 0x00000000, 0x10F40000, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D3, 0x0043FD00, 0x00000000, 0x00000000, 0x10F40001, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x000007D3, 0x0043FD00, 0x00000000, 0x00000000, 0x10F40002, 0x00010000,
        0x00024010, 0x003C0000, 0x00000000, 0x0000080F, 0x0043FD00, 0x00000000, 0x00000000, 0x11300000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007F8, 0x0043FD00, 0x00000000, 0x00000000,
        0x111C0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007E6, 0x0043FD00, 0x00000000,
        0x00000000, 0x110A0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043FD00,
        0x00000000, 0x00000000, 0x11940002, 0x00000000, 0x00010080, 0x00230003, 0x00000000, 0x800E4244,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D4, 0x0043FD00, 0x00000000, 0x00000000, 0x10FE0000, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D4, 0x0043FD00, 0x00000000, 0x00000000, 0x10FE0001, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x000007D4, 0x0043FD00, 0x00000000, 0x00000000, 0x10FE0002, 0x00010000,
        0x00024010, 0x003C0000, 0x00000000, 0x0000080E, 0x0043FD00, 0x00000000, 0x00000000, 0x11340000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007FC, 0x0043FD00, 0x00000000, 0x00000000,
        0x11200000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007E7, 0x0043FD00, 0x00000000,
        0x00000000, 0x110B0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043FD00,
        0x00000000, 0x00000000, 0x11940003, 0x00000000, 0x00010080, 0x00230003, 0x00000000, 0x800E4254,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D4, 0x0043FD00, 0x00000000, 0x00000000, 0x10FE0003, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D4, 0x0043FD00, 0x00000000, 0x00000000, 0x10FE0004, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x000007D4, 0x0043FD00, 0x00000000, 0x00000000, 0x10FE0005, 0x00010000,
        0x00024010, 0x003C0000, 0x00000000, 0x0000080C, 0x0043FD00, 0x00000000, 0x00000000, 0x11330000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007FB, 0x0043FD00, 0x00000000, 0x00000000,
        0x111F0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007E8, 0x0043FD00, 0x00000000,
        0x00000000, 0x110C0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043FD00,
        0x00000000, 0x00000000, 0x11940004, 0x00000000, 0x00010080, 0x00230003, 0x00000000, 0x800E4264,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00750000, 0x00000000,
        0x00000810, 0x0043FD00, 0x00000000, 0x00000000, 0x11310000, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007FA, 0x0043FD00, 0x00000000, 0x00000000, 0x111D0000, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x000007E9, 0x0043FD00, 0x00000000, 0x00000000, 0x110D0000, 0x00010000,
        0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043FD00, 0x00000000, 0x00000000, 0x11940005,
        0x00000000, 0x00010081, 0x0000001E, 0x00000000, 0x800E2594, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Multi_CreateMenuWithDefaultMusicGainPackedAddress24_Objectdata,
        0x00000000, 0x00451450, 0x00310000, (unsigned int)g_Multi_EmptyItemHookPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00300000,
        0x00000000, 0x00452544, 0x27A50020, 0x3C07800C, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01,
        0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00451B60, 0x00010000, 0x00444310,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00090000, 0x00000000, 0x00452194, 0x00451B60, 0x00010000,
        (unsigned int)g_Items_PrepareControllerReturnPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00090000, 0x00000000, 0x00000000, 0x02803821,
        0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000401, 0x00000028, 0x0000FF01, 0x800E3964, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Player_FormatPlayerPartnerStatusPackedAddress24_Objectdata,
        0x00000000, 0x00000000, 0x00010000, 0x20010001, 0x00000000, 0x00000001, 0x0000012D, (unsigned int)g_Player_DrawPulsingMenuSpritePackedAddress24_Objectdata,
        0x00000000, (unsigned int)g_Player_RespawnItemPlayerPackedAddress24_Objectdata, 0x00000000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385,
        (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000401, 0x00000028, 0x0000FF01,
        0x800E39E4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Player_FormatPlayerPartnerStatusPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010000, 0x20010001, 0xFFEC0000,
        0xEC000001, 0x0000012D, (unsigned int)g_Player_DrawPulsingMenuSpritePackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Player_RespawnItemPlayerPackedAddress24_Objectdata, 0x00000000, 0x00010000, 0x50000000,
        0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000401, 0x00000028, 0x0000FF01, 0x800E3A64, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Player_FormatPlayerPartnerStatusPackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00010000, 0x20010001, 0x00000000, 0x00000001, 0x0000012D, (unsigned int)g_Player_DrawPulsingMenuSpritePackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Player_RespawnItemPlayerPackedAddress24_Objectdata,
        0x00000000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000401, 0x00000028, 0x0000FF01, 0x800E3AE4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24,
        (unsigned int)g_Player_FormatPlayerPartnerStatusPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010000, 0x20010001, 0x00000000, 0x00000001, 0x0000012D,
        (unsigned int)g_Player_DrawPulsingMenuSpritePackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Player_RespawnItemPlayerPackedAddress24_Objectdata, 0x00000000, 0x00451BD0, 0x00030000, (unsigned int)g_Player_ConfigurePlayerMenuFlagsPackedAddress24_Objectdata, 0x00000000,
        (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)g_Player_UpdatePlayerRespawnDelayPackedAddress24_Objectdata, 0x00020000, 0x00000000, 0x00000000, 0x00451C3C, 0x00030000, (unsigned int)g_Player_ConfigurePlayerMenuFlagsPackedAddress24_Objectdata,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)g_Player_UpdatePlayerRespawnDelayPackedAddress24_Objectdata, 0x00020000, 0x00000000, 0x00000000, 0x00451CA8, 0x00030000,
        (unsigned int)g_Player_ConfigurePlayerMenuFlagsPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)g_Player_UpdatePlayerRespawnDelayPackedAddress24_Objectdata, 0x00020000, 0x00000000, 0x00000000, 0x00451D14,
        0x00030000, (unsigned int)g_Player_ConfigurePlayerMenuFlagsPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)g_Player_UpdatePlayerRespawnDelayPackedAddress24_Objectdata, 0x00020000, 0x00000000, 0x00000000,
        0x00451BD0, 0x00030000, (unsigned int)g_Player_ConfigureAndProbeControllerPakPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x000E0000, 0x00000000,
        0x00000000, 0x00451C3C, 0x00030000, (unsigned int)g_Player_ConfigureAndProbeControllerPakPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x000E0000,
        0x00000000, 0x00000000, 0x00451CA8, 0x00030000, (unsigned int)g_Player_ConfigureAndProbeControllerPakPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000,
        0x000E0000, 0x00000000, 0x00000000, 0x00451D14, 0x00030000, (unsigned int)g_Player_ConfigureAndProbeControllerPakPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24,
        0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x00451BD0, 0x00030000, (unsigned int)g_Player_ConfigureControllerPakMenuPackedAddress24_Objectdata, 0x00000000,
        (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x00451C3C, 0x00030000, (unsigned int)g_Player_ConfigureControllerPakMenuPackedAddress24_Objectdata,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x00451CA8, 0x00030000,
        (unsigned int)g_Player_ConfigureControllerPakMenuPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x00451D14,
        0x00030000, (unsigned int)g_Player_ConfigureControllerPakMenuPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x000E0000, 0x00000000, 0x00000000,
        0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x08000021, 0x00000008, 0x0000FF01, 0x800E4034, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00400041, 0x0000002A, 0x0000FF01, 0x800E20F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24,
        (unsigned int)g_Items_SelectSceneMaskTextPackedAddress24_Objectdata, (unsigned int)g_Items_CycleSceneMaskPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800E2124,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Items_SelectPlayerOption7BTextPackedAddress24_Objectdata, (unsigned int)g_Items_AdjustPlayerOption7BPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01,
        0x800E2154, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Items_SelectPlayerOption7CTextPackedAddress24_Objectdata, (unsigned int)g_Items_AdjustPlayerOption7CPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000,
        0x0000FF01, 0x800E2174, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Items_SelectPlayerOption7DTextPackedAddress24_Objectdata, (unsigned int)g_Items_AdjustPlayerOption7DPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00410041,
        0x00000000, 0x0000FF01, 0x800E21A4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Items_SelectPlayerOption7ETextPackedAddress24_Objectdata, (unsigned int)g_Items_AdjustPlayerOption7EPackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00410041, 0x00000000, 0x0000FF01, 0x800E21B4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Items_SelectFirstListModeTextPackedAddress24_Objectdata, (unsigned int)g_Items_AdjustFirstListModePackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800E21E4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Items_SelectGameOption1FTextPackedAddress24_Objectdata, (unsigned int)g_Items_AdjustGameOption1FPackedAddress24_Objectdata,
        0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800E2224, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Items_FormatPackedGameOptionPackedAddress24_Objectdata,
        (unsigned int)g_Items_AdjustPackedGameOptionPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800E2244, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24,
        (unsigned int)g_Items_FormatPlayerOption79StepPackedAddress24_Objectdata, (unsigned int)g_Items_AdjustPlayerOption79PackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800E2264,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Items_FormatPlayerOption7AStepPackedAddress24_Objectdata, (unsigned int)g_Items_AdjustPlayerOption7APackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01,
        0x800E2284, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Items_SelectPlayerFlag82TextPackedAddress24_Objectdata, (unsigned int)g_Items_TogglePlayerFlag82PackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000,
        0x0000FF01, 0x800E2294, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Items_UpdateScreenModeMenuItemPackedAddress24_Objectdata, (unsigned int)g_Items_RequestScreenModeFadePackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00410041,
        0x00000000, 0x0000FF01, 0x800E22F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Pak_FormatPackedButtonOptionPackedAddress24_Objectdata, (unsigned int)g_Pak_AdjustPackedButtonOptionPackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00410041, 0x00000000, 0x0000FF01, 0x800E2304, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_CItemValue_BindItemValueFieldPackedAddress24, (unsigned int)g_Items_AdjustLanguagePackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00010201, 0x00000013, 0x0000FF01, 0x800E2314, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Menu_TryCreateMenuPackedAddress24_Objectdata,
        0x00000000, 0x00451F30, 0x00110000, (unsigned int)g_Items_ResetScreenModeFadeCooldownPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00100000,
        0x00000000, 0x00000000, 0x80420013, 0x44820000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01,
        0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000041, 0x00000008,
        0x0000FF01, 0x800E2574, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000101,
        0x0000005D, 0x0000FF01, 0x800E33C4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00010101, 0x0000000A, 0x0000FF01, 0x800E33E4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Pak_StopMusicAndResetMatchPackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00010101, 0x00000000, 0x0000FF01, 0x800E33F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Menu_TryCreateMenuPackedAddress24_Objectdata,
        0x00000000, 0x004521C0, 0x00050000, (unsigned int)g_Pak_SetRecordTypeFourPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00040000,
        0x00000000, 0x00452544, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08002001, 0x00000008, 0x0000FF01, 0x800E4074,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00410041, 0x00000032, 0x0000FF01,
        0x800E40B4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Pak_UpdateFirstVolumeLabelPackedAddress24_Objectdata, (unsigned int)g_Pak_AdjustVolumeSlotZeroPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000,
        0x0000FF01, 0x800E40F4, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Pak_FormatVolumeSlotOnePackedAddress24_Objectdata, (unsigned int)g_Pak_AdjustVolumeSlotOnePackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00410041,
        0x00000000, 0x0000FF01, 0x800E4134, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Pak_UpdateThirdVolumeLabelPackedAddress24_Objectdata, (unsigned int)g_Pak_AdjustVolumeSlotTwoPackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00410041, 0x00000000, 0x0000FF01, 0x800E4144, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, (unsigned int)g_Pak_FormatMusicPreviewPackedAddress24_Objectdata, (unsigned int)g_Pak_SelectMusicPreviewPackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00410401, 0x00000044, 0x0000FF01, 0x800E2314, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Pak_RestoreAudioAndCloseMenuPackedAddress24_Objectdata,
        0x00000000, 0x00452298, 0x00070000, 0x00000000, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, 0x00000000, 0x00020000,
        0x00000000, 0x00000000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress24,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000041, 0x00000008, 0x0000FF01, 0x800E24F4,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000028, 0x0000FF01,
        0x800E2504, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Pak_ResumeMenuAudioPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010041, 0x00000000,
        0x0000FF01, 0x800E2514, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Pak_ReturnCallbackSuccessPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010041,
        0x00000000, 0x0000FF01, 0x800E2524, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Pak_AllocateMenuSlotOnePackedAddress24, 0x00000000, 0x00000000,
        0x00010041, 0x00000000, 0x0000FF01, 0x800E2534, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Pak_AllocateMenuSlotTwoPackedAddress24, 0x00000000,
        0x00000000, 0x00010041, 0x00000000, 0x0000FF01, 0x800E2554, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Pak_AllocateMenuSlotThreePackedAddress24,
        0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, 0x800E4074, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000,
        (unsigned int)g_Pak_OpenMusicPreviewMenuPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, 0x800E3434, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24,
        0x00000000, (unsigned int)g_Pak_AllocateMenuSlotFourPackedAddress24, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, 0x800E2564,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Pak_AllocateMenuSlotFivePackedAddress24, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01,
        0x800E2574, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, (unsigned int)g_Pak_AllocateMenuSlotSixPackedAddress24, 0x00000000, 0x004523B8, 0x000B0000, (unsigned int)g_Pak_EnterPlayerOptionsPackedAddress24_Objectdata,
        (unsigned int)g_Pak_RestoreControllerSetupPackedAddress24_Objectdata, (unsigned int)g_Pak_RenderMenuEntryCallbackPackedAddress24_Objectdata, 0x00000000, 0x00020000, 0x00000000, 0x00000000, 0x06210002, 0x00572004,
        0x00000000, 0x00000041, 0x00000000, 0x0000FF01, 0x800E3314, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress24, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00210101, 0x00000008, 0x0000FF01, 0x800F2B50, (unsigned int)g_Setup_DrawNameCursorPackedAddress24_Objectdata, (unsigned int)g_Setup_UpdateNameCursorPackedAddress24_Objectdata,
        0x00000000, 0x00000000, 0x00000000, 0x00210101, 0x00000008, 0x0000FF01, 0x800F2B60, (unsigned int)g_Setup_DrawNameCursorPackedAddress24_Objectdata,
        (unsigned int)g_Setup_UpdateNameCursorPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00210101, 0x00000008, 0x0000FF01, 0x800F2B70,
        (unsigned int)g_Setup_DrawNameCursorPackedAddress24_Objectdata, (unsigned int)g_Setup_UpdateNameCursorPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00210101, 0x00000008, 0x0000FF01,
        0x800F2B80, (unsigned int)g_Setup_DrawNameCursorPackedAddress24_Objectdata, (unsigned int)g_Setup_UpdateNameCursorPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010110, 0x0000000A,
        0x07012008, 0x800E42B8, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF012008, 0x800E42CC, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFF012008, 0x800E42E0, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00024110, 0x00060000, 0xFF012008, 0x800E42F4, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF012008, 0x800E4308, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000,
        (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF012008, 0x800E431C, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata,
        0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF012008, 0x800E4330,
        (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFFF92008,
        0x800E4344, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010110, 0x00000004,
        0x0701F808, 0x800E4358, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F808, 0x800E436C, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFF01F808, 0x800E4380, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800E4394, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800E43A8, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000,
        (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800E43BC, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata,
        0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800E43D0,
        (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFFF9F808,
        0x800E43E4, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010110, 0x00000004,
        0x0701F808, 0x800E43F8, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F808, 0x800E440C, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFF01F808, 0x800E4420, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800E4434, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800E4448, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000,
        (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800E445C, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata,
        0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800E4470,
        (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFFF9F808,
        0x800E4484, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010110, 0x00000004,
        0x0701F808, 0x800E4498, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F808, 0x800E44AC, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFF01F808, 0x800E44C0, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800E44D4, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800E44E8, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000,
        (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800E44FC, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata,
        0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800E4510,
        (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFFF9F808,
        0x800E4524, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00010110, 0x00000004,
        0x0701F8E0, 0x800E4538, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F8E0, 0x800E454C, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFF01F8E0, 0x800E4560, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000,
        0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0, 0x800E4574, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0, 0x800E41F4, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000,
        (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0, 0x800E4588, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata,
        0x00000000, (unsigned int)g_Setup_AppendNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0, 0x800E459C,
        (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_DeleteNameCharacterPackedAddress24_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFFF9F8E0,
        0x800E45B0, (unsigned int)g_Menu_DrawLocalizedMenuItemTextPackedAddress24_Objectdata, 0x00000000, (unsigned int)g_Setup_CommitPlayerNamePackedAddress24_Objectdata, 0x00000000, 0x00452570, 0x002D0000, (unsigned int)g_Setup_SetupNameSpinnerPackedAddress24_Objectdata,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress24, (unsigned int)g_Setup_HasActiveGameCountersPackedAddress24_Objectdata, 0x00050000, 0x00000000, 0x00000000, 0x01210821, 0x8C26B434,
    },
};
#endif

/* OBJECTDATA.CPP */
#if defined(VERSION_DE)
extern char addrLow_Snapshot_BeginProfileSave[];
extern char addrLow_Snapshot_BeginProfileLoad[];
extern char addrLow_Snapshot_CheckControllerPak[];
extern char addrLow_Snapshot_BeginSnapshotSave[];
extern char addrLow_Snapshot_BeginBlockLoad[];
extern char addrLow_Snapshot_SelectNote[];
extern char addrLow_Snapshot_UpdateNoteLabel[];
extern char addrLow_Snapshot_UpdateSpaceLabel[];
extern char addrLow_Snapshot_HandleMenuAction[];
extern char addrLow_Snapshot_CloseNoteBrowser[];
extern char addrLow_Snapshot_UpdateThresholdLabel[];
extern char addrLow_Pak_ConfirmProfileOrDeleteNote[];
extern char addrLow_Pak_ClosePromptByKind[];
extern char addrLow_Pak_ConfirmPendingOperation[];
extern char addrLow_Timer_CancelPendingOperation[];
extern char addrLow_Timer_CheckMenuPakChange[];
extern char addrLow_Timer_CheckChangedMenuChannel[];
extern char addrLow_Timer_UpdateManagerStatus[];
extern char addrLow_Timer_UpdateManagerChannelLabel[];
extern char g_Timer_UpdateOwnerChannelLabelEncodedCallback[];
extern char g_Timer_UpdateOperationChoiceLabelEncodedCallback[];
extern char addrLow_Timer_SetManagerHeading[];
extern char addrLow_Timer_EnableAlternatePrompt[];
extern char addrLow_Timer_DisableAlternatePrompt[];
extern char addrLow_Timer_UpdateAlternatePromptLabel[];
extern char addrLow_Timer_UpdatePreviewDepthLabel[];
extern char addrLow_Timer_FormatPreviewPageCount[];
extern char addrLow_Timer_FormatPreviewValue[];
extern char addrLow_Timer_DispatchPreviewHandle[];
extern char addrLow_Timer_FormatPreviewDottedTriple[];
extern char addrLow_Timer_UpdateAlternateActionLabel[];
extern char addrLow_Timer_OpenSelectedPrompt[];
extern char addrLow_Timer_EnableProfilePreview[];
extern char addrLow_Timer_ClearProfilePreview[];
extern char addrLow_Timer_DisablePreviewSelection[];
extern char addrLow_Timer_UpdatePreviewKindLabel[];
extern char addrLow_Menu_FormatRightAlignedName[];
extern char addrLow_Menu_FormatNoteTypeLabel[];
extern char addrLow_Pak_FormatPreviewFourDigitValue[];
extern char addrLow_Pak_UpdateProfileActionLabel[];
extern char addrLow_Pak_OpenProfileActionPrompt[];
extern char addrLow_Pak_SelectPromptKindZero[];
extern char addrLow_Pak_SelectPromptKindOne[];
extern char addrLow_Pak_SelectPromptKindTwo[];
extern char addrLow_Pak_SelectPromptKindThree[];
extern char addrLow_Pak_SelectPromptKindFour[];
extern char addrLow_Pak_SelectPromptKindFive[];
extern char addrLow_Pak_SelectPromptKindSix[];
extern char addrLow_Pak_SelectPromptKindSeven[];
extern char addrLow_Pak_SelectPromptKindEight[];
extern char addrLow_Pak_SelectPromptKindNine[];
extern char addrLow_Pak_SelectPromptKindNinePending[];
extern char addrLow_Pak_SelectPromptKindTen[];
extern char addrLow_Pak_SelectPromptKindEleven[];
extern char addrLow_Pak_SelectPromptKindTwelve[];
extern char addrLow_Pak_SelectPromptKindThirteen[];
extern char addrLow_Pak_SelectPromptKindFourteen[];
extern char addrLow_Pak_SelectPromptKindFifteen[];
extern char addrLow_Pak_SelectPromptActionHeading[];
extern char addrLow_Pak_SelectPromptTextGroupOne[];
extern char addrLow_Pak_SelectPromptTextGroupTwo[];
extern char addrLow_Pak_SelectPromptTextGroupThree[];
extern char addrLow_Pak_SelectPromptTextGroupFour[];
extern char addrLow_Pak_SelectPromptTextGroupFive[];
extern char addrLow_Pak_SelectModalPromptLabel[];
extern char addrLow_Pak_CheckOperationPakChange[];
extern char addrLow_Pak_EnableOperationHeading[];
extern char addrLow_Pak_DisableOperationHeading[];
extern char addrLow_Pak_SelectOperationHeading[];
extern char addrLow_Pak_SelectOperationDescription[];
extern char addrLow_Pak_FormatOperationChannelLabel[];
extern char addrLow_Pak_OpenPakChannel[];
extern char addrLow_Pak_OpenPakStatusPrompt[];
extern char addrLow_Pak_CancelPakAction[];
extern char addrLow_Pak_SelectPakLoadHeading[];
extern char addrLow_Pak_CheckPakActionChange[];
extern char addrLow_Pak_SelectPakOperationZero[];
extern char addrLow_Pak_SelectPakOperationOne[];
extern char addrLow_Pak_SelectPakOperationTwo[];
extern char addrLow_Pak_SelectPakOperationThree[];
extern char addrLow_Pak_SelectPakOperationFour[];
extern char addrLow_Pak_SelectPakOperationTextOne[];
extern char addrLow_Frontend_SelectPakOperationTextTwo[];
extern char addrLow_Frontend_SelectPakOperationTextThree[];
extern char addrLow_Frontend_SelectPakOperationTextFour[];
extern char addrLow_Frontend_SelectPakOperationTextFive[];
extern char addrLow_Frontend_SelectPakConfirmationLabel[];
extern char addrLow_Menu_SelectPakOperationActionLabel[];
extern char addrLow_Encoded_HandleUnlockedLevelSelection[];
extern char addrLow_Encoded_ResetTextEntryResult[];
extern char addrLow_Encoded_DrawTextEntryCursor[];
extern char addrLow_Encoded_UpdateTextEntryCursor[];
extern char addrLow_Encoded_TextEntryReturnZero[];
extern char addrLow_Encoded_InsertTextEntryCharacter[];
extern char g_Frontend_SelectPreviousEquipmentChoicePackedAddress242[];
extern char addrLow_Encoded_ApplyCheatCode[];
extern char addrLow_Encoded_SetTextEntryResultLabel[];
extern char addrLow_Menu_SetSelectedLevelLabel[];
extern char addrLow_Pak_ToggleTextChoice[];
extern char addrLow_Option_UpdateOptionBit0Item[];
extern char addrLow_Option_ToggleOptionBit1[];
extern char addrLow_Option_UpdateOptionBit1Item[];
extern char addrLow_Option_ToggleOptionBit2[];
extern char addrLow_Option_UpdateOptionBit2Item[];
extern char addrLow_Option_ToggleOptionBit3[];
extern char addrLow_Option_UpdateOptionBit3Item[];
extern char addrLow_Option_ToggleOptionBit4[];
extern char addrLow_Option_UpdateOptionBit4Item[];
extern char addrLow_Option_ToggleOptionBit5[];
extern char addrLow_Option_UpdateOptionBit5Item[];
extern char addrLow_Option_ToggleOptionBit6[];
extern char addrLow_Option_UpdateOptionBit6Item[];
extern char addrLow_Option_ToggleOptionBit7[];
extern char addrLow_Option_UpdateOptionBit7Item[];
extern char addrLow_Option_ToggleOptionBit8[];
extern char addrLow_Option_UpdateOptionBit8Item[];
extern char addrLow_Option_ToggleOptionBit9[];
extern char addrLow_Option_UpdateOptionBit9Item[];
extern char addrLow_Option_ToggleOptionBit10[];
extern char addrLow_Option_UpdateOptionBit10Item[];
extern char addrLow_Option_ToggleOptionBit11[];
extern char addrLow_Option_UpdateOptionBit11Item[];
extern char addrLow_Option_ToggleOptionBit12[];
extern char addrLow_Option_UpdateOptionBit12Item[];
extern char addrLow_Option_ToggleOptionBit13[];
extern char addrLow_Option_UpdateOptionBit13Item[];
extern char addrLow_Option_ToggleOptionBit14[];
extern char addrLow_Option_UpdateOptionBit14Item[];
extern char addrLow_Option_ToggleOptionBit15[];
extern char addrLow_Option_UpdateOptionBit15Item[];
extern char addrLow_Menu_ForwardRulesLock[];
extern char addrLow_Menu_HandleSessionOptionPage[];
extern char addrLow_Items_HandleCharacterPreviewSelectionGerman[];
extern char addrLow_Items_SelectToggleRowTextGerman[];
extern char addrLow_CMenuProfile_HasRoundProgress[];
extern char addrLow_CMenuProfile_ResetPlayerControllerProfile[];
extern char addrLow_CMenuProfile_HasSavedRoundProgress[];
extern char addrLow_CMenuProfile_AdjustControllerSelection[];
extern char addrLow_CMenuProfile_FormatProfileQuantityLabel[];
extern char addrLow_CMenuProfile_ToggleProfileMode[];
extern char addrLow_CMenuProfile_OpenPrimaryProfileMenu[];
extern char addrLow_CMenuProfile_BindSelectedDebugField[];
extern char addrLow_CMenuProfile_OpenSecondaryProfileMenu[];
extern char addrLow_CMenuProfile_UpdateProfileModeLabel[];
extern char addrLow_CMenuProfile_EnableOwnerControllerPak[];
extern char addrLow_CMenuProfile_EnableControllerPakAndClearState[];
extern char addrLow_CMenuProfile_HasProfileRoundProgress[];
extern char addrLow_CMenuProfile_OpenTimedPlayerDialog[];
extern char addrLow_CMenuProfile_ProfileModeReturnZero[];
extern char addrLow_CMenuProfile_GameSpeedReturnZero[];
extern char addrLow_CMenuProfile_HasDialogRoundProgress[];
extern char addrLow_CMenuProfile_OpenPrimaryPlayerDialog[];
extern char addrLow_CMenuProfile_OpenAlternatePlayerDialog[];
extern char g_initial_ToggleMenuRowOptionEntry[];
extern char addrLow_Initial_OpenMatchSetupMenu[];
extern char addrLow_Initial_ProbeMenuControllerPak[];
extern char addrLow_Initial_EnableMenuControllerPak[];
extern char addrLow_Initial_OpenDialogWithControllerPak[];
extern char addrLow_Initial_OpenDialogAfterTimerReset[];
extern char addrLow_Initial_RequestTransitionWithPakDisabled[];
extern char addrLow_Initial_SelectInitialController[];
extern char addrLow_Initial_UpdateMultiplayerAvailability[];
extern char addrLow_Initial_OpenLocalPlayerSetup[];
extern char addrLow_Initial_OpenDialog450E9C[];
extern char addrLow_Initial_OpenDialog44F4A4[];
extern char addrLow_Initial_OpenDialog44F798[];
extern char addrLow_Initial_OpenTrackPreviewMenu[];
extern char addrLow_Items_ResetGameOverTimer[];
extern char addrLow_Multi_CompleteGameOverDelay[];
extern char addrLow_Multi_DecreaseGameOverTimer[];
extern char addrLow_Multi_EmptyItemHook[];
extern char addrLow_Multi_CreateMenuWithDefaultMusicGain[];
extern char addrLow_Menu_DrawMenuOptionSprite[];
extern char addrLow_Menu_DrawMenuModel[];
extern char addrLow_Menu_DrawMenuEntries[];
extern char addrLow_Menu_DrawMenuItemLabel[];
extern char addrLow_Menu_DrawLocalizedMenuItemText[];
extern char addrLow_Menu_TryCreateMenu[];
extern char addrLow_Items_PrepareMenuReturnDe[];
extern char addrLow_Items_PrepareControllerReturn[];
extern char addrLow_Player_FormatPlayerPartnerStatus[];
extern char addrLow_Player_RespawnItemPlayer[];
extern char addrLow_Player_DrawPulsingMenuSprite[];
extern char addrLow_Player_UpdatePlayerRespawnDelay[];
extern char addrLow_Player_ConfigurePlayerMenuFlags[];
extern char addrLow_Player_ConfigureAndProbeControllerPak[];
extern char addrLow_Player_ConfigureControllerPakMenu[];
extern char addrLow_Items_ResetScreenModeFadeCooldown[];
extern char addrLow_Items_CycleSceneMask[];
extern char addrLow_Items_SelectSceneMaskText[];
extern char addrLow_Items_AdjustPlayerOption7B[];
extern char addrLow_Items_SelectPlayerOption7BText[];
extern char addrLow_Items_AdjustPlayerOption7C[];
extern char addrLow_Items_SelectPlayerOption7CText[];
extern char addrLow_Items_AdjustPlayerOption7D[];
extern char addrLow_Items_SelectPlayerOption7DText[];
extern char addrLow_Items_AdjustPlayerOption7E[];
extern char addrLow_Items_SelectPlayerOption7EText[];
extern char addrLow_Items_AdjustGameOption1F[];
extern char addrLow_Items_SelectGameOption1FText[];
extern char addrLow_Items_FormatPackedGameOption[];
extern char addrLow_Items_AdjustPackedGameOption[];
extern char addrLow_Items_AdjustPlayerOption79[];
extern char addrLow_Items_FormatPlayerOption79Step[];
extern char addrLow_Items_AdjustPlayerOption7A[];
extern char addrLow_Items_FormatPlayerOption7AStep[];
extern char addrLow_Items_SelectPlayerFlag82Text[];
extern char addrLow_Items_TogglePlayerFlag82[];
extern char addrLow_Items_UpdateScreenModeMenuItem[];
extern char addrLow_Items_RequestScreenModeFade[];
extern char addrLow_Pak_AdjustPackedButtonOption[];
extern char addrLow_Pak_FormatPackedButtonOption[];
extern char addrLow_Pak_StopMusicAndResetMatch[];
extern char addrLow_Pak_SetRecordTypeFour[];
extern char addrLow_Pak_ResumeMenuAudio[];
extern char addrLow_Pak_ReturnCallbackSuccess[];
extern char addrLow_Pak_OpenMenuVariantOne_de[];
extern char addrLow_Pak_OpenMenuVariantTwo_de[];
extern char addrLow_Pak_OpenMenuVariantThree_de[];
extern char addrLow_Pak_OpenMenuVariantFour_de[];
extern char addrLow_Pak_OpenMenuVariantFive_de[];
extern char addrLow_Pak_RestoreAudioAndCloseMenu[];
extern char addrLow_Pak_AdjustVolumeSlotTwo[];
extern char addrLow_Pak_UpdateThirdVolumeLabel[];
extern char addrLow_Pak_AdjustVolumeSlotZero[];
extern char addrLow_Pak_UpdateFirstVolumeLabel[];
extern char addrLow_Pak_AdjustVolumeSlotOne[];
extern char addrLow_Pak_FormatVolumeSlotOne[];
extern char addrLow_Pak_SelectMusicPreview[];
extern char addrLow_Pak_FormatMusicPreview[];
extern char addrLow_Pak_OpenMusicPreviewMenu[];
extern char addrLow_Pak_EnterPlayerOptions[];
extern char addrLow_Pak_RestoreControllerSetup[];
extern char addrLow_Pak_RenderMenuEntryCallback[];
extern char addrLow_Setup_LoadNameEditBuffer[];
extern char addrLow_Setup_UpdateNameCursor[];
extern char addrLow_Setup_AppendNameCharacter[];
extern char addrLow_Setup_DrawNameCursor[];
extern char addrLow_Setup_DeleteNameCharacter[];
extern char addrLow_Setup_CommitPlayerName[];
extern char addrLow_Setup_HasActiveGameCounters[];
struct {
    unsigned int words0[1733];
    float floats1[1];
    unsigned int words2[1];
    char text3[4];
    unsigned int words4[1819];
} k_ObjectdataEncodedWords = {
    {
        0x800D36D4, 0x00442024, (unsigned int)g_Timer_UpdateOwnerChannelLabelEncodedCallback, 0x00010000, 0x90000000, 0x00000000, 0x0000FF01, 0x00000385,
        (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000041, 0x0000000A, 0x0000FF01,
        0x800D36E4, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)g_Timer_UpdateOwnerChannelLabelEncodedCallback, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x0000FFF8,
        0x0000FF01, 0x800D373C, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)g_Timer_UpdateOperationChoiceLabelEncodedCallback, 0x00000000, 0x00000000, 0x00000000, 0x00011001,
        0x00000006, 0x0000FF01, 0x800D36E8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000,
        0x00011001, 0x00000000, 0x0000FF01, 0x800D36EC, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000,
        0x00000000, 0x00011001, 0x00000000, 0x0000FF01, 0x800D36F0, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote,
        0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, 0x800D36F4, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Snapshot_UpdateNoteLabel,
        (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, 0x800D36F8, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, 0x800D36FC,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01,
        0x800D3700, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001, 0x00000000,
        0x0000FF01, 0x800D3704, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001,
        0x00000000, 0x0000FF01, 0x800D3708, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000,
        0x00011001, 0x00000000, 0x0000FF01, 0x800D370C, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000,
        0x00000000, 0x00011001, 0x00000000, 0x0000FF01, 0x800D3710, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote,
        0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, 0x800D3714, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Snapshot_UpdateNoteLabel,
        (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, 0x800D3718, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, 0x800D371C,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01,
        0x800D3720, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001, 0x00000000,
        0x0000FF01, 0x800D3724, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001,
        0x00000003, 0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Snapshot_UpdateSpaceLabel, 0x00000000, 0x00000000, 0x00000000,
        0x00010041, 0x0000000A, 0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Timer_UpdateManagerChannelLabel, (unsigned int)addrLow_Snapshot_HandleMenuAction, 0x00000000,
        0x00000000, 0x00010041, 0x00000004, 0x0000FF01, 0x800D374C, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Timer_SetManagerHeading, (unsigned int)addrLow_Snapshot_CloseNoteBrowser,
        0x00000000, 0x0044E150, 0x00160000, (unsigned int)addrLow_Snapshot_BeginProfileLoad, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_Timer_CheckMenuPakChange, 0x00150000,
        0x00000000, 0x00000000, 0x0044E150, 0x00160000, (unsigned int)addrLow_Snapshot_BeginProfileSave, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_Timer_CheckMenuPakChange,
        0x00140000, 0x00000000, 0x00000000, 0x0044E150, 0x00160000, (unsigned int)addrLow_Snapshot_BeginBlockLoad, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries,
        (unsigned int)addrLow_Timer_CheckChangedMenuChannel, 0x00150000, 0x00000000, 0x00000000, 0x0044E150, 0x00160000, (unsigned int)addrLow_Snapshot_BeginSnapshotSave, 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_Timer_CheckChangedMenuChannel, 0x00140000, 0x00000000, 0x00000000, 0x0044E150, 0x00160000, (unsigned int)addrLow_Snapshot_CheckControllerPak,
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_Timer_UpdateManagerStatus, 0x00140000, 0x00000000, 0x00000000, 0x00010000, 0x90000000,
        0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x08000801, 0x00000008, 0x0000FF01, 0x800D37A0, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Timer_UpdateAlternatePromptLabel, 0x00000000, 0x00000000,
        0x00000000, 0x00010041, 0x00000014, 0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Timer_DispatchPreviewHandle, 0x00000000,
        0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, 0x800D37BC, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Timer_FormatPreviewDottedTriple,
        0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x0000000A, 0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        (unsigned int)addrLow_Timer_UpdatePreviewDepthLabel, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, 0x800D37B4,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Timer_FormatPreviewPageCount, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01,
        0x800D37B8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Timer_FormatPreviewValue, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000014,
        0x0000FF01, 0x800D37E4, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Timer_UpdateAlternateActionLabel, 0x00000000, 0x00000000, 0x00000000, 0x00010040,
        0x007D000A, 0x00010000, 0x800D3A64, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00408870, 0x00000000, 0x00000000,
        0x00024040, 0x000A0000, 0xFF000000, 0x800D3A68, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Timer_OpenSelectedPrompt, 0x00000000,
        0x0044E51C, 0x000A0000, (unsigned int)addrLow_Timer_EnableAlternatePrompt, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00080000, 0x00000000,
        0x00000000, 0x0044E51C, 0x000A0000, (unsigned int)addrLow_Timer_DisableAlternatePrompt, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00090000,
        0x00000000, 0x00000000, 0x00010000, 0x90000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000021, 0x00000008, 0x0000FF01, 0x800D37C0,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Timer_UpdatePreviewKindLabel, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000032, 0x0000FF01,
        0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Menu_FormatRightAlignedName, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000002,
        0x0000FF01, 0x800D37D8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Menu_FormatNoteTypeLabel, 0x00000000, 0x00000000, 0x00000000, 0x00010041,
        0x00000002, 0x0000FF01, 0x800D37DC, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Pak_FormatPreviewFourDigitValue, 0x00000000, 0x00000000, 0x00000000,
        0x00010041, 0x00000002, 0x0000FF01, 0x800D37E0, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Snapshot_UpdateThresholdLabel, 0x00000000, 0x00000000,
        0x00000000, 0x00010041, 0x00000010, 0x0000FF01, 0x800D37E4, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Pak_UpdateProfileActionLabel, 0x00000000,
        0x00000000, 0x00000000, 0x00010040, 0x007D000A, 0x00010000, 0x800D3A64, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000,
        (unsigned int)addrLow_Pak_ConfirmProfileOrDeleteNote, 0x00000000, 0x00000000, 0x00024040, 0x000A0000, 0xFF000000, 0x800D3A68, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        0x00000000, (unsigned int)addrLow_Pak_OpenProfileActionPrompt, 0x00000000, 0x0044E6CC, 0x00090000, (unsigned int)addrLow_Timer_EnableProfilePreview, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries,
        0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E6CC, 0x00090000, (unsigned int)addrLow_Timer_ClearProfilePreview, 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00080000, 0x00000000, 0x00000000, 0x0044E6CC, 0x00090000, (unsigned int)addrLow_Timer_DisablePreviewSelection,
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00080000, 0x00000000, 0x00000000, 0x00010000, 0x90000000,
        0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x08000801, 0x00000008, 0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Pak_SelectPromptActionHeading, 0x00000000, 0x00000000,
        0x00000000, 0x00010041, 0x0000001E, 0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Pak_SelectPromptTextGroupOne, 0x00000000,
        0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Pak_SelectPromptTextGroupTwo,
        0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        (unsigned int)addrLow_Pak_SelectPromptTextGroupThree, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, 0x800D3DE8,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Pak_SelectPromptTextGroupFour, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01,
        0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Pak_SelectPromptTextGroupFive, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000019,
        0x0000FF01, 0x800D37F8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Pak_SelectModalPromptLabel, (unsigned int)addrLow_Pak_ClosePromptByKind, 0x00000000, 0x0044E87C, 0x00080000,
        (unsigned int)addrLow_Pak_SelectPromptKindZero, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E87C,
        0x00080000, (unsigned int)addrLow_Pak_SelectPromptKindOne, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00070000, 0x00000000, 0x00000000,
        0x0044E87C, 0x00080000, (unsigned int)addrLow_Pak_SelectPromptKindTwo, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00070000, 0x00000000,
        0x00000000, 0x0044E87C, 0x00080000, (unsigned int)addrLow_Pak_SelectPromptKindThree, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00070000,
        0x00000000, 0x00000000, 0x0044E87C, 0x00080000, (unsigned int)addrLow_Pak_SelectPromptKindFour, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000,
        0x00070000, 0x00000000, 0x00000000, 0x0044E87C, 0x00080000, (unsigned int)addrLow_Pak_SelectPromptKindFive, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries,
        0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E87C, 0x00080000, (unsigned int)addrLow_Pak_SelectPromptKindSix, 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E87C, 0x00080000, (unsigned int)addrLow_Pak_SelectPromptKindSeven,
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E87C, 0x00080000,
        (unsigned int)addrLow_Pak_SelectPromptKindEight, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E87C,
        0x00080000, (unsigned int)addrLow_Pak_SelectPromptKindNine, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00070000, 0x00000000, 0x00000000,
        0x0044E87C, 0x00080000, (unsigned int)addrLow_Pak_SelectPromptKindNinePending, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00070000, 0x00000000,
        0x00000000, 0x0044E87C, 0x00080000, (unsigned int)addrLow_Pak_SelectPromptKindTen, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00070000,
        0x00000000, 0x00000000, 0x0044E87C, 0x00080000, (unsigned int)addrLow_Pak_SelectPromptKindEleven, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000,
        0x00070000, 0x00000000, 0x00000000, 0x0044E87C, 0x00080000, (unsigned int)addrLow_Pak_SelectPromptKindTwelve, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries,
        0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E87C, 0x00080000, (unsigned int)addrLow_Pak_SelectPromptKindFifteen, 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E87C, 0x00080000, (unsigned int)addrLow_Pak_SelectPromptKindThirteen,
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E87C, 0x00080000,
        (unsigned int)addrLow_Pak_SelectPromptKindFourteen, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x00010000,
        0x90000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x08000021, 0x00000008, 0x0000FF01, 0x800D3940, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00010041, 0x00000028, 0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Pak_SelectOperationHeading,
        0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        (unsigned int)addrLow_Pak_SelectOperationDescription, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, 0x800D3DE8,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Pak_FormatOperationChannelLabel, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000014, 0x0000FF01,
        0x800D395C, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Pak_OpenPakChannel, 0x00000000, 0x00000000, 0x00010041, 0x00000005,
        0x0000FF01, 0x800D3960, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Pak_OpenPakStatusPrompt, 0x00000000, 0x00000000, 0x00010041,
        0x00000005, 0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Pak_SelectPakLoadHeading, (unsigned int)addrLow_Pak_CancelPakAction, 0x00000000, 0x0044EC00,
        0x00080000, (unsigned int)addrLow_Pak_EnableOperationHeading, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_Pak_CheckOperationPakChange, 0x00070000, 0x00000000, 0x00000000,
        0x0044EC00, 0x00080000, (unsigned int)addrLow_Pak_DisableOperationHeading, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_Pak_CheckOperationPakChange, 0x00050000, 0x00000000,
        0x00000000, 0x00010000, 0x90000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x08000801, 0x00000008, 0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        (unsigned int)addrLow_Pak_SelectPakOperationTextOne, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000023, 0x0000FF01, 0x800D3DE8,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Frontend_SelectPakOperationTextTwo, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000004, 0x0000FF01,
        0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Frontend_SelectPakOperationTextThree, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000004,
        0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Frontend_SelectPakOperationTextFour, 0x00000000, 0x00000000, 0x00000000, 0x00010041,
        0x00000004, 0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Frontend_SelectPakOperationTextFive, 0x00000000, 0x00000000, 0x00000000,
        0x00012001, 0x00000023, 0x0000FF01, 0x800D39DC, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Frontend_SelectPakConfirmationLabel, (unsigned int)addrLow_Pak_ConfirmPendingOperation, 0x00000000,
        0x00000000, 0x00012001, 0x00000005, 0x0000FF01, 0x800D39E0, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Menu_SelectPakOperationActionLabel, (unsigned int)addrLow_Timer_CancelPendingOperation,
        0x00000000, 0x0044ED68, 0x00080000, (unsigned int)addrLow_Pak_SelectPakOperationZero, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_Pak_CheckPakActionChange, 0x00070000,
        0x00000000, 0x00000000, 0x0044ED68, 0x00080000, (unsigned int)addrLow_Pak_SelectPakOperationOne, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_Pak_CheckPakActionChange,
        0x00070000, 0x00000000, 0x00000000, 0x0044ED68, 0x00080000, (unsigned int)addrLow_Pak_SelectPakOperationTwo, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries,
        (unsigned int)addrLow_Pak_CheckPakActionChange, 0x00070000, 0x00000000, 0x00000000, 0x0044ED68, 0x00080000, (unsigned int)addrLow_Pak_SelectPakOperationThree, 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_Pak_CheckPakActionChange, 0x00070000, 0x00000000, 0x00000000, 0x0044ED68, 0x00080000, (unsigned int)addrLow_Pak_SelectPakOperationFour,
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_Pak_CheckPakActionChange, 0x00070000, 0x00000000, 0x00000000, 0x00000001, 0x800DE17C,
        0x800D3AB4, 0x00000020, 0x00000001, 0x800DE16C, 0x800D3ABC, 0x00000080, 0x00000001, 0x800DE164,
        0x800D3AC0, 0x00000100, 0x00000001, 0x800DE158, 0x800D3AB8, 0x00000040, 0x00000001, 0x800DE14C,
        0x800D3AC4, 0x00000200, 0x00000001, 0x800DE138, 0x800D3AC8, 0x00000400, 0x00000001, 0x800DE12C,
        0x800D3ACC, 0x00000800, 0x00000001, 0x800DE124, 0x800D3AD0, 0x00001000, 0x00000001, 0x800DE118,
        0x800D3AD8, 0x00004000, 0x00000001, 0x800DE10C, 0x800D3ADC, 0x00008000, 0x00000001, 0x800DE0F4,
        0x800E1C8C, 0xFFFFFFFF, 0x00000001, 0x800DE0E0, 0x800E1CA8, 0x0400C7E0, 0x00000001, 0x00010000,
        0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x08000801, 0x00000008, 0x0000FF01, 0x800D3A78, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00210041, 0x00000014, 0x0000FF01, 0x800E1C74, (unsigned int)addrLow_Encoded_DrawTextEntryCursor, (unsigned int)addrLow_Encoded_UpdateTextEntryCursor,
        (unsigned int)addrLow_Encoded_TextEntryReturnZero, 0x00000000, 0x00000000, 0x00010050, 0x00580014, 0x0601FF07, 0x800D3E1C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText,
        0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01FE07, 0x800D3E24,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01FD07,
        0x800D3E2C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFF01FC07, 0x800D3E34, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050,
        0x00080000, 0xFF01FB07, 0x800D3E3C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000,
        0x00024050, 0x00080000, 0xFF01FA07, 0x800D3E44, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000,
        0x00000000, 0x00024050, 0x00080000, 0xFFFAF907, 0x800D3E4C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter,
        0x00000000, 0x00000000, 0x00010050, 0x00580008, 0x0601F907, 0x800D3E54, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, 0x800D3E5C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText,
        0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, 0x800D3E64,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907,
        0x800D3E6C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFF01F907, 0x800D3E74, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050,
        0x00080000, 0xFF01F907, 0x800D3E7C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000,
        0x00024050, 0x00080000, 0xFFFAF907, 0x800D3E84, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000,
        0x00000000, 0x00010050, 0x00580008, 0x0601F907, 0x800D3E8C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter,
        0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, 0x800D3E94, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, 0x800D3E9C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText,
        0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, 0x800D3EA4,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907,
        0x800D3EAC, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFF01F907, 0x800D3EB4, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050,
        0x00080000, 0xFFFAF907, 0x800D3EBC, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000,
        0x00010050, 0x00580008, 0x0601F908, 0x800D3EC4, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000,
        0x00000000, 0x00024050, 0x00080000, 0xFF01F907, 0x800D3ECC, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter,
        0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F906, 0x800D3ED4, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F905, 0x800D3EDC, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText,
        0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F904, 0x800D3EE4,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F903,
        0x800D3F44, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)g_Frontend_SelectPreviousEquipmentChoicePackedAddress242, 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFFFAF902, 0x800D3F4C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_ApplyCheatCode, 0x00000000, 0x00000000, 0x00011001,
        0x00000014, 0x00000000, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Encoded_SetTextEntryResultLabel, 0x00000000, 0x00000000, 0x00000000,
        0x00310201, 0x00000018, 0x0000FEE2, 0x800D3A88, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Menu_TryCreateMenu, 0x00000000,
        0x0044F000, 0x00210000, (unsigned int)addrLow_Encoded_ResetTextEntryResult, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00020000, 0x00000000,
        0x00000000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x08000801, 0x00000008, 0x0000FF01, 0x800D3A6C, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00411001, 0x0000000C, 0x0000FF01, 0x800D3B10,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Option_UpdateOptionBit0Item, (unsigned int)addrLow_Pak_ToggleTextChoice, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01,
        0x800D3B18, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Option_UpdateOptionBit1Item, (unsigned int)addrLow_Option_ToggleOptionBit1, 0x00000000, 0x00000000, 0x00411001, 0x00000000,
        0x0000FF01, 0x800D3B20, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Option_UpdateOptionBit2Item, (unsigned int)addrLow_Option_ToggleOptionBit2, 0x00000000, 0x00000000, 0x00411001,
        0x00000000, 0x0000FF01, 0x800D3B28, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Option_UpdateOptionBit3Item, (unsigned int)addrLow_Option_ToggleOptionBit3, 0x00000000, 0x00000000,
        0x00411001, 0x00000000, 0x0000FF01, 0x800D3B30, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Option_UpdateOptionBit4Item, (unsigned int)addrLow_Option_ToggleOptionBit4, 0x00000000,
        0x00000000, 0x00411001, 0x00000000, 0x0000FF01, 0x800D3B38, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Option_UpdateOptionBit5Item, (unsigned int)addrLow_Option_ToggleOptionBit5,
        0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, 0x800D3B40, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Option_UpdateOptionBit6Item,
        (unsigned int)addrLow_Option_ToggleOptionBit6, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, 0x800D3B50, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        (unsigned int)addrLow_Option_UpdateOptionBit8Item, (unsigned int)addrLow_Option_ToggleOptionBit8, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, 0x800D3B48,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Option_UpdateOptionBit7Item, (unsigned int)addrLow_Option_ToggleOptionBit7, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01,
        0x800D3B58, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Option_UpdateOptionBit9Item, (unsigned int)addrLow_Option_ToggleOptionBit9, 0x00000000, 0x00000000, 0x00411001, 0x00000000,
        0x0000FF01, 0x800D3B60, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Option_UpdateOptionBit10Item, (unsigned int)addrLow_Option_ToggleOptionBit10, 0x00000000, 0x00000000, 0x00411001,
        0x00000000, 0x0000FF01, 0x800D3B68, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Option_UpdateOptionBit11Item, (unsigned int)addrLow_Option_ToggleOptionBit11, 0x00000000, 0x00000000,
        0x00411001, 0x00000000, 0x0000FF01, 0x800D3B70, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Option_UpdateOptionBit12Item, (unsigned int)addrLow_Option_ToggleOptionBit12, 0x00000000,
        0x00000000, 0x00411001, 0x00000000, 0x0000FF01, 0x800D3B78, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Option_UpdateOptionBit13Item, (unsigned int)addrLow_Option_ToggleOptionBit13,
        0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, 0x800D3B80, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Option_UpdateOptionBit14Item,
        (unsigned int)addrLow_Option_ToggleOptionBit14, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, 0x800D3B88, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        (unsigned int)addrLow_Option_UpdateOptionBit15Item, (unsigned int)addrLow_Option_ToggleOptionBit15, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, 0x800D3DE8,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Menu_SetSelectedLevelLabel, (unsigned int)addrLow_Encoded_HandleUnlockedLevelSelection, 0x00000000, 0x00000000, 0x00000201, 0x000000C0, 0x0000FF01,
        0x800D3A88, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Menu_TryCreateMenu, 0x00000000, 0x0044F4C8, 0x00140000, 0x0043C550,
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00130000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000021, 0x00000000, 0x0000FF01, 0x800D3A8C, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00010081, 0x00000028, 0x0000FF01, 0x800D3A64, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Menu_ForwardRulesLock,
        0x00000000, 0x00000000, 0x00010081, 0x00000000, 0x0000FF01, 0x800D3A68, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000,
        (unsigned int)addrLow_Menu_HandleSessionOptionPage, 0x00000000, 0x0044F7C0, 0x00030000, 0x00000000, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000,
        0x00010000, 0x00000000, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x00000000, 0x800D366C,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x00000000,
        0x800D3670, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011001, 0x00000000,
        0x00000000, 0x800D3674, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011001,
        0x00000000, 0x00000000, 0x800D3678, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00011001, 0x00000000, 0x00000000, 0x800D367C, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00011001, 0x00000000, 0x00000000, 0x800D3680, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x00000000, 0x800D3684, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x00000000, 0x800D3688, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x00000000, 0x800D3668,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_CMenuProfile_ResetPlayerControllerProfile, 0x00000000, 0x0044F850, 0x00090000, 0x00000000, 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_CMenuProfile_HasRoundProgress, 0x00080000, 0x00000000, 0x0044FA6C, 0x00000000, 0x00011001, 0x00000000,
        0x0000FF02, 0x800D363C, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_CMenuProfile_OpenPrimaryProfileMenu, 0x00000000, 0x00000000, 0x00010101,
        0x00000008, 0x00000000, 0x800D3640, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_CMenuProfile_BindSelectedDebugField, 0x00000000, 0x00000000, 0x00000000,
        0x00411001, 0x00000008, 0x0000FE01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_CMenuProfile_FormatProfileQuantityLabel, (unsigned int)addrLow_CMenuProfile_AdjustControllerSelection, 0x00000000,
        0x00000000, 0x00411001, 0x00000002, 0x0000FF01, 0x800D365C, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_CMenuProfile_UpdateProfileModeLabel, (unsigned int)addrLow_CMenuProfile_ToggleProfileMode,
        0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, 0x800D3668, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000,
        (unsigned int)addrLow_CMenuProfile_OpenSecondaryProfileMenu, 0x00000000, 0x0044F9B8, 0x00050000, 0x00000000, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_CMenuProfile_HasSavedRoundProgress,
        0x00040000, 0x00000000, 0x0044FB2C, 0x00000460, 0x0000000B, 0x00000000, 0x00000000, 0xC2480000,
        0xC4610000, 0x40000000, 0x40000000, 0x40000000, 0x00000032, 0x00000050, 0x3DB2B8C4, 0x00010000,
        0x30000000, 0x00000000, 0x0000FF01, 0x00000387, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000,
        0x00030000, 0x00410021, 0x00000000, 0x0000FF01, 0x0044FA90, (unsigned int)addrLow_Menu_DrawMenuModel, (unsigned int)addrLow_CMenuProfile_GameSpeedReturnZero, (unsigned int)addrLow_Items_HandleCharacterPreviewSelectionGerman,
        0x00000000, 0x00000000, 0x00010081, 0x00000019, 0x0000FF01, 0x800D3638, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_CMenuProfile_ProfileModeReturnZero,
        (unsigned int)addrLow_CMenuProfile_OpenTimedPlayerDialog, 0x00000000, 0x0044FAC0, 0x00030000, (unsigned int)addrLow_CMenuProfile_EnableOwnerControllerPak, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_CMenuProfile_HasProfileRoundProgress,
        0x00010000, 0x00000000, 0x00000000, 0x0044FAC0, 0x00030000, (unsigned int)addrLow_CMenuProfile_EnableControllerPakAndClearState, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries,
        (unsigned int)addrLow_CMenuProfile_HasProfileRoundProgress, 0x00010000, 0x00000000, 0x00000000, 0x00010000, 0x30000000, 0x00000000, 0x0000FF01,
        0x00000387, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010081, 0x00000000,
        0x0000FF01, 0x800D368C, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010101,
        0x0000000C, 0x0000FF01, 0x800D3690, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_CMenuProfile_OpenPrimaryPlayerDialog, 0x00000000, 0x00000000,
        0x00010101, 0x00000000, 0x0000FF01, 0x800D3694, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_CMenuProfile_OpenAlternatePlayerDialog, 0x00000000,
        0x0044FB74, 0x00040000, 0x00000000, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_CMenuProfile_HasDialogRoundProgress, 0x00020000, 0x00000000,
        0x00000000, 0xBF000000, 0xBECCCCCD, 0xBE99999A, 0xBE4CCCCD, 0xBDCCCCCD, 0x00000000, 0x3DCCCCCD,
        0x3E4CCCCD, 0x3E99999A, 0x3ECCCCCD, 0x3F000000, 0x3F19999A, 0x3F333333, 0x3F4CCCCD, 0x3F666666,
    },
    { 0.7f },
    {
        0x3F4CCCCD, 0x3F666666, 0x3F800000, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385,
    },
    "\?fff",
    {
        0x3F800000, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x08000201, 0x0000000C, 0x0000FF01, 0x800D3D10, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00410041, 0x0000001E, 0x0000FF01, 0x800D3DE8,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Items_SelectToggleRowTextGerman, (unsigned int)g_initial_ToggleMenuRowOptionEntry, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01,
        0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Items_SelectToggleRowTextGerman, (unsigned int)g_initial_ToggleMenuRowOptionEntry, 0x00000000, 0x00000000, 0x00410041, 0x00000000,
        0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Items_SelectToggleRowTextGerman, (unsigned int)g_initial_ToggleMenuRowOptionEntry, 0x00000000, 0x00000000, 0x00410041,
        0x00000000, 0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Items_SelectToggleRowTextGerman, (unsigned int)g_initial_ToggleMenuRowOptionEntry, 0x00000000, 0x00000000,
        0x00410041, 0x00000000, 0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Items_SelectToggleRowTextGerman, (unsigned int)g_initial_ToggleMenuRowOptionEntry, 0x00000000,
        0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Items_SelectToggleRowTextGerman, (unsigned int)g_initial_ToggleMenuRowOptionEntry,
        0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Items_SelectToggleRowTextGerman,
        (unsigned int)g_initial_ToggleMenuRowOptionEntry, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800D3DE8, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        (unsigned int)addrLow_Items_SelectToggleRowTextGerman, (unsigned int)g_initial_ToggleMenuRowOptionEntry, 0x00000000, 0x00000000, 0x00010201, 0x0000002D, 0x0000FF01, 0x800D3A88,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Menu_TryCreateMenu, 0x00000000, 0x0044FC68, 0x000B0000, 0x00000000, 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x000A0000, 0x00000000, 0x0044FEA8, 0x00010000, 0x10000000, 0x00000000,
        0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000801,
        0x00000008, 0x0000FF01, 0x800D3C64, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00010081, 0x00000000, 0x0000FF01, 0x800D3D10, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Initial_OpenMatchSetupMenu, 0x00000000,
        0x00000000, 0x00010201, 0x00000038, 0x0000FF01, 0x800D3A88, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Menu_TryCreateMenu,
        0x00000000, 0x0044FE18, 0x00040000, 0x00000000, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00020000,
        0x00000000, 0x0045010C, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000021, 0x00000008, 0x0000FF01, 0x800D3C54,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010081, 0x00000036, 0x0000FF01,
        0x800D3C58, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Initial_OpenDialogWithControllerPak, 0x00000000, 0x00000000, 0x00010081, 0x00000004,
        0x0000FF01, 0x800D3C5C, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Initial_OpenDialogAfterTimerReset, 0x00000000, 0x00000000, 0x00010201,
        0x00000049, 0x0000FF01, 0x800D3630, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Initial_RequestTransitionWithPakDisabled, 0x00000000, 0x0044FECC,
        0x00050000, (unsigned int)addrLow_Initial_ProbeMenuControllerPak, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00020000, 0x00000000, 0x00000000,
        0x0044FECC, 0x00050000, (unsigned int)addrLow_Initial_EnableMenuControllerPak, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00020000, 0x00000000,
        0x00000000, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000,
        0x00000000, 0x00000000, 0x0044FFC8, 0x00010000, 0x00000000, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000,
        0x00020000, 0x00000000, 0x0045010C, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000384,
        (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000081, 0x0000001E, 0x0000FF01,
        0x800D3C54, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Initial_SelectInitialController, 0x00000000, 0x00000000, 0x00010081, 0x0000000C,
        0x0000FF01, 0x800D3C60, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Initial_UpdateMultiplayerAvailability, (unsigned int)addrLow_Initial_OpenLocalPlayerSetup, 0x00000000, 0x00000000, 0x00010081,
        0x0000000C, 0x0000FF01, 0x800D3A78, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Initial_OpenDialog44F4A4, 0x00000000, 0x00000000,
        0x00010081, 0x0000000C, 0x0000FF01, 0x800D3D7C, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Initial_OpenDialog44F798, 0x00000000,
        0x00000000, 0x00010081, 0x0000000C, 0x0000FF01, 0x800D3D78, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Initial_OpenDialog450E9C,
        0x00000000, 0x00000000, 0x00010081, 0x0000000C, 0x0000FF01, 0x800D3D88, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000,
        (unsigned int)addrLow_Initial_OpenTrackPreviewMenu, 0x00000000, 0x00450010, 0x00070000, 0x00000000, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000,
        0x00010000, 0x00000000, 0x00000000, 0x00010000, 0x00000000, 0x00000000, 0x00000000, 0x00000064,
        (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000089, 0x00000028, 0x00000000,
        0x800D3F54, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Multi_DecreaseGameOverTimer, 0x00000000, 0x00000000, 0x00450130, 0x00020000, (unsigned int)addrLow_Items_ResetGameOverTimer,
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_Multi_CompleteGameOverDelay, 0x00010000, 0x00000000, 0x00000000, 0x00000000, 0x00010000,
        0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x08000801, 0x00000008, 0x0000FF01, 0x800D36CC, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00010080, 0x00230016, 0x00000000, 0x800D3DF0, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000,
        0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D0, 0x0043EE60,
        0x00000000, 0x00000000, 0x10D60000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D0,
        0x0043EE60, 0x00000000, 0x00000000, 0x10D60001, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D0, 0x0043EE60, 0x00000000, 0x00000000, 0x10D60002, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D1, 0x0043EE60, 0x00000000, 0x00000000, 0x10E00000, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x000007D1, 0x0043EE60, 0x00000000, 0x00000000, 0x10E00001, 0x00010000,
        0x00024010, 0x00030000, 0x00000000, 0x000007D1, 0x0043EE60, 0x00000000, 0x00000000, 0x10E00002,
        0x00010000, 0x00024010, 0x00290000, 0x00000000, 0x000007E4, 0x0043EE60, 0x00000000, 0x00000000,
        0x11080000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043EE60, 0x00000000,
        0x00000000, 0x11940000, 0x00000000, 0x00010080, 0x00230003, 0x00000000, 0x800D3DF4, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D2,
        0x0043EE60, 0x00000000, 0x00000000, 0x10EA0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D2, 0x0043EE60, 0x00000000, 0x00000000, 0x10EA0001, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D2, 0x0043EE60, 0x00000000, 0x00000000, 0x10EA0002, 0x00010000, 0x00024010,
        0x003C0000, 0x00000000, 0x0000080D, 0x0043EE60, 0x00000000, 0x00000000, 0x11320000, 0x00010000,
        0x00024010, 0x00030000, 0x00000000, 0x000007F9, 0x0043EE60, 0x00000000, 0x00000000, 0x111E0000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007E5, 0x0043EE60, 0x00000000, 0x00000000,
        0x11090000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043EE60, 0x00000000,
        0x00000000, 0x11940001, 0x00000000, 0x00010080, 0x00230003, 0x00000000, 0x800D3DF8, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D3,
        0x0043EE60, 0x00000000, 0x00000000, 0x10F40000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D3, 0x0043EE60, 0x00000000, 0x00000000, 0x10F40001, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D3, 0x0043EE60, 0x00000000, 0x00000000, 0x10F40002, 0x00010000, 0x00024010,
        0x003C0000, 0x00000000, 0x0000080F, 0x0043EE60, 0x00000000, 0x00000000, 0x11300000, 0x00010000,
        0x00024010, 0x00030000, 0x00000000, 0x000007F8, 0x0043EE60, 0x00000000, 0x00000000, 0x111C0000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007E6, 0x0043EE60, 0x00000000, 0x00000000,
        0x110A0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043EE60, 0x00000000,
        0x00000000, 0x11940002, 0x00000000, 0x00010080, 0x00230003, 0x00000000, 0x800D3DFC, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D4,
        0x0043EE60, 0x00000000, 0x00000000, 0x10FE0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D4, 0x0043EE60, 0x00000000, 0x00000000, 0x10FE0001, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D4, 0x0043EE60, 0x00000000, 0x00000000, 0x10FE0002, 0x00010000, 0x00024010,
        0x003C0000, 0x00000000, 0x0000080E, 0x0043EE60, 0x00000000, 0x00000000, 0x11340000, 0x00010000,
        0x00024010, 0x00030000, 0x00000000, 0x000007FC, 0x0043EE60, 0x00000000, 0x00000000, 0x11200000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007E7, 0x0043EE60, 0x00000000, 0x00000000,
        0x110B0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043EE60, 0x00000000,
        0x00000000, 0x11940003, 0x00000000, 0x00010080, 0x00230003, 0x00000000, 0x800D3E00, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D4,
        0x0043EE60, 0x00000000, 0x00000000, 0x10FE0003, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D4, 0x0043EE60, 0x00000000, 0x00000000, 0x10FE0004, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D4, 0x0043EE60, 0x00000000, 0x00000000, 0x10FE0005, 0x00010000, 0x00024010,
        0x003C0000, 0x00000000, 0x0000080C, 0x0043EE60, 0x00000000, 0x00000000, 0x11330000, 0x00010000,
        0x00024010, 0x00030000, 0x00000000, 0x000007FB, 0x0043EE60, 0x00000000, 0x00000000, 0x111F0000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007E8, 0x0043EE60, 0x00000000, 0x00000000,
        0x110C0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043EE60, 0x00000000,
        0x00000000, 0x11940004, 0x00000000, 0x00010080, 0x00230003, 0x00000000, 0x800D3E04, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00750000, 0x00000000, 0x00000810,
        0x0043EE60, 0x00000000, 0x00000000, 0x11310000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007FA, 0x0043EE60, 0x00000000, 0x00000000, 0x111D0000, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007E9, 0x0043EE60, 0x00000000, 0x00000000, 0x110D0000, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x00000820, 0x0043EE60, 0x00000000, 0x00000000, 0x11940005, 0x00000000,
        0x00010081, 0x0000001E, 0x00000000, 0x800D36D0, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Multi_CreateMenuWithDefaultMusicGain, 0x00000000,
        0x004501A0, 0x00310000, (unsigned int)addrLow_Multi_EmptyItemHook, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00300000, 0x00000000,
        0x00451220, 0x00000000, 0x00090000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385,
        (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000, 0x004508B0, 0x00010000, (unsigned int)addrLow_Items_PrepareMenuReturnDe, 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00090000, 0x00000000, 0x00450E9C, 0x004508B0, 0x00010000, (unsigned int)addrLow_Items_PrepareControllerReturn,
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00090000, 0x00000000, 0x00000000, 0x004434A0, 0x00010000,
        0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000401, 0x00000028, 0x0000FF01, 0x800D3BC4, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Player_FormatPlayerPartnerStatus, 0x00000000,
        0x00000000, 0x00010000, 0x20010001, 0x00000000, 0x00000001, 0x0000012D, (unsigned int)addrLow_Player_DrawPulsingMenuSprite, 0x00000000,
        (unsigned int)addrLow_Player_RespawnItemPlayer, 0x00000000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000401, 0x00000028, 0x0000FF01, 0x800D3BE4,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Player_FormatPlayerPartnerStatus, 0x00000000, 0x00000000, 0x00010000, 0x20010001, 0xFFEC0000, 0xEC000001,
        0x0000012D, (unsigned int)addrLow_Player_DrawPulsingMenuSprite, 0x00000000, (unsigned int)addrLow_Player_RespawnItemPlayer, 0x00000000, 0x00010000, 0x50000000, 0x00000000,
        0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000401,
        0x00000028, 0x0000FF01, 0x800D3C04, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Player_FormatPlayerPartnerStatus, 0x00000000, 0x00000000, 0x00010000,
        0x20010001, 0x00000000, 0x00000001, 0x0000012D, (unsigned int)addrLow_Player_DrawPulsingMenuSprite, 0x00000000, (unsigned int)addrLow_Player_RespawnItemPlayer, 0x00000000,
        0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000401, 0x00000028, 0x0000FF01, 0x800D3C24, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Player_FormatPlayerPartnerStatus,
        0x00000000, 0x00000000, 0x00010000, 0x20010001, 0x00000000, 0x00000001, 0x0000012D, (unsigned int)addrLow_Player_DrawPulsingMenuSprite,
        0x00000000, (unsigned int)addrLow_Player_RespawnItemPlayer, 0x00000000, 0x00450920, 0x00030000, (unsigned int)addrLow_Player_ConfigurePlayerMenuFlags, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries,
        (unsigned int)addrLow_Player_UpdatePlayerRespawnDelay, 0x00020000, 0x00000000, 0x00000000, 0x0045098C, 0x00030000, (unsigned int)addrLow_Player_ConfigurePlayerMenuFlags, 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_Player_UpdatePlayerRespawnDelay, 0x00020000, 0x00000000, 0x00000000, 0x004509F8, 0x00030000, (unsigned int)addrLow_Player_ConfigurePlayerMenuFlags,
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_Player_UpdatePlayerRespawnDelay, 0x00020000, 0x00000000, 0x00000000, 0x00450A64, 0x00030000,
        (unsigned int)addrLow_Player_ConfigurePlayerMenuFlags, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_Player_UpdatePlayerRespawnDelay, 0x00020000, 0x00000000, 0x00000000, 0x00450920,
        0x00030000, (unsigned int)addrLow_Player_ConfigureAndProbeControllerPak, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x000E0000, 0x00000000, 0x00000000,
        0x0045098C, 0x00030000, (unsigned int)addrLow_Player_ConfigureAndProbeControllerPak, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x000E0000, 0x00000000,
        0x00000000, 0x004509F8, 0x00030000, (unsigned int)addrLow_Player_ConfigureAndProbeControllerPak, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x000E0000,
        0x00000000, 0x00000000, 0x00450A64, 0x00030000, (unsigned int)addrLow_Player_ConfigureAndProbeControllerPak, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000,
        0x000E0000, 0x00000000, 0x00000000, 0x00450920, 0x00030000, (unsigned int)addrLow_Player_ConfigureControllerPakMenu, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries,
        0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x0045098C, 0x00030000, (unsigned int)addrLow_Player_ConfigureControllerPakMenu, 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x004509F8, 0x00030000, (unsigned int)addrLow_Player_ConfigureControllerPakMenu,
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x00450A64, 0x00030000,
        (unsigned int)addrLow_Player_ConfigureControllerPakMenu, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x00010000,
        0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x08000021, 0x00000008, 0x0000FF01, 0x800D3D78, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00400041, 0x0000002F, 0x0000FF01, 0x800D35A8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Items_SelectSceneMaskText,
        (unsigned int)addrLow_Items_CycleSceneMask, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800D35B4, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        (unsigned int)addrLow_Items_SelectPlayerOption7BText, (unsigned int)addrLow_Items_AdjustPlayerOption7B, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800D35C0,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Items_SelectPlayerOption7CText, (unsigned int)addrLow_Items_AdjustPlayerOption7C, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01,
        0x800D35C8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Items_SelectPlayerOption7DText, (unsigned int)addrLow_Items_AdjustPlayerOption7D, 0x00000000, 0x00000000, 0x00410041, 0x00000000,
        0x0000FF01, 0x800D35D4, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Items_SelectPlayerOption7EText, (unsigned int)addrLow_Items_AdjustPlayerOption7E, 0x00000000, 0x00000000, 0x00410041,
        0x00000000, 0x0000FF01, 0x800D35E4, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Items_SelectGameOption1FText, (unsigned int)addrLow_Items_AdjustGameOption1F, 0x00000000, 0x00000000,
        0x00410041, 0x00000000, 0x0000FF01, 0x800D35F4, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Items_FormatPackedGameOption, (unsigned int)addrLow_Items_AdjustPackedGameOption, 0x00000000,
        0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800D35FC, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Items_FormatPlayerOption79Step, (unsigned int)addrLow_Items_AdjustPlayerOption79,
        0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800D3604, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Items_FormatPlayerOption7AStep,
        (unsigned int)addrLow_Items_AdjustPlayerOption7A, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800D360C, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        (unsigned int)addrLow_Items_SelectPlayerFlag82Text, (unsigned int)addrLow_Items_TogglePlayerFlag82, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800D3610,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Items_UpdateScreenModeMenuItem, (unsigned int)addrLow_Items_RequestScreenModeFade, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01,
        0x800D3628, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Pak_FormatPackedButtonOption, (unsigned int)addrLow_Pak_AdjustPackedButtonOption, 0x00000000, 0x00000000, 0x00010201, 0x0000001E,
        0x0000FF01, 0x800D3630, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Menu_TryCreateMenu, 0x00000000, 0x00450C80, 0x000F0000,
        (unsigned int)addrLow_Items_ResetScreenModeFadeCooldown, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x00010000,
        0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x08000041, 0x00000008, 0x0000FF01, 0x800D36C8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000101, 0x0000005D, 0x0000FF01, 0x800D3A5C, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00010101, 0x0000000A, 0x0000FF01, 0x800D3A64, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        0x00000000, (unsigned int)addrLow_Pak_StopMusicAndResetMatch, 0x00000000, 0x00000000, 0x00010101, 0x00000000, 0x0000FF01, 0x800D3A68,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Menu_TryCreateMenu, 0x00000000, 0x00450EC0, 0x00050000, (unsigned int)addrLow_Pak_SetRecordTypeFour, 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00040000, 0x00000000, 0x00451220, 0x00010000, 0x50000000, 0x00000000,
        0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08002001,
        0x00000008, 0x0000FF01, 0x800D3D88, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00410041, 0x00000032, 0x0000FF01, 0x800D3D98, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Pak_UpdateFirstVolumeLabel, (unsigned int)addrLow_Pak_AdjustVolumeSlotZero, 0x00000000,
        0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800D3DA8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Pak_FormatVolumeSlotOne, (unsigned int)addrLow_Pak_AdjustVolumeSlotOne,
        0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800D3DB8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Pak_UpdateThirdVolumeLabel,
        (unsigned int)addrLow_Pak_AdjustVolumeSlotTwo, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, 0x800D3DBC, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        (unsigned int)addrLow_Pak_FormatMusicPreview, (unsigned int)addrLow_Pak_SelectMusicPreview, 0x00000000, 0x00000000, 0x00410401, 0x00000044, 0x0000FF01, 0x800D3630,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Pak_RestoreAudioAndCloseMenu, 0x00000000, 0x00450F98, 0x00070000, 0x00000000, 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries, 0x00000000, 0x00020000, 0x00000000, 0x00000000, 0x00010000, 0x50000000, 0x00000000,
        0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000041,
        0x00000008, 0x0000FF01, 0x800D36A8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00010041, 0x00000028, 0x0000FF01, 0x800D36AC, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Pak_ResumeMenuAudio, 0x00000000,
        0x00000000, 0x00010041, 0x00000000, 0x0000FF01, 0x800D36B0, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Pak_ReturnCallbackSuccess,
        0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, 0x800D36B8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000,
        (unsigned int)addrLow_Pak_OpenMenuVariantOne_de, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, 0x800D36C0, (unsigned int)addrLow_Menu_DrawMenuItemLabel,
        0x00000000, (unsigned int)addrLow_Pak_OpenMenuVariantTwo_de, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, 0x800D3D88,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Pak_OpenMusicPreviewMenu, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01,
        0x800D3A78, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Pak_OpenMenuVariantThree_de, 0x00000000, 0x00000000, 0x00010041, 0x00000000,
        0x0000FF01, 0x800D36C4, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Pak_OpenMenuVariantFour_de, 0x00000000, 0x00000000, 0x00010041,
        0x00000000, 0x0000FF01, 0x800D36C8, (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_Pak_OpenMenuVariantFive_de, 0x00000000, 0x004510B8,
        0x000A0000, (unsigned int)addrLow_Pak_EnterPlayerOptions, (unsigned int)addrLow_Pak_RestoreControllerSetup, (unsigned int)addrLow_Pak_RenderMenuEntryCallback, 0x00000000, 0x00020000, 0x00000000, 0x00000000,
        0x800E2150, 0x00445B80, 0x00445924, 0x00000000, 0x00000041, 0x00000000, 0x0000FF01, 0x800D3A30,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00210101, 0x00000008, 0x0000FF01,
        0x800E2160, (unsigned int)addrLow_Setup_DrawNameCursor, (unsigned int)addrLow_Setup_UpdateNameCursor, 0x00000000, 0x00000000, 0x00000000, 0x00210101, 0x00000008,
        0x0000FF01, 0x800E2164, (unsigned int)addrLow_Setup_DrawNameCursor, (unsigned int)addrLow_Setup_UpdateNameCursor, 0x00000000, 0x00000000, 0x00000000, 0x00210101,
        0x00000008, 0x0000FF01, 0x800E2168, (unsigned int)addrLow_Setup_DrawNameCursor, (unsigned int)addrLow_Setup_UpdateNameCursor, 0x00000000, 0x00000000, 0x00000000,
        0x00210101, 0x00000008, 0x0000FF01, 0x800E216C, (unsigned int)addrLow_Setup_DrawNameCursor, (unsigned int)addrLow_Setup_UpdateNameCursor, 0x00000000, 0x00000000,
        0x00000000, 0x00010110, 0x0000000A, 0x07012008, 0x800D3E1C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF012008, 0x800D3E24, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF012008, 0x800D3E2C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText,
        0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF012008, 0x800D3E34,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF012008,
        0x800D3E3C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000,
        0xFF012008, 0x800D3E44, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF012008, 0x800D3E4C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFFF92008, 0x800D3E54, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000,
        0x00000000, 0x00010110, 0x00000004, 0x0701F808, 0x800D3E5C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800D3E64, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800D3E6C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText,
        0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800D3E74,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808,
        0x800D3E7C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000,
        0xFF01F808, 0x800D3E84, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F808, 0x800D3E8C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFFF9F808, 0x800D3E94, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000,
        0x00000000, 0x00010110, 0x00000004, 0x0701F808, 0x800D3E9C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800D3EA4, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800D3EAC, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText,
        0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800D3EB4,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808,
        0x800D3EBC, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000,
        0xFF01F808, 0x800D3EC4, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F808, 0x800D3ECC, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFFF9F808, 0x800D3ED4, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000,
        0x00000000, 0x00010110, 0x00000004, 0x0701F808, 0x800D3EDC, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800D3EE4, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800D3EEC, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText,
        0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, 0x800D3EF4,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808,
        0x800D3EFC, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000,
        0xFF01F808, 0x800D3F04, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F808, 0x800D3F0C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFFF9F808, 0x800D3F14, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000,
        0x00000000, 0x00010110, 0x00000004, 0x0701F8E0, 0x800D3F1C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0, 0x800D3F24, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0, 0x800D3F2C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText,
        0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0, 0x800D3F34,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0,
        0x800D3DE8, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110, 0x00060000,
        0xFF01F8E0, 0x800D3F3C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F8E0, 0x800D3F44, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_DeleteNameCharacter, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFFF9F8E0, 0x800D3F4C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Setup_CommitPlayerName, 0x00000000,
        0x00451250, 0x002D0000, (unsigned int)addrLow_Setup_LoadNameEditBuffer, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries, (unsigned int)addrLow_Setup_HasActiveGameCounters, 0x00050000, 0x00000000,
        0x00000000, 0xC6200004, 0x4600010D,
    },
};
#endif
