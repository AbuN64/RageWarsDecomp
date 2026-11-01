#ifndef COMMON_RESULTS_TEXT_H
#define COMMON_RESULTS_TEXT_H
/* Results-screen texts: one per language in PAL builds, chosen by the game settings. */
#include "TYPES.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/MENU_TEXT.H"
/* The game settings record. */
static inline Shared_Game *currentGame(void) {
    return &g_gameSettings;
}
#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* PAL builds keep one text per language, chosen by the game settings. */
#define RESULTS_LANGUAGE (currentGame()->language)
extern ResultsHeadingCharacter g_resultCharacterHeadingTranslations[];
extern char g_resultsHeadingText[];
extern u8 *g_characterPreviewTextReferenceEu1[];
extern char *g_characterPreviewTextReferenceShared6[];
extern char *g_characterPreviewTextReferenceEu3[];
extern char *g_characterPreviewTextReferenceShared7[];
extern char *g_characterPreviewTextReferenceShared8[];
extern char *g_resultsRoundsOneFormatLocalized[];
extern char *g_resultsRoundsTwoFormatLocalized[];
extern char *g_resultsRoundsThreeFormatLocalized[];
extern char *g_resultsLapsOneFormatLocalized[];
extern char *g_resultsLapsTwoFormatLocalized[];
extern char *g_resultsLapsThreeFormatLocalized[];
extern char *g_resultsLapsFourFormatLocalized[];
extern char *g_resultsLapsFiveFormatLocalized[];
extern char *g_resultsGoalOneFormatLocalized[];
extern char *g_resultsGoalTwoFormatLocalized[];
extern char *g_resultsTimeLimitFormatLocalized[];
extern char *g_resultsMinutesSecondsOneFormatLocalized[];
extern char *g_resultsMinutesSecondsTwoFormatLocalized[];
extern char *g_resultsMinutesOneFormatLocalized[];
extern char *g_resultsMinutesTwoFormatLocalized[];
extern char *g_resultsPlayerOrLivesOneFormatLocalized[];
extern char *g_resultsPlayerOrLivesTwoFormatLocalized[];
extern char *g_resultsGoalLabelFormatLocalized[];
extern char *g_resultsGoalValueFormatLocalized[];
extern char *g_slotSelectionTextReferenceEu7[];
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
