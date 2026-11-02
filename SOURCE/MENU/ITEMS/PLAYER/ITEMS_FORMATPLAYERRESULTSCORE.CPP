#include "ENGINE/DEFS.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/ACTORRECAT260.H"
#include "COMMON/TEXTLAYERMETRICS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#include "COMMON/MENURECAT20V1.H"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "ENGINE/DEFS.H"
extern Shared_MenuData g_playerViewRenderContext;
extern s16 g_playerResultScoreFields[];

s32 Player_FormatPlayerResultScore(LayeredText *field, struct MenuRules *holder) {
    Shared_MenuData *players = &g_playerViewRenderContext;
    s32 player = Player_GetPlayerIndex(players, holder->locked);
    s32 value = g_playerResultScoreFields[player * 75];
    char *text = (char *)field->text[players->game.language];
    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_playerMenuValueFormat, value);
    return 0;
}
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#if defined(VERSION_EU) || defined(VERSION_EU_X)

#else
#endif
/* Formats the halfword g_playerResultScoreFieldsDe holds for the player Player_GetPlayerIndexDe identifies from the owner at offset
   0x1C of the second argument, player records being 150 bytes apart, into a field's text with the
   format g_fmtDec4PadDe four bytes before the length Menu_CountLineChars reports. Returns zero. */

#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern struct LocalizedInputState g_playerViewRenderContext;
#else
extern char g_playerViewRenderContext[];
#endif

extern char g_fmtDec4Pad[];
extern s32 Player_GetPlayerIndex(void *, unsigned int);
extern s32 Menu_CountLineChars(LayeredText *);

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
s32 Player_FormatPlayerResultScore(LayeredText *field, struct MenuRules *holder) {

#if defined(VERSION_EU) || defined(VERSION_EU_X)
    struct LocalizedInputState *players = &g_playerViewRenderContext;
    s32 player = Player_GetPlayerIndex(players, holder->locked);
#else
    s32 player = Player_GetPlayerIndex(g_playerViewRenderContext, holder->locked);
#endif

    s32 value = g_gameSettings.playerSettings[player].resultScore;
    char *text =

#if defined(VERSION_EU) || defined(VERSION_EU_X)
        (char *)field->text[players->language];
#else
        (char *)*field->text;
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_playerMenuValueFormat, value);
#else
    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_fmtDec4Pad, value);
#endif
    return 0;
}

#endif
#endif
