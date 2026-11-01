#ifndef COMMON_MENU_OPTIONS_AND_RESULTS_H
#define COMMON_MENU_OPTIONS_AND_RESULTS_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
struct PlayerStatisticsCountView;
typedef struct PlayerStatisticsCountView PlayerStatisticsCountView;


struct PlayerStatisticsCountView;
struct PlayerStatisticsCountView {
    char pad0[2];
    s16 totalDeaths;
    s16 totalKills;
    char pad6[0x96 - 6];
};

struct CompactOptionsCommitContext;
typedef struct CompactOptionsCommitContext CompactOptionsCommitContext;

struct StateFrontendHandlePlayModeShortcut;
struct StateFrontendHandlePlayModeShortcut {
    void *first;
    char pad4[0x18 - 4];
    s32 value;
};



struct OptionsCommitContext;
struct OptionsCommitContext {
    void *menu;
    void *title;
    void * gammaSlider;
    void * bloodModeList;
    void * twoPlayerScreenList;
    void * resolutionList;
    s32 reserved18[2];
    s32 value;
    s32 state;
};







struct ChoiceMenuCellView;
struct MenuFrontendUpdatePlayModeMenu;
struct StateFrontendUpdatePlayModeMenu;
struct StateFrontendUpdatePlayModeMenu {
    struct MenuFrontendUpdatePlayModeMenu *menu;
    char pad4[0x8 - 0x4];
    struct ChoiceMenuCellView *list;
    s32 opening;
    char pad10[0x14 - 0x10];
    s32 delay;
    s32 target;
};


struct TabOptionsCommitContext;
struct TabOptionsCommitContext {
    char pad0[0x50];
    void * gammaSlider;
    void * bloodModeList;
    void * resolutionList;
};

struct TabOptionsCommitContext;
typedef struct TabOptionsCommitContext TabOptionsCommitContext;

struct MessageScreen;
struct MessageScreen {
    char pad0[0x1C];
    s32 shown;
    char pad20[0x30 - 0x20];
    s32 mode;
    s32 next_mode;
    char pad38[0x44 - 0x38];
    void *window;
    char pad48[0x4C - 0x48];
    void *second_window;
    char pad50[0x60 - 0x50];
    s32 timer;
};


struct CompactOptionsCommitContext;
struct CompactOptionsCommitContext {
    void * gammaSlider;
    void * bloodModeList;
    void * resolutionList;
};


struct OptionsCommitContext;
typedef struct OptionsCommitContext OptionsCommitContext;


extern int g_loadoutWeaponIds[];
extern int g_trialBonusWeaponIds[];
extern int g_trialSpecialWeaponIds[];




extern void Menu_ReleaseOptionsScene_Optiontransition();

extern s32 ScenarioSetup_IsCupSelected(void);
enum MatchEnd {
    MATCH_END_TIME_UP,
    MATCH_END_SCORE_LIMIT,
    MATCH_END_TAG_LIMIT,
    MATCH_END_POINT_TARGET
};
extern f32 g_resultBadgeDrawParameters[];
extern f32 g_resultBadgeDefaultAlpha;
extern void Frontend_DrawResultSelectionPreview(void);

extern void Menu_SetOptionsSceneSelection(s32);

extern char g_characterAndTimeFormatText[];
extern char g_resultsBestTimeFormat[];
extern char g_resultsBestTimePlaceholder[];
extern void Random_ReplaceTextOccurrences(char *, char *, char *);


extern s32 Control_IsControllerConnected(s32);
#endif
