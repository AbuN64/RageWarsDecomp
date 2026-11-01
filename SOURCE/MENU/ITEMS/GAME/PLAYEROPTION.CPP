#include "include_asm.h"
#include "MENU/HOLDERRECAT1CV2.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/NODERECAT2A8.H"
#include "FRONTEND/SCREEN_VIDEO_MODE.H"
#include "ENGINE/DEFS.H"
/* Replaces the option halfword g_gamePackedOptions with what Menu_AdjustValue returns for the second argument,
   that halfword, 0x10, 0, 0x100 and 0, then stores its low byte in the byte after it, or 0xFF when
   the value is 0xFF or more. Returns zero. */
extern s32 Menu_AdjustValue(struct MenuValueStepView *menu,s32 value,s32 step,s32 minimum,s32 maximum,s32 wrap);
/* Replaces the byte at offset 0x79 of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) with what Menu_AdjustValue returns for the second argument, that byte, 8, 8, 0xF8 and 0, and returns zero. */
extern struct MenuSettings g_gameSettings;
#if defined(VERSION_EU)
/* Points an option field at the settings byte 0x79 of the holder's owner settings (or the defaults g_playerPartnerNameFallback) as a signed offset from 128 in steps of eight, using the text g_playerOption79ZeroText for zero and otherwise the text g_playerOption79StepText_eu formatted with g_playerMenuStepFormatGerman for a positive or g_playerMenuStepFormat for a negative step four bytes before the length Menu_CountLineChars reports, returning zero. */
/* Points an option field at the settings byte 0x79 of the holder's owner settings (or the defaults g_playerPartnerNameFallback) as a signed offset from 128 in steps of eight, using the text g_playerOption79ZeroText for zero and otherwise the text g_playerOption79StepText_eu_x formatted with g_playerMenuStepFormatGerman for a positive or g_playerMenuStepFormat for a negative step four bytes before the length Menu_CountLineChars reports, returning zero. */
/* Points an option field at the settings byte 0x79 of the holder's owner settings (or the defaults g_playerPartnerNameFallback) as a signed offset from 128 in steps of eight, using the text g_playerOption79ZeroText for zero and otherwise the text g_playerOption79StepText formatted with g_playerMenuStepFormatGerman for a positive or g_fmtSpaceDec3_Playeroption for a negative step four bytes before the length Menu_CountLineChars reports, returning zero. */
extern char *g_playerOption79StepText_eu;
#elif defined(VERSION_EU_X)
extern char *g_playerOption79StepText_eu_x;
#endif
extern s32 Menu_CountLineChars(struct Field *);
#if defined(VERSION_EU)
/* Replaces the byte at offset 0x7A of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) with what Menu_AdjustValue returns for the second argument, that byte, 8, 8, 0xF8 and 0, and returns zero. Adapted from Items_AdjustPlayerOption79 with the settings byte 0x7A changed. */
extern char *g_playerOption7AStepText_eu;
#elif defined(VERSION_EU_X)
extern char *g_playerOption7AStepText_eu_x;
#endif
/* Points a field's text at g_playerFlag82OnText when the byte at offset 0x82 of the settings the second argument's owner holds, or of the defaults g_playerPartnerNameFallback without an owner, is one, and at g_playerFlag82OffText otherwise, returning zero. Adapted from Pak_UpdateOwnerModeText with the settings lookup of Items_TogglePlayerFlag82 and the texts g_playerFlag82OnText and g_playerFlag82OffText changed, and a zero result local declared first to give the owner and settings pointers the cartridge's registers. */
/* Toggles the byte at offset 0x82 of the settings the object at offset 0x5D8 of the second
   argument's owner holds, or of the defaults g_playerPartnerNameFallback when there is no owner, and returns zero. */
/* Counts the timer g_controllerPakProbeState down by g_frameElapsedTime without passing zero, then sets bit 24 of the flag word at offset 8 of a record unless Defs_GetMemorySize reports 0x400000, in which case the bit is cleared, stores what Frontend_GetScreenModePalette_Playeroption returns at offset 0x14 and returns zero. Adapted from Pak_UpdateScreenModeAvailability with the timer countdown added, Defs_GetMemorySize called without arguments and bit 24 instead of bit 23 changed. */
extern f32 g_controllerPakProbeState;
extern f32 g_frameElapsedTime;
extern s32 Defs_GetMemorySize(void);
extern s32 Frontend_GetScreenModePalette();
s32 Items_AdjustPackedGameOption(void *first, void *second) {
    u16 *option = &g_gamePackedOptions;
    u8 limited;

    *option = Menu_AdjustValue(second, *option, 16, 0, 256, 0);
    limited = 0xFF;
    if (*option < 0xFF) {
        limited = ((u8 *) option)[1];
    }
    ((u8 *) option)[2] = limited;
    return 0;
}
s32 Items_AdjustPlayerOption79(void *first, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    settings->option79 = Menu_AdjustValue(holder, settings->option79, 8, 8, 248, 0);
    return 0;
}
s32 Items_FormatPlayerOption79Step(struct Field *field, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;
    s32 step;
    char *text;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    step = (settings->option79 - 128) / 8;
    if (step == 0) {
        field->text = &g_playerOption79ZeroText;
    } else if (step > 0) {
#if defined(VERSION_EU)
        field->text = &g_playerOption79StepText_eu;
#elif defined(VERSION_EU_X)
        field->text = &g_playerOption79StepText_eu_x;
#else
        field->text = &g_playerOption79StepText;
#endif
        text =
#if defined(VERSION_EU) || defined(VERSION_EU_X)
field->text[g_gameSettings.language]
#else
*field->text
#endif
;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_playerMenuStepFormatGerman, step);
    } else {
#if defined(VERSION_EU)
        field->text = &g_playerOption79StepText_eu;
#elif defined(VERSION_EU_X)
        field->text = &g_playerOption79StepText_eu_x;
#else
        field->text = &g_playerOption79StepText;
#endif
        text =
#if defined(VERSION_EU) || defined(VERSION_EU_X)
field->text[g_gameSettings.language]
#else
*field->text
#endif
;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_playerMenuStepFormat, step);
#else
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_fmtSpaceDec3, step);
#endif
    }
    return 0;
}
s32 Items_AdjustPlayerOption7A(void *first, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    settings->option7A = Menu_AdjustValue(holder, settings->option7A, 8, 8, 248, 0);
    return 0;
}
s32 Items_FormatPlayerOption7AStep(struct Field *field, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;
    s32 step;
    char *text;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    step = (settings->option7A - 128) / 8;
    if (step == 0) {
        field->text = &g_playerOption7AZeroText;
    } else if (step > 0) {
#if defined(VERSION_EU)
        field->text = &g_playerOption7AStepText_eu;
#elif defined(VERSION_EU_X)
        field->text = &g_playerOption7AStepText_eu_x;
#else
        field->text = &g_playerOption7AStepText;
#endif
        text =
#if defined(VERSION_EU) || defined(VERSION_EU_X)
field->text[g_gameSettings.language]
#else
*field->text
#endif
;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_playerMenuStepFormatGerman, step);
    } else {
#if defined(VERSION_EU)
        field->text = &g_playerOption7AStepText_eu;
#elif defined(VERSION_EU_X)
        field->text = &g_playerOption7AStepText_eu_x;
#else
        field->text = &g_playerOption7AStepText;
#endif
        text =
#if defined(VERSION_EU) || defined(VERSION_EU_X)
field->text[g_gameSettings.language]
#else
*field->text
#endif
;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_playerMenuStepFormat, step);
#else
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_fmtSpaceDec3, step);
#endif
    }
    return 0;
}
s32 Items_SelectPlayerFlag82Text(struct PakActionLabelView *field, struct PlayerSettingsTextHolder *holder) {
    s32 result = 0;
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0) {
        settings = holder->owner->settings;
    }
    if (settings->flag82 == 1) {
        field->text = g_playerFlag82OnText;
    } else {
        field->text = g_playerFlag82OffText;
    }
    return result;
}
s32 Items_TogglePlayerFlag82(void *unused, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0) {
        settings = holder->owner->settings;
    }
    if (settings->flag82 == 1) {
        settings->flag82 = 0;
    } else {
        settings->flag82 = 1;
    }
    return 0;
}
s32 Items_UpdateScreenModeMenuItem(struct MenuTextResultView *record) {
    g_controllerPakProbeState -= g_frameElapsedTime;
    if (g_controllerPakProbeState <= 0.0f) {
        g_controllerPakProbeState = 0.0f;
    }
    if (Defs_GetMemorySize() != 0x400000) {
        record->flags |= 0x1000000;
    } else {
        record->flags &= ~0x1000000;
    }
    record->value = Frontend_GetScreenModePalette();
    return 0;
}
s32 Items_RequestScreenModeFade(void) {
    if (g_controllerPakProbeState == 0.0f) {
        Frontend_StartScreenModeFade();
        g_controllerPakProbeState = (18.0f);
        g_frontendSavedVideoModeIndex = (u8)g_frontendCurrentVideoModeIndex;
    }
    return 0;
}
