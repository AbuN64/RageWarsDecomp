#include "Engine/defs.h"
#include "Menu/optioneditstate.h"
#include "types.h"
#include "include_asm.h"
#include "Common/shared_gameslot.h"
#include "Common/Lone/g_languageindex.h"
#include "Common/textlayermetrics.h"
#include "Common/runtime_declarations.h"
#include "Menu/menu_createmenufromparameters.h"
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "Common/effectrender.h"
#include "Common/triple.h"
#include "Common/globals.h"
#include "Common/shared_menureply.h"
#include "Menu/Pak/Button/button_symbols.h"

/* Replaces a field of the option block g_gameSettings with what Menu_AdjustValue returns
   for the second argument, that word, 0x10, 0, 0x80 and 0, and returns zero. */
s32 Pak_AdjustPackedButtonOption(void *first, void *second) {
    struct OptionsPakAdjustPackedButtonOption *options = &g_gameSettings;

    options->value = Menu_AdjustValue(second, options->value, 16, 0, 128, 0);
    return 0;
}

/* The step text ends in a four-character number field that the step code overwrites. */
#define BUTTON_STEP_NUMBER_LENGTH 4

static inline char *Button_StepNumberField_button(u8 *text, s32 textLength) {
    return (char *)text + (textLength - BUTTON_STEP_NUMBER_LENGTH);
}

/* Shows the packed button option: the zero text when the step is 0, otherwise the step text
   with the step number written into its trailing number field. */
s32 Pak_FormatPackedButtonOption(LayeredText *item) {
    u32 code;
    u8 *text;
    s32 length;
    Shared_Game *game = &g_gameSettings;

    code = (u32)game->lightingGamma >> 4;
    Cache_SetResourceActivityState((u32)Cache_GetResourceActivityState() + 2U);
    if (code == 0) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        item->text = g_packedButtonOptionZeroTextTableEu;
#else
        item->text = &g_packedButtonOptionZeroText;
#endif
    } else {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        item->text = g_packedButtonOptionStepTextTableEu;
        text = item->text[game->language];
#else
        item->text = &g_packedButtonOptionStepText;
        text = *item->text;
#endif
        length = Menu_CountLineChars(item);
        Defs_FormatIntegerValue((char *)text + (length - 4), g_playerMenuStepFormatGerman, code);
    }
    return 0;
}
