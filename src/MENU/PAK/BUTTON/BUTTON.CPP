#include "ENGINE/DEFS.H"
#include "MENU/OPTIONEDITSTATE.H"
#include "TYPES.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/TEXTLAYERMETRICS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"

/* Replaces the word at offset 0x10 of the option block g_gameSettings with what Menu_AdjustValue returns
   for the second argument, that word, 0x10, 0, 0x80 and 0, and returns zero. */


extern s32 Menu_AdjustValue(struct MenuValueStepView *menu,s32 value,s32 step,s32 minimum,s32 maximum,s32 wrap);

s32 Pak_AdjustPackedButtonOption(void *first, void *second) {
    struct OptionsPakAdjustPackedButtonOption *options = &g_gameSettings;

    options->value = Menu_AdjustValue(second, options->value, 16, 0, 128, 0);
    return 0;
}


#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/SHARED_GAMESLOT.H"
#include "ENGINE/DEFS.H"
extern u8 *g_packedButtonOptionZeroTextTableEu[], *g_packedButtonOptionStepTextTableEu[];

s32 Pak_FormatPackedButtonOption(LayeredText *item) {
    u32 code;
    u8 *text;
    s32 length;
    Shared_Game *game = &g_gameSettings;
    code = (u32)game->lightingGamma >> 4;
    Cache_SetResourceActivityState((u32)Cache_GetResourceActivityState() + 2U);
    if (code == 0) item->text = g_packedButtonOptionZeroTextTableEu;
    else {
        item->text = g_packedButtonOptionStepTextTableEu;
        text = item->text[game->language];
        length = Menu_CountLineChars(item);
        Defs_FormatIntegerValue((char *)text + (length - 4), g_playerMenuStepFormatGerman, code);
    }
    return 0;
}
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern u8 *g_packedButtonOptionZeroTextTableEu[];
extern u8 *g_packedButtonOptionStepTextTableEu[];
#else
extern u8 *g_packedButtonOptionStepText;
#endif
extern s32 Cache_GetResourceActivityState(void);
extern void Cache_SetResourceActivityState(u32);
extern s32 Menu_CountLineChars(LayeredText *);

s32 Pak_FormatPackedButtonOption(LayeredText *item) {
    u32 code;
    u8 *text;
    s32 length;

    code = g_gameSettings.lightingGamma >> 4;
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
        text = item->text[g_languageIndex];
#else
        item->text = &g_packedButtonOptionStepText;
        text = *item->text;
#endif
        length = Menu_CountLineChars(item);
        Defs_FormatIntegerValue((char *)text + (length - 4), g_playerMenuStepFormatGerman, code);
    }
    return 0;
}
#endif
