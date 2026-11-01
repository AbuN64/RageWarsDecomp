#ifndef COMMON_MENULISTSCREEN_H
#define COMMON_MENULISTSCREEN_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
struct ChoiceMenuCellView;
struct MenuFrontendUpdatePlayModeMenu;
struct StateMenuUpdateScrollingChoiceScreen;
struct StateMenuUpdateScrollingChoiceScreen {
    struct MenuFrontendUpdatePlayModeMenu *menu;
    char pad4[0x8 - 0x4];
    struct ChoiceMenuCellView *list;
    s32 delay;
    s32 target;
    s32 seen;
};

struct MenuMenuCreateTitleButtonScreen;
struct ResourceSmpFlickerCreateFlickerWidget;
struct MenuMenuCreateTitleButtonScreen {
    void *title;
    void *button;
    struct ResourceSmpFlickerCreateFlickerWidget *item;
    s32 count;
    s32 selection;
};


struct MenuListScreen;
typedef struct MenuListScreen MenuListScreen;


struct Label;
struct MenuStepState;
struct MenuStepState {
    void *menu;
    char pad4[0x20 - 4];
    s32 value;
    char pad24[0x28 - 0x24];
    s32 item;
    struct Label *label;
    char text[1];
};

struct MenuListScreen;
struct MenuListScreen {
    void *panels[2];
    void *listB;
    void *listA;
    void *listC;
    s32 selection;
    void *window;
};

struct StateMenuSelectAlternatePlayerSettingsEntry;
struct StateMenuSelectAlternatePlayerSettingsEntry {
    void *c;
    void *d;
    void *b;
    void *a;
    void *e;
};

struct StateMenuSelectPlayerSettingsEntry;
struct StateMenuSelectPlayerSettingsEntry {
    char pad0[8];
    void *c;
    void *d;
    void *b;
    void *a;
    void *e;
};




extern s32 g_playerSettingsSlotNumberFormat;


extern void Random_SetMenuChoiceResult(s32);

extern FieldRow g_scrollingChoiceEventIds[];
extern FieldRow g_scrollingChoiceEventKinds[];
#endif
