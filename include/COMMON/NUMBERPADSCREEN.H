#ifndef COMMON_NUMBERPADSCREEN_H
#define COMMON_NUMBERPADSCREEN_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
extern void Menu_ApplyExtraOptionFlags(void);

struct ChoiceMenuCellView;

extern float k_menuFadeInConstants;

extern void Menu_ReleaseOptionsScene(void);


extern void Menu_ShowExtraOptionsPanel(void);




struct MenuWidget;
struct NumberPadScreen;

struct NumberPadScreen;
typedef struct NumberPadScreen NumberPadScreen;


extern void Menu_OpenOptionsKeypad(void);

struct Meter;
struct ResourceSmpFlickerCreateFlickerWidget;
struct Meter {
    s32 amount;
    s32 done;
    s32 falling;
    struct ResourceSmpFlickerCreateFlickerWidget *bar;
};

struct Meter;


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

struct ChoiceMenuCellView;


struct Triple;

struct RecGobjinstSampleBoneTranslation;
#endif
