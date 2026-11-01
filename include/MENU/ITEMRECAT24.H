#ifndef MENU_ITEMRECAT24_H
#define MENU_ITEMRECAT24_H
#include "COMMON/ITEMRECAT20V1.H"
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
#endif
