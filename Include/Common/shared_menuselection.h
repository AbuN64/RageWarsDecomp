#ifndef COMMON_SHARED_MENUSELECTION_H
#define COMMON_SHARED_MENUSELECTION_H
#include "types.h"
struct Shared_MenuSelection;
typedef struct Shared_MenuSelection {
    u32 reservedWord;
    s8 index;
} Shared_MenuSelection;
typedef struct Shared_MenuHandle {
    u8 reservedPrefix[0x1C];
    struct SharedPlayer *owner;
    struct Shared_MenuSelection *selection;
} Shared_MenuHandle;
typedef struct Shared_MenuInput {
    u32 reservedPrefix[8];
    s32 buttons;
} Shared_MenuInput;

#include "Common/runtime_declarations.h"



#endif
