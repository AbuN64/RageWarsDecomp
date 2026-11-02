#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "MENU/OPTIONEDITSTATE.H"
#include "COMMON/TEXTLAYERMETRICS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#include "COMMON/GAMEPLAY_SOUND_TABLE.H"
#include "ENGINE/DEFS.H"

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1) || defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/SHARED_GAMESLOT.H"
#define VOLUME_BYTE g_gameSettings.volume[0]
#else
#define VOLUME_BYTE g_gameSettings.volume[0]
#endif
/* Selects a localized volume label and formats an intermediate value.
 * DE/US-rev1 source and proofs remain preserved separately. */

/* Points a field's text at one of g_volumeZeroNeutralLabelFixed, g_volumeZeroMaximumLabelFixed or g_volumeZeroMinimumLabelFixed when the option byte g_gameSettingsVolumeBytes measured from 0x80 in steps of eight is zero, fifteen or minus sixteen, and otherwise at g_volumeZeroValueLabelFixed with the step formatted into it, returning zero. Adapted from Pak_UpdateThirdVolumeLabel with g_soundEffectsVolumeOption_PakFormatvolumeslotone changed to g_gameSettingsVolumeBytes and the text slots g_volumeTwoMinimumLabel..g_volumeTwoValueLabel changed to g_volumeZeroMinimumLabelFixed..g_volumeZeroValueLabelFixed. */



extern s32 Menu_CountLineChars(LayeredText *);

s32 Pak_UpdateFirstVolumeLabel(LayeredText *field) {
    s32 step = (VOLUME_BYTE - 128) / 8;
    char *text;

    if (step == 0) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        field->text = g_volumeZeroNeutralLabels;
#else
        field->text = &g_volumeZeroNeutralLabelFixed;
#endif
    } else if (step == 15) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        field->text = g_volumeZeroMaximumLabels;
#else
        field->text = &g_volumeZeroMaximumLabelFixed;
#endif
    } else if (step == -16) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        field->text = g_volumeZeroMinimumLabels;
#else
        field->text = &g_volumeZeroMinimumLabelFixed;
#endif
    } else if (step > 0) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        field->text = g_volumeZeroValueLabels;
        text = (char *)field->text[g_gameSettings.language];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_volumePositiveStepFormat, step);
#else
        field->text = (u8 **)&g_volumeZeroValueLabelFixed;
        text = (char *)*field->text;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_pakFormatSpacedInt2, step);
#endif
    } else {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        field->text = g_volumeZeroValueLabels;
        text = (char *)field->text[g_gameSettings.language];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_volumeNegativeStepFormat, step);
#else
        field->text = (u8 **)&g_volumeZeroValueLabelFixed;
        text = (char *)*field->text;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_pakFormatSpacedInt3, step);
#endif
    }
    return 0;
}

#endif
