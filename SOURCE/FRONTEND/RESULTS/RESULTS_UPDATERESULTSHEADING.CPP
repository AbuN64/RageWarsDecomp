#include "include_asm.h"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/SCENE_FRAME_AND_EFFECT_UPDATES.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "TYPES.H"
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "FRONTEND/RESULTS_UPDATERESULTSHEADING.H"
#include "ACHIEVE/ACHIEVE.H"
#include "FRONTEND/RESULTS.H"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern struct ResultsHeadingCharacter g_resultCharacterHeadingTranslations[];
#define RES_TIMEFMT g_resultsBestTimeFormatEuro
#define RES_TIMEPOST g_resultsBestTimePlaceholderEuro
#define RES_HEAD3 ((char *)g_resultsThreePlayerHeadingTranslations[g_languageIndex])
#define RES_HEAD4 ((char *)g_resultsFourPlayerHeadingTranslations[settings->language])
#define RES_NAME(m) (((char **)g_resultCharacterHeadingTranslations[m].name)[settings->language])
#else
#define RES_TIMEFMT g_resultsBestTimeFormat
#define RES_TIMEPOST g_resultsBestTimePlaceholder
#define RES_HEAD3 g_resultsThreePlayerHeadingText
#define RES_HEAD4 g_resultsFourPlayerHeadingText
#define RES_NAME(m) (g_resultCharacterHeadings[m].name->text)
#endif
/* Writes the heading of the results screen g_trialCatalogueScreen into item 0x153: in one-player mode the
   label 0x69 followed by the name of the character in the player's status record; in three-player
   mode the label 0x3D with the stage's best time as minutes and seconds in item 0x156 (the record's
   time when set, else the stage default from Achieve_CopyPreset) and the heading g_resultsThreePlayerHeadingText; in
   four-player mode the heading g_resultsFourPlayerHeadingText. */

/* The results screen item and phrase ids renumber on the de cartridge: its heading item is 0x151,
   its name phrase 0x6B, its time phrase 0x3F and its time item 0x154; on eu-x 0x157, 0x6C, 0x40 and
   0x15A. eu and eu-x pick the heading and character name strings by language (RES_* above). */
#if defined(VERSION_DE)
enum { HEADING_ITEM = 337, NAME_PHRASE = 107, TIME_PHRASE = 63, TIME_ITEM = 340 };
#elif defined(VERSION_EU_X)
enum { HEADING_ITEM = 343, NAME_PHRASE = 108, TIME_PHRASE = 64, TIME_ITEM = 346 };
#else
enum { HEADING_ITEM = 339, NAME_PHRASE = 105, TIME_PHRASE = 61, TIME_ITEM = 342 };
#endif

extern struct ResultsHeadingScreen *g_trialCatalogueScreen;
extern struct ResultsHeadingRecord g_localPlayerProfiles[];
extern struct ResultsHeadingCharacter g_resultCharacterHeadings[];

extern u8 *XPlus_CopyString(u8 *destination, u8 *source);
extern s32 Key_FindKeyIndex(s32);
extern s32 XStdio_FormatBuffer(void *goal, s32 fmt0, ...);

void Results_UpdateResultsHeading(void) {
    Shared_Game *settings;
    struct Label *item;
    s32 time;
    u8 best;
    char buffer[32];

    /* the hub lookup returns its Item view; the Label view names the text pointer this unit writes */
    ((struct Label *) Node_FindWidgetByResourceId(g_trialCatalogueScreen->window, HEADING_ITEM))->text = g_trialCatalogueScreen->heading;
    settings = &g_gameSettings;
    switch (settings->controllerMode) {
    case 1:
        XPlus_CopyString(g_trialCatalogueScreen->heading, Node_GetStringByIndex(NAME_PHRASE));
        Random_ReplaceTextOccurrences(g_trialCatalogueScreen->heading, g_characterAndTimeFormatText,
                      RES_NAME(Key_FindKeyIndex(settings->playerSettings[g_trialCatalogueScreen->record].character)));
        break;
    case 3:
        XPlus_CopyString(g_trialCatalogueScreen->time, Node_GetStringByIndex(TIME_PHRASE));
        item = (struct Label *) Node_FindWidgetByResourceId(g_trialCatalogueScreen->window, TIME_ITEM);
        Widget_SetWidgetFlag08(item, 1);
        item->text = g_trialCatalogueScreen->time;
        time = g_localPlayerProfiles[g_trialCatalogueScreen->record].times[g_trialCatalogueScreen->stage];
        if (time > 0) {
            XStdio_FormatBuffer(buffer, RES_TIMEFMT, time / 60, time % 60);
        } else {
            best = ((struct ResultsHeadingStage *) Achieve_CopyPreset(g_trialCatalogueScreen->stage, 3, 0))->time;
            XStdio_FormatBuffer(buffer, RES_TIMEFMT, (u8)(best / 60), (u8)(best % 60));
        }
        Random_ReplaceTextOccurrences(g_trialCatalogueScreen->time, RES_TIMEPOST, buffer);
        XPlus_CopyString(g_trialCatalogueScreen->heading, RES_HEAD3);
        break;
    case 4:
        XPlus_CopyString(g_trialCatalogueScreen->heading, RES_HEAD4);
        break;
    }
}
