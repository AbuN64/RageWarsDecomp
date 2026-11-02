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
#define VOLUME_BYTE g_gameSettings.volume[2]
#else
#define VOLUME_BYTE g_gameSettings.volume[2]
#endif
/* Shows one of three fixed volume texts for steps zero, fifteen and minus
 * sixteen from the option byte g_soundEffectsVolumeOption_PakFormatvolumeslotone. Other steps are formatted into
 * the alternate text with the positive or negative format. */



extern s32 Menu_CountLineChars(LayeredText *);

s32 Pak_UpdateThirdVolumeLabel(LayeredText *field) {
    s32 step = (VOLUME_BYTE - 128) / 8;
    char *text;

    if (step == 0) {
        field->text = &g_volumeTwoNeutralLabel;
    } else if (step == 15) {
        field->text = &g_volumeTwoMaximumLabel;
    } else if (step == -16) {
        field->text = &g_volumeTwoMinimumLabel;
    } else if (step > 0) {
        field->text = (u8 **)&g_volumeTwoValueLabel;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (char *)field->text[g_gameSettings.language];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_volumePositiveStepFormat, step);
#else
        text = (char *)*field->text;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_pakFormatSpacedInt2, step);
#endif
    } else {
        field->text = (u8 **)&g_volumeTwoValueLabel;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (char *)field->text[g_gameSettings.language];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_volumeNegativeStepFormat, step);
#else
        text = (char *)*field->text;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_pakFormatSpacedInt3, step);
#endif
    }
    return 0;
}

#endif
