#include "ENGINE/DEFS.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "MENU/HOLDERRECAT1CV2.H"
#include "COMMON/TEXTLAYERMETRICS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "COMMON/MENURECAT20V1.H"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/SHARED_GAMESLOT.H"
#include "ENGINE/DEFS.H"

s32 Items_FormatPackedGameOption(LayeredText *field) {
    char *text;
    s32 value = g_gameSettings.packedOptions >> 4;

    if (value == 0) {
        field->text = g_packedGameOptionZeroText;
    } else if (value == 16) {
        field->text = g_packedGameOptionSixteenText;
    } else {
        field->text = (u8 **)&g_packedGameOptionValueText;
        text = (char *)field->text[g_gameSettings.language];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2), g_fmtDec2Pad, value);
    }
    return 0;
}
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/* Shows g_packedGameOptionZeroText in a field when the top twelve bits of g_gamePackedOptions are zero, g_packedGameOptionSixteenText when they are sixteen, and otherwise points the field at g_packedGameOptionValueText and formats their value into it with g_fmtDec2Pad_ItemsFormatpackedgameoption two bytes before the length Menu_CountLineChars reports, returning zero. Adapted from Pak_FormatMusicPreview with the value taken from the top twelve bits of the halfword g_gamePackedOptions, a second fixed text for sixteen, and the texts and format changed. */




extern s32 Menu_CountLineChars(LayeredText *);

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
s32 Items_FormatPackedGameOption(LayeredText *field) {
    char *text;
    s32 value = g_gameSettings.packedOptions >> 4;

    if (value == 0) {
        field->text = g_packedGameOptionZeroText;
    } else if (value == 16) {
        field->text = g_packedGameOptionSixteenText;
    } else {
        field->text = (u8 **)&g_packedGameOptionValueText;
        text = (char *)*(u8 **)&g_packedGameOptionValueText;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2), g_fmtDec2Pad, value);
    }
    return 0;
}

#endif
#endif
