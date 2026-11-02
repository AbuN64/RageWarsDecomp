#include "COMMON/RECORDRECATCV1.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "MENU/PAK_PREVIEW_VIEWS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
extern PakPreview *g_controllerPakSnapshotPayload;
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/MENURECAT24.H"
#include "MENU/PAK/TIMER_UPDATEOPERATIONCHOICELABEL.H"
#include "ENGINE/DEFS.H"

extern s32 g_pakUseScannedChannel;









extern char *g_unlockedLevelResultLabel[];


/* Sets g_pakAlternateOptionEnabled to one; Timer_DisableAlternatePrompt clears it. */



/* Points the output record's table at 0x14 at the variant for the display depth at 0x90 of
   g_controllerPakSnapshotPayload: 16 and 32 have their own, 8 and anything else use the default; returns 0. */









#if defined(VERSION_EU) || defined(VERSION_EU_X)
#endif

/* Formats the word at offset 0x1C of the structure g_controllerPakSnapshotPayload points to, shifted down eight bits,
   into a field's text with the format g_pakFormatInt3_TimerUpdateoperationchoicelabel, three bytes before the length Menu_CountLineChars
   reports, and returns zero. */







extern s32 Menu_CountLineChars(struct Field *);


/* Selects a menu field's label table from the connection mode and the option index. */
s32 Timer_UpdateOperationChoiceLabel(struct Field *field, s16 *option_ptr) {
    s32 option;
    u32 rel;

    option = *option_ptr;
    rel = option - 3;
    if (g_pakProfileLoadActive != 0) {
        if (g_pakProfileLoadMode_de != 0) {
            field->text = g_pakProfileLoadProfileChoiceLabels;
        } else {
            field->text = g_pakProfileLoadSnapshotChoiceLabels;
        }
        goto done;
    }
    if (g_pakSaveMenuActiveDe != 0) {
        if (rel < 16) {
            field->text = g_pakSaveMenuNoteSlotChoiceLabels;
            return 0;
        }
        if (option == 21) {
            field->text = g_unlockedLevelResultLabel;
        } else if (g_pakProfileLoadMode_de != 0) {
            field->text = g_pakSaveMenuProfileChoiceLabels;
        } else {
            field->text = g_pakSaveMenuSnapshotChoiceLabels;
        }
        goto done;
    }
    if (g_pakUseScannedChannel != 0) {
        field->text = g_pakScannedChannelChoiceLabels;
    }
done:
    return 0;
}

s32 Timer_SetManagerHeading(struct MenuLabelPointerView *record) {
    if (g_pakUseScannedChannel != 0) {
        record->label = g_pakScannedChannelManagerHeading;
    }
    return 0;
}

void Timer_EnableAlternatePrompt(void) {
    g_pakAlternateOptionEnabled = 1;
}

void Timer_DisableAlternatePrompt(void) {
    g_pakAlternateOptionEnabled = 0;
}

s32 Timer_UpdateAlternatePromptLabel(struct PakActionLabelView *field) {
    if (g_pakAlternateOptionEnabled != 0) {
        field->text = g_pakNoteLabelSlots;
    } else {
        field->text = g_pakAlternatePromptDefaultLabel;
    }
    return 0;
}

int Timer_UpdatePreviewDepthLabel(MenuLabelPointerView *out) {
    switch (g_controllerPakSnapshotPayload->depth) {
    case 8:
    default:
        out->label = &g_pakPreviewDepthEightLabel;
        break;
    case 16:
        out->label = &g_pakPreviewDepthSixteenLabel;
        break;
    case 32:
        out->label = &g_pakPreviewDepthThirtyTwoLabel;
        break;
    }
    return 0;
}

s32 Timer_FormatPreviewPageCount(struct Field *field) {
    s32 value = g_controllerPakSnapshotPayload->value >> 8;
    char *text =
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        field->text[g_languageIndex];
#else
        *field->text;
#endif

    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 3), g_pakFormatInt3, value);
    return 0;
}
