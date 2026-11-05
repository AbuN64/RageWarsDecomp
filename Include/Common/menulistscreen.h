#ifndef COMMON_MENULISTSCREEN_H
#define COMMON_MENULISTSCREEN_H
#include "Frontend/frontend.h"
#include "types.h"
#include "Common/resident_event_handler.h"
#include "Common/runtime_declarations.h"
struct FieldRow;
struct MenuFrontendUpdatePlayModeMenu;
struct StateMenuUpdateScrollingChoiceScreen;
struct StateMenuUpdateScrollingChoiceScreen {
    struct MenuFrontendUpdatePlayModeMenu *menu;
    char pad4[0x8 - 0x4];
    struct MenuWidget *list;
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

typedef struct StateMenuSelectPlayerSettingsEntry {
    char pad0[8];
    void *c;
    void *d;
    void *b;
    void *a;
    void *e;
} StateMenuSelectPlayerSettingsEntry;




extern s32 g_playerSettingsSlotNumberFormat;
extern s32 g_playerSettingsSlotNumberTranslations[];


extern void Random_SetMenuChoiceResult(s32);

extern struct ResidentEventHandlerEntry g_scrollingChoiceEventIds[];
extern struct FieldRow g_scrollingChoiceEventKinds[];
#endif
