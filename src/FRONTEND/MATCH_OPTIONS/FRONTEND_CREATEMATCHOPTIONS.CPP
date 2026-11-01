#include "include_asm.h"
#include "COMMON/LEVEL_GOAL.H"
#include "TYPES.H"
#include "OPTIONS.H"
#include "FRONTEND/FRONTEND_ACTIVATEMATCHOPTIONACTION.H"
#include "COMMON/SHARED_GAMESLOT.H"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern char *g_matchOptionsSelectLabelFirstByLanguage[];
extern char *g_matchOptionsSelectLabelSecondByLanguage[];
extern char *g_matchOptionsCursorLabelFirstByLanguage[];
extern char *g_matchOptionsCursorLabelSecondByLanguage[];
extern char *g_matchOptionsCursorLabelThirdByLanguage[];
extern char *g_matchOptionsCursorLabelFourthByLanguage[];
extern char *g_matchOptionsCursorLabelFifthByLanguage[];
#define MO_TEXT(i, fixed, eu) ((eu)[settings->language])
#else
#define MO_TEXT(i, fixed, eu) (fixed)
#endif

#if defined(VERSION_DE)
enum { OPTIONS_TEXT = 859 };
#else
#if defined(VERSION_EU_X)
enum { OPTIONS_TEXT = 867 };
#else
enum { OPTIONS_TEXT = 863 };
#endif
#endif

extern struct MatchOptionsScreen *g_matchOptionsScreen;
extern char *g_matchOptionsSelectLabelFirst, *g_matchOptionsSelectLabelSecond, *g_matchOptionsCursorLabelFirst, *g_matchOptionsCursorLabelSecond, *g_matchOptionsCursorLabelThird, *g_matchOptionsCursorLabelFourth, *g_matchOptionsCursorLabelFifth;
extern struct Record *Cache_AllocateMemory(s32 size);
extern void Frontend_InitMenuImage(s32 *record, s32 first, s32 second, s32 third, s32 fourth);
extern s32 Join_CountOpenPlayerSlots(void);
extern void *Node_FindWidgetByResourceId(void *root, s32 identifier);
extern void Widget_SetWidgetFlag100(void *record, s32 enable);
extern struct RecordN64EngCreateNumericWidget *N64Eng_CreateNumericWidget(s32 sourceResourceId, s32 childResourceId, s32 minimumValue, s32 maximumValue, s32 wrapEnabled);
extern void *SmpButton_CreateListWidget(s32, s32);
extern void SmpButton_AppendListText(struct MenuListWidget *menu, u8 *text);
extern void SmpButton_WrapButtonWidget(s32);

s32 Frontend_CreateMatchOptions(void *root) {
    struct MatchOptionsScreen *screen;
    Shared_Game *settings;
    void *selectList;
    void *cursorList;

    screen = Cache_AllocateMemory(64);
    g_matchOptionsScreen = screen;
    Frontend_InitMenuImage(screen->transition, 103, 0, 0, 0);
    g_matchOptionsScreen->countCap = Join_CountOpenPlayerSlots();
    switch (g_currentResultMode.kind) {
    case 1:
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(root, OPTIONS_TEXT + 0), 1);
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(root, OPTIONS_TEXT + 4), 1);
        break;
    case 0:
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(root, OPTIONS_TEXT + 6), 1);
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(root, OPTIONS_TEXT + 4), 1);
        break;
    case 2:
    case 3:
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(root, OPTIONS_TEXT + 0), 1);
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(root, OPTIONS_TEXT + 6), 1);
        break;
    }
    g_matchOptionsScreen->widget24 = N64Eng_CreateNumericWidget(OPTIONS_TEXT + 4, OPTIONS_TEXT + 5, 0, 100, 1);
    g_matchOptionsScreen->widget28 = N64Eng_CreateNumericWidget(OPTIONS_TEXT + 2, OPTIONS_TEXT + 3, 0, 100, 1);
    g_matchOptionsScreen->widget2C = N64Eng_CreateNumericWidget(OPTIONS_TEXT + 0, OPTIONS_TEXT + 1, 0, 100, 1);
    g_matchOptionsScreen->widget30 = N64Eng_CreateNumericWidget(OPTIONS_TEXT + 6, OPTIONS_TEXT + 7, 0, 100, 1);
    g_matchOptionsScreen->countDefault = 0;
    if (g_matchOptionsScreen->countCap == 3) {
        g_matchOptionsScreen->countDefault = 1;
    }
    g_matchOptionsScreen->widget34 = N64Eng_CreateNumericWidget(OPTIONS_TEXT + 13, OPTIONS_TEXT + 14, g_matchOptionsScreen->countDefault,
                                            g_matchOptionsScreen->countCap, 1);
    selectList = SmpButton_CreateListWidget(OPTIONS_TEXT + 8, OPTIONS_TEXT + 9);
    {void **slot = &g_matchOptionsScreen->selectWidget; *slot = selectList;}
    settings = &g_gameSettings;
    SmpButton_AppendListText(selectList, MO_TEXT(0, g_matchOptionsSelectLabelFirst, g_matchOptionsSelectLabelFirstByLanguage));
    SmpButton_AppendListText(g_matchOptionsScreen->selectWidget, MO_TEXT(1, g_matchOptionsSelectLabelSecond, g_matchOptionsSelectLabelSecondByLanguage));
    cursorList = SmpButton_CreateListWidget(OPTIONS_TEXT + 15, OPTIONS_TEXT + 16);
    {void **slot = &g_matchOptionsScreen->cursorWidget; *slot = cursorList;}
    SmpButton_AppendListText(cursorList, MO_TEXT(2, g_matchOptionsCursorLabelFirst, g_matchOptionsCursorLabelFirstByLanguage));
    SmpButton_AppendListText(g_matchOptionsScreen->cursorWidget, MO_TEXT(3, g_matchOptionsCursorLabelSecond, g_matchOptionsCursorLabelSecondByLanguage));
    SmpButton_AppendListText(g_matchOptionsScreen->cursorWidget, MO_TEXT(4, g_matchOptionsCursorLabelThird, g_matchOptionsCursorLabelThirdByLanguage));
    SmpButton_AppendListText(g_matchOptionsScreen->cursorWidget, MO_TEXT(5, g_matchOptionsCursorLabelFourth, g_matchOptionsCursorLabelFourthByLanguage));
    SmpButton_AppendListText(g_matchOptionsScreen->cursorWidget, MO_TEXT(6, g_matchOptionsCursorLabelFifth, g_matchOptionsCursorLabelFifthByLanguage));
    SmpButton_WrapButtonWidget(OPTIONS_TEXT + 10);
    SmpButton_WrapButtonWidget(OPTIONS_TEXT + 11);
    SmpButton_WrapButtonWidget(OPTIONS_TEXT + 12);
    Frontend_LoadMatchOptionWidgets();
    Frontend_SyncMatchJoinSlots(0);
    Frontend_LoadMatchOptionWidgets();
    return 0;
}
