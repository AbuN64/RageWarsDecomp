#include "ENGINE/DEFS.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/TEXTLAYERMETRICS.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/MENURECAT20V1.H"
#include "COMMON/ACTORRECAT260.H"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "ENGINE/DEFS.H"
extern Shared_MenuData g_playerViewRenderContext;
extern s16 g_playerRewardScoreFields[];

s32 Player_FormatPlayerRewardScore(LayeredText *field, struct MenuRules *holder) {
    Shared_MenuData *players = &g_playerViewRenderContext;
    s32 player = Player_GetPlayerIndex(players, holder->locked);
    s32 value = g_playerRewardScoreFields[player * 75];
    char *text = (char *)field->text[players->game.language];
    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_playerMenuValueFormat, value);
    return 0;
}
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/* Formats the halfword g_playerRewardScoreFieldsDe holds for the player Player_GetPlayerIndexDe identifies from the owner at offset
   0x1C of the second argument, player records being 150 bytes apart, into a field's text with the
   format g_fmtDec4PadDe four bytes before the length Menu_CountLineChars reports. Returns zero. */

extern char g_playerViewRenderContext[];
extern char g_fmtDec4Pad[];
extern s32 Player_GetPlayerIndex(void *, unsigned int);
extern s32 Menu_CountLineChars(LayeredText *);

s32 Player_FormatPlayerRewardScore(LayeredText *field, struct Holder *holder) {
    s32 player = Player_GetPlayerIndex(g_playerViewRenderContext, (u32)holder->owner);
    s32 value = g_gameSettings.playerSettings[player].score;
    char *text = (char *)*field->text;

    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_fmtDec4Pad, value);
    return 0;
}
#endif
