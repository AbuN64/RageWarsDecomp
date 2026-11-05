#ifndef MENU_OPTIONS_TYPES_H
#define MENU_OPTIONS_TYPES_H
#include "Frontend/frontend.h"
#include "types.h"
struct MenuWidget;
struct MenuListWidget;
typedef struct Shared_OptionsScreen Shared_OptionsScreen;
struct Shared_OptionsScreen {
    u32 unknown00[7];
    union { s32 cursor; s32 shown; s32 choice; };
    struct MenuWidget *leftTab;
    s32 leftStep;
    struct MenuWidget *rightTab;
    s32 rightStep;
    union { s32 page; s32 messageMode; };
    union { s32 pages; s32 messageNextMode; };
    void *title;
    struct MenuWidget *marker;
    struct MenuWidget *header;
    union { struct MenuWidget *footer; void *window; };
    struct MenuWidget *pakIcon;
    union { struct MenuWidget *rumbleIcon; void *second_window; };
    union { void *slider; void *gammaSlider; };
    union { struct MenuListWidget *firstList; void *bloodModeList; };
    union { struct MenuListWidget *secondList; void *resolutionList; };
    s32 state;
    union { s32 selection; s32 timer; s32 mode; };
    union { s32 sound; s32 arena; };
    struct MenuWidget *prompt;
};
#endif
