#ifndef COMMON_MENU_UI_PROVIDERS_H
#define COMMON_MENU_UI_PROVIDERS_H
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SHARED_GAMESLOT.H"
typedef struct MenuOptionBox {
    s32 reservedWord;
    s32 width;
    s32 height;
    f32 scaleX;
    f32 scaleY;
    s32 left;
    s32 right;
    s32 top;
} MenuOptionBox;
#include "COMMON/MENU_MATCH_GLOBALS.H"
extern f32 g_menuSpriteAlphaScale;
extern void OnScreen_DrawBevelBox(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
#endif
