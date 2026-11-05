#ifndef MENU_PAK_RECORDS_H
#define MENU_PAK_RECORDS_H
#include "types.h"

struct EntryPakCreateMenuFromParameters {
    s16 type;
    char pad[0x22];
};

struct TargetPakSelectPromptKindEight {
    char pad[0x120];
    s32 flags;
};

#endif
