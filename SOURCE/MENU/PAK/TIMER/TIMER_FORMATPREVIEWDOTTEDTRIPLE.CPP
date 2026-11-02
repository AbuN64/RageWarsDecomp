#include "COMMON/RECORDRECATCV1.H"
#include "COMMON/LONE/g_controllerPakReadyDialogResource.H"
#include "MENU/PAK_PREVIEW_VIEWS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/NAME.H"
#include "TYPES.H"
extern PakPreview *g_controllerPakSnapshotPayload;
#include "MENU/PAK/PROFILE_PREVIEW_AND_LINE_TEXT.H"
#include "ENGINE/DEFS.H"
#include "MENU/PAK/TIMER.H"

/* Calls Menu_ClassifyResourceRange on the word at offset 0x24 of the structure g_controllerPakSnapshotPayload points to and
   returns zero. */




#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
extern s32 Menu_ClassifyResourceRange(s32);
#else
extern s32 Pickup_ClassifyMenuCode(s32);
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)

#else
#endif


extern s32 Menu_CountLineChars(struct Field *);


/* Points a field's text at g_pakAlternateActionLabel when the option g_pakAlternateOptionEnabled is set and at g_pakActionLabel otherwise, and returns
   zero: the label an option menu shows for that option. */





extern char g_matchEndingTeamWheelClose[];


extern void *Menu_OpenDialog(void *parent, struct Dialog *list, s32 player, s32 controller, s32 d);

/* Stores 1 in g_pakProfileLoaded and 0 in g_pakUseDefaultPreviewLabels. */





s32 Timer_DispatchPreviewHandle(void) {

#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
Menu_ClassifyResourceRange
#else
Pickup_ClassifyMenuCode
#endif
(g_controllerPakSnapshotPayload->handle);
    return 0;
}

/* Formats the three floats at offsets 0xC, 0x10 and 0x14 of the structure g_controllerPakSnapshotPayload points to,
   truncated to integers, into a field's text with the format g_pakFormatDottedTriple_TimerFormatpreviewdottedtriple, nine bytes before the
   length Menu_CountLineChars reports. Returns zero. */

s32 Timer_FormatPreviewDottedTriple(struct Field *field) {
    s32 x = g_controllerPakSnapshotPayload->x;
    s32 y = g_controllerPakSnapshotPayload->y;
    s32 z = g_controllerPakSnapshotPayload->z;
    char *text =

#if defined(VERSION_EU) || defined(VERSION_EU_X)
        field->text[g_languageIndex];
#else
        *field->text;
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Defs_FormatThreeIntegers(text + (Menu_CountLineChars(field) - 9), g_pakDottedTripleFormat, z, y, x);
#else
    Defs_FormatThreeIntegers(text + (Menu_CountLineChars(field) - 9), g_pakFormatDottedTriple, z, y, x);
#endif
    return 0;
}

s32 Timer_UpdateAlternateActionLabel(struct PakActionLabelView *field) {
    if (g_pakAlternateOptionEnabled != 0) {
        field->text = g_pakAlternateActionLabel;
    } else {
        field->text = g_pakActionLabel;
    }
    return 0;
}

s32 Timer_OpenSelectedPrompt(void *unused, struct PakSelectedPromptView *record) {
    do {
        if (g_pakAlternateOptionEnabled != 0) {
            Menu_OpenDialog(g_matchEndingTeamWheelClose, g_controllerPakReadyDialogResource, record->first, record->second, 0);
        } else {
            Menu_OpenDialog(g_matchEndingTeamWheelClose, record->resource, record->first, record->second, 0);
        }
    } while (0);
    return 1;
}

void Timer_EnableProfilePreview(void) {
    g_pakProfileLoaded = 1;
    g_pakUseDefaultPreviewLabels = 0;
}

void Timer_ClearProfilePreview(void) {
    g_pakProfileLoaded = 0;
    g_pakUseDefaultPreviewLabels = 0;
}

void Timer_DisablePreviewSelection(struct PakPreviewSelectionView *record) {
    record->target->first &= ~0x01800000;
    g_pakProfileLoaded = 0;
    g_pakUseDefaultPreviewLabels = 1;
    record->target->second &= ~0x01800000;
}

s32 Timer_UpdatePreviewKindLabel(struct PakActionLabelView *field) {
    if (g_pakProfileLoaded != 0) {
        field->text = g_pakPreviewKindLabelProfile;
    } else if (g_pakUseDefaultPreviewLabels != 0) {
        field->text = g_pakPreviewKindLabelDefault;
    } else {
        field->text = g_pakPreviewKindLabelSelected;
    }
    return 0;
}
