#include "COMMON/RECORDRECATCV1.H"
#include "COMMON/LONE/g_pakProfileActionDialogResource.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "MENU/PAK_LOAD.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ACTORRECAT5E0.H"
#include "COMMON/MENURECAT24.H"
#include "MENU/ITEMRECAT24.H"
#include "COMMON/TEXTLAYERMETRICS.H"
#include "MENU/PAK/PROFILE.H"
#include "ENGINE/DEFS.H"
#include "COMMON/NODERECAT2A8.H"
#include "include_asm.h"
#include "COMMON/TRIPLE.H"
#include "COMMON/EFFECTRENDER.H"

extern s32 g_controllerPakPromptKind;

/* Formats the score into the last four characters of the item's text and returns zero.
   PAL items select their text using the current language. */

#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern char g_pakFourDigitValueFormat[];
#else
#endif

extern s32 Menu_CountLineChars(LayeredText *);


/* Draws an item's label at its position into the text layer g_matchEndingTeamWheelClose through Menu_OpenDialog, using
   the fixed label g_profileDialogFixedLabel instead of the item's own when g_pakProfileLoaded is set; returns 1. */


extern char g_matchEndingTeamWheelClose[];


extern void *Menu_OpenDialog(void *parent, struct Dialog *list, s32 player, s32 controller, s32 d);

/* Clears the word held in g_controllerPakPromptKind. */


/* Sets the state word g_controllerPakPromptKind to 1; this is one of a run of functions that each store one
   state number there, and Pak_SelectPromptKindZero clears it. */


/* Sets the state word g_controllerPakPromptKind to 2; this is one of a run of functions that each store one
   state number there, and Pak_SelectPromptKindZero clears it. */


/* Sets the state word g_controllerPakPromptKind to 3; this is one of a run of functions that each store one
   state number there, and Pak_SelectPromptKindZero clears it. */


/* Sets the state word g_controllerPakPromptKind to 4; this is one of a run of functions that each store one
   state number there, and Pak_SelectPromptKindZero clears it. */


/* Sets the state word g_controllerPakPromptKind to 5; this is one of a run of functions that each store one
   state number there, and Pak_SelectPromptKindZero clears it. */


/* Sets the state word g_controllerPakPromptKind to 6; this is one of a run of functions that each store one
   state number there, and Pak_SelectPromptKindZero clears it. */


/* Sets the state word g_controllerPakPromptKind to 7; this is one of a run of functions that each store one
   state number there, and Pak_SelectPromptKindZero clears it. */


/* Clears bit 26 and sets bit 3 of the flag word at offset 0x120 of the object at offset 0xC of a
   record, stores 8 in the state word g_controllerPakPromptKind between the two, and calls Control_ClearMenuControlFlag. */






/* Stores 9 in g_controllerPakPromptKind and 0 in g_pakPromptKindNinePending. */


/* Stores 9 in the state word g_controllerPakPromptKind and one in g_pakPromptKindNinePending; Pak_SelectPromptKindNine stores 9 and zero. */


/* Sets the state word g_controllerPakPromptKind to 0xA; this is one of a run of functions that each store one
   state number there, and Pak_SelectPromptKindZero clears it. */


/* Sets the state word g_controllerPakPromptKind to 0xB; this is one of a run of functions that each store one
   state number there, and Pak_SelectPromptKindZero clears it. */


/* Sets the state word g_controllerPakPromptKind to 0xC; this is one of a run of functions that each store one
   state number there, and Pak_SelectPromptKindZero clears it. */


/* Sets the state word g_controllerPakPromptKind to 0xD; this is one of a run of functions that each store one
   state number there, and Pak_SelectPromptKindZero clears it. */


/* Sets the state word g_controllerPakPromptKind to 0xE; this is one of a run of functions that each store one
   state number there, and Pak_SelectPromptKindZero clears it. */


/* Sets the state word g_controllerPakPromptKind to 0xF; this is one of a run of functions that each store one
   state number there, and Pak_SelectPromptKindZero clears it. */


/* Points a field's text at the label for the state word g_controllerPakPromptKind: the second string through the jump table
   k_selectPromptActionHeadingJumpTable for states 0 to 15, and g_SelectPromptActionHeadingStateOtherText for any other state. Returns zero. An earlier attempt misjudged this switch as a dispatch head whose
   cases lay outside the interval; its case bodies are inside it. */




/* Points a field's text at the label for the state word g_controllerPakPromptKind: one of 15 strings through the jump table
   k_selectPromptTextGroupOneJumpTable for states 0 to 15, and g_SelectPromptTextGroupOneStateOtherText for any other state. Returns zero. */




/* Points a field's text at the label for the state word g_controllerPakPromptKind: one of 15 strings through the jump table
   k_selectPromptTextGroupTwoJumpTable for states 0 to 15, and g_SelectPromptTextGroupTwoStateOtherText for any other state. Returns zero. */




/* Points a field's text at the label for the state word g_controllerPakPromptKind: one of 15 strings through the jump table
   k_selectPromptTextGroupThreeJumpTable for states 0 to 15, and g_SelectPromptTextGroupThreeStateOtherText for any other state. Returns zero. */




/* Points a field's text at the label for the state word g_controllerPakPromptKind: one of 15 strings through the jump table
   k_selectPromptTextGroupFourJumpTable for states 0 to 15, and g_SelectPromptTextGroupFourStateOtherText for any other state. Returns zero. */




/* Points a field's text at the label for the state word g_controllerPakPromptKind: one of 15 strings through the jump table
   k_selectPromptTextGroupFiveJumpTable for states 0 to 15, and g_SelectPromptTextGroupFiveStateOtherText for any other state. Returns zero. */




/* Points a field's text at the label for the state word g_controllerPakPromptKind: the second string through the jump table
   k_selectModalPromptLabelJumpTable for states 0 to 15, and g_SelectModalPromptLabelStateOtherText for any other state. Returns zero. An earlier attempt misjudged this switch as a dispatch head whose
   cases lay outside the interval; its case bodies are inside it. */




/* Latches g_pakNamePromptAccepted to one when the record's team value is not -1 and both Control_PeekPakChange_Pak and Snapshot_CheckStatusPrompt accept it, then returns g_pakNamePromptAccepted. Adapted from Timer_CheckMenuPakChange with the latch g_pakMenuPromptAccepted changed to g_pakNamePromptAccepted. */





extern s32 g_pakUseScannedChannel;

extern s32 Snapshot_CheckStatusPrompt(struct Shared_PakMenu *, s32, s32);

static inline s32 Pak_GetMenuChannel(struct Shared_PakMenu *record) {
    if (g_pakUseScannedChannel != 0) {
        return g_introSelectedItem;
    }
    return record->owner->controllerPort;
}

s32 Pak_FormatPreviewFourDigitValue(LayeredText *field) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    s32 value = g_pakProfileRankScore;
    char *text = (char *)field->text[g_languageIndex];

    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_pakFourDigitValueFormat, value);
#else
    s32 value = g_pakLoadedProfile.values[2];
    char *text = (char *)*field->text;

    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_pakFormatInt04, value);
#endif
    return 0;
}

/* Points a field's text at g_pakAlternateActionLabel when g_pakProfileLoaded is set, at g_pakDefaultPreviewActionLabel when g_pakUseDefaultPreviewLabels is set instead, and at
   g_pakActionLabel otherwise. Returns zero. */



s32 Pak_UpdateProfileActionLabel(struct PakActionLabelView *field) {
    if (g_pakProfileLoaded != 0) {
        field->text = g_pakAlternateActionLabel;
    } else if (g_pakUseDefaultPreviewLabels != 0) {
        field->text = g_pakDefaultPreviewActionLabel;
    } else {
        field->text = g_pakActionLabel;
    }
    return 0;
}

int Pak_OpenProfileActionPrompt(int unused, PakActionPromptItemView *item) {
    if (g_pakProfileLoaded != 0) {
        Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakProfileActionDialogResource, item->x, item->y, 0);
    } else {
        Menu_OpenDialog(g_matchEndingTeamWheelClose, item->label, item->x, item->y, 0);
    }
    return 1;
}

void Pak_SelectPromptKindZero(void) {
    g_controllerPakPromptKind = 0;
}

void Pak_SelectPromptKindOne(void) {
    g_controllerPakPromptKind = 1;
}

void Pak_SelectPromptKindTwo(void) {
    g_controllerPakPromptKind = 2;
}

void Pak_SelectPromptKindThree(void) {
    g_controllerPakPromptKind = 3;
}

void Pak_SelectPromptKindFour(void) {
    g_controllerPakPromptKind = 4;
}

void Pak_SelectPromptKindFive(void) {
    g_controllerPakPromptKind = 5;
}

void Pak_SelectPromptKindSix(void) {
    g_controllerPakPromptKind = 6;
}

void Pak_SelectPromptKindSeven(void) {
    g_controllerPakPromptKind = 7;
}

void Pak_SelectPromptKindEight(struct MenuPromptKindView *record) {
    record->target->flags &= ~0x04000000;
    g_controllerPakPromptKind = 8;
    record->target->flags |= 8;
    Control_ClearMenuControlFlag();
}

void Pak_SelectPromptKindNine(void) {
    g_controllerPakPromptKind = 9;
    g_pakPromptKindNinePending = 0;
}

void Pak_SelectPromptKindNinePending(void) {
    g_controllerPakPromptKind = 9;
    g_pakPromptKindNinePending = 1;
}

void Pak_SelectPromptKindTen(void) {
    g_controllerPakPromptKind = 10;
}

void Pak_SelectPromptKindEleven(void) {
    g_controllerPakPromptKind = 11;
}

void Pak_SelectPromptKindTwelve(void) {
    g_controllerPakPromptKind = 12;
}

void Pak_SelectPromptKindThirteen(void) {
    g_controllerPakPromptKind = 13;
}

void Pak_SelectPromptKindFourteen(void) {
    g_controllerPakPromptKind = 14;
}

void Pak_SelectPromptKindFifteen(void) {
    g_controllerPakPromptKind = 15;
}

s32 Pak_SelectPromptActionHeading(struct PakActionLabelView *field) {
    u32 state = g_controllerPakPromptKind;

    if (state >= 16) {
        goto state_other;
    }
    switch (state) {
        case 0: goto state_other;
        case 1: goto state_other;
        case 2: goto state_other;
        case 3: goto state_other;
        case 4: goto state_other;
        case 5: goto case_1;
        case 6: goto case_1;
        case 7: goto state_other;
        case 8: goto state_other;
        case 9: goto case_1;
        case 10: goto case_1;
        case 11: goto state_other;
        case 12: goto case_1;
        case 13: goto state_other;
        case 14: goto state_other;
        case 15: goto case_1;
        }
state_other:
    field->text = g_SelectPromptActionHeadingStateOtherText;
    goto done;
case_1:
    field->text = g_SelectPromptActionHeadingCase1Text;
done:
    return 0;
}

s32 Pak_SelectPromptTextGroupOne(struct PakActionLabelView *field) {
    u32 state = g_controllerPakPromptKind;

    if (state >= 16) {
        goto state_other;
    }
    switch (state) {
        case 0: goto state_other;
        case 1: goto case_1;
        case 2: goto case_2;
        case 3: goto case_3;
        case 4: goto case_4;
        case 5: goto case_5;
        case 6: goto case_6;
        case 7: goto case_7;
        case 8: goto case_8;
        case 9: goto case_9;
        case 10: goto case_10;
        case 11: goto case_11;
        case 12: goto case_12;
        case 13: goto case_13;
        case 14: goto case_14;
        case 15: goto case_15;
        }
state_other:
    field->text = g_SelectPromptTextGroupOneStateOtherText;
    goto done;
case_1:
    field->text = g_SelectPromptTextGroupOneCase1Text;
    goto done;
case_2:
    field->text = g_SelectPromptTextGroupOneCase2Text;
    goto done;
case_3:
    field->text = g_SelectPromptTextGroupOneCase3Text;
    goto done;
case_4:
    field->text = g_SelectPromptTextGroupOneCase4Text;
    goto done;
case_5:
    field->text = g_SelectPromptTextGroupOneCase5Text;
    goto done;
case_6:
    field->text = g_SelectPromptTextGroupOneCase6Text;
    goto done;
case_7:
    field->text = g_SelectPromptTextGroupOneCase7Text;
    goto done;
case_8:
    field->text = g_SelectPromptTextGroupOneCase8Text;
    goto done;
case_9:
    field->text = g_SelectPromptTextGroupOneCase9Text;
    goto done;
case_10:
    field->text = g_SelectPromptTextGroupOneCase10Text;
    goto done;
case_11:
    field->text = g_SelectPromptTextGroupOneCase11Text;
    goto done;
case_12:
    field->text = g_SelectPromptTextGroupOneCase12Text;
    goto done;
case_13:
    field->text = g_SelectPromptTextGroupOneCase13Text;
    goto done;
case_14:
    field->text = g_SelectPromptTextGroupOneCase14Text;
    goto done;
case_15:
    field->text = g_SelectPromptTextGroupOneCase15Text;
done:
    return 0;
}

s32 Pak_SelectPromptTextGroupTwo(struct PakActionLabelView *field) {
    u32 state = g_controllerPakPromptKind;

    if (state >= 16) {
        goto state_other;
    }
    switch (state) {
        case 0: goto state_other;
        case 1: goto case_1;
        case 2: goto case_2;
        case 3: goto case_3;
        case 4: goto case_4;
        case 5: goto case_5;
        case 6: goto case_6;
        case 7: goto case_7;
        case 8: goto case_8;
        case 9: goto case_9;
        case 10: goto case_10;
        case 11: goto case_11;
        case 12: goto case_12;
        case 13: goto case_13;
        case 14: goto case_14;
        case 15: goto case_15;
        }
state_other:
    field->text = g_SelectPromptTextGroupTwoStateOtherText;
    goto done;
case_1:
    field->text = g_SelectPromptTextGroupTwoCase1Text;
    goto done;
case_2:
    field->text = g_SelectPromptTextGroupTwoCase2Text;
    goto done;
case_3:
    field->text = g_SelectPromptTextGroupTwoCase3Text;
    goto done;
case_4:
    field->text = g_SelectPromptTextGroupTwoCase4Text;
    goto done;
case_5:
    field->text = g_SelectPromptTextGroupTwoCase5Text;
    goto done;
case_6:
    field->text = g_SelectPromptTextGroupTwoCase6Text;
    goto done;
case_7:
    field->text = g_SelectPromptTextGroupTwoCase7Text;
    goto done;
case_8:
    field->text = g_SelectPromptTextGroupTwoCase8Text;
    goto done;
case_9:
    field->text = g_SelectPromptTextGroupTwoCase9Text;
    goto done;
case_10:
    field->text = g_SelectPromptTextGroupTwoCase10Text;
    goto done;
case_11:
    field->text = g_SelectPromptTextGroupTwoCase11Text;
    goto done;
case_12:
    field->text = g_SelectPromptTextGroupTwoCase12Text;
    goto done;
case_13:
    field->text = g_SelectPromptTextGroupTwoCase13Text;
    goto done;
case_14:
    field->text = g_SelectPromptTextGroupTwoCase14Text;
    goto done;
case_15:
    field->text = g_SelectPromptTextGroupTwoCase15Text;
done:
    return 0;
}

s32 Pak_SelectPromptTextGroupThree(struct PakActionLabelView *field) {
    u32 state = g_controllerPakPromptKind;

    if (state >= 16) {
        goto state_other;
    }
    switch (state) {
        case 0: goto state_other;
        case 1: goto case_1;
        case 2: goto case_2;
        case 3: goto case_3;
        case 4: goto case_4;
        case 5: goto case_5;
        case 6: goto case_6;
        case 7: goto case_7;
        case 8: goto case_8;
        case 9: goto case_9;
        case 10: goto case_10;
        case 11: goto case_11;
        case 12: goto case_12;
        case 13: goto case_13;
        case 14: goto case_14;
        case 15: goto case_15;
        }
state_other:
    field->text = g_SelectPromptTextGroupThreeStateOtherText;
    goto done;
case_1:
    field->text = g_SelectPromptTextGroupThreeCase1Text;
    goto done;
case_2:
    field->text = g_SelectPromptTextGroupThreeCase2Text;
    goto done;
case_3:
    field->text = g_SelectPromptTextGroupThreeCase3Text;
    goto done;
case_4:
    field->text = g_SelectPromptTextGroupThreeCase4Text;
    goto done;
case_5:
    field->text = g_SelectPromptTextGroupThreeCase5Text;
    goto done;
case_6:
    field->text = g_SelectPromptTextGroupThreeCase6Text;
    goto done;
case_7:
    field->text = g_SelectPromptTextGroupThreeCase7Text;
    goto done;
case_8:
    field->text = g_SelectPromptTextGroupThreeCase8Text;
    goto done;
case_9:
    field->text = g_SelectPromptTextGroupThreeCase9Text;
    goto done;
case_10:
    field->text = g_SelectPromptTextGroupThreeCase10Text;
    goto done;
case_11:
    field->text = g_SelectPromptTextGroupThreeCase11Text;
    goto done;
case_12:
    field->text = g_SelectPromptTextGroupThreeCase12Text;
    goto done;
case_13:
    field->text = g_SelectPromptTextGroupThreeCase13Text;
    goto done;
case_14:
    field->text = g_SelectPromptTextGroupThreeCase14Text;
    goto done;
case_15:
    field->text = g_SelectPromptTextGroupThreeCase15Text;
done:
    return 0;
}

s32 Pak_SelectPromptTextGroupFour(struct PakActionLabelView *field) {
    u32 state = g_controllerPakPromptKind;

    if (state >= 16) {
        goto state_other;
    }
    switch (state) {
        case 0: goto state_other;
        case 1: goto case_1;
        case 2: goto case_2;
        case 3: goto case_3;
        case 4: goto case_4;
        case 5: goto case_5;
        case 6: goto case_6;
        case 7: goto case_7;
        case 8: goto case_8;
        case 9: goto case_9;
        case 10: goto case_10;
        case 11: goto case_11;
        case 12: goto case_12;
        case 13: goto case_13;
        case 14: goto case_14;
        case 15: goto case_15;
        }
state_other:
    field->text = g_SelectPromptTextGroupFourStateOtherText;
    goto done;
case_1:
    field->text = g_SelectPromptTextGroupFourCase1Text;
    goto done;
case_2:
    field->text = g_SelectPromptTextGroupFourCase2Text;
    goto done;
case_3:
    field->text = g_SelectPromptTextGroupFourCase3Text;
    goto done;
case_4:
    field->text = g_SelectPromptTextGroupFourCase4Text;
    goto done;
case_5:
    field->text = g_SelectPromptTextGroupFourCase5Text;
    goto done;
case_6:
    field->text = g_SelectPromptTextGroupFourCase6Text;
    goto done;
case_7:
    field->text = g_SelectPromptTextGroupFourCase7Text;
    goto done;
case_8:
    field->text = g_SelectPromptTextGroupFourCase8Text;
    goto done;
case_9:
    field->text = g_SelectPromptTextGroupFourCase9Text;
    goto done;
case_10:
    field->text = g_SelectPromptTextGroupFourCase10Text;
    goto done;
case_11:
    field->text = g_SelectPromptTextGroupFourCase11Text;
    goto done;
case_12:
    field->text = g_SelectPromptTextGroupFourCase12Text;
    goto done;
case_13:
    field->text = g_SelectPromptTextGroupFourCase13Text;
    goto done;
case_14:
    field->text = g_SelectPromptTextGroupFourCase14Text;
    goto done;
case_15:
    field->text = g_SelectPromptTextGroupFourCase15Text;
done:
    return 0;
}

s32 Pak_SelectPromptTextGroupFive(struct PakActionLabelView *field) {
    u32 state = g_controllerPakPromptKind;

    if (state >= 16) {
        goto state_other;
    }
    switch (state) {
        case 0: goto state_other;
        case 1: goto case_1;
        case 2: goto case_2;
        case 3: goto case_3;
        case 4: goto case_4;
        case 5: goto case_5;
        case 6: goto case_6;
        case 7: goto case_7;
        case 8: goto case_8;
        case 9: goto case_9;
        case 10: goto case_10;
        case 11: goto case_11;
        case 12: goto case_12;
        case 13: goto case_13;
        case 14: goto case_14;
        case 15: goto case_15;
        }
state_other:
    field->text = g_SelectPromptTextGroupFiveStateOtherText;
    goto done;
case_1:
    field->text = g_SelectPromptTextGroupFiveCase1Text;
    goto done;
case_2:
    field->text = g_SelectPromptTextGroupFiveCase2Text;
    goto done;
case_3:
    field->text = g_SelectPromptTextGroupFiveCase3Text;
    goto done;
case_4:
    field->text = g_SelectPromptTextGroupFiveCase4Text;
    goto done;
case_5:
    field->text = g_SelectPromptTextGroupFiveCase5Text;
    goto done;
case_6:
    field->text = g_SelectPromptTextGroupFiveCase6Text;
    goto done;
case_7:
    field->text = g_SelectPromptTextGroupFiveCase7Text;
    goto done;
case_8:
    field->text = g_SelectPromptTextGroupFiveCase8Text;
    goto done;
case_9:
    field->text = g_SelectPromptTextGroupFiveCase9Text;
    goto done;
case_10:
    field->text = g_SelectPromptTextGroupFiveCase10Text;
    goto done;
case_11:
    field->text = g_SelectPromptTextGroupFiveCase11Text;
    goto done;
case_12:
    field->text = g_SelectPromptTextGroupFiveCase12Text;
    goto done;
case_13:
    field->text = g_SelectPromptTextGroupFiveCase13Text;
    goto done;
case_14:
    field->text = g_SelectPromptTextGroupFiveCase14Text;
    goto done;
case_15:
    field->text = g_SelectPromptTextGroupFiveCase15Text;
done:
    return 0;
}

s32 Pak_SelectModalPromptLabel(struct PakActionLabelView *field) {
    u32 state = g_controllerPakPromptKind;

    if (state >= 16) {
        goto state_other;
    }
    switch (state) {
        case 0: goto state_other;
        case 1: goto state_other;
        case 2: goto state_other;
        case 3: goto state_other;
        case 4: goto state_other;
        case 5: goto state_other;
        case 6: goto state_other;
        case 7: goto state_other;
        case 8: goto case_1;
        case 9: goto state_other;
        case 10: goto state_other;
        case 11: goto state_other;
        case 12: goto state_other;
        case 13: goto state_other;
        case 14: goto state_other;
        case 15: goto state_other;
        }
state_other:
    field->text = g_SelectModalPromptLabelStateOtherText;
    goto done;
case_1:
    field->text = g_SelectModalPromptLabelCase1Text;
done:
    return 0;
}

s32 Pak_CheckOperationPakChange(struct Shared_PakMenu *record) {
    if (g_pakNamePromptAccepted == 0) {
        if (Pak_GetMenuChannel(record) != -1) {
            if (Control_PeekPakChange(Pak_GetMenuChannel(record)) != 0) {
                if (Snapshot_CheckStatusPrompt(record, Pak_GetMenuChannel(record), 0) != 0) {
                    g_pakNamePromptAccepted = 1;
                }
            }
        }
    }
    return g_pakNamePromptAccepted;
}

/* Stores 0 in g_pakNamePromptAccepted and 1 in g_pakAlternateNameSelected. */

void Pak_EnableOperationHeading(void) {
    g_pakNamePromptAccepted = 0;
    g_pakAlternateNameSelected = 1;
}

/* Stores 0 in g_pakNamePromptAccepted and 0 in g_pakAlternateNameSelected. */

void Pak_DisableOperationHeading(void) {
    g_pakNamePromptAccepted = 0;
    g_pakAlternateNameSelected = 0;
}

/* Points a field's text at g_pakAlternateOperationHeadingLabel when the option g_pakAlternateNameSelected is set and at g_pakOperationHeadingLabel otherwise, and returns
   zero: the label an option menu shows for that option. */



s32 Pak_SelectOperationHeading(struct PakActionLabelView *field) {
    if (g_pakAlternateNameSelected != 0) {
        field->text = g_pakAlternateOperationHeadingLabel;
    } else {
        field->text = g_pakOperationHeadingLabel;
    }
    return 0;
}

/* Points a field's text at g_pakAlternateOperationDescriptionLabel when the option g_pakAlternateNameSelected is set and at g_pakOperationDescriptionLabel otherwise, and returns
   zero: the label an option menu shows for that option. */



s32 Pak_SelectOperationDescription(struct PakActionLabelView *field) {
    if (g_pakAlternateNameSelected != 0) {
        field->text = g_pakAlternateOperationDescriptionLabel;
    } else {
        field->text = g_pakOperationDescriptionLabel;
    }
    return 0;
}


#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/PAK_MENU.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "ENGINE/DEFS.H"
#if defined(VERSION_US)
INCLUDE_RODATA("game_data", k_statusUpdateStatusTextJumpTableTrailingZeroWord);
#endif
extern char g_pakTwoDigitValueFormat[];
extern char *g_pakAlternateChannelLabelTexts[];

s32 Pak_FormatOperationChannelLabel(struct Field *field, Shared_PakMenu *pThis) {
    char *text;
    char **strings;
    s32 value;
    if (g_pakUseScannedChannel != 0) {
        value = g_introSelectedItem;
    } else {
        value = pThis->owner->controllerPort;
    }
    if (g_pakAlternateNameSelected != 0) {
        field->text = g_pakAlternateChannelLabelTexts;
    } else {
        strings = g_pakChannelLabelTexts_eu;
        field->text = strings;
        text = strings[g_gameSettings.language];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2), g_pakTwoDigitValueFormat, value + 1);
    }
    return 0;
}
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#else
#endif
/* Takes g_introSelectedItem when g_pakUseScannedChannel is set and otherwise the signed byte at offset 4 of the second argument's record at 0x20, then shows g_pakAlternateChannelLabelTexts in a field when g_pakAlternateNameSelected is set and otherwise points the field at g_pakChannelLabelTexts and formats one more than that value into it with g_digitDotFormat_Profile two bytes before the length Menu_CountLineChars reports, returning zero.
   Adapted from Timer_UpdateOwnerChannelLabel with the value source chosen by g_pakUseScannedChannel, the text chosen by g_pakAlternateNameSelected, the offset two bytes, and the texts and format changed. */


extern u8 *g_pakAlternateChannelLabelTexts[];

extern char g_digitDotFormat[];

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
s32 Pak_FormatOperationChannelLabel(LayeredText *field, struct Shared_PakMenu *holder) {
    char *text;
    s32 value;

#if defined(VERSION_EU) || defined(VERSION_EU_X)
    u8 **table;

#else
#endif
    if (g_pakUseScannedChannel != 0) {
        value = g_introSelectedItem;
    } else {
        value = holder->owner->controllerPort;
    }
    if (g_pakAlternateNameSelected != 0) {
        field->text = g_pakAlternateChannelLabelTexts;
    } else {

#if defined(VERSION_EU) || defined(VERSION_EU_X)
        table = ((u8 **)(void *)g_pakChannelLabelTexts_eu);
        field->text = table;
        text = (char *)table[g_languageIndex];
#else
        field->text = ((u8 **)(void *)&g_pakChannelLabelTexts);
        text = ((char **)(void *)&g_pakChannelLabelTexts)[0];
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2), g_pakTwoDigitValueFormat, value + 1);
#else
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2), g_digitDotFormat, value + 1);
#endif
    }
    return 0;
}

#endif
#endif
