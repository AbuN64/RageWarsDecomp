#ifndef COMMON_MENU_UI_PROVIDERS_H
#define COMMON_MENU_UI_PROVIDERS_H
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/shared_gameslot.h"
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
#include "Common/menu_match_globals.h"
extern f32 g_menuSpriteAlphaScale;
extern void OnScreen_DrawBevelBox(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
#endif
