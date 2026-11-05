#ifndef MENU_PAK_ACTION_PROMPT_H
#define MENU_PAK_ACTION_PROMPT_H
#include "Menu/pak_records.h"
struct PakActionPromptItemView;
typedef struct PakActionPromptItemView PakActionPromptItemView;




struct PakActionPromptItemView;
struct PakActionPromptItemView {
    char pad[0x1C];
    int x;
    int y;
    char *label;
};







extern unsigned char g_controllerPakPreviewNameLastCharacter;






struct MenuPromptKindView;
struct MenuPromptKindView {
    char pad[0xC];
    struct TargetPakSelectPromptKindEight *target;
};

#endif
