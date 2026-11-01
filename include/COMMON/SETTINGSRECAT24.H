#ifndef COMMON_SETTINGSRECAT24_H
#define COMMON_SETTINGSRECAT24_H
#include "TYPES.H"
#include "COMMON/ACTIVE.H"
#include "COMMON/ITEMRECAT20V1.H"
struct MatchTimeSettingView;
struct MatchTimeSettingView {
    char pad0[0x24];
    s8 timeSetting;
};

struct MatchTimeSettingView;
typedef struct MatchTimeSettingView MatchTimeSettingView;

struct MatchResultsRulesView;
typedef struct MatchResultsRulesView MatchResultsRulesView;

struct MatchResultsRulesView;
struct MatchResultsRulesView {
    char pad0[0x14];
    f32 timeLeft;
    char pad18[0x98 - 0x18];
    s32 lastStanding;
};

struct MatchResultsGameSettingsView;
struct MatchResultsGameSettingsView {
    char pad0[0xCAC];
    MatchTimeSettingView settings;
    char padCD1[0x1284 - 0xCD1];
    MatchResultsRulesView rules;
};


extern void ScenarioSetup_HideResultCatalogueWidgets(void);


extern void Frontend_AwardResultMilestones(void);

struct Shared_Rec3;
struct Shared_Rec3 {
    char pad0[0x91];
    u8 flag;
    u8 rank;
    char pad93[0x3];
};

struct ChoiceMenuCellView;
struct MenuFrontendUpdatePlayModeMenu;
struct StateFrontendUpdatePlayerCountScreen;
struct StateFrontendUpdatePlayerCountScreen {
    struct MenuFrontendUpdatePlayModeMenu *menu;
    char pad4[0x8 - 0x4];
    struct ChoiceMenuCellView *list;
    s32 delay;
    s32 target;
};

struct IntPair;

struct PlayerCountSettingsSlotView;
typedef struct PlayerCountSettingsSlotView PlayerCountSettingsSlotView;

extern void Frontend_ContinueCupOrOpenResults(void);

struct MatchScoreScreen;
typedef struct MatchScoreScreen MatchScoreScreen;
typedef struct MatchScoreScreen MatchScoreScreenView;


struct ResourceBank;
typedef struct ResourceBank ResourceBank;

struct ResourceBank;
struct ResourceBank {
    u16 ids[20];
};


struct MatchScoreScreen {
    s32 transition[7];
    s32 active;
    char pad20[0xC0];
    void * window;
    s32 buttonAddress;
    s32 first, count;
    union { s32 players[8]; void *data; };
    s32 icons[8][2];
    char killText[4][25], scoreText[4][25], ratioText[4][25], valueText[4][25];
    char name[64];
    s32 phase, mode, dirty, selection;
};




struct Shared_Rec3;
typedef struct Shared_Rec3 Shared_Rec3;

extern void Frontend_AwardResultAchievements(void);



extern void Frontend_OpenControllerModeResults(void);


struct MatchResultsGameSettingsView;
typedef struct MatchResultsGameSettingsView MatchResultsGameSettingsView;



extern void Frontend_HideResultBadgeGroup(s32 rootWidgetId);


extern s32 Frontend_GetMatchEndReason(void);

struct PlayerCountSettingsSlotView;
struct PlayerCountSettingsSlotView {
    char pad0[0x78];
    u8 active;
    char pad79[6];
    u8 index;
    char pad80[0x16];
};


extern void Frontend_InitMatchResultsMenu(void);

/* Results-screen group identifiers from each native menu resource set. */
#if defined(VERSION_DE)
enum { RESULTS_RANK_GROUP = 612, RESULTS_SECONDARY_GROUP = 617, RESULTS_MENU_SHIFT=-4, RESULTS_RIGHT_ITEM=618 };
#elif defined(VERSION_EU_X)
enum { RESULTS_RANK_GROUP = 621, RESULTS_SECONDARY_GROUP = 626, RESULTS_MENU_SHIFT=5, RESULTS_RIGHT_ITEM=627 };
#else
enum { RESULTS_RANK_GROUP = 617, RESULTS_SECONDARY_GROUP = 622, RESULTS_MENU_SHIFT=0, RESULTS_RIGHT_ITEM=615 };
#endif
#endif
