#include "COMMON/SCREEN.H"
#include "include_asm.h"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/NAME.H"
#include "TYPES.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "COMMON/WIDGETRECAT1A.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* 8042E080_27.CPP */
/* Cancels player playerEntryId's pickup when the state at 0x58 of its 2920-byte record is 12 and selectionPressed asks:
   sets the word at 0xBA0 to 2, clears 0xBA4, drops one from the count at 0xB9C, stamps 0x41 on
   that count's two-byte slot at 0xB8C when the slot is free, silences the sound handle taken from
   the player's entry of the slot array at 4 of the block, and reports the cancel through
   SoundElement_PlayFlatSound. Records 13 and above are left alone; the function always returns zero. */

extern void *SmpOverlay_GetSlotValue(s32 root, s32 player);

s32 PAKInterface_MoveNameCursorBackward(s32 unused0, s32 unused1, s32 playerEntryId, s32 selectionPressed) {
    struct ResourceSmpFlickerCreateFlickerWidget *sound;
    struct PakPanelSelectionView *row;
    char *base;
    u8 *mark;
    s32 index;
    s32 offset;
    s32 state;
    s32 count;

    index = playerEntryId & 0xFFFF;
    offset = index * 2920;
    state = ((struct PakPanelSelectionView *)(offset + (char *)g_pakProfileScreenState))->state;
    if (state == 13) {
        return 0;
    }
    if (state >= 14) {
        return 0;
    }
    if (state == 12 && selectionPressed == 1) {
        sound = SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, index);
        row = (struct PakPanelSelectionView *)(index * sizeof(PakProfilePanelState) + (char *)g_pakProfileScreenState);
        row->phase = 2;
        count = row->count;
        row->timer = 0;
        if (count > 0) {
            row->count = count - 1;
        }
        base = (char *)g_pakProfileScreenState;
        mark = (u8 *)(base + ((((struct PakPanelSelectionView *)(offset + base))->count * 2) +
                              index * sizeof(PakProfilePanelState)) + (((char *)&((struct PakMenuController *)0)->players - (char *)0) + ((char *)&((PakProfilePanelState *)0)->name - (char *)0)));
        if (*mark == 0) {
            *mark = 65;
        }
        sound->value = 0xFF;
        SoundElement_PlayFlatSound(3700);
    }
    return 0;
}

/* Handles Controller Pak menu confirmations for the active channel, clearing its status on a confirmed state-12 prompt and returning focus to an enabled widget in the list states. */
s32 Smos_GetControlRepeatLimit();                                /* extern */
s32 Widget_ListHasFlag100(struct WidgetNode *node);                          /* extern */
void SmpOverlay_ShowSlotNode(s32,s32,struct MenuWidget *);                  /* extern */
void PAKInterface_RelabelSlotRows(s32);                               /* extern */
void PAKInterface_UpdatePlayerControlRows(s32);                               /* extern */
void PAKInterface_ScrollNoteList(s32, s32);                            /* extern */
void PAKInterface_DecrementNameCharacter(s32);                               /* extern */

s32 PAKInterface_HandleNextPanelSelection(s32 unusedWidget, s32 unusedEventId, s32 playerEntryId, s32 selectionPressed, s32 fifth) {
    s32 repeatMagnitude;
    s32 player;
    s32 playerState;
    MenuWidget *nextCharacterWidget;
    MenuWidget *nextChoiceWidget;
    MenuWidget *nextOptionWidget;

    player = playerEntryId & 0xFFFF;
    playerState = g_pakProfileScreenState->players[player].state;
    switch (playerState) {
    case 12:
        repeatMagnitude = XMath_AbsoluteInteger(fifth);
        if (repeatMagnitude < Smos_GetControlRepeatLimit()) {
            g_pakProfileScreenState->players[player].nameTimer = 0;
            g_pakProfileScreenState->players[player].namePhase = 2;
        }
        if (selectionPressed == 1) {
            MarkMenuEventHandled();
            PAKInterface_DecrementNameCharacter(player);
            g_pakProfileScreenState->players[player].namePhase = 0;
            SoundElement_PlayFlatSound(3713);
            return 0;
        }
        return 0;
    case 4:
        if (selectionPressed == 1) {
            MarkMenuEventHandled();
            PAKInterface_ScrollNoteList(player, 1);
            g_pakProfileScreenState->selected[player] = 0;
            SoundElement_PlayFlatSound(3700);
            return 0;
        }
        return 0;
    case 13:
        if ((g_pakProfileScreenState->players[player].sub == 6) && (selectionPressed == 1)) {
            MarkMenuEventHandled();
            nextCharacterWidget = ((MenuWidget *)SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, player))->next;
loop_11:
            if (Widget_ListHasFlag100(nextCharacterWidget) != 0) {
                nextCharacterWidget = nextCharacterWidget->next;
                goto loop_11;
            }
            SmpOverlay_ShowSlotNode((g_pakProfileScreenState->root), player, nextCharacterWidget);
            SoundElement_PlayFlatSound(3700);
            return 0;
        }
        return 0;
    case 22:
        if (selectionPressed == 1) {
            nextChoiceWidget = ((MenuWidget *)SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, player))->next;
loop_16:
            if (Widget_ListHasFlag100(nextChoiceWidget) != 0) {
                nextChoiceWidget = nextChoiceWidget->next;
                goto loop_16;
            }
            SmpOverlay_ShowSlotNode((g_pakProfileScreenState->root), player, nextChoiceWidget);
            PAKInterface_RelabelSlotRows(player);
        }
        goto block_24;
    case 27:
        if (selectionPressed == 1) {
            nextOptionWidget = ((MenuWidget *)SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, player))->next;
loop_21:
            if (Widget_ListHasFlag100(nextOptionWidget) != 0) {
                nextOptionWidget = nextOptionWidget->next;
                goto loop_21;
            }
            SmpOverlay_ShowSlotNode((g_pakProfileScreenState->root), player, nextOptionWidget);
            PAKInterface_UpdatePlayerControlRows(player);
        }
block_24:
        MarkMenuEventHandled();
        break;
    }
    return 0;
}

/* Handles Controller Pak menu confirmations and returns focus to an enabled widget for the active channel. */
extern void PAKInterface_IncrementNameCharacter(s32);
s32 PAKInterface_HandlePakMenuConfirm(s32 unused0, s32 unused1, s32 packedPlayerEvent, s32 pressState, s32 fifth) {
    WidgetReferenceNodeView *node;
    s32 player;

    player = packedPlayerEvent & 0xFFFF;
    switch (g_pakProfileScreenState->players[player].state) {
    case 12:
        if (XMath_AbsoluteInteger(fifth) < Smos_GetControlRepeatLimit()) {
            g_pakProfileScreenState->players[player].nameTimer = 0;
            g_pakProfileScreenState->players[player].namePhase = 2;
        }
        if (pressState == 1) {
            MarkMenuEventHandled();
            g_pakProfileScreenState->players[player].namePhase = pressState;
            PAKInterface_IncrementNameCharacter(player);
            SoundElement_PlayFlatSound(3713);
        }
        return 0;
    case 4:
        if (pressState == 1) {
            MarkMenuEventHandled();
            PAKInterface_ScrollNoteList(player, 0);
            g_pakProfileScreenState->selected[player] = 0;
            SoundElement_PlayFlatSound(3700);
        }
        return 0;
    case 13:
        if (g_pakProfileScreenState->players[player].sub == 6 && pressState == 1) {
            MarkMenuEventHandled();
            node = SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, player);
            node = node->ref2C;
            while (Widget_ListHasFlag100(node) != 0) {
                node = node->ref2C;
            }
            SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, player, node);
            SoundElement_PlayFlatSound(3700);
        }
        return 0;
    case 22:
        if (pressState == 1) {
            node = SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, player);
            node = node->ref2C;
            while (Widget_ListHasFlag100(node) != 0) {
                node = node->ref2C;
            }
            SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, player, node);
            PAKInterface_RelabelSlotRows(player);
        }
        MarkMenuEventHandled();
        break;
    case 27:
        if (pressState == 1) {
            node = SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, player);
            node = node->ref2C;
            while (Widget_ListHasFlag100(node) != 0) {
                node = node->ref2C;
            }
            SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, player, node);
            PAKInterface_UpdatePlayerControlRows(player);
        }
        MarkMenuEventHandled();
        break;
    }
    return 0;
}

/* 8042E080_28.CPP */
/* Handles a cancel event for the player the low half of the third argument names: calls
   MarkMenuEventHandled and, when the block g_pakProfileScreenState points to is in phase 7 at 0x54, returns to screen 3
   through PAKInterface_BeginScreenExit; otherwise by the player's state at the start of its 2920-byte record at
   0x58: in state 0 it leaves for screen 0x1B unless PAKInterface_CountActivePlayerPanels reports something pending, in
   state 0xC it blanks the character at the cursor of the name at 0xB34 of the record, and in
   states 0x16 and 0x1B it closes the keyboard through PAKInterface_RelabelSlotRows_FrontendResetlinkedlocalprofile or PAKInterface_UpdatePlayerControlRows_PakinterfaceHandlenextpanelselection with -1,
   returns the player to state 0xD and redraws through PAKInterface_RefreshPlayerPanel_PakinterfaceActivateplayerpanelaction. Returns zero. Written from
   the assembly with the player index as an unsigned short parameter. */

extern void PAKInterface_RefreshPlayerPanel(s32);

s32 PAKInterface_HandlePlayerPanelBack(void *unused0, void *unused1, u16 player) {
    MarkMenuEventHandled();
    if (g_pakProfileScreenState->phase == 7) {
        PAKInterface_BeginScreenExit(3);
        return 0;
    }
    switch (g_pakProfileScreenState->players[player].state) {
    case 0:
        if (PAKInterface_CountActivePlayerPanels() > 0) {
            return 0;
        }
        MarkMenuEventHandled();
        PAKInterface_BeginScreenExit(27);
        return 0;
    case 12:
        MarkMenuEventHandled();
        g_pakProfileScreenState->players[player].name[g_pakProfileScreenState->players[player].nameCursor].available = ' ';
        break;
    case 22:
        MarkMenuEventHandled();
        PAKInterface_RelabelSlotRows(-1);
        g_pakProfileScreenState->players[player].state = 13;
        PAKInterface_RefreshPlayerPanel(player);
        break;
    case 27:
        MarkMenuEventHandled();
        PAKInterface_UpdatePlayerControlRows(-1);
        g_pakProfileScreenState->players[player].state = 13;
        PAKInterface_RefreshPlayerPanel(player);
        break;
    default:
        return 0;
    }
    return 0;
}
