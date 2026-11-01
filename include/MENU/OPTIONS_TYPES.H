#ifndef MENU_OPTIONS_TYPES_H
#define MENU_OPTIONS_TYPES_H
#include "TYPES.H"
struct MenuWidget;
struct MenuListWidget;
typedef struct Shared_OptionsScreen Shared_OptionsScreen;
struct Shared_OptionsScreen {
    u32 unknown00[7];
    s32 cursor;
    struct MenuWidget *leftTab;
    s32 leftStep;
    struct MenuWidget *rightTab;
    s32 rightStep;
    s32 page;
    s32 pages;
    void *title;
    struct MenuWidget *marker;
    struct MenuWidget *header;
    struct MenuWidget *footer;
    struct MenuWidget *pakIcon;
    struct MenuWidget *rumbleIcon;
    void *slider;
    struct MenuListWidget *firstList;
    struct MenuListWidget *secondList;
    s32 state;
    s32 selection;
    s32 sound;
    struct MenuWidget *prompt;
};
#endif
