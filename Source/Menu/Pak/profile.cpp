#include "Menu/menu_event_handlers.h"
extern s32 g_pakProfileSavePending;
#include "Common/pak_preview_selection.h"
#include "Common/Lone/g_pakprofileactiondialogresource.h"
#include "Common/Lone/g_languageindex.h"
#include "Menu/pak_load.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/snapshot_actor.h"
#include "Common/player_message_menu.h"
#include "Menu/pak_action_prompt.h"
#include "Common/textlayermetrics.h"
#include "Menu/Pak/profile.h"
#include "Engine/defs.h"
#include "Common/frontend_video_mode.h"
#include "include_asm.h"
#include "Common/triple.h"
#include "Common/effectrender.h"
#include "Menu/menu_createmenufromparameters.h"
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "Snapshot/g_digitdotformat.h"
#include "Snapshot/pak_profile_rank_score_format.h"
#include "Snapshot/snapshot_checkstatusprompt.h"
#include "Common/sessionhandlerrow.h"
#include "Menu/Pak/Profile/profile_symbols.h"
#if ((defined(VERSION_EU) || defined(VERSION_EU_X)))
#include "Common/pak_menu.h"
#endif
#if ((defined(VERSION_EU) || defined(VERSION_EU_X)))
#include "Common/shared_gameslot.h"
#include "Menu/menu_event_handlers.h"
#endif

/* Latches g_pakNamePromptAccepted to one when the record's team value is not -1 and both Control_PeekPakChange_Pak and Snapshot_CheckStatusPrompt accept it, then returns g_pakNamePromptAccepted. */
static inline s32 Pak_GetMenuChannel_profile(struct Shared_PakMenu *record) {
    if (g_pakUseScannedChannel != 0) {
        return g_introSelectedItem;
    }
    return record->owner->controllerPort;
}

s32 Pak_FormatPreviewFourDigitValue(LayeredText *field) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    s32 value = g_pakProfileRankScore;
    char *text = field->text[g_languageIndex];

    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_pakProfileValueFormat, value);
#else
    s32 value = g_pakLoadedProfile.values[2];
    char *text = *field->text;

    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_pakProfileRankScoreFormat, value);
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

int Pak_OpenProfileActionPrompt(int entry, PakActionPromptItemView *item) {
    if (g_pakProfileLoaded != 0) {
        Menu_OpenDialog(&g_matchEndingTeamWheelClose, g_pakProfileActionDialogResource, item->x, item->y, 0);
    } else {
        Menu_OpenDialog(&g_matchEndingTeamWheelClose, item->label, item->x, item->y, 0);
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

void Pak_SelectPromptKindEight(MenuBuildState *record) {
    record->entries[7].flags &= ~0x04000000;
    g_controllerPakPromptKind = 8;
    record->entries[7].flags |= 8;
    Control_ClearMenuControlFlag();
}

void Pak_SelectProfilePrompt(void) {
    g_controllerPakPromptKind = 9;
    g_pakProfileSavePending = 0;
}

void Pak_SelectProfilePromptWithSavePending(void) {
    g_controllerPakPromptKind = 9;
    g_pakProfileSavePending = 1;
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

    switch (state) {
        case 0:
        default:
            field->text = g_promptActionHeadingDefault;
            break;
        case 5:
        case 6:
        case 9:
        case 10:
        case 12:
        case 15:
            field->text = g_promptActionHeadingText;
            break;
    }
    return 0;
}

s32 Pak_SelectPromptTextGroupOne(struct PakActionLabelView *field) {
    u32 state = g_controllerPakPromptKind;

    switch (state) {
        case 0:
        default:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_DEFAULT][0];
            break;
        case 1:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND1][0];
            break;
        case 2:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND2][0];
            break;
        case 3:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND3][0];
            break;
        case 4:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND4][0];
            break;
        case 5:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND5][0];
            break;
        case 6:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND6][0];
            break;
        case 7:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND7][0];
            break;
        case 8:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND8][0];
            break;
        case 9:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND9][0];
            break;
        case 10:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND10][0];
            break;
        case 11:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND11][0];
            break;
        case 12:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND12][0];
            break;
        case 13:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND13][0];
            break;
        case 14:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND14][0];
            break;
        case 15:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND15][0];
            break;
    }
    return 0;
}

s32 Pak_SelectPromptTextGroupTwo(struct PakActionLabelView *field) {
    u32 state = g_controllerPakPromptKind;

    switch (state) {
        case 0:
        default:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_DEFAULT][1];
            break;
        case 1:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND1][1];
            break;
        case 2:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND2][1];
            break;
        case 3:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND3][1];
            break;
        case 4:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND4][1];
            break;
        case 5:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND5][1];
            break;
        case 6:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND6][1];
            break;
        case 7:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND7][1];
            break;
        case 8:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND8][1];
            break;
        case 9:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND9][1];
            break;
        case 10:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND10][1];
            break;
        case 11:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND11][1];
            break;
        case 12:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND12][1];
            break;
        case 13:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND13][1];
            break;
        case 14:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND14][1];
            break;
        case 15:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND15][1];
            break;
    }
    return 0;
}

s32 Pak_SelectPromptTextGroupThree(struct PakActionLabelView *field) {
    u32 state = g_controllerPakPromptKind;

    switch (state) {
        case 0:
        default:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_DEFAULT][2];
            break;
        case 1:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND1][2];
            break;
        case 2:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND2][2];
            break;
        case 3:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND3][2];
            break;
        case 4:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND4][2];
            break;
        case 5:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND5][2];
            break;
        case 6:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND6][2];
            break;
        case 7:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND7][2];
            break;
        case 8:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND8][2];
            break;
        case 9:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND9][2];
            break;
        case 10:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND10][2];
            break;
        case 11:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND11][2];
            break;
        case 12:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND12][2];
            break;
        case 13:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND13][2];
            break;
        case 14:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND14][2];
            break;
        case 15:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND15][2];
            break;
    }
    return 0;
}

s32 Pak_SelectPromptTextGroupFour(struct PakActionLabelView *field) {
    u32 state = g_controllerPakPromptKind;

    switch (state) {
        case 0:
        default:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_DEFAULT][3];
            break;
        case 1:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND1][3];
            break;
        case 2:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND2][3];
            break;
        case 3:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND3][3];
            break;
        case 4:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND4][3];
            break;
        case 5:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND5][3];
            break;
        case 6:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND6][3];
            break;
        case 7:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND7][3];
            break;
        case 8:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND8][3];
            break;
        case 9:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND9][3];
            break;
        case 10:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND10][3];
            break;
        case 11:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND11][3];
            break;
        case 12:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND12][3];
            break;
        case 13:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND13][3];
            break;
        case 14:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND14][3];
            break;
        case 15:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND15][3];
            break;
    }
    return 0;
}

s32 Pak_SelectPromptTextGroupFive(struct PakActionLabelView *field) {
    u32 state = g_controllerPakPromptKind;

    switch (state) {
        case 0:
        default:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_DEFAULT][4];
            break;
        case 1:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND1][4];
            break;
        case 2:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND2][4];
            break;
        case 3:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND3][4];
            break;
        case 4:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND4][4];
            break;
        case 5:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND5][4];
            break;
        case 6:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND6][4];
            break;
        case 7:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND7][4];
            break;
        case 8:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND8][4];
            break;
        case 9:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND9][4];
            break;
        case 10:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND10][4];
            break;
        case 11:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND11][4];
            break;
        case 12:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND12][4];
            break;
        case 13:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND13][4];
            break;
        case 14:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND14][4];
            break;
        case 15:
            field->text = g_pakPromptLineCells[PAK_PROMPT_ROW_KIND15][4];
            break;
    }
    return 0;
}

s32 Pak_SelectModalPromptLabel(struct PakActionLabelView *field) {
    u32 state = g_controllerPakPromptKind;

    switch (state) {
        case 8:
            field->text = g_SelectModalPromptLabelEmptyText;
            break;
        default:
            field->text = g_SelectModalPromptLabelStateOtherText;
            break;
    }
    return 0;
}

s32 Pak_CheckOperationPakChange(struct Shared_PakMenu *record) {
    if (g_pakNamePromptAccepted == 0) {
        if (Pak_GetMenuChannel_profile(record) != -1) {
            if (Control_PeekPakChange(Pak_GetMenuChannel_profile(record)) != 0) {
                if (Snapshot_CheckStatusPrompt(record, Pak_GetMenuChannel_profile(record), 0) != 0) {
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
#if defined(VERSION_US)
INCLUDE_RODATA("game_data", k_statusUpdateStatusTextJumpTableTrailingZeroWord);
#endif

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
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2), g_pakProfileChannelValueFormat, value + 1);
    }
    return 0;
}
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/* Takes g_introSelectedItem when g_pakUseScannedChannel is set and otherwise the signed channel byte of the record the second argument carries, then shows g_pakAlternateChannelLabelTexts in a field when g_pakAlternateNameSelected is set and otherwise points the field at g_pakChannelLabelTexts and formats one more than that value into it with g_digitDotFormat_Profile into the last two characters of the field text (the length Menu_CountLineChars reports), returning zero.
   */
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
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2), g_pakProfileChannelValueFormat, value + 1);
#else
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2), g_digitDotFormat, value + 1);
#endif
    }
    return 0;
}

#endif
#endif
