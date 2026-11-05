#ifndef ACHIEVE_ADDRESS_SYMBOLS_H
#define ACHIEVE_ADDRESS_SYMBOLS_H
#include "Frontend/frontend_address_symbols.h"
#include "types.h"
#include "Common/active.h"
#include "Common/runtime_declarations.h"
typedef s32 (*ResultsActorEventHandler)(void *, s32, s32, s32, s32);
/* Symbols that exist only at a fixed ROM address; each is referenced through its address. */
extern char g_profileModePlayedLevels[4][5];
extern u8 g_profileAchievementProgressRows[][0x96];
extern s32 g_profileAchievementCountRows[][100];
extern u8 g_profileAchievementCounters[];
extern s8 g_matchAchievementQualificationFlagA;
extern s8 g_matchAchievementQualificationFlagB;
extern struct ResultsHeadingCharacter g_resultCharacterHeadings[];
extern char *g_resultCharacterUnlockFormat, *g_resultPreviouslyCompletedText, *g_resultCampaignCompleteText, *g_resultTrialsCompleteText;
extern char g_resultPercentFormat[];
extern f32 g_resultPreviewSmallScale;
extern f32 g_resultPreviewCameraZ;
extern f32 g_resultPreviewDefaultAlpha;
extern ResultsActorEventHandler g_resultsActorEventHandlers;
extern struct SelectionMessageScreen *g_resultsModelPreviewScreen;
extern f32 g_resultTimeToSeconds;
extern char g_resultPreviewNumberFormatDe[];
#endif
