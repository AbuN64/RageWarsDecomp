#ifndef FRONTEND_RESULTS_SETUP_TEXT_H
#define FRONTEND_RESULTS_SETUP_TEXT_H
#include "Common/shared_gameslot.h"
#include "Common/Lone/g_languageindex.h"
struct ResultsHeadingCharacter;
struct Shared_Game;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern struct ResultsHeadingCharacter g_resultCharacterHeadingTranslations[];
extern char *g_resultCharacterUnlockTranslations[], *g_resultPreviouslyCompletedTranslations[], *g_resultCampaignCompleteTranslations[], *g_resultTrialsCompleteTranslations[];
extern char *g_resultUnavailableTranslations[], *g_resultTeamHeadingTranslations[], *g_resultModeHeadingTranslations[], *g_resultTrialModeTranslations[], *g_resultChallengeModeTranslations[];
static inline char *resultsUnavailable(struct Shared_Game *game) { return g_resultUnavailableTranslations[game->language]; }
static inline char *resultsFirstHeading(void) { return g_resultTeamHeadingTranslations[g_languageIndex]; }
static inline char *resultsSecondHeading(void) { return g_resultModeHeadingTranslations[g_languageIndex]; }
static inline char *resultsThirdHeading(void) { return g_resultTrialModeTranslations[g_languageIndex]; }
static inline char *resultsFourthHeading(void) { return g_resultChallengeModeTranslations[g_languageIndex]; }
#else
extern char *g_resultUnavailableText, *g_resultTeamHeadingText, *g_resultModeHeadingText, *g_resultTrialModeText, *g_resultChallengeModeText;
static inline char *resultsUnavailable(struct Shared_Game *game) { return g_resultUnavailableText; }
static inline char *resultsFirstHeading(void) { return g_resultTeamHeadingText; }
static inline char *resultsSecondHeading(void) { return g_resultModeHeadingText; }
static inline char *resultsThirdHeading(void) { return g_resultTrialModeText; }
static inline char *resultsFourthHeading(void) { return g_resultChallengeModeText; }
#endif
#if defined(VERSION_DE)
enum { RESULTS_HEADING1=567, RESULTS_HEADING2=566 };
#elif defined(VERSION_EU_X)
enum { RESULTS_HEADING1=575, RESULTS_HEADING2=576 };
#else
enum { RESULTS_HEADING1=570, RESULTS_HEADING2=571 };
#endif
#endif
