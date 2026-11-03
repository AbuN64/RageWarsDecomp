
/* Updates the selected player's setup panel and its linked controls. */
#include "TYPES.H"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "FRONTEND/WIDGET_FINDWIDGETATPOINT.H"
/* menu_setup_versions.h declares this scalar only cart-guarded; the slot-error scalar is real in every cart */
extern s32 g_pakProfileOperationPhase;
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "FRONTEND/SMP_OVERLAY.H"
typedef struct SetupTextNode SetupTextNode;
typedef struct SetupRosterChoice SetupRosterChoice;
typedef struct SetupRosterSlot SetupRosterSlot;
typedef struct SetupCharacterState SetupCharacterState;
typedef struct SetupLinkedLabel SetupLinkedLabel;
typedef struct SetupRosterRecord SetupRosterRecord;
struct SetupTextNode {
    char pad0[0x34];
    s32 stringTableIndex;
    void* nameText;
};
struct SetupRosterChoice {
    char pad0[0x64];
    void* reservedPointer;
    char pad64[0xADC];
    s32 selectedChoice;
};
struct SetupRosterSlot {
    char pad0[0x64];
    void* reservedPointer1;
    char pad64[0xAC8];
    s32 selectedRosterIndex;
};
struct SetupCharacterState {
    char pad0[0xBA0];
    s32 animationState;
    s32 animationFrame;
};
struct SetupLinkedLabel {
    char pad0[0x8];
    MenuWidget * textNode;
    char pad8[0x4];
    u8 alpha;
    char pad10[0x27];
    void* nextLabel;
};
struct SetupRosterRecord {
    char pad0[0x64];
    void* reservedPointer2;
    char pad64[0xB1C];
    s32 rosterRecord;
};






int Control_IsControllerConnected(int);
u8 * XPlus_CopyString(u8 *, u8 *);
char * Node_GetStringByIndex(s32);
void SmpOverlay_SetSlotValue(void *, s32, s32);
void *SmpOverlay_GetSlotValue(s32, s32);
void SmpOverlay_ShowSlotNode(s32,s32,struct MenuWidget *);
void Random_ReplaceTextOccurrences(char *, char *, char *);
void PAKInterface_BuildProfileSlotList(s32);
void PAKInterface_RelabelSlotRows(s32);
void PAKInterface_LoadNoteList(s32);
void PAKInterface_LabelActiveProfileRows(s32);
s32 PAKInterface_CountPendingPlayerPanels(void);
void PAKInterface_BeginScreenExit(s32);
void Frontend_StartMenuImageTransition(s32 *record);
void PAKInterface_UpdatePlayerControlRows(s32);                    /* extern */


/* The slot-error scalar is real external storage in every ROM version. */
























void PAKInterface_RefreshPlayerPanel(s32 playerIndex) {



    s32 text_node;

    s32 itemIndex;

    s32 slot_active;



    s32 unusedValue;
    s32 characterIndex;
    s32 slotLabelId;


    s32 selectionOrLabel;
    s32 playerLinkOffset;

    s8 *replacement;
    s8 *panelTemplate;
    u16 unusedValue1;
    u16 statusPanelResourceId;
    u16 slotLabelResourceId;
    u32 panelState;
    u32 screenPhase;
    u32 exitPhase;
    void *previousPanel;
    SlotSelectionWidget *idlePanel;
    SlotSelectionWidget *notePanelOrLabel;
    SetupRosterSlot *unusedPointer;
    SlotSelectionWidget *linkedProfilePanel;
    SlotSelectionWidget *stateElevenPanel;
    SlotSelectionWidget *nameEntryPanel;
    SlotSelectionWidget *profileListPanel;
    SlotSelectionWidget *readyPanel;
    SlotSelectionWidget *createProfilePanel;
    SlotSelectionWidget *recordPanel;
    SetupRosterRecord *unusedPointer1;
    SlotSelectionWidget *missingSavePanel;
    SlotSelectionWidget *stateTwentyThreePanel;
    SlotSelectionWidget *fullProfilesPanel;
    SlotSelectionWidget *unavailableProfilesPanel;
    SlotSelectionWidget *stateTwentySixPanel;
    SlotSelectionWidget *stateTwentyEightPanel;
    SlotSelectionWidget *stateTwentyNinePanel;
    SlotSelectionWidget *pakErrorPanel;
    SlotSelectionWidget *statusPanel;
    SlotSelectionWidget *pakUnavailablePanel;
    SlotSelectionWidget *noteListPanel;
    SlotSelectionWidget *activeProfilesPanel;
    SlotSelectionWidget *chosenProfilePanel;
    SetupRosterChoice *unusedPointer2;
    SetupCharacterState *unusedPointer3;
    void *unusedPointer4;
    void *panelSprite;
    void *panelWidget;
    PakMenuController *linkScan;

    previousPanel = g_pakProfileScreenState->players[playerIndex].menuWidget;
    if (previousPanel != 0) {
        Widget_SetWidgetFlag08((SlotSelectionWidget *) previousPanel, 0);
    }
    Widget_SetWidgetFlag40(SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, playerIndex), 0);
    /* the published B6E8 takes the controller handle as a plain scalar */
    SmpOverlay_ShowSlotById((s32) g_pakProfileScreenState->windowAddress, playerIndex, SETUP_LABEL_ID);
    panelState = g_pakProfileScreenState->players[playerIndex].state;
    switch (panelState) {                              /* switch 1 */
    case 0:                                         /* switch 1 */

        idlePanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, PANEL_ROOT_ID);
        g_pakProfileScreenState->players[playerIndex].menuWidget = idlePanel;
        Widget_SetWidgetFlag08(idlePanel, 1);
        text_node = (s32)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, PANEL_TEXT_ID);
        ((SetupTextNode *)text_node)->nameText = g_pakProfileScreenState->players[playerIndex].nameText;
        screenPhase = g_pakProfileScreenState->phase;

        switch (screenPhase) {                        /* switch 2 */
        case 1:                                     /* switch 2 */
        case 7:                                     /* switch 2 */
            replacement = Node_GetStringByIndex(MODE_17_ID);
            panelTemplate = Node_GetStringByIndex(((SetupTextNode *)text_node)->stringTableIndex);
            break;
        case 2:                                     /* switch 2 */
            replacement = Node_GetStringByIndex(MODE_2_ID);
            panelTemplate = Node_GetStringByIndex(((SetupTextNode *)text_node)->stringTableIndex);
            break;
        case 3:                                     /* switch 2 */
            replacement = Node_GetStringByIndex(MODE_3_ID);
            panelTemplate = Node_GetStringByIndex(((SetupTextNode *)text_node)->stringTableIndex);
            break;
        case 4:                                     /* switch 2 */
        case 6:                                     /* switch 2 */
            replacement = Node_GetStringByIndex(MODE_46_ID);
            panelTemplate = Node_GetStringByIndex(((SetupTextNode *)text_node)->stringTableIndex);
            break;
        case 5:                                     /* switch 2 */
            replacement = Node_GetStringByIndex(MODE_5_ID);
            panelTemplate = Node_GetStringByIndex(((SetupTextNode *)text_node)->stringTableIndex);
            break;
        case 0:                                     /* switch 2 */
        default:                                    /* switch 2 */
            replacement = Node_GetStringByIndex(MODE_DEFAULT_ID);
            panelTemplate = Node_GetStringByIndex(((SetupTextNode *)text_node)->stringTableIndex);
            break;
        }


        XPlus_CopyString((&g_pakProfileScreenState->players[playerIndex])->nameText, panelTemplate);
        Random_ReplaceTextOccurrences((&g_pakProfileScreenState->players[playerIndex])->nameText, g_modeToken, replacement);
        playerLinkOffset = playerIndex * 8;
        if (g_pakProfileScreenState->phase == 6) {
            Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, MODE_HIDE_ID), 0);
            playerLinkOffset = playerIndex * 8;
        }
        break;
    case 1:                                         /* switch 1 */

        pakErrorPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_1_2EC);
        g_pakProfileScreenState->players[playerIndex].menuWidget = pakErrorPanel;
        Widget_SetWidgetFlag08(pakErrorPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_1_2EE));
        playerLinkOffset = playerIndex * 8;
        break;
    case 2:                                         /* switch 1 */

        panelSprite = g_pakProfileScreenState->players[playerIndex].sprite;
        statusPanelResourceId = UI_CASE_2_2D4;
block_36:
        statusPanel = Node_FindWidgetByResourceId(panelSprite, statusPanelResourceId);
        g_pakProfileScreenState->players[playerIndex].menuWidget = statusPanel;
        Widget_SetWidgetFlag08(statusPanel, 1);
        playerLinkOffset = playerIndex * 8;
        break;
    case 3:                                         /* switch 1 */

        pakUnavailablePanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_3_2BB);
        g_pakProfileScreenState->players[playerIndex].menuWidget = pakUnavailablePanel;
        Widget_SetWidgetFlag08(pakUnavailablePanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_3_2BC));
        break;
    case 4:                                         /* switch 1 */

        noteListPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_4_2D5);
        g_pakProfileScreenState->players[playerIndex].menuWidget = noteListPanel;
        Widget_SetWidgetFlag08(noteListPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_4_2DA));
        PAKInterface_LoadNoteList(playerIndex);
        playerLinkOffset = playerIndex * 8;
        break;
    case 22:                                        /* switch 1 */
        /* the panel slot is untyped storage; the hub types the E8D8 argument as the item */
        Widget_SetWidgetFlag08((SlotSelectionWidget *) g_pakProfileScreenState->players[playerIndex].menuWidget, 1);
        linkScan = g_pakProfileScreenState;
        selectionOrLabel = 0;
        if (linkScan->links[0].state == 0) {
            do {
                linkScan = (void *)((char *)linkScan + sizeof(PakMenuLink));
                selectionOrLabel += 1;
            } while (linkScan->links[0].state == 0);
        }
        slotLabelId = SLOT_DEFAULT_ID;
        if (selectionOrLabel == 1) {
            goto case22_one;
        }
        if (selectionOrLabel >= 2) {
            goto case22_check_two;
        }
        if (selectionOrLabel == 0) {
            goto case22_selected;
        }
        goto case22_default;
case22_check_two:
        if (selectionOrLabel == 2) {
            goto case22_two;
        }
case22_check_three:
        if (selectionOrLabel == 3) {
            goto case22_three;
        }
case22_default:
        slotLabelId = SLOT_DEFAULT_ID;
        goto case22_selected;
case22_one:
        slotLabelId = SLOT_1_ID;
        goto case22_selected;
case22_two:
        slotLabelId = SLOT_2_ID;
        goto case22_selected;
case22_three:
        slotLabelId = SLOT_3_ID;
case22_selected:
        SmpOverlay_ShowSlotById((s32) g_pakProfileScreenState->windowAddress, playerIndex, slotLabelId);
        PAKInterface_RelabelSlotRows(playerIndex);
        playerLinkOffset = playerIndex * 8;
        break;
    case 6:                                         /* switch 1 */

        activeProfilesPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_6_2E4);
        g_pakProfileScreenState->players[playerIndex].menuWidget = activeProfilesPanel;
        Widget_SetWidgetFlag08(activeProfilesPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_6_2E8));
        PAKInterface_LabelActiveProfileRows(playerIndex);
        playerLinkOffset = playerIndex * 8;
        break;
    case 7:                                         /* switch 1 */

        chosenProfilePanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_7_2CA);
        g_pakProfileScreenState->players[playerIndex].menuWidget = chosenProfilePanel;
        Widget_SetWidgetFlag08(chosenProfilePanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_7_2CC));

        panelWidget = g_pakProfileScreenState->players[playerIndex].menuWidget;
        selectionOrLabel = g_pakProfileScreenState->players[playerIndex].chosen;
        slotLabelResourceId = UI_CASE_7_2CB;

        (((MenuWidget *)(Node_FindWidgetByResourceId(panelWidget, slotLabelResourceId)))->text) = (&g_pakProfileScreenState->players[playerIndex])->slots[selectionOrLabel];
        goto block_84;
    case 8:                                         /* switch 1 */

        notePanelOrLabel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_8_2CE);
        g_pakProfileScreenState->players[playerIndex].menuWidget = notePanelOrLabel;
        Widget_SetWidgetFlag08(notePanelOrLabel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_8_2CF));

        selectionOrLabel = g_pakProfileScreenState->players[playerIndex].slot;
        notePanelOrLabel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_8_2CB);

        ((MenuWidget *)notePanelOrLabel)->text = g_pakProfileScreenState->players[playerIndex].names[selectionOrLabel].code;
        goto block_84;
    case 9:                                         /* switch 1 */

        linkedProfilePanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_9_2C6);
        g_pakProfileScreenState->players[playerIndex].menuWidget = linkedProfilePanel;
        Widget_SetWidgetFlag08(linkedProfilePanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_9_2C8));
        ((MenuWidget *)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_9_2C7))->text = g_pakProfileScreenState->players[g_pakProfileScreenState->links[0].player].slots[g_pakProfileScreenState->links[0].entry];
        goto block_84;
    case 10:                                        /* switch 1 */

        statusPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_10_2A4);
        g_pakProfileScreenState->players[playerIndex].menuWidget = statusPanel;
        Widget_SetWidgetFlag08(statusPanel, 1);
        playerLinkOffset = playerIndex * 8;
        break;
    case 11:                                        /* switch 1 */

        stateElevenPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_11_2D1);
        g_pakProfileScreenState->players[playerIndex].menuWidget = stateElevenPanel;
        Widget_SetWidgetFlag08(stateElevenPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_11_2D2));
        break;
    case 12:                                        /* switch 1 */

        nameEntryPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_12_2F2);
        g_pakProfileScreenState->players[playerIndex].menuWidget = nameEntryPanel;
        Widget_SetWidgetFlag08(nameEntryPanel, 1);
        itemIndex = 0;
        selectionOrLabel = (s32)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_12_2F3);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, (void *)selectionOrLabel);


        g_pakProfileScreenState->players[playerIndex].nameCursor = 0;

        do {
            if (itemIndex == 0) {
                g_pakProfileScreenState->players[playerIndex].name[itemIndex].available = 65;
            } else {
                g_pakProfileScreenState->players[playerIndex].name[itemIndex].available = 0;
            }
            g_pakProfileScreenState->players[playerIndex].name[itemIndex].slot = 0;
            itemIndex++;
        } while (itemIndex < 7);

        g_pakProfileScreenState->players[playerIndex].nameTimer = 0;
        g_pakProfileScreenState->players[playerIndex].namePhase = 2;
        characterIndex = 0;
        do {
            ((SetupLinkedLabel *)selectionOrLabel)->alpha = 0xFF;
            text_node = (s32)((SetupLinkedLabel *)selectionOrLabel)->textNode;
            ((MenuWidget *)text_node)->text = &g_pakProfileScreenState->players[playerIndex].name[characterIndex].available;
            selectionOrLabel = (s32)((SetupLinkedLabel *)selectionOrLabel)->nextLabel;
            characterIndex += 1;
        } while (selectionOrLabel != 0);
        playerLinkOffset = playerIndex * 8;
        break;
    case 13:                                        /* switch 1 */

        profileListPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_13_2AF);
        g_pakProfileScreenState->players[playerIndex].menuWidget = profileListPanel;
        Widget_SetWidgetFlag08(profileListPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_13_2B6));
        PAKInterface_BuildProfileSlotList(playerIndex);
        playerLinkOffset = playerIndex * 8;
        break;
    case 14:                                        /* switch 1 */
    case 17:                                        /* switch 1 */
        SmpOverlay_ShowSlotById((s32) g_pakProfileScreenState->windowAddress, playerIndex, SETUP_LABEL_ID);
        SmpOverlay_SetSlotValue(g_pakProfileScreenState->root, playerIndex, 1);

        readyPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_17_2A5);
        g_pakProfileScreenState->players[playerIndex].menuWidget = readyPanel;
        Widget_SetWidgetFlag08(readyPanel, 1);
        if (PAKInterface_CountPendingPlayerPanels() == 0) {
            exitPhase = g_pakProfileScreenState->phase;
            if (exitPhase == 4) {
                goto mode_default;
            }
            if ((s32)exitPhase < 5) {
                goto mode_default;
            }
            if (exitPhase == 5) {
                goto mode_five;
            }
            if (exitPhase == 6) {
                goto mode_six;
            }
            goto mode_default;
mode_five:
            Tsmos_DeactivateControllerState();
            Frontend_StartMenuImageTransition(g_pakProfileScreenState->menu);
            goto mode_end;
mode_six:
            {
                PAKInterface_BeginScreenExit(29);
                if (g_pakProfileOperationPhase == 1) {
                    g_pakProfileControllerPort -= 1;
                }
                if (g_pakProfileOperationPhase == 0) {
                    g_pakProfileControllerPort = -1;
                }
                goto mode_end;
            }
mode_default:
            PAKInterface_BeginScreenExit(27);
mode_end:;
        }
        playerLinkOffset = playerIndex * 8;
        break;
    case 15:                                        /* switch 1 */

        createProfilePanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_15_2EF);
        g_pakProfileScreenState->players[playerIndex].menuWidget = createProfilePanel;
        Widget_SetWidgetFlag08(createProfilePanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_15_2F1));
        break;
    case 16:                                        /* switch 1 */

        recordPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_16_2B7);
        g_pakProfileScreenState->players[playerIndex].menuWidget = recordPanel;
        Widget_SetWidgetFlag08(recordPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_16_2B9));
        slotLabelResourceId = UI_CASE_16_2BA;

        panelWidget = g_pakProfileScreenState->players[playerIndex].menuWidget;
        selectionOrLabel = g_pakProfileScreenState->players[playerIndex].record;
block_61:

        (((MenuWidget *)(Node_FindWidgetByResourceId(panelWidget, slotLabelResourceId)))->text) = (&g_pakProfileScreenState->players[playerIndex])->slots[selectionOrLabel];
        goto block_84;
    case 21:                                        /* switch 1 */

        missingSavePanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_21_2E1);
        g_pakProfileScreenState->players[playerIndex].menuWidget = missingSavePanel;
        Widget_SetWidgetFlag08(missingSavePanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_21_2E2));
        break;
    case 23:                                        /* switch 1 */

        stateTwentyThreePanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_23_2AC);
        g_pakProfileScreenState->players[playerIndex].menuWidget = stateTwentyThreePanel;
        Widget_SetWidgetFlag08(stateTwentyThreePanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_23_2AE));
        break;
    case 24:                                        /* switch 1 */

        fullProfilesPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_24_2A9);
        g_pakProfileScreenState->players[playerIndex].menuWidget = fullProfilesPanel;
        Widget_SetWidgetFlag08(fullProfilesPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_24_2AA));
        break;
    case 25:                                        /* switch 1 */

        unavailableProfilesPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_25_2EA);
        g_pakProfileScreenState->players[playerIndex].menuWidget = unavailableProfilesPanel;
        Widget_SetWidgetFlag08(unavailableProfilesPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_25_2EB));
        break;
    case 26:                                        /* switch 1 */

        stateTwentySixPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_26_2A6);
        g_pakProfileScreenState->players[playerIndex].menuWidget = stateTwentySixPanel;
        Widget_SetWidgetFlag08(stateTwentySixPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_26_2A7));
        break;
case27_found:
        SmpOverlay_ShowSlotById((s32) g_pakProfileScreenState->windowAddress, playerIndex, slotLabelId);
        goto case27_done;
    case 27:                                        /* switch 1 */
        Widget_SetWidgetFlag08((SlotSelectionWidget *) g_pakProfileScreenState->players[playerIndex].menuWidget, 1);
        itemIndex = 0;

        SmpOverlay_ShowSlotById((s32) g_pakProfileScreenState->windowAddress, playerIndex, CHECK_0_ID);
        do {
loop_69:
        if (itemIndex == 1) {
            goto case27_one;
        }
        if (itemIndex >= 2) {
            goto case27_check_two;
        }
        if (itemIndex == 0) {
            goto case27_zero;
        }
        slotLabelId = CHECK_DEFAULT_ID;
        goto case27_selected;
case27_check_two:
        if (itemIndex == 2) {
            goto case27_two;
        }
        slotLabelId = CHECK_DEFAULT_ID;
        goto case27_selected;
case27_zero:
        slotLabelId = CHECK_0_ID;
        goto case27_selected;
case27_one:
        slotLabelId = CHECK_1_ID;
        goto case27_selected;
case27_two:
        slotLabelId = CHECK_2_ID;
case27_selected:
        slot_active = Control_IsControllerConnected(itemIndex);
        itemIndex += 1;
        if (slot_active == 1) {
            goto case27_found;
        }
        } while (itemIndex < 4);
case27_done:
        PAKInterface_UpdatePlayerControlRows(playerIndex);
        playerLinkOffset = playerIndex * 8;
        break;
    case 28:                                        /* switch 1 */

        stateTwentyEightPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_28_2DE);
        g_pakProfileScreenState->players[playerIndex].menuWidget = stateTwentyEightPanel;
        Widget_SetWidgetFlag08(stateTwentyEightPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_28_2DF));
        break;
    case 29:                                        /* switch 1 */

        stateTwentyNinePanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_29_2BF);
        g_pakProfileScreenState->players[playerIndex].menuWidget = stateTwentyNinePanel;
        Widget_SetWidgetFlag08(stateTwentyNinePanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_29_2C0));
        playerLinkOffset = playerIndex * 8;
        break;
    default:                                        /* switch 1 */
block_84:
        playerLinkOffset = playerIndex * 8;
        break;
    }
    ((SetupLinkedLabel *)g_pakProfileScreenState->players[playerIndex].menuWidget)->alpha = 150;
}
