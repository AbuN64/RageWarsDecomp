#ifndef COMMON_NUMBERPADSCREEN_H
#define COMMON_NUMBERPADSCREEN_H
#include "Frontend/frontend.h"
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
extern void Menu_ApplyExtraOptionFlags(void);


extern float k_menuFadeInConstants;

extern void Menu_ReleaseOptionsScene(void);


extern void Menu_ShowExtraOptionsPanel(void);




struct MenuWidget;
struct NumberPadScreen;

struct NumberPadScreen;
typedef struct NumberPadScreen NumberPadScreen;


extern void Menu_OpenOptionsKeypad(void);

struct ResourceSmpFlickerCreateFlickerWidget;
typedef struct Meter {
    s32 amount;
    s32 done;
    s32 falling;
    struct ResourceSmpFlickerCreateFlickerWidget *bar;
} Meter;



extern float k_menuFadeOutConstants;


struct NumberPadScreen {
    union { s32 dialog; void *title; };
    void *list;
    void *window;
    void *buttons[4];
    char pad1C[4];
    struct MenuWidget *pad;
    char pad24[4];
    s32 length;
    s32 mode;
    s32 value;
    union { s32 open; s32 cursor; };
    union { s32 confirmed; s32 full; };
};



struct Triple;

#endif
