#ifndef COMMON_RESULTS_TEXT_H
#define COMMON_RESULTS_TEXT_H
struct ResultsHeadingCharacter;
struct Shared_Game;
/* Results-screen texts: one per language in PAL builds, chosen by the game settings. */
#include "types.h"
#include "Common/Lone/g_languageindex.h"
#include "Common/shared_gameslot.h"
#include "Common/menu_text.h"
/* The game settings record. */
static inline struct Shared_Game *currentGame(void) {
    return &g_gameSettings;
}
#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* PAL builds keep one text per language, chosen by the game settings. */
#define RESULTS_LANGUAGE (currentGame()->language)
extern struct ResultsHeadingCharacter g_resultCharacterHeadingTranslations[];
extern char g_resultsHeadingText[];
extern u8 *g_characterNamesLocalized[];
extern char *g_bastilleNameLocalized[];
extern char *g_syraNameLocalized[];
extern char *g_symbiontNameLocalized[];
extern char *g_talSetRaptorMantidMitesNamesLocalized[];
extern char *g_resultsRoundSingularFormatLocalized[];
extern char *g_resultsRoundsPluralFormatLocalized[];
extern char *g_resultsRoundsControllerModeFormatLocalized[];
extern char *g_resultsLapSingularFormatLocalized[];
extern char *g_resultsLapsPluralFormatLocalized[];
extern char *g_resultsLapsControllerModeFormatLocalized[];
extern char *g_resultsSingleLapSingularFormatLocalized[];
extern char *g_resultsSingleLapsPluralFormatLocalized[];
extern char *g_resultsGoalSingularFormatLocalized[];
extern char *g_resultsGoalsPluralFormatLocalized[];
extern char *g_resultsTimeLimitFormatLocalized[];
extern char *g_resultsMinuteSecondsSingularFormatLocalized[];
extern char *g_resultsMinutesSecondsPluralFormatLocalized[];
extern char *g_resultsMinuteSingularFormatLocalized[];
extern char *g_resultsMinutesPluralFormatLocalized[];
extern char *g_resultsPlayerOrLivesSingularFormatLocalized[];
extern char *g_resultsLivesPluralFormatLocalized[];
extern char *g_resultsGoalLabelFormatLocalized[];
extern char *g_resultsGoalValueFormatLocalized[];
extern char *g_slotAchievementTextPointers_EveryManForThemselves[];
#define RESULTS_CHARACTERS g_resultCharacterHeadingTranslations
#define RESULTS_NAME_FORMAT g_resultsHeadingText
#else
#define RESULTS_LANGUAGE 0
#define RESULTS_CHARACTERS g_resultCharacterHeadings
#define RESULTS_NAME_FORMAT g_resultsNameFormat_de
#endif
/* A results text in the language the game settings select. */
#define RESULTS_TEXT(fixed, table) RW_LOCALIZED_TEXT(fixed, table, table, RESULTS_LANGUAGE)
#endif
