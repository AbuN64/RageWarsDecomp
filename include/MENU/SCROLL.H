#ifndef MENU_SCROLL_H
#define MENU_SCROLL_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"




struct SmpButtonOwnerView;
struct MenuListWidget;
struct MenuListWidget {
    s32 words_00[3];
    s16 activeKind;
    s16 widgetKind;
    s32 words_10[2];
    s16 itemExtent;
    s16 reservedWord;
    s32 words_1C[4];
    s32 fields_2C[5];
    s32 reservedWord1;
    struct SmpButtonOwnerView *owner;
    struct Key entries[10];
    s32 index;
    s32 count;
};


extern s32 SmpButton_DispatchListEvent(void *actor, s32 event, s32 itemId, s32 value, s32 context);

struct SequenceTicksPerQuarterView;
struct Scroll;
struct Scroll {
    char pad[0x44];
    struct SequenceTicksPerQuarterView *bar;
    s32 length;
    s32 count;
    s32 item;
};
typedef struct Scroll Scroll;

struct MenuSliderWidget;
struct MenuSliderWidget {
    s32 words_00[3];
    s16 activeKind;
    s16 widgetKind;
    s32 words_10[2];
    s16 itemExtent;
    s16 reservedWord2;
    s32 words_1C[4];
    s32 fields_2C[5];
    s32 reservedWord3;
    struct MenuSliderWidget *bar;
    s32 length;
    s32 count;
    s32 item;
    s32 mode;
};

struct MenuListWidget;
typedef struct MenuListWidget MenuListWidget;


struct Scroll;

struct MenuSliderWidget;
typedef struct MenuSliderWidget MenuSliderWidget;
#endif
