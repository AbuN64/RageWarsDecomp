#ifndef MENU_PAK_MENU_ENTRIES_H
#define MENU_PAK_MENU_ENTRIES_H
#include "TYPES.H"
struct MenuCursorNavigationView {
    s16 cursor;
    char pad2[0xA];
    struct PakMenuChoiceEntry *entries;
    s32 count;
};
#endif
