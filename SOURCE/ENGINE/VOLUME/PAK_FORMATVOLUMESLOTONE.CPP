#include "ENGINE/DEFS.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/MENURECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "MENU/OPTIONEDITSTATE.H"
#include "ENGINE/VOLUME.H"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/SHARED_GAMESLOT.H"
#include "ENGINE/DEFS.H"

s32 Pak_FormatVolumeSlotOne(struct Field *field) {
    s32 step = (g_gameSettings.volume[1] - 128) / 8;
    char *text;

    if (step == 0) {
        field->text = g_volumeOneNeutralLabel;
    } else if (step == 15) {
        field->text = g_volumeOneMaximumLabel;
    } else if (step == -16) {
        field->text = g_volumeOneMinimumLabel;
    } else if (step > 0) {
        field->text = g_volumeOneValueLabel;
        text = field->text[g_gameSettings.language];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_volumePositiveStepFormat, step);
    } else {
        field->text = g_volumeOneValueLabel;
        text = field->text[g_gameSettings.language];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_volumeNegativeStepFormat, step);
    }
    return 0;
}
#endif

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
/* Points a field's text at one of g_volumeOneNeutralLabel, g_volumeOneMaximumLabel or g_volumeOneMinimumLabel when the option byte g_soundEffectsVolumeOption measured from 0x80 in steps of eight is zero, fifteen or minus sixteen, and otherwise at g_volumeOneValueLabel with the step formatted into it, returning zero. Adapted from Pak_UpdateThirdVolumeLabel with g_soundEffectsVolumeOption_PakFormatvolumeslotone changed to g_soundEffectsVolumeOption and the text slots g_volumeTwoMinimumLabel..g_volumeTwoValueLabel changed to g_volumeOneMinimumLabel..g_volumeOneValueLabel. */

extern s32 Menu_CountLineChars(struct Field *);

s32 Pak_FormatVolumeSlotOne(struct Field *field) {
    s32 step = (g_gameSettings.volume[1] - 128) / 8;
    char *text;

    if (step == 0) {
        field->text = &g_volumeOneNeutralLabel;
    } else if (step == 15) {
        field->text = &g_volumeOneMaximumLabel;
    } else if (step == -16) {
        field->text = &g_volumeOneMinimumLabel;
    } else if (step > 0) {
        field->text = &g_volumeOneValueLabel;
        text = *field->text;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_pakFormatSpacedInt2, step);
    } else {
        field->text = &g_volumeOneValueLabel;
        text = *field->text;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_pakFormatSpacedInt3, step);
    }
    return 0;
}
#endif
