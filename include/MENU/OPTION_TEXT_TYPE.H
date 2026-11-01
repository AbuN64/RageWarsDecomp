#ifndef MENU_OPTION_TEXT_TYPE_H
#define MENU_OPTION_TEXT_TYPE_H
#include "TYPES.H"
typedef struct ToggleRowTextView ToggleRowTextView;
struct ToggleRowTextView {
    s32 toggleRow;
    char pad0[0x10];
    char **text;
};
#endif
